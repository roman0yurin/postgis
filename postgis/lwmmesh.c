/**********************************************************************
 * MultiMesh - множественная поверхность. Позволяет работать с мешем
 * как с топологически непрерывной поверхностью (Tin) , а множество таких поверхностей задавать как MultiMesh
 * @author Юрин Роман
 **********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liblwgeom_internal.h"
#include "lwgeom_log.h"


void lwmmesh_release(LWMMESH *lwmmesh){
	lwgeom_release(lwmmesh_as_lwgeom(lwmmesh));
}

LWMMESH *lwmmesh_construct_empty(int srid, char hasz, char hasm){
	LWMMESH *ret = (LWMMESH*)lwcollection_construct_empty(MULTIMESH_TYPE, srid, hasz, hasm);
	return ret;
}


LWMMESH* lwmmesh_add_tin(LWMMESH *mobj, const LWTIN *obj){
	return (LWMMESH*)lwcollection_add_lwgeom((LWCOLLECTION*)mobj, (LWGEOM*)obj);
}


void lwmmesh_free(LWMMESH *mmesh)
{
	int i;
	if ( ! mmesh ) return;
	if ( mmesh->bbox )
		lwfree(mmesh->bbox);

	for ( i = 0; i < mmesh->ngeoms; i++ )
		if ( mmesh->geoms && mmesh->geoms[i] )
			lwtin_free(mmesh->geoms[i]);

	if ( mmesh->geoms )
		lwfree(mmesh->geoms);

	lwfree(mmesh);
}