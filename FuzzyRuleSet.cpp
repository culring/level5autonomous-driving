#include "FuzzyRuleSet.h"
#include <iostream>

std::map<std::string, double> FuzzyRuleSet::mergeOutputValues(std::vector<double> values) const
{
	std::map<std::string, double> outputValues;
	for(int i = 0; i<values.size(); ++i)
	{
		if (outputValues.find(m_outputs[i]) == outputValues.end())
		{
			outputValues[m_outputs[i]] = 0;
		}
		outputValues[m_outputs[i]] = std::max(outputValues[m_outputs[i]], values[i]);
	}
	return outputValues;
}

std::map<std::string, double> FuzzyRuleSet::computeRulesForData(const std::vector<double> &data) const
{
	std::vector<double> values;
	// for each rule
	for (auto i = 0; i < m_rules.size(); ++i)
	{
		// for each factor in a rule
		double minimum = 1;
		for(int j = 0; j<m_rules[i].size(); ++j)
		{
			if(m_rules[i][j] == "x")
			{
				continue;
			}
			if(m_rules[i][j][0] == '~')
			{
				minimum = std::min(
					minimum,
					1 - m_features[j]->getValue(m_rules[i][j].substr(1, m_rules[i][j].size()), data[j])
				);
				continue;
			}
			minimum = std::min(
				minimum,
				m_features[j]->getValue(m_rules[i][j], data[j])
			);
		}
		values.push_back(minimum);
	}
	return mergeOutputValues(values);
}

void FuzzyRuleSet::printRules()
{
	for(int i = 0; i<m_rules.size(); ++i)
	{
		std::cout << "IF ";
		bool isFirst = true;
		for(int j = 0; j<m_features.size(); ++j)
		{
			if (m_rules[i][j] == "x")
			{
				continue;
			}
			std::cout << (isFirst ? "" : " AND ");
			std::cout << m_features[j]->getName() << "=" << m_rules[i][j];
			isFirst = false;
		}
		std::cout << " THEN " << m_outputs[i] << std::endl;
	}
}