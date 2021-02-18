//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ICMSUtils.h $
//  
//  Owner: Matt Phillips
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
#ifndef __ICMSUtils__
#define __ICMSUtils__

#include "ColorMgmtID.h"
#include "IPMUnknown.h"
#include "Utils.h"

#include "ICMSManager.h"		// for ICMSManager::CMSPolicy
#include "ICMSSettings.h"
#include "ICMSProofing.h"

#include "ScriptData.h"

// Flags for command wrappers (cmdFlags):

/** Marks the command as auto-undoable. */
const uint32 kCMSCmdAutoUndo = (1L<<1);

// Flags for Query operations (cmsQueryFlags):

/**	If operation involves a dynamically created set, using this flag prevents
	the set from being created (which changes a database) in response to the
	query.  In that case the interface returned is nil.
*/
const int32 kCMSQueryNoAutoCreate = (1L<<0);

class ICMSProfileList;
class IColorPresetsSettings;
class ICommand;
class IScriptRequestData;
class UIDList;


/**	CMS-related utility functions.
*/
class ICMSUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICMSUTILS };

	/**	Returns the CMSProfileList from the document.
		@param doc IN The document.  If nil, returns the default document's CMSProfileList.
		@param cmsQueryFlags IN kCMSQuery* flags (optional).
		@return A refcounted ICMSProfileList containing all the profiles used in the document.		
	*/
	virtual ICMSProfileList *QueryCMSProfileList(IDocument *doc, uint32 cmsQueryFlags = 0) = 0;
	
	/**	Returns the CMSProfileList from the document.
		@param docRef IN A reference to a document boss.
		@param cmsQueryFlags IN kCMSQuery* flags (optional).
		@return A refcounted ICMSProfileList containing all the profiles used in the document.		
	*/
	virtual ICMSProfileList *QueryCMSProfileList(const UIDRef& docRef, uint32 cmsQueryFlags = 0) = 0; 

	/**	Returns the CMS manager.  While in theory multiple CMS managers are permitted, in practice
		there is only one, which through ACE supports multiple CMMs.
		@param whichCMSMgr IN The class to use (kInvalidClass invokes the standard manager).
		@param cmsQueryFlags IN Not currently used.
		@return A refcounted ICMSManager interface.
	*/		
	virtual ICMSManager *QueryCMSManager(ClassID whichCMSMgr = kInvalidClass, uint32 cmsQueryFlags = 0) = 0;
	
	/** Returns the ColorPresetsSettings for the application.
		@return A refcounted IColorPresetsSettings interface.
	*/
	virtual IColorPresetsSettings *QueryColorPresetsSettings() = 0;
	
	/** Returns kTrue if currently emulating the 1.x CMS off state, otherwise kFalse.
	*/
	virtual bool16 IsEmulating1xCMSOffState() = 0;
	
	/**	Returns the CMSSettings from the document.  Note that CMSSettings on a document only contains 
		the default vector rendering intent.
		@param doc IN The document.  If nil, returns the default document's settings.
		@param cmsQueryFlags IN kCMSQuery* flags (optional).
		@return A refcounted ICMSSettings interface for the document.
	*/
	virtual ICMSSettings *QueryCMSSettings
		(
			IDocument *doc, 
			uint32 cmsQueryFlags = 0
		) = 0;

	/**	Returns the CMSSettings from the document.  Note that CMSSettings on a document only contains 
		the default vector rendering intent.
		@param docRef IN A reference to a document boss.
		@param cmsQueryFlags IN kCMSQuery* flags (optional).
		@return A refcounted ICMSSettings interface for the document.
	*/
	virtual ICMSSettings *QueryCMSSettings
		(
			const UIDRef& docRef, 
			uint32 cmsQueryFlags = 0
		) = 0;

	/**	Returns the default object settings from the document.  This controls the default RI for newly
		placed content.
		@param doc IN The document.  If nil, returns the default document's settings.
		@param cmsQueryFlags IN kCMSQuery* flags (optional).
		@return A refcounted ICMSSettings interface for the document.
	*/
	virtual ICMSSettings *QueryDefaultObjectSettings
		(
			IDocument *doc, 
			uint32 cmsQueryFlags = 0
		) = 0;

	/**	Returns the default object settings from the document.  This controls the default RI for newly
		placed content.
		@param docRef IN A reference to a document boss.
		@param cmsQueryFlags IN kCMSQuery* flags (optional).
		@return A refcounted ICMSSettings interface for the document.
	*/
	virtual ICMSSettings *QueryDefaultObjectSettings
		(
			const UIDRef& docRef, 
			uint32 cmsQueryFlags = 0
		) = 0;
	
	/**	Turns CMS on or off for a page item or document.  This is deprecated; you can still 
		turn cms on or off for a page item, but now that's interpreted as "use document default 
		profile and rendering intent."  The document on/off state is no longer honored at all.
		@param turnItOn IN The new state.
		@param itemList IN The list of items to affect.  Items must have the ICMSSettings interface.
		@param cmdFlags IN kCMSCmd* (optional)
		@param cmsMgrID IN Obsolete; leave at default.
		@return True if successful.
	*/
	virtual bool16 DoTurnCMSOnOrOff
		(
			bool16 turnItOn, 
			const UIDList& itemlist, 
			uint32 cmdFlags = 0, 
			ClassID cmsMgrID = kInvalidClass 
		) = 0;

	/**	Selects a CMM to use.
		@param cmmChoicetOn IN The name of the new CMM.
		@param doc IN Obsolete.  Not used.
		@param cmdFlags IN kCMSCmd* (optional)
		@param cmsMgrID IN Obsolete; leave at default.
		@return True if successful.
	*/
	virtual bool16 DoCMMChoice
		(
			const PMString& cmmChoice, 
			IDocument *doc, 
			uint32 cmdFlags = 0, 
			ClassID cmsMgrID = kInvalidClass
		) = 0;

 	/**	Sets a document profile (CMYK or RGB) via a kCMSUseProfileCmd.
		@param profileName The name of the profile to use.
		@param doc IN The document that should be affected.  Must be non-nil to have any effect.
		@param which IN Which of the profiles to set.  Only CMYK and RGB profiles have any effect.
		@param cmdFlags IN kCMSCmd* (optional)
		@param cmsMgrID IN Obsolete; leave at default.
		@param installDefaultFlag IN If true, ignore the name passed in and set the document to use the current working space. 
		@return True if successful.
	*/
 	virtual bool16 DoDocUseProfileCmd
 		(	
 			const PMString& profileName, 
 			IDocument *doc, 
 			ICMSProfile::profileCategory which,
 			uint32 cmdFlags = 0,
 			ClassID cmsMgrID = kInvalidClass,
 			bool16 installDefaultFlag = kFalse
 		) = 0; 

 	/**	Assigns an external (from disk) profile to an image via a command. 
		@param itemUIDRef IN The image page item boss.
		@param profileName The name of the profile to use.
		@param cmdFlags IN kCMSCmd* (optional)
		@param cmsMgrID IN Obsolete; leave at default.
		@return True if successful.
	*/
	virtual bool16 DoItemUseExternalProfileCmd
		(
			const UIDRef& itemUIDRef,
			const PMString& profileName,
			uint32 cmdFlags = 0,
			ClassID cmsMgrID = kInvalidClass
		) = 0;
							
 	/**	Assigns an embedded (from the image itself) profile to an image via a command. 
		@param itemUIDRef IN The item to which to assign the profile.
		@param pProfileData e profile data; nil to pull from item.
		@param dataSize Size of data, or 0 to pull from item.
		@param profileName Name of embedded profile, if not providing data and the item hasn't 
							yet been set up with emb data. In all other cases, nil is appropriate.
		@param cmdFlags IN kCMSCmd* (optional)
		@param cmsMgrID IN Obsolete; leave at default.
		@return True if successful.
	*/
	virtual bool16 DoItemUseEmbeddedProfileCmd
		(
			const UIDRef& itemUIDRef,
			void *pProfileData = nil,
			int32 dataSize = 0,
			PMString *pName = nil,
			uint32 cmdFlags = 0,
			ClassID cmsMgrID = kInvalidClass
		) = 0;
							
 	/**	Resets an image to use the document default profile. 
		@param itemUIDRef IN The image page item boss.
		@param cmdFlags IN kCMSCmd* (optional)
		@param cmsMgrID IN Obsolete; leave at default.
		@return True if successful.
	*/
	virtual bool16 DoItemUseDocDefaultProfileCmd
		(
			const UIDRef& itemUIDRef,
			uint32 cmdFlags = 0,
			ClassID cmsMgrID = kInvalidClass
		) = 0;
		
	/** Indicates whether the specified profile is in use in the specified document.
		@param profileName IN The name to look for.
		@param db IN The database of the document.
		@param cmsMgrID IN Obsolete; leave at default.
		@return True if successful.
	*/
	virtual bool16 DoesProfileExist
		(
			const PMString& profileName,
			IDataBase *db, 
			ClassID cmsMgrID = kInvalidClass
		) = 0;
	
	/** Sets the RI for a page item or document (anything with an ICMSSettings interface) via a command.
		@param itemRef IN The boss with an ICMSSettings interface you want to change.
		@param choice IN The new RI to assign.
		@param cmdFlags IN kCMSCmd* (optional)
		@return True if successful.
	*/
	virtual bool16 DoSetRenderingIntent
		(
			const UIDRef& itemRef, 
			ICMSSettings::renderingIntent choice, 
			uint32 cmdFlags = 0
		) = 0;
	
	/** Sets the RI for a list of items (anything with an ICMSSettings interface) via a command.
		@param itemList IN The list of items with ICMSSettings interfaces you want to change.
		@param choice IN The new RI to assign.
		@param cmdFlags IN kCMSCmd* (optional)
		@return True if successful.
	*/
	virtual bool16 DoSetRenderingIntent
		(
			const UIDList& itemList, 
			ICMSSettings::renderingIntent choice, 
			uint32 cmdFlags = 0
		) = 0;
	
	/** Creates and executes a kCMSCopyCMSSetupCmdBoss with specified src and dst items.  Handles the recreation 
		of the settings on the item in the destination document.  Src and destination documents can be same, 
		or different.  Used when copying page items from one document to another, or whatever you like.
		@param srcItem IN The item from which the settings are copied
		@param dstItem IN The item to which the settings are copied
		@param cmdFlags IN kCMSCmd* (optional)
		@param cmsMgrID IN Obsolete; leave at default.
		@return True if successful.
	*/
	virtual bool16 DoCopyCMSSettingsCmd
		(
			UIDRef srcItem, 
			UIDRef dstItem, 
			uint32 cmdFlags = 0, 
			ClassID cmsMgrID = kInvalidClass
		) = 0;

	/**	Creates and executes a kCMSRemoveCMSSetupCmdBoss with specified item.   This removes the CMS setup 
		from the item.  Normally done prior to deletion.
		@param theItem IN The item to reset
		@param cmdFlags IN kCMSCmd* (optional)
		@param cmsMgrID IN Obsolete; leave at default.
		@return True if successful.
	*/
	virtual bool16 DoRemoveCMSSetup
		(
			UIDRef theItem, 
			uint32 cmdFlags = 0, 
			ClassID cmsMgrID = kInvalidClass
		) = 0;

	/** Broadcast on the subject of the target database with IID_ICOLORXFORMCHANGE protocol, 
		alerting the world of the change and updating pageitems and/or spreads
		as appropriate in open documents. The IID_ICOLORXFORMCHANGE interface is on the active context.
		@param iDataBase IN the command's target database from which the change is broadcast.
		@param cmdChangedBy IN The command that's passed to the subject.
		@param changeFlags IN CXFORMFLAG_* options.
		@return True if successful.
	*/
	virtual bool16 ColorXFormChange
		(
			IDataBase* iDataBase,
			ICommand *cmdChangedBy,
			int32 changeFlags
		) = 0;
	
	/** Sets the current color settings en masse.
		@param emulate1xCMSOff True to use "CMS off" mode.
		@param isCustom Indicates that the settings are not based on a CSF but are custom.
		@param presetName For non-custom CSFs, the name of the preset.
		@param presetPath For non-custom CSFs, the location of the preset file.
		@param description The internal name of the preset.
		@param workingRGB The working RGB profile.
		@param workingRGBName The name of the working RGB profile.
		@param workingRGBCode The profile code of the working RGB profile.
		@param workingCMYK The working CMYK profile.
		@param workingCMYKName The name of the working CMYK profile.
		@param workingCMYKCode The profile code of the working CMYK profile.
		@param policyRGB The profile policy for RGB.
		@param policyCMYK The profile policy for CMYK.
		@param mismatchAskOpening Whether to display profile-mismatch dialogs when opening documents.
		@param mismatchAskPasting Whether to display profile-mismatch dialogs when pasting content.
		@param missingAskOpening Whether to display profile-missing dialogs when opening documents.
		@param engineCMS The index of the CMS to use.  Should always be zero for now.
		@param engineCMM The index of the CMM to use.
		@param intent The default rendering intent.
		@param kpc The default black point compensation setting (on/off).
		@param nFlags IN kCMSCmd* (optional)
		@return True if successful.
	*/
	virtual bool16 DoColorPresetsSettingsSetCmd(bool16 emulate1xCMSOff, 
											   bool16 isCustom, 
											   const PMString &presetName, 
											   const PMString &presetPath, 
											   const PMString &description, 
											   ICMSProfile *workingRGB, 
											   const PMString &workingRGBName,
											   ICMSProfile::profileCode workingRGBCode,
											   ICMSProfile *workingCMYK, 
											   const PMString &workingCMYKName,
											   ICMSProfile::profileCode workingCMYKCode,
											   ICMSManager::CMSPolicy policyRGB, 
											   ICMSManager::CMSPolicy policyCMYK, 
											   bool16 mismatchAskOpening, 
											   bool16 mismatchAskPasting, 
											   bool16 missingAskOpening, 
											   uint32 engineCMS, 
											   uint32 engineCMM, 
											   ICMSSettings::renderingIntent intent, 
											   bool16 kpc,
											   int32  nFlags = 0) = 0;
	
	/** Configures proofing parameters via a command.  This version specifies a profile by interface.
		@param iCMSProofing IN The interface to affect.
		@param isProofingOn IN Enables/disables proofing.
		@param proofingType IN Any of the default proofing states, or custom. 
		@param iCMSProfile IN The custom proofing profile, if applicable.
		@param paperWhite IN Whether to simulate paper color.
		@param inkBlack IN Whether to simulate ink black.
		@param preserveNumbers IN Whether to preserve numbers for same-family untagged objects.
		@return The error code from the command.
	*/
	virtual ErrorCode DoCMSSetProofingCmd
		(
			ICMSProofing *iCMSProofing, 
			bool16 isProofingOn, 
			ICMSProofing::ProofingType proofingType, 
			ICMSProfile *iCMSProfile, 
			bool32 paperWhite, 
			bool32 inkBlack, 
			bool32 preserveNumbers = kTrue
		) = 0;
		
	/** Configures proofing parameters via a command.  This version specifies a profile by name.
		@param iCMSProofing IN The interface to affect.
		@param isProofingOn IN Enables/disables proofing.
		@param proofingType IN Any of the default proofing states, or custom. 
		@param name IN The custom proofing profile, if applicable.
		@param paperWhite IN Whether to simulate paper color.
		@param inkBlack IN Whether to simulate ink black.
		@param preserveNumbers IN Whether to preserve numbers for same-family untagged objects.
		@return The error code from the command.
	*/
	virtual ErrorCode DoCMSSetProofingCmd
		(
			ICMSProofing *iCMSProofing, 
			bool16 isProofingOn, 
			ICMSProofing::ProofingType proofingType, 
			PMString &name, 
			bool32 paperWhite, 
			bool32 inkBlack, 
			bool32 preserveNumbers = kTrue
		) = 0;
	
	/** Processes a convert to profile command that will convert all native swatches to a new profile.
		@param doc IN The document to affect.
		@param category IN The profile category to convert (must be CMYK or RGB)
		@param name IN The name of the profile to use for the new destination (will be assigned to the document after conversion)
		@param engineCMS IN The index of the CMS (leave as default).
		@param engineCMM IN The index of the CMM.
		@param intent IN The RI to apply for the conversions.
		@param useKPC IN The BPC to apply for the conversions.
		@return The error code from the command.
	*/
	virtual ErrorCode DoConvertToProfileCmd
		(
			IDocument *doc, 
			ICMSProfile::profileCategory category, 
			const PMString &name, 
			uint32 engineCMS = 0, 
			uint32 engineCMM = 0, 
			ICMSSettings::renderingIntent intent = ICMSSettings::kImage, 
			bool16 useKPC = kTrue
		) = 0;

	/** Resolves any rendering intents which are pointers (e.g., UseCSFImageRI) down to a simple intent.  Requires
		iDoc when any of the UseDoc* intents are used.
		@param iDoc IN The document to use.  Can be nil if the RI to resolve is not document-based.
		@param ri IN The RI to resolve.
		@return The resolved RI.
	*/
	virtual ICMSSettings::renderingIntent ResolveIntent
		(
			IDocument* iDoc, 
			ICMSSettings::renderingIntent ri
		) = 0;	
	
#ifdef DEBUG
	virtual void DumpCMSManager(IDocument* document) = 0;
#endif

	/**	Adds the names of the profiles in plistSource to the specified IScriptList.
		@param plistSource Specifies the list of profiles to read from.
		@param plistTarget The list to populate.
		@return True if successful.
	*/
	virtual bool32 BuildScriptableProfileArray
		(
			CMSAvailableProfileList* plistSource, 
			ScriptListData& plistTarget
		) = 0;

	/**	Sets up a filter which is appropriate for retrieving the set of profiles that apply to the specified image.
		@param uidImage The image for which you want to build a list of profiles.
		@param filter Receives the filter to use.
		@return True if successful.
	*/
	virtual bool32 SetupImageFilter
		(
			UIDRef uidImage, 
			CMSMgrProfileFilter& filter
		) = 0;

	/** Converts from on of the script enumeration values (en_... in ScriptingDefs.h) to the intenral rendering intent
		@param pDoc The document (required for indirect document referenced rendering intents).
		@param nScriptIntent The ID of the intent from the scripting world.
		@param nIntentType Used if nScriptIntent is en_UseColorSettings; indicates which of the default RIs to use.
		@param nError Receives the error code.
		@return The resolved rendering intent.
	*/
	virtual ICMSSettings::renderingIntent ScriptIntentToCMSIntent
		(
			IDocument* pDoc, 
			ScriptID nScriptIntent, 
			ICMSSettings::renderingIntent nIntentType, 
			ErrorCode& nError
		) = 0;
		
	/** Opposite of ScriptIntentToCMSIntent.
		@param nCMSIntent The intent you want to convert.
		@return The corresponding script ID.
	*/
	virtual ScriptID CMSIntentToScriptIntent(ICMSSettings::renderingIntent nCMSIntent) = 0;	

	/** Given infomration about a scripting context, returns the set of cms profiles that satisfy the specified
		profile category to the scripting implementation.
		@param data The scripting data to fill in.
		@param script Not currently used.
		@param profileCategory The category to use to populate the list of profiles.
		@param propID Which scripting field to use.
		@return kSuccess or kFailure.
	*/
	virtual int32 AccessCMSProfileList
		(
			IScriptRequestData*data, 
			IScript*script, 
			ICMSProfile::profileCategory profileCategory,
			ScriptID propID
		) = 0;

	/**	Given information about a scripting context, gets or sets the cms profile name for the specified profile type.  
		nParamID is the constant for the script parameter which contains the name of the new profile to use if the operation is
		a set.
		@param pDoc The document whose profiles are needed.
		@param data The data to fill in.
		@param script Not currently used.
		@param nProfileType The profile category you're interested in.
		@param propID Which scripting field to use.
		@return kSuccess or kFailure.
	*/
	virtual int32 AccessCMSProfile
		(
			IDocument* pDoc, 
			IScriptRequestData*data, 
			IScript*script, 
			ICMSProfile::profileCategory nProfileType, 
			ScriptID propID
		) = 0;

	/** Returns true if a profile w/ the specified name can be located on the filesystem in one of the 
		standard search paths.
		@param strName The profile name for which to look.
		@return True if the profile exists.
	*/
	virtual bool16 CanFindProfile( const PMString& strName ) = 0;

	/** Returns whether the profile with the specified name supports ink black/paper white.
		@param strName The name of the profile.
		@param bSupportsInkBlack Receives true if the profile supports ink black proofing; false otherwise.
		@param bSupportsPaperWhite Receives true if the profile supports paper white proofing; false otherwise.
	*/
	virtual void GetProfileProofingSupport
		( 
			const PMString& strName, 
			bool16& bSupportsInkBlack, 
			bool16& bSupportsPaperWhite 
		) = 0;

	/** Tell the destination document to use the source document's profiles.
		@param pSrc The document from which to copy profiles.
		@param pDst The document to which to copy profiles.
	*/
	virtual void CopyColorProfiles
		(
			IDataBase* pSrc,
			IDataBase* pDst 
		) = 0;

};


#endif	// __ICMSUtils__
