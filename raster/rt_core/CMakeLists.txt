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
project(rtcore C)

set_property(GLOBAL PROPERTY LIBRTCORE_INCLUDE_DIRS
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(HHEADERS
				${CMAKE_CURRENT_SOURCE_DIR}/rt_serialize.h
				${CMAKE_CURRENT_SOURCE_DIR}/librtcore.h
				${CMAKE_CURRENT_SOURCE_DIR}/librtcore_internal.h
				${CMAKE_CURRENT_SOURCE_DIR}/../raster_config.h
)

set_property(GLOBAL PROPERTY RT_CORE_HEADERS ${HHEADERS})
set_property(GLOBAL PROPERTY RT_CORE_HEADERS_DIRS ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

set(CSOURCES
	rt_util.c
	rt_spatial_relationship.c
	rt_mapalgebra.c
	rt_geometry.c
	rt_statistics.c
	rt_pixel.c
	rt_warp.c
	rt_band.c
	rt_raster.c
	rt_serialize.c
	rt_wkb.c
	rt_context.c
)

set(LIB_NAME ${PROJECT_NAME})

add_library(${LIB_NAME} STATIC ${CSOURCES} ${HHEADERS}) #always static
target_link_extlibraries(${LIB_NAME})
set(TARGET_LINK_LIB ${TARGET_LINK_LIB} ${LIB_NAME} PARENT_SCOPE)
set(DEPENDENCY_LIB ${DEPENDENCY_LIB} ${LIB_NAME} PARENT_SCOPE)

