//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IMultiStateObjectPrefs.h $
//  
//  Owner: Mitch Coleman
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
#ifndef __IMultiStateObjectPrefs_h__
#define __IMultiStateObjectPrefs_h__

#include "IPMUnknown.h"

#include "FormFieldID.h"

//=============================================================================

class IMultiStateObjectPrefs : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IMULTISTATEOBJECTPREFS };

	/** Indicate whether the multi-state object is initally hidden in interactive export.
		@param inIsInitallyHidden whether to hide the multi-state object initially
	*/
	virtual void SetIsInitiallyHidden(bool16 inIsInitiallyHidden) = 0;

	/** Determine whether the multi-state object is initally hidden in interactive export.
		@return whether the multi-state object is initially hidden
	*/
	virtual bool16 GetIsInitiallyHidden() const = 0;
};

//=============================================================================

#endif // __IMultiStateObjectPrefs_h__

//  IMultiStateObjectPrefs.h.
