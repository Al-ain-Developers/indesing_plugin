//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IMakeNewSelectionSuite.h $
//  
//  Owner: Kevin Van Wiel
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
//  ADOBE CONFIDENTIAL
//  
//  Used to create an initial selection when none exists already. Only necessary when creating a
//  window initially usually. Otherwise use the IGenericTextSelectionSuite or ICTextNavigationSuite.
//  Unlike most suites which will not be queryable when there is no selection this one is available
//  in the no selection state. 	
//  
//========================================================================================

#pragma once
#ifndef __IMakeNewSelectionSuite__
#define __IMakeNewSelectionSuite__

//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________
#include "ShuksanID.h"
#include "IPMUnknown.h"
#include "WritingModeUIID2.h"
#include "WritingModeID2.h"


/** 
	The purpose of this interface is to create an initial selection in a galley or story view when none
	exists. The necessity of this is a side effect of the implementation of the selection code for
	galley/story view which will be eliminited at which point the need for this interface will also go
	away.
*/
class IMakeNewSelectionSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IMAKENEWSELECTIONSUITE };

	/**
		Activate a selection for a story visible in a story or galley view. Activates the selectionsuite.
		@param storyRef - uid reference to a story being displayed in the story view the initial selection will be set to text index 0.
		@return none
	**/
	virtual bool16 	InitializeSelection(const UIDRef& storyRef) = 0;
};

#endif // __IMakeNewSelectionSuite__
