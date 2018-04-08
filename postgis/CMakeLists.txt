################################################################################
# Project:  CMake4PostGIS
# Purpose:  CMake build scripts
# Author:   Dmitry Baryshnikov, polimax@mail.ru
################################################################################
# Copyright (C) 2016, NextGIS <info@nextgis.com>
# Copyright (C) 2012 Mateusz Loskot <mateusz@loskot.net>
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
project(postgis C)

set(LIB_NAME ${PROJECT_NAME})
set(MODULE_PATHNAME "\$libdir/${LIB_NAME}-${POSTGIS_MAJOR_VERSION}.${POSTGIS_MINOR_VERSION}")

configure_file(sqldefines.h.in ${CMAKE_CURRENT_SOURCE_DIR}/sqldefines.h) # +

macro(sqlin2sql sqlin sql)
  execute_process(
    COMMAND "${CMAKE_C_COMPILER}" -w -x c -E ${sqlin} -I ../libpgcommon
    COMMAND grep -v "^#"
    COMMAND "${PERL_EXECUTABLE}" -lpe
      "s'MODULE_PATHNAME'\$libdir/postgis-${POSTGIS_MAJOR_VERSION}.${POSTGIS_MINOR_VERSION}'g"
    OUTPUT_FILE ${sql}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
endmacro()

#configure_file(long_xact.sql.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/long_xact.sql)
sqlin2sql(long_xact.sql.in ${CMAKE_CURRENT_BINARY_DIR}/long_xact.sql)
file(READ ${CMAKE_CURRENT_BINARY_DIR}/long_xact.sql LONG_XACT_SQL) # use in *.cmake.in
# configure_file(geography.sql.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/geography.sql)
sqlin2sql(geography.sql.in ${CMAKE_CURRENT_BINARY_DIR}/geography.sql)
file(READ ${CMAKE_CURRENT_BINARY_DIR}/geography.sql GEOGRAPHY_SQL)  # use in *.cmake.in

if(POSTGIS_PGSQL_VERSION GREATER 90)
    set(GIST_GEOMETRY_OPS_ND_ADDS "
 -- Availability: 2.2.0
	OPERATOR        13       <<->> FOR ORDER BY pg_catalog.float_ops,")
endif()

if(POSTGIS_PGSQL_VERSION GREATER 94)
    set(GEOMETRY_DISTANCE_CENTROID distance)
    set(GIST_GEOMETRY_OPS_ND_ADDS "${GIST_GEOMETRY_OPS_ND_ADDS}
 -- Availability: 2.2.0
	OPERATOR        20       |=| FOR ORDER BY pg_catalog.float_ops,")
else()
    set(GEOMETRY_DISTANCE_CENTROID gserialized_distance_centroid_2d)
endif()

if(POSTGIS_PGSQL_VERSION GREATER 90)
    set(GIST_GEOMETRY_OPS_2D_ADDS "
    OPERATOR        13       <-> FOR ORDER BY pg_catalog.float_ops,
	OPERATOR        14       <#> FOR ORDER BY pg_catalog.float_ops,
	FUNCTION        8        geometry_gist_distance_2d (internal, geometry, int4),")

	set(GIST_GEOMETRY_OPS_ND_ADDS "${GIST_GEOMETRY_OPS_ND_ADDS}
 -- Availability: 2.2.0
	FUNCTION        8        geometry_gist_distance_nd (internal, geometry, int4),")
endif()

# configure_file(postgis.sql.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/postgis.sql)
sqlin2sql(postgis.sql.in ${CMAKE_CURRENT_BINARY_DIR}/postgis.sql)

#configure_file(legacy_minimal.sql.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/legacy_minimal.sql)
#configure_file(legacy.sql.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/legacy.sql)
#configure_file(legacy_gist.sql.in ${CMAKE_CURRENT_BINARY_DIR}/legacy_gist.sql)
sqlin2sql(legacy_minimal.sql.in ${CMAKE_CURRENT_BINARY_DIR}/legacy_minimal.sql)
sqlin2sql(legacy.sql.in ${CMAKE_CURRENT_BINARY_DIR}/legacy.sql)
sqlin2sql(legacy_gist.sql.in ${CMAKE_CURRENT_BINARY_DIR}/legacy_gist.sql)

set(PL_SKIP \$skip)
set(PL_NEWSRID \${newsrid})
set(SRID_MAXIMUM ${SRID_MAX})
set(SRID_USER_MAXIMUM ${SRID_USR_MAX})
configure_file(${CMAKE_POSTGIS_SOURCE_DIR}/utils/postgis_restore.pl.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/postgis_restore.pl)

execute_process(COMMAND ${PERL_EXECUTABLE}
                    ${CMAKE_POSTGIS_SOURCE_DIR}/utils/postgis_proc_set_search_path.pl
                    ${CMAKE_CURRENT_BINARY_DIR}/postgis.sql "UNUSED"
                OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/postgis_proc_set_search_path.sql)

#/usr/bin/perl ../utils/postgis_proc_upgrade.pl postgis.sql UNUSED > postgis_upgrade.sql.in
#echo "BEGIN;" > postgis_upgrade.sql
#cat postgis_drop_before.sql postgis_upgrade.sql.in postgis_drop_after.sql >> postgis_upgrade.sql
#echo "COMMIT;" >> postgis_upgrade.sql

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/postgis_upgrade.sql "BEGIN;\n")

append_file(${CMAKE_CURRENT_BINARY_DIR}/postgis_upgrade.sql
            ${CMAKE_CURRENT_SOURCE_DIR}/postgis_drop_before.sql)

execute_process(COMMAND ${PERL_EXECUTABLE}
                    ${CMAKE_POSTGIS_SOURCE_DIR}/utils/postgis_proc_upgrade.pl
                    ${CMAKE_CURRENT_BINARY_DIR}/postgis.sql "UNUSED"
                OUTPUT_VARIABLE PG_UPGRADE_OUT)

file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/postgis_upgrade.sql "${PG_UPGRADE_OUT}\n")
unset(PG_UPGRADE_OUT)

append_file(${CMAKE_CURRENT_BINARY_DIR}/postgis_upgrade.sql
            ${CMAKE_CURRENT_SOURCE_DIR}/postgis_drop_after.sql)

file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/postgis_upgrade.sql "COMMIT;")

create_undef(postgis)
create_undef(legacy)

if(POSTGIS_WITH_SFCGAL)
    if(POSTGIS_SFCGAL_VERSION LESS 12)
        set(ST_APPROXIMATEMEDIALAXIS "
       AS $$
       DECLARE
         poly alias for $1;
         ret GEOMETRY;
       BEGIN
         WITH components AS (
           SELECT (ST_Dump(ST_StraightSkeleton(poly))).geom
         ),
         filtered AS (
           SELECT ST_Collect(geom) g
           FROM components
           WHERE NOT ST_Touches(geom, ST_Boundary(poly))
         )
         SELECT
          COALESCE(g, ST_SetSRID('MULTILINESTRING EMPTY'::geometry, ST_Srid(poly)))
         INTO ret
         FROM filtered;
         RETURN ret;
       END; $$
       LANGUAGE 'plpgsql' ")
    else()
        set(ST_APPROXIMATEMEDIALAXIS "
        AS '${MODULE_PATHNAME}','sfcgal_approximate_medial_axis'
       LANGUAGE 'c'")
    endif()

    # configure_file(sfcgal.sql.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/sfcgal.sql)
    sqlin2sql(sfcgal.sql.in ${CMAKE_CURRENT_BINARY_DIR}/sfcgal.sql)

    #sfcgal_upgrade.sql.in: sfcgal.sql ../utils/postgis_proc_upgrade.pl
	#$(PERL) ../utils/postgis_proc_upgrade.pl $< UNUSED > $@
	# postgis_drop_after.sql

    execute_process(COMMAND ${PERL_EXECUTABLE}
                    ${CMAKE_POSTGIS_SOURCE_DIR}/utils/postgis_proc_upgrade.pl
                    ${CMAKE_CURRENT_BINARY_DIR}/sfcgal.sql "UNUSED"
                OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/sfcgal_upgrade.sql)

    append_file(${CMAKE_CURRENT_BINARY_DIR}/sfcgal_upgrade.sql
                ${CMAKE_CURRENT_SOURCE_DIR}/postgis_drop_after.sql)

    create_undef(sfcgal)
endif()

unset (LONG_XACT_SQL) # use in *.cmake.in
unset (GEOGRAPHY_SQL) # use in *.cmake.in


set(POSTGIS_CONTRIB_FILES
    ${CMAKE_CURRENT_BINARY_DIR}/postgis.sql
    ${CMAKE_POSTGIS_SOURCE_DIR}/spatial_ref_sys.sql
    ${CMAKE_CURRENT_BINARY_DIR}/legacy.sql
    ${CMAKE_CURRENT_BINARY_DIR}/legacy_gist.sql
    ${CMAKE_CURRENT_BINARY_DIR}/legacy_minimal.sql
    ${CMAKE_POSTGIS_SOURCE_DIR}/doc/postgis_comments.sql
    ${CMAKE_CURRENT_BINARY_DIR}/postgis_restore.pl
    ${CMAKE_CURRENT_BINARY_DIR}/uninstall_postgis.sql
    ${CMAKE_CURRENT_BINARY_DIR}/uninstall_legacy.sql
    ${CMAKE_CURRENT_BINARY_DIR}/postgis_upgrade.sql
)

if(POSTGIS_WITH_SFCGAL)
    set(POSTGIS_CONTRIB_FILES ${POSTGIS_CONTRIB_FILES}
        ${CMAKE_POSTGIS_SOURCE_DIR}/doc/sfcgal_comments.sql
    )
endif()

set_property(GLOBAL PROPERTY POSTGIS_INCLUDE_DIRS
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(HHEADERS
  geography.h
  geography_measurement_trees.h
  lwgeom_export.h
  lwgeom_functions_analytic.h
  lwgeom_geos.h
  lwgeom_geos_prepared.h
  lwgeom_rtree.h

  geobuf.h
  mvt.h
  uthash.h
)

set(CSOURCES
  postgis_module.c
  lwgeom_accum.c
  lwgeom_spheroid.c
  lwgeom_ogc.c
  lwgeom_functions_analytic.c
  lwgeom_inout.c
  lwgeom_functions_basic.c
  lwgeom_btree.c
  lwgeom_box.c
  lwgeom_box3d.c
  lwgeom_backend_api.c
  lwgeom_geos.c
  lwgeom_geos_prepared.c
  lwgeom_geos_clean.c
  lwgeom_geos_relatematch.c
  lwgeom_export.c
  lwgeom_in_gml.c
  lwgeom_in_kml.c
  lwgeom_in_geohash.c
  lwgeom_in_geojson.c
  lwgeom_in_encoded_polyline.c
  lwgeom_triggers.c
  lwgeom_dump.c
  lwgeom_dumppoints.c
  lwgeom_functions_lrs.c
  lwgeom_functions_temporal.c
  lwgeom_functions_basic.c
  lwgeom_window.c
  long_xact.c
  lwgeom_sqlmm.c
  lwgeom_rtree.c
  lwgeom_transform.c
  gserialized_typmod.c
  gserialized_gist_2d.c
  gserialized_gist_nd.c
  gserialized_estimate.c
  geography_inout.c
  geography_btree.c
  geography_measurement.c
  geography_measurement_trees.c
  geometry_inout.c

  geobuf.c
  geography_centroid.c
  lwgeom_out_geobuf.c
  lwgeom_out_mvt.c
  mvt.c
  postgis_libprotobuf.c
)

if(NOT POSTGIS_PGSQL_VERSION LESS 95)

  set(CSOURCES
    ${CSOURCES}
    brin_nd.c
    brin_2d.c
    brin_common.c
  )

endif()


if(PROTOBUF_FOUND)

    add_definitions(-DHAVE_LIBPROTOBUF)

    execute_process(
        COMMAND "protoc-c" --c_out=. vector_tile.proto geobuf.proto
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

    set(CSOURCES
      ${CSOURCES}
      vector_tile.pb-c.c
      geobuf.pb-c.c
    )
endif()

add_library(${LIB_NAME} SHARED
  ${CSOURCES}
  ${HHEADERS}
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

    install(FILES ${POSTGIS_CONTRIB_FILES} DESTINATION "${PGSQL_SHAREDIR}/contrib/postgis-${POSTGIS_MAJOR_VERSION}.${POSTGIS_MINOR_VERSION}/")
endif()


