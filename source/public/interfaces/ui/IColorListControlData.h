//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IColorListControlData.h $
//  
//  Owner: Ryan Gano
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
#ifndef __IColorListControlData_h__
#define __IColorListControlData_h__

#include "widgetid.h"

//========================================================================================
// CLASS TEMPLATE IColorListController
//========================================================================================

class IColorListControlData : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_ICOLORLISTCONTROLDATA };
	typedef enum { kIncludeCustom = 0, kColorsOnly } IncludeCustom;

	// Initialization	
	/**	Fill in the list box using the correct color list
		@param workspace - workspace that the color list is in
		@param whichInterface - The color list to use (IID_IUICOLORLIST or IID_ISWATCHLIST)
		@param kIncludeCustom - Include an entry for a custom color?
		@param selectedColor - UID of the default color to select
		@return none
	 */
	virtual void		Setup(UIDRef workspace, PMIID whichInterface, IncludeCustom customOption = kIncludeCustom, UID selectedColor = kInvalidUID) = 0;

	/**	Select a particular color
		@param whichColor - UID of the color to select (kInvalid will select nothing in the list)
		@return none
	 */
	virtual void		Select(UID whichColor, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue) = 0;

	// Accessors
	/**	Has the color list been initialized yet?  If the list has been initialized we
		don't need to intialize it again.
		@param workspace - UIDRef of the document this should have been setup for 
		@return bool16 - kTrue means the widget has been setup
	 */
	virtual bool16		IsSetup(UIDRef workspace = UIDRef::gNull) const = 0;

	/**	Get the UID of the selected color
		@param none
		@return UID - UID of the selected color
	 */
	virtual UID			GetSelection() const = 0;

	
	/** Adds an "(Ignore)" entry to end of list, if none exists already
		@param none
	*/
	virtual void 		AddIgnore() const = 0;

	/** Removes "(Ignore)" entry, if in list
		@param none
	*/
	virtual void 		RemoveIgnore() const = 0;

	/** Adds "[Unnamed Color]" entry to the end of the list if one doesn't already exist
		@param UIDRef	the ref of the unnamed color
	*/
	virtual void 		AddUnnamed(UIDRef swatchRef) const = 0;		

	/** Removes "[Unnamed Color]" entry to the end of the list if one doesn't already exist
		@param none
	*/
	virtual void 		RemoveUnnamed() const = 0;		
};

#endif // __IColorListControlData_h__
