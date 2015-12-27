#include<iostream>
#include"RTree.h"
using namespace std;

int main()
{
	CRTree *rTree=new CRTree();
	SRectangle *rect;

	/*
	rect=new SRectangle(0,0,2,2);
	rTree->insert(rect);
	
	rect=new SRectangle(1,1,4,4);
	rTree->insert(rect);

	rect=new SRectangle(2,2,3,3);
	rTree->insert(rect);

	rect=new SRectangle(2,2,6,6);
	rTree->insert(rect);

	rect=new SRectangle(3,3,5,5);
	rTree->insert(rect);
	
	rTree->display();

	rect=new SRectangle(0,0,2,2);
	rTree->erase(rect);
	rTree->display();

	rect=new SRectangle(1,1,4,4);
	rTree->erase(rect);
	rTree->display();

	rect=new SRectangle(2,2,3,3);
	rTree->erase(rect);
	rTree->display();

	rect=new SRectangle(3,3,5,5);
	rTree->erase(rect);
	rTree->display();

	rect=new SRectangle(0,0,2,2);
	rTree->erase(rect);
	rTree->display();
	*/

	/*
	rect=new SRectangle(0,0,2,2);
	rTree->insert(rect);
	cout<<"查找矩形: [（"<<rect->m_LeftBottomX<<","<<rect->m_LeftBottomY<<"),("<<rect->m_RightTopX<<","<<rect->m_RightTopY<<"）]"<<endl;
	rTree->search(rect);
	rTree->display();

	rect=new SRectangle(1,1,4,4);
	rTree->insert(rect);
    cout<<"查找矩形: [（"<<rect->m_LeftBottomX<<","<<rect->m_LeftBottomY<<"),("<<rect->m_RightTopX<<","<<rect->m_RightTopY<<"）]"<<endl;
	rTree->search(rect);
	rTree->display();

	rect=new SRectangle(2,2,3,3);
	rTree->insert(rect);
	cout<<"查找矩形: [（"<<rect->m_LeftBottomX<<","<<rect->m_LeftBottomY<<"),("<<rect->m_RightTopX<<","<<rect->m_RightTopY<<"）]"<<endl;
	rTree->search(rect);
	rTree->display();

	rect=new SRectangle(2,2,6,6);
	rTree->insert(rect);
	cout<<"查找矩形: [（"<<rect->m_LeftBottomX<<","<<rect->m_LeftBottomY<<"),("<<rect->m_RightTopX<<","<<rect->m_RightTopY<<"）]"<<endl;
	rTree->search(rect);
	rTree->display();

	rect=new SRectangle(3,3,5,5);
	rTree->insert(rect);
	cout<<"查找矩形: [（"<<rect->m_LeftBottomX<<","<<rect->m_LeftBottomY<<"),("<<rect->m_RightTopX<<","<<rect->m_RightTopY<<"）]"<<endl;
	rTree->search(rect);
	rTree->display();

	rect=new SRectangle(0,0,7,7);
	rTree->insert(rect);
	cout<<"查找矩形: [（"<<rect->m_LeftBottomX<<","<<rect->m_LeftBottomY<<"),("<<rect->m_RightTopX<<","<<rect->m_RightTopY<<"）]"<<endl;
	rTree->search(rect);
	rTree->display();

	rect=new SRectangle(1,1,5,5);
	rTree->insert(rect);
	cout<<"查找矩形: [（"<<rect->m_LeftBottomX<<","<<rect->m_LeftBottomY<<"),("<<rect->m_RightTopX<<","<<rect->m_RightTopY<<"）]"<<endl;
	rTree->search(rect);
	rTree->display();

	rect=new SRectangle(2,2,7,7);
	rTree->insert(rect);
	cout<<"查找矩形: [（"<<rect->m_LeftBottomX<<","<<rect->m_LeftBottomY<<"),("<<rect->m_RightTopX<<","<<rect->m_RightTopY<<"）]"<<endl;
	rTree->search(rect);
	rTree->display();

		rect=new SRectangle(1,1,8,5);
	rTree->insert(rect);
	cout<<"查找矩形: [（"<<rect->m_LeftBottomX<<","<<rect->m_LeftBottomY<<"),("<<rect->m_RightTopX<<","<<rect->m_RightTopY<<"）]"<<endl;
	rTree->search(rect);
	rTree->display();

	rect=new SRectangle(1,2,9,7);
	rTree->insert(rect);
	cout<<"查找矩形: [（"<<rect->m_LeftBottomX<<","<<rect->m_LeftBottomY<<"),("<<rect->m_RightTopX<<","<<rect->m_RightTopY<<"）]"<<endl;
	rTree->search(rect);
	rTree->display();

	rect=new SRectangle(2,4,7,7);
	rTree->insert(rect);
	cout<<"查找矩形: [（"<<rect->m_LeftBottomX<<","<<rect->m_LeftBottomY<<"),("<<rect->m_RightTopX<<","<<rect->m_RightTopY<<"）]"<<endl;
	rTree->search(rect);
	rTree->display();

		rect=new SRectangle(1,3,8,5);
	rTree->insert(rect);
	cout<<"查找矩形: [（"<<rect->m_LeftBottomX<<","<<rect->m_LeftBottomY<<"),("<<rect->m_RightTopX<<","<<rect->m_RightTopY<<"）]"<<endl;
	rTree->search(rect);
	rTree->display();

	rect=new SRectangle(1,3,9,7);
	rTree->insert(rect);
	cout<<"查找矩形: [（"<<rect->m_LeftBottomX<<","<<rect->m_LeftBottomY<<"),("<<rect->m_RightTopX<<","<<rect->m_RightTopY<<"）]"<<endl;
	rTree->search(rect);
	rTree->display();

	
	rect=new SRectangle(0,0,7,7);
	cout<<"删除矩形: [（"<<rect->m_LeftBottomX<<","<<rect->m_LeftBottomY<<"),("<<rect->m_RightTopX<<","<<rect->m_RightTopY<<"）]"<<endl;
	rTree->erase(rect);
	cout<<"查找矩形: [（"<<rect->m_LeftBottomX<<","<<rect->m_LeftBottomY<<"),("<<rect->m_RightTopX<<","<<rect->m_RightTopY<<"）]"<<endl;
	rTree->search(rect);
	rTree->display();

	rect=new SRectangle(1,0,7,7);
	cout<<"删除矩形: [（"<<rect->m_LeftBottomX<<","<<rect->m_LeftBottomY<<"),("<<rect->m_RightTopX<<","<<rect->m_RightTopY<<"）]"<<endl;
	rTree->erase(rect);
	cout<<"查找矩形: [（"<<rect->m_LeftBottomX<<","<<rect->m_LeftBottomY<<"),("<<rect->m_RightTopX<<","<<rect->m_RightTopY<<"）]"<<endl;
	rTree->search(rect);
	rTree->display();
	
	*/

	
	for(int i=0;i<10;++i)
	{
		for(int j=0;j<10;++j)
		{
			rect=new SRectangle(10-i,j+10,30-i,30-j);
        	rTree->insert(rect);
        	//cout<<"查找矩形: [（"<<rect->m_LeftBottomX<<","<<rect->m_LeftBottomY<<"),("<<rect->m_RightTopX<<","<<rect->m_RightTopY<<"）]"<<endl;
	       // rTree->search(rect);
	       
		}
	}
	// rTree->display();
	/*
	rect=new SRectangle(8,10,28,30);
	  cout<<"删除矩形: [（"<<rect->m_LeftBottomX<<","<<rect->m_LeftBottomY<<"),("<<rect->m_RightTopX<<","<<rect->m_RightTopY<<"）]"<<endl;
	rTree->erase(rect);
  rTree->display();
  */
		for(int j=0;j<10;++j)	
	for(int i=0;i<10;++i)
	{
			rect=new SRectangle(10-i,j+10,30-i,30-j);
			cout<<"删除矩形: [（"<<rect->m_LeftBottomX<<","<<rect->m_LeftBottomY<<"),("<<rect->m_RightTopX<<","<<rect->m_RightTopY<<"）]"<<endl;
			rTree->erase(rect);
	        rTree->display();
	}

	system("pause");
	return 0;
}