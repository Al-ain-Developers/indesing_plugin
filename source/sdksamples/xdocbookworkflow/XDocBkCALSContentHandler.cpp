//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xdocbookworkflow/XDocBkCALSContentHandler.cpp $
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
#include "ITableCommands.h"
#include "ITableFrame.h"
#include "ITableModel.h"
#include "ITableTextContainer.h"
#include "ITableTextContent.h"
#include "ITableUtils.h"
#include "ITextModel.h"
#include "ITextModelCmds.h"
#include "IXDocBkFacade.h"
#include "IXMLAttributeCommands.h"
#include "IXMLImporter.h"
#include "IXMLImportOptionsPool.h"
#include "IXMLImportPreferences.h"
#include "IXMLParsingContext.h"
#include "IXMLServicesError.h"
#include "IXMLTableParsingContext.h"
#include "IXMLTagList.h"
#include "IXMLUtils.h"
#include "IXMLTagCommands.h"

// General includes
#include "CSAXDOMSerializerHandler.h"
#include "UIDList.h"
#include "XDocBkID.h"
#include "textiterator.h"
#include "XDocBkTableHelper.h"
#include "XDocBkConstants.h"

/** Implementation of ISAXDOMSerializerHandler that creates tables based
	on DocBook tables.
	Also uses our error-string service to deliver user-friendly errors
	when problems are encountered in parsing the XML data.
	
	Uses exceptions to generate clean way to abort parsing and make sure that error
	is transmitted to topmost level methods in this plug-in.

	The parsing-related methods of ISAXDOMSerializerHandler that we override (Characters,
	StartElement, EndElement) all have try-catch blocks, and exceptions are only thrown
	within the scope of these methods.

	This means that we don't propagate exceptions outside of our plug-in.

	@ingroup xdocbookworkflow
	@see ISAXDOMSerializerHandler
	@see XML Fundamentals documentation
	@see XDocBkErrorStringService, IErrorStringService
*/
class XDocBkCALSContentHandler : public CSAXDOMSerializerHandler
{
public:
	XDocBkCALSContentHandler(IPMUnknown* boss);
	virtual ~XDocBkCALSContentHandler();


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

	/**	Start parsing table
		@param ctx IN
		@param tableCtx  IN
	 */
 	void BeginTable(IXMLParsingContext* ctx, IXMLTableParsingContext* tableCtx);
	/**	Finish parsing table
		@param ctx IN
		@param tableCtx  IN
	 */
	void EndTable(IXMLParsingContext* ctx, IXMLTableParsingContext* tableCtx);

	/**	Start parsing header rows of table
		@param ctx  IN
		@param tableCtx  IN
	 */
 	void BeginHeader(IXMLParsingContext* ctx, IXMLTableParsingContext* tableCtx);

	/**	Start parsing body rows of table
		@param ctx  IN
		@param tableCtx  IN
	 */
 	void BeginBody(IXMLParsingContext* ctx, IXMLTableParsingContext* tableCtx);

	/**	Add row to existing table 
		@param ctx  IN
		@param tableCtx  IN
	 */
 	void AddRowToTable(IXMLParsingContext* ctx, IXMLTableParsingContext* tableCtx);

	/**	Add column to existing table 
		@param ctx  IN
		@param tableCtx  IN
	 */
	void AddColumnToTable(IXMLParsingContext* ctx, IXMLTableParsingContext* tableCtx);

	/**	Trim the existing table to fit the incoming XML data
		@param tableModel  IN
	 */
	void TrimTableToFitIncoming(ITableModel* tableModel);
	

	/**	Determine if string is whitespace only
		@param chars  IN
		@return bool16 kTrue if whitespace only, kFalse otherwise
	 */
	bool16 IsIgnorableWhiteSpace(const WideString& chars) const;

	/**	Put some text into the current cell
		@param chars  IN
	 */
	void ImportCellText(const WideString& chars);

	/**	Set the insertion position in the parsing context
		@param storyUIDRef 
		@param element  IN 
	 */
	void UpdateCurrentInsertionPosition(const UIDRef& storyUIDRef, IIDXMLElement* element);

	/**	Determine if element has associated story 
		@param element  IN
		@return ErrorCode kSuccess if we have associated text model, other ErrorCode otherwise
	 */
	ErrorCode VerifyElementHasAssocTextModel(IIDXMLElement *element);

	/**	Wrap a table in an element.
		This is partly a workaround because at time of writing (build 209, CS2),
		attempting to tag table created in this parsing context doesn't work correctly.

		@param textModelUIDRef IN
		@param firstTableFrameTextIndex  IN
		@param tagName  IN
		@param addAttribute  IN
		@param attrName  IN
		@param attrValue  IN
		@return ErrorCode  IN
	 */
	ErrorCode WrapTable(const UIDRef& textModelUIDRef,
							const TextIndex& firstTableFrameTextIndex, 
							const WideString& tagName,
							bool16 addAttribute,
							const WideString& attrName,
							const WideString& attrValue);					

	/**	Insert single character into story
		@param textModelUIDRef  IN
		@param where  IN
		@param whatChar  IN
		@return ErrorCode 
	 */
	ErrorCode InsertChar(const UIDRef& textModelUIDRef,
										 const TextIndex& where,
										 const textchar& whatChar);


private:
	ISAXDOMSerializerServices* fSAXServices;
	bool16 fEnabled;
};


// TODO think about adding back in exception handling to deal with malformed input

CREATE_PMINTERFACE(XDocBkCALSContentHandler, kXDocBkCALSContentHandlerImpl)

/*
*/
XDocBkCALSContentHandler::XDocBkCALSContentHandler(IPMUnknown* boss) :
	CSAXDOMSerializerHandler(boss),
	fSAXServices(nil),
	fEnabled(kFalse)
{
}

/*
*/
XDocBkCALSContentHandler::~XDocBkCALSContentHandler()
{
	if (fSAXServices) {
		fSAXServices->Release();
	}
}


/*
*/
void XDocBkCALSContentHandler::Register(ISAXDOMSerializerServices* saxServices, IPMUnknown *xmlImporter)
{
	do {
		fEnabled = Utils<IXDocBkFacade>()->IsUsingCALSContentHandler();
		if (!fEnabled) {
			break;
		}
		// end of check to see if we're turned on

		ASSERT(saxServices);
		if(!saxServices){
			break;
		}
		// Not in namespace
		saxServices->RegisterElementHandler(WideString(""), WideString(XDocBkConstants::k_INFORMALTABLE_TAG), this);
		saxServices->RegisterElementHandler(WideString(""), WideString(XDocBkConstants::k_TABLE_TAG), this);
		// Cache this interface; we need this later and don't have easy way to acquire it
		// again? 
		fSAXServices = saxServices;
		fSAXServices->AddRef();
	} while(kFalse);
}


/*
*/
bool16 XDocBkCALSContentHandler::HandlesSubElements( ) const
{
	return kTrue;
}


/*
*/
void XDocBkCALSContentHandler::Characters(const WideString& chars, IIDXMLDOMNode* currentNode)
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
			InterfacePtr<IXMLTableParsingContext> tableCtx(ctx, UseDefaultIID());
			ASSERT(tableCtx);
			if(!tableCtx) {
				break;
			}
			if (tableCtx->InTableCell() && !this->IsIgnorableWhiteSpace(chars)) {
				this->ImportCellText(chars);
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
void XDocBkCALSContentHandler::StartElement(const WideString& uri, const WideString& localname, const WideString& qname, ISAXAttributeList* attrs, IIDXMLDOMNode* currentNode)
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
			InterfacePtr<IXMLTableParsingContext> tableCtx(ctx, UseDefaultIID());
			ASSERT(ctx);
			ASSERT(tableCtx);
			if(!(ctx && tableCtx)) {
				break;
			}
			WideString lcname = qname;
			lcname.ToLower();
	
			if (lcname == XDocBkConstants::k_INFORMALTABLE_TAG ||
					lcname == XDocBkConstants::k_TABLE_TAG) { 

				this->BeginTable(ctx, tableCtx);
			}
			else if (lcname == XDocBkConstants::k_TGROUP_TAG ||
						lcname == XDocBkConstants::k_COLSPEC_TAG ||
						lcname == XDocBkConstants::k_TITLE_TAG	// formal table may have a title...
					) {
				; // Take no action... 
			}
			else if (lcname == XDocBkConstants::k_THEAD_TAG) {
				this->BeginHeader(ctx, tableCtx);
			}
			else if (lcname == XDocBkConstants::k_TBODY_TAG) {
				this->BeginBody(ctx, tableCtx);
			}
			else if (lcname == XDocBkConstants::k_ROW_TAG) {
				this->AddRowToTable(ctx, tableCtx);
			}
			else if (lcname == XDocBkConstants::k_ENTRY_TAG) {
				this->AddColumnToTable(ctx, tableCtx);
			}
			else {
				if (tableCtx->InTable()) {
					throw (ErrorCode)kXDocBkXMLParseAlreadyInTableElementErr;
				}
			}


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
void XDocBkCALSContentHandler::EndElement(const WideString& uri, 
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
			InterfacePtr<IXMLTableParsingContext> tableCtx(ctx, UseDefaultIID());
			ASSERT(tableCtx);
			if(!tableCtx) {
				break;
			}
			

			WideString lcname = qname;			
			lcname.ToLower();

			if (lcname == XDocBkConstants::k_ENTRY_TAG) {
				tableCtx->SetInCell(kFalse);
			}
			else if (lcname == XDocBkConstants::k_ROW_TAG) {
				tableCtx->SetInRow(kFalse);
			}
			else if (lcname == XDocBkConstants::k_TBODY_TAG) {
				tableCtx->SetInBody(kFalse); 
			}
			else if (lcname == XDocBkConstants::k_THEAD_TAG) {
				tableCtx->SetInHeader(kFalse);
			}
			else if (lcname == XDocBkConstants::k_TGROUP_TAG ||
						lcname == XDocBkConstants::k_COLSPEC_TAG ||
						lcname == XDocBkConstants::k_TITLE_TAG	// formal table may have a title...
					) {
				// IXMLTableParsingContext doesn't know about groups...
				;
			}
			else if (lcname == XDocBkConstants::k_INFORMALTABLE_TAG
				|| lcname == XDocBkConstants::k_TABLE_TAG) {
				this->EndTable(ctx, tableCtx);

				
			}
			else {	
				throw (ErrorCode)kXDocBkXMLParseUnknownElementErr;
			}
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
void XDocBkCALSContentHandler::BeginTable(IXMLParsingContext* ctx, 
										  IXMLTableParsingContext* tableCtx) // throws Exception
{

	do {
		ASSERT(ctx);
		ASSERT(tableCtx);
		if(!(ctx && tableCtx)) {
			break;
		}

		// Make sure that the table tag is valid at this point in structure
		if (tableCtx->InTable() && !tableCtx->InTableCell()) {
			throw (ErrorCode)kXDocBkXMLParseInTableNotInCellElementErr;
		}
		// Save the current context
		InterfacePtr<IXMLParsingContext> context(
			::CreateObject2<IXMLParsingContext>(kXMLParserLocatorBoss));
		
		ASSERT(context);
		if(!context) {
			break;
		}
		InterfacePtr<IXMLTableParsingContext> tableContext(context, UseDefaultIID());
		ASSERT(tableContext);
		if(!tableContext) {
			break;
		}
		context->Set(ctx);
		tableContext->Set(tableCtx);
		tableContext->SetInsertPos(ctx->GetInsertPos());
		ASSERT(fSAXServices);
		if(!fSAXServices) {
			break;
		}
		// We may want to Pop_Back this context in case of error
		fSAXServices->Push_Back(context);
	
		// Make sure we have a TextModel to insert a table into
		InterfacePtr<IIDXMLElement> element(ctx->GetElement().Instantiate());
		ErrorCode err = VerifyElementHasAssocTextModel(element);
		if (err != kSuccess) {
			// The method VerifyElementHasAssocTextModel can
			// return some more interesting error messages,
			// so propagate
			throw err;
		}

		// Are we already in the middle of table? Handle the nested table
		if (tableCtx->InTableCell())
		{
			tableCtx->Reset();
			tableCtx->SetInsertPos(ctx->GetInsertPos());
		}
		
		tableCtx->SetInTable(kTrue);
		tableCtx->SetTotalRows(0, 0);
	} while(kFalse);
}


void XDocBkCALSContentHandler::EndTable(IXMLParsingContext* ctx, IXMLTableParsingContext* tableCtx)
{
	do {
		ASSERT(ctx);
		ASSERT(tableCtx);
		if(!(ctx && tableCtx)) {
			break;
		}

		UIDRef tableModelUIDRef = tableCtx->GetTableRef();
		if(tableModelUIDRef.GetUID() == kInvalidUID) {
			throw (ErrorCode)kXDocBkXMLParseDontHaveTableErr;
		}
		InterfacePtr<ITableModel> tableModel(tableModelUIDRef, UseDefaultIID());
		if(!tableModel) {
			throw (ErrorCode)kXDocBkXMLParseDontHaveTableErr;
		}
		InterfacePtr<ITableCommands> tableCommands(tableModel, UseDefaultIID());
		ASSERT(tableCommands);
		if(!tableCommands) {
			break;
		}
		if (tableModelUIDRef != UIDRef::gNull)
		{
			RowRange headerRows(tableCtx->GetHeaderRows());
			if (!headerRows.IsEmpty() && tableModel->CanConvertToHeaderRows(headerRows)) {
				tableCommands->ConvertToHeaderRows(tableCtx->GetHeaderRows());
			}
			
			
			// Trim the table if the original table is larger than the data we have imported
			this->TrimTableToFitIncoming(tableModel);
			XDocBkTableHelper tableHelper(tableModelUIDRef);
			tableHelper.ApplyDefaultStyle();

			InterfacePtr<ITableTextContainer> ttContainer(tableModel, UseDefaultIID());
			ASSERT(ttContainer);
			if(!ttContainer) {
				break;
			}
			TextIndex  whereTextIndex = ttContainer->GetAnchorTextIndex();
			InterfacePtr<ITextModel> textModel(ttContainer->QueryTextModel());
			ASSERT(textModel);
			if(textModel) {
				WideString tagName(XDocBkConstants::k_PARA_TAG);
				WideString attr(XDocBkConstants::k_ROLE_ATTR); 
				WideString val("TABLEHOLDER");
				this->WrapTable(::GetUIDRef(textModel), whereTextIndex, tagName, kTrue, attr,val);
			}
			
			
		}
		
		// Restore the previous context
		InterfacePtr<IXMLTableParsingContext> tableContext(fSAXServices->Back(), UseDefaultIID());
		ASSERT(tableContext);
		ctx->SetInsertPos(tableContext->GetInsertPos());
		tableCtx->Set(tableContext);
		IXMLParsingContext* poppedContext = fSAXServices->Pop_Back();
		//
		
		// We still have to update the insertion point to account for the inserted table in this story thread.
		if (tableCtx->InTable() && (tableCtx->GetTableRef() != UIDRef::gNull))
		{
			TextIndex insertPos;
			RowRange totalRows = tableCtx->GetTotalRows();
			int32 numOfCols = tableCtx->GetNumOfCols();
			GridArea cellArea(totalRows.End() - 1, 
								numOfCols - 1, 
								totalRows.End(), 
								numOfCols);
			InterfacePtr<ITableModel> currTabl( tableCtx->GetTableRef(), UseDefaultIID());
			ASSERT(currTabl);
			if(!currTabl) {
				break;
			}
			// Don't try to get text chunk outside our table
			bool16 pred1 = (currTabl->GetTotalCols().End() >= numOfCols);
			bool16 pred2 = (currTabl->GetTotalRows().End() >= totalRows.End());
			if(pred1 && pred2) {

				InterfacePtr<ITableTextContent> textContent(currTabl, UseDefaultIID());
				ASSERT(textContent);
				if(!textContent) {
					break;
				}
				int32 numberOfChars = textContent->GetTextChunk(cellArea, insertPos);
				ctx->SetInsertPos(insertPos + numberOfChars - 1);
			} else {
				// Something badly wrong here with the data
				throw (ErrorCode)kXDocBkXMLParseCantGetTextChunkErr;
			}
		}
		else
		{
			InterfacePtr<IIDXMLElement> element(ctx->GetElement().Instantiate());
			this->UpdateCurrentInsertionPosition(ctx->GetStoryRef(), element);
		}
	} while(kFalse);
}
/*
*/
void XDocBkCALSContentHandler::UpdateCurrentInsertionPosition(const UIDRef& storyUIDRef, IIDXMLElement* element)
{
	do {
		ASSERT(fSAXServices);
		if(!fSAXServices) {
			break;
		}
		ASSERT(element);
		if(!element) {
			break;
		}
		InterfacePtr<IXMLParsingContext> ctx(fSAXServices->QueryCurrentParsingContext());
		ASSERT(ctx);
		if(!ctx) {
			break;
		}
		if (element->GetContentItem() != kInvalidUID)
		{
			TextIndex threadStart;
			int32 threadSpan = 0;
			InterfacePtr<ITextModel> textModel(storyUIDRef, UseDefaultIID());
			ASSERT(textModel);
			if(!textModel) {
				break;
			}
			textModel->GetStoryThreadSpan(ctx->GetInsertPos(), &threadStart, &threadSpan);
			ctx->SetInsertPos(threadStart + threadSpan - 1);
		}
		else
		{
			// If there are any children then we want to move the insertion point 
			// just before the current child's starting index.  If we have parsed past all of
			// the children of this element then we use the default position of just before the end tag
			int32 childCount = element->GetChildCount();
			if ((childCount > 0) && (ctx->GetChildIndex() < childCount))
			{
				XMLReference childRef(element->GetNthChild(ctx->GetChildIndex()));
				InterfacePtr<IIDXMLElement> childElement(childRef.Instantiate());
				ASSERT(childElement);
				TextIndex childStartTextIndex, childEndTextIndex;
				Utils<IXMLUtils>()->GetElementIndices(childElement, 
						&childStartTextIndex, &childEndTextIndex);
				ctx->SetInsertPos(childStartTextIndex);
			}
			else
			{
				TextIndex startTextIndex, endTextIndex;
				Utils<IXMLUtils>()->GetElementIndices(element, &startTextIndex, &endTextIndex);
				ctx->SetInsertPos(endTextIndex);
			}
		}
	} while(kFalse);
}

/*
*/
ErrorCode XDocBkCALSContentHandler::VerifyElementHasAssocTextModel(IIDXMLElement *element)
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
			err = kXDocBkCantGetTextModelFromContentItemErr;
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
		InterfacePtr<IXMLTableParsingContext> tableContext(ctx, UseDefaultIID());
		ASSERT(tableContext);
		if(!tableContext) {
			break;
		}
		tableContext->SetInsertPos(0);
	} while(kFalse);

	return err;
}


/*
*/
void XDocBkCALSContentHandler::BeginHeader(IXMLParsingContext* ctx, IXMLTableParsingContext* tableCtx)
{
	do {
		ASSERT(ctx);
		ASSERT(tableCtx);
		if(!(ctx && tableCtx)) {
			break;
		}
		// Discover if a header element is valid here
		if (tableCtx->InHeader() || tableCtx->InBody() ) {
			throw (ErrorCode)kXDocBkXMLParseHeaderCantGoHereErr;
		}
	
		// Headers have to be the first rows in the table
		if (tableCtx->GetTotalRows().End() > 0) {
			throw (ErrorCode)kXDocBkXMLHeaderFirstRowsErr;
		}
			
		tableCtx->SetInHeader(kTrue);
		tableCtx->SetHeaderRows(tableCtx->GetTotalRows().End(), 0);
	} while(kFalse);
}



/*
*/
void XDocBkCALSContentHandler::BeginBody(IXMLParsingContext* ctx, IXMLTableParsingContext* tableCtx)
{
	do {
	
		ASSERT(ctx);
		ASSERT(tableCtx);
		if(!(ctx && tableCtx)) {
			break;
		}

		// Make sure that a body is valid at this point
		if (tableCtx->InHeader() || tableCtx->InBody() ) {
			throw (ErrorCode)kXDocBkAlreadyInHeaderOrBodyErr;
		}
		
		tableCtx->SetInBody(kTrue);
	} while(kFalse);
}


/*
*/
void XDocBkCALSContentHandler::AddRowToTable(IXMLParsingContext* ctx, IXMLTableParsingContext* tableCtx)
{
	do {
		ASSERT(ctx);
		ASSERT(tableCtx);
		if(!(ctx && tableCtx)) {
			break;
		}
		// Make sure we can add a row at this point
		if (!tableCtx->InTable()){
			throw (ErrorCode)kXDocBkXMLParseCantAddRowNotInTableErr;
		}
	
		if (tableCtx->GetTableRef() != UIDRef::gNull)
		{
			InterfacePtr<ITableModel> tableModel(tableCtx->GetTableRef(), UseDefaultIID());
			
			RowRange totalRows(tableModel->GetTotalRows());
			if (totalRows.count <= tableCtx->GetTotalRows().count)
			{
				const PMReal kRowHeightContinue(0.0);
				InterfacePtr<ITableCommands> tableCommands(tableModel, UseDefaultIID());
				ASSERT(tableCommands);
				if(!tableCommands) {
					break;
				}
				tableCommands->InsertRows(RowRange(totalRows.End(), 1), Tables::eBefore, kRowHeightContinue);
			}
		}

		// Save some parsing status
		tableCtx->SetInRow(kTrue);
		tableCtx->SetNumOfCols(0);
		
		if (tableCtx->InHeader()) {
			tableCtx->SetHeaderRows(
					tableCtx->GetHeaderRows().start, 
					tableCtx->GetHeaderRows().count + 1);
		}
		else {
			tableCtx->SetInBody(kTrue);
		}

		tableCtx->SetTotalRows(
			tableCtx->GetTotalRows().start, 
			tableCtx->GetTotalRows().count + 1);
	} while(kFalse);
}


/*
*/
void XDocBkCALSContentHandler::AddColumnToTable(IXMLParsingContext* ctx, IXMLTableParsingContext* tableCtx)
{
	do {
		ASSERT(ctx);
		ASSERT(tableCtx);
		if(!(ctx && tableCtx)) {
			break;
		}
		if (!tableCtx->InTable()) {
			throw (ErrorCode)kXDocBkXMLParseNotInTableElementErr;
			
		}
		if (!tableCtx->InRow()) {
			throw (ErrorCode)kXDocBkXMLParseNotInRowElementErr;
			
		}
		
		if (tableCtx->GetTableRef() == UIDRef::gNull)
		{
			// Does a table already exist at this position in the text frame?  If so use it
			// We can't use the utility here because we need to know if table exists at this EXACT text index.
			InterfacePtr<ITextModel> textModel(ctx->GetStoryRef(), UseDefaultIID());
			ASSERT(textModel);
			if(!textModel) {
				break;
			}
			InterfacePtr<IItemStrand> itemStrand((IItemStrand*) textModel->QueryStrand(kOwnedItemStrandBoss, IID_IITEMSTRAND));
			ASSERT(itemStrand);
			if(!itemStrand) {
				break;
			}
			UID uid = itemStrand->GetOwnedUID(ctx->GetInsertPos(), kTableFrameBoss);
			if (uid != kInvalidUID)
			{
				IDataBase* db = ctx->GetElement().GetDataBase();
				InterfacePtr<ITableFrame> anchorTableFrame(db, uid, UseDefaultIID());
				ASSERT(anchorTableFrame);
				if(!anchorTableFrame) {
					break;
				}
				tableCtx->SetTableRef(anchorTableFrame->GetModelRef());
			}

			// If there isn't a table then go ahead and create one.
			if (tableCtx->GetTableRef() == UIDRef::gNull)
			{
				const PMReal kRowHeightAutoGrow(0.0);
				const PMReal kColWidth(120.0);
		
				// ITableUtils used to be on session but it's in the 'right' 
				// place now
				Utils<ITableUtils>()->InsertTable(textModel, 
													ctx->GetInsertPos(), 
													0, 
													1, 
													1, 
													kRowHeightAutoGrow, 
													kColWidth, 
													kTextContentType, 
													ITableUtils::eNoSelection);

				tableCtx->SetTableRef(
					Utils<ITableUtils>()->GetTableModel(textModel, 
												ctx->GetInsertPos()));
			}
		}
		
		InterfacePtr<ITableModel> tableModel(tableCtx->GetTableRef(), UseDefaultIID());
		ASSERT(tableModel);
		if(!tableModel) {
			break;
		}
		ColRange totalCols(tableModel->GetTotalCols());
		if (totalCols.count <= tableCtx->GetNumOfCols())
		{
			const PMReal kColumnWidthContinue(0.0);
			InterfacePtr<ITableCommands> tableCommands(tableModel, UseDefaultIID());
			ASSERT(tableCommands);
			if(!tableCommands) {
				break;
			}
			tableCommands->InsertColumns(
				ColRange(totalCols.End(), 1), Tables::eBefore, kColumnWidthContinue);
		}
		
		// Save some parsing status
		tableCtx->SetInCell(kTrue);
		tableCtx->SetNumOfCols(tableCtx->GetNumOfCols() + 1);

		if (tableCtx->GetNumOfCols() > tableCtx->GetMaxNumOfCols()) {
  			tableCtx->SetMaxNumOfCols(
					tableCtx->GetNumOfCols());
		}
		// Update our text index
		TextIndex insertPos;
		RowRange totalRows = tableCtx->GetTotalRows();
		int32 numOfCols = tableCtx->GetNumOfCols();
		// Check that we're able to get a chunk of content from this table
		// Don't try to get text chunk outside our table
		bool16 pred1 = (tableModel->GetTotalCols().End() >= numOfCols);
		bool16 pred2 = (tableModel->GetTotalRows().End() >= totalRows.End());
		if(pred1 && pred2) {
			GridArea cellArea(totalRows.End() - 1, numOfCols - 1, totalRows.End(), numOfCols);
			InterfacePtr<ITableTextContent> textContent(tableModel, UseDefaultIID());
			ASSERT(textContent);
			if(!textContent) {
				break;
			}
			int32 numberOfChars = textContent->GetTextChunk(cellArea, insertPos);

			ctx->SetInsertPos(insertPos + numberOfChars - 1);
		} else {
			throw (ErrorCode)kXDocBkXMLParseCantGetTextChunkErr;
		}
	
	} while(kFalse);
}


/*
*/
void XDocBkCALSContentHandler::TrimTableToFitIncoming(ITableModel* tableModel)
{
	do {
		ASSERT(tableModel);
		if(!tableModel) {
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
		InterfacePtr<IXMLTableParsingContext> tableCtx(ctx, UseDefaultIID());
		ASSERT(tableCtx);
		if(!tableCtx) {
			break;
		}
		InterfacePtr<ITableCommands> tableCommands(tableModel, UseDefaultIID());
		ASSERT(tableCommands);
		if(!tableCommands) {
			break;
		}
		RowRange actualBodyRows(tableModel->GetBodyRows());
		int32 numOfBodyRows = tableCtx->GetTotalRows().count - 
			(tableCtx->GetHeaderRows().count);
		// Trim the existing table to fit the incoming data,
		// Throw away any excess rows in our table
		if (actualBodyRows.count > 0 && actualBodyRows.count > numOfBodyRows) {
			int32 deletionRowCount = actualBodyRows.End() - numOfBodyRows;
			if(deletionRowCount > 0) {
				RowRange deleteRowRange(actualBodyRows.start + numOfBodyRows, deletionRowCount);
				tableCommands->DeleteRows(deleteRowRange);
			}
		}
		// Throw away any excess columns...
		ColRange totalCols(tableModel->GetTotalCols());
		int32 maxColumns = tableCtx->GetMaxNumOfCols();
		if (totalCols.count > maxColumns) {
			int32 deleteColCount = totalCols.count - maxColumns;
  			tableCommands->DeleteColumns(ColRange(maxColumns, deleteColCount));
		}


		
		
	} while(kFalse);

}


/*
*/
bool16 XDocBkCALSContentHandler::IsIgnorableWhiteSpace(const WideString& chars) const
{
	int32 length = chars.CharCount();
	int32 index = 0;
	bool16 retval = kTrue;
	
	while (index < length) {
		if (chars[index] == 0x20 || 
			chars[index] == 0x09 || 
			chars[index] == 0xA || 
			chars[index] == 0xD) {
			index++;
		}
		else {
			retval = kFalse;
			break;
		}
	}
	
	return retval;
}

/*
*/
void XDocBkCALSContentHandler::ImportCellText(const WideString& chars)
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
		InterfacePtr<IXMLTableParsingContext> tableCtx(ctx, UseDefaultIID());
		ASSERT(tableCtx);
		if(!tableCtx) {
			break;
		}
		boost::shared_ptr<WideString> textToInsert (new WideString(chars));
		
		// Replace all linefeeds with carriage returns in order to create true paragrahs in InDesign
		WideString::const_iterator_raw end = textToInsert->end_raw();
		int32 i = 0;
 		for (WideString::iterator_raw q = textToInsert->begin_raw(); q != end; i++, ++q) {		
			// Convert line feeds and Unicode paragraph separators to our internal representation, CR
			if (*q == kTextChar_LF || *q == 0x2029) {
				*q = kTextChar_CR;
			}
			
			// When we output, we replace our internal representation of soft return into the unicode version, 0x2028,
			// On import, we convert them back.  
			if (*q == 0x2028) {
				*q = kTextChar_SoftCR;
			}
		}

		InterfacePtr<ITextModelCmds> textModelCmds(ctx->GetStoryRef(), UseDefaultIID());
		ASSERT(textModelCmds);
		if(!textModelCmds) {
			break;
		}
		InterfacePtr<ICommand> insertCmd(textModelCmds->InsertCmd(ctx->GetInsertPos(), textToInsert));
		ASSERT(insertCmd);
		if(!insertCmd) {
			break;
		}
		ErrorCode err = CmdUtils::ProcessCommand (insertCmd);
		ASSERT(err == kSuccess);

		// Update our text index
		TextIndex insertPos;
		RowRange totalRows = tableCtx->GetTotalRows();
		int32 numOfCols = tableCtx->GetNumOfCols();
		InterfacePtr<ITableModel> tableModel(tableCtx->GetTableRef(), UseDefaultIID());
		ASSERT(tableModel);
		if(!tableModel) {
			break;
		}
		// Don't try to get text chunk outside our table	
		bool16 pred1 = (tableModel->GetTotalCols().End() >= numOfCols);
		bool16 pred2 = (tableModel->GetTotalRows().End() >= totalRows.End());
		if(pred1 && pred2) {

			GridArea cellArea(totalRows.End() - 1, numOfCols - 1, totalRows.End(), numOfCols);
			
			InterfacePtr<ITableTextContent> textContent(tableModel, UseDefaultIID());
			ASSERT(textContent);
			if(!textContent) {
				break;
			}
			int32 numberOfChars = textContent->GetTextChunk(cellArea, insertPos);

			ctx->SetInsertPos(insertPos + numberOfChars - 1);
		}  else {
			throw (ErrorCode)kXDocBkXMLParseCantGetTextChunkErr;
		}
	} while(kFalse);
}


/*
*/
ErrorCode XDocBkCALSContentHandler::WrapTable(const UIDRef& textModelUIDRef,
									const TextIndex& firstTableFrameTextIndex, 
									const WideString& tagName,
									bool16 addAttribute,
									const WideString& attrName,
									const WideString& attrValue)


{
	ErrorCode retval = kFailure;
	do {
		InterfacePtr<ITextModel> textModel(textModelUIDRef, UseDefaultIID());
		ASSERT(textModel);
		if(!textModel) {
			break;
		}
		InterfacePtr<IXMLTagList>	tagList(Utils<IXMLUtils>()->QueryXMLTagList(::GetDataBase(textModel)));
		ASSERT(tagList);
		if(!tagList) {
			break;
		}
		UID uid = tagList->GetTag(tagName);
		if(uid == kInvalidUID)
            retval = Utils<IXMLTagCommands>()->CreateTag (::GetUIDRef(tagList),
                                                            tagName,
                                                            kInvalidUID,
                                                            &uid);

		if(uid == kInvalidUID) break;

		TextIterator end(textModel, textModel->GetPrimaryStoryThreadSpan());
		TextIterator iter(textModel, firstTableFrameTextIndex);
		TRACE("firstTableFrameTextIndex = %d\n", firstTableFrameTextIndex);
		
		for (; iter != end; iter++)
		{
			UTF32TextChar  val = *iter;
	
			if(!(val == kTextChar_Table  || val == kTextChar_TableContinued)) {
				break;
			}
		}
		TextIndex finishedAtIndex = iter.Position();
		TRACE("finishedAtIndex = %d\n", finishedAtIndex);
		
		if(finishedAtIndex < textModel->GetPrimaryStoryThreadSpan() -1) {
			XMLReference newElement;
			Utils<IXMLElementCommands>()->CreateElement(uid, 
				textModelUIDRef, 
				firstTableFrameTextIndex-1, 
				finishedAtIndex, 
				kInvalidXMLReference, 
				&newElement);
			if(addAttribute) {
				ErrorCode err= Utils<IXMLAttributeCommands>()->CreateAttribute(newElement, (WideString)attrName, (WideString)attrValue);
				ASSERT(err == kSuccess);
			}
		
				
			retval = this->InsertChar(textModelUIDRef, finishedAtIndex+1, kTextChar_CR);
			
		}
		
		
		retval = kSuccess;
	} while(kFalse);
	return retval;
}

/*
*/
ErrorCode XDocBkCALSContentHandler::InsertChar(const UIDRef& textModelUIDRef,
										 const TextIndex& where,
										 const textchar& whatChar)
{
	ErrorCode retval = kFailure;
	do {
		InterfacePtr<ITextModelCmds> textModelCmds(textModelUIDRef, UseDefaultIID());
		ASSERT(textModelCmds);
		if(!textModelCmds) {
			break;
		}
		boost::shared_ptr<WideString> text(new WideString);
		text->Append(whatChar);

		InterfacePtr<ICommand> iInsertCmd(textModelCmds->InsertCmd(where, text));
		ASSERT(iInsertCmd);
		if(!iInsertCmd) {
			break;
		}
		ErrorCode err = CmdUtils::ProcessCommand(iInsertCmd);
		ASSERT(err==kSuccess);
		retval = err;
	} while(kFalse);

	return retval;
}


//  Code generated by DollyXS code generator
