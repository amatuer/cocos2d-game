#include "GuiMgr.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

boost::property_tree::ptree s_guiConfig;

GuiMgr::GuiMgr()
{
	boost::property_tree::read_json("config/gui.json", s_guiConfig);
}

GuiMgr::~GuiMgr()
{

}

std::string GuiMgr::getStr(const char* ctrlId, const char* propertyName, const char* defaultValue) const
{
	return s_guiConfig.get_child(ctrlId).get<std::string>(propertyName, defaultValue);
}

int GuiMgr::getData(const char* ctrlId, const char* propertyName, int defaultValue) const
{
	std::string temp = getStr(ctrlId, propertyName, "");
	if (temp.empty()) {
		return defaultValue;
	} else {
		return boost::lexical_cast<int>(temp);
	}
}