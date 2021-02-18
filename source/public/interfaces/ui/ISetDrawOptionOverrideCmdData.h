//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ISetDrawOptionOverrideCmdData.h $
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
//  Purpose: This Data interface is used to set an object level override of the IDrawOptions
//  on a pageitem.
//  
//========================================================================================

#pragma once
#ifndef __ISetDrawOptionOverrideCmdData__
#define __ISetDrawOptionOverrideCmdData__

#include "IDrawOptionOverrides.h"
#include "GenericID.h"

class DisplayOptionRange
{
public:
	DisplayOptionRange(): fnStart(0), fnCount(0), fnOption(0) {}
	DisplayOptionRange(const DisplayOptionRange& r): fnStart(r.fnStart), fnCount(r.fnCount), fnOption(r.fnOption) {}
public:
	uint32 fnOption;
	int32  fnStart;
	int32  fnCount;
};

/**
 Description:
 This interface is a data interface for the kSetDrawOptionOverrideCmdBoss and is used to set drawing characteristics
 of page items.  Typically, draw options are set on the View and apply to all page items.  However, draw options can
 also be set on individual page items as overrides.  Early versions of InDesign persisted these object level overrides
 such that if you changed a display setting on a page item, closed and re-opened a document, the changed setting was
 still active.  On the surface, this behavior seems appropriate.  However, drawing in high-quality mode can be expensive,
 especially the first time you draw an object.  Therefore, if you opened a document with persisted display overrides on
 1 or more page items, the first draw of the document could be quite slow giving the impression that document Open was
 slow.  So, in later versions of InDesign, this behavior was changed such that the object level display overrides were
 not persisted unless new preference was set to force the overrides to be persisted.
 
 This interface and its associated command are used to set the override options on 1 or more page items.
 
 @see IDrawOptionOverrides.h, IDrawOptions.h
*/
class ISetDrawOptionOverrideCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISETDRAWOPTIONOVERRIDECMDDATA };

	/** Set the display setting on the target page items to one of the draw options defined in IDrawOptions.h 
		such as IDrawOptions::kUseDefault.
	 
		@param displayOption [IN]: 
	 */
	virtual void SetDisplayOption(uint32 displayOption) = 0;	

	/** Get the display option that was set via SetDisplayOption().
	 */
	virtual uint32 GetDisplayOption() const  = 0;	

	/** The option range methods are used to store the values that will be passed to IDrawOptions::SetDrawOptionGroup().
	 */
	virtual void ClearOptionRange() = 0;
	virtual void AppendOptionRange( const DisplayOptionRange& range ) = 0;
	virtual int32 GetOptionRangeCount() const = 0;
	virtual DisplayOptionRange GetNthDisplayOptionRange(int32 n) const = 0;

	/** Accessor for override location. Default is IDrawOptionOverrides::kUseDisplayPreferences. 
		The override location determines if the override is persisted or not.  You can explicitly
		set whether or not it is persisted or allow the command to determine whether or not to 
		persist based on the value of IDrawOptions::GetSaveLocalOverrides() */
	virtual void SetOverrideLocation(IDrawOptionOverrides::OverrideLocation location) = 0;
	virtual IDrawOptionOverrides::OverrideLocation GetOverrideLocation() const = 0;
};

#endif // __ISetDrawOptionOverrideCmdData__