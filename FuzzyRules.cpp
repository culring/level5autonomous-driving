#include "FuzzyRules.h"

std::map<std::string, double> FuzzyRules::mergeOutputValues(std::vector<double> values) const
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

std::map<std::string, double> FuzzyRules::computeRulesForData(std::vector<double> data) const
{
	std::vector<double> values;
	// for each rule
	for (auto i = 0; i < m_rules.size(); ++i)
	{
		// for each factor in a rule
		double minimum = std::numeric_limits<double>::infinity();
		for(int j = 0; j<m_rules[i].size(); ++j)
		{
			minimum = std::min(
				minimum,
				m_features[j]->getValue(m_rules[i][j], data[j])
			);
		}
		values.push_back(minimum);
	}
	return mergeOutputValues(values);
}
