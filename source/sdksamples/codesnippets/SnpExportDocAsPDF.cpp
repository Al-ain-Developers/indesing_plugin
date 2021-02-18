//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpExportDocAsPDF.cpp $
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
#include "IApplication.h"
#include "IDocumentList.h"
#include "ISelectionUtils.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "IExportProvider.h"
#include "ISession.h"

// General includes:
#include "FileTypeRegistry.h"
#include "FileUtils.h"
#include "IDFile.h"
#include "K2Vector.h"
#include "Utils.h"
#include "SDKFileHelper.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/** \li	Exports a document to a PDF.
 * 
 * 	This snippet shows how to use the PDF export service provider
 * 	to export a document to interactive or print PDF. 
 * 
 * 	@ingroup sdk_snippet
 * 	@ingroup sdk_export
 * 	@ingroup sdk_layout
 * 	@ingroup sdk_graphic
 *
 * 	@see IExportProvider
 */
class SnpExportDocAsPDF 
{
public:
	/** Constructor.
	 */
	SnpExportDocAsPDF() {}

	/** Destructor.
	 */
	virtual	~SnpExportDocAsPDF() {}

	/** Exports a document as interactive or print PDF.
	 * 	This method wraps the the PDF export service provider.
	 *
	 * 	@param doc IN The document to export.
	 * 	@param pdfFileName IN The IDFile to which you want to export.
	 * 	@param pdfFileFormat IN The PDF file format - interactive or print.
	 *
	 * 	@return kSuccess on success, other ErrorCode otherwise.
	 *
	 * 	@see IDocument
	 * 	@see IExportProvider
	 */
	ErrorCode ExportDocAsPDF(IDocument* doc,
							const IDFile& pdfFileName,
							const PMString& pdfFileFormat);

	/** Choose a PDF filename (IDFile) to save the document, based on the document's filename.
	 * 	@param chosenFile    OUT The file to save.
	 *  @param pdfFileFormat OUT The PDF file format - interactive or print.
	 * 	@return kSuccess if success, kFailure otherwise.
	 * 	@see SDKFileSaveChooser
	 */
	ErrorCode ChooseSaveLocation(IDFile& chosenFile, PMString& pdfFileFormat);

	/** Gets the names of documents currently available.
	 * 	@param docList IN The session's document list.
	 * 	@return A list of PMStrings containing names of documents that are currently open.
	 */
	K2Vector<PMString> GetDocNames(IDocumentList* docList);

};

ErrorCode SnpExportDocAsPDF::ExportDocAsPDF(IDocument* doc, 
											const IDFile& pdfFileName, 
											const PMString& pdfFileFormat)
{
	ErrorCode status = kFailure;

	do {
		SDKFileHelper fileHelper(pdfFileName);
		if (doc == nil || fileHelper.GetPath().empty())
		{ 
			ASSERT_FAIL("One or more preconditions are not met - exiting");
			break; 
		} 

		InterfacePtr<ISelectionManager> selection(Utils<ISelectionUtils>()->QueryActiveSelection());
		
		InterfacePtr<IK2ServiceRegistry> k2ServiceRegistry(GetExecutionContextSession(), UseDefaultIID());
		// Look for all service providers with kExportProviderService.
		int32 exportProviderCount = k2ServiceRegistry->GetServiceProviderCount(kExportProviderService);
		// Iterate through them.
		for (int32 i = 0; i < exportProviderCount; i++)
		{
			// get the service provider boss class
			InterfacePtr<IK2ServiceProvider> k2ServiceProvider
				(k2ServiceRegistry->QueryNthServiceProvider(kExportProviderService,	i));
			// Get the export provider implementation itself.
			InterfacePtr<IExportProvider> exportProvider(k2ServiceProvider, IID_IEXPORTPROVIDER);
			// Check to see if the current selection specifier can be exported by this provider.
			bool16 canExportByTarget = exportProvider->CanExportThisFormat(doc, selection, pdfFileFormat);
			if (canExportByTarget)
			{
				// assume pdfFileName is a valid IDFile to hold the soon to be created PDF
				exportProvider->ExportToFile(pdfFileName, doc, selection, pdfFileFormat, kFullUI);
				status = kSuccess;
				break;
			}
		}

	} while (false);

	return status;
}

ErrorCode SnpExportDocAsPDF::ChooseSaveLocation(IDFile& chosenFile, PMString& pdfFileFormat)
{
	ErrorCode result = kCancel;	

	K2Vector<PMString> fileFormats;
	fileFormats.push_back(PMString("Adobe PDF (Interactive)"));
	fileFormats.push_back(PMString("Adobe PDF (Print)"));

	SDKFileSaveChooser fileChooser;
	SysOSType macFileCreator = FileTypeRegistry::GetCurrentFileCreator(kPublicationFileTypeInfoID);
	for(int32 i = 0; i < fileFormats.size(); i++)
	{
		fileChooser.AddFilter(macFileCreator, 'PDF ', "pdf", fileFormats.at(i));
	}

	fileChooser.ShowDialog();
	if (!fileChooser.IsChosen()) 
	{
		return result;
	}

	// Return the chosen file and format to the caller.
	chosenFile = fileChooser.GetIDFile();

	int32 filterIndex = fileChooser.GetFilterIndex();
	if (filterIndex < 0 || filterIndex >= fileFormats.size())
	{
		filterIndex = 0;
	}
	pdfFileFormat = fileFormats.at(filterIndex);

	result = kSuccess;
	return result;
}

K2Vector<PMString> SnpExportDocAsPDF::GetDocNames(IDocumentList* docList)
{
	K2Vector<PMString> docNames;
	docNames.clear();

	do {
		if (docList == nil) 
		{
			ASSERT(docList);
			break;
		}
		int32 docCount = docList->GetDocCount();
		for (int32 i = 0; i < docCount; i++) 
		{
			IDocument* doc = docList->GetNthDoc(i);
			if (doc == nil) 
			{
				continue; // go onto the next doc
			}
			// get the doc name
			PMString docName;
			doc->GetName(docName);
			ASSERT(docName.empty() == kFalse);
			docNames.push_back(docName);
		}
	} while (false);

	return docNames;
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

/** Makes the snippet SnpExportDocAsPDF available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerExportDocAsPDF : public SnpRunnable
{
public:
	// SnippetRunner framework hooks.

	/** Constructor.
	 */
	_SnpRunnerExportDocAsPDF(void);

	/** Destructor.
	 */
	virtual	~_SnpRunnerExportDocAsPDF(void);

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

	/** get the snippet context
		@return eSnpRunContextType for this snippet
	*/
	virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunCustomContext;}

	/** Set up the proper context for the snippert.
		@param runnableContext
		@return kSuccess on success, other ErrorCode otherwise
	*/
	virtual ErrorCode SetupContext(ISnpRunnableContext* runnableContext);

};

/* Constructor.
*/
_SnpRunnerExportDocAsPDF::_SnpRunnerExportDocAsPDF() : SnpRunnable("ExportDocAsPDF")
{
	this->SetDescription("Exports a document to PDF");
	this->SetPreconditions("At least one document must be open");
	this->SetCategories("sdk_snippet, sdk_architecture");
}

/* Destructor.
*/
_SnpRunnerExportDocAsPDF::~_SnpRunnerExportDocAsPDF()
{
	// Do nothing
}

/* Check if your preconditions are met.
*/
bool16 _SnpRunnerExportDocAsPDF::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {
		// get the application object for the session
		InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
		if (app == nil)
		{
			break;
		}

		// get the document list for the application
		InterfacePtr<IDocumentList> docList(app->QueryDocumentList());
		if (docList == nil || docList->GetDocCount() <= 0) 
		{ 
			break; 
		}

		// if we got here, we can export a document
		result = kTrue;
	} while(false);
	return result;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerExportDocAsPDF::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		SnpExportDocAsPDF instance;

		// get the application object for the session
		InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
		if (app == nil)
		{
			break;
		}

		// get the document list for the application
		InterfacePtr<IDocumentList> docList(app->QueryDocumentList());
		if (docList == nil || docList->GetDocCount() <= 0) 
		{ 
			SNIPLOG("There is no document open. You must first open a document before running this snippet.");
			break;
		}

		// which doc to export?
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> docNames = instance.GetDocNames(docList);
		PMString prompt = "Which document do you want to export?";
		int32 docChoice = parameterUtils->GetChoice(prompt, docNames, 0);
		if (parameterUtils->WasDialogCancelled()) 
		{
			break;
		}

		// get doc
		IDocument* doc = docList->GetNthDoc(docChoice);
		ASSERT(doc);

		// create a PDF filename for this doc
		IDFile pdfFilename;
		PMString pdfFileFormat;
		status = instance.ChooseSaveLocation(pdfFilename, pdfFileFormat);

		// perform the export operation
		status = instance.ExportDocAsPDF(doc, pdfFilename, pdfFileFormat);

		SDKFileHelper fileHelper(pdfFilename);
		if (status == kSuccess)
		{
			SNIPLOG("Successfully exported document to \"%s\".", 
					fileHelper.GetPath().GetPlatformString().c_str());
		}
		else
		{
			SNIPLOG("ExportDocAsPDF failed!");
		}

	} while(false);
	return (status);
}

/* 
*/
bool16 _SnpRunnerExportDocAsPDF::CanLoad() const
{
	bool16 result = kTrue;
	if (LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS)) {
		// This snippet is not for InCopy.
		result = kFalse;
	}
	return result;
}

ErrorCode _SnpRunnerExportDocAsPDF::SetupContext(ISnpRunnableContext* runnableContext)
{
	return kSuccess;
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerExportDocAsPDF instance_SnpRunnerExportDocAsPDF;
DEFINE_SNIPPET(_SnpRunnerExportDocAsPDF) 	

// End, SnpExportDocAsPDF.cpp
