//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IDropDownListOpenCloseHandler.h $
//  
//  Owner: Dave Burnard
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
#ifndef __IDropDownListOpenCloseHandler_h__
#define __IDropDownListOpenCloseHandler_h__

#include "IPMUnknown.h"
#include "widgetid.h"

//========================================================================================
// CLASS IDropDownListOpenCloseHandler
//
//	Attach this interface to a DropDownList boss, to add behavior just before the dropdown opens
//		and/or just after it closes. These methods are called from the DVDropDownListView impl.
//
//
//	In CS5 and earlier this customization was accomplished with a custom IEventHandler override 
//		that had to catch the platform menu opening and closing events, and then called 
//		the event handler's customized PrepForShowControl or PrepForCloseControl methods. 
//========================================================================================

class IDropDownListOpenCloseHandler : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_IDROPDOWNLISTOPENCLOSEHANDLER };

	/** DropDown is about to open.	
		@return none
	*/

	virtual void		HandlePreOpenDropDown() = 0;
	
	/** DropDown has just closed.	
		@return none
	*/

	virtual void		HandlePostCloseDropDown() = 0;
};

#endif