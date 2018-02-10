#pragma once
#include <exception>
#include <vector>
#include <ostream>
#include <algorithm>

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

enum COMMAND
{
	TURN_LEFT,
	TURN_RIGHT,
	DONT_TURN
};