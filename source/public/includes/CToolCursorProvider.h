//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CToolCursorProvider.h $
//  
//  Owner: Lonnie Millett
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
#ifndef __CToolCursorProvider__
#define __CToolCursorProvider__

#include "CCursorProvider.h"

#include "IControlView.h"
#include "ISnapTo.h"

#pragma export on

/** Basic implementation of a cursor provider used by a toolbox tool.  
		CToolCursorProvider provides the default behavior for handling special keys
		in the toolbox and giving the apperance of changing tools.
		Tool implementors can derive their tool cursor providers either from this or from ICursorProvider.

		@see ICursorProvider
*/
class WIDGET_DECL CToolCursorProvider : public CCursorProvider
{
	public:
		/** Dynamic cursor support for the selection cursor. */
		static CursorSpec GetSelectionCursor(IControlView* viewUnderMouse, const SysPoint globalLocation, ICursorMgr::eCursorModifierState modifiers);
		/** Dynamic cursor support for the direct selection cursor. */
		static CursorSpec GetDirectSelectionCursor(IControlView* viewUnderMouse, const SysPoint globalLocation, ICursorMgr::eCursorModifierState modifiers);

		CToolCursorProvider(IPMUnknown* boss);
		~CToolCursorProvider();
		
		/** Default behavior:  Returns kTrue unless modifiers for zoom cursor or open hand cursor are down. */
		bool16	HasLockedState() const;

		/** Default behavior:  handles zoom cursor, open hand cursor, pointer tool toggling, and dynamic selection cursors. */
		virtual CursorSpec	GetCursor(IControlView* viewUnderMouse, const SysPoint globalMouse, ICursorMgr::eCursorModifierState modifiers) const;
		
		using CCursorProvider::GetCursor; // needed to defeat C++ name lookup rules, so that we can find the other function with the same name in the base class.
		
		/** Default behavior: returns kTrue */
		virtual bool16	ModifiersAffectCursor(SysRgn cursorRgn) const;


	protected:
		/** Default behavior: basic tool cursor snapping.
				Called from certain tool trackers to do a snap to on the global mouse point. 
				Will use the view provided to find the ISnapTo interface, and will use the SnapFlags. 
				Used from the creation tool cursor providers and the place tool cursor providers to give better feedback to the user before the mouse is pressed. 
				The type of snapping performed is returned, and may be used to change the cursor.

			@param globalLocation IN global mouse point
			@param modifiers IN event modifiers
			@param layoutView IN active layoutView
			@param snapFlags IN what sort of snapping to perform
			@return what type of snapping (none, X, Y, both).
		*/
		virtual SnapType SnapCursor(const SysPoint globalLocation, ICursorMgr::eCursorModifierState modifiers, IControlView* layoutView, SnapFlags snapFlags = ISnapTo::kSnapAllPageMarks) const;
};

#pragma export off

#endif
