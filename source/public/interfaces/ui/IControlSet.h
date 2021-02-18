//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IControlSet.h $
//  
//  Owner: Dave Burnard (was Daniel Guenther)
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
#ifndef __IControlSet__
#define __IControlSet__

#include "PMTypes.h"
#include "K2Vector.h"
#include "ShuksanID.h"

class IControlView;

//========================================================================================
// CLASS IControlSet

/** Interface that represents a set of controls, one or more of which can be visible at a time.
		IControlSet is typically used to manage different appearances of the same UI, for example the
		large and small row versions of list boxes. Another example is the progressive disclosure used
		by some palettes.
		
		There are subclasses for horizontal and vertical orientations (kControlSetHorzImpl, kControlSetVertImpl).
*/
//========================================================================================
class IControlSet : public IPMUnknown
{
public:
		enum { kDefaultIID = IID_ICONTROLSET };

		/** Get the count of visible control sets */
		virtual int32		VisibleSetCount() = 0;
		/** Get the total count of control sets */
		virtual int32		TotalSetCount() = 0;
		/** Show the specified control sets */
		virtual void		ShowSets(K2Vector<int32>) = 0;
		/** Show the currently visible control sets */
		virtual void		ShowSets() = 0;
		/** Initialize the control set's view. */
		virtual void		Initialize( bool16 bCreateMenuButton = kFalse ) = 0;
		/** Is the control set customizeable - only possible for InCopy. */
		virtual bool16		IsCustomizable() = 0;

		/** Get a list of the visible control sets (by index).
			@param sets OUT the list to put the visible sets in.
		*/
		virtual void		GetVisibleControlSets (K2Vector<int32>& sets) const = 0;
		
		/** Set the visible control sets to those in a list (by index) - called after customize dialog finishes. 
			@param sets IN the list to set as visible.
		*/
		virtual void		SetVisibleControlSets (K2Vector<int32> sets) = 0;
		
		/** Set the visible control sets to whatever is currently visible. */
		virtual void		ResetVisibleControlSets () = 0;

		/** Return the nth control set (not necessary the same as the nth control view due to separator widgets). */
		virtual IControlView*	GetNthControlSet(const int32 index) const = 0;

};


#endif
