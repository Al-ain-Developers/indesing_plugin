//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmldataupdater/DataUpdaterFacade.cpp $
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

// Interfaces:
#include "IDocument.h"
#include "IStoryList.h"
#include "ITextModel.h"
#include "XMLReference.h"
#include "IXMLUtils.h"
#include "IXMLReferenceData.h"
#include "IItemLockData.h"
#include "ITextStoryThread.h"
#include "IIDXMLElement.h"
// General:

#include "CmdUtils.h"
#include "CPMUnknown.h"
#include "K2Vector.h"
#include "Utils.h"
#include "UIDRef.h"
#include "ILayoutUtils.h"
#include "CAlert.h"
#include "K2Vector.tpp"

// Project:
#include "DataUpdaterUtils.h"
#include "IDataUpdaterFacade.h"
#include "DataUpdaterConst.h"
#include "DataUpdaterCSVFileHelper.h"
#include "ErrorUtils.h"


/** From SDK sample; IDataUpdaterFacade implementation.

	@ingroup xmldataupdater
*/
class DataUpdaterFacade : public CPMUnknown<IDataUpdaterFacade>
{
public:

	/** Constructor
		@param boss on which this interface is aggregated.
	*/
	DataUpdaterFacade(IPMUnknown* boss);

	/** Destructor.
	*/
	virtual ~DataUpdaterFacade();

	/** See IDataUpdaterFacade::CanInsertData.
	*/
	bool16 CanInsertData(ITextModel* iTextModel, TextIndex textIndex, int32 length);

	/** See IDataUpdaterFacade::InsertData.
	*/
	ErrorCode InsertData(ITextModel* iTextModel, TextIndex& textIndex, int32 length, const WideString& table, const WideString& key, const WideString& field, const WideString& value );

	/** See IDataUpdaterFacade::InsertAllData.
	*/
	ErrorCode InsertAllData(ITextModel* iTextModel, TextIndex& textIndex, const IDFile& file);


	/** See IDataUpdaterFacade::UpdateData.
	*/
	ErrorCode UpdateData(const UIDRef& docUIDRef, const IDFile& file);



private:
	/** Is the element one of our special DataUpdater elements?.
	*/
	bool16 IsDataUpdaterElement(XMLReference elementRef);

	/** Helper class that iterates over stories in a given document.
		@ingroup xmldataupdater
	*/ 
	class DataUpdaterStoryIterator {
	public:
		/** Constructor.
			@param docUIDRef reference to document continaing the stories
		*/
		DataUpdaterStoryIterator(const UIDRef& docUIDRef);
		
		/** Destructor.
		*/
		virtual ~DataUpdaterStoryIterator();
		
		/** Must be called after construction to get the first story and
			subsequent stories.
			@return kTrue if a story is available, kFalse otherwise
			@post DataUpdaterStoryIterator::QueryTextModel can be called to acquire the story's text model interface.
		*/
		bool16 Next();
		
		/** Query the text model interface of the current story in the iterator.
			@return ITextModel interface pointer, or nil if there is no current story
		*/
		ITextModel* QueryTextModel();
		
		/** Return kTrue if the current story is locked, kFalse otherwise.
			@return kTrue if the current story is locked, kFalse otherwise.
		*/
		bool16 IsLocked();
		
	private:
		InterfacePtr<IStoryList> fStoryList;
		int32 fIndex;
	};

	/**
	Callback function as a IXMLUtils::ForEachElement() method. 
	ForEachElement() visit every XML element of a document, this 
	callback function is the visitor. 
	*/
	class XMLDataUpdaterCallback : public IXMLUtils::IXMLCallback
	{
	public:
		XMLDataUpdaterCallback() : fTextModel(nil)
		{}
		ContinuationCode Visit(IIDXMLElement* element);
		
		ErrorCode Initialize(ITextModel * textModel, IDFile csvFile);
	private:
		ITextModel * fTextModel;
		DataUpdaterCSVFileHelper fDataFileHelper;
	};


};

/* Make the implementation available to the application.
*/
CREATE_PMINTERFACE(DataUpdaterFacade, kDataUpdaterFacadeImpl)

/*
*/
DataUpdaterFacade::DataUpdaterFacade(IPMUnknown* boss) : CPMUnknown<IDataUpdaterFacade>(boss)
{

}

/*
*/
DataUpdaterFacade::~DataUpdaterFacade()
{
}

bool16 DataUpdaterFacade::IsDataUpdaterElement(XMLReference elementRef)
{
	if (elementRef != kInvalidXMLReference)
	{
		WideString DataUpdaterStr(kDataUpdaterTagNamePrefix);
		InterfacePtr<IIDXMLElement> element(elementRef.Instantiate());
		WideString eleName = element->GetTagString();		
		if(eleName.Contains(DataUpdaterStr) == 0 || DataUpdaterStr.Contains(eleName) == 0)
			return kTrue;
	}

	return kFalse;
}
/*
*/
bool16 DataUpdaterFacade::CanInsertData(ITextModel* textModel, TextIndex textIndex, int32 length)
{
	ErrorCode result = kDataUpdaterTargetTextAlreadyTaggedErrorCode;
	do {
		InterfacePtr<IItemLockData> itemLockData(textModel, UseDefaultIID());
		if (itemLockData != nil) {
			if (itemLockData->GetInsertLock() ) 
			{	// Can't insert  data if the story is  locked.
				result = kDataUpdaterTargetStoryLockedErrorCode;
				break;
			}
		}

		RangeData targetedRange = RangeData(textIndex, textIndex + length, RangeData::kLeanForward);
		TextIndex storyThreadStart = 0;
		int32 storyThreadSpan = 0;
		textModel->GetStoryThreadSpan(textIndex, &storyThreadStart, &storyThreadSpan);

		// see if the story thread has XML tag
		InterfacePtr<ITextStoryThread> textStoryThread(textModel->QueryStoryThread(textIndex));
		InterfacePtr<IXMLReferenceData> threadXMLRefData(textStoryThread, UseDefaultIID());
		XMLReference parentXMLRef(threadXMLRefData->GetReference());
		if (!threadXMLRefData || parentXMLRef == kInvalidXMLReference)
		{	// If the story do not have XML tags at all, we can insert
			result = kSuccess;
			break;	
		}

		// story thread is tagged, see if the selection falls under a single parent element
		bool16 isIP(length == 0);
		TextIndex endIndex = textIndex + length;
		XMLReference endParentXMLRef;
		int32 startIndexInParent(0), endIndexInParent(0);
		K2Vector<XMLReference> childRefList;
		ErrorCode calParent = Utils<IXMLUtils>()->CalcXMLParent(parentXMLRef, startIndexInParent, childRefList, endParentXMLRef, endIndexInParent, textIndex, endIndex, textModel);
		if (length == 0 || calParent == IXMLUtils::kSuccessCalc)
		{
			// Find a parent, see if it is any of our special DataUpdater elements
			if (this->IsDataUpdaterElement(parentXMLRef))
				break; // If it is a DataUpdater special element, don't not insert. (While technically we could allow nested XML tags)
		}
		else 
		{
			break; // we have unmatching tags, selected across the boundary, bail out
		}

		// If we get here, insert is OK.
		result = kSuccess;

	} while(false);
	return result == kSuccess;
}

/*
*/
ErrorCode DataUpdaterFacade::InsertData(ITextModel* iTextModel, TextIndex& textIndex, int32 length, const WideString& table, const WideString& key, const WideString& field, const WideString& value )
{
	ErrorCode status = kFailure;

	do
	{		
		// Wrap the merge in a command sequence.
		CmdUtils::SequencePtr seq;
		seq->SetName(kDataUpdaterInsertSequenceStringKey);

		// Create XML tags is not yet created
		IDataBase* db = ::GetDataBase(iTextModel);

		InterfacePtr<IXMLTagList> tagList(Utils<IXMLUtils>()->QueryXMLTagList(db));
		ASSERT(tagList);
		if(!tagList) {
			break;
		}
		WideString tableTag(kDataUpdaterTableTag);
		WideString keyTag(kDataUpdaterKeyTag); 
		WideString fieldTag(kDataUpdaterFieldTag); 
		UIDRef tableRef = DataUpdaterUtils::AcquireOneTag(tagList, tableTag);
		UIDRef keyRef = DataUpdaterUtils::AcquireOneTag(tagList, keyTag);
		UIDRef fieldRef = DataUpdaterUtils::AcquireOneTag(tagList, fieldTag);
		if ((tableRef ==kInvalidUIDRef)||(keyRef ==kInvalidUIDRef)||(fieldRef ==kInvalidUIDRef))
			break;


		TextIndex startIndex = textIndex;
		// Create a buffer for the string to be inserted
		boost::shared_ptr<WideString> wideVal(new WideString(value));
		status = DataUpdaterUtils::ReplaceText(iTextModel, textIndex, length, wideVal);
		TextIndex endIndex =  textIndex + wideVal->Length();

		UIDRef storyRef = ::GetUIDRef(iTextModel);
		
		// Story will be tagged by the if it has not been tagged yet

		// tag  field
		status = DataUpdaterUtils::TagTextWithAttributeValue(fieldRef.GetUID(), storyRef,
			startIndex, endIndex, kDataUpdaterFieldNameAttribute, field);
		if (status != kSuccess)
			break;

		// tag key (record)
		endIndex += numZWCharsAdded;
		status = DataUpdaterUtils::TagTextWithAttributeValue(keyRef.GetUID(), storyRef,
			startIndex, endIndex, kDataUpdaterRecordKeyAttribute, key);
		if (status != kSuccess)
			break;

		// tag table 
		endIndex += numZWCharsAdded;
		status = DataUpdaterUtils::TagTextWithAttributeValue(tableRef.GetUID(), storyRef,
			startIndex, endIndex, kDataUpdaterTableNameAttribute, table);
		if (status != kSuccess)
			break;
		
	} while (false);

	return status;

}

/*
*/
ErrorCode DataUpdaterFacade::InsertAllData(ITextModel* iTextModel, TextIndex& textIndex, const IDFile& file)
{
	ErrorCode status = kFailure; // Will indicate sequence init/fail/success.
	
	do
	{	
		// Begin the sequence:
		CmdUtils::SequencePtr seq;
		// Name the command sequence:
		seq->SetName(kDataUpdaterInsertAllSequenceStringKey);

		// Read the file into a helper class for dealing with CSV data
		DataUpdaterCSVFileHelper csvFileHelper;
		status = csvFileHelper.Load(file);
		if (status != kSuccess) {
			break;
		}

		UIDRef storyRef = ::GetUIDRef(iTextModel);

		// Create XML tags is not yet created
		IDataBase* db = ::GetDataBase(iTextModel);
				
		InterfacePtr<IXMLTagList> tagList(Utils<IXMLUtils>()->QueryXMLTagList(db));
		ASSERT(tagList);
		if(!tagList) {
			break;
		}
		WideString tableTag(kDataUpdaterTableTag);
		WideString keyTag(kDataUpdaterKeyTag); 
		WideString fieldTag(kDataUpdaterFieldTag); 
		UIDRef tableRef = DataUpdaterUtils::AcquireOneTag(tagList, tableTag);
		UIDRef keyRef = DataUpdaterUtils::AcquireOneTag(tagList, keyTag);
		UIDRef fieldRef = DataUpdaterUtils::AcquireOneTag(tagList, fieldTag);
		if ((tableRef ==kInvalidUIDRef)||(keyRef ==kInvalidUIDRef)||(fieldRef ==kInvalidUIDRef))
			break;

		// Insert each record passed by this method's parameters.
		WideString key;
		WideString field;
		WideString value;
		const int32 kFieldsPerRecord = csvFileHelper.fFields.size();
		const int32 kMaxKeys = csvFileHelper.fKeys.size();
		

		int32 recordIndex = 0;
		int32 valueIndex = 0;
		TextIndex tableStartIndex = textIndex;
		TextIndex recordStartIndex = tableStartIndex;
		TextIndex currentPos = recordStartIndex;
		for (int32 keyIndex = 0; keyIndex < kMaxKeys; keyIndex++)
		{
			// There is one key per record
			key = csvFileHelper.fKeys [keyIndex];
			recordIndex = keyIndex * kFieldsPerRecord;
			valueIndex = 0;
			TextIndex fieldStartIndex = recordStartIndex;
			for (int32 fieldIndex = 0; fieldIndex < kFieldsPerRecord; fieldIndex++)
			{
				// Look up the value for the field:
				field = csvFileHelper.fFields [fieldIndex];
				valueIndex = recordIndex + fieldIndex;
				value = csvFileHelper.fValues [valueIndex];
				
				// Create a buffer for the string to be inserted
				boost::shared_ptr<WideString> wideVal(new WideString(value));
				status = DataUpdaterUtils::ReplaceText(iTextModel, fieldStartIndex, 0, wideVal);
				currentPos =  fieldStartIndex + wideVal->Length();

				if (status == kSuccess)
				{
					// apply field tag
					status = DataUpdaterUtils::TagTextWithAttributeValue(fieldRef.GetUID(), storyRef,
						fieldStartIndex, currentPos, kDataUpdaterFieldNameAttribute, field);
					currentPos += numZWCharsAdded; 
					
					if (status == kSuccess && fieldIndex != kFieldsPerRecord-1)
					{
						// Insert delimiter after each field, outside of the tag
						// Create a buffer for the string to be inserted
						boost::shared_ptr<WideString> delimiter(new WideString(kWideString_DataUpdaterSeparatorSpace));
						status = DataUpdaterUtils::ReplaceText(iTextModel, currentPos,0, delimiter);
						currentPos +=  delimiter->Length();
					}
				}

				fieldStartIndex = currentPos; //update for next field
			}

			// Now tag all the field values for each record on one line
			if (status == kSuccess)
			{
				status = DataUpdaterUtils::TagTextWithAttributeValue(keyRef.GetUID(), storyRef,
				recordStartIndex, currentPos, kDataUpdaterRecordKeyAttribute, key);
				if (status != kSuccess)
					break;
				currentPos += numZWCharsAdded; 
				
				// Insert a line breaker for each record
				boost::shared_ptr<WideString> recBreaker(new WideString(kWideString_DataUpdaterCarriageReturn));
				status = DataUpdaterUtils::ReplaceText(iTextModel, currentPos, 0, recBreaker);
				currentPos +=  recBreaker->Length();

			}
			//prepare for next record
			recordStartIndex = currentPos;
		}

		// now tag the whole table 
		status = DataUpdaterUtils::TagTextWithAttributeValue(tableRef.GetUID(), storyRef,
			tableStartIndex, currentPos, kDataUpdaterTableNameAttribute, csvFileHelper.fTableName);
		if (status != kSuccess)
		{
			ErrorUtils::PMSetGlobalErrorCode(status);
			break;
		}

	} while (false); // Only one time.


	return status;
}


/*
*/			
ErrorCode DataUpdaterFacade::UpdateData(const UIDRef& docUIDRef, const IDFile& file)
{
	ErrorCode status = kSuccess;

	do
	{
		// Wrap the merge in a command sequence.
		CmdUtils::SequencePtr seq;
		seq->SetName(kDataUpdaterMergeSequenceStringKey);

		// Iterate over each story in the document.
		DataUpdaterStoryIterator storyIterator(docUIDRef);
		while(status == kSuccess && storyIterator.Next()) 
		{
			if (storyIterator.IsLocked()) {
				// Skip locked stories.
				continue;
			}

			InterfacePtr<ITextModel> textModel(storyIterator.QueryTextModel());
			ASSERT(textModel);
			if (!textModel) {
				break;
			}

			InterfacePtr<IXMLReferenceData> storyXMLRefData(textModel, UseDefaultIID());
			if (!storyXMLRefData || (storyXMLRefData->GetReference() == kInvalidXMLReference)) 
				continue; // skip those story that don't have XML reference

			InterfacePtr<IIDXMLElement> storyElement(storyXMLRefData->GetReference().Instantiate());

			boost::shared_ptr<XMLDataUpdaterCallback> callback(new XMLDataUpdaterCallback());
			status = callback->Initialize(textModel, file);

			if(status != kSuccess)
				break;
  
			Utils<IXMLUtils>()->ForEachElement(storyElement, callback.get());
			status = ErrorUtils::PMGetGlobalErrorCode();

		} // end while storyIterator

		if (status != kSuccess)
			ErrorUtils::PMSetGlobalErrorCode(kSuccess);
	} while (false); // Only do once.
	
	return status;

}


// --------------------------------- DataUpdaterStoryIterator ---------------------------------------------------
/*
*/
DataUpdaterFacade::DataUpdaterStoryIterator::DataUpdaterStoryIterator(const UIDRef& docUIDRef) :
	fStoryList(nil),
	fIndex(-1)
{
	do {
		InterfacePtr<IDocument> document(docUIDRef, UseDefaultIID());
		if (!document) {
			break;
		}
		InterfacePtr<IStoryList> storyList(document, UseDefaultIID());
		if (!storyList) {
			break;
		}
		fStoryList = storyList;
	} while(false);
}

/*
*/
DataUpdaterFacade::DataUpdaterStoryIterator::~DataUpdaterStoryIterator()
{
}

/*
*/
bool16 DataUpdaterFacade::DataUpdaterStoryIterator::Next()
{
	bool16 result = kFalse;
	if (fStoryList) {
		int32 numStories = fStoryList->GetUserAccessibleStoryCount();
		if (fIndex + 1 < numStories) {
			fIndex++;
			result = kTrue;
		}
	}
	return result;
}

/*
*/
bool16 DataUpdaterFacade::DataUpdaterStoryIterator::IsLocked()
{
	bool16 result = kFalse;
	if (fStoryList && fIndex >= 0) {
		UIDRef story = fStoryList->GetNthUserAccessibleStoryUID(fIndex);
		InterfacePtr<ITextModel> textModel(story, UseDefaultIID());		
		InterfacePtr<IItemLockData> itemLockData(textModel, UseDefaultIID());
		if (itemLockData) {
			if (itemLockData->GetInsertLock() || itemLockData->GetAttributeLock()) {
				result = kTrue;
			}
		}
	}
	return result;
}

/*
*/
ITextModel* DataUpdaterFacade::DataUpdaterStoryIterator::QueryTextModel()
{
	InterfacePtr<ITextModel> result;
	if (fStoryList && fIndex >= 0) {
		UIDRef story = fStoryList->GetNthUserAccessibleStoryUID(fIndex);
		InterfacePtr<ITextModel> textModel(story, UseDefaultIID());
		result = textModel;
	}
	return result.forget();
}

//
ErrorCode DataUpdaterFacade::XMLDataUpdaterCallback::Initialize(ITextModel* textModel, IDFile csvFile)
{
	fTextModel = textModel;
	// Read the file into a helper class for dealing with CSV data
	return fDataFileHelper.Load(csvFile);
}
//Visit -- called for each node on the tree and passes it to the rule set to process.
//
IXMLUtils::IXMLCallback::ContinuationCode DataUpdaterFacade::XMLDataUpdaterCallback::Visit(IIDXMLElement* element)
{
    IXMLUtils::IXMLCallback::ContinuationCode code = IXMLUtils::IXMLCallback::kKeepIterating;
    ErrorCode err = kSuccess;

	do {

		if (!element)
			break;

		//We only care about our special XML data updater elements
		WideString tagName = element->GetTagString();
		if (tagName != kDataUpdaterFieldTag)
			break;
		WideString field = element->GetAttributeValue(kDataUpdaterFieldNameAttribute);


		//Now get "name" attributes of field, record, and table element
		XMLReference recordRef = element->GetParent();
		InterfacePtr<IIDXMLElement> recordElement(recordRef.Instantiate());
		WideString recTagName = recordElement->GetTagString();
		if (recTagName != kDataUpdaterKeyTag)
			break; //If the element's parent is not a record, bail out
		WideString key = recordElement->GetAttributeValue(kDataUpdaterRecordKeyAttribute);

		XMLReference tableRef = recordElement->GetParent();
		InterfacePtr<IIDXMLElement> tableElement(tableRef.Instantiate());
		WideString tableTagName = tableElement->GetTagString();
		if (tableTagName != kDataUpdaterTableTag)
			break; //If the element's grandparent is not a table, bail out
		WideString table = tableElement->GetAttributeValue(kDataUpdaterTableNameAttribute);

		//Find the corresponding field in the new file
		if (table != fDataFileHelper.fTableName) 
			break; // not the same table, can not update

		WideString newValue; //set to be empty if new table does not has corresponding record and field.
		// Look up the record
		K2Vector<WideString>::const_iterator keyIter = std::find(fDataFileHelper.fKeys.begin(), fDataFileHelper.fKeys.end(), key);
		int32 keyIndex = keyIter - fDataFileHelper.fKeys.begin();

		// Look up the field
		K2Vector<WideString>::const_iterator fieldIter = std::find(fDataFileHelper.fFields.begin(), fDataFileHelper.fFields.end(), field);
		int32 fieldIndex = fieldIter - fDataFileHelper.fFields.begin();
		if ( keyIndex >= 0 && fieldIndex >= 0)
		{	// Found. set the new value
			int32 recordIndex = keyIndex * fDataFileHelper.fFields.size();
			int32 valueIndex = recordIndex + fieldIndex;
			newValue = fDataFileHelper.fValues [valueIndex];
		}

		// Find the corresponding position of existing text
		TextIndex startPos; 
		TextIndex endPos;
		Utils<IXMLUtils>()->GetElementMarkerPositions(element, &startPos, &endPos);
		startPos += 1; // move forward to exclude the starting tag

		//Replace underlying text with new value
		boost::shared_ptr<WideString> wideVal(new WideString(newValue));
		err = DataUpdaterUtils::ReplaceText(fTextModel, startPos, endPos - startPos, wideVal);

 
	} while (false);

	if (err == kSuccess)
	{
		code = IXMLUtils::IXMLCallback::kKeepIterating;
	}
	else
	{
		code = IXMLUtils::IXMLCallback::kStopIterating;
	}

    return code;
}


// End DataUpdaterFacade.cpp
