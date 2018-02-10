#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include "Feature.h"
#include "FuzzyRuleSet.h"

class Parser
{
private:
	const std::string m_outputColumnName = "out";
	const std::string m_ruleNumberColumnName = "rule_number";
	unsigned int m_outputColumnIndex;
	unsigned int m_ruleNumberColumnIndex;

	std::vector<std::string> parseWordsFromLine(const std::string &line) const;
	void extractSpecialColumnsIndexes(const std::string &columnNames);
	std::vector<unsigned> getOrderOfFeatures(const std::string& columnNames,
	                                         const std::vector<const Feature*> features);
	FuzzyRuleSet parseRulesToFuzzyRules(std::ifstream& stream,
	                                  const std::vector<unsigned>& order, const std::vector<const Feature*>& features) const;

public:
	Parser() = default;
	FuzzyRuleSet parse(std::string filename, const std::vector<const Feature*> &features);
};
