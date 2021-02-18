//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xdocbookworkflow/XDocBkXMLPostImportIteration.cpp $
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

// Interfaces
#include "IDocument.h"
#include "IIDXMLElement.h"
#include "IImportExportFacade.h"
#include "IImportResourceCmdData.h"
#include "IImportXMLData.h"
#include "IItemStrand.h"
#include "IPlaceGun.h"
#include "IPMUnknownData.h"
#include "IPostImportResponderData.h"
#include "IRangeData.h"
#include "ITableFrame.h"
#include "ITableModel.h"
#include "ITextModelCmds.h"
#include "IUIDData.h"
#include "IXDocBkFacade.h"
#include "IXDocBkOptions.h"
#include "IURIUtils.h"

#include "IXMLImporter.h"
#include "IXMLImportOptionsPool.h"
#include "IXMLImportPreferences.h"
#include "IXMLPostImportIteration.h"
#include "IXMLReferenceData.h"
#include "IXMLUtils.h"

// General includes
#include "UIDList.h"
#include "Utils.h"
#include "textiterator.h"
#include "SDKFileHelper.h"

// Project includes
#include "XDocBkConstants.h"
#include "XDocBkID.h"


/** Implementation of a post-import iterator (IXMLPostImportIteration) that, subject to preference settings, will:
	\li place images referred to in the input
	\li delete unwanted elements in the input
	\li tag tables that were created earlier by a SAX DOM serializer handler.

	This used to require a path to the asset folder, but now it just uses the
	path relative to the XML being imported, since the XML importer (kXMLImporterBoss)
	maintains this and we have access to that through  IPostImportResponderData (see BeforeIteration).

	@see IXMLPostImportIteration
	@ingroup xdocbookworkflow
*/
class XDocBkXMLPostImportIteration : public CPMUnknown<IXMLPostImportIteration>
{
public:

	/**	Constructor
		@param boss IN refers to boss object on which this implementation is aggregated
	 */
	XDocBkXMLPostImportIteration(IPMUnknown * boss);


	/**	@see IXMLPostImportIteration::ShouldIterate
		@param responderData The responder data from kXMLImporterPostImportSignalMgrBoss.
		@return bool16 kTrue if this service should be iterated. kFalse if this service should 
		not be iterated
	*/
	virtual bool16 ShouldIterate(IPostImportResponderData* responderData);

	/**	@see IXMLPostImportIteration::BeforeIteration
		@param responderData IN refers to objects like importer (kXMLImporterBoss)
		@return ErrorCode kSuccess on success, other ErrorCode otherwise
	 */
	virtual ErrorCode BeforeIteration(IPostImportResponderData* responderData);

	/**	@see IXMLPostImportIteration::HandleElement
		@param element IN current element in iteration
		@param domNode IN 
		@return ErrorCode kSuccess on success, other ErrorCode otherwise
	 */
	virtual ErrorCode HandleElement(IIDXMLElement* element, IIDXMLDOMNode *domNode);

	/**	@see IXMLPostImportIteration::AfterIteration
		@return ErrorCode kSuccess on success, other ErrorCode otherwise
	 */
	virtual ErrorCode AfterIteration();

protected:


	/**	Attempt importing an image if the given element specifies one should be imported.
		@param element IN 
		@param domNode IN 
		@return ErrorCode 
	 */
	ErrorCode DoTryImageImport(IIDXMLElement* element, IIDXMLDOMNode* domNode);


	/**	Attempt tagging a table if given element matches our specification, a &lt;para;&gt; element
		with an attribute of TABLEHOLDER

		@param element IN 
		@param domNode IN 
		@return ErrorCode 
	 */
	ErrorCode DoTryTaggingTable(IIDXMLElement* element, IIDXMLDOMNode* domNode);


	/**	Attempt deleting an element if it matches our specification, ie tagString is what we expect
		@param element IN 
		@param domNode IN 
		@param tagString IN 
		@return ErrorCode 
	 */
	ErrorCode DoTryDeleteElement(IIDXMLElement* element, IIDXMLDOMNode* domNode, const WideString& tagString);

	/**	Try to find an image that matches the specified name, and place it in-line.
		@param element IN location of element that may contain a specification of an image we'd like to place
		@param attribName IN names the attribute that could have a media reference
		@param whereTextIndex IN locus in the textmodel where we'd like to place the graphic as inline
	 */
	void ImportAndPlace(IIDXMLElement* element, 
						const WideString& attribValue,
						const TextIndex& whereTextIndex);

	/**	Place inline graphics referenced in logical structure within the associated text model for
		 @param xmlRef IN
		 @param elemName IN 
		 @param attribName IN 
		 @param subDict IN
	*/
	void PlaceInlines(const XMLReference& xmlRef, const WideString& elemName, const WideString& attribName);
	

	/**	Method to execute an import of specified image into text model at given TextIndex
		@param sysFile IN
		@param iTextModel IN
		@param whereTextIndex IN
	 */
	void ImportImage(const IDFile& sysFile, const InterfacePtr<ITextModel>& iTextModel,const TextIndex& whereTextIndex);

	/**	Tag given table
		@param tableModelUIDRef IN 
		@param tableTagName IN 
		@param cellTagName IN 
		@param outCreatedXMLReference OUT
		@return ErrorCode kSuccess on success, other ErrorCode otherwise
	 */
	ErrorCode TagTable(const UIDRef& tableModelUIDRef,
							const WideString& tableTagName,
							const WideString& cellTagName,
							XMLReference& outCreatedXMLReference);

private:
	IDFile fXMLFileImported;
	bool16 fImageImportEnabled;
	bool16 fDeleteEnabled;
	bool16 fTagTableEnabled;
};

CREATE_PMINTERFACE(XDocBkXMLPostImportIteration, kXDocBkXMLPostImportIterationImpl)

/*
*/
XDocBkXMLPostImportIteration::XDocBkXMLPostImportIteration(IPMUnknown * boss) : 
	CPMUnknown<IXMLPostImportIteration>(boss),
		fImageImportEnabled(kFalse),
		fDeleteEnabled(kFalse),
		fTagTableEnabled(kFalse)
{}

/*
*/
bool16 XDocBkXMLPostImportIteration::ShouldIterate(IPostImportResponderData* responderData)
{
	return kTrue;
}

/*
*/
ErrorCode XDocBkXMLPostImportIteration::BeforeIteration(IPostImportResponderData* responderData)
{
	ErrorCode err(kSuccess);
	do {
		ASSERT(responderData);
		if(!responderData) {
			break;
		}
		IPMUnknown* xmlImporter = responderData->GetImporter();
		// Refers to kXMLImporterBoss
		ASSERT(xmlImporter);
		if(!xmlImporter) {
			break;
		}
		InterfacePtr<IPMUnknownData> importData(xmlImporter, UseDefaultIID());
		ASSERT(importData);
		if(!importData) {
			break;
		}
		InterfacePtr<IImportXMLData> importXMLData(importData->GetPMUnknown(), UseDefaultIID());
		ASSERT(importXMLData);
		if(!importXMLData) {
			break;
		}
		this->fXMLFileImported = importXMLData->GetImportSource();

		this->fImageImportEnabled = Utils<IXDocBkFacade>()->IsUsingPostImportIterator();
		this->fDeleteEnabled = Utils<IXDocBkFacade>()->IsDeleteInboundStrucTableElements();
		this->fTagTableEnabled = Utils<IXDocBkFacade>()->IsTaggingTable();
	} while(kFalse);
	return err;
}


/*
*/
ErrorCode XDocBkXMLPostImportIteration::HandleElement(IIDXMLElement* element, IIDXMLDOMNode *domNode)
{
	ErrorCode err(kSuccess);
	if(fImageImportEnabled) {
		err = this->DoTryImageImport(element, domNode);
		ASSERT(err == kSuccess);
	}

	if(fDeleteEnabled) {
		err = this->DoTryDeleteElement(element, domNode, XDocBkConstants::k_INFORMALTABLE_TAG);
		ASSERT(err == kSuccess);
		err = this->DoTryDeleteElement(element, domNode, XDocBkConstants::k_TABLE_TAG);
		ASSERT(err == kSuccess);
	}

	if(fTagTableEnabled) {
		err = this->DoTryTaggingTable(element, domNode);
		ASSERT(err == kSuccess);
	}
	
	return err;
}

/*
*/
ErrorCode XDocBkXMLPostImportIteration::DoTryImageImport(IIDXMLElement* element, IIDXMLDOMNode *domNode)
{
	ErrorCode err(kSuccess);
	do {

		if(!fImageImportEnabled) {
			// Not turned on
			break;
		}

		if(!element) {
			// Nothing to do
			break;
		}
		if(!element->HasAttribute((WideString)XDocBkConstants::k_FILEREF_ATTR)) {
			// Similarly, nothing to do
			break;
		}
		WideString attribValue = element->GetAttributeValue((WideString)XDocBkConstants::k_FILEREF_ATTR);
		bool16 elementHasFileRef = attribValue.CharCount()>0;
		if(!elementHasFileRef) {
			break;
		}

		InterfacePtr<ITextModel> textModel(Utils<IXMLUtils>()->QueryTextModel(element));
		ASSERT(textModel);
		if(!textModel) {
			// Maybe not inline element?
			break;
		}
		UIDRef textModelUIDRef = ::GetUIDRef(textModel);
		// Don't attempt to modify in locked story
		if(Utils<IXMLUtils>()->IsStoryLocked(textModelUIDRef)) {
			break;
		}

		// get the iIDXMLElement's content
		TextIndex startTextIndex, endTextIndex;
		if (Utils<IXMLUtils>()->GetElementIndices(element, &startTextIndex, &endTextIndex))
		{
			// marker positions returned, make sure the end is also included
			ASSERT(endTextIndex != kInvalidTextIndex);
			endTextIndex++;
		}
		this->ImportAndPlace(element, attribValue, endTextIndex+1);
	
	} while(kFalse);
	return err;
}



/*
*/
ErrorCode XDocBkXMLPostImportIteration::DoTryDeleteElement(IIDXMLElement* element, IIDXMLDOMNode* domNode, const WideString& tagString)
{
// 
	ErrorCode err(kSuccess);
	do {

		if(!fDeleteEnabled) {
			// Not turned on
			break;
		}

		if(!element) {
			// Nothing to do
			break;
		}
		if(element->GetTagString() != (WideString)tagString) {
			break;
		}
		err = Utils<IXMLElementCommands>()->DeleteElement(element->GetXMLReference(), kTrue);

	} while(kFalse);
	return err;
}


/*
*/
ErrorCode XDocBkXMLPostImportIteration::DoTryTaggingTable(IIDXMLElement* element, IIDXMLDOMNode* domNode)
{
// 
	ErrorCode err(kSuccess);
	do {

		if(!fTagTableEnabled) {
			// Not turned on
			break;
		}

		if(!element) {
			// Nothing to do
			break;
		}
		if(
			!(element->GetTagString() == (WideString)XDocBkConstants::k_PARA_TAG 
				&& element->HasAttribute((WideString)XDocBkConstants::k_ROLE_ATTR)
			)
		) {
			// Similarly, nothing to do
			break;
		}
		WideString attribValue = element->GetAttributeValue(XDocBkConstants::k_ROLE_ATTR);
		bool16 elementHasValidRole = attribValue.CharCount()>0;
		if(!elementHasValidRole) {
			break;
		}
		if(attribValue != WideString("TABLEHOLDER")) {
			break;
		}

		InterfacePtr<ITextModel> textModel(Utils<IXMLUtils>()->QueryTextModel(element));
		ASSERT(textModel);
		if(!textModel) {
			// Maybe not inline element?
			break;
		}
		UIDRef textModelUIDRef = ::GetUIDRef(textModel);
		// Don't attempt to modify in locked story
		if(Utils<IXMLUtils>()->IsStoryLocked(textModelUIDRef)) {
			break;
		}

		// get the iIDXMLElement's content
		TextIndex startTextIndex, endTextIndex;
		if (Utils<IXMLUtils>()->GetElementIndices(element, &startTextIndex, &endTextIndex))
		{
			// Go through this text range and look for ID tables
			InterfacePtr<IItemStrand> itemStrand((IItemStrand*) textModel->QueryStrand(kOwnedItemStrandBoss, IID_IITEMSTRAND));
			ASSERT(itemStrand);
			if(!itemStrand) {
				break;
			}
			TextIterator begin(textModel, startTextIndex);
			TextIterator end(textModel, endTextIndex);
			for (TextIterator iter = begin; iter != end; iter++) {
				

				UID uid = itemStrand->GetOwnedUID(iter.Position(), kTableFrameBoss);
				if (uid != kInvalidUID)
				{
					InterfacePtr<ITableFrame> anchorTableFrame(textModelUIDRef.GetDataBase(), uid, UseDefaultIID());
					ASSERT(anchorTableFrame);
					if(!anchorTableFrame) {
						break;
					}
					UIDRef tableModelUIDRef = anchorTableFrame->GetModelRef();
					XMLReference outXMLRef;
					
					ErrorCode tagErr = this->TagTable(
						tableModelUIDRef, WideString("Table"), WideString("Cell"), outXMLRef);
					ASSERT(tagErr == kSuccess);
				}
			}

		}
	} while(kFalse);
	return err;
}


/*
*/
ErrorCode XDocBkXMLPostImportIteration::AfterIteration()
{
	ErrorCode err(kSuccess);

	return err;
}



/* ImportAndPlace
*/
void XDocBkXMLPostImportIteration::ImportAndPlace(IIDXMLElement* element,
													const WideString& attribValue,
													const TextIndex& whereTextIndex)
{
	do
	{
		ASSERT(element);
		if (!element)
		{
			break;
		}

		WideString fileRef = attribValue;

		Utils<IXDocBkFacade> facade;
		ASSERT(facade);
		if (!facade)
		{
			break;
		}
		SDKFileHelper importSourceFileHelper(this->fXMLFileImported);
		//PMString currFolder(importSourceFileHelper.GetParentFolderAsString());
		//currFolder = facade->AddPathSeparator(currFolder);
		//PMString testAssetRef = currFolder + fileRef;
		// Verify if this file exists:	
		//SDKFileHelper fileHelper(testAssetRef);

		// Fix #1086490 by supporting arbitrary use of ../ in paths
		IDFile absFile = importSourceFileHelper.GetAbsoluteFromRelative(fileRef);
		SDKFileHelper fileHelper(absFile);
		if (fileHelper.IsExisting())
		{
			InterfacePtr<ITextModel> textModel(Utils<IXMLUtils>()->QueryTextModel(element));
			ASSERT(textModel);
			this->ImportImage(fileHelper.GetIDFile(),textModel,whereTextIndex);
			break;
		}
		
	
	} while (kFalse);
}


/* ImportImage
*/
void XDocBkXMLPostImportIteration::ImportImage(const IDFile& sysFile, 
								 const InterfacePtr<ITextModel>& textModel, 
								 const TextIndex& whereTextIndex)
{
	// This is to let it run clean in debug: kChangeILGCmdBoss has no translated name
	//
	CmdUtils::SequencePtr cmdSeq;
	WideString pstr("XDocBkXMLPostImportIteration::ImportImage");
	cmdSeq->SetName(pstr);

	do
	{
		ASSERT(textModel);
		if (!textModel)
		{
			ErrorUtils::PMSetGlobalErrorCode(kFailure);
			break;
		}
		IDataBase* db = ::GetDataBase(textModel);


		URI tmpURI;
		Utils<IURIUtils>()->IDFileToURI(sysFile, tmpURI);
		const bool16 retainFormat = kFalse ;
		const bool16 convertQuotes = kFalse ;
		const bool16 applyCJKGrid = kFalse ;
		bool16 useClippingFrame, skipPlace ;
		ErrorCode err = Utils<Facade::IImportExportFacade>()->ImportAndLoadPlaceGun(db, tmpURI, kMinimalUI, 
			retainFormat, convertQuotes, applyCJKGrid, useClippingFrame, skipPlace ) ;
		ASSERT(err==kSuccess);
		if (err != kSuccess)
		{
			break;
		}

		// Get the contents of the place gun
		InterfacePtr<IPlaceGun> placeGun(db, db->GetRootUID(), UseDefaultIID());
		ASSERT(placeGun);
		if (!placeGun)
		{
			ErrorUtils::PMSetGlobalErrorCode(kFailure);
			break;
		}
		UIDRef placedItem(db, placeGun->GetFirstPlaceGunItemUID());
		// no text in place gun. Do inline case

		UID inlineUID = placedItem.GetUID();
		ASSERT(inlineUID != kInvalidUID);
		if(inlineUID == kInvalidUID) {
			ErrorUtils::PMSetGlobalErrorCode(kFailure);
			break;
		}
		// insert ILG
		boost::shared_ptr<WideString>  insertMe(new WideString);
		insertMe->Append(kTextChar_Inline);

		InterfacePtr<ITextModelCmds> textModelCmds(textModel, UseDefaultIID());
		ASSERT(textModelCmds);
		if(!textModelCmds) {
			ErrorUtils::PMSetGlobalErrorCode(kFailure);
			break;
		}
		InterfacePtr<ICommand> insertCmd(textModelCmds->InsertCmd(whereTextIndex, insertMe));
		err = CmdUtils::ProcessCommand(insertCmd);
		ASSERT(err == kSuccess);
		if (err != kSuccess)
		{
			break;
		}
		InterfacePtr<ICommand> changeCmd(CmdUtils::CreateCommand(kChangeILGCmdBoss));
		ASSERT(changeCmd);
		if (!changeCmd)
		{
			ErrorUtils::PMSetGlobalErrorCode(kFailure);
			break;
		}
		InterfacePtr<IRangeData> iRangeData(changeCmd, UseDefaultIID());
		ASSERT(iRangeData);
		if (!iRangeData)
		{
			ErrorUtils::PMSetGlobalErrorCode(kFailure);
			break;  
		}
		iRangeData->Set(whereTextIndex, whereTextIndex);
		InterfacePtr<IUIDData> ilgUIDData(changeCmd, UseDefaultIID());
		ASSERT(ilgUIDData);
		if (!ilgUIDData)
		{
			ErrorUtils::PMSetGlobalErrorCode(kFailure);
			break;
		}
		ilgUIDData->Set(db, inlineUID);
		changeCmd->SetItemList(UIDList(textModel));
		err = CmdUtils::ProcessCommand(changeCmd);
		ASSERT(err == kSuccess);
		if (err != kSuccess)
		{
			break;
		}
		err = Utils<Facade::IImportExportFacade>()->ClearPlaceGun( placeGun, Facade::IImportExportFacade::kFirstItem );
		ASSERT(err == kSuccess);
	} while (kFalse);

}


/*
*/
ErrorCode XDocBkXMLPostImportIteration::TagTable(const UIDRef& tableModelUIDRef,
												const WideString& tableTagName,
												const WideString& cellTagName,
												XMLReference& outCreatedXMLReference)
{
	ErrorCode err = kSuccess;
	do {
		// + preconditions
		InterfacePtr<ITableModel> tableModel(tableModelUIDRef, UseDefaultIID());
		ASSERT(tableModel != nil);
		// - preconditions
		if(!tableModel) {
			break;
		}
		// The table might be tagged already- if so don't try to retag
	
		InterfacePtr<IXMLReferenceData> xmlReferenceData(tableModel, UseDefaultIID());
		ASSERT(xmlReferenceData);
		if(!xmlReferenceData) {
			break;
		}
		// if it refers to something... then it is tagged
		XMLReference xmlRef = xmlReferenceData->GetReference();
		// If the reference is empty- it looks like it could be tagged
		if(xmlRef == kInvalidXMLReference) {
			IDataBase* database = tableModelUIDRef.GetDataBase();
			UIDRef documentUIDRef(database, database->GetRootUID());

			err = Utils<IXMLElementCommands>()->CreateTableElement (tableTagName,
																		cellTagName,
																		tableModelUIDRef,
																		&outCreatedXMLReference);
			ASSERT(err == kSuccess);
		}
	} while(kFalse);
	return err;

}
//  Code generated by DollyXS code generator
