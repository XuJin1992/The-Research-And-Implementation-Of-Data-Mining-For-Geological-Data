#ifndef CO_LOCATION_H
#define CO_LOCATION_H

#include<string>
#include"Rectangle.h"
#include"Grid.h"
#include"GridSet.h"
#include"Co_LocationResultSet.h"


class CCo_Location
{
private:
	int m_nExtendLength;//向周围扩展领域的长度
	CGridSet *m_pCGridSet;//数据集
	double m_dMin_prevalence;//全局参与索引阀值

	CCo_LocationResultSet* m_pCo_Location1ItemSet;
	CCo_LocationResultSet* m_pPreCandidateSet;//Apriori_gen算法生成侯选同位模式 k-1
	CCo_LocationResultSet* m_pCurCandidateSet;//Apriori_gen算法生成侯选同位模式 k

private:
	void findCo_Location1ItemSet();
	SCo_LocationResult* isExist(CCo_LocationResultSet* tpResultSet,vector<string> &tVecCandidateSet);
	bool hasInfrequentSubSet(vector<string> &tVecCandidateSet);
	void aprioriGen();
	void generateTableInstance();
	void filter();

public:
	CCo_Location(int tExtendLength,double tMin_prevalence,CGridSet *tPDaSet);
	void findCo_LocationSet();
	void print();
};


#endif