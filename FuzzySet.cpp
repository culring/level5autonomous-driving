#include "FuzzySet.h"

TriangleFuzzySet::TriangleFuzzySet(float left, float middle, float right)
{
	if(left >= right || middle < left || middle > right)
	{
		throw WrongFuzzyParameters();
	}
	m_left = left;
	m_middle = middle;
	m_right = right;
}

float TriangleFuzzySet::getValue(float t)
{
	if(t < m_left)
	{
		return 0;
	}
	if(t <= m_middle)
	{
		if (m_left == m_middle) return 1.0f;
		return (t - m_left) / (m_middle - m_left);
	}
	if(t <= m_right)
	{
		if (m_right == m_middle) return 1.0f;
		return (m_right - t) / (m_right - m_middle);
	}
	return 0;
}

SingletonFuzzySet::SingletonFuzzySet(float x) : m_x(x) {}

float SingletonFuzzySet::getValue(float t)
{
	if(t == m_x)
	{
		return 1.0f;
	}
	return 0.0f;
}

TrapezoidFuzzySet::TrapezoidFuzzySet(float leftBottomBase, float leftTopBase, float rightTopBase, float rightBottomBase)
{
	if(leftBottomBase > leftTopBase || leftTopBase >= rightTopBase || rightTopBase > rightBottomBase)
	{
		throw WrongFuzzyParameters();
	}
	m_leftBottomBase = leftBottomBase;
	m_leftTopBase = leftTopBase;
	m_rightTopBase = rightTopBase;
	m_rightBottomBase = rightBottomBase;
}

float TrapezoidFuzzySet::getValue(float t)
{
	if(t < m_leftBottomBase)
	{
		return 0.0f;
	}
	if(t <= m_leftTopBase)
	{
		if (m_leftBottomBase == m_leftTopBase) return 1.0f;
		return (t - m_leftBottomBase) / (m_leftTopBase - m_leftBottomBase);
	}
	if(t <= m_rightTopBase)
	{
		return 1.0f;
	}
	if(t <= m_rightBottomBase)
	{
		return (m_rightBottomBase - t) / (m_rightBottomBase - m_rightTopBase);
	}
	else
	{
		return 0.0f;
	}
}

CompundFuzzySet::~CompundFuzzySet()
{
	for(FuzzySet *fuzzySet : m_fuzzySets)
	{
		delete fuzzySet;
	}
	m_fuzzySets.clear();
}

void CompundFuzzySet::addFuzzySet(FuzzySet* fuzzySet)
{
	m_fuzzySets.push_back(fuzzySet);
}

float CompundFuzzySet::getValue(float t)
{
	float maximum = 0.0f;
	for(FuzzySet *fuzzySet : m_fuzzySets)
	{
		maximum = std::max(maximum, fuzzySet->getValue(t));
	}

	return maximum;
}
