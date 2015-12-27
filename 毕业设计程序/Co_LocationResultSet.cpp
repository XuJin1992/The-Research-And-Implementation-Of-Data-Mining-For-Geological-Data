/**
 * Created by xujin on 2015/05/22.
   All Rights Reserved£¬but you can use this program.
 */

#include"Co_LocationResultSet.h"

CCo_LocationResultSet::CCo_LocationResultSet()
{
	m_vecResultSet.clear();
}

vector<SCo_LocationResult*> CCo_LocationResultSet::getResultSet()
{
	return m_vecResultSet;
}

void CCo_LocationResultSet::addResult(SCo_LocationResult *tVecResultSet)
{
	m_vecResultSet.push_back(tVecResultSet);
}

int CCo_LocationResultSet::getSize()
{
	return m_vecResultSet.size();
}