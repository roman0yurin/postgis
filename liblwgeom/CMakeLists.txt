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

project(lwgeom C)

configure_file(liblwgeom.h.in ${CMAKE_CURRENT_BINARY_DIR}/liblwgeom.h)

set_property(GLOBAL PROPERTY LIBLWGEOM_INCLUDE_DIRS
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

check_lwgeom_version(LIBLWGEOM_ABI_MAJOR LIBLWGEOM_ABI_MINOR LIBLWGEOM_ABI_PATCH)

set(HHEADERS_PUB
    ${CMAKE_CURRENT_BINARY_DIR}/liblwgeom.h
    liblwgeom_topo.h
)

set(HHEADERS ${HHEADERS_PUB}
    bytebuffer.h
    effectivearea.h
    liblwgeom_internal.h
    libtgeom.h
    lwgeodetic.h
    lwgeodetic_tree.h
    lwgeom_geos.h
    liblwgeom_topo.h
    liblwgeom_topo_internal.h
    lwgeom_log.h
    lwgeom_sfcgal.h
    lwin_wkt.h
    lwin_wkt_parse.h
    lwout_twkb.h
    lwtree.h
    measures3d.h
    measures.h
    stringbuffer.h
    varint.h
    kmeans.h
  )

set(CSOURCES
	stringbuffer.c
	bytebuffer.c
	measures.c
	measures3d.c
	box2d.c
	ptarray.c
	lwgeom_api.c
	lwgeom.c
	lwpoint.c
	lwline.c
	lwpoly.c
	lwtriangle.c
	lwmpoint.c
	lwmline.c
	lwmpoly.c
	lwcollection.c
	lwcircstring.c
	lwcompound.c
	lwcurvepoly.c
	lwmcurve.c
	lwmsurface.c
	lwpsurface.c
	lwtin.c
	lwout_wkb.c
	lwin_geojson.c
	lwin_wkb.c
	lwin_twkb.c
	lwout_wkt.c
	lwout_twkb.c
	lwin_wkt_parse.c
	lwin_wkt_lex.c
	lwin_wkt.c
	lwin_encoded_polyline.c
	lwutil.c
	lwhomogenize.c
	lwalgorithm.c
	lwstroke.c
	lwlinearreferencing.c
	lwprint.c
	g_box.c
	g_serialized.c
	g_util.c
	lwspheroid.c
	lwgeodetic.c
	lwgeodetic_tree.c
	lwtree.c
	lwout_gml.c
	lwout_kml.c
	lwout_geojson.c
	lwout_svg.c
	lwout_x3d.c
	lwout_encoded_polyline.c
	lwgeom_debug.c
	lwgeom_geos.c
	lwgeom_geos_clean.c
	lwgeom_geos_cluster.c
	lwgeom_geos_node.c
	lwgeom_geos_split.c
	lwgeom_topo.c
	lwgeom_transform.c
	lwgeom_wrapx.c
	lwunionfind.c
	effectivearea.c
	varint.c
	lwiterator.c
	lwboundingcircle.c
	lwgeom_median.c
	lwkmeans.c
	kmeans.c
)

set(LIB_NAME ${PROJECT_NAME})
set_property(GLOBAL PROPERTY LIB_NAME_LWGEOM ${LIB_NAME})

add_library(${LIB_NAME} ${CSOURCES} ${HEADERS})

if(UNIX)
    set(LIB_OUTPUT_NAME "${LIB_NAME}-${POSTGIS_MAJOR_VERSION}.${POSTGIS_MINOR_VERSION}.${POSTGIS_MICRO_VERSION}")
    set_target_properties(${LIB_NAME} PROPERTIES OUTPUT_NAME ${LIB_OUTPUT_NAME})
elseif(BUILD_SHARED_LIBS AND WIN32)
    set_target_properties(${LIB_NAME} PROPERTIES SUFFIX "${POSTGIS_MAJOR_VERSION}${POSTGIS_MINOR_VERSION}.dll")
endif()

if(BUILD_SHARED_LIBS)
    if(WIN32)
        set (LIB_VERSION ${LIBLWGEOM_ABI_MAJOR})
        if(MSVC)
            set_target_properties(${LIB_NAME} PROPERTIES IMPORT_SUFFIX "_i.lib")
        endif()
    else ()
      set (LIB_VERSION "${LIBLWGEOM_ABI_MAJOR}.${LIBLWGEOM_ABI_MINOR}.${LIBLWGEOM_ABI_PATCH}")
    endif()
    set_target_properties (${LIB_NAME} PROPERTIES VERSION ${LIB_VERSION})
    set_target_properties (${LIB_NAME} PROPERTIES SOVERSION ${LIBLWGEOM_ABI_MAJOR})
endif()


target_link_extlibraries(${LIB_NAME})
set(TARGET_LINK_LIB ${TARGET_LINK_LIB} ${LIB_NAME} PARENT_SCOPE)
set(DEPENDENCY_LIB ${DEPENDENCY_LIB} ${LIB_NAME} PARENT_SCOPE)

if(UNIX)
    add_custom_command(
        TARGET ${LIB_NAME} POST_BUILD
        COMMAND ln -sf $<TARGET_LINKER_FILE_NAME:${LIB_NAME}> ${CMAKE_SHARED_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}
        COMMENT "Create symlink ${CMAKE_SHARED_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}"
    )
endif()

if(NOT SKIP_INSTALL_LIBRARIES AND NOT SKIP_INSTALL_ALL )
    install(TARGETS ${LIB_NAME}
        EXPORT ${LIB_NAME}
        RUNTIME DESTINATION ${INSTALL_BIN_DIR} COMPONENT libraries
        ARCHIVE DESTINATION ${INSTALL_LIB_DIR} COMPONENT libraries
        LIBRARY DESTINATION ${INSTALL_LIB_DIR} COMPONENT libraries
    )
    if(UNIX)
        install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX} DESTINATION "${INSTALL_LIB_DIR}" COMPONENT libraries)
    endif()
endif()


if(NOT SKIP_INSTALL_FILES AND NOT SKIP_INSTALL_ALL )
    install(FILES ${HHEADERS_PUB} DESTINATION "${INSTALL_INC_DIR}" COMPONENT headers)
endif()
