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

option(ENABLE_NLS "Translate messages to user locale" ON)

include (CheckFunctionExists)
include (CheckIncludeFile)
include (CheckIncludeFiles)
include (CheckPrototypeExists)
include (CheckSymbolExists)
include (CheckTypeSize)
include (CheckCSourceCompiles)

################################################################################
# Predefined constants
set(SRID_MAX 999999)
set(SRID_USR_MAX 998999)


option(POSTGIS_ENABLE_AUTOCACHE_BBOX
    "Set ON|OFF (default=ON) to control BBOX caching within geometries" ON)
set(POSTGIS_AUTOCACHE_BBOX 1)
if(NOT POSTGIS_ENABLE_AUTOCACHE_BBOX)
    set(POSTGIS_AUTOCACHE_BBOX 0)
endif()

option(POSTGIS_ENABLE_PROFILE
  "Set ON|OFF (default=OFF) to control use GEOS profiling" OFF)
set(POSTGIS_PROFILE 0)
if(POSTGIS_ENABLE_PROFILE)
    set(POSTGIS_PROFILE 1)
endif()

option(POSTGIS_ENABLE_DEBUG
  "Set ON|OFF (default=OFF) to control verbose debugging messages" OFF)
set(POSTGIS_DEBUG_LEVEL 0)
if(POSTGIS_ENABLE_DEBUG)
    set(POSTGIS_DEBUG_LEVEL 4)
endif()

if(GDAL_FOUND)
    if(WITH_GDAL_EXTERNAL)
        set(GDALFPOLYGONIZE 1)
    else()
        set(CMAKE_REQUIRED_INCLUDES ${GDAL_INCLUDE_DIR})
        set(CMAKE_REQUIRED_LIBRARIES ${GDAL_LIBRARY})
        check_function_exists(GDALFPolygonize GDALFPOLYGONIZE)
        unset(CMAKE_REQUIRED_INCLUDES)
        unset(CMAKE_REQUIRED_LIBRARIES)
    endif()
endif()

check_function_exists(CFLocaleCopyCurrent HAVE_CFLOCALECOPYCURRENT)
check_function_exists(CFPreferencesCopyAppValue HAVE_CFPREFERENCESCOPYAPPVALUE)
check_function_exists(dcgettext HAVE_DCGETTEXT)
check_function_exists(gettext HAVE_GETTEXT)
check_function_exists(iconvctl HAVE_ICONVCTL)
check_function_exists(libiconvctl HAVE_LIBICONVCTL)
check_function_exists(vasprintf HAVE_VASPRINTF)
check_function_exists(asprintf HAVE_ASPRINTF)

check_prototype_exists(isfinite cmath HAVE_FINITE)

if(MSVC)
    check_prototype_exists(_finite float.h HAVE_FINITE)
else()
    check_symbol_exists(isfinite math.h HAVE_GNU_ISFINITE)
endif()

check_function_exists(strcasestr HAVE_STRCASESTR)

check_include_file("ieeefp.h" HAVE_IEEEFP_H)

check_function_exists(fseeko HAVE_FSEEKO)

if(LIBXML2_FOUND)
    set(HAVE_LIBXML2 1)
    set(CMAKE_REQUIRED_INCLUDES ${LIBXML2_INCLUDE_DIR})
    set(CMAKE_REQUIRED_DEFINITIONS ${LIBXML2_DEFINITIONS})
    check_include_file("libxml/parser.h" HAVE_LIBXML_PARSER_H)
    check_include_file("libxml/tree.h" HAVE_LIBXML_TREE_H)
    check_include_file("libxml/xpathInternals.h" HAVE_LIBXML_XPATHINTERNALS_H)
    check_include_file("libxml/xpath.h" HAVE_LIBXML_XPATH_H)
    unset(CMAKE_REQUIRED_INCLUDES)
    unset(CMAKE_REQUIRED_DEFINITIONS)
endif()

check_include_file("dlfcn.h" HAVE_DLFCN_H)
check_include_file("inttypes.h" HAVE_INTTYPES_H)
check_include_file("memory.h" HAVE_MEMORY_H)
check_include_file("stdint.h" HAVE_STDINT_H)

check_include_file("ctype.h" HAVE_CTYPE_H)
check_include_file("stdlib.h" HAVE_STDLIB_H)

if (HAVE_CTYPE_H AND HAVE_STDLIB_H)
    set(STDC_HEADERS 1)
endif ()

check_include_file("strings.h" HAVE_STRINGS_H)
check_include_file("string.h" HAVE_STRING_H)
check_include_file("sys/stat.h" HAVE_SYS_STAT_H)
check_include_file("sys/types.h" HAVE_SYS_TYPES_H)
check_include_file("unistd.h" HAVE_UNISTD_H)

if(NOT HAVE_UNISTD_H)
    set(YY_NO_UNISTD_H 1)
endif()

find_package(BISON)
find_package(FLEX)
if(FLEX_FOUND)
    #На винде проявляется баг - пробел между -o и названием файла недопустим.
    execute_process(COMMAND "${FLEX_EXECUTABLE}" "-o${CMAKE_POSTGIS_BINARY_DIR}/lexyy.c"
                            "${CMAKE_POSTGIS_SOURCE_DIR}/cmake/lex_test.l")


    try_compile(YYTEXT_POINTER
      ${CMAKE_POSTGIS_BINARY_DIR}
      ${CMAKE_POSTGIS_BINARY_DIR}/lexyy.c
      LINK_LIBRARIES ${FLEX_LIBRARIES}
      COMPILE_DEFINITIONS  "-DYYTEXT_POINTER=1"
      CMAKE_FLAGS "-DINCLUDE_DIRECTORIES:STRING=\"${FLEX_INCLUDE_DIRS}\"")

endif()

if(NOT WIN32)
    find_library(M_LIBRARY
        NAMES m
        PATHS /usr/lib /usr/local/lib
    )
    if(NOT M_LIBRARY)
      message(STATUS "math lib 'libm' not found; floating point support disabled")
    endif()
else()
  # not needed on windows
  set(M_LIBRARY "")
endif()

set(TARGET_LINK_LIB ${TARGET_LINK_LIB} ${M_LIBRARY})

################################################################################
# Generate config header
configure_file(${CMAKE_POSTGIS_SOURCE_DIR}/postgis_config.h.cmake.in
    ${CMAKE_POSTGIS_BINARY_DIR}/postgis_config.h)
configure_file(${CMAKE_POSTGIS_SOURCE_DIR}/cmake/uninstall.cmake.in
    ${CMAKE_POSTGIS_BINARY_DIR}/cmake_uninstall.cmake IMMEDIATE @ONLY)


