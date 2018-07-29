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
project(address_standardizer C CXX)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH})

set(LIB_NAME ${PROJECT_NAME})
if(WIN32)
	set(MODULE_PATHNAME "\$libdir/lib${LIB_NAME}${POSTGIS_MAJOR_VERSION}${POSTGIS_MINOR_VERSION}")
else()
	set(MODULE_PATHNAME "\$libdir/${LIB_NAME}-${POSTGIS_MAJOR_VERSION}.${POSTGIS_MINOR_VERSION}")
endif()

configure_file(address_standardizer.control.in ${CMAKE_CURRENT_BINARY_DIR}/address_standardizer.control)
configure_file(address_standardizer_types.sql.in ${CMAKE_CURRENT_BINARY_DIR}/address_standardizer_types.sql)
configure_file(address_standardizer_functions.sql.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/address_standardizer_functions.sql)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/sql)
#cat sql/address_standardizer_types.sql sql/address_standardizer_functions.sql > sql/address_standardizer.sql
file(REMOVE ${CMAKE_CURRENT_BINARY_DIR}/sql/address_standardizer.sql)
append_file(${CMAKE_CURRENT_BINARY_DIR}/sql/address_standardizer.sql
                ${CMAKE_CURRENT_BINARY_DIR}/address_standardizer_types.sql)
append_file(${CMAKE_CURRENT_BINARY_DIR}/sql/address_standardizer.sql
                ${CMAKE_CURRENT_BINARY_DIR}/address_standardizer_functions.sql)

#cat sql/address_standardizer_functions.sql > sql/address_standardizer--1.0--2.2.2.sql
configure_file(${CMAKE_CURRENT_BINARY_DIR}/address_standardizer_functions.sql
     ${CMAKE_CURRENT_BINARY_DIR}/sql/address_standardizer--1.0--${POSTGIS_LIB_VERSION}.sql COPYONLY)

#cat sql/address_standardizer_types.sql sql/address_standardizer_functions.sql > sql/address_standardizer--2.2.2.sql
configure_file(${CMAKE_CURRENT_BINARY_DIR}/sql/address_standardizer.sql
     ${CMAKE_CURRENT_BINARY_DIR}/sql/address_standardizer--${POSTGIS_LIB_VERSION}.sql COPYONLY)

#cat sql/address_standardizer_functions.sql > sql/address_standardizer--2.2.2--2.2.2next.sql
configure_file(${CMAKE_CURRENT_BINARY_DIR}/address_standardizer_functions.sql
     ${CMAKE_CURRENT_BINARY_DIR}/sql/address_standardizer--${POSTGIS_LIB_VERSION}--${POSTGIS_LIB_VERSION}next.sql COPYONLY)

#cat sql/address_standardizer_functions.sql > sql/address_standardizer--2.2.2next--2.2.2.sql
configure_file(${CMAKE_CURRENT_BINARY_DIR}/address_standardizer_functions.sql
     ${CMAKE_CURRENT_BINARY_DIR}/sql/address_standardizer--${POSTGIS_LIB_VERSION}next--${POSTGIS_LIB_VERSION}.sql COPYONLY)

#cat us_lex.sql us_gaz.sql us_rules.sql sql_bits/address_standardizer_data_us_mark_editable_objects.sql.in > sql/address_standardizer_data_us.sql
set(APPEND_POSTGIS
    us_lex.sql
    us_gaz.sql
    us_rules.sql
    sql_bits/address_standardizer_data_us_mark_editable_objects.sql.in
)

file(REMOVE ${CMAKE_CURRENT_BINARY_DIR}/sql/address_standardizer_data_us.sql)
foreach(APPEND_FILE ${APPEND_POSTGIS})
    append_file(${CMAKE_CURRENT_BINARY_DIR}/sql/address_standardizer_data_us.sql
                ${APPEND_FILE})
endforeach()

configure_file(address_standardizer_data_us.control.in ${CMAKE_CURRENT_BINARY_DIR}/address_standardizer_data_us.control)

#cat us_lex.sql us_gaz.sql us_rules.sql sql_bits/address_standardizer_data_us_mark_editable_objects.sql.in > sql/address_standardizer_data_us--2.2.2.sql
configure_file(${CMAKE_CURRENT_BINARY_DIR}/sql/address_standardizer_data_us.sql
     ${CMAKE_CURRENT_BINARY_DIR}/sql/address_standardizer_data_us--${POSTGIS_LIB_VERSION}.sql COPYONLY)

#cat sql/address_standardizer_data_us--2.2.2.sql > sql/address_standardizer_data_us--2.2.2--2.2.2next.sql
configure_file(${CMAKE_CURRENT_BINARY_DIR}/sql/address_standardizer_data_us--${POSTGIS_LIB_VERSION}.sql
     ${CMAKE_CURRENT_BINARY_DIR}/sql/address_standardizer_data_us--${POSTGIS_LIB_VERSION}--${POSTGIS_LIB_VERSION}next.sql COPYONLY)

#cat sql/address_standardizer_data_us--2.2.2.sql > sql/address_standardizer_data_us--2.2.2next--2.2.2.sql
configure_file(${CMAKE_CURRENT_BINARY_DIR}/sql/address_standardizer_data_us--${POSTGIS_LIB_VERSION}.sql
     ${CMAKE_CURRENT_BINARY_DIR}/sql/address_standardizer_data_us--${POSTGIS_LIB_VERSION}next--${POSTGIS_LIB_VERSION}.sql COPYONLY)

set(POSTGIS_EXTENSION_FILES
    ${CMAKE_CURRENT_BINARY_DIR}/address_standardizer.control
    ${CMAKE_CURRENT_BINARY_DIR}/sql/address_standardizer--1.0--${POSTGIS_LIB_VERSION}.sql
    ${CMAKE_CURRENT_BINARY_DIR}/sql/address_standardizer--${POSTGIS_LIB_VERSION}--${POSTGIS_LIB_VERSION}next.sql
    ${CMAKE_CURRENT_BINARY_DIR}/sql/address_standardizer--${POSTGIS_LIB_VERSION}.sql
    ${CMAKE_CURRENT_BINARY_DIR}/sql/address_standardizer--${POSTGIS_LIB_VERSION}next--${POSTGIS_LIB_VERSION}.sql
    ${CMAKE_CURRENT_BINARY_DIR}/sql/address_standardizer.sql
    ${CMAKE_CURRENT_BINARY_DIR}/sql/address_standardizer_data_us--${POSTGIS_LIB_VERSION}--${POSTGIS_LIB_VERSION}next.sql
    ${CMAKE_CURRENT_BINARY_DIR}/sql/address_standardizer_data_us--${POSTGIS_LIB_VERSION}.sql
    ${CMAKE_CURRENT_BINARY_DIR}/sql/address_standardizer_data_us--${POSTGIS_LIB_VERSION}next--${POSTGIS_LIB_VERSION}.sql
    ${CMAKE_CURRENT_BINARY_DIR}/address_standardizer_data_us.control
    ${CMAKE_CURRENT_BINARY_DIR}/sql/address_standardizer_data_us.sql
)

set_property(GLOBAL PROPERTY LIBADDRESS_STD_INCLUDE_DIRS
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_POSTGIS_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})


set(HHEADERS
	gamma.h
	hash.h
	pagc_tools.h
	parseaddress-api.h
	std_pg_hash.h
)

set(CSOURCES
	address_parser.c
    address_standardizer.c
    std_pg_hash.c
    analyze.c
    err_param.c
    export.c
    gamma.c
    hash.c
    lexicon.c
    pagc_tools.c
    parseaddress-api.c
    standard.c
    tokenize.c
)

add_library(${LIB_NAME}
  ${CSOURCES}
  ${HHEADERS}
)

#Подключаем библиотеку регулярных выражения PCRE
find_package(PCRE REQUIRED)
include_directories(${PCRE_INCLUDE_DIRS})

set(TARGET_LINK_LIB ${TARGET_LINK_LIB};${PCRE_LIBRARIES})
target_link_extlibraries(${LIB_NAME})

set(TARGET_LINK_LIB ${TARGET_LINK_LIB} ${LIB_NAME} PARENT_SCOPE)


if(UNIX)
    set_target_properties(${LIB_NAME} PROPERTIES
        OUTPUT_NAME "${LIB_NAME}-${POSTGIS_MAJOR_VERSION}.${POSTGIS_MINOR_VERSION}"
        PREFIX ""
        )
elseif(BUILD_SHARED_LIBS AND WIN32)
    set_target_properties(${LIB_NAME} PROPERTIES SUFFIX "${POSTGIS_MAJOR_VERSION}${POSTGIS_MINOR_VERSION}.dll")
endif()

#/usr/lib/postgresql/9.5/lib/address_standardizer-2.2.so
if(NOT SKIP_INSTALL_LIBRARIES AND NOT SKIP_INSTALL_ALL )
    install(TARGETS ${LIB_NAME}
        EXPORT ${LIB_NAME}
        RUNTIME DESTINATION ${PGSQL_PKGBINDIR} COMPONENT libraries
        ARCHIVE DESTINATION ${PGSQL_PKGLIBDIR} COMPONENT libraries
        LIBRARY DESTINATION ${PGSQL_PKGLIBDIR} COMPONENT libraries
    )

    install(FILES ${POSTGIS_EXTENSION_FILES} DESTINATION "${PGSQL_SHAREDIR}/extension/")
endif()




