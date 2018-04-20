/**
* Набор функций для работы со ссылочной геометрией
* @author Юрин Роман
* @date 16.04.18
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <liblwgeom.h>
#include "liblwgeom_internal.h"

void lwref3d_release(LWREF3D *ref){
	lwgeom_release(lwref3d_as_lwgeom(ref));
}

LWREF3D* lwref3d_construct(int srid, GBOX *bbox, uint32_t refId){
	LWREF3D *ref = lwref3d_construct_empty(srid);
	if(!bbox)
		lwerror("BBOX is required for REF3D, id=%d", refId);
	ref->bbox = bbox;
	ref->refId = refId;
	return ref;
}

LWREF3D* lwref3d_construct_empty(int srid){
	LWREF3D *ref = lwalloc(sizeof(LWREF3D));
	ref->type = REF3D_TYPE;
	ref->flags = gflags(true, false, false);
	FLAGS_SET_BBOX(ref->flags, true);
	ref->srid = srid;
	return ref;
}

LWREF3D *lwref3d_clone(const LWREF3D *ref){
	return lwref3d_construct(ref->srid, gbox_clone(ref->bbox), ref->refId);
}

char lwref3d_same(const LWREF3D *ref1, const LWREF3D *ref2){
	return ref1->srid == ref2->srid &&
			ref1->bbox != NULL && ref2 != NULL &&
			gbox_same(ref1->bbox, ref2->bbox) &&
			ref1->refId == ref2->refId;
}

extern void lwref3d_free(LWREF3D *ref){
	if(ref->bbox)
		lwfree(ref->bbox);
	lwfree(ref);
}

extern void printLWREF3d(LWREF3D *ref){
	if(ref->type != REF3D_TYPE)
		lwerror("Incorrect type in REF3D");
	lwnotice("LWREF3D {    SRID = %i    REF_ID = %i", ref->srid, ref->refId);
	if(ref->bbox) {
		BOX3D *box = box3d_from_gbox(ref->bbox);
		lwnotice(box);
		lwfree(box);
	}
	lwnotice("}");
}

LWGEOM *lwref3d_as_lwgeom(const LWREF3D *obj){
	return (LWGEOM *)obj;
}

LWREF3D *lwgeom_as_ref3d(const LWGEOM *lwgeom){
	assert(!lwgeom || lwgeom->type == REF3D_TYPE);
	return (LWREF3D *)lwgeom;
}