################################################################################
# CMakeLists.txt - root CMake configuration file, part PostGIS project
#
# Copyright (C) 2012 Mateusz Loskot <mateusz@loskot.net>
# Copyright (C) 2016, NextGIS <info@nextgis.com>
# @author Юрин Роман @date 05.03.2018
################################################################################
project(postgis C CXX)
cmake_minimum_required(VERSION 3.5.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_C_STANDARD 11)

#модульные зависимости Postgis
set(POSTGIS_SUBMODULES pq geos-static geos_c geos-static gdal proj4 sfcgal CGAL CGAL_Core CGAL_ImageIO)

#Устанавливаем корневые папки для модуля CGAL
set(CMAKE_POSTGIS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_POSTGIS_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

# some init settings
set(CMAKE_COLOR_MAKEFILE ON)
# set path to additional CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_POSTGIS_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH})
include(util)
include(GNUInstallDirs)
################################################################################
# User options to control PostGIS features

option(POSTGIS_WITH_RASTER
    "Set ON|OFF (default=ON) to control building raster extension" ON)

option(POSTGIS_WITH_TOPOLOGY
    "Set ON|OFF (default=ON) to control building topology extension" ON)

# TODO: Add cgal support from https://github.com/nextgis-borsch/lib_cgal
option(POSTGIS_WITH_SFCGAL
    "Set ON|OFF (default=OFF) to control building SFCGAL extension" ON)

option(POSTGIS_WITH_ADDRESS_STD
    "Set ON|OFF (default=ON) to control building address standardizer extension" ON)

option(POSTGIS_WITH_RASTER_WARN_ON_TRUNCATION
    "Set ON|OFF (default=OFF) to control warning outputted every time a double is truncated" OFF)
set(POSTGIS_RASTER_WARN_ON_TRUNCATION 0)
if(POSTGIS_WITH_RASTER_WARN_ON_TRUNCATION)
    set(POSTGIS_RASTER_WARN_ON_TRUNCATION 1)
endif()

option(POSTGIS_ENABLE_STATS
    "Set ON|OFF (default=ON) to control use ANALYZE statistics" ON)
set(POSTGIS_USE_STATS 1)
if(NOT POSTGIS_ENABLE_STATS)
    set(POSTGIS_USE_STATS 0)
endif()


################################################################################
# Version and build date information
check_version(POSTGIS_MAJOR_VERSION POSTGIS_MINOR_VERSION POSTGIS_MICRO_VERSION)
check_raster_version(POSTGIS_RASTER_MAJOR_VERSION POSTGIS_RASTER_MINOR_VERSION POSTGIS_RASTER_MICRO_VERSION)

set(POSTGIS_USE_PROJ 1) # Proj.4 is required
set(POSTGIS_USE_GEOS 1) # GEOS is required

set(POSTGIS_VERSION "${POSTGIS_MAJOR_VERSION}.${POSTGIS_MINOR_VERSION} USE_GEOS=${POSTGIS_USE_GEOS} USE_PROJ=${POSTGIS_USE_PROJ} USE_STATS=${POSTGIS_USE_STATS}")
set(POSTGIS_LIB_VERSION "${POSTGIS_MAJOR_VERSION}.${POSTGIS_MINOR_VERSION}.${POSTGIS_MICRO_VERSION}")
set(POSTGIS_SCRIPTS_VERSION "${POSTGIS_LIB_VERSION}")

set(POSTGIS_RASTER_VERSION "${POSTGIS_RASTER_MAJOR_VERSION}.${POSTGIS_RASTER_MINOR_VERSION}")
set(POSTGIS_RASTER_LIB_VERSION "${POSTGIS_RASTER_MAJOR_VERSION}.${POSTGIS_RASTER_MINOR_VERSION}.${POSTGIS_RASTER_MICRO_VERSION}")
set(POSTGIS_RASTER_SCRIPTS_VERSION "${POSTGIS_RASTER_LIB_VERSION}")

report_version(${PROJECT_NAME} ${POSTGIS_VERSION})

set(TARGET_OBJECTS)

include(FindAnyProject)
include(PostGISUtilities)

if(NOT SUPPRESS_VERBOSE_OUTPUT)
    message(STATUS)
    colormsg(_HIBLUE_ "Configuring PostGIS:")
    message(STATUS)
endif()

################################################################################
#Продключаем модуль Postgres
set(WITH_POSTGRESQL ON)
set(POSTGIS_POSTGRESQL_VERSION 103)
set(PGSQL_VERSION_MAJOR 10)
set(PGSQL_VERSION_MINOR 3)
get_property(POSTGRES_INCLUDE_DIRS GLOBAL PROPERTY POSTGRES_INCLUDE_DIRS)
get_property(PGSQL_INCLUDEDIR GLOBAL PROPERTY POSTGRES_INCLUDE_ROOT)
include_directories(${POSTGRES_INCLUDE_DIRS})
set(PGSQL_INCLUDEDIR_SERVER ${PGSQL_INCLUDEDIR}/server)

set(HAVE_LIBPQ 1)
set(POSTGIS_PGSQL_VERSION ${PGSQL_VERSION_MAJOR}${PGSQL_VERSION_MINOR})


#exec_program(${PG_CONFIG} ARGS --includedir
#    OUTPUT_VARIABLE PGSQL_INCLUDEDIR)
#exec_program(${PG_CONFIG} ARGS --includedir-server
#    OUTPUT_VARIABLE PGSQL_INCLUDEDIR_SERVER)
#exec_program(${PG_CONFIG} ARGS --pgxs
#    OUTPUT_VARIABLE PGSQL_PGXS)
#
#if(NOT EXISTS ${PGSQL_PGXS})
#    message(FATAL_ERROR "The PGXS Makefile '${PGSQL_PGXS}' cannot be found. Please install the PostgreSQL server development packages")
#endif()

include_directories(${PGSQL_INCLUDEDIR})
include_directories(${PGSQL_INCLUDEDIR_SERVER})
message("Postgres server include ${PGSQL_INCLUDEDIR}")
if(WIN32)
    include_directories(${PGSQL_INCLUDEDIR_SERVER}/port/win32)
    if(MSVC)
        include_directories(${PGSQL_INCLUDEDIR_SERVER}/port/win32_msvc)
    endif()
endif()

#exec_program(${PG_CONFIG} ARGS --pkglibdir OUTPUT_VARIABLE PGSQL_PKGLIBDIR)
get_property(PGSQL_PKGLIBDIR GLOBAL PROPERTY POSTGRES_DISTRIB_LIB_DIR)
#exec_program(${PG_CONFIG} ARGS --sharedir OUTPUT_VARIABLE PGSQL_SHAREDIR)
get_property(PGSQL_SHAREDIR GLOBAL PROPERTY POSTGRES_DISTRIB_SHARE_DIR)
#exec_program(${PG_CONFIG} ARGS --bindir OUTPUT_VARIABLE PGSQL_PKGBINDIR)
get_property(PGSQL_PKGBINDIR GLOBAL PROPERTY POSTGRES_DISTRIB_BIN_DIR)
#exec_program(${PG_CONFIG} ARGS --localedir OUTPUT_VARIABLE PGSQL_LOCALEDIR)
get_property(PGSQL_LOCALEDIR GLOBAL PROPERTY POSTGRES_DISTRIB_LOCALE_DIR)

set(INSTALL_BIN_DIR ${PGSQL_PKGLIBDIR} CACHE INTERNAL "Installation directory for executables" FORCE)
set(INSTALL_LIB_DIR ${PGSQL_PKGLIBDIR} CACHE INTERNAL "Installation directory for libraries" FORCE)
set(INSTALL_INC_DIR ${PGSQL_INCLUDEDIR} CACHE INTERNAL "Installation directory for headers" FORCE)
set(INSTALL_MAN_DIR ${PGSQL_SHAREDIR} CACHE INTERNAL "Installation directory for headers" FORCE)

#set(TARGET_LINK_LIB ${TARGET_LINK_LIB} ${POSTGRESQL_LIBRARIES})

find_anyproject(ICONV DEFAULT ON) #default OFF, to set ON add DEFAULT ON
if(ICONV_FOUND)
    set(HAVE_ICONV TRUE)
endif()

################################################################################
# Dependency (required): PROJ.4
get_property(PROJ4_INDLUDE_DIRS GLOBAL PROPERTY PROJ4_INDLUDE_DIRS)
include_directories(${PROJ4_INDLUDE_DIRS})
set(POSTGIS_PROJ4_VERSION 49)
set(WITH_PROJ4 ON)
################################################################################
# Dependency (required): GEOS
get_property(GEOS_INCLUDE_DIRS GLOBAL PROPERTY GEOS_INCLUDE_DIRS)
include_directories(${GEOS_INCLUDE_DIRS})
set(POSTGIS_GEOS_VERSION 36)
set(WITH_GEOS ON)
################################################################################
# Dependency (optional): GDAL
if(POSTGIS_WITH_RASTER)
    get_property(GDAL_INCLUDE_DIRS GLOBAL PROPERTY GDAL_INCLUDE_DIRS)
    include_directories(${GDAL_INCLUDE_DIRS})
    set(POSTGIS_GDAL_VERSION 22)
    set(WITH_GDAL ON)
endif()

find_anyproject(LibXml2 REQUIRED)
if(LIBXML2_FOUND)
    set(POSTGIS_LIBXML2_VERSION ${LIBXML2_VERSION_STRING})
endif()

find_package(Perl)

find_package(Protobuf)

# Determine build date and time
string(TIMESTAMP POSTGIS_BUILD_DATE "%Y-%m-%d %H:%M:%S" UTC)
string(TIMESTAMP POSTGIS_RASTER_BUILD_DATE "%Y-%m-%d %H:%M:%S" UTC)

include(configure)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_POSTGIS_SOURCE_DIR})

if(WIN32)
    add_definitions(-DDLL_EXPORT)
else()
  # Warnings specification
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wmissing-prototypes")

  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffloat-store")

  # Turn on Position Independent Code generation for GEOS C shared library
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -DPIC")
endif()

################################################################################
# Configure all subdirectories with any build targets
### Object libraries
add_subdirectory(liblwgeom)

get_property(LIBLWGEOM_INCLUDE_DIRS GLOBAL PROPERTY LIBLWGEOM_INCLUDE_DIRS)
include_directories(${LIBLWGEOM_INCLUDE_DIRS})

add_subdirectory(libpgcommon)

get_property(LIBPGCOMMON_INCLUDE_DIRS GLOBAL PROPERTY LIBPGCOMMON_INCLUDE_DIRS)
include_directories(${LIBPGCOMMON_INCLUDE_DIRS})

if(POSTGIS_WITH_RASTER)
    add_subdirectory(raster)
endif()

if(POSTGIS_WITH_TOPOLOGY)
    add_subdirectory(topology)
endif()

if(POSTGIS_WITH_SFCGAL)
    get_property(SFCGAL_INCLUDE_DIRS GLOBAL PROPERTY SFCGAL_INCLUDE_DIRS)
    include_directories(${SFCGAL_INCLUDE_DIRS})
    set(POSTGIS_SFCGAL_VERSION 13)
    set(HAVE_SFCGAL_RESULT yes)
endif()

### Shared libraries
add_subdirectory(postgis)
add_subdirectory(extensions)

#set(TARGET_LINK_LIB ${TARGET_LINK_LIB} ${PostgreSQL_LIBRARIES})
add_subdirectory(loader)

################################################################################
# uninstall
add_custom_target(uninstall_postgis COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

# info
if(NOT SUPPRESS_VERBOSE_OUTPUT)
    include(summary)
endif()

add_custom_target(installPostgisDb
        COMMAND ${check_make_command} install -j 8
        DEPENDS postgis
)
