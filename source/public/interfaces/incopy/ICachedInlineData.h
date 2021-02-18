//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/ICachedInlineData.h $
//  
//  Owner: Ryan Gano
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
//  Holds a cache of addref'd inline page items. Allows access to the cache by UIDRef.
//  
//========================================================================================

#pragma once
#ifndef __ICachedInlineData__
#define __ICachedInlineData__

#include "IPMUnknown.h"

#include "InCopyWorkflowID.h"

/** Holds a cache of addref'd inline page items. Allows access to the cache by UIDRef.
*/
class ICachedInlineData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICACHEDINLINES };
		

/**	Append the inlineItem to its collection
	@param inlineItem 
	@return  
 */
	virtual void 								Append(const UIDRef& inlineItem) = 0;

/**	Clear its collection
	@param none
	@return  
 */
	virtual void 								Clear() = 0;


/**	Check if item is exist in the collection
	@param item 
	@return bool16 kFalse = item is not in the colleciton
 */
	virtual bool16								Contains(const UIDRef& item) = 0;

/**	Check if the collection is empty
	@param none
	@return virtual kTrue = collectio is empty
 */
	virtual	bool16								IsEmpty() = 0;
};

#endif // __ICachedInlineData__
