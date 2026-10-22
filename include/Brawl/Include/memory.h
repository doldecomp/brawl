#pragma once

#include <StaticAssert.h>
#include <stddef.h>
#include <types.h>
#include <sr/sr_common.h>
#include <MEM.h>

#define MEMINIT( p) __memfill( p, 0, sizeof( *p ) )

void* free(void* ptr);



