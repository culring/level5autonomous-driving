#pragma once
#include "FuzzySet.h"
#include "Feature.h"

template<typename T>
T computeRuleValue(const std::initializer_list<T>& list);

class FuzzyController
{
private:
	FeatureDistance *m_featureDistance;
	FeatureAngle *m_featureAngle;
	FeatureDirection *m_featureDirection;
	FeatureSide *m_featureSide;

public:
	FuzzyController(
		//		float distanceBoundary = 52.0f, float distanceTolerance = 18.0f, 
		//		float directionTolerance = 2.0f,
		//		float sideTolerance = 5.0f,
		//		float boundaryAngle = 45.0f, float angleTolerance = 5.0f
		float distanceBoundary = 70.0f, float distanceTolerance = 0.01f,
		float directionTolerance = 5.0f,
		float sideTolerance = 0.01f,
		float boundaryAngle = 60.0f, float angleTolerance = 0.01f
	);

	~FuzzyController();

	COMMAND getCommand(
		float distanceParameter,
		float directionParameter,
		float sideParameter,
		float angleParameter
	) const;
};