//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ISpreadHistoryData.h $
//  
//  Owner: tommyd
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
#ifndef __ISPREADHISTORYDATA__
#define __ISPREADHISTORYDATA__

#include "IPMUnknown.h"
#include "SpreadHistoryID.h"

/** ISpreadHistoryData is an interface off the layout widget (kLayoutWidgetBoss) which
	contains a stack history of page turns for a given layout.
	This list is not persistent.
	@ingroup layout_history
	@see kLayoutWidgetBoss
	@see kSpreadBoss

*/
class ISpreadHistoryData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISPREADHISTORYDATA };

	enum { kAtTheEnd = -1 };

	virtual void AddSpread(UID spreadUID, UID pageUID = kInvalidUID) = 0;
		//	Put the given spread in the stack. If the pageUID is specified,
		//	save the page within the spread too. (SetPageCmd case).

	virtual void ClearAllSpreads() = 0;
		//	Removes all the spreads from the stack

	virtual void ClearThisSpread(UID theUID) = 0;
		//	This method walks from the current stack position
		//	to the top of the stack, and if it finds this spread (or page),
		//	it removes that spread and every spread above it.
		//	It then walks from the current stack position to the bottom
		//	of the stack, repeating the process.

	virtual void GoBack(UID* spreadUID, UID* pageUID) = 0;
		//	Returns the UID of the 'Go Back' spread and page & updates
		//	internal stack pointer
		
	virtual void GoForward(UID* spreadUID, UID* pageUID) = 0;
		//	Returns the UID of the 'Go Forward' spread and page & updates
		//	internal stack pointer
		
	virtual bool16 EnableGoBack() = 0;
		//	Returns TRUE if the 'Go Back' command should be enabled
		
	virtual bool16 EnableGoForward() = 0;
		//	Returns TRUE if the 'Go Forward' command should be enabled
		
	virtual void SetStackSizeLimit(int32 stackSizeLimit) = 0;
		//	Sets the maximum allowed number of items stored in the
		//	stack. If the stack hits this limit, the oldest items
		//	will be dropped off the bottom. We default to 100.

};


#endif // __ISPREADHISTORYDATA__

