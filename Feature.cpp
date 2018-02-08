#include "Feature.h"

std::string Feature::getName() const
{
	return m_name;
}

double Feature::getValue(std::string name, double t) const
{
	return m_fuzzySets[fuzzySetsNamesToIndexes[name]]->getValue(t);
}

bool Feature::containsName(std::string name) const
{
	return fuzzySetsNamesToIndexes.find(name) != fuzzySetsNamesToIndexes.end();
}
