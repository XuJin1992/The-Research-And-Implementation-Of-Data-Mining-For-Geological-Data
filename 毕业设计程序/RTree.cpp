
#include"RTree.h"

#include<cmath>
#include<list>
#include<map>


int CRTree::g_nMaxChildNumber=MAX_CHILD;
int CRTree::g_nMinChildNumber=MIN_CHILD;     

CRTree::CRTree()
{
	m_pSRTreeNodeRoot = new SRTreeNode();
}

bool CRTree::isOverlap(SRectangle *tpRecA,SRectangle *tpRecB)
{
	int maxX=tpRecA->m_LeftBottomX>tpRecB->m_LeftBottomX?tpRecA->m_LeftBottomX:tpRecB->m_LeftBottomX;
	int maxY=tpRecA->m_LeftBottomY>tpRecB->m_LeftBottomY?tpRecA->m_LeftBottomY:tpRecB->m_LeftBottomY;

	int minX=tpRecA->m_RightTopX<tpRecB->m_RightTopX?tpRecA->m_RightTopX:tpRecB->m_RightTopX;
	int minY=tpRecA->m_RightTopY<tpRecB->m_RightTopY?tpRecA->m_RightTopY:tpRecB->m_RightTopY;

	if(maxY<minY&&maxX<minX)
		return true;
	return false;
}

SRectangle *CRTree::mergeTwoRect(SRectangle *tpRecA,SRectangle *tpRecB)
{
	int minX=tpRecA->m_LeftBottomX<tpRecB->m_LeftBottomX?tpRecA->m_LeftBottomX:tpRecB->m_LeftBottomX;
	int minY=tpRecA->m_LeftBottomY<tpRecB->m_LeftBottomY?tpRecA->m_LeftBottomY:tpRecB->m_LeftBottomY;

	int maxX=tpRecA->m_RightTopX>tpRecB->m_RightTopX?tpRecA->m_RightTopX:tpRecB->m_RightTopX;
	int maxY=tpRecA->m_RightTopY>tpRecB->m_RightTopY?tpRecA->m_RightTopY:tpRecB->m_RightTopY;

	SRectangle *rect=new SRectangle(minX,minY,maxX,maxY);
	return rect;
}

void CRTree::search(SRectangle *tpRect)
{
	if(tpRect==NULL)
		return ;
	this->search(m_pSRTreeNodeRoot,tpRect);
}

void CRTree::search(SRTreeNode *tpRoot,SRectangle *tpRect)
{
	for(int i=0;i<tpRoot->m_nSize;++i)
	{
		if(this->isOverlap(tpRoot->m_pRect[i],tpRect))
		{
			if(tpRoot->m_bIsLeaf)
			{
				if(this->isSame(tpRoot->m_pRect[i],tpRect))
				{
					m_ofRTree<<" [（"<<tpRoot->m_pRect[i]->m_LeftBottomX<<","<<tpRoot->m_pRect[i]->m_LeftBottomY<<"),("<<tpRoot->m_pRect[i]->m_RightTopX<<","<<tpRoot->m_pRect[i]->m_RightTopY<<"）]"<<endl;
				}
			}
			else this->search(tpRoot->m_pRTreeChild[i],tpRect);
		}
	}
}

int CRTree::getRectArea(SRectangle *tpRec)
{
	return (tpRec->m_RightTopX-tpRec->m_LeftBottomX)*(tpRec->m_RightTopY-tpRec->m_LeftBottomY);
}

int CRTree::getDiffArea(SRectangle *tpRecA,SRectangle *tpRecB)
{
	return abs(this->getRectArea(tpRecA)-this->getRectArea(tpRecB));
}

SRectangle *CRTree::mergeAllRect(SRTreeNode *tpRoot)
{
	int minX=tpRoot->m_pRect[0]->m_LeftBottomX,minY=tpRoot->m_pRect[0]->m_LeftBottomY,
		maxX=tpRoot->m_pRect[0]->m_RightTopX,maxY=tpRoot->m_pRect[0]->m_RightTopY;
	for(int i=1;i<tpRoot->m_nSize;++i)
	{
		minX=minX<tpRoot->m_pRect[i]->m_LeftBottomX?minX:tpRoot->m_pRect[i]->m_LeftBottomX;
		minY=minY<tpRoot->m_pRect[i]->m_LeftBottomY?minY:tpRoot->m_pRect[i]->m_LeftBottomY;

		maxX=maxX>tpRoot->m_pRect[i]->m_RightTopX?maxX:tpRoot->m_pRect[i]->m_RightTopX;
		maxY=maxY>tpRoot->m_pRect[i]->m_RightTopY?maxY:tpRoot->m_pRect[i]->m_RightTopY;
	}
	return new SRectangle(minX,minY,maxX,maxY);
}


void CRTree::insert(SRectangle *tpRect)
{
	if(tpRect==NULL)
		return ;
	this->m_pSRTreeNodeRoot=this->insert(this->m_pSRTreeNodeRoot,tpRect);
}


void CRTree::splitNode(SRTreeNode *tpRoot,int tId)
{
	SRTreeNode *oneNode=tpRoot->m_pRTreeChild[tId];
	SRTreeNode *otherNode=new SRTreeNode();

	otherNode->m_bIsLeaf=oneNode->m_bIsLeaf;
	otherNode->m_nSize=CRTree::g_nMinChildNumber;
	for(int i=0;i<CRTree::g_nMinChildNumber;++i)
	{
		otherNode->m_pRect[i]=oneNode->m_pRect[i+CRTree::g_nMinChildNumber];
		otherNode->m_pRTreeChild[i]=oneNode->m_pRTreeChild[i+CRTree::g_nMinChildNumber];
	}

	for(int i=CRTree::g_nMinChildNumber;i<CRTree::g_nMaxChildNumber;++i)
	{
		oneNode->m_pRect[i]=NULL;
		oneNode->m_pRTreeChild[i]=NULL;
	}
	oneNode->m_nSize=CRTree::g_nMinChildNumber;

	for(int i=tpRoot->m_nSize;i>tId;--i)
	{
		tpRoot->m_pRect[i]=tpRoot->m_pRect[i-1];
		tpRoot->m_pRTreeChild[i]=tpRoot->m_pRTreeChild[i-1];
	}
	tpRoot->m_pRect[tId+1]=mergeAllRect(otherNode);
	tpRoot->m_pRTreeChild[tId+1]=otherNode;

	tpRoot->m_pRect[tId]=mergeAllRect(oneNode);
	tpRoot->m_pRTreeChild[tId]=oneNode;
	++ tpRoot->m_nSize;
}

SRTreeNode *CRTree::insert(SRTreeNode *tpRoot,SRectangle *tpRect)
{
	if(tpRoot->m_nSize==CRTree::g_nMaxChildNumber)
	{
		SRTreeNode *tmpNode=new SRTreeNode();
		tmpNode->m_bIsLeaf=false;
		tmpNode->m_pRTreeChild[0]=tpRoot;
		++tmpNode->m_nSize;
		this->splitNode(tmpNode,0);
		tmpNode->m_pRect[0]=this->mergeTwoRect(tmpNode->m_pRect[0],tpRect);

		this->insertNotGull(tmpNode->m_pRTreeChild[0],tpRect);
		return tmpNode;
	}
	else
	{
		this->insertNotGull(tpRoot,tpRect);
		return tpRoot;
	}
}

void CRTree::insertNotGull(SRTreeNode *tpRoot,SRectangle *tpRect)
{
	if(tpRoot->m_bIsLeaf)
	{
		tpRoot->m_pRect[tpRoot->m_nSize]=tpRect;
		++tpRoot->m_nSize;
	}
	else
	{
		SRectangle *sumRect=this->mergeTwoRect(tpRect,tpRoot->m_pRect[0]);
		int minExpendId=0;
		int minExpendDif=this->getDiffArea(sumRect,tpRoot->m_pRect[0]);

		for(int i=1;i<tpRoot->m_nSize;++i)
		{
			sumRect=this->mergeTwoRect(tpRect,tpRoot->m_pRect[i]);
			int tmpExpendDif=this->getDiffArea(sumRect,tpRoot->m_pRect[i]);
			if(minExpendDif>tmpExpendDif)
			{
				minExpendId=i;
				minExpendDif=tmpExpendDif;
			}
		}
		if(tpRoot->m_pRTreeChild[minExpendId]->m_nSize==CRTree::g_nMaxChildNumber)
		{
			this->splitNode(tpRoot,minExpendId);
		}

		tpRoot->m_pRect[minExpendId]=this->mergeTwoRect(tpRoot->m_pRect[minExpendId],tpRect);
		this->insertNotGull(tpRoot->m_pRTreeChild[minExpendId],tpRect);
	}
}


bool CRTree::isContain(SRectangle *tpRecBig,SRectangle *tpRecSmall)
{
	if(tpRecBig->m_LeftBottomX<=tpRecSmall->m_LeftBottomX
		&&tpRecBig->m_LeftBottomY<=tpRecSmall->m_LeftBottomY
		&&tpRecBig->m_RightTopX>=tpRecSmall->m_RightTopX
		&&tpRecBig->m_RightTopY>=tpRecSmall->m_RightTopY)
		return true;
	return false;
}

bool CRTree::isSame(SRectangle *tpRecA,SRectangle *tpRecB)
{
	if(tpRecA->m_LeftBottomX==tpRecB->m_LeftBottomX
		&&tpRecA->m_LeftBottomY==tpRecB->m_LeftBottomY
		&&tpRecA->m_RightTopX==tpRecB->m_RightTopX
		&&tpRecA->m_RightTopY==tpRecB->m_RightTopY)
		return true;
	return false;
}

bool CRTree::getCertainPath(SRTreeNode *tpRoot,SRectangle *tpRect,list<SRTreeNode *>&tVecPath)
{
	if(tpRoot->m_bIsLeaf)
	{
		for(int i=0;i<tpRoot->m_nSize;++i)
		{
			if(this->isSame(tpRoot->m_pRect[i],tpRect))
			{
				return true;
			}
		}
		return false;
	}

	for(int i=0;i<tpRoot->m_nSize;++i)
	{
		if(this->isContain(tpRoot->m_pRect[i],tpRect))
		{
			tVecPath.push_back(tpRoot->m_pRTreeChild[i]);
			if(this->getCertainPath(tpRoot->m_pRTreeChild[i],tpRect,tVecPath))
			{
				return true;
			}
			tVecPath.pop_back();
		}
	}
	return false;
}

void CRTree::freeSRTreeNode(SRTreeNode *tpCRTNode)
{
	delete tpCRTNode;
}

void CRTree::freeSRectangle(SRectangle *tpRect)
{
	delete tpRect;
}

int CRTree::mergeNode(SRTreeNode * &tpRoot,int tId)
{
	if(tId>0&&tpRoot->m_pRTreeChild[tId-1]->m_nSize>CRTree::g_nMinChildNumber)
	{//左边兄弟最后一个移动到自己第一个
		for(int i=tpRoot->m_pRTreeChild[tId]->m_nSize ;i>0;--i)
		{                                           
			tpRoot->m_pRTreeChild[tId]->m_pRect[i]=tpRoot->m_pRTreeChild[tId]->m_pRect[i-1];
			tpRoot->m_pRTreeChild[tId]->m_pRTreeChild[i]=tpRoot->m_pRTreeChild[tId]->m_pRTreeChild[i-1];
		}

		int lSize=tpRoot->m_pRTreeChild[tId-1]->m_nSize;
		tpRoot->m_pRTreeChild[tId]->m_pRect[0]=tpRoot->m_pRTreeChild[tId-1]->m_pRect[lSize-1];
		tpRoot->m_pRTreeChild[tId]->m_pRTreeChild[0]=tpRoot->m_pRTreeChild[tId-1]->m_pRTreeChild[lSize-1];

		--tpRoot->m_pRTreeChild[tId-1]->m_nSize;
		++tpRoot->m_pRTreeChild[tId]->m_nSize;
		tpRoot->m_pRect[tId-1]= this->mergeAllRect(tpRoot->m_pRTreeChild[tId-1]);
		tpRoot->m_pRect[tId]=this->mergeAllRect(tpRoot->m_pRTreeChild[tId]);

		return tId;

	}
	else if(tId<tpRoot->m_nSize-1&&tpRoot->m_pRTreeChild[tId+1]->m_nSize>CRTree::g_nMinChildNumber)
	{//右边兄弟第一个移动到自己最后一个
		int size=tpRoot->m_pRTreeChild[tId]->m_nSize;
		tpRoot->m_pRTreeChild[tId]->m_pRect[size]=tpRoot->m_pRTreeChild[tId+1]->m_pRect[0];
		tpRoot->m_pRTreeChild[tId]->m_pRTreeChild[size]=tpRoot->m_pRTreeChild[tId+1]->m_pRTreeChild[0];

		for(int i=0;i<tpRoot->m_pRTreeChild[tId+1]->m_nSize-1;++i)
		{
			tpRoot->m_pRTreeChild[tId+1]->m_pRect[i]=tpRoot->m_pRTreeChild[tId+1]->m_pRect[i+1];
			tpRoot->m_pRTreeChild[tId+1]->m_pRTreeChild[i]=tpRoot->m_pRTreeChild[tId+1]->m_pRTreeChild[i+1];
		}

		--tpRoot->m_pRTreeChild[tId+1]->m_nSize;
		++tpRoot->m_pRTreeChild[tId]->m_nSize;

		tpRoot->m_pRect[tId+1]= this->mergeAllRect(tpRoot->m_pRTreeChild[tId+1]);
		tpRoot->m_pRect[tId]=this->mergeAllRect(tpRoot->m_pRTreeChild[tId]);

		return tId;
	}
	else
	{
		if(tId>0)
		{
			int lSize=tpRoot->m_pRTreeChild[tId-1]->m_nSize;
			for(int i=tpRoot->m_pRTreeChild[tId]->m_nSize-1;i>=0;--i)
			{
				tpRoot->m_pRTreeChild[tId]->m_pRect[i+lSize]=tpRoot->m_pRTreeChild[tId]->m_pRect[i];
				tpRoot->m_pRTreeChild[tId]->m_pRTreeChild[i+lSize]=tpRoot->m_pRTreeChild[tId]->m_pRTreeChild[i];
			}
			for(int i=0;i<lSize;++i)
			{
				tpRoot->m_pRTreeChild[tId]->m_pRect[i]=tpRoot->m_pRTreeChild[tId-1]->m_pRect[i];
				tpRoot->m_pRTreeChild[tId]->m_pRTreeChild[i]=tpRoot->m_pRTreeChild[tId-1]->m_pRTreeChild[i];
			}
			tpRoot->m_pRTreeChild[tId]->m_nSize=tpRoot->m_pRTreeChild[tId]->m_nSize+lSize;
			tpRoot->m_pRect[tId]=this->mergeAllRect(tpRoot->m_pRTreeChild[tId]);

			this->freeSRTreeNode(tpRoot->m_pRTreeChild[tId-1]);

			for(int i=tId-1;i<tpRoot->m_nSize-1;++i)
			{
				tpRoot->m_pRect[i]=tpRoot->m_pRect[i+1];
				tpRoot->m_pRTreeChild[i]=tpRoot->m_pRTreeChild[i+1];
			}
			--tpRoot->m_nSize;
			return tId-1;
		}
		else if(tId<tpRoot->m_nSize-1)
		{

			int size=tpRoot->m_pRTreeChild[tId]->m_nSize;
			for(int i=0;i<tpRoot->m_pRTreeChild[tId+1]->m_nSize;++i)
			{
				tpRoot->m_pRTreeChild[tId]->m_pRect[size+i]=tpRoot->m_pRTreeChild[tId+1]->m_pRect[i];
				tpRoot->m_pRTreeChild[tId]->m_pRTreeChild[size+i]=tpRoot->m_pRTreeChild[tId+1]->m_pRTreeChild[i];
			}
			tpRoot->m_pRTreeChild[tId]->m_nSize=size+tpRoot->m_pRTreeChild[tId+1]->m_nSize;
			tpRoot->m_pRect[tId]=this->mergeAllRect(tpRoot->m_pRTreeChild[tId]);

			this->freeSRTreeNode(tpRoot->m_pRTreeChild[tId+1]);

			for(int i=tId+1;i<tpRoot->m_nSize-1;++i)
			{
				tpRoot->m_pRect[i]=tpRoot->m_pRect[i+1];
				tpRoot->m_pRTreeChild[i]=tpRoot->m_pRTreeChild[i+1];
			}

			--tpRoot->m_nSize;
			return tId;
		}
		else//只有一个孩子，缩短高度
		{
			SRTreeNode *p=tpRoot;
			tpRoot=tpRoot->m_pRTreeChild[0];
			this->freeSRTreeNode(p);
			return -1;
		}
	}

}

void CRTree::erase(SRTreeNode *&tpRoot,SRectangle *tpRect,list<SRTreeNode *>::iterator tIterVecPath,list<SRTreeNode *>::iterator iterEnd)
{
	if(tpRoot->m_bIsLeaf)
	{
		bool bFound=false;
		int i=0;
		for(;i<tpRoot->m_nSize;++i)
		{
			if(this->isSame(tpRoot->m_pRect[i],tpRect))
			{
				bFound=true;
				break;
			}
		}

		if(bFound)
		{
			this->freeSRectangle(tpRoot->m_pRect[i]);
			for(int j=i+1;j<tpRoot->m_nSize;++j)
				tpRoot->m_pRect[j-1]=tpRoot->m_pRect[j];
			-- tpRoot->m_nSize;
		}
	}
	else
	{
		if(tIterVecPath==iterEnd)
			return;
		++tIterVecPath;
		for(int i=0;i<tpRoot->m_nSize;++i)
		{
			if(tpRoot->m_pRTreeChild[i]==(*tIterVecPath))
			{
				int id=i;
				if(tpRoot->m_pRTreeChild[i]->m_nSize==CRTree::g_nMinChildNumber)
				{
					id=this->mergeNode(tpRoot,i);
				}
				if(-1==id)
					this->erase(tpRoot,tpRect,tIterVecPath,iterEnd);
				else 
				    this->erase(tpRoot->m_pRTreeChild[id],tpRect,tIterVecPath,iterEnd);

				if(1==tpRoot->m_nSize)
		        {
					SRTreeNode *p=tpRoot;
					tpRoot=tpRoot->m_pRTreeChild[0];
				    this->freeSRTreeNode(p);
				}
				break;
			}
		}
	}
}

void CRTree::erase(SRectangle *tpRect)
{
	if(tpRect==NULL)
		return ;
	list<SRTreeNode *>path;
	path.clear();
	if(this->m_pSRTreeNodeRoot!=NULL)
	{
		path.push_back(this->m_pSRTreeNodeRoot);
		if(this->getCertainPath(this->m_pSRTreeNodeRoot,tpRect,path))
		{
	  		m_ofRTree<<"查找成功 ："<<" [（"<<tpRect->m_LeftBottomX<<","<<tpRect->m_LeftBottomY<<"),("<<tpRect->m_RightTopX<<","<<tpRect->m_RightTopY<<"）]"<<endl;
		    list<SRTreeNode *>::iterator iter= path.begin();
			this->erase(this->m_pSRTreeNodeRoot,tpRect,iter,path.end());
		}
		else
		{
			m_ofRTree<<"查找失败 ："<<" [（"<<tpRect->m_LeftBottomX<<","<<tpRect->m_LeftBottomY<<"),("<<tpRect->m_RightTopX<<","<<tpRect->m_RightTopY<<"）]"<<endl;
		}
		path.clear();
	}
}

void CRTree::display(SRTreeNode *tpRoot,int tDepth)
{
	map<int,int>::iterator iter=m_mapDepthCount.find(tDepth);
	if(iter==m_mapDepthCount.end())
	{
		m_mapDepthCount.insert(make_pair(tDepth,tpRoot->m_nSize));
	}
	else
	{
		iter->second+=tpRoot->m_nSize;
	}
	for(int i=0;i<tpRoot->m_nSize;++i)
	{
		for(int j=0;j<tDepth;++j)
		{
			m_ofRTree<<"    ";		}
		m_ofRTree<<"[（"<<tpRoot->m_pRect[i]->m_LeftBottomX<<","<<tpRoot->m_pRect[i]->m_LeftBottomY<<"),("<<tpRoot->m_pRect[i]->m_RightTopX<<","<<tpRoot->m_pRect[i]->m_RightTopY<<"）]";
		if(tpRoot->m_bIsLeaf)
		{
			m_ofRTree<<"叶"<<endl;
		}
		else
		{
			m_ofRTree<<"非叶"<<endl;
		}
		if(!tpRoot->m_bIsLeaf)
		{
			this->display(tpRoot->m_pRTreeChild[i],tDepth+1);
		}
	}
}

void CRTree::display()
{
	m_mapDepthCount.clear();

	m_ofRTree.open("result/R树形状.txt");
	m_ofRTree<<endl<<"显示R树"<<endl;

	this->display(this->m_pSRTreeNodeRoot,0);
	for(map<int,int>::iterator iter=m_mapDepthCount.begin();iter!=m_mapDepthCount.end();++iter)
	{
		m_ofRTree<<iter->first<<" : "<<iter->second<<endl;
	}

	cout<<"R树索引结构打印到result/R树形状.txt"<<endl<<endl;
	m_ofRTree.close();
}


list<SRectangle *> CRTree::searchAllLeaves(SRectangle *tpRect)
{
	list<SRectangle *>leavesList;
	leavesList.clear();
	if(tpRect==NULL)
		return leavesList;
	this->searchAllLeaves(m_pSRTreeNodeRoot,tpRect,leavesList);
	return leavesList;
}

void CRTree::searchAllLeaves(SRTreeNode *tpRoot,SRectangle *tpRect,list<SRectangle *>&leavesList)
{
	for(int i=0;i<tpRoot->m_nSize;++i)
	{
		if(this->isOverlap(tpRoot->m_pRect[i],tpRect))//有重合
		{
			if(this->isContain(tpRect,tpRoot->m_pRect[i]))//包含当前节点
			{
				if(tpRoot->m_bIsLeaf)
				{
					leavesList.push_back(tpRoot->m_pRect[i]);
				}
				else 
				{
					this->searchAllLeaves(tpRoot->m_pRTreeChild[i],leavesList);
				}
			}
			else 
			{
				if(!tpRoot->m_bIsLeaf)
				{
				   this->searchAllLeaves(tpRoot->m_pRTreeChild[i],tpRect,leavesList);
				}
			}
		}
	}
}

void CRTree::searchAllLeaves(SRTreeNode *tpRoot,list<SRectangle *>&leavesList)
{
	if(tpRoot->m_bIsLeaf)
	{
		for(int i=0;i<tpRoot->m_nSize;++i)
		{
			leavesList.push_back(tpRoot->m_pRect[i]);
		}
	}
	else
	{
		for(int i=0;i<tpRoot->m_nSize;++i)
		{
			this->searchAllLeaves(tpRoot->m_pRTreeChild[i],leavesList);
		}
	}
}