//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmlmarkupinjector/XMLMrkSuiteTextCSB.cpp $
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
#include "ITextTarget.h"
#include "IXMLElementCommands.h"
#include "IXMLAttributeCommands.h"
#include "IXMLTagList.h"
#include "IXMLElementCommands.h"
#include "IXMLUtils.h"
#include "ITextSelectionSuite.h"
#include "IIDXMLElement.h"
#include "ITextModel.h"
#include "IXMLMrkSuite.h"
#include "ITextModelCmds.h" // New for 3.0
// General includes:
#include "CPMUnknown.h"
#include "RangeData.h"
#include "TextChar.h"
#include "TextPair.h"
#include "textiterator.h"
#include "K2Vector.tpp"
#include "DataWrapper.h"
// Project includes:
#include "XMLMrkConstants.h"
#include "XMLMrkID.h"



/** Represents the location within the text model of the start/end index for the text within each column,
	for an entire row.
	@ingroup xmlmarkupinjector
*/
typedef K2Vector<TextPair> ColumnEnds;


/** An operator that is used in deciding which row is the 'widest', that is, which contains the most columns.
	@ingroup xmlmarkupinjector
*/
struct SmallerSize : public std::binary_function<const ColumnEnds& , const ColumnEnds&, bool>
{
	/** Returns the wider of the two rows associated with the ColumEnds type. */
	bool operator()(const ColumnEnds& x, const ColumnEnds& y) const
	{
		return x.size() < y.size();
	}
};

/**
	Class XMLMrkSuiteTextCSB.
	This is the implementation of IXMLMrkSuite on the text selection boss class.
	
	@ingroup xmlmarkupinjector
*/
class XMLMrkSuiteTextCSB : public CPMUnknown<IXMLMrkSuite>
{
	public:
		/** Constructor.
			@param boss boss object on which this interface is aggregated.
		 */
		XMLMrkSuiteTextCSB (IPMUnknown *boss);

		/** Destructor.
		 */
		virtual ~XMLMrkSuiteTextCSB (void);

	public:
	
	

		/**	See IXMLMrkSuite::CanMakeTable
			@param none
			@return bool16 
		 */
		virtual bool16 CanMakeTable() const;

	
		/**	IXMLMrkSuite::MakeTable
			@param hasHeaderRow 
			@return ErrorCode 
		 */
		virtual ErrorCode MakeTable(bool16 hasHeaderRow);

		/**	See IXMLMrkSuite::CanMakeKeywordSet
			@param none
			@return bool16 
		 */
		virtual bool16 CanMakeKeywordSet() const ;

	
		/**	See IXMLMrkSuite::MakeKeywordSet
			@param none
			@return ErrorCode 
		 */
		virtual ErrorCode MakeKeywordSet() ;

		/**	See IXMLMrkSuite::CanMakeItemizedList
			@param none
			@return bool16 
		 */
		virtual bool16 CanMakeItemizedList() const ;

		/**	See IXMLMrkSuite::MakeItemizedList
			@param none
			@return ErrorCode 
		 */
		virtual ErrorCode MakeItemizedList() ;

		/**	See IXMLMrkSuite::CanMakeSectionComposite
			@param none
			@return bool16 
		 */
		virtual bool16 CanMakeSectionComposite() const ;


		/**	See IXMLMrkSuite::MakeSectionComposite
			@param none
			@return ErrorCode 
		 */
		virtual ErrorCode MakeSectionComposite() ;

		/**	See IXMLMrkSuite::CanMakeMediaObject
			@param none
			@return bool16 
		 */
		virtual bool16 CanMakeMediaObject() const;


		/**	See IXMLMrkSuite::MakeMediaObject
			@param none
			@return ErrorCode 
		 */
		virtual ErrorCode MakeMediaObject();

	protected:

		/**
		   Determine many columns are present given the ColumnEnds.
		   @param rows represents the rows (in terms of the sets of TextPair's for each column)
		   @return 	int32 giving the maximum number of columns across the rows 
		 */
		int32 getMaxNumberCols(const K2Vector<ColumnEnds>& rows);

		/** Determine the text span associated with a given row, represented by its ColumnEnds.
		*/


		/**
		   Determine the text-span for a given row in the table being created.
		   @param colEnds represents the row in terms of the text spans of each column
		   @return RangeData  
		 */
		RangeData getRowRange(const ColumnEnds& colEnds);


		/**
		   Get a persistent ref to the tag given its name, from which we can get an IXMLTagData
		   @param pstr 
		   @return UIDRef persistent reference to the tag
		 */
		UIDRef getTag(const WideString& pstr) const;

		/**
		   Determine if a particular tag is present within the active document.
		   @param pstr 
		   @return kTrue if the tag is present in active document, kFalse otherwise
		 */
		bool16 isTagPresent(const WideString& pstr) const ;
		
		
		/** Parse the text selection and find the text spans for each column in each row. Delimiters are 'tab' for
			columns, and CR for rows. For creating an XML-based table, we care about both columns and rows. For
			the other types of entities (e.g. keywordset), the columns are ignored, and we use only the row information.
			
			@param textUIDRef text model of interest
			@param rows [OUT] holds the result of parsing the text
			@param startOfTableText starting index to begin the parse
			@param endOfTableText end index for the parse
		*/
		void parseText(const UIDRef& textUIDRef, 
						K2Vector<ColumnEnds>& rows, 
						const TextIndex& startOfTableText, 
						const TextIndex& endOfTableText);

		/** Create element marking-up specified range, with option to add (single) attribute to the element created.
			Delegates to IXMLElementCommands::CreateElement to do the complex part.

			@param textModelRef text model of interest
			@param startIndex specifies where to start tagging from
			@param endIndex specifies where to end tagging
			@param pstrTag name for the tag
			@param addAttribute whether to add an attribute
			@param attrName name of the attribute, if addAttribute is kFalse, this is ignored
			@param attrValue attribute value,  if addAttribute is kFalse, this is ignored
			@return kSucess if the operation succeeded, kFailure otherwise
		*/
		ErrorCode tagTextRange(const UIDRef& textModelRef, 
								const TextIndex& startIndex, 
								const TextIndex& endIndex,
								const WideString& pstrTag,
								bool16 addAttribute,
								const WideString& attrName,
								const WideString& attrValue);

		/** Does the selection cover any text?
			@return kTrue if the selection covers some text, kFalse otherwise
		*/
		bool16 isNonEmptyRange() const;


		/**	Determine if the given row contains any text we could select and markup.
			@param colEnds [IN]
			@return bool16 kTrue if empty, kFalse otherwise
		 */
		bool16 isEmptyRow(const ColumnEnds& colEnds);

};




/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(XMLMrkSuiteTextCSB, kXMLMrkSuiteTextCSBImpl)


/* XMLMrkSuiteTextCSB Constructor
*/
XMLMrkSuiteTextCSB::XMLMrkSuiteTextCSB(IPMUnknown* boss) :
	CPMUnknown<IXMLMrkSuite>(boss)
{
}

/* XMLMrkSuiteTextCSB Destructor
*/
XMLMrkSuiteTextCSB::~XMLMrkSuiteTextCSB(void)
{
}

/* CanMakeTable
*/
bool16 XMLMrkSuiteTextCSB::CanMakeTable() const
{
	bool16 result = kFalse;
	do
	{
		
		// We need to be sure that we have 
		// the right tags in the curr document
		// to support the content model of the XML-based table
		result = isNonEmptyRange() &&
						isTagPresent(XMLMrkConstants::k_INFORMALTABLE_TAG) && 
						isTagPresent(XMLMrkConstants::k_TGROUP_TAG) && 
						isTagPresent(XMLMrkConstants::k_THEAD_TAG) && 
						isTagPresent(XMLMrkConstants::k_TBODY_TAG) && 
						isTagPresent(XMLMrkConstants::k_ROW_TAG) && 
						isTagPresent(XMLMrkConstants::k_ENTRY_TAG);
		
		
	} while(kFalse);
	return result;
}

/*
*/
bool16 XMLMrkSuiteTextCSB::isTagPresent(const WideString& tagName) const {
	return getTag(tagName) != UIDRef::gNull;
}


/*
*/
UIDRef XMLMrkSuiteTextCSB::getTag(const WideString& tagName) const
{
	UIDRef retval = UIDRef::gNull;

	do {
		InterfacePtr<const ITextTarget> iTextTarget (this, UseDefaultIID ());
		ASSERT(iTextTarget);
		if(!iTextTarget) {
			break;
		}
		UIDRef	textModelRef = iTextTarget->GetTextModel();
		InterfacePtr<IXMLTagList>	tagList(Utils<IXMLUtils>()->QueryXMLTagList(textModelRef.GetDataBase()));
		ASSERT(tagList);
		if(!tagList) {
			break;
		}
		UID uid = tagList->GetTag(tagName);
		if(uid == kInvalidUID) {
			break;
		}
		retval = UIDRef(textModelRef.GetDataBase(),uid);
	} while(kFalse);

	return retval;	
}

/*
*/
ErrorCode XMLMrkSuiteTextCSB::MakeTable(bool16 hasHeaderRow)
{
	ErrorCode result = kFailure;
	do
	{

		InterfacePtr<const ITextTarget>			iTextTarget (this, UseDefaultIID ());
		ASSERT(iTextTarget);
		if(!iTextTarget) {
			break;
		}
		UIDRef textModelRef = iTextTarget->GetTextModel();
		RangeData range = iTextTarget->GetRange();
		TextIndex startIndex = range.Start(nil);
		TextIndex endIndex = range.End();

		if(this->CanMakeTable()) {
			
			// Parse the text before we pollute it with any tags
			K2Vector<ColumnEnds> rows;
			this->parseText(textModelRef, rows, startIndex,	endIndex);

			// TODO PMStringConversion
			int32 numCols = this->getMaxNumberCols(rows);
			PMString numberColsStr("");
			numberColsStr.AppendNumber(numCols);
			int32 zeroWidthCharsAdded=0;
			this->tagTextRange(textModelRef,
								startIndex,		
								endIndex,	
								XMLMrkConstants::k_INFORMALTABLE_TAG,
								kFalse,WideString(),WideString());
			zeroWidthCharsAdded++;
			// At this point we've added one zero-width character, a [ into the textflow before the text
			// we want to mark-up, and one that is just after, the ] for the informaltable.
			this->tagTextRange(textModelRef,
								zeroWidthCharsAdded + startIndex,	
								zeroWidthCharsAdded + endIndex,	
								XMLMrkConstants::k_TGROUP_TAG,
								kTrue,
								XMLMrkConstants::k_COLS_ATTR,
								WideString(numberColsStr));	
			zeroWidthCharsAdded++;


			// We're now ready to add the tbody context
			this->tagTextRange(textModelRef,
								zeroWidthCharsAdded + startIndex,	
								zeroWidthCharsAdded + endIndex,	
								XMLMrkConstants::k_TBODY_TAG,
								kFalse,WideString(),WideString());
			zeroWidthCharsAdded++;

			int32 offset = startIndex;
		
			for(K2Vector<ColumnEnds>::const_iterator i = rows.begin(); i != rows.end(); ++i) 
			{
				if(this->isEmptyRow(*i)) {
					continue;
				}
				RangeData rowRange = this->getRowRange(*i);
				TextIndex rowStartIndex = rowRange.Start(nil);
				TextIndex rowEndIndex = rowRange.End();
				ASSERT(rowEndIndex > rowStartIndex);
				// We have to put a 'row' context around a row
				this->tagTextRange(textModelRef,
									zeroWidthCharsAdded + (offset + rowStartIndex),
									zeroWidthCharsAdded + (offset + rowEndIndex),	
									XMLMrkConstants::k_ROW_TAG,
									kFalse,
									WideString(),WideString());

				++zeroWidthCharsAdded;

				for(K2Vector<TextPair>::const_iterator j = i->begin(); j != i->end(); ++j) 
				{
				
					this->tagTextRange( textModelRef, 
										zeroWidthCharsAdded + (j->first + offset), 
										zeroWidthCharsAdded + (j->second + offset),
										XMLMrkConstants::k_ENTRY_TAG,
										kFalse,WideString(),WideString());
					// We've added a [ and a ], so make the next
					// entry offset correctly
					++zeroWidthCharsAdded;
					++zeroWidthCharsAdded;
				
				}
				// When we go to the next row, we've got the trailing ] from the
				// row above added
				++zeroWidthCharsAdded;
				
				}
			result = kSuccess;
		}
	} while(kFalse);

	return result;
}


/*
Came from TextToTableCmd.cpp
*/
void XMLMrkSuiteTextCSB::parseText(const UIDRef& textUIDRef, K2Vector<ColumnEnds>& rows, const TextIndex& startOfTableText, const TextIndex& endOfTableText)
{
	do {
		InterfacePtr<ITextModel> textModel(textUIDRef, UseDefaultIID());
		ASSERT(textModel);
		if(!textModel) {
			break;
		}
		TextIterator cur(textModel, startOfTableText);
		TextIterator end(textModel, endOfTableText);
		// We're interested in two characters in the text;
		// tabs indicate potential column delimiters for tables,
		// and CR indicate row-ends.
		const wchar_t separators[2] = {kTextChar_Tab, kTextChar_CR};
		ColumnEnds currentColEnds;
		TextIndex oldIndex = startOfTableText;
		TextPair lastRange(0, 0);
		// Find instances of either tab or CR characters in the text range
		while((cur =  std::find_first_of(cur, end, separators, separators + 2)) != end) {
			lastRange = TextPair(oldIndex - startOfTableText, cur.Position() - startOfTableText);
			currentColEnds.push_back(lastRange);
			if(*cur == kTextChar_CR) {
				// If we have found a CR, then this indicates a new row.
				// The working 'ColumnEnds' (recall, this is just  a vector of text-pairs)
				// will be flushed and we'll start working on the next row
				rows.push_back(currentColEnds);
				currentColEnds.clear();
			}
			++cur;
			oldIndex = cur.Position();
		}	

		ASSERT(cur == end);
		--cur;
		// We might not have ended on a separator
		TextIterator last(textModel, oldIndex);
		currentColEnds.push_back(TextPair(oldIndex - startOfTableText, endOfTableText - startOfTableText));
		if(!currentColEnds.empty()) {
			rows.push_back(currentColEnds);
		}
	} while(kFalse);
}
 
/*
*/
int32 XMLMrkSuiteTextCSB::getMaxNumberCols(const K2Vector<ColumnEnds>& rows)
{
	// This is returning the largest number of columns across all the rows. 
	// It is an exercise left to the
	// reader to adapt this code to work for non-rectangular tables, i.e. ones with split or
	// merged cells (rowspan or colspan different to 1 for some cells).
	// The results of parsing text where there are different numbers of columns in each row is undefined.
	int32 numRows = rows.size();
	K2Vector<ColumnEnds>::const_iterator biggestRow = std::max_element(rows.begin(), rows.end(), SmallerSize());
	ASSERT(biggestRow != rows.end());
	int32 numCols = biggestRow->size();
	return numCols;
}

/*
*/
RangeData XMLMrkSuiteTextCSB::getRowRange(const ColumnEnds& colEnds) 
{
	ColumnEnds::const_iterator begin = colEnds.begin();
	ColumnEnds::const_iterator end = colEnds.end();
	// The 'end' iterator points just off the end, so we're just moving it back
	// to point at the end-index for the last column in the row
	--end;

	TextPair firstTp = *begin;
	TextPair lastTp = *end;
	int32 rowStart = firstTp.first;
	int32 rowEnd = lastTp.second;
	ASSERT(rowEnd > rowStart);
	// We shouldn't be calling this with duff data
	RangeData retval(rowStart,rowEnd);
	return retval;
	
}

/*
*/
bool16 XMLMrkSuiteTextCSB::isEmptyRow(const ColumnEnds& colEnds) 
{
	ColumnEnds::const_iterator begin = colEnds.begin();
	ColumnEnds::const_iterator end = colEnds.end();
	--end;
	TextPair firstTp = *begin;
	TextPair lastTp = *end;
	int32 rowStart = firstTp.first;
	int32 rowEnd = lastTp.second;
	return (rowEnd <= rowStart);
}

/*
*/
ErrorCode XMLMrkSuiteTextCSB::tagTextRange(const UIDRef& textModelRef, 
									const TextIndex& startIndex, 
									const TextIndex& endIndex,
									const WideString& pstrTag,
									bool16 addAttribute,
									const WideString& attrName,
									const WideString& attrValue)
{
	ErrorCode retval = kFailure;
	do {
		// The tag (IXMLTag) should be already present in the document workspace.
		// If it isn't there, then we're not going to attempt to create it. Just fail.
		bool16 preconditions = isTagPresent(pstrTag) && 
								(endIndex> startIndex) &&
								 (textModelRef != UIDRef::gNull);
		ASSERT(preconditions);
		if(!preconditions) {
			break;
		}
		UIDRef tagUIDRef = this->getTag(pstrTag);
		//tag the selected text
		XMLReference newElement;
			Utils<IXMLElementCommands>()->CreateElement(tagUIDRef.GetUID(), 
															textModelRef, 
															startIndex, 
															endIndex, 
															kInvalidXMLReference, 
															&newElement);
		if(addAttribute) {
		ErrorCode err= Utils<IXMLAttributeCommands>()->CreateAttribute(newElement, attrName, attrValue);
		ASSERT(err == kSuccess);
		

		}
		retval = kSuccess;
	} while(kFalse);
	return retval;
}



/* CanMakeKeywordSet
*/
bool16 XMLMrkSuiteTextCSB::CanMakeKeywordSet() const
{
	bool16 result = kFalse;
	do
	{
		result =	isNonEmptyRange() &&
						isTagPresent(XMLMrkConstants::k_KEYWORDSET_TAG) && 
						isTagPresent(XMLMrkConstants::k_KEYWORD_TAG);		
		
	} while(kFalse);
	return result;
}

bool16 XMLMrkSuiteTextCSB::isNonEmptyRange() const
{
	bool16 retval = kFalse;
	do {
		InterfacePtr<const ITextTarget> iTextTarget (this, UseDefaultIID ());
		ASSERT(iTextTarget);
		if(!iTextTarget) {
			break;
		}
		RangeData range = iTextTarget->GetRange();
		retval = range.Length() >0;
	} while(kFalse);
	return retval;
}

/*
*/
ErrorCode XMLMrkSuiteTextCSB::MakeKeywordSet()
{
	ErrorCode result = kFailure;
	do
	{

		InterfacePtr<const ITextTarget>			iTextTarget (this, UseDefaultIID ());
		ASSERT(iTextTarget);
		if(!iTextTarget) {
			break;
		}
		UIDRef textModelRef = iTextTarget->GetTextModel();
		RangeData range = iTextTarget->GetRange();
		TextIndex startIndex = range.Start(nil);
		TextIndex endIndex = range.End();

		if(this->CanMakeKeywordSet()) {
			
			K2Vector<ColumnEnds> rows;
			this->parseText(textModelRef, rows, startIndex,	endIndex);

			int32 zeroWidthCharsAdded=0;
			this->tagTextRange(textModelRef,
								startIndex,		
								endIndex,	
								XMLMrkConstants::k_KEYWORDSET_TAG,
								kFalse,WideString(),WideString());
			zeroWidthCharsAdded++;
		
			int32 offset = startIndex;
		
			for(K2Vector<ColumnEnds>::const_iterator i = rows.begin(); i != rows.end(); ++i) 
			{
				if(this->isEmptyRow(*i)) {
					continue;
				}
				RangeData rowRange = this->getRowRange(*i);
				TextIndex rowStartIndex = rowRange.Start(nil);
				TextIndex rowEndIndex = rowRange.End();
				ASSERT(rowEndIndex > rowStartIndex);
				// Make a single keyword out of the whole row
				this->tagTextRange(textModelRef,
									zeroWidthCharsAdded + (offset + rowStartIndex),
									zeroWidthCharsAdded + (offset + rowEndIndex),	
									XMLMrkConstants::k_KEYWORD_TAG,
									kFalse,
									WideString(),WideString());

				++zeroWidthCharsAdded;
				++zeroWidthCharsAdded;
			
			}
			result = kSuccess;
		}
	} while(kFalse);

	return result;
}


/* CanMakeItemizedList
*/
bool16 XMLMrkSuiteTextCSB::CanMakeItemizedList() const
{
	bool16 result = kFalse;
	do
	{
		result =	isNonEmptyRange() &&
						isTagPresent(XMLMrkConstants::k_ITEMIZEDLIST_TAG) && 
						isTagPresent(XMLMrkConstants::k_LISTITEM_TAG) &&
						isTagPresent(XMLMrkConstants::k_PARA_TAG);
		
		
	} while(kFalse);
	return result;
}

/*
*/
ErrorCode XMLMrkSuiteTextCSB::MakeItemizedList()
{
	ErrorCode result = kFailure;
	do
	{

		InterfacePtr<const ITextTarget>			iTextTarget (this, UseDefaultIID ());
		ASSERT(iTextTarget);
		if(!iTextTarget) {
			break;
		}
		UIDRef textModelRef = iTextTarget->GetTextModel();
		RangeData range = iTextTarget->GetRange();
		TextIndex startIndex = range.Start(nil);
		TextIndex endIndex = range.End();

		if(this->CanMakeItemizedList()) {
			
			K2Vector<ColumnEnds> rows;
			this->parseText(textModelRef, rows, startIndex,	endIndex);

			int32 zeroWidthCharsAdded=0;
			this->tagTextRange(textModelRef,
								startIndex,		
								endIndex,	
								XMLMrkConstants::k_ITEMIZEDLIST_TAG,
								kFalse,WideString(),WideString());
			zeroWidthCharsAdded++;
		
			int32 offset = startIndex;
		
			for(K2Vector<ColumnEnds>::const_iterator i = rows.begin(); i != rows.end(); ++i) 
			{
				if(this->isEmptyRow(*i)) {
					continue;
				}
				RangeData rowRange = this->getRowRange(*i);
				TextIndex rowStartIndex = rowRange.Start(nil);
				TextIndex rowEndIndex = rowRange.End();
				ASSERT(rowEndIndex > rowStartIndex);
				// We have to put a listitem context around a row
				this->tagTextRange(textModelRef,
									zeroWidthCharsAdded + (offset + rowStartIndex),
									zeroWidthCharsAdded + (offset + rowEndIndex),	
									XMLMrkConstants::k_LISTITEM_TAG,
									kFalse,
									WideString(),WideString());

				++zeroWidthCharsAdded;

				{
					// Here's the para that's a child of the listitem
					this->tagTextRange(textModelRef,
										zeroWidthCharsAdded + (offset + rowStartIndex),
										zeroWidthCharsAdded + (offset + rowEndIndex),	
										XMLMrkConstants::k_PARA_TAG,
										kFalse,
										WideString(),WideString());

					++zeroWidthCharsAdded;
					++zeroWidthCharsAdded;
				}	
				
				// When we go to the next row, we've got the trailing ] from the
				// row above added
				++zeroWidthCharsAdded;
				
				}
			result = kSuccess;
		}
	} while(kFalse);

	return result;
}




/* CanMakeSectionComposite
*/
bool16 XMLMrkSuiteTextCSB::CanMakeSectionComposite() const
{
	bool16 result = kFalse;
	do
	{
		result =	isNonEmptyRange() &&
						isTagPresent(XMLMrkConstants::k_SECTION_TAG) && 
						isTagPresent(XMLMrkConstants::k_TITLE_TAG) && 
						isTagPresent(XMLMrkConstants::k_PARA_TAG);
		
		
	} while(kFalse);
	return result;
}

/*
*/
ErrorCode XMLMrkSuiteTextCSB::MakeSectionComposite()
{
	ErrorCode result = kFailure;
	do
	{

		InterfacePtr<const ITextTarget>			iTextTarget (this, UseDefaultIID ());
		ASSERT(iTextTarget);
		if(!iTextTarget) {
			break;
		}
		UIDRef textModelRef = iTextTarget->GetTextModel();
		RangeData range = iTextTarget->GetRange();
		TextIndex startIndex = range.Start(nil);
		TextIndex endIndex = range.End();

		if(this->CanMakeSectionComposite()) {
			
			K2Vector<ColumnEnds> rows;
			this->parseText(textModelRef, rows, startIndex,	endIndex);

			int32 zeroWidthCharsAdded=0;
			this->tagTextRange(textModelRef,
								startIndex,		
								endIndex,	
								XMLMrkConstants::k_SECTION_TAG,
								kFalse,WideString(),WideString());
			zeroWidthCharsAdded++;
		
			int32 offset = startIndex;
			bool16 noTitle = kTrue;

			for(K2Vector<ColumnEnds>::const_iterator i = rows.begin(); i != rows.end(); ++i) 
			{
				if(this->isEmptyRow(*i)) {
					continue;
				}
				RangeData rowRange = this->getRowRange(*i);
				TextIndex rowStartIndex = rowRange.Start(nil);
				TextIndex rowEndIndex = rowRange.End();
				if(rowEndIndex > rowStartIndex) {
					this->tagTextRange(textModelRef,
										zeroWidthCharsAdded + (offset + rowStartIndex),
										zeroWidthCharsAdded + (offset + rowEndIndex),	
										noTitle ? XMLMrkConstants::k_TITLE_TAG : XMLMrkConstants::k_PARA_TAG,
										kFalse,
										WideString(),WideString());

					++zeroWidthCharsAdded;
					++zeroWidthCharsAdded;
					noTitle = kFalse;
				}
				
				}
			result = kSuccess;
		}
	} while(kFalse);

	return result;
}



/* CanMakeMediaObject
*/
bool16 XMLMrkSuiteTextCSB::CanMakeMediaObject() const
{
	bool16 result = kFalse;
	do
	{
		result =	isNonEmptyRange() &&
						isTagPresent(XMLMrkConstants::k_MEDIAOBJECT_TAG) && 
						isTagPresent(XMLMrkConstants::k_IMAGEOBJECT_TAG) && 
						isTagPresent(XMLMrkConstants::k_IMAGEDATA_TAG);
		
		
	} while(kFalse);
	return result;
}


/*
*/
ErrorCode XMLMrkSuiteTextCSB::MakeMediaObject()
{
	ErrorCode result = kFailure;
	do
	{

		InterfacePtr<const ITextTarget>			iTextTarget (this, UseDefaultIID ());
		ASSERT(iTextTarget);
		if(!iTextTarget) {
			break;
		}
		UIDRef textModelRef = iTextTarget->GetTextModel();
		RangeData range = iTextTarget->GetRange();
		TextIndex startIndex = range.Start(nil);
		TextIndex endIndex = range.End();

		if(this->CanMakeMediaObject()) {
			WideString widey;
			InterfacePtr<ITextModel> textModel(textModelRef, UseDefaultIID());
			ASSERT(textModel);
			if(!textModel) {
				break;
			}
			TextIterator beginTextChunk(textModel, startIndex);
			TextIterator endTextChunk(textModel, endIndex);
			widey.reserve(endIndex-startIndex);
			std::copy(beginTextChunk, endTextChunk, std::back_inserter(widey));

			int32 zeroWidthCharsAdded=0;
			this->tagTextRange(textModelRef,
								startIndex,		
								endIndex,	
								XMLMrkConstants::k_MEDIAOBJECT_TAG,
								kFalse,WideString(),WideString());
			zeroWidthCharsAdded++;
			this->tagTextRange(textModelRef,
								zeroWidthCharsAdded + startIndex,	
								zeroWidthCharsAdded + endIndex,	
								XMLMrkConstants::k_IMAGEOBJECT_TAG,
								kFalse,WideString(),WideString());	
			zeroWidthCharsAdded++;
			this->tagTextRange(textModelRef,
								zeroWidthCharsAdded + startIndex,	
								zeroWidthCharsAdded + endIndex,	
								XMLMrkConstants::k_IMAGEDATA_TAG,
								kTrue,XMLMrkConstants::k_FILEREF_ATTR,widey);
			zeroWidthCharsAdded++;
			// Now want to consume the part of the text model so that there's no char content
			RangeData deleteRangeData( zeroWidthCharsAdded + startIndex, zeroWidthCharsAdded + endIndex);
			InterfacePtr<ITextModelCmds> textModelCmds(textModel, UseDefaultIID());
			ASSERT(textModelCmds);
			if(!textModelCmds) {
				break;
			}
			InterfacePtr<ICommand> iDeleteCmd(textModelCmds->DeleteCmd(deleteRangeData));
			ASSERT(iDeleteCmd);
			if(!iDeleteCmd) {
				break;
			}
			ErrorCode err = CmdUtils::ProcessCommand(iDeleteCmd);
			ASSERT(err == kSuccess);

			result = kSuccess;
			}
	} while(kFalse);

	return result;
}


// End, XMLMrkSuiteTextCSB.cpp.



