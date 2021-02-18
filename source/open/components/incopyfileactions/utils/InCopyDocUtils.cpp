//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/incopyfileactions/utils/InCopyDocUtils.cpp $
//  
//  Owner: Jon Pugh
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

#ifdef WINDOWS
    #include "ShObjIdl.h"
#endif
#include "CPMUnknown.h"

// ----- Interfaces -----

#include "IActiveContext.h"
#include "IApplication.h"
#include "IAssignmentMgr.h"
#include "IBoolData.h"
#include "IDataBase.h"
#include "IClassIDData.h"
#include "ICloseWinCmdData.h"
#include "ICommand.h"
#include "IConditionalTextFacade.h"
#include "IControlView.h"
#include "ICoreFilename.h"
#include "ICreateMCFrameData.h"
#include "IDocFileHandler.h"
#include "IDocFileType.h"
#include "IDocSavePrefs.h"
#include "IDocSavePrefsCmdData.h"
#include "IDocument.h"
#include "IDocumentCommands.h"
#include "IDocumentLayer.h"
#include "IDocumentList.h"
#include "IDocumentUIActions.h"
#include "IDocumentUtils.h"
#include "IFileStreamData.h"
#include "IFrameList.h"
#include "IGalleyUtils.h"
#include "IGeometry.h"
#include "IGeometryFacade.h"
#include "IGraphicFrameData.h"
#include "IGridAttributesPrefs.h"
#include "IHierarchy.h"
#include "IInCopyApp.h"
#include "IInCopyImportOptions.h"
#include "IInCopyFileInfo.h"
#include "IInCopyStoryList.h"
#include "IInCopyViewPrefs.h"
#include "IInCopyWorkgroupHelper.h"
#include "IInCopyWorkflow.h"
#include "IIntData.h"
#include "IINXInfo.h"
#include "IINXManager.h"
#include "IINXImportValidation.h"
#include "IItemLockData.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "ILayerUtils.h"
#include "ILayoutControlData.h"
#include "ILayoutSelectionSuite.h"
#include "ILayoutUtils.h"
#include "ILink.h"
#include "ILinkManager.h"
#include "ILinkPrefs.h"
#include "ILinkResource.h"
#include "ILinkState.h"
#include "ILiveEditFacade.h"
#include "ILockPosition.h"
#include "IMargins.h"
#include "IMasterSpreadList.h"
#include "IMultiColumnItemData.h"
#include "IMultiColumnTextFrame.h"
#include "INewPageItemCmdData.h"
#include "IOpenFileCmdData.h"
#include "IPageItemAdornmentList.h"
#include "IPageItemTypeUtils.h"
#include "IPanelControlData.h"
#include "IPlaceBehavior.h"
#include "IPMLockFile.h"
#include "IPMStream.h"
#include "IPresentationList.h"
#include "IRecoveryList.h"
#include "IReplaceCmdData.h"
#include "ISaveFileDialog.h"
#include "ISaxContentHandler.h"
#include "ISAXEntityResolver.h"
#include "ISAXParserOptions.h"
#include "ISAXServices.h"
#include "IScrapItem.h"
#include "ISnippetExport.h"
#include "ISnippetImport.h"
#include "ISpread.h"
#include "ISpreadLayer.h"
#include "ISpreadList.h"
#include "IStandAloneDoc.h"
#include "IStoryList.h"
#include "IStoryNeedsRelinkData.h"
#include "IStringData.h"
#include "ISysFileData.h"
#include "ITextAreaPrefs.h"
#include "ITextFrameColumn.h"
#include "ITextFrameFacade.h"
#include "ITextLines.h"
#include "ITextSelectionSuite.h"
#include "ITextModel.h"
#include "ITrackChangesSettings.h"
#include "IUIDData.h"
#include "IUIFlagData.h"
#include "IWidgetParent.h"
#include "IWindowList.h"
#include "IWorkgroupFacade.h"
#include "IWorkgroupStoryFacade.h"
#include "IWorkgroupUIFacade.h"
#include "IWorkspace.h"
#include "IXMLElementCommands.h"
#include "IXMLReferenceData.h"
#include "ILinkedStoryModificationState.h"
#include "IInCopyCoreOverflowHandler.h"
#include "IContainerClassification.h"
#include "IInCopySharedUtils.h"
#include "IBGTasksUIUtils.h"
#include "IEndnoteFacade.h"

// ----- Includes -----

#include "CAlert.h"
#include "CreateObject.h"
#include "FileTypeInfo.h"
#include "FileTypeRegistry.h"
#include "PMString.h"
#include "InCopyImportExportDefs.h"		// InCopy::kInCopyStoryFormatName
#include <set>
#include "K2Vector.tpp"
#include "LocaleSetting.h"
#include "SnippetStringDefs.h"
#include "SysFileList.h"
#include "UIDList.h"
#include "WideString.h"

// ----- Utility files -----

#include "IAssignmentUtils.h"
#include "IBGTasksUtils.h"
#include "IConditionalTextUtils.h"
#include "DBErrorUtils.h"
#include "IDocumentSetupUtils.h"
#include "ErrorUtils.h"
#include "FileUtils.h"
#include "IInCopyDocUtils.h"
#include "IInCopyWorkFlowUtils.h"
//#include "IINXUtils.h"
#include "ILayoutUIUtils.h"
#include "ILinkUtils.h"
#include "INoteDataUtils.h"
#include "PreferenceUtils.h"
#include "ISelectionUtils.h"
#include "IShowAlertRegistryUtils.h"
#include "IStoryLabel.h"
#include "IStoryUtils.h"
#include "StreamUtil.h"
#include "StringUtils.h"
#include "ITLAdornmentUtils.h"
#include "ITextScriptUtils.h"
#include "TransformUtils.h"
#include "Utils.h"
#include "IDocumentUIUtils.h"
#include "IHyperlinkUtils.h"

// ----- ID.h files -----

#include "DocSetupID.h"
#include "ImportExportUIID.h"
#include "InCopyCoreID.h"
#include "InCopyFileActionsID.h"
#include "InCopyFileActionsUIID.h"
#include "InCopyImportID.h"
#include "InCopySharedUIID.h"
#include "SplineID.h"



//----------------------------------------------
// Alert button string defs
#ifdef MACINTOSH
#define kUpdateDesignButtonString "Update"
#define kRevertButtonString "Revert"
#define kCancelButtonString kCancelString
#define kRevertShortcuts mRevertShortcuts
#endif

#ifdef WINDOWS
#define kUpdateDesignButtonString kYesString
#define kRevertButtonString kYesString
#define kCancelButtonString kNoString
#define kRevertShortcuts 0
#endif

//========================================================================================
// CLASS : InCopyDocUtils
//========================================================================================

class InCopyDocUtils : public CPMUnknown<IInCopyDocUtils>
{
		enum WarnType 
		{
			WarnType_CantSave,
			WarnType_UndoableSave
		};

		enum FileTypes{ kICMarkup=0, kICTemplate, kText, kRTF, kWord, kNumTypes};

public:

		const		int16	kNativeByteMark;
		const   	int16	kCrossByteMark;
		
		InCopyDocUtils(IPMUnknown* boss);
		
		//----- Doc File Actions
		virtual		void		DoSave(const UIDRef& textModel, UIFlags uiFlags = kFullUI);
		virtual		void		DoSaveAll(const UIDRef& doc, UIFlags uiFlags = kFullUI);
		virtual		void		DoSaveAs(const UIDRef& doc, bool16 copy = kFalse, const IDFile *destFile = nil, UIFlags uiFlags = kFullUI, bool8 asStationary = kFalse, FileTypeInfoID fileTypeID = kInvalidFileTypeInfoID);
		virtual		UIDRef		DoNew(bool16 openWin, IDocument::UndoSupport undoSupport);
		virtual		void		DoNewWindow(const UIDRef& doc);
		virtual		UIDRef		DoOpen(const IDFile& filesToOpen, IOpenFileCmdData::OpenFlags flags, bool16 showWindow, IDocument::UndoSupport undoSupport, UIFlags uiFlags = kFullUI);
		virtual		void		DoRevert(const UIDRef& doc, UIFlags uiFlags = kFullUI);
		virtual		void		DoUpdateDesign(const UIDRef& docRef, UIFlags uiFlags = kFullUI);
		virtual		void		DoClose(const UIDRef& doc, UIFlags uiFlags, bool16 allowCancel, IDocFileHandler::CloseCmdMode cmdMode);

		virtual		void		SetInCopyUserFile(IDocument *doc, const IDFile &newFile);

		virtual		IDocFileHandler*	QueryDocFileHandler();
		
		virtual 	bool16		ShouldDoSaveAs(IDocument* doc);
		
		//----- Menu Enablement
		virtual		bool16		CanDoSave(const UIDRef& doc);
		virtual		bool16		CanDoSaveAll(const UIDRef& doc);
		virtual		bool16		CanDoRevert(const UIDRef& doc);
		virtual		bool16		CanDoUpdateDesign(const UIDRef& doc);
		
		virtual		bool16		IsReadOnly (IDocument* iDoc);

		//----- Story Export/Import
		virtual		void		ExportAllLinkedStories(IDocument* doc, const FileTypeInfoID& fileTypeID, UIFlags uiFlags = kFullUI);
		virtual		void		ExportStoryAndCreateLink(const UIDRef& story, const IDFile& file, const FileTypeInfoID& fileTypeID);
		virtual		ErrorCode	ExportLinkedStory(const UIDRef& story, const FileTypeInfoID& fileTypeID);

		virtual		void		ImportAllLinkedStories(IDocument* doc, const FileTypeInfoID& fileTypeID, IInCopyImportOptions* options);		
		virtual		ErrorCode	ImportStoryAndCreateLink(const UIDRef& story, IPMStream* stream, IInCopyImportOptions* options, const FileTypeInfoID& fileTypeID, bool16 createLink = kTrue, UIDRef *importedItem = nil);
		virtual		ErrorCode	ImportLinkedStory(const UIDRef& sotry, const FileTypeInfoID& fileTypeID, IInCopyImportOptions* options = nil);
		
		virtual		UIDRef		GetFirstUserStory(IDocument* doc);
		virtual		void		GetLinkedStories(IDocument* doc, UIDList* stories, UIDList* links, IDataBase* db = nil);
	
	
		//----- Utils	
		virtual		UIDRef		CreateDefaultTextFrame(IDocument* doc);
		virtual		UIDRef		CreateDefaultGraphicFrame(IDocument* doc);
		
		virtual
		IDocFileHandler::
		CloseOptions 			CheckOnClose(const UIDRef& doc, UIFlags uiFlags, bool8 allowCancel);
		virtual		bool16		CheckOnRevertStory(const UIDRef& storyRef);
		
		virtual		bool16		IsFileAlreadyOpen(const IDFile& file, UIDRef* doc, UIDRef* foundStory = nil);
			
		virtual		void		GetCopyDefaultName(const UIDRef& doc, IDFile *name, bool16& useSystemDefaultDir);		
		virtual		bool16		GetOpenFileType(const IDFile& sysFile, SysOSType &type);
		virtual		bool16		GetStreamFileType(IPMStream* stream, SysOSType &type);
		virtual		void		LockNonInCopyStories(const UIDRef& doc);

private:
					void		BringOpenDocToFront( const UIDRef& newDocRef, const UIDRef& storyRef ) ;
					ErrorCode	CheckInStories( IDocument * document );
					void		LockPageItem(const UIDRef& pageItem);	
					void		DoRevertDialog(const UIDRef& doc);
					void		WarnUserUpdateDesign(IDocument* doc, WarnType type);
					void		AlertUserUnableToSave(const UIDList& failedLinks);					
					void		SwapBytes(uchar* buffer, int32 len);
					void		SetSelectionTo(IDataBase* db,const UIDRef& story);
					void		GetLinkedStories(IDocument* doc, UIDList* storyList, SysFileList* filesToOpen, IDataBase* db);
					bool16		GetStoryForImport(IDocument* doc, UIDRef& storyToImport, IDFile* fileToOpen, IDataBase* db, UIDList* storyList, const PMString& formatType, bool16 skipEndnoteStory = kFalse);
					void		GetOpenInCopyFiles(SysFileList* fileList, const UIDRef& excludeThisDoc);
					bool16		FileInList(const SysFileList& list, const IDFile& file);
					void		BuildSavePopupMenu(ISaveFileDialog *dlg);
					IInCopyViewPrefs::ActiveView GetCurrentDocView(UIDRef docRef);
					void 		SetView(IInCopyViewPrefs *sessionViewPrefs, IInCopyViewPrefs::ActiveView activeView);
					void 		SaveSelectionForUpdateDesign(UIDRef docRef, int32 &activeStoryIndex, PMString &labelString, RangeData &restoreRange);
					void 		RestoreSelectionForUpdateDesign(UIDRef newDocRef, int32 activeStoryIndex, const PMString &labelString, const RangeData &restoreRange);

					void		ValidInCopyStory(const UIDRef& storyRef, UIDRef& storyToImport, IDFile* fileToOpen, bool16* isMissing, bool16* isInCopyStory);

					PMRect		GetDefaultPageRect(IDocument* doc, ISpread *spread);
					UID			GetDefaultLayerUID(IDataBase *db, ISpread *spread);

					void 		InstallUnmanagedFrameAdornment(const UIDRef &lockableStoryRef);
					bool16		SaveChecksOnClose(const UIDRef& doc, UIFlags uiFlags, bool16 allowCancel);

					ErrorCode   HandleDocActionConflict(const UIDRef& doc, const ActionID& action, UIFlags uiFlags, bool bDoDetailChecking = false);

					bool16		AnchorStoriesAreLocked(const ITextModel* textModel, const UIDRef& docRef);
};


//========================================================================================
//	Local functions
bool16 DisableConvertQuotes(IDataBase* db);
void RestoreConvertQuotes(IDataBase* db, bool16 state);
void PostTextOptionBooleanCommand(ClassID attributeCmdBoss, IWorkspace* workspace, bool16 isUseAttribute);

//========================================================================================

CREATE_PMINTERFACE(InCopyDocUtils, kInCopyDocUtilsImpl)

//-----
// InCopyDocUtils

InCopyDocUtils::InCopyDocUtils(IPMUnknown* boss) :
	CPMUnknown<IInCopyDocUtils>(boss),
	kNativeByteMark(0xFEFFu),
	kCrossByteMark(0xFFFEu)
{

}


//--------------------------------------------------------------------------------------
#pragma mark-

//-----
// DoSaveAs()
void InCopyDocUtils::DoSaveAs(const UIDRef& doc, bool16 copy, const IDFile *destFile, UIFlags uiFlags, bool8 asStationery, FileTypeInfoID fileTypeID)
{
#ifndef ALLOW_SAVE_WITH_CLONES
	// Prevent SaveAs if doc is in use by BG Tasks
	if(HandleDocActionConflict(doc, kSaveAsActionID, uiFlags) != kSuccess)
	{
		// Cancel the action
		return;
	}
#endif /* ALLOW_SAVE_WITH_CLONES */

	// Conflict was resolved ... Continuing with the save as


	InterfacePtr<IDocFileType> docType(doc, UseDefaultIID());
	FileTypeInfoID docTypeID = docType->GetDocFileType();
	FileTypeInfoID saveTypeID = docTypeID;
	if (fileTypeID != kInvalidFileTypeInfoID)
	{
		if (fileTypeID == kPublicationFileTypeInfoID)
			saveTypeID = kInCopyXMLMarkupFileTypeInfoID;	// !INCOPY DEFAULT!
		else
			saveTypeID = fileTypeID;
	}
	else
	{
		/* hack to switch over to .icml as default */
		if (destFile)
		{
			PMString destFileName(FileUtils::SysFileToPMString(*destFile));
			if (destFileName.Contains(".icml"))
				saveTypeID = kInCopyXMLMarkupFileTypeInfoID;
			else if (destFileName.Contains(".incx"))
				saveTypeID = kInCopyXMLInterchangeFileTypeInfoID;
		}
	}

	bool8 createdDestSysFile = kFalse;
	PMString*	title = nil;
	IDFile originalPath;			// needed if we end up saving the doc as an alternate
	IDFile *originalPathPtr = nil;	// needed if we end up saving the doc as an alternate

	InterfacePtr<IInCopyWorkgroupHelper> icwgHelper(GetExecutionContextSession(), UseDefaultIID());

	if(destFile == nil && uiFlags == kSuppressUI)
	{
		ErrorUtils::PMSetGlobalErrorCode(kSaveDocCouldntShowUIError);
	}
	else
	{
		if(!destFile)
		{
			
			InterfacePtr<ISaveFileDialog> saveDlg((ISaveFileDialog*)::CreateObject(kSaveDocDialogBoss, IID_ISAVEFILEDIALOG));
			BuildSavePopupMenu(saveDlg);
#ifdef WINDOWS				
			saveDlg->SetAdditionalFOSFlags(FOS_OVERWRITEPROMPT | FOS_NOREADONLYRETURN);
#endif
			IDFile defaultFile;
			bool16 useSystemDefaultDir = kFalse;				

			if (copy)
			{
				title = new PMString("Save a Copy");
				title->Translate();
				GetCopyDefaultName(doc, &defaultFile, useSystemDefaultDir);			
			}
			else
			{		
			  	// Get the document's current file. This will be the default Save As file name. If there is
			  	// no current file name (because the document hasn't been saved yet), use the document name
			  	// in the users document directory.
			  	InterfacePtr<IDocument> document(doc, IID_IDOCUMENT);
			  	IDataBase *db = doc.GetDataBase();
				IDFile *pDefaultFile = nil;
				const IDFile *pDocSysFile = db->GetSysFile();
				IDFile docSysFile;

				IDFile originalSysFile;
				if ( pDocSysFile != nil )
				{
					if (icwgHelper && icwgHelper->GetOriginalSysFile(doc, originalSysFile))
					{
						pDefaultFile = &originalSysFile;
					}
					else
					{
						docSysFile = *pDocSysFile;
						pDefaultFile = &docSysFile;
					}
				}

			  	if ((pDefaultFile == nil) || (document->IsReadOnly()))
			  	{
			  		PMString docName;
			  		document->GetName(docName);	// default name for saved document is old name
			  		
			  		InterfacePtr<IInCopyApp> appIC(GetExecutionContextSession(), UseDefaultIID());
			  		defaultFile = appIC->GetDefaultFile(docName, &useSystemDefaultDir);
			  	}
			  	else
			  		defaultFile = *pDefaultFile;
			}

			InterfacePtr<const IDocSavePrefs> iDocSavePrefs( (IDocSavePrefs*)::QuerySessionPreferences(IID_IDOCSAVEPREFS) );

			InterfacePtr<IBoolData> savepreview( saveDlg, IID_IBOOLDATA );
			bool16 setbool = iDocSavePrefs->GetSaveThumbnailWithDocument();
			savepreview->Set( setbool );
			IDFile whatFile;
			int32 listIndex = 0;						

			// set up the workgroup save as data, used by the dialog
			if (icwgHelper && !copy)
				icwgHelper->SetWorkgroupSaveAsData(doc);

			if(!saveDlg->DoDialog(&defaultFile, &whatFile, &listIndex, useSystemDefaultDir, kTrue, title))
			{
				ErrorUtils::PMSetGlobalErrorCode(kCancel);
			}
			else
			{			
				bool16 continueSave = kFalse;
			
				while (kTrue)
				{
					PMString whatExtension;
					FileUtils::GetExtension(whatFile, whatExtension);
					whatExtension.SetTranslatable(kFalse);
					
					switch (listIndex)
					{
						case kICTemplate:
							saveTypeID = kInCopyTemplateFileTypeInfoID;
							break;
						case kText:
							saveTypeID = kTEXTFileTypeInfoID;
							break;
						case kRTF:
							saveTypeID = kRTFFileTypeInfoID;
							break;
						case kICMarkup:
							saveTypeID = kInCopyXMLMarkupFileTypeInfoID;
							break;
						default:
							ASSERT_FAIL("unknown file type");
					}
					
					PMString legalExtension(FileTypeRegistry::GetCurrentFileExtension(saveTypeID));
					legalExtension.SetTranslatable(kFalse);
					bool16 legalName = legalExtension.Compare(kFalse, whatExtension) == 0;
#if MACINTOSH
					if (whatExtension.IsEmpty())	// no extension is legal on Mac
						legalName = kTrue;
#endif

					if (!legalName)
					{
						// need to replace the bad extension with the proper one
						APathComponent name = whatFile.GetName();
						AString le(legalExtension.GrabUTF16Buffer(nil));
						name.SetExtension(le);
						whatFile.SetName(name);
					}
					
					// at this point we have a legal name
					// now we want to make sure that there isn't a lock or lock file for that file name
					// if so, we want to display an alert and allow the user to choose a new name

					if ( !Utils<Facade::IWorkgroupStoryFacade>()->IsWriteable( whatFile ) )
					{
						// Story file cannot be written because it is already locked somewhere.
						PMString userName, docName, appName;
						Utils<Facade::IWorkgroupStoryFacade>()->GetStoryLockNames( whatFile, userName, docName, appName, uiFlags );
						PMString msg("");
						if ( Utils<Facade::IWorkgroupFacade>()->IsVersioned( whatFile ) )
						{
							msg = PMString("CannotSaveOntoLockedFileMinimal");
							msg.Translate();
							ReplaceStringParameters(&msg, userName);
						}
						else
						{
							msg = PMString("CannotSaveOntoLockedFile");
							msg.Translate();
							ReplaceStringParameters(&msg, userName, appName, docName);
						}
						CAlert::ErrorAlert(msg);
						if (!saveDlg->DoDialog(&defaultFile, &whatFile, &listIndex, useSystemDefaultDir, kTrue, title))
						{
							ErrorUtils::PMSetGlobalErrorCode(kCancel);
							break;
						}
						else
						{
							continue;
						}						
					}

					bool16 currentbool = savepreview->GetBool();
					if (currentbool != setbool)
					{
						InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSetDocSavePrefsCmdBoss));
						InterfacePtr<IDocSavePrefsCmdData> iDocSavePrefsCmdData(cmd,IID_IDOCSAVEPREFSCMDDATA);

						iDocSavePrefsCmdData->SetSaveThumbnailWithDocument(currentbool);
						iDocSavePrefsCmdData->SetThumbnailOptions(iDocSavePrefs->GetThumbnailOptions());
						iDocSavePrefsCmdData->SetPreviewSizeOptions(iDocSavePrefs->GetPreviewSizeOptions());

						CmdUtils::ProcessCommand(cmd);
					}

					destFile = new IDFile(whatFile);
					createdDestSysFile = destFile != nil;

					// see if save as alternate was checked in save as dialog
					if (!copy && icwgHelper && icwgHelper->ShouldSaveAsAlternate(doc, originalPath))
						originalPathPtr = &originalPath;

					if (!Utils<IStoryUtils>()->IsAStoryInterchangeFileTypeID(saveTypeID))
					{
						// warn the user the format/feature might lost because the type changed
						PMString complaint("SaveAsFeatureLost");
						complaint.Translate();
						int16 result = CAlert::ModalAlert(complaint, kYesString, kNoString,	"", 1, CAlert::eWarningIcon);
						if (result == 2)
						{
							continueSave = kFalse;
							if(createdDestSysFile)
							{
								delete destFile;
								destFile = nil;			
								createdDestSysFile = kFalse;
							}
							
							if (!saveDlg->DoDialog(&defaultFile, &whatFile, &listIndex, useSystemDefaultDir, kTrue, title))
							{
								ErrorUtils::PMSetGlobalErrorCode(kCancel);
								break;
							}						
						}
						else
						{
							continueSave = kTrue;
							break;
						}
					}
					else
						break;
				}
			}
		}

		if (!copy && ErrorUtils::PMGetGlobalErrorCode() == kSuccess)
		{
			// If we're saving a previous version as the current version, determine if the 
			// current version is open, then silently close the current version document 
			// (discarding any changes)

			UIDRef	currentVersionDoc = icwgHelper ? icwgHelper->GetCurrentVersionDoc(doc, *destFile) : UIDRef::gNull;
			if (currentVersionDoc != UIDRef::gNull)
			{
				// In this case the original is never the front document, but it must be in order to
				// close it.
				InterfacePtr<ICommand> frontDocCmd(CmdUtils::CreateCommand(kSetFrontDocCmdBoss));
				frontDocCmd->SetItemList( UIDList(currentVersionDoc) );
				CmdUtils::ProcessCommand(frontDocCmd);

				//DoClose(currentVersionDoc, kSuppressUI, kFalse, IDocFileHandler::kSchedule);
				DoClose(currentVersionDoc, kFullUI, kTrue, IDocFileHandler::kSchedule);
				CmdUtils::ProcessScheduledCmds();
			}
		}
	}

	if(destFile && ErrorUtils::PMGetGlobalErrorCode() == kSuccess)
	{
		//----- turn off undo so that anything we do inside the save as command is not placed on the undo stack
		CmdUtils::AutoUndoSequencePtr seq(doc.GetDataBase());
		if (copy) 
		{
			InterfacePtr<ICommand> cmd(Utils<IDocumentCommands>()->CreateSaveACopyCommand() );
			cmd->SetItemList(  UIDList(doc));
			
			InterfacePtr<ISysFileData> data(cmd, IID_ISYSFILEDATA);
			data->Set(*destFile);	
			InterfacePtr<IUIFlagData> uiFlagData(cmd, IID_IUIFLAGDATA);
			uiFlagData->Set(uiFlags);
			InterfacePtr<IDocFileType> dType(cmd, UseDefaultIID());
			if (dType)
				dType->SetDocFileType(saveTypeID);
			
			CmdUtils::ProcessCommand(cmd);
		}
		else 
		{
		//	Utils<IDocumentCommands>()->SaveAs(doc, *destFile, uiFlags);
			InterfacePtr<ICommand> cmd(Utils<IDocumentCommands>()->CreateSaveAsCommand() );
			cmd->SetItemList(UIDList(doc));
			InterfacePtr<ISysFileData> sysFileData(cmd, IID_ISYSFILEDATA);
			sysFileData->Set(*destFile);
			InterfacePtr<IUIFlagData> uiFlagData(cmd, IID_IUIFLAGDATA);
			uiFlagData->Set(uiFlags);
			InterfacePtr<IDocFileType> dType(cmd, UseDefaultIID());
			if (dType)
				dType->SetDocFileType(saveTypeID);
			CmdUtils::ProcessCommand(cmd);
			
			if (ErrorUtils::PMGetGlobalErrorCode() == kSuccess)
				docType->SetDocFileType(saveTypeID); // reset the file type for the current doc

			//if (ErrorUtils::PMGetGlobalErrorCode() == kSuccess && 
			//	originalPathPtr != nil && 
			//	icwgHelper)
			//{
			//	// make the alternate
			//	icwgHelper->MakeAlternate(destFile, originalPathPtr);
			//}
		}
	}
	
	if(destFile && createdDestSysFile)
		delete destFile;
			
	if (title)
		delete title;
	
	return;
}

//-----
// DoSave()

void InCopyDocUtils::DoSave(const UIDRef& textModel, UIFlags uiFlags)
{
	IDataBase* db = textModel.GetDataBase();
	UIDRef doc(db, db->GetRootUID());
	InterfacePtr<IDocument> document(doc, UseDefaultIID());
	InterfacePtr<IDocFileType> dType(doc, UseDefaultIID());

	FileTypeInfoID fileInfoID = dType->GetDocFileType();
	if ( fileInfoID == kTEXTFileTypeInfoID || fileInfoID == kRTFFileTypeInfoID)
	{
		if (document->IsSaved() && !document->IsReadOnly())
		{
			PMString complaint("SaveAsFeatureLost");
			complaint.Translate();
			int16 result = CAlert::ModalAlert(complaint, kYesString, kNoString,	"",
													1, CAlert::eWarningIcon);
			if (result == 2)
			{
				return;
			}

			// reset the selection to an insert point not a range
			UIDRef modelRef;
			TextIndex activeStart, activeEnd;
			Utils<IGalleyUtils>()->GetCurrentTextSelection(activeStart, activeEnd, &modelRef);
			if (activeStart != activeEnd)
			{
				RangeData restoreRange = RangeData(activeStart, RangeData::kLeanForward);
				InterfacePtr<ISelectionManager> selMgr(Utils<ISelectionUtils>()->QueryActiveSelection());

				// Get the selection suite (for whatever view)
				InterfacePtr<ITextSelectionSuite> suite(selMgr, UseDefaultIID());
				if (!suite)
					suite.reset(InterfacePtr<ITextSelectionSuite>(selMgr, IID_ITEMPTEXTSELECTION_SUITE).forget());
			
				if (suite)
					suite->SetTextSelection(modelRef, restoreRange, Selection::kScrollIntoView, &restoreRange);
			}

			// direct save, will call exportmanager to export the document with the right file type
			Utils<IDocumentCommands>()->Save(doc, uiFlags);

			return;
		}
	}

	// make sure we have a document file & create one if necessary
	InterfacePtr<IStandAloneDoc> standAlone(document, IID_ISTANDALONEDOC);
	InterfacePtr<IIntData> iIntData(doc, IID_IBACKGROUNDSAVE);
	if (standAlone->IsStandAloneDoc() && iIntData->GetInt()==0)
	{
		if (ShouldDoSaveAs(document))
		{
			DoSaveAs(doc, kFalse, nil, uiFlags);
			return;
		}
	}

	InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kInCopySaveStoryCmdBoss));
	cmd->SetItemList(UIDList(textModel));

	InterfacePtr<IBoolData> iBoolData(cmd, UseDefaultIID());
	iBoolData->Set(kTrue);

	InterfacePtr<IUIFlagData> uiFlagData(cmd, IID_IUIFLAGDATA);
	uiFlagData->Set(uiFlags);

	CmdUtils::ProcessCommand(cmd);
}

//-----
// DoSaveAll()

void InCopyDocUtils::DoSaveAll(const UIDRef& doc, UIFlags uiFlags)
{
#ifndef ALLOW_SAVE_WITH_CLONES
	// Prevent Save all stories if doc is in use by BG Tasks
	if(HandleDocActionConflict(doc, kSaveAllStoriesActionID, uiFlags) != kSuccess)
	{
		// Cancel the action
		return;
	}
	// Conflict was resolved ... Continuing with the save all stories
#endif /* ALLOW_SAVE_WITH_CLONES */

	InterfacePtr<IDocument> document(doc, IID_IDOCUMENT);
	InterfacePtr<IDocFileType> dType(doc, UseDefaultIID());

	FileTypeInfoID fileInfoID = dType->GetDocFileType();
	if ( fileInfoID == kTEXTFileTypeInfoID || fileInfoID == kRTFFileTypeInfoID)
	{
		if (document->IsSaved() && !document->IsReadOnly())
		{
			PMString complaint("SaveAsFeatureLost");
			complaint.Translate();
			int16 result = CAlert::ModalAlert(complaint, kYesString, kNoString,	"",
													1, CAlert::eWarningIcon);
			if (result == 2)
			{
				return;
			}
	
			// reset the selection to an insert point not a range
			UIDRef modelRef;
			TextIndex activeStart, activeEnd;
			Utils<IGalleyUtils>()->GetCurrentTextSelection(activeStart, activeEnd, &modelRef);
			if (activeStart != activeEnd)
			{
				RangeData restoreRange = RangeData(activeStart, RangeData::kLeanForward);
				InterfacePtr<ISelectionManager> selMgr(Utils<ISelectionUtils>()->QueryActiveSelection());

				// Get the selection suite (for whatever view)
				InterfacePtr<ITextSelectionSuite> suite(selMgr, UseDefaultIID());
				if (!suite)
					suite.reset(InterfacePtr<ITextSelectionSuite>(selMgr, IID_ITEMPTEXTSELECTION_SUITE).forget());
			
				if (suite)
					suite->SetTextSelection(modelRef, restoreRange, Selection::kScrollIntoView, &restoreRange);
			}

			// direct save, will call exportmanager to export the document with the right file type
			Utils<IDocumentCommands>()->Save(doc, uiFlags);
			return;
		}
	}

	if (ShouldDoSaveAs(document))
	{
		//----- redirect to save as if standalone, otherwise save
		//      as many stories as possible and warn user
		InterfacePtr<IStandAloneDoc> standAlone(doc, IID_ISTANDALONEDOC);
		if (standAlone->IsStandAloneDoc())
		{
			DoSaveAs(doc, kFalse, nil, uiFlags);
			return;
		}
	}
  
	Utils<IDocumentCommands>()->Save(doc, uiFlags);
	
	// Write out the story order file.
	Utils<IGalleyUtils>()->WriteStoryListFile(doc);
		
	return;
}

//-----
// DoNew()

UIDRef InCopyDocUtils::DoNew(bool16 openWin, IDocument::UndoSupport undoSupport)
{
	ErrorCode err = kFailure;
	
	UIDRef newDocRef (nil, kInvalidUID);

	//----- Create a new document
	InterfacePtr<ICommand> newDocCmd(Utils<IDocumentCommands>()->CreateNewCommand(/*flags = */kFullUI, /*styleToUse*/nil, undoSupport));
	if((err = CmdUtils::ProcessCommand(newDocCmd)) == kSuccess)
	{
		UIDRef defaultFrame(newDocCmd->GetItemList()->GetRef(1));
		newDocRef = newDocCmd->GetItemList()->GetRef(0);
		IDataBase* db = newDocRef.GetDataBase();

		if ( openWin )
		{
			CmdUtils::AutoUndoSequencePtr seq(db);

			//----- Find the default story
			InterfacePtr<IGraphicFrameData> frame(defaultFrame, IID_IGRAPHICFRAMEDATA);
			InterfacePtr<IMultiColumnTextFrame> mcf(db, frame->GetTextContentUID(), UseDefaultIID());
			UIDRef story(db, mcf->GetTextModelUID());

			//the purpose of IID_INEWDOC is to tell
		    //GalleyOpenLayoutWinResponder that it needs to apply the none para style as default when the newly created document has frame grid
			InterfacePtr<IBoolData> newDocFlag(db, db->GetRootUID(), IID_INEWDOC);
			if (newDocFlag)
				newDocFlag->Set(kTrue);

			//----- create a layout window for the new doc
			InterfacePtr<ICommand> newWinCmd(Utils<ILayoutUIUtils>()->CreateNewLayoutPresentationCmd());
			newWinCmd->SetItemList(newDocRef);
			
			if ((err = CmdUtils::ProcessCommand(newWinCmd)) == kSuccess)
			{
				SetSelectionTo(db, story);
			}
			
		}
		
		// New document should not result in the user being asked whether they want to
		// save the document when they close. Normally, we would check the state of the
		// database on entry and only set it on exit if it's been changed in this case
		// there is no database on entry because we created it so just set the modified
		// state to false. Part of fix for bug 476281.
		db->SetModified(kFalse);
		
	}

	return newDocRef;
}

//-----
// DoNewWindow()

void InCopyDocUtils::DoNewWindow(const UIDRef& doc)
{
	InterfacePtr<ICommand> newWinCmd(Utils<ILayoutUIUtils>()->CreateNewLayoutPresentationCmd());
	newWinCmd->SetItemList( UIDList(doc) );

	CmdUtils::ProcessCommand(newWinCmd);
}

//-----
// DoOpen()

UIDRef InCopyDocUtils::DoOpen(const IDFile& fileToOpen, IOpenFileCmdData::OpenFlags flags, bool16 showWindow, IDocument::UndoSupport undoSupport, UIFlags uiFlags)
{
	ErrorCode err = kSuccess;

	IDFile theFileToCheck(fileToOpen);
	UIDRef newDocRef(nil, kInvalidUID);
	UIDRef storyRef(nil, kInvalidUID);
	FileTypeInfoID fileInfoID = FileTypeRegistry::GetFileTypeInfoIDForFile(theFileToCheck);
	if ( Utils<IAssignmentUtils>()->IsInCopyAssignmentPackageFileTypeID(fileInfoID) )
	{
		if (!fileToOpen.Exists())
		{
			//sync with workgroup if it is installed
			InterfacePtr<IInCopyWorkgroupHelper> icwgHelper(GetExecutionContextSession(), UseDefaultIID());
			if( !icwgHelper->WorkgroupSyncPreLoad( fileToOpen ) )
				return newDocRef;
		}
		
		// InCopy assignment package: get the the assignment file to be opened from this package
		// so that we can check to see if it is already open.
		InterfacePtr<IAssignmentMgr> assMgr(GetExecutionContextSession(), UseDefaultIID());
		IDFile assignmentFileToOpen = assMgr->GetAssignmentFileToOpenFromPackage(theFileToCheck);
		if (assignmentFileToOpen.Exists())
			theFileToCheck = assignmentFileToOpen;
	}

	bool16 isAlreadyOpen = IsFileAlreadyOpen(theFileToCheck, &newDocRef, &storyRef);
	if (isAlreadyOpen && flags != IOpenFileCmdData::kOpenCopy)
	{
		if (Utils<IAssignmentUtils>()->IsInCopyAssignmentPackageFileTypeID(fileInfoID))
		{
			// InCopy assignment package: assignment file is already open, explode the contents of the package so 
			// update design will enable if appropriate.
			IDFile file;
			InterfacePtr<IAssignmentMgr> assMgr(GetExecutionContextSession(), UseDefaultIID());
			assMgr->ExplodeInCopyPackageForOpen(fileToOpen, uiFlags, file);
		}

		BringOpenDocToFront( newDocRef, storyRef ) ;
		return newDocRef;
	}

	//----- We call the regular open file with window command and allow the open manager to call 
	//      our open provider that handles incopy files
	InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(showWindow ? kOpenFileWithWindowCmdBoss : kOpenFileCmdBoss));
	InterfacePtr<IOpenFileCmdData> iFileToOpen(cmd, IID_IOPENFILECMDDATA);			

	//sync with workgroup if it is installed
	InterfacePtr<IInCopyWorkgroupHelper> icwgHelper(GetExecutionContextSession(), UseDefaultIID());
	if( !icwgHelper->WorkgroupSyncPreLoad( fileToOpen ) )
		return newDocRef;
	

	// Check to make sure the file exists after WorkgroupSyncPreLoad because
	// we might not have a local replica of the file and PreLoad will assure
	// that we do.
	//
	if (!fileToOpen.Exists())
	{
		PMString errorMessage("The file ^1 was not found"); 
		errorMessage.Translate(); 
		PMString failedName(FileUtils::SysFileToPMString(fileToOpen)); 
		failedName.SetTranslatable(kFalse); 
		StringUtils::ReplaceStringParameters (&errorMessage, failedName); 

		ErrorUtils::PMSetGlobalErrorCode(kFileNotFound, &errorMessage);
		return newDocRef;
	}
	
	//----- InDesign files are generally opened as copies, InCopy files can open as a copy or original
	//      If we have an InDesign file, make sure that flag is set to open a copy.
	//---- make sure we close the stream we open or webdav will have problems...besides it's just a nice thing to do
	{
		SysOSType type;
		InterfacePtr<IPMStream> stream(StreamUtil::CreateFileStreamRead(fileToOpen));
		if (stream && !GetStreamFileType(stream, type))
		{
			SysFileType anothertype;
			FileUtils::GetStreamFileType(stream, anothertype);
			if (anothertype == kPubFileType)
			{
				flags = IOpenFileCmdData::kOpenCopy;

				//if it's a pub file that's already open, bring it to front
				if ( isAlreadyOpen )
				{
					BringOpenDocToFront( newDocRef, storyRef ) ;
					return newDocRef ;
				}
			}
			else if (!GetOpenFileType(fileToOpen, type)) // might be text or rtf 
			{		
				DBErrorUtils::SetDBError(kOpenDocFailedError, &fileToOpen);
				return newDocRef;
			}
		}
		else
		{
			// If default is set, then we open a copy if the file is a template (stationary) file, otherwise open original.
			if (flags == IOpenFileCmdData::kOpenDefault)
			{
				SysFileType fileType;
				bool16 gotType = FileUtils::GetOpenFileType(fileToOpen, fileType);
				if (gotType && (fileType == kTplFileType))
					flags = IOpenFileCmdData::kOpenCopy;
				else
					flags = IOpenFileCmdData::kOpenOriginal;
			}
//			if (fileInfoID == kInCopyTemplateFileTypeInfoID)
//				flags = IOpenFileCmdData::kOpenCopy;
		}
	}

	iFileToOpen->Set(fileToOpen, uiFlags, flags, /*lockFlags */ IOpenFileCmdData::kUseLockFile, undoSupport);				

	err = CmdUtils::ProcessCommand(cmd);

	if (err == kSuccess) 
	{
		if (cmd->GetItemList() && cmd->GetItemList()->Length() > 0)
		{
			newDocRef = cmd->GetItemList()->GetRef(0);

			InterfacePtr<IDocument> doc(newDocRef, IID_IDOCUMENT);
			
			// Attach overset text frame to the all the incopy stories. This used to be done in a responder but because of ordering issues between responders
			// and observers it was moved here.
			InterfacePtr<IStandAloneDoc> standAlone(doc, IID_ISTANDALONEDOC);
			if (standAlone && !standAlone->IsStandAloneDoc())
			{
				InterfacePtr<IInCopyStoryList> icStoryList(doc, UseDefaultIID());
						
				for (int32 i = 0; i < icStoryList->GetStoryCount(); i++)
				{
					InterfacePtr<ITextModel> model(icStoryList->GetNthStoryRef(i), UseDefaultIID());
					if (model)
					{
						InterfacePtr<IFrameList> frameList(model->QueryFrameList());
						int32 preFrameCount = frameList->GetFrameCount();

						// braces are for scoping the autosequence and are important, see comment below
						{
							IDataBase* db = newDocRef.GetDataBase();
							CmdUtils::AutoUndoSequencePtr seq(db);
							IDataBase::SaveRestoreModifiedState smersh(db);
							
							InterfacePtr<IInCopyCoreOverflowHandler> overflowHandler(doc, UseDefaultIID());
							overflowHandler->AppendOversetContainer(icStoryList->GetNthStoryRef(i));
						}
						
						// This labeling of overset frames used to be handled in the AppendOversetContainer call but now with CS4 the column frames are added
						// on a notification when the sequence point goes out of scope. So the frame list isn't correct until this point
						for (int32 frameIndex = preFrameCount; frameIndex < frameList->GetFrameCount(); frameIndex++)
						{
							InterfacePtr<ITextFrameColumn> newTFC(frameList->QueryNthFrame(frameIndex));
							InterfacePtr<IContainerClassification> classifier(newTFC, UseDefaultIID());
							classifier->SetClassification(IContainerClassification::kOversetContainer);
						}
					}
				}
			}


			//----- Set the text tool and insertion for this document. It would be nice to find some
			//      way to get the default text frame besides digging for it
			UIDRef defaultStory = GetFirstUserStory(doc);
			if (defaultStory != UIDRef::gNull)
			{
				IDataBase* db = defaultStory.GetDataBase();
				CmdUtils::AutoUndoSequencePtr seq(db);
				
				SetSelectionTo(db, defaultStory);
		
				//----- mark the database as unmodified unless we opened a copy of a standalone
				bool16 isStandAloneDoc = standAlone && standAlone->IsStandAloneDoc();

				//----- Lock the story here if it is a standalone graphic story; the
				//		bridge responder handles standalone text stories
				if (isStandAloneDoc)
				{
					InterfacePtr<IGraphicFrameData> graphicData( defaultStory, UseDefaultIID() );
					if ( graphicData && graphicData->IsGraphicFrame()  && graphicData->GetTextContentUID() == kInvalidUID )
					{
						// okay, this is a standalone graphic story so lock it
						InterfacePtr<ICommand> lockCmd(CmdUtils::CreateCommand(kSetItemLockDataCmdBoss));
						if (lockCmd)
						{
							InterfacePtr<IBoolData> lockData(lockCmd, IID_IBOOLDATA);
							lockData->Set(kTrue);
							lockCmd->SetItemList(defaultStory);
							err = CmdUtils::ProcessCommand(lockCmd);
							ASSERT_MSG(err == kSuccess, "InCopyDocUtils::DoOpen: SetStoryLockStateCmd failed");
						}
					}
				}

				if (isStandAloneDoc && flags == IOpenFileCmdData::kOpenCopy)
					db->SetModified(kTrue);
				else
					db->SetModified(kFalse);					
			}
		}
	}

	return newDocRef;
}

// put the selection in the newly "opened" document, which is already open
void InCopyDocUtils::BringOpenDocToFront( const UIDRef& newDocRef, const UIDRef& storyRef )
{
	IDocumentPresentation* docPres = Utils<IDocumentUIUtils>()->GetFrontmostPresentationForDocument(newDocRef.GetDataBase());
	if (docPres)
		docPres->MakeActive();
	IActiveContext* ac = GetExecutionContextSession()->GetActiveContext();
	IControlView* view = ac->GetContextView();
	if (view)
	{
		InterfacePtr<ITextModel> textModel(storyRef, UseDefaultIID());
		if (docPres && textModel)	// can only select if we have a window and a text story
		{
			if (Utils<IGalleyUtils>()->InLayout(docPres))
				Utils<IGalleyUtils>()->SetLayoutTextSelection(0, 0, storyRef, kFalse); 
			else
				Utils<IGalleyUtils>()->SetGalleyTextSelection(0, 0, storyRef, view, kFalse);
		}
	}
}

//-----
// DoRevert()
// create a default docfilehandler and let it do the revert

void InCopyDocUtils::DoRevert(const UIDRef& doc, UIFlags uiFlags)
{
	// Prevent Revert if doc is in use by BG Tasks
	if(HandleDocActionConflict(doc, kRevertActionID, uiFlags) != kSuccess)
	{
		// Cancel the action
		return;
	}
	// Conflict was resolved ... Continuing with the Revert

	InterfacePtr<IDocFileHandler> docFileHandler((IDocFileHandler*)::CreateObject(
		Utils<IDocumentUIActions>()->GetDefaultDocFileHandlerID(), 
		IID_IDOCFILEHANDLER
		));
	if (docFileHandler)
	{
		docFileHandler->Revert(doc, uiFlags);
	}
}

//-----
// DoUpdateDesign()

void InCopyDocUtils::DoUpdateDesign(const UIDRef& docRef, UIFlags uiFlags)
{

	ErrorCode result = kFailure;
	
	//----- Before responders would go here, but we don't need them yet

	IDFile originalFile;
	if ( !Utils<Facade::ILiveEditFacade>() ) /* verify workgroup & bridge plugins are available */
	{
		ErrorUtils::PMSetGlobalErrorCode(kFailure);
		return;
	}
	
	IDataBase* db = docRef.GetDataBase();
	K2Vector<IDFile> checkedOutLinks;
	IDocument::UndoSupport docUndoSupport (IDocument::kFullUndoSupport); 
	//----- Save all the linked stories, scope so we release the document ptr before closing
	{ 	
		//----- We now stuff a "fake" sysfile that points to the original document into the database
		//      of InDesign and InCopy files opened in Denali. We can now just get the databases sysfile
		// 		to do update design.
		
		const IDFile* tmpFile = docRef.GetDataBase()->GetSysFile();	//Copy the sysfile because it is going away when we close
		if (tmpFile == nil)
		{
			ErrorUtils::PMSetGlobalErrorCode(kFailure);
			return;
		}
		
		originalFile = (*tmpFile);
		
		InterfacePtr<IDocument> doc(docRef, IID_IDOCUMENT);
		docUndoSupport = doc->GetUndoSupport();
		InterfacePtr<IInCopyStoryList> icStories(doc, IID_IINCOPYSTORYLIST);
		//----- If the doc is dirtied, warn the user that they will not be able to undo any
		//		changes after the update design and give them a chance to back out
		if (kFullUI == uiFlags && (db->IsModified() && icStories->GetStoryCount() > 0))
		{
			WarnUserUpdateDesign(doc, WarnType_UndoableSave);
			if (ErrorUtils::PMGetGlobalErrorCode() != kSuccess)
				return;
		}
		
		//----- If there are stories that can't be saved, give the user
		//      a chance to back out. We only care to do this warning if there
		//      are incopy stories in the story list.
		if (ShouldDoSaveAs(doc) && (icStories->GetStoryCount() > 0))
		{
			// if we are suppressing the ui we can't proceed
			if (kSuppressUI == uiFlags)
			{
				// get out of here
				ErrorUtils::PMSetGlobalErrorCode(kCancel);
				return;
			}

			WarnUserUpdateDesign(doc, WarnType_CantSave);
			if (ErrorUtils::PMGetGlobalErrorCode() != kSuccess)
				return;
		}

		Utils<ILinkUtils> linkUtils;
		UIDList checkedOutStories(db);
		Utils<Facade::IWorkgroupStoryFacade> iWorkgroupStoryFacade;
		Utils<Facade::IWorkgroupFacade> wgUtils;
		// find all the checked out stories in the open doc
		for (int32 i = 0; i < icStories->GetStoryCount() && wgUtils && iWorkgroupStoryFacade; ++i)
		{
			UIDRef storyRef(icStories->GetNthStoryRef(i));
			IDFile storyFile;
			linkUtils->GetFileFromLink(storyRef, &storyFile);

			if ( wgUtils->CanCheckIn( iWorkgroupStoryFacade->GetAssetUIDRef( storyRef ), storyRef.GetUID() ) )
			{
				checkedOutStories.Append(storyRef);
				checkedOutLinks.push_back(storyFile);
			}
		}
		
		//----- start a transaction on this database
		CmdUtils::AutoUndoSequencePtr seq(db);

		Utils<Facade::ILiveEditFacade>()->CheckIn( checkedOutStories,
										  Facade::ILiveEditFacade::CheckInOptions( Facade::ILiveEditFacade::enUnlockAsset | Facade::ILiveEditFacade::enExportStory ), // Do not save a new version!
										  nil, nil, ICommand::kAutoUndo, uiFlags );	
		//----- make sure that we mark the database as not modified
		db->SetModified(kFalse);
		
	}
	

	//----- Save aside the view so it can be restored after the replacement document open
	IInCopyViewPrefs::ActiveView docView = GetCurrentDocView(docRef);
	
	
	//----- Save aside selection information so that we can attempt to restore it later. 
	RangeData restoreRange(0, RangeData::kLeanForward);
	int32 activeStoryIndex;
	PMString activeStoryLabel;
	SaveSelectionForUpdateDesign(docRef, activeStoryIndex, activeStoryLabel, restoreRange);
	
	//----- Close this document	
	InterfacePtr<IDocumentUtils> docUtils ( (IDocumentUtils*)GetExecutionContextSession()->QueryInterface(IID_IDOCUMENTUTILS));
	InterfacePtr<IDocFileHandler> handler(docUtils->QueryDocFileHandler(docRef));
	if(handler)
	{
		handler->Close(docRef, uiFlags);
		result = ErrorUtils::PMGetGlobalErrorCode();
		if (result != kSuccess)
			return;
	}
	
	//----- Flush pending commands so that the document is fully closed
	bool16 flushed = CmdUtils::ProcessScheduledCmds(ICommand::kLowestPriority);
	ASSERT_MSG(flushed, "InCopyDocUtils::DoUpdateDesign() - all commands were not flushed, there may be problems closing doc");	
	
	//----- reopen the file	using closed documents view preferences
	InterfacePtr<IInCopyViewPrefs>	sessionViewPrefs((IInCopyViewPrefs*)::QuerySessionPreferences(IID_IINCOPYVIEWPREFS));
	IInCopyViewPrefs::ActiveView savedSessionView = sessionViewPrefs->GetActiveView();
	if (savedSessionView != docView)
	{
		SetView(sessionViewPrefs, docView);
	}

	// opening the new document invalidates all the UIDs in our current doc
	UIDRef newDocRef = DoOpen(originalFile, IOpenFileCmdData::kOpenCopy, /*showWindow*/ kTrue, docUndoSupport);

	ErrorCode err = ErrorUtils::PMGetGlobalErrorCode();

	if (err == kSuccess && newDocRef != UIDRef::gNull)
	{
		//----- Restore the original session view preferences
		if (savedSessionView != docView)
		{
			SetView(sessionViewPrefs, savedSessionView);
		}

		// check out the previously checked out stories
		Utils<ILinkUtils> linkUtils;
		InterfacePtr<IDocument> newDoc(newDocRef, UseDefaultIID());
		InterfacePtr<IInCopyStoryList> newStories(newDoc, IID_IINCOPYSTORYLIST);
		UIDList newCheckedOutStories(newDocRef.GetDataBase());
		// find all the checked out stories in the open doc
		for (int32 i = 0; i < newStories->GetStoryCount(); ++i)
		{
			UIDRef storyRef(newStories->GetNthStoryRef(i));
			IDFile storyFile;
			linkUtils->GetFileFromLink(storyRef, &storyFile);
			K2Vector<IDFile>::iterator file = std::find(checkedOutLinks.begin(), checkedOutLinks.end(), storyFile);
			if (file != checkedOutLinks.end())
			{
				// this story's file is in the checkedOutLinks list
				newCheckedOutStories.Append(storyRef);
				checkedOutLinks.erase(file);
			}
		}
		if (newCheckedOutStories.Length() > 0)
			Utils<Facade::ILiveEditFacade>()->CheckOut( newCheckedOutStories, ICommand::kRegularUndo, nil, kFalse, uiFlags );

		//----- Restore selection if we can match it up from the old document information
		RestoreSelectionForUpdateDesign(newDocRef, activeStoryIndex, activeStoryLabel, restoreRange);
	}
}

bool16 InCopyDocUtils::SaveChecksOnClose(const UIDRef& doc, UIFlags uiFlags, bool16 allowCancel)
{

	bool askAgain;

	do
	{
		askAgain = false;

		// we are about to close the last window of the document, ask the user
		IDocFileHandler::CloseOptions closeStatus = CheckOnClose(doc, uiFlags, allowCancel);

		// If the user asked to cancel and we are willing to accept that answer,
		// return with our global error code set to indicate cancellation.
		// Otherwise, keep asking until we get an answer that we can accept.
		if (closeStatus == IDocFileHandler::kCancel)
		{
			if(!allowCancel)
			{
				while(closeStatus == IDocFileHandler::kCancel)
					closeStatus = CheckOnClose(doc, uiFlags, allowCancel);
			}
			else
			{
				ErrorUtils::PMSetGlobalErrorCode(kCancel);
				return kFalse;
			}
		}

		// If we get here, we are either saving or not.
		if (closeStatus == IDocFileHandler::kSave || closeStatus == IDocFileHandler::kSaveVersion)
		{
			DoSaveAll(doc, uiFlags);

			if(ErrorUtils::PMGetGlobalErrorCode() != kSuccess)
			{
				// report the error and make them choose again
				PMString alertStr = ErrorUtils::PMGetGlobalErrorString();
				if (!alertStr.IsEmpty())
				{
					CAlert::WarningAlert(alertStr, doc, ErrorUtils::PMGetGlobalErrorCode());
				}
				// hkhalfal: (NACSR) No abortable command sequence is used
				// save error
				ErrorUtils::PMSetGlobalErrorCode(kSuccess);	// need to clear the error once its been reported
				// DO NOT return HERE!!  It's not legal to return with a success code and not schedule the close doc cmd
				askAgain = true;
			}
			else if (closeStatus == IDocFileHandler::kSaveVersion)
			{
				// saved to disk, now save workgroup version
				Utils<IInCopyWorkFlowUtils> icWFUtils;
				UIDList storyUIDList(icWFUtils ? icWFUtils->GetStandaloneStory(doc) : UIDRef::gNull);
				if (storyUIDList.Length() > 0)
				{
					if ( Utils<Facade::ILiveEditFacade>()->CheckIn( storyUIDList, Facade::ILiveEditFacade::CheckInOptions( Facade::ILiveEditFacade::enUnlockAsset | Facade::ILiveEditFacade::enSaveVersion ), nil, nil, ICommand::kAutoUndo, uiFlags ) == kCancel )
						return kFalse;										
				}
			}
		}
	}
	while (askAgain);

	return kTrue;
}

//-----
// DoClose()

void InCopyDocUtils::DoClose(const UIDRef& doc, UIFlags uiFlags, bool16 allowCancel, IDocFileHandler::CloseCmdMode cmdMode)
{
	// Prevent Close if doc is in use by BG Tasks
	if(HandleDocActionConflict(doc, kCloseActionID, uiFlags, true) != kSuccess)
	{
		// Cancel the action
		return;
	}
	// Conflict was resolved ... Continuing with the Close

	if (cmdMode == IDocFileHandler::kProcess)
	{
		{
			// Note that this InterfacePtr MUST be in this nested scope, because you MUST
			// release the reference to the document windowlist before processing the close command
			InterfacePtr<IPresentationList> docPList (doc, UseDefaultIID());
			if (docPList)
				ASSERT_MSG (docPList->size () == 0, "InCopyDocFileHandler::Close() illegal with open document windows and cmdMode == kProcess");
		}

		Utils<IDocumentCommands>()->Close(doc, uiFlags);
		return;
	}

	// Do NOT move this interface ptr above process block
	InterfacePtr<IPresentationList> presList (doc, UseDefaultIID());
	if (presList && !presList->empty())
	{
		for (int32 i = presList->size() - 1; i >= 0; --i)
		{
			if(i == 0 && uiFlags != kSuppressUI)
			{
				if (!SaveChecksOnClose(doc, uiFlags, allowCancel))
					return;
			}

			InterfacePtr<ICommand> closeCmd(presList->At(i)->CreateCloseCommand(allowCancel));
			CmdUtils::ProcessCommand(closeCmd);
		}
	}
	else
	{
		if (uiFlags != kSuppressUI)
		{
			if (!SaveChecksOnClose(doc, uiFlags, allowCancel))
				return;
		}
			
		InterfacePtr<ICommand> closeDoc(Utils<IDocumentCommands>()->CreateCloseCommand(doc, uiFlags));		
		CmdUtils::ScheduleCommand(closeDoc);
	}
}


//-----
// ShouldDoSaveAs()

bool16 InCopyDocUtils::ShouldDoSaveAs(IDocument* doc)
{
	//----- Regular Indesign docs use these conditions:
	//if(!doc->IsSaved() || doc->IsReadOnly())
	// We will use the following conditions for stand alone and multistory cases:
	// if( !story has link || link is read only ) 
	// we don't want to do a save as when recovered because saving to a new location
	// breaks the link.

	// Additionally, if this asset is a temporary version we want to force saveas
	InterfacePtr<IInCopyWorkgroupHelper> icwgHelper(GetExecutionContextSession(), UseDefaultIID());
	if (icwgHelper && icwgHelper->IsTemporaryVersion(::GetUIDRef(doc)))
		return kTrue;

	//----- Find all stories with a data link to an incopy file
	IDataBase* db = ::GetDataBase(doc);
	UIDList storyList(db);
	UIDList linkList(db);
	GetLinkedStories(doc, &storyList, &linkList, db);
	
	if (storyList.IsEmpty())
		return kTrue;
		
	//----- Check to see if any links are read only
	Utils<IStoryUtils> storyUtils;
	int32 count = storyList.Length();
	while (count-- > 0)
	{
		UIDRef itemRef = storyList.GetRef(count);
		if (storyUtils->IsAStory(itemRef ))
		{
			if (!storyUtils->IsLinkResourceAccessible(itemRef))
				return kTrue;
		}	
	}
	
	return kFalse;

}

//-------------------------------------------------------------------------------------------------------------
#pragma mark-

//-----
// CanDoSave()

bool16 InCopyDocUtils::CanDoSave(const UIDRef& doc)
{
	// Here's the deal - if there isn't a text selection, we don't know what story to save (Unless we're in Standalone)
	InterfacePtr<IStandAloneDoc> standAlone (doc, UseDefaultIID());

	if (standAlone && !standAlone->IsStandAloneDoc())
	{	
		UIDRef story;
		TextIndex start, end;
		Utils<IGalleyUtils>()->GetCurrentTextSelection(start, end, &story);

		if (story == UIDRef::gNull)
			return kFalse;
	}
	
	InterfacePtr<IInCopyStoryList> stories(doc, IID_IINCOPYSTORYLIST);
	if (stories) {
		if (stories->GetStoryCount() < 1)
			return kFalse;
	}
	
	IDataBase *db = doc.GetDataBase();
	return db->IsModified();
}

//-----
// CanDoSaveAll()

bool16 InCopyDocUtils::CanDoSaveAll(const UIDRef& doc)
{
	//----- We don't care if the Document model doc has been saved, we only care about if there
	//      have been changes since the last save. If there are no InCopy stories we don't allow a save.
	
	// For Save All, we Disable if we're in Standalone
	InterfacePtr<IStandAloneDoc> standAlone (doc, UseDefaultIID());
	if (standAlone && standAlone->IsStandAloneDoc())
		return kFalse;

	
	InterfacePtr<IInCopyStoryList> stories(doc, IID_IINCOPYSTORYLIST);
	if (stories)
	{
		if (stories->GetStoryCount() < 1)
			return kFalse;
	}
	
	IDataBase *db = doc.GetDataBase();
	return db->IsModified();
}

//-----
// CanDoRevert()

bool16 InCopyDocUtils::CanDoRevert(const UIDRef& doc)
{
	//----- We need to know if anything has been modified, and if it has if it has one of our links
	
	IDataBase *db = doc.GetDataBase();
	if (db->IsModified())
	{
		UIDList storyList(db);
		UIDList linkList(db);
		InterfacePtr<IDocument> pDoc(doc, IID_IDOCUMENT);
		GetLinkedStories(pDoc, &storyList, &linkList, db);
		
		if (!storyList.IsEmpty() && !linkList.IsEmpty())
			return kTrue;		
	}
	return kFalse;
}

//-----
// CanDoUpdateDesign()

bool16 InCopyDocUtils::CanDoUpdateDesign(const UIDRef& doc)
{
	bool16 can = kFalse;
	//----- The doc has to be InDesign or DUD
	InterfacePtr<IStandAloneDoc> standAlone(doc, IID_ISTANDALONEDOC);
	if (standAlone && !standAlone->IsStandAloneDoc())
	{
		// Check if the date of the disk file differs from the file opened
		IDataBase *docDB = doc.GetDataBase();
		const IDFile *savedFile = docDB->GetSysFile();
		if (savedFile == nil)
			return kFalse;
		if (!FileUtils::DoesFileExist(*savedFile))
			return kFalse;
		uint32 modDate;
		if (FileUtils::GetModificationDate(*savedFile, &modDate))
		{
			InterfacePtr<IIntData> openedDate(doc, IID_IOPENEDFILEDATE);
			if (openedDate && (openedDate->GetInt() != 0) && (openedDate->GetInt() != modDate))
				can = kTrue;
		}

		if (!can)
		{
			InterfacePtr<IInCopyWorkgroupHelper> icwgHelper(GetExecutionContextSession(), UseDefaultIID());
			if (icwgHelper)
				can = icwgHelper->HasNewerVersion(doc);
		}
	}
	
	return can;
}

bool16 InCopyDocUtils::IsReadOnly (IDocument* iDoc)
{
	InterfacePtr<IStandAloneDoc> standAlone(iDoc, IID_ISTANDALONEDOC);
	if (standAlone->IsStandAloneDoc())
	{

		//----- we should only have one story, but if we have more and any of them are locked
		//      report that the doc is read only

		IDataBase* db = ::GetDataBase(iDoc);
				UIDList stories(db), links(db);
		
		Utils<IInCopyDocUtils>()->GetLinkedStories(iDoc, &stories, &links, db);
		Utils<IStoryUtils> storyUtils;
		int32 count = stories.Length();
		while (count-- > 0)
		{
			UIDRef itemRef = stories.GetRef(count);
			if (storyUtils->IsAStory(itemRef ))
			{
				if (!storyUtils->IsLinkResourceAccessible(itemRef))
					return kTrue;
			}	
		}
	}
	return kFalse;
}


//-------------------------------------------------------------------------------------------------------------
#pragma mark-


//-----
// ExportAllLinkedStories()
// Modifies the database when marking the stories (and the links) as up to date
// Call from the context of a database transaction

void InCopyDocUtils::ExportAllLinkedStories(IDocument* doc, const FileTypeInfoID& /*fileTypeID*/, UIFlags uiFlags)
{
	//----- Get all stories with data links
	IDataBase* db = ::GetDataBase(doc);
	UIDList storyList(db);
	UIDList linkList(db);
	GetLinkedStories(doc, &storyList, &linkList, db);
	
	bool16 wasModified = db->IsModified();
	if (!storyList.IsEmpty())
	{
		K2Vector<KeyValuePair<UID, ErrorCode> > exportStoryList;
		int32 count = storyList.Length();
		ASSERT( count == linkList.Length() );
		for (int32 i=0; i<count; i++)
			exportStoryList.push_back(KeyValuePair<UID, ErrorCode>(storyList[i], kFailure));

		Utils<IInCopySharedUtils>()->UpdateInCopyStoriesMTSync(db, exportStoryList);

		UIDList failedLinks(db);
		for (int32 i=0; i<exportStoryList.size(); i++)
		{
			ErrorCode err = exportStoryList[i].Value();
			int32 index = storyList.Location(exportStoryList[i].Key());
			if (err == kSuccess)
			{
				InterfacePtr<ILink>	link(linkList.GetRef(index), UseDefaultIID());

				// update the link state
				InterfacePtr<ILinkManager> iLinkManager( db, db->GetRootUID(), UseDefaultIID() );
				if ( iLinkManager )
				{
					iLinkManager->UpdateResourceState( link->GetResource(), ILinkManager::kSynchronous );
					link->SetResourceModificationState(ILink::kResourceUnmodified);
				}

				//----- Mark the story as up to date
				InterfacePtr<ITextModel> textModel(storyList.GetRef(index), IID_ITEXTMODEL);
				if (textModel)
					textModel->SetChanged(kFalse);
			}
			else if (err!=kSuccess && err!=kLockedInCopyStoryError)
			{
				failedLinks.Append(linkList.GetRef(index).GetUID());
			}
		}

		//---- Alert the user if we had links we could not save to
		if (!failedLinks.IsEmpty())
		{
			if (kFullUI == uiFlags)
				AlertUserUnableToSave(failedLinks);
			ErrorUtils::PMSetGlobalErrorCode(kFailure);
		}
		
		//----- make sure we didn't make the database modified by exporting
		db->SetModified(wasModified);
	}
}


//------
// ExportStoryAndCreateLink()
// Modifies the database when marking the story (and the link) as up to date
// Call from the context of a database transaction
// ONLY CALLED BY InCopySaveAsDocCmd :: Do()

void InCopyDocUtils::ExportStoryAndCreateLink(const UIDRef& storyToExport, const IDFile& file, const FileTypeInfoID& fileTypeID)
{
	//----- Export the story
	if (storyToExport != kInvalidUIDRef) 
	{
		if( FileUtils::DoesFileExist( file ) )
		{
			bool8 canOpen = FileUtils::CanOpen(file, FileUtils::kReadWrite);

			if( !canOpen )
			{
				PMString	errString;
				errString = "CannotSwitchDBMode";
				ErrorUtils::PMSetGlobalErrorCode(kFailure, &errString);
				return;			
		  	}
		}
		
		AOSType type, creator;
		file.GetAttribute(AFile::kType, type);
		file.GetAttribute(AFile::kCreator, creator);
	  	InterfacePtr<IPMStream> stream(StreamUtil::CreateFileStreamWrite(file, kOpenOut | kOpenTrunc, type, creator));			
		if (!stream)
		{	
			PMString	errString("Cannot save X for reason Y");			
			errString.Translate();
			PMString fileName(FileUtils::SysFileToPMString(file));
			fileName.SetTranslatable(kFalse);
			PMString nothing(" ");
			nothing.SetTranslatable(kFalse);
			::ReplaceStringParameters(&errString, nothing, fileName);
			
			ErrorUtils::PMSetGlobalErrorCode(kFailure, &errString);
			return;
		}

		ASSERT_MSG(Utils<IStoryUtils>()->IsAStoryInterchangeFileTypeID(fileTypeID), FORMAT_ARGS("InCopyDocUtils::ExportStoryAndCreateLink - Bogus file type of %X!", fileTypeID.Get()));

		UIDList uidList(storyToExport);
		ASSERT(fileTypeID == kInCopyXMLMarkupFileTypeInfoID || fileTypeID == kInCopyTemplateFileTypeInfoID);
		ErrorCode err = Utils<ISnippetExport>()->ExportInCopyInterchange(stream, uidList);
		stream->Close(); //??

		//------ Create the link
		UID linkUID;
		Utils<IStoryUtils>()->CreateLink(storyToExport, file, kInCopyImportProviderBoss, fileTypeID, linkUID);

		//----- Mark the link as up to date

		//InterfacePtr<ILink> link(storyToExport.GetDataBase(), linkUID, UseDefaultIID());
		//if (link)
		//	link->SetResourceModificationState(ILink::kResourceUnmodified);

		InterfacePtr<ITextModel> model(storyToExport, IID_ITEXTMODEL);
		if (model)
		{
			model->SetChanged(kFalse);
			InterfacePtr<ILinkedStoryModificationState> linkedStoryState(model,UseDefaultIID());
			linkedStoryState->SetCurrentStateAsUnmodified();				
		}	
		
	}
}

//------
// ExportLinkedSotry()
// Note: This export does not change the database, and consequently does not mark
//       the story (and therefore the link) as up to date. You can do this with
//       outside the context of this method with kLinkChangedCmdBoss

ErrorCode InCopyDocUtils::ExportLinkedStory(const UIDRef& storyToExport, const FileTypeInfoID& fileTypeID)
{
	ErrorCode err = kFailure;

	//----- Get all stories with data links
	IDataBase* db = storyToExport.GetDataBase();
	
	if (storyToExport != kInvalidUIDRef)
	{
		InterfacePtr<ILinkManager> linkManager(db, db->GetRootUID(), UseDefaultIID());
		ASSERT(linkManager != nil);

		InterfacePtr<ILink> link(linkManager->QueryLinkByUID(Utils<ILinkUtils>()->FindLink(storyToExport)));	
		if (link)
		{
			//----- only export if we can access the file
			if (Utils<IStoryUtils>()->IsLinkResourceAccessible(storyToExport))
			{
				if (Utils<IStoryUtils>()->IsAStoryInterchangeFileTypeID(fileTypeID))
				{
					InterfacePtr<IPMStream> stream(Utils<ILinkUtils>()->CreateWriteStreamFromLink(storyToExport));
					if (stream)	
					{
						/* ExportAllLinkedStories uses the doc file type in some situations, we really want the value on each story */
						if (Utils<IStoryUtils>()->IsAStoryInterchangeFileTypeID(fileTypeID))		// Why is this check duplicated?
						{		
							UIDList uidList(storyToExport);
							ASSERT(fileTypeID == kInCopyXMLMarkupFileTypeInfoID || fileTypeID == kInCopyTemplateFileTypeInfoID);
							err = Utils<ISnippetExport>()->ExportInCopyInterchange(stream, uidList);

							linkManager->UpdateResourceState( link->GetResource(), ILinkManager::kSynchronous );
							// update the link state
							link->SetResourceModificationState(ILink::kResourceUnmodified);
						}
					}
					else
					{
						IDFile linkSysFile;
						Utils<ILinkUtils>()->GetFileFromLink(link, &linkSysFile);
						DBErrorUtils::SetDBError(kSaveDocFailedError, &linkSysFile);
					}
				}
				else
					ASSERT_FAIL("Bogus file type");
			}
		}
	}
	return err;
}

//-----
// ImportAllLinkedStories()

void InCopyDocUtils::ImportAllLinkedStories(IDocument* doc, const FileTypeInfoID& fileTypeID, IInCopyImportOptions* options)
{
	IDataBase* db = ::GetDataBase(doc);
	IDataBase::SaveRestoreModifiedState smersh(db);
	UIDList storyList(db); //the list of stories we have tried to import
	IDFile fileToOpen; //the file linked to the import story
	UIDRef storyToImport; //the uid of the story
	InterfacePtr<IInCopyStoryList> icsList(db, db->GetRootUID(), IID_IINCOPYSTORYLIST);

	//----- Collect a list of all incopy stories that are already opened
	SysFileList openStories;
	GetOpenInCopyFiles(&openStories, ::GetUIDRef(doc));

	ErrorCode err;	

	// Smart quotes. Disable the global smart quotes setting
	// This is kind of funky, but smart quotes is controlled by a single user preference, 
	// which can be overridden here. So we temporarily disable the smart quotes
	//	then after the imports, switch it back to the old value. - cdr 4/3/2002
	const bool16 oldState = DisableConvertQuotes(db);
	ErrorCode globalErr = ErrorUtils::PMGetGlobalErrorCode();

	// In order to make best use of the INX multiple session import make 2 passes
	// with the first pass importing ICML and the second pass importing the other
	// formats (INCX and INCD).
	int32 numPasses = 2;
	bool16 skipEndnoteStory = kTrue;

	for (int32 i=0; i < numPasses && globalErr != kCancel; ++i)
	{
		PMString formatTypeForPass(i == 0 ? InCopy::kInCopyMarkupFormatName : "" /* don't care*/);

		// Get a story for importing- we get the stories one at a time
		// because depending on which order they are imported,and whether or not they are inline,
		// the stories and links may change; previously we collected all stories
		// and links first.
		bool16 fileMissing = GetStoryForImport(doc, storyToImport, &fileToOpen, db, &storyList, formatTypeForPass, skipEndnoteStory);

		Utils<ILinkUtils> linkUtils;
		InterfacePtr<ILinkManager> linkManager(doc, UseDefaultIID());

		InterfacePtr<IINXManager> iINXManager( GetExecutionContextSession()->QueryINXManager() ) ;
		iINXManager->BeginImportSession();
		while(storyToImport != UIDRef::gNull && globalErr != kCancel)
		{
			err = kFailure;
			const IDFile constFileToOpen(fileToOpen); //const the sysFile of the target story

			if (!fileMissing)
			{
				err = kSuccess;

				InterfacePtr<ILink> link(linkManager ? linkManager->QueryLinkByUID(linkUtils->FindLink(storyToImport)) : nil);
				if (link)
				{
					// If the link is embedded, its state is known.
					InterfacePtr<ILinkResource> linkResource(db, link->GetResource(), UseDefaultIID());
					if (linkResource && linkResource->GetStoreState() != ILinkResource::kEmbedded)
					{
						// Bypass the import linked story if user is not checking links on open. Do this
						// here rather than FileActionsOpenDocResponder so that the stories will be added
						// to the IInCopyStoryList.
						InterfacePtr<ILinkPrefs> iLinkPrefs(QuerySessionWorkspace<ILinkPrefs>());
						bool16 checkLinksOnOpen = !iLinkPrefs || iLinkPrefs->GetCheckLinksOnOpen();
						if ((checkLinksOnOpen && link->GetResourceModificationState() == ILink::kResourceModified) || Utils<IAssignmentUtils>()->IsAssignmentFileTypeID(fileTypeID)) 
							err = ImportLinkedStory(storyToImport, fileTypeID, options);
					}
				}
			}
			else
			{
				InterfacePtr<IInCopyWorkgroupHelper> icwgHelper(GetExecutionContextSession(), UseDefaultIID());
				if (icwgHelper->ShouldSyncPrePlace(storyToImport)) 
				{
					//----- link is managed, so go ahead and add it to the incopy story list.
					//          this way the story can be checked out or updated from galley/story
					if( icwgHelper->WorkgroupSyncPrePlace( storyToImport ) )
					{
						fileMissing = GetStoryForImport(doc, storyToImport, &fileToOpen, db, &storyList, formatTypeForPass, skipEndnoteStory);
						if (!fileMissing) continue;
						err = kSuccess;
					}
				}
			}

			if (err == kSuccess)
			{		
				//----- Add to the story list if not already there, and not already opened
				if (!FileInList(openStories, constFileToOpen))
				{
					if (icsList) 
					{
						icsList->AddStory(storyToImport.GetUID());
					}
				}
			}

			// save first error and blindly reset subsequent errors
			if (globalErr == kSuccess || err == kCancel)
			{
				// only save the first error or a cancel
				globalErr = err;
				err = ErrorUtils::PMGetGlobalErrorCode();
			}
			// hkhalfal: (NACSR) No abortable command sequence is used
			// changes will not be reverted in case of error
			ErrorUtils::PMSetGlobalErrorCode(kSuccess);

			//append the story to the list of stories we have attempted to import
			storyList.Append(storyToImport);
			//get the next story to try
			fileMissing = GetStoryForImport(doc, storyToImport, &fileToOpen, db, &storyList, formatTypeForPass, skipEndnoteStory);
			if (storyToImport == UIDRef::gNull)
			{
				//Now import all endnote stories
				skipEndnoteStory = kFalse;

				//get the next story to try
				fileMissing = GetStoryForImport(doc, storyToImport, &fileToOpen, db, &storyList, formatTypeForPass, skipEndnoteStory);
			}
		}
		iINXManager->EndImportSession();
	}

	ASSERT(ErrorUtils::PMGetGlobalErrorCode() == kSuccess);
	// Ok, we might have some stuff in the list that we don't want
	// If the story is an Inline and is in another managed story, we don't want to list it
	Utils<IGalleyUtils> galleyUtils;
	UIDList acceptableStories(db);
	galleyUtils->GetListOfUserStories(doc, acceptableStories);

	// Now we filter the InCopyStoryList
	if (icsList)
	{
		for (int32 i = (icsList->GetStoryCount() - 1); i >= 0; --i)
		{
			UID storyToCheck = icsList->GetNthStoryUID(i);
			if (acceptableStories.Location(storyToCheck) == -1)
				icsList->RemoveStory(storyToCheck);
		}
	}	
	RestoreConvertQuotes(db, oldState);
	ErrorUtils::PMSetGlobalErrorCode(globalErr);
}

//-----
// ImportStoryAndCreateLink()

ErrorCode InCopyDocUtils::ImportStoryAndCreateLink(const UIDRef& story, IPMStream* stream, IInCopyImportOptions* options, const FileTypeInfoID& fileTypeID, bool16 createLink, UIDRef *importedItem)
{
	ErrorCode err = kFailure;
	bool16 bIsGraphicStory(kFalse);
	if (importedItem)
		*importedItem = UIDRef::gNull;

	// if we have a file type of .incx we want to parse to see if we are opening a graphic or a story.
	if (Utils<IStoryUtils>()->IsCurrentStoryDocumentFileType(fileTypeID))
	{
		InterfacePtr<IINXImportValidation> validation((IINXImportValidation*)::CreateObject(kSnippetImportValidationBoss, IID_IINXIMPORTVALIDATION));
		ASSERT_MSG((validation != nil), "InCopyDocUtils::ImportStoryAndCreateLink() - Could not create import validation!");

		InterfacePtr<IINXManager> iINXManager( GetExecutionContextSession()->QueryINXManager() ) ;
		ErrorCode result = iINXManager->ValidateINX(stream, validation);
		InterfacePtr<IStringData> snippetType(validation, IID_ISTRINGDATA);
		PMString snippetTypeString = snippetType->GetString();

		if (snippetTypeString == PMString(kPageItemSnippetType))
			bIsGraphicStory = kTrue;
	}

	//----- Import the story
	if (bIsGraphicStory)
	{
		// incopy graphic story

		IDataBase	*storyDB = story.GetDataBase();
		if (!storyDB)
			return err;

		// get list of existing page items
		UIDList	pageItemListBefore(storyDB);
		InterfacePtr<ISpreadList> spreadList(storyDB, storyDB->GetRootUID(), IID_ISPREADLIST);
		InterfacePtr<IMasterSpreadList> masterSpreadList(storyDB, storyDB->GetRootUID(), UseDefaultIID());
		for (int32 i = 0; i < 2; ++i)
		{
			bool16 bMaster = (i == 1);
			int32 numSpreads = bMaster ? masterSpreadList->GetMasterSpreadCount() : spreadList->GetSpreadCount();
			for (int32 k = 0; k < numSpreads; ++k)
			{
				InterfacePtr<IHierarchy> parentHier(storyDB, bMaster ? masterSpreadList->GetNthMasterSpreadUID(k) : spreadList->GetNthSpreadUID(k), UseDefaultIID());
				int32 numLayers = parentHier->GetChildCount();
				for (int32 j = 0; j < numLayers; ++j)
				{
					InterfacePtr<IHierarchy> layerHierarchy(parentHier->QueryChild(j));

					int32 numItems = layerHierarchy->GetChildCount();
					for (int32 n = 0; n < numItems; ++n)
						pageItemListBefore.Append(layerHierarchy->GetChildUID(n));
				}
			}
		}

		// do the import
		InterfacePtr<IDOMElement> documentElement(storyDB, storyDB->GetRootUID(), UseDefaultIID());
		err = Utils<ISnippetImport>()->ImportFromStream(stream, documentElement);

		if (err != kSuccess)
        {
			PMString errorMessage = ErrorUtils::PMGetErrorString(err);
            ErrorUtils::PMSetGlobalErrorCode (kSuccess);
            ErrorUtils::PMSetGlobalErrorCode (err, &errorMessage);
            return ErrorUtils::PMGetGlobalErrorCode();   
        }

		else 
		{
			// get list of page items after the import
			UIDList	pageItemListAfter(storyDB);
			for (int32 i = 0; i < 2; ++i)
			{
				bool16 bMaster = (i == 1);
				int32 numSpreads = bMaster ? masterSpreadList->GetMasterSpreadCount() : spreadList->GetSpreadCount();
				for (int32 k = 0; k < numSpreads; ++k)
				{
					InterfacePtr<IHierarchy> parentHier(storyDB, bMaster ? masterSpreadList->GetNthMasterSpreadUID(k) : spreadList->GetNthSpreadUID(k), UseDefaultIID());
					int32 numLayers = parentHier->GetChildCount();
					for (int32 j = 0; j < numLayers; ++j)
					{
						InterfacePtr<IHierarchy> layerHierarchy(parentHier->QueryChild(j));

						int32 numItems = layerHierarchy->GetChildCount();
						for (int32 n = 0; n < numItems; ++n)
							pageItemListAfter.Append(layerHierarchy->GetChildUID(n));
					}
				}
			}
			// determine which item was added by the import by comparing lists
			for (int32 i=pageItemListAfter.Length()-1; i>=0; i--)
			{
				if (pageItemListBefore.Location(pageItemListAfter[i])>=0)
					pageItemListAfter.Remove(i);
			}

			// we should have just one, assert if more
			ASSERT(pageItemListAfter.Length() == 1);

			// tell caller (if requested) the imported ref
			if (importedItem)
				*importedItem = pageItemListAfter.GetRef(0);

			if (story.GetUID() != kInvalidUID)
			{
				PMString storyLabel("");

				// Acquire the old story label in order to copy it to the new page item.
				InterfacePtr<IStoryLabel> iStoryLabel(*importedItem, IID_ISTORYLABEL);
				if (iStoryLabel)
					storyLabel = iStoryLabel->GetLabel();

				// if a valid story was passed in then the caller must intend us to replace that
				// story - do this now:

				// Replace the old page item with the new one if imported snippet has content.
				// Otherwise, this was an empty frame, delete the snippet, which is just an empty graphic frame anyway.
				InterfacePtr<IGraphicFrameData> importedFrameData(*importedItem, UseDefaultIID());
				if (importedFrameData && importedFrameData->HasContent())
				{
					InterfacePtr<IPlaceBehavior> placeBehavior(story, UseDefaultIID());
					if (placeBehavior)
					{
						IPlaceBehavior::eAfterPlace afterPlace;
						// Temporarily unlock the story so the placebehavior can actually reposition it if needed
						InterfacePtr<ILockPosition> lock(story, IID_ILOCKPOSITION);
						int32 previousLock = ILockPosition::kUnlock;
						if (lock)
						{
							previousLock = lock->GetLockPosition();
							if (previousLock == ILockPosition::kLock)
								lock->Set(ILockPosition::kUnlock);
						}
						if (placeBehavior->ProcessReplace(*importedItem, ::GetUIDRef(placeBehavior), kFalse,&afterPlace) != kInvalidUID)
							importedItem->ResetUID(story.GetUID());
						if (previousLock == ILockPosition::kLock && lock)
							lock->Set(previousLock);
					}
				}
				else
				{
					InterfacePtr<IScrapItem> importedItemScrap(*importedItem, IID_ISCRAPITEM);
					if (importedItemScrap)
					{
						InterfacePtr<ICommand>  deleteGFCmd ( importedItemScrap->GetDeleteCmd());
						if ((err = CmdUtils::ProcessCommand(deleteGFCmd)) == kSuccess)
							importedItem->ResetUID(story.GetUID());
					}
				}

				//----- Story Label
				if (err == kSuccess)
				{
					InterfacePtr<ICommand> labelCmd(CmdUtils::CreateCommand(kSetStoryLabelCmdBoss));
					InterfacePtr<IStringData> labelData(labelCmd, IID_ISTRINGDATA);
					InterfacePtr<IBoolData>	  boolData(labelCmd, IID_IBOOLDATA);
					boolData->Set(kFalse);
					labelData->Set(storyLabel);
					labelCmd->SetItemList(story);
					err = CmdUtils::ProcessCommand(labelCmd);
				}
			}

			// save information on original file type
			InterfacePtr<IInCopyFileInfo> icFileInfo(*importedItem, UseDefaultIID());
			if (icFileInfo)
				icFileInfo->FileType(IInCopyFileInfo::kTypeInCopyInterchangeGraphicStory);

			//----- Add the link
			if (createLink)
			{
				InterfacePtr<IFileStreamData> fileData(stream, IID_IFILESTREAMDATA);
				FileTypeInfoID localFileTypeID = kInvalidFileTypeInfoID;
				if (fileTypeID == FileTypeRegistry::GetCurrentFileType(kInCopyXMLInterchangeFileTypeInfoID) )
					localFileTypeID = kInCopyXMLInterchangeFileTypeInfoID;
				else if (fileTypeID == FileTypeRegistry::GetCurrentFileType(kInCopyXMLMarkupFileTypeInfoID) )
					localFileTypeID = kInCopyXMLMarkupFileTypeInfoID;
				else
					ASSERT_FAIL("Bogus file type");

				UID linkUID;
				err = Utils<IStoryUtils>()->CreateLink(*importedItem, fileData->GetSysFile(), kInCopyImportProviderBoss, localFileTypeID, linkUID);
			} 

			//----- Add to the story list if not already there
			if (err == kSuccess)
			{
				IDataBase* db = importedItem->GetDataBase();
				InterfacePtr<IInCopyStoryList> icsList(db, db->GetRootUID(), IID_IINCOPYSTORYLIST);
				if (icsList)
				{
					icsList->AddStory(importedItem->GetUID());
				}
			}
		}
	}
    else if (story != kInvalidUIDRef)
	{
		// Smart quotes. Disable the global smart quotes setting
		// This is kind of funky, but smart quotes is controlled by a single user preference, 
		// which can be overridden here. So we temporarily disable the smart quotes
		//	then after the import, switch it back to the old value. - cdr 4/3/2002
		bool16 oldState = DisableConvertQuotes(story.GetDataBase());

		// save information on original file type
		InterfacePtr<IInCopyFileInfo> icFileInfo(story, UseDefaultIID());

		if (fileTypeID == FileTypeRegistry::GetCurrentFileType(kInCopyFileTypeInfoID))
		{			
			if (icFileInfo)
				icFileInfo->FileType(IInCopyFileInfo::kTypeInCopyStory);
			err = Utils<IInCopyWorkflow>()->ImportStory(story, stream, options);
		}
		else if (Utils<IStoryUtils>()->IsCurrentStoryDocumentFileType(fileTypeID)
			     || fileTypeID == FileTypeRegistry::GetCurrentFileType(kInCopyTemplateFileTypeInfoID))
		{
			TextIndex start = 0;
			int32 startIndex = 0;

			InterfacePtr<ITextModel> textModel(story, UseDefaultIID());
			if (!textModel)
				return err;
			
			// save information on original file type
			if (icFileInfo)
				icFileInfo->FileType(IInCopyFileInfo::kTypeInCopyInterchangeTextStory);
			
			// for now use the document as the root element?
			IDataBase* db = story.GetDataBase();
			InterfacePtr<IDOMElement> documentElement(db, db->GetRootUID(), UseDefaultIID());

			err = Utils<ISnippetImport>()->ImportFromStream(stream, documentElement);

			if (err != kSuccess)
			{
				PMString errorMessage = ErrorUtils::PMGetErrorString(err);
				ErrorUtils::PMSetGlobalErrorCode (kSuccess);
				ErrorUtils::PMSetGlobalErrorCode (err, &errorMessage);
				return ErrorUtils::PMGetGlobalErrorCode();   
			}

			if (err == kSuccess) {
				Utils<Facade::IEndnoteFacade>()->MoveEndnoteRange(story);
				if (Utils<Facade::IEndnoteFacade>()->IsSeparatorChar(story, 0))
					textModel->Delete(0, 1);
			}

			// add kICBridgeTextLockAdornmentBoss 
			if (Utils<IStoryUtils>()->IsCurrentStoryDocumentFileType(fileTypeID))
			{
				InterfacePtr<ICommand> lockCmd(CmdUtils::CreateCommand(kSetItemLockDataCmdBoss));
				if (lockCmd)
				{
					InterfacePtr<IBoolData> lockData(lockCmd, IID_IBOOLDATA);
					lockData->Set(kFalse);
					lockCmd->SetItemList(story);
					err = CmdUtils::ProcessCommand(lockCmd);
					ASSERT_MSG(err == kSuccess, "SetStoryLockStateCmd failed");
				}
			}
		}
		else
			ASSERT_FAIL("Bogus file type");

		
		//----- clear the global error state for this command and then reset it
		ErrorCode currentErr = ErrorUtils::PMGetGlobalErrorCode();
		if (currentErr != kSuccess)
			// hkhalfal: (NACSR) No abortable command sequence is used
			// changes will not be reverted in case of error
			ErrorUtils::PMSetGlobalErrorCode(kSuccess);

		RestoreConvertQuotes(story.GetDataBase(), oldState);

		if (currentErr != kSuccess)
			ErrorUtils::PMSetGlobalErrorCode(currentErr);

		if (err == kSuccess)
		{
			//----- Add the link
			if (createLink)
			{
				InterfacePtr<IFileStreamData> fileData(stream, IID_IFILESTREAMDATA);
				FileTypeInfoID localFileTypeID = kInvalidFileTypeInfoID;
				if (fileTypeID == FileTypeRegistry::GetCurrentFileType(kInCopyFileTypeInfoID))
					localFileTypeID = kInCopyFileTypeInfoID;
				else if (fileTypeID == FileTypeRegistry::GetCurrentFileType(kInCopyXMLInterchangeFileTypeInfoID) )
					localFileTypeID = kInCopyXMLInterchangeFileTypeInfoID;
				else if (fileTypeID == FileTypeRegistry::GetCurrentFileType(kInCopyXMLMarkupFileTypeInfoID) )
					localFileTypeID = kInCopyXMLMarkupFileTypeInfoID;
				else
					ASSERT_FAIL("Bogus file type");

				UID linkUID;
				err = Utils<IStoryUtils>()->CreateLink(story, fileData->GetSysFile(), kInCopyImportProviderBoss, localFileTypeID, linkUID);
			} 
		
			//----- Add to the story list if not already there
			if (err == kSuccess)
			{
				IDataBase* db = story.GetDataBase();
				InterfacePtr<IInCopyStoryList> icsList(db, db->GetRootUID(), IID_IINCOPYSTORYLIST);
				if (icsList)
				{
					icsList->AddStory(story.GetUID());
				}
			}
		}
	}

	return err;		
}


//-----
// ImportLinkedStory()
// TODO remove fileTypeID from this API
ErrorCode InCopyDocUtils::ImportLinkedStory(const UIDRef& storyToImport, const FileTypeInfoID& fileTypeID, IInCopyImportOptions* options)
{
	ErrorCode err = kFailure;
	IDataBase* db = storyToImport.GetDataBase();

	if (storyToImport != kInvalidUIDRef)
	{
		InterfacePtr<ILinkManager> linkManager(db, db->GetRootUID(), UseDefaultIID());
		InterfacePtr<ILink> originalLink(linkManager ? linkManager->QueryLinkByUID(Utils<ILinkUtils>()->FindLink(storyToImport)) : nil);
  		if (originalLink)
		{
			InterfacePtr<IPMStream> stream(Utils<ILinkUtils>()->CreateReadStreamFromLink(storyToImport));			
				
			bool16 preLock = kFalse;
			InterfacePtr<IItemLockData> itemLockData(storyToImport, IID_IITEMLOCKDATA);
			if (itemLockData)
				preLock = itemLockData->GetInsertLock();

			if (preLock)
			{
				// If the story is locked, we need to unlock it before the import. Otherwise the old story
				// cannot be deleted during import.		-- Vantive #503396
				InterfacePtr<ICommand> setStoryLockStateCmd(CmdUtils::CreateCommand(kSetItemLockDataCmdBoss));
				InterfacePtr<IBoolData> lockData(setStoryLockStateCmd, IID_IBOOLDATA);
      
				// set the command data
				lockData->Set(kFalse);	// unlock
				setStoryLockStateCmd->SetItemList(UIDList(storyToImport));
				err = CmdUtils::ProcessCommand(setStoryLockStateCmd);

				if (err != kSuccess)
				{
					ASSERT_FAIL("SetStoryLockStateCmd failed");
					return err;
				}
			}

			if (!options)
			{
				/* Set the import to not import the style table and not import the swatch list as we don't want
				to add styles/swatches to the existing doc. */
				options =  (IInCopyImportOptions*)::CreateObject(kInCopyImportOptionsBoss, IID_IINCOPYIMPORTOPTIONS);
				options->Set(kFalse, kFalse);
			}
			else
				options->AddRef();	// for release later

			// Smart quotes. Disable the global smart quotes setting
			// This is kind of funky, but smart quotes is controlled by a single user preference, 
			// which can be overridden here. So we temporarily disable the smart quotes
			//	then after the imports, switch it back to the old value. - cdr 4/3/2002
			bool16 oldState = DisableConvertQuotes(db);
			//----- Import from file
			InterfacePtr<ILinkResource> linkResource(db, originalLink->GetResource(), UseDefaultIID());
			
			// still only want InCopy formatted links

			if (linkResource && linkResource->GetFormatType() == InCopy::kInCopyStoryFormatName)
			{				
				// save information on original file type
				InterfacePtr<IInCopyFileInfo> icFileInfo(storyToImport, UseDefaultIID());
				if (icFileInfo)
					icFileInfo->FileType(IInCopyFileInfo::kTypeInCopyStory);

				err = Utils<IInCopyWorkflow>()->ImportStory(storyToImport, stream, options);
				ASSERT_MSG(err == kSuccess, "kInCopyStoryFormat Failed to import");
			}
			else if (linkResource && 
				(linkResource->GetFormatType() == InCopy::kInCopyInterchangeFormatName || 
				 linkResource->GetFormatType() == InCopy::kInCopyMarkupFormatName))
			{
				InterfacePtr<ITextModel> textModel(storyToImport, UseDefaultIID());
				if (textModel)
				{
					// save information on original file type
					InterfacePtr<IInCopyFileInfo> icFileInfo(storyToImport, UseDefaultIID());
					if (icFileInfo)
						icFileInfo->FileType(IInCopyFileInfo::kTypeInCopyInterchangeTextStory);
					
					// shut off change tracking before we do anything to the story otherwise garbage gets left at end of story
					InterfacePtr<ICommand> tcCmd(CmdUtils::CreateCommand(kSetRedlineTrackingCmdBoss));
					InterfacePtr<IBoolData> tcData(tcCmd, IID_IBOOLDATA);
					tcData->Set(kFalse);
					tcCmd->SetItemList(UIDList(textModel));
					err = CmdUtils::ProcessCommand(tcCmd);

					if (err == kSuccess)
					{
						// if the existing story is XML tagged, then we'll need to untag it first; 
						//	otherwise, if the incoming Snippet is also tagged, we won't be able 
						//	to re-tag things. Watson 1166186
						InterfacePtr<IXMLReferenceData> storyXMLRefData(textModel, UseDefaultIID());
						if (storyXMLRefData && storyXMLRefData->GetReference() != kInvalidXMLReference)
						{
							err = Utils<IXMLElementCommands>()->DeleteElement(storyXMLRefData->GetReference(), kTrue);
						}
					}

					if (err == kSuccess)
					{
						TextIndex threadStart;
						int32 threadSpan = 0;
						textModel->GetStoryThreadSpan(0, &threadStart, &threadSpan);

						bool16 needCleanup = kFalse;
						//Fixes bug # 1030733
						//Blow away the text model content (if it isn't empty)
						if (threadSpan > 1)
						{
							// Delete the hyperlink text destinations in the old text range  
							// so that we will avoid unnecessary unique key conflicts while 
							// still keep the private destinations around.
							Utils<IHyperlinkUtils>()->DeleteHyperlinkSrcsAndDestsInStory(textModel, threadStart, threadStart + threadSpan);
							Utils<Facade::IEndnoteFacade> endnoteFacade;
							if (endnoteFacade->IsEndnoteStory(::GetUIDRef(textModel)))
								endnoteFacade->DeleteEndnoteRangesInStory(textModel, threadStart, threadStart + threadSpan);

							needCleanup = kTrue;
							
							textModel->GetStoryThreadSpan(0, &threadStart, &threadSpan);
							textModel->Delete(threadStart, threadSpan-1);
						}

						// accept a potentially left-over tracked deletion
						InterfacePtr<ICommand> acceptAllCmd(CmdUtils::CreateCommand(kAcceptAllRedlineCmdBoss));
						if (acceptAllCmd)
						{
							acceptAllCmd->SetItemList(UIDList(textModel));	
							err = CmdUtils::ProcessCommand(acceptAllCmd);
						}

						// Clear potentially left-over applied conditions so they don't get applied to imported story content.
						// This case can happen when condition(s) are applied on first character and revert content.
						K2Vector<UID> noConditions;
						Utils<Facade::IConditionalTextFacade>()->ApplyConditionsToText(storyToImport, 0, 1, noConditions, kTrue/*remove others*/);

						UID oldLinkUID = ::GetUID(originalLink); // remember the old link uid before import

						// find a text frame which contains this incopy text story
						InterfacePtr<IFrameList> frameList(textModel->QueryFrameList());
						ASSERT(frameList->GetFrameCount() > 0);
						InterfacePtr<ITextFrameColumn> startTFC (frameList->QueryNthFrame(0));
						ASSERT(startTFC);
						if ( startTFC )
						{
							//The IID_ISCRIPT interface for a "text frame" object in the Scripting DOM is actually on the graphic frame container
							InterfacePtr<IDOMElement> gFrameElement((IDOMElement*)Utils<ITextScriptUtils>()->QueryGraphicFrame( startTFC, IID_IDOMELEMENT ));
							err = Utils<ISnippetImport>()->ImportFromStream(stream, gFrameElement);
						}

						if (needCleanup)
							Utils<IHyperlinkUtils>()->CleanupHiddenDestinations(db);
						
						if (err == kSuccess) {
							Utils<Facade::IEndnoteFacade>()->MoveEndnoteRange(storyToImport);
							if (Utils<Facade::IEndnoteFacade>()->IsSeparatorChar(storyToImport, 0))
								textModel->Delete(0, 1);
						}

						if (err == kSuccess) {
							InterfacePtr<IBoolData> toCreateEndnoteAnchor(storyToImport, IID_ICREATEENDNOTEANCHOR);
							if (toCreateEndnoteAnchor->GetBool() == kFalse)
								toCreateEndnoteAnchor->Set(kTrue);
						}
						if (err == kSuccess)
						{

							//----- The imported story may have conditional text and the visibility needs to synchronize
							// with the condition visibility states in the InDesign pub or assignment.
							InterfacePtr<IStandAloneDoc> saDoc(db, db->GetRootUID(), UseDefaultIID());
							if (!saDoc || !saDoc->IsStandAloneDoc())
								Utils<IConditionalTextUtils>()->SynchronizeConditionalTextVisibility(storyToImport);
						}
					}
					ASSERT_MSG(err == kSuccess || err == kCancel, "kInCopyInterchangeFormat Failed to import");
				}
				else
				{
					// incopy graphic story

					// gather the interfaces
					InterfacePtr<IHierarchy> itemHier(storyToImport, UseDefaultIID());
					ASSERT(itemHier != nil);
					InterfacePtr<IHierarchy> parentHier(itemHier->QueryRoot());
					ASSERT(parentHier != nil);
					InterfacePtr<ISpread> currentISpread(parentHier, UseDefaultIID());
					ASSERT(currentISpread != nil);

					// get list of existing page items
					UIDList	pageItemListBefore(db);
					int32 numLayers1 = parentHier->GetChildCount();
					for (int32 j = 0; j < numLayers1; ++j)
					{
						InterfacePtr<IHierarchy> layerHierarchy(parentHier->QueryChild(j));

						int32 numItems = layerHierarchy->GetChildCount();
						for (int32 n = 0; n < numItems; ++n)
							pageItemListBefore.Append(layerHierarchy->GetChildUID(n));
					}

					// do the import
					InterfacePtr<IDOMElement> parentElement(parentHier, UseDefaultIID());
					err = Utils<ISnippetImport>()->ImportFromStream(stream, parentElement);
					ASSERT_MSG(err == kSuccess || err == kCancel, "kInCopyInterchangeFormat Failed to import");

					if (err == kSuccess)
					{
						// snippet import creates a new page item, we need to replace the old one now

						// get list of page items after the import
						UIDList	pageItemListAfter(db);
						int32 numLayers = parentHier->GetChildCount();
						for (int32 j = 0; j < numLayers; ++j)
						{
							InterfacePtr<IHierarchy> layerHierarchy(parentHier->QueryChild(j));

							int32 numItems = layerHierarchy->GetChildCount();
							for (int32 n = 0; n < numItems; ++n)
								pageItemListAfter.Append(layerHierarchy->GetChildUID(n));
						}
						// determine which item was added by the import by comparing lists
						for (int32 i=pageItemListAfter.Length()-1; i>=0; i--)
						{
							if (pageItemListBefore.Location(pageItemListAfter[i])>=0)
								pageItemListAfter.Remove(i);
						}

						// we should have one or less (import reused storyToImport), assert if more
						ASSERT(pageItemListAfter.Length() <= 1);

						if (pageItemListAfter.Length() == 1)
						{
							PMString storyLabel("");

							// Acquire the old story label in order to copy it to the new page item.
							InterfacePtr<IStoryLabel> iStoryLabel(pageItemListAfter.GetRef(0), IID_ISTORYLABEL);
							if (iStoryLabel)
								storyLabel = iStoryLabel->GetLabel();

							// Replace the old page item with the new one if imported snippet has content.
							// Otherwise, this was an empty frame, delete the snippet, which is just an empty graphic frame anyway.
							InterfacePtr<IGraphicFrameData> importedFrameData(pageItemListAfter.GetRef(0), UseDefaultIID());
							if (importedFrameData && importedFrameData->HasContent())
							{
								// save information on new page item
								InterfacePtr<IInCopyFileInfo> icFileInfo(pageItemListAfter.GetRef(0), UseDefaultIID());
								if (icFileInfo)
									icFileInfo->FileType(IInCopyFileInfo::kTypeInCopyInterchangeGraphicStory);

								InterfacePtr<IPlaceBehavior> placeBehavior(storyToImport, UseDefaultIID());
								if (placeBehavior)
								{
									IPlaceBehavior::eAfterPlace afterPlace;
									placeBehavior->ProcessReplace(pageItemListAfter.GetRef(0), ::GetUIDRef(placeBehavior), kFalse,&afterPlace);
								}
							}
							else
							{
								// imported snippet has no content, discard the placed pageitem
								InterfacePtr<IScrapItem> importedItemScrap(pageItemListAfter.GetRef(0), IID_ISCRAPITEM);
								if (importedItemScrap)
								{
									InterfacePtr<ICommand> deleteGFCmd(importedItemScrap->GetDeleteCmd());
									err = CmdUtils::ProcessCommand(deleteGFCmd);
								}

								// and clear the contents of the old frame
								InterfacePtr<IGraphicFrameData> oldFrameData(storyToImport, UseDefaultIID());
								if (err == kSuccess && oldFrameData && oldFrameData->HasContent())
								{
									InterfacePtr<IHierarchy> oldItemHier(storyToImport, UseDefaultIID());
									if (oldItemHier && oldItemHier->GetChildCount() == 1)
									{
										InterfacePtr<IScrapItem> oldContentItemScrap(storyToImport.GetDataBase(), oldItemHier->GetChildUID(0), IID_ISCRAPITEM);
										if (oldContentItemScrap)
										{
											InterfacePtr<ICommand> deleteContentCmd(oldContentItemScrap->GetDeleteCmd());
											err = CmdUtils::ProcessCommand(deleteContentCmd);
										}
									}
								}
							}

							//----- Story Label
							if (err == kSuccess)
							{
								InterfacePtr<ICommand> labelCmd(CmdUtils::CreateCommand(kSetStoryLabelCmdBoss));
								InterfacePtr<IStringData> labelData(labelCmd, IID_ISTRINGDATA);
								InterfacePtr<IBoolData>	  boolData(labelCmd, IID_IBOOLDATA);
								boolData->Set(kFalse);
								labelData->Set(storyLabel);
								labelCmd->SetItemList(storyToImport);
								err = CmdUtils::ProcessCommand(labelCmd);
							}
						}

						// save information on original file type
						InterfacePtr<IInCopyFileInfo> icFileInfo(storyToImport, UseDefaultIID());
						if (icFileInfo)
							icFileInfo->FileType(IInCopyFileInfo::kTypeInCopyInterchangeGraphicStory);
					}
				}
			}
			else
				ASSERT_FAIL("Bogus link format");
			
			if (err == kSuccess)
			{		
				// Make sure it is up to date
				if( Utils<IStoryUtils>()->IsLinkResourceOutOfDate(storyToImport) )
				{
					// Re-aquire the ILink as it may have been modified during the import.
					InterfacePtr<ILink> link(linkManager ? linkManager->QueryLinkByUID(Utils<ILinkUtils>()->FindLink(storyToImport)) : nil);
					if (link)
						link->SetResourceModificationState(ILink::kResourceUnmodified);
					InterfacePtr<IStoryNeedsRelinkData> relink(storyToImport, UseDefaultIID());
					if (relink)
						relink->Set(kFalse);
					// Since we're opening the latest version of the story from disk, make sure
					// that the proxy version number is also updated. This assures that the
					// link status will be normal in InCopy.
					UIDRef assetRef = Utils<Facade::IWorkgroupStoryFacade>()->GetAssetUIDRef(storyToImport);
					if ( Utils<Facade::IWorkgroupFacade>()->HasVersionedContent( assetRef ) )
						Utils<Facade::IWorkgroupFacade>()->UpdateProxyVersionNumber( assetRef );
				}
				//----- Add to the story list if not already there
				InterfacePtr<IInCopyStoryList> icsList(db, db->GetRootUID(), IID_IINCOPYSTORYLIST);
				if (icsList)
				{
						icsList->AddStory(storyToImport.GetUID());
				}
			}

			//----- clear the global error state for this command and then reset it
			ErrorCode currentErr = ErrorUtils::PMGetGlobalErrorCode();
			if (currentErr != kSuccess)
				// hkhalfal: (NACSR) No abortable command sequence is used
				// changes will not be reverted in case of error
				ErrorUtils::PMSetGlobalErrorCode(kSuccess);

			RestoreConvertQuotes(db, oldState);

			if (preLock)
			{
				// We have unlocked the story. Now restore the original lock.
				InterfacePtr<ICommand> setStoryLockStateCmd(CmdUtils::CreateCommand(kSetItemLockDataCmdBoss));
				InterfacePtr<IBoolData> lockData(setStoryLockStateCmd, IID_IBOOLDATA);
       
				// set the command data
				lockData->Set(kTrue);	// lock
				setStoryLockStateCmd->SetItemList(UIDList(storyToImport));
				err = CmdUtils::ProcessCommand(setStoryLockStateCmd);

				if (err != kSuccess)
				{
					ASSERT_FAIL("SetStoryLockStateCmd failed");
					return err;
				}
			}

			if (currentErr != kSuccess)
			{
				ErrorUtils::PMSetGlobalErrorCode(currentErr);
				err = currentErr;
			}

			if (options)
				options->Release();

		}
	}

	return err;
}

//-----
// GetFirstUserStory()

UIDRef InCopyDocUtils::GetFirstUserStory(IDocument* doc)
{
	// try and get the first exported incopy story first
	InterfacePtr<IInCopyStoryList> icStoryList(doc, UseDefaultIID());
	if (icStoryList && icStoryList->GetStoryCount())
	{
		return icStoryList->GetNthStoryRef(0);
	}

	// as there was no exported incopy story, try and get the first user accessible story
	InterfacePtr<IStoryList> storyList(doc, IID_ISTORYLIST);
	if ( storyList && storyList->GetUserAccessibleStoryCount() )
	{
		return storyList->GetNthUserAccessibleStoryUID (0);
	}
		
	// there were no stories
	return kInvalidUIDRef;
}

//-----
// GetStoryForImport
bool16 InCopyDocUtils::GetStoryForImport(IDocument* doc, UIDRef& storyToImport, IDFile* fileToOpen, IDataBase* db, UIDList *importedStories, const PMString& formatType, bool16 skipEndnoteStory)
{
	Utils<Facade::IEndnoteFacade> iEndnoteFacade;

 	//----- Get the next eligible story for import
 	bool16 isMissing = kTrue;
	bool16 isInCopyStory = kFalse;
	storyToImport = UIDRef::gNull; //default return value
	if (!db)
	{
  		db = ::GetDataBase(doc);
	}
  	
	InterfacePtr<IStoryList> storyList(doc, IID_ISTORYLIST);
	if(!storyList)
	{
		return isMissing;
	}

  	int32 numStories = storyList->GetUserAccessibleStoryCount();

	Utils<IStoryUtils> storyUtils;

  	UIDRef storyRef;	
	// process the stories in story list (creation) order so that they appear that way in galley
	for (int32 count(0); count < numStories; count++)
	{
		storyToImport = UIDRef::gNull;
  		storyRef = storyList->GetNthUserAccessibleStoryUID(count);

		if(importedStories->Location(storyRef.GetUID()) < 0 && (formatType.IsEmpty() || storyUtils->GetStoryFormatType(storyRef) == formatType))
		{
			if (skipEndnoteStory && iEndnoteFacade->IsEndnoteStory(storyRef))
				continue;

			ValidInCopyStory(storyRef, storyToImport, fileToOpen, &isMissing, &isInCopyStory);
			if (isInCopyStory)
				return isMissing;
		}
  	}

	if (skipEndnoteStory && importedStories->size() < numStories)
	{
		//We would be coming back with skipEndnoteStory off,
		//So, bail now
		return isMissing;
	}

	// look for graphic stories now
	InterfacePtr<ISpreadList> spreadList(doc, UseDefaultIID());
	InterfacePtr<IMasterSpreadList> masterSpreadList(doc, UseDefaultIID());

	for (int32 i = 0; i < 2; ++i)
	{
		bool16 bMaster = (i == 1);

		int32 numSpreads = bMaster ? masterSpreadList->GetMasterSpreadCount() : spreadList->GetSpreadCount();
		for (int32 k = 0; k < numSpreads; ++k)
		{
			InterfacePtr<IHierarchy> spreadHierarchy(db, bMaster ? masterSpreadList->GetNthMasterSpreadUID(k) : spreadList->GetNthSpreadUID(k), UseDefaultIID());

			int32 numLayers = spreadHierarchy->GetChildCount();
			for (int32 j = 0; j < numLayers; ++j)
			{
				InterfacePtr<IHierarchy> layerHierarchy(spreadHierarchy->QueryChild(j));

				int32 numItems = layerHierarchy->GetChildCount();
				for (int32 n = 0; n < numItems; ++n)
				{
					UID childUID = layerHierarchy->GetChildUID(n);
					InterfacePtr<IGraphicFrameData> graphicFrameData1(db, childUID, UseDefaultIID());
					if (graphicFrameData1 && graphicFrameData1->IsGraphicFrame() && graphicFrameData1->GetTextContentUID() == kInvalidUID && !graphicFrameData1->HasContent())
					{
						storyToImport = UIDRef::gNull;
						storyRef = UIDRef(db, childUID);

						if(importedStories->Location(storyRef.GetUID()) < 0 && (formatType.IsEmpty() || storyUtils->GetStoryFormatType(storyRef) == formatType))
						{
							ValidInCopyStory(storyRef, storyToImport, fileToOpen, &isMissing, &isInCopyStory);
							if (isInCopyStory)
								return isMissing;
						}
					}
					else if (Utils<IPageItemTypeUtils>()->IsGroup(UIDRef(db, childUID)) || (graphicFrameData1 && graphicFrameData1->IsGraphicFrame() && graphicFrameData1->HasContent()))
					{
						InterfacePtr<IHierarchy> hierarchy(db, childUID, UseDefaultIID());

						UIDList tempList(db);
						hierarchy->GetDescendents(&tempList, IID_IGRAPHICFRAMEDATA);

						// add-in the graphic stories of a group
						int32 numGroupItems = tempList.Length();
						for (int32 p = 0; p < numGroupItems; ++p)
						{
							UIDRef itemRef = tempList.GetRef(p);
							InterfacePtr<IGraphicFrameData> graphicFrameData(itemRef, UseDefaultIID());
							if (graphicFrameData && graphicFrameData->IsGraphicFrame() && graphicFrameData->GetTextContentUID() == kInvalidUID && !graphicFrameData->HasContent())
							{
								storyToImport = UIDRef::gNull;
								storyRef = itemRef;

								if(importedStories->Location(storyRef.GetUID()) < 0 && (formatType.IsEmpty() || storyUtils->GetStoryFormatType(storyRef) == formatType))
								{
									ValidInCopyStory(storyRef, storyToImport, fileToOpen, &isMissing, &isInCopyStory);
									if (isInCopyStory)
										return isMissing;
								}
							}
						}
					}
				}
			}
		}
	}

	return isMissing;
}

//-----
// GetLinkedStories()
	
void InCopyDocUtils::GetLinkedStories(IDocument* doc, UIDList* storyList, SysFileList* filesToOpen, IDataBase* db)
{
	UIDList linkList(db);
	GetLinkedStories(doc, storyList, &linkList, db);

	Utils<ILinkUtils> linkUtils;

	for (int i = linkList.Length()-1; i >= 0 ; --i)
	{
		InterfacePtr<ILink> link(db, linkList[i], UseDefaultIID());
		if (!link)
			continue;

		IDFile sysFile;
		if (!linkUtils->GetFileFromLink(link, &sysFile))
			continue;

		//add the sysFile to our list
		filesToOpen->AddFile(reinterpret_cast<const IDFile *>(&sysFile));
	}
}

//-----
// GetLinkedStories()

void InCopyDocUtils::GetLinkedStories(IDocument* doc, UIDList* stories, UIDList* links, IDataBase* db)
{
	if (!doc || !stories || !links)
	{
		ASSERT_FAIL("InCopyDocUtils::GetLinkedStories() - no document or no story list or no link list passed in!");
		return;
	}

  	//----- Loop over all the stories looking for user Accessible stories with data links
  	if (!db) 
  		db = ::GetDataBase(doc);
  	
	Utils<ILinkUtils> linkUtils;
	InterfacePtr<ILinkManager> linkManager(db, db->GetRootUID(), UseDefaultIID());
	ASSERT(linkManager != nil);

  	InterfacePtr<IStoryList> storyList(doc, IID_ISTORYLIST);
  	int32 count = 0;
  	UIDRef storyRef;	
  	
  	while(count < storyList->GetUserAccessibleStoryCount())
	{
  		storyRef = storyList->GetNthUserAccessibleStoryUID(count);

		InterfacePtr<ILink> link(linkManager->QueryLinkByUID(linkUtils->FindLink(storyRef)));
		if (link)
		{
			UID linkUID = ::GetUID(link);
  			//----- We only want InCopy data links
  			if (db->IsValidUID(linkUID))
			{
  				InterfacePtr<ILinkState> state(storyRef, UseDefaultIID());
  				ClassID linkClass = state->GetProviderClass();
  				if (linkClass == kInCopyImportProviderBoss || linkClass == 0)
				{
  					stories->Append(storyRef);
  					links->Append(linkUID);
  				}
  			}
  		}
  		++count;
  	}

	// now the graphic  stories
	InterfacePtr<ISpreadList> spreadList(doc, UseDefaultIID());
	InterfacePtr<IMasterSpreadList> masterSpreadList(doc, UseDefaultIID());

	for (int32 i = 0; i < 2; ++i)
	{
		bool16 bMaster = (i == 1);

		int32 numSpreads = bMaster ? masterSpreadList->GetMasterSpreadCount() : spreadList->GetSpreadCount();
		for (int32 k = 0; k < numSpreads; ++k)
		{
			InterfacePtr<IHierarchy> spreadHierarchy(db, bMaster ? masterSpreadList->GetNthMasterSpreadUID(k) : spreadList->GetNthSpreadUID(k), IID_IHIERARCHY);

			int32 numLayers = spreadHierarchy->GetChildCount();
			for (int32 j = 0; j < numLayers; ++j)
			{
				InterfacePtr<IHierarchy> layerHierarchy(spreadHierarchy->QueryChild(j));

				int32 numItems = layerHierarchy->GetChildCount();
				for (int32 n = 0; n < numItems; ++n)
				{
					UID childUID = layerHierarchy->GetChildUID(n);
					InterfacePtr<IGraphicFrameData> graphicFrameData1(db, childUID, UseDefaultIID());
					if ( graphicFrameData1 && graphicFrameData1->IsGraphicFrame() && graphicFrameData1->GetTextContentUID() == kInvalidUID )
					{
						storyRef = UIDRef(db, childUID);

						InterfacePtr<ILink> link(linkManager->QueryLinkByUID(linkUtils->FindLink(storyRef)));
						if (link)
						{
							UID linkUID = ::GetUID(link);
							//----- We only want InCopy data links
							if (db->IsValidUID(linkUID))
							{
								InterfacePtr<ILinkState> state(storyRef, IID_ILINKSTATE);
								ClassID linkClass = state->GetProviderClass();
								if (linkClass == kInCopyImportProviderBoss || linkClass == 0)
								{
									stories->Append(storyRef);
									links->Append(linkUID);
								}
							}
						}
					}
					else if (Utils<IPageItemTypeUtils>()->IsGroup(UIDRef(db, childUID)))
					{
						InterfacePtr<IHierarchy> groupHier(db, childUID, UseDefaultIID());

						UIDList tempList(db);
						groupHier->GetDescendents( &tempList, IID_IGRAPHICFRAMEDATA );

						// add-in the graphic stories of a group
						int32 numGroupItems = tempList.Length();
						for (int32 p = 0; p < numGroupItems; ++p)
						{
							UIDRef itemRef = tempList.GetRef(p);
							InterfacePtr<IGraphicFrameData> graphicFrameData(itemRef, UseDefaultIID());
							if ( graphicFrameData && graphicFrameData->IsGraphicFrame() && graphicFrameData->GetTextContentUID() == kInvalidUID )
							{
								storyRef = itemRef;

								InterfacePtr<ILink> link(linkManager->QueryLinkByUID(linkUtils->FindLink(storyRef)));
								if (link)
								{
									UID linkUID = ::GetUID(link);
									//----- We only want InCopy data links
									if (db->IsValidUID(linkUID))
									{
										InterfacePtr<ILinkState> state(storyRef, IID_ILINKSTATE);
										ClassID linkClass = state->GetProviderClass();
										if (linkClass == kInCopyImportProviderBoss || linkClass == 0)
										{
											stories->Append(storyRef);
											links->Append(linkUID);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	} 		
 }

//-------------------------------------------------------------------------------------------------------------
#pragma mark-


//-----
// CreateDefaultTextFrame()

#include "IBaselineFrameGridData.h"
UIDRef InCopyDocUtils::CreateDefaultTextFrame(IDocument* doc)
{
	IDataBase* db = ::GetDataBase(doc);
	UIDRef newItem;

	//----- Find the first spread
	InterfacePtr<ISpreadList> spreadList(doc, IID_ISPREADLIST);
	if (spreadList && spreadList->GetSpreadCount())
	{		
		int32 spreadIndex = spreadList->GetSpreadCount()-1;
		InterfacePtr<ISpread> spread(db, spreadList->GetNthSpreadUID(0), IID_ISPREAD);
		
		if (spread)
		{
			PMRect pageRect = GetDefaultPageRect(doc, spread);

			UID layerUID = GetDefaultLayerUID(db, spread);
			
			//----- Create the text frame
			bool16 isHorizontal = kTrue;
			bool16 isFrameGrid = kFalse;
			bool16 isLeftToRight = !(LocaleSetting::GetLocale().IsLanguageFS(kRightToLeftLanguageFS));

			ErrorCode err = Utils<Facade::ITextFrameFacade>()->CreateTextFrame(UIDRef(db, layerUID), newItem, pageRect, kTrue/*noGraphicAttr*/, isHorizontal, isFrameGrid, isLeftToRight);
			if (err != kFailure)
			{
				InterfacePtr<IGraphicFrameData> frame(newItem, IID_IGRAPHICFRAMEDATA);
				InterfacePtr<IMultiColumnTextFrame> mcf(db, frame->GetTextContentUID(), UseDefaultIID());
	
				InterfacePtr<IBoolData> nonprivateTF(mcf, IID_IINCOPYNONPRIVATETEXTFRAME);
				nonprivateTF->Set(kFalse);
	
				//----- Lock the frame
				LockPageItem(newItem);
			}
						
		}		
	}
	
	return newItem;
}

//-----
// CreateDefaultGraphicFrame()

#include "IBaselineFrameGridData.h"
#include "IPathUtils.h"
UIDRef InCopyDocUtils::CreateDefaultGraphicFrame(IDocument* doc)
{
	IDataBase* db = ::GetDataBase(doc);

	//----- Find the first spread
	InterfacePtr<ISpreadList> spreadList(doc, IID_ISPREADLIST);
	if (spreadList && spreadList->GetSpreadCount())
	{		
		int32 spreadIndex = spreadList->GetSpreadCount()-1;
		InterfacePtr<ISpread> spread(db, spreadList->GetNthSpreadUID(0), IID_ISPREAD);
		
		if (spread)
		{
			PMRect pageRect = GetDefaultPageRect(doc, spread);

			UID layerUID = GetDefaultLayerUID(db, spread);
		
			UIDRef newItem = Utils<IPathUtils>()->CreateRectangleSpline(UIDRef(db, layerUID), pageRect, INewPageItemCmdData::kGraphicFrameAttributes);
			if (newItem != UIDRef::gNull)
			{
				LockPageItem(newItem);
				return newItem;
			}
		}		
	}
	
	return kInvalidUIDRef;
}

//-----
// CheckOnClose()

IDocFileHandler::CloseOptions InCopyDocUtils::CheckOnClose(const UIDRef& doc, UIFlags uiFlags, bool8 allowCancel)
{

	IDocFileHandler::CloseOptions closeStatus = IDocFileHandler::kDontSave;
	IDataBase *db = doc.GetDataBase();
	InterfacePtr<IDocument> document(doc, UseDefaultIID());
	Utils<IBGTasksUIUtils> bgTasksUIUtils;
	if ( uiFlags != kSuppressUI && bgTasksUIUtils )
	{
		if ( document )
		{
			UIDRef item = ::GetUIDRef(document); 
			switch ( bgTasksUIUtils->ShowDocActionWarningAboutBGTasks(item, kCloseActionID, uiFlags) )
			{
				case IBGTasksUIUtils::kProcessCmd			:  break;
				case IBGTasksUIUtils::kAbortCmd			: return IDocFileHandler::kCancel;
			} // end switch
		}
	} // end if
	InterfacePtr<IStandAloneDoc> standAlone(doc, UseDefaultIID());
	bool isStandAlone = standAlone && standAlone->IsStandAloneDoc();
	UIDList checkedOutStoryList( ::GetDataBase(document) );
	
	// check for locked stories and offer to check them in
	Utils<Facade::IWorkgroupStoryFacade> wgStoryFacade;
	if (!isStandAlone && wgStoryFacade)
	{
		UIDList docStoryList = Utils<IStoryUtils>()->GetStories( document );
		
		for ( int i = 0; i < docStoryList.Length(); i++ )
		{
			UIDRef storyRef = docStoryList.GetRef(i);
			if ( wgStoryFacade->GetStoryLockState( storyRef, kFalse, uiFlags ) == IAMLockable::enCheckedOut )
				checkedOutStoryList.Append( storyRef.GetUID() );
		}

		if ( checkedOutStoryList.Length() > 0 )
		{		
			PMString cancelString = kCancelString;
			if (!allowCancel) 
				cancelString = kNullString;

			// complain
			PMString complaint("ICShared_CheckInOnClose");
			complaint.Translate();
			int16 result = CAlert::ModalAlert(complaint,
								kYesString,
								kNoString,
								cancelString,
								1, CAlert::eWarningIcon);
			if (result == 1)
 			{
				GlobalErrorStatePreserver gEsp;
				if ( Utils<Facade::ILiveEditFacade>()->CheckIn( checkedOutStoryList, Facade::ILiveEditFacade::CheckInOptions( Facade::ILiveEditFacade::enUnlockAsset | Facade::ILiveEditFacade::enSaveVersion | Facade::ILiveEditFacade::enExportStory ) ) == kSuccess )
					checkedOutStoryList.Clear();
 			}
		
			else if (result == 3)
			{
				// cancel
				return IDocFileHandler::kCancel;
			}
		}	
	}

	// ask if you want to save - presumably we need some better indicator than the db dirty flag
	if ( (db->IsModified()) && (isStandAlone || !Facade::IsLiveEditAvailable() || checkedOutStoryList.Length() > 0) )
	{
		InterfacePtr<IInCopyStoryList> storyList( doc, IID_IINCOPYSTORYLIST );
		
		if ( storyList && storyList->GetStoryCount() > 0 )
		{
			PMString docName;
			document->GetName(docName);			
			UIDRef assetRef = Utils<Facade::IWorkgroupStoryFacade>()->GetAssetUIDRef( storyList->GetNthStoryRef(0) );
			switch ( Utils<IWorkgroupUIFacade>()->DoSaveAlert( assetRef, docName, allowCancel ) )
			{
				case IAMUIService::enSave			: closeStatus = IDocFileHandler::kSave; break;
				case IAMUIService::enCancel			: closeStatus = IDocFileHandler::kCancel; break;
				case IAMUIService::enSaveVersion	: closeStatus = IDocFileHandler::kSaveVersion; break;
				case IAMUIService::enDontSave		: 				
				default								: closeStatus = IDocFileHandler::kDontSave; break;
			} // end switch
		}
	}

	return closeStatus;
}  
  

//-----
// IsFileAlreadyOpened()

bool16 InCopyDocUtils::IsFileAlreadyOpen(const IDFile& file, UIDRef* doc, UIDRef* foundStory)
{
	//----- Check to see if file is already open by looking across all open docs for a datalink to the same file
	InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IDocumentList> docList(theApp->QueryDocumentList());
	
	IDocument* currentDoc = nil;
	
	int32 count = docList->GetDocCount();
	
	while(count--)
	{
		currentDoc = docList->GetNthDoc(count);
		if (currentDoc)
		{
		
			//----- collect a list of incopy stories from the current doc
			IDataBase* db = ::GetDataBase(currentDoc);
			SysFileList incopyFiles;
			UIDList stories(db);
			
			GetLinkedStories(currentDoc, &stories, &incopyFiles, db);
			
			//----- see if our file is in the list
			int32 fileCount = 0;
			while (fileCount < incopyFiles.GetFileCount())
			{
				const IDFile* f = incopyFiles.GetNthFile(fileCount);
				if (FileUtils::IsEqual(*f, file))
				{
					*doc = ::GetUIDRef(currentDoc);
					if (foundStory)
						*foundStory = stories.GetRef(fileCount);
					return kTrue;
				}
				++fileCount;
			}
					
		}
		
	}
	
	currentDoc = docList->FindDoc(file); // InCopy could open text/rtf directly
	if (currentDoc)
		(*doc) = ::GetUIDRef(currentDoc);
	else
	//----- did not find the file
		*doc = UIDRef::gNull;
	
	return *doc !=  UIDRef::gNull;		 
}


//-----
// FileInList()

bool16 InCopyDocUtils::FileInList(const SysFileList& list, const IDFile& file)
{
	int32 count = list.GetFileCount();
	while (count--)
	{
		if (FileUtils::IsEqual(*(list.GetNthFile(count)), file))
			return kTrue;
	}
	
	return kFalse;
}
 
//-----
// GetOpenInCopyFiles()

void InCopyDocUtils::GetOpenInCopyFiles(SysFileList* fileList, const UIDRef& excludeThisDoc)
{
	//----- Collect a list of InCopy files that are already open in any document
	
	InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IDocumentList> docList(theApp->QueryDocumentList());
	
	IDocument* currentDoc = nil;	
	int32 count = docList->GetDocCount();
	
	while(count--)
	{
		
		currentDoc = docList->GetNthDoc(count);
		
		if (currentDoc && ::GetUIDRef(currentDoc) != excludeThisDoc)
		{
				IDataBase* db = ::GetDataBase(currentDoc);
				UIDList stories(db);
				GetLinkedStories(currentDoc, &stories , fileList, db);			
		}
		
	}
	 
}

 
//-----
// GetCopyDefaultName()

void InCopyDocUtils::GetCopyDefaultName(const UIDRef& doc, IDFile *name, bool16& useSystemDefaultDir)
{
  	useSystemDefaultDir = kFalse;
  
  	// Get the document's current file and append "copy". This will be the default 
  	// Save A Copy file name. If there is no current file name (because the document 
  	// hasn't been saved yet), start with the document name.
  	
  	//----- Find the link of the story we should be saving
  	InterfacePtr<IDocument> pDoc(doc, IID_IDOCUMENT);
  	UIDRef story = GetFirstUserStory(pDoc);
  	
  	if (story != kInvalidUIDRef)
	{
		InterfacePtr<ILinkManager> linkManager(doc, UseDefaultIID());
		InterfacePtr<ILink> link(linkManager ? linkManager->QueryLinkByUID(Utils<ILinkUtils>()->FindLink(story)) : nil);	
		if (link)
		{
			//----- We have a link, so use the name and path of the link				
			InterfacePtr<ICoreFilename> cfn((ICoreFilename *)::CreateObject(kCoreFilenameBoss, IID_ICOREFILENAME));
			IDFile linkFile;
			Utils<ILinkUtils>()->GetFileFromLink(link, &linkFile);

			if (cfn->Initialize(&linkFile))
				return;

			PMString baseName = *cfn->GetBaseName();

			// Remove the extension if there is one.
			PMString extension;
			cfn->GetExtension(&extension);
			CharCounter extLen = extension.CharCount();
			if (extLen != 0)
			{
				baseName.Remove(baseName.CharCount()-(extLen+1), extLen+1);
			}

			// Append " copy".
			PMString copyString(" copy");
			copyString.Translate();
			baseName.Append(copyString);

			// Put back the extension.
			if (extLen != 0)
			{
				baseName.Append('.');
				baseName.Append(extension);
			}

			if (cfn->SetBaseName(&baseName))
			{
				// The name was too long.
				// This time replace the last characters.
				baseName = *cfn->GetBaseName();
				if (extLen != 0)
				{
					baseName.Remove(baseName.CharCount()-(extLen+1), (extLen+1));
				}

				CharCounter copyStringLen = copyString.CharCount();
				baseName.Remove(baseName.CharCount()-copyStringLen, copyStringLen);

				baseName.Append(copyString);
				if (extLen != 0)
				{
					baseName.Append('.');
					baseName.Append(extension);
				}

				cfn->SetBaseName(&baseName);
			}

			cfn->GetSysFile(name);

			// The above mumbo jumbo doesn't actually change the name because the ICoreFilename interface
			// full path name remains the same after a SetBaseName call it is however useful for validating the file name length
			// but actually change the name here.
			AString newName;
			newName.Append(baseName.GrabUTF16Buffer(nil), kMaxUInt32);
			name->SetName(newName);		
		}
		else
		{
			//----- No link yet, so we can only return the name of the document
			PMString docName;
			pDoc->GetName(docName);
			FileUtils::PMStringToIDFile(docName, *name);
			useSystemDefaultDir = kTrue;
			return;
		}
  	}
  	
}

//-----
// GetOpenFileType

bool16 InCopyDocUtils::GetOpenFileType(const IDFile& sysFile, SysOSType &type)
{
	// Can we provide an answer from the file's type or extension?

	PMString pubExtension(FileTypeRegistry::GetCurrentFileExtension(kInCopyFileTypeInfoID));

	SysOSType fileType = 0;
#ifdef MACINTOSH
	SysOSType creator;
	FileUtils::GetFileCreatorType(sysFile, &fileType,&creator);
#endif
	PMString extension, baseName;
	FileUtils::GetFileName(sysFile, extension);
	FileUtils::GetBaseFileName(sysFile, baseName);
	extension.Remove(0, baseName.CharCount());

	SysOSType inCopyBinaryType = FileTypeRegistry::GetCurrentFileType(kInCopyFileTypeInfoID);
	SysOSType inCopyType = FileTypeRegistry::GetCurrentFileType(kInCopyXMLMarkupFileTypeInfoID);
	if ( (fileType == inCopyBinaryType) || (extension.IsEqual(pubExtension, kFalse /*casesensitive*/)) )
	{
		type = inCopyBinaryType;
		return kTrue;
	}
	else if ( (fileType == inCopyType) || (extension.IsEqual(pubExtension, kFalse /*casesensitive*/)) )
	{
		type = inCopyType;
		return kTrue;
	}
	else if ( FileTypeRegistry::GetFileTypeInfoIDForFile(sysFile) == kInCopyXMLInterchangeFileTypeInfoID )
	{
		type = FileTypeRegistry::GetCurrentFileType(kInCopyXMLInterchangeFileTypeInfoID);
		return kTrue;
	}
	else if ( FileTypeRegistry::GetFileTypeInfoIDForFile(sysFile) == kInCopyXMLMarkupFileTypeInfoID 
				||  FileTypeRegistry::GetFileTypeInfoIDForFile(sysFile) == kInCopyTemplateFileTypeInfoID )
	{
		type = FileTypeRegistry::GetCurrentFileType(kInCopyXMLMarkupFileTypeInfoID);
		return kTrue;
	}

	// support the Text and RTF open
	//SysOSType txtType = FileTypeRegistry::GetFileTypeInfoIDForFile(sysFile);
	if ( FileTypeRegistry::GetFileTypeInfoIDForFile(sysFile) == kTEXTFileTypeInfoID )
	{
		type = FileTypeRegistry::GetCurrentFileType(kTEXTFileTypeInfoID);
		return kTrue;
	}

	if ( FileTypeRegistry::GetFileTypeInfoIDForFile(sysFile) == kRTFFileTypeInfoID )
	{
		type = FileTypeRegistry::GetCurrentFileType(kRTFFileTypeInfoID);
		return kTrue;
	}

	if ( FileTypeRegistry::GetFileTypeInfoIDForFile(sysFile) == kMSWordFileTypeInfoID )
	{
		type = FileTypeRegistry::GetCurrentFileType(kMSWordFileTypeInfoID);
		return kTrue;
	}

	if ( Utils<IAssignmentUtils>()->IsInCopyAssignmentPackageFileTypeID(FileTypeRegistry::GetFileTypeInfoIDForFile(sysFile)) )
	{
		type = FileTypeRegistry::GetCurrentFileType(FileTypeRegistry::GetFileTypeInfoIDForFile(sysFile));
		return kTrue;
	}

	// if can not determined by extension or type, try read Magic number
	InterfacePtr<IPMStream> stream(StreamUtil::CreateFileStreamRead(sysFile));
	return GetStreamFileType(stream, type);
}

//-----
// GetStreamFileType()

bool16 InCopyDocUtils::GetStreamFileType(IPMStream *stream, SysOSType &type)
{
	// parse the file as XML using our doc detection content handler to see if this is ours
	InterfacePtr<IK2ServiceRegistry> serviceRegistry(GetExecutionContextSession(), UseDefaultIID());
	InterfacePtr<IK2ServiceProvider> xmlProvider(serviceRegistry->QueryServiceProviderByClassID(kXMLParserService, kXMLParserServiceBoss));
	InterfacePtr<ISAXServices> saxServices(xmlProvider, UseDefaultIID());

	// use our doc detection content handler
	InterfacePtr<ISAXContentHandler> contentHandler(static_cast<ISAXContentHandler*>(::CreateObject(kInCopyDocDetectContentHandlerBoss, ISAXContentHandler::kDefaultIID)));

	// use an empty entity resolver to silent entity resolving attempts
	InterfacePtr<ISAXEntityResolver> entityResolver(static_cast<ISAXEntityResolver*>(::CreateObject(kXMLEmptyEntityResolverBoss, ISAXEntityResolver::kDefaultIID)));
	// no whinning please
	if (Utils<IShowAlertRegistryUtils>())
	{
		Utils<IShowAlertRegistryUtils>()->DoSetShouldShowCmd(kXMLEntityNotResolved, kFalse);
		Utils<IShowAlertRegistryUtils>()->DoSetShouldShowCmd(kXMLPublicIDsNotSupported, kFalse);
	}

	// set parser options
	InterfacePtr<ISAXParserOptions> parserOptions(saxServices, UseDefaultIID());
	parserOptions->SetNamespacesFeature(kTrue);

	// let's do it. We don't care about any errors
	ASSERT_MSG(ErrorUtils::PMGetGlobalErrorCode() == kSuccess, "InCopyDocUtils::GetStreamFileType: already in error state");
	saxServices->ParseStream(stream, contentHandler, entityResolver);

	// get the results
	InterfacePtr<IBoolData> foundBool(contentHandler, IID_IDOCDETECTFILETYPEFOUND);
	if (foundBool->Get()) {
		// we did figure out the file type. If it's not InCopy, then it's XML
		InterfacePtr<IIntData> isInCopyFileFlag(contentHandler, IID_IDOCDETECTISINCOPYFILE);
		FileTypeInfoID fileType;
		switch (isInCopyFileFlag->Get())
		{
			case 0:
				fileType = kXMLFileTypeInfoID;
				break;
			case 1:
				fileType = kInCopyFileTypeInfoID;
				break;
			case 3:
				fileType = kInCopyXMLMarkupFileTypeInfoID;
				break;
			case 2:
				{
	//				if (Utils<IINXUtils>()->GetINXOptions().IsExpandedStructure())
	//					fileType = kInCopyXMLMarkupFileTypeInfoID;
	//				else 
						fileType = kInCopyXMLInterchangeFileTypeInfoID;
				}
				break;
			default:
				ASSERT_FAIL("Unknown flag value");
		}
		
		type = FileTypeRegistry::GetCurrentFileType(fileType);
	}
	// if we set an error, we need to clear it
	if (ErrorUtils::PMGetGlobalErrorCode() != kSuccess) {
		// hkhalfal: (NACSR) No abortable command sequence is used
		// changes will not be reverted in case of error
		ErrorUtils::PMSetGlobalErrorCode(kSuccess);
	}
	return foundBool->Get();
}



//----------------------------------------------------------------------------------
#pragma mark-

// -----
// CheckInStories()

ErrorCode InCopyDocUtils::CheckInStories( IDocument * document )
{
	ErrorCode errorCode(kFailure);
	if ( document )
	{
		errorCode = kSuccess;
		UIDList checkedOutStories( ::GetDataBase(document) );
		UIDList allStories( Utils<IStoryUtils>()->GetStories(document) );
		Utils<Facade::IWorkgroupStoryFacade> wgStoryFacade;
		Utils<Facade::IWorkgroupFacade> wgFacade;		
		for ( int32 i = 0; i < allStories.Length() && wgStoryFacade && wgFacade; i++ )
		{
			UIDRef storyRef( allStories.GetRef( i ) );
			if ( wgFacade->CanCheckIn( wgStoryFacade->GetAssetUIDRef( storyRef ), storyRef.GetUID() ) )
				checkedOutStories.Append( storyRef.GetUID() );
		}	
		if ( checkedOutStories.Length() > 0 )
			errorCode = Utils<Facade::ILiveEditFacade>()->CheckIn( checkedOutStories, Facade::ILiveEditFacade::CheckInOptions( Facade::ILiveEditFacade::enUnlockAsset | Facade::ILiveEditFacade::enSaveVersion | Facade::ILiveEditFacade::enExportStory ) );	
	}
	return errorCode;
}

//-----
// LockPageItem()

void InCopyDocUtils::LockPageItem(const UIDRef& pageItem)
{
	
	if (pageItem != kInvalidUIDRef)
	{
		UIDList resultList = UIDList(pageItem.GetDataBase());
		InterfacePtr<IHierarchy> hier(pageItem, IID_IHIERARCHY);
		hier->GetDescendents(&resultList, IID_ILOCKPOSITION);
		
		int32 count = resultList.Length();
		while (count-- > 0)
		{
			InterfacePtr<ILockPosition> lock(resultList.GetRef(count), IID_ILOCKPOSITION);
			if (lock)
				lock->Set(ILockPosition::kLock);
		}
	
	}
}

//-----
// DoRevertDialog()

void InCopyDocUtils::DoRevertDialog(const UIDRef& doc)
{ 

InterfacePtr<IDocument> document(doc, IID_IDOCUMENT);
// ask the user for permission to blow away his changes

	PMString alertString("Revert^1Alert");
	alertString.Translate();
	PMString pubName;
	document->GetName(pubName);
	
	::ReplaceStringParameters(&alertString, pubName);

	if(CAlert::ModalAlert(alertString,
						kRevertButtonString, 
						kCancelButtonString, 
						kNullString,
						1, CAlert::eWarningIcon) == 2) // cancel
	{
		ErrorUtils::PMSetGlobalErrorCode(kCancel);
		return;
	}
	
}

//-----
// WarnUserUpdateDesign()

void InCopyDocUtils::WarnUserUpdateDesign(IDocument* doc, WarnType type)
{ 
	PMString alertString;
	if (type == WarnType_UndoableSave)
	{
		alertString = "Undoable^1Save";
	}
	else if (type == WarnType_CantSave)
	{
		alertString = "Update^1Alert";
	}

	alertString.Translate();
	PMString pubName;
	doc->GetName(pubName);
	
	::ReplaceStringParameters(&alertString, pubName);

	if(CAlert::ModalAlert(alertString,
						kUpdateDesignButtonString, 
						kCancelButtonString, 
						kNullString,
						1, CAlert::eWarningIcon) == 2) // cancel
	{
		ErrorUtils::PMSetGlobalErrorCode(kCancel);
		return;
	}
}

//-----
// SwapBytes()

void InCopyDocUtils::SwapBytes(uchar* buffer, int32 len)
{
	uchar* current = buffer;
	uchar temp = 0;
	
	for (int32 i = 0; i < len/2; i++)
	{
		temp = *current;
		*current = *(current+1);
		*(current+1) = temp;
		current += 2;
	}	

}

void InCopyDocUtils::LockNonInCopyStories(
	const UIDRef& docRef
	)
{
 	InterfacePtr<IStoryList> storyList(docRef, UseDefaultIID());
	InterfacePtr<IInCopyStoryList> icsList(docRef, UseDefaultIID());

	// if this document has any user accessible stories
	if (storyList && icsList)
	{
		// collect a list of any user accessible stories that the user isn't allowed to edit
		UIDList lockableStories(docRef.GetDataBase());
		int32 storyCount(storyList->GetUserAccessibleStoryCount());
		for (int32 i = 0; i < storyCount; i++)
		{
			UID storyUID = storyList->GetNthUserAccessibleStoryUID(i).GetUID();
			if (-1 == icsList->Location(storyUID))
			{
				InterfacePtr<ITextModel> textModel(docRef.GetDataBase(), storyUID, UseDefaultIID());
				if (textModel)
				{
					InterfacePtr<IFrameList> frameList(textModel->QueryFrameList());
					if (frameList && frameList->GetFrameCount() > 0)
					{
						// don't set item lock if this is an inline, lock is same as
						// parent; setting causes bugs like 1149500.
						InterfacePtr<ITextFrameColumn> textFrameColumn(frameList->QueryNthFrame(0));
						if (Utils<IPageItemTypeUtils>()->IsInline(textFrameColumn))
							continue;
					}
				}
				lockableStories.Append(storyUID);
			}
		}

		Utils<IInCopyWorkFlowUtils> inCopyWorkflowUtils;
		InterfacePtr<IDocument> document(docRef, UseDefaultIID());
		lockableStories.Append( inCopyWorkflowUtils->GetNonInCopyGraphicStories( document ) ); // use default doIncludeMasterItems=kTrue because need to lock all nonInCopy stories on page including master items

		// lock any stories the user isn't allowed to edit
		if (lockableStories.Length() > 0)
		{
			InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSetItemLockDataCmdBoss));
			cmd->SetItemList(lockableStories);

			InterfacePtr<IBoolData> data(cmd, IID_IBOOLDATA);
			data->Set(kTrue);	

			CmdUtils::ProcessCommand(cmd);

			//Bug #489900- When an ID pub with no IC stories is opened, all
			//the stories are locked. In that case, no text-lock adornments were added
			//to the framelists. Add the locked text adornments now to be sure they are
			//there in the no IC story case.
			for (int32 j = 0; j < lockableStories.Length(); j++)
			{
				InterfacePtr<ITextModel> textModel(docRef.GetDataBase(), lockableStories[j], UseDefaultIID());
				if (textModel) {
					if (Utils<Facade::IEndnoteFacade>()->IsEndnoteStory(::GetUIDRef(textModel)) && !AnchorStoriesAreLocked(textModel, docRef))
					{
						InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSetItemLockDataCmdBoss));
						cmd->SetItemList(UIDList(::GetUIDRef(textModel)));

						InterfacePtr<IBoolData> data(cmd, IID_IBOOLDATA);
						data->Set(kFalse);

						CmdUtils::ProcessCommand(cmd);
						continue;
					}
				}
				InstallUnmanagedFrameAdornment(lockableStories.GetRef(j));
				
				// check to see if TextLockAdornment exist in first story, first frame
				InterfacePtr<ITextModel> iTextModel(lockableStories.GetRef(j), UseDefaultIID());
				if (!iTextModel)
					continue;

				InterfacePtr<IFrameList> iFrameList (iTextModel->QueryFrameList());
				if( iFrameList == nil )
					continue;

				if (Utils<ITLAdornmentUtils>()->HasTextLockAdornment(iFrameList))
					continue;

				UIDRef ur = docRef;
				Utils<ITLAdornmentUtils>()->RemoveFrameListTextLockAdornment(iFrameList, ur);
				Utils<ITLAdornmentUtils>()->AddFrameListTextLockAdornment(iFrameList, ur);
			}
		}
	}
}

void InCopyDocUtils::InstallUnmanagedFrameAdornment(const UIDRef &lockableStoryRef)
{
	InterfacePtr<ITextModel> tm(lockableStoryRef, UseDefaultIID());
	IDataBase *db = lockableStoryRef.GetDataBase();
	
	if (tm)
	{
		InterfacePtr<IFrameList> frameList(tm->QueryFrameList());
		if (frameList)
		{
			int32 frameCount = frameList->GetFrameCount();
			ASSERT(frameCount > 0);
			for (int32 i = 0; i < frameCount; ++i)
			{
				UID frameUID = frameList->GetNthFrameUID(i);
				InterfacePtr<ITextFrameColumn> textFrameColumn(frameList->QueryNthFrame(i));
				
				InterfacePtr<IHierarchy> textFrameColumnHier(textFrameColumn, UseDefaultIID());
				if (textFrameColumnHier)
				{
					InterfacePtr<IHierarchy> multiColumnFrame(textFrameColumnHier->QueryParent());
					InterfacePtr<IGraphicFrameData> grfd(::GetDataBase(multiColumnFrame), multiColumnFrame->GetParentUID(), UseDefaultIID());
					ASSERT(grfd != nil);
					
					if (grfd)
					{
						InterfacePtr<IPageItemAdornmentList> checkForAdornment(grfd, UseDefaultIID());
						if (checkForAdornment && !checkForAdornment->HasAdornment(kUnavailableTextFrameAdornmentBoss, IAdornmentShape::kAfterContent))
						{
							InterfacePtr<ICommand> adornmentCmd(CmdUtils::CreateCommand( kAddPageItemAdornmentCmdBoss));
							adornmentCmd->SetItemList(UIDList(db, ::GetUID(grfd)));
							InterfacePtr<IClassIDData> labelAdornIDData(adornmentCmd, IID_ICLASSIDDATA);
							labelAdornIDData->Set(kUnavailableTextFrameAdornmentBoss);
							CmdUtils::ProcessCommand(adornmentCmd);
						}
					}
				}
			}
		}
	}
	else
	{
		InterfacePtr<IGraphicFrameData> graphicFrameData(lockableStoryRef, UseDefaultIID());
		if (graphicFrameData)
		{
			InterfacePtr<IPageItemAdornmentList> checkForAdornment(graphicFrameData, UseDefaultIID());
			if (checkForAdornment && !checkForAdornment->HasAdornment(kUnavailableGraphicFrameAdornmentBoss, IAdornmentShape::kAfterContent))
			{
				InterfacePtr<ICommand> adornmentCmd(CmdUtils::CreateCommand( kAddPageItemAdornmentCmdBoss));
				adornmentCmd->SetItemList(UIDList(lockableStoryRef));
				InterfacePtr<IClassIDData> labelAdornIDData(adornmentCmd, IID_ICLASSIDDATA);
				labelAdornIDData->Set(kUnavailableGraphicFrameAdornmentBoss);
				CmdUtils::ProcessCommand(adornmentCmd);
			}
		}

	}
}

void InCopyDocUtils::SetSelectionTo(
	IDataBase* db,
	const UIDRef& story
	)
{
	IDocumentPresentation* pres = Utils<IDocumentUIUtils>()->GetFrontmostPresentationForDocument(db);
	if (!pres)
		return;

	InterfacePtr<IPanelControlData> panelData(pres, UseDefaultIID());
	IControlView* galleyView = panelData->FindWidget(kWritingId);

	if (galleyView && galleyView->IsVisible())
	{
		// temporarily re-enable composition so that selecting will work
		InterfacePtr<ITextLines> textlines(galleyView, UseDefaultIID());
		bool16 composeFlag = textlines->ComposeLayout();
		textlines->SetComposeLayout(kTrue);

		InterfacePtr<ISelectionManager> selMgr(Utils<ISelectionUtils>()->QueryActiveSelection());

		// Get the selection suite (for whatever view)
		InterfacePtr<ITextSelectionSuite> suite(selMgr, UseDefaultIID());
		if (!suite)
			suite.reset(InterfacePtr<ITextSelectionSuite>(selMgr, IID_ITEMPTEXTSELECTION_SUITE).forget());

		if (suite)
			suite->SetTextSelection(story, RangeData(0, RangeData::kLeanForward), Selection::kScrollIntoView, (const RangeData*)0);


		// reset composition to previous condition
		textlines->SetComposeLayout(composeFlag);
	}
}

//-----
// AlertUserUnableToSave()
void InCopyDocUtils::AlertUserUnableToSave(const UIDList& failedLinks)
{
	PMString message("AlertUnableToSave");
	message.Translate();

	int32 count = failedLinks.Length();
	IDataBase* db = failedLinks.GetDataBase();
						
	while (count--)
	{
		InterfacePtr<ILink> link(failedLinks.GetRef(count), UseDefaultIID());
		if (!link) continue;

		PMString linkFileName;
		InterfacePtr<ILinkResource> linkResource(db, link->GetResource(), UseDefaultIID());
		if (linkResource)
		{
			WideString wstr = linkResource->GetLongName(true);
			wstr.GetSystemString(&linkFileName);
			linkFileName.SetTranslatable(kFalse);

			message.Append("\n");
			message.Append(linkFileName);
		}
	}
	message.SetTranslated();

	CAlert::WarningAlert(message);
}

//-----
// QueryDocFileHandler

IDocFileHandler* InCopyDocUtils::QueryDocFileHandler()
{
	return static_cast<IDocFileHandler*> (::CreateObject(kInCopyDocFileHandlerBoss, IID_IDOCFILEHANDLER));
}


//-----
// SetInCopyUserFIle

void InCopyDocUtils::SetInCopyUserFile(IDocument *doc, const IDFile &newFile)
{
	IDataBase* db = GetDataBase(doc);
	db->SetFauxUserFile(newFile);
	InterfacePtr<IRecoveryList> list(GetExecutionContextSession(), IID_IRECOVERYLIST);
	list->UpdateDocument(doc);
}


//----- This util functions came from DocFileHandler...it would be better to put these in a common place
//      So we can use them here and elsewhere

//-----
// BuildSavePopupMenu
	
void InCopyDocUtils::BuildSavePopupMenu(ISaveFileDialog *dlg)
{
	FileTypeInfo pubInfo;
	FileTypeInfo staInfo;

	PMString icmlDoc("InCopyMarkup");
	icmlDoc.Translate();
	pubInfo = FileTypeRegistry::GetCurrentFileTypeInfo(kInCopyXMLMarkupFileTypeInfoID);
	dlg->AddFileTypeInfo(icmlDoc, pubInfo.GetFileExtension());

	//PMString incxDoc("InCopyInterchange");
	//incxDoc.Translate();
	//pubInfo = FileTypeRegistry::GetCurrentFileTypeInfo(kInCopyXMLInterchangeFileTypeInfoID);
	//dlg->AddFileTypeInfo(incxDoc, pubInfo.GetFileCreator(), pubInfo.GetFileType(), pubInfo.GetFileExtension());

	PMString stationeryDesc("InCopyInterchangeTemplate");
    stationeryDesc.Translate();
    staInfo = FileTypeRegistry::GetCurrentFileTypeInfo(kInCopyTemplateFileTypeInfoID);
    dlg->AddFileTypeInfo(stationeryDesc, staInfo.GetFileExtension());

	PMString textDoc("Sangam Text Export");
	textDoc.Translate();
	pubInfo = FileTypeRegistry::GetCurrentFileTypeInfo(kTEXTFileTypeInfoID);
	dlg->AddFileTypeInfo(textDoc, pubInfo.GetFileExtension());
	
	PMString rtfDoc("Sangam RTF Export");
	rtfDoc.Translate();
	pubInfo = FileTypeRegistry::GetCurrentFileTypeInfo(kRTFFileTypeInfoID);
	dlg->AddFileTypeInfo(rtfDoc, pubInfo.GetFileExtension());

}

//-----
// DisableConvertQuotes

bool16 DisableConvertQuotes(
	IDataBase* db
	)
{
	InterfacePtr<IDocument> doc(db, db->GetRootUID(), UseDefaultIID());
	InterfacePtr<IWorkspace> workspace(doc->GetDocWorkSpace(), UseDefaultIID());
	InterfacePtr<ITextOptions> textOptions(workspace, UseDefaultIID());
	bool16 oldQuotes = textOptions->GetUseTypographersQuotes();

	PostTextOptionBooleanCommand(kUseTypographersQuotesCmdBoss, workspace, kFalse);

	return oldQuotes;
}

//-----
// RestoreConvertQuotes

void RestoreConvertQuotes(
	IDataBase* db,
	bool16 state
	)
{
	InterfacePtr<IDocument> doc(db, db->GetRootUID(), UseDefaultIID());
	InterfacePtr<IWorkspace> workspace(doc->GetDocWorkSpace(), UseDefaultIID());

	PostTextOptionBooleanCommand(kUseTypographersQuotesCmdBoss, workspace, state);
}

//-----
// PostTextOptionBooleanCommand

// Copied from textoptions panel code
void PostTextOptionBooleanCommand(
	ClassID attributeCmdBoss, 
	IWorkspace* workspace, 
	bool16 isUseAttribute
	)
{
	InterfacePtr<ICommand> attributeCmd(CmdUtils::CreateCommand(attributeCmdBoss));
	InterfacePtr<IUIDData> useAttributeUidData(attributeCmd, IID_IUIDDATA);
	useAttributeUidData->Set(workspace);
	InterfacePtr<IBoolData> useAttributeBoolData(attributeCmd, IID_IBOOLDATA);
	useAttributeBoolData->Set(isUseAttribute);
	CmdUtils::ProcessCommand(attributeCmd);
}

//-----
// Get active window's view if there is one otherwise use the session's

IInCopyViewPrefs::ActiveView InCopyDocUtils::GetCurrentDocView(UIDRef docRef)
{
	InterfacePtr<IInCopyViewPrefs> windowPrefs( Utils<IDocumentUIUtils>()->GetFrontmostPresentationForDocument(docRef.GetDataBase()), UseDefaultIID());
	if ( windowPrefs )
		return windowPrefs->GetActiveView();

	InterfacePtr<IInCopyViewPrefs> sessionViewPrefs((IInCopyViewPrefs*)::QuerySessionPreferences(IID_IINCOPYVIEWPREFS));
	return sessionViewPrefs->GetActiveView();
}

//-----
// Set the session view preferences

void InCopyDocUtils::SetView(IInCopyViewPrefs *sessionViewPrefs, IInCopyViewPrefs::ActiveView activeView)
{
	if(sessionViewPrefs && activeView != sessionViewPrefs->GetActiveView())
	{
		//no window? set active view for next time a standalone opens
		InterfacePtr<ICommand>	changePrefsCmd( CmdUtils::CreateCommand(kChangeInCopyViewPrefsCmdBoss) );
		InterfacePtr<IWorkspace>	ws(GetExecutionContextSession()->QueryWorkspace());
		changePrefsCmd->SetItemList( ::GetUIDRef(ws) );
		InterfacePtr<IInCopyViewPrefs>	cmdPrefs( changePrefsCmd, UseDefaultIID() );
		cmdPrefs->SetActiveView( activeView );
		CmdUtils::ProcessCommand( changePrefsCmd );
	}
}

void InCopyDocUtils::SaveSelectionForUpdateDesign(UIDRef docRef, int32 &activeStoryIndex, PMString &labelString, RangeData &restoreRange)
{
	// This function is used in conjuction with the RestoreSelectionForUpdateDesign function in this same file. The two used together
	// will attempt to match up the story that was selected before the update design started with the equivalent story in the new document
	// that is open after the update design completes. The story index and story label are saved aside and then on new document open they are
	// matched up. That is, they are matched if a match can be found. If a match can't be found nothing is done. The selection will be in the
	// first story. If a match can be found then the selection will be set in the matching story. This is done to fix bug 639367.
	restoreRange = RangeData(0, RangeData::kLeanForward);
	labelString = PMString("");
	activeStoryIndex = -1;
	{
		UIDRef modelRef;
		TextIndex activeStart, activeEnd;
		Utils<IGalleyUtils>()->GetCurrentTextSelection(activeStart, activeEnd, &modelRef);
		
		// We only attempt to save an insert point not a range. Restoring a range can lead to problems with the selection range overlapping
		// story threads on restore. Can improve this later. This was a last minute feature and we want to keep complexity to 
		// a minimum. The intent of this code is mainly to keep the user looking at the same part of the story as they
		// were before the update design occurred.
		restoreRange = RangeData(activeStart, RangeData::kLeanForward);
		
		InterfacePtr<ITextModel> model(modelRef, UseDefaultIID());
		if (model)
		{
			// Get the current story index and story label string for matching in RestoreSelectionForUpdateDesign().
			InterfacePtr<IStoryLabel> label(model, UseDefaultIID());
			if (label)
			{
				labelString = label->GetLabel();
			}
			
			InterfacePtr<IStoryList> sl(docRef, UseDefaultIID());
			if (sl)
			{
				activeStoryIndex = sl->GetUserAccessibleStoryIndex(modelRef.GetUID());
			}
		}
	}
}

void InCopyDocUtils::RestoreSelectionForUpdateDesign(UIDRef newDocRef, int32 activeStoryIndex, const PMString &labelString, const RangeData &restoreRange)
{
	//----- Restore selection if we can match it up from the old document information
	RangeData newRange = restoreRange;
	
	// See if there is a valid saved index
	if (activeStoryIndex != -1)
	{
		InterfacePtr<ISelectionManager> selMgr(Utils<ISelectionUtils>()->QueryActiveSelection());

		// Get the selection suite (for whatever view)
		InterfacePtr<ITextSelectionSuite> suite(selMgr, UseDefaultIID());
		if (!suite)
			suite.reset(InterfacePtr<ITextSelectionSuite>(selMgr, IID_ITEMPTEXTSELECTION_SUITE).forget());
			
		if (suite)
		{
			InterfacePtr<IStoryList> newStoryList(newDocRef, UseDefaultIID());
			if (newStoryList && activeStoryIndex < newStoryList->GetUserAccessibleStoryCount())
			{
				UIDRef newModelRef = newStoryList->GetNthUserAccessibleStoryUID(activeStoryIndex);
				InterfacePtr<ITextModel> newModel(newModelRef, UseDefaultIID());
				if (newModel)
				{
					InterfacePtr<IStoryLabel> newLabel(newModel, UseDefaultIID());
					if (newLabel && newLabel->GetLabel() == labelString)
					{
						// Found the story validate the selection range before setting
						if (newRange.End() >= newModel->TotalLength())
						{
							newRange = RangeData(newModel->TotalLength()-1, RangeData::kLeanForward);
						}
						
						// We've got a match and a valid place to set the selection so do it
						suite->SetTextSelection(newModelRef, newRange, Selection::kScrollIntoView, &newRange);
					}
				}
			}
		}
	}
}

void InCopyDocUtils::ValidInCopyStory(const UIDRef& storyRef, UIDRef& storyToImport, IDFile* fileToOpen, bool16* isMissing, bool16* isInCopyStory)
{
	ASSERT(isMissing);
	ASSERT(isInCopyStory);
	*isInCopyStory = kFalse;

	Utils<ILinkUtils> linkUtils;
	InterfacePtr<ILinkState> state(storyRef, IID_ILINKSTATE);
	ClassID linkClass = state->GetProviderClass();
	if (linkClass == kInCopyImportProviderBoss || linkClass == 0)
	{
		// still only want InCopy formatted links
		if (Utils<IStoryUtils>()->IsAStory(storyRef))
		{
			// If the data link is embedded then treat it as not incopy
			// InCopy must have a linked file in order to save
			if (!linkUtils->IsLinkEmbedded(storyRef)) 
			{
				storyToImport = storyRef;
				*isInCopyStory = kTrue;
				//----- if the link is missing, don't try to import it, a warning will happen at open
				//         we do want mananged links to get added to the ICStorylist though, se we do return
				//         storyRef
				if (linkUtils->IsLinkMissing(storyRef)) 
				{
					*isMissing = kTrue;
					return;
				}


				if (!linkUtils->GetFileFromLink(storyRef, fileToOpen))
				{
					*isMissing = kTrue; // The name does not specify a disk file name.
					return;
				}

				if ( !FileUtils::DoesFileExist (*fileToOpen) )
				{
					*isMissing = kTrue;
					return;
				}
				*isMissing = kFalse;
			}
		}
	}
}

PMRect InCopyDocUtils::GetDefaultPageRect(IDocument* doc, ISpread *spread)
{
	bool16 IsJFeatureSet = LocaleSetting::GetLocale().GetLanguageFS() == kJapaneseLanguageFS;
	bool16 isVertical = kFalse;
	if (IsJFeatureSet)
	{
		InterfacePtr<IGridAttributesPrefs> gaPrefs( (IGridAttributesPrefs*)::QueryPreferences(IID_IGRIDATTRIBUTESPREFERENCES, doc));	
		IGridAttributesPrefs::TextDirection direction = gaPrefs->GetDirection();		
		if (direction == IGridAttributesPrefs::kVertical)
			isVertical = kTrue;
	}

	//----- Get the first page bounds 
	InterfacePtr<IGeometry> pageGeom(spread->QueryNthPage(0));
	PMRect pageRect(Utils<Facade::IGeometryFacade>()->GetItemBounds( ::GetUIDRef(pageGeom), Transform::ParentCoordinates(), Geometry::OuterStrokeBounds()));

	//----- Get the margins for the page
	InterfacePtr<IMargins> margins(Utils<ILayoutUtils>()->QueryMargins(0, spread));

	PMReal frameWidth;
	PMReal taWidth = Utils<IDocumentSetupUtils>()->GetDocumentSetupTextAreaLength( doc );

	if (margins->MarginsAreValid())
	{
		PMRect marginRect;
		margins->GetMargins(&marginRect);
		if (isVertical)
		{
			pageRect.Top() += marginRect.Top();
			pageRect.Bottom() = pageRect.Top()+taWidth;
			pageRect.Left() += marginRect.Left();
			pageRect.Right() -= marginRect.Right();	
			frameWidth = pageRect.Height();				
		}
		else
		{
			pageRect.Top() += marginRect.Top();
			pageRect.Bottom() -= marginRect.Bottom();
			pageRect.Left() += marginRect.Left();
			pageRect.Right() = pageRect.Left()+taWidth;	

		}
	}
	else
	{
		// get the text area width
		PMReal pageWidth = pageRect.Width();

		if (IsJFeatureSet)
		{
			PMReal	margin = kJDefaultMargin/2;

			if (isVertical)
			{
				PMReal widthMargin = (pageRect.Height()-taWidth)/2;
				pageRect.Top() += widthMargin;
				pageRect.Bottom() = pageRect.Top()+taWidth;
				pageRect.Left() += margin;
				pageRect.Right() -= margin;	
			}
			else
			{
				PMReal widthMargin = (pageRect.Width()-taWidth)/2;
				pageRect.Top() += margin;
				pageRect.Bottom() -= margin;
				pageRect.Left() += widthMargin;
				pageRect.Right() = pageRect.Left()+taWidth;	
			}
		}
		else
		{
			PMReal	margin = kRDefaultMargin/2;
			PMReal widthMargin = (pageRect.Width()-taWidth)/2;
			pageRect.Top() += margin;
			pageRect.Bottom() -= margin;
			pageRect.Left() += widthMargin;
			pageRect.Right() = pageRect.Left()+taWidth;	

		}
	}

	return pageRect;
}

			
UID InCopyDocUtils::GetDefaultLayerUID(IDataBase *db, ISpread *spread)
{
	InterfacePtr<IDocument> doc(db, db->GetRootUID(), UseDefaultIID());
	InterfacePtr<IDocumentLayer> activeDocLayer(Utils<ILayerUtils>()->QueryDocumentActiveLayer(doc));
	InterfacePtr<ISpreadLayer> spreadLayer(spread->QueryLayer(activeDocLayer));

	return ::GetUID(spreadLayer);
}


//-----
// CheckOnRevertStory()

bool16 InCopyDocUtils::CheckOnRevertStory(const UIDRef& storyRef)
{ 
	if (storyRef == kInvalidUIDRef)
	{
		ASSERT_FAIL("InCopyDocUtils::CheckOnRevertStory - invalid story UIDRef?");
		return kFalse;
	}

	PMString	icStoryFileName;

	IDataBase* db = storyRef.GetDataBase();
	InterfacePtr<ILinkManager> linkManager(db, db->GetRootUID(), UseDefaultIID());
	InterfacePtr<ILink> link(linkManager ? linkManager->QueryLinkByUID(Utils<ILinkUtils>()->FindLink(storyRef)) : nil);
	if ( link != nil )
	{
		InterfacePtr<ILinkResource> linkResource(db, link->GetResource(), UseDefaultIID());
		if (linkResource && Utils<IStoryUtils>()->IsAStoryFormatName( linkResource->GetFormatType() ))
		{
			WideString wstr = linkResource->GetLongName(true);
			if( !wstr.empty() )
			{
				PMString fileName;
				wstr.GetSystemString(&fileName);

				const PlatformChar macSeparator = ':';
				const PlatformChar winSeparator = '\\';
				const PlatformChar urlSeparator = '/';
				
				for( int32 i = fileName.CharCount() - 1; i > 0 && icStoryFileName.IsEmpty(); --i )
				{
					const PlatformChar lastChar = fileName.GetChar( i );
					if( lastChar == macSeparator || lastChar == winSeparator || lastChar == urlSeparator )
					{
						fileName.Remove( 0, i + 1 );
						icStoryFileName = fileName;
					}
				}
				
				// file name without separator?
				if( icStoryFileName.IsEmpty() )
					icStoryFileName = fileName;
			}
		}	
	}
	
	if( icStoryFileName.IsEmpty() )
	{
		icStoryFileName = "[Unknown File]";
		icStoryFileName.Translate();
	}
	else
		icStoryFileName.SetTranslatable(kFalse);

	PMString alertString("Revert^1Alert");
	alertString.Translate();
	
	::ReplaceStringParameters(&alertString, icStoryFileName);

	if(CAlert::ModalAlert(alertString,
						kRevertButtonString, 
						kCancelButtonString, 
						kNullString,
						1, CAlert::eWarningIcon) == 2) // cancel
	{
		ErrorUtils::PMSetGlobalErrorCode(kCancel);
		return kFalse;
	}

	return kTrue;
}

ErrorCode InCopyDocUtils::HandleDocActionConflict(const UIDRef& doc, const ActionID& action, UIFlags uiFlags, bool bDoDetailChecking)
{
	bool bSavingInBG = false;
	// InCopy uses bgTasks for saves, so check if this document has any outstanding saves
	{
		InterfacePtr<IIntData> bgSaves(doc, IID_IBACKGROUNDSAVE);
		bSavingInBG = (bgSaves && bgSaves->GetInt() > 0);
	}
	if(bSavingInBG || Utils<IBGTasksUtils>()->IsDocumentInUseByBGTasks(doc, bDoDetailChecking))
	{
		if(Utils<IBGTasksUIUtils>()->ShowDocActionWarningAboutBGTasks(doc, action, uiFlags) == IBGTasksUIUtils::kAbortCmd)
		{
			return kCancel;
		}
	}
	return kSuccess;
}

bool16 InCopyDocUtils::AnchorStoriesAreLocked(const ITextModel * textModel, const UIDRef& docRef)
{
	InterfacePtr<IStoryList> storyList(docRef, UseDefaultIID());
	InterfacePtr<IInCopyStoryList> icsList(docRef, UseDefaultIID());
	Utils<Facade::IEndnoteFacade> endnoteFacade;
	UIDList anchorStoryList = endnoteFacade->GetEndnoteAnchorStories(::GetUIDRef(textModel));
	for (int32 i = 0; i < anchorStoryList.Length(); i++)
	{
		InterfacePtr<IItemLockData> lockData(anchorStoryList.GetRef(i) , UseDefaultIID());
		if ((icsList->Location(anchorStoryList[i]) != -1) || (lockData && lockData->GetInsertLock() == kFalse))
			return kFalse;
	}
	return kTrue;
}
