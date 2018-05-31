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
			PG_RETURN_POINTER(box3d);
		}else{

			PG_RETURN_NULL();
		}
	}

	/**
	* Получает геометрию.
	* Возвращает объем данных содержащихся в ней без полного чтения и аллокаций.
	* Длина содержится в стандартном заголовке VARLENA
	*/
	PG_FUNCTION_INFO_V1(c60_getGeomByteLen);
	Datum c60_getGeomByteLen(PG_FUNCTION_ARGS){
		GSERIALIZED *geom = (GSERIALIZED*)PG_DETOAST_DATUM(PG_GETARG_POINTER(0));
		PG_RETURN_INT32(geom->size);
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
			PG_RETURN_POINTER(result);
		}else{

			PG_RETURN_NULL();
		}
	}

}