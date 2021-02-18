//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpManipulateXMLElements.cpp $
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
#include "IActionManager.h"
#include "IApplication.h"
#include "ICellContent.h"
#include "IDocument.h"
#include "IGraphicFrameData.h"
#include "IFrameType.h"
#include "IHierarchy.h"
#include "IIDXMLElement.h"
#include "ISelectionManager.h" // We're querying suite interfaces off IActiveContext::GetContextSelection()
#include "IStringData.h"
#include "ITableModel.h"
#include "IMultiColumnTextFrame.h"
#include "IXMLAttributeCommands.h"
#include "IXMLCreateElementCmdData.h"
#include "IXMLLoadDTDCmdData.h"
#include "IXMLReferenceData.h"
#include "IXMLStructureSuite.h"
#include "IXMLTagSuite.h"
#include "IXMLUtils.h"
#include "IXMLValidator.h"
#include "IXMLTagList.h"
#include "IWorkspace.h"
// General includes:
#include "XMLContentIterator.h"
// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunSuite.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"
#include "SnpTextModelHelper.h"
#include "SDKFileHelper.h"
#include "SnpXMLSampleHelper.h"
#if __INTEL_COMPILER || MACINTOSH
#include "K2Vector.tpp"
#endif
//#include "SnpXMLStructureViewHelper.h"

/**
	\li How to obtain list of all elements
	\li How to obtain reference to root or document element
	\li How to associate a DTD with the logical structure
	\li How to create elements in the logical structure
	\li How to create XML comments and processing instructions
	\li How to modify comments and processing instructions
	\li How to tag a graphic frame (IGraphicFrameData) for instance as image placeholder
	\li How to tag a story (kTextStoryBoss)
	\li how to tag a table (kTableModelBoss)
	\li How to tag a text range
	\li How to validate logical structure against a DTD
	
	Once you have run the snippet options, an interesting thing to do is try using SnpInspectSelectionXMLProperties to find out
	something about what has been created. For instance, if you run TagGraphic, select the frame in the layout
	view and run SnpInspectSelectionXMLProperties.


	<h2>Exercising</h2>

	<h3>AcquireElements</h3>
		-# Create a new document
		-# Run the snippet ManipulateXMLElements
		-# Choose the option AcquireElements.
		-# If all is well, there should be no asserts (if in debug build).
	<h3>AssociateDTD</h3>
		-# Create a new document
		-# Run the snippet ManipulateXMLElements
		-# Choose the option AssociateDTD.
		-# If all is well, there should be no asserts (if in debug build).
	<h3>CreateElementsAndAttributes</h3>
		-# Create a new document
		-# Run the snippet ManipulateXMLElements
		-# Choose the option CreateElementsAndAttributes.
		-# If all is well, there should be no asserts (if in debug build).
		-# You should see some elements with attributes in the logical structure
	<h3>CreateComment/PI</h3>
		-# Create a new document
		-# Run the snippet ManipulateXMLElements
		-# Choose the option CreateComment/PI.
		-# If all is well, there should be no asserts (if in debug build).
		-# You should see some new comment/PI in logical structure
	<h3>ModifyComment/PI</h3>
		-# Create a new document
		-# Run the snippet ManipulateXMLElements
		-# Choose the option ModifyComment/PI.
		-# If all is well, there should be no asserts (if in debug build).
		-# You should see comment/PI in logical structure created, which was the thing modified
	<h3>TagGraphic</h3>
		-# Create a new document
		-# Run the snippet ManipulateXMLElements
		-# Choose the option TagGraphic.
		-# If all is well, there should be no asserts (if in debug build).
		-# You should see a placeholder graphic created and tagged
	<h3>TagStory</h3>
		-# Create a new document
		-# Run the snippet ManipulateXMLElements
		-# Choose the option TagStory.
		-# If all is well, there should be no asserts (if in debug build).
	<h3>TagTable</h3>
		-# Create a new document
		-# Run the snippet ManipulateXMLElements
		-# Choose the option TagTable.
		-# If all is well, there should be no asserts (if in debug build).
	<h3>TagTextRange</h3>
		-# Create a new document
		-# Run the snippet ManipulateXMLElements
		-# Choose the option TagTextRange.
		-# If all is well, there should be no asserts (if in debug build).
	<h3>ValidateAgainstDTD</h3>
		-# Create a new document
		-# Run the snippet ManipulateXMLElements
		-# Choose the option ValidateAgainstDTD.
		-# If all is well, there should be no asserts (if in debug build).

	@ingroup sdk_snippet
	@ingroup sdk_xmedia

	@see _SnpRunnerManipulateXMLElements::Run for driver code
*/
class SnpManipulateXMLElements {
public:
	/** Constructor */
	SnpManipulateXMLElements() {}

	/** Destructor */
	virtual ~SnpManipulateXMLElements() {}

	/**	Obtain reference to document element (kXMLDocumentBoss)
		@precondition documentUIDRef should allow IDocument to be instantiated
		@param documentUIDRef specifies document of interest
		@return XMLReference to document element
		@see IXMLUtils::QueryDocElement
		*/
	XMLReference GetDocumentElementRef(const UIDRef& documentUIDRef);

	/**	Obtain list of all elements in document
		@precondition documentUIDRef should allow IDocument to be instantiated
		@param documentUIDRef specifies document of interest
		@param outElems OUT stores list of elements in the document
		*/
	void GetFlattenedElementList(const UIDRef& documentUIDRef, K2Vector<XMLReference>& outElems);

	/**	Obtain reference to root element
		@precondition documentUIDRef should allow IDocument to be instantiated
		@return XMLReference 
		@see IXMLUtils::QueryRootElement
		*/
	XMLReference GetRootElementRef(const UIDRef& documentUIDRef);


	/**	Create element(s) in document with given parent
		@precondition parentXMLReference should allow IIDXMLElement to be instantiated
		@param parentXMLReference parent for newly created element(s)
		@param tagName specifies tag to use for created element(s)
		@param numElements how many elements to create
		@param outElementsCreated stores the references to elements created
		@return ErrorCode kSuccess on success, other ErrorCode otherwise
	 */
	ErrorCode CreateElements(const XMLReference& parentXMLReference,
							const PMString& tagName,
							int32 numElements,
							K2Vector<XMLReference>& outElementsCreated);


	/**	Create a new attribute for the elements supplied
		@precondition each element in elements should allow IIDXMLElement to be instantiated
		@precondition attribName shouldn't already exist on the elements supplied
		@param elements 
		@param attribName name of attribute
		@param attribValue value for the attribute
		@return ErrorCode kSuccess on success, other ErrorCode otherwise
	 */
	ErrorCode CreateAttributes(const K2Vector<XMLReference>& elements,
									const PMString& attribName,
									const PMString& attribValue);


	/**	Create a new XML comment (kXMLCommentBoss)
		@precondition  parentXMLReference should allow IIDXMLElement to be instantiated
		@param parentXMLReference parent in logical structure for new element
		@param commentText what the comment should contain
		@param outXMLReferenceCreated allows IIDXMLElement to be instantiated for new element (kXMLCommentBoss)
		@return ErrorCode kSuccess on success, other ErrorCode otherwise
	*/
	ErrorCode CreateComment(const XMLReference& parentXMLReference,
															const PMString& commentText,
															XMLReference& outXMLReferenceCreated);


	/**	Create a processing instruction (kXMLPIBoss)
		@precondition  parentXMLReference should allow IIDXMLElement to be instantiated
		@param parentXMLReference 
		@param piKey key for the PI to create
		@param piValue value for the PI to create
		@param outXMLReferenceCreated allows IIDXMLElement to be instantiated for new element (kXMLPIBoss)
		@return ErrorCode kSuccess on success, other ErrorCode otherwise
	 */
	ErrorCode CreateProcessingInstruction(const XMLReference& parentXMLReference,
											const PMString& piKey, const PMString& piValue,
											XMLReference& outXMLReferenceCreated);
	
	

	/**	Modify text of an existing comment
		@precondition  commentXMLReference should allow IIDXMLElement to be instantiated
		@param commentXMLReference 
		@param newCommentText 
		@return ErrorCode kSuccess on success, other ErrorCode otherwise
	 */
	ErrorCode ModifyComment(const XMLReference& commentXMLReference,
											const PMString& newCommentText);


	/**	Modify properties of an existing processing instruction
		@precondition  piXMLReference should allow IIDXMLElement to be instantiated
		@param piXMLReference 
		@param newPiKey 
		@param newPiValue 
		@return ErrorCode kSuccess on success, other ErrorCode otherwise
	 */
	ErrorCode ModifyProcessingInstruction(const XMLReference& piXMLReference,
											const PMString& newPiKey, 
											const PMString& newPiValue);


	/**	Assign tag to a graphic frame
		@precondition  graphicFrameUIDRef should allow IGraphicFrameData to be instantiated
		@param tagName 
		@param graphicFrameUIDRef 
		@return ErrorCode kSuccess on success, other ErrorCode otherwise
	 */
	ErrorCode TagGraphic(const PMString& tagName, const UIDRef& graphicFrameUIDRef);


	/**	Assign a tag to a story through its associated text frame
		@precondition textFrameContainerUIDRef should allow IHierarchy to be instantiated
		@precondition textFrameContainerUIDRef have zeroth child with IMultiColumnTextFrame
		@param tagName specifies name of tag to apply, is created if not existing
		@param textFrameContainerUIDRef identifies text frame
		@return ErrorCode kSuccess on success, other ErrorCode otherwise
	 */
	ErrorCode TagStoryThroughFrame(const PMString& tagName,
									const UIDRef& textFrameContainerUIDRef);


	/**	Assign tag to a story
		@precondition textModelUIDRef should allow ITextModel to be instantiated
		@param tagName 
		@param textModelUIDRef 
		@return ErrorCode kSuccess on success, other ErrorCode otherwise

	*/
	ErrorCode TagStory(const PMString& tagName,
						const UIDRef& textModelUIDRef);	


	/**	Assign tag to a table, and tag the cells too. 
		@precondition story in which table is located should already be tagged
		@precondition tableModelUIDRef should allow ITableModel to be instantiated
		@param tableModelUIDRef identifies table
		@param tableTagName tag to apply to table
		@param cellTagName tag to apply to cells
		@param outCreatedXMLReference stores element created from which IIDXMLElement can be instantiated
		@return ErrorCode kSuccess on success, other ErrorCode otherwise
	 */
	ErrorCode TagTable(const UIDRef& tableModelUIDRef,
								const PMString& tableTagName,
								const PMString& cellTagName,
								XMLReference& outCreatedXMLReference);


	/**	Assign tag to a range of text in a story
		@precondition story should already be tagged
		@precondition textModelUIDRef should allow ITextModel to be instantiated
		@param textModelUIDRef story
		@param tagName name of tag to apply
		@param startIndex beginning of range to tag
		@param endIndex end of range to tag
		@return ErrorCode kSuccess on success, other ErrorCode otherwise
	 */
	ErrorCode TagTextRange(const UIDRef& textModelUIDRef,
									const PMString& tagName,
									const TextIndex& startIndex,
									const TextIndex& endIndex);

	/** Validates the logical structure of document against associated DTD 
		using an action executed via the 
		action manager (IActionManager).
		Needs active context (IActiveContext) to drive method on action manager (IActionManager)
		@param context current active context
	*/
	void ValidateFromRoot(IActiveContext* context);

	/**	Validate logical structure against associated DTD from specified element.
		@precondition xmlRef should allow IIDXMLElement to be instantiated
		@param xmlRef specifies element (IIDXMLElement) from which to start validating
	 */
	void ValidateFromElement(const XMLReference& xmlRef);

private:

	/**	Helper method to add descendants into a flattened list of elements
		@param xmlRef current node
		@param outElem stores the list of elements
	 */
	void addXMLReferenceAndDependents(const XMLReference& xmlRef, K2Vector<XMLReference>& outElem);

};



/*
*/
XMLReference SnpManipulateXMLElements::GetDocumentElementRef(const UIDRef& documentUIDRef)
{
	XMLReference docXMLReference;
	do {
		IDataBase*db = documentUIDRef.GetDataBase();
		InterfacePtr<IIDXMLElement> docXMLElement(Utils<IXMLUtils>()->QueryDocElement(db));
		ASSERT(docXMLElement);
		if(!docXMLElement) {
			break;
		}
		
		docXMLReference = docXMLElement->GetXMLReference();

	} while(kFalse);

	return docXMLReference;
}


/*
*/
XMLReference SnpManipulateXMLElements::GetRootElementRef(const UIDRef& documentUIDRef)
{
	XMLReference rootXMLReference;
	do {
		IDataBase*db = documentUIDRef.GetDataBase();
		InterfacePtr<IIDXMLElement> rootXMLElement(Utils<IXMLUtils>()->QueryRootElement(db));
		ASSERT(rootXMLElement);
		if(!rootXMLElement) {
			break;
		}
		rootXMLReference = rootXMLElement->GetXMLReference();
	
		

	} while(kFalse);
	return rootXMLReference;
}


/*
*/
void SnpManipulateXMLElements::GetFlattenedElementList(const UIDRef& documentUIDRef, K2Vector<XMLReference>& outElems)
{
	XMLReference docElem = this->GetDocumentElementRef(documentUIDRef);
	this->addXMLReferenceAndDependents(docElem, outElems);
}

/*
*/
void SnpManipulateXMLElements::addXMLReferenceAndDependents(const XMLReference& xmlRef, K2Vector<XMLReference>& outElems)
{
	outElems.push_back(xmlRef);

	do {
		InterfacePtr<IIDXMLElement> element(xmlRef.Instantiate());
		if(!element) {
			break;
		}
		// Since this is a recursive method, you might with a very large document
		// get a stack overflow. You could use another technique, e.g. a goto and your own stack impl.
		// to avoid this in the general case
		for(int32 i=0; i < element->GetChildCount(); i++) {
			XMLReference childRef = element->GetNthChild(i);
			this->addXMLReferenceAndDependents(childRef,outElems);
		}
	} while(kFalse);
}


/*
*/
ErrorCode SnpManipulateXMLElements::CreateElements(const XMLReference& parentXMLReference,
													const PMString& tagName,
													int32 numElements,
													K2Vector<XMLReference>& outElementsCreated)
{
	ErrorCode err = kFailure;
	do {
		// +preconditions
		InterfacePtr<IIDXMLElement> parentElement(parentXMLReference.Instantiate());
		ASSERT(parentElement);
		if(!parentElement) {
			break;
		}
		IDataBase* database = parentXMLReference.GetDataBase();
		UIDRef documentUIDRef(database, database->GetRootUID());
		InterfacePtr<IDocument> document(documentUIDRef, UseDefaultIID());
		ASSERT(document);
		if(!document) {
			break;
		}
		// - preconditions
		SnpXMLHelper xmlHelper;
		UIDRef tagUIDRef = xmlHelper.AcquireTag(documentUIDRef, tagName);
		for(int32 i=0; i < numElements; i++) {
			int32 indexInParent =  parentElement->GetChildCount()-1;
			if(indexInParent < 0) {
				indexInParent = 0;
			} 
			XMLReference createdElem;
			err = Utils<IXMLElementCommands>()->CreateElement (tagUIDRef.GetUID(), 
											kInvalidUID, 
											parentXMLReference, 
											indexInParent,
											&createdElem);
			ASSERT(err == kSuccess);
			if(err != kSuccess) {
				break;
			}
			outElementsCreated.push_back(createdElem);
		}
	
	} while(kFalse);
	return err;
}


/*
*/
ErrorCode SnpManipulateXMLElements::CreateAttributes(const K2Vector<XMLReference>& elements,
													const PMString& attribName,
													const PMString& attribValue)
{			
	ErrorCode err = kFailure;
	do {
		Utils<IXMLAttributeCommands> attributeFacade;
		ASSERT(attributeFacade);
		if(!attributeFacade) {
			break;
		}
		K2Vector<XMLReference>::const_iterator iter;
		for(iter = elements.begin(); iter != elements.end(); iter++) {
			XMLReference nextXMLRef = *iter;
			err = attributeFacade->CreateAttribute(nextXMLRef,(WideString)attribName, (WideString)attribValue);
			ASSERT(err == kSuccess);
			if(err != kSuccess) {
				break;
			}
		}
	} while(kFalse);
	return err;
}


	
/*
*/
ErrorCode SnpManipulateXMLElements::CreateComment(const XMLReference& parentXMLReference,
															const PMString& commentText,
															XMLReference& outXMLReferenceCreated)
{
	ErrorCode err = kFailure;
	
	do {

		InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kXMLCreateCommentCmdBoss));
		ASSERT(cmd);
		if(!cmd) {
			break;
		}
		InterfacePtr<IXMLCreateElementCmdData> cmdData(cmd, UseDefaultIID());
		ASSERT(cmdData);
		if(!cmdData) {
			break;
		}
	
		InterfacePtr<IIDXMLElement> parentXMLElement(parentXMLReference.Instantiate());
		ASSERT(parentXMLElement);
		if(!parentXMLElement) {
			break;
		}
		int32 indexInParent =  (parentXMLElement->GetChildCount());				

		if(indexInParent < 0) {
			indexInParent = 0;
		} 
		cmdData->Set(kInvalidUID, kInvalidUID, parentXMLReference, indexInParent);
		
		InterfacePtr<IStringData> cmdStringData(cmd, IID_IXMLCOMMENTBODYSTRINGDATA);
		ASSERT(cmdStringData);
		if(!cmdStringData) {
			break;
		}
		cmdStringData->Set(commentText);

		err = CmdUtils::ProcessCommand(cmd);
		ASSERT(err == kSuccess);
		// The command posts the XMLReference created through modifying this data interface on
		// the command
		outXMLReferenceCreated = cmdData->GetCreatedElement();
	} while(kFalse);
	return err;
}

/*
*/
ErrorCode SnpManipulateXMLElements::CreateProcessingInstruction(
											const XMLReference& parentXMLReference,
											const PMString& piKey, const PMString& piValue,
											XMLReference& outXMLReferenceCreated)
{
	ErrorCode err = kFailure; 
	do {
		InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kXMLCreatePICmdBoss));
		ASSERT(cmd);
		if(!cmd) {
			break;
		}
		InterfacePtr<IXMLCreateElementCmdData> cmdData(cmd, UseDefaultIID());
		ASSERT(cmdData);
		if(!cmdData) {
			break;
		}
		
		InterfacePtr<IIDXMLElement> parentXMLElement(parentXMLReference.Instantiate());
		ASSERT(parentXMLElement);
		if(!parentXMLElement) {
			break;
		}
		int32 indexInParent =  (parentXMLElement->GetChildCount());				
		if(indexInParent < 0) {
			indexInParent = 0;
		} 
		cmdData->Set(kInvalidUID, kInvalidUID, parentXMLReference, indexInParent);
		// PITarget
		InterfacePtr<IStringData> cmdPITargetData(cmd, IID_IXMLPITARGET);
		ASSERT(cmdPITargetData);
		if(!cmdPITargetData) {
			break;
		}
		cmdPITargetData->Set(piKey);
		// PIData
		InterfacePtr<IStringData> cmdPIDataData(cmd, IID_IXMLPIDATA);
		ASSERT(cmdPIDataData);
		if(!cmdPIDataData) {
			break;
		}
		cmdPIDataData->Set(piValue);
		err = CmdUtils::ProcessCommand(cmd);
		ASSERT(err == kSuccess);
		// The command posts the XMLReference created through modifying this data interface on
		// the command
		outXMLReferenceCreated = cmdData->GetCreatedElement();

	} while(kFalse);
	return err;
}



/*
*/
ErrorCode SnpManipulateXMLElements::ModifyComment(const XMLReference& commentXMLReference,
											const PMString& newCommentText)
{
	ErrorCode err = kFailure;
	do {
		InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kXMLSetCommentCmdBoss));
		ASSERT(cmd);
		if(!cmd) {
			break;
		}
		InterfacePtr<IXMLReferenceData> cmdXMLRefData(cmd, UseDefaultIID());
		ASSERT(cmdXMLRefData);
		if(!cmdXMLRefData) {
			break;
		}
		cmdXMLRefData->Set(commentXMLReference);
		InterfacePtr<IStringData> cmdStringData(cmd, UseDefaultIID());
		ASSERT(cmdStringData);
		if(!cmdStringData) {
			break;
		}
		cmdStringData->Set(newCommentText);
		err= CmdUtils::ProcessCommand(cmd);
	
	} while(kFalse);
	return err;
}

/*
*/
ErrorCode SnpManipulateXMLElements::ModifyProcessingInstruction(const XMLReference& piXMLReference,
											const PMString& newPiKey, 
											const PMString& newPiValue)
{
	ErrorCode err = kFailure;
	do {
		InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kXMLSetPICmdBoss));
		ASSERT(cmd);
		if(!cmd) {
			break;
		}
		InterfacePtr<IXMLReferenceData> cmdXMLRefData(cmd, UseDefaultIID());
		ASSERT(cmdXMLRefData);
		if(!cmdXMLRefData) {
			break;
		}
		cmdXMLRefData->Set(piXMLReference);
		InterfacePtr<IStringData> targetStrData(cmd, IID_IXMLPITARGET);
		ASSERT(targetStrData);
		if(!targetStrData) {
			break;
		}
		targetStrData->Set(newPiKey);
		InterfacePtr<IStringData> dataStrData(cmd, IID_IXMLPIDATA);
		ASSERT(dataStrData);
		if(!dataStrData) {
			break;
		}
		dataStrData->Set(newPiValue);
		err = CmdUtils::ProcessCommand(cmd);
	} while(kFalse);
	return err;
}



/*
*/
ErrorCode SnpManipulateXMLElements::TagGraphic(const PMString& tagName, const UIDRef& graphicFrameUIDRef)
{	
	ErrorCode err = kFailure;
	do {
		IDataBase* database = graphicFrameUIDRef.GetDataBase();
		UIDRef documentUIDRef(database, database->GetRootUID());
		// + preconditions
		InterfacePtr<IGraphicFrameData> graphicFrameData(graphicFrameUIDRef, UseDefaultIID());
		ASSERT(graphicFrameData != nil);
		if(!graphicFrameData) {
			break;
		}
		
		InterfacePtr<IIDXMLElement> rootXMLElement(Utils<IXMLUtils>()->QueryRootElement(database));
		ASSERT(rootXMLElement);
		if(!rootXMLElement) {
			break;
		}
		XMLReference rootXMLReference = rootXMLElement->GetXMLReference();

		int32 indexInParent =  rootXMLElement->GetChildCount();
		if(indexInParent < 0) {
			indexInParent = 0;
		} 
		bool16 isTaggable = Utils<IXMLUtils>()->IsTaggablePageItem(graphicFrameData);
		ASSERT(isTaggable);
		if(!isTaggable) {
			break;
		}
		SnpXMLHelper xmlHelper;
		UIDRef tagUIDRef = xmlHelper.AcquireTag(documentUIDRef, tagName);
		err = Utils<IXMLElementCommands>()->CreateElement(tagUIDRef.GetUID(), 
			graphicFrameUIDRef.GetUID(),
			rootXMLReference,
			indexInParent
			);

	} while(kFalse);
	return err;
}


ErrorCode SnpManipulateXMLElements::TagStory(
								   const PMString& tagName,
									const UIDRef& textModelUIDRef)
{
	ErrorCode err = kFailure;
	do {
		IDataBase* database = textModelUIDRef.GetDataBase();
		UIDRef documentUIDRef(database, database->GetRootUID());

		InterfacePtr<ITextModel> textModel(textModelUIDRef, UseDefaultIID());
		ASSERT(textModel);
		if(!textModel) {
			break;
		}
		
		InterfacePtr<IIDXMLElement> rootXMLElement(Utils<IXMLUtils>()->QueryRootElement(database));
		ASSERT(rootXMLElement);
		if(!rootXMLElement) {
			break;
		}
		XMLReference rootXMLReference = rootXMLElement->GetXMLReference();

		int32 indexInParent =  rootXMLElement->GetChildCount();
		if(indexInParent < 0) {
			indexInParent = 0;
		} 
		
		SnpXMLHelper xmlHelper;

		UIDRef tagUIDRef = xmlHelper.AcquireTag(documentUIDRef, tagName);
		err = Utils<IXMLElementCommands>()->CreateElement(tagUIDRef.GetUID(), 
			textModelUIDRef.GetUID(),
			rootXMLReference,
			indexInParent
			);
		ASSERT(err == kSuccess);
	} while(kFalse);
	return err;
}
/*
*/
ErrorCode SnpManipulateXMLElements::TagStoryThroughFrame(
											   const PMString& tagName,
											   const UIDRef& textFrameContainerUIDRef)
{
	ErrorCode err = kFailure;
	do {
		IDataBase* database = textFrameContainerUIDRef.GetDataBase();
		UIDRef documentUIDRef(database, database->GetRootUID());
		
		InterfacePtr<IHierarchy> hierarchy(textFrameContainerUIDRef, UseDefaultIID());
		ASSERT(hierarchy);
		if(!hierarchy) {
			break;
		}
	
		InterfacePtr<IHierarchy> childHierarchy(hierarchy->QueryChild(0));
		ASSERT(childHierarchy);
		if(!childHierarchy) {
			break;
		}
			
		InterfacePtr<IMultiColumnTextFrame> mcfTextFrame(childHierarchy, UseDefaultIID());
		ASSERT(mcfTextFrame);
		if(!mcfTextFrame) {
			break;
		}
		InterfacePtr<ITextModel> textModel(mcfTextFrame->QueryTextModel());
		ASSERT(textModel);
		if(!textModel) {
			break;
		}

		err = this->TagStory(tagName, ::GetUIDRef(textModel));

	} while(kFalse);
	return err;
}


/*
*/
ErrorCode SnpManipulateXMLElements::TagTable(const UIDRef& tableModelUIDRef,
								const PMString& tableTagName,
								const PMString& cellTagName,
								XMLReference& outCreatedXMLReference)
{
	ErrorCode err = kFailure;
	do {
		// + preconditions
		InterfacePtr<ITableModel> tableModel(tableModelUIDRef, UseDefaultIID());
		ASSERT(tableModel != nil);
		// - preconditions
		if(!tableModel) {
			break;
		}
		IDataBase* database = tableModelUIDRef.GetDataBase();
		UIDRef documentUIDRef(database, database->GetRootUID());

		SnpXMLHelper xmlHelper;
		UIDRef tablTagUIDRef = xmlHelper.AcquireTag(documentUIDRef, tableTagName);
		UIDRef cellTagUIDRef = xmlHelper.AcquireTag(documentUIDRef, cellTagName);

		err = Utils<IXMLElementCommands>()->CreateTableElement (tablTagUIDRef.GetUID(),
											cellTagUIDRef.GetUID(),
											tableModelUIDRef,
											&outCreatedXMLReference);
		ASSERT(err == kSuccess);

	} while(kFalse);
	return err;
}



/*
*/
ErrorCode SnpManipulateXMLElements::TagTextRange(const UIDRef& textModelUIDRef,
									const PMString& tagName,
									const TextIndex& startIndex,
									const TextIndex& endIndex)
{
	ErrorCode err = kFailure;
	do {
		IDataBase* database = textModelUIDRef.GetDataBase();
		UIDRef documentUIDRef(database, database->GetRootUID());
		// + preconditions
		InterfacePtr<ITextModel> textModel(textModelUIDRef, UseDefaultIID());
		ASSERT(textModel != nil);
		if(!textModel) {
			break;
		}
		SnpXMLHelper xmlHelper;
		UIDRef tagUIDRef = xmlHelper.AcquireTag(documentUIDRef,
												tagName);
		err = Utils<IXMLElementCommands>()->CreateElement(tagUIDRef.GetUID(), 
														textModelUIDRef,
														startIndex, endIndex);

		ASSERT(err == kSuccess);
	} while(kFalse);
	return err;
}


/*
*/
void SnpManipulateXMLElements::ValidateFromRoot(IActiveContext* context)
{
	do {
		InterfacePtr<IApplication> application(GetExecutionContextSession()->QueryApplication());
		ASSERT(application);
		if(!application) {
			break;
		}
		InterfacePtr<IActionManager> actionManager(application->QueryActionManager());
		ASSERT(actionManager);
		if(!actionManager) {
			break;
		}
		// See Watson 1059986; crash if structure-view not visible
		actionManager->PerformAction(context, kStructureValidateRootActionID);
		} while(kFalse);
}

/*
*/
void SnpManipulateXMLElements::ValidateFromElement(const XMLReference& xmlRef)
{
	do {
		K2Vector<XMLDTDValidationError> errors;
		Utils<IXMLUtils>()->ValidateXML(xmlRef, errors);

		// list the errors
		for (K2Vector<XMLDTDValidationError>::const_iterator iter = errors.begin(); iter != errors.end(); ++iter) {
			PMString err(ErrorUtils::PMGetErrorString(iter->GetErrorCode()));
				SNIPLOG("Error = %s", err.GetPlatformString().c_str());
	
			// list the suggestions
			const K2Vector<XMLDTDValidateSuggest*>& suggestions = iter->GetSuggestions();
			for (K2Vector<XMLDTDValidateSuggest*>::const_iterator suggestIter = suggestions.begin(); suggestIter != suggestions.end(); ++suggestIter) {
				K2::scoped_ptr<PMString> str((*suggestIter)->QueryDisplayString());
				SNIPLOG("Suggestion: %s", str->GetPlatformString().c_str());
			}
		}

	} while(kFalse);

}


// --------------------------------- SnippetRunner framework hook ---------------------------------------------------

/** Makes the snippet SnpManipulateXMLElements available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerManipulateXMLElements : public SnpRunnable
{
	public:
		/** This constructor describes your snippet to the framework.
		 */
		_SnpRunnerManipulateXMLElements();

		/** Destructor.
		 */
		virtual			~_SnpRunnerManipulateXMLElements();

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
_SnpRunnerManipulateXMLElements::_SnpRunnerManipulateXMLElements() : SnpRunnable("ManipulateXMLElements")
{
	this->SetDescription("Manipulate XML elements and logical structure");
	this->SetPreconditions("open document");
	this->SetCategories("sdk_snippet, sdk_xmedia");
}

/* Destructor.
*/
_SnpRunnerManipulateXMLElements::~_SnpRunnerManipulateXMLElements()
{
}

/* Check if your snippet's preconditions are met here.
*/
bool16	_SnpRunnerManipulateXMLElements::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {
		ASSERT(runnableContext->GetActiveContext()); 
		if(!runnableContext->GetActiveContext()) {
			break;
		}
		IDocument* document = runnableContext->GetActiveContext()->GetContextDocument();
		result = document != nil;
	} while(false);
	return result;
}

/* Set up and call your snippet here.
*/
ErrorCode _SnpRunnerManipulateXMLElements::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode err = kCancel;
	IActiveContext* activeContext = runnableContext->GetActiveContext();
	UIDRef documentUIDRef = ::GetUIDRef(activeContext->GetContextDocument());
	SnpManipulateXMLElements instance;
	SnpXMLSampleHelper xmlHelper;
	XMLReference rootXMLRef = xmlHelper.GetRootXMLReference(documentUIDRef);
	
	PMString acquireElements("AcquireElements"); // 0
	PMString associateDTD("AssociateDTD (via helper)"); // 1
	PMString createElements("CreateElements"); //2
	PMString createComment("CreateComment/PI"); //3
	PMString modifyComment("ModifyComment/PI"); //4
	PMString tagGraphic("TagGraphic"); //5
	PMString tagStory("TagStory"); //6
	PMString tagTable("TagTable"); //7
	PMString tagText("TagTextRange"); //8
	PMString validateAgainstDTD("ValidateAgainstDTD"); //9
	
	do {
		
		
		K2Vector<PMString> choices;
		choices.push_back(acquireElements); //0
		choices.push_back(associateDTD); //1
		choices.push_back(createElements); //2
		choices.push_back(createComment); //3
		choices.push_back(modifyComment); //4
		choices.push_back(tagGraphic); //5
		choices.push_back(tagStory); //6
		choices.push_back(tagTable); //7
		choices.push_back(tagText); //8
		choices.push_back(validateAgainstDTD); //9
		choices.push_back(PMString("UnitTest")); //10
	
		Utils<ISnipRunParameterUtils> parameterUtils;
		ASSERT(parameterUtils);
		if(!parameterUtils) {
			break;
		}
		int32 choice = parameterUtils->GetChoice(PMString("What action?"), choices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		switch(choice) {
			case 0:
			{
				SNIPLOG("AcquireElements");
				SNIPLOG("--- Inspecting all elements ---");
			
				K2Vector<XMLReference> allXMLRefs;
				instance.GetFlattenedElementList(documentUIDRef,allXMLRefs);
				for(K2Vector<XMLReference>::const_iterator iter = allXMLRefs.begin();
					iter != allXMLRefs.end(); iter++) {
						XMLReference nextRef = *iter;
						SNIPLOG("Element: %s", 
							xmlHelper.AsString(nextRef).GetPlatformString().c_str());
				}
				err = allXMLRefs.size() > 0 ? kSuccess : kFailure;
				ASSERT(err == kSuccess);
			
				SNIPLOG("--- Acquire document element ---");
			
				XMLReference docXMLRef = instance.GetDocumentElementRef(documentUIDRef);
				SnpXMLHelper xmlHelper;
				SNIPLOG("Document element as string = %s", 
					xmlHelper.AsString(docXMLRef).GetPlatformString().c_str());
				InterfacePtr<IIDXMLElement> docXMLElement(docXMLRef.Instantiate());
				ASSERT(docXMLElement);
				// Just root element
				SNIPLOG("--- Acquire root element ---");
				
				XMLReference rootXMLRef = instance.GetRootElementRef(documentUIDRef);
				SNIPLOG("Root element as string = %s", 
					xmlHelper.AsString(rootXMLRef).GetPlatformString().c_str());
				
				InterfacePtr<IIDXMLElement> rootXMLElement(rootXMLRef.Instantiate());
				ASSERT(rootXMLElement);
				
				SNIPLOG("\nThis scenario showed info about elements in the logical structure");
			
			}
			break;

			case 1:
			{
				SNIPLOG("AssociateDTD");
				IDFile sysFile = xmlHelper.GetSampleFile(".dtd");
				xmlHelper.CreateSampleDTD(sysFile);
				err = xmlHelper.AssociateDTD(documentUIDRef, sysFile);
				ASSERT(err == kSuccess);
				SNIPLOG("\nThis scenario showed importing a sample DTD, see the structure-view");
			}
			break;

			case 2:
			{
				SNIPLOG("CreateElementsAndAttributes");
				K2Vector<XMLReference> elementsCreated;
				const int32 numElementsToCreate = 4;
				err = instance.CreateElements(rootXMLRef,
										PMString("section"),
										numElementsToCreate, 
										elementsCreated);	
				ASSERT(err == kSuccess);
				SNIPLOG("CreateAttributes");
				err = instance.CreateAttributes(elementsCreated, 
					PMString("new-attrib"), PMString("new-value"));	
				
				ASSERT(err == kSuccess);
				SNIPLOG("\nThis snippet created some new <section> elements and created attributes for these elements.");
			}
			break;

			case 3:
			{
				SNIPLOG("CreateComment");
				PMString commentText("My comment");
				PMString piTarget("pi-target");
				PMString piData("pi-data");
				commentText.SetTranslatable(kFalse);
				piTarget.SetTranslatable(kFalse);
				piData.SetTranslatable(kFalse);
				
				XMLReference createdCommentXMLRef, createdPIXMLRef;
				err = instance.CreateComment(rootXMLRef, 
					commentText, createdCommentXMLRef);
				ASSERT(err == kSuccess);
				SNIPLOG("CreateProcessingInstruction");
				err = instance.CreateProcessingInstruction(rootXMLRef, 
					piTarget, piData,createdPIXMLRef);
				ASSERT(err == kSuccess);
				SNIPLOG("\nThis scenario created new comments and processing instructions, check comments etc are visible in structure-view");

			}
			break;

			case 4:
			{
				SNIPLOG("ModifyComment");
				PMString commentText("My comment");
				PMString piTarget("pi-target");
				PMString piData("pi-data");
				commentText.SetTranslatable(kFalse);
				piTarget.SetTranslatable(kFalse);
				piData.SetTranslatable(kFalse);
				XMLReference commentXMLRef;
				instance.CreateComment(rootXMLRef, commentText, commentXMLRef);
				PMString newText("Modified comment text");
				newText.SetTranslatable(kFalse);
				err = instance.ModifyComment(commentXMLRef, newText);
				ASSERT(err == kSuccess);
				
				XMLReference piXMLRef;
				instance.CreateProcessingInstruction(rootXMLRef,piTarget,piData,piXMLRef);

				PMString modifiedPiTarget("Modified target");
				PMString modifiedPiData("Modified data");
				modifiedPiTarget.SetTranslatable(kFalse);
				modifiedPiData.SetTranslatable(kFalse);
				SNIPLOG("ModifyProcessingInstruction");
				err = instance.ModifyProcessingInstruction(piXMLRef, modifiedPiTarget, modifiedPiData);
				ASSERT(err == kSuccess);
				SNIPLOG("\nThis scenario modified comments and processing instructions");

			}
			break;

			case 5:
			{
				SNIPLOG("TagGraphic");
				PMRect rect;
				xmlHelper.GetNextRect(rect);
				UIDRef frameRef = xmlHelper.CreateRectangleFrame(documentUIDRef, rect, 0, 0);
				err = instance.TagGraphic(PMString("tag-graphic"), frameRef);
				ASSERT(err == kSuccess);
				SNIPLOG("\nThis scenario created a rectangle and tagged it");

			}
			break;
			
			case 6:
			{
				SNIPLOG("TagStory");
				PMRect rect;
				xmlHelper.GetNextRect(rect);
				UIDRef storyRef = xmlHelper.CreateStoryThroughFrame(
					documentUIDRef,
					rect,0,0);

				
				PMString tagName("tag-for-story");
				err = instance.TagStory(tagName, storyRef);
				
				ASSERT(err == kSuccess);
				SNIPLOG("\nThis scenario created a story and tagged it");
			} 
			break;

			case 7:
			{
				SNIPLOG("TagTable");
				PMRect rect;
				xmlHelper.GetNextRect(rect);
				UIDRef textModelUIDRef;
				UIDRef tableUIDRef;
				err = xmlHelper.CreateTableThroughFrame(documentUIDRef, rect, tableUIDRef, textModelUIDRef);
				ASSERT(err == kSuccess);
				instance.TagStory(PMString("story-tag"), textModelUIDRef);
			
				XMLReference xmlRef;
				err =  instance.TagTable( tableUIDRef, 
											PMString("table-tag"),
											PMString("cell-tag"), 
											xmlRef);
				ASSERT(err == kSuccess);
				SNIPLOG("\nThis scenario creates and tags table content");
			} 
			break;

			case 8:
			{
				SNIPLOG("TagTextRange");
				PMRect rect;
				SnpXMLSampleHelper xmlHelper;
				xmlHelper.GetNextRect(rect);
				UIDRef storyRef = xmlHelper.CreateStoryThroughFrame(documentUIDRef,
					rect,0,0);
					
				// First, tag the story, otherwise first tag we apply to the text range is applied to the story
				xmlHelper.TagStory(storyRef, PMString("story-tag"));
				//
				UIDRef firstStyleUIDRef = xmlHelper.AcquireParaStyle(documentUIDRef, PMString("para-style-1"));
				TextIndex nextIndex;
				err = xmlHelper.InsertStyledLine(storyRef,"Tagged Text 0", 0, firstStyleUIDRef, nextIndex);
				ASSERT(err == kSuccess);
				const int32 cNumberLines = 11;
				for(int32 i=0;i  < cNumberLines; i++) {
					PMString pstr("Tagged Text ");
					pstr.AppendNumber(i+1);
					PMString paraName("para-style-");
					paraName.AppendNumber(i+1);
					UIDRef styleUIDRef = 
						xmlHelper.AcquireParaStyle(documentUIDRef, paraName);

					TextIndex startIndex = nextIndex;
					err = xmlHelper.InsertStyledLine(storyRef,pstr, startIndex, styleUIDRef, nextIndex);
					ASSERT(err == kSuccess);
					PMString tagName("tag-p-");
					tagName.AppendNumber(i+1);
					// Now tag the range of text that we just created
					err = instance.TagTextRange( storyRef, tagName, startIndex, nextIndex-1);
					ASSERT(err == kSuccess);
			
					const int32 cCountZeroWidthCharsAddedToStory = 2;
					nextIndex += cCountZeroWidthCharsAddedToStory;
				}
				ASSERT(err == kSuccess);
				SNIPLOG("\nThis scenario created tagged text");
			} 
			break;

			case 9:
			{
				SNIPLOG("ValidateAgainstDTD");
				IDFile sysFile = xmlHelper.GetSampleFile(".dtd");
				xmlHelper.CreateSampleDTD(sysFile);
				xmlHelper.AssociateDTD(documentUIDRef, sysFile);	
				instance.ValidateFromRoot(activeContext);
				instance.ValidateFromElement(rootXMLRef);
				
				SDKFileHelper fileHelper(sysFile);
				SNIPLOG("\nThis scenario validated the logical structure against a sample DTD that can be found in %s",
					fileHelper.GetPath().GetPlatformString().c_str());
				// These methods don't return err codes
				err = kSuccess;

			}
			break;

			case 10:
			{
				PMString snippetName("ManipulateXMLElements");
				InterfacePtr<ISnipRunSuite> suite(activeContext->GetContextSelection(), UseDefaultIID());
				ASSERT(suite);
				if (!suite)
					break;

				if (suite->CanRun(snippetName))
				{
					// Check names above
					suite->Run(snippetName, acquireElements);
					suite->Run(snippetName, associateDTD);
					suite->Run(snippetName, createElements);
					suite->Run(snippetName, createComment);
					suite->Run(snippetName, modifyComment);
					suite->Run(snippetName, tagGraphic);
					suite->Run(snippetName, tagStory);
					suite->Run(snippetName, tagTable);
					suite->Run(snippetName, tagText);
					suite->Run(snippetName, validateAgainstDTD);
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

	
	return err;
}

/*	Declare an instance to register the snippet hook with the framework.
*/
static _SnpRunnerManipulateXMLElements instance_SnpRunnerManipulateXMLElements;
DEFINE_SNIPPET(_SnpRunnerManipulateXMLElements) 	
