/**
 * Created by xujin on 2014/12/1.
   All Rights Reserved£¬but you can use this program.
 */

#include"Grid.h"


CGrid::CGrid()
{
	m_pSRect = NULL;
}

CGrid::CGrid(SRectangle *tpSRect)
{
	m_pSRect = tpSRect;
}

CGrid::CGrid(SRectangle *tpSRect,vector<string>& tVec)
{
	m_pSRect = tpSRect;
	for(vector<string>::iterator iter=tVec.begin(); iter!= tVec.end();++iter)
	{
		m_vecItem.push_back(*iter);
	}
}

CGrid::CGrid(vector<string>& tVec)
{
	m_pSRect = NULL;
	for(vector<string>::iterator iter=tVec.begin(); iter!= tVec.end();++iter)
	{
		m_vecItem.push_back(*iter);
	}
}


bool CGrid::isContain(vector<string>& tVec)
{
	if(tVec.empty())
		return true;
	for(vector<string>::iterator out=tVec.begin(); out!= tVec.end();++out)
	{
		bool flag=false;
		for(vector<string>::iterator in=m_vecItem.begin();in!=m_vecItem.end();++in)
		{
			if(*in==*out)
			{
				flag=true;
				break;
			}
		}
		if(!flag)
			return false;
	}
	return true;
}

vector<string>& CGrid::getVecItem()
{
	return m_vecItem;
}

void CGrid::print(ofstream &ofFile)
{
	for(vector<string>::iterator iter=m_vecItem.begin(); iter!=m_vecItem.end();++iter)
	{
		ofFile<<(*iter).c_str()<<"   ";
	}
	ofFile<<endl;
}

void CGrid::addItem(string tItem)
{
	this->m_vecItem.push_back(tItem);
}

SRectangle *CGrid::getSRectangle()
{
	return m_pSRect;
}