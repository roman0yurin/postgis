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

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-variable")

set(RASTER2PGSQL raster2pgsql)

set(CSOURCES
    raster2pgsql.c
)

set(HHEADERS
    raster2pgsql.h
)

add_executable(${RASTER2PGSQL} ${CSOURCES} ${HHEADERS})
target_link_extlibraries(${RASTER2PGSQL})

set(MAN_FILES
    ${CMAKE_POSTGIS_SOURCE_DIR}/doc/man/raster2pgsql.1
)

if(NOT SKIP_INSTALL_LIBRARIES AND NOT SKIP_INSTALL_ALL )
    install(TARGETS ${RASTER2PGSQL}
        RUNTIME DESTINATION ${INSTALL_BIN_DIR} COMPONENT applications
        ARCHIVE DESTINATION ${INSTALL_LIB_DIR} COMPONENT applications
        LIBRARY DESTINATION ${INSTALL_LIB_DIR} COMPONENT applications
    )

    install(FILES ${MAN_FILES} DESTINATION "${INSTALL_MAN_DIR}/man1")
endif()
