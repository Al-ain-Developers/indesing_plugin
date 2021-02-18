//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IInCopyViewPrefs.h $
//  
//  Owner: Matt Joss
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
#ifndef __IInCopyViewPrefs__
#define __IInCopyViewPrefs__

#include "WritingModeUIID2.h"
#include "WritingModeID2.h"
#include "IPMUnknown.h"

/** 
	An interface the will keep track of which tab is active in the main document window for InCopy
*/
class IInCopyViewPrefs : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IINCOPYVIEWPREFS };

	/** 
		A value for each of the possible active tabs
	*/
	typedef enum { 
		/** Galley tab */
		kGalley, 
		/** Story tab */
		kStory, 
		/** Layout tab */
		kLayout 
	} ActiveView;
	
	/**
		Get the current active tab for a view
		@return one of the ActiveView enum values above corresponding to which is currently active.
	**/
	virtual	ActiveView					GetActiveView() const = 0;
	
	/**
		Set the current active tab. Normally you wouldn't call this directly, it would be triggered from a call
		to SetDocWindowView() in IGalleyUtils.
		@param activeView - tab to activate.
		@return none.
	**/	
	virtual	void						SetActiveView(ActiveView activeView) = 0;
};


#endif
