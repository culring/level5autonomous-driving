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
	Feature() = default;

	std::string getName() const;
	double getValue(std::string name, double t) const;
	bool containsName(std::string name) const;
};

class FeatureDistance : public Feature
{
	float m_distanceTolerance, m_distanceBoundary;

public:
	FeatureDistance(float distanceBoundary, float distanceTolerance);
	~FeatureDistance();

	float low(float t);
	float high(float t);
};

class FeatureDirection
{
	float m_directionTolerance;
	FuzzySet *m_fuzzySets[3];

public:
	FeatureDirection(float directionTolerance);
	~FeatureDirection();

	float in(float t) const;
	float inBackwards(float t) const;
	float out(float t) const;
};

class FeatureSide
{
	float m_sideTolerance;
	FuzzySet *m_fuzzySets[2];

public:
	FeatureSide(float sideTolerance);

	float left(float t);
	float right(float t);
};

class FeatureAngle
{
	float m_boundaryAngle, m_angleTolerance;
	FuzzySet *m_fuzzySets[3];

public:
	FeatureAngle(float boundaryAngle, float angleTolerance);

	float zero(float t);
	float low(float t);
	float high(float t);
};
