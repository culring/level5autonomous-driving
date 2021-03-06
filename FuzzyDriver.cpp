#include "FuzzyDriver.h"
#include <iostream>
#include "Feature.h"
#include "Parser.h"

template <typename T>
T computeRuleValue(const std::initializer_list<T>& list)
{
	std::initializer_list<T> list2(list.begin() + 1, list.end());
	return std::max(*list.begin(), min(list2));
}

Feature* FuzzyDriver::createFeatureDistance(float distanceBoundary, float distanceTolerance)
{
	Feature *feature;
	feature = new Feature("distance", { { "low", 0 },{ "high", 1 } });
	// low fuzzy set
	feature->addFuzzySet(new TrapezoidFuzzySet(
		0.0f, 0.0f,
		distanceBoundary - distanceTolerance, distanceBoundary + distanceTolerance
	));
	// high fuzzy set
	feature->addFuzzySet(new TrapezoidFuzzySet(
		distanceBoundary - distanceTolerance, distanceBoundary + distanceTolerance,
		std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()
	));

	return feature;
}

Feature* FuzzyDriver::createFeatureDirection(float directionTolerance)
{
	Feature *feature;
	feature = new Feature("direction", { { "in", 0 },{ "back", 1 },{ "out", 2 } });

	// in
	TrapezoidFuzzySet* inTrapezoidFuzzySet = new TrapezoidFuzzySet(
		-directionTolerance, directionTolerance,
		90.0f - directionTolerance, 90.0f + directionTolerance
	);

	// in_backwards
	CompundFuzzySet* inBackwardsFuzzySet = new CompundFuzzySet();
	TrapezoidFuzzySet* inBackwardsTrapezoidFuzzySet = new TrapezoidFuzzySet(
		90.0f - directionTolerance, 90.0f + directionTolerance,
		180.0f - directionTolerance, 180.0f + directionTolerance
	);
	TriangleFuzzySet* inBackwardsTriangleFuzzySet = new TriangleFuzzySet(
		-180.0f - directionTolerance, -180.0f - directionTolerance, -180.0f + directionTolerance
	);
	inBackwardsFuzzySet->addFuzzySet(inBackwardsTrapezoidFuzzySet);
	inBackwardsFuzzySet->addFuzzySet(inBackwardsTriangleFuzzySet);

	//out
	CompundFuzzySet* outFuzzySet = new CompundFuzzySet();
	TriangleFuzzySet* outTriangleFuzzySet = new TriangleFuzzySet(
		180.0f - directionTolerance, 180.0f + directionTolerance, 180.0f + directionTolerance
	);
	TrapezoidFuzzySet* outTrapezoidFuzzySet = new TrapezoidFuzzySet(
		-180.0f - directionTolerance, -180.0f + directionTolerance,
		-directionTolerance, directionTolerance
	);
	outFuzzySet->addFuzzySet(outTriangleFuzzySet);
	outFuzzySet->addFuzzySet(outTrapezoidFuzzySet);

	feature->addFuzzySet(inTrapezoidFuzzySet);
	feature->addFuzzySet(inBackwardsFuzzySet);
	feature->addFuzzySet(outFuzzySet);

	return feature;
}

Feature* FuzzyDriver::createFeatureSide(float sideTolerance)
{
	Feature *feature;
	feature = new Feature("side", { {"left", 0}, {"right", 1} });

	// left
	CompundFuzzySet* leftFuzzySet = new CompundFuzzySet();
	TriangleFuzzySet* leftTriangleFuzzySet = new TriangleFuzzySet(-180.0f, -180.0f, -180.0f + 2 * sideTolerance);
	TrapezoidFuzzySet* leftTrapezoidFuzzySet = new TrapezoidFuzzySet(
		-sideTolerance, sideTolerance,
		180.0f - 2 * sideTolerance, 180.0f
	);
	leftFuzzySet->addFuzzySet(leftTriangleFuzzySet);
	leftFuzzySet->addFuzzySet(leftTrapezoidFuzzySet);

	// right
	CompundFuzzySet* rightFuzzySet = new CompundFuzzySet();
	TriangleFuzzySet* rightTriangleFuzzySet = new TriangleFuzzySet(
		180.0f - 2 * sideTolerance, 180.0f, 180.0f
	);
	TrapezoidFuzzySet* rightTrapezoidFuzzySet = new TrapezoidFuzzySet(
		-180.0f, -180.0f + 2 * sideTolerance,
		sideTolerance, sideTolerance
	);
	rightFuzzySet->addFuzzySet(rightTriangleFuzzySet);
	rightFuzzySet->addFuzzySet(rightTrapezoidFuzzySet);

	feature->addFuzzySet(leftFuzzySet);
	feature->addFuzzySet(rightFuzzySet);

	return feature;
}

Feature* FuzzyDriver::createFeatureAngle(float boundaryAngle, float angleTolerance)
{
	Feature *feature;
	feature = new Feature("angle", { { "zero", 0 }, { "low", 1 }, { "high", 2 } });

	// zero
	TriangleFuzzySet* triangleFuzzySet = new TriangleFuzzySet(-angleTolerance, 0.0f, angleTolerance);

	// low
	CompundFuzzySet* lowCompoundFuzzySet = new CompundFuzzySet();
	TrapezoidFuzzySet* leftTrapezoidFuzzySet = new TrapezoidFuzzySet(
		-boundaryAngle - angleTolerance, -boundaryAngle + angleTolerance,
		-2 * angleTolerance, 0.0f
	);
	TrapezoidFuzzySet* rightTrapezoidFuzzySet = new TrapezoidFuzzySet(
		0.0f, 2 * angleTolerance,
		boundaryAngle - angleTolerance, boundaryAngle + angleTolerance
	);
	lowCompoundFuzzySet->addFuzzySet(leftTrapezoidFuzzySet);
	lowCompoundFuzzySet->addFuzzySet(rightTrapezoidFuzzySet);

	// high
	CompundFuzzySet* highCompoundFuzzySet = new CompundFuzzySet();
	TrapezoidFuzzySet* highLeftTrapezoidFuzzySet = new TrapezoidFuzzySet(
		-180.0f, -180.0f,
		-boundaryAngle - angleTolerance, -boundaryAngle + angleTolerance
	);
	TrapezoidFuzzySet* highRightTrapezoidFuzzySet = new TrapezoidFuzzySet(
		boundaryAngle - angleTolerance, boundaryAngle + angleTolerance,
		180.0f, 180.0f
	);
	highCompoundFuzzySet->addFuzzySet(highLeftTrapezoidFuzzySet);
	highCompoundFuzzySet->addFuzzySet(highRightTrapezoidFuzzySet);

	feature->addFuzzySet(triangleFuzzySet);
	feature->addFuzzySet(lowCompoundFuzzySet);
	feature->addFuzzySet(highCompoundFuzzySet);

	return feature;
}

FuzzyDriver::FuzzyDriver(float distanceBoundary, float distanceTolerance, float directionTolerance,
                         float sideTolerance, float boundaryAngle, float angleTolerance)
{
	m_featureDistance = createFeatureDistance(distanceBoundary, distanceTolerance);
	m_featureDirection = createFeatureDirection(directionTolerance);
	m_featureSide = createFeatureSide(sideTolerance);
	m_featureAngle = createFeatureAngle(boundaryAngle, angleTolerance);

	m_fuzzyRuleSet = Parser().parse(
		"rule_tables\\base_rule_table.rls", { m_featureDistance, m_featureDirection, m_featureSide, m_featureAngle }
	);
}

FuzzyDriver::~FuzzyDriver()
{
	delete m_featureAngle;
	delete m_featureDirection;
	delete m_featureDistance;
	delete m_featureSide;
}

COMMAND FuzzyDriver::getCommand(float distanceParameter, float directionParameter, float sideParameter,
	float angleParameter) const
{
	auto output = m_fuzzyRuleSet.computeRulesForData({ distanceParameter, directionParameter, sideParameter, angleParameter });
	
	double leftProbability = (output.find("left") != output.end() ? output.at("left") : 0);
	double rightProbability = (output.find("right") != output.end() ? output.at("right") : 0);
	double noTurnProbability = (output.find("no_turn") != output.end() ? output.at("no_turn") : 0);

//	std::cout << "probabilities: " << leftProbability << " " << rightProbability << " " << noTurnProbability << std::endl;

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