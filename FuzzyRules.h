#pragma once
#include <utility>
#include <vector>
#include "Feature.h"
#include <map>

class FuzzyRules
{
protected:
	std::vector<std::string> m_outputs;
	std::vector<const Feature*> m_features;
	std::vector<std::vector<std::string>> m_rules;

	virtual std::map<std::string, double> mergeOutputValues(std::vector<double> values) const;

public:
	FuzzyRules() = default;
	FuzzyRules(std::vector<std::string> outputs,
		std::vector<const Feature*> features,
		std::vector<std::vector<std::string>> rules) :
	m_outputs(std::move(outputs)), m_features(std::move(features)), m_rules(std::move(rules)) {}

	std::map<std::string, double> FuzzyRules::computeRulesForData(const std::vector<double> &data) const;

	void printRules();
};
