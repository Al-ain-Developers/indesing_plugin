//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IFlowData.h $
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
#ifndef __IFLOWDATA__
#define __IFLOWDATA__

#include "IPMUnknown.h"
#include "MasterPageID.h"

class PMString;

/**
	IFlowData persists the primary text flow. This interface exists on spreads which
	happen to be master spreads (kMasterPagesBoss), and does not exist on spreads which are not masters (regular kSpreadBoss).
	The document has an IMasterSpreadList which is a list of the document's IMasterSpreads.

	@ingroup layout_spread
	@see kDocBoss
	@see kMasterPagesBoss
	@see kSpreadBoss
	@see ISpread

 */
class IFlowData : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_IFLOWDATA };

	/** GetPrimaryTextFlowStory - Return the primary text flow story for this spread
	 */
	virtual UID GetPrimaryTextFlowStory() const = 0;

	/** SetPrimaryTextFlowStory - Set the primary text flow story for this spread
	 */
	virtual void SetPrimaryTextFlowStory(const UID& primaryFlowStoryRef) = 0;
};

#endif
