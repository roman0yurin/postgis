################################################################################
# Project:  CMake4PostGIS
# Purpose:  CMake build scripts
# Author:   Dmitry Baryshnikov, polimax@mail.ru
################################################################################
# Copyright (C) 2016, NextGIS <info@nextgis.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
################################################################################
project(postgis_topology C)

macro(sqlin2sql sqlin sql)
  execute_process(
    COMMAND "${CMAKE_C_COMPILER}" -w -x c -E ${sqlin}
    COMMAND grep -v "^#"
    COMMAND "${PERL_EXECUTABLE}" -lpe
      "s'MODULE_PATHNAME'\$libdir/postgis_topology-${POSTGIS_MAJOR_VERSION}.${POSTGIS_MINOR_VERSION}'g"
    OUTPUT_FILE ${sql}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
endmacro()

set_property(GLOBAL PROPERTY LIBTOPOLOGY_INCLUDE_DIRS
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(LIB_NAME ${PROJECT_NAME})
set(MODULE_PATHNAME "\$libdir/${LIB_NAME}-${POSTGIS_MAJOR_VERSION}.${POSTGIS_MINOR_VERSION}")


file(READ "${CMAKE_CURRENT_SOURCE_DIR}/sql/manage/TopologySummary.sql.in" TOPOLOGYSUMMARY_CONTENT)
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/sql/manage/CopyTopology.sql.in" COPYTOPOLOGY_CONTENT)
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/sql/predicates.sql.in" PREDICATES_CONTENT)

sqlin2sql(${CMAKE_CURRENT_SOURCE_DIR}/sql/query/getnodebypoint.sql.in
               ${CMAKE_CURRENT_BINARY_DIR}/getnodebypoint.sql)

file(READ "${CMAKE_CURRENT_BINARY_DIR}/getnodebypoint.sql" GETNODEBYPOINT_CONTENT)
sqlin2sql(${CMAKE_CURRENT_SOURCE_DIR}/sql/query/getedgebypoint.sql.in
               ${CMAKE_CURRENT_BINARY_DIR}/getedgebypoint.sql)
file(READ "${CMAKE_CURRENT_BINARY_DIR}/getedgebypoint.sql" GETEDGEBYPOINT_CONTENT)
sqlin2sql(${CMAKE_CURRENT_SOURCE_DIR}/sql/query/getfacebypoint.sql.in
               ${CMAKE_CURRENT_BINARY_DIR}/getfacebypoint.sql)
file(READ "${CMAKE_CURRENT_BINARY_DIR}/getfacebypoint.sql" GETFACEBYPOINT_CONTENT)

if(POSTGIS_TOPOLOGY_DEBUG)
    set(POSTGIS_TOPOLOGY_DEBUG1_STR "
    RAISE DEBUG 'containing face: %', containing_face;
    ")

    set(POSTGIS_TOPOLOGY_DEBUG2_STR "
    RAISE DEBUG 'Edge already known as %', rec.edge_id;
    ")

    set(POSTGIS_TOPOLOGY_DEBUG3_STR "
    RAISE DEBUG 'Edge % (left:%, right:%) - ring : % - right_side : %',
        rec.edge_id, rec.left_face, rec.right_face, rrec.path, right_side;
    ")

    set(POSTGIS_TOPOLOGY_DEBUG4_STR "
    RAISE DEBUG 'Left edges: %', left_edges;
    RAISE DEBUG 'Right edges: %', right_edges;
    ")

    set(POSTGIS_TOPOLOGY_DEBUG5_STR "
    RAISE DEBUG 'Face already known as %, not forcing a new face', faceid;
    ")

    set(POSTGIS_TOPOLOGY_DEBUG6_STR "
    RAISE DEBUG 'Face already known as %, forcing a new face', faceid;
    ")

endif()
sqlin2sql(${CMAKE_CURRENT_SOURCE_DIR}/sql/populate.sql.in
               ${CMAKE_CURRENT_BINARY_DIR}/populate.sql)
file(READ "${CMAKE_CURRENT_BINARY_DIR}/populate.sql" POPULATE_CONTENT)
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/sql/polygonize.sql.in" POLYGONIZE_CONTENT)

file(READ "${CMAKE_CURRENT_SOURCE_DIR}/sql/topoelement/topoelement_agg.sql.in" TOPOELEMENT_AGG_CONTENT)

file(READ "${CMAKE_CURRENT_SOURCE_DIR}/sql/topogeometry/type.sql.in" TYPE_CONTENT)

if(POSTGIS_TOPOLOGY_DEBUG)
    set(POSTGIS_TOPOLOGY_DEBUG1_STR "
    RAISE DEBUG '%', sql;
    ")
endif()
sqlin2sql(${CMAKE_CURRENT_SOURCE_DIR}/sql/topogeometry/cleartopogeom.sql.in
               ${CMAKE_CURRENT_BINARY_DIR}/cleartopogeom.sql)
file(READ "${CMAKE_CURRENT_BINARY_DIR}/cleartopogeom.sql" CLEARTOPOGEOM_CONTENT)

file(READ "${CMAKE_CURRENT_SOURCE_DIR}/sql/topogeometry/simplify.sql.in" SIMPLIFY_CONTENT)

if(POSTGIS_TOPOLOGY_DEBUG)
    set(POSTGIS_TOPOLOGY_DEBUG1_STR "
    RAISE DEBUG 'TopoGeometry is \"%\", its topology_id is \"%\"', tg, topology_id(tg);
    ")

    set(POSTGIS_TOPOLOGY_DEBUG2_STR "
    RAISE DEBUG 'Elem % already in %', elem, elems;
    RAISE DEBUG '% @> ARRAY[%] returned true', elems, elem;
    ")

    set(POSTGIS_TOPOLOGY_DEBUG3_STR "
    RAISE DEBUG 'Elem % NOT in %', elem, elems;
    ")

    set(POSTGIS_TOPOLOGY_DEBUG4_STR "
    RAISE DEBUG '%', sql;
    ")
endif()
sqlin2sql(${CMAKE_CURRENT_SOURCE_DIR}/sql/topogeometry/totopogeom.sql.in
               ${CMAKE_CURRENT_BINARY_DIR}/totopogeom.sql)
file(READ "${CMAKE_CURRENT_BINARY_DIR}/totopogeom.sql" TOTOPOGEOM_CONTENT)

file(READ "${CMAKE_CURRENT_SOURCE_DIR}/sql/export/gml.sql.in" GML_CONTENT)

if(POSTGIS_TOPOLOGY_DEBUG)
    set(POSTGIS_TOPOLOGY_DEBUG1_STR "
    RAISE DEBUG 'Faces: %', all_faces;
    ")

    set(POSTGIS_TOPOLOGY_DEBUG2_STR "
          RAISE DEBUG 'LOOP START - looking for next % binding faces %',
        CASE WHEN looking_for_holes THEN 'hole' ELSE 'shell' END, faces;
    ")

    set(POSTGIS_TOPOLOGY_DEBUG3_STR "
    RAISE DEBUG ' edge % lf:%(%) rf:%(%)' , rec.signed_edge_id, rec.lf, rec.left_face, rec.rf, rec.right_face;
    ")

    set(POSTGIS_TOPOLOGY_DEBUG4_STR "
    RAISE DEBUG 'ARC id: %' , arcid;
    ")

    set(POSTGIS_TOPOLOGY_DEBUG5_STR "
    RAISE DEBUG 'NO MORE holes, rings:%', ringtxt;
    ")

    set(POSTGIS_TOPOLOGY_DEBUG6_STR "
    RAISE DEBUG ' % arcs: %', CASE WHEN looking_for_holes THEN 'hole' ELSE 'shell' END, arcs;
    ")
endif()
sqlin2sql(${CMAKE_CURRENT_SOURCE_DIR}/sql/export/TopoJSON.sql.in
               ${CMAKE_CURRENT_BINARY_DIR}/TopoJSON.sql)
file(READ "${CMAKE_CURRENT_BINARY_DIR}/TopoJSON.sql" TOPOJSON_CONTENT)

if(POSTGIS_TOPOLOGY_DEBUG)
    set(POSTGIS_TOPOLOGY_DEBUG1_STR "
    RAISE DEBUG 'Universal face has no MBR, doing nothing';
    ")

    set(POSTGIS_TOPOLOGY_DEBUG2_STR "
    RAISE DEBUG 'ring: %', fan.newring_edges;
    ")

    set(POSTGIS_TOPOLOGY_DEBUG3_STR "
    RAISE DEBUG 'not a ring';
    ")

    set(POSTGIS_TOPOLOGY_DEBUG4_STR "
    RAISE DEBUG 'Edge % split face %', anedge, oface;
    ")

    set(POSTGIS_TOPOLOGY_DEBUG5_STR "
    RAISE DEBUG '%', sql;
    ")

    set(POSTGIS_TOPOLOGY_DEBUG6_STR "
    RAISE DEBUG 'got shell';
    ")

    set(POSTGIS_TOPOLOGY_DEBUG7_STR "
    RAISE DEBUG 'winding: %', CASE WHEN isccw THEN 'CCW' ELSE 'CW' END;
    ")

    set(POSTGIS_TOPOLOGY_DEBUG8_STR "
    RAISE DEBUG 'Not considering CW ring in universe face';
    ")

    set(POSTGIS_TOPOLOGY_DEBUG9_STR "
    RAISE DEBUG 'Updating old face mbr';
    ")

    set(POSTGIS_TOPOLOGY_DEBUG10_STR "
    RAISE DEBUG 'Inserting new face';
    ")

    set(POSTGIS_TOPOLOGY_DEBUG12_STR "
    RAISE DEBUG 'Updating backward and forward edges in new ring: %', sql;
    ")

    set(POSTGIS_TOPOLOGY_DEBUG13_STR "
    RAISE DEBUG 'Updating backward edges in new ring: %', sql;
    ")

    set(POSTGIS_TOPOLOGY_DEBUG14_STR "
    RAISE DEBUG 'Updating rings in former shell';
    ")

    set(POSTGIS_TOPOLOGY_DEBUG15_STR "
    RAISE DEBUG 'Updating contained edges';
    ")

    set(POSTGIS_TOPOLOGY_DEBUG16_STR "
    RAISE DEBUG 'Updating edges bounding the old face: %', sql;
    ")

    set(POSTGIS_TOPOLOGY_DEBUG17_STR "
    RAISE DEBUG 'Updating isolated nodes in old face';
    ")

    set(POSTGIS_TOPOLOGY_DEBUG18_STR "
    RAISE DEBUG 'Noding input linework';
    ")

    set(POSTGIS_TOPOLOGY_DEBUG19_STR "
    RAISE DEBUG 'Computed % noded edges', ST_NumGeometries(nodededges);
    ")

    set(POSTGIS_TOPOLOGY_DEBUG20_STR "
    RAISE DEBUG 'Merged edges: %', ST_NumGeometries(nodededges);
    ")

    set(POSTGIS_TOPOLOGY_DEBUG21_STR "
    RAISE DEBUG 'Collected % input points', ST_NumGeometries(points);
    ")

    set(POSTGIS_TOPOLOGY_DEBUG22_STR "
      RAISE DEBUG 'Noded edges became % after point-split',
    ST_NumGeometries(nodededges);
    ")

    set(POSTGIS_TOPOLOGY_DEBUG23_STR "
    RAISE DEBUG 'Total nodes count: %', ST_NumGeometries(points);
    ")

endif()
sqlin2sql(${CMAKE_CURRENT_SOURCE_DIR}/sql/sqlmm.sql.in
               ${CMAKE_CURRENT_BINARY_DIR}/sqlmm.sql)
file(READ "${CMAKE_CURRENT_BINARY_DIR}/sqlmm.sql" SQLMM_CONTENT)

file(READ "${CMAKE_CURRENT_SOURCE_DIR}/sql/query/GetRingEdges.sql.in" GETRINGEDGES_CONTENT)

if(POSTGIS_TOPOLOGY_DEBUG)
    set(POSTGIS_TOPOLOGY_DEBUG1_STR "
    RAISE DEBUG 'sql: %', sql;
    ")

    set(POSTGIS_TOPOLOGY_DEBUG2_STR "
    RAISE DEBUG 'Edge:% az:%', rec.edge_id, rec.az;
    ")
endif()
sqlin2sql(${CMAKE_CURRENT_SOURCE_DIR}/sql/query/GetNodeEdges.sql.in
               ${CMAKE_CURRENT_BINARY_DIR}/GetNodeEdges.sql)
file(READ "${CMAKE_CURRENT_BINARY_DIR}/GetNodeEdges.sql" GETNODEEDGES_CONTENT)

file(READ "${CMAKE_CURRENT_SOURCE_DIR}/sql/manage/ManageHelper.sql.in" MANAGEHELPER_CONTENT)

if(POSTGIS_PGSQL_VERSION GREATER 91)
    set(TOPOLOGY_TOPOELEMENT "
 IF EXISTS")
endif()

if(POSTGIS_TOPOLOGY_DEBUG)
    set(POSTGIS_TOPOLOGY_DEBUG_STR "
   RAISE DEBUG 'Query: %', query;")
endif()

# create topology.sql
sqlin2sql(topology.sql.in ${CMAKE_CURRENT_BINARY_DIR}/topology.sql)

unset(TOPOLOGYSUMMARY_CONTENT)
unset(COPYTOPOLOGY_CONTENT)
unset(PREDICATES_CONTENT)
unset(GETNODEBYPOINT_CONTENT)
unset(GETEDGEBYPOINT_CONTENT)
unset(GETFACEBYPOINT_CONTENT)
unset(POPULATE_CONTENT)
unset(POLYGONIZE_CONTENT)
unset(TOPOELEMENT_AGG_CONTENT)
unset(TYPE_CONTENT)
unset(CLEARTOPOGEOM_CONTENT)
unset(SIMPLIFY_CONTENT)
unset(TOTOPOGEOM_CONTENT)
unset(GML_CONTENT)
unset(TOPOJSON_CONTENT)
unset(SQLMM_CONTENT)
unset(GETRINGEDGES_CONTENT)
unset(GETNODEEDGES_CONTENT)
unset(MANAGEHELPER_CONTENT)

# create topology_drop_before.sql
sqlin2sql(topology_drop_before.sql.in ${CMAKE_CURRENT_BINARY_DIR}/topology_drop_before.sql)

# create topology_drop_after.sql
sqlin2sql(topology_drop_after.sql.in ${CMAKE_CURRENT_BINARY_DIR}/topology_drop_after.sql)

# create topology_upgrade.sql
# /usr/bin/perl -0777 -ne 's/^(CREATE|ALTER) (CAST|OPERATOR|TYPE|TABLE|SCHEMA|DOMAIN|TRIGGER).*?;//msg;print;' topology.sql > topology_upgrade.sql.in
execute_process(COMMAND ${PERL_EXECUTABLE} -0777 -ne
"s/^(CREATE|ALTER) (CAST|OPERATOR|TYPE|TABLE|SCHEMA|DOMAIN|TRIGGER).*?;//msg;print;"
${CMAKE_CURRENT_BINARY_DIR}/topology.sql
                OUTPUT_VARIABLE TOPOLOGY_UPGRADE_SQL)

# cat topology_drop_before.sql topology_upgrade.sql.in topology_drop_after.sql > topology_upgrade.sql
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/topology_upgrade.sql "--topology_upgrade\n")
append_file(${CMAKE_CURRENT_BINARY_DIR}/topology_upgrade.sql
            ${CMAKE_CURRENT_BINARY_DIR}/topology_drop_before.sql)
#append_file(${CMAKE_CURRENT_BINARY_DIR}/topology_upgrade.sql
#            ${CMAKE_CURRENT_BINARY_DIR}/topology_upgrade.sql.in)
file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/topology_upgrade.sql "${TOPOLOGY_UPGRADE_SQL}\n")
append_file(${CMAKE_CURRENT_BINARY_DIR}/topology_upgrade.sql
            ${CMAKE_CURRENT_BINARY_DIR}/topology_drop_after.sql)

#/usr/bin/perl ../utils/create_undef.pl topology.sql 94 > uninstall_topology.sql
create_undef(topology)

set(TOPOLOGY_CONTRIB_FILES
    ${CMAKE_SOURCE_DIR}/doc/topology_comments.sql
    ${CMAKE_CURRENT_BINARY_DIR}/topology.sql
    ${CMAKE_CURRENT_BINARY_DIR}/topology_upgrade.sql
    ${CMAKE_CURRENT_BINARY_DIR}/uninstall_topology.sql
)

set(CSOURCES
	postgis_topology.c
)

add_library(${LIB_NAME}
  ${CSOURCES}
)

target_link_extlibraries(${LIB_NAME})

set(TARGET_LINK_LIB ${TARGET_LINK_LIB} ${LIB_NAME} PARENT_SCOPE)


if(UNIX)
    set_target_properties(${LIB_NAME} PROPERTIES
        LINK_FLAGS "-Wl,--exclude-libs,ALL"
        OUTPUT_NAME "${LIB_NAME}-${POSTGIS_MAJOR_VERSION}.${POSTGIS_MINOR_VERSION}"
        PREFIX ""
        )
elseif(BUILD_SHARED_LIBS AND WIN32)
    set_target_properties(${LIB_NAME} PROPERTIES SUFFIX "${POSTGIS_MAJOR_VERSION}${POSTGIS_MINOR_VERSION}.dll")
endif()

#/usr/lib/postgresql/9.3/lib/postgis-2.1.so
if(NOT SKIP_INSTALL_LIBRARIES AND NOT SKIP_INSTALL_ALL )
    install(TARGETS ${LIB_NAME}
        EXPORT ${LIB_NAME}
        RUNTIME DESTINATION ${PGSQL_PKGBINDIR} COMPONENT libraries
        ARCHIVE DESTINATION ${PGSQL_PKGLIBDIR} COMPONENT libraries
        LIBRARY DESTINATION ${PGSQL_PKGLIBDIR} COMPONENT libraries
    )

    install(FILES ${TOPOLOGY_CONTRIB_FILES} DESTINATION "${PGSQL_SHAREDIR}/contrib/postgis-${POSTGIS_MAJOR_VERSION}.${POSTGIS_MINOR_VERSION}/")
endif()


