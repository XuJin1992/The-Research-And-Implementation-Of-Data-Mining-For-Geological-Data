
#include"Rectangle.h"
#include"Apriori.h"
#include"FP_Tree.h"
#include"FP_Growth.h"

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

int main()
{
	CGridSet vecGridSet;

	SRectangle *pSRect1=new SRectangle(1,1,2,2);
	vector<string> vecGridSet1;
	vecGridSet1.push_back("I2");
	vecGridSet1.push_back("I3");
	CGrid da1(pSRect1,vecGridSet1);
	vecGridSet.addGrid(da1);

	SRectangle *pSRect2=new SRectangle(1,1,3,3);
	vector<string> vecGridSet2;
	vecGridSet2.push_back("I1");
	vecGridSet2.push_back("I2");
	vecGridSet2.push_back("I4");
	CGrid da2(pSRect2,vecGridSet2);
	vecGridSet.addGrid(da2);

	SRectangle *pSRect3=new SRectangle(2,2,5,5);
	vector<string> vecGridSet3;
	vecGridSet3.push_back("I1");
	vecGridSet3.push_back("I3");
	CGrid da3(pSRect3,vecGridSet3);
	vecGridSet.addGrid(da3);

	SRectangle *pSRect4=new SRectangle(1,1,6,6);
	vector<string> vecGridSet4;
	vecGridSet4.push_back("I2");
	vecGridSet4.push_back("I3");
	CGrid da4(pSRect4,vecGridSet4);
	vecGridSet.addGrid(da4);

	SRectangle *pSRect5=new SRectangle(4,4,8,8);
	vector<string> vecGridSet5;
	vecGridSet5.push_back("I1");
	vecGridSet5.push_back("I3");
	CGrid da5(pSRect5,vecGridSet5);
	vecGridSet.addGrid(da5);

	SRectangle *pSRect6=new SRectangle(3,3,6,6);
	vector<string> vecGridSet6;
	vecGridSet6.push_back("I1");
	vecGridSet6.push_back("I2");
	vecGridSet6.push_back("I3");
	vecGridSet6.push_back("I5");
	CGrid da6(pSRect6,vecGridSet6);
	vecGridSet.addGrid(da6);

	SRectangle *pSRect7=new SRectangle(3,3,8,8);
	vector<string> vecGridSet7;
	vecGridSet7.push_back("I1");
	vecGridSet7.push_back("I2");
	vecGridSet7.push_back("I3");
	CGrid da7(pSRect7,vecGridSet7);
	vecGridSet.addGrid(da7);

	SRectangle *pSRect8=new SRectangle(3,3,9,9);
	vector<string> vecGridSet8;
	vecGridSet8.push_back("I1");
	vecGridSet8.push_back("I2");
	vecGridSet8.push_back("I5");
	CGrid da8(pSRect8,vecGridSet8);
	vecGridSet.addGrid(da8);

	SRectangle *pSRect9=new SRectangle(4,4,8,8);
	vector<string> vecGridSet9;
	vecGridSet9.push_back("I2");
	vecGridSet9.push_back("I4");
	CGrid da9(pSRect9,vecGridSet9);
	vecGridSet.addGrid(da9);
	

	
	CApriori apriori(0.1,0.24,3,&vecGridSet);
	apriori.findFrequentKItemSet();
	apriori.print();
	
	
	CFP_Tree *pFP_Tree=new CFP_Tree(vecGridSet,0.1,0.24,1);

	//vecGridSet.print();

	for(vector<CGrid>::iterator iter=vecGridSet.getVeCGrid().begin(); iter!=vecGridSet.getVeCGrid().end();++iter)
	{
		pFP_Tree->insertFPTree(*iter,0,1);
	}
	/*
	pFP_Tree->printPath();
	pFP_Tree->printItemHeaderList();
	*/


	vector<ItemSupport> itemSupportSet;

	cout<<cout<<"############ FP_GrowthËã·¨ ##################"<<endl;
	CFP_Growth *pFP_Growth=new CFP_Growth(pFP_Tree,itemSupportSet);
	cout<<"###########################################"<<endl<<endl;
	
	//pFP_Growth->printPath();
	//pFP_Growth->printItemHeaderList();;


	pFP_Tree->destroy();

	system("pause");

	return 0;
}
