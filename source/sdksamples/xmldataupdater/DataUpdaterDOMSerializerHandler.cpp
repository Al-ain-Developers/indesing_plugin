//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmldataupdater/DataUpdaterDOMSerializerHandler.cpp $
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
// Interface includes
#include "IHierarchy.h"
#include "IIDXMLElement.h"
#include "IItemStrand.h"
#include "IPMUnknownData.h"
#include "ISAXAttributes.h"
#include "ISAXDOMSerializerServices.h"
#include "IDataUpdaterParsingContext.h"
#include "ITextModel.h"
#include "ITextModelCmds.h"
#include "IXMLAttributeCommands.h"
#include "IXMLImporter.h"
#include "IXMLImportOptionsPool.h"
#include "IXMLImportPreferences.h"
#include "IXMLParsingContext.h"
#include "IXMLServicesError.h"
#include "IXMLTagList.h"
#include "IXMLUtils.h"
#include "IXMLImportMatchRecorder.h"
#include "IIDXMLDOMNode.h"

// General includes
#include "CSAXDOMSerializerHandler.h"
#include "UIDList.h"
#include "textiterator.h"
#include "DataUpdaterID.h"
#include "DataUpdaterConst.h"
#include "DataUpdaterUtils.h"

/** Implementation of ISAXDOMSerializerHandler that creates individual fields
    elements that describes the value of the fields.

	For example, XML segment of 
<pre>
	<_DataUpdater_RECORD_ key="A767">
		A767, ?, Screwdriver
	</_DataUpdater_RECORD_>
</pre>
    will be changed to
<pre>
	<_DataUpdater_RECORD_ key="A767">
		<_DataUpdater_FIELD_ field="SKU">A767</_DataUpdater_FIELD_>
		<_DataUpdater_FIELD_ field="Price">?</_DataUpdater_FIELD_>
		<_DataUpdater_FIELD_ field="Description">Screwdriver</_DataUpdater_FIELD_>
	</_DataUpdater_RECORD_>
</pre>

	@ingroup xmldataupdater
	@see ISAXDOMSerializerHandler
	@see XML Fundamentals documentation
*/
class DataUpdaterDOMSerializerHandler : public CSAXDOMSerializerHandler
{
public:
	DataUpdaterDOMSerializerHandler(IPMUnknown* boss);
	virtual ~DataUpdaterDOMSerializerHandler();


	/**	@see ISAXDOMSerializerHandler::Register
	 */
	virtual void Register(ISAXDOMSerializerServices* saxServices, IPMUnknown *importer);

	/**	@see ISAXDOMSerializerHandler::HandlesSubElements
	 */
	virtual bool16 HandlesSubElements() const;

	/**	@see ISAXDOMSerializerHandler::Characters
	 */
	virtual void Characters(const WideString& chars, IIDXMLDOMNode* currentNode);

	/**	@see ISAXDOMSerializerHandler::StartElement
		 */
	virtual void StartElement(const WideString& uri, const WideString& localname, const WideString& qname, ISAXAttributeList* attrs, IIDXMLDOMNode* currentNode);

	/**	@see ISAXDOMSerializerHandler::EndElement
	 */
	virtual void EndElement(const WideString& uri, const WideString& localname, const WideString& qname, IIDXMLDOMNode* currentNode);

protected:

	/**	Put some text into the current cell
		@param chars  IN
	 */
	void ImportRecord(const WideString& chars);

	/**	Put some text into the current cell
		@param chars  IN
	 */
	void ImportWholeTable(const WideString& chars);
	void BeginRecord(IXMLParsingContext *ctx, IIDXMLDOMNode* currentNode);
	void BeginTable(IXMLParsingContext *ctx, IIDXMLDOMNode* currentNode);
	void EndRecord(IXMLParsingContext *ctx);
	void EndTable(IXMLParsingContext *ctx);

	/**	Determine if element has associated story 
		@param element  IN
		@return ErrorCode kSuccess if we have associated text model, other ErrorCode otherwise
	 */
	ErrorCode VerifyElementHasAssocTextModel(IIDXMLElement *element);


	/** Parsing a record string to inserted into story
		@param chars IN The record string
		@param insertPos  IN/OUT where the record should be inserted
		@param storyUIDRef  IN the story
		@param parentXMLR IN parent XMLReference
		@return ErrorCode 
	*/
	ErrorCode  HandleARecord(const WideString& chars, TextIndex &insertPos, UIDRef storyUIDRef, XMLReference &parentXMLR);
private:
	/**
	   Does the node has at least one child element
	*/
	bool16 HasElementChildNode(IIDXMLDOMNode* node);
	/**
	   Does the string only contain ignorable white space
	*/
    bool16 IsIgnorableWhiteSpace(const WideString& chars) const;

	/**
	   Break string into lines with linefeed or carriage return
	*/
 	void BreakLines (WideString& stringToBreak, K2Vector<WideString> &result);

	/**
	   Delete any contents and elements of a XMLElement
	*/
	void ClearXMLChildrenAndContents (UIDRef storyRef, XMLReference elementRef);

	ISAXDOMSerializerServices* fSAXServices;
	IXMLImportMatchRecorder* fMatchRecorder;
	bool16 fEnabled;  //TODO, add a preference to xmlimport dialog
};



CREATE_PMINTERFACE(DataUpdaterDOMSerializerHandler, kDataUpdaterDOMSerializerHandlerImpl)

/*
*/
DataUpdaterDOMSerializerHandler::DataUpdaterDOMSerializerHandler(IPMUnknown* boss) :
	CSAXDOMSerializerHandler(boss),
	fSAXServices(nil),
	fMatchRecorder(nil),
	fEnabled(kTrue)
{
}

/*
*/
DataUpdaterDOMSerializerHandler::~DataUpdaterDOMSerializerHandler()
{
	if (fSAXServices) 
		fSAXServices->Release();
	
	if (fMatchRecorder)
		fMatchRecorder->Release();
}


/*
*/
void DataUpdaterDOMSerializerHandler::Register(ISAXDOMSerializerServices* saxServices, IPMUnknown *xmlImporter)
{
	do {
		// TODO Get fEnabled = ???;
		if (!fEnabled) {
			break;
		}

		ASSERT(saxServices);
		if(!saxServices){
			break;
		}

		// Not in namespace
		saxServices->RegisterElementHandler(WideString(""), WideString(kDataUpdaterKeyTag), this);
		saxServices->RegisterElementHandler(WideString(""), WideString(kDataUpdaterTableTag), this);

		// Cache this interface; 
		fSAXServices = saxServices;
		fSAXServices->AddRef();

		// Set get match recorder
		// clear out any remaining stuff from last time
		if (fMatchRecorder)
		{
			fMatchRecorder->Release();
			fMatchRecorder = nil;
		}
		if (xmlImporter)
			fMatchRecorder = static_cast<IXMLImportMatchRecorder*>(xmlImporter->QueryInterface(IXMLImportMatchRecorder::kDefaultIID));

	} while(kFalse);
}


/*
*/
bool16 DataUpdaterDOMSerializerHandler::HandlesSubElements( ) const
{
	return kFalse;
}


/*
*/
void DataUpdaterDOMSerializerHandler::Characters(const WideString& chars, IIDXMLDOMNode* currentNode)
{
	try {

		do{

			if(!fEnabled) {
				break;
			}

			InterfacePtr<IXMLParsingContext> ctx(fSAXServices->QueryCurrentParsingContext());
			ASSERT(ctx);
			if(!ctx) {
				break;
			}

			InterfacePtr<IDataUpdaterParsingContext> duContext(ctx, UseDefaultIID());
			IDataUpdaterParsingContext::ParsingState pState = duContext->GetParsingState();
			if (pState == IDataUpdaterParsingContext::kWithinTableNoChild)
				this->ImportWholeTable(chars);
			else if (pState == IDataUpdaterParsingContext::kWithinRecordNoChild)
				this->ImportRecord(chars);
			else if (pState == IDataUpdaterParsingContext::kWithinRecordHasChildren)
			{ //This is the case where everfield is present

			}
			else
			{   
				if (!this->IsIgnorableWhiteSpace(chars))
				{
					//insert comming characters into the current insertion postion
					TextIndex startTextIndex = ctx->GetInsertPos();
					WideString charsToInsert(chars);
					UIDRef storyUIDRef = ctx->GetStoryRef();
					InterfacePtr<ITextModel> textModel(storyUIDRef, UseDefaultIID());	
					textModel->Insert(startTextIndex, &charsToInsert);
					TextIndex endIndex =  startTextIndex + charsToInsert.Length();
					// Update insertion position
					ctx->SetInsertPos( endIndex);		
				}
			}
		
		}
		while(kFalse);

	} // end of try block
	catch (ErrorCode code)
	{
		if(fSAXServices) {
			InterfacePtr<IXMLParsingContext> ctx(fSAXServices->QueryCurrentParsingContext());
			InterfacePtr<IXMLServicesError> servicesError(fSAXServices, UseDefaultIID());
			if(servicesError) {
				servicesError->SetErrorCode(code);
				if(ctx) {
					servicesError->SetErrorTag(ctx->GetTagName());
				}
			}
		}
	
	}

	
}



/*
*/
void DataUpdaterDOMSerializerHandler::StartElement(const WideString& uri, const WideString& localname, const WideString& qname, ISAXAttributeList* attrs, IIDXMLDOMNode* currentNode)
{
	try {


		do
		{
			if(!fEnabled) {
				break;
			}
			ASSERT(fSAXServices);
			if(!fSAXServices) {
				break;
			}
			InterfacePtr<IXMLParsingContext> ctx(fSAXServices->QueryCurrentParsingContext());
			ASSERT(ctx);
			if(!ctx) {
				break;
			}
			WideString lcname = qname;		
	
			if (lcname == kDataUpdaterKeyTag)
			{
				this->BeginRecord(ctx, currentNode);
			}
			else if (lcname == kDataUpdaterTableTag)
				this->BeginTable(ctx, currentNode);

		} while(kFalse);

	} // try block
	catch (ErrorCode code)
	{
		InterfacePtr<IXMLServicesError> servicesError(fSAXServices, UseDefaultIID());
		if(servicesError) {
			servicesError->SetErrorCode(code);
			servicesError->SetErrorTag(qname);
		}
		
	}
}

/*
*/
void DataUpdaterDOMSerializerHandler::EndElement(const WideString& uri, 
										  const WideString& localname, 
										  const WideString& qname, IIDXMLDOMNode* currentNode )
{

	

	try {

		do
		{
			if(!fEnabled) {
				break;
			}

			ASSERT(fSAXServices);
			if(!fSAXServices) {
				break;
			}
			InterfacePtr<IXMLParsingContext> ctx(fSAXServices->QueryCurrentParsingContext());
			ASSERT(ctx);
			if(!ctx) {
				break;
			}

			WideString lcname = qname;
		
			if (lcname == kDataUpdaterKeyTag)
				this->EndRecord(ctx);
			else if (lcname == kDataUpdaterTableTag) 
				this->EndTable(ctx);

		} while(kFalse);

	} // try block
	catch (ErrorCode code)
	{
		InterfacePtr<IXMLServicesError> servicesError(fSAXServices, UseDefaultIID());
		if(servicesError) {
			servicesError->SetErrorCode(code);
			servicesError->SetErrorTag(qname);
		}
		
	}
}

/*
*/
void DataUpdaterDOMSerializerHandler::BeginTable(IXMLParsingContext* ctx, IIDXMLDOMNode* currentNode)
{

	do {
		ASSERT(ctx);
		
		// Make sure we have a TextModel to insert a table into.
		// The element we get from ctx set the default/other content handler, a story
		InterfacePtr<IIDXMLElement> existingelement(ctx->GetElement().Instantiate());
		ErrorCode err = VerifyElementHasAssocTextModel(existingelement);
		if (err != kSuccess) {
			throw err;
		}

		//Set parsing context. 
		//We need to find our own matched DataUpdate_Table element
		XMLReference elementRef;
		if (fMatchRecorder && fMatchRecorder->FindMatch(currentNode, &elementRef))
		{
			TextIndex startTextIndex, endTextIndex;
			InterfacePtr<IIDXMLElement> element(elementRef.Instantiate());
			if (Utils<IXMLUtils>()->GetElementIndices(element, &startTextIndex, &endTextIndex)) {
				// marker position returned, move over the marker
				startTextIndex++;
			}
			ctx->SetInsertPos(startTextIndex);
		}

		InterfacePtr<IDataUpdaterParsingContext> duContext(ctx, UseDefaultIID());
		duContext->SetParsingElement(elementRef);
		if (this->HasElementChildNode(currentNode) )
			duContext->SetParsingState(IDataUpdaterParsingContext::kWithinTableHasChildren);
		else
			duContext->SetParsingState(IDataUpdaterParsingContext::kWithinTableNoChild);

	} while(kFalse);
}


void DataUpdaterDOMSerializerHandler::EndTable(IXMLParsingContext* ctx)
{
	do {
		ASSERT(ctx);
		if(!ctx) 
			break;

		//Set parsing context
		InterfacePtr<IDataUpdaterParsingContext> duContext(ctx, UseDefaultIID());
		duContext->SetParsingState(IDataUpdaterParsingContext::kOutside);
	} while(kFalse);
}


void DataUpdaterDOMSerializerHandler::BeginRecord(IXMLParsingContext* ctx, IIDXMLDOMNode* currentNode)
{

	do {
		ASSERT(ctx);

		XMLReference elementRef;
		if (fMatchRecorder && fMatchRecorder->FindMatch(currentNode, &elementRef))
		{
			TextIndex startTextIndex, endTextIndex;
			InterfacePtr<IIDXMLElement> element(elementRef.Instantiate());
			if (Utils<IXMLUtils>()->GetElementIndices(element, &startTextIndex, &endTextIndex)) {
				// marker position returned, move over the marker
				startTextIndex++;
			}
			ctx->SetInsertPos(startTextIndex);
		}

		//Set parsing context
		InterfacePtr<IDataUpdaterParsingContext> duContext(ctx, UseDefaultIID());
		duContext->SetParsingElement(elementRef);
		if (this->HasElementChildNode(currentNode) )
			duContext->SetParsingState(IDataUpdaterParsingContext::kWithinRecordHasChildren);
		else
			duContext->SetParsingState(IDataUpdaterParsingContext::kWithinRecordNoChild);

	} while(kFalse);
}


void DataUpdaterDOMSerializerHandler::EndRecord(IXMLParsingContext* ctx)
{
	do {
		ASSERT(ctx);
		if(!ctx) 
			break;

		//Set parsing context
		InterfacePtr<IDataUpdaterParsingContext> duContext(ctx, UseDefaultIID());
		duContext->SetParsingState(IDataUpdaterParsingContext::kWithinTableHasChildren);

		//break records with line breaker
		TextIndex startTextIndex = ctx->GetInsertPos() + 1; //after ending record marker
		UIDRef storyUIDRef = ctx->GetStoryRef();
		InterfacePtr<ITextModel> textModel(storyUIDRef, UseDefaultIID());	
		WideString recBreaker(kWideString_DataUpdaterCarriageReturn);
		textModel->Insert(startTextIndex, &recBreaker);
		TextIndex endIndex =  startTextIndex + recBreaker.Length();
		// Update insertion position
		ctx->SetInsertPos( endIndex);		

	} while(kFalse);
}


/*
*/
ErrorCode DataUpdaterDOMSerializerHandler::VerifyElementHasAssocTextModel(IIDXMLElement *element)
{
	ErrorCode err = kFailure;
	do {

		ASSERT(element);
		if(!element) {
			break;
		}

		// any existing text element must live in a TextModel
		if (element->GetContentItem() == kInvalidUID) {
			err = kSuccess;
			break;
		}
		// see if the content the element is pointing to has a TextModel
		UID contentItem(element->GetContentItem());
		IDataBase *db = element->GetXMLReference().GetDataBase();
		InterfacePtr<ITextModel> textModel(db, contentItem, UseDefaultIID());
		if (textModel) {
			err = kSuccess;
			break;
		}
		// no TextModel, need to convert page item to a text frame
		InterfacePtr<IHierarchy> hierarchy(db, contentItem, UseDefaultIID());
		ASSERT(hierarchy);
		if(!hierarchy) {
			break;
		}
		InterfacePtr<ICommand> convertToTextFrameCmd(CmdUtils::CreateCommand(kConvertItemToTextCmdBoss));
		ASSERT(convertToTextFrameCmd);
		if(!convertToTextFrameCmd) {
			break;
		}
		UIDList uidList(db, hierarchy->GetParentUID());
		convertToTextFrameCmd->SetItemList(uidList);
		err = CmdUtils::ProcessCommand(convertToTextFrameCmd);
		ASSERT(err == kSuccess);
		if (err != kSuccess) {
			break;
		}

		// make sure we have a TextModel now
		InterfacePtr<ITextModel> newTextModel(db, element->GetContentItem(), UseDefaultIID());
		ASSERT(newTextModel);
		if (!newTextModel)
		{
			break;
		}

		// update insert info
		InterfacePtr<IXMLParsingContext> ctx(fSAXServices->QueryCurrentParsingContext());
		ASSERT(ctx);
		if(!ctx) {
			break;
		}
		ctx->SetStoryRef(UIDRef(db, element->GetContentItem()));
		ctx->SetInsertPos(0);
	} while(kFalse);

	return err;
}



/*
*/
void DataUpdaterDOMSerializerHandler::ImportRecord(const WideString& chars)
{
	do {
		ASSERT(fSAXServices);
		if(!fSAXServices) {
			break;
		}
	
		InterfacePtr<IXMLParsingContext> ctx(fSAXServices->QueryCurrentParsingContext());
		ASSERT(ctx);
		if(!ctx) {
			break;
		}

		UIDRef storyUIDRef = ctx->GetStoryRef();
		TextIndex startTextIndex = ctx->GetInsertPos();

		InterfacePtr<IDataUpdaterParsingContext> duContext(ctx, UseDefaultIID());
		XMLReference parentXMLR = duContext->GetParsingElement();
		this->ClearXMLChildrenAndContents(storyUIDRef, parentXMLR);

		this->HandleARecord(chars, startTextIndex,storyUIDRef, parentXMLR);
		// Update insertion position
		ctx->SetInsertPos( startTextIndex );		
	} while(kFalse);
}

/*
*/
ErrorCode  DataUpdaterDOMSerializerHandler::HandleARecord(const WideString& chars, TextIndex &insertPos, UIDRef storyUIDRef, XMLReference &parentXMLR)
{
	ErrorCode  err = kSuccess;
	WideString delimiterComma(",");
	do {
		// Process the string
		K2::scoped_ptr<WideString> sku (chars.GetItem (delimiterComma, 1));
		K2::scoped_ptr<WideString> price (chars.GetItem (delimiterComma, 2));
		K2::scoped_ptr<WideString> description (chars.GetItem (delimiterComma, 3));
		ASSERT_MSG(sku && price && description, "Ill formated record!");

		if (!sku || !price || !description)
		{
			err = kFailure;
			break;
		}

		WideString delimiter(kWideString_DataUpdaterSeparatorSpace);
		WideString fieldTag(kDataUpdaterFieldTag);

		WideString keyString(k_DataUpdatekeyString);
		WideString priceString(k_DataUpdatepriceString);
		WideString descString(k_DataUpdatedescriptionString);

		InterfacePtr<ITextModel> textModel(storyUIDRef, UseDefaultIID());	
		TextIndex startTextIndex = insertPos;

		// insert SKU
		textModel->Insert(startTextIndex, sku.get());
		TextIndex endIndex =  startTextIndex + sku->Length();
		XMLReference createdElement;
        Utils<IXMLElementCommands>()->CreateElement(fieldTag, storyUIDRef, startTextIndex, endIndex, parentXMLR, &createdElement);
		Utils<IXMLAttributeCommands>()->CreateAttribute(createdElement,kDataUpdaterFieldNameAttribute, (WideString)keyString);
		endIndex += numZWCharsAdded;
		textModel->Insert(endIndex, &delimiter);
		endIndex += delimiter.Length();

		// insert price
		TextIndex newStart = endIndex;
		textModel->Insert(newStart, price.get());
		endIndex =  newStart + price->Length();
		XMLReference priceElement;
        Utils<IXMLElementCommands>()->CreateElement(fieldTag, storyUIDRef, newStart, endIndex, parentXMLR, &priceElement);
		Utils<IXMLAttributeCommands>()->CreateAttribute(priceElement,kDataUpdaterFieldNameAttribute, (WideString)priceString);
		endIndex += numZWCharsAdded;
		textModel->Insert(endIndex, &delimiter);
		endIndex += delimiter.Length();

		// insert description
		newStart = endIndex;
		textModel->Insert(newStart, description.get());
		endIndex =  newStart + description->Length();
		XMLReference descElement;
        Utils<IXMLElementCommands>()->CreateElement(fieldTag, storyUIDRef, newStart, endIndex, parentXMLR, &descElement);
		Utils<IXMLAttributeCommands>()->CreateAttribute(descElement,kDataUpdaterFieldNameAttribute, (WideString)descString);
		endIndex += numZWCharsAdded;
		textModel->Insert(endIndex, &delimiter);
		endIndex += delimiter.Length();

		// Update insertion position
		insertPos = endIndex;

	} while(kFalse);

	return err;
}

void DataUpdaterDOMSerializerHandler::ImportWholeTable(const WideString& chars)
{
	do {
		ASSERT(fSAXServices);
		if(!fSAXServices) {
			break;
		}
	

		InterfacePtr<IXMLParsingContext> ctx(fSAXServices->QueryCurrentParsingContext());
		ASSERT(ctx);
		if(!ctx) {
			break;
		}

		UIDRef storyUIDRef = ctx->GetStoryRef();
		InterfacePtr<ITextModel> textModel(storyUIDRef, UseDefaultIID());	

		// Process the string
        K2Vector <WideString> recordStrings;
		WideString workingString(chars);

		this->BreakLines(workingString,recordStrings);

		//Now insert every record
		WideString recordTag(kDataUpdaterKeyTag);

		InterfacePtr<IDataUpdaterParsingContext> duContext(ctx, UseDefaultIID());
		XMLReference parentXMLR = duContext->GetParsingElement();// should be the table
        //Clear existing content of the first
		this->ClearXMLChildrenAndContents(storyUIDRef, parentXMLR);

		TextIndex startTextIndex = ctx->GetInsertPos();
		TextIndex recordStartIndex = startTextIndex; 
		TextIndex recordEndIndex = startTextIndex;
		WideString record = WideString("");
        K2Vector<WideString>::const_iterator iter = recordStrings.begin();
        while (iter != recordStrings.end())
        {
			record = *iter;
			if (iter == recordStrings.begin() 
				&& record.Contains(k_DataUpdatekeyString) 
				&& record.Contains(k_DataUpdatepriceString) 
				&& record.Contains(k_DataUpdatedescriptionString))
			{
				//this is the first line header, should not appears in XML
				iter++;
				continue;
			}
			recordStartIndex = recordEndIndex; //last record ending
			recordEndIndex = recordStartIndex;
			this->HandleARecord(WideString(record), recordEndIndex,storyUIDRef, parentXMLR);
			// Tag the record
			XMLReference recElement;
			K2::scoped_ptr<WideString> key (record.GetItem (WideString(","), 1));
			Utils<IXMLElementCommands>()->CreateElement(recordTag, storyUIDRef, recordStartIndex, recordEndIndex, parentXMLR, &recElement);
			Utils<IXMLAttributeCommands>()->CreateAttribute(recElement,kDataUpdaterRecordKeyAttribute, (WideString)*key);
			recordEndIndex += numZWCharsAdded; 

			// Insert a line breaker for each record
			WideString recBreaker(kWideString_DataUpdaterCarriageReturn);
			textModel->Insert(recordEndIndex, &recBreaker);
			recordEndIndex +=  recBreaker.Length();
            iter++;
		}
  
		// Update insertion position
		ctx->SetInsertPos( recordEndIndex );		
		
	} while(kFalse);
}

bool16 DataUpdaterDOMSerializerHandler::HasElementChildNode(IIDXMLDOMNode* node)
{
    bool16 hasElementChild(kFalse);

    if (node->IsValid() && node->GetNodeType() == IIDXMLDOMNode::kElement && node->HasChildNodes()) {
        IIDXMLDOMNode *child = node->GetFirstChild();
        while (child && !hasElementChild) {
            if (child->GetNodeType() == IIDXMLDOMNode::kElement) {
                hasElementChild = kTrue;
            }
            else {
                child = child->GetNextSibling();
            }
        }
    }

    return hasElementChild;
}

bool16 DataUpdaterDOMSerializerHandler::IsIgnorableWhiteSpace(const WideString& chars) const
{
    int32 length = chars.CharCount();
    int32 index = 0;
    while (index < length)
    {
        if (chars[index] == 0x20 || chars[index] == 0x09 || chars[index] == 0xA || chars[index] == 0xD)
            index++;
        else
            return kFalse;
    }

    return kTrue;
}

void DataUpdaterDOMSerializerHandler::BreakLines (WideString& stringToBreak, K2Vector<WideString> &result)
{	
	CharCounter totalNumChars = stringToBreak.CharCount();
	CharCounter charsProcessed = 0, onelineLength = 0;
	
	WideString *oneline = nil;
	while(charsProcessed < totalNumChars)
	{
		// guess at this line: if there is a \n somewhere, guess that is where we will break. otherwise guess the entire string.
		// We now break on \n, or \r, or \r\n
		CharCounter iLineFeedPos = stringToBreak.IndexOf('\n',charsProcessed);
		CharCounter iCarriageReturnPos = stringToBreak.IndexOf('\r',charsProcessed);
		if (iLineFeedPos >= 0 || iCarriageReturnPos >= 0)
		{
			if (iLineFeedPos >= 0 && (iCarriageReturnPos == -1 || iLineFeedPos < iCarriageReturnPos) )
				oneline = stringToBreak.Substring(charsProcessed, iLineFeedPos - charsProcessed);
			else
				oneline = stringToBreak.Substring(charsProcessed, iCarriageReturnPos - charsProcessed);
		}
		else
		{
 			oneline = stringToBreak.Substring(charsProcessed, kMaxInt32);
		}

		if(oneline)
		{

			// cache onelineLength because Length is slow for long 2byte strings
			onelineLength = oneline->CharCount();
			charsProcessed += onelineLength;
			result.push_back(*oneline);
			delete oneline;
		}
		if(iLineFeedPos == charsProcessed)
			charsProcessed += 1; // if we are breaking at a linefeed, consider it processed.
		if(iCarriageReturnPos == charsProcessed)
		{
			 // if we are breaking at a carriage return, check for a following linefeed, then consider them processed.
			if (iLineFeedPos == (iCarriageReturnPos + 1))
				charsProcessed += 2;
			else
				charsProcessed += 1;
		}
	}
}

void DataUpdaterDOMSerializerHandler::ClearXMLChildrenAndContents (UIDRef storyRef, XMLReference elementRef)
{
	InterfacePtr<IIDXMLElement> element(elementRef.Instantiate());
	if (element->GetChildCount()> 0)
	{ 
		for (int32 i = element->GetChildCount()-1; i>=0; i--) 
		{
			XMLReference nthChild = element->GetNthChild(i);
			Utils<IXMLElementCommands>()->DeleteElementAndContent(nthChild);
		}
	}
}