/**
 * Created by xujin on 2014/12/1.
   All Rights Reserved，but you can use this program.
 */

#include"Apriori.h"


CApriori::CApriori(double tMinCon,double tMinSup,int tK,CGridSet *tPDaSet)
{
	this->m_dMinConfidence=tMinCon;
	this->m_dMinSupport=tMinSup;
	this->m_nK=tK;
	this->m_pCGridSet = tPDaSet;

	this->m_nSize = tPDaSet->getSize();

	this->m_nMinConfidence=this->m_dMinConfidence*this->m_nSize;
	this->m_nMinSupport=this->m_dMinSupport*this->m_nSize;

	this->m_pCDateCandidateSet=new CGridSet();

}

bool CApriori::hasInfrequentSubSet(vector<string> &tVecCandidateSet)
{
	bool bRet=false;
	if(this->m_pCDateCandidateSet!=NULL)
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
			if(!this->m_pCDateCandidateSet->isContain(tmp))
			{
				bRet=true;
				break;
			}
		}
	}
	return bRet;
}

void CApriori::aprioriGen()
{
	vector<string> can;
	CGridSet *CandidateSet=new CGridSet();
	for(size_t i=0;i<(this->m_pCDateCandidateSet->getSize());++i)
	{
		for(size_t j=0;j<(this->m_pCDateCandidateSet->getSize());++j)
		{
			if(i!=j)
			{
				can.clear();
				if(this->m_pCDateCandidateSet->combineFrequentSet(i,j,can))
				{
					if(!this->hasInfrequentSubSet(can)&&!CandidateSet->isExist(can))
						CandidateSet->addGrid(CGrid(can));
				}
			}
		}
	}
	eraseCandidateSet();
	this->m_pCDateCandidateSet=CandidateSet;
}

void CApriori::eraseCandidateSet()
{
	for(vector<CGrid>::iterator iter=this->m_pCDateCandidateSet->getVeCGrid().begin();
		iter!=this->m_pCDateCandidateSet->getVeCGrid().end();++iter)
	{
		iter->getVecItem().clear();
	}
	this->m_pCDateCandidateSet->getVeCGrid().clear();
	delete this->m_pCDateCandidateSet;
	this->m_pCDateCandidateSet=NULL;
}

bool CApriori::isFrequentSet(vector<string> &tVecCandidateSet)
{
	int sup=this->m_pCGridSet->getSupportCount(tVecCandidateSet);
	if(sup<m_nMinSupport)
		return false;
	return true;
}

void CApriori::findFrequent1ItemSet()
{
	for(vector<CGrid>::iterator iter=this->m_pCGridSet->getVeCGrid().begin();iter!=this->m_pCGridSet->getVeCGrid().end();++iter)
	{
		for(vector<string>::iterator strIter=iter->getVecItem().begin();strIter!=iter->getVecItem().end();++strIter)
		{
			vector<string> vec1Itemset;
			vec1Itemset.push_back(*strIter);
			if(this->isFrequentSet(vec1Itemset))
			{
				if(!this->isExist(vec1Itemset))
				   m_pCDateCandidateSet->addGrid(CGrid(vec1Itemset));
			}
		}
	}
}


void CApriori::findFrequentKItemSet()
{
	cout<<"Apriori算法开始执行……"<<endl;
	this->findFrequent1ItemSet();
	for(int i=2;i<=this->m_nK;++i)
	{
		cout<<"处理"<<i<<"项集"<<endl;
		this->aprioriGen();
		if(this->m_pCDateCandidateSet->getVeCGrid().size()==0)
			return ;
		for(vector<CGrid>::iterator iter=this->m_pCDateCandidateSet->getVeCGrid().begin();iter!=(this->m_pCDateCandidateSet->getVeCGrid().end());)
		{
			int sup=this->m_pCGridSet->getSupportCount(iter->getVecItem());
			
			if(sup<this->m_nMinSupport)
			{
				iter=this->m_pCDateCandidateSet->getVeCGrid().erase(iter);
			}
			else ++iter;
		}
	}
}

void CApriori::print(ofstream &ofFile)
{
	m_pCDateCandidateSet->print(ofFile);
}

bool CApriori::isExist(vector<string> &tVecCandidateSet)
{
    if(this->m_pCDateCandidateSet->isExist(tVecCandidateSet))
		return true;
	return false;
}