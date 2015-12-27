#ifndef RECTANGLE_H
#define RECTANGLE_H

struct SRectangle
{
	int m_RightTopX,m_RightTopY;
	int m_LeftBottomX,m_LeftBottomY;
	SRectangle(int tLeftBottomX,int tLeftBottomY,int tRightTopX,int tRightTopY)
	{
		m_LeftBottomX=tLeftBottomX;
		m_LeftBottomY=tLeftBottomY;
	    m_RightTopX=tRightTopX;
		m_RightTopY=tRightTopY;
	}
};

#endif
