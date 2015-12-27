#ifndef CO_LOCATIONRESULT_H
#define CO_LOCATIONRESULT_H

#include"Rectangle.h"

#include<vector>
#include<string>
#include<iostream>
using namespace std;

struct SCo_LocationResult
{
	vector<string> m_vecItem;
	vector<vector<SRectangle*>> m_vecRectList;
	vector<double>m_vecParticipateProbability;
	double m_dParticipateIndex;
	SCo_LocationResult()
	{
		this->m_vecItem.clear();
	    this->m_vecParticipateProbability.clear();
	    this->m_vecRectList.clear();
	    this->m_dParticipateIndex=0;
	}
	void addRectList(vector<SRectangle*> tpVecRect)
	{
		m_vecRectList.push_back(tpVecRect);
	}
};

class CCo_LocationResultSet
{
private:
	vector<SCo_LocationResult*>m_vecResultSet;

public:
	CCo_LocationResultSet();
	vector<SCo_LocationResult*>getResultSet();
	void addResult(SCo_LocationResult *tVecResultSet);
	int getSize();
	
};


#endif