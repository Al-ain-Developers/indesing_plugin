//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IScriptUtils.h $
//  
//  Owner: Jonathan W. Brown
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
#ifndef __IScriptUtils__
#define __IScriptUtils__

#include "IPMUnknown.h"
#include "IScriptLabel.h"
#include "IScriptPreferences.h"
#include "IScriptRunner.h"

#include "ScriptInfo.h"
#include "Utils.h"

class ICommand ;
class IDocument ;
class IScript ;
class IScriptEvent ;
class IScriptManager ;
class IScriptRequestData ;
class IScriptInfoManager ;
class IScriptRequestHandler ;
class ScriptObject ;

/**
	This prefix is used by IScriptUtils::TranslateKeyStringFromScriptClient()
	to identify key strings passed in from scripting clients.
*/
#define keyStringPrefix "$ID/"
// The wide char version
#define keyStringPrefixW	L"$ID/"

typedef K2Vector< InterfacePtr<IScriptManager> > ScriptManagerList ;

namespace ScriptInfo
{
class ObjectScriptElement ;
}

using namespace ScriptInfo ;


class IScriptUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISCRIPTUTILS };

	/**
		Obtain the IScript interface to the application object
	*/
	virtual IScript* QueryApplicationScript() const = 0;

	/**
		Query a particular ScriptInfoManager
	*/
	virtual IScriptInfoManager* QueryScriptInfoManager( const RequestContext& context ) const = 0 ;

	/**
		Query a particular ScriptRequestHandler
	*/
	virtual IScriptRequestHandler* QueryScriptRequestHandler( const RequestContext& context ) const = 0 ;

	/**
		Get all script managers
	*/
	virtual void GetScriptManagers( ScriptManagerList& mgrs ) const = 0 ;

	/**
		Finds a particular script manager
	*/
	virtual IScriptManager* QueryScriptManager( ClassID boss ) const = 0 ;

	/**
		Finds a script runner that can handle a script file
		@return nil if no script runner can handle the file
	*/
	virtual IScriptRunner* QueryScriptRunner( const IDFile& ) const = 0 ;

	/**
		Return kTrue if any Script Manager has an active script
	*/
	virtual bool16 IsScriptActive() = 0 ;

	/**
		Returns kTrue if the active script context is the script manager for saving to InDesign interchange format
	*/
	virtual bool16 IsINX( const RequestContext& context ) = 0 ;
	virtual bool16 IsINX() = 0 ;

	/**
		Returns kTrue if the active script context is the script manager for INX traditional
	*/
	virtual bool16 IsINXTraditional( const RequestContext& context ) = 0 ;

	/**
		Returns kTrue if the active script context is the script manager for INX expanded
	*/
	virtual bool16 IsINXExpanded( const RequestContext& context ) = 0 ;

	/**
		Returns kTrue if the active script context is the INX script manager during export session
	*/
	virtual bool16 IsINXExport( const RequestContext& context ) = 0 ;

	/**
		Translate a scriptID into its four character code
	*/
	virtual PMString GetScriptID( const ScriptID& scriptID ) = 0;

	/**
		Create a proxy script object
	*/
	virtual IScript* CreateProxyScriptObject( const RequestContext& context, const ClassID& classID, const ScriptID& objectID, const IPMUnknown* parent, int32 index = 0 ) = 0 ;

	/**
		Release all references to script objects in the database (i.e., because the database is closing)
	*/
	virtual void ReleaseAllObjectsInDatabase( IDataBase* db ) const = 0;
	
	/**
		Return the workspace (document or application) for the script object
		@param script is the script object
		@param context is the request context
		@return the workspace for the script object
	*/
	virtual IWorkspace* QueryWorkspaceFromScript( const IScript* script, const RequestContext& context ) = 0 ;

	/**
		Access the document containing a script object
		@param script is the script object
		@param context is the request context
		@return the document containing the script object (or nil if not in a document)
	*/
	virtual IDocument* QueryDocumentFromScript( const IScript* script, const RequestContext& context ) = 0 ;

	/**
		A utility for script providers during their handling of e_Create.
		When handling the create event, there are several cases providers need to deal with:
		1. The simplest case is when no insertion location is provided. In this case ExtractInsertionLocation simply populates
			outLocation with en_Unknown and it is up to the script provider to determine the default behavior.
		2. The user can provide an insertion location of en_Begin or en_End. In this case ExtractInsertionLocation populates
			outLocation with either en_Begin or en_End. outScript will be nil.
		3. The user can also provide another object to insert before or after. In this case ExtractInsertionLocation populates
			outLocation with either en_Before or en_After. outScript will be the object to insert before or after.
		The utility will verify that outScript is in the same database as inScript, but the script provider must verify
			that outScript is a valid type.

		@param inScript is the IScript off the parent object. This is the IScript passed to a create event handler.
		@param inData is the IScriptRequestData passed to the create event.
		@param objectType is the type of object being created.
		@param outLocation will be set to one of five values: en_Unknown, en_Before, en_After, en_Begin, or en_End.
		@param outScript - if outLocation is en_Before or en_After, then this will also be populated
						with the object to insert before or after.
	*/
	virtual ErrorCode ExtractInsertionLocation( IScript* inScript, IScriptRequestData* inData, const ScriptID& objectType, ScriptID& outLocation, InterfacePtr<IScript>& outScript ) = 0 ;

	/**
		A utility for script providers during their handling of e_Move and e_Duplicate.
		@param outLocation is one of the following: en_Before/en_After/en_Begin/en_End
		@param outScript is the object to move before/after at the beginning/end of
	*/
	virtual ErrorCode GetMoveLocation( const IScriptRequestData* inData, ScriptID& outLocation, InterfacePtr<IScript>& outScript ) = 0 ;

	/**
		Returns kTrue if the value of the param is the Nothing enumeration
	*/
	virtual bool16 IsNothing( const ScriptData& scriptData ) = 0 ;

	/**
		Generate a text specifier for a scriptable object.
		This specifier can be resolved to retrieve the object.
		@param context IN the request context
		@param object IN the object to convert
		@param specifier OUT the generated specifier
		@param form IN the desired specifier format
	*/
	virtual ErrorCode GenerateSpecifier( const EngineContext& context, const IScript* object, PMString& specifier, SpecifierForm form = kFormDefault ) = 0 ;

	/**
		Generate a text specifier for a scriptable object as two parts: the workspace and the object.
		This specifier can be concatenated and resolved to retrieve the object.
		@param context IN the request context
		@param object IN the object to convert
		@param workSpaceSpecifier OUT the generated specifier for the workspace
		@param objectSpecifier OUT the generated specifier for the object
		@param form IN the desired specifier format
	*/
	virtual ErrorCode GenerateSpecifier( const EngineContext& context, const IScript* object, PMString& workSpaceSpecifier, PMString& objectSpecifier, SpecifierForm form = kFormDefault ) = 0 ;

	/**
		Generate a text specifier for a list of scriptable objects.
		This specifier can be resolved to retrieve the objects.
		@param context IN the request context
		@param objects IN the objects to convert
		@param specifier OUT the generated specifier
		@param form IN the desired specifier format
	*/
	virtual ErrorCode GenerateListSpecifier( const EngineContext& context, const ScriptList& objects, PMString& specifier, SpecifierForm form = kFormDefault ) = 0 ;

	/**
		Combine two specfiers to generate a range specifier for scriptable objects.
		This specifier can be resolved to retrieve the objects.
		@param context IN is the request context
		@param fromSpecifier IN a specifier for the "from" part of the range
		@param toSpecifier IN a specifier for the "to" part of the range
		@param specifier OUT the generated specifier
	*/
	virtual ErrorCode GenerateRangeSpecifier( const EngineContext& context, const PMString& fromSpecifier, const PMString& toSpecifier, PMString& specifier ) = 0 ;

	/**
		Append the specifier for a scripting object to an existing specifier.
		@param context IN the request context
		@param objectScriptElement IN an ObjectScriptElement describing the object
		@param scriptObject IN a ScriptObject describing the specific instance of the object
		@param specifier IN/OUT the specifier onto which to append
	*/
	virtual ErrorCode AppendSpecifier( const EngineContext& context, const ScriptInfo::ObjectScriptElement* objectScriptElement, const ScriptObject& scriptObject, PMString& specifier ) = 0 ;

	/**
		Resolve an object specifier into a list of objects.
		@param context IN the request context
		@param specifier IN the object specifier to resolve
		@param resolvedObjects OUT the list of objects that were specified
	*/
	virtual ErrorCode ResolveSpecifier( const EngineContext& context, const PMString& specifier, ScriptList& resolvedObjects ) = 0 ;

	/**
		Resolve an object specifier into a list of objects.
		@param context IN the request context
		@param workSpaceSpecifier IN the workspace specifier to resolve
		@param objectSpecifier IN the object specifier to resolve
		@param resolvedObjects OUT the list of objects that were specified
	*/
	virtual ErrorCode ResolveSpecifier( const EngineContext& context, const PMString& workSpaceSpecifier, const PMString& objectSpecifier, ScriptList& resolvedObjects ) = 0 ;

	/*
		Find a common base object for two types of objects.
		@param si1 is the first type of object
		@param si2 is the second type of object
		@return the object info for their common base object or nil if there isn't one
	*/
	virtual const ObjectScriptElement* GetCommonBaseInfo( const ObjectScriptElement* si1, const ObjectScriptElement* si2 ) const = 0 ;

	/**
		Returns the folder in which scripting support files are stored.
		@param &outFolder IDFile of scripting support folder
		@return kSuccess or kFailure
	*/
	virtual ErrorCode GetScriptingSupportFolder( const RequestContext& context, IDFile& outFolder ) const = 0 ;

	/**
		Appends the folder in which scripting resources such as VB typelibs, AETE resources are stored.
		@param &sysFile IDFile of scripting support folder to append to
	*/
	virtual void AppendDirectoryForDOMVersion( const RequestContext& context, IDFile& sysFile ) const = 0 ;

	/**
		Executes the command to set a script label
		@param scriptList is the list of target objects
		@param context is the request context
		@param label is the label to set
		@param key is the key for the label, if any
	*/
	virtual ErrorCode SetScriptingTag( const ScriptList& scriptList, const EngineContext& context, 
									   const IScriptLabel::ScriptLabelValue& label, 
									   const IScriptLabel::ScriptLabelKey& key = IScriptLabel::kDefaultScriptLabelKey ) const = 0 ;
	/**
		Executes the command to set multiple script labels
		@param scriptList is the list of target objects
		@param context is the request context
		@param labels are the labels to set
		@param replaceExistingLabels if kTrue, instructs command to first remove all existing labels and insert 
			the newly supplied ones; if kFalse, instructs command to append labels whose keys are not found in 
			the existing set of labels, and replace labels whose keys are found in the existing set of labels
	*/
	virtual ErrorCode SetScriptingTags( const ScriptList& scriptList, const EngineContext& context, 
										const IScriptLabel::ScriptLabelKeyValueList& labels,
										bool16 replaceExistingLabels = kFalse ) const = 0 ;

	/**
		GetScriptsFolder returns the folder containing the user's scripts panel scripts.
		This is the folder the Scripts Panel displays for User scripts.
		In CS2, this was the folder named "Scripts" in the application's "Presets" folder.
		In CS3, this is the folder named "Scripts Panel" in the user's InDesign preferences' "Scripts" folder.
		@param scriptsFolder is the scripts folder [out]
		@param resolveAlias - if true, the value returned in the scriptsFolder parameter is resolved if 
			it's an alias/shortcut [in]
	*/
	virtual ErrorCode GetScriptsFolder( IDFile& scriptsFolder, bool16 resolveAlias ) const = 0 ;

	/**
		Extracts a ScriptVersion from a p_Version property. 	
		@param data IN The IScriptRequestData to get the 
		@param internalVersion OUT Will be set based on data
		@return kSuccess if the property can be extracted, otherwise an appropriate error code.
	*/
	virtual ErrorCode ExtractVersion( IScriptRequestData* data, ScriptVersion& internalVersion ) const = 0 ;

	/**
		Dispatch a script to the appropriate script runner.
		@param scriptRunner is the desired script runner to use to execute the script (or nil if not known) IN
		@param script is the script to execute (may be a String, a File, or a Function) IN
		@param arguments is used to pass arguments to the script IN
		@param result is the return value OUT
		@param errorString is the error string OUT
		@param showErrorAlert if kTrue show an error alert if an error occurs IN
		@param invokeDebugger indicates whether to load script into debugger for execution IN
		@param undoMode indicates how to handle undo for document changes made by the script IN
		@param undoName is the name for the undo step in single undo step mode IN
		@param domVersion is the desired version of the DOM in which to execute the script.
			For script files, defaults to the version of the DOM corresponding to the current version of the application (unless the file is in a "Version X.X Folder").
			Ignored for text scripts, which use the version of the DOM currently set.
			Ignored for function callbacks, which use the version of the DOM in the function's context.
		@return kSuccess or an error
	*/
	virtual ErrorCode DispatchScriptRunner( IScriptRunner* scriptRunner, const ScriptData& script, 
											const ScriptRecordData& arguments, ScriptData& result, 
											PMString& errorString, const bool16 showErrorAlert,
											const bool16 invokeDebugger = kFalse,
											const RunScriptParams::UndoMode undoMode = RunScriptParams::kUndoScriptRequest, 
											const PMString& undoName = PMString(),
											const ScriptVersion& domVersion = ScriptVersion() ) const = 0 ;

	/**
		Clear the script provider cache. Call this if you are implementing your own script manager
		when the active script state changes. @see IncrementActiveScriptCount and
		@see DecrementActiveScriptCount.
	*/
	virtual void ClearScriptProviders() const = 0 ;

	/**
		Execute a command to set the application script prefs
		@param redraw is whether to enable redraw during script execution
	*/
	virtual ErrorCode SetAppScriptPrefs( bool16 redraw ) const = 0 ;

	/**
		If a scripting client hands us a string that begins with the keyStringPrefix ("$ID/"), we assume
		it is a key string, and we use this method to translate it (after dropping the prefix).
		@param s is the string to translate
		@return is kTrue if the string was a key string (and got translated)
	*/
	virtual bool16 TranslateKeyStringFromScriptClient( PMString& s ) const = 0 ;

	/** Turns off idle processing during scripting. When idle processing is disabled,
		scheduled command will NOT be executed, idle task handlers will NOT
		be executed, and no user cancel events will be detected.
		Note: Must be paired with EnableIdleProcessingDuringScripts() call.
		Given the effect on command processing, use this API with extreme caution.
	*/
	virtual void DisableIdleProcessingDuringScripts() = 0 ;

	/** Turns back on idle processing during scripting. 
		Note: Used with DisableIdleProcessingDuringScripts() call.
	*/
	virtual void EnableIdleProcessingDuringScripts() = 0 ;

	/** Checks if idle processing is enabled during scripting. When idle processing is
		disabled, scheduled command will NOT be executed, idle task handlers will NOT
		be executed, and no user cancel events will be detected.
	*/
	virtual bool16 IsIdleProcessingEnabledDuringScripts() const = 0 ;
	
	/**
	 INTERNAL USE ONLY
	 Dispatch a script to the appropriate script runner.
	 @param scriptRunner is the desired script runner to use to execute the script (or nil if not known) IN
	 @param script is the script to execute (may be a String, a File, or a Function) IN
	 @param evalStringAsFilePath if kTrue evaluate if the script string is a file path IN
	 @param arguments is used to pass arguments to the script IN
	 @param result is the return value OUT
	 @param errorString is the error string OUT
	 @param showErrorAlert if kTrue show an error alert if an error occurs IN
	 @param invokeDebugger indicates whether to load script into debugger for execution IN
	 @param undoMode indicates how to handle undo for document changes made by the script IN
	 @param undoName is the name for the undo step in single undo step mode IN
	 @param domVersion is the desired version of the DOM in which to execute the script.
	 For script files, defaults to the version of the DOM corresponding to the current version of the application (unless the file is in a "Version X.X Folder").
	 Ignored for text scripts, which use the version of the DOM currently set.
	 Ignored for function callbacks, which use the version of the DOM in the function's context.
	 @return kSuccess or an error
	 */
	virtual ErrorCode DispatchScriptRunner( IScriptRunner* scriptRunner, const ScriptData& script, bool16 evalStringAsFilePath,
										   const ScriptRecordData& arguments, ScriptData& result,
										   PMString& errorString, const bool16 showErrorAlert,
										   const bool16 invokeDebugger = kFalse,
										   const RunScriptParams::UndoMode undoMode = RunScriptParams::kUndoScriptRequest,
										   const PMString& undoName = PMString(),
										   const ScriptVersion& domVersion = ScriptVersion() ) const = 0 ;
};

	/** This stack-based class can be used in a scope where you want to turn
		off idle processing during scripts. When idle processing is disabled,
		scheduled command will NOT be executed, idle task handlers will NOT
		be executed, and no user cancel events will be detected.
		Given the effect on command processing, use this API with extreme caution
		and only when absolutely necessary.
	*/
class DisableIdleProcessingDuringScripts
{
public:
	DisableIdleProcessingDuringScripts()
	{
		Utils<IScriptUtils>()->DisableIdleProcessingDuringScripts() ;
	}
	~DisableIdleProcessingDuringScripts()
	{
		Utils<IScriptUtils>()->EnableIdleProcessingDuringScripts() ;
	}
} ;

#endif	// __IScriptUtils__
