#pragma once

#include "../GameCommon/Singleton.h"
#include <vector>
#include <string>

typedef unsigned int uint32;

class SlotMachineData : public Singleton<SlotMachineData>
{
public:
	SlotMachineData();
	~SlotMachineData();

	void createDataListByNumber(int start, int end, const char* strStart, const char* strEnd);
	void createDataListByText(const char* text);
	std::string getRandomName(const std::string& str1, const std::string& str2) const;
	std::string getNextName();
	int getStartIndex();
	bool testHasSelected(const std::string& text) const;
	void addSelectedName(const std::string& text);

	void setAutoStop(uint32 time);			// 是否自动停止，0则不自动停止，否则传多少毫秒后自动停止
private:
	std::vector<std::string> m_allNameData;
	std::vector<std::string> m_selectedName;
	std::string m_title;

	uint32 m_autoStopTime;
	uint32 m_curIndex;
};