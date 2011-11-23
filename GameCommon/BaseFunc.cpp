#include "BaseFunc.h"

unsigned int getTime()
{
#ifdef WIN32
	return GetTickCount();
#else
#endif
}