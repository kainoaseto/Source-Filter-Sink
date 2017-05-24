#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include <stdio.h>
#include <stdlib.h>

#include <Windows.h>
#include <WinBase.h>

#define ART_DELAY() { volatile int x; for( x = 0; x < 1000000; ++x); }

#endif // __INCLUDE_H__