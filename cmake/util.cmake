################################################################################
# Project:  CMake4GDAL
# Purpose:  CMake build scripts
# Author:   Dmitry Baryshnikov, polimax@mail.ru
################################################################################
# Copyright (C) 2015, NextGIS <info@nextgis.com>
# Copyright (C) 2012,2013,2014 Dmitry Baryshnikov
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

SET(THREE_PART_VERSION_REGEX "[0-9]+\\.[0-9]+\\.[0-9]+")

# Breaks up a string in the form n1.n2.n3 into three parts and stores
# them in major, minor, and patch.  version should be a value, not a
# variable, while major, minor and patch should be variables.
MACRO(THREE_PART_VERSION_TO_VARS version major minor patch)
  IF(${version} MATCHES ${THREE_PART_VERSION_REGEX})
    STRING(REGEX REPLACE "^([0-9]+)\\.[0-9]+\\.[0-9]+" "\\1" ${major} "${version}")
    STRING(REGEX REPLACE "^[0-9]+\\.([0-9])+\\.[0-9]+" "\\1" ${minor} "${version}")
    STRING(REGEX REPLACE "^[0-9]+\\.[0-9]+\\.([0-9]+)" "\\1" ${patch} "${version}")
  ELSE(${version} MATCHES ${THREE_PART_VERSION_REGEX})
    MESSAGE("MACRO(THREE_PART_VERSION_TO_VARS ${version} ${major} ${minor} ${patch}")
    MESSAGE(FATAL_ERROR "Problem parsing version string, I can't parse it properly.")
  ENDIF(${version} MATCHES ${THREE_PART_VERSION_REGEX})
ENDMACRO(THREE_PART_VERSION_TO_VARS)

function(check_svn_revision rev)
    file(READ "${CMAKE_SOURCE_DIR}/postgis_svn_revision.h" _POSTGIS_SVN)
    string(STRIP ${_POSTGIS_SVN} _POSTGIS_SVN)

    string(REGEX MATCH "POSTGIS_SVN_REVISION[t\ ]([0-9]+)"
        POSTGIS_SVN_REVISION ${_POSTGIS_SVN})
    string (REGEX MATCH "([0-9]+)"
      POSTGIS_SVN_REVISION ${POSTGIS_SVN_REVISION})
    set(${rev} ${POSTGIS_SVN_REVISION} PARENT_SCOPE)
endfunction()

function(check_version major minor rev)

    file(READ "${CMAKE_SOURCE_DIR}/Version.config" _POSTGIS_VERSION_CONFIG)
    string(STRIP ${_POSTGIS_VERSION_CONFIG} _POSTGIS_VERSION_CONFIG)

    string(REGEX REPLACE ".*POSTGIS_MAJOR_VERSION=([0-9]+)[\r\n\t\ ].*" "\\1"
        POSTGIS_MAJOR_VERSION ${_POSTGIS_VERSION_CONFIG})
    string(REGEX REPLACE ".*POSTGIS_MINOR_VERSION=([0-9]+)[\r\n\t\ ].*" "\\1"
        POSTGIS_MINOR_VERSION "${_POSTGIS_VERSION_CONFIG}")
    string(REGEX REPLACE ".*POSTGIS_MICRO_VERSION=([0-9]+).*[\r\n\t\ ].*" "\\1"
        POSTGIS_MICRO_VERSION "${_POSTGIS_VERSION_CONFIG}")

    set(${major} ${POSTGIS_MAJOR_VERSION} PARENT_SCOPE)
    set(${minor} ${POSTGIS_MINOR_VERSION} PARENT_SCOPE)
    set(${rev} ${POSTGIS_MICRO_VERSION} PARENT_SCOPE)
endfunction()

function(check_lwgeom_version major minor rev)

    file(READ "${CMAKE_SOURCE_DIR}/Version.config" _POSTGIS_VERSION_CONFIG)
    string(STRIP ${_POSTGIS_VERSION_CONFIG} _POSTGIS_VERSION_CONFIG)

    string(REGEX REPLACE ".*LIBLWGEOM_IFACE_CUR=([0-9]+)[\r\n\t\ ].*" "\\1"
        LIBLWGEOM_IFACE_CUR ${_POSTGIS_VERSION_CONFIG})
    string(REGEX REPLACE ".*LIBLWGEOM_IFACE_AGE=([0-9]+)[\r\n\t\ ].*" "\\1"
        LIBLWGEOM_IFACE_AGE "${_POSTGIS_VERSION_CONFIG}")
    string(REGEX REPLACE ".*LIBLWGEOM_IFACE_REV=([0-9]+).*" "\\1"
        LIBLWGEOM_IFACE_REV "${_POSTGIS_VERSION_CONFIG}")

    set(${major} ${LIBLWGEOM_IFACE_CUR} PARENT_SCOPE)
    set(${minor} ${LIBLWGEOM_IFACE_AGE} PARENT_SCOPE)
    set(${rev} ${LIBLWGEOM_IFACE_REV} PARENT_SCOPE)
endfunction()

function(check_raster_version major minor rev)

    file(READ "${CMAKE_SOURCE_DIR}/raster/Version.config" _POSTGIS_VERSION_CONFIG)
    string(STRIP ${_POSTGIS_VERSION_CONFIG} _POSTGIS_VERSION_CONFIG)

    string(REGEX REPLACE ".*POSTGIS_RASTER_MAJOR_VERSION=([0-9a-z]+)[\r\n\t\ ].*" "\\1"
        POSTGIS_RASTER_MAJOR_VERSION ${_POSTGIS_VERSION_CONFIG})
    string(REGEX REPLACE ".*POSTGIS_RASTER_MINOR_VERSION=([0-9a-z]+)[\r\n\t\ ].*" "\\1"
        POSTGIS_RASTER_MINOR_VERSION "${_POSTGIS_VERSION_CONFIG}")
    string(REGEX REPLACE ".*POSTGIS_RASTER_MICRO_VERSION=([0-9a-z]+).*" "\\1"
        POSTGIS_RASTER_MICRO_VERSION "${_POSTGIS_VERSION_CONFIG}")

    set(${major} ${POSTGIS_RASTER_MAJOR_VERSION} PARENT_SCOPE)
    set(${minor} ${POSTGIS_RASTER_MINOR_VERSION} PARENT_SCOPE)
    set(${rev} ${POSTGIS_RASTER_MICRO_VERSION} PARENT_SCOPE)
endfunction()

function(report_version name ver)

    string(ASCII 27 Esc)
    set(BoldYellow  "${Esc}[1;33m")
    set(ColourReset "${Esc}[m")

    message(STATUS "${BoldYellow}${name} version ${ver}${ColourReset}")

endfunction()

function(prepare_extension_sql input_path output_path)
    file (READ ${input_path} _file_content)
	string (REPLACE "COMMIT;" "--COMMIT" _file_content "${_file_content}")
	string (REPLACE "BEGIN;" "--BEGIN" _file_content "${_file_content}")

    file(WRITE ${output_path} "-- extension ready \n")
    file(APPEND ${output_path} "${_file_content}")
endfunction()

function(append_file file_to_append file_which_append)
    file(READ ${file_which_append} APPEND_DATA)
    file(APPEND ${file_to_append} "${APPEND_DATA}\n")
    unset(APPEND_DATA)
endfunction()

function(create_undef name)
#/usr/bin/perl ../utils/create_undef.pl postgis.sql 94 > uninstall_postgis.sql
    execute_process(COMMAND ${PERL_EXECUTABLE}
                    ${CMAKE_SOURCE_DIR}/utils/create_undef.pl
                    ${CMAKE_CURRENT_BINARY_DIR}/${name}.sql ${POSTGIS_PGSQL_VERSION}
                OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/uninstall_${name}.sql)

endfunction()

# macro to find packages on the host OS
macro( find_exthost_package )
    if(CMAKE_CROSSCOMPILING)
        set( CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER )
        set( CMAKE_FIND_ROOT_PATH_MODE_LIBRARY NEVER )
        set( CMAKE_FIND_ROOT_PATH_MODE_INCLUDE NEVER )

        find_package( ${ARGN} )

        set( CMAKE_FIND_ROOT_PATH_MODE_PROGRAM ONLY )
        set( CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY )
        set( CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY )
    else()
        find_package( ${ARGN} )
    endif()
endmacro()


# macro to find programs on the host OS
macro( find_exthost_program )
    if(CMAKE_CROSSCOMPILING)
        set( CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER )
        set( CMAKE_FIND_ROOT_PATH_MODE_LIBRARY NEVER )
        set( CMAKE_FIND_ROOT_PATH_MODE_INCLUDE NEVER )

        find_program( ${ARGN} )

        set( CMAKE_FIND_ROOT_PATH_MODE_PROGRAM ONLY )
        set( CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY )
        set( CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY )
    else()
        find_program( ${ARGN} )
    endif()
endmacro()
