//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpCreateAnimatedMultiStateObject.cpp $
//  
//  Owner: Adobe Developer Technologies
//  
//  $Author: vans $
//  
//  $DateTime: 2020/11/06 05:06:09 $
//  
//  $Revision: #1 $
//  
//  $Change: 1088554 $
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
#include "ICreateFormFieldCmdData.h"
#include "IDocument.h"
#include "IDynamicDocumentsExportCommandData.h"
#include "IDataBase.h"
#include "IGraphicFrameData.h"
#include "IHierarchy.h"
#include "IPageList.h"
#include "ISpreadList.h"
#include "ISwatchList.h"
#include "ISWFExportPreferences.h"
#include "IXFLExportPreferences.h"
#include "IXFLExportCommandData.h" 
#include "IUIDData.h"
#include "IWorkspace.h"
#include "IAppearanceItemFacade.h"
#include "ILayerUtils.h"
#include "IControlView.h"
#include "IMultiStateObjectBehaviorData.h"
#include "IMotionPresetMgr.h"
#include "IMotionPresetUtils.h"
#include "IAnimationFacade.h"
#include "IAnimationData.h"
#include "IAnimationAttributeData.h"
#include "IDynamicEventTimingFacade.h"
#include "IDynamicEventTimingMgr.h"
#include "ILayoutControlData.h"
#include "IAnimationUtils.h"


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
class SnpCreateAnimatedMultiStateObject
{
	public:
		/** Builds a Multi-State object on a new document and adds buttons to transition between states.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode CreateAnimatedMultiStateObject(ISnpRunnableContext* runnableContext);

	private:

		ErrorCode ExportSWF(const UIDRef & documentUIDRef, IDFile& swfFileName);
		ErrorCode ExportXFL(const UIDRef & documentUIDRef, IDFile& xflFileName);
		ErrorCode ChooseSaveLocation(IDFile& xflFileName, int32 choice);
		ErrorCode CreateMSO(const UIDRef & documentUIDRef, UIDRef &msoRef);
		ErrorCode AddAnimationToState(const UIDRef & pageItemRef, const UIDRef &msoRef);
		ErrorCode ModifyAnimationTriggers(const UIDRef & msoRef);
		ErrorCode CreateButtons(const UIDRef & documentUIDRef, const UIDRef &msoRef);
		ErrorCode CreateTextFrame(const UIDRef & spreadLayerRef,
									const WideString & text, 
									const PMRect & bounds,
									UIDList & splineItemUIDs,
									UIDList & mcfUIDs
								);
		ErrorCode ConvertTextFramesToButtons( UIDList & splineItemUIDs, const UIDRef &msoRef);
		ErrorCode AddButtonAction(ClassID createCmdBoss, const UIDRef & item, const UIDRef &msoRef);

		SDKLayoutHelper fLayoutHelper;
		SnpTextModelHelper	fTextCmdHelper;
		IBehaviorData* QuerySelectedBehaviorData(int32 actionType) const; 
};

/*
*/
ErrorCode SnpCreateAnimatedMultiStateObject::CreateTextFrame(const UIDRef & spreadLayerRef,
													const WideString & text, 
													const PMRect & bounds,
													UIDList & splineItemUIDs,
													UIDList & mcfUIDs
													)
{
	

	UIDRef pageItemUIDRef = fLayoutHelper.CreateTextFrame(spreadLayerRef, bounds, 1, kFalse);
	if( pageItemUIDRef == kInvalidUIDRef )
		return kFailure;
	splineItemUIDs.Append(pageItemUIDRef.GetUID());

	// Add  text to the frame
	InterfacePtr<IGraphicFrameData> graphicFrameData(pageItemUIDRef, UseDefaultIID());
	if(graphicFrameData == nil )
		return kFailure;

	InterfacePtr<IMultiColumnTextFrame> mcTextFrame(graphicFrameData->QueryMCTextFrame());
	mcfUIDs.Append(::GetUID(mcTextFrame));
	InterfacePtr<ITextModel> textModel(mcTextFrame->QueryTextModel());

	boost::shared_ptr<WideString> string(new WideString(text));
	return fTextCmdHelper.InsertText(textModel, 0, string );
}



ErrorCode SnpCreateAnimatedMultiStateObject::AddButtonAction(ClassID behaviorCmdBoss, const UIDRef & item, const UIDRef &msoRef)
{
	InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kPipelineSequenceCmdBoss));
	InterfacePtr<ICmdCollection> cmdCollection(cmd, UseDefaultIID());
	cmd->SetName("$$$/Command/New State Behavior");
	{ 
		// This block is here because ownership of the command is transferred to the cmdCollection
		ICommand * behaviorCmd = CmdUtils::CreateCommand(behaviorCmdBoss);
		behaviorCmd->SetItemList(item);
		cmdCollection->Append(behaviorCmd);

		//Associate the MSO with the button action.
		InterfacePtr<IMultiStateObjectBehaviorData> behaviorEditCmdData(behaviorCmd, UseDefaultIID());
		behaviorEditCmdData->SetTarget(msoRef.GetUID());
			
		// ---- Create and initialize the adopt behavior command.			
		ICommand* adoptCmd = CmdUtils::CreateCommand(kAdoptBehaviorCmdBoss);
		InterfacePtr<IBehaviorEventData> cmdEventData(adoptCmd, UseDefaultIID());
		cmdEventData->SetEvent(kMouseUpEvt);  
			
		InterfacePtr<IUIDData> cmdUIDData(adoptCmd, UseDefaultIID());
		cmdUIDData->Set(item);

		cmdCollection->Append(adoptCmd);
	}
	return CmdUtils::ProcessCommand(cmd);
}


/*
*/
ErrorCode SnpCreateAnimatedMultiStateObject::ConvertTextFramesToButtons( UIDList & splineItemUIDs, const UIDRef &msoRef)
{
	UIDList buttonUIDs(splineItemUIDs.GetDataBase());
	Utils<Facade::IAppearanceItemFacade> iFacade;
	ErrorCode result = iFacade->CreateAppearanceItem(splineItemUIDs, kPushButtonItemBoss, &buttonUIDs);	
	if( result != kSuccess )
		return result;

	ASSERT(buttonUIDs.Length() == 2); // We've added two buttons so this must be two
	if( buttonUIDs.Length() == 2 )
	{
		result = AddButtonAction(kCreateSwitchToPrevMSOStateBehaviorCmdBoss, buttonUIDs.GetRef(0), msoRef);
		if( result != kSuccess )
			return result;

		return AddButtonAction(kCreateSwitchToNextMSOStateBehaviorCmdBoss, buttonUIDs.GetRef(1), msoRef);
	}

	return kFailure;
}

/*
*/
ErrorCode SnpCreateAnimatedMultiStateObject::CreateButtons(const UIDRef & documentUIDRef, const UIDRef &msoRef)
{
	ErrorCode result = kSuccess;
	IDataBase * db = documentUIDRef.GetDataBase();

	InterfacePtr<ISpreadList> spreadList(documentUIDRef, UseDefaultIID());
	if( spreadList == nil)
		return kFailure;

	InterfacePtr<IHierarchy> spreadUIDRef(db, spreadList->GetNthSpreadUID(0), UseDefaultIID());
	UIDRef spreadLayerRef(db, spreadUIDRef->GetChildUID(2)); // Skip the two pages layer
	
	// UIDs for the new text frames spline and MCF will be saved in these UIDLists.
	UIDList splineItemUIDs(db), mcfUIDs(db);
	
	// Create a text frame at the lower left corner of the spread.
	WideString previousButtonText("<-Previous State");
	PMPoint previousButtonStartPoint(-95,70);	// Upper Left in Page Coords
	PMPoint previousButtonEndPoint(80, 20);		// Size of rectangle
	previousButtonEndPoint += previousButtonStartPoint;
	PMRect previousButtonBounds(previousButtonStartPoint, previousButtonEndPoint);

	result = CreateTextFrame(spreadLayerRef,  previousButtonText,  previousButtonBounds, splineItemUIDs, mcfUIDs); 
	if( result != kSuccess )
		return result;

	// Create a text frame at the lower right corner of the sprad.
	WideString nextButtonText("Next State->");
	PMPoint nextButtonStartPoint(30,70);	// Upper Left in Page Coords
	PMPoint nextButtonEndPoint(70, 20);		// Size of rectangle
	nextButtonEndPoint += nextButtonStartPoint;
	PMRect nextButtonBounds(nextButtonStartPoint, nextButtonEndPoint);

	result = CreateTextFrame(spreadLayerRef, nextButtonText, nextButtonBounds, splineItemUIDs, mcfUIDs);
	if( result != kSuccess )
		return result;

	//Convert To Buttons
	result = ConvertTextFramesToButtons( splineItemUIDs, msoRef );
	if( result != kSuccess )
		return result;

	return kSuccess;
}

/*
*/
ErrorCode SnpCreateAnimatedMultiStateObject::CreateMSO(const UIDRef & documentUIDRef, UIDRef & msoRef)
{
	ErrorCode result = kFailure;

	InterfacePtr<ISpreadList> spreadList(documentUIDRef, UseDefaultIID());
	if( spreadList == nil)
		return kFailure;

	InterfacePtr<IDocument> document(documentUIDRef, UseDefaultIID());
	if( document == nil)
		return kFailure;

	InterfacePtr<ISwatchList> swatchList(document->GetDocWorkSpace(), IID_ISWATCHLIST);
	if( swatchList == nil)
		return kFailure;

	//Get the number of visible swatches
	int visibleSwatches = swatchList->GetNumVisibleSwatches();

	//Create the UIDList containing the states
	IDataBase * db = documentUIDRef.GetDataBase();
	UIDList stateList(db);

	//Get the UIDRefs 
	InterfacePtr<IHierarchy> spreadUIDRef(db, spreadList->GetNthSpreadUID(0), UseDefaultIID());
	UIDRef spreadLayerRef(db, spreadUIDRef->GetChildUID(2)); // Skip the two pages layer

	//Create the bounds for the states of the MSO
	PMPoint startPoint(-60, -60);	// Upper Left in Page Coords
	PMPoint endPoint(120, 120);		// Size of rectangle
	endPoint += startPoint;
	PMRect bounds(startPoint, endPoint);
	
	//For each swatch create a state and add it to the state list.
	for (int swatch = 4; swatch < visibleSwatches; swatch++)
	{
		UIDRef pageItemUIDRef = fLayoutHelper.CreateRectangleFrame(spreadLayerRef, bounds);
		if( pageItemUIDRef == kInvalidUIDRef )
			return kFailure;				

		SnpGraphicHelper graphicHelper(pageItemUIDRef);
		graphicHelper.AddFillRendering(swatchList->GetNthVisibleSwatch(swatch).GetUID());
		graphicHelper.ApplyAttributes();

		stateList.Append(pageItemUIDRef);
	}

	//Creates a new Multi-State object and add the states to it.	
	UIDList outItems(msoRef);
	Utils<Facade::IAppearanceItemFacade> iFacade;
	result = iFacade->CreateAppearanceItem(stateList, kMultiStateObjectItemBoss, &outItems);	
	msoRef = outItems.GetRef(0); 

	//Add animations to each of the states.
	for( int32 i = 0; i < stateList.Length(); i++)
	{
		UIDRef pageItemUIDRef = stateList.GetRef(i);
		result = AddAnimationToState(pageItemUIDRef, msoRef);
		if( result != kSuccess )
			return result;
	}
	return result;
}


/*
*/
ErrorCode SnpCreateAnimatedMultiStateObject::AddAnimationToState(const UIDRef & pageItemRef, const UIDRef & msoRef)
{	
	ErrorCode result = kFailure;
	//TODO: Add the source of the preset names
	PMString presetName = "twirl";

	//Get the animation preset index
	InterfacePtr<IMotionPresetMgr> iPresetMgr (Utils<IMotionPresetUtils>()->QueryMotionPresetManager (nil)); 
	int32 presetIndex = iPresetMgr->FindPreset (presetName, false /*case sensitive*/); 

    if (presetIndex >= 0) 
    {      
		//Get a UIDRef for the Preset
        UID presetUID = iPresetMgr->GetNthPresetUID (presetIndex); 
        UIDRef presetRef = UIDRef (::GetDataBase (iPresetMgr), presetUID); 

		//Set the pageitem animation preset
		Utils<Facade::IAnimationFacade > iAnimationFacade;
		result = iAnimationFacade->SetPageItemMotionPreset(pageItemRef, presetRef);

		//Set Animation Attribute to a non-default value.
		InterfacePtr<IAnimationAttributeData> iAnimationAttrData (pageItemRef, UseDefaultIID ()); 	
		iAnimationAttrData->SetDuration(1.5);
    } 
	return result;
}


ErrorCode SnpCreateAnimatedMultiStateObject::ModifyAnimationTriggers(const UIDRef & msoRef)
{	
	UIDRef spreadRef;
	
	//Get SpreadRef
	IControlView* view = GetExecutionContextSession()->GetActiveContext()->GetContextView(); 
    if (view) 
    { 
		//IID_ILAYOUTCONTROLDATA
        InterfacePtr<ILayoutControlData> viewSpreadMgr(view, UseDefaultIID()); 
        spreadRef = viewSpreadMgr->GetSpreadRef();
	}
	else
	{
		return kFailure;
	}
	 

	//Remove default page load events from the spread
	Utils<Facade::IDynamicEventTimingFacade > iDynEvtTimingFacade;
	InterfacePtr<IDynamicEventTimingMgr> iDynEvtTimingMgr (spreadRef, UseDefaultIID ());
	uint32 numTriggers = iDynEvtTimingMgr->GetNumDynamicEvents ();
	for( int32 i = 0; i < numTriggers; i++)
	{
		EventTriggerType trigger = iDynEvtTimingFacade->GetNthDynamicEvent (spreadRef, i); 
		bool successful = iDynEvtTimingFacade->RemoveDynamicEvent(spreadRef, trigger);	
		if (!successful)
			return  kFailure;
	}
		
	//Add the Page_Load Event for each state.
	IAnimationUtils* animationUtils = Utils<IAnimationUtils>();		
	UID parentTimingUID = animationUtils->GetTimingParentUID(msoRef);
	InterfacePtr<IDynamicEventTimingMgr> iMsoTimingMgr (msoRef.GetDataBase (), parentTimingUID, UseDefaultIID ()); 
	IDynamicEventTimingMgr::DynamicTargetPtr dynamicTarget =  iDynEvtTimingFacade->CreateDynamicTarget (msoRef, kOnPageLoad, kTimingTargetVerbPlay);
	bool successful = iMsoTimingMgr->AddTargetInNthGroup (kOnPageLoad, dynamicTarget, -1);
	if (!successful)
		return kFailure;

	return kSuccess;
}


/*
*/
ErrorCode SnpCreateAnimatedMultiStateObject::ExportSWF(const UIDRef & documentUIDRef,
											  IDFile& swfFileName)
{
	ErrorCode status = kFailure;
	InterfacePtr<IPMStream> outStream(StreamUtil::CreateFileStreamWriteLazy(swfFileName, kOpenOut | kOpenTrunc));

	SDKFileHelper fileHelper(swfFileName);
	if (fileHelper.GetPath().empty()) 
	{ 
		ASSERT_FAIL("Invalid or missing filename.");
		return kFailure; 
	} 

	// create the SWF export action command
	InterfacePtr<ICommand> swfExportCmd(CmdUtils::CreateCommand(kSWFExportCommandBoss));
	if (swfExportCmd == nil) 
	{ 
		ASSERT(swfExportCmd);
		return kFailure;; 
	}
	
	// Set Target
	UIDList items(documentUIDRef.GetDataBase());
	InterfacePtr<IPageList const> pageList(documentUIDRef, UseDefaultIID());
	for (int32 pageIndex = 0, pageCount = pageList->GetPageCount(); pageIndex < pageCount; ++pageIndex)
		items.Append(pageList->GetNthPageUID(pageIndex));
	swfExportCmd->SetItemList(items);

	// Set cmd data 
	// IID_IDYNDOCSEXPORTCOMMANDDATA
	InterfacePtr<IDynamicDocumentsExportCommandData> dynamicDocsCmdData(swfExportCmd, UseDefaultIID());
	dynamicDocsCmdData->SetStream(outStream);
	dynamicDocsCmdData->SetUIFlags(kSuppressUI);

	// IID_ISWFEXPORTPREFERENCES
	InterfacePtr<ISWFExportPreferences> swfCmdData(swfExportCmd, UseDefaultIID());
	InterfacePtr<IWorkspace> iAppWS(GetExecutionContextSession()->QueryWorkspace());
	InterfacePtr<ISWFExportPreferences> iSWFExportPrefs(iAppWS, UseDefaultIID());
	swfCmdData->Copy(iSWFExportPrefs);

	// process the command
	return CmdUtils::ProcessCommand(swfExportCmd);
}


ErrorCode SnpCreateAnimatedMultiStateObject::ExportXFL(const UIDRef & documentUIDRef,
											  IDFile& xflFileName)
{
	ErrorCode status = kFailure;
	InterfacePtr<IPMStream> outStream(StreamUtil::CreateFileStreamWriteLazy(xflFileName, kOpenOut | kOpenTrunc));

	SDKFileHelper fileHelper(xflFileName);
	if (fileHelper.GetPath().empty()) 
	{ 
		ASSERT_FAIL("Invalid or missing filename.");
		return kFailure; 
	} 

	InterfacePtr<ICommand> xflExportCmd(CmdUtils::CreateCommand(kXFLExportCommandBoss));
	if (xflExportCmd == nil) 
	{ 
		ASSERT(xflExportCmd);
		return kFailure;; 
	}
	
	// Set Target
	UIDList items(documentUIDRef.GetDataBase());
	InterfacePtr<IPageList const> pageList(documentUIDRef, UseDefaultIID());
	for (int32 pageIndex = 0, pageCount = pageList->GetPageCount(); pageIndex < pageCount; ++pageIndex)
	{
		items.Append(pageList->GetNthPageUID(pageIndex));
	}
	xflExportCmd->SetItemList(items);	

	// Set Dynamic Docs Command Data
	InterfacePtr<IDynamicDocumentsExportCommandData> dynamicDocsCmdData(xflExportCmd, UseDefaultIID());
	dynamicDocsCmdData->SetStream(outStream);

	//Suppress the "Export Adobe Flash CS4 Professional (XFL)" dialogue box
	//that a user sees when exporting to XFL in the File -> Export menu.
	dynamicDocsCmdData->SetUIFlags(kSuppressUI);


	//Set XFL Command Data
	InterfacePtr<IXFLExportCommandData> xflCmdData(xflExportCmd, UseDefaultIID());
	if (xflCmdData) 
	{
		//XFL Files are packages.  This ensures a package is created.
		xflCmdData->SetExportAsPackage(true);
	}

	// Set export preferences
	InterfacePtr<IWorkspace> iAppWS(GetExecutionContextSession()->QueryWorkspace());
	InterfacePtr<IXFLExportPreferences> xflPrefs_WS(iAppWS, UseDefaultIID());
	InterfacePtr<IXFLExportPreferences> xflPrefs_Cmd(xflExportCmd, UseDefaultIID());	
	xflPrefs_Cmd->Copy(xflPrefs_WS);	

	// process the command
	return CmdUtils::ProcessCommand(xflExportCmd);
}


ErrorCode SnpCreateAnimatedMultiStateObject::ChooseSaveLocation(IDFile& chosenFile, int32 choice)
{
	ErrorCode result = kCancel;	

	SDKFileSaveChooser fileChooser;
	SysOSType macFileCreator = FileTypeRegistry::GetCurrentFileCreator(kPublicationFileTypeInfoID);	
	
	enum {kSWF, kXFL};
	switch (choice) 
	{
		default:
		case kSWF:
			{
				fileChooser.AddFilter(macFileCreator, 'SWF ', "swf", "SWF file(swf)");	
				break;
			}
		case kXFL:
			{
				fileChooser.AddFilter(macFileCreator, 'XFL ', "xfl", "XFL file(xfl)");	
				break;
			}
	}
	
	fileChooser.ShowDialog();
	if (!fileChooser.IsChosen()) 
	{
		return result;
	}

	// Return the chosen file to the caller.
	chosenFile = fileChooser.GetIDFile();
	result = kSuccess;

	return result;
}

/*
*/
ErrorCode SnpCreateAnimatedMultiStateObject::CreateAnimatedMultiStateObject(ISnpRunnableContext* runnableContext)
{
	ErrorCode result;

	// Create a Document
	UIDRef documentUIDRef = fLayoutHelper.CreateDocument(kSuppressUI,
				200, // Width
				200, // Height
				1,   // Number of Pages
				1);  // Number of Pages Per Spread

	if (documentUIDRef == UIDRef::gNull)
		return kFailure;

	// Open a view onto the document.
	result = fLayoutHelper.OpenLayoutWindow(documentUIDRef);
	if( result != kSuccess )
		return result;

	UIDRef msoRef;

	// Create rectangle frame on each page, and fill each page with a unique swatch.	
	result = CreateMSO(documentUIDRef, msoRef);
	if( result != kSuccess )
		return result;
	
	result = ModifyAnimationTriggers(msoRef);
	if( result != kSuccess )
		return result;
	
	result = CreateButtons(documentUIDRef, msoRef);
	if( result != kSuccess )
		return result;

	//Choose which file type to export
	Utils<ISnipRunParameterUtils> parameterUtils;
	K2Vector<PMString> choices;
	choices.push_back(PMString("Export to .swf"));
	choices.push_back(PMString("Export to .xfl"));
	enum {kSWF, kXFL};
	int32 choice = parameterUtils->GetChoice(PMString("Export Options"), choices);
	if (parameterUtils->WasDialogCancelled()) {
		return result;
	}

	//Choose where to save the file
	IDFile exportFile;
	result = ChooseSaveLocation(exportFile, choice);

	//Log results
	SDKFileHelper fileHelper(exportFile);
	if( result == kSuccess )
	{
		SNIPLOG("\nExporting to (%s)", fileHelper.GetPath().GetPlatformString().c_str());
	}
	else if( result == kCancel)
	{
		SNIPLOG("\nCancelled Exporting to (%s)", fileHelper.GetPath().GetPlatformString().c_str());
		return result;
	}
	else
	{
		SNIPLOG("\nFailed Exporting to (%s)", fileHelper.GetPath().GetPlatformString().c_str());
		return result;
	}

	//Export Dynamic Document.
	switch (choice) 
	{
	default:
	case kSWF:
		{
			return ExportSWF(documentUIDRef, exportFile);
			break;
		}
	case kXFL:
		{
			return ExportXFL(documentUIDRef, exportFile);
			break;
		}
	}
	return kFailure;
}

// --------------------------------- SnippetRunner framework hook ---------------------------------------------------

/** Makes the snippet SnpExportDynamicDocument available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerCreateAnimatedMultiStateObject : public SnpRunnable
{
	public:
		/** This constructor describes your snippet to the framework.
		 */
		_SnpRunnerCreateAnimatedMultiStateObject();

		/** Destructor.
		 */
		virtual			~_SnpRunnerCreateAnimatedMultiStateObject();

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
_SnpRunnerCreateAnimatedMultiStateObject::_SnpRunnerCreateAnimatedMultiStateObject() : SnpRunnable("CreateAnimatedMultiStateObject")
{
	this->SetDescription("Creates an Animated MultiStateObject");
	this->SetPreconditions("none");
	this->SetCategories("sdk_snippet");
}

/* Destructor.
*/
_SnpRunnerCreateAnimatedMultiStateObject::~_SnpRunnerCreateAnimatedMultiStateObject()
{
}

/* Check if your snippet's preconditions are met here.
*/
bool16	_SnpRunnerCreateAnimatedMultiStateObject::CanRun(ISnpRunnableContext* runnableContext)
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
ErrorCode _SnpRunnerCreateAnimatedMultiStateObject::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		// TODO:
		// Use runnableContext to discover the selection target or IActiveContext if you need a context.

		// Use IParameterUtils to prompt for parameters to set up your call(if any).
		// Utils<ISnipRunParameterUtils> parameterUtils;

		// Perform your operation.
		SnpCreateAnimatedMultiStateObject instance;
		status = instance.CreateAnimatedMultiStateObject(runnableContext);
		
	} while(false);
	return (status);
}

/*	Declare an instance to register the snippet hook with the framework.
*/
static _SnpRunnerCreateAnimatedMultiStateObject instance_SnpRunnerCreateAnimatedMultiStateObject;
DEFINE_SNIPPET(_SnpRunnerCreateAnimatedMultiStateObject) 	

// End, SnpExportDynamicDocument.cpp