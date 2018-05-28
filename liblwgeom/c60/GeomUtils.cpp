/**
 * Дополнительный набор геометрических функций для платформы С60
 * @author Юрин Роман 28.05.18
 */

#include "GeomUtils.hpp"
#include <assert.h>

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

}