#pragma once
#include "FuzzySet.h"
#include "Feature.h"
#include "FuzzyRuleSet.h"

template<typename T>
T computeRuleValue(const std::initializer_list<T>& list);

class FuzzyDriver
{
private:
	Feature *m_featureDistance;
	Feature *m_featureAngle;
	Feature *m_featureDirection;
	Feature *m_featureSide;
	FuzzyRuleSet m_fuzzyRuleSet;

	Feature* createFeatureDistance(float distanceBoundary = 70.0f, float distanceTolerance = 0.01f);
	Feature* createFeatureDirection(float directionTolerance = 5.0f);
	Feature* createFeatureSide(float sideTolerance = 0.01f);
	Feature* createFeatureAngle(float boundaryAngle = 60.0f, float angleTolerance = 0.01f);

public:
	FuzzyDriver(
//				float distanceBoundary = 52.0f, float distanceTolerance = 18.0f, 
//				float directionTolerance = 2.0f,
//				float sideTolerance = 5.0f,
//				float boundaryAngle = 45.0f, float angleTolerance = 5.0f
		float distanceBoundary = 70.0f, float distanceTolerance = 0.01f,
		float directionTolerance = 0.1f,
		float sideTolerance = 0.01f,
		float boundaryAngle = 60.0f, float angleTolerance = 0.01f
	);
	~FuzzyDriver();

	COMMAND getCommand(
		float distanceParameter,
		float directionParameter,
		float sideParameter,
		float angleParameter
	) const;
};