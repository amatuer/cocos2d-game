#pragma once

#include "Config.h"					// 配置一些功能的开关

#if defined(_DEBUG) && !defined(DEBUG)
#define DEBUG
#endif

#ifdef _MSC_VER
#pragma warning (disable:4786)
#pragma warning (disable:4018)
#pragma warning (disable:4996)
#pragma warning (disable:4244)			//  possible loss of data
#endif

// c
#include <cstdlib>
#include <cstring>
#include <cerrno>

// stl
#include <algorithm>
#include <map>
#include <vector>
#include <list>
#include <deque>
#include <utility>

// tr1
#include <memory>

#ifdef WIN32
	#include <windows.h>
#endif

#define pow2(value) ((value)*(value))

#ifndef __max
#define __max(a,b)  (((a) > (b)) ? (a) : (b))
#endif

#ifndef __min
#define __min(a,b)  (((a) < (b)) ? (a) : (b))
#endif

#define UNUSED(x) (x)

#define ARRAY_SIZE(x) ((sizeof(x)) / (sizeof(x[0])))

#define COMPILE_TIME_ASSERT(name, x) typedef int dummy_ ## name[(x) * 2 - 1]

#define SAFE_DELETE(x) {delete x; x = NULL;}
#ifdef WIN32
#define snprintf _snprintf
#define strlcpy strncpy
#else
#define stricmp strcasecmp
#endif

#ifndef _MAX_PATH
#define _MAX_PATH 260
#endif

#ifdef WIN32
#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif
#endif

typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef int int32;
typedef short int16;
typedef char int8;

#if (defined (_WIN32) && defined(_MSC_VER))
typedef unsigned __int64 uint64;
typedef __int64 int64;
#else
typedef unsigned long long uint64;
typedef long long int64;
#endif

// #include <vld.h>
// #pragma comment(lib, "vld.lib")
