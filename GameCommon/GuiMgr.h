#pragma once
#include <map>
#include "Singleton.h"

class GuiMgr : public Singleton<GuiMgr> 
{
public:
	GuiMgr();
	~GuiMgr();

	std::string getStr(const char* ctrlId, const char* propertyName, const char* defaultValue = "") const;
	int getData(const char* ctrlId, const char* propertyName, int defaultValue = 0) const;
};
