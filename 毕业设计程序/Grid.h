/**
 * Created by xujin on 2014/12/1.
   All Rights Reserved，but you can use this program.
 */

#ifndef GRID_H
#define GRID_H

#include"Rectangle.h"

#include<vector>
#include<string>
#include<iostream>
#include<fstream>
using namespace std;

class CGrid
{
private:
	//非空间属性
	vector<string> m_vecItem;
	//空间属性
	SRectangle *m_pSRect;

public:
	CGrid(SRectangle *tpSRect,vector<string>& tVec);
	CGrid(SRectangle *tpSRect);
	CGrid();
	CGrid(vector<string>& tVec);

	void addItem(string tItem);
	bool isContain(vector<string>& tVec);
	vector<string>& getVecItem();
	void print(ofstream &ofFile);
	SRectangle *getSRectangle();

};


#endif