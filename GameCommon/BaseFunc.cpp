#include "BaseFunc.h"
#include <windows.h>

unsigned int getTime()
{
#ifdef WIN32
	return GetTickCount();
#else
#endif
}