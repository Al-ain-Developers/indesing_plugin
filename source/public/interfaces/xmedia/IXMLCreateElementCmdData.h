//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLCreateElementCmdData.h $
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
#ifndef __IXMLCreateElementCmdData__
#define __IXMLCreateElementCmdData__

#include "IPMUnknown.h"
#include "XMLID.h"
#include "XMLReference.h"
#include "TableTypes.h"		// for GridID

/**
	Data interface for adding elements to the logical structure tree;
	if you're writing client code, use IXMLElementCommands and you won't need this
	interface.

	Similar to IHierarchyCmdData, but handles adding only one element
	at a time.
*/
class IXMLCreateElementCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXMLCREATEELEMENTCMDDATA };

	/**	Set the data through a text range, naming the tag.
		@param tagToApply tag to apply to the element tag to apply to the element
		@param storyUIDRef UIDRef of the story containing the text UIDRef of the story containing the text
		@param startTextIndex TextIndex of the text to start tagging TextIndex of the text to start tagging
		@param endTextIndex TextIndex of the last character to tag TextIndex of the last character to tag
		@param parentXMLRef if the story isn't tagged (i.e. backing store), may pass in an ancestor reference for structure position calculations
	 */
	virtual void Set(const WideString& tagToApply, UIDRef storyUIDRef, TextIndex startTextIndex, TextIndex endTextIndex, const XMLReference& parentXMLRef = kInvalidXMLReference) = 0;

	/**	Set the data through a text range, passing UID of tag to apply
		@param tagToApply tag to apply to the element 
		@param storyUIDRef UIDRef of the story containing the text 
		@param startTextIndex TextIndex of the text to start tagging 
		@param endTextIndex TextIndex of the last character to tag 
		@param parentXMLRef if the story isn't tagged (i.e. backing store), may pass in an ancestor reference for structure position calculations 
	 */
	virtual void Set(UID tagToApply, UIDRef storyUIDRef, TextIndex startTextIndex, TextIndex endTextIndex, const XMLReference& parentXMLRef = kInvalidXMLReference) = 0;

	/**	Set data through specifying UID of content item, e.g. frame, naming tag to use.
		@param tagToApply tag to apply to the element 
		@param contentItem content item in the layout view which will represent the content, or the frame UID
		@param parentXMLRef the parent element
		@param indexInParent the index within the parent's list of child elements
	 */
	virtual void Set(const WideString& tagToApply, UID contentItem, const XMLReference& parentXMLRef, int32 indexInParent) = 0;

	/**	Set data through specifying UID of content item, e.g. frame, giving UID of tag (IXMLTag) to use.
		@param tagToApply tag to apply to the element 
		@param contentItem content item in the layout view which will represent the content, or the frame UID
		@param parentXMLRef the parent element
		@param indexInParent the index within the parent's list of child elements
	 */
	virtual void Set(UID tagToApply, UID contentItem, const XMLReference& parentXMLRef, int32 indexInParent) = 0;


	/**	Set data through specifying a range of cells, naming tag to use.
		@param tagToApply tag to apply to the element 
		@param table UIDRef of table model containing the cells
		@param anchor GridID of anchor cell in grid area
		@param span size of grid area to tag
	 */
	virtual void Set(const WideString& tagToApply, const UIDRef& table, GridID anchor, const GridSpan& span) = 0;

	/**	Set data through specifying a range of cells, giving UID of tag (IXMLTag) to use.
		@param tagToApply tag to apply to the element 
		@param table UIDRef of table model containing the cells
		@param anchor GridID of anchor cell in grid area
		@param span size of grid area to tag
	 */
	virtual void Set(UID tagToApply, const UIDRef& table, GridID anchor, const GridSpan& span) = 0;


	/**	Set data through specifying a cell, naming tag to use
		@param tagToApply tag to apply to the element 
		@param tableModelUIDRef UIDRef of table model containing the cell
		@param cellGridID GridID of cell to tag
	 */
	virtual void Set(const WideString& tagToApply, const UIDRef& tableModelUIDRef, GridID cellGridID) = 0;

	/**	Set data through specifying a cell, giving UID of tag (IXMLTag) to use.
		@param tagToApply tag to apply to the element 
		@param tableModelUIDRef UIDRef of table model containing the cell
		@param cellGridID GridID of cell to tag
	 */
	virtual void Set(UID tagToApply, const UIDRef& tableModelUIDRef, GridID cellGridID) = 0;
	
	
	/** Set data through specifying a parent and child index. Note that this will create a 
		structural only, no content associated element
		NOTE: this is limited use only. Do not use unless absolutely necessary
		@param tagToApply tag to apply to the element
		@param parentXMLRef XMLReference of the parent element
		@param indexInParent child index under parentXMLRef the new element should be
	*/
	virtual void Set(const WideString& tagToApply, const XMLReference& parentXMLRef, int32 indexInParent) = 0;
	
	/** Set data through specifying a parent and child index. Note that this will create a 
		structural only, no content associated element
		NOTE: this is limited use only. Do not use unless absolutely necessary
		@param tagToApply tag to apply to the element
		@param parentXMLRef XMLReference of the parent element
		@param indexInParent child index under parentXMLRef the new element should be
	*/
	virtual void Set(UID tagToApply, const XMLReference& parentXMLRef, int32 indexInParent) = 0;
	
	/** Set data through specifying a story and the content item. 
		Since no parent element is specified, 
		the created element is not added to XML structure.
		The caller is responsible for maintaining the new element.
		NOTE: this is limited use only. Do not use unless absolutely necessary
		@param tagToApply tag to apply to the element
		@param storyUIDRef UIDRef of the story containing the element 
		@param contentItem content item in the layout view which will represent the content
		@parem addToDocRefList If kTrue, the created element is added to the IXMLReferenceListData on the document.
	*/
	virtual void Set(UID tagToApply, const UIDRef& storyUIDRef, UID contentItem, bool16 addToDocRefList) = 0;
	
	/**	Accessor for element created, once command executed.
		
		@return the item that was added (call this after the command is processed) 
	 */
	virtual const XMLReference& GetCreatedElement() const = 0;
	
	/**	For use by the command only; don't invoke from client code
		@param newItem [INTERNAL] don't set this from client code
	 */
	virtual void SetCreatedElement(const XMLReference& newItem) = 0;
	
	/**	For use by the command only. 
		Return which Set was used (whether a text-based 'Set' method or a content-item based 'Set' method)
		
		@return bool16 kTrue if table grid area set was used
	 */
	virtual bool16 UsedTableSet() const = 0;

	/**	For use by the command only. 
		Return which Set was used (whether a text-based 'Set' method or a content-item based 'Set' method)
		
		@return bool16 kTrue if text-based set (default) used
	 */
	virtual bool16 UsedTextSet() const = 0;

	/** For use by the command only. Do not invoke from client code
		Return which Set() was used

		@return bool16 kTrue if table cell Set() was used
	*/
	virtual bool16 UsedTableCellSet() const = 0;
	
	/** For use by the command only. Do not invoke from client code
		Return which Set() was used

		@return bool16 kTrue if structural Set() was used
	*/
	virtual bool16 UsedStructuralSet() const = 0;

	/**	For use by the command only; don't invoke from client code
		@param usedTextSet [INTERNAL] don't set this from client code
	 */
	virtual void SetSetMethod(bool16 usedTextSet) = 0;
	
	/**	For use by the command only	
		@return the XML tag that will be applied to the new item.
 
	 */
	virtual UID GetTag() const = 0;
	

	/**	For use by the command only.
		
		@return UIDRef of story stored on this interface
	 */
	virtual UIDRef GetStoryUIDRef() const = 0;

	/**	For use by the command only.
		@param storyUIDRef [INTERNAL] don't set this from client code
	 */
	virtual void SetStoryUIDRef(const UIDRef& storyUIDRef) = 0;
	
	/**	For use by the command only. 
		
		@return the text range to tag 
	 */
	virtual TextIndex GetStartTextIndex() const = 0;

	/**	For use by the command only
		
		@return TextIndex end of text range to be tagged
	 */
	virtual TextIndex GetEndTextIndex() const = 0;

	/**	For use by the command only. 
		
		@return the first cell in the range to tag 
	 */
	virtual const UIDRef& GetTable() const = 0;

	/**	For use by the command only. 
		
		@return the first cell in the range to tag 
	 */
	virtual GridID GetAnchor() const = 0;

	/**	For use by the command only
		
		@return last cell of the range to be tagged
	 */
	virtual const GridSpan& GetSpan() const = 0;

	/**	For use by the command only
		@param startTextIndex [INTERNAL] don't set this from client code, TextIndex of the text to start tagging 
		@param endTextIndex [INTERNAL] don't set this from client code, TextIndex of the last character to tag 
	 */
	virtual void SetTextRange(TextIndex startTextIndex, TextIndex endTextIndex) = 0;
	
	/**	For use by the command only. 
		
		@return   the parent element for the new item
	 */
	virtual const XMLReference& GetParent() const = 0;

	/**	For use by the command only. 
		@param parentXMLRef [INTERNAL] don't set this from client code
	 */
	virtual void SetParent(const XMLReference& parentXMLRef) = 0;

	/**	For use by the command only. 
		@return whether to add the new element to the IXMLReferenceListData on the document.
	 */
	virtual bool16 GetAddToDocRefList() const = 0;

	/**	For use by the command only. 
		
		@return the index within the parent's list of children
	 */
	virtual int32 GetIndexInParent() const = 0;

	/**	For use by the command only. 
		@param indexInParent [INTERNAL] don't set this from client code
	 */
	virtual void SetIndexInParent(int32 indexInParent) = 0;

	/**	For use by the command only. 
		
		@return UID of the item where the content will appear 
	 */
	virtual UID GetContentItem() const = 0;	

	/**	For use by the command only. 
		@param contentItemUID [INTERNAL] don't set this from client code
	 */
	virtual void SetContentItem(UID contentItemUID) = 0;

	/**	For use by the command only. 
		
		@return boss ClassID for the new element 
	 */
	virtual ClassID GetBossID() const = 0;

	/**	For use by the command only. 
		@param bossID [INTERNAL] don't set this from client code
	 */
	virtual void SetBossID(ClassID bossID) = 0;

	/**	For use by the command only. Return whether this content is text on a path content
		
		@return bool16 kTrue if is text on path
	 */
	virtual bool16 IsTextOnPathInline() const = 0;

	/**	For use by the command only. 
		@param isTOP [INTERNAL] don't set this from client code
	 */
	virtual void SetTextOnPathInline(bool16 isTOP) = 0;

	/**	For use by the command only. Return whether the cmd should hook up the item as an inline (if it is an inline).
		This is an override to handle the case where the item is an inline, but is being
		hooked up as a child of a TOP inline.
		
		@return bool16 kTrue if inline check enabled, kFalse otherwise
	 */
	virtual bool16 DoInlineCheck() const = 0;

	/**	For use by the command only. 
		@param doInlineCheck whether to check for inlines during create
	 */
	virtual void SetDoInlineCheck(bool16 doInlineCheck) = 0;

	/** For use by the command only. Return whether the cmd should use forward traverse version 
		of CalcXMLParent. Default is kFalse
	*/
	virtual bool16 DoForwardCalcXMLParent() const = 0;

	/** For use by the command only.
		CalcXMLParent is optimized for append cases, so it traverses in reverse order to find data 
		faster. However, if this command is used to build XML structure in the reverse order, 
		reverse traversal could slow things down, as data is now usually found at the end of the 
		iterations. Use this method to tell the command to use forward traversal version of 
		CalcXMLParent instead. Default is kFalse
	*/
	virtual void SetDoForwardCalcXMLParent(bool16 forwardCalcXMLParent) = 0;

	/**	Get whether or not to add the marker characters to the model or use the existing markers
		@param none
		@return bool16 kTrue = the create command should use the existing markers (caller guarantees they are valid marker characters)
	 */
	virtual bool16 UseExistingMarkers() const = 0;

	/**	Set whether or not to add the marker characters to the model or use the existing markers.
		The caller who sets this to kTrue guarantees that the special marker character exist
		in the text model at the text index location.
		@param shouldUse
	 */
	virtual void SetUseExistingMarkers(const bool16 shouldUse) = 0;

};

#endif	// __IXMLCreateElementCmdData__
