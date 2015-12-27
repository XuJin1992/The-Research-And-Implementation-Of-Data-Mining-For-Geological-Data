/**
 * Created by xujin on 2014/12/4.
   All Rights Reserved，but you can use this program.
 */
#include"FP_Growth.h"
#include<algorithm>
using namespace std;

ofstream CFP_Growth::g_ofFP_GrowthResult;

void CFP_Growth::initCFP_Growth(CFP_Tree *tCFPTTree,vector<ItemSupport>& tItemSupportSet)
{
	for(vector<ItemSupport>::iterator iter=tCFPTTree->m_vecItemSupportSet.begin();iter!=tCFPTTree->m_vecItemSupportSet.end();++iter)
	{
		map<ItemType,CItemHeaderNode>::iterator iterMap=tCFPTTree->m_mapItemHeaderList.find(iter->m_ITItemName);

		//创建条件FP_growth树
		CFP_Tree * pCFPTConTree =new CFP_Tree(tCFPTTree->m_dMinConfidence,tCFPTTree->m_dMinSupport,tCFPTTree->m_nSize);
		for(CFP_TreeNode *next=iterMap->second.m_pFPFirst; next!=NULL; next=next->m_pLinkedNode)
		{
			CGrid tran;
			CFP_TreeNode *fa=next->m_pFatherNode;
			int count=next->m_nSupportCount;
			while(fa!=NULL&&!fa->m_ITItemName.empty())
			{
				tran.addItem(fa->m_ITItemName);
				pCFPTConTree->addItem(fa->m_ITItemName,count);
				fa=fa->m_pFatherNode;
			}
			CGrid reve;
			for(vector<string>::reverse_iterator iter=tran.getVecItem().rbegin();iter!=tran.getVecItem().rend();++iter)
			{
				reve.addItem(*iter);
			}
			pCFPTConTree->insertFPTree(reve,0,count);
		}
		pCFPTConTree->sortMapItemHeaderList();

		tItemSupportSet.push_back(ItemSupport(iterMap->first,iterMap->second.m_nSupportCount));
		new CFP_Growth(pCFPTConTree,tItemSupportSet);
		tItemSupportSet.pop_back();
	}
}

CFP_Growth::CFP_Growth(CFP_Tree *tCFPTTree,vector<ItemSupport> &tItemSupportSet)
{
	this->m_pCFPTConditionTree=tCFPTTree;

	if(0==tCFPTTree->m_pCFP_TreeRoot->m_nChildSize)
	{
		this->printOneFreSet(tItemSupportSet);
		return ;
	}
	else if(tCFPTTree->isSinglePath(tCFPTTree->m_pCFP_TreeRoot))
	{
		findCombine(tCFPTTree->m_pCFP_TreeRoot->m_pChildNode[0],tItemSupportSet);
		return ;
	}
	else
	{
		initCFP_Growth(tCFPTTree,tItemSupportSet);
	}
}

void CFP_Growth::findCombine(CFP_TreeNode *tRoot,vector<ItemSupport> &tItemSupportSet)
{
	if(tRoot==NULL)
	{
		printOneFreSet(tItemSupportSet);
		return ;
	}
	findCombine(tRoot->m_pChildNode[0],tItemSupportSet);

	tItemSupportSet.push_back(ItemSupport(tRoot->m_ITItemName,tRoot->m_nSupportCount));
	findCombine(tRoot->m_pChildNode[0],tItemSupportSet);
	tItemSupportSet.pop_back();

}

void CFP_Growth::printOneFreSet(vector<ItemSupport> &tItemSupportSet)
{
	if(1==tItemSupportSet.size())
		return ;

	int count=m_pCFPTConditionTree->m_nSize*10;

	for(vector<ItemSupport>::reverse_iterator iter=tItemSupportSet.rbegin();iter!=tItemSupportSet.rend();++iter)
	{
		if(count>iter->m_nSupportCount)
			count=iter->m_nSupportCount;
	}
	if(count<m_pCFPTConditionTree->m_nMinSupport)
	   return ;

	//g_ofFP_GrowthResult<<"{ ";
	for(vector<ItemSupport>::reverse_iterator iter=tItemSupportSet.rbegin();iter!=tItemSupportSet.rend();++iter)
	{
		g_ofFP_GrowthResult<<iter->m_ITItemName<<" ";
	}
	//g_ofFP_GrowthResult<<count<<" }"<<endl;
	g_ofFP_GrowthResult<<count<<endl;
}



void CFP_Growth::printPath()
{
	vector<ItemSupport>tItemSupportSet;
	cout<<"打印FP_Tree树:"<<endl;
	this->m_pCFPTConditionTree->DFSPrintPath(this->m_pCFPTConditionTree->m_pCFP_TreeRoot,tItemSupportSet);
}


void CFP_Growth::printItemHeaderList()
{
	cout<<"打印顶点表中每个单链表:"<<endl;
	for(map<ItemType,CItemHeaderNode>::iterator iter=this->m_pCFPTConditionTree->m_mapItemHeaderList.begin();iter!=this->m_pCFPTConditionTree->m_mapItemHeaderList.end();++iter)
	{
		if(iter->second.m_pFPFirst!=NULL)
		{
			cout<<"("<<iter->first<<","<<iter->second.m_nSupportCount<<") :";
			this->m_pCFPTConditionTree->printLinkList(iter->second.m_pFPFirst);
			cout<<endl;
		}
	}
}


