#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include "Feature.h"
#include "FuzzyRules.h"

class Parser
{
private:
	const std::string outputColumnName = "out";
	const std::string ruleNumberColumnName = "rule_number";
	unsigned int outputColumnIndex;
	unsigned int ruleNumberColumnIndex;

	std::vector<std::string> parseWordsFromLine(const std::string &line) const;
	void extractSpecialColumnsIndexes(const std::string &columnNames);
	std::vector<const Feature*> getOrderedFeatures(std::string columnNames, 
												   const std::vector<const Feature*> features) const;
	FuzzyRules parseRulesToFuzzyRules(std::ifstream &stream,
									  const std::vector<const Feature*>& orderedFeatures) const;

public:
	Parser() = default;
	FuzzyRules parse(std::string filename, const std::vector<const Feature*> &features);
};
