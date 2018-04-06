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

configure_file(postgis.control.in ${CMAKE_CURRENT_BINARY_DIR}/postgis.control)

prepare_extension_sql(${CMAKE_BINARY_DIR}/postgis/postgis.sql ${CMAKE_CURRENT_BINARY_DIR}/postgis.sql)

execute_process(COMMAND ${PERL_EXECUTABLE}
                    ${CMAKE_SOURCE_DIR}/utils/create_spatial_ref_sys_config_dump.pl
                    ${CMAKE_SOURCE_DIR}/spatial_ref_sys.sql
                OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/spatial_ref_sys_config_dump.sql)
prepare_extension_sql(${CMAKE_SOURCE_DIR}/spatial_ref_sys.sql ${CMAKE_CURRENT_BINARY_DIR}/spatial_ref_sys.sql)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/sql)
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/sql/postgis.sql "\\echo Use \"CREATE EXTENSION postgis\" to load this file. \\quit\n")

if(POSTGIS_WITH_RASTER)
    #sed -e 's/BEGIN;//g' -e 's/COMMIT;//g'  ../../raster/rt_pg/rtpostgis.sql > sql_bits/rtpostgis.sql
    prepare_extension_sql(${CMAKE_BINARY_DIR}/raster/rt_pg/rtpostgis.sql ${CMAKE_CURRENT_BINARY_DIR}/rtpostgis.sql)
endif()

#cat sql_bits/postgis.sql sql_bits/postgis_comments.sql sql_bits/rtpostgis.sql sql_bits/spatial_ref_sys_config_dump.sql sql_bits/raster_comments.sql sql_bits/spatial_ref_sys.sql >> sql/postgis.sql

set(APPEND_POSTGIS
    ${CMAKE_CURRENT_BINARY_DIR}/postgis.sql
    ${CMAKE_SOURCE_DIR}/doc/postgis_comments.sql
    ${CMAKE_CURRENT_BINARY_DIR}/spatial_ref_sys_config_dump.sql
    ${CMAKE_CURRENT_BINARY_DIR}/spatial_ref_sys.sql
)

if(POSTGIS_WITH_RASTER)
    set(APPEND_POSTGIS ${APPEND_POSTGIS}
        ${CMAKE_CURRENT_BINARY_DIR}/rtpostgis.sql
        ${CMAKE_SOURCE_DIR}/doc/raster_comments.sql
    )
endif()

foreach(APPEND_FILE ${APPEND_POSTGIS})
    append_file(${CMAKE_CURRENT_BINARY_DIR}/sql/postgis.sql
                ${APPEND_FILE})
endforeach()

configure_file(${CMAKE_CURRENT_BINARY_DIR}/sql/postgis.sql
     ${CMAKE_CURRENT_BINARY_DIR}/sql/postgis--${POSTGIS_LIB_VERSION}.sql COPYONLY)

#cat ../../postgis/postgis.sql ../../raster/rt_pg/rtpostgis.sql | /usr/bin/perl ../../utils/create_unpackaged.pl postgis > sql/postgis--unpackaged--2.2.2.sql


file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/postgis_unpackaged.sql "-- unpackaged\n")
append_file(${CMAKE_CURRENT_BINARY_DIR}/postgis_unpackaged.sql
            ${CMAKE_BINARY_DIR}/postgis/postgis.sql)

if(POSTGIS_WITH_RASTER)
    append_file(${CMAKE_CURRENT_BINARY_DIR}/postgis_unpackaged.sql
                ${CMAKE_BINARY_DIR}/raster/rt_pg/rtpostgis.sql)
endif()

execute_process(COMMAND ${PERL_EXECUTABLE}
                    ${CMAKE_SOURCE_DIR}/utils/create_unpackaged.pl
                    postgis
                    ${CMAKE_CURRENT_BINARY_DIR}/postgis_unpackaged.sql
                OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/sql/postgis--unpackaged--${POSTGIS_LIB_VERSION}.sql)

macro(prepare_extension_drop_sql input_path output_path)
    file(WRITE ${output_path} "-- extension ready \n")

    set(DONE FALSE)
    set(CURRENT_OFFSET 0)
    set(LEFT_STR)
    while(NOT DONE)
	    file(READ ${input_path} FILE_DATA LIMIT 4097 OFFSET ${CURRENT_OFFSET})
	    string(LENGTH "${FILE_DATA}" FILE_DATA_LEN) # EOF
	    if(FILE_DATA_LEN EQUAL 0)
	        break()
	    endif()

	    if(FILE_DATA_LEN EQUAL 4097) # cut '\n'
	        string(SUBSTRING "${FILE_DATA}" 0 4096 FILE_DATA)
	        set(FILE_DATA_LEN 4096)
	    endif()

	    MATH(EXPR CURRENT_OFFSET "${CURRENT_OFFSET}+${FILE_DATA_LEN}")

	    set(FILE_DATA "${LEFT_STR}${FILE_DATA}")

	    set(SCAN_DONE FALSE)
	    while(NOT SCAN_DONE)

	        string(FIND "${FILE_DATA}" "\n" POS)

	        if(POS EQUAL -1)
	            set(LEFT_STR "${FILE_DATA}")
	            break()
	        endif()

	        MATH(EXPR AFT_POS "${POS}+1")
	        string(SUBSTRING "${FILE_DATA}" 0 ${AFT_POS} LEFT_STR)

	        set(CONTINUE TRUE)
	        if(LEFT_STR MATCHES ".*BEGIN;.*" OR LEFT_STR MATCHES ".*COMMIT;.*")
	            string(SUBSTRING "${FILE_DATA}" ${AFT_POS} -1 FILE_DATA)
                set(CONTINUE FALSE)
            endif()

            if(CONTINUE)
                if(LEFT_STR MATCHES "^DROP.*;")
                    string (REGEX REPLACE "^(DROP.*);" "SELECT postgis_extension_drop_if_exists('postgis', '\\1');\n\\1;" LEFT_STR "${LEFT_STR}")
                endif()

	            file(APPEND ${output_path} "${LEFT_STR}")
	            string(SUBSTRING "${FILE_DATA}" ${AFT_POS} -1 FILE_DATA)
	        endif()
	    endwhile()

    endwhile()

    if(LEFT_STR MATCHES ".*BEGIN;.*" OR LEFT_STR MATCHES ".*COMMIT;.*")
        set(LEFT_STR)
    endif()
    if(LEFT_STR MATCHES "^DROP.*;")
        string (REGEX REPLACE "^(DROP.*);" "SELECT postgis_extension_drop_if_exists('postgis', '\\1');\n\\1;" LEFT_STR "${LEFT_STR}")
    endif()
    file(APPEND ${output_path} "${LEFT_STR}")

endmacro()

#sed -e 's/BEGIN;//g' -e 's/COMMIT;//g' \
#    -e "s/^\(DROP .*\);/SELECT postgis_extension_drop_if_exists('postgis', '\1');\n\1;/" \
#../../postgis/postgis_upgrade.sql > sql_bits/postgis_upgrade.sql

prepare_extension_drop_sql(${CMAKE_BINARY_DIR}/postgis/postgis_upgrade.sql
                           ${CMAKE_CURRENT_BINARY_DIR}/postgis_upgrade.sql)


set(POSTGIS_EXTENSION_FILES
    ${CMAKE_CURRENT_BINARY_DIR}/postgis.control
    ${CMAKE_CURRENT_BINARY_DIR}/sql/postgis--unpackaged--${POSTGIS_LIB_VERSION}.sql
    ${CMAKE_CURRENT_BINARY_DIR}/sql/postgis--${POSTGIS_LIB_VERSION}.sql
)

if(POSTGIS_WITH_RASTER)
#sed -e 's/BEGIN;//g' -e 's/COMMIT;//g' \
#    -e "s/^\(DROP .*\);/SELECT postgis_extension_drop_if_exists('postgis', '\1');\n\1;/" \
#../../raster/rt_pg/rtpostgis_upgrade.sql > sql_bits/rtpostgis_upgrade.sql
    prepare_extension_drop_sql(${CMAKE_BINARY_DIR}/raster/rt_pg/rtpostgis_upgrade.sql
                               ${CMAKE_CURRENT_BINARY_DIR}/rtpostgis_upgrade.sql)

#echo '\echo Use "CREATE EXTENSION postgis" to load this file. \quit' > sql_bits/postgis_raster_upgrade_minor.sql
    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/postgis_raster_upgrade_minor.sql
        "\\echo Use \"CREATE EXTENSION postgis\" to load this file. \\quit\n")
#cat ../postgis_extension_helper.sql sql_bits/postgis_upgrade.sql sql_bits/rtpostgis_upgrade.sql ../../doc/raster_comments.sql ../../doc/postgis_comments.sql ../postgis_extension_helper_uninstall.sql >> sql_bits/postgis_raster_upgrade_minor.sql
    append_file(${CMAKE_CURRENT_BINARY_DIR}/postgis_raster_upgrade_minor.sql
                ../postgis_extension_helper.sql)
    append_file(${CMAKE_CURRENT_BINARY_DIR}/postgis_raster_upgrade_minor.sql
                ${CMAKE_CURRENT_BINARY_DIR}/postgis_upgrade.sql)
    append_file(${CMAKE_CURRENT_BINARY_DIR}/postgis_raster_upgrade_minor.sql
                ${CMAKE_CURRENT_BINARY_DIR}/rtpostgis_upgrade.sql)
    append_file(${CMAKE_CURRENT_BINARY_DIR}/postgis_raster_upgrade_minor.sql
                ${CMAKE_SOURCE_DIR}/doc/raster_comments.sql)
    append_file(${CMAKE_CURRENT_BINARY_DIR}/postgis_raster_upgrade_minor.sql
                ${CMAKE_SOURCE_DIR}/doc/postgis_comments.sql)
    append_file(${CMAKE_CURRENT_BINARY_DIR}/postgis_raster_upgrade_minor.sql
                ../postgis_extension_helper_uninstall.sql)

#cp sql_bits/postgis_raster_upgrade_minor.sql sql/postgis--2.2.2--2.2.2next.sql
    configure_file(${CMAKE_CURRENT_BINARY_DIR}/postgis_raster_upgrade_minor.sql
        ${CMAKE_CURRENT_BINARY_DIR}/sql/postgis--${POSTGIS_LIB_VERSION}--${POSTGIS_LIB_VERSION}next.sql COPYONLY)
#cp sql_bits/postgis_raster_upgrade_minor.sql sql/postgis--2.2.2next--2.2.2.sql
    configure_file(${CMAKE_CURRENT_BINARY_DIR}/postgis_raster_upgrade_minor.sql
        ${CMAKE_CURRENT_BINARY_DIR}/sql/postgis--${POSTGIS_LIB_VERSION}next--${POSTGIS_LIB_VERSION}.sql COPYONLY)

    set(POSTGIS_EXTENSION_FILES ${POSTGIS_EXTENSION_FILES}
        ${CMAKE_CURRENT_BINARY_DIR}/sql/postgis--${POSTGIS_LIB_VERSION}--${POSTGIS_LIB_VERSION}next.sql
        ${CMAKE_CURRENT_BINARY_DIR}/sql/postgis--${POSTGIS_LIB_VERSION}next--${POSTGIS_LIB_VERSION}.sql
    )

#for OLD_VERSION in 2.0.0 2.0.1 2.0.2 2.0.3 2.0.4 2.0.5 2.0.6 2.0.7 2.1.0 2.1.1 2.1.2 2.1.3 2.1.4 2.1.5 2.1.6 2.1.7 2.1.8 2.1.9 2.2.0 2.2.1 2.2.2; do \
#  	  cat sql_bits/postgis_raster_upgrade_minor.sql > sql/postgis--$OLD_VERSION--2.2.2.sql; \
#done
    foreach(UPGRADEABLE_VERSION ${UPGRADEABLE_VERSIONS})
        configure_file(${CMAKE_CURRENT_BINARY_DIR}/postgis_raster_upgrade_minor.sql
            ${CMAKE_CURRENT_BINARY_DIR}/sql/postgis--${UPGRADEABLE_VERSION}--${POSTGIS_LIB_VERSION}.sql COPYONLY)

        set(POSTGIS_EXTENSION_FILES ${POSTGIS_EXTENSION_FILES}
            ${CMAKE_CURRENT_BINARY_DIR}/sql/postgis--${UPGRADEABLE_VERSION}--${POSTGIS_LIB_VERSION}.sql
        )
    endforeach()
endif()

if(NOT SKIP_INSTALL_LIBRARIES AND NOT SKIP_INSTALL_ALL )
    install(FILES ${POSTGIS_EXTENSION_FILES} DESTINATION "${PGSQL_SHAREDIR}/extension/")
endif()

