//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ICloseWinCmdData.h $
//  
//  Owner: Robin_Briggs
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
//  Data interface for the CloseWinCmd.
//  
//========================================================================================

#pragma once
#ifndef __ICloseWinCmdData__
#define __ICloseWinCmdData__

#include "IPMUnknown.h"
#include "DocumentID.h"

class IDocument;
class IWindow;

/**
   This interface is used to get/set window for several close window related commands, 
   e.g., kCloseWinCmdBoss, kCloseDialogCmdBoss.
*/

class ICloseWinCmdData : public IPMUnknown {
public:	
	/**
		Set the window we operate on.

		@param win refers to the window we operate on.
		@return void.
	*/

	virtual void Set(IWindow *win) = 0;

	/**
		Get the window we operate on.

		@return IWindow, the window we operate on.
	*/

	virtual IWindow *GetWindow() const = 0;
};


#endif // __ICloseWinCmdData__
