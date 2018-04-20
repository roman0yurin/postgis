/**
 * Набор методов для работы с геометрией в модуле postgis
 * @author Юрин Р.Е.
 * @date 20.04.2018
 */
#ifndef POSTGIS_PG_GEOMETRY_H
#define POSTGIS_PG_GEOMETRY_H

#include <liblwgeom/liblwgeom.h>

/**
 * Создать полигональную поверхность коробки
 **/
LWPSURFACE *box3d2Surface(GBOX *gbox, int SRID);


#endif //POSTGIS_PG_GEOMETRY_H
