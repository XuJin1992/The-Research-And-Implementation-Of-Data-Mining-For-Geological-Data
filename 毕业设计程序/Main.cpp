
#include"Rectangle.h"
#include"Apriori.h"
#include"FP_Tree.h"
#include"FP_Growth.h"
#include"RTree.h"
#include"SpatialCo_Location.h"

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

int main()
{
	
	CGridSet vecGridSet;
	ifstream inFile;
	inFile.open("dataset/testA32.txt");
	string lineStr;
	string pattern=",";
	vector<string>vecLine;
	while(getline(inFile,lineStr))
	{
		vecLine.clear();
		size_t start=0,index=lineStr.find_first_of(pattern,0);
		while(index!=lineStr.npos)
		{
			if(start!=index)
				vecLine.push_back(lineStr.substr(start,index-start));
			start=index+1;
			index=lineStr.find_first_of(pattern,start);
		}
		if(!lineStr.substr(start).empty())
			vecLine.push_back(lineStr.substr(start));

		
		SRectangle *pSRect=new SRectangle(std::atoi(vecLine[0].c_str()),std::atoi(vecLine[1].c_str()),
			std::atoi(vecLine[2].c_str()),std::atoi(vecLine[3].c_str()));
	    vector<string> vecItemSet;
		for(int i=4;i<vecLine.size();++i)
		{
		 	vecItemSet.push_back(vecLine[i]);
		}
		CGrid da(pSRect,vecItemSet);
	   	vecGridSet.addGrid(da);
	}
	inFile.close();
	
	double minSupport=0.20;
	double minConfidence=0.024;
	int K=3;
	int height=1;
	int width=1;
	bool bIsUseIndex=true;
	
	CSpatialCo_Location *pSpatialCo_Location=new CSpatialCo_Location(minConfidence,minSupport,K,&vecGridSet,height,width,bIsUseIndex);
	pSpatialCo_Location->findFrequentKItemSetByApriori();
	pSpatialCo_Location->findFrequentItemSetByFP_Growth();
	

	/*
	CGridSet vecGridSet;
	SRectangle *pSRect1=new SRectangle(1,1,2,2);
	vector<string> vecGridSet1;
	vecGridSet1.push_back("I2");
	CGrid da1(pSRect1,vecGridSet1);
	vecGridSet.addGrid(da1);


	SRectangle *pSRect2=new SRectangle(2,1,3,2);
	vector<string> vecGridSet2;
	vecGridSet2.push_back("I1");
	CGrid da2(pSRect2,vecGridSet2);
	vecGridSet.addGrid(da2);

	SRectangle *pSRect3=new SRectangle(3,1,4,2);
	vector<string> vecGridSet3;
	vecGridSet3.push_back("I2");
	CGrid da3(pSRect3,vecGridSet3);
	vecGridSet.addGrid(da3);


	SRectangle *pSRect4=new SRectangle(4,1,5,2);
	vector<string> vecGridSet4;
	vecGridSet4.push_back("I3");
	CGrid da4(pSRect4,vecGridSet4);
	vecGridSet.addGrid(da4);


	SRectangle *pSRect5=new SRectangle(1,2,2,3);
	vector<string> vecGridSet5;
	vecGridSet5.push_back("I4");
	CGrid da5(pSRect5,vecGridSet5);
	vecGridSet.addGrid(da5);

	SRectangle *pSRect6=new SRectangle(2,2,3,3);
	vector<string> vecGridSet6;
	vecGridSet6.push_back("I5");
	CGrid da6(pSRect6,vecGridSet6);
	vecGridSet.addGrid(da6);


	SRectangle *pSRect7=new SRectangle(3,2,4,3);
	vector<string> vecGridSet7;
	vecGridSet7.push_back("I3");
	CGrid da7(pSRect7,vecGridSet7);
	vecGridSet.addGrid(da7);


	SRectangle *pSRect8=new SRectangle(4,2,5,3);
	vector<string> vecGridSet8;
	vecGridSet8.push_back("I1");
	CGrid da8(pSRect8,vecGridSet8);
	vecGridSet.addGrid(da8);
	
	CSpatialCo_Location *pSpatialCo_Location=new CSpatialCo_Location(0.1,0.24,3,&vecGridSet,0,1);
	pSpatialCo_Location->findFrequentKItemSetByApriori();
	pSpatialCo_Location->findFrequentItemSetByFP_Growth();
	*/
	/*
	SRectangle *pSRect9=new SRectangle(4,4,8,8);
	vector<string> vecGridSet9;
	vecGridSet9.push_back("I2");
	CGrid da9(pSRect9,vecGridSet9);
	vecGridSet.addGrid(da9);
	*/

	/*
	for(vector<CGrid>::iterator iter=vecGridSet.getVeCGrid().begin(); iter!=vecGridSet.getVeCGrid().end();++iter)
	{
	SRectangle *rect=iter->getSRectangle();
	cout<<"[£¨"<<(rect)->m_LeftBottomX<<","<<(rect)->m_LeftBottomY
	<<"),("<<(rect)->m_RightTopX<<","<<(rect)->m_RightTopY<<"£©]"<<endl;
	}
	cout<<"************************************"<<endl;
	vecGridSet.sortGridSet();

	for(vector<CGrid>::iterator iter=vecGridSet.getVeCGrid().begin(); iter!=vecGridSet.getVeCGrid().end();++iter)
	{
	SRectangle *rect=iter->getSRectangle();
	cout<<"[£¨"<<(rect)->m_LeftBottomX<<","<<(rect)->m_LeftBottomY
	<<"),("<<(rect)->m_RightTopX<<","<<(rect)->m_RightTopY<<"£©]"<<endl;
	}
	cout<<"************************************"<<endl;

	SRectangle *pSRect=new SRectangle(1,1,6,6);
	list<SRectangle *> rectList;
	rectList.clear();
	rectList.push_back(pSRect);

	vector<CGrid> cGridList=vecGridSet.getCGridByRectList(rectList);
	printf("cGridList.size()=%d\n",cGridList.size());
	for(vector<CGrid>::iterator iter=cGridList.begin(); iter!=cGridList.end();++iter)
	{
	SRectangle *rect=iter->getSRectangle();
	cout<<"[£¨"<<(rect)->m_LeftBottomX<<","<<(rect)->m_LeftBottomY
	<<"),("<<(rect)->m_RightTopX<<","<<(rect)->m_RightTopY<<"£©]"<<endl;
	}
	cout<<"************************************"<<endl;
	*/
	/*
	CSpatialCo_Location *pSpatialCo_Location=new CSpatialCo_Location(0.1,0.24,3,&vecGridSet,0,1);
	pSpatialCo_Location->findFrequentKItemSetByApriori();
	pSpatialCo_Location->findFrequentItemSetByFP_Growth();
	*/
	/*
	CRTree *rTree=new CRTree();
	SRectangle *rect;

	for(int i=0;i<2;++i)
	{
	for(int j=0;j<2;++j)
	{
	rect=new SRectangle(10-i,j+10,30-i,30-j);
	rTree->insert(rect);
	cout<<"²éÕÒ¾ØÐÎ: [£¨"<<rect->m_LeftBottomX<<","<<rect->m_LeftBottomY
	<<"),("<<rect->m_RightTopX<<","<<rect->m_RightTopY<<"£©]"<<endl;
	rTree->search(rect);

	}
	}
	rTree->display();

	rect=new SRectangle(9,11,30,30);
	list<SRectangle *>listLeaves=rTree->searchAllLeaves(rect);
	for(list<SRectangle *>::iterator iter=listLeaves.begin();iter!=listLeaves.end();++iter)
	{
	cout<<"[£¨"<<(*iter)->m_LeftBottomX<<","<<(*iter)->m_LeftBottomY
	<<"),("<<(*iter)->m_RightTopX<<","<<(*iter)->m_RightTopY<<"£©]"<<endl;
	}
	*/
	system("pause");

	return 0;
}
