/**
 * Created by xujin on 2014/12/1.
   All Rights Reserved，but you can use this program.
 */

#ifndef APRIORI_H
#define APRIORI_H

#include"Rectangle.h"
#include"Grid.h"
#include"GridSet.h"

#include<fstream>
using namespace std;

class CApriori
{
private:
	double m_dMinConfidence;//最小置信度
	double m_dMinSupport;//最小支持度

	int m_nSize;//事务集大小
    int m_nMinConfidence;//满足最小支持度的事务数
	int m_nMinSupport;//满足最小置信度的事务数
	int m_nK;//K项集

	CGridSet *m_pCGridSet;//频繁项集
	CGridSet *m_pCDateCandidateSet;//候选集

private:
	void eraseCandidateSet();
	bool hasInfrequentSubSet(vector<string> &tVecCandidateSet);
	void aprioriGen();
    void findFrequent1ItemSet();
	bool isFrequentSet(vector<string> &tVecCandidateSet);
	bool isExist(vector<string> &tVecCandidateSet);

public:
	CApriori(double tMinCon,double tMinSup,int tK,CGridSet *tPDaSet);
	void findFrequentKItemSet();
	void print(ofstream &ofFile);
};


#endif