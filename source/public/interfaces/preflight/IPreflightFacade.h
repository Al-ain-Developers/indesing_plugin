//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightFacade.h $
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

#include "IPreflightOptions.h"
#include "IPreflightRuleInfo.h"
#include "IPreflightRuleData.h"

#include "PackageAndPreflightID.h"
#include "Utils.h"

class IPreflightProfile;
class IPreflightBookOptions;

namespace Facade
{
	/** This facade provides services for obtaining and modifying the preflight	engine 
		that is new to InDesign CS4. This preflight engine supports preflight profiles, 
		extensible rule sets, and background (idle loop) as well as synchronous preflight.

		Working from the top down, the important interfaces and objects in the preflight
		domain include the following.

		Preflight profiles: These are bosses which represent a named set of rules and rule
		parameters. A list of these is maintained at the application and document levels
		by the IPreflightProfileManager interface.
			@see IPreflightProfileManager
			@see IPreflightProfile
			@see IPreflightProfileUtils

		Each preflight profile maintains a list of profile rules. These rules are bosses
		created by preflight rule services. InDesign has a native rule service boss which
		implements all the rules that ship with the application. Anyone can implement a
		rule service which extends the set of rules that work with the application.
			@see IPreflightProfileRules
			@see IPreflightRuleService

		The engine itself is governed by the application-level IPreflightProcessManager
		and each instance of a profile being cheked against a document is represented
		by an in-memory Preflight Process boss that hosts an IPreflightProcess interface. 
			@see IPreflightProcessManager
			@see IPreflightProcess

		The preflight process is basically a state machine with a database attached. The
		state machine uses the database to keep track of what parts of the document have 
		been examined against the set of rules in its assigned profile, and what results
		if any were found during that traversal. Since preflight works in the background,
		changes to the document require selective invalidation of portions of the database
		and subsequent re-investigation of those portions.

		The preflight process is actually governed by two inputs. The first is the preflight
		profile, which of course provides the rules and rule parameters. The second is the
		preflight options, which control the filtering of objects that the rules are shown.
			@see IPreflightOptions

		Another core piece of the preflight feature is the preflight object model. This
		is the mechanism by which preflight rules can access information in the document
		including information that has no other API; it also allows preflight to maintain
		information about documents that aren't open at the moment; and it's extensible so
		that a developer can introduce its own hierarchy and objects. The preflight object
		model is implemented via a service and abstracted/multiplexed at the application 
		level via IPreflightObjectModel.
			@see IPreflightObjectModel
			@see IPreflightObjectModelService

		Preflight also works at the book level. The IPreflightBookRef interface sits on the
		book and maintains a reference to an in-memory preflight book object. This object
		shadows the book's content and records the preflight results for each chapter.
		It also has an IPreflightBookController interface which drives the state machine
		of book preflight, which is *not* a background operation.
			@see IPreflightBookRef
			@see IPreflightBookData
			@see IPreflightBookOptions
			@see IPreflightBookController
			@see IPreflightBookContentData
			@see IPreflightBookUtils
		
		This facade doesn't attempt to cover everything above. In particular the extensible
		pieces, rule and object model services, are not represented here because they're 
		well defined in their own interface headers. Instead this facade concentrates on 
		the maintenance of preflight profiles, their rule settings, and getting/setting
		the parameters assigned to document preflight processes.
	*/
	class IPreflightFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IPREFLIGHTFACADE };

		/**	The Preflight preferences facade methods
		*/

		/**	Turn preflight on for the specified data base.
			If the database is the application default database, this action affects
			all new documents as well as all currently opened documents.
			If the database is a document database, then preflight is turned on for this document only.
			@param iTargetDB is the database for which the preflighting is turned on. 
			If nil, application default database is assumed.
		*/
		virtual void TurnOnPreflighting (IDataBase* iTargetDB) = 0;
		/**	Turn preflight off for the specified data base.
			If the database is the application default database, this action affects
			all new documents as well as all currently opened documents.
			If the database is a document database, then preflight is turned off for this document only.
			@param iTargetDB is the database for which the preflighting is turned off.
			If nil, application default database is assumed.
		*/
		virtual void TurnOffPreflighting (IDataBase* iTargetDB) = 0;

		/**	Returns true if preflight is turned on for the given database.
			@param iTargetDB is the specified database
			If nil, application default database is assumed.
		*/
		virtual bool16 IsPreflightingOn (IDataBase* iTargetDB) const = 0;

		/**	Set to true if the current default working preflight profile should be automatically
			embedded when creating a new document.
			This is an application level only preference setting.
			@param autoEmbed is true if auto embed the working profile in the new document.
		*/
		virtual void SetEmbedProfileInNewDocuments (bool16 autoEmbed) = 0;
		/**	
			@return true if auto embed the wokring profile in the new document.
		*/
		virtual bool16 GetEmbedProfileInNewDocuments (void) const = 0;

		/**	Set the preflight profile policy for openeing existing document.
			This is an application level only preference setting.
			@param profilePolicy
			@see also IPreflightOptions.h
		*/
		virtual void SetOpenDocumentPolicy (IPreflightOptions::PreflightProfilePolicy& profilePolicy) = 0;
		/**
			@return the current default preflight profile policy for opening existing document.
		*/
		virtual IPreflightOptions::PreflightProfilePolicy GetOpenDocumentPolicy (void) const = 0;


		/**	Set the preflight's include layer options for the specified database.
			If the database is the application default database, this setting is applied to new documents and
			when opening documents.
			If the database is a document database, this setting is only valid for as long as the document stayed
			opened. The setting is not saved with the document. When the document is opened again, this setting
			is initialized to the current application default.
			@param iTargetDB is the database.
			@param whichLayer is the include layer option to set.
			@see also IPreflightOptions.h
		*/

		virtual void SetIncludeLayers (IDataBase* iTargetDB, const IPreflightOptions::LayerOptions whichLayer) = 0;
		/**
			@return the current preflight include layer preference for the specified database.
		*/
		virtual IPreflightOptions::LayerOptions GetIncludeLayers (IDataBase* iTargetDB) const = 0;

		/**	Set the preflight's include objects on pasteboard preference for the specified database.
			If the database is the application default database, this setting is applied to new documents and
			when opening documents.
			If the database is a document database, this setting is only valid for as long as the document stayed
			opened. The setting is not saved with the document. When the document is opened again, this setting
			is initialized to the current application default.
			@param iTargetDB is the database.
			@param onOff is true if set inclusion to true; otherwise set to false.
			@see also IPreflightOptions.h
		*/
		virtual void SetIncludeObjectsOnPasteboard (IDataBase* iTargetDB, const bool16 onOff) = 0;
		/**
			@return the current preflight include objects on pasteborad preference for the specified database.
		*/
		virtual bool16 GetIncludeObjectsOnPasteboard (IDataBase*) const = 0;

		/**	Set the preflight's include non-printing objects preference for the specified database.
			If the database is the application default database, this setting is applied to new documents and
			when opening documents.
			If the database is a document database, this setting is only valid for as long as the document stayed
			opened. The setting is not saved with the document. When the document is opened again, this setting
			is initialized to the current application default.
			@param iTargetDB is the database.
			@param onOff is true if set inclusion to true; otherwise set to false.
			@see also IPreflightOptions.h
		*/
		virtual void SetIncludeNonPrintingObjects (IDataBase*, const bool16 onOff) = 0;
		/**
			@return the current preflight include non-printing objects preference for the specified database.
		*/
		virtual bool16 GetIncludeNonPrintingObjects (IDataBase*) const = 0;

		/**	Set the preflight's scope preference for the specified database.
			This setting is only applicable if database is a document database.
			If the database is a application default database, the setting is ignored.
			@param iTargetDB is the database.
			@param scope is the preflight scope to set to.
			@param pPageRange if not nil sets the page ranges. This parameter is only useful
				if setting scope to kPageRange.
			@see also IPreflightOptions.h
		*/
		virtual void SetPreflightScope 
			(
				IDataBase* iTargetDB, 
				const IPreflightOptions::PreflightScope& scope, 
				PMString* pPageRange = nil
			) = 0;

		/**	Returns the preflight scope for the specified document database.
			If hte database is a application default database, the scope is always set to IPreflightOptions::kAllPages.
			@param iTargetDB is the database.
			@return the current scope.
			@see also IPreflightOptions.h
		*/
		virtual IPreflightOptions::PreflightScope GetPreflightScope (IDataBase* iTargetDB) const = 0;
		
		/**	Returns the preflight scope's page range for the specified document database.
			If hte database is a application default database, the scope page range is always set to an empty string.
			@param iTargetDB is the database.
			@param pageRange the current scope page range.
			@see also IPreflightOptions.h
		*/
		virtual void GetPreflightScopePageRange (IDataBase* iTargetDB, PMString& pageRange) const = 0;

		/**	Sets the working preflight profile for the given database.
			If the database is the application default database, this is the working space that will be
			set in the document when it is opened if the open document policy is set to use the working profile.
			If open policy is set to using the document embedded and the document does not have an embedded profile,
			then the document's working profile is set to the application default working profile when the document
			if first opened.
			@see also SetOpenDocumentPolicy

			This is also the working profile to auto-embed if 
			@see also SetEmbedProfileInNewDocuments
		*/
		virtual void SetWorkingProfile (IDataBase* iTargetDB, const UIDRef& preflightProfile) = 0;
		/**	Get the current working preflight profile for the specified database.
			The working profile will have the same database if it's the document's embedded profile.
			Or the working profile is a profile in the application's profile list.
			@param iTargetDB is the database.
			@return the UIDRef of the working profile.
		*/
		virtual UIDRef GetWorkingProfile (IDataBase* iTargetDB) const = 0;

		/**	The Preflight profile facade methods
		*/

		/**	This method does the following:
			- Create a new preflight profile with a specified name/description application default database;
			- Add it to that database's preflight profile manager;
			- Optionally return the new profile's UID.

			@param profileName IN The name to use for the new profile. 
				@see IPreflightProfileManager::GetUniqueProfileName to ensure a unique name.
			@param profileDesc IN The longer description of the profile.
			@param prepopulateRules IN kTrue if you want to prepopulate the rule list for the new profile with
				all rules registered with the rule manager; the rules will be disabled but present with
				default settings. If kFalse, the profile will not have any rules and will need to be 
				added 'manually.'
			@param newProfileUID receives the UID of new profile. If profile is not created, kInvalidUID is returned.
			@return kSuccess or an error code from the command.
		*/
		virtual ErrorCode CreateProfile 
			(
				const PMString& profileName,
				const PMString& profileDesc,
				bool prepopulateRules,
				UID* newProfileUID
			) = 0;
		
		/**	Delete the specified profile. This removes the profile from its database's profile 
			manager list and then deletes the UID of the profile and all rules.

			@param profileRef is the profile to delete.
			@return kSuccess or an error code from the command.
		*/
		virtual ErrorCode DeleteProfile
			(
				const UIDRef& profileRef
			) = 0;

			

		/**	Duplicate the specified profile in the specified target database (which can be the 
			same database as the source profile). The name of the new profile is autogenerated via
			GetUniqueProfileName() using the source profile's name.

			@param targetDB is the database in which the new profile should be created (and the
				corresponding IPreflightProfileManager that will receive the new profile). If 
				nil, the new profile will be created in the default document (aka app).
			@param srcProfileRef is the UIDRef of the profile to duplicate.
			@param newProfileUID receives the UID of the duplicate (or kInvalidUID if error). This
				UID will be in the target DB.
			@return kSuccess or an error code from the command.
		*/
		virtual ErrorCode DuplicateProfile 
			(
				IDataBase* targetDB,
				const UIDRef& refSrcProfile,
				UID* newProfileUID
			) = 0;

		/**	Embed a profile in a document. This creates a copy of an application level profile
			in a document, removing any existing document profile.

			@param docDB is the target document database.
			@param refProfileToEmbed is the application-level profile to embed.
			@param embeddedProfileUID if not nil receives the resulting profile UID in the document.
			@return kSuccess or an error code from the command.
		*/
		virtual ErrorCode EmbedProfile
			(
				IDataBase* docDB,
				const UIDRef& refProfileToEmbed,
				UID* embeddedProfileUID
			) = 0;
		
		/**	Unembed the document profile. This simply deletes any existing profiles in the document.

			@param docDB is the target document.
			@param copyEmbeddedToApplication IN Specifies whether to apply the default behavior
				that the currently-embedded profile in the document, if any, will be copied to 
				the application level list of profiles if a profile by that name does not currently
				exist at the application level. If this argument is false then this method does
				a simple unembed without any copying.
			@return kSuccess or an error code from the command.
		*/
		virtual ErrorCode UnembedProfile
			(
				IDataBase* docDB,
				bool copyEmbeddedToApplication = kTrue
			) = 0;

		/**	Import a preflight profile from a file. This file can be a InDesign preflight profile file (IDPP)
			or an InDesign document.

			@param sourceFile is the file to import from.
			@param pNewProfileUID is the UID of the profile imported from the specified INX file.
			@param showAlert is true if alert should be shown for errors.
			@return kSuccess or an error code.
		*/
		virtual ErrorCode LoadPreflightProfileFromFile
			(
				const IDFile& sourceFile,
				UID* pNewProfileUID,
				bool16	showAlert
			) = 0;

		/**	Export a preflight profile as an InDesign preflight profile file. 

			@param iProfile is the preflight profile to export.
			@param exportFile is the IDFile to export to.
			@return kSuccess or an error code.
		*/
		virtual ErrorCode ExportPreflightProfileAsINX
			(
				const UIDRef& preflightProfile,
				const IDFile& exportFile
			) = 0;


		/**	Returns a list of all the profiles in the application profile list. 

			@param profileList Out The list containing the profiles..
		*/
		virtual void GetAllProfiles (UIDList& profileList) const = 0;

		/**	Returns the profile name for the specified profile. 

			@param profileRef IN The UIDRef of the profile.
			@param profileName OUT The profile name of the specified preflight profile.
		*/
		virtual void GetProfileName (const UIDRef& preflightProfile, PMString& profileName) const = 0;
		/**	Sets the new profile name for the specified profile. 

			@param profileRef IN The UIDRef of the profile.
			@param profileName IN The profile name to set.
		*/
		virtual ErrorCode SetProfileName (const UIDRef preflightProfile, const PMString& profileName) = 0;

		/**	Returns the profile description for the specified profile. 

			@param profileRef IN The UIDRef of the profile.
			@param profileDesc OUT The profile description of the specified preflight profile.
		*/
		virtual void GetProfileDescription (const UIDRef& preflightProfile, PMString& profileDesc) const = 0;
		/**	Sets the new profile description for the specified profile. 

			@param profileRef IN The UIDRef of the profile.
			@param profileDesc IN The profile description to set.
		*/
		virtual ErrorCode SetProfileDescription (const UIDRef& preflightProfile, const PMString& profileDesc) = 0;

		/**	The Preflight profile rules facade methods
		*/

		/**	Returns the rule UID for the specified ruleID in the given preflight profile.
			@param preflighProfile IN The preflight profile.
			@param ruleID IN The rule ID in the preflight profile.
			@return the corresponding rule UID for the specified ruleID in the profile.
		*/
		virtual UID GetRule (const UIDRef preflightProfile, const PreflightRuleID& ruleID) const = 0;

		/**	Returns the nth rule UID in the given preflight profile.
			@param preflighProfile IN The preflight profile.
			@param n IN The nth rule UID to get.
			@return rule UID or kInvalidUID.
		*/
		virtual UID GetNthRule (const UIDRef preflightProfile, int16 n) const = 0;
		/**	Returns the number of rules in the given preflight profile.
			@param preflighProfile IN The preflight profile.
			@return the number rules in the profile.
		*/
		virtual int32 GetProfileRuleCount (const UIDRef preflightProfile) const = 0;

		/**	Remove all rules in the given profile
			@param preflighProfile IN The preflight profile.
		*/
		virtual ErrorCode RemoveAllRules (const UIDRef preflightProfile) = 0;
		
		/** Give all of the rules in the specified profile(s) a chance to update their parameter
			values. If a rule's parameters change from one version to another it may need to tweak
			the parameters.

			@param profiles IN A list of the profiles to update.
			@return kSuccess or an error code from the command.
		*/
		virtual ErrorCode UpdateEachRulesData (const UIDList& profiles) = 0; 

		/**	Create an instance of rule ID in the database
			@param preflightProfile IN The target profile in which to create the rule.
			@param ruleID IN The rule to create.
			@param pNewRuleUID OUT If not nil, contains the new rule UID.
		*/
		virtual ErrorCode CreateRule (const UIDRef& preflightProfile, const PreflightRuleID& ruleID, UID* pNewRuleUID) = 0;

		/**	Delete athe specified rule
			@param rule IN The rule to delete.
			@param pNewRuleUID OUT If not nil, contains the new rule UID.
		*/
		virtual ErrorCode DeleteRule (const UIDRef& rule) = 0; 

		/**	Returns a list of rule categories supported
			@param allCategories OUT The list of all categories
		*/
		virtual void GetAllCategories(K2Vector<PMString>& allCategories) const = 0;
		/**	Returns a list of rules in the specified category.
			@param category IN The rule category.
			@param rules OUT The list of rules for the specified category.
		*/
		virtual void GetRulesInCategory(const PMString& category, PreflightRuleIDVector& rules) const = 0;

		/**	Returns the category for the specified rule.
			@param rule IN The rule.
			@return the rule category.
		*/
		virtual PMString GetRuleCategory (const UIDRef& rule) const = 0;

		/**	Returns the rule ID for the specified rule.
			@param rule IN The rule.
			@return the rule ID.
		*/
		virtual PreflightRuleID GetRuleID (const UIDRef& rule) const = 0;


		/**	@return true if this rule is enabled in the profile.
		*/
		virtual bool16 IsRuleEnabled (const UIDRef& rule) const = 0;

		/**	Enable or disable the specified rule.
			@param rule IN The rule.
			@param isEnabled IN Enable the rule if true; otherwise disable the rule.
		*/
		virtual ErrorCode EnableRule (const UIDRef& rule, bool isEnabled) = 0;

		/**	Returns the rule description for the specified rule.
			Rule description cannot be edited.
			@param rule IN The rule.
			@return rule description.
		*/
		virtual PMString GetRuleDescription (const UIDRef& rule) const = 0;

		/**	Set rule data for the specified rule.
			@param rule IN The rule.
			@param key IN The data parameter key.
			@param value IN The data parameter value.
			@return kSuccess if data set correctly; otherwise returns kFailure.
		*/
		virtual ErrorCode SetRuleData (const UIDRef& rule, const IPreflightRuleData::Key& key, const ScriptData& value) = 0;

		/**	Get rule data for the specified rule.
			@param rule IN The rule.
			@param key IN The data parameter key.
			@param value OUT The data parameter value corresponding to the key.
			@param pExist OUT If not nil, this is true if the specified data key exists for the rule; otherwise, it is false.
			@return kSuccess if data set correctly; otherwise returns kFailure.
		*/
		virtual ErrorCode GetRuleData (const UIDRef& rule, const IPreflightRuleData::Key& key, ScriptData& value, bool* pExist) const = 0;

		/**	Preflight result related facade.
		*/

		/**	Return true if the active preflight process for the specified database has completed and
			aggregated result are available.
			@param iTargetDB is the database of the preflight process result.
			@return true is results are available; otherwise returns false.
		*/
		virtual bool16 ArePreflightResultsAvailable (IDataBase* iTargetDB) const = 0;

		/**	Return the aggregated result for the active preflight process of the specified database
			@param iTargetDB is the database of the preflight process result.
			@param results is aggregated results.
				The results are formated as key-value pairs:
					document name key (string)		document name (string)
					profile name key (string)		profile name (string)
					ResultEntryKey (string)			list of string arrays entries for error nodes.

				Each of the string array describes an error node with the following:
					1. Node ID (int32)
					2. Error name (string)
					3. Page number (string)
				
		*/
		virtual void GetPreflightResults (IDataBase* iTargetDB, ScriptListData& results) const = 0;

	};

} // namespace Facade
