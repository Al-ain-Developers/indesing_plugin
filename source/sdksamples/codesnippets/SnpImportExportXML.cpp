//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpImportExportXML.cpp $
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

// interface includes
#include "IDocument.h"
#include "IIDXMLElement.h"
#include "IImportXMLData.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "IExportProvider.h"
#include "IPMUnknownData.h"
#include "ISelectionManager.h"
#include "ISnippetExport.h"

#include "ISnippetImport.h"
#include "ITableModel.h"
#include "IWorkspace.h"
#include "IXMLExportHandlerData.h"
#include "IXMLExportOptions.h"
#include "IXMLImportPreferences.h"
#include "IXMLImportOptions.h"
#include "IXMLImportOptionsPool.h"
#include "IXMLReferenceData.h"
#include "IXMLStreamUtils.h"
#include "IXMLStructureSuite.h"
#include "IXMLUtils.h"
// general includes
#include "StreamUtil.h"
#include "UIDList.h"	// This really is needed
#include "K2Vector.tpp"	// K2Vector<XMLReference> to link...
#include "PMRect.h"

#include "SnipRunLog.h"
#include "SDKFileHelper.h"
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "ISnipRunSuite.h"
#include "SnpXMLSampleHelper.h"

/** 
	\li How to export XML using service provider
	\li How to export directly from an individual element
	\li How to export XML elements as a Snippet
	\li How to import an XML file
	\li How to import an XML snippet.

	<h2>Exercising</h2>

	<h3>ExportViaServiceProvider</h3>
		-# Create a new document
		-# Run the snippet ImportExportXML
		-# Choose the option ExportViaServiceProvider.
		-# If all is well, there should be no asserts (if in debug build).
		-# You should see a message about a file being created.
		-# Save snippet runner log, grab the path to the file and open the file on your local system and inspect with XML-aware editor or text editor.
	<h3>ExportElement</h3>
		-# Create a new document
		-# Run the snippet ImportExportXML
		-# Choose the option ExportElement
		-# If all is well, there should be no asserts (if in debug build).
		-# You should see a message about a file being created.
		-# Save snippet runner log, grab the path to the file and open the file on your local system and inspect with XML-aware editor or text editor.
	<h3>ExportTable</h3>
		-# Create a new document
		-# Run the snippet ImportExportXML
		-# Choose the option ExportTable
		-# If all is well, there should be no asserts (if in debug build).
	<h3>ExportElementsAsSnippet</h3>
		-# Create a new document
		-# Run the snippet ImportExportXML
		-# Choose the option ExportElementsAsSnippet
		-# If all is well, there should be no asserts (if in debug build).
		-# You should see a message about a file being created.
		-# Save snippet runner log, grab the path to the file and open the file on your local system and inspect with XML-aware editor or text editor.
	<h3>Import</h3>
		-# Make sure you have already run ExportViaServiceProvider
		-# Create a new document
		-# Run the snippet ImportExportXML
		-# Choose the option Import
		-# If all is well, there should be no asserts (if in debug build).
		-# You should see new XML elements in the logical structure
	<h3>ImportXMLSnippetIntoRoot</h3>
		-# Make sure you have already run ExportElementsAsSnippet option
		-# Run the snippet ImportExportXML
		-# Create a new document
		-# Choose the option ImportXMLSnippetIntoRoot
		-# If all is well, there should be no asserts (if in debug build).
		-# You should see the content that was created on ExportElementsAsSnippet now imported at the root of the document
		-# Note that there will be document content as well as XML elements

		@ingroup sdk_snippet
		@ingroup sdk_xmedia
		@see  _SnpRunnerImportExportXML::Run for driver code

*/
class SnpImportExportXML {
public:


	/**	Export the logical structure of the given document to specified file as XML.
		@precondition documentUIDRef should allow IDocument to be instantiated
		@param documentUIDRef document of interest
		@param targetFile  file to which output should be written
		@return ErrorCode kSuccess on success, some other ErrorCode otherwise
	 */
	ErrorCode ExportViaServiceProvider(const UIDRef& documentUIDRef, const IDFile& targetFile);

	/**	Export only the supplied element to specified file as XML.
		@precondition xmlRef should allow IIDXMLElement to be instantiated
		@param xmlRef reference to element (IIDXMLElement) to export
		@param targetFile  file to which output should be written
		@return ErrorCode kSuccess on success, some other ErrorCode otherwise
	 */
	ErrorCode ExportElement(const XMLReference& xmlRef, const IDFile& targetFile, const PMString& formatName = "XML", UIFlags uiFlags = kSuppressUI);

	/**	Export a tagged table to specified file
		@precondition tableModelUIDRef should allow ITableModel to be instantiated
		@precondition table should be tagged, i.e. IXMLReferenceData should return XMLReference of element (IIDXMLElement) that can be instantiated
		@param tableModelUIDRef identifies table to export to specified file
		@param targetFile  file to which output should be written
		@return ErrorCode kSuccess on success, some other ErrorCode otherwise
	 */
	ErrorCode ExportTable(const UIDRef& tableModelUIDRef, const IDFile& targetFile);

	/**	Export the XML elements supplied as Snippet
		@param targetFile specifies the file to write to
		@param elements list of elements (IIDXMLElement) to export as Snippet
		@return ErrorCode kSuccess on success, some other ErrorCode otherwise
	 */
	ErrorCode ExportElementsAsSnippet(const IDFile& targetFile, const K2Vector<XMLReference>& elements);

	/**	Import an XML file into the document
		@precondition documentUIDRef should allow IDocument to be instantiated
		@param documentUIDRef specifies document into which to import
		@param targetFile XML data file to import
		@param xmlReferenceWhere kInvalidXMLReference to import into the root, since this can legitimately be kInvalidXMLReference, we require documentUIDRef
		@return ErrorCode kSuccess on success, some other ErrorCode otherwise
	 */
	ErrorCode Import(const UIDRef& documentUIDRef, const IDFile& targetFile, const XMLReference& xmlReferenceWhere);

	
	/**	Import a set of XML elements from a Snippet file, which should be set up
		by ExportElementsAsSnippet.
		@precondition documentUIDRef should allow IDocument to be instantiated
		@param documentUIDRef document into which
		@param targetFile specifies the Snippet file to import
		@return ErrorCode kSuccess on success, some other ErrorCode otherwise
	 */
	ErrorCode ImportXMLSnippetIntoRoot(const UIDRef& documentUIDRef, const IDFile& targetFile);


};

/*
*/
ErrorCode SnpImportExportXML::ExportViaServiceProvider(const UIDRef& documentUIDRef, const IDFile& targetFile)
{
	ErrorCode err = kFailure;
	do {
		// +precondition
		InterfacePtr<IDocument> document(documentUIDRef, UseDefaultIID());
		ASSERT(document);
		if(!document) {
			break;
		}
		// -precondition
		InterfacePtr<IK2ServiceRegistry> serviceRegistry(GetExecutionContextSession(), UseDefaultIID());
		ASSERT(serviceRegistry);
		InterfacePtr<IK2ServiceProvider> serviceProvider
			(serviceRegistry->QueryServiceProviderByClassID(kExportProviderService, kXMLExportProviderBoss));
		ASSERT(serviceProvider);
		if(!serviceProvider) {
			break;
		}
		InterfacePtr<IExportProvider> exportProvider(serviceProvider, UseDefaultIID());
		ASSERT(exportProvider);
		if(!exportProvider) {
			break;
		}
		PMString formatName("XML");
		if(exportProvider->CanExportThisFormat( document, nil, formatName ))
		{
			// We found the appropriate provider, now we can export
			InterfacePtr<IPMStream> stream(StreamUtil::CreateFileStreamWrite(targetFile, kOpenOut|kOpenTrunc, 'TEXT', 'CWIE'));
			ASSERT(stream);
			if(!stream) {
				break;
			}
			stream->Open();
			if (stream->GetStreamState() != kStreamStateGood)
			{
				stream->Close();
				break;
			}
			exportProvider->ExportToStream(stream, document, nil, formatName, kSuppressUI);		
			stream->Flush();
			stream->Close();
			// Assume that failure is signalled by export provider
			err = ErrorUtils::PMGetGlobalErrorCode();
		}
		
	} while(kFalse);
	return err;
}

/*
*/
ErrorCode SnpImportExportXML::ExportElement(const XMLReference& xmlRef, const IDFile& targetFile, const PMString& formatName, UIFlags uiFlags)
{
	ErrorCode err = kFailure;
	do {
		// +Preconditions
		IDataBase* database = xmlRef.GetDataBase();
		UIDRef documentUIDRef(database, database->GetRootUID());
		InterfacePtr<IDocument> document(documentUIDRef, UseDefaultIID());
		ASSERT(document);
		if(!document) {
			break;
		}

		InterfacePtr<IIDXMLElement> element(xmlRef.Instantiate());
		ASSERT(element);
		if(!element) {
			break;
		}
		// -preconditions
		// we can use IXMLUtils::ExportElement and specify the reference of the element to
		// export from.
		// Locate XML parser service to get IXMLAccess (visitor pattern).
		InterfacePtr<IK2ServiceRegistry> serviceRegistry(GetExecutionContextSession(), UseDefaultIID());
		ASSERT(serviceRegistry);
		InterfacePtr<IK2ServiceProvider> xmlParserServiceProvider
			(serviceRegistry->QueryServiceProviderByClassID(kXMLParserService, 
					kXMLParserServiceBoss));
		ASSERT(xmlParserServiceProvider);
		if(!xmlParserServiceProvider) {
			break;
		}
		InterfacePtr<IXMLAccess> access(xmlParserServiceProvider, UseDefaultIID());
		ASSERT(access);
		if(!access) {
			break;
		}
		// Create instance of class with IXMLHandler interface
		// EXTENSION POINT: subclass kXMLExportHandlerBoss and implement
		// your own IXMLHandler to customize XML Export, for instance, to
		// replace the way that IXMLGenerator works for elements associated to
		// stories (kTextStoryBoss) with your own IMyXMLGenerator added in to
		// kTextXMLElementBoss, say
		InterfacePtr<IXMLHandler> xmlExportHandler(
			CreateObject2<IXMLHandler>(kXMLExportHandlerBoss));
		ASSERT(xmlExportHandler);
		if(!xmlExportHandler) {
			break;
		}
	
		InterfacePtr<IXMLExportHandlerData> handlerData(xmlExportHandler, UseDefaultIID());
		ASSERT(handlerData);
		if(!handlerData) {
			break;
		}
		// Determine current setting of encoding
		InterfacePtr<IXMLExportOptions> xmlExportOptions(document->GetDocWorkSpace(), UseDefaultIID());
		ASSERT(xmlExportOptions);
		if(!xmlExportOptions) {
			break;
		}
		// Must have the stream ... although we pass a IDFile to the method,
		// we need to set up the stream. This is something to do with image conversion.
		InterfacePtr<IXMLOutStream> xmlStream(
			Utils<IXMLStreamUtils>()->CreateXMLOutFileStream(targetFile, 
				xmlExportOptions->GetEncodingType()));

		handlerData->SetStream(xmlStream);
		err = Utils<IXMLUtils>()->ExportElement(element, 
			kTrue, 
			access, 
			xmlExportHandler, 
			targetFile, 
			document,
			formatName,
			uiFlags); 
		xmlStream->Close();
		ASSERT(err == kSuccess);
		
	} while(kFalse);
	return err;
}




ErrorCode SnpImportExportXML::ExportTable(
									const UIDRef& tableModelUIDRef,
									const IDFile& targetFile)
{
	ErrorCode err = kFailure;
	
	do {
		IDataBase* database = tableModelUIDRef.GetDataBase();
		InterfacePtr<IDocument> document( UIDRef(database, database->GetRootUID()), 
											UseDefaultIID());
		ASSERT(document);
		if(!document) {
			break;
		}
		// To do this, we need to follow up the IXMLReferenceData
		// which gets us to the kTextXMLElementBoss that is associated with
		// a tagged table (kTableModelBoss)
		InterfacePtr<ITableModel> tableModel(tableModelUIDRef, UseDefaultIID());
		ASSERT(tableModel);
		if(!tableModel) {
			break;
		}
		
		InterfacePtr<IXMLReferenceData> xmlReferenceData(tableModel, UseDefaultIID());
		ASSERT(xmlReferenceData);
		if(!xmlReferenceData) {
			break;
		}
		XMLReference tableXMLReference = xmlReferenceData->GetReference();
		SnpXMLHelper xmlHelper;
		SNIPLOG("tableXMLReference: %s", (xmlHelper.AsString(tableXMLReference)).GetPlatformString().c_str());
		InterfacePtr<IIDXMLElement> tableElement(tableXMLReference.Instantiate());
		ASSERT(tableElement);
		if(!tableElement) {
			break;
		}
		err = this->ExportElement(tableXMLReference, targetFile);
		ASSERT(err == kSuccess);
	} while(kFalse);
	return err;
}




/*
*/
ErrorCode SnpImportExportXML::ExportElementsAsSnippet(const IDFile& targetFile, 
														const K2Vector<XMLReference>& elements)
{
	ErrorCode err = kFailure;
	do {
		ASSERT(elements.size()>0);
		InterfacePtr<IPMStream> stream(StreamUtil::CreateFileStreamWrite(targetFile, kOpenOut|kOpenTrunc, 'TEXT', 'CWIE'));
		ASSERT(stream);
		if(!stream) {
			break;
		}
		stream->Open();
		if (stream->GetStreamState() == kStreamStateGood)
		{
			stream->SetEndOfStream();
			err = Utils<ISnippetExport>()->ExportXMLElements(stream, elements);
			stream->Flush();
			ASSERT(err == kSuccess);

		}
		stream->Close();
	} while(kFalse);
	return err;
}


/*
*/
ErrorCode SnpImportExportXML::Import(const UIDRef& documentUIDRef, const IDFile& targetFile, const XMLReference& xmlReferenceWhere)
{
	ErrorCode err = kFailure;
	do {
		// +precondition
		InterfacePtr<IDocument> document(documentUIDRef, UseDefaultIID());
		ASSERT(document);
		if(!document) {
			break;
		}
		// -precondition
		
		InterfacePtr<ICommand> importCmd(CmdUtils::CreateCommand(kImportXMLFileCmdBoss));
		ASSERT(importCmd);
		InterfacePtr<IImportXMLData> importXMLData(CreateObject2<IImportXMLData>(kImportXMLDataBoss));
		ASSERT(importXMLData);
		if(!importXMLData) {
			break;
		}
		importXMLData->Set(documentUIDRef.GetDataBase(), targetFile, xmlReferenceWhere, kSuppressUI);
		InterfacePtr<IXMLImportOptions> docXMLOptions( document->GetDocWorkSpace(), UseDefaultIID() );
		ASSERT(docXMLOptions);
		if(!docXMLOptions) {
			break;
		}
		InterfacePtr<IXMLImportOptions> importXMLOptions(importXMLData, UseDefaultIID());
		ASSERT(importXMLOptions);
		if(!importXMLOptions) {
			break;
		}
		importXMLOptions->Copy(docXMLOptions);

		InterfacePtr<IPMUnknownData> pmUnknownData(importCmd, UseDefaultIID());
		ASSERT(pmUnknownData);
		if(!pmUnknownData) {
			break;
		}
		pmUnknownData->SetPMUnknown(importXMLData);

		err = CmdUtils::ProcessCommand(importCmd);
		ASSERT(err==kSuccess);
	} while(kFalse);
	return err;
}



/*
*/
ErrorCode SnpImportExportXML::ImportXMLSnippetIntoRoot(const UIDRef& documentUIDRef, const IDFile& targetFile)
{
	ErrorCode err= kFailure;
	do {
		// + precondition
		InterfacePtr<IDocument> document(documentUIDRef, UseDefaultIID());
		ASSERT(document);
		if(!document) {
			break;
		}
		SDKFileHelper targetFileHelper(targetFile);
		ASSERT(targetFileHelper.IsExisting());
		// -preconditions

		InterfacePtr<IPMStream> stream(static_cast<IPMStream*>(
			StreamUtil::CreateFileStreamRead(targetFile, kOpenIn)));
		ASSERT(stream);
		if(!stream) {
			break;
		}
		InterfacePtr<IDOMElement> rootDOMElement(documentUIDRef, UseDefaultIID());
		ASSERT(rootDOMElement);
		if(!rootDOMElement) {
			break;
		}
		err = Utils<ISnippetImport>()->ImportFromStream(stream, rootDOMElement);
		
	} while(kFalse);
	return err;
}

//------------ SNIPPET RUNNER FRAMEWORK HOOK CODE BELOW ----------------------------------------------------------------------------------------

/** Makes the snippet SnpImportExportXML available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerImportExportXML : public SnpRunnable
{
	public:
		/** This constructor describes your snippet to the framework.
		 */
		_SnpRunnerImportExportXML();

		/** Destructor.
		 */
		virtual			~_SnpRunnerImportExportXML();

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
};

/* Describe your snippet to the framework here.
*/
_SnpRunnerImportExportXML::_SnpRunnerImportExportXML() : SnpRunnable("ImportExportXML")
{
	this->SetDescription("Import/ export of XML");
	this->SetPreconditions("open document");
	this->SetCategories("sdk_snippet, sdk_xmedia");
}

/* Destructor.
*/
_SnpRunnerImportExportXML::~_SnpRunnerImportExportXML()
{
}

/* Check if your snippet's preconditions are met here.
*/
bool16	_SnpRunnerImportExportXML::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {
		ASSERT(runnableContext->GetActiveContext()); 
		IDocument* document = runnableContext->GetActiveContext()->GetContextDocument();
		return document != nil;
	} while(false);
	return result;
}

/* Set up and call your snippet here.
*/
ErrorCode _SnpRunnerImportExportXML::Run(ISnpRunnableContext* snpRunContext)
{
	SNIPLOG("\n--- Start SnpImportExportXML::Run ---");
	// If no action was chosen that we recognise, this is effectively a Cancel operation
	ErrorCode err = kCancel;
	IActiveContext* activeContext = snpRunContext->GetActiveContext();
	UIDRef documentUIDRef = ::GetUIDRef(activeContext->GetContextDocument());
	SnpImportExportXML instance;
	SnpXMLSampleHelper xmlHelper;
	do {

		PMString exportVia("ExportViaServiceProvider");
		PMString exportElement("ExportElement");
		PMString exportTable("ExportTable");
		PMString exportSnippet("ExportElementsAsSnippet");
		PMString import("Import");
		PMString importTable("ImportTable");
		PMString importSnippet("ImportXMLSnippetIntoRoot");


		K2Vector<PMString> choices;
		choices.push_back(exportVia); //0
		choices.push_back(exportElement); //1
		choices.push_back(exportTable); //2
		choices.push_back(exportSnippet); //3
		choices.push_back(import); //4
		choices.push_back(importTable); //5
		choices.push_back(importSnippet); //6
		choices.push_back(PMString("UnitTest")); //7
		
		Utils<ISnipRunParameterUtils> parameterUtils;
		int32 choice = parameterUtils->GetChoice(PMString("What action?"), choices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		switch(choice) {
			case 0:
			{
				SNIPLOG("ExportViaServiceProvider");
			
				IDFile sysNoSelectionFile = xmlHelper.GetSampleFile("-no-sel.xml");
				// Create some content to export
				PMRect rect;
				xmlHelper.GetNextRect(rect);
				UIDRef textModelUIDRef = xmlHelper.CreateStoryThroughFrame(documentUIDRef,rect,0,0);
				xmlHelper.CreateSampleTaggedStory(textModelUIDRef);
				xmlHelper.SetExportFromSelected(
					::GetUIDRef(activeContext->GetContextWorkspace()),kFalse);
				err = instance.ExportViaServiceProvider(documentUIDRef, sysNoSelectionFile);
				ASSERT(err == kSuccess);
				SDKFileHelper file2Helper(sysNoSelectionFile);
				SNIPLOG("This scenario created XML file; %s",
					file2Helper.GetPath().GetPlatformString().c_str());

			} 
			break;

			case 1:
			{
				SNIPLOG("ExportElement");
			
				PMRect rect;
				xmlHelper.GetNextRect(rect);
				UIDRef textModelRef;
				UIDRef tableUIDRef;
				err = xmlHelper.CreateTableThroughFrame(documentUIDRef, rect, tableUIDRef, textModelRef);
				ASSERT(err == kSuccess);
				
				err = xmlHelper.TagStory(textModelRef, PMString("Story"));
				ASSERT(err == kSuccess);
				
				XMLReference tableXMLRef;
				err = xmlHelper.TagTable(tableUIDRef, PMString("Table"), PMString("cell"),tableXMLRef);
				ASSERT(err == kSuccess);
				
				IDFile sysFile = xmlHelper.GetSampleFile("-root-elem.xml");
				err = instance.ExportElement(xmlHelper.GetRootXMLReference(documentUIDRef), 
										sysFile );
				
				ASSERT(err == kSuccess);
				
				SDKFileHelper fileHelper(sysFile);
				SNIPLOG("\nThis scenario exported the root element and its dependents to %s", fileHelper.GetPath().GetPlatformString().c_str()); 
			}
			break;

			case 2:
			{
				
				SNIPLOG("ExportTable");
				PMRect rect;
				
				xmlHelper.GetNextRect(rect);
				UIDRef textModelRef;
				UIDRef tableUIDRef;
				err = xmlHelper.CreateTableThroughFrame(documentUIDRef, rect, tableUIDRef, textModelRef);
				ASSERT(err == kSuccess);
				err = xmlHelper.TagStory(textModelRef, PMString("Story"));
				ASSERT(err == kSuccess);
				XMLReference tableXMLRef;
				err = xmlHelper.TagTable(tableUIDRef, PMString("Table"), PMString("cell"),tableXMLRef);
				ASSERT(err == kSuccess);
				IDFile sysFile = xmlHelper.GetSampleFile("-table.xml");
				err = instance.ExportTable(tableUIDRef, sysFile );
				ASSERT(err == kSuccess);
				SDKFileHelper fileHelper(sysFile);
				SNIPLOG("\nThis scenario created and tagged a table, and exported only the table to file %s", fileHelper.GetPath().GetPlatformString().c_str()); 
			} 
			break;


			case 3:
			{
				SNIPLOG("ExportElementsAsSnippet");
			
				InterfacePtr<IIDXMLElement> rootElement(Utils<IXMLUtils>()->QueryRootElement(documentUIDRef.GetDataBase()));
				ASSERT(rootElement);
				
				K2Vector<XMLReference> elements;
				elements.push_back(rootElement->GetXMLReference());
				IDFile sysFile2 = xmlHelper.GetSampleFile("-elem.inds");
				err = instance.ExportElementsAsSnippet(sysFile2, elements);
				 
				SNIPLOG("\nThis scenario exported an XML snippet based on an XML element");

			}
			break;

			case 4:
			{
				SNIPLOG("Import");
				IDFile sysNoSelectionFile = xmlHelper.GetSampleFile("-no-sel.xml");
				SDKFileHelper fileHelper(sysNoSelectionFile);
				bool16 fileExists = fileHelper.IsExisting();
				if(!fileExists) {
					SNIPLOG("ERROR: file to import does not yet exist; create by ExportViaServiceProvider");
					break;
				}
				// We're hoping that export scenario has created this sample file already
				// If not we will fail
				err = instance.Import(documentUIDRef, sysNoSelectionFile, kInvalidXMLReference);
				ASSERT(err == kSuccess);
				
				SNIPLOG("\nThis scenario attempted to import XML file created by prior export into the logical structure");
			}
			break;

			case 5:
			{
				SNIPLOG("ImportTable");
				PMRect rect;
				xmlHelper.GetNextRect(rect);
				UIDRef textModelRef = xmlHelper.CreateStoryThroughFrame(documentUIDRef,rect,0,0);
				err = xmlHelper.TagStory(textModelRef, PMString("Story"));
				ASSERT(err == kSuccess);
				IDFile sysFile = xmlHelper.GetSampleFile("-table.xml");
				SDKFileHelper fileHelper(sysFile);
				bool16 fileExists = fileHelper.IsExisting();
				if(!fileExists) {
					SNIPLOG("ERROR: file to import does not yet exist; create by ExportTable");
					break;
				}
				// get XML element into which to import this table
				InterfacePtr<IXMLReferenceData> xmlReferenceData(textModelRef, UseDefaultIID());
				ASSERT(xmlReferenceData);
				err = instance.Import(documentUIDRef, sysFile, xmlReferenceData->GetReference());
				ASSERT(err == kSuccess);
				SNIPLOG("This scenario created a tagged story, and imported a file %s into it, which should have been created with snippet to export table.",
					fileHelper.GetPath().GetPlatformString().c_str());
			}
			break;

		

			case 6:
			{
				SNIPLOG("ImportXMLSnippetIntoRoot");
				IDFile sysFile2 = xmlHelper.GetSampleFile("-elem.inds");
				SDKFileHelper fileHelper(sysFile2);
				bool16 fileExists = fileHelper.IsExisting();
				if(!fileExists) {
					SNIPLOG("ERROR: file to import does not yet exist; create by ExportElementsAsSnippet");
						break;
				}
				err = instance.ImportXMLSnippetIntoRoot(documentUIDRef, sysFile2);
				ASSERT(err == kSuccess);
				SNIPLOG("\nThis scenario attempted to import an XML snippet created by prior export (%s) into the root of the logical structure",
					fileHelper.GetPath().GetPlatformString().c_str());
			}
			break;

			case 7:
			{
				PMString snippetName("ImportExportXML");
				InterfacePtr<ISnipRunSuite> suite(activeContext->GetContextSelection(), UseDefaultIID());
				ASSERT(suite);
				if (!suite)
					break;

				if (suite->CanRun(snippetName))
				{
					// Check names above]
					suite->Run(snippetName, exportVia);
					suite->Run(snippetName, exportElement);
					suite->Run(snippetName, exportTable);
					suite->Run(snippetName, exportSnippet);
					suite->Run(snippetName, import);
					suite->Run(snippetName, importTable);
					suite->Run(snippetName, importSnippet);
					
					// If we got here without crashes or asserts, consider
					// that a success
					err = kSuccess;
				} else {
					SNIPLOG("Can't run snippet self");
				}
			}
			break;


		} // end of switch
		 
	} while(kFalse);

	SNIPLOG("--- End SnpImportExportXML::Run ---\n");

	return err;
}


/*	Declare an instance to register the snippet hook with the framework.
*/
static _SnpRunnerImportExportXML instance_SnpRunnerImportExportXML;
DEFINE_SNIPPET(_SnpRunnerImportExportXML) 	
