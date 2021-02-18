//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IDrawOptionOverrides.h $
//  
//  Owner: David Stephens
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
//  Purpose:
//  Allow local overrides on the display setting for drawable page items.
//  
//========================================================================================

#pragma once
#ifndef __IDrawOptionOverrides__
#define __IDrawOptionOverrides__

#include "IPMUnknown.h"
#include "IDrawOptions.h"
#include "GenericID.h"

/** IDrawOptionOverrides
	If the IDrawOptions::GetIgnoreOverrides for the session returns kTrue, then this interface
	is completely ignored.  If GetIgnoreOverrides returns kFalse, then this interface is used to
	apply a drawing preference to a page item and persist that setting.  In most cases, this
	behavior is undesirable because it can lead to extremely bad performance in unexpected
	situations.  For example, image placing a very complex PDF with mixed content and transparency
	and then applying an override to draw the PDF in High Quality mode regardless of the view
	setting.  Then, you save and close the document and either re-open at a later date or give
	the document to someone else.  As soon as the document is opened and the placed PDF is scrolled
	into view (it may already be in view), you will have to wait for InDesign to read the PDF from
	disk into memory, parse it into a display list which our graphics engine can use, and then RIP
	the display list to render it to screen.  All of this reading, parsing and rendering must occur
	before the document is drawn for the first time.  As a result, the user sits wondering what in
	the world is happening during Open that is taking so long.  This behavior used to occur by default
	before InDesign CS.  However, the behavior of local display overrides was changed in CS to not
	be persisted by default.  To persist the overrides, the IDrawOptions::SetIgnoreOverrides must
	be called with a kFalse argument.
	@see IDrawOptions
*/
class IDrawOptionOverrides : public IPMUnknown
{
public:
	/** default IID for this interface
	*/
	enum { kDefaultIID = IID_IDRAWOPTIONOVERRIDE };

	enum OverrideLocation
	{
		 kUseDisplayPreferences = 0,	/** The display preference determines the location of local overrides. @see IDrawOptions */
		 kUsePersistedSetting,			/** Local overrides saved in the document. */
		 kUseInMemorySetting			/** Local overrides in memory that get lost on doc close. */
	};

	/** Set which display option group to use as an override.
		@param displayOption - IN: The override.  Valid values include:
			1. IDrawOptions::kFastGroup
			2. IDrawOptions::kTypicalGroup
			3. IDrawOptions::kHighQualityGroup
			4. IDrawOptions::kUseDefault - removes the override and uses the current view setting instead.
		@param location - IN: Where to set the override.
	*/
	virtual void SetDrawOptionGroup(uint32 displayOption, OverrideLocation location = kUseDisplayPreferences) = 0;

	/** 
		Returns the current override setting.  Valid return values include.
			1. IDrawOptions::kFastGroup
			2. IDrawOptions::kTypicalGroup
			3. IDrawOptions::kHighQualityGroup
			4. IDrawOptions::kUseDefault - Indicates no override.  Page item uses current view setting.
		@param location - IN: Where to get the override.

	*/
	virtual uint32 GetDrawOptionGroup(OverrideLocation location = kUseDisplayPreferences) const = 0;

	/** Returns the actual DrawOptionsSet instead of its ID.
		@param location - IN: Where to get the override.
	*/
	virtual DrawOptionsSet GetDrawOptions(OverrideLocation location = kUseDisplayPreferences) const = 0;
};

#endif
