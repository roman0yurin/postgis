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

set(PGSQL2SHP_CLI pgsql2shp)
set(SHP2PGSQL_CLI shp2pgsql)
set(SHP2PGSQL_GUI shp2pgsql-gui)

set(SHPLIB_CSOURCES
    shpopen.c
    dbfopen.c
    getopt.c
    shpcommon.c
    safileio.c
)

set(SHP2PGSQL_HHEADERS
    shp2pgsql-core.h
    shpcommon.h
)

set(SHP2PGSQL_CSOURCES ${SHPLIB_CSOURCES}
    shp2pgsql-core.c
    shp2pgsql-cli.c
)

set(PGSQL2SHP_HHEADERS
    pgsql2shp-core.h
    shpcommon.h
)

set(PGSQL2SHP_CSOURCES ${SHPLIB_CSOURCES}
    pgsql2shp-core.c
    pgsql2shp-cli.c
)

set(SHP2PGSQL_GUI_CSOURCES ${SHPLIB_CSOURCES}
    shp2pgsql-gui.c
    shp2pgsql-core.c
    pgsql2shp-core.c
)


if(WIN32)
    set(SHP2PGSQL_GUI_CSOURCES ${SHP2PGSQL_GUI_CSOURCES}
        shp2pgsql-gui.rc
        shp2pgsql-gui.ico
    )
endif()

add_executable(${PGSQL2SHP_CLI} ${PGSQL2SHP_CSOURCES} ${PGSQL2SHP_HHEADERS})
target_link_extlibraries(${PGSQL2SHP_CLI})

add_executable(${SHP2PGSQL_CLI} ${SHP2PGSQL_CSOURCES} ${SHP2PGSQL_HHEADERS})
target_link_extlibraries(${SHP2PGSQL_CLI})

set(TARGETS_OUT ${PGSQL2SHP_CLI} ${SHP2PGSQL_CLI})
set(MAN_FILES
    ${CMAKE_SOURCE_DIR}/doc/man/pgsql2shp.1
    ${CMAKE_SOURCE_DIR}/doc/man/shp2pgsql.1
)

find_package(GTK2)
if(GTK2_FOUND)
    set(TARGET_LINK_LIB ${TARGET_LINK_LIB} ${GTK2_LIBRARIES})
    include_directories(${GTK2_INCLUDE_DIRS})

    if(WIN32)
        add_executable(${SHP2PGSQL_GUI} WIN32 ${SHP2PGSQL_GUI_CSOURCES} ${SHP2PGSQL_HHEADERS})
    else()
        add_executable(${SHP2PGSQL_GUI} ${SHP2PGSQL_GUI_CSOURCES} ${SHP2PGSQL_HHEADERS})
    endif()

    target_link_extlibraries(${SHP2PGSQL_GUI})
    set(TARGETS_OUT ${TARGETS_OUT} ${SHP2PGSQL_GUI})
    set(MAN_FILES ${MAN_FILES}
        ${CMAKE_CURRENT_SOURCE_DIR}/shp2pgsql-gui.1
    )
endif()

if(NOT SKIP_INSTALL_LIBRARIES AND NOT SKIP_INSTALL_ALL )
    install(TARGETS ${TARGETS_OUT}
        RUNTIME DESTINATION ${INSTALL_BIN_DIR} COMPONENT applications
        ARCHIVE DESTINATION ${INSTALL_LIB_DIR} COMPONENT applications
        LIBRARY DESTINATION ${INSTALL_LIB_DIR} COMPONENT applications
    )

    install(FILES ${MAN_FILES} DESTINATION "${INSTALL_MAN_DIR}/man1")
endif()
