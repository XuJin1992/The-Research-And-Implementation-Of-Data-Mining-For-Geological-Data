/**
 * Created by xujin on 2014/12/1.
   All Rights Reserved£¬but you can use this program.
 */

#ifndef GRIDSET_H
#define GRIDSET_H

#include"Rectangle.h"
#include"Grid.h"

#include<string>
#include<vector>
#include<list>
#include<fstream>
using namespace std;


class CGridSet
{
private:
	vector<CGrid> m_veCGrid;

private:
	int compareRect(SRectangle *tpRecA,SRectangle *tpRecB);
	bool isContain(SRectangle *tpRecBig,SRectangle *tpRecSmall);

public:
	void sortGridSet();
	CGridSet();
	int getSize();
	void addGrid(CGrid tGrid);
	int getSupportCount(vector<string>& tVecCandidateSet);
	bool isContain(vector<string>& tVecPreCandidateSet);
	void print(ofstream &ofFile);
	bool combineFrequentSet(size_t id1,size_t id2,vector<string>& tVecPreCandidateSet);
	vector<CGrid>& getVeCGrid();
	bool isExist(vector<string> &tVecCandidateSet);
	vector<CGrid> getCGridByRectList(list<SRectangle *>tpRectList);
	vector<CGrid>getCGridByRect(SRectangle * tpRect);
	CGrid *binarySearch(SRectangle *key);
};


#endif