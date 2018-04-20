/**
 * Набор статических функций для работы с прямоугольным покрытием
 * @author Юрин Р.Е.
 * @date 20.04.2018
 */
#include "SFCGAL/Solid.h"
#include "BoxUtils.h"




extern "C"{
	#include "liblwgeom/lwgeom_sfcgal.h"


	/**
	* Получить поверхность прямоугольного покррытия в формате SFCGAL
	**/
	sfcgal_geometry_t* c_box2SolidPolyhedron(GBOX *box, int SRID){
		return BoxUtils::box2SolidPolyhedron(box, SRID);
	}


	LWPOLY* lwpoly_construct_rectangle3D(int SRID, POINT4D *p1, POINT4D *p2, POINT4D *p3, POINT4D *p4) {
		POINTARRAY *pa = ptarray_construct_empty(LW_TRUE, LW_FALSE, 5);
		LWPOLY *lwpoly = lwpoly_construct_empty(SRID, LW_TRUE, LW_FALSE);

		ptarray_append_point(pa, p1, LW_TRUE);
		ptarray_append_point(pa, p2, LW_TRUE);
		ptarray_append_point(pa, p3, LW_TRUE);
		ptarray_append_point(pa, p4, LW_TRUE);
		ptarray_append_point(pa, p1, LW_TRUE);

		lwpoly_add_ring(lwpoly, pa);

		return lwpoly;
	}


	/**
	 * Создать полигональную поверхность коробки
	 **/
	LWPSURFACE *box3d2Surface(GBOX *gbox, int SRID){
		assert(FLAGS_GET_Z(gbox->flags));
		LWPSURFACE *surface = (LWPSURFACE *)lwcollection_construct_empty(POLYHEDRALSURFACETYPE, SRID, 1, 0);
		POINT4D vertex[8];//Вершины параллелограмма

		vertex[0].x = gbox->xmin;
		vertex[0].y = gbox->ymin;
		vertex[0].z = gbox->zmin;

		vertex[1].x = gbox->xmax;
		vertex[1].y = gbox->ymin;
		vertex[1].z = gbox->zmin;

		vertex[2].x = gbox->xmax;
		vertex[2].y = gbox->ymax;
		vertex[2].z = gbox->zmin;

		vertex[3].x = gbox->xmin;
		vertex[3].y = gbox->ymax;
		vertex[3].z = gbox->zmin;

		vertex[4].x = gbox->xmin;
		vertex[4].y = gbox->ymin;
		vertex[4].z = gbox->zmax;

		vertex[5].x = gbox->xmax;
		vertex[5].y = gbox->ymin;
		vertex[5].z = gbox->zmax;

		vertex[6].x = gbox->xmax;
		vertex[6].y = gbox->ymax;
		vertex[6].z = gbox->zmax;

		vertex[7].x = gbox->xmin;
		vertex[7].y = gbox->ymax;
		vertex[7].z = gbox->zmax;

		//Добавляем грани, соблюдая правила буравчика при задании направления обхода.
		lwpsurface_add_lwpoly(
						surface,
						lwpoly_construct_rectangle3D(SRID, &vertex[0], &vertex[3], &vertex[2], &vertex[1])
		);

		lwpsurface_add_lwpoly(
						surface,
						lwpoly_construct_rectangle3D(SRID, &vertex[0], &vertex[1], &vertex[5], &vertex[4])
		);

		lwpsurface_add_lwpoly(
						surface,
						lwpoly_construct_rectangle3D(SRID, &vertex[0], &vertex[4], &vertex[7], &vertex[3])
		);

		lwpsurface_add_lwpoly(
						surface,
						lwpoly_construct_rectangle3D(SRID, &vertex[1], &vertex[2], &vertex[6], &vertex[5])
		);

		lwpsurface_add_lwpoly(
						surface,
						lwpoly_construct_rectangle3D(SRID, &vertex[3], &vertex[7], &vertex[6], &vertex[2])
		);

		lwpsurface_add_lwpoly(
						surface,
						lwpoly_construct_rectangle3D(SRID, &vertex[4], &vertex[5], &vertex[6], &vertex[7])
		);

		return surface;
	}
}


/**
 * Получить поверхность прямоугольного покррытия в формате SFCGAL
 **/
SFCGAL::PolyhedralSurface * BoxUtils::box2Polyhedral(GBOX *box, int SRID){
	LWPSURFACE *surface = box3d2Surface(box, SRID);
	SFCGAL::PolyhedralSurface * p = (SFCGAL::PolyhedralSurface *)(LWGEOM2SFCGAL((LWGEOM*)surface));
	lwgeom_free((LWGEOM*)surface);
	return p;
}

/**
* Задать объемное тело с полигональной поверхностью заданной прямоугольным прокрытием.
**/
SFCGAL::Solid * BoxUtils::box2SolidPolyhedron(GBOX *box, int SRID){
	SFCGAL::PolyhedralSurface *s = box2Polyhedral(box, SRID);
	return new SFCGAL::Solid(s);
}
