//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpShareAppResources.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "VCPlugInHeaders.h"
#include "SnipRunID.h"
#include "SnippetID.h"

// Interface includes:
#include "IAppPrefsImportOptions.h"
#include "IDataBase.h"
#include "IScript.h"
#include "IScriptUtils.h"
#include "ISnippetExport.h"
#include "ISnippetImport.h"
#include "ISnipRunParameterUtils.h"
#include "IWorkspace.h"
#include "IDOMElement.h"

// General includes:
#include "AppPrefsListElementTypes.h"
#include "FileUtils.h"
#include "IDFile.h"
#include "StreamUtil.h"
#include "ScriptingDefs.h"

// Framework includes:
#include "SnpRunnable.h"
#include "SnipRunLog.h"

/** 
	\li	How to export and import application preferences, text styles, XML tags, object styles, and swatches.

	This code contains seven export methods and two import method.  The
	seven export methods show how to export the previously mentioned application
	resources as INX Snippets.  The two import methods import any one of these INX 
	Snippets into the application.  The difference is ImportToAppWithOptions()
	shows how to set import options before importing.

	For simplicity the 7 exports all write out a file named SnpShareAppResources.xml 
	in the users application preference folder.  The import methods read in this
	file, updating the specified resources.

	Note: This also runs in InCopy, but you will run into several instances of an 
	assert in the debug build.  The assert is related to the scriptability of a UI 
	color used in InCopy.  It's a bug, but it's safe to ignore.
	
  	@ingroup sdk_snippet
 */
class SnpShareAppResources 
{
public:

	/** Constructor.
	 */
	SnpShareAppResources() {}

	/** Destructor.
	 */
	virtual			~SnpShareAppResources() {}

	/** Shows how to exort all preference objects in the scripting DOM
		
	@return  kSuccess on success, or kFailure or another ErrorCode value identifying the error.
	@postcondition Creates SnpShareAppResources.xml in the user's  preference folder.
	*/
	ErrorCode	ExportAppWorkspace();
	
	/** Shows how to limit an export to some set of scripting preference objects.  In this
		case it exports everything that is known to live in the preferences panel.
		
	@return  kSuccess on success, or kFailure or another ErrorCode value identifying the error.
	@postcondition Creates SnpShareAppResources.xml in the user's  preference folder.
	*/
	ErrorCode	ExportPrefsPanel();
	
	/** Shows how to export everything except some excluded set of objects.  In this case
		the excluded set is taken from AppPrefsListElementTypes.h, which holds a list off
		all InDesign's native list element types of preference objects.  This includes list of
		items such as paragraph and character styles, swatches, XML tags, etc.
		
	@return  kSuccess on success, or kFailure or another ErrorCode value identifying the error.
	@postcondition Creates SnpShareAppResources.xml in the user's  preference folder.
	*/
	ErrorCode	ExportPrefsAndDefaults();
	
	/** Shows how to export all character and paragraph styles.
	@return  kSuccess on success, or kFailure or another ErrorCode value identifying the error.
	@postcondition Creates SnpShareAppResources.xml in the user's  preference folder.
	*/
	ErrorCode	ExportTextStyles();

	/** Shows how to export all object styles.
	@return  kSuccess on success, or kFailure or another ErrorCode value identifying the error.
	@postcondition Creates SnpShareAppResources.xml in the user's  preference folder.
	*/
	ErrorCode	ExportObjectStyles();
	
	/** Shows how to export all XML tags and related preferences.
	@return  kSuccess on success, or kFailure or another ErrorCode value identifying the error.
	@postcondition Creates SnpShareAppResources.xml in the user's  preference folder.
	*/
	ErrorCode	ExportXMLTagsAndPrefs();
	
	/** Shows how to export all swatches in the swatches panel.
	@return  kSuccess on success, or kFailure or another ErrorCode value identifying the error.
	@postcondition Creates SnpShareAppResources.xml in the user's  preference folder.
	*/
	ErrorCode	ExportSwatches();

	/** Imports the INX Snippets back into the application.
	@precondition  A valid INX snippet named SnpShareAppResources.xml should exist in the users preference folder.
				Run one of the export routines to create one.
	@return  kSuccess on success, or kFailure or another ErrorCode value identifying the error.
	@postcondition The application defaults and preferences should be updated.
	*/
	ErrorCode	ImportToApp();

	/** Temporarily sets IAppPrefsImportOptions and Imports the INX Snippets back into the application.
		The IAppPrefsImportOptions interface is used to specify a policy for dealing with matching and 
		non-matching existing items in lists.  For example, if you have three Paragraph Styles A,B, and C, 
		what happens if you import Paragraph Styles B and C.  You could or delete A. And, you could keep 
		or replace B and C.
	@precondition  A valid INX snippet named SnpShareAppResources.xml should exist in the users preference folder.
				Run one of the export routines to create one.
	@return  kSuccess on success, or kFailure or another ErrorCode value identifying the error.
	@postcondition The application defaults and preferences should be updated.
	*/
	ErrorCode	ImportToAppWithOptions();


private:

	/** Utility method for creating the appropriate in or out stream
	@return A valid pointer to an IPMStream instance on success.
	@postcondition The caller will be responsible for calling Release() on this object.
	*/
	IPMStream *	CreateStream(IPMStream::_StreamType type) const;


	
};

/* CreateOutStream()
*/
IPMStream * SnpShareAppResources::CreateStream(IPMStream::_StreamType type) const
{
	//This creates a read or write stream for SnpShareAppResources.xml in the preferences folder.
	// If we are writing, it will overwrite an existing file, so if you want to compare a couple of these
	// exports then you'll have to save off the file manually.
	IDFile preferenceSetFile;
	bool16 gotFile = FileUtils::GetAppRoamingDataFolder(&preferenceSetFile, "SnpShareAppResources.xml");
	ASSERT(gotFile);
	if( ! gotFile )
		return nil;
    
	IPMStream * stream = nil;

	switch( type )
	{
	case IPMStream::kReader:
		SNIPLOG("Opening \"%s\" for reading.", FileUtils::SysFileToPMString(preferenceSetFile).GetPlatformString().c_str());
		stream = StreamUtil::CreateFileStreamRead(preferenceSetFile);
		break;

	case IPMStream::kWriter:
		SNIPLOG("Opening \"%s\" for writing.", FileUtils::SysFileToPMString(preferenceSetFile).GetPlatformString().c_str());
		stream = StreamUtil::CreateFileStreamWrite(preferenceSetFile, kOpenOut | kOpenTrunc);
		break;

	default:
		ASSERT_FAIL("Unexpected case in SnpShareAppResources::CreateStream()");
		break;
	}

	if( stream == nil)
		SNIPLOG("Failed to open \"%s\" in SnpShareAppResources::CreateStream().",FileUtils::SysFileToPMString(preferenceSetFile).GetPlatformString().c_str());

	return stream;
}

/* ExportAppWorkspace()
*/
ErrorCode SnpShareAppResources::ExportAppWorkspace()
{
	InterfacePtr<IPMStream> stream( CreateStream(IPMStream::kWriter) );
	ASSERT( stream );
	if( ! stream )
		return kFailure;

	return Utils<ISnippetExport>()->ExportAppPrefs( stream );
}

/* ExportPrefsPanel()
*/
ErrorCode SnpShareAppResources::ExportPrefsPanel()
{
	// This shows how to export the prefs in the preference panel.
	// What we need to do is pass in a list of ScriptIDs for each of the
	// preference objects that provide access to these preferences.

	// This list was built by trial and error.  The challenge is mapping
	// IDs in ScriptingDefs.h to the User Interface.  Also, there were
	// a couple of scripting bugs or omissions discovered.  Please see
	// the Shared Resources technote for information regarding which widgets
	// are not properly scriptable.

	K2Vector<ScriptID>  idList;
	idList.push_back(c_GeneralPrefs);
	idList.push_back(c_ClipboardPrefs);
	idList.push_back(c_AutoCorrectPref);
	idList.push_back(c_DictPref);
	idList.push_back(c_SpellPref);
	idList.push_back(c_GridPref);
	idList.push_back(c_DocPref);
	idList.push_back(c_GuidePref);
	idList.push_back(c_PasteboardPref);
	idList.push_back(c_ImageIOPref);
	idList.push_back(c_TextOptPref);
	idList.push_back(c_TextEditingPref);
	idList.push_back(c_DefViewSettingPref);
	idList.push_back(c_ViewPref);
	idList.push_back(c_NotePref);
	idList.push_back(c_GalleyPref);
	idList.push_back(c_TrackChangesPref);
	idList.push_back(c_CJKGridPreferences);
	idList.push_back(c_MojikumiUIPref);
	idList.push_back(c_IMEPref);

	InterfacePtr<IPMStream> stream( CreateStream(IPMStream::kWriter) );
	ASSERT( stream );
	if( ! stream )
		return kFailure;

	return Utils<ISnippetExport>()->ExportAppPrefs( stream , ISnippetExport::kInclude, idList );
}

/* ExportPrefsAndDefaults()
*/
ErrorCode SnpShareAppResources::ExportPrefsAndDefaults()
{
	// AppPrefsListElementTypes contains a list of all the internal list types InDesign
	// will export by default.

	// Convert from std::set to K2Vector
	K2Vector<ScriptID>  idList;
	const std::set<ScriptID>& listElementTypes = AppPrefsListElementTypes::GetListElementTypes();
	for ( std::set<ScriptID>::const_iterator itr = listElementTypes.begin(); itr != listElementTypes.end(); itr++)
	{
		ScriptID preferenceID = *itr;
		idList.push_back(preferenceID);
	}

	// NOTE: If a non-Adobe plug-in has added list element preference types to the scripting DOM, 
	// and you don't want these exported, then you would need to add those ScriptIDs to idList here.

	// Create the stream
	InterfacePtr<IPMStream> stream( CreateStream(IPMStream::kWriter) );
	ASSERT( stream );
	if( ! stream )
		return kFailure;
	
	// Export all the preferences except the list of items.
	return Utils<ISnippetExport>()->ExportAppPrefs( stream , ISnippetExport::kExclude, idList );
}

/* ExportTextStyles()
*/
ErrorCode SnpShareAppResources::ExportTextStyles()
{
	// Exporting all text styles is pretty simple.
	// The thing to keep in mind is these styles may contain references to other 
	// objects (like swatches).  These other objects (if scriptable) will be 
	// brought along by the snippet architecture.

	K2Vector<ScriptID>  idList;

	idList.push_back(c_CharStyle);
	idList.push_back(c_ParaStyle);

	InterfacePtr<IPMStream> stream( CreateStream(IPMStream::kWriter) );
	ASSERT( stream );
	if( ! stream )
		return kFailure;

	return Utils<ISnippetExport>()->ExportAppPrefs( stream , ISnippetExport::kInclude, idList );
}

/* ExportObjectStyles()
*/
ErrorCode SnpShareAppResources::ExportObjectStyles()
{
	// Exporting all object styles is pretty simple.
	// The thing to keep in mind is these styles may likely contain references to other 
	// styles.  These other objects styles (if scriptable) will be 
	// brought along by the snippet architecture.

	K2Vector<ScriptID>  idList;

	idList.push_back(c_ObjectStyle);

	InterfacePtr<IPMStream> stream( CreateStream(IPMStream::kWriter) );
	ASSERT( stream );
	if( ! stream )
		return kFailure;

	return Utils<ISnippetExport>()->ExportAppPrefs( stream , ISnippetExport::kInclude, idList );
}

/* ExportXMLTagsAndPrefs()
*/
ErrorCode SnpShareAppResources::ExportXMLTagsAndPrefs()
{
	// This code exports XML tags and other preferences.

	K2Vector<ScriptID>  idList;

	idList.push_back(c_XMLPreferences);
	idList.push_back(c_XMLTagToStyleMap);
	idList.push_back(c_XMLStyleToTagMap);
	idList.push_back(c_XMLTag);
	idList.push_back(c_XMLViewPref);

	InterfacePtr<IPMStream> stream( CreateStream(IPMStream::kWriter) );
	ASSERT( stream );
	if( ! stream )
		return kFailure;

	return Utils<ISnippetExport>()->ExportAppPrefs( stream , ISnippetExport::kInclude, idList );
}

/* ExportSwatches()
*/
ErrorCode SnpShareAppResources::ExportSwatches()
{
	// This code shows how to export all the swatches in the swatches  panel.
	// The thing to notice here is that instead of exporting c_Swatch, we end up
	// exporting the individual swatch types.  In the scripting DOM each of these
	// individual swatch types is a type of swatch.  One might expect specifying
	// c_Swatch would export all types of swatches, however, this API doesn't 
	// understand this level of inheritance, so you must specify the individual
	// swatch types.  Nothing is exported if you only specify c_Swatch.
	K2Vector<ScriptID>  idList;
	idList.push_back(c_Color);
	idList.push_back(c_Gradient);
	idList.push_back(c_Tint);
	idList.push_back(c_Ink);

	InterfacePtr<IPMStream> stream( CreateStream(IPMStream::kWriter) );
	ASSERT( stream );
	if( ! stream )
		return kFailure;

	return Utils<ISnippetExport>()->ExportAppPrefs( stream , ISnippetExport::kInclude, idList );
}

/* ImportToApp()
*/
ErrorCode SnpShareAppResources::ImportToApp()
{
	// Here we create a stream from the known file and import it into the application.
	InterfacePtr<IPMStream> stream( CreateStream(IPMStream::kReader));
	if( ! stream )
		return kFailure;

	// Notice that the root objects is set to the Application.
	InterfacePtr<IScript> appScript(Utils<IScriptUtils>()->QueryApplicationScript());
	InterfacePtr<IDOMElement> rootXMLFragment(appScript, UseDefaultIID());
	return Utils<ISnippetImport>()->ImportFromStream( stream, rootXMLFragment );
}

/* ImportToAppWithOptions()
*/
ErrorCode SnpShareAppResources::ImportToAppWithOptions()
{
	// There are a couple decisions that need to be made when importing.
	//
	// These options persist on the session workspace in an instance
	// of IAppPrefsImportOptions.  To set these options all you  have to
	// do is query for that instance of IAppPrefsImportOptions and call
	// the appropriate set method.  That implemenation in turns takes
	// creates and processes a command to change it's own state.
	//
	// First, snippet import needs to know what to do when list items
	// already in the app match those that are being imported.
	// To set the policy for this call SetHandleListItemsWithMatchingNames
	// with either kUseExistingListItems or kReplaceListItems.  These
	// are available on an enumeration in the IAppPrefsImportOptions interface.
	// The default value is kReplaceListItems, but that can change so it's
	// wise to explicitly set this value as one in this method.
	//
	// Next, snippet import needs to know what to do when items exist
	// in the list that are not being imported.  You can either delete
	// everything that is not in the imported list, or you can leave existing
	// items alone.  To set this policy call SetDeleteNonImportedListItems 
	// with kTrue or kFalse.  When called with kTrue, items not in the imported
	// list will be deleted.  This is the default behavior, but again it's 
	// wise to be explicit about what you want.
	//
	// So, for instance, if you want to completely restore lists such as paragraph 
	// styles to exported snippets, you set the above two properties to 
	// kReplaceListItems and kTrue.  This will replace any existing list items and 
	// delete list items not in the import.  This is the default behavior, but
	// you should be explicit.
	//
	
	//  Save the current state of the options (I'm only doing this because I want to
	//	restore the state at the end of this method.)
	InterfacePtr<IAppPrefsImportOptions>    appPrefsImportOptions((IAppPrefsImportOptions*)GetExecutionContextSession()->QueryWorkspace(IID_IAPPPREFSIMPORTOPTIONS));
	IAppPrefsImportOptions::ListImportMatchAction matchPolicy = appPrefsImportOptions->HandleListItemsWithMatchingNames();
	bool16 deletePolicy = appPrefsImportOptions->DeleteNonImportedListItems();

	// Set Options to non-default values
	appPrefsImportOptions->SetHandleListItemsWithMatchingNames(IAppPrefsImportOptions::kUseExistingListItems);
	appPrefsImportOptions->SetDeleteNonImportedListItems( kFalse );

	ErrorCode result = this->ImportToApp();

	// Restore options
	appPrefsImportOptions->SetHandleListItemsWithMatchingNames(matchPolicy);
	appPrefsImportOptions->SetDeleteNonImportedListItems( deletePolicy );

	return result;
}


// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------
class _SnpRunnerShareAppResources : public SnpRunnable
{
	public:
		// SnippetRunner framework hooks.

		/** Constructor.
		 */
		_SnpRunnerShareAppResources();

		/** Destructor.
		 */
		virtual			~_SnpRunnerShareAppResources();

		/** Return kTrue if the snippet can run.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kTrue if snippet can run, kFalse otherwise
		 */
		bool16			CanRun(ISnpRunnableContext* runnableContext);

		/** Run the snippet.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode		Run(ISnpRunnableContext* runnableContext);
		
		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunNoContext;}
};


/* Constructor.
*/
_SnpRunnerShareAppResources::_SnpRunnerShareAppResources() : SnpRunnable("ShareAppResources")
{
	this->SetDescription("Manage Shared Resources");
	this->SetPreconditions("none");
	this->SetCategories("sdk_snippet");
}

/* Destructor.
*/
_SnpRunnerShareAppResources::~_SnpRunnerShareAppResources()
{
}

/*
*/
bool16	_SnpRunnerShareAppResources::CanRun(ISnpRunnableContext* runnableContext)
{
	return kTrue;
}

/* _SnpRunnerShareAppResources::Run
*/
ErrorCode _SnpRunnerShareAppResources::Run(ISnpRunnableContext* runnableContext)
{
	// This method presents a choice dialog for the user
	// and then calls the appropriate SnpShareAppResources method.

	SnpShareAppResources instance;
	
	// Initialize "choice" strings	
	const PMString EXPORTAPPWORKSPACE = "Export App Workspace";
	const PMString EXPORTPREFSPANEL = "Export Prefs";
	const PMString EXPORTPREFSANDDEFAULTS = "Export Prefs and Defaults";
	const PMString EXPORTTEXTSTYLES = "Export Text Styles";
	const PMString EXPORTOBJECTSTYLES = "Export Object Styles";
	const PMString EXPORTXMLTAGSANDPREFS = "Export XML Tags and Prefs";
	const PMString EXPORTSWATCHES = "Export Swatches";
	const PMString IMPORTTOAPP = "Import To Application";
	const PMString IMPORTTOAPPWITHOPTIONS = "Import To App With Options";

	// Create a K2Vector containing the strings which will become
	// the choices presented to the user in a drop down.
	K2Vector<PMString> choices;
	choices.push_back(PMString(EXPORTAPPWORKSPACE));
	choices.push_back(PMString(EXPORTPREFSPANEL));
	choices.push_back(PMString(EXPORTPREFSANDDEFAULTS));
	choices.push_back(PMString(EXPORTTEXTSTYLES));
	choices.push_back(PMString(EXPORTOBJECTSTYLES));
	choices.push_back(PMString(EXPORTXMLTAGSANDPREFS));
	choices.push_back(PMString(EXPORTSWATCHES));
	choices.push_back(PMString(IMPORTTOAPP));
	choices.push_back(PMString(IMPORTTOAPPWITHOPTIONS));

	// Present choice drop down.
	Utils<ISnipRunParameterUtils> parameterUtils;
	int32 i =(parameterUtils->GetChoice(PMString("Manage Shared Resources"), choices, 0));
	if (parameterUtils->WasDialogCancelled()) {
		return kCancel;
	}
	
	// Check the results and call the appropriate method
	ErrorCode status = kFailure;
	if( choices[i].IsEqual(EXPORTAPPWORKSPACE))
		status = instance.ExportAppWorkspace();
	else if( choices[i].IsEqual(EXPORTPREFSPANEL))
		status = instance.ExportPrefsPanel();
	else if( choices[i].IsEqual(EXPORTPREFSANDDEFAULTS))
		status = instance.ExportPrefsAndDefaults();
	else if( choices[i].IsEqual(EXPORTTEXTSTYLES))
		status = instance.ExportTextStyles();
	else if( choices[i].IsEqual(EXPORTOBJECTSTYLES))
		status = instance.ExportObjectStyles();
	else if( choices[i].IsEqual(EXPORTXMLTAGSANDPREFS))
		status = instance.ExportXMLTagsAndPrefs();
	else if( choices[i].IsEqual(EXPORTSWATCHES))
		status = instance.ExportSwatches();
	else if( choices[i].IsEqual(IMPORTTOAPP))
		status = instance.ImportToApp();
	else if( choices[i].IsEqual(IMPORTTOAPPWITHOPTIONS))
		status = instance.ImportToAppWithOptions();

	if( status == kSuccess )
		SNIPLOG("ShareAppResources finished with a success");
	else
		SNIPLOG("ShareAppResources finished with a failure");

	return status;
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerShareAppResources instance_SnpRunnerShareAppResources;
DEFINE_SNIPPET(_SnpRunnerShareAppResources) 	

// End, SnpShareAppResources.cpp

