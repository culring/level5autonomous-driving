#pragma once
#include <exception>
#include <vector>
#include <algorithm>
#include <ostream>
#include <iostream>

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
	FuzzySet *m_fuzzySets[2];

public:
	FeatureDirection(float directionTolerance) :
		m_directionTolerance(directionTolerance)
	{
		// in
		CompundFuzzySet *inFuzzySet = new CompundFuzzySet();
		TriangleFuzzySet *inTriangleFuzzySet = new TriangleFuzzySet(-180.0f, -180.0f, -180.0f + 2 * m_directionTolerance);
		TrapezoidFuzzySet *inTrapezoidFuzzySet = new TrapezoidFuzzySet(
			-m_directionTolerance, m_directionTolerance, 
			180.0f - 2*m_directionTolerance, 180.0f
		);
		inFuzzySet->addFuzzySet(inTriangleFuzzySet);
		inFuzzySet->addFuzzySet(inTrapezoidFuzzySet);

		//out
		CompundFuzzySet *outFuzzySet = new CompundFuzzySet();
		TriangleFuzzySet *outTriangleFuzzySet = new TriangleFuzzySet(
			180.0f - 2 * m_directionTolerance, 180.0f, 180.0f
		);
		TrapezoidFuzzySet *outTrapezoidFuzzySet = new TrapezoidFuzzySet(
			-180.0f, -180.0f + 2*m_directionTolerance,
			-m_directionTolerance, m_directionTolerance
		);
		outFuzzySet->addFuzzySet(outTriangleFuzzySet);
		outFuzzySet->addFuzzySet(outTrapezoidFuzzySet);

		m_fuzzySets[0] = inFuzzySet;
		m_fuzzySets[1] = outFuzzySet;
	}
	~FeatureDirection()
	{
		for (auto fuzzySet : m_fuzzySets)
		{
			delete fuzzySet;
		}
	}

	float in(float t)
	{
		return m_fuzzySets[0]->getValue(t);
	}
	float out(float t)
	{
		return m_fuzzySets[1]->getValue(t);
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

class FuzzyController
{
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
	)
	{
		float lowDistance = m_featureDistance->low(distanceParameter),
			highDistance = m_featureDistance->high(distanceParameter),
			in = m_featureDirection->in(directionParameter),
			out = m_featureDirection->out(directionParameter),
			left = m_featureSide->left(sideParameter),
			right = m_featureSide->right(sideParameter),
			zeroAngle = m_featureAngle->zero(angleParameter),
			lowAngle = m_featureAngle->low(angleParameter),
			highAngle = m_featureAngle->high(angleParameter);
			
		float leftProbability = 0.0f,
			rightProbability = 0.0f,
			noTurnProbability = 0.0f;

		// fuzzy rules
		/* 1*/ rightProbability = std::max(rightProbability, std::min(highDistance, std::min(in, std::min(lowAngle, left))));
		/* 2*/ leftProbability = std::max(leftProbability, std::min(highDistance, std::min(in, std::min(lowAngle, right))));
		/* 3*/ noTurnProbability = std::max(noTurnProbability, std::min(highDistance, std::min(in, highAngle)));
		/* 4*/ rightProbability = std::max(rightProbability, std::min(highDistance, std::min(out, left)));
		/* 5*/ leftProbability = std::max(leftProbability, std::min(highDistance, std::min(out, right)));
		/* 6*/ rightProbability = std::max(rightProbability, std::min(highDistance, std::min(zeroAngle, left)));
		/* 7*/ leftProbability = std::max(leftProbability, std::min(highDistance, std::min(zeroAngle, right)));
		/* 8*/ leftProbability = std::max(leftProbability, std::min(lowDistance, std::min(in, std::min(lowAngle, left))));
		/* 9*/ leftProbability = std::max(leftProbability, std::min(lowDistance, std::min(in, std::min(highAngle, left))));
		/*10*/ rightProbability = std::max(rightProbability, std::min(lowDistance, std::min(in, std::min(lowAngle, right))));
		/*11*/ rightProbability = std::max(rightProbability, std::min(lowDistance, std::min(in, std::min(highAngle, right))));
		/*12*/ rightProbability = std::max(rightProbability, std::min(lowDistance, std::min(out, std::min(lowAngle, left))));
		/*12*/ leftProbability = std::max(leftProbability, std::min(lowDistance, std::min(out, std::min(lowAngle, right))));
		/*13*/ rightProbability = std::max(rightProbability, std::min(lowDistance, std::min(out, std::min(highAngle, left))));
		/*14*/ leftProbability = std::max(leftProbability, std::min(lowDistance, std::min(out, std::min(highAngle, right))));
		/*15*/ noTurnProbability = std::max(noTurnProbability, std::min(lowDistance, zeroAngle));

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