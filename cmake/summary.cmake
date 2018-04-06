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

macro(summary_message text value is_text)
    string(ASCII 27 Esc)
    set(BoldYellow  "${Esc}[1;33m")
    set(Magenta     "${Esc}[35m")
    set(Cyan        "${Esc}[36m")
    set(BoldCyan    "${Esc}[1;36m")
    set(White       "${Esc}[37m")
    set(ColourReset "${Esc}[m")

    if(${is_text})
        message(STATUS "${BoldCyan}  ${text} ${${value}}${ColourReset}")
    elseif("${${value}}")
         message(STATUS "${BoldCyan}  ${text} yes${ColourReset}")
    else()
        message(STATUS "${Cyan}  ${text} no${ColourReset}")
    endif()
endmacro()

message(STATUS "PostGIS is now configured for ${CMAKE_SYSTEM_NAME}")

message(STATUS "\n-------------- Compiler Info -------------")
message(STATUS "  C compiler:                ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS}")

message(STATUS "\n---------------- Details -----------------")
summary_message("PostGIS version:           " POSTGIS_VERSION TRUE)
summary_message("PostGIS library version:   " POSTGIS_LIB_VERSION TRUE)
summary_message("PostGIS scripts version:   " POSTGIS_SCRIPTS_VERSION TRUE)
summary_message("PostGIS build date:        " POSTGIS_BUILD_DATE TRUE)
summary_message("PostgreSQL version:        " POSTGIS_PGSQL_VERSION TRUE)

message(STATUS "\n-------------- Dependencies --------------")
summary_message("GEOS support:              " WITH_GEOS FALSE)
summary_message("GDAL support:              " WITH_GDAL FALSE)
summary_message("PostgreSQL support:        " WITH_POSTGRESQL FALSE)
summary_message("PROJ.4 support:            " WITH_PROJ4 FALSE)
summary_message("libxml2 support:           " WITH_LibXml2 FALSE)
summary_message("PostGIS debug level:       " POSTGIS_DEBUG_LEVEL TRUE)

message(STATUS "\n--------------- Extensions ---------------")
summary_message("PostGIS Raster:            " POSTGIS_WITH_RASTER FALSE)
summary_message("PostGIS Topology:          " POSTGIS_WITH_TOPOLOGY FALSE)
summary_message("SFCGAL support:            " POSTGIS_WITH_SFCGAL FALSE)
summary_message("Address Standardizer support: " POSTGIS_WITH_ADDRESS_STD FALSE)

