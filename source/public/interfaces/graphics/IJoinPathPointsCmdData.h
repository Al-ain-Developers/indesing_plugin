//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IJoinPathPointsCmdData.h $
//  
//  Owner: Shengliu Dai
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//  
//  Purpose:
//  Specifies the points for joining two end points of paths.
//  
//========================================================================================

#pragma once
#ifndef __IJoinPathPointsCmdData__
#define __IJoinPathPointsCmdData__

#include "IPMUnknown.h"
#include "SplineID.h"
#include "PathTypes.h"

class IJoinPathPointsCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IJOINPATHPOINTSCMDDATA };

	/**
		Define join method. kJoin means two end points is very close and the resulting
		point will replace the two end points, kConnect means connect these two
		end point with a line.
		In both cases, two path becomes one and the 2nd is deleted.
	*/
	typedef enum { 
		kJoin,
		kConnect
	} JoinMethod;

   /**  Set Join Path point command data
        @param method Join method defined above (either kJoin or kConnect)
        @param endPoints List of end point to join 
     */
  	virtual void Set (PointSelectorList endPoints, JoinMethod method = kJoin) = 0;


	/** GetJoinMethod
        @param none
        @return  the joining method
     */
 	virtual JoinMethod GetJoinMethod() const = 0 ;

	/** GetEndPoints
        @param none
        @return  the EndPoint list
     */
	virtual PointSelectorList GetEndPoints() const = 0 ;

};

#endif	// __IJoinPathPointsCmdData__
