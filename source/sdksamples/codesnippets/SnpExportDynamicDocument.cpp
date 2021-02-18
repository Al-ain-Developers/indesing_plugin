//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpExportDynamicDocument.cpp $
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
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IAttrReport.h"
#include "IBehaviorEventData.h"
#include "ICmdCollection.h"
#include "IComposeScanner.h"
#include "ICompositionStyle.h"
#include "ICreateFormFieldCmdData.h"
#include "IDocument.h"
#include "IDynamicDocumentsExportCommandData.h"
#include "IDataBase.h"
#include "IGeometry.h"
#include "IGraphicFrameData.h"
#include "IHierarchy.h"
#include "IIntData.h"
#include "IMasterSpreadList.h"
#include "IMultiColumnTextFrame.h"
#include "IPageList.h"
#include "ISpreadList.h"
#include "ISwatchList.h"
#include "ISWFExportPreferences.h"
#include "IXFLExportPreferences.h"
#include "IXFLExportCommandData.h" 
#include "ITextAttrAlign.h"
#include "ITextModel.h"
#include "IUIDData.h"
#include "IWorkspace.h"
#include "IAppearanceItemFacade.h"
#include "IDocumentCommands.h"
#include "INewDocCmdData.h"

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
#include "TransformUtils.h"
#include "UIDList.h"
#include "Utils.h"

// Framework includes:
#include "SnpRunnable.h"
#include "SnpGraphicHelper.h"
#include "SnpTextAttrHelper.h"
#include "SnpTextModelHelper.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/** 
	\li	Shows how to build and export a dynamic document.

  	@ingroup sdk_snippet

 */
class SnpExportDynamicDocument
{
	public:
		/** Builds dynamic document.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode BuildDynamicDocument(ISnpRunnableContext* runnableContext);

	private:

		ErrorCode ExportSWF(const UIDRef & documentUIDRef, IDFile& swfFileName);
		ErrorCode ExportXFL(const UIDRef & documentUIDRef, IDFile& xflFileName);
		ErrorCode CreateDocument(UIDRef & documentUIDRef, const PMReal width, const PMReal height, const uint32 numPages, const uint32 pagesPerSpread );
		ErrorCode ChooseSaveLocation(IDFile& xflFileName, int32 choice);
		ErrorCode ColorSpreads(const UIDRef & documentUIDRef);
		ErrorCode CreateButtonsOnMaster(const UIDRef & documentUIDRef);
		ErrorCode CreateTextFrame(const UIDRef & spreadLayerRef,
									const WideString & text, 
									const PMRect & bounds,
									UIDList & splineItemUIDs,
									UIDList & mcfUIDs
								);
		ErrorCode SetTextAlignment( const UIDRef & mcfUIDRef, ICompositionStyle::TextAlignment alignment );
		ErrorCode SetVerticalJustification( UIDList & mcfUIDs );
		ErrorCode ConvertTextFramesToButtons( UIDList & splineItemUIDs );
		ErrorCode AddButtonAction(ClassID createCmdBoss, const UIDRef & item);

		SDKLayoutHelper fLayoutHelper;
		SnpTextModelHelper	fTextCmdHelper;
};

/*
*/
ErrorCode SnpExportDynamicDocument::CreateTextFrame(const UIDRef & spreadLayerRef,
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


/*
*/
ErrorCode SnpExportDynamicDocument::SetTextAlignment( const UIDRef & mcfUIDRef, ICompositionStyle::TextAlignment alignment )
{
	InterfacePtr<IMultiColumnTextFrame> mcTextFrame(mcfUIDRef, UseDefaultIID());
	InterfacePtr<ITextModel> textModel(mcTextFrame->QueryTextModel());

	InterfacePtr<IAttrReport> textAttrAlign(SnpTextAttrHelper::CreateTextAttribute<ITextAttrAlign, ITextAttrAlign::ValueType>(kTextAttrAlignmentBoss, alignment));
	ASSERT(textAttrAlign != nil);
	if(textAttrAlign==nil) {
		return kFailure;
	}

	boost::shared_ptr<AttributeBossList> paraAttributeBossList (new AttributeBossList());
	ASSERT(paraAttributeBossList);
	if (!paraAttributeBossList) {
		return kFailure;
	}
	paraAttributeBossList->ApplyAttribute(textAttrAlign);

	// Use SnpTextModelHelper::ApplyOverrides to apply the attribute. We are applying a paragraph 
	// attribute, so we indicate kParaAttributeStrand.
	return fTextCmdHelper.ApplyOverrides(textModel, 0, 1, paraAttributeBossList, kParaAttrStrandBoss);
}

/*
*/
ErrorCode SnpExportDynamicDocument::SetVerticalJustification( UIDList & mcfUIDs )
{
	// Apply vertical justification (Center)
	InterfacePtr<ICommand> vjCmd(CmdUtils::CreateCommand(kSetFrameVertJustifyCmdBoss));
	InterfacePtr<IIntData> vjCmdData(vjCmd, UseDefaultIID());
	vjCmd->SetItemList(mcfUIDs);
	vjCmdData->Set((int32) Text::kVJCenter);
	return CmdUtils::ProcessCommand(vjCmd);
}


ErrorCode SnpExportDynamicDocument::AddButtonAction(ClassID createCmdBoss, const UIDRef & item)
{
	InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kPipelineSequenceCmdBoss));
	cmd->SetCreatorID(ICommand::kUniqueCreatorID);
	InterfacePtr<ICmdCollection> cmdCollection(cmd, UseDefaultIID());
	cmd->SetName("$$$/Command/New Behavior");
	{ 
		// This block is here because ownership of the command sis transferred to the cmdCollection
		ICommand * createCmd = CmdUtils::CreateCommand(createCmdBoss);
		createCmd->SetCreatorID(ICommand::kUniqueCreatorID);
		createCmd->SetItemList(item);
		cmdCollection->Append(createCmd);
			
		// ---- Create and initialize the adopt behavior command.
			
		ICommand* adoptCmd = CmdUtils::CreateCommand(kAdoptBehaviorCmdBoss);
		adoptCmd->SetCreatorID(ICommand::kUniqueCreatorID);
		InterfacePtr<IBehaviorEventData> cmdEventData(adoptCmd, UseDefaultIID());
		cmdEventData->SetEvent(kMouseUpEvt);  // HLTODO note... This is even hard coded in the script provider
			
		InterfacePtr<IUIDData> cmdUIDData(adoptCmd, UseDefaultIID());
		cmdUIDData->Set(item);

		cmdCollection->Append(adoptCmd);
	}
	return CmdUtils::ProcessCommand(cmd);
}

/*
*/
ErrorCode SnpExportDynamicDocument::ConvertTextFramesToButtons( UIDList & splineItemUIDs )
{
	UIDList buttonUIDs(splineItemUIDs.GetDataBase());
	Utils<Facade::IAppearanceItemFacade> iFacade;
	ErrorCode result = iFacade->CreateAppearanceItem(splineItemUIDs, kPushButtonItemBoss, &buttonUIDs);	
	if( result != kSuccess )
		return result;

	ASSERT(buttonUIDs.Length() == 2); // We've added two buttons so this must be two
	if( buttonUIDs.Length() == 2 )
	{
		result = AddButtonAction(kCreateGoToPreviousPageBehaviorCmdBoss, buttonUIDs.GetRef(0));
		if( result != kSuccess )
			return result;

		return AddButtonAction(kCreateGoToNextPageBehaviorCmdBoss, buttonUIDs.GetRef(1));
	}

	return kFailure;
}

/*
*/
ErrorCode SnpExportDynamicDocument::CreateButtonsOnMaster(const UIDRef & documentUIDRef)
{
	ErrorCode result = kSuccess;
	IDataBase * db = documentUIDRef.GetDataBase();


	// Create buttons on the master pages.
	// Begin by creating two text frames, one at the lower left and another at the lower right of the two pages.
	InterfacePtr<IMasterSpreadList> masterSpreadList(documentUIDRef, UseDefaultIID());
	if( masterSpreadList == nil)
		return kFailure;

	InterfacePtr<IHierarchy> masterSpreadHier(db, masterSpreadList->GetNthMasterSpreadUID(0), UseDefaultIID());
	UIDRef masterSpreadLayerRef(db, masterSpreadHier->GetChildUID(2)); // Skip the two pages layer
	
	// UIDs for the new text frames spline and MCF will be saved in these UIDLists.
	UIDList splineItemUIDs(db), mcfUIDs(db);
	
	// Create a text frame at the lower left corner of the spread, with Left alignment.
	WideString previousButtonText("<-Previous");
	PMRect  previousButtonBounds(-144, 9, -72, 27); 
	result = CreateTextFrame(masterSpreadLayerRef,  previousButtonText,  previousButtonBounds, splineItemUIDs, mcfUIDs); 
	if( result != kSuccess )
		return result;
	result = SetTextAlignment(mcfUIDs.GetRef(0), ICompositionStyle::kTextAlignLeft);
	if( result != kSuccess )
		return result;

	// Create a text frame at teh lower right corner of the sprad, with right alignment.
	WideString nextButtonText("Next->");
	PMRect  nextButtonBounds(72, 9, 144, 27); 
	result = CreateTextFrame(masterSpreadLayerRef,  nextButtonText,  nextButtonBounds, splineItemUIDs, mcfUIDs);
	if( result != kSuccess )
		return result;
	result = SetTextAlignment(mcfUIDs.GetRef(1), ICompositionStyle::kTextAlignRight);
	if( result != kSuccess )
		return result;

	// Set VJ for both text frames
	result = SetVerticalJustification( mcfUIDs );
	if( result != kSuccess )
		return result;

	//Convert To Buttons
	result = ConvertTextFramesToButtons( splineItemUIDs );
	if( result != kSuccess )
		return result;

	return kSuccess;
}

/*
*/
ErrorCode SnpExportDynamicDocument::ColorSpreads(const UIDRef & documentUIDRef)
{
	InterfacePtr<ISpreadList> spreadList(documentUIDRef, UseDefaultIID());
	if( spreadList == nil)
		return kFailure;

	InterfacePtr<IDocument> document(documentUIDRef, UseDefaultIID());
	if( document == nil)
		return kFailure;
	InterfacePtr<ISwatchList> swatchList(document->GetDocWorkSpace(), IID_ISWATCHLIST);
	if( swatchList == nil)
		return kFailure;

	int visibleSwatches = swatchList->GetNumVisibleSwatches();
	int swatchStart = 4;

	IDataBase * db = documentUIDRef.GetDataBase();

	for(int32 i=0, swatch = swatchStart; i< spreadList->GetSpreadCount() && swatch < visibleSwatches; i++, swatch++)
	{
		InterfacePtr<IColorData> colorData(swatchList->GetNthVisibleSwatch(i), UseDefaultIID());

		InterfacePtr<IHierarchy> spreadHier(db, spreadList->GetNthSpreadUID(i), UseDefaultIID());
		UIDRef spreadLayerRef(db, spreadHier->GetChildUID(2)); // Skip the two pages layer

		

		InterfacePtr<IHierarchy> pagesLayerHier(db, spreadHier->GetChildUID(0), UseDefaultIID());
		for( int32 j=0; j<pagesLayerHier->GetChildCount(); j++)
		{
			InterfacePtr<IGeometry> pageGeometry( db, pagesLayerHier->GetChildUID(j), UseDefaultIID() );
			PMRect bounds = pageGeometry->GetStrokeBoundingBox(::InnerToParentMatrix(pageGeometry));
			bounds.Bottom(0);
			
			UIDRef pageItemUIDRef = fLayoutHelper.CreateRectangleFrame(spreadLayerRef, bounds);
				if( pageItemUIDRef == kInvalidUIDRef )
					return kFailure;

			SnpGraphicHelper graphicHelper(pageItemUIDRef);
			graphicHelper.AddFillRendering(swatchList->GetNthVisibleSwatch(swatch).GetUID());
			graphicHelper.ApplyAttributes();
		}

		if (swatch == (visibleSwatches - 1))
			swatch = swatchStart;
	}
	
	return kSuccess;
}

/*
*/
ErrorCode SnpExportDynamicDocument::ExportSWF(const UIDRef & documentUIDRef,
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


ErrorCode SnpExportDynamicDocument::ExportXFL(const UIDRef & documentUIDRef,
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


ErrorCode SnpExportDynamicDocument::ChooseSaveLocation(IDFile& chosenFile, int32 choice)
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

ErrorCode SnpExportDynamicDocument::CreateDocument(UIDRef & documentUIDRef, const PMReal width, const PMReal height, const uint32 numPages, const uint32 pagesPerSpread )
{
	InterfacePtr<ICommand> newDocCmd(Utils<IDocumentCommands>()->CreateNewCommand(kSuppressUI));
	if (newDocCmd == nil) {
		return kFailure;
	}
		
	// Set the command's parameterised data.
	InterfacePtr<INewDocCmdData> newDocCmdData(newDocCmd, UseDefaultIID());
	if (newDocCmdData == nil) {
		return kFailure;
	}

	newDocCmdData->SetCreateBasicDocument(kFalse); // Override the following defaults.
	PMPageSize pageSize(width, height);
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


/*
*/
ErrorCode SnpExportDynamicDocument::BuildDynamicDocument(ISnpRunnableContext* runnableContext)
{
	ErrorCode result;

	//Create a new document with intent set for for web.
	UIDRef documentUIDRef;
	result = CreateDocument(documentUIDRef,
				144, // Width
				144, // Height
				10,   // Number of Pages
				2);  // Number of Pages Per Spread
	if( result != kSuccess )
		return result;

	// Open a view onto the document.
	result = fLayoutHelper.OpenLayoutWindow(documentUIDRef);
	if( result != kSuccess )
		return result;

	// Create rectangle frame on each page, and fill each page with a unique swatch.	
	result = ColorSpreads(documentUIDRef);
	if( result != kSuccess )
		return result;
	
	result = CreateButtonsOnMaster(documentUIDRef);
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
class _SnpRunnerExportDynamicDocument : public SnpRunnable
{
	public:
		/** This constructor describes your snippet to the framework.
		 */
		_SnpRunnerExportDynamicDocument();

		/** Destructor.
		 */
		virtual			~_SnpRunnerExportDynamicDocument();

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
_SnpRunnerExportDynamicDocument::_SnpRunnerExportDynamicDocument() : SnpRunnable("ExportDynamicDocument")
{
	this->SetDescription("Provides a ExportDynamicDocument");
	this->SetPreconditions("none");
	this->SetCategories("sdk_snippet");
}

/* Destructor.
*/
_SnpRunnerExportDynamicDocument::~_SnpRunnerExportDynamicDocument()
{
}

/* Check if your snippet's preconditions are met here.
*/
bool16	_SnpRunnerExportDynamicDocument::CanRun(ISnpRunnableContext* runnableContext)
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
ErrorCode _SnpRunnerExportDynamicDocument::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		// TODO:
		// Use runnableContext to discover the selection target or IActiveContext if you need a context.

		// Use IParameterUtils to prompt for parameters to set up your call(if any).
		// Utils<ISnipRunParameterUtils> parameterUtils;

		// Perform your operation.
		SnpExportDynamicDocument instance;
		status = instance.BuildDynamicDocument(runnableContext);
		
	} while(false);
	return (status);
}

/*	Declare an instance to register the snippet hook with the framework.
*/
static _SnpRunnerExportDynamicDocument instance_SnpRunnerExportDynamicDocument;
DEFINE_SNIPPET(_SnpRunnerExportDynamicDocument) 	

// End, SnpExportDynamicDocument.cpp