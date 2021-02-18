//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PathOutlineInfo.h $
//  
//  Owner: Bernd Paradies
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
//========================================================================================

#pragma once
#ifndef __PathOutlineInfo__
#define __PathOutlineInfo__
 
#include "IOutlineInfo.h"
#include "PMPoint.h"
#include "PMPathPoint.h"

class IPathGeometry;
 
#pragma export on

class PUBLIC_DECL PathOutlineInfo : public IOutlineInfo
{
public:
	PathOutlineInfo(IPathGeometry *pPolygon);
	~PathOutlineInfo();
	
	virtual void 		BeginPath();
	virtual void		EndPath();
	
	virtual void 		moveto(const PMReal& x, const PMReal& y);
	virtual void 		lineto(const PMReal& x, const PMReal& y);
	virtual void 		curveto(const PMReal& x1, const PMReal& y1, const PMReal& x2, const PMReal& y2, const PMReal& x3, const PMReal& y3);
	virtual void 		closepath();
	
private:
	void CreateNewPath(const PMPathPoint& pathPt);
	
private:
	IPathGeometry *		fPolygon;
	int32				fCurrentPathIndex;
	bool16				fCurrentPathCreated;
	bool16				fBeginPathCalled;
	PMPathPoint			fLastPt;
	
};

#pragma export off

#endif

