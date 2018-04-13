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
project(rtpostgis C)

macro(sqlin2sql sqlin sql)
  execute_process(
    COMMAND "${CMAKE_C_COMPILER}" -w -x c -E ${sqlin} -I ../../postgis
    COMMAND grep -v "^#"
    COMMAND "${PERL_EXECUTABLE}" -lpe
      "s'MODULE_PATHNAME'\$libdir/rtpostgis-${POSTGIS_MAJOR_VERSION}.${POSTGIS_MINOR_VERSION}'g"
    OUTPUT_FILE ${sql}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
endmacro()

set_property(GLOBAL PROPERTY LIBRTPOSTGIS_INCLUDE_DIRS
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(LIB_NAME ${PROJECT_NAME})
set(MODULE_PATHNAME "\$libdir/${LIB_NAME}-${POSTGIS_MAJOR_VERSION}.${POSTGIS_MINOR_VERSION}")

# create rtpostgis.sql
sqlin2sql(rtpostgis.sql.in ${CMAKE_CURRENT_BINARY_DIR}/rtpostgis.sql)

# create rtpostgis_legacy.sql
sqlin2sql(rtpostgis_legacy.sql.in ${CMAKE_CURRENT_BINARY_DIR}/rtpostgis_legacy.sql)

# create rtpostgis_legacy.sql
sqlin2sql(rtpostgis_upgrade_cleanup.sql.in ${CMAKE_CURRENT_BINARY_DIR}/rtpostgis_upgrade_cleanup.sql)

# create rtpostgis_drop.sql
sqlin2sql(rtpostgis_drop.sql.in ${CMAKE_CURRENT_BINARY_DIR}/rtpostgis_drop.sql)

# create rtpostgis_upgrade.sql
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/rtpostgis_upgrade.sql "BEGIN;\n")
append_file(${CMAKE_CURRENT_BINARY_DIR}/rtpostgis_upgrade.sql
            ${CMAKE_CURRENT_BINARY_DIR}/rtpostgis_upgrade_cleanup.sql)
execute_process(COMMAND ${PERL_EXECUTABLE}
                    ${CMAKE_POSTGIS_SOURCE_DIR}/utils/postgis_proc_upgrade.pl
                    ${CMAKE_CURRENT_BINARY_DIR}/rtpostgis.sql "UNUSED"
                OUTPUT_VARIABLE PG_UPGRADE_OUT)

file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/rtpostgis_upgrade.sql "${PG_UPGRADE_OUT}\n")
unset(PG_UPGRADE_OUT)

append_file(${CMAKE_CURRENT_BINARY_DIR}/rtpostgis_upgrade.sql
            ${CMAKE_CURRENT_BINARY_DIR}/rtpostgis_drop.sql)

file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/rtpostgis_upgrade.sql "COMMIT;")

# create rtpostgis_proc_set_search_path.sql
execute_process(COMMAND ${PERL_EXECUTABLE}
                    ${CMAKE_POSTGIS_SOURCE_DIR}/utils/postgis_proc_set_search_path.pl
                    ${CMAKE_CURRENT_BINARY_DIR}/rtpostgis.sql "UNUSED"
                OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/rtpostgis_proc_set_search_path.sql)

# create uninstall_rtpostgis.sql
create_undef(rtpostgis)

set(RTPOSTGIS_CONTRIB_FILES
    ${CMAKE_POSTGIS_SOURCE_DIR}/doc/raster_comments.sql
    ${CMAKE_CURRENT_BINARY_DIR}/rtpostgis.sql
    ${CMAKE_CURRENT_BINARY_DIR}/rtpostgis_legacy.sql
    ${CMAKE_CURRENT_BINARY_DIR}/rtpostgis_upgrade.sql
    ${CMAKE_CURRENT_BINARY_DIR}/uninstall_rtpostgis.sql
)

set(HHEADERS
	rtpostgis.h
	../raster_config.h
)

set(CSOURCES
	rtpostgis.c
	rtpg_internal.c
	rtpg_spatial_relationship.c
	rtpg_mapalgebra.c
	rtpg_utility.c
	rtpg_inout.c
	rtpg_geometry.c
	rtpg_raster_properties.c
	rtpg_band_properties.c
	rtpg_pixel.c
	rtpg_create.c
	rtpg_gdal.c
	rtpg_statistics.c
)

foreach(s ${CSOURCES})
	list(APPEND SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${s})
endforeach()

set_property(GLOBAL PROPERTY RT_PG_SRC ${SRC_PATH})

add_library(${LIB_NAME} SHARED
  ${CSOURCES}
  ${HHEADERS}
)

target_link_extlibraries(${LIB_NAME})
target_link_libraries(${LIB_NAME} rtcore)

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

    install(FILES ${RTPOSTGIS_CONTRIB_FILES} DESTINATION "${PGSQL_SHAREDIR}/contrib/postgis-${POSTGIS_MAJOR_VERSION}.${POSTGIS_MINOR_VERSION}/")
endif()


