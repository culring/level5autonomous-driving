#pragma once
#include <exception>
#include <vector>
#include <algorithm>
#include <ostream>
#include <iostream>
#include <list>

class WrongFuzzyParameters : public std::exception
{
};

class FuzzySet
{
public:
	virtual ~FuzzySet() = default;
	virtual float getValue(float t) = 0;
};

class TriangleFuzzySet : public FuzzySet
{
	float m_left, m_middle, m_right;

public:
	TriangleFuzzySet(float left, float middle, float right);
	~TriangleFuzzySet() = default;
	float getValue(float t) override;
};

class SingletonFuzzySet : public FuzzySet
{
	float m_x;

public:
	SingletonFuzzySet(float x);
	~SingletonFuzzySet() = default;
	float getValue(float t) override;
};

class TrapezoidFuzzySet : public FuzzySet
{
	float m_leftBottomBase, m_leftTopBase, m_rightTopBase, m_rightBottomBase;

public:
	TrapezoidFuzzySet(float leftBottomBase, float leftTopBase, float rightTopBase, float rightBottomBase);
	~TrapezoidFuzzySet() = default;
	float getValue(float t) override;
};

class CompundFuzzySet : public FuzzySet
{
	std::vector<FuzzySet*> m_fuzzySets;

public:
	~CompundFuzzySet();
	void addFuzzySet(FuzzySet *fuzzySet);
	float getValue(float t) override;
};

class FeatureDistance
{
	float m_distanceTolerance, m_distanceBoundary;
	FuzzySet *m_fuzzySets[2];

public:
	FeatureDistance(float distanceBoundary, float distanceTolerance) :
		m_distanceBoundary(distanceBoundary), m_distanceTolerance(distanceTolerance)
	{
		// low fuzzy set
		m_fuzzySets[0] = new TrapezoidFuzzySet(
			0.0f, 0.0f, 
			distanceBoundary - distanceTolerance, distanceBoundary + distanceTolerance
		);
		// high fuzzy set
		m_fuzzySets[1] = new TrapezoidFuzzySet(
			distanceBoundary - distanceTolerance, distanceBoundary + distanceTolerance,
			std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()
		);
	}
	~FeatureDistance()
	{
		for(auto fuzzySet : m_fuzzySets)
		{
			delete fuzzySet;
		}
	}

	float low(float t)
	{
		return m_fuzzySets[0]->getValue(t);
	}
	float high(float t)
	{
		return m_fuzzySets[1]->getValue(t);
	}
};

class FeatureDirection
{
	float m_directionTolerance;
	FuzzySet *m_fuzzySets[3];

public:
	FeatureDirection(float directionTolerance) :
		m_directionTolerance(directionTolerance)
	{
		// in
		TrapezoidFuzzySet *inTrapezoidFuzzySet = new TrapezoidFuzzySet(
			-m_directionTolerance, m_directionTolerance,
			90.0f - m_directionTolerance, 90.0f + directionTolerance
		);

		// in_backwards
		CompundFuzzySet *inBackwardsFuzzySet = new CompundFuzzySet();
		TrapezoidFuzzySet *inBackwardsTrapezoidFuzzySet = new TrapezoidFuzzySet(
			90.0f - directionTolerance, 90.0f + directionTolerance,
			180.0f - directionTolerance, 180.0f + directionTolerance
		);
		TriangleFuzzySet *inBackwardsTriangleFuzzySet = new TriangleFuzzySet(
			-180.0f - directionTolerance, -180.0f - directionTolerance, -180.0f + directionTolerance
		);
		inBackwardsFuzzySet->addFuzzySet(inBackwardsTrapezoidFuzzySet);
		inBackwardsFuzzySet->addFuzzySet(inBackwardsTriangleFuzzySet);

		//out
		CompundFuzzySet *outFuzzySet = new CompundFuzzySet();
		TriangleFuzzySet *outTriangleFuzzySet = new TriangleFuzzySet(
			180.0f - m_directionTolerance, 180.0f + m_directionTolerance, 180.0f + m_directionTolerance
		);
		TrapezoidFuzzySet *outTrapezoidFuzzySet = new TrapezoidFuzzySet(
			-180.0f - m_directionTolerance, -180.0f + m_directionTolerance,
			-m_directionTolerance, m_directionTolerance
		);
		outFuzzySet->addFuzzySet(outTriangleFuzzySet);
		outFuzzySet->addFuzzySet(outTrapezoidFuzzySet);

		m_fuzzySets[0] = inTrapezoidFuzzySet;
		m_fuzzySets[1] = inBackwardsFuzzySet;
		m_fuzzySets[2] = outFuzzySet;
	}
	~FeatureDirection()
	{
		for (auto fuzzySet : m_fuzzySets)
		{
			delete fuzzySet;
		}
	}

	float in(float t) const
	{
		return m_fuzzySets[0]->getValue(t);
	}
	float inBackwards(float t) const 
	{
		return m_fuzzySets[1]->getValue(t);
	}
	float out(float t) const 
	{
		return m_fuzzySets[2]->getValue(t);
	}
};

class FeatureSide
{
	float m_sideTolerance;
	FuzzySet *m_fuzzySets[2];

public:
	FeatureSide(float sideTolerance) :
		m_sideTolerance(sideTolerance)
	{
		// left
		CompundFuzzySet *leftFuzzySet = new CompundFuzzySet();
		TriangleFuzzySet *leftTriangleFuzzySet = new TriangleFuzzySet(-180.0f, -180.0f, -180.0f + 2 * m_sideTolerance);
		TrapezoidFuzzySet *leftTrapezoidFuzzySet = new TrapezoidFuzzySet(
			-m_sideTolerance, m_sideTolerance,
			180.0f - 2 * m_sideTolerance, 180.0f
		);
		leftFuzzySet->addFuzzySet(leftTriangleFuzzySet);
		leftFuzzySet->addFuzzySet(leftTrapezoidFuzzySet);

		// right
		CompundFuzzySet *rightFuzzySet = new CompundFuzzySet();
		TriangleFuzzySet *rightTriangleFuzzySet = new TriangleFuzzySet(
			180.0f - 2 * m_sideTolerance, 180.0f, 180.0f
		);
		TrapezoidFuzzySet *rightTrapezoidFuzzySet = new TrapezoidFuzzySet(
			-180.0f, -180.0f + 2 * m_sideTolerance,
			m_sideTolerance, m_sideTolerance
		);
		rightFuzzySet->addFuzzySet(rightTriangleFuzzySet);
		rightFuzzySet->addFuzzySet(rightTrapezoidFuzzySet);

		m_fuzzySets[0] = leftFuzzySet;
		m_fuzzySets[1] = rightFuzzySet;
	}

	float left(float t)
	{
		return m_fuzzySets[0]->getValue(t);
	}
	float right(float t)
	{
		return m_fuzzySets[1]->getValue(t);
	}
};

class FeatureAngle
{
	float m_boundaryAngle, m_angleTolerance;
	FuzzySet *m_fuzzySets[3];

public:
	FeatureAngle(float boundaryAngle, float angleTolerance) :
		m_boundaryAngle(boundaryAngle), m_angleTolerance(angleTolerance)
	{
		// zero
		TriangleFuzzySet *triangleFuzzySet = new TriangleFuzzySet(-angleTolerance, 0.0f, angleTolerance);
		m_fuzzySets[0] = triangleFuzzySet;

		// low
		CompundFuzzySet *lowCompoundFuzzySet = new CompundFuzzySet();
		TrapezoidFuzzySet *leftTrapezoidFuzzySet = new TrapezoidFuzzySet(
			-boundaryAngle-angleTolerance, -boundaryAngle+angleTolerance,
			-2*angleTolerance, 0.0f
		);
		TrapezoidFuzzySet *rightTrapezoidFuzzySet = new TrapezoidFuzzySet(
			0.0f, 2*angleTolerance,
			boundaryAngle-angleTolerance, boundaryAngle+angleTolerance
		);
		lowCompoundFuzzySet->addFuzzySet(leftTrapezoidFuzzySet);
		lowCompoundFuzzySet->addFuzzySet(rightTrapezoidFuzzySet);
		m_fuzzySets[1] = lowCompoundFuzzySet;

		// high
		CompundFuzzySet *highCompoundFuzzySet = new CompundFuzzySet();
		TrapezoidFuzzySet *highLeftTrapezoidFuzzySet = new TrapezoidFuzzySet(
			-180.0f, -180.0f,
			-boundaryAngle-angleTolerance, -boundaryAngle+angleTolerance
		);
		TrapezoidFuzzySet *highRightTrapezoidFuzzySet = new TrapezoidFuzzySet(
			boundaryAngle-angleTolerance, boundaryAngle+angleTolerance,
			180.0f, 180.0f
		);
		highCompoundFuzzySet->addFuzzySet(highLeftTrapezoidFuzzySet);
		highCompoundFuzzySet->addFuzzySet(highRightTrapezoidFuzzySet);
		m_fuzzySets[2] = highCompoundFuzzySet;
	}

	float zero(float t)
	{
		return m_fuzzySets[0]->getValue(t);
	}
	float low(float t)
	{
		return m_fuzzySets[1]->getValue(t);
	}
	float high(float t)
	{
		return m_fuzzySets[2]->getValue(t);
	}
};

enum COMMAND
{
	TURN_LEFT,
	TURN_RIGHT,
	DONT_TURN
};

template<typename T>
T computeRuleValue(const std::initializer_list<T> &list)
{
	std::initializer_list<T> list2(list.begin()+1, list.end());
	return std::max(*list.begin(), min(list2));
}

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
	)
	{
		m_featureDistance = new FeatureDistance(distanceBoundary, distanceTolerance);
		m_featureDirection = new FeatureDirection(directionTolerance);
		m_featureSide = new FeatureSide(sideTolerance);
		m_featureAngle = new FeatureAngle(boundaryAngle, angleTolerance);
	}
	~FuzzyController()
	{
		delete m_featureAngle;
		delete m_featureDirection;
		delete m_featureDistance;
		delete m_featureSide;
	}

	COMMAND getCommand(
		float distanceParameter,
		float directionParameter,
		float sideParameter,
		float angleParameter
	) const
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
};