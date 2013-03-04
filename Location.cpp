// Location.cpp: implementation of the Location class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thunder3.h"
#include "Location.h"
#include <math.h>
#include "GlobalFunc.h"
#include "classes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Location::Location(void)
{
}

Location::Location( float x,float y,float z )
{
	X=x;
	Y=y;
	Z=z;
}

Location::~Location(void)
{
}

double Location::DistanceFrom( float nX,float nY,float nZ )
{
	float dis=(this->X-nX)*(this->X-nX)+(this->Y-nY)*(this->Y-nY)+
		(this->Z-nZ)*(this->Z-nZ);
// 	double x=1.0;
// 	while (x*x-dis<-0.00001||x*x-dis>0.00001)
// 	{
// 		x=(dis/x+x)/2.0;
// 	}
// 	return x;
	return sqrt(dis);
}

double Location::DistanceFrom(Location pos)
{
	return this->DistanceFrom(pos.X,pos.Y,pos.Z);
}

double Location::DistanceToSelf()
{
	try
	{
		return this->DistanceFrom(GetMyPlayer().loc());
	}
	catch(...)
	{
		return 0;
	}
}
