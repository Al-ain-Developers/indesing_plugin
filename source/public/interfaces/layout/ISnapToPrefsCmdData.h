//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ISnapToPrefsCmdData.h $
//  
//  Owner: psorrick
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
//  Data interface for SnapTo prefs commands.
//  includes : 	SnapTos drawn in front or back
//  
//========================================================================================

#pragma once
#ifndef __ISnapToPrefsCmdData__
#define __ISnapToPrefsCmdData__

#include "IPMUnknown.h"
#include "SpreadID.h"
#include "UIDRef.h" 
#include "PMReal.h"

class IDataBase;

class ISnapToPrefsCmdData : public IPMUnknown
{
public:
	virtual void Set(	const	UIDRef&	doc, 			/* which document to affect */
								bool16	snapGuides,		/* ruler, column and margin SnapTo */
								bool16	snapGrid,	 	/* grid SnapTo */
						const	PMReal& zone) = 0;		/* Snap to zone */
	virtual const UIDRef& GetDocument() const = 0;
	virtual const bool16 GetSnapToGuides() const = 0;
	virtual const bool16 GetSnapToGrid() const = 0;
	virtual const PMReal& GetSnapToZone() const = 0;
};


#endif // __ISnapToPrefsCmdData__
