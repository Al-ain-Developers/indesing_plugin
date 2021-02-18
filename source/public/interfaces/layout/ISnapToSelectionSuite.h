//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ISnapToSelectionSuite.h $
//  
//  Owner: Paul Sorrick
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
//  Note:
//  
//========================================================================================

#pragma once
#ifndef __ISnapToSelectionSuite__
#define __ISnapToSelectionSuite__

#include "ISnapTo.h"
#include "SpreadUIID.h"

class IDocument;
class ILayoutControlData;

//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________

//================================================================================================
//________________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________________

/** Defines the interface for a snap-to suite to be used in the new selection architecture
	@ingroup layout_suite
*/
class ISnapToSelectionSuite : public IPMUnknown
{
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_ISNAPTOSELECTIONSUITE };

	//____________________________________________________________________________________________
	//	Member functions
	//____________________________________________________________________________________________
	public:
		/**	Is this selection suite enabled? Can SnapToPoint be called?
			@param *document
			@param flags ISnapTo::SnapFlags
			@return bool16 kTrue if enabled, kFalse otherwise
		 */
		virtual bool16 CanDoSnapTo(IDocument *document, SnapFlags flags) const = 0;

		/**	Snap the given point to the selection.
			@param snapTo ISnapTo interface
			@param theView view doing the snapping
			@param thePoint in/out point that might be snapped
			@param theRect 
			@param snapType how thePoint was snapped (one of SnapType enum values)
			@param snapToZone 
			@param layoutData 
			@return  
		 */
		virtual	SnapType SnapToPoint(ISnapTo* snapTo,
				IControlView* theView, 
				PMPoint& thePoint, 
				const PMRect* theRect,
				SnapType snapType, 
				PMReal snapToZone,
				ILayoutControlData* layoutData) = 0;		
};

#endif // __ISnapToSelectionSuite__