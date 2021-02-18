//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CCursorProvider.h $
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
//  
//  Provides a starting point creating cursor providers.
//  
//========================================================================================

#pragma once
#ifndef __CCursorProvider__
#define __CCursorProvider__

#include "ICursorProvider.h"
#include "HelperInterface.h"
#include "CursorSpec.h"

#pragma export on

/** Basic implementation of the ICursorProvider interface, representing the connection between a region on the screen and the cursor to be used when withing that region.
		Implementors of ICursorProvider should either derive from either this, or just use SimpleCursorProvider.

		@see ICursorProvider, SimpleCursorProvider
 */
class WIDGET_DECL CCursorProvider : public ICursorProvider
{
	public:
		CCursorProvider(IPMUnknown* boss);
		~CCursorProvider();
		
		/** Default behavior: returns kCrsrPointer */
		virtual CursorSpec	GetCursor(IControlView* viewUnderMouse, const SysPoint globalLocation, ICursorMgr::eCursorModifierState modifiers) const;

		/** Default behavior: returns kFalse */
		virtual bool16	LocationAffectsCursor(SysRgn cursorRgn) const;

		/** Default behavior: returns kFalse */
		virtual bool16	ModifiersAffectCursor(SysRgn cursorRgn) const;

		/** Default behavior: returns kTrue */
		virtual bool16	HasLockedState() const;
			
		/** Default behavior: does nothing.  In debug builds, this asserts when called unless overridden.
				The SimpleCursorProvider implementation is intended for providers involving only a single cursor.
		*/
		virtual void SetSingleCursor(const CursorSpec&);
			
	private:
		DECLARE_HELPER_METHODS()
};

#pragma export off

#endif // __CCursorProvider__
