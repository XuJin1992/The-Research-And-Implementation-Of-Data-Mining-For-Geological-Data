
/**
 * Created by xujin on 2015/01/29.
   All Rights Reserved，but you can use this program.
 */


#include"SpatialCo_Location.h"


CSpatialCo_Location::CSpatialCo_Location(double tMinCon,double tMinSup,int tK,CGridSet *tpDaSet,int tHeight,int tWidth,bool bIsUseIndex)
{
	this->m_dMinConfidence=tMinCon;
	this->m_dMinSupport=tMinSup;
	this->m_nAprioriK =tK;
	this->m_nHeight=tHeight;
	this->m_nWidth=tWidth;

	this->m_pPreCGridSet=tpDaSet;
	this->m_pPreCGridSet->sortGridSet();

	this->m_pCApriori= NULL;
	this->m_pFP_Tree= NULL;

	this->m_pCGridSet=new CGridSet();

	if(bIsUseIndex)
		this->createTransactionByRTree();
	else 
		this->createTransactionByEnumerate();

	this->m_nSize=this->m_pCGridSet->getSize();
}

void CSpatialCo_Location::findFrequentKItemSetByApriori()
{
	clock_t nTimeStart=clock(); 

	this->m_pCApriori = new CApriori(this->m_dMinConfidence,this->m_dMinSupport,this->m_nAprioriK,this->m_pCGridSet);
	this->m_pCApriori->findFrequentKItemSet();
	ofstream ofFrequentKItemSet;
	ofFrequentKItemSet.open("result/Apriori.txt");
	this->m_pCApriori->print(ofFrequentKItemSet);

    clock_t nTimeStop = clock();
	double durTime=(double)(nTimeStop - nTimeStart)/CLOCKS_PER_SEC;
	cout<<"Apriori算法挖掘结束,耗时"<<durTime<<"秒,结果打印到result/Apriori.txt"<<endl<<endl;
	ofFrequentKItemSet<<"Apriori算法挖掘结束,耗时"<<durTime<<"秒"<<endl;
	ofFrequentKItemSet.close();
}

void CSpatialCo_Location::findFrequentItemSetByFP_Growth()
{
	cout<<"FP_Growth算法开始执行……"<<endl;
	clock_t nTimeStart=clock(); 

	CFP_Tree *pFP_Tree=new CFP_Tree(*(this->m_pCGridSet),this->m_dMinConfidence,this->m_dMinSupport,1);
	for(vector<CGrid>::iterator iter=this->m_pCGridSet->getVeCGrid().begin(); iter!=this->m_pCGridSet->getVeCGrid().end();++iter)
	{
 		pFP_Tree->insertFPTree(*iter,0,1);
	}

	vector<ItemSupport> itemSupportSet;
	CFP_Growth::g_ofFP_GrowthResult.open("result/FP_Growth.txt");
	CFP_Growth *pFP_Growth=new CFP_Growth(pFP_Tree,itemSupportSet);
	pFP_Tree->destroy();

    clock_t nTimeStop = clock();
	double durTime=(double)(nTimeStop - nTimeStart)/CLOCKS_PER_SEC;
	cout<<"FP_Growth算法挖掘结束,耗时"<<durTime<<"秒,结果打印到result/FP_Growth.txt"<<endl<<endl;

	CFP_Growth::g_ofFP_GrowthResult<<"FP_Growth算法挖掘结束,耗时"<<durTime<<"秒"<<endl;
	CFP_Growth::g_ofFP_GrowthResult.close();
}

void CSpatialCo_Location::createTransactionByRTree()
{
	
	this->m_pCRTree=new CRTree();
	vector<CGrid>vecGrid=this->m_pPreCGridSet->getVeCGrid();
	for(vector<CGrid>::iterator iter=vecGrid.begin(); iter!=vecGrid.end();++iter)
	{
		SRectangle *rect=iter->getSRectangle();
		this->m_pCRTree->insert(rect);
	}
	this->m_pCRTree->display();

	clock_t nTimeStart=clock(); 

	vecGrid=this->m_pPreCGridSet->getVeCGrid();
	for(vector<CGrid>::iterator iter=vecGrid.begin(); iter!=vecGrid.end();++iter)
	{
		SRectangle *rect=iter->getSRectangle();
		SRectangle *newRect=new SRectangle(rect->m_LeftBottomX-this->m_nWidth,rect->m_LeftBottomY-this->m_nHeight,rect->m_RightTopX+this->m_nWidth,rect->m_RightTopY+this->m_nHeight);
		vector<string> vecCo_Colation;
		vecCo_Colation.clear();

		list<SRectangle *>rectList=this->m_pCRTree->searchAllLeaves(newRect);
		vector<CGrid> cGridList=this->m_pPreCGridSet->getCGridByRectList(rectList);
	    for(vector<CGrid>::iterator iterInCGrid=cGridList.begin(); iterInCGrid!=cGridList.end();++iterInCGrid)
		{
			vector<string>vecItem=iterInCGrid->getVecItem();
			for(vector<string>::iterator iterItem=vecItem.begin();iterItem!=vecItem.end();++iterItem)
			{
				bool flag=false;
				for(vector<string>::iterator iterVecCo_Colation=vecCo_Colation.begin();iterVecCo_Colation!=vecCo_Colation.end();++iterVecCo_Colation)
				{
					if((*iterVecCo_Colation)==(*iterItem))
					{
						flag=true;
						break;
					}
				}
				if(!flag)
					vecCo_Colation.push_back(*iterItem);
			}

		}

		CGrid da(newRect,vecCo_Colation);
		this->m_pCGridSet->addGrid(da);
	}
	
	 clock_t nTimeStop = clock();
	double durTime=(double)(nTimeStop - nTimeStart)/CLOCKS_PER_SEC;

	ofstream ofItemSet;
	ofItemSet.open("result/生成空间事务集.txt");
	this->m_pCGridSet->print(ofItemSet);
	cout<<"栅格扫描完成,耗时"<<durTime<<"秒,空间事务集打印到result/生成空间事务集.txt"<<endl<<endl;
	ofItemSet<<"栅格扫描完成,耗时"<<durTime<<"秒"<<endl;
	ofItemSet.close();
}


void CSpatialCo_Location::createTransactionByEnumerate()
{
	clock_t nTimeStart=clock(); 

	vector<CGrid>vecGrid=this->m_pPreCGridSet->getVeCGrid();
	for(vector<CGrid>::iterator iter=vecGrid.begin(); iter!=vecGrid.end();++iter)
	{
		SRectangle *rect=iter->getSRectangle();
		SRectangle *newRect=new SRectangle(rect->m_LeftBottomX-this->m_nWidth,rect->m_LeftBottomY-this->m_nHeight,rect->m_RightTopX+this->m_nWidth,rect->m_RightTopY+this->m_nHeight);
		vector<string> vecCo_Colation;
		vecCo_Colation.clear();

		vector<CGrid> cGridList=this->m_pPreCGridSet->getCGridByRect(newRect);

	    for(vector<CGrid>::iterator iterInCGrid=cGridList.begin(); iterInCGrid!=cGridList.end();++iterInCGrid)
		{
			vector<string>vecItem=iterInCGrid->getVecItem();
			for(vector<string>::iterator iterItem=vecItem.begin();iterItem!=vecItem.end();++iterItem)
			{
				bool flag=false;
				for(vector<string>::iterator iterVecCo_Colation=vecCo_Colation.begin();iterVecCo_Colation!=vecCo_Colation.end();++iterVecCo_Colation)
				{
					if((*iterVecCo_Colation)==(*iterItem))
					{
						flag=true;
						break;
					}
				}
				if(!flag)
					vecCo_Colation.push_back(*iterItem);
			}

		}

		CGrid da(newRect,vecCo_Colation);
		this->m_pCGridSet->addGrid(da);
	}
	
	clock_t nTimeStop = clock();
	double durTime=(double)(nTimeStop - nTimeStart)/CLOCKS_PER_SEC;

	ofstream ofItemSet;
	ofItemSet.open("result/不加空间索引生成空间事务集.txt");
	this->m_pCGridSet->print(ofItemSet);
	cout<<"不加空间索引栅格扫描完成,耗时"<<durTime<<"秒,空间事务集打印到result/不加空间索引生成空间事务集.txt"<<endl<<endl;
	ofItemSet<<"不加空间索引栅格扫描完成,耗时"<<durTime<<"秒"<<endl;
	ofItemSet.close();
}

