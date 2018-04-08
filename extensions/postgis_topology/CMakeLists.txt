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

configure_file(postgis_topology.control.in ${CMAKE_CURRENT_BINARY_DIR}/postgis_topology.control)

macro(prepare_extension_sql2 input_path output_path)
    file (READ ${input_path} _file_content)
	string (REPLACE "COMMIT;" "--COMMIT" _file_content "${_file_content}")
	string (REPLACE "BEGIN;" "--BEGIN" _file_content "${_file_content}")
	string (REPLACE "\nCREATE SCHEMA" "\n--CREATE SCHEMA" _file_content "${_file_content}")

    file(WRITE ${output_path} "-- extension ready \n")
    file(APPEND ${output_path} "${_file_content}")
endmacro()

#sed -e 's/BEGIN;//g' -e 's/COMMIT;//g' -e '/^CREATE SCHEMA/d;'  ../../topology/topology.sql > sql_bits/topology.sql
prepare_extension_sql2(${CMAKE_POSTGIS_BINARY_DIR}/topology/topology.sql ${CMAKE_CURRENT_BINARY_DIR}/topology.sql)

#mkdir -p sql
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/sql)

#cat extlock.sql sql_bits/topology.sql sql_bits/mark_editable_objects.sql.in sql_bits/topology_comments.sql > sql/postgis_topology.sql
set(APPEND_POSTGIS
    ${CMAKE_CURRENT_SOURCE_DIR}/extlock.sql
    ${CMAKE_CURRENT_BINARY_DIR}/topology.sql
    ${CMAKE_CURRENT_SOURCE_DIR}/sql_bits/mark_editable_objects.sql.in
    ${CMAKE_POSTGIS_SOURCE_DIR}/doc/topology_comments.sql
)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/sql/postgis_topology.sql "-- postgis_topology\n")
foreach(APPEND_FILE ${APPEND_POSTGIS})
    append_file(${CMAKE_CURRENT_BINARY_DIR}/sql/postgis_topology.sql
                ${APPEND_FILE})
endforeach()


#cp sql/postgis_topology.sql sql/postgis_topology--2.2.2.sql
configure_file(${CMAKE_CURRENT_BINARY_DIR}/sql/postgis_topology.sql
     ${CMAKE_CURRENT_BINARY_DIR}/sql/postgis_topology--${POSTGIS_LIB_VERSION}.sql COPYONLY)

#cat ../../topology/topology.sql | /usr/bin/perl ../../utils/create_unpackaged.pl postgis_topology > sql/postgis_topology--unpackaged--2.2.2.sql
execute_process(COMMAND ${PERL_EXECUTABLE}
                    ${CMAKE_POSTGIS_SOURCE_DIR}/utils/create_unpackaged.pl
                    postgis_topology
                    ${CMAKE_POSTGIS_BINARY_DIR}/topology/topology.sql
                OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/sql/postgis_topology--unpackaged--${POSTGIS_LIB_VERSION}.sql)

#sed -e 's/BEGIN;//g' -e 's/COMMIT;//g' -e '/^CREATE SCHEMA/d;'  ../../topology/topology_upgrade.sql > sql/topology_upgrade.sql
prepare_extension_sql2(${CMAKE_POSTGIS_BINARY_DIR}/topology/topology_upgrade.sql ${CMAKE_CURRENT_BINARY_DIR}/sql/topology_upgrade.sql)

#cat extlock.sql ../postgis_extension_helper.sql sql_bits/remove_from_extension.sql.in sql/topology_upgrade.sql sql_bits/mark_editable_objects.sql.in sql_bits/topology_comments.sql ../postgis_extension_helper_uninstall.sql > sql/postgis_topology--2.2.2--2.2.2next.sql
set(APPEND_POSTGIS
    ${CMAKE_CURRENT_SOURCE_DIR}/extlock.sql
    ${CMAKE_CURRENT_SOURCE_DIR}/../postgis_extension_helper.sql
    ${CMAKE_CURRENT_SOURCE_DIR}/sql_bits/remove_from_extension.sql.in
    ${CMAKE_CURRENT_BINARY_DIR}/sql/topology_upgrade.sql
    ${CMAKE_CURRENT_SOURCE_DIR}/sql_bits/mark_editable_objects.sql.in
    ${CMAKE_POSTGIS_SOURCE_DIR}/doc/topology_comments.sql
    ${CMAKE_CURRENT_SOURCE_DIR}/../postgis_extension_helper_uninstall.sql
)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/sql/postgis_topology--${POSTGIS_LIB_VERSION}--${POSTGIS_LIB_VERSION}next.sql "-- postgis_topology\n")
foreach(APPEND_FILE ${APPEND_POSTGIS})
    append_file(${CMAKE_CURRENT_BINARY_DIR}/sql/postgis_topology--${POSTGIS_LIB_VERSION}--${POSTGIS_LIB_VERSION}next.sql
                ${APPEND_FILE})
endforeach()

#cat sql/postgis_topology--2.2.2--2.2.2next.sql > sql/postgis_topology--2.2.2next--2.2.2.sql
configure_file(${CMAKE_CURRENT_BINARY_DIR}/sql/postgis_topology--${POSTGIS_LIB_VERSION}--${POSTGIS_LIB_VERSION}next.sql
     ${CMAKE_CURRENT_BINARY_DIR}/sql/postgis_topology--${POSTGIS_LIB_VERSION}next--${POSTGIS_LIB_VERSION}.sql COPYONLY)


set(POSTGISTOPO_EXTENSION_FILES
    ${CMAKE_CURRENT_BINARY_DIR}/postgis_topology.control
    ${CMAKE_CURRENT_BINARY_DIR}/sql/postgis_topology--${POSTGIS_LIB_VERSION}.sql
    ${CMAKE_CURRENT_BINARY_DIR}/sql/postgis_topology--${POSTGIS_LIB_VERSION}next--${POSTGIS_LIB_VERSION}.sql
    ${CMAKE_CURRENT_BINARY_DIR}/sql/postgis_topology--unpackaged--${POSTGIS_LIB_VERSION}.sql
    ${CMAKE_CURRENT_BINARY_DIR}/sql/postgis_topology--${POSTGIS_LIB_VERSION}--${POSTGIS_LIB_VERSION}next.sql
)


#for OLD_VERSION in 2.0.0 2.0.1 2.0.2 2.0.3 2.0.4 2.0.5 2.0.6 2.0.7 2.1.0 2.1.1 2.1.2 2.1.3 2.1.4 2.1.5 2.1.6 2.1.7 2.1.8 2.1.9 2.2.0 2.2.1 2.2.2; do \
#  	  cat extlock.sql ../postgis_extension_helper.sql sql_bits/remove_from_extension.sql.in sql/topology_upgrade.sql sql_bits/mark_editable_objects.sql.in sql_bits/topology_comments.sql ../postgis_extension_helper_uninstall.sql > sql/postgis_topology--$OLD_VERSION--2.2.2.sql; \
foreach(UPGRADEABLE_VERSION ${UPGRADEABLE_VERSIONS})
    configure_file(${CMAKE_CURRENT_BINARY_DIR}/sql/postgis_topology--${POSTGIS_LIB_VERSION}--${POSTGIS_LIB_VERSION}next.sql
        ${CMAKE_CURRENT_BINARY_DIR}/sql/postgis_topology--${UPGRADEABLE_VERSION}--${POSTGIS_LIB_VERSION}.sql COPYONLY)

    set(POSTGISTOPO_EXTENSION_FILES ${POSTGISTOPO_EXTENSION_FILES}
        ${CMAKE_CURRENT_BINARY_DIR}/sql/postgis_topology--${UPGRADEABLE_VERSION}--${POSTGIS_LIB_VERSION}.sql
    )
endforeach()

if(NOT SKIP_INSTALL_LIBRARIES AND NOT SKIP_INSTALL_ALL )
    install(FILES ${POSTGISTOPO_EXTENSION_FILES} DESTINATION "${PGSQL_SHAREDIR}/extension/")
endif()

