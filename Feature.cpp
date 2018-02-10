#include "Feature.h"

Feature::Feature(std::string name, std::map<std::string, unsigned> fuzzySetsNamesToIndexes) :
	m_name(name), m_fuzzySetsNamesToIndexes(fuzzySetsNamesToIndexes)
{
}

Feature::~Feature()
{
	for(auto& fuzzySet : m_fuzzySets)
	{
		delete fuzzySet;
	}
	m_fuzzySets.clear();
}

void Feature::addFuzzySet(FuzzySet* fuzzySet)
{
	m_fuzzySets.push_back(fuzzySet);
}

std::string Feature::getName() const
{
	return m_name;
}

double Feature::getValue(std::string name, double t) const
{
	return m_fuzzySets[m_fuzzySetsNamesToIndexes.at(name)]->getValue(t);
}

bool Feature::containsName(std::string name) const
{
	return m_fuzzySetsNamesToIndexes.find(name) != m_fuzzySetsNamesToIndexes.end();
}