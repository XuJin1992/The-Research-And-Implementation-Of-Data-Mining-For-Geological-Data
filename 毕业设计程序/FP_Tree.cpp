/**
 * Created by xujin on 2014/12/4.
   All Rights Reserved，but you can use this program.
 */
#include<algorithm>
#include"FP_Tree.h"

bool cmp(ItemSupport &a,ItemSupport &b)
{
	return a.m_nSupportCount<b.m_nSupportCount;
}

void CFP_Tree::sortMapItemHeaderList()
{
	vector<ItemSupport>tItemSupportSet;

	for(map<ItemType,CItemHeaderNode>::iterator iter=m_mapItemHeaderList.begin();iter!=m_mapItemHeaderList.end();++iter)
	{
		tItemSupportSet.push_back(ItemSupport(iter->first,iter->second.m_nSupportCount));
	}
	
	sort(tItemSupportSet.begin(),tItemSupportSet.end(),cmp);

	m_vecItemSupportSet.clear();
	for(vector<ItemSupport>::iterator iter=tItemSupportSet.begin();iter!=tItemSupportSet.end();++iter)
	{
		m_vecItemSupportSet.push_back(*iter);
	}
}

	
CFP_Tree::CFP_Tree(CGridSet &tTranSet,double tMinCon,double tMinSup,int tCount)
{
	this->m_mapItemHeaderList.clear();
	this->m_vecItemSupportSet.clear();
	this->m_dMinConfidence=tMinCon;
	this->m_dMinSupport =tMinSup;
	this->m_nSize=tTranSet.getSize();
    this->m_nMinConfidence = (this->m_dMinConfidence)*(this->m_nSize);
	this->m_nMinSupport=(this->m_dMinSupport)*(this->m_nSize);

	this->m_pCFP_TreeRoot=new CFP_TreeNode(tCount);
	
	for(vector<CGrid>::iterator iter=tTranSet.getVeCGrid().begin();iter!=tTranSet.getVeCGrid().end();++iter)
	{
		for(vector<string>::iterator strIter=iter->getVecItem().begin();strIter!=iter->getVecItem().end();++strIter)
		{
			this->addItem(*strIter,1);
		}
	}
	this->sortGridSet(tTranSet);

	//??????????????????*/
	//this->eraseInfrequent1ItemSet();
	this->sortMapItemHeaderList();
}

CFP_Tree::CFP_Tree(double tMinCon,double tMinSup,int tSize)
{
	this->m_mapItemHeaderList.clear();
	this->m_vecItemSupportSet.clear();
	this->m_dMinConfidence=tMinCon;
	this->m_dMinSupport =tMinSup;
	this->m_nSize=tSize;
    this->m_nMinConfidence = (this->m_dMinConfidence)*tSize;
	this->m_nMinSupport=(this->m_dMinSupport)*tSize;

	this->m_pCFP_TreeRoot=new CFP_TreeNode();
}

void CFP_Tree::addItem(ItemType tItem,int tCount)
{
	map<ItemType,CItemHeaderNode>::iterator iter=m_mapItemHeaderList.find(tItem);
	if(iter!=m_mapItemHeaderList.end())
	{
		iter->second.m_nSupportCount +=tCount;
	}
	else
	{
	    CItemHeaderNode p(tCount);
		pair<ItemType,CItemHeaderNode> node=make_pair(tItem,p);
		m_mapItemHeaderList.insert(node);	
	}
}


void CFP_Tree::eraseInfrequent1ItemSet()
{
	;
	for(map<ItemType,CItemHeaderNode>::iterator iter=m_mapItemHeaderList.begin();iter!=m_mapItemHeaderList.end();)
	{
		if(iter->second.m_nSupportCount<this->m_nMinSupport)
		{
			m_mapItemHeaderList.erase(iter++);
		}
		else 
		{
			++iter;
		}
	}
}

class CGridItemSort
{
public:
  static bool cmp(ItemType a,ItemType b);
  static CFP_Tree *g_pRoot;
//std::sort要求函数对象，或是静态/全局函数指针
//非静态成员函数指针不能直接传递给std::sort
 
};

CFP_Tree *CGridItemSort::g_pRoot=NULL;


bool CGridItemSort::cmp(ItemType a,ItemType b)
{
	int aCount,bCount;
	map<ItemType,CItemHeaderNode>::iterator iter=CGridItemSort::g_pRoot->m_mapItemHeaderList.find(a);
	if(iter!=CGridItemSort::g_pRoot->m_mapItemHeaderList.end())
	{
		aCount=iter->second.m_nSupportCount;
	}
	else
	{
		aCount=-1;
	}

	iter=CGridItemSort::g_pRoot->m_mapItemHeaderList.find(b);
	if(iter!=CGridItemSort::g_pRoot->m_mapItemHeaderList.end())
	{
		bCount=iter->second.m_nSupportCount;
	}
	else
	{
		bCount=-1;
	}
	return aCount>bCount;
}


void CFP_Tree::sortGridSet(CGridSet &tTranSet)
{
	CGridItemSort::g_pRoot=this;
	for(vector<CGrid>::iterator iter=tTranSet.getVeCGrid().begin();iter!=tTranSet.getVeCGrid().end();++iter)
	{
		sort(iter->getVecItem().begin(),iter->getVecItem().end(),CGridItemSort::cmp);
	}
}



void CFP_Tree::insertFPTree(CFP_TreeNode *tRoot,CGrid &tTran,int id,int tCount)
{
	if(id>=tTran.getVecItem().size()||this->m_mapItemHeaderList.find(tTran.getVecItem()[id])==this->m_mapItemHeaderList.end())
		return ;

	CFP_TreeNode *pChild;
	for(int i=0;i<tRoot->m_nChildSize;++i)
	{
		 pChild=tRoot->m_pChildNode[i];
		if(pChild!=NULL&&pChild->m_ITItemName==tTran.getVecItem()[id])
		{
			pChild->m_nSupportCount+=tCount;
			this->insertFPTree(pChild,tTran,id+1,tCount);
			return ;
		}
	}

	ItemType item=tTran.getVecItem()[id];
	pChild=new CFP_TreeNode(item,tRoot, this->m_mapItemHeaderList[item].m_pFPFirst,tCount);
	this->m_mapItemHeaderList[item].m_pFPFirst=pChild;
	tRoot->m_pChildNode[tRoot->m_nChildSize]=pChild;
	++tRoot->m_nChildSize;	
	insertFPTree(pChild,tTran,id+1,tCount);
}

void CFP_Tree::insertFPTree(CGrid &tTran,int id,int tCount)
{
	this->insertFPTree(this->m_pCFP_TreeRoot,tTran,id,tCount);
}


void CFP_Tree::DFSPrintPath(CFP_TreeNode *tRoot,vector<ItemSupport> &tItemSupportSet)
{
	if(tRoot->m_nChildSize==0)
	{
		for(vector<ItemSupport>::iterator iter=tItemSupportSet.begin(); iter!=tItemSupportSet.end();++iter)
			cout<<"--->("<<iter->m_ITItemName<<","<<iter->m_nSupportCount<<")";
		cout<<endl;
		return ;
	}

	for(int i=0;i<tRoot->m_nChildSize;++i)
	{
		CFP_TreeNode *pChild= tRoot->m_pChildNode[i];
		tItemSupportSet.push_back(ItemSupport(pChild->m_ITItemName,pChild->m_nSupportCount));
		DFSPrintPath(pChild,tItemSupportSet);
		tItemSupportSet.pop_back();
	}
}

void CFP_Tree::printPath()
{
	vector<ItemSupport>tItemSupportSet;
	cout<<"打印FP_Tree树:"<<endl;
	this->DFSPrintPath(m_pCFP_TreeRoot,tItemSupportSet);
}

void CFP_Tree::printLinkList(CFP_TreeNode *tRoot)
{
	cout<<"--->("<<tRoot->m_ITItemName<<","<<tRoot->m_nSupportCount<<")";
	if(tRoot->m_pLinkedNode!=NULL)
	  printLinkList(tRoot->m_pLinkedNode);
}

void CFP_Tree::printItemHeaderList()
{
	cout<<"打印顶点表中每个单链表:"<<endl;
	for(map<ItemType,CItemHeaderNode>::iterator iter=m_mapItemHeaderList.begin();iter!=m_mapItemHeaderList.end();++iter)
	{
		if(iter->second.m_pFPFirst!=NULL)
		{
			cout<<"("<<iter->first<<","<<iter->second.m_nSupportCount<<") :";
			printLinkList(iter->second.m_pFPFirst);
			cout<<endl;
		}
	}
}



void CFP_Tree::destroy(CFP_TreeNode *tRoot)
{
	CFP_TreeNode *pChild;
	for(int i=0;i<tRoot->m_nChildSize;++i)
	{
	    pChild=tRoot->m_pChildNode[i];
		if(pChild!=NULL)
		{
			destroy(pChild);
		}
	}
	tRoot->m_pFatherNode=NULL;
	tRoot->m_pLinkedNode=NULL;
	for(int i=0;i<tRoot->m_nChildSize;++i)
	{
		if(tRoot->m_pChildNode[i]!=NULL)
		{
		   delete tRoot->m_pChildNode[i];
	    	tRoot->m_pChildNode[i]=NULL;
		}
	}
}

void CFP_Tree::destroy()
{
	this->destroy(this->m_pCFP_TreeRoot);
}

bool CFP_Tree::isSinglePath(CFP_TreeNode *tRoot)
{
	if(0==tRoot->m_nChildSize)
		return true;
	else if(tRoot->m_nChildSize>1)
		return false;
	return isSinglePath(tRoot->m_pChildNode[0]);
}


