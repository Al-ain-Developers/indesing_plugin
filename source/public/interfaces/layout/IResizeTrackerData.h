//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IResizeTrackerData.h $
//  
//  Owner: Lonnie Millett
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
#ifndef __IRESIZETRACKERDATA__
#define __IRESIZETRACKERDATA__

#include "PMTypes.h"
#include "IHandleShape.h"

//----------------------------------------------------------------------------------------
// Forward Declarations
//----------------------------------------------------------------------------------------

class UIDList;

//----------------------------------------------------------------------------------------
// IResizeTrackerData:
//----------------------------------------------------------------------------------------

class IResizeTrackerData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IRESIZETRACKERDATA };

		virtual void Set(UIDList* itemList, const PointSelector& selectionHandleID, bool16 hideOriginal = kTrue) = 0;
		virtual UIDList* GetItemList() const = 0;
		virtual const PointSelector& GetHandleID() const = 0;
		virtual bool16 GetHideOriginal() const = 0;
};

#endif