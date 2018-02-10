#include "FuzzyController.h"
#include <iostream>
#include "Feature.h"

template <typename T>
T computeRuleValue(const std::initializer_list<T>& list)
{
	std::initializer_list<T> list2(list.begin() + 1, list.end());
	return std::max(*list.begin(), min(list2));
}

FuzzyController::FuzzyController(float distanceBoundary, float distanceTolerance, float directionTolerance,
	float sideTolerance, float boundaryAngle, float angleTolerance)
{
	m_featureDistance = new FeatureDistance(distanceBoundary, distanceTolerance);
	m_featureDirection = new FeatureDirection(directionTolerance);
	m_featureSide = new FeatureSide(sideTolerance);
	m_featureAngle = new FeatureAngle(boundaryAngle, angleTolerance);
}

FuzzyController::~FuzzyController()
{
	delete m_featureAngle;
	delete m_featureDirection;
	delete m_featureDistance;
	delete m_featureSide;
}

COMMAND FuzzyController::getCommand(float distanceParameter, float directionParameter, float sideParameter,
	float angleParameter) const
{
	double lowDistance = m_featureDistance->low(distanceParameter),
		highDistance = m_featureDistance->high(distanceParameter),
		in = m_featureDirection->in(directionParameter),
		inBackwards = m_featureDirection->inBackwards(directionParameter),
		out = m_featureDirection->out(directionParameter),
		left = m_featureSide->left(sideParameter),
		right = m_featureSide->right(sideParameter),
		zeroAngle = m_featureAngle->zero(angleParameter),
		lowAngle = m_featureAngle->low(angleParameter),
		highAngle = m_featureAngle->high(angleParameter);

	double leftProbability = 0.0f,
		rightProbability = 0.0f,
		noTurnProbability = 0.0f;

	// fuzzy rules
	leftProbability = computeRuleValue({ leftProbability, inBackwards, 1 - zeroAngle, left });
	rightProbability = computeRuleValue({ rightProbability, inBackwards, 1 - zeroAngle, right });

	rightProbability = computeRuleValue({ rightProbability, highDistance, in, lowAngle, left });
	leftProbability = computeRuleValue({ leftProbability, highDistance, in, lowAngle, right });
	noTurnProbability = computeRuleValue({ noTurnProbability, highDistance, in, highAngle });

	rightProbability = computeRuleValue({ rightProbability, highDistance, out, left });
	leftProbability = computeRuleValue({ leftProbability, highDistance, out, right });
	rightProbability = computeRuleValue({ rightProbability, highDistance, zeroAngle, left });

	leftProbability = computeRuleValue({ leftProbability, highDistance, zeroAngle, right });
	leftProbability = computeRuleValue({ leftProbability, lowDistance, in, lowAngle, left });
	leftProbability = computeRuleValue({ leftProbability, lowDistance, in, highAngle, left });

	rightProbability = computeRuleValue({ rightProbability, lowDistance, in, lowAngle, right });
	rightProbability = computeRuleValue({ rightProbability, lowDistance, in, highAngle, right });
	rightProbability = computeRuleValue({ rightProbability, lowDistance, out, lowAngle, left });

	leftProbability = computeRuleValue({ leftProbability, lowDistance, out, lowAngle, right });
	rightProbability = computeRuleValue({ rightProbability, lowDistance, out, highAngle, left });
	leftProbability = computeRuleValue({ leftProbability, lowDistance, out, highAngle, right });

	noTurnProbability = computeRuleValue({ noTurnProbability, lowDistance, zeroAngle });

	std::cout << "inputs: " << lowDistance << " " << highDistance << std::endl;
	std::cout << "probabilities: " << leftProbability << " " << rightProbability << " " << noTurnProbability << std::endl;
	if (leftProbability >= rightProbability && leftProbability >= noTurnProbability)
	{
		return TURN_LEFT;
	}
	if (rightProbability >= leftProbability && rightProbability >= noTurnProbability)
	{
		return TURN_RIGHT;
	}
	return DONT_TURN;
}