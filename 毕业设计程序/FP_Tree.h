
/**
 * Created by xujin on 2014/12/4.
   All Rights Reserved，but you can use this program.
 */
#ifndef FP_TREE_H
#define FP_TREE_H

#include"Grid.h"
#include"GridSet.h"

#include<map>
using namespace std;

const int MAXN_CHILD=20;
typedef string ItemType;

struct ItemSupport
{
	ItemType m_ITItemName;
	int m_nSupportCount;
	ItemSupport(ItemType tItem,int tSup)
	{
		m_ITItemName=tItem;
	    m_nSupportCount=tSup;
	}
};

struct CFP_TreeNode
{
	int m_nSupportCount;
	int m_nChildSize;
	ItemType m_ITItemName;
	CFP_TreeNode *m_pFatherNode;
	CFP_TreeNode *m_pLinkedNode;
	CFP_TreeNode *m_pChildNode[MAXN_CHILD];

	CFP_TreeNode()
	{
		m_ITItemName.clear();
		m_nChildSize=0;
		m_nSupportCount =0;
		m_pFatherNode=NULL;
		m_pLinkedNode=NULL;
		for(int i=0;i<MAXN_CHILD;++i)
			m_pChildNode[i]=NULL;
	}

	
	CFP_TreeNode(int tCount)
	{
		m_ITItemName.clear();
		m_nChildSize=0;
		m_nSupportCount =tCount;
		m_pFatherNode=NULL;
		m_pLinkedNode=NULL;
		for(int i=0;i<MAXN_CHILD;++i)
			m_pChildNode[i]=NULL;
	}

	CFP_TreeNode(ItemType tITtem,CFP_TreeNode *tFa,CFP_TreeNode *tLinked,int tCount)
	{
		m_ITItemName=tITtem;
		m_nChildSize=0;
		m_nSupportCount=tCount;
		m_pFatherNode =tFa;
		m_pLinkedNode=tLinked;
		for(int i=0;i<MAXN_CHILD;++i)
			m_pChildNode[i]=NULL;
	}

};

struct CItemHeaderNode
{
	int m_nSupportCount;
	CFP_TreeNode *m_pFPFirst;
	CItemHeaderNode()
	{
		m_nSupportCount =0 ;
		m_pFPFirst = NULL;
	}
	CItemHeaderNode(int tCount)
	{
		m_nSupportCount =tCount ;
		m_pFPFirst = NULL;
	}
};




class CFP_Tree
{
private:
	double m_dMinConfidence;
	double m_dMinSupport;
	int m_nSize;
	int m_nMinConfidence;
	int m_nMinSupport;

	CFP_TreeNode *m_pCFP_TreeRoot;

private:
	

	void insertFPTree(CFP_TreeNode *tRoot,CGrid &tTran,int id,int tCount);
	void DFSPrintPath(CFP_TreeNode *tRoot,vector<ItemSupport> &tItemSupportSet);
	void printLinkList(CFP_TreeNode *tRoot);
	void destroy(CFP_TreeNode *tRoot);

public:
	vector<ItemSupport>m_vecItemSupportSet;
	map<ItemType,CItemHeaderNode>m_mapItemHeaderList;

	void sortMapItemHeaderList();
	void addItem(ItemType tItem,int tCount);
	void eraseInfrequent1ItemSet();

	/***********************************************
	*
	*功能:对tTranSet进行计数支持度从大到小排序
	*
	***********************************************/
	void sortGridSet(CGridSet &tTranSet);
	
	CFP_Tree(CGridSet &tTranSet,double tMinCon,double tMinSup,int tCount);
	CFP_Tree(double tMinCon,double tMinSup,int tSize);
	void insertFPTree(CGrid &tTran,int id,int tCount);
	void printPath();
	void printItemHeaderList();
	bool isSinglePath(CFP_TreeNode *tRoot);
	void destroy();
	friend class CFP_Growth;
};



#endif