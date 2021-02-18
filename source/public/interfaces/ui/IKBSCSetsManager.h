//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IKBSCSetsManager.h $
//  
//  Owner: Michel hutinel
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
#ifndef __IKBSCSetsManager__
#define __IKBSCSetsManager__

/** this interface is deprecated. @see IShortcutManager */
#ifdef ID_DEPRECATED

#include "IPMUnknown.h"
#include "KBSCEditorDlgID.h"
#include "WidgetDefs.h"

#include "PMString.h"


#define kKBSCInvalidSetIndex	-1
#define kKBSCDefaultSetIndex	0

#define kKBSCNameMaxCharLength	kPMNamedItemMaxChars

/** This interface is used by the shortcut editor dialog. Most of the methods just call into IShortcutManager to do the real work. @see IShortcutManager for more information */

class IKBSCSetsManager : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IKBSCSETSMANAGER };

	/** Manage KBSC sets created by user (kUserKBSCArea), and default sets we ship with (kDefaultKBSCArea).
		kDefaultKBSCArea corresponds to FileUtils::GetPresetsFolder()
		kUserKBSCArea corresponds to FileUtils::GetAppRoamingDataFolder()
		kDefaultKBSCArea shortcut sets are not editable by the user, those in kUserKBSCArea area. */
	typedef enum { kDefaultKBSCArea = 0, kUserKBSCArea = 1 } KBSCArea;

	/** Populate internal list with available shortcut files */
	virtual bool16		ReadSetFiles() = 0;
	
	/** Save the current shortcut file */
	virtual bool16		SaveCurrentSetFile() = 0;
	
	/** Returns the current shortcut set name */
	virtual PMString	GetCurrentSetName() = 0;

	/** Returns the current shortcut set area */
	virtual IKBSCSetsManager::KBSCArea	GetCurrentSetKBSCArea() = 0;

	/** load the named shortcut set file */
	virtual bool16		SwitchToSet(const PMString& setName, KBSCArea area) const = 0;

	/** load the indexed shortcut set file */
	virtual bool16		SwitchToSet(const int32 index, KBSCArea area) const = 0;

	/** Returns the number of shortcut sets */
	virtual int32		GetNumSets(KBSCArea area) const = 0;

	/** Returns the name of the nth shortcut set */
	virtual PMString	GetSetName(const int32 index, KBSCArea area) const = 0;
		
	/** Returns the index of the named set (kInvalidShortcutSetIndex if does not exist) */
	virtual int32		GetSetIndex(const PMString& setName, KBSCArea area) const = 0;

	/** Returns kTrue if the indexed set is editable */
	virtual bool16		IsSetEditable(const int32 index, KBSCArea area) const = 0;

	/** Returns kTrue if the named set is editable */
	virtual bool16		IsSetEditable(const PMString& setName, KBSCArea area) const = 0;
	
	/** Returns true if the set in memory differs from the one on disk. */
	virtual bool16		IsSetDirty(const int32 index, KBSCArea area) const = 0;

	/** Returns kTrue if the named set in memory differs from the one on disk */
	virtual bool16		IsSetDirty(const PMString& setName, KBSCArea area) const = 0;

	/** Marks the set as needing to be written to disk */
	virtual void		DirtySet(const int32 index, KBSCArea area) = 0;

	/** Marks the named set as needing to be written to disk */
	virtual void		DirtySet(const PMString& setName, KBSCArea area) = 0;

	/** Duplicates the set named origName to a new set named destName. Optionally make the duplicated set editable. */
	virtual bool16		DuplicateSet(const PMString& origName, KBSCArea origArea, const PMString& destName, bool16 desEditable) = 0;

	/** Delete the set setName */
	virtual bool16		DeleteSet(const PMString& setName) = 0;

	/** Determines if the given set names are the equal */
	virtual bool16		EqualSetNames(const PMString& name1, const PMString& name2) = 0;

	/** Return appropriate directory based on area, kFalse if failure, kTrue if successful. */
	virtual bool16		GetKBSCDirectory(IDFile& folderFileSpec, KBSCArea area) = 0;
};

#endif

#endif
		// __IKBSCSetsManager__
