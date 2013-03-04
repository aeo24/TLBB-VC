// Location.h: interface for the Location class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOCATION_H__C980EEA4_BA6D_48CE_B488_E5F61AC10464__INCLUDED_)
#define AFX_LOCATION_H__C980EEA4_BA6D_48CE_B488_E5F61AC10464__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Location
{
public:
	double DistanceToSelf();
	double DistanceFrom(Location pos);
	Location(void);
	virtual ~Location(void);

	float X;
	float Y;
	float Z;
	
	Location(float x,float y,float z);
	
	double DistanceFrom(float nX,float nY,float nZ);
};


#endif // !defined(AFX_LOCATION_H__C980EEA4_BA6D_48CE_B488_E5F61AC10464__INCLUDED_)
