/**
 * Обертка утилит для C
 * @author Юрин Р.Е.
 * @date 20.04.2018
 */
#pragma once


/**
 * Получить поверхность прямоугольного покррытия в формате SFCGAL
 **/
sfcgal_geometry_t* c_box2SolidPolyhedron(GBOX *box, int SRID);

