//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IDynamicTransformData.h $
//  
//  Owner: Shawn Sheridan
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//  
//  Note:
//  
//========================================================================================

#pragma once
#ifndef __IDynamicTransformData__
#define __IDynamicTransformData__

#include "IPMUnknown.h"
#include "LayoutUIID.h"

class PMMatrix;
class PMPolygon4;
class PMPoint;

class IDynamicTransformData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDYNAMICTRANSFORMDATA};
	
	
	virtual void SetDynamicTransformMatrix( const PMMatrix& m) = 0;
	virtual ErrorCode GetDynamicTransformMatrix( PMMatrix* m) const = 0; //returns kSuccess if matrix was set

	//note that b[0] is left top, b[1] is right top, b[2] is right bottom and b[3] is left bottom
	virtual void SetDynamicTransformBounds( const PMPolygon4& b) = 0;
	virtual ErrorCode GetDynamicTransformBounds( PMPolygon4* b) const = 0; //returns kSuccess if bounds were set

	virtual void SetDynamicTransformLocation( const PMPoint& p) = 0;
	virtual ErrorCode GetDynamicTransformLocation( PMPoint* p) const = 0; //returns kSuccess if location was set

};




#endif // __IDynamicTransformData__

