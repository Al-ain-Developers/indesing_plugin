//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IWindowSettings.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __IWindowSettings__
#define __IWindowSettings__

#include "IWindow.h"

//========================================================================================
// CLASS IWindowSettings
//========================================================================================

/** Interface responsible for recording/retrieving window size information. This interface is just for bookkeeping so
	we're able to restore windows to their last state after the window is closed and opened again. Only useful on WINDOWS
*/
class IWindowSettings : public IPMUnknown
{
// ----- Accessors
public:
	/**  Record the new window visibility for the app frame window.
		@param state new state we're setting to
	*/
	virtual void SetFrameWindowVisibleState(IWindow::VisibleState state) = 0;
	/**  Retrieve the window visibility state for the app frame window.
		@return state previously recorded state
	*/
	virtual IWindow::VisibleState GetFrameWindowVisibleState() const = 0;

	/**  Record the new window visibility for the document window.
		@param state new state we're setting to
	*/
	virtual void SetDocumentWindowVisibleState(IWindow::VisibleState state) = 0;
	
	/**  Retrieve the window visibility state for the document window.
		@return state previously recorded state
	*/
	virtual IWindow::VisibleState GetDocumentWindowVisibleState() const = 0;

	/**  Record the new window frame for the app frame window.
		@param rect new frame we're setting to
	*/
	virtual void SetAppWindowFrame(const GSysRect& rect) = 0;

	/**  Retrieve the window frame for the app frame window.
		@return the recorded frame
	*/
	virtual GSysRect GetAppWindowFrame() const = 0;
};

#endif
