//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IPanelMover.h $
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
#ifndef __IPanelMover__
#define __IPanelMover__

class IControlView;
class IWindow;
class IPanelControlData;

#include "widgetid.h"
#include "IPMUnknown.h"
#include "PMPoint.h"

/** Utility interface for moving panels between windows. 
		This is an ancient interface once used by the floating palette code, that is now used in a few isolated cases (see CDialog).
		IPanelMover should be used use the via the UtilsBoss, see Utils.h.
		Clients must call SetPanelToMove first, and then the operation to perform.
		This code can not be used to move panels between palettes and palette specific methods have been removed.

		Utils<IPanelMover>()->SetPanelToMove( myControlView );
		Utils<IPanelMover>()->...
		
		@see IPanelMgr, IPaletteControlData
*/
class IPanelMover : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPANELMOVER };

	/** Set the panel that subsequent calls will work with and returns the previously set panel.
			Caller should restore the previous panel after using IPanelMover.

		@param thePanel IN panel to operate on
		@return the previously set panel
	*/
	virtual IControlView* SetPanelToMove(IControlView *thePanel) = 0;
	
	/** Move the panel to the specified window. Delete panel's former palette if it becomes empty as a result.

		@param theWindow IN the target window
		@param adjustWindowAccordingly IN if set, open the destination window
		@param controlViewID IN widget ID of the "tab area" widget, if present. Ugh.
		@precondition caller must have called SetPanelToMove to specify the "current" panel.
	*/
	virtual void MoveToWindow(IWindow *theWindow, bool16 adjustWindowAccordingly = kTrue, int32 controlViewID = 0) = 0;
	
	/** Size a palette window to fit the panels it contains

		@param theWindow IN the palette window
	*/
	virtual void SizeWindowToFit(IWindow *theWindow) = 0;

};

#endif
