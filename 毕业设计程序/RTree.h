#ifndef RTREE_H
#define RTREE_H

#include"rectangle.h"

#include<iostream>
#include<map>
#include<list>
#include<fstream>
using namespace std;

const int MIN_CHILD=2;
const int MAX_CHILD=MIN_CHILD*2;


struct SRTreeNode
{
	int m_nSize;   
	bool m_bIsLeaf;
	SRectangle *m_pRect[MAX_CHILD];
	SRTreeNode *m_pRTreeChild[MAX_CHILD];
	SRTreeNode *m_pRTreeFather;///////////暂时还没用到
	SRTreeNode()
	{
		m_nSize=0;
		m_bIsLeaf=true;
		for(int i=0;i<MAX_CHILD;++i)
		{
		   m_pRect[i]= NULL;
		   m_pRTreeChild[i]=NULL;
		}
		m_pRTreeFather=NULL;
	}
};

class CRTree
{
public:
	static int g_nMaxChildNumber;
	static int g_nMinChildNumber;

private:
	map<int,int>m_mapDepthCount;
	SRTreeNode *m_pSRTreeNodeRoot;
	ofstream m_ofRTree;

	bool isOverlap(SRectangle *tpRecA,SRectangle *tpRecB);
	bool isContain(SRectangle *tpRecBig,SRectangle *tpRecSmall);
	bool isSame(SRectangle *tpRecA,SRectangle *tpRecB);

	SRectangle *mergeTwoRect(SRectangle *tpRecA,SRectangle *tpRecB);
	void search(SRTreeNode *tpRoot,SRectangle *tpRect);
	void searchAllLeaves(SRTreeNode *tpRoot,SRectangle *tpRect,list<SRectangle *>&leavesList);
	void searchAllLeaves(SRTreeNode *tpRoot,list<SRectangle *>&leavesList);

	SRTreeNode *insert(SRTreeNode *tpRoot,SRectangle *tpRect);
	void insertNotGull(SRTreeNode *tpRoot,SRectangle *tpRect);
	int getDiffArea(SRectangle *tpRecA,SRectangle *tpRecB);
	int getRectArea(SRectangle *tpRec);
	void splitNode(SRTreeNode *tpRoot,int tId);
	SRectangle *mergeAllRect(SRTreeNode *tpRoot);
	int mergeNode(SRTreeNode * &tpRoot,int tId);
	bool getCertainPath(SRTreeNode *tpRoot,SRectangle *tpRect,list<SRTreeNode *>&tVecPath);
	void erase(SRTreeNode *&tpRoot,SRectangle *tpRect,list<SRTreeNode *>::iterator tIterVecPath,list<SRTreeNode *>::iterator iterEnd);
	void display(SRTreeNode *tpRoot,int tDepth);
	void freeSRTreeNode(SRTreeNode *tpCRTNode);
	void freeSRectangle(SRectangle *tpRect);
	
public:
	CRTree();
	void search(SRectangle *tpRect);
	list<SRectangle *>searchAllLeaves(SRectangle *tpRect);
	void insert(SRectangle *tpRect);
	void erase(SRectangle *tpRect);
	void display();
};


#endif