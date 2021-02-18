//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLElementCommands.h $
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
#ifndef __IXMLElementCommands__
#define __IXMLElementCommands__

#include "XMLID.h"
#include "XMLReference.h"
#include "TableTypes.h"		// for GridID
#include "TableTagData.h"

class ICommand;
class ITextStoryThread;
class RangeData;
class XMLDTDInsertElement;
class XMLDTDReplaceElement;

/** Processes (and creates) commands for creating, deleting, and manipulating XML elements.
  	For instance, there are overloaded CreateElement methods for creating an XML element. 
	Each one takes different arguments, but all of them create a regular element that can hold content.
	There are methods to process commands to delete elements in different way; directly, through reference
	or indirectly, through deleting elements that are marking-up a particular text range.
	There are other methods to change the properties of an element, such as its tag name.
*/
class IXMLElementCommands : public IPMUnknown 
{
	public:
		enum	{kDefaultIID = IID_IXMLELEMENTCOMMANDS};

		/**	Can be used to tag a text range; creates named tag if it doesn't already exist in tag-list.
			The command will automatically find the XML element which will be the parent of the of the new element, based on the
			range you pass in. This can be slow on a story with many elements, so optionally you may pass a reference to an element (parentXMLR)
			in the story to start searching from, to find the element that encloses the text range. 		
			Returns a reference to the new element in createdElement, if createdElement is not nil.
			This and related methods may process a command of type kXMLCreateElementCmdBoss behind the facade.

			@param tagToApply name of tag to mark up text range; it will create a tag in the document tag list (IXMLTagList)if one doesn't already exist. 
			@param storyUIDRef specifies text model containing text to mark-up
			@param startTextIndex location of the start of the range you want to tag in the text model
			@param endTextIndex location of end of the range you want to tag in the text model
			@param parentXMLR parent reference, can be kInvalidXMLReference, optionally you may pass a reference to an element
			in the story to start searching from, to find the element that encloses the text range
			@param createdElement [OUT] if createdElement is not nil, contains a reference to the newly created element
			@param doVerify [DEBUG only] whether to perform structure verification after command is executed
			@param useExistingMarkers If kFalse, the create command will create new markers for the element.
			If kTrue, the create command will use the existing markers at startTextIndex and endTextIndex for the element (caller guarantees they are valid marker characters)
			@return ErrorCode kSuccess if operation could be completed, kFailure otherwise
		*/
		virtual ErrorCode CreateElement(const WideString& tagToApply, UIDRef storyUIDRef, TextIndex startTextIndex, TextIndex endTextIndex, const XMLReference& parentXMLR = kInvalidXMLReference, XMLReference *createdElement = nil, bool16 doVerify = kTrue, bool16 useExistingMarkers = kFalse) = 0;

		/**	Can be used to tag a text range; creates named tag if it doesn't already exist in tag-list.
			The command will automatically find the XML element which will be the parent of the of the new element, based on the
			range you pass in. This can be slow on a story with many elements, so optionally you may pass a reference to an element (parentXMLR)
			in the story to start searching from, to find the element that encloses the text range. 		
			Returns a command of type kXMLCreateElementCmdBoss to create the new element.

			@param tagToApply name of tag to mark up text range; it will create a tag in the document tag list (IXMLTagList)if one doesn't already exist. 
			@param storyUIDRef specifies text model containing text to mark-up
			@param startTextIndex location of the start of the range you want to tag in the text model
			@param endTextIndex location of end of the range you want to tag in the text model
			@param parentXMLR parent reference, can be kInvalidXMLReference, optionally you may pass a reference to an element
			in the story to start searching from, to find the element that encloses the text range
			@param doVerify [DEBUG only] whether to perform structure verification after command is executed
			@param useExistingMarkers If kFalse, the create command will create new markers for the element.
			If kTrue, the create command will use the existing markers at startTextIndex and endTextIndex for the element (caller guarantees they are valid marker characters)
		    @return ICommand interface ptr with reference count incremented 
		*/
		virtual ICommand* CreateElementCommand(const WideString& tagToApply, UIDRef storyUIDRef, TextIndex startTextIndex, TextIndex endTextIndex, const XMLReference& parentXMLR = kInvalidXMLReference, bool16 doVerify = kTrue, bool16 useExistingMarkers = kFalse) = 0;

		/**	Method to create element and tag a text range
		   @param tagToApply name of tag to mark up text range; it will create a tag in the document tag list (IXMLTagList) if one doesn't already exist.
		   @param storyUIDRef specifies text model containing text to mark-up
		   @param range identifies range to mark-up with given tag
		   @param parentXMLR parent reference, can be kInvalidXMLReference, optionally you may pass a reference to an element
			in the story to start searching from, to find the element that encloses the text range
		   @param createdElement [OUT] if createdElement is not nil, contains a reference to the newly created element
		   @param doVerify [DEBUG only] whether to perform structure verification after command is executed
			@param useExistingMarkers If kFalse, the create command will create new markers for the element.
			If kTrue, the create command will use the existing markers at the beginning and the end of the range for the element (caller guarantees they are valid marker characters)
		   @return ErrorCode kSuccess if operation could be completed, kFailure otherwise
		 */
		virtual ErrorCode CreateElement(const WideString& tagToApply, UIDRef storyUIDRef, const RangeData& range, const XMLReference& parentXMLR = kInvalidXMLReference, XMLReference *createdElement = nil, bool16 doVerify = kTrue, bool16 useExistingMarkers = kFalse) = 0;

		/**	Method to create a command to create an element and tag a text range
		    @param tagToApply name of tag to mark up text range; it will create a tag in the document tag list (IXMLTagList) if one doesn't already exist.
		    @param storyUIDRef specifies text model containing text to mark-up
		    @param range identifies range to mark-up with given tag
		    @param parentXMLR parent reference, can be kInvalidXMLReference, optionally you may pass a reference to an element
			in the story to start searching from, to find the element that encloses the text range
			@param doVerify [DEBUG only] whether to perform structure verification after command is executed
			@param useExistingMarkers If kFalse, the create command will create new markers for the element.
			If kTrue, the create command will use the existing markers at the beginning and the end of the range for the element (caller guarantees they are valid marker characters)
		    @return ICommand interface ptr with reference count incremented 
		 */
		virtual ICommand* CreateElementCommand(const WideString& tagToApply, UIDRef storyUIDRef, const RangeData& range, const XMLReference& parentXMLR = kInvalidXMLReference, bool16 doVerify = kTrue, bool16 useExistingMarkers = kFalse) = 0;

		/** Method to create element and tag text range.
			@param tagToApply UID of tag to apply
			@param storyUIDRef specifies text model containing text to mark-up
			@param startTextIndex location of the start of the range you want to tag in the text model
			@param endTextIndex location of end of the range you want to tag in the text model
			@param parentXMLRef parent reference, can be kInvalidXMLReference, optionally you may pass a reference to an element
			in the story to start searching from, to find the element that encloses the text range
			@param createdElement [OUT] if not nil, contains a reference to the newly created element 
			@param doVerify [DEBUG only] whether to perform structure verification after command is executed
			@param useExistingMarkers If kFalse, the create command will create new markers for the element.
			If kTrue, the create command will use the existing markers at startTextIndex and endTextIndex for the element (caller guarantees they are valid marker characters)
		   @return ErrorCode kSuccess if operation could be completed successfully, kFailure otherwise
		 */
		virtual ErrorCode CreateElement(UID tagToApply, UIDRef storyUIDRef, TextIndex startTextIndex, TextIndex endTextIndex, const XMLReference& parentXMLRef = kInvalidXMLReference, XMLReference *createdElement = nil, bool16 doVerify = kTrue, bool16 useExistingMarkers = kFalse) = 0;

		/** Method to create a command to create an element and tag text range.
			@param tagToApply UID of tag to apply
		    @param storyUIDRef specifies text model containing text to mark-up
		    @param startTextIndex location of the start of the range you want to tag in the text model
		    @param endTextIndex location of end of the range you want to tag in the text model
		    @param parentXMLRef parent reference, can be kInvalidXMLReference, optionally you may pass a reference to an element
			in the story to start searching from, to find the element that encloses the text range
			@param doVerify [DEBUG only] whether to perform structure verification after command is executed
			@param useExistingMarkers If kFalse, the create command will create new markers for the element.
			If kTrue, the create command will use the existing markers at startTextIndex and endTextIndex for the element (caller guarantees they are valid marker characters)
		    @return ICommand interface ptr with reference count incremented 
		 */
		virtual ICommand* CreateElementCommand(UID tagToApply, UIDRef storyUIDRef, TextIndex startTextIndex, TextIndex endTextIndex, const XMLReference& parentXMLRef = kInvalidXMLReference, bool16 doVerify = kTrue, bool16 useExistingMarkers = kFalse) = 0;

		/**	Call when you are creating a new element as a child of an existing element, and you want the start and end locations in the text
			to be generated automatically. 
			
			@param tagToApply name of tag; it will create a tag in the document if one doesn't already exist. 
			@param contentItem reference to the content the tag will hold (text story, image, or pdf) or a graphic frame
			@param parentXMLRef parent reference, can be kInvalidXMLReference, optionally you may pass a reference to an element
			in the story to start searching from, to find the element that encloses the text range
			@param indexInParent location within the parent where the new
			element will be created
			@param createdElement [OUT] if createdElement is not nil, contains a reference to the newly created element 
			@param doVerify [DEBUG only] whether to perform structure verification after command is executed
			@return ErrorCode kSuccess if operation could be completed successfully, kFailure otherwise
		*/
		virtual ErrorCode CreateElement(const WideString& tagToApply, UID contentItem, const XMLReference& parentXMLRef, int32 indexInParent, XMLReference *createdElement = nil, bool16 doVerify = kTrue) = 0;

		/** Create an element given a UID of a tag to apply (IXMLTag)
		   @param tagToApply name of tag; it will create a tag in the document if one doesn't already exist. 
		   @param contentItem reference to the content the tag will hold (text story, image, or pdf) or a graphic frame
		   @param parentXMLRef parent reference, can be kInvalidXMLReference, optionally you may pass a reference to an element
			in the story to start searching from, to find the element that encloses the text range
		   @param indexInParent location within the parent where the new
			element will be created
		   @param createdElement [OUT] if createdElement is not nil, contains a reference to the newly created element 
		   @param doVerify [DEBUG only] whether to perform structure verification after command is executed
		   @return ErrorCode kSuccess if operation could be completed successfully, kFailure otherwise
		 */
		virtual ErrorCode CreateElement(UID tagToApply, UID contentItem, const XMLReference& parentXMLRef, int32 indexInParent, XMLReference *createdElement = nil, bool16 doVerify = kTrue) = 0;
		
		/** Create an element given a name of a tag to apply
			@param tagToApply name of tag; it will create a tag in the document if one doesn't already exist. 
			@param startCell first cell in the range to tag
			@param endCell last cell in the range to tag
			@param parentXMLRef parent reference, can be kInvalidXMLReference, optionally you may pass a reference to an element
			in the story to start searching from, to find the element that encloses the text range
			@param createdElement [OUT] if createdElement is not nil, contains a reference to the newly created element 
			@param doVerify [DEBUG only] whether to perform structure verification after command is executed
			@return ErrorCode kSuccess if operation could be completed successfully, kFailure otherwise
		*/
		virtual ErrorCode CreateElement(const WideString& tagToApply, const UIDRef& table, GridID anchor, const GridSpan& span, XMLReference *createdElement = nil, bool16 doVerify = kTrue) = 0;

		/** Create an element given a UID of a tag to apply (IXMLTag)
		    @param tagToApply name of tag; it will create a tag in the document if one doesn't already exist. 
			@param startCell first cell in the range to tag
			@param endCell last cell in the range to tag
		    @param parentXMLRef parent reference, can be kInvalidXMLReference, optionally you may pass a reference to an element
			in the story to start searching from, to find the element that encloses the text range
		    @param createdElement [OUT] if createdElement is not nil, contains a reference to the newly created element 
		    @param doVerify [DEBUG only] whether to perform structure verification after command is executed
		    @return ErrorCode kSuccess if operation could be completed successfully, kFailure otherwise
		 */
		virtual ErrorCode CreateElement(UID tagToApply, const UIDRef& table, GridID anchor, const GridSpan& span, XMLReference *createdElement = nil, bool16 doVerify = kTrue) = 0;

		/** Create an element given a name of a tag to apply
			@param tagToApply name of tag; it will create a tag in the document if one doesn't already exist
			@param tableModelUIDRef UIDRef of table model containing the cell
			@param cellGridID GridID of cell to tag
			@param createdElement [OUT] if createdElement is not nil, contains a reference to the newly created element 
			@param doVerify [DEBUG only] whether to perform structure verification after command is executed
			@return ErrorCode kSuccess if operation could be completed successfully, kFailure otherwise
		*/
		virtual ErrorCode CreateElement(const WideString& tagToApply, const UIDRef& tableModelUIDRef, GridID cellGridID, XMLReference *createdElement = nil, bool16 doVerify = kTrue) = 0;

		/** Create an element given a UID of a tag to apply (IXMLTag)
		    @param tagToApply UID of tag to apply (IXMLTag)
			@param tableModelUIDRef UIDRef of table model containing the cell
			@param cellGridID GridID of cell to tag
			@param createdElement [OUT] if createdElement is not nil, contains a reference to the newly created element 
			@param doVerify [DEBUG only] whether to perform structure verification after command is executed
			@return ErrorCode kSuccess if operation could be completed successfully, kFailure otherwise
		 */
		virtual ErrorCode CreateElement(UID tagToApply, const UIDRef& tableModelUIDRef, GridID cellGridID, XMLReference *createdElement = nil, bool16 doVerify = kTrue) = 0;

		/** Create an element given a UID of a tag to apply (IXMLTag)
		    @param tagToApply UID of tag to apply (IXMLTag)
			@param tableModelUIDRef UIDRef of table model containing the cell
			@param cellGridID GridID of cell to tag
			@param doVerify [DEBUG only] whether to perform structure verification after command is executed
		    @return ICommand interface ptr with reference count incremented 
		 */
		virtual ICommand *CreateElementCommand(UID tagToApply, const UIDRef& tableModelUIDRef, GridID cellGridID, bool16 doVerify = kTrue) = 0;

		/** Create an element using the given insert element info
		   @param xmlDTDInsertElement insert element info to create element with
		   @param createdElement [OUT] if returned error is kSuccess and createdElement is not nil, contains the reference to the newly created element 
		   @param doVerify [DEBUG only] whether to perform structure verification after command is executed
		   @return ErrorCode kSuccess if operation be completed successfully; error code otherwise
		 */
		virtual ErrorCode CreateElement(const XMLDTDInsertElement& xmlDTDInsertElement, XMLReference *createdElement = nil, bool16 doVerify = kTrue) = 0;

		/** Create an element given the containing story and the content item. 
			Since no parent element is specified, 
			the created element is not added to the XML structure.
			The caller is responsible for maintaining the new element.
			NOTE: this is limited use only. Do not use unless absolutely necessary.  Structure verification is not done because there's no parent anyway and is thus not part of XML structure.
			@param tagToApply tag to apply to the element
			@param storyUIDRef UIDRef of the story containing the element 
			@param contentItem content item in the layout view which will represent the content
			@param addToDocRefList whetehr to insert the new element to the IXMLReferenceListData interface on the document
			@param createdElement [OUT] if returned error is kSuccess and createdElement is not nil, contains the reference to the newly created element 
		*/
		virtual ErrorCode CreateElement(UID tagToApply, const UIDRef& storyUIDRef, UID contentItem, bool16 addToDocRefList, XMLReference *createdElement = nil, bool16 doVerify = kTrue) = 0;

		/** Create table and table cell elements
			@param tableTagToApply name of tag to apply to the table
			@param tableCellTagToApply name of tag to apply to the table cells
			@param storyUIDRef UIDRef of the story containing the table
			@param textIndex textIndex of any cell in the table
			@param createdElement [OUT] if createdElement is not nil, receives a reference to the newly created element
			@param doVerify [DEBUG only] whether to perform structure verification after command is executed
			@return ErrorCode kSuccess if operation could be completed successfully, kFailure otherwise
		*/
		virtual ErrorCode CreateTableElement(const WideString& tableTagToApply, const WideString& tableCellTagToApply, const UIDRef& storyUIDRef, TextIndex textIndex, XMLReference *createdTableElement = nil, bool16 doVerify = kTrue) = 0;


		/** Generate a command to create table and table cell elements
			@param tableTagToApply name of tag to apply to the table
			@param tableCellTagToApply name of tag to apply to the table cells
			@param storyUIDRef UIDRef of the story containing the table
			@param textIndex textIndex of any cell in the table
			@param doVerify [DEBUG only] whether to perform structure verification after command is executed
		    @return ICommand interface ptr with reference count incremented 
		*/
		virtual ICommand *CreateTableElementCommand(const WideString& tableTagToApply, const WideString& tableCellTagToApply, const UIDRef& storyUIDRef, TextIndex textIndex, bool16 doVerify = kTrue) = 0;


		/** Create table and table cell elements
			@param tableTagToApply UID of tag to apply to the table
			@param tableCellTagToApply UID of tag to apply to the table cells
			@param storyUIDRef UIDRef of the story containing the table
			@param textIndex textIndex of any cell in the table
			@param createdElement [OUT] if createdElement is not nil, receives a reference to the newly created element
			@param doVerify [DEBUG only] whether to perform structure verification after command is executed
			@return ErrorCode kSuccess if operation could be completed successfully, kFailure otherwise
		*/
		virtual ErrorCode CreateTableElement(UID tableTagToApply, UID tableCellTagToApply, const UIDRef& storyUIDRef, TextIndex textIndex, XMLReference *createdTableElement = nil, bool16 doVerify = kTrue) = 0;


		/** Generate a command to create table and table cell elements
			@param tableTagToApply UID of tag to apply to the table
			@param tableCellTagToApply UID of tag to apply to the table cells
			@param storyUIDRef UIDRef of the story containing the table
			@param textIndex textIndex of any cell in the table
			@param doVerify [DEBUG only] whether to perform structure verification after command is executed
		    @return ICommand interface ptr with reference count incremented 
		*/
		virtual ICommand *CreateTableElementCommand(UID tableTagToApply, UID tableCellTagToApply, const UIDRef& storyUIDRef, TextIndex textIndex, bool16 doVerify = kTrue) = 0;


		/** Create table and table cell elements
			@param tableTagToApply name of tag to apply to the table
			@param tableCellTagToApply name of tag to apply to the table cells
			@param tableModelUIDRef UIDRef of table model to tag
			@param createdElement [OUT] if createdElement is not nil, receives a reference to the newly created element
			@param doVerify [DEBUG only] whether to perform structure verification after command is executed
			@return ErrorCode kSuccess if operation could be completed successfully, kFailure otherwise
		*/
		virtual ErrorCode CreateTableElement(const WideString& tableTagToApply, const WideString& tableCellTagToApply, const UIDRef& tableModelUIDRef, XMLReference *createdTableElement = nil, bool16 doVerify = kTrue) = 0;


		/** Generate a command to create table and table cell elements
			@param tableTagToApply name of tag to apply to the table
			@param tableCellTagToApply name of tag to apply to the table cells
			@param tableModelUIDRef UIDRef of table model to tag
			@param doVerify [DEBUG only] whether to perform structure verification after command is executed
		    @return ICommand interface ptr with reference count incremented 
		*/
		virtual ICommand *CreateTableElementCommand(const WideString& tableTagToApply, const WideString& tableCellTagToApply, const UIDRef& tableModelUIDRef, bool16 doVerify = kTrue) = 0;


		/** Create table and table cell elements
			@param tableTagToApply UID of tag to apply to the table
			@param tableCellTagToApply UID of tag to apply to the table cells
			@param tableModelUIDRef UIDRef of table model to tag
			@param createdElement [OUT] if createdElement is not nil, receives a reference to the newly created element
			@param doVerify [DEBUG only] whether to perform structure verification after command is executed
			@return ErrorCode kSuccess if operation could be completed successfully, kFailure otherwise
		*/
		virtual ErrorCode CreateTableElement(UID tableTagToApply, UID tableCellTagToApply, const UIDRef& tableModelUIDRef, XMLReference *createdTableElement = nil, bool16 doVerify = kTrue) = 0;


		/** Generate a command to create table and table cell elements
			@param tableTagToApply UID of tag to apply to the table
			@param tableCellTagToApply UID of tag to apply to the table cells
			@param tableModelUIDRef UIDRef of table model to tag
			@param doVerify [DEBUG only] whether to perform structure verification after command is executed
		    @return ICommand interface ptr with reference count incremented 
		*/
		virtual ICommand *CreateTableElementCommand(UID tableTagToApply, UID tableCellTagToApply, const UIDRef& tableModelUIDRef, bool16 doVerify = kTrue) = 0;
		
		/** Create table and table cell elements
			@param tableTagData information about what tags to use when tagging
			@param tableModelUIDRef UIDRef of table model to tag
			@param createdElement [OUT] if createdElement is not nil, receives a reference to the newly created element
			@param doVerify [DEBUG only] whether to perform structure verification after command is executed
			@return ErrorCode kSuccess if operation could be completed successfully, kFailure otherwise
		*/
		virtual ErrorCode CreateTableElement(const TableTagData& tableTagData, const UIDRef& tableModelUIDRef, XMLReference *createdTableElement = nil, bool16 doVerify = kTrue) = 0;
		
		/** Create table and table cell elements
			@param tableTagData information about what tags to use when tagging
			@param storyUIDRef UIDRef of the story containing the table
			@param textIndex textIndex of any cell in the table
			@param createdElement [OUT] if createdElement is not nil, receives a reference to the newly created element
			@param doVerify [DEBUG only] whether to perform structure verification after command is executed
			@return ErrorCode kSuccess if operation could be completed successfully, kFailure otherwise
		*/
		virtual ErrorCode CreateTableElement(const TableTagData& tableTagData, const UIDRef& storyUIDRef, TextIndex textIndex, XMLReference *createdTableElement = nil, bool16 doVerify = kTrue) = 0;
					
		/** Generate a command to create table and table cell elements
			@param tableTagData information about what tags to use when tagging
			@param tableModelUIDRef UIDRef of table model to tag
			@param doVerify [DEBUG only] whether to perform structure verification after command is executed
		    @return ICommand interface ptr with reference count incremented 
		*/
		virtual ICommand *CreateTableElementCommand(const TableTagData& tableTagData, const UIDRef& tableModelUIDRef, bool16 doVerify = kTrue) = 0;
		
		/** Generate a command to create table and table cell elements
			@param tableTagData information about what tags to use when tagging
			@param storyUIDRef UIDRef of the story containing the table
			@param textIndex textIndex of any cell in the table
			@param doVerify [DEBUG only] whether to perform structure verification after command is executed
		    @return ICommand interface ptr with reference count incremented 
		*/
		virtual ICommand *CreateTableElementCommand(const TableTagData& tableTagData, const UIDRef& storyUIDRef, TextIndex textIndex, bool16 doVerify = kTrue) = 0;
			
		/**	Create elements using the Style-To-Tag mapping. This will cycle through user accessible stories in the document. If a story is tagged, 
			all non-link element children in the story are deleted; if a story is not tagged, it will be tagged if it contains a mapped style. Then
			the content of the story is scanned, and elements are created if any style is mapped to a tag. 

			@param docUIDRef specifies the document to process
			@param storyTagUID a story tag UID. If no story tag UID is provided, "Story" will be used, and created if necessary. 
			@return ErrorCode kSuccess if operation could be completed successfully, kFailure otherwise
		 */
		virtual ErrorCode CreateStyleToTagElements(const UIDRef& docUIDRef, UID storyTagUID = kInvalidUID) = 0;

		/**	Delete an element. 
			@param deleteElementXMLRef reference to the element to be deleted
			@param deleteChildren flag which if kTrue will cause the element's children to be deleted
			also
			@param deleteInSameStoryOnly if kTrue, then child elements which are in the 
			same story are deleted, but child elements which are in 
			separate stories (e.g., placed in another frame) are not deleted).  
			@param reconnectChildren if kTrue, deleted element's children are
			reconnected to deleted element's parent at the deleted element's position; this requires deleteChildren to be kFalse.
			@param doVerify [DEBUG only] whether to perform structure verification after command is executed
			@return ErrorCode kSuccess if operation could be completed, kFailure otherwise
		 */
		virtual ErrorCode DeleteElement(const XMLReference& deleteElementXMLRef, bool16 deleteChildren, bool16 deleteInSameStoryOnly = kFalse, bool16 reconnectChildren = kFalse, bool16 doVerify = kTrue) = 0;

		/** Create command to delete an element.
		   @param deleteElementXMLRef reference to the element to be deleted
		   @param deleteChildren flag which if kTrue will cause the element's children to be deleted
			also
		   @param deleteInSameStoryOnly if kTrue, then child elements which are in the 
			same story are deleted, but child elements which are in 
			separate stories (e.g., placed in another frame) are not deleted).  
		   @param reconnectChildren if kTrue, deleted element's children are
			reconnected to deleted element's parent at the deleted element's position; this requires deleteChildren to be kFalse.
		   @param doVerify [DEBUG only] whether to perform structure verification after command is executed
		   @return ICommand interface ptr with reference count incremented 
		 */
		virtual ICommand *DeleteElementCommand(const XMLReference& deleteElementXMLRef, bool16 deleteChildren, bool16 deleteInSameStoryOnly = kFalse, bool16 reconnectChildren = kFalse, bool16 doVerify = kTrue) = 0;
		
		/**	Delete elements (with exception of linked elements) which has at least one marker in the specified text range 
			[startTextIndex, endTextIndex]. 
			Text range is a selection range; i.e.(1,2) means process character at position 1 only.

		   @param storyUIDRef reference to the story containing the text range
		   @param startTextIndex start TextIndex of the text range to process
		   @param endTextIndex end TextIndex of the text range to process
		   @return ErrorCode kSuccess if operation could be completed, kFailure otherwise
		 */
		virtual ErrorCode RangeDeleteElement(const UIDRef& storyUIDRef, TextIndex startTextIndex, TextIndex endTextIndex) = 0;

		/** Does a RangeDeleteElement with startTextIndex of range.Start(nil), endTextIndex of range.End()
		   @param storyUIDRef reference to the story containing the text range
		   @param range specifies the selection range to process; i.e.(1,2) means process character at position 1 only.
		   @return ErrorCode kSuccess if operation could be completed, kFailure otherwise
		 */
		virtual ErrorCode RangeDeleteElement(const UIDRef& storyUIDRef, const RangeData& range) = 0;

		/**	Create a RangeDeleteElement command for later processing
		   @param storyUIDRef reference to the story containing the text range
		   @param startTextIndex start of text range to be processed by command
		   @param endTextIndex end of text range to be processed
		   @return ICommand interface ptr with reference count incremented 
		 */
		virtual ICommand *RangeDeleteElementCommand(const UIDRef& storyUIDRef, TextIndex startTextIndex, TextIndex endTextIndex) = 0;

		/**	Delete an Element and all of it's content. This will delete the element itself and all content including text, 
			linked stories and graphic content  
		   @param deleteElementXMLRef specifies element to delete
		   @param deletePageItems when kFalse (default), only page item contents will be deleted 
		   while page items will remain. When kTrue, page items linked to by the elements will be 
		   deleted as well
		   @return ErrorCode kSuccess if operation could be completed, kFailure otherwise
		 */
		virtual ErrorCode DeleteElementAndContent(const XMLReference& deleteElementXMLRef, bool16 deletePageItems = kFalse) = 0;
		
	
		/**	Move an element to a different location in the hierarchy. 
			Client may either specify an exact text index of the new element in contentOffset; or, if contentOffset is invalid, 
			it will figure out the
			text index based on the element's target position within the parent (newIndexInParent).
		   @param moveElementXMLRef specifies element to move
		   @param newParentXMLRef new location in the hierarchy 
		   @param newIndexInParent 
		   @param contentOffset 
		   @return ErrorCode kSuccess if operation could be completed, kFailure otherwise
		 */
		virtual ErrorCode MoveElement(const XMLReference& moveElementXMLRef, const XMLReference& newParentXMLRef, int32 newIndexInParent, TextIndex contentOffset, bool16 doVerify = kTrue) = 0;
		

		/**	Place an element into a graphic frame. Processes a command of type kXMLPlaceElementCmdBoss behind the
			facade, 
		   @param elementToPlace specifies element to place
		   @param graphicFrame specifies the element into which its to be placed
		   @return ErrorCode kSuccess if operation could be completed, kFailure otherwise
		 */
		virtual ErrorCode PlaceElement(const XMLReference& elementToPlace, const UIDRef& graphicFrame) = 0;

		/**	"Unplace" or suck content back into the story of the parent element. Processes a command of
			type kXMLUnplaceElementCmdBoss behind the facade.

		   @param elementToUnplace reference to element to unplace
		   @return ErrorCode kSuccess if operation could be completed, kFailure otherwise
		 */
		virtual ErrorCode UnplaceElement(const UIDRef& elementToUnplace) = 0;

		/** Create command to "Unplace" or suck content back into the story of the parent element.
			Creates command boss object of type kXMLUnplaceElementCmdBoss.
			@param elementToUnplace reference to element to unplace
		   @return ICommand interface ptr with reference count incremented 
		 */
		virtual ICommand *UnplaceElementCommand(const UIDRef& elementToUnplace) = 0;
		
		/**	Set the tag of an existing element
		   @param elementRef specifies element to change property of
		   @param tag UID of tag (IXMLTag) to associate with element
		   @return ErrorCode kSuccess if operation could be completed, kFailure otherwise
		 */

		virtual ErrorCode SetElement(const XMLReference& elementRef, UID tag) = 0;

		/**	Change the name associated with a given element.
			@param elementRef specifies element to change property of
			@param tag name of the element to use
			@return ErrorCode kSuccess if operation could be completed, kFailure otherwise
		 */
		virtual ErrorCode SetElement(const XMLReference& elementRef, const WideString& tag) = 0;
		
		/** Replace an element associated with a DTD with another element
			@param replaceElement data indicating the replacement. This is usually returned from IIDXMLElement::GetReplaceElementList()
			@return ErrorCode kSuccess if operation be completed successfully; error code otherwise
			
			@see XMLDTDReplaceElement
			@see IIDXMLElement
		*/
		virtual ErrorCode SetElement(const XMLDTDReplaceElement& replaceElement) = 0;
		
		/**	Delete the content in the elements.
			@param elementRef specifies element to remove content from
			@return ErrorCode kSuccess if operation could be completed, kFailure otherwise
		 */
		virtual ErrorCode DeleteElementContent(const XMLReference& elementRef) = 0;

		enum TableTagPreference { 
			kTagByRow, 		/** Each row of the table gets tagged automatically */
			kTagByColumn, 	/** Each column of the table gets tagged automatically */
			kNone,			/** No automatic row/column tagging */
			kTagByRowAndBody	/** In addition to each row of the table gets tagged automatically, also add header, body, and footer elements as appropriate */
			};
			
		/**	Specify how the table should be dynamically tagged.
			Tables can be tagged by row or by column, and then row & column elements will be 
			added dynamically as the table grid layout changes. Or you can set this to none,
			and no dynamic changes are made.
			@param table specifies the table to tag
			@param newSetting how to tag the table
			@return ErrorCode kSuccess if operation could be completed, kFailure otherwise
		 */
		virtual ErrorCode SetTableTagPreference(const XMLReference& tableElement, TableTagPreference newSetting, const TableTagData& tableTagData) = 0;

		/** Starting with the given story thread, recursively tag the story thread and its parent 
			threads until a tagged story thread is reached or it doesn't have a parent thread.
			Tags used are the default tags
			@param textStoryThread story thread and its parent to tag
			@param doVerify [DEBUG only] whether to perform a XML structure verification. Set to 
			kFalse if this is a temporary state
			@return ErrorCode error code from the operation
		*/
		virtual ErrorCode MakeParentStoryThreadTagged(ITextStoryThread *textStoryThread, bool16 doVerify = kTrue) = 0;

		
};
	
#endif // __IXMLElementCommands__
