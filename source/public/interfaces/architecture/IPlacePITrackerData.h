//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IPlacePITrackerData.h $
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
#ifndef __IPLACEPITRACKERDATA__
#define __IPLACEPITRACKERDATA__

#include "IPMUnknown.h"
#include "GenericID.h"
#include "PMPoint.h"

class IDocument;

class IPlacePITrackerData : public IPMUnknown
{
	public:
		virtual void Set(IDocument* document, const UIDRef& parent, UID newItem, const PMPointList* initialPoints) = 0;
		virtual IDocument* GetDocument() const = 0;
		virtual const UIDRef& GetParent() = 0;
		virtual UID GetNewItem() = 0;
		virtual const PMPointList* GrabPointList() const = 0;
};


#endif

