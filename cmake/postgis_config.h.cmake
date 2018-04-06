#ifndef POSTGIS_CONFIG_H
#define POSTGIS_CONFIG_H 1

#include "postgis_svn_revision.h"

/* checking whether NLS is requested */
#cmakedefine ENABLE_NLS 1

/* Define to 1 if GDALFPolygonize function is available */
#cmakedefine GDALFPOLYGONIZE 1

/* Define to 1 if you have the MacOS X function CFLocaleCopyCurrent in the
   CoreFoundation framework. */
#cmakedefine HAVE_CFLOCALECOPYCURRENT 1

/* Define to 1 if you have the MacOS X function CFPreferencesCopyAppValue in
   the CoreFoundation framework. */
#cmakedefine HAVE_CFPREFERENCESCOPYAPPVALUE 1

/* Define if the GNU dcgettext() function is already present or preinstalled.
   */
#cmakedefine HAVE_DCGETTEXT 1
#cmakedefine HAVE_VASPRINTF 1
#cmakedefine HAVE_ASPRINTF 1
#cmakedefine HAVE_GNU_ISFINITE 1
#cmakedefine HAVE_FSEEKO 1
#cmakedefine HAVE_STRCASESTR 1

/* cmakedefine to 1 if you have the <dlfcn.h> header file. */
#cmakedefine HAVE_DLFCN_H 1

/* Define if the GNU gettext() function is already present or preinstalled. */
#cmakedefine HAVE_GETTEXT 1

/* cmakedefined if libiconv headers and library are present */
#cmakedefine HAVE_ICONV 1

/* Define to 1 if you have the `iconvctl' function. */
#cmakedefine HAVE_ICONVCTL 1

/* Define to 1 if you have the `libiconvctl' function. */
#cmakedefine HAVE_LIBICONVCTL 1

/* ieeefp.h header */
#cmakedefine HAVE_IEEEFP_H 1

/* cmakedefine to 1 if you have the <inttypes.h> header file. */
#cmakedefine HAVE_INTTYPES_H 1

/* cmakedefine to 1 if you have the `geos_c' library (-lgeos_c). */
#cmakedefine HAVE_LIBGEOS_C 1

/* cmakedefine to 1 if you have the `pq' library (-lpq). */
#cmakedefine HAVE_LIBPQ 1

/* cmakedefine to 1 if you have the `proj' library (-lproj). */
#cmakedefine HAVE_LIBPROJ 1

/* Define to 1 if you have the `xml2' library (-lxml2). */
#cmakedefine HAVE_LIBXML2 1

/* Define to 1 if you have the <libxml/parser.h> header file. */
#cmakedefine HAVE_LIBXML_PARSER_H 1

/* Define to 1 if you have the <libxml/tree.h> header file. */
#cmakedefine HAVE_LIBXML_TREE_H 1

/* Define to 1 if you have the <libxml/xpathInternals.h> header file. */
#cmakedefine HAVE_LIBXML_XPATHINTERNALS_H 1

/* Define to 1 if you have the <libxml/xpath.h> header file. */
#cmakedefine HAVE_LIBXML_XPATH_H 1

/* cmakedefine to 1 if you have the <memory.h> header file. */
#cmakedefine HAVE_MEMORY_H 1

/* cmakedefine to 1 if you have the <stdint.h> header file. */
#cmakedefine HAVE_STDINT_H 1

/* cmakedefine to 1 if you have the <stdlib.h> header file. */
#ifndef HAVE_STDLIB_H
#cmakedefine HAVE_STDLIB_H 1
#endif // HAVE_STDLIB_H

/* cmakedefine to 1 if you have the <strings.h> header file. */
#cmakedefine HAVE_STRINGS_H 1

/* cmakedefine to 1 if you have the <string.h> header file. */
#cmakedefine HAVE_STRING_H 1

/* cmakedefine to 1 if you have the <sys/stat.h> header file. */
#cmakedefine HAVE_SYS_STAT_H 1

/* cmakedefine to 1 if you have the <sys/types.h> header file. */
#cmakedefine HAVE_SYS_TYPES_H 1

/* cmakedefine to 1 if you have the <unistd.h> header file. */
#cmakedefine HAVE_UNISTD_H 1

/* cmakedefine to 1 if you don't have the <unistd.h> header file. */
#cmakedefine YY_NO_UNISTD_H 1

/* Location of PostgreSQL locale directory */
#cmakedefine PGSQL_LOCALEDIR "@PGSQL_LOCALEDIR@"

/* SFCGAL library version at buil time */
#cmakedefine POSTGIS_SFCGAL_VERSION "@POSTGIS_SFCGAL_VERSION@"

/* PostGIS major version */
#cmakedefine POSTGIS_MAJOR_VERSION "@POSTGIS_MAJOR_VERSION@"

/* PostGIS micro version */
#cmakedefine POSTGIS_MICRO_VERSION "@POSTGIS_MICRO_VERSION@"

/* PostGIS minor version */
#cmakedefine POSTGIS_MINOR_VERSION "@POSTGIS_MINOR_VERSION@"

/* PostgreSQL server version */
#cmakedefine POSTGIS_PGSQL_VERSION @POSTGIS_PGSQL_VERSION@

/* Enable caching of bounding box within geometries */
#cmakedefine POSTGIS_AUTOCACHE_BBOX @POSTGIS_AUTOCACHE_BBOX@

/* PostGIS build date */
#cmakedefine POSTGIS_BUILD_DATE "@POSTGIS_BUILD_DATE@"

/* PostGIS library debug level (0=disabled) */
#define POSTGIS_DEBUG_LEVEL @POSTGIS_DEBUG_LEVEL@

/* GEOS library version */
#cmakedefine POSTGIS_GEOS_VERSION @POSTGIS_GEOS_VERSION@

/* PostGIS libxml2 version */
#cmakedefine POSTGIS_LIBXML2_VERSION "@POSTGIS_LIBXML2_VERSION@"

/* PostGIS library version */
#cmakedefine POSTGIS_LIB_VERSION "@POSTGIS_LIB_VERSION@"

/* Enable GEOS profiling (0=disabled) */
#define POSTGIS_PROFILE @POSTGIS_PROFILE@

/* PROJ library version */
#cmakedefine POSTGIS_PROJ_VERSION @POSTGIS_PROJ_VERSION@

/* PostGIS scripts version */
#cmakedefine POSTGIS_SCRIPTS_VERSION "@POSTGIS_SCRIPTS_VERSION@"

/* Enable use of ANALYZE statistics */
#cmakedefine POSTGIS_USE_STATS @POSTGIS_USE_STATS@

/* PostGIS version */
#cmakedefine POSTGIS_VERSION "@POSTGIS_VERSION@"

/* PostGIS Raster build date */
#cmakedefine POSTGIS_RASTER_BUILD_DATE "@POSTGIS_RASTER_BUILD_DATE@"

/* PostGIS Raster library version */
#cmakedefine POSTGIS_RASTER_LIB_VERSION "@POSTGIS_RASTER_LIB_VERSION@"

/* PostGIS Raster major version */
#cmakedefine POSTGIS_RASTER_MAJOR_VERSION "@POSTGIS_RASTER_MAJOR_VERSION@"

/* PostGIS Raster micro version */
#cmakedefine POSTGIS_RASTER_MICRO_VERSION "@POSTGIS_RASTER_MICRO_VERSION@"

/* PostGIS Raster minor version */
#cmakedefine POSTGIS_RASTER_MINOR_VERSION "@POSTGIS_RASTER_MINOR_VERSION@"

/* PostGIS Raster scripts version */
#cmakedefine POSTGIS_RASTER_SCRIPTS_VERSION "@POSTGIS_RASTER_SCRIPTS_VERSION@"

/* PostGIS Raster version */
#cmakedefine POSTGIS_RASTER_VERSION "@POSTGIS_RASTER_VERSION@"

/* Define to 1 if a warning is outputted every time a double is truncated */
#cmakedefine POSTGIS_RASTER_WARN_ON_TRUNCATION 1

/* cmakedefine to 1 if you have the ANSI C header files. */
#cmakedefine STDC_HEADERS 1

/* cmakedefine to 1 if `lex' declares `yytext' as a `char *' by default, not a
   `char[]'. */
#cmakedefine YYTEXT_POINTER 1

#endif /* POSTGIS_CONFIG_H */
