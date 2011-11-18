#include "StrMgr.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

StrMgr::StrMgr()
{
	loadFile("config/string.json");
}

StrMgr::~StrMgr()
{

}

void StrMgr::loadFile(const char* fileName)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json(fileName, pt);

	BOOST_FOREACH(const boost::property_tree::ptree::value_type &v, pt)
	{
		strings_[v.first] = v.second.data();
	}
}

const char* StrMgr::getStr(const char* idRes) const
{
	if (!idRes) {
#ifdef DEBUG
		return "Unknown";
#else
		return "";
#endif
	}
	std::map<std::string, std::string>::const_iterator itr = strings_.find(idRes);
	if (itr == strings_.end()) {
#ifdef DEBUG
		return "Unknown";
#else
		return "";
#endif
	}

	return itr->second.c_str();
}
