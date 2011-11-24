#include "SlotMachineData.h"
#include <boost/format.hpp>
#include <algorithm>
#include "../GameCommon/BaseFunc.h"

SlotMachineData::SlotMachineData()
{
	m_curIndex = 0;
	m_autoStopTime = 0;
}

SlotMachineData::~SlotMachineData()
{

}

void SlotMachineData::createDataListByNumber(int start, int end, const char* strStart, const char* strEnd)
{
	if (start > end) {
		std::swap(start, end);
	}

	for (int i = start; i <= end; ++i) {
		std::string text = str(boost::format("%s%d%s") % strStart % i % strEnd);
		m_allNameData.push_back(text);
	}

	srand(getTime());
	std::random_shuffle(m_allNameData.begin(), m_allNameData.end());
}

void SlotMachineData::createDataListByText(const char* text)
{

}

std::string SlotMachineData::getRandomName(const std::string& str1, const std::string& str2) const
{
	int amount = m_allNameData.size();

	int index = rand() % amount;
	std::string text = m_allNameData[index];

	if (amount < 5) {
		if (text == str1) {
			return getRandomName(str1, str2);
		} else {
			return text;
		}
	} else {
		if (text == str1 || text == str2) {
			return getRandomName(str1, str2);
		} else {
			return text;
		}
	}
}

bool SlotMachineData::testHasSelected(const std::string& text) const
{
	const std::vector<std::string>::const_iterator itr = std::find(m_selectedName.begin(), m_selectedName.end(), text);
	return itr != m_selectedName.end();
}

void SlotMachineData::addSelectedName(const std::string& text)
{
	if (testHasSelected(text)) {
		return;
	}

	m_selectedName.push_back(text);
}

void SlotMachineData::setAutoStop(uint32 time)
{
	m_autoStopTime = time;
}

std::string SlotMachineData::getNextName()
{
	if (m_curIndex >= m_allNameData.size()) {
		m_curIndex = 0;
	}

	std::string text = m_allNameData[m_curIndex];
	++m_curIndex;
	return text;
}

int SlotMachineData::getStartIndex()
{
	int index = rand() % (m_allNameData.size() - 1);
	m_curIndex = index;
	return index;
}
