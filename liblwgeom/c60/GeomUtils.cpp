/**
 * Дополнительный набор геометрических функций для платформы С60
 * @author Юрин Роман 28.05.18
 */

#include "GeomUtils.hpp"
#include <assert.h>
#include <liblwgeom.h>

extern "C"{

	#include "liblwgeom/liblwgeom_internal.h"

	/**
	* Получает геометрию.
	* Извлекаем прямоугольное покрытие 3D без чтения всего значения и аллокаций.
	* Это позволяет произвести быстрый анализ анализ геометрических данных в том случае, когда сама геометрия велика.
	**/
	PG_FUNCTION_INFO_V1(c60_getBBOX3D);
	Datum c60_getBBOX3D(PG_FUNCTION_ARGS){
		GSERIALIZED *geom = (GSERIALIZED*)PG_DETOAST_DATUM(PG_GETARG_POINTER(0));
		GBOX bbox;
		if ( gserialized_read_gbox_p(geom, &bbox) == LW_SUCCESS ){
			BOX3D *box3d = box3d_from_gbox(&bbox);
			PG_FREE_IF_COPY(geom, 0);
			PG_RETURN_POINTER(box3d);
		}else{
			PG_FREE_IF_COPY(geom, 0);
			PG_RETURN_NULL();
		}
	}

	/**
	 * Превращает любую геометрию в Ref3D с нулевым ID
	 **/
	PG_FUNCTION_INFO_V1(c60_toRef3d);
	Datum c60_toRef3d(PG_FUNCTION_ARGS){
		GSERIALIZED *geom = (GSERIALIZED*)PG_DETOAST_DATUM(PG_GETARG_POINTER(0));
		GBOX bbox;
		if ( gserialized_read_gbox_p(geom, &bbox) == LW_SUCCESS ){
			LWREF3D result;
			result.type = REF3D_TYPE;
			result.bbox = &bbox;
			result.refId = 0;
			result.flags = geom->flags;
			result.srid = gserialized_get_srid(geom);
			GSERIALIZED *sresult = geometry_serialize(lwref3d_as_lwgeom(&result));
			PG_FREE_IF_COPY(geom, 0);
			PG_RETURN_POINTER(sresult);
		}else{
			PG_FREE_IF_COPY(geom, 0);
			PG_RETURN_NULL();
		}
	}

	/**
	 * Быстрое извлечение средневзвешенного размера коробки (корень куб. от объема)
	 * Читает только заголовок геометрии. Работает с 2D и 3D
	 **/
	PG_FUNCTION_INFO_V1(c60_getBBoxSize);
	Datum c60_getBBoxSize(PG_FUNCTION_ARGS){
		GSERIALIZED *geom = (GSERIALIZED*)PG_DETOAST_DATUM(PG_GETARG_POINTER(0));
		GBOX bbox;
		if ( gserialized_read_gbox_p(geom, &bbox) == LW_SUCCESS ){
			PG_FREE_IF_COPY(geom, 0);
			if(FLAGS_GET_Z(bbox.flags)){
				double volume = (bbox.xmax - bbox.xmin) * (bbox.ymax - bbox.ymin) * (bbox.zmax - bbox.zmin);
				PG_RETURN_FLOAT8(pow(volume, 1.0/3));
			}else{
				double square = (bbox.xmax - bbox.xmin) * (bbox.ymax - bbox.ymin);
				PG_RETURN_FLOAT8(sqrt(square));
			}
		}else{
			PG_FREE_IF_COPY(geom, 0);
			PG_RETURN_NULL();
		}
	}

	/**Быстрое определение, что геометрия является REF3D **/
	PG_FUNCTION_INFO_V1(c60_isRef3D);
	Datum c60_isRef3D(PG_FUNCTION_ARGS){
		GSERIALIZED *geom = (GSERIALIZED*)PG_DETOAST_DATUM(PG_GETARG_POINTER(0));
		bool result = geom && geom->size < 200 && gserialized_get_type(geom) == REF3D_TYPE;
		PG_FREE_IF_COPY(geom, 0);
		PG_RETURN_BOOL(result); //У Ref3D размер данных всегда 160, если больше 200 значит это другая геометрия
	}

	/**
	* Получает геометрию.
	* Возвращает объем данных содержащихся в ней без полного чтения и аллокаций.
	* Длина содержится в стандартном заголовке VARLENA
	*/
	PG_FUNCTION_INFO_V1(c60_getGeomByteLen);
	Datum c60_getGeomByteLen(PG_FUNCTION_ARGS){
		GSERIALIZED *geom = (GSERIALIZED*)PG_DETOAST_DATUM(PG_GETARG_POINTER(0));
		int32_t result = geom->size;
		PG_FREE_IF_COPY(geom, 0);
		PG_RETURN_INT32(result);
	}

	/**
	* Быстрое извлечение 3D центроида геометри (без полного чтения).
    * Принимает геометри возвращает 3д точку.
	**/
	PG_FUNCTION_INFO_V1(c60_getMbrCentroid3D);
	Datum c60_getMbrCentroid3D(PG_FUNCTION_ARGS){
		GSERIALIZED *geom = (GSERIALIZED*)PG_DETOAST_DATUM(PG_GETARG_POINTER(0));
		GBOX bbox;
		if ( gserialized_read_gbox_p(geom, &bbox) == LW_SUCCESS ){
			int32_t srid = gserialized_get_srid(geom);
			LWPOINT *center = lwpoint_make3dz(
					srid,
					(bbox.xmin + bbox.xmax)/2,
					(bbox.ymin + bbox.ymax)/2,
					(bbox.zmin + bbox.zmax)/2
			);
			GSERIALIZED *result = geometry_serialize(lwpoint_as_lwgeom(center));
			lwpoint_free(center);
			PG_FREE_IF_COPY(geom, 0);
			PG_RETURN_POINTER(result);
		}else{
			PG_FREE_IF_COPY(geom, 0);
			PG_RETURN_NULL();
		}
	}

	/**
	 * Данная геометрия подразумевает вывод в графику (иначе она нужна только для семантических целей)
	 **/
	PG_FUNCTION_INFO_V1(c60_isGraphicGeom);
	Datum c60_isGraphicGeom(PG_FUNCTION_ARGS){
		GSERIALIZED *geom = (GSERIALIZED*)PG_DETOAST_DATUM(PG_GETARG_POINTER(0));
		if(gserialized_get_type(geom) == REF3D_TYPE) {
			LWREF3D *geometry = reinterpret_cast<LWREF3D *>(lwgeom_from_gserialized(geom));
		  PG_RETURN_BOOL(geometry->refId != 0);
		}else{
			PG_RETURN_BOOL(true);
		}
	}

}