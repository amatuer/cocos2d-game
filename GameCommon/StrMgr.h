#pragma once
#include <map>
#include "Singleton.h"

class StrMgr : public Singleton<StrMgr> 
{
public:
	StrMgr();
	~StrMgr();

	void loadFile(const char* fileName);
	const char* getStr(const char* idRes) const;
	const char* getStr(const std::string& idRes) const;
private:
	std::map<std::string, std::string> strings_;
};

#define LOAD_STRING(x) StrMgr::instance().getStr(x)