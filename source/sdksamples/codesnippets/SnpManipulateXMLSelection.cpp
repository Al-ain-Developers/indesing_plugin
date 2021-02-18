//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpManipulateXMLSelection.cpp $
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
#include "IDocument.h"
#include "IIDXMLElement.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "ISelectionManager.h" // We're querying suite interfaces off IActiveContext::GetContextSelection()
#include "ISnippetExportSuite.h"
#include "IStringData.h"
#include "ITableModel.h"
#include "IWorkspace.h"
#include "IXMLExportHandlerData.h"
#include "IXMLNodeTarget.h"
#include "IXMLStreamUtils.h"
#include "IXMLStructureSuite.h"
#include "IXMLTagSuite.h"
#include "IXMLUtils.h"
#include "IXMLValidator.h"
// General includes:
#include "XMLDTDValidationError.h"
#include "StreamUtil.h"
// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"
#include "SDKFileHelper.h"
#include "SnpXMLSampleHelper.h"

/** Manipulates properties of an XML selection, 
	nodes selected in the structure view.

	@ingroup sdk_snippet
	@ingroup sdk_xmedia
*/
class SnpManipulateXMLSelection {
public:


	/**	Attempt to create attributes for selected node(s)
		@param selectionManager reference to the abstract selection
		@param attribName name of attribute
		@param attribValue value to assign to newly created attribute
		@return ErrorCode kSuccess on success, kFailure otherwise
	 */
	ErrorCode CreateAttributesInSelection(ISelectionManager* selectionManager, 
									const PMString& attribName,
									const PMString& attribValue);


	/**	Attempt to create a comment (kXMLCommentBoss) parented by selected node(s)
		@param selectionManager reference to the abstract selection
		@param commentText 
		@return ErrorCode kSuccess on success, other ErrorCode otherwise
	 */
	ErrorCode CreateCommentInSelection(ISelectionManager* selectionManager,
											const PMString& commentText);


	/**	Attempt to create elements  parented by selected node(s)
		@param selectionManager reference to the abstract selection
		@param tagUIDRef 
		@param numElements 
	@return ErrorCode kSuccess on success, other ErrorCode otherwise
		 */
	ErrorCode CreateElementsInSelection(ISelectionManager* selectionManager,
											const UIDRef& tagUIDRef,
											int32 numElements);


	/**	Attempt to create a processing instruction parented by selected node(s)
		@param selectionManager reference to the abstract selection
		@param piKey 
		@param piValue 
	@return ErrorCode kSuccess on success, other ErrorCode otherwise
		 */
	ErrorCode CreateProcessingInstructionInSelection(ISelectionManager* selectionManager, 
											const PMString& piKey, 
											const PMString& piValue);



	/**	Export the selected node(s) as Snippet
		@param selectionManager reference to the abstract selection
		@param targetFile 
	@return ErrorCode kSuccess on success, other ErrorCode otherwise
		 */
	ErrorCode ExportXMLSnippetFromSelection(ISelectionManager* selectionManager, 
											const IDFile& targetFile);


	/**	Export selected node(s) as XML
		@param selectionManager reference to the abstract selection
		@param targetFile 
		@return ErrorCode kSuccess on success, other ErrorCode otherwise
	*/
	ErrorCode ExportFromSelection(ISelectionManager* selectionManager, 
									const IDFile& targetFile);
	

	/**	Attempt to import specified XML data file into logical structure to be
		parented by selected node. If multiple nodes selected, then
		top level element(s) in imported content becomes peers of selected nodes.

		@param selectionManager reference to the abstract selection
		@param database document's database into which to import 
			(NB: the API used is slightly at variance with abstract selection model) 
		@param targetFile 
		@return ErrorCode kSuccess on success, other ErrorCode otherwise
	 */
	ErrorCode ImportIntoSelection(ISelectionManager* selectionManager, 
											IDataBase* database,
											const IDFile& targetFile);


	/**	Attempt to validate selected node(s) against associated DTD
		
		@precondition DTD must be associated with doc
		@param selectionManager reference to the abstract selection
		@param xmlValidator 
			(NB: the API used is slightly at variance with abstract selection model) 
		@return ErrorCode kSuccess on success, other ErrorCode otherwise
	 */
	ErrorCode ValidateFromSelection(ISelectionManager* selectionManager, IXMLValidator* xmlValidator);

};



/*
*/
ErrorCode SnpManipulateXMLSelection::CreateElementsInSelection(ISelectionManager* selectionManager, 
																const UIDRef& tagUIDRef,
																int32 numElements)
{
	ErrorCode err = kFailure;
	do {
			// + preconditions 
		ASSERT(selectionManager);
			if (!selectionManager) {
			break;
		}
		
		InterfacePtr<IXMLStructureSuite> xmlStructureSuite(selectionManager, UseDefaultIID());
		ASSERT(xmlStructureSuite);
		if(!xmlStructureSuite) {
			SNIPLOG("IXMLStructureSuite nil, FAILED: CURRENTLY DEPENDS ON SELECTION IN STRUCTURE_VIEW");
			break;
		}
		if(!xmlStructureSuite->CanAddElement ()) {
			SNIPLOG("Couldn't add element: IXMLStructureSuite::CanAddElement false");
			SNIPLOG("Is there a unique node selection in the structure-view?");
			break;
		}
		// - preconditions 
		
		for(int32 i=0; i < numElements; i++) {
			// I'm retesting this condition as we're changing underlying model state
			if(xmlStructureSuite->CanAddElement ()) {
				err = xmlStructureSuite->AddElement(tagUIDRef);
				ASSERT(err == kSuccess);
				if(err != kSuccess) {
					break;
				}
			} else {
				SNIPLOG("CanAddElement failed in loop");
				break;
			}
				
		}
		
		// Postcondition: numElements were created successfully with selected node
		// as parent
		ASSERT(err == kSuccess);
	} while(kFalse);
	return err;
}

/*
*/
ErrorCode SnpManipulateXMLSelection::CreateAttributesInSelection(ISelectionManager* selectionManager, 
									const PMString& attribName,
									const PMString& attribValue)
{
	ErrorCode err = kFailure;
	do {
		ASSERT(selectionManager);
		if(!selectionManager) {
			break;
		}
		InterfacePtr<IXMLStructureSuite> xmlStructureSuite(selectionManager, UseDefaultIID());

		ASSERT(xmlStructureSuite);
		if(!xmlStructureSuite) {
			SNIPLOG("IXMLStructureSuite nil, FAILED: CURRENTLY DEPENDS ON SELECTION IN STRUCTURE_VIEW");
			break;
		}
		
		if(xmlStructureSuite->CanAddAttribute()) {

			// If the attribute we're adding exists already on element(s) in selection, 
			// then we shouldn't try to re-add. 
			// To change existing attribute's value, we'd use a different method
			if(xmlStructureSuite->CanAddSpecificAttribute(attribName)) {

				err = xmlStructureSuite->AddAttribute(attribName, attribValue);
				ASSERT(err == kSuccess);
			} else {
				SNIPLOG("Attribute %s may exist already on selected node(s)", attribName.GetPlatformString().c_str());
			}
		} else {
			SNIPLOG("CanAddAttribute failed, selected node(s) likely don't support adding attributes");
		}
		err = kSuccess;
	} while(kFalse);
	return err;
}


/*
*/
ErrorCode SnpManipulateXMLSelection::CreateCommentInSelection(ISelectionManager* selectionManager,
											const PMString& commentText)
{
	ErrorCode err = kFailure;
	do {
	
		ASSERT(selectionManager);
		if(!selectionManager) {
			break;
		}
		InterfacePtr<IXMLTagSuite> xmlTagSuite(selectionManager, UseDefaultIID());

		ASSERT(xmlTagSuite);
		if(!xmlTagSuite) {
			SNIPLOG("IXMLTagSuite nil, FAILED");
			break;
		}
		if(xmlTagSuite->CanAddComment()) {
			err = xmlTagSuite->AddComment(commentText);
			ASSERT(err == kSuccess);
		} else {
			SNIPLOG("IXMLTagSuite::CanAddComment false, does element selected support having a comment as dependent?");
		}
		
	} while(kFalse);
	return err;
}

/*
*/
ErrorCode SnpManipulateXMLSelection::CreateProcessingInstructionInSelection(
											ISelectionManager* selectionManager, 
											const PMString& piKey, const PMString& piValue)
{
	ErrorCode err = kFailure;
	do {
		ASSERT(selectionManager);
		if(!selectionManager) {
			break;
		}

		InterfacePtr<IXMLTagSuite> xmlTagSuite(selectionManager, UseDefaultIID());

		ASSERT(xmlTagSuite);
		if(!xmlTagSuite) {
			SNIPLOG("IXMLTagSuite nil, FAILED");
			break;
		}
		if(xmlTagSuite->CanAddProcessingInstruction()) {
			err = xmlTagSuite->AddProcessingInstruction(piKey,piValue);
			ASSERT(err == kSuccess);
		} else {
			SNIPLOG("IXMLTagSuite::CanAddComment false, does element selected support having a processing instruction as dependent?");
		}

	} while(kFalse);
	return err;
}


/*
*/
ErrorCode SnpManipulateXMLSelection::ExportFromSelection(ISelectionManager* selectionManager, 
																 const IDFile& targetFile)
{
	ErrorCode err = kFailure;
	do {
		ASSERT(selectionManager);	
		if (!selectionManager) {
			break;
		}

		InterfacePtr<IXMLStructureSuite> structureSuite(selectionManager, UseDefaultIID());
		if(structureSuite && structureSuite->IsExportable()) {
		
		
			// Locate XML parser service to get IXMLAccess
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
			
			// Must have the stream or we crash
			InterfacePtr<IXMLOutStream>xmlStream(
				Utils<IXMLStreamUtils>()->CreateXMLOutFileStream(targetFile, 
					IXMLOutStream::kUTF16 ));

			handlerData->SetStream(xmlStream);
			err = structureSuite->Export(access, xmlExportHandler, targetFile);
			xmlStream->Close();
			ASSERT(err == kSuccess);
		}
	} while(kFalse);
	return err;
}

/*
*/
ErrorCode SnpManipulateXMLSelection::ExportXMLSnippetFromSelection(ISelectionManager* selectionManager, 
																   const IDFile& targetFile)
{
	ErrorCode err = kFailure;
	do {
		ASSERT(selectionManager);
		if (!selectionManager) {
			break;
		}
	
		InterfacePtr<ISnippetExportSuite> exportSuite(selectionManager, UseDefaultIID());
		if(exportSuite && exportSuite->CanExport()) {
			
			InterfacePtr<IPMStream> stream(StreamUtil::CreateFileStreamWrite(targetFile, kOpenOut, 'TEXT', 'CWIE'));
			ASSERT(stream);
			if(!stream) {
				break;
			}
			stream->Open();
			if (stream->GetStreamState() == kStreamStateGood)
			{
				stream->SetEndOfStream();
				exportSuite->DoExport(stream);
				
				//
				stream->Flush();
			}
			stream->Close();
			err = kSuccess;
		}
		
	} while(kFalse);
	return err;
}


/*
*/
ErrorCode SnpManipulateXMLSelection::ImportIntoSelection(ISelectionManager* selectionManager, 
														 IDataBase* database,
														 const IDFile& targetFile)
{
	ErrorCode err = kFailure;
	do {
		ASSERT(selectionManager);
		if(!selectionManager) {
			break;
		}

			
		InterfacePtr<IXMLStructureSuite> xmlStructureSuite(selectionManager, UseDefaultIID());
		ASSERT(xmlStructureSuite);
		if(!xmlStructureSuite) {
			SNIPLOG("IXMLStructureSuite nil, FAILED: CURRENTLY DEPENDS ON SELECTION IN STRUCTURE_VIEW");
			break;
		}
		if(xmlStructureSuite->IsImportable  ()) {
			err = xmlStructureSuite->Import(database, &targetFile, kSuppressUI);
			ASSERT(err == kSuccess);
		}
	
	} while(kFalse);
	return err;
}


/*
*/
ErrorCode SnpManipulateXMLSelection::ValidateFromSelection(ISelectionManager* selectionManager, IXMLValidator* xmlValidator)
{
	ErrorCode err = kFailure;
	do {
		ASSERT(selectionManager);
		if(!selectionManager) {
			break;
		}
		InterfacePtr<IXMLStructureSuite> xmlStructureSuite(selectionManager, UseDefaultIID());

		ASSERT(xmlStructureSuite);
		if(!xmlStructureSuite) {
			SNIPLOG("IXMLStructureSuite nil, FAILED: CURRENTLY DEPENDS ON SELECTION IN STRUCTURE_VIEW");
			break;
		}
		if(xmlStructureSuite->CanValidateSelection()) {
			
			xmlStructureSuite->ValidateSelection(xmlValidator);
			err = kSuccess;

			SNIPLOG("Validation error count= %d", xmlValidator->GetErrorCount());
			// list the errors
			for (int32 i = 0; i < xmlValidator->GetErrorCount(); i++) {
				XMLDTDValidationError validationError = xmlValidator->GetErrorAt(i);
				PMString err(ErrorUtils::PMGetErrorString(validationError.GetErrorCode()));
				SNIPLOG("Error = %s", err.GetPlatformString().c_str());
				// list the suggestions
				const K2Vector<XMLDTDValidateSuggest*>& suggestions = validationError.GetSuggestions();
				for (K2Vector<XMLDTDValidateSuggest*>::const_iterator suggestIter = suggestions.begin(); suggestIter != suggestions.end(); ++suggestIter) {
					K2::scoped_ptr<PMString> str((*suggestIter)->QueryDisplayString());
					SNIPLOG("Suggestion: %s", str->GetPlatformString().c_str());
				}
			}
		
		}
	} while(kFalse);
	return err;
}


// --------------------------------- SnippetRunner framework hook ---------------------------------------------------

/** Makes the snippet SnpManipulateXMLSelection available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerManipulateXMLSelection : public SnpRunnable
{
	public:
		/** This constructor describes your snippet to the framework.
		 */
		_SnpRunnerManipulateXMLSelection();

		/** Destructor.
		 */
		virtual			~_SnpRunnerManipulateXMLSelection();

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
_SnpRunnerManipulateXMLSelection::_SnpRunnerManipulateXMLSelection() : SnpRunnable("ManipulateXMLSelection")
{
	this->SetDescription("Manipulate the logical structure through an XML selection");
	this->SetPreconditions("open document");
	this->SetCategories("sdk_snippet, sdk_xmedia");}

/* Destructor.
*/
_SnpRunnerManipulateXMLSelection::~_SnpRunnerManipulateXMLSelection()
{
}

/* Check if your snippet's preconditions are met here.
*/
bool16	_SnpRunnerManipulateXMLSelection::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 err = kFalse;
	// Needs XML selection
	InterfacePtr<IXMLNodeTarget> xmlNodeTarget(runnableContext, UseDefaultIID()); 
	err =  (xmlNodeTarget != nil);

	return err;
}

/* Set up and call your snippet here.
*/
ErrorCode _SnpRunnerManipulateXMLSelection::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;
	do {
		IActiveContext* activeContext = runnableContext->GetActiveContext();
		UIDRef documentUIDRef = ::GetUIDRef(activeContext->GetContextDocument());
		SnpManipulateXMLSelection instance;
		ISelectionManager *selectionManager = activeContext->GetContextSelection();
		SnpXMLSampleHelper xmlHelper;
		
		K2Vector<PMString> choices;
		choices.push_back(PMString("CreateAttributesInSelection")); //0
		choices.push_back(PMString("CreateElementsInSelection")); //1
		choices.push_back(PMString("CreatePIsAndCommentsInSelection")); //2
		choices.push_back(PMString("ValidateAgainstDTDFromSelection")); //3
		choices.push_back(PMString("ExportFromSelection")); //4
		choices.push_back(PMString("ExportXMLSnippetFromSelection")); //5
		choices.push_back(PMString("ImportIntoSelection")); //6
		
		Utils<ISnipRunParameterUtils> parameterUtils;
		int32 choice = parameterUtils->GetChoice(PMString("What action?"), choices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		switch(choice) {
		case 0:
			{
				//CreateAttributesInSelection
				SNIPLOG("CreateAttributesInSelection");
				status = instance.CreateAttributesInSelection(selectionManager,
									PMString("new-sel-attrib"), 
									PMString("seln-value"));
				ASSERT(status == kSuccess);
				SNIPLOG("\nThis snippet attempted to create new attributes for selected node(s)");

			}
			break;

		case 1:
			{
				// CreateElementsInSelection
				SNIPLOG("CreateElementsInSelection");
				const int32 numElementsToCreate = 6;
				// NB suite interface IXMLTagSuite requires 'model' information
				UIDRef tagUIDRef = xmlHelper.AcquireTag(documentUIDRef, PMString("story"));
				ASSERT(tagUIDRef != UIDRef::gNull);
				status = instance.CreateElementsInSelection(selectionManager, tagUIDRef ,numElementsToCreate);	
				if(status == kSuccess)
					SNIPLOG("\nThis snippet created some new <story> elements with selected node as parent");
			}
			break;

		case 2:
			{
				//CreatePIsAndCommentsInSelection
				SNIPLOG("CreatePIsAndCommentsInSelection");
				PMString commentText("My comment");
				PMString piTarget("pi-target");
				PMString piData("pi-data");
				commentText.SetTranslatable(kFalse);
				piTarget.SetTranslatable(kFalse);
				piData.SetTranslatable(kFalse);

				status =instance.CreateCommentInSelection(selectionManager, commentText);
				if(status == kSuccess)
				{
					status = instance.CreateProcessingInstructionInSelection(selectionManager,piTarget, piData);
					if(status == kSuccess)
						SNIPLOG("\nThis scenario created new comments and processing instructions parented by selected node(s)");
				}
			}
			break;

		case 3:
			{
				//ValidateAgainstDTDFromSelection
				SNIPLOG("ValidateAgainstDTDFromSelection");
				IDFile sysFile = xmlHelper.GetSampleFile(".dtd");
				xmlHelper.CreateSampleDTD(sysFile);
				xmlHelper.AssociateDTD(documentUIDRef, sysFile);
		
				InterfacePtr<IIDXMLElement> docElement(
					Utils<IXMLUtils>()->QueryDocElement(documentUIDRef.GetDataBase()));
				ASSERT(docElement);
				if(!docElement) {
					break;
				}
				InterfacePtr<IXMLValidator> xmlValidator(docElement, UseDefaultIID());
				ASSERT(xmlValidator);
				if(!xmlValidator) {
					break;
				}
				status = instance.ValidateFromSelection(selectionManager, xmlValidator);
				if(status == kSuccess)
				{
					SDKFileHelper fileHelper(sysFile);
					SNIPLOG("\nThis scenario validated the logical structure of the selection against a sample DTD that can be found in %s",
						fileHelper.GetPath().GetPlatformString().c_str());
				}
			}
			break;


		case 4:
			{
				//ExportFromSelection
				SNIPLOG("ExportFromSelection");
				IDFile sysHasSelectionFile = xmlHelper.GetSampleFile("-from-sel.xml");
				
				status = instance.ExportFromSelection(selectionManager, sysHasSelectionFile);
				if(status == kSuccess)
				{
					SDKFileHelper file1Helper(sysHasSelectionFile);
					SNIPLOG("This scenario created XML file from the selection; %s",
					file1Helper.GetPath().GetPlatformString().c_str());
				}

	
			}
			break;


		case 5:
			{
				//ExportXMLSnippetFromSelection
				SNIPLOG("ExportXMLSnippetFromSelection");
				IDFile sysFile = xmlHelper.GetSampleFile("-sel.inds");
				status = instance.ExportXMLSnippetFromSelection(selectionManager, sysFile);
				if(status == kSuccess)
				{
					SDKFileHelper fileHelper(sysFile);
					SNIPLOG("\nThis scenario exported an XML snippet based on selected nodes to %s",
					fileHelper.GetPath().GetPlatformString().c_str());
				}
	
			}
			break;

		case 6:
			{
				//ImportIntoSelection
				SNIPLOG("ImportIntoSelection");
				IDataBase* database = documentUIDRef.GetDataBase();
				IDFile sysHasSelectionFile = xmlHelper.GetSampleFile("-from-sel.xml");
				status = instance.ImportIntoSelection(selectionManager, database, sysHasSelectionFile);
				if(status == kSuccess)			
					SNIPLOG("\nThis scenario imported XML file created by prior export into selection in the logical structure");
	
			}
			break;

		}// switch

	} while(kFalse);

	return status;
}

/*	Declare an instance to register the snippet hook with the framework.
*/
static _SnpRunnerManipulateXMLSelection instance_SnpRunnerManipulateXMLSelection;
DEFINE_SNIPPET(_SnpRunnerManipulateXMLSelection) 	
