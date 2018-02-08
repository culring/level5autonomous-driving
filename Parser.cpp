#include "Parser.h"
#include "FileInputException.h"

std::vector<std::string> Parser::parseWordsFromLine(const std::string& line) const
{
	std::istringstream istringstream(line);
	std::vector<std::string> output;
	while(istringstream)
	{
		std::string word;
		istringstream >> word;
		output.push_back(word);
	}

	return output;
}

void Parser::extractSpecialColumnsIndexes(const std::string& columnNames)
{
	auto words = parseWordsFromLine(columnNames);
	unsigned int index = -1;
	bool isFoundRuleNumberColumn = false;
	bool isFoundOutputColumn = false;
	outputColumnIndex = ruleNumberColumnIndex = -1;
	for (auto const& word : words)
	{
		++index;
		if (word == ruleNumberColumnName)
		{
			isFoundRuleNumberColumn = true;
			ruleNumberColumnIndex = index;
			continue;
		}
		if (word == outputColumnName)
		{
			isFoundOutputColumn = true;
			outputColumnIndex = index;
			continue;
		}
	}
	if (!isFoundRuleNumberColumn || !isFoundOutputColumn)
	{
		throw FileInputException();
	}
}

std::vector<const Feature*> Parser::getOrderedFeatures(std::string columnNames,
	const std::vector<const Feature*> features) const
{
	std::vector<const Feature*> orderedFeatures;
	{
		auto words = parseWordsFromLine(columnNames);
		for (auto const& word : words)
		{
			if (word == ruleNumberColumnName || word == outputColumnName)
			{
				continue;
			}
			for (auto const& feature : features)
			{
				bool isFound = false;
				if (word == feature->getName())
				{
					orderedFeatures.push_back(feature);
					isFound = true;
				}
				if (!isFound)
				{
					throw FileInputException();
				}
			}
		}
	}
	return orderedFeatures;
}

FuzzyRules Parser::parseRulesToFuzzyRules(std::ifstream &stream,
										  const std::vector<const Feature*>& orderedFeatures) const
{
	std::vector<std::vector<std::string>> rules;
	std::vector<std::string> outputs;
	{
		std::string line;
		int rule = 0;
		while (std::getline(stream, line))
		{
			auto words = parseWordsFromLine(line);
			for (unsigned int i = 0, j = 0; i < words.size(); ++i)
			{
				if (i == outputColumnIndex)
				{
					outputs.push_back(words[i]);
					continue;
				}
				if(i == ruleNumberColumnIndex)
				{
					continue;
				}
				if(!orderedFeatures[j]->containsName(words[i]))
				{
					throw FileInputException();
				}
				rules[rule].push_back(words[i]);
				++j;
			}
			++rule;
		}
	}
	return FuzzyRules(outputs, orderedFeatures, rules);
}

FuzzyRules Parser::parse(std::string filename, const std::vector<const Feature*>& features)
{
	std::ifstream file(filename, std::ifstream::failbit | std::ifstream::badbit | std::ifstream::eofbit);
	std::string line;
	// read column names
	std::getline(file, line);
	// set special columns indexes
	// and get features in column order
	extractSpecialColumnsIndexes(line);
	auto orderedFeatures = getOrderedFeatures(line, features);
	auto fuzzyRules = parseRulesToFuzzyRules(file, orderedFeatures);
	file.close();

	return fuzzyRules;
}
