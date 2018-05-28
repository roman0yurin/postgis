/**
 * Дополнительный набор геометрических функций для платформы С60
 * @author Юрин Роман 28.05.18
 */
#pragma once

#include <cmath>//Без этого подключается не та математика и происходит нестыковка на этапе компиляции

extern "C"{
	#include "postgres.h"
	#include "fmgr.h"
	#include "utils/elog.h"
	#include "utils/geo_decls.h"

	#include "../postgis_config.h"
	#include "libpgcommon/lwgeom_pg.h"
	#include "liblwgeom.h"

	#include <math.h>
	#include <float.h>
	#include <string.h>
	#include <stdio.h>
	#include <errno.h>
}