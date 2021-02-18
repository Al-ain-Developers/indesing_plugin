//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IMotionPresetMgr.h $
//  
//  Owner: SusanCL
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
#ifndef __IMotionPresetMgr__
#define __IMotionPresetMgr__

#include "DynamicDocumentsID.h"
#include "IPMUnknown.h"

class IMotionPresetData;

/**
	This is the main interface for InDesign animation presets. This interface sits on the application or document workspace boss. 
*/
class IMotionPresetMgr : public IPMUnknown
{	
public:

	enum { kDefaultIID = IID_IMOTIONPRESETMANAGER };

	/** Returns the number of motion presets in the list.
		@return The number of motion presets.
	*/
	virtual int32 		GetNumPresets() const = 0;

	/** Obtains the name of the Nth preset.
		@param index IN The index of the preset you're interested in.
		@param pName OUT Receives the name of the preset.
		@return An error code or kSuccess if successful.
	*/
	virtual ErrorCode   GetNthPresetName (int32 index, PMString& pName) const = 0;

	/** Get the description of the Nth preset.
		@param index IN The index of the preset you're interested in.
		@param pDesc OUT Receives the description of the preset.
		@return An error code or kSuccess if successful.
	*/
	virtual ErrorCode	GetNthPresetDescription (int32 index, PMString *pDesc) const = 0;

	/** Get the UID of the Nth preset object.  From this you can get/set the 
		client items.  Note that this only is used by preset lists that use UIDList-based storage.

		@param index IN The style to obtain the UIDRef for.
		@return The UIDRef of the style.
	*/
	virtual UID GetNthPresetUID (int32 index) const = 0;

	/** Returns true if the nth preset is an InDesign default preset.
		@param index the nth preset
		@return true if it's a default preset.
	*/
	virtual bool IsDefaultPreset (int32 index) const = 0;

	/** Returns true if the nth preset can be edited.
		@param index the nth preset
		@return true if preset edibable.
	*/
	virtual bool CanEditNthPreset (int32 index) const = 0;

	/** Returns true if the nth preset can be deleted.
		@param index the nth preset
		@return true if preset edibable.
	*/
	virtual bool CanDeleteNthPreset (int32 index) const = 0;

		/** Returns IMotionPresetData for the nth preset.
		@param index the nth preset
		@return IMotionPresetData* to nth preset
	*/
	virtual IMotionPresetData* QueryNthPreset (int32 index) const = 0;

	/** Searches the list for a preset with the specified name.
		@param name IN The name of the style to look for.
		@param casesensitive is true if doing case sensitive preset name comparison.
		The default is to do case sensitive comparison.
		@return The index of the style, or -1 if it wasn't found.
	*/
	virtual int32 FindPreset (const PMString& pName, bool casesensitive = true) const = 0;
	
	/** Searches the list for a preset with the specified UID.
		@param presetUID IN The UID of the preset to look for.
		@return The index of the preset, or -1 if it wasn't found.
	*/
	virtual int32 FindPreset (UID presetUID) const = 0;
	
	/** Adds a new preset with specified initial name.  If the name is already in
		the list, the function fails.

		@param iMotionPreset IN The new preset to insert
		@param atPosition IN The position to insert at. If atPosition is -1, the new preset is added at the end.
	*/
	virtual ErrorCode InsertPreset (IPMUnknown* iMotionPreset, int32 atPosition = -1) = 0;
		
	/** Deletes a preset.

		@param index IN The index of the preset to delete.
		@param deleteUID IN true if the UID representing the motion preset is to be deleted from the DB.
		@return Error code, or kSuccess if successful.
	*/
	virtual ErrorCode RemoveNthPreset(int32 index, bool deleteUID = true) = 0;
	
	/**	Generate a unique preset name. If the base string is empty, the the new
		will look something like: Motion Preset 1, Motion Preset 2. If the base string contains
		an exisiting style name, then the new name will look something like:
		<original name> copy 1, <original name> copy 2.

		@param baseName IN The base name for which you want a unique name.
		@param appendString IN the string to append before the name. If not specified, the default is " ".
		Translate the appendstring first.
		@param casesensitive is true if doing case sensitive preset name comparison.
		The default is to do case sensitive comparison.
		@return A unique name (ie, a version of baseName that is not currently in the list).
	*/
	virtual PMString GetUniquePresetName(PMString& baseName, const PMString& appendString = PMString (), bool casesensitive = true) const = 0;

	/** Internal use only.
	*/
	virtual ErrorCode SyncMotionPresetFileList () = 0;

};

#endif // __IMotionPresetMgr__

