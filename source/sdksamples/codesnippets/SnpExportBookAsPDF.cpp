//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpExportBookAsPDF.cpp $
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
#include "IBookCmdData.h"
#include "IBookContent.h"
#include "IBookContentMgr.h"
#include "IBookManager.h"
#include "IBookOutputActionCmdData.h"
#include "ICommand.h"
#include "IDataBase.h"
#include "IDatalink.h"
#include "IPDFExportPrefs.h"
#include "IPDFExptStyleListMgr.h"
#include "ISession.h"
#include "IStringData.h"
#include "IDFile.h"
#include "IBookContent.h"

// General includes:
#include "BookID.h"
#include "CmdUtils.h"
#include "K2Vector.h"
#include "PersistUtils.h"
#include "PreferenceUtils.h"
#include "SDKFileHelper.h"
#include "UIDList.h"
#include "Utils.h"
#include "LocaleSetting.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/** \li	Exports a book to a PDF.
 * 
 * 	This snippet shows how to use the kBookExportActionCmdBoss
 * 	to export a book in various ways to PDF. 
 * 	When you export to PDF, you can export all of the book contents, 
 * 	or specific book contents.
 * 
 * 	@ingroup sdk_snippet
 * 	@ingroup sdk_export
 * 	@ingroup sdk_layout 
 * 	@ingroup sdk_graphic 
 * 	@see kBookExportActionCmdBoss
 *	@see IBookOutputActionCmdData
 * 	@see IPDFExportPrefs
 * 	@see kSetPDFExportPrefsCmdBoss
 */
class SnpExportBookAsPDF 
{
public:
	/** Constructor.
	 */
	SnpExportBookAsPDF() {}

	/** Destructor.
	 */
	virtual	~SnpExportBookAsPDF() {}

	/** Exports a book as PDF.
	 * 	This method wraps the kBookExportActionCmdBoss.
	 * 	@param book IN The book to export.
	 * 	@param pdfFileName IN The IDFile to which you want to export.
	 * 	@param bookContentsToExport IN UIDList containing the specific 
	 * 		book contents to export. This is ignored if 
	 * 		exportAllDocsInBook is kTrue.
	 * 	@param exportAllDocsInBook IN A flag to specify if you want all 
	 * 		of the book content to be exported.  Default: kTrue.
	 * 	@param options IN UI Options for the operation.  
	 * 		By default, this is set to IBookOutputActionCmdData::kSuppressEverything, 
	 * 		which will not show any dialog.
	 * 		Refer to the comments in the Run() method for more details
	 * 		on how to change the PDF Export preferences programmatically.
	 * 	@return kSuccess on success, other ErrorCode otherwise.
	 * 
	 * 	@see IBookOutputActionCmdData::OutputUIOptions 
	 * 	@see IBook
	 * 	@see IBookManager
	 * 	@see IBookContentMgr
	 */
	ErrorCode ExportBookAsPDF(IBook* book, 
							  IDFile& pdfFileName, 
							  UIDList& bookContentsToExport, 
							  bool16 exportAllDocsInBook = kTrue,
							  IBookOutputActionCmdData::OutputUIOptions options = IBookOutputActionCmdData::kSuppressEverything);
	
	/** Makes a PDF filename (IDFile) for the book, based on the 
	 * 		book's filename. It just replaces the .indb with .pdf.
	 * 	@param book IN The book that you want to export.
	 * 	@return IDFile for the PDF to export.
	 * 	@see SDKFileHelper
	 */
	const IDFile MakePDFFilename(IBook* book);

	/** Sets the PDF export style by index. 
	 * 	@param pdfStylesIndex IN The index of the IGenStlEdtListMgr/IPDFExptStyleListMgr styles. 
	 * 		Note that all import and export styles are grouped together. 
	 * 	@return kSuccess if success, kFailure otherwise.
	 */
	ErrorCode SetPDFExportStyleByIndex(int32 pdfStylesIndex);


	/** Gets the names of books currently available.
	 * 	@param bookManager IN The session's book manager.
	 * 	@return A list of PMStrings containing names of books that are currently open.
	 */
	K2Vector<PMString> GetBookNames(IBookManager* bookManager);

	/** Gets the names of contents in a book.
	 * 	@param bookContentMgr IN The book's content manager.
	 * 	@return A list of PMStrings containing names of contents (documents) in the book.
	 */
	K2Vector<PMString> GetBookContentNames(IBookContentMgr* bookContentMgr);

	/** Gets the names of PDF export styles.
	 * 	@return List of PDF export styles by their names. 
	 */
	K2Vector<PMString> GetPDFExportStyles(void);

	/** Returns the index of the current PDF export style
	 * 	@return The index of the current PDF export style. This index is from the 
	 * 		IGenStlEdtListMgr/IPDFExptStyleListMgr styles that are for exporting.
	 */
	int32 GetCurrentPDFExportStyle(void);


};

/* ExportBookAsPDF
*/
ErrorCode SnpExportBookAsPDF::ExportBookAsPDF(IBook* book, 
                                              IDFile& pdfFileName, 
											  UIDList& bookContentsToExport, 
											  bool16 exportAllDocsInBook,
											  IBookOutputActionCmdData::OutputUIOptions options)
{
	ErrorCode status = kFailure;
	do
	{
		SDKFileHelper fileHelper(pdfFileName);
		if (book == nil ||
			fileHelper.GetPath().empty()) 
		{ 
			ASSERT_FAIL("One or more preconditions are not met - exiting");
			break; 
		} 
		if (exportAllDocsInBook != kTrue && bookContentsToExport.IsEmpty())
		{
            /*	If you want to export specific contents within a book
				to PDF, make sure you fill out UIDList with kBookContentBoss UIDs 
				that you want to export.
				
				Hint: Use IBookContentManager (kBookBoss), which gives you UIDs for kBookContentBoss. 
				Also, use IBookContent and IDataLink (GetFullName() method is useful)
				in kBookContentBoss. 
				
				If you want to add docs to a book, use the kAddDocToBookCmdBoss command. (BookID.h)
			*/
			ASSERT_FAIL("You want to export specific documents from the book, but your bookContentsToExport UIDList is empty!");
			break;
		}

		// create the book export action command
		InterfacePtr<ICommand> bookExportCmd(CmdUtils::CreateCommand(kBookExportActionCmdBoss));
		if (bookExportCmd == nil) 
		{ 
			ASSERT(bookExportCmd);
			break; 
		}
		// Get the IBookOutputActionCmdData data interface
		InterfacePtr<IBookOutputActionCmdData>  data(bookExportCmd, IID_IBOOKOUTPUTACTIONCMDDATA);
		if (data == nil) 
		{ 
			break; 
		}

		// get the filename of the book database
		IDFile bookFile = book->GetBookFileSpec();
		// set the book file name, book content list, and the export-all flag
		data->Set(bookFile, &bookContentsToExport, exportAllDocsInBook); 
		// check if the PDF filepath is a valid path
		SDKFileHelper helper(pdfFileName);
		bool16 hasFileName = (helper.GetPath().empty() == kFalse);
		// set the output filename
		data->SetOutputFile(pdfFileName, hasFileName);
		// set the UI options
		data->SetOutputUIOptions(options);

		// process the command
		status = CmdUtils::ProcessCommand(bookExportCmd);

		ASSERT(status == kSuccess);

	} while (false);
	return status;
}

/* MakePDFFilename
*/
const IDFile SnpExportBookAsPDF::MakePDFFilename(IBook* book)
{
	IDFile bookFile;
	do {
		if (book == nil) 
		{
			ASSERT(book);
			break;
		}
		// get the full path of the book.
		SDKFileHelper booktitleFileHelper(book->GetBookFileSpec());
		PMString bookTitleName = booktitleFileHelper.GetPath();
		ASSERT(bookTitleName.empty() == kFalse);
		CharCounter lastPeriod = bookTitleName.LastIndexOfWChar(UTF32TextChar('.'));
		int32 len = bookTitleName.WCharLength();
		if (lastPeriod > 0) 
		{
			// period found - truncate last N chars
			bookTitleName.Truncate(len-lastPeriod);
		}

		// just append a .pdf at the end
		bookTitleName.Append(".pdf");
		SDKFileHelper fileHelper(bookTitleName);
		bookFile = fileHelper.GetIDFile();

	} while (false);
#ifdef DEBUG
	SDKFileHelper fileCheckHelper(bookFile);
	ASSERT(fileCheckHelper.GetPath().empty() == kFalse);
#endif
	return bookFile;
}

/* SetPDFExportStyleByIndex
*/
ErrorCode SnpExportBookAsPDF::SetPDFExportStyleByIndex(int32 pdfStylesIndex)
{
	ErrorCode status = kFailure;
	do {
		if (pdfStylesIndex == this->GetCurrentPDFExportStyle()) 
		{
			// the style isn't different - no need to change it
			status = kSuccess;
			break;
		}

		// get the PDF export style list
        InterfacePtr<IPDFExptStyleListMgr> styleMgr
			((IPDFExptStyleListMgr*)::QuerySessionPreferences(IPDFExptStyleListMgr::kDefaultIID));
        if (styleMgr == nil)
		{
			ASSERT_FAIL("Failed to get IPDFExptStyleListMgr");
			break;
		}

		UIDRef pdfExportStyleRef = styleMgr->GetNthStyleRef(pdfStylesIndex);
        InterfacePtr<IPDFExportPrefs> pdfExportStyleToSet(pdfExportStyleRef, UseDefaultIID());
		if (pdfExportStyleToSet == nil) 
		{
			ASSERT_FAIL("Failed to get IPDFExportPrefs/pdfExportStyleToSet");
			break;
		}

		// process kSetPDFExportPrefsCmdBoss to change current settings
		InterfacePtr<ICommand> setPDFExportPrefsCmd(CmdUtils::CreateCommand(kSetPDFExportPrefsCmdBoss));
		if (setPDFExportPrefsCmd == nil) 
		{
			ASSERT_FAIL("Failed to get setPDFExportPrefsCmd");
			break;
		}
		InterfacePtr<IPDFExportPrefs> pdfExportPrefs(setPDFExportPrefsCmd, UseDefaultIID());
		if (pdfExportPrefs == nil) 
		{
			ASSERT_FAIL("Failed to get IPDFExportPrefs/pdfExportPrefs");
			break;
		}
		pdfExportPrefs->CopyPrefs(pdfExportStyleToSet);
		status = CmdUtils::ProcessCommand(setPDFExportPrefsCmd);

	} while (false);
	return status;
}

/* GetBookNames
*/
K2Vector<PMString> SnpExportBookAsPDF::GetBookNames(IBookManager* bookManager)
{
	K2Vector<PMString> bookNames;
	bookNames.clear();

	do {
		if (bookManager == nil) 
		{
			ASSERT(bookManager);
			break;
		}
		int32 bookCount = bookManager->GetBookCount();
		for (int32 i = 0 ; i < bookCount ; i++) 
		{
			IBook* book = bookManager->GetNthBook(i);
			if (book == nil) 
			{
				// go onto the next book...
				continue;
			}
			// get the book name
			PMString bookName = book->GetBookTitleName();
			ASSERT(bookName.empty() == kFalse);
			bookNames.push_back(bookName);
		}
		
	} while (false);
	return bookNames;
}

/* GetBookContentNames
*/
K2Vector<PMString> SnpExportBookAsPDF::GetBookContentNames(IBookContentMgr* bookContentMgr)
{
	K2Vector<PMString> bookContentNames;
	bookContentNames.clear();
	do {
		if (bookContentMgr == nil) 
		{
			ASSERT(bookContentMgr);
			break;
		}

		// get the book's database (same for IBook)
		IDataBase* bookDB = ::GetDataBase(bookContentMgr);
		if (bookDB == nil) 
		{
			ASSERT_FAIL("bookDB is nil - wrong database?"); 
			break;
		}

		int32 contentCount = bookContentMgr->GetContentCount();
		for (int32 i = 0 ; i < contentCount ; i++) 
		{
			UID contentUID = bookContentMgr->GetNthContent(i);
			if (contentUID == kInvalidUID) 
			{
				// somehow, we got a bad UID
				continue; // just goto the next one
			}
			// get the nth IBookContent of the book
			InterfacePtr<IBookContent> bookContent(bookDB, contentUID, UseDefaultIID());
			if (bookContent == nil) 
			{
				ASSERT_FAIL(FORMAT_ARGS("IBookContent for book #%d is missing", i));
				break; // out of for loop
			}

			// get the book name and add it to the list
			PMString shortName = bookContent->GetShortName();
			ASSERT(shortName.empty() == kFalse);
			bookContentNames.push_back(shortName);
		}

	} while (false);
	return bookContentNames;
}

/* GetPDFExportStyles
*/
K2Vector<PMString> SnpExportBookAsPDF::GetPDFExportStyles(void)
{
	K2Vector<PMString> styles;
	styles.clear();
	do {
        InterfacePtr<IPDFExptStyleListMgr> styleMgr
			((IPDFExptStyleListMgr*)::QuerySessionPreferences(IPDFExptStyleListMgr::kDefaultIID));
        if (styleMgr == nil)
		{
			ASSERT_FAIL("Failed to load IPDFExptStyleListMgr");
			break;
		}
		int32 numStyles = styleMgr->GetNumStyles();
		for (int32 i = 0 ; i < numStyles ; i++) 
		{
			PMString name;
			ErrorCode status = kSuccess;
			status = styleMgr->GetNthStyleName(i, &name);
			if (status != kSuccess) 
			{
				ASSERT_FAIL(FORMAT_ARGS("Could not get %dth PDF Export style name", i));
				continue;
			}
			else
			{
				styles.push_back(name);
			}
		}
	} while (false);
	return styles;
}

/* GetCurrentPDFExportStyle
*/
int32 SnpExportBookAsPDF::GetCurrentPDFExportStyle(void)
{
	int32 index = -1;
	do {
		// get the IPDFExptStyleListMgr
        InterfacePtr<IPDFExptStyleListMgr> styleMgr
			((IPDFExptStyleListMgr*)::QuerySessionPreferences(IPDFExptStyleListMgr::kDefaultIID));
        if (styleMgr == nil)
		{
			ASSERT_FAIL("Failed to get IPDFExptStyleListMgr");
			break;
		}
		// get the last use export style
        InterfacePtr<IStringData> lastPDFExportStyleUsed
			((IStringData*)::QuerySessionPreferences(IID_IPDFEXPORTSTYLELASTUSED));
        if (lastPDFExportStyleUsed == nil)
		{
			ASSERT_FAIL("Failed to get IStringData");
			break;
		}
		PMString lastStyleName = lastPDFExportStyleUsed->Get();

		if (lastStyleName.empty()) 
		{
			ASSERT_FAIL("(BENIGN) There was no last used PDF export style. To quiet this assert, open the PDF Export Styles dialog, select one of the styles, and click on the 'Edit' button.");
			break;
		}
		// ask for the index of the last used style
		index = styleMgr->GetStyleIndexByName(lastStyleName);

	} while (false);
	return index;
}


// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

/** Makes the snippet SnpExportBookAsPDF available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerExportBookAsPDF : public SnpRunnable
{


public:
	// SnippetRunner framework hooks.

	/** Constructor.
	 */
	_SnpRunnerExportBookAsPDF(void);

	/** Destructor.
	 */
	virtual	~_SnpRunnerExportBookAsPDF(void);

	/** Return kTrue if the snippet can run.
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kTrue if snippet can run, kFalse otherwise
	 */
	bool16 CanRun(ISnpRunnableContext* runnableContext);

	/** Run the snippet.
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode Run(ISnpRunnableContext* runnableContext);

	/**	Don't present this snippet in the framework's UI if the
		product we are running under is InCopy. 
		@return kTrue if the snippet can be loaded, kFalse otherwise.
	*/
	bool16 CanLoad() const;
	
	/** 
		get the snippet context
		@return eSnpRunContextType for this snippet
	*/
	virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunCustomContext;}

	virtual ErrorCode SetupContext(ISnpRunnableContext* runnableContext);

};

/* Constructor.
*/
_SnpRunnerExportBookAsPDF::_SnpRunnerExportBookAsPDF() : SnpRunnable("ExportBookAsPDF")
{
	this->SetDescription("Exports a book to PDF");
	this->SetPreconditions("At least one book must be open");
	this->SetCategories("sdk_snippet, sdk_architecture");
}

/* Destructor.
*/
_SnpRunnerExportBookAsPDF::~_SnpRunnerExportBookAsPDF()
{
	// Do nothing
}

/* Check if your preconditions are met.
*/
bool16	_SnpRunnerExportBookAsPDF::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {
		// Look for "some" open book file.
		InterfacePtr<IBookManager> bookManager(GetExecutionContextSession(), UseDefaultIID());
		if (bookManager == nil) 
		{ 
			break; 
		}
		if (bookManager->GetBookCount() <= 0)
		{
			break;
		}

		// if we got here, we can export a book
		result = kTrue;
	} while(false);
	return result;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerExportBookAsPDF::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		SnpExportBookAsPDF instance;
		InterfacePtr<IBookManager> bookManager(GetExecutionContextSession(), UseDefaultIID());
		if (bookManager == nil) 
		{ 
			ASSERT_FAIL("There is not book manager!");
			break; 
		}
		if (bookManager->GetBookCount() <= 0)
		{
			SNIPLOG("There is no book open. You must first open a book before running this snippet.");
			break;
		}

		// get parameters
		Utils<ISnipRunParameterUtils> parameterUtils;
		int32 defaultChoice = 0;
		PMString prompt("");

		// which book?
		K2Vector<PMString> bookNames = instance.GetBookNames(bookManager);
		prompt = "Which book do you want to export?";
		int32 bookChoice = parameterUtils->GetChoice(prompt, bookNames, defaultChoice);
		if (parameterUtils->WasDialogCancelled()) 
		{
			break;
		}

		// get book from index
		IBook* book = bookManager->GetNthBook(bookChoice);
		ASSERT(book);

		// what book content?
		bool16 exportAllDocsInBook = kTrue; // assume user wants all
		UIDList bookContentsToExport(::GetDataBase(book)); // TODO - correct database?
		InterfacePtr<IBookContentMgr> bookContentMgr(book, UseDefaultIID());
		if (bookContentMgr == nil) 
		{
			ASSERT_FAIL("This book doesn't have a book content manager!  Something is wrong.");
			break;
		}
		K2Vector<PMString> bookContentNames = instance.GetBookContentNames(bookContentMgr);
		prompt = "Which content do you want to export?";
		int32 lastContentIndex = bookContentNames.size() - 1;
		if (lastContentIndex < 0)
		{
			ASSERT_FAIL("This book doesn't have any content!");
			break;
		}

		// add the "ALL" choice.
		bookContentNames.push_back(PMString("<ALL>"));
		int32 bookContentChoice = parameterUtils->GetChoice(prompt, bookContentNames, lastContentIndex);
		if (parameterUtils->WasDialogCancelled()) 
		{
			break;
		}
		if (bookContentChoice <= lastContentIndex) 
		{
			// user wants specific book content to output
			UID bookContentUID = bookContentMgr->GetNthContent(bookContentChoice);
			ASSERT(bookContentUID != kInvalidUID);
			bookContentsToExport.Append(bookContentUID);
			exportAllDocsInBook = kFalse;
		}
		else
		{
			exportAllDocsInBook = kTrue;
		}
		// create a PDF filename for this book
		IDFile pdfFilename = instance.MakePDFFilename(book);


		// Now, deal with export styles
		
		// get current PDF export style index
		int32 defaultPDFExportStyle = instance.GetCurrentPDFExportStyle();
		if (defaultPDFExportStyle < 0) 
		{
			SNIPLOG("NOTE: No PDF export style is used yet!");
		}

		// get PDF export styles
		K2Vector<PMString> pdfExportStyles = instance.GetPDFExportStyles();
		if (!pdfExportStyles.empty())
		{
			if (defaultPDFExportStyle < 0 || defaultPDFExportStyle >= static_cast<int32>(pdfExportStyles.size()))
			{
				defaultPDFExportStyle = 0;
			}
			// set prompt
			prompt = "Which PDF export style do you want to use? (Current = " + pdfExportStyles[defaultPDFExportStyle] + ")";
			// get user choice
			int32 pdfExportStyleChoice = parameterUtils->GetChoice(prompt, pdfExportStyles, defaultPDFExportStyle);
			if (parameterUtils->WasDialogCancelled()) 
			{
				break;
			}
			if (pdfExportStyleChoice != defaultPDFExportStyle) 
			{
				// want to use different export style
				status = instance.SetPDFExportStyleByIndex(pdfExportStyleChoice);
				if (status != kSuccess) 
				{
					SNIPLOG("Could not set PDF export style to \"%s\".", 
							pdfExportStyles[pdfExportStyleChoice].GetPlatformString().c_str());  
					break;
				}
			}
		}

		// perform the export operation
		status = instance.ExportBookAsPDF(book, 
									   pdfFilename, 
									   bookContentsToExport, 
									   exportAllDocsInBook);

		SDKFileHelper bookFileHelper(pdfFilename);
		if (status == kSuccess)
		{
			SNIPLOG("Successfully exported book to \"%s\".", 
					bookFileHelper.GetPath().GetPlatformString().c_str());
		}
		else
		{
			SNIPLOG("ExportBookAsPDF failed!");
		}

	} while(false);
	return (status);
}

/* 
*/
bool16  _SnpRunnerExportBookAsPDF::CanLoad() const
{
	bool16 result = kTrue;
	if (LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS)) {
		// InCopy can't open books so the Go button for this
		// snippet would always be disabled.
		result = kFalse;
	}
	return result;
}

ErrorCode _SnpRunnerExportBookAsPDF::SetupContext(ISnpRunnableContext* runnableContext)
{
	ErrorCode errCode = kSuccess;

	//Set up a book!
	InterfacePtr<IBookManager> bookMgr( GetExecutionContextSession(), IID_IBOOKMANAGER ) ;
    int32 bookCount = bookMgr->GetBookCount();
	
	if (bookCount == 0)
	{
		IDFile bookFile;

		InterfacePtr<ICommand> bookCmd(CmdUtils::CreateCommand(kNewBookCmdBoss));
		InterfacePtr<IBookCmdData> bookCmdData(bookCmd, UseDefaultIID());
		
		bookCmdData->SetSysFile(bookFile);
		
		//bookCmd->SetName(PMString("New Book"));

		errCode = CmdUtils::ProcessCommand(bookCmd);
		if (errCode == kSuccess)
		{
			 if (bookCmd->GetItemList() != nil)
			 {
				


			 }
		}
	}

	return errCode;
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerExportBookAsPDF instance_SnpRunnerExportBookAsPDF;
DEFINE_SNIPPET(_SnpRunnerExportBookAsPDF) 	

// End, SnpExportBookAsPDF.cpp

