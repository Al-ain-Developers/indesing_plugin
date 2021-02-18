//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpAddMediaFile.cpp $
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
//  Copyright 1997-2008 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IBehaviorEventData.h"
#include "ICmdCollection.h"
#include "ICommandFactory.h"
#include "IComposeScanner.h"
#include "IDocument.h"
#include "IDataBase.h"
#include "IGraphicFrameData.h"
#include "IHierarchy.h"
#include "IPageList.h"
#include "ISpreadList.h"
#include "ISwatchList.h"
#include "IUIDData.h"
#include "IWorkspace.h"
#include "ILayerUtils.h"
#include "IControlView.h"
#include "IMediaSuite.h"
#include "IMediaUtils.h"
#include "IMediaInfo.h"
#include "IImportExportFacade.h"
#include "IURIUtils.h"
#include "IPageSetupPrefs.h"
#include "IPlaceGun.h"
#include "IDocumentCommands.h"
#include "INewDocCmdData.h"
#include "IFrameContentFacade.h"

// General includes:
#include "DynamicDocumentsID.h"
#include "FileTypeRegistry.h"
#include "FileUtils.h"
#include "PMRect.h"
#include "SDKFileHelper.h"
#include "SDKLayoutHelper.h"
#include "SnipRunLog.h"
#include "StreamUtil.h"
#include "TextRange.h"
#include "UIDList.h"
#include "Utils.h"
#include "BehaviorTypes.h"
#include "IPMStream.h"
#include "PreferenceUtils.h" 


// Framework includes:
#include "SnpRunnable.h"
#include "SnpGraphicHelper.h"
#include "SnpTextAttrHelper.h"
#include "SnpTextModelHelper.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/** 
	\li	Shows how to Create a Multi-State object and how to transition between states.

  	@ingroup sdk_snippet

 */
class SnpAddMediaFile
{
	public:
		/** Builds a Multi-State object on a new document and adds buttons to transition between states.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode AddMediaFile(ISnpRunnableContext* runnableContext);

	private:
		SDKLayoutHelper fLayoutHelper;

		ErrorCode CreateDocument(UIDRef & documentUIDRef, const PMReal width, const PMReal height, const uint32 numPages, const uint32 pagesPerSpread );
		ErrorCode ChooseFileToOpen(IDFile& chosenFile);
};


/*
*/
ErrorCode SnpAddMediaFile::AddMediaFile(ISnpRunnableContext* runnableContext)
{
	ErrorCode result;

	//Create a new document with intent set for for web.
	UIDRef documentUIDRef;
	result = CreateDocument(documentUIDRef,
				500, // Width
				500, // Height
				1,   // Number of Pages
				1);  // Number of Pages Per Spread
	if( result != kSuccess )
		return result;

	// Open a view onto the document.
	result = fLayoutHelper.OpenLayoutWindow(documentUIDRef);
	if( result != kSuccess )
		return result;

	//Browse for media file to import.
	IDFile file;
	result = ChooseFileToOpen(file);
	if( result != kSuccess )
		return result;

	//Get the path to the media file selected.
	SDKFileHelper fileHelper(file);
	SNIPLOG("Chosen file or folder was %s", fileHelper.GetPath().GetPlatformString().c_str());
	PMString filePath = fileHelper.GetPath();

	//Get spread layer reference
	InterfacePtr<ISpreadList> spreadList(documentUIDRef, UseDefaultIID()); 
    if(!spreadList) { 
        return kFailure;
    } 
	SDKLayoutHelper layoutHelper;
	UIDRef spreadRef = UIDRef(documentUIDRef.GetDataBase(), spreadList->GetNthSpreadUID(0)); 
    UIDRef spreadLayerRef = layoutHelper.GetActiveSpreadLayerRef(spreadRef); 

	//Create the bounds for the page item which will contain the media file.
	PMPoint startPoint(-200, -100);	// Upper Left in Page Coords
	PMPoint endPoint(400, 200);		// Size of rectangle
	endPoint += startPoint;
	PMRect bounds(startPoint, endPoint);

	UIDRef pageItemUIDRef = fLayoutHelper.CreateRectangleFrame(spreadLayerRef, bounds);
	if( pageItemUIDRef == kInvalidUIDRef )
		return kFailure;	

	URI uri;
	if (!Utils<IURIUtils>()->IDFileToURI(file, uri)) 
        return kFailure; 

	//Import the media file
	Utils<Facade::IImportExportFacade> iFacade;		
	result = iFacade->ImportAndLoadPlaceGun(documentUIDRef.GetDataBase(), uri, kSuppressUI, kTrue /*retainFormat*/, kTrue /*convertQuotes*/, kTrue /*applyCJKGrid*/, kTrue /*useClippingFrame*/, IPlaceGun::kAddToBack  /*location*/);
	if( result != kSuccess )
		return result;
	
	//Place media file inside the page item
	UIDList replaceList;
	IDataBase * db = documentUIDRef.GetDataBase();
	InterfacePtr<IPlaceGun> placeGun(documentUIDRef.GetDataBase(), documentUIDRef.GetDataBase()->GetRootUID(), UseDefaultIID());
	result = iFacade->ReplacePageItem(db , pageItemUIDRef.GetUID(), placeGun->GetFirstPlaceGunItemUID(), kFalse, replaceList ) ; 
	if( result != kSuccess )
		return result;

	//Fit page item frame to fit the media file
	result =  Utils<Facade::IFrameContentFacade>()->FitFrameToContent (replaceList); 
	if( result != kSuccess )
		return result;

	//Get Skin Names
	K2Vector<IDFile> skins;
	K2Vector<PMString> skinNames;
	Utils<IMediaUtils>()->GetInstalledVideoSkins(skins);
	for (K2Vector<IDFile>::const_iterator i = skins.begin(), end = skins.end(); i != end; ++i) 
	{ 
		PMString skinName; 
		FileUtils::GetBaseFileName(*i, skinName); 
		skinNames.push_back( skinName );
	}

	//Prompt for controller skin choice
	Utils<ISnipRunParameterUtils> parameterUtils;
	int32 choice = parameterUtils->GetChoice(PMString("Controller Skin Options"), skinNames);
	if (parameterUtils->WasDialogCancelled()) {
		return kFailure;
	}
	SNIPLOG("Chosen controller skin: %s", skinNames.at(choice).GetPlatformString().c_str());
	

	//Set controller skin
	InterfacePtr<ICommand> setMediaAttrCmd( CmdUtils::CreateCommand( kSetMediaAttrCmdBoss ) ); 
    InterfacePtr<ISetMediaAttrCmdData> setMediaAttrCmdData ( setMediaAttrCmd, UseDefaultIID() );
    setMediaAttrCmd->SetItemList( replaceList ); 
    setMediaAttrCmdData->SetAttribute( IMediaAttributes::enControllerSkinName, skinNames.at(choice)); 
    result =  CmdUtils::ProcessCommand( setMediaAttrCmd );
	if( result != kSuccess )
		return result;

	return kSuccess;
}


ErrorCode SnpAddMediaFile::CreateDocument(UIDRef & documentUIDRef, const PMReal width, const PMReal height, const uint32 numPages, const uint32 pagesPerSpread )
{
	InterfacePtr<ICommand> newDocCmd(Utils<IDocumentCommands>()->CreateNewCommand(kSuppressUI));
	if (newDocCmd == nil) 
		return kFailure;
		
	// Set the command's parameterized data.
	InterfacePtr<INewDocCmdData> newDocCmdData(newDocCmd, UseDefaultIID());
	if (newDocCmdData == nil) 
		return kFailure;

	newDocCmdData->SetCreateBasicDocument(kFalse); // Override the following defaults.
	PMPageSize pageSize( width, height);
	newDocCmdData->SetNewDocumentPageSize(pageSize);
	newDocCmdData->SetWideOrientation(kFalse);
	
	// Size margin proportional to document width and height.
	PMReal horMargin = width / 20;
	PMReal verMargin = height / 20;
	newDocCmdData->SetMargins(horMargin, verMargin, horMargin, verMargin);
	newDocCmdData->SetNumPages(numPages);
	newDocCmdData->SetPagesPerSpread(pagesPerSpread);
	newDocCmdData->SetIntent(kWebIntent);

	// Create the new document.
	if (CmdUtils::ProcessCommand(newDocCmd) != kSuccess) {
		ASSERT_FAIL("IDocumentCommands::CreateNewCommand failed");
		return kFailure;
	}

	// Pass the UIDRef of the new document back to the caller.
	const UIDList& newDocCmdUIDList = newDocCmd->GetItemListReference();
	documentUIDRef = newDocCmdUIDList.GetRef(0);
	if (documentUIDRef == UIDRef::gNull) 
	{
		ASSERT_FAIL("newDocCmd returned invalid document UIDRef!");
		return kFailure;
	}

	return kSuccess;
}

ErrorCode SnpAddMediaFile::ChooseFileToOpen(IDFile& chosenFile)
{
	PMString title = "Choose Media Files";
	title.SetTranslatable(kFalse);

	// Set up the file chooser to show files of the requested kind.
	SDKFileOpenChooser fileChooser;
	fileChooser.AddAllFiles();		
	fileChooser.SetTitle(title);
	fileChooser.ShowDialog();
	if (!fileChooser.IsChosen()) 
		return kCancel;

	// Return the chosen file to the caller.
	chosenFile = fileChooser.GetIDFile();

	return kSuccess;
}



// --------------------------------- SnippetRunner framework hook ---------------------------------------------------

/** Makes the snippet SnpExportDynamicDocument available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerAddMediaFile : public SnpRunnable
{
	public:
		/** This constructor describes your snippet to the framework.
		 */
		_SnpRunnerAddMediaFile();

		/** Destructor.
		 */
		virtual			~_SnpRunnerAddMediaFile();

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

/* Describe your snippet to the framework here.
*/
_SnpRunnerAddMediaFile::_SnpRunnerAddMediaFile() : SnpRunnable("AddMediaFile")
{
	this->SetDescription("Add Media Files");
	this->SetPreconditions("none");
	this->SetCategories("sdk_snippet");
}

/* Destructor.
*/
_SnpRunnerAddMediaFile::~_SnpRunnerAddMediaFile()
{
}

/* Check if your snippet's preconditions are met here.
*/
bool16	_SnpRunnerAddMediaFile::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {
		// TODO: query runnableContext for the selection target 
		// e.g. ILayoutTarget or ITextTarget. Or call
		// runnableContext to get the IActiveContext.
		// See ISnpRunnableContext for documentation.
		result = kTrue;
	} while(false);
	return result;
}

/* Set up and call your snippet here.
*/
ErrorCode _SnpRunnerAddMediaFile::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		// TODO:
		// Use runnableContext to discover the selection target or IActiveContext if you need a context.

		// Use IParameterUtils to prompt for parameters to set up your call(if any).
		// Utils<ISnipRunParameterUtils> parameterUtils;

		// Perform your operation.
		SnpAddMediaFile instance;
		status = instance.AddMediaFile(runnableContext);
		
	} while(false);
	return (status);
}

/*	Declare an instance to register the snippet hook with the framework.
*/
static _SnpRunnerAddMediaFile instance_SnpRunnerAddMediaFile;
DEFINE_SNIPPET(_SnpRunnerAddMediaFile) 	

// End, SnpExportDynamicDocument.cpp

