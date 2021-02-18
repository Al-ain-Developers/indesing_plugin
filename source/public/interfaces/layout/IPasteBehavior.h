//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPasteBehavior.h $
//  
//  Owner: 
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
#ifndef __IPasteBehavior__
#define __IPasteBehavior__

#include "IPMUnknown.h"
#include "GenericID.h"


class UIDRef;

/**
	This is a call-back interface that provides information used when pasting a page item.
	A page item boss should include this interface if it needs to control how it is pasted
	into another page item.
*/
class IPasteBehavior : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_IPASTEBEHAVIOR};

	/** Tests if the boss aggregating this interface can be pasted into a specified
		target.
		@param pasteInsideSourceScrap valid UIDRef to item that would be pasted.
		@return kTrue if it's OK to paste pasteInsideSourceScrap into this; kFalse if not.
	*/
	virtual bool16 CanPasteInto( UIDRef pasteInsideSourceScrap )  const = 0;
};


#endif //__IPasteBehavior__

