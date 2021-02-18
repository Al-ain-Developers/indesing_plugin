//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ILinkedStoryModificationState.h $
//  
//  Owner: lance bushore
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
#ifndef __ILinkedStoryModificationState__
#define __ILinkedStoryModificationState__

#include "IPMUnknown.h"
#include "TextID.h"

/** This interface records information about whether or not a story has been modified after being imported from an external file/resource.
*/
class ILinkedStoryModificationState : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILINKEDSTORYMODIFICATIONSTATE };
		
	/** 	Records the current state as 'unmodified'
	*/
	virtual void SetCurrentStateAsUnmodified() = 0;
	
	/** 	Return true if the text is unmodified since import
	*/
	virtual bool16 IsTextStateUnmodified() const = 0;

	/** 	Return true if the text attributes are unmodified since import
	*/
	virtual bool16 IsAttributeStateUnmodified() const = 0;

	/** 	Return true if the non-text, non-attribute state is unmodified since import
	*/
	virtual bool16 IsOtherStateUnmodified() const = 0;
};


#endif // __ILinkedStoryModificationState__
