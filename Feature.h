#pragma once
#include <string>
#include <vector>
#include <map>
#include "FuzzySet.h"

class Feature
{
protected:
	std::string m_name;
	std::map<std::string, unsigned int> fuzzySetsNamesToIndexes;
	std::vector<FuzzySet*> m_fuzzySets;

public:
	std::string getName() const;
	double getValue(std::string name, double t) const;
	bool containsName(std::string name) const;
};

