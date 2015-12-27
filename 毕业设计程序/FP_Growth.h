/**
 * Created by xujin on 2014/12/4.
   All Rights Reserved£¬but you can use this program.
 */
#ifndef FP_GROWTH_H
#define FP_GROWTH_H

#include"Grid.h"
#include"GridSet.h"
#include"FP_Tree.h"

#include<fstream>
using namespace std;

class CFP_Growth
{
public:
	static ofstream g_ofFP_GrowthResult;

private:
	CFP_Tree *m_pCFPTConditionTree;

private:
	void initCFP_Growth(CFP_Tree *tCFPTTree,vector<ItemSupport>& tItemSupportSet);	
	void printOneFreSet(vector<ItemSupport> &tItemSupportSet);
	void findCombine(CFP_TreeNode *tRoot,vector<ItemSupport> &tItemSupportSet);

public:
	CFP_Growth(CFP_Tree *tCFPTTree,vector<ItemSupport>& tItemSupportSet);
	void printPath();
	void printItemHeaderList();
};

#endif