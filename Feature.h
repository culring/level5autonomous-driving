#pragma once
#include <string>
#include <vector>
#include <map>
#include "FuzzySet.h"

class Feature
{
protected:
	std::string m_name;
	std::map<std::string, unsigned int> m_fuzzySetsNamesToIndexes;
	std::vector<FuzzySet*> m_fuzzySets;

public:
	Feature(std::string name, std::map<std::string, 
		unsigned int> fuzzySetsNamesToIndexes);
	~Feature();

	void addFuzzySet(FuzzySet *fuzzySet);

	std::string getName() const;
	double getValue(std::string name, double t) const;
	bool containsName(std::string name) const;
};