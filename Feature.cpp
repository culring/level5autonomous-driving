#include "Feature.h"

std::string Feature::getName() const
{
	return m_name;
}

double Feature::getValue(std::string name, double t) const
{
	return m_fuzzySets[fuzzySetsNamesToIndexes.at(name)]->getValue(t);
}

bool Feature::containsName(std::string name) const
{
	return fuzzySetsNamesToIndexes.find(name) != fuzzySetsNamesToIndexes.end();
}

FeatureDistance::FeatureDistance(float distanceBoundary, float distanceTolerance) :
	m_distanceTolerance(distanceTolerance), m_distanceBoundary(distanceBoundary)
{
	// low fuzzy set
	m_fuzzySets.push_back(new TrapezoidFuzzySet(
		0.0f, 0.0f,
		distanceBoundary - distanceTolerance, distanceBoundary + distanceTolerance
	));
	// high fuzzy set
	m_fuzzySets.push_back(new TrapezoidFuzzySet(
		distanceBoundary - distanceTolerance, distanceBoundary + distanceTolerance,
		std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()
	));
}

FeatureDistance::~FeatureDistance()
{
	for (auto fuzzySet : m_fuzzySets)
	{
		delete fuzzySet;
	}
	m_fuzzySets.clear();
}

float FeatureDistance::low(float t)
{
	return m_fuzzySets[0]->getValue(t);
}

float FeatureDistance::high(float t)
{
	return m_fuzzySets[1]->getValue(t);
}

FeatureDirection::FeatureDirection(float directionTolerance) :
	m_directionTolerance(directionTolerance)
{
	// in
	TrapezoidFuzzySet* inTrapezoidFuzzySet = new TrapezoidFuzzySet(
		-m_directionTolerance, m_directionTolerance,
		90.0f - m_directionTolerance, 90.0f + directionTolerance
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
		180.0f - m_directionTolerance, 180.0f + m_directionTolerance, 180.0f + m_directionTolerance
	);
	TrapezoidFuzzySet* outTrapezoidFuzzySet = new TrapezoidFuzzySet(
		-180.0f - m_directionTolerance, -180.0f + m_directionTolerance,
		-m_directionTolerance, m_directionTolerance
	);
	outFuzzySet->addFuzzySet(outTriangleFuzzySet);
	outFuzzySet->addFuzzySet(outTrapezoidFuzzySet);

	m_fuzzySets[0] = inTrapezoidFuzzySet;
	m_fuzzySets[1] = inBackwardsFuzzySet;
	m_fuzzySets[2] = outFuzzySet;
}

FeatureDirection::~FeatureDirection()
{
	for (auto fuzzySet : m_fuzzySets)
	{
		delete fuzzySet;
	}
}

float FeatureDirection::in(float t) const
{
	return m_fuzzySets[0]->getValue(t);
}

float FeatureDirection::inBackwards(float t) const
{
	return m_fuzzySets[1]->getValue(t);
}

float FeatureDirection::out(float t) const
{
	return m_fuzzySets[2]->getValue(t);
}

FeatureSide::FeatureSide(float sideTolerance) :
	m_sideTolerance(sideTolerance)
{
	// left
	CompundFuzzySet* leftFuzzySet = new CompundFuzzySet();
	TriangleFuzzySet* leftTriangleFuzzySet = new TriangleFuzzySet(-180.0f, -180.0f, -180.0f + 2 * m_sideTolerance);
	TrapezoidFuzzySet* leftTrapezoidFuzzySet = new TrapezoidFuzzySet(
		-m_sideTolerance, m_sideTolerance,
		180.0f - 2 * m_sideTolerance, 180.0f
	);
	leftFuzzySet->addFuzzySet(leftTriangleFuzzySet);
	leftFuzzySet->addFuzzySet(leftTrapezoidFuzzySet);

	// right
	CompundFuzzySet* rightFuzzySet = new CompundFuzzySet();
	TriangleFuzzySet* rightTriangleFuzzySet = new TriangleFuzzySet(
		180.0f - 2 * m_sideTolerance, 180.0f, 180.0f
	);
	TrapezoidFuzzySet* rightTrapezoidFuzzySet = new TrapezoidFuzzySet(
		-180.0f, -180.0f + 2 * m_sideTolerance,
		m_sideTolerance, m_sideTolerance
	);
	rightFuzzySet->addFuzzySet(rightTriangleFuzzySet);
	rightFuzzySet->addFuzzySet(rightTrapezoidFuzzySet);

	m_fuzzySets[0] = leftFuzzySet;
	m_fuzzySets[1] = rightFuzzySet;
}

float FeatureSide::left(float t)
{
	return m_fuzzySets[0]->getValue(t);
}

float FeatureSide::right(float t)
{
	return m_fuzzySets[1]->getValue(t);
}

FeatureAngle::FeatureAngle(float boundaryAngle, float angleTolerance) :
	m_boundaryAngle(boundaryAngle), m_angleTolerance(angleTolerance)
{
	// zero
	TriangleFuzzySet* triangleFuzzySet = new TriangleFuzzySet(-angleTolerance, 0.0f, angleTolerance);
	m_fuzzySets[0] = triangleFuzzySet;

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
	m_fuzzySets[1] = lowCompoundFuzzySet;

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
	m_fuzzySets[2] = highCompoundFuzzySet;
}

float FeatureAngle::zero(float t)
{
	return m_fuzzySets[0]->getValue(t);
}

float FeatureAngle::low(float t)
{
	return m_fuzzySets[1]->getValue(t);
}

float FeatureAngle::high(float t)
{
	return m_fuzzySets[2]->getValue(t);
}