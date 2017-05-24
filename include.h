// Kainoa Seto
// Source-Filter-Sink 
// Contains universal includes and Artificial delay function used in all projects
// include.h

#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include <stdio.h>
#include <stdlib.h>

#include <Windows.h>
#include <WinBase.h>

#define ART_DELAY() { volatile int x; for( x = 0; x < 3000000; ++x); }

#endif // __INCLUDE_H__