//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ISelectionDataSuite.h $
//  
//  Owner: Michael Martz
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
	#ifndef _ISelectionDataSuite_
	#define _ISelectionDataSuite_
//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________
	#include "IPMUnknown.h"
	#include "ShuksanID.h"
	#include "PMRect.h"
//================================================================================================
	class IControlView;
//________________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________________

/** Provides interface to return information about any type of selection.
*/
class ISelectionDataSuite : public IPMUnknown
	{
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_ISELECTIONDATASUITE };

	//____________________________________________________________________________________________
	//	Member functions
	//____________________________________________________________________________________________
	public:
		/**	Calculate the bounds of the selection in Pasteboard coordinates
			@param iLayoutControlView The IControlView to calculate.
			@return Rect of selection. May return an empty rect (kEmptyRect).
		 */
		virtual PBPMRect CalculatePBSelectionBounds (IControlView* iLayoutControlView) const = 0;

		/**	Calculate the bounds of the selection in View coordinates
			@param iLayoutControlView The IControlView to calculate.
			@return Rect of selection. May return an empty rect (kEmptyRect).
		 */
		virtual PMRect CalculateViewSelectionBounds (IControlView* iLayoutControlView) const = 0;

		/**	Calculate the SysRgn of the selection (view coordinates)
			@param iLayoutControlView The IControlView to calculate.
			@return SysRgn of the selection.
		 */
		virtual SysRgn GetSelectionRgn (IControlView* iLayoutControlView) const = 0;

		/**	Calculate the center point of the selection in Pasteboard coordinates. 
			Note: This returns the actual center of the selection, not necessarily
		    the center of the PMRect returned above
			@param iLayoutControlView IControlView to calculate.
			@return Center Point of selection.
		 */
		virtual PBPMPoint CalculatePBCenterPoint (IControlView* iLayoutControlView) const = 0;

		/**	Calculate the center point of the selection in View coordinates
			@param iLayoutControlView The IControlView to calculate.
			@return Center Point of selection.
		 */
		virtual PMPoint CalculateViewCenterPoint (IControlView* iLayoutControlView) const = 0;

		/**	For the pageitem passed in, determine whether there's a selection
			associated with it.  This routine is used more or less privately by
			the hit-test code, which needs (in SelectionHitTestHandler) to know
			whether an item hit is also selected.  NOT MEANT TO REPLACE A PROPERLY-	
			WRITTEN SUITE for handling selection tasks or queries.
			@param theItem 
			@return kTrue if item is selected, kFalse otherwise.
		 */
		virtual bool16 IsItemSelected(IPMUnknown* theItem) const = 0;

		/**	Determine whether there's a selection associated with it.  
			@return kTrue if there is a selection; kFalse if there is not.
		 */
		virtual bool16 HasItemSelected() const = 0;

		/**	Return a count for the selection. 
			@return \li For layoutCSB, this is a number of selected page items (with kStripStandoffs). 
				\li For textCSB, length of range of selection.
				\li If unknown, or doesn't apply, returns -1.
		 */
		virtual int32 GetSelectionCount() const = 0;
	};

#endif // _ISelectionDataSuite_
