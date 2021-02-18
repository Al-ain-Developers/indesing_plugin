//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IMotionPresetCmdData.h $
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

#include "DynamicDocumentsID.h"

/**
 Data interface apply motion preset file command.
 */
class IMotionPresetCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IMOTIONPRESETCMDDATA };
	
	/**
	 Set the flag to indicate whether to create a default empty preset.

	 @param createEmpty is true if create a default empty preset.
	*/
	virtual void SetCreateEmpty (bool createEmpty) = 0;

	/**
	 Set the preset name.

	 @param name the preset name.
	*/
	virtual void SetPresetName (const PMString& name) = 0;

	/**
	 Set the preset description.

	 @param description the preset description.
	*/
	virtual void SetPresetDescription (const PMString& description) = 0;

	/** 
	 Sets motion preset file to apply
	 
	 @param	presetFile is the motion preset file to add.
	 */
	virtual void SetMotionPresetFile (const IDFile& presetFile) = 0;

	/** 
	 Sets motion preset data to apply
	 
	 @param	presetData is the WideString representing the motion preset data to add.
	 */
	virtual void SetMotionPresetData (const WideString& presetData) = 0;

	/** 
	 Sets flag to indicate generate motion xml for SWF
	 
	 @param	useFile	is set to true if using a IDFile
	 */
	virtual void SetUsePresetFile (const bool& useFile) = 0;

	/** 
	 Set target DB
	 
	 @param iDB is the target DB for the new preset
	 */
	virtual void SetTargetDB (IDataBase* iDB) = 0;

	/** 
	 Get flag indicate whether or not the new preset is custom
	 
	 @param	isCustom		bool. 
	 */
	virtual  void SetIsCustomPreset (bool isCustom) = 0;
	
	/**
	 Get the flag whether to create a default empty preset.

	 @return true if create a default empty preset
	*/
	virtual bool GetCreateEmpty () const = 0;

	/**
	 @return the preset name.
	*/
	virtual PMString GetPresetName () const = 0;

	/**
	 @return the preset description.
	*/
	virtual PMString GetPresetDescription () const = 0;

	/**
	 @return true if description should be set.
	*/
	virtual bool GetSetDescriptionFlag () const = 0;

	/**
	 @return true if name should be set.
	*/
	virtual bool GetSetNameFlag () const = 0;

	/**
		Sets the edit lock info.

		@param editLocked is the lock info to set.
	*/
	virtual void SetEditLocked (bool editLocked) = 0;

	/**
		Sets the dellete lock info.

		@param deleteLocked is the lock info to set.
	*/
	virtual void SetDeleteLocked (bool deleteLocked) = 0;

	/**
		Sets the name lock info.

		@param nameLocked is the lock info to set.
	*/
	virtual void SetNameLocked (bool nameLocked) = 0;
	/**
		@return the name lock info setting.
	*/
	virtual bool GetEditLockInfo () const = 0;
	/**
		@return the name lock info setting.
	*/
	virtual bool GetDeleteLockInfo () const = 0;
	/**
		@return the name lock info setting.
	*/
	virtual bool GetNameLockInfo () const = 0;
	/**
		@return set edit lock info flag.
	*/
	virtual bool GetSetEditLockInfo () const = 0;
	/**
		@return set delete lock info flag.
	*/
	virtual bool GetSetDeleteLockInfo () const = 0;
	/**
		@return set name lock info flag.
	*/
	virtual bool GetSetNameLockInfo () const = 0;

	/**
	 Get the motion preset input.
	 
	 @param	presetFile returns the current motion preset file.
	 */
	virtual void GetMotionPresetFile(IDFile& presetFile) const = 0;

	/**
	 Get the motion preset input.
	 
	 @param	presetData returns the current motion preset data to use.
	 */
	virtual void GetMotionPresetData(WideString& presetData) const = 0;

	/** 
	 Get flag indicating whether to use IDFile or WideString for motion data
	 
	 @return true if using a IDFile.
	 */
	virtual bool GetUsePresetFile () const = 0;

	/** 
	 Get the target DataBase for this command
	 
	 @return	targetDB
	 */
	virtual IDataBase* GetTargetDB () const = 0;

	/** 
	 Get flag indicate whether or not the new preset is custom
	 
	 @return	true if custom preset
	 */	virtual bool GetIsCustomPreset () const = 0;
};
