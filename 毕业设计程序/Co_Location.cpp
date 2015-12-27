/**
 * Created by xujin on 2015/05/22.
   All Rights Reserved，but you can use this program.
 */

#include"Co_Location.h"

CCo_Location::CCo_Location(int tExtendLength,double tMin_prevalence,CGridSet *tPDaSet)
{
	this->m_nExtendLength=tExtendLength;
	this->m_dMin_prevalence=tMin_prevalence;
	this->m_pCGridSet = tPDaSet;
	this->m_pPreCandidateSet=new CCo_LocationResultSet();
	this->m_pCurCandidateSet=new CCo_LocationResultSet();
	this->m_pCo_Location1ItemSet=new CCo_LocationResultSet();
}

void CCo_Location::findCo_LocationSet()
{
	this->findCo_Location1ItemSet();
	while(this->m_pPreCandidateSet->getSize()!=0)
	{
		aprioriGen();
		generateTableInstance();
		filter();
		m_pPreCandidateSet=m_pCurCandidateSet;
	}
}

void CCo_Location::print()
{
	cout<<"########### Co_Location算法 ###############"<<endl;
	
	cout<<"###########################################"<<endl<<endl;
}

void CCo_Location::findCo_Location1ItemSet()
{
	for(vector<CGrid>::iterator iter=this->m_pCGridSet->getVeCGrid().begin();iter!=this->m_pCGridSet->getVeCGrid().end();++iter)
	{
		for(vector<string>::iterator strIter=iter->getVecItem().begin();strIter!=iter->getVecItem().end();++strIter)
		{
			vector<string> vec1Itemset;
			vec1Itemset.push_back(*strIter);
			SCo_LocationResult* ret=this->isExist(this->m_pCo_Location1ItemSet,vec1Itemset);
			if(NULL==ret)//添加完整项
			{
				SCo_LocationResult *vecResultSet=new SCo_LocationResult();

				vecResultSet->m_vecItem.push_back(*strIter);

				vector<SRectangle*>rectList;
				rectList.clear();
				rectList.push_back(iter->getSRectangle());
				vecResultSet->m_vecRectList.push_back(rectList);

				m_pCo_Location1ItemSet->addResult(vecResultSet);
			}
			else 
			{
				vector<SRectangle*>rectList;
				rectList.clear();
				rectList.push_back(iter->getSRectangle());
				ret->addRectList(rectList);
			}
		}
	}
	m_pPreCandidateSet=m_pCurCandidateSet;
}

SCo_LocationResult* CCo_Location::isExist(CCo_LocationResultSet* tpResultSet,vector<string> &tVecCandidateSet)
{
	vector<SCo_LocationResult*> vecResultset=tpResultSet->getResultSet();
	for(vector<SCo_LocationResult*>::iterator iterResult=vecResultset.begin();iterResult!=vecResultset.end();++iterResult)
	{
		if((*iterResult)->m_vecItem.size()!=tVecCandidateSet.size())
			continue;
		int equalCount=0;
		for(vector<string>::iterator iterStr=(*iterResult)->m_vecItem.begin();iterStr!=(*iterResult)->m_vecItem.end();++iterStr)
		{
			for(vector<string>::iterator iter=tVecCandidateSet.begin();iter!=tVecCandidateSet.end();++iter)
			{
				if((*iterStr)==(*iter))
				{
					++equalCount;
				}
			}
		}
		if(equalCount==tVecCandidateSet.size())
			return *iterResult;
	}
	return NULL;
}

bool CCo_Location::hasInfrequentSubSet(vector<string> &tVecCandidateSet)
{
	bool bRet=false;
	if(this->m_pPreCandidateSet!=NULL)
	{
		for(vector<string>::iterator out=tVecCandidateSet.begin();out!=tVecCandidateSet.end();++out)
		{
			vector<string>tmp;
			tmp.clear();
			for(vector<string>::iterator in=tVecCandidateSet.begin();in!=tVecCandidateSet.end();++in)
			{
				if(*out!=*in)
				{
					tmp.push_back(*in);
				}
			}
		//	if(!this->m_pPreCandidateSet->isContain(tmp))
			{
				bRet=true;
				break;
			}
		}
	}
	return bRet;
}

void CCo_Location::aprioriGen()
{
	vector<string> can;
	for(size_t i=0;i<(this->m_pPreCandidateSet->getSize());++i)
	{
		for(size_t j=0;j<(this->m_pPreCandidateSet->getSize());++j)
		{
			if(i!=j)
			{
				can.clear();
			/*	if(this->m_pPreCandidateSet->combineFrequentSet(i,j,can))
				{
					if(!this->hasInfrequentSubSet(can)&&!m_pCurCandidateSet->isExist(can))
						m_pCurCandidateSet->addGrid(CGrid(can));
				}
				*/
			}
		}
	}
}

void CCo_Location::generateTableInstance()
{
}

void CCo_Location::filter()
{
}
