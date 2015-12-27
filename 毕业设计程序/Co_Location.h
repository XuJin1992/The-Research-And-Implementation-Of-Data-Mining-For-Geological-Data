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
	int m_nExtendLength;//����Χ��չ����ĳ���
	CGridSet *m_pCGridSet;//���ݼ�
	double m_dMin_prevalence;//ȫ�ֲ���������ֵ

	CCo_LocationResultSet* m_pCo_Location1ItemSet;
	CCo_LocationResultSet* m_pPreCandidateSet;//Apriori_gen�㷨���ɺ�ѡͬλģʽ k-1
	CCo_LocationResultSet* m_pCurCandidateSet;//Apriori_gen�㷨���ɺ�ѡͬλģʽ k

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