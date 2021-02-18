//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPathSelectionData.h $
//  
//  Owner: Paul Sorrick
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
#ifndef __IPATHSELECTIONDATA__
#define __IPATHSELECTIONDATA__

#include "IPMUnknown.h"
#include "PathTypes.h"
#include "LayoutUIID.h"

/**
	Data interface for passing/storing a single path point selection.
*/
class IPathSelectionData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IPATHSELECTIONDATA } ;

		/** Set the selected path point */
		virtual void Set(const UIDRef& item, const PointSelector& handle) = 0;
		/** Clear the selection data */
		virtual void Clear() = 0;

		/** Get the item */
		virtual const UIDRef& GetItem() const = 0;
		/** Get the selected path point */
		virtual const PointSelector& GetHandle() const = 0;
};

#endif	// __IPATHSELECTIONDATA__
