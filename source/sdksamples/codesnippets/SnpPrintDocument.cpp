//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpPrintDocument.cpp $
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

// Interface includes:
#include "IBook.h"
#include "IBookContentMgr.h"
#include "IBookManager.h"
#include "IBookOutputActionCmdData.h"
#include "ICommand.h"
#include "IDatalink.h"
#include "IDocument.h"
#include "IPageList.h"
#include "IPrintCmdData.h"
#include "IPrintData.h"
#include "IPrStStyleListMgr.h"
#include "IUIDData.h"
#include "IWorkspace.h"
#include "ILayerList.h"
#include "IDocumentLayer.h"
#include "IBoolData.h"
#include "IBookContent.h"

// General includes:
#include "DocFrameworkID.h" // for kScriptInvalidConfiguration
#include "LocaleSetting.h"
#include "Utils.h"
#include "UIDList.h"
#include "PrintID.h" // kPrintActionCmdBoss, kInCopyPrintActionCmdBoss
#include "K2Vector.h"
#include "K2Vector.tpp"
#include "K2Pair.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/** \li	Prints a document using the print command.

	@ingroup sdk_snippet, sdk_print
	@author Ken Sadahiro
 */
class SnpPrintDocument
{
public:
	/** Prints a document.
	 * 	@param document IN The document to print.
	 * 	@param printUIOptions IN The UI options during printing.
	 * 	@param printStyle IN The print style to use.
	 * 	@param whichPages IN Which pages to print.  Either IPrintData::kAllPages or IPrintData::kPageRange.
	 *	@param pageRangeString IN The string that denotes the range of pages to print. 
	 * 	@see IPageList::PageRangeStringToUIDList
	 * 	@see IPrintData::kAllPages
	 * 	@see IPrintData::kPageRange
	 * 	@see kPrintSavePrintDataCmdBoss
	 * 	@see kPrintActionCmdBoss
	 * 	@return kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode DoPrintDocument(IDocument* document, 
							  IPrintCmdData::PrintUIOptions printUIOptions, 
							  const UIDRef& printStyle,
							  const int32 whichPages, 
							  const PMString& pageRangeString);

	/** Set the printability of a document layer
	 * 	@param docLayer IN The document layer to be set printable or not.
	 * 	@param printable IN The boolean represents the printability.
	 * 	@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode SetLayerPrintability(IDocumentLayer* docLayer, bool16 printable);

	/** Prints a book.
	 * 	@param book IN The book to print.
	 * 	@param printUIOptions IN The UI options.
	 * 	@param documentToPrint IN The index of the book content (document) to print. 
	 * 			-1 means print all book contents. 
	 * 	@return kSuccess if success.  If the configuration is invalid, 
	 * 			a specific error code is returned. 
	 */
	ErrorCode DoPrintBook(IBook* book, 
											IBookOutputActionCmdData::OutputUIOptions printUIOptions, 
											const int32 documentToPrint = -1);
	
	/** Get the names of the book contents. 
	 * 	@param book IN The book to examine.
	 * 	@return A list of names of book contents. 
	 */
	K2Vector<PMString> GetBookContentNames(IBook* book);

	/** Sort a UIDList by UIDs contained.
	 * 	@param uidlist IN The UIDList to be sorted.
	 * 	@return A new UIDList sorted by UIDs.
	 */
	UIDList SortUIDList(const UIDList& uidlist);
};

/* DoPrintDocument
	NOTE: The commands used in this method will modify the document, 
	so you will need to save it later.
*/
ErrorCode SnpPrintDocument::DoPrintDocument(IDocument* document, IPrintCmdData::PrintUIOptions printUIOptions, const UIDRef& printStyle, const int32 whichPage, const PMString& pageRangeString)
{
	ErrorCode result = kFailure;
	do 
	{
		// check the document
		if (document == nil)
		{
			SNIPLOG("A document is required for DoPrintDocument.");
			break;
		}

		// get the document's print data
		InterfacePtr<IPrintData> docPrintData(document->GetDocWorkSpace(), UseDefaultIID());
		if (docPrintData == nil)
		{
			ASSERT(docPrintData);
			break;
		}

		// STEP 1: modify the page range to print
		InterfacePtr<ICommand> printSavePrintDataCmd(CmdUtils::CreateCommand(kPrintSavePrintDataCmdBoss));
		ASSERT(printSavePrintDataCmd);
		InterfacePtr<IPrintCmdData> printSavePrintDataCmdData(printSavePrintDataCmd, UseDefaultIID());
		ASSERT(printSavePrintDataCmdData);
		// set the document
		printSavePrintDataCmdData->SetIDoc(document);
		// create a temp non-persistent IPrintData
		InterfacePtr<IPrintData> tempPrintData(CreateObject2<IPrintData>(kPrintDataBoss));
		ASSERT(tempPrintData);
		// copy data from the document workspace
		tempPrintData->CopyData(docPrintData, kTrue);
		// set the whichPage and pageRange
		tempPrintData->SetWhichPages(whichPage);
		tempPrintData->SetPageRange(pageRangeString);
		// store off the document's UIDRef in the print data boss
		UIDRef docUIDRef = ::GetUIDRef(document);
		InterfacePtr<IUIDData> iUIDData(tempPrintData, UseDefaultIID());
		ASSERT(iUIDData);
		iUIDData->Set(docUIDRef);
		// set the print data for the command
		printSavePrintDataCmdData->SetPrintData(tempPrintData);

		result = CmdUtils::ProcessCommand(printSavePrintDataCmd);
		if (result != kSuccess)
		{
			SNIPLOG("kPrintSavePrintDataCmdBoss failed");
			break;
		}

		// STEP 2: check if the print style is gNull. If so, use the default
		PMString description;
		UIDRef localPrintStyle = printStyle;
		if (localPrintStyle == UIDRef::gNull)
		{
			InterfacePtr<IWorkspace> workspace(GetExecutionContextSession()->QueryWorkspace());
			ASSERT(workspace);
			InterfacePtr<IPrStStyleListMgr> printStyleListMgr(workspace, UseDefaultIID());
			ASSERT(printStyleListMgr);
			const PMString kUntranslatedDefaultStyleName = "kPrSt_DefaultName";
			int32 index = printStyleListMgr->GetStyleIndexByName(kUntranslatedDefaultStyleName);
			localPrintStyle = printStyleListMgr->GetNthStyleRef(index);
		}
		if (localPrintStyle == UIDRef::gNull)
		{
			ASSERT(localPrintStyle != UIDRef::gNull);
			break;
		}

		// STEP 3: Execute the print action cmd
		// InDesign and InCopy use different commands
        ClassID printCmdBossClassID = kPrintActionCmdBoss;
        if (LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS)) 
		{
			SNIPLOG("Printing in InDesign - using kInCopyPrintActionCmdBoss");
            printCmdBossClassID = kInCopyPrintActionCmdBoss;
        }
		else
		{
			SNIPLOG("Printing in InDesign - using kPrintActionCmdBoss");
		}
        InterfacePtr<ICommand> printActionCmd(CmdUtils::CreateCommand(printCmdBossClassID));
		if (printActionCmd == nil)
		{
			ASSERT(printActionCmd);
			break;
		}
		InterfacePtr<IPrintCmdData> printActionCmdData(printActionCmd, UseDefaultIID());
		if (printActionCmdData == nil)
		{
			ASSERT(printActionCmdData);
			break;
		}
		// bare minimum settings for printing!
		printActionCmdData->SetIDoc(document);
		printActionCmdData->SetPrintUIOptions(printUIOptions);
		printActionCmdData->SetPrtStyleUIDRef(localPrintStyle);

		// NOTE: If you use "Adobe PDF" as a printer, then setting the PDF filename 
		// is part of the "Adobe PDF" printer driver, not an InDesign print option.

		// NOTE 2: If you specify that you want to bring up the print dialog, but 
		// click on Cancel, you will not be able to find out whether the dialog was cancelled
		// from the printActionCmd.  You will have to call lower-level commands. 
		// Also, if you are implementing a kPrintSetupService, it would be a good
		// idea to call ErrorUtils::PMGetGlobalErrorCode to see if the status is
		// NOT kSuccess before performing any tasks. 

		// PRINTING IS NOT UNDOABLE!
		// so there is no point in processing the command and keeping it on the undo stack. 
		result = CmdUtils::ProcessCommand(printActionCmd);
		if (result != kSuccess)
		{
			SNIPLOG("kPrintActionCmdBoss failed");
			break;
		}

	} while (false);
	return result;
}

/* SetLayerPrintability
*/
ErrorCode SnpPrintDocument::SetLayerPrintability(IDocumentLayer* docLayer, bool16 printable)
{
	ErrorCode status = kFailure;
	do
	{
		InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kPrintLayerCmdBoss));
		cmd->SetItemList(UIDList(docLayer));
		InterfacePtr<IBoolData> boolData(cmd, IID_IBOOLDATA);
		boolData->Set(printable);
		status = CmdUtils::ProcessCommand(cmd);
	} while (false);
	return status;
}

/* DoPrintBook
*/
ErrorCode SnpPrintDocument::DoPrintBook(IBook* book, IBookOutputActionCmdData::OutputUIOptions printUIOptions, int32 documentToPrint)
{
	ErrorCode status = kFailure;
	do
	{
		if (book == nil)
		{
			SNIPLOG("A book is required for GetBookContentNames.");
			break;
		}
		// prepare book content UID list
		UIDList uidList(::GetDataBase(book));
		InterfacePtr<IBookContentMgr> bookContentMgr(book, UseDefaultIID());
		if (!bookContentMgr)
		{
			ASSERT_FAIL("bookContentMgr is nil");
			break;
		}
		// default: print all book contents - the UIDList only needs to have the book database
		bool16 printAll = kTrue;

		if (documentToPrint >= 0)
		{
			// We want to print a specific book content
			// NOTE: You can actually append more than one book by 
			// appending more book contents to this uidList.
			// To keep this sample simple, we are only printing one document out of this book
			uidList.Append(bookContentMgr->GetNthContent(documentToPrint));
			printAll = kFalse;
		}
		else
		{
			// We want to print all book contents
			SNIPLOG("Printing all documents in book");
		}
		// get the book file
		IDFile bookFile = book->GetBookFileSpec();

		// create the command
		InterfacePtr<ICommand> printCmd(::CmdUtils::CreateCommand(kBookPrintActionCmdBoss));
		if (printCmd == nil)
		{
			ASSERT_FAIL("(book)printCmd is nil");
			break;
		}
		InterfacePtr<IBookOutputActionCmdData> printCmdData(printCmd, IID_IBOOKOUTPUTACTIONCMDDATA);
		if (printCmdData == nil)
		{
			ASSERT_FAIL("(book)printCmdData is nil");
			break;
		}
		// set the command data
		printCmdData->Set(bookFile, &uidList, printAll);
		printCmdData->SetOutputUIOptions(printUIOptions);
		// execute the command
		status = CmdUtils::ProcessCommand(printCmd);

		// NOTE: If the user prints a black document without enabling
		// print blank pages, the print cmd aborts by returning kCancel.  
		// However, we want to return a little better error message, 
		// so we return this invalid configuration.
		if (status == kCancel)
		{
			// change the error code to something a bit more meaningful... 
			// (see DocumentFrameworkID.h)
			status = kScriptInvalidConfiguration; 
		}

	} while (false);
	return status;
}


/* GetBookContentNames
*/
K2Vector<PMString> SnpPrintDocument::GetBookContentNames(IBook* book)
{
	ErrorCode result = kFailure;
	K2Vector<PMString> bookContentNames;
	bookContentNames.clear();
	do 
	{
		// check the book
		if (book == nil)
		{
			SNIPLOG("A book is required for GetBookContentNames.");
			break;
		}
		IDataBase* bookDB = :: GetDataBase(book);
		if (bookDB == nil)
		{
			ASSERT_FAIL("bookDB is nil");
			break;
		}
		InterfacePtr<IBookContentMgr> bookContentMgr(book, UseDefaultIID());
		if (bookContentMgr == nil)
		{
			ASSERT_FAIL("bookContentMgr is nil");
			break;
		}
		int32 nBooks = bookContentMgr->GetContentCount();
		for (int32 iBook = 0 ; iBook < nBooks ; iBook++)
		{
			UIDRef bookContentUIDRef(bookDB, bookContentMgr->GetNthContent(iBook));
			PMString bookName;
			if (bookContentUIDRef.ExistsInDB() == kTrue)
			{
				InterfacePtr<IBookContent> iBookContent(bookContentUIDRef, UseDefaultIID());
				if (iBookContent)
				{
					bookName = iBookContent->GetShortName();
				}
			}
			bookContentNames.push_back(bookName);
		}
	} while(false);
	return bookContentNames;
}

/* SortUIDList
*/
UIDList SnpPrintDocument::SortUIDList(const UIDList& uidlist)
{
	UIDList sortedUIDList(uidlist.GetDataBase());
	int32 n = uidlist.Length();
	if (n > 0)
	{
		K2Vector<UID> contents;
		contents.clear();
		int32 i;
		// stuff into a vector
		for (i = 0 ; i < n ; i++)
		{
			contents.push_back(uidlist[i]);
		}
		// sort
		K2Vector<UID>::iterator begin = contents.begin();
		K2Vector<UID>::iterator end = contents.end();
		std::sort(begin, end);
		// restuff into UIDList
		for (i = 0 ; i < n ; i++)
		{
			sortedUIDList.Append(contents[i]);
		}
	}
	return sortedUIDList;
}

// --------------------------------- SnippetRunner framework hook ---------------------------------------------------

/** Makes the snippet SnpPrintDocument available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerPrintDocument : public SnpRunnable
{
	public:
		/** This constructor describes your snippet to the framework.
		 */
		_SnpRunnerPrintDocument();

		/** Destructor.
		 */
		virtual			~_SnpRunnerPrintDocument();

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
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunFrontDocContext;}

private:
	ErrorCode Run_PrintDocument(IDocument* document);
	ErrorCode Run_PrintBook(IBook* book);
};

/* Constructor.
*/
_SnpRunnerPrintDocument::_SnpRunnerPrintDocument() : SnpRunnable("PrintDocument")
{
	this->SetDescription("Prints a document or a book");
	this->SetPreconditions("Document or book open; ");
	this->SetCategories("sdk_snippet, sdk_print");
}

/* Destructor.
*/
_SnpRunnerPrintDocument::~_SnpRunnerPrintDocument()	
{
}

/* Check if your preconditions are met.
*/
bool16  _SnpRunnerPrintDocument::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do 
	{
		// see if there is a front document.
		if (runnableContext->GetActiveContext()->GetContextDocument() != nil)
		{
			result = kTrue;
			break;
		}
		// see if there is an active book.
        InterfacePtr<IBookManager> bookManager(GetExecutionContextSession(), UseDefaultIID());
		if (bookManager && bookManager->GetCurrentActiveBook() != nil)
		{
			result = kTrue;
			break;
		}
	} while (false);
	return result;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerPrintDocument::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do
	{
		/* --- STEP 0: Get document and/or book to print --- */
		IDocument* document = runnableContext->GetActiveContext()->GetContextDocument();

		InterfacePtr<IBookManager> bookManager(GetExecutionContextSession(), UseDefaultIID());
		if (bookManager == nil)
		{
			ASSERT_FAIL("bookManager is nil");
			break;
		}
		IBook* book = bookManager->GetCurrentActiveBook();


		// Use IParameterUtils to prompt for parameters
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		PMString prompt;
		int32 defaultChoice;

		enum { kPrintDocument, kPrintBook, kPrintUnknown };
		int32 printOperation = kPrintUnknown;
		if (document && !book) 
			printOperation = kPrintDocument;
		if (!document && book) 
			printOperation = kPrintBook;

		if (printOperation == kPrintUnknown)
		{
			choices.clear();
			choices.push_back("Print active document");
			choices.push_back("Print active book");
			prompt = PMString("Choose what you want to print", PMString::kEncodingASCII);
			defaultChoice = kPrintDocument;
			printOperation = parameterUtils->GetChoice(prompt, choices, defaultChoice);
			if (parameterUtils->WasDialogCancelled() == kTrue)
			{
				status = kCancel;
				break;
			}
		}

		switch (printOperation)
		{
		case kPrintDocument:
			status = this->Run_PrintDocument(document);
			break;
		case kPrintBook:
			status = this->Run_PrintBook(book);
			break;
		}

	} while (false);
	return(status);
}

ErrorCode _SnpRunnerPrintDocument::Run_PrintDocument(IDocument* document)
{
	ErrorCode status = kCancel;
	do
	{
		// Use IParameterUtils to prompt for parameters
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		int32 defaultChoice;
		PMString prompt;

		/* --- Get print UI options --- */
		IPrintCmdData::PrintUIOptions printUIOptions = IPrintCmdData::kSuppressEverything;
		choices.clear();
		choices.push_back("SuppressNothing");			// 0x0,
		choices.push_back("SuppressPrintProgress");		// 0x1,
		choices.push_back("SuppressPrintWarnings");		// 0x2,
		choices.push_back("SuppressPrintDialog");		// 0x4,
		choices.push_back("SuppressFileSaveDialog");	// 0x8,
		choices.push_back("SuppressEverything");		// 0xFF
		prompt = PMString("Select a UI option", PMString::kEncodingASCII);
		defaultChoice = 5;
		int32 choice = parameterUtils->GetChoice(prompt, choices, defaultChoice);
		if (parameterUtils->WasDialogCancelled() == kTrue)
		{
			status = kCancel;
			break;
		}
		SNIPLOG("Selected UI Option: %s", choices[choice].GetPlatformString().c_str());
		switch (choice)
		{
		case 1: 	printUIOptions = IPrintCmdData::kSuppressPrintProgress; break;
		case 2: 	printUIOptions = IPrintCmdData::kSuppressPrintWarnings; break;
		case 3: 	printUIOptions = IPrintCmdData::kSuppressPrintDialog; break;
		case 4: 	printUIOptions = IPrintCmdData::kSuppressFileSaveDialog; break;
		case 5: 	printUIOptions = IPrintCmdData::kSuppressEverything; break;
		default: 	printUIOptions = IPrintCmdData::kSuppressNothing; break;
		}

		/* --- Get print style to use --- */
		choices.clear();
		InterfacePtr<IWorkspace> workspace(GetExecutionContextSession()->QueryWorkspace());
		ASSERT(workspace);
		InterfacePtr<IPrStStyleListMgr> printStyleListMgr(workspace, UseDefaultIID());
		ASSERT(printStyleListMgr);
		int32 numStyles = printStyleListMgr->GetNumStyles();
		for (int32 i = 0; i < numStyles ; i++)
		{
			PMString styleName = "";
			PMString styleDescr = "";
			status = printStyleListMgr->GetNthStyleName(i, &styleName);
			if (status == kSuccess)
			{
				choices.push_back(styleName);
			}
			else
			{
				SNIPLOG("Problem getting print style index %d", i);
				break;
			}
		}
		if (status != kSuccess)
		{
			status = kCancel;
			break;
		}

		prompt = PMString("Select a print style", PMString::kEncodingASCII);
		defaultChoice = 0;
		int32 printStyleIndex = parameterUtils->GetChoice(prompt, choices, defaultChoice);
		if (parameterUtils->WasDialogCancelled() == kTrue)
		{
			status = kCancel;
			break;
		}
		UIDRef printStyle = printStyleListMgr->GetNthStyleRef(printStyleIndex);
		SNIPLOG("Selected print style:\n%s", choices[printStyleIndex].GetPlatformString().c_str());


		/* --- Get page range to print --- */
		prompt = PMString("Specify a page range", PMString::kEncodingASCII);
		// make a string that contains all pages in doc
		PMString allPagesString;
		IDataBase* db = ::GetDataBase(document);
		if (db == nil)
		{
			ASSERT_FAIL("db is nil!");
			break;
		}
		InterfacePtr<IPageList> pageList(document, UseDefaultIID());
		if (pageList == nil)
		{
			ASSERT_FAIL("pageList is nil!");
			break;
		}
		int32 numPages = pageList->GetPageCount();
		UIDList pagesUIDList(::GetDataBase(document));
		for (int32 i = 0 ; i < numPages ; i++)
		{
			pagesUIDList.Append(pageList->GetNthPageUID(i));
		}
		// make a page string for all pages 
		pageList->GetPageRangeString(pagesUIDList, &allPagesString);

		// ask the user
		PMString pageRangeString = parameterUtils->GetPMString(prompt, allPagesString);
		if (parameterUtils->WasDialogCancelled() == kTrue)
		{
			status = kCancel;
			break;
		}
		// validate page range
		UIDList validatedUIDList(db);
		ITextDataValidation::RangeError rangeError = 
			pageList->PageRangeStringToUIDList(pageRangeString, &validatedUIDList);
		if (rangeError != ITextDataValidation::kNoError)
		{
			SNIPLOG("An invalid page range \"%s\" was specified. (RangeError = %d, see ITextDataValidation::RangeError) Aborted.", 
					pageRangeString.GetPlatformString().c_str(), rangeError);
			status = kCancel;
			break;
		}

		SNIPLOG("Page range: %s", pageRangeString.GetPlatformString().c_str());

		// let's get ready to print...
		SnpPrintDocument instance;
		// Let user chooses which layer to print
		InterfacePtr<ILayerList> iLayerList(document, UseDefaultIID());
		for (int32 i=1; i<iLayerList->GetCount(); i++)
		{
			InterfacePtr<IDocumentLayer> iDocLayer(iLayerList->QueryLayer(i));
			PMString layerName = iDocLayer->GetName();
			prompt = PMString("Do you want to print layer ", PMString::kEncodingASCII);
			prompt += layerName;
			choices.clear();
			choices.push_back("Yes");			// 0x0,
			choices.push_back("No");		// 0x1,
			defaultChoice = 0;
			int32 choice = parameterUtils->GetChoice(prompt, choices, defaultChoice);
			if (parameterUtils->WasDialogCancelled() == kTrue)
			{
				status = kCancel;
				break;
			}
			bool16 isPrintable = iDocLayer->IsPrintable();
			if ((choice == 0 && !isPrintable) || (choice == 1 && isPrintable))
			{
				if (choice == 0)
					status = instance.SetLayerPrintability(iDocLayer, kTrue);
				else
					status = instance.SetLayerPrintability(iDocLayer, kFalse);
			}
		}
		if (status != kSuccess)
			break;
			
		// default: we are printing all pages
		int32 whichPages = IPrintData::kAllPages;
		// change the page range only if we are not printing all pages
		UIDList sortedValidatedUIDList(instance.SortUIDList(validatedUIDList));
		UIDList sortedPagesUIDList(instance.SortUIDList(pagesUIDList));
		if (sortedPagesUIDList != sortedValidatedUIDList)
		{
			SNIPLOG("Specifying the use of a specific page range (instead of all pages)");
			whichPages = IPrintData::kPageRange;
		}

		/* --- Print the document --- */
		status = instance.DoPrintDocument(document, printUIOptions, printStyle, whichPages, pageRangeString);

	} while (false);
	return(status);
}

ErrorCode _SnpRunnerPrintDocument::Run_PrintBook(IBook* book)
{
	ErrorCode status = kCancel;
	do
	{
		// Use IParameterUtils to prompt for parameters
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		int32 defaultChoice;
		PMString prompt;

		SnpPrintDocument instance;
	
		/* --- Get print UI options --- */
		IBookOutputActionCmdData::OutputUIOptions printUIOptions = IBookOutputActionCmdData::kSuppressNothing;
		choices.clear();
		choices.push_back("SuppressNothing");			// 0x0,
		choices.push_back("SuppressPrintProgress");		// 0x1,
		choices.push_back("SuppressPrintWarnings");		// 0x2,
		choices.push_back("SuppressPrintDialog");		// 0x4,
		choices.push_back("SuppressEverything");		// 0xFF
		prompt = PMString("Select a UI option", PMString::kEncodingASCII);
		defaultChoice = 4;
		int32 choice = parameterUtils->GetChoice(prompt, choices, defaultChoice);
		if (parameterUtils->WasDialogCancelled() == kTrue)
		{
			status = kCancel;
			break;
		}
		SNIPLOG("Selected UI Option: %s", choices[choice].GetPlatformString().c_str());
		switch (choice)
		{
		case 1: 	printUIOptions = IBookOutputActionCmdData::kSuppressOutputProgress; break;
		case 2: 	printUIOptions = IBookOutputActionCmdData::kSuppressOutputWarnings; break;
		case 3: 	printUIOptions = IBookOutputActionCmdData::kSuppressOutputDialog; break;
		case 4: 	printUIOptions = IBookOutputActionCmdData::kSuppressEverything; break;
		default:	printUIOptions = IBookOutputActionCmdData::kSuppressNothing; break;
		}

		/* -- Print all or some of the documents in the book? -- */
		choices.clear();
		K2Vector<PMString> bookContentNames(instance.GetBookContentNames(book));
		bookContentNames.insert(bookContentNames.begin(), PMString("[ALL]"));

		prompt = PMString("Select the document to print", PMString::kEncodingASCII);
		defaultChoice = 0;
		int32 documentToPrint = parameterUtils->GetChoice(prompt, bookContentNames, defaultChoice);
		if (parameterUtils->WasDialogCancelled() == kTrue)
		{
			status = kCancel;
			break;
		}
		SNIPLOG("Selected document to print : %s", bookContentNames[documentToPrint].GetPlatformString().c_str());
		// index is offset by one, so decrement.
		documentToPrint--;
		status = instance.DoPrintBook(book, printUIOptions, documentToPrint);

	} while(false);
	return status;
}

/*	Declare an instance to register the snippet hook with the framework.
*/
static _SnpRunnerPrintDocument instance_SnpRunnerPrintDocument;
DEFINE_SNIPPET(_SnpRunnerPrintDocument) 	


// End, SnpPrintDocument.cpp

