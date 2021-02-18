//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IToolChangeSuite.h $
//  
//  Owner: Danielle Bessette
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
//  Note:	This is the suite called when a tool in the tool box is changed
//  It gives the different selections a chance to update themselves to the new tool
//  
//========================================================================================

#pragma once
	#ifndef __IToolChangeSuite__
	#define __IToolChangeSuite__
//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________
	#include "IPMUnknown.h"
	#include "ShuksanID.h"
//________________________________________________________________________________________
//	CLASS FORWARDS
//________________________________________________________________________________________
	class ITool;
	class IControlView;
	class ISelectionManager;
/** 
	The suite notified when a tool changes in the tool panel
	@ingroup layout
*/
class IToolChangeSuite : public IPMUnknown
	{
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_ITOOLCHANGESUITE };

	//____________________________________________________________________________________________
	//	Member functions
	//____________________________________________________________________________________________
	public:
		/**
			Called when a tool changes so the selection can be updated for the new tool
			@param	changedTool		The ITool that changed
			@param 	view				The current IControlView
		*/
		virtual void			ToolChanged(ITool *changedTool, IControlView *view) const = 0;

		/**
			Called when the selection is restored after undo or redo and it may need to further be changed
			to adjust to the active tool.
			@param	activeTool			The active ITool 
			@param 	selectionManager	The selection manager associated with the view.
		*/
		virtual void			MatchSelectionWithTool(ITool *currentTool,ISelectionManager *selectionManager) const = 0;
};

#endif // _IToolChangeSuite_
