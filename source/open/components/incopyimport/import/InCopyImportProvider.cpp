//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/incopyimport/import/InCopyImportProvider.cpp $
//  
//  Owner: kvanwiel 
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

// ----- Interfaces -----

#include "ICJKGridData.h"
#include "IDocumentSignalData.h"
#include "IFileStreamData.h"
#include "IFilteredCJKGridCmdData.h"
#include "IFlavorData.h"
#include "IFormatType.h"
#include "IGraphicFrameData.h"
#include "IGuideData.h"
#include "IHierarchy.h"
#include "IINXManager.h"
#include "IINXImportValidation.h"
#include "IInCopyFileInfo.h"
#include "IInCopyImportOptions.h"
#include "IInCopyWorkflow.h"
#include "ILinkState.h"
#include "INamedGridUID.h"
#include "IScript.h"
#include "ISnippetImport.h"
#include "ISpread.h"
#include "ISpreadList.h"
#include "IStandAloneDoc.h"
#include "IStoryOptions.h"
#include "istoryuseraccess.h"
#include "IStyleNameTable.h"
#include "IStringData.h"
#include "IMultiColumnTextFrame.h"
#include "IUIDData.h"
#include "IWorkspace.h"
#include "IClassIDData.h"
#include "IEndnoteSettings.h"
#include "IBoolData.h"

// ----- Includes -----

#include "FileTypeRegistry.h"
#include "InCopyImportExportDefs.h"
#include "ListLazyNotificationData.h"
#include "MuteBackingStoreSubject.h"
#include "ProgressBar.h"
#include "SnippetStringDefs.h"
#include "IEndnoteFacade.h"

// ----- Utility files -----

#include "FileUtils.h"
#include "IInCopyDocUtils.h"
#include "IINXInfo.h"
#include "IPageItemTypeUtils.h"
#include "IPageItemUtils.h"
#include "Utils.h"


// ----- ID.h files -----

#include "InCopyImportID.h"
#include "IDocumentSignalData.h"
#include "isignalmgr.h"

class InCopyImportProvider : public IImportProvider
{
public:
	enum {kInCopyFormat = 0, kInCopyInterchangeFormat = 1, kInCopyMarkupFormat = 2};

	InCopyImportProvider(IPMUnknown *boss) : HELPER_METHODS_INIT(boss), fImportFamily(-1) {}
	
	virtual int32 CountFileTypes();
	virtual SysOSType GetFileType(int32 n);

	virtual int32 CountFormats();
	virtual PMString GetFormatName(int32 formatIndex);
	
	virtual int32 CountExtensionsForFormat(int32 formatIndex);
	virtual PMString GetExtensionForFormat(int32 formatIndex, int32 extensionIndex);

	virtual ImportAbility CanImportThisType(IFormatType *formatType);
	virtual ImportAbility CanImportThisStream(IPMStream *stream);
	virtual void ImportThis(IDataBase *db, IPMStream* stream, UIFlags uiFlags, UIDRef * importedItem, UIDRef * dataLink, PMString * asFormat);

	virtual PMFlavor GetInternalFlavor();
	virtual int32 CountExternalFlavors();
	virtual ExternalPMFlavor GetExternalFlavor(int32 n);

private:
	int32	fImportFamily;
	
	FileTypeRegistry::OSTypeList				fICStoryTypeList;
	FileTypeRegistry::OSTypeList				fICInterchangeTypeList;
	FileTypeRegistry::OSTypeList				fICDocumentTypeList;
	FileTypeRegistry::FileExtensionList			fICStoryExtList;
	FileTypeRegistry::FileExtensionList			fICInterchangeExtList;
	FileTypeRegistry::FileExtensionList			fICMarkupExtList;

	DECLARE_HELPER_METHODS()
};


CREATE_PMINTERFACE(InCopyImportProvider, kInCopyImportProviderImpl)
DEFINE_HELPER_METHODS(InCopyImportProvider)


// LocalSpreadPageItemCollector collects all the page items that fall on
// a given spread. By default we disregard guides.
class LocalSpreadPageItemCollector : public ItemManipulator
{
public:
	LocalSpreadPageItemCollector(UIDList * items, bool16 includeGuides = kFalse);
	
	virtual bool16 ManipulateItem(IHierarchy * pgItemHier);

private:
	UIDList * fItems;
	bool16 fIncludeGuides;
};

// SpreadPageItemCollector collects all the page items that fall on
// a given spread. This does NOT include ruler guides.
LocalSpreadPageItemCollector::LocalSpreadPageItemCollector(UIDList * listIn, bool16 includeGuides) :
	fItems(listIn),
	fIncludeGuides(includeGuides)
{
}

bool16 LocalSpreadPageItemCollector::ManipulateItem(IHierarchy * pgItemHier)
{
	InterfacePtr<IGuideData> guideData(pgItemHier, IID_IGUIDEDATA);
	if (fIncludeGuides || !guideData)
		fItems->Append(::GetUID((IPMUnknown*)pgItemHier));

	return kTrue;
}


//
// ** Constants **
//

// file types and extensions we recognize
#define kNumFamilies					3			//2
#define kNumFileTypes					3			//2


//---------------------------------------------------------------
// InCopyImportProvider::CountFileTypes 
//---------------------------------------------------------------

int32 InCopyImportProvider::CountFileTypes()
{
	return kNumFileTypes;
}

//---------------------------------------------------------------
// InCopyImportProvider::GetFileType 
//---------------------------------------------------------------

SysOSType InCopyImportProvider::GetFileType(int32 i)
{
	if (i == 0)
		return FileTypeRegistry::GetCurrentFileType(kInCopyFileTypeInfoID);
	else if (i == 1)
		return FileTypeRegistry::GetCurrentFileType(kInCopyXMLInterchangeFileTypeInfoID);
	else
		return FileTypeRegistry::GetCurrentFileType(kInCopyXMLMarkupFileTypeInfoID);
}

//---------------------------------------------------------------
// InCopyImportProvider::CountExtensionsForFormat 
//---------------------------------------------------------------

int32 InCopyImportProvider::CountExtensionsForFormat(int32 formatIndex)
{
	if (formatIndex == kInCopyFormat)
	{
		if (fICStoryExtList.empty())
		{
			// Make a list of all of the unique file extensions that this filter supports.
			FileTypeRegistry::GetAllFileExtension(kInCopyFileTypeInfoID, fICStoryExtList, kFalse);
		}
		return fICStoryExtList.size();
	}
	else if (formatIndex == kInCopyInterchangeFormat)
	{
		if (fICInterchangeExtList.empty())
		{
			// Make a list of all of the unique file extensions that this filter supports.
			FileTypeRegistry::GetAllFileExtension(kInCopyXMLInterchangeFileTypeInfoID, fICInterchangeExtList, kFalse);
		}
	
		return fICInterchangeExtList.size();
	}
	else if (formatIndex == kInCopyMarkupFormat)
	{
		if (fICMarkupExtList.empty())
		{
			// Make a list of all of the unique file extensions that this filter supports.
			FileTypeRegistry::GetAllFileExtension(kInCopyXMLMarkupFileTypeInfoID, fICMarkupExtList, kFalse);
		}
	
		return fICMarkupExtList.size();
	}
	else
	{
		ASSERT_FAIL("Bogus Extension index");	
		return 0;
	}
}


//---------------------------------------------------------------
// InCopyImportProvider::GetExtensionForFormat 
//---------------------------------------------------------------

PMString InCopyImportProvider::GetExtensionForFormat(int32 formatIndex, int32 n)
{
	switch (formatIndex) 
	{
		case kInCopyFormat:
			if (n == 0)
			{
				return FileTypeRegistry::GetCurrentFileExtension(kInCopyFileTypeInfoID);
			}
			break;
		case kInCopyInterchangeFormat:
			if (n == 0)
			{
				return FileTypeRegistry::GetCurrentFileExtension(kInCopyXMLInterchangeFileTypeInfoID);
			}
			break;
		case kInCopyMarkupFormat:
			if (n == 0)
			{
				return FileTypeRegistry::GetCurrentFileExtension(kInCopyXMLMarkupFileTypeInfoID);
			}
			break;
		default:
			break;
	}
	return PMString();
}

//---------------------------------------------------------------
// InCopyImportProvider::CountFormats 
//---------------------------------------------------------------

int32 InCopyImportProvider::CountFormats()
{
	return kNumFamilies;
}


//---------------------------------------------------------------
// InCopyImportProvider::GetFormatName
//
// Return the format of the last place or the default.
//---------------------------------------------------------------

PMString InCopyImportProvider::GetFormatName(int32 formatIndex)
{
	PMString formatName( formatIndex == 0 ? InCopy::kInCopyStoryFormatName : formatIndex == 1 ? InCopy::kInCopyInterchangeFormatName : InCopy::kInCopyMarkupFormatName );
	return formatName;
}

//---------------------------------------------------------------
// InCopyImportProvider::CanImportThisType 
//---------------------------------------------------------------

IImportProvider::ImportAbility InCopyImportProvider::CanImportThisType(IFormatType *formatType)
{
	PMString theExtension;
	PMString extension;
	formatType->GetExtension(extension);
	
	theExtension.SetString(FileTypeRegistry::GetCurrentFileExtension(kInCopyFileTypeInfoID));
	if (extension.Compare(false, theExtension) == 0)
	{
		fImportFamily = kInCopyFormat;
		return IImportProvider::kFullImport; 
	}
	
	theExtension.SetString(FileTypeRegistry::GetCurrentFileExtension(kInCopyXMLInterchangeFileTypeInfoID));
	if (extension.Compare(false, theExtension) == 0)
	{
		fImportFamily = kInCopyInterchangeFormat;
		return IImportProvider::kFullImport; 
	}
	
	theExtension.SetString(FileTypeRegistry::GetCurrentFileExtension(kInCopyXMLMarkupFileTypeInfoID));
	if (extension.Compare(false, theExtension) == 0)
	{
		fImportFamily = kInCopyMarkupFormat;
		return IImportProvider::kFullImport; 
	}
	
	SysOSType fileType = formatType->GetSysOSType();

	if (fileType == FileTypeRegistry::GetCurrentFileType(kInCopyFileTypeInfoID))
		return IImportProvider::kFullImport;  

	if (fileType == FileTypeRegistry::GetCurrentFileType(kInCopyXMLInterchangeFileTypeInfoID))
		return IImportProvider::kFullImport;  

	if (fileType == FileTypeRegistry::GetCurrentFileType(kInCopyXMLMarkupFileTypeInfoID))
		return IImportProvider::kFullImport;  

	fImportFamily = -1;
	
	return IImportProvider::kCannotImport;
}

IImportProvider::ImportAbility InCopyImportProvider::CanImportThisStream(IPMStream *stream)
{
	// This gets called when there is no format type or extension information.
	// Look at the first few bytes and determine whether this is a stream that
	// can be imported.

	if (!stream->IsReading())
		return IImportProvider::kCannotImport;

	IImportProvider::ImportAbility importAbility = kCannotImport;

	// make sure this is an incopy stream that we can import
	InterfacePtr<IFileStreamData> fileData(stream, IID_IFILESTREAMDATA);
	if (fileData)
	{
		IDFile file = fileData->GetSysFile();
		
		SysOSType	fileType = 0;
#ifdef MACINTOSH
		SysOSType	creator;
		FileUtils::GetFileCreatorType(file, &fileType, &creator);
#endif
		PMString	extension, baseName;
		FileUtils::GetBaseFileName(file, baseName);
		FileUtils::GetFileName(file, extension);
		int32 removeLen = baseName.CharCount();
		removeLen += (extension.CharCount() > baseName.CharCount())? 1: 0;
		extension.Remove(0, removeLen);

		{
		SysOSType inCopyType = FileTypeRegistry::GetCurrentFileType(kInCopyFileTypeInfoID);
		PMString inCopyExt = FileTypeRegistry::GetCurrentFileExtension(kInCopyFileTypeInfoID);
		if ((fileType == inCopyType) || (inCopyExt.Compare(kFalse, extension) == 0))
		{
			fImportFamily = kInCopyFormat;
			importAbility = kFullImport;
		}
		}
		
		if (importAbility == kCannotImport)
		{
			{
			SysOSType inCopyDocumentType = FileTypeRegistry::GetCurrentFileType(kInCopyXMLMarkupFileTypeInfoID);
			PMString inCopyDocumentExt = FileTypeRegistry::GetCurrentFileExtension(kInCopyXMLMarkupFileTypeInfoID);
			PMString inCopyTemplateExt = FileTypeRegistry::GetCurrentFileExtension(kInCopyTemplateFileTypeInfoID);
			if ((fileType == inCopyDocumentType && (inCopyTemplateExt.Compare(kFalse, extension) != 0)) || (inCopyDocumentExt.Compare(kFalse, extension) == 0))
			{
				fImportFamily = kInCopyMarkupFormat;
				importAbility = kFullImport;
			}
			}
		}
		
		// We need to be careful with the next file test because InCopy Interchange and InCopy Template files
		// have the same Macintosh file type.  If we aren't more careful, we will place template files when we
		// shouldn't (see Watson bug 1089758).

		if (importAbility == kCannotImport)
		{
			SysOSType inCopyInterchangeType = FileTypeRegistry::GetCurrentFileType(kInCopyXMLInterchangeFileTypeInfoID);
			PMString inCopyInterchangeExt = FileTypeRegistry::GetCurrentFileExtension(kInCopyXMLInterchangeFileTypeInfoID);
			PMString inCopyTemplateExt = FileTypeRegistry::GetCurrentFileExtension(kInCopyTemplateFileTypeInfoID);
			if ( ((fileType == inCopyInterchangeType) && (inCopyTemplateExt.Compare(kFalse, extension) != 0)) || (inCopyInterchangeExt.Compare(kFalse, extension) == 0))
			{
				fImportFamily = kInCopyInterchangeFormat;
				importAbility = kFullImport;
			}
		}

		if (importAbility == kCannotImport)
		{
			// okay, now dig into the file to see if we're good to go
		}
	}

	return importAbility; 
}

//---------------------------------------------------------------
// InCopyImportProvider::ImportThis 
//---------------------------------------------------------------
void InCopyImportProvider::ImportThis(IDataBase *db, IPMStream *stream, UIFlags uiFlags, UIDRef * importedItem, UIDRef * dataLink, PMString * asFormat)
{	
	ASSERT(importedItem != nil);

	Utils<Facade::IEndnoteFacade> endnoteFacade;
	InterfacePtr<IEndnoteSettings> endnoteSettings(endnoteFacade->QueryEndnoteSettings(db));
	IEndnoteSettings::Scope scope = endnoteSettings->GetScope();

	// Mute the backing store so that xml observers don't happen during import
	// This is a huge performance boost in some cases. Make sure this goes
	// out of scope before we try to tell observers to update
	{
		MuteBackingStoreSubject backingStoreMuter(db);

		UID	 docUID = db->GetRootUID();
		//UID  contentUID = kInvalidUID;
		//UID	 newStoryUID = kInvalidUID;
		bool8 importingClipBoard = kFalse;

		InterfacePtr<IFileStreamData> fileData(stream, IID_IFILESTREAMDATA);
		if (!fileData) 
		{
			InterfacePtr<IFlavorData> flavorData(stream, UseDefaultIID());
			importingClipBoard = (flavorData != nil);
		}

		bool16 bCreateStory = kTrue;

		// if we have a file type of .incx we want to parse to see if we are opening a graphic or a story.
		if (fImportFamily == kInCopyInterchangeFormat || fImportFamily == kInCopyMarkupFormat)
		{
			InterfacePtr<IINXImportValidation> validation((IINXImportValidation*)::CreateObject(kSnippetImportValidationBoss, IID_IINXIMPORTVALIDATION));
			ASSERT_MSG((validation != nil), "InCopyOpenDocCmd::Do() - Could not create import validation!");

			InterfacePtr<IINXManager> iINXManager( GetExecutionContextSession()->QueryINXManager() ) ;
			ErrorCode result = iINXManager->ValidateINX(stream, validation);
			InterfacePtr<IStringData> snippetType(validation, IID_ISTRINGDATA);
			PMString snippetTypeString = snippetType->GetString();

			if (snippetTypeString == PMString(kPageItemSnippetType))
				bCreateStory = kFalse;
		}

		ErrorCode error = kSuccess;
		InterfacePtr<ICommand> newStoryCmd(nil);

		if (bCreateStory)
		{
			//make a new story to import into
			//Create a command for the creation of a new story
			//This is undoable, as part of ImportFileCmd's sequence
			

			newStoryCmd.reset(CmdUtils::CreateCommand(kNewStoryCmdBoss));
			InterfacePtr<IUIDData> newStoryData(newStoryCmd, IID_IUIDDATA);

			InterfacePtr<IStoryUserAccess> storyAccess(newStoryCmd, IID_ISTORYUSERACCESS);
			storyAccess->SetStoryAccess(kUserAccessible);

			newStoryData->Set(db, docUID);
			if (endnoteFacade->IsEndnoteStory(*dataLink))
			{
				InterfacePtr<IClassIDData> classIdData(newStoryCmd, UseDefaultIID());
				classIdData->Set(kEndnoteStoryBoss);
			}
			const UIDList *result = nil;
			error = CmdUtils::ProcessCommand(newStoryCmd);
			if (error != kSuccess)
			{
				ErrorUtils::PMSetGlobalErrorCode(kFailure);
				return;
			}

			//Get the UIDList from the new story.
			result = newStoryCmd->GetItemList();
			//get the UID for the new TextModel created, within the Story
			*importedItem = result->GetRef(0);
			endnoteFacade->CopyEndnoteDataFromSourceStoryToDestStory(*dataLink, *importedItem);
		}

		InterfacePtr<IDocument> doc(db, db->GetRootUID(), UseDefaultIID());
		InterfacePtr<ITextOptions> textOptions(doc->GetDocWorkSpace(), UseDefaultIID());
		bool16 prevQuotes = textOptions->GetUseTypographersQuotes();
		textOptions->SetUseTypographersQuotes(kFalse);

		/* Create an import options object, through which you can control the the import of the style table the swatch list
		* how to handle missing swatches and styles, etc. Use defaults in this simple case, import everything and don't 
		* provide an import support object. 
		*/
		InterfacePtr<IInCopyImportOptions> options((IInCopyImportOptions*)::CreateObject(kInCopyImportOptionsBoss, IID_IINCOPYIMPORTOPTIONS));

		//incopy workflow interface is on Utils boss;
		//pass datalink as the storyToReplace parameter so inlines will be copied
		//yes, the original text model is in the so-called datalink param

		if ( dataLink )
		{
			UIDRef storyToReplace (*dataLink);

			// If the dataLink is not a text model then maybe it is a frame?
			InterfacePtr<IGraphicFrameData> iGraphicFrameData (storyToReplace, IID_IGRAPHICFRAMEDATA);

			// if a text model then this will be nil
			if ( iGraphicFrameData && (iGraphicFrameData->GetTextContentUID() != kInvalidUID) )
			{
				InterfacePtr<IMultiColumnTextFrame> mcf (db, iGraphicFrameData->GetTextContentUID(), UseDefaultIID());

				if ( mcf && (mcf->GetTextModelUID() != kInvalidUID) )
				{
					storyToReplace.ResetUID (mcf->GetTextModelUID());
				}
			}

			if (fImportFamily == kInCopyFormat)
			{
				InterfacePtr<ITextModel> iTestTheModel (storyToReplace, IID_ITEXTMODEL);

				// if we have a text model then use it for the story to replace
				if ( iTestTheModel )
				{
					error =  Utils<IInCopyWorkflow>()->ImportStory(*importedItem, stream, options, storyToReplace);
				}
				else
				{
					error =  Utils<IInCopyWorkflow>()->ImportStory(*importedItem, stream, options, UIDRef::gNull);
				}

				if (asFormat)
					asFormat->SetString(InCopy::kInCopyStoryFormatName);
			}
			else if (fImportFamily == kInCopyInterchangeFormat || fImportFamily == kInCopyMarkupFormat)
			{	
				//IDataBase* importedItemDB = importedItem->GetDataBase();
				InterfacePtr<IDocument> document(db, db->GetRootUID(), IID_IDOCUMENT);
				InterfacePtr<IDOMElement> documentElement(document, UseDefaultIID());

				if (!bCreateStory)
				{
					// replacing a graphic frame

					// gather the interfaces
					InterfacePtr<IHierarchy> itemHier(storyToReplace, UseDefaultIID());
					InterfacePtr<ISpread> currentISpread(nil);
					if (itemHier)
					{
						// use the stuff we have
						if (Utils<IPageItemTypeUtils>() && Utils<IPageItemTypeUtils>()->IsPlacedInsideText(storyToReplace))
						{
							InterfacePtr<IHierarchy> inlineParentHier( Utils<IPageItemUtils>()->QueryPlacedItemParentPageItem(itemHier) );

							ASSERT(inlineParentHier != nil);
							InterfacePtr<IHierarchy> parentHier(inlineParentHier->QueryRoot());
							ASSERT(parentHier != nil);
							currentISpread.reset(InterfacePtr<ISpread>(parentHier, UseDefaultIID()).forget());
						}
						else
						{
							InterfacePtr<IHierarchy> parentHier(itemHier->QueryRoot());
							ASSERT(parentHier != nil);
							currentISpread.reset(InterfacePtr<ISpread>(parentHier, UseDefaultIID()).forget());
						}
					}
					else
					{
						// grab and use the first spread for import
						InterfacePtr<ISpreadList> spreadList(doc, IID_ISPREADLIST);
						if (spreadList && spreadList->GetSpreadCount())
						{
							currentISpread.reset(InterfacePtr<ISpread>(db, spreadList->GetNthSpreadUID(0), IID_ISPREAD).forget());
						}
					}
					ASSERT(currentISpread != nil);

					// get list of existing page items
					UIDList pageItemListBefore(db), pageItemListAfter(db);
					LocalSpreadPageItemCollector pageItemCollector(&pageItemListBefore, kTrue);	
					currentISpread->ForEachItem(&pageItemCollector, nil);

					// do the import
					InterfacePtr<IScript> spreadScript(currentISpread, UseDefaultIID());
					InterfacePtr<IDOMElement> parentElement(spreadScript, UseDefaultIID());
					error = Utils<ISnippetImport>()->ImportFromStream(stream, parentElement, kInvalidClass, uiFlags);

					if (error == kSuccess)
					{
						// determine which item was added by the import by comparing lists
						LocalSpreadPageItemCollector pageItemCollector2(&pageItemListAfter, kTrue);	
						currentISpread->ForEachItem(&pageItemCollector2, nil);
						for (int32 i=pageItemListAfter.Length()-1; i>=0; i--)
						{
							if (pageItemListBefore.Location(pageItemListAfter[i])>=0)
								pageItemListAfter.Remove(i);
						}

						// we should have just one, assert if more
						ASSERT(pageItemListAfter.Length() == 1);

						*importedItem = pageItemListAfter.GetRef(0);

						// identify this as an incopy graphic story (text stories are handled in the InCopyInterchangeImportPolicy)
						InterfacePtr<IInCopyFileInfo> icFileInfo(*importedItem, UseDefaultIID());
						if (icFileInfo)
							icFileInfo->FileType(IInCopyFileInfo::kTypeInCopyInterchangeGraphicStory);
					}
				}
				else
				{
					// we have to set up the SetCJKGridDataCmd BEFORE calling ImportFromStream, since
					// ImportFromStream modifies importedItem. After the modification, we execute the SetCJKGridDataCmd.
					InterfacePtr<ICommand> cjkGridCmd;
					InterfacePtr<IStandAloneDoc> standAlone(document, UseDefaultIID());

					if (!standAlone || !standAlone->IsStandAloneDoc())
					{
						InterfacePtr<IStoryOptions> storyOptions(storyToReplace, UseDefaultIID());
						if (storyOptions && storyOptions->GetCJKGridActive())
						{
							InterfacePtr<ICJKGridData> cjkGridData(storyToReplace, UseDefaultIID());
							InterfacePtr<INamedGridUID> namedGridUID(storyToReplace, UseDefaultIID());

							if (cjkGridData && namedGridUID)
							{
								if (importedItem)
								{
									UIDList itemList(*importedItem);
									UID namedGrid = namedGridUID->Get();

									InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSetCJKGridDataCmdBoss));
									cjkGridCmd = cmd;
									
									InterfacePtr<INamedGridUID> cmdNamedGridUID(cjkGridCmd, IID_INAMEDGRIDUID);
									cmdNamedGridUID->Set( namedGridUID->Get() );

									cjkGridCmd->SetItemList(itemList);

									InterfacePtr<IFilteredCJKGridCmdData> cmdGridData(cjkGridCmd, IID_IFILTEREDCJKGRIDCMDDATA);
									cmdGridData->CopyFrom( cjkGridData );

									TRACEFLOW("CJKGrid", "InCopyImportProvider::ImportThis(): Setting up SetCJKGridCommand with namedGrid UID %d and gridData from storyToReplace...\n", namedGrid.Get());

									TRACEFLOW("CJKGrid", "InCopyImportProvider::ImportThis(): Firing SetCJKGridDataCmd...\n");
									CmdUtils::ProcessCommand(cjkGridCmd);
								}
							}
						}
					}

					//----- transfer the incopyfileinfo?
					error = Utils<ISnippetImport>()->ImportFromStream(stream, documentElement, kInvalidClass, uiFlags);
					
					if (error == kSuccess) {
						endnoteFacade->MoveEndnoteRange(*importedItem);
						InterfacePtr<ITextModel> storyCreatedOnImport(*importedItem, IID_ITEXTMODEL);
						if (endnoteFacade->IsSeparatorChar(*importedItem, 0))
							storyCreatedOnImport->Delete(0, 1);
						if (!endnoteFacade->IsEndnoteStory(*importedItem))
							endnoteFacade->CopyEndnoteDataFromSourceStoryToDestStory(*dataLink, *importedItem);
					}

					// what's the resulting frame UID?
					if (error == kSuccess)
					{
						InterfacePtr<IInCopyFileInfo> icFileInfo(storyToReplace, UseDefaultIID());
						if (icFileInfo)
						{
							// 						ASSERT(icFileInfo->FileType() == IInCopyFileInfo::kTypeInvalid);
							icFileInfo->FileType(IInCopyFileInfo::kTypeInCopyInterchangeTextStory);
						}
					}
				}

//				ASSERT_MSG(error == kSuccess, "Utils<ISnippetImport>()->ImportFromStream returned an err.");

				if (asFormat)
				{
					if (fImportFamily == kInCopyInterchangeFormat)
						asFormat->SetString(InCopy::kInCopyInterchangeFormatName);
					else
						asFormat->SetString(InCopy::kInCopyMarkupFormatName);
				}
			}
			else
				ASSERT_FAIL("Bogus family");
		}
		else
		{
			if (fImportFamily == kInCopyFormat)
			{
				error =  Utils<IInCopyWorkflow>()->ImportStory(*importedItem, stream, options, UIDRef::gNull);

				if (asFormat)
					asFormat->SetString(InCopy::kInCopyStoryFormatName);

				// save information on original file type
				InterfacePtr<IInCopyFileInfo> icFileInfo(*importedItem, UseDefaultIID());
				if (icFileInfo)
				{
					IInCopyFileInfo::eInCopyFileType icFileType = icFileInfo->FileType();

					if (icFileType == IInCopyFileInfo::kTypeInvalid )
						icFileInfo->FileType(IInCopyFileInfo::kTypeInCopyStory);
				}
			}
			else if (fImportFamily == kInCopyInterchangeFormat || fImportFamily == kInCopyMarkupFormat)
			{	
				//IDataBase* db = importedItem->GetDataBase();
				InterfacePtr<IDocument> document(db, db->GetRootUID(), IID_IDOCUMENT);
				InterfacePtr<IDOMElement> documentElement(document, UseDefaultIID());

				error = Utils<ISnippetImport>()->ImportFromStream(stream, documentElement, kInvalidClass, uiFlags);
//				ASSERT_MSG(error == kSuccess, "Utils<ISnippetImport>()->ImportFromStream returned an err.");

				if (asFormat)
					asFormat->SetString(fImportFamily == kInCopyInterchangeFormat ? InCopy::kInCopyInterchangeFormatName : InCopy::kInCopyMarkupFormatName);

				// save information on original file type
				InterfacePtr<IInCopyFileInfo> icFileInfo(*importedItem, UseDefaultIID());
				if (icFileInfo)
				{
					IInCopyFileInfo::eInCopyFileType icFileType = icFileInfo->FileType();

					if (icFileType == IInCopyFileInfo::kTypeInvalid )
					{
						InterfacePtr<IGraphicFrameData> iGraphicFrameData (*importedItem, IID_IGRAPHICFRAMEDATA);
						if (iGraphicFrameData && iGraphicFrameData->GetTextContentUID() == kInvalidUID)
							icFileInfo->FileType(IInCopyFileInfo::kTypeInCopyInterchangeGraphicStory);
						else
							icFileInfo->FileType(IInCopyFileInfo::kTypeInCopyInterchangeTextStory);
					}
				}
			}
			else
				ASSERT_FAIL("Bogus family");
		}

		if (error != kSuccess)
		{
			PMString errorMessage = ErrorUtils::PMGetErrorString(error);
			ErrorUtils::PMSetGlobalErrorCode (kSuccess);
			ErrorUtils::PMSetGlobalErrorCode (error, &errorMessage);

			*importedItem = UIDRef::gNull;
		}
		else
		{
			InterfacePtr<ILinkState> linkState((*importedItem), IID_ILINKSTATE);
			if (linkState)
				linkState->SetIsLinkNeeded(kFalse);
		}

		textOptions->SetUseTypographersQuotes(prevQuotes);
	}

	if (*importedItem != UIDRef::gNull)
	{
		// Now send a message to allow the XML observers to refresh themselves
		InterfacePtr<ISubject> subject(db, db->GetRootUID(), UseDefaultIID());
		
		ListLazyNotificationData<ClassID> *cookie = new ListLazyNotificationData<ClassID>;
		cookie->ItemAdded(kXMLBackingStoreUnmutedMsg);

		subject->ModelChange(kXMLBackingStoreUnmutedMsg, IID_IIMPORTMANAGER, this, cookie);
	}
}

PMFlavor InCopyImportProvider::GetInternalFlavor()
{
	return kNoFlavor;
}


int32 InCopyImportProvider::CountExternalFlavors()
{
	return 0;
}


ExternalPMFlavor InCopyImportProvider::GetExternalFlavor(int32 n)
{
	return kNoExternalFlavor;
}
