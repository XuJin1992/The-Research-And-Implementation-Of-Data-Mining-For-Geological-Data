/**
 * Created by xujin on 2014/12/1.
   All Rights Reserved£¬but you can use this program.
 */

#include"GridSet.h"
#include<list>
#include<algorithm>

CGridSet::CGridSet()
{
	m_veCGrid.clear();
}

int CGridSet::getSize()
{
	return m_veCGrid.size();
}

void CGridSet::addGrid(CGrid tGrid)
{
	m_veCGrid.push_back(tGrid);
}

int CGridSet::getSupportCount(vector<string>& tVecCandidateSet)
{
	int count =0;
	for(vector<CGrid>::iterator iter= m_veCGrid.begin();iter!=m_veCGrid.end();++iter)
	{
		if(iter->isContain(tVecCandidateSet))
			++count;
	}
	return count;
}

bool CGridSet::isContain(vector<string>& tVecPreCandidateSet)
{
	for(vector<CGrid>::iterator iter= m_veCGrid.begin();iter!=m_veCGrid.end();++iter)
	{
		if(iter->isContain(tVecPreCandidateSet))
			return true;
	}
	return false;
}

bool CGridSet::isExist(vector<string> &tVec)
{
	for(vector<CGrid>::iterator iter= m_veCGrid.begin();iter!=m_veCGrid.end();++iter)
	{
		if(iter->isContain(tVec)&&tVec.size()==iter->getVecItem().size())
			return true;
	}
	return false;
}

bool CGridSet::combineFrequentSet(size_t id1,size_t id2,vector<string>& tVecPreCandidateSet)
{
	int sameCount=0;
	string single1;
	for(vector<string>::iterator out=m_veCGrid[id1].getVecItem().begin();out!=m_veCGrid[id1].getVecItem().end();++out)
	{
		bool flag=false;
		for(vector<string>::iterator in=m_veCGrid[id2].getVecItem().begin();in!=m_veCGrid[id2].getVecItem().end();++in)
		{
			if(*out==*in)
			{
				flag=true;
				++sameCount;
				break;
			}
		}
		if(!flag)
			single1=*out;
	}
	if(sameCount != m_veCGrid[id1].getVecItem().size()-1)
		return false;
	for(vector<string>::iterator iter=m_veCGrid[id2].getVecItem().begin();iter!=m_veCGrid[id2].getVecItem().end();++iter)
	{
		tVecPreCandidateSet.push_back(*iter);
	}
	tVecPreCandidateSet.push_back(single1);
	return true;
}

vector<CGrid>& CGridSet::getVeCGrid()
{
	return this->m_veCGrid;
}

void CGridSet::print(ofstream &ofFile)
{
	for(vector<CGrid>::iterator iter=m_veCGrid.begin(); iter!=m_veCGrid.end();++iter)
	{
		iter->print(ofFile);
	}
}

bool cmpCGrid( CGrid &a, CGrid &b)
{
	SRectangle *aa=a.getSRectangle(),*bb=b.getSRectangle();
	if(aa->m_LeftBottomX!=bb->m_LeftBottomX)
		return aa->m_LeftBottomX<bb->m_LeftBottomX;
	else
	{
		if(aa->m_RightTopX!=bb->m_RightTopX)
			return aa->m_RightTopX<bb->m_RightTopX;
		else
		{
			if(aa->m_LeftBottomY!=bb->m_LeftBottomY)
				return aa->m_LeftBottomY<bb->m_LeftBottomY;
			else
				return aa->m_RightTopY<bb->m_RightTopY;
		}
	}
}

void CGridSet::sortGridSet()
{
	std::sort(m_veCGrid.begin(),m_veCGrid.end(),cmpCGrid);
}

vector<CGrid> CGridSet::getCGridByRectList(list<SRectangle *>tpRectList)
{
	vector<CGrid>retCGrid;
	
	for(list<SRectangle *>::iterator iter=tpRectList.begin();iter!=tpRectList.end();++iter)
	{
		CGrid *value=binarySearch(*iter);
		if(value!=NULL)
			retCGrid.push_back(*value);
	}
	return retCGrid;
}

int CGridSet::compareRect(SRectangle *tpRecA,SRectangle *tpRecB)
{
	if(tpRecA->m_LeftBottomX==tpRecB->m_LeftBottomX
		&&tpRecA->m_LeftBottomY==tpRecB->m_LeftBottomY
		&&tpRecA->m_RightTopX==tpRecB->m_RightTopX
		&&tpRecA->m_RightTopY==tpRecB->m_RightTopY)
		return 0;

	if(tpRecA->m_LeftBottomX<tpRecB->m_LeftBottomX)
		return 1;
	if(tpRecA->m_LeftBottomX>tpRecB->m_LeftBottomX)
		return -1;

	if(tpRecA->m_RightTopX<tpRecB->m_RightTopX)
		return 1;
	if(tpRecA->m_RightTopX>tpRecB->m_RightTopX)
		return -1;

	if(tpRecA->m_LeftBottomY<tpRecB->m_LeftBottomY)
		return 1;
	if(tpRecA->m_LeftBottomY>tpRecB->m_LeftBottomY)
		return -1;

	if(tpRecA->m_RightTopY<tpRecB->m_RightTopY)
		return 1;
	if(tpRecA->m_RightTopY>tpRecB->m_RightTopY)
		return -1;
}

CGrid* CGridSet::binarySearch(SRectangle *key)
{
	int left=0,right = m_veCGrid.size()-1;
    int middle;
    while(left<=right)
	{
		middle=(left+right)>>1;
		SRectangle *tmp=m_veCGrid[middle].getSRectangle();
		int code=compareRect(tmp,key);
		if(0==code)
			return &m_veCGrid[middle];
		else if(1==code)
			left=middle+1;
		else 
			right=middle-1;
    }
	CGrid *ret=NULL;
	return ret;
}

bool CGridSet::isContain(SRectangle *tpRecBig,SRectangle *tpRecSmall)
{
	if(tpRecBig->m_LeftBottomX<=tpRecSmall->m_LeftBottomX
		&&tpRecBig->m_LeftBottomY<=tpRecSmall->m_LeftBottomY
		&&tpRecBig->m_RightTopX>=tpRecSmall->m_RightTopX
		&&tpRecBig->m_RightTopY>=tpRecSmall->m_RightTopY)
		return true;
	return false;
}

vector<CGrid> CGridSet::getCGridByRect(SRectangle* tpRect)
{
	vector<CGrid>retCGrid;
	for(vector<CGrid>::iterator iter=m_veCGrid.begin(); iter!=m_veCGrid.end();++iter)
	{
		if(this->isContain(tpRect,iter->getSRectangle()))
			retCGrid.push_back(*iter);
	}
	return retCGrid;
}