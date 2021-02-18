//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLUtils.h $
//  
//  Owner: robin briggs
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

#pragma once
#ifndef __IXMLUtils__
#define __IXMLUtils__

#include "K2Vector.h"
#include "Utils.h"
#include "XMLID.h"
#include "TableTypes.h"

class IDataBase;
class IDocument;
class IIDXMLElement;
class ITextModel;
class IXMLAccess;
class IXMLHandler;
class IXMLOutStream;
class IXMLReferenceData;
class IXMLStyleToTagMap;
class IXMLTagList;
class IXMLTagToStyleMap;
class UIDList;
class XMLDTDValidationError;
class XMLReference;

/** Utilities for traversing and working within the logical structure tree.
*/
class IXMLUtils : public IPMUnknown 
{
	public:
		enum	{kDefaultIID = IID_IXMLUTILS};

		virtual UIDRef GetBackingStore(IDocument *doc) = 0;
		virtual UIDRef GetBackingStore(IDataBase *db) = 0;
		
		/**	Return the XML document element for the given document
			@param document specifies document of interest
			@return IIDXMLElement interface ptr that has its reference-count incremented
		 */
		virtual IIDXMLElement* QueryDocElement(IDocument* document) = 0;

		/** Return the XML document element for the given database, based on the database' document
			@param db specifies database of interest
			@return IIDXMLElement interface ptr that has its reference-count incremented
		 */
		virtual IIDXMLElement* QueryDocElement(IDataBase* db) = 0;

		/** Return the root element of the given XML document element
			@param xmlDocElement XML document element of interest
			@return IIDXMLElement interface ptr that has its reference-count incremented
		 */
		virtual IIDXMLElement* QueryRootElement(IIDXMLElement* xmlDocElement) = 0;


		/** Return the root element of the given document
			@param document specifies document of interest
			@return IIDXMLElement interface ptr that has its reference-count incremented to the root XML element
		 */
		virtual IIDXMLElement* QueryRootElement(IDocument* document) = 0;

		/** Return the root element of the given database (based on the db's document)
			@param db database from document
			@return IIDXMLElement interface ptr that has its reference-count incremented to the root element
		 */
		virtual IIDXMLElement* QueryRootElement(IDataBase* db) = 0;


		/** Query for the tag-list in the given database.
			@param db database containing tag-list of interest
			@return IXMLTagList interface ptr that has its reference-count incremented
		 */
		virtual IXMLTagList* QueryXMLTagList(IDataBase* db) = 0;

		/** Query for the mapping between paragraph/character styles and tags in the given databse.
			@param db specifies database of interest
			@return IXMLStyleToTagMap interface ptr that has its reference-count incremented
		 */
		virtual IXMLStyleToTagMap* QueryXMLStyleToTagMap(IDataBase* db) = 0;

		/** Query for the mapping between tag-names and paragraph/character styles in the
			given database. 
			@param db database containing mapping of interest
			@return IXMLTagToStyleMap interface ptr that has its reference-count incremented,
			for given database
		 */
		virtual IXMLTagToStyleMap* QueryXMLTagToStyleMap(IDataBase* db) = 0;

		/** Query for the text model associated with given element.
			@param element specifies element of interest. 	
			Note that <code>element->GetContentItem()</code> should be a valid UID.
			@return ITextModel interface ptr that has its reference-count incremented
		
		 */
		virtual ITextModel* QueryTextModel(const IIDXMLElement* element) = 0;


		/** Given any interface on an arbitrary boss object, determine if there is XML data
			associated with it's content. This method checks the contents of frames in the following order;
			<ol>
				<li>a text on a path frame
				<li>a text frame
				<li>a graphic frame
			</ol>
			It will try to return an IXMLReferenceData given knowledge about the model format.

			@param item specifies the boss object of interest (frame of some kind)
			@param allowTOP set to be kTrue if text on path frames are allowable, kFalse otherwise
			@return IXMLReferenceData interface ptr that has its reference-count incremented for the content of the frame
		 */
		virtual IXMLReferenceData* QueryXMLReferenceData(IPMUnknown* item, bool16 allowTOP = kFalse) = 0;

		/** Overload of method QueryXMLReferenceData, given a persistent reference rather than an interface ptr.
			@param item specifies frame of interest
			@param allowTOP kTrue if text on path frames are allowable, kFalse otherwise 
			@return IXMLReferenceData interface ptr that has its reference-count incremented
		 */
		virtual IXMLReferenceData* QueryXMLReferenceData(const UIDRef& item, bool16 allowTOP = kFalse) = 0;

		/** Given a text index position, return the IXMLReferenceData associated with the text index.
			@param storyUIDRef UIDRef of the story the text index is in
			@param textIndex TextIndex to query IXMLReferenceData for
			@param allowTOP kTrue if text on path frames are allowable, kFalse otherwise 
			@return IXMLReferenceData interface ptr that has its reference-count incremented
		*/
		virtual IXMLReferenceData* QueryXMLReferenceData(const UIDRef& storyUIDRef, TextIndex textIndex, bool16 allowTOP = kFalse) = 0;

		/** Given a text index position, return the IXMLReferenceData associated with the text index.
			@param textModel TextModel of the story the text index is in
			@param textIndex TextIndex to query IXMLReferenceData for
			@param allowTOP kTrue if text on path frames are allowable, kFalse otherwise 
			@return IXMLReferenceData interface ptr that has its reference-count incremented
		*/
		virtual IXMLReferenceData* QueryXMLReferenceData(ITextModel *textModel, TextIndex textIndex, bool16 allowTOP = kFalse) = 0;

		/** Given a XMLReference, return the IXMLReferenceData associated with the element's 
			content, if applicable
			@param xmlReference XMLReference of the element to process
			@return IXMLReferenceData interfaceptr that has its reference-count incremeneted, if 
			the element has such content. nil otherwise
		*/
		virtual IXMLReferenceData* QueryXMLReferenceData(const XMLReference& xmlReference) = 0;

		/**	Get the positions of the marker characters for the given element
			returns kTrue if the positions are marker positions; kFalse if content position 
			(i.e. story element which does not have markers)
			@param element specifies element of interest
			@param startPos [OUT] TextIndex where the begin-element marker tag is located in the textflow
			@param endPos [OUT] TextIndex where the end-element marker tag is located in the textflow
			@return bool16 kTrue if positions are marker positions, kFalse if content positions and the story
				element does not have markers in it
		 */
		virtual bool16 GetElementIndices(const IIDXMLElement* element, TextIndex* startPos, TextIndex* endPos) = 0;
		
		/**	Get the actual positions of the marker characters for the given element. The values returned
			are always marker positions in the story that contains the markers, which is not always
			the content's story (such as link elements)
			@param element specifies XML element of interest
			@param startPos [OUT] start of text-range tagged by this element
			@param endPos [OUT] end of text-range tagged by this element
		 */
		virtual void GetElementMarkerPositions(IIDXMLElement* element, TextIndex* startPos, TextIndex* endPos) = 0;

		/**	Calculate the range of text before/after/in between child objects per the XML structure.
			Used when generating chunks of XML content.
			@param element specifies XML element of interest
			@param beforeChildIndex specifies the indicies to be calculated are BEFORE this child (to
				   get the indices after the last child pass the last child index + 1)
			@param startPos [OUT] start of text-range before specified child
			@param endPos [OUT] end of text-range before specified child
			@return bool16 kFalse if there is no XML content for the specified element before the specified child
		 */
		virtual bool16 CalculateStartEndTextIndex(IIDXMLElement *element, int32 beforeChildIndex, TextIndex &startTextIndex, TextIndex &endTextIndex) = 0;

		/** Automatic attributes are at present 'href'.
			If the element associated with the given XMLReference is a graphic item,
			then at the time of writing (InDesign 2.0) it will automatically get an
			href attribute added to it.
			@param ref 
			@return ErrorCode 
		 */
		virtual ErrorCode UpdateAutoAttrib(const XMLReference& ref) = 0;

		/**	Return the XMLReference that corresponds to the story. In the case
			the story is the backing store (unplaced content), the XML document's XMLReference
			is returned
			@param storyRef specifies the story of interest
			@return XMLReference to story corresponding to given XMLReference
		 */
		virtual XMLReference GetStoryXMLReference(const UIDRef& storyRef) = 0;

		/** Returns the XMLReference corresponding to the given text position's story thread
			@param storyUIDRef UIDRef of the story
			@param textIndex TextIndex of the text position
			@return XMLReference of the given text position's story thread
		*/
		virtual XMLReference GetStoryThreadXMLReference(const UIDRef& storyUIDRef, TextIndex textIndex) = 0;

		/** Returns the XMLReference corresponding to the given text position's story thread
			@param textModel TextModel of the story
			@param textIndex TextIndex of the text position
			@return XMLReference of the given text position's story thread
		*/
		virtual XMLReference GetStoryThreadXMLReference(ITextModel *textModel, TextIndex textIndex) = 0;

		/** Enumeration containing return values for CalcXMLParent()
		*/
		enum CalcXMLParent_Result {
			kSuccessCalc = 0,
			kStartUnmatched = 1,
			kEndUnmatched = 2,
			kBothUnmatched = kStartUnmatched+kEndUnmatched
		};
	
		/** Perform the element calculations as if the given text range is to be tagged.
			Given a text range, determine the XML element (given as XMLReference) that
			should be the parent (along with the child index) of the selection. Also
			calculates a list of children of the final parent that should become
			the children of the created element

			@param startParentXMLRef parent XML element to start the calculation. Receives
			the XML element that should be the parent of the selection.
			If the result is not kSuccessCalc, receives the parent of startTextIndex
			@param startIndexInParent receives the child index of startParentXMLRef the selection
			should be inserted as
			@param childRefList a list of children of startParentXMLRef that should become
			children of the new XML element. Valid on return only if returned result code is kSuccessCalc
			@param endParentXMLRef if the result is not kSuccessCalc, receives the parent of endTextIndex.
			Valid on return only if returned result code is not kSuccessCalc
			@param endIndexInParent if the result is not kSuccessCalc, receives the child index of endParentXMLRef.
			Valid on return only if returned result code is not kSuccessCalc
			@param startTextIndex TextIndex to start the calculation
			@param endTextIndex TextIndex to stop the calculation (INCLUSIVE, this means range of
			3,3 is actually one character; 3,2 signifies an insertion position)
			@param iTextModel text model of text to insert
			@param useReverseSearch Usually, this method searches the child elements in the reverse 
			order, from back to front. This is to optimize for the case of repeated append operations,
			such as when building XML structure during import using the parsed order to create elements.
			Reverse search is faster in this case because most of the desired data is at the end of the 
			child list. Set this parameter to kFalse will cause the search to be done in the front to 
			back order. This search order can be faster for cases such as building the structure in the
			reverse order, where most of the desired data is at the front of the child list
			@return CalcXMLParent_Result code 
		 */
		virtual int32 CalcXMLParent(XMLReference& startParentXMLRef, int32& startIndexInParent, K2Vector<XMLReference>& childRefList, 
				XMLReference& endParentXMLRef, int32& endIndexInParent,
				TextIndex startTextIndex, TextIndex endTextIndex, ITextModel* iTextModel, bool16 useReverseSearch = kTrue) = 0;

		/** Given a text range, calculate a list of top-level XML elements that are 
			fully contained in the range.
			Elements that are partially inside the range are not included in the list.
			startTextIndex and endTextIndex must be in the same story thread.

			@iTextModel	[IN] text model of the range
			@ startTextIndex [IN] TextIndex to start the calculation
			@ endTextIndex [IN] TextIndex to stop the calculation (INCLUSIVE, this means range of
			3,3 is actually one character; 3,2 signifies an insertion position)
			@ parentXMLRef [OUT] the parent of the elements in chilRefList
			@ childRefList [OUT] a list of top-level children in the text range
		*/
		virtual void CalcXMLElementsInTextRange(ITextModel *iTextModel, TextIndex startTextIndex, TextIndex endTextIndex, XMLReference& parentXMLRef, K2Vector<XMLReference>& childRefList) = 0;

		/** Create a new tag (IXMLTag) in the tag-list (IXMLTagList).
		   @param strTag specifies the tag-name to use
		   @param db identifies the database, into whose tag-list the new tag is inserted
		   @param colorUID contains the UID of the color to use for the tag (kInvalidUID if you don't care)
		   @param tagUID contains the UID of the newly created tag or kInvalidUID if unsuccessful.
		   @return ErrorCode 
		 */
		virtual	ErrorCode AssignTagUID(const WideString& strTag, IDataBase* db, UID colorUID, UID& tagUID) = 0;

		/** Checks to see if a given tag-name would be appropriate as the name for an XML element (not
			whether tag already exists as that would imply a database).
			Determines in order;
			<ol>
				<li>if the tag is empty
				<li>if there are whitespace characters in the name
				<li>If there are 'illegal' characters; 
				see <a href="http://www.w3c.org/TR/2000/REC-xml-20001006#NT-Name">XML 1.0 specification</a> 
			</ol>

			For instance, names for an XML element can only begin with an alphabetic character
			or an underline, or a colon. 
		   @param tag name of tag to check
		   @return bool16 kTrue if can be used for tag-name, kFalse otherwise
		 */
		virtual bool16 IsTagValid(const WideString& tag) = 0;

		/** Determine whether the given token matched XML 1.0 specification's (REC-xml-20001060) 
			production for [7] Nmtoken
			@param token token to check
			@return bool16 kTrue if the token is a Nmtoken; kFalse otherwise
		*/
		virtual bool16 IsNmtoken(const PMString& token) = 0;

		/** Determine whether the given comment is a valid XML comment per XML 1.0 specification
			(REC-xml-20001006), section 2.5
			@param comment comment to check
			@return bool16 kTrue if the comment is valid; kFalse otherwise
		*/
		virtual bool16 IsValidXMLComment(const PMString& comment) = 0;

		/** Determine whether the given string is a valid XML processing instruction target per
			XML 1.0 specification (REC-xml-20001006), section 2.6
			@param piTarget PI target to check
			@return bool16 kTrue if piTarget is a valid PI target; kFalse otherwise
		*/
		virtual bool16 IsValidXMLPITarget(const PMString& piTarget) = 0;

		/** Determine whether the given string is a valid XML processing instruction data per
			XML 1.0 specification (REC-xml-20001006), section 2.6
			@param piData PI data to check
			@return bool16 kTrue if piData is a valid PI data; kFalse otherwise
		*/
		virtual bool16 IsValidXMLPIData(const PMString& piData) = 0;

		/**	Determine if given boss object could be marked-up.
			If this item or a child down the hierarchy has an IXMLReferenceData IFace, it is  it can be marked-up (is taggable).
			Alternatively if this item is a graphic frame, it can be marked-up (is taggable).
			If this item is a group or a guide it cannot be marked-up (is not taggable)
			@param item interface on boss object (page item) of interest
			@return bool16 kTrue if the page item can be marked up, kFalse otherwise
		 */
		virtual bool16 IsTaggablePageItem(IPMUnknown* item) = 0;

		/** Given an open document, return which are not used to mark-up content in the document.
		   @param unusedTag [OUT] list of tags not marking up content in document implied by its database.
		   Note that the database of the UIDList supplied should be the database of the document
		   containing the tags that the query is about.
		 */
		virtual void FindUnusedTags(UIDList& unusedTag) = 0;

		/** Import a page item into the given database using the 'href' passed in as the path to the file.
			Note that this doesn't imply that the content will be loaded across the wire; it is strictly
			a path in the local file system at the time of writing.
		   @param db  database to import the page item into
		   @param href a string which represents the path to the file you want to import
		   @param relativeTo if passed in (it can be nil), the href passed in will be used as a relative path with respect to 'relativeTo'
			if 'relativeTo' is a directory, the path will stem from it, if 'relativeTo' is a file, 
			the path will stem from it's parent directory
		   @param useFrame [OUT] parameter
			@param uiFlags specifies how much UI to show
		   @return  UID of the page item created
		 */
		virtual	UID ImportHREF(IDataBase* db, const PMString& href, const IDFile* relativeTo, bool16& useFrame, UIFlags uiFlags = kFullUI ) = 0;

		/**	Checks to see if the content is locked given the element via ITextLockData on given element.
		   @param element specifies element of interest
		   @return bool16 kTrue if locked and kFalse otherwise
		 */
		virtual bool16 IsElementLocked( const IIDXMLElement* element ) = 0;

		/**	Checks to see if the content is locked given the story
			NOTE: now it works for generic page items too, not just stories
		   @param storyRef specifies story of interest
		   @return bool16 kTrue if story locked, kFalse otherwise
		 */
		virtual bool16 IsStoryLocked(const UIDRef& storyRef) = 0;
		
		/** Returns true if the database contains unlocked stories
		   @param in IDatabase current database		
		 */
		virtual bool HasUnlockedStory (IDataBase *db) = 0;

		/**	Determines whether there are any link elements in the given text range.

			@param storyUIDRef specifies story of interest
			@param start where to start looking for link elements
			@param numChars how many chars forward in the textmodel to search
			@return kTrue if the text range contains at least one link XML element; kFalse otherwise
		 */
		virtual bool16 LinkElementInTextRange(const UIDRef& storyUIDRef, TextIndex start, int32 numChars) = 0;
		
		/** Returns the graphic frame that contains the content. If the content is a text model,
			it returns the graphic frame that contains the multi-column frame. 
			If the content is a page item, it returns the graphic frame that contains the page item.
		   @param contentUID specifies the content item that we're interested in
		   @return UID of graphic frame containing the content, which can be kInvalidUID if the
			content isn't placed into a story yet
		 */
		virtual UID GetGraphicFrame(const UIDRef& contentUID) = 0;

		/** Determine if we consider the element to be a graphic element.  If it has an href and no content or 
			children, then we consider it a graphic
		   @param element specifies element of interest
		   @return bool16 kTrue if a graphic element,kFalse otherwise
		 */
		virtual bool16  IsElementAGraphic(IIDXMLElement*	element) const = 0;

		/**
			Return the taggable content UIDRef that's associated with the incoming UID.
			Returns true if the item can be tagged. Returns a valid contentRef if there
			is content that can be immediately tagged. A return value of kTrue, together
			with an invalid contentRef shows that item can be tagged if placeholder content
			can be added.

			If caller passed in a graphic frame, this method will return the taggable content from the graphic frame.
			If it is a text frame, will return the story.

			If its a graphic frame, and it has content, this method will tunnel down to the children to find taggable content. 
			If the frame has content, but the content isn't taggable, this method would flag an error by returning kFalse

			@param contentRef [OUT] holds the content item if it can be found
			@return bool16 indicating success of operation(if kTrue) or failure (kFalse)
		 */
		virtual bool16 GetActualContent(UIDRef& contentRef) = 0;

		/**
		   Validate the XML against a DTD.
		   @param startXMLRef XMLReference of the element to start the validation at. Use the
		   document element to validate the entire XML
		   @param errors [OUT] receives vector of validation errors found
		   @see XMLDTDValidationError
		   @param maxErrors maximum number of errors to retrieve. Use -1 to get all the errors
		   @param treatAsRoot if startXMLRef is not the document element or the root element, 
		   whether to check startXMLRef against DOCTYPE root element type. This is used when 
		   validating from something other than the root, but still wants to treat the starting 
		   element as root
		   @param checkHasDTD if startXMLRef has no DTD reference, whether it should be flagged as
		   an error. Set this flag to kFalse, and XML without DTD will also "pass" the validation
		*/
		virtual void ValidateXML(const XMLReference& startXMLRef, K2Vector<XMLDTDValidationError>& errors, int32 maxErrors = 250, bool16 treatAsRoot = kFalse, bool16 checkHasDTD = kFalse) = 0;

		/**
			Export an XML element and its children to a stream
		   @param element specifies the element to export
		   @param includeHeader Include the DTD in the XML?
		   @param access used to navigate and export the sub-elements
		   @param exportHandler contains the stream to write to
		   @param sysFile the actual file we are writing to
		   @param doc document we are writing the XML from
		   @return ErrorCode Did theexport work?
		*/
		virtual ErrorCode ExportElement(IIDXMLElement *element, bool16 includeHeader, IXMLAccess* access, 
				IXMLHandler* exportHandler, const IDFile& sysFile, IDocument* doc, const PMString& formatName, UIFlags uiFlags) const = 0;

		/** Export the DTD to the given stream.
			@param xmlRef XMLReference of any element in the XML to export the DTD from
			@param s stream to export to
			@param internalSubsetOnly whether to write internal subset only
		*/
		virtual void ExportDTDToStream(const XMLReference& xmlRef, IXMLOutStream *s, bool16 internalSubsetOnly = kFalse) = 0;

#ifdef DEBUG
		/**
		   Verify that XML structure of the target document.  This utility examines
		   all the XML elements, parent/parent child relationships, links etc.  It
		   asserts if it discovers a problem with the structure.
		   @param targetDocument specifies the document whose structure is to be verified.
		 */
		virtual void VerifyXMLStructure(IDocument* targetDocument) = 0;
#endif

		/** determine whether the given story is exportable as an InCopy story from XML's perspective
			@param storyUIDRef UIDRef of story to export
			@return bool16 kTrue if the story is exportable as InCopy story; kFalse otherwise
		*/
		virtual bool16 IsExportableInCopyStory(const UIDRef& storyUIDRef) = 0;

		/**
			Allow the user to find a missing file referenced in the XML. In the server case
			log an error to the error list
			@param filename string that describes the file name in the XML
			@param fileToImport string that returns the file name that was selected
			@return bool16 whether the file was found or not
		*/
		virtual bool16 FindMissingFile(PMString filename, IDFile& fileToImport) = 0;

		/**
			Returns the the root element of the imported XML data.
			@param importer An interface on kXMLImporterBoss. Must not be nil.
			@return XMLReference The XMLReference of the roort element.
			Returns kInvalidXMLReference if no root element is found.
		*/
		virtual XMLReference GetImportedRootXMLReference(IPMUnknown* importer) = 0;

		class IXMLCallback 
		{
		public:
			typedef enum { kKeepIterating = 0, kSkipChildren, kStopIterating } ContinuationCode;
			
			/** Visit will be called once for each element. It may do whatever processing
				it needs to on the element, and then returns true to continue visiting
				other elements, false otherwise.
				@param element the element we're visiting
				@return kTrue to continue visiting more elements, false otherwise.
			**/
			virtual ContinuationCode Visit(IIDXMLElement *element) = 0;
		};
		
		/**
			Iterate a portion of the XML tree, using the supplied element as
			the root of a sub-tree. Will call into the callback object for
			each element in the sub-tree. Uses a non-recursive algorithm so it
			works with deep trees.
			@param root The root of the elements to iterate.
			@param callback The object to callback for each element
			Returns kInvalidXMLReference if no root element is found.
		*/
		virtual void ForEachElement(IIDXMLElement* root, IXMLCallback *callback) = 0;

		/**
			Checks whether the Parent of the Passed element is Table-Cell With CellType being equal to the
			passed CellType like kPageItemContentType, kTextContentType etc
			@param childElement The element whose Parent we need to check, if parent is not Table-Cell then returns kFalse
			@param cellType		The cellType of the Parent of element which is Table-Cell is also matched if the Parent is Table-Cell. 
			Returns kTrue if Parent is Table-Cell and CellType also matches the passed cellType.
		*/
		virtual bool16 IsParentCellWithType(IIDXMLElement* childElement, CellType cellType) = 0;

		/**
		Sets the preference to also delete the XML element when its content has been deleted. Default is kFalse.
		*/
		virtual ErrorCode SetShouldDeleteElementOnContentDeletion(const bool16 shouldDelete = kTrue) const = 0;

		/**
		Gets the value for preference to also delete the XML element when its content has been deleted. 
		@see IXMLUtils::SetShouldDeleteElementOnContentDeletion.
		*/
		virtual bool16 ShouldDeleteElementOnContentDeletion() const = 0;

		/** Set the tag for a layout item (page item)
		@param target - The target to use when tagging the object
		@param tag - The UIDRef of the tag you want to use
		@param retag - Whether to retag an existing element with a new tag
		@param allowPresetUI - Allow the tagging preset UI to popup
		@return - Whether the method succeeded or not
		*/ 
		virtual ErrorCode SetLayoutTag(const UIDList& itemList, const UIDRef& tag, bool16 retag, bool16 allowPresetUI) = 0; 
};
	
#endif // __IXMLUtils__
