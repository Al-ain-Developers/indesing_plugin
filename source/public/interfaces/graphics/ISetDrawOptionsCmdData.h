//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ISetDrawOptionsCmdData.h $
//  
//  Owner: Dave Stephens
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
//  Purpose: This Data interface is used to pass Draw options for a given set
//  to the SetDrawOptionsCmd.
//  
//========================================================================================

#pragma once
#ifndef __ISetDrawOptionsCmdData__
#define __ISetDrawOptionsCmdData__

#include "IDrawOptions.h"
#include "IPMUnknown.h"

/**
	ISetDrawOptionsCmdData

	This class is used to apply or clear display option overrides on page items.  Overrides can be persistent
	(not recommended) or non-persistent (recommended).
*/
class ISetDrawOptionsCmdData : public IPMUnknown
{
public:
	/**
		enum flags
	*/
	enum SetDrawOptionsSetFlags
	{
		kSetSaveLocalOverrides = 0x01
	};

public:
	/**
		Add or replace a DrawOptionsSet to the list of DrawOptionsSets stored in the Session workspace.
		Note: CALLING THIS ROUTINE IS OPTIONAL IF ALL YOU WANT TO DO IS SET THE IGNORE FLAG.

		@param	set	- IN: The new set of draw options.
		@param	isDefault - IN: kTrue to use this set as the default set of draw options for new windows.
	*/
	virtual void SetSet(DrawOptionsSet set, bool8 isDefault) = 0;	
	
	/**
		SetIgnore	Set the "Ignore Local Overrides" setting.  When kTrue, local overrides (stored in a page item's
		IDrawOptionOverrides interface) will be ignored.
		Note: YOU MUST CALL THIS METHOD TO GUARANTEE THAT THE IGNOREOVERRIDES SETTINGS IS CORRECT.
	
		@param	ignoreOverrides - IN: kTrue to ignore local display overrides (set from the Object->Display Performance menu).
	*/
	virtual void SetIgnore(bool8 ignoreOverrides) = 0;

	/**	
		@param	save - IN: kTrue to persist local display overrides on page items.  Not recommended as it can
		dramatically slow down the time it takes to open and navigate through a document.
	*/
	virtual void SetSaveLocalOverrides(bool8 save) = 0;
	
	
	/**	
		@param	set - IN: Pointer to a valid DrawOptionsSet.
		@return	Returns kTrue if SetSet was previously called.  Returns kFalse if SetSet was never called.
	*/
	virtual bool8 GetSet(DrawOptionsSet *set) const  = 0;
																
	/**	
		Returns whether the set returned via GetSet the default view set.
	*/
	virtual bool8 IsDefault(void) const = 0;				

	/**	
		Returns	kTrue if local display setting overrides on page items should be ignored.  That is,
		are we ignoring local overrides?
	*/
	virtual bool8 DoIgnore(void) const = 0;					// Are we ignoring local overrides?

	/**	
		Returns whether	we are persisting local overrides
	*/
	virtual bool8 DoSaveLocalOverrides() const = 0;

	/**	
		Obsolete.  Serves no useful purpose.
	*/
	virtual SetDrawOptionsSetFlags GetSetFlags() const = 0;
};

#endif // __ISetDrawOptionsCmdData__