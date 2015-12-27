/**
 * Created by xujin on 2014/12/1.
   All Rights Reserved��but you can use this program.
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
	double m_dMinConfidence;//��С���Ŷ�
	double m_dMinSupport;//��С֧�ֶ�

	int m_nSize;//���񼯴�С
    int m_nMinConfidence;//������С֧�ֶȵ�������
	int m_nMinSupport;//������С���Ŷȵ�������
	int m_nK;//K�

	CGridSet *m_pCGridSet;//Ƶ���
	CGridSet *m_pCDateCandidateSet;//��ѡ��

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