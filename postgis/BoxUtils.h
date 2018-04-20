/**
 * Набор статических функций для работы с прямоугольным покрытием
 * @author Юрин Р.Е.
 * @date 20.04.2018
 */
#pragma once


#include <SFCGAL/PolyhedralSurface.h>

extern "C" {
	#include <liblwgeom.h>
	#include "liblwgeom/lwgeom_sfcgal.h"
}

namespace BoxUtils {
		/**
		 * Получить поверхность прямоугольного покррытия в формате SFCGAL
		 **/
		SFCGAL::PolyhedralSurface *box2Polyhedral(GBOX *box, int SRID);

		/**
	 * Задать объемное тело с полигональной поверхностью заданной прямоугольным прокрытием.
	 **/
		SFCGAL::Solid *box2SolidPolyhedron(GBOX *box, int SRID);
};

