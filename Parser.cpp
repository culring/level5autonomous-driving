#include "Parser.h"
#include "FileInputException.h"
#include <iostream>

std::vector<std::string> Parser::parseWordsFromLine(const std::string& line) const
{
	std::istringstream istringstream(line);
	std::vector<std::string> output;
	while (istringstream)
	{
		std::string word;
		istringstream >> word;
		if(!word.empty())
		{
			output.push_back(word);
		}
	}

	return output;
}

void Parser::extractSpecialColumnsIndexes(const std::string& columnNames)
{
	auto words = parseWordsFromLine(columnNames);
	unsigned int index = -1;
	bool isFoundRuleNumberColumn = false;
	bool isFoundOutputColumn = false;
	m_outputColumnIndex = m_ruleNumberColumnIndex = -1;
	for (auto const& word : words)
	{
		++index;
		if (word == m_ruleNumberColumnName)
		{
			isFoundRuleNumberColumn = true;
			m_ruleNumberColumnIndex = index;
			continue;
		}
		if (word == m_outputColumnName)
		{
			isFoundOutputColumn = true;
			m_outputColumnIndex = index;
			continue;
		}
	}
	if (!isFoundRuleNumberColumn || !isFoundOutputColumn)
	{
		throw FileInputException();
	}
}

std::vector<unsigned> Parser::getOrderOfFeatures(const std::string& columnNames,
                                                 const std::vector<const Feature*> features)
{
	extractSpecialColumnsIndexes(columnNames);
	auto words = parseWordsFromLine(columnNames);
	std::vector<unsigned int> order(words.size());
	for (int i = 0; i < words.size(); ++i)
	{
		if (i == m_outputColumnIndex || i == m_ruleNumberColumnIndex)
		{
			continue;
		}
		bool isFound = false;
		for (int j = 0; j < features.size(); ++j)
		{
			if (words[i] == features[j]->getName())
			{
				isFound = true;
				order[i] = j;
				break;
			}
		}
		if (!isFound)
		{
			throw FileInputException();
		}
	}

	for(const auto& o : order)
	{
		std::cout << o << " ";
	}
	std::cout << std::endl;

	return order;
}

FuzzyRuleSet Parser::parseRulesToFuzzyRules(std::ifstream &stream,
										  const std::vector<unsigned int>& order,
										  const std::vector<const Feature*>& features) const
{
	std::vector<std::vector<std::string>> rules;
	std::vector<std::string> outputs;
	{
		std::string line;
		int rule = 0;
		// iterate through all rules from stream
		while (std::getline(stream, line))
		{
			rules.emplace_back(features.size());
			auto words = parseWordsFromLine(line);
			for (unsigned int i = 0; i < words.size(); ++i)
			{
				if (i == m_outputColumnIndex)
				{
					outputs.push_back(words[i]);
					continue;
				}
				if(i == m_ruleNumberColumnIndex)
				{
					continue;
				}
				if(words[i] != "x")
				{
					if (words[i][0] == '~')
					{
						const std::string substring = words[i].substr(1, words[i].size());
						if (!features[order[i]]->containsName(substring))
						{
							throw FileInputException();
						}
					}
					else
					{
						if (!features[order[i]]->containsName(words[i]))
						{
							throw FileInputException();
						}
					}
				}
				rules[rule][order[i]] = words[i];
			}
			++rule;
		}
	}
	return FuzzyRuleSet(outputs, features, rules);
}

FuzzyRuleSet Parser::parse(std::string filename, const std::vector<const Feature*>& features)
{
	std::ifstream file;
	file.open(filename);
	std::string line;
	// read column names
	std::getline(file, line);
	// set special columns indexes
	// and get features in column order
	auto order = getOrderOfFeatures(line, features);
	auto fuzzyRules = parseRulesToFuzzyRules(file, order, features);
	file.close();
	return fuzzyRules;
}
