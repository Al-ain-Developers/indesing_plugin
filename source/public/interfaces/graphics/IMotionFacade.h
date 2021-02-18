//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IMotionFacade.h $
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
//  ADOBE CONFIDENTIAL
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
#include "DynamicDocumentsID.h"

#include "WideString.h"
#include "Utils.h"

class IMotionPresetMgr;
class IMotionPresetData;
class ISubject;

namespace Facade
{

class IMotionFacade : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IMOTIONFACADE };
		
		/**	Apply specified motion preset to the list of page items.
			@param presetRef is the motion preset to apply
			@param itemList is the list of page items
			@param skipTargeting is true if not to add this object to its default triggering event.
			@param doForceCreateNew is true if to create new preset in the document even if a preset with the
			same name one already exist. The default is false.
			@return kSuccess otherwise an error code.
		*/
		virtual ErrorCode ApplyMotionPresetToPageItems (const UIDRef& presetRef, const UIDList& itemList, bool skipTargeting = false, bool doForceCreateNew = false) = 0;

		/** Returs the animation object for the specified motion preset.
			@param iDB is the data base in which to create the new preset.
			@param newName is name for the new preset.
			@param newDescription is description for the new preset.
			@param newPreset is the preset UID for the newly create preset.
			@return the error code.
		*/
		virtual ErrorCode NewMotionPreset (IDataBase* iDB, const PMString& newName, const PMString& newDescription, UID& newPresetUID) = 0;

		/** Delete the specified motion preset from the database's preset list.
			If it is the application preset list, the corresponding file will be deleted from disk.
			@param presetRef is the preset to update
			@param doShowAlert is true if to show an alert dialog warning about the deletion.
			@return the error code.
		*/
		virtual ErrorCode DeleteMotionPreset (const UIDRef& presetRef, bool doShowAlert = true) = 0;

		/** Duplicate the specified motion preset.
			A new motion preset xml file will be created for the newly duplicated motion preset in the
			same folder as the original preset.
			@param presetRef is the preset to duplicate
			@param newPresetName is the new preset name for the duplicated preset. 
			If empty string is passed in as name, a preset name will be generated using the name of the preset being
			duplicated with " Copy n" appended at end.
			@param newPresetUID is the newly duplicated preset UID.
			@return the error code.
		*/
		virtual ErrorCode DuplicateMotionPreset (const UIDRef& presetRef, const PMString& newPresetName, UID& newPresetUID) = 0;

		/** Update specified motion preset with new motion data.
			@param presetRef is the preset to update
			@param newData is the new motion data to update from.
			@return the error code.
		*/
		virtual ErrorCode SetMotionPresetMotionData (const UIDRef& presetRef, const WideString& newData) = 0;
		
		/** Load motion preset from specifiec preset file.
			@param sourceFileList is a list of files to import
			@param showAlert is true if alert dialog can be shown in case of errors.
			@return the resulting motion preset object.
		*/
		virtual ErrorCode LoadPresetFromFile (const std::vector<IDFile>& sourceFileList, UID& newPresetUID, bool showAlert = true) const = 0;

		/** Save the motion preset to a preset file.
			@param presetRef is the motion preset to save.
			@param exportFile is the preset file to save to.
			@return kSuccess otherwise an error code.
		*/
		virtual ErrorCode SavePresetToFile (const UIDRef& presetRef, const IDFile& exportFile) const = 0;

		/**	Returns true if motion preset can be edited. Default app presets are not editable. 
			Custom presets will be editable.
			@param presetRef is the preset UIDRef
			@return true if motion preset can be edited.
		*/
		virtual	bool PresetIsEditLocked (const UIDRef& presetRef) const = 0;

		/**	Returns true if motion preset is delete locked. Default app presets can not be deleted. 
			@param presetRef is the preset UIDRef
			@return true if motion preset can be deleted.
		*/
		virtual	bool PresetIsDeleteLocked (const UIDRef& presetRef) const = 0;
};

};	// namespace