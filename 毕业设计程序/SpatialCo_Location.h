
/**
 * Created by xujin on 2015/01/29.
   All Rights Reserved£¬but you can use this program.
 */

#ifndef SPATIALCO_LOCATION_H
#define SPATIALCO_LOCATION_H

#include"Rectangle.h"
#include"Grid.h"
#include"GridSet.h"
#include"Apriori.h"
#include"FP_Tree.h"
#include"FP_Growth.h"
#include"RTree.h"

#include<iostream>
#include<fstream>¡¿
#include<ctime>
using namespace std;

class CSpatialCo_Location
{
private:
	int m_nSize;
	int m_nAprioriK;
	double m_dMinConfidence;
	double m_dMinSupport;
	int m_nHeight;
	int m_nWidth;

	CGridSet *m_pPreCGridSet;
	CGridSet *m_pCGridSet;
	CRTree *m_pCRTree;
	CApriori *m_pCApriori;
	CFP_Tree *m_pFP_Tree;

private:
	void createTransactionByRTree();
	void createTransactionByEnumerate();

public:
	CSpatialCo_Location(double tMinCon,double tMinSup,int tK,CGridSet *tpDaSet,int tHeight,int tWidth,bool bIsUseIndex);
	void findFrequentKItemSetByApriori();
	void findFrequentItemSetByFP_Growth();
};

#endif