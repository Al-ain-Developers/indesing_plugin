//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLNodeTarget.h $
//  
//  Owner: Daniel Guenther
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
//  
//  Note:
//  
//========================================================================================

#pragma once
	#ifndef _IXMLNodeTarget_
	#define _IXMLNodeTarget_
//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________
	#include "IPMUnknown.h"
	#include "ShuksanID.h"
	#include "NodeID.h"
#include "K2Vector.h"
#include "XMediaUIID.h"
#include "XMLID.h"
#include "XMLReference.h"
#include "XMLAttributeReference.h"

//________________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________________
/** Represents the nodes in the structure that are the 'target' of operations performed on an active selection
	in the structure view. Would be used from a suite implementation.

	If you are writing your own suite implementation and you
	add in your suite to the ASB and the CSB kXMLStructureSelectionBoss, then in your CSB implementation code
	you'd query for the IXMLNodeTarget interface on 'this'
	to get at the nodes in the structure tree to manipulate from your implementation on the CSB.
 
*/
class IXMLNodeTarget : public IPMUnknown
	{
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_IXMLNODETARGET };

		/** List filter enumeration */
		enum XMLNodeFilterType
		{
			/** */ kRemoveDescendents
		};
		

	//____________________________________________________________________________________________
	//	Member functions
	//____________________________________________________________________________________________
	public:
		//................................................................................
		//	Utilities
		//................................................................................

		/**	Set the database for the layout target (i.e. page items)
		
		 */
//		virtual void			Initialize	(IDataBase*) = 0;

		/**	Is the specified item in the layout target list.
			@return  Index (>= 0 if in list); negative number (< 0) if not in list.

		 */
		virtual int32			Location	(const XMLAttributeReference&) const = 0;

		/**	Is the specified item in the layout target list?
			
			@return Index (>= 0 if in list); negative number (< 0) if not in list. 
		 */
		virtual int32			Location	(const XMLReference&) const = 0;
		
		/** Is the specified item in the layout target list?
			@return Index (>= 0 if in list); negative number (< 0) if not in list
		*/
		virtual int32			CommentLocation	(const XMLReference&) const = 0;

		/** Is the specified item in the layout target list?
			@return Index (>=0 if in list); negative number (< 0) if not in list
		*/
		virtual int32			PILocation(const XMLReference&) const = 0;

		/** Is the specific item in the non-attribute target list?
			@return Index (>= 0 if in list); negative number (< 0) if not in list
		*/
		virtual int32			AllLocation(const XMLReference&) const = 0;

		//................................................................................
		//	(Add to / Remove from) the XML target
		//................................................................................

		/**	Add an attribute to the selection target attribute list.
			@param newItem specifies attribute to add
		 */
		virtual void 									AddAttribute (const XMLAttributeReference& newItem) = 0;

		/**	Remove an attribute from the selection target attribute list.
			@param itemToRemove specifies attribute to remove from list
		 */
		virtual void 									RemoveAttribute (const XMLAttributeReference& itemToRemove) = 0;


		/**	Add an element to the selection target element list.
			@param newItem specifies item to add
		 */
		virtual void 									AddElement (const XMLReference& newItem) = 0;

		/**	Remove an element from the selection target element list.
			@param itemToRemove specifies element to remove
		 */
		virtual void 									RemoveElement (const XMLReference& itemToRemove) = 0;
		

		/** Add a comment to the selection target comment list
			@param newItem specifies item to add
		*/
		virtual void									AddComment (const XMLReference& newItem) = 0;

		/** Remove a comment from the selection target comment list
			@param itemToRemove specifies comment to remove
		*/
		virtual void									RemoveComment (const XMLReference& itemToRemove) = 0;


		/** Add a processing instruction to the selection target PI list
			@param newItem specifies item to add
		*/
		virtual void									AddPI (const XMLReference& newItem) = 0;

		/** Remove a processing instruction from the selection target PI list
			@param itemToRemove specifies PI to remove
		*/
		virtual void									RemovePI (const XMLReference& itemToRemove) = 0;


		/** Add a non-attribute to the selection target all list
			@param newItem specifies item to add
		*/
		virtual void									AddNonAttribute (const XMLReference& newItem) = 0;

		/** Remove a non-attribute from the selection target all list
			@param itemToRemove specifies item to remove
		*/
		virtual void									RemoveNonAttribute (const XMLReference& itemToRemove) = 0;

		
		/**	Remove all elements and attributes from the selection target lists.
			
		 */
		virtual void									Clear (void) = 0;

		/** Remove all non-attributes from the selection target list */
		virtual void									ClearNonAttributes(void) = 0;

		/**	Remove all elements from the selection target list
			
		 */
		virtual void 									ClearElements () = 0;

		/** Remove all comments from the selection target list */
		virtual void									ClearComments(void) = 0;

		/** Remove all processing instructions from the selection target list */
		virtual void									ClearPIs(void) = 0;

		/**	Remove all attributes from the selection target list
			
		 */
		virtual void 									ClearAttributes () = 0;
		

		/**	Return a K2 Vector of XMLAttributeReferences that reflects the current attribute selection.
			
			@return collection of attributes in the selection target list 
		 */
		virtual const K2Vector<XMLAttributeReference>&	GetAttributeNodeList () const = 0;		

		/**	Set target attribute list
			
		 */
		virtual void									SetAttributeNodeList (const K2Vector<XMLAttributeReference>&) = 0;		

		/**	Set the target's attribute UIDList.
			@param XMLAttributeReference 
		 */
		virtual void									SetAttributeNodeList (const XMLAttributeReference&) = 0;

		/**	@return  target attribute list size
		 */
		virtual int32									GetAttributeCount() const = 0;

		/**	Accessor for attribute in list by index
			@param index specifies the location of interest in list
			@return XMLAttributeReference for attribute at given index 
		 */
		virtual const XMLAttributeReference&			GetNthAttribute(int32 index) const = 0;


		/**	Return a K2 Vector of XMLReferences that reflects the current element selection.
			
			@return K2Vector of elements in selection target list 
		 */
		virtual const K2Vector<XMLReference>&			GetElementNodeList () const = 0;		

		/**	Accessor for list of nodes selected, filtered
			@param sortedList [OUT] parameter containing the filtered list from the selection
		 */
		virtual void									GetFilteredElementNodeList (XMLNodeFilterType, K2Vector<XMLReference>& sortedList) const = 0;

		/**	Set the target's element list.
			
		 */
		virtual void									SetElementNodeList (const K2Vector<XMLReference>&) = 0;		

		/**	Set the target element UIDList.
		 */
		virtual void									SetElementNodeList (const XMLReference&) = 0;

		/**	Accessor for count of elements in selected list
			@return  element count
		 */
		virtual int32									GetElementCount() const = 0;

		/**	Accessor for element by index
			@param index location of element of interest
			@return XMLReference to element at given location
		 */
		virtual const XMLReference&						GetNthElement(int32 index) const = 0;
				

		/** Return a K2Vector of XMLReferences that reflects the current comment selection
			@return K2Vector<XMLReference> list of comments in selection target list
		*/
		virtual const K2Vector<XMLReference>&			GetCommentNodeList () const = 0;

		/** Set the target's comment list
			@param K2Vector<XMLReference>& list of comments' XMLReferences
		*/
		virtual void									SetCommentNodeList (const K2Vector<XMLReference>&) = 0;

		/** Set the target's comment list
			@param XMLReference comment's XMLReference
		*/
		virtual void									SetCommentNodeList (const XMLReference&) = 0;

		/** Accessor for count of comments in selected list
			@return int32 comment count
		*/
		virtual int32									GetCommentCount() const = 0;

		/** Accessor for comment by index
			@param index location of comment of interest
			@return XMLReference to comment at given location
		*/
		virtual const XMLReference&						GetNthComment(int32 index) const = 0;

		
		/** Return a K2Vector of XMLReferences that reflects the current processing instruction selection
			@return K2Vector<XMLReference> list of PIs in selection target list
		*/
		virtual const K2Vector<XMLReference>&			GetPINodeList () const = 0;

		/** Set the target's processing instruction list
			@param K2Vector<XMLReference>& list of PIs' XMLReferences
		*/
		virtual void									SetPINodeList (const K2Vector<XMLReference>&) = 0;

		/** Set the target's processing instruction list
			@param XMLReference PI's XMLReference
		*/
		virtual void									SetPINodeList (const XMLReference&) = 0;

		/** Accessor for count of processing instructions in selected list
			@return int32 PI count
		*/
		virtual int32									GetPICount() const = 0;

		/** Accessor for processing instruction by index
			@param index location of PI of interest
			@return XMLReference to PI at given location
		*/
		virtual const XMLReference&						GetNthPI(int32 index) const = 0;

		
		/** Return a K2Vector of XMLReferences that reflects the current non-attribute selection
			@return K2Vector<XMLReference> list of non-attributes in selection target list
		*/
		virtual const K2Vector<XMLReference>&			GetAllNodeList() const = 0;

		/** Set the target's non-attribute list. The type-specific lists will also get filled out 
			according to the element type of each entry in the given list
			@param K2Vector<XMLReference>& list of non-attributes' XMLReferences
		*/
		virtual void									SetAllNodeList (const K2Vector<XMLReference>&) = 0;

		/** Set the target's non-attribute list. The type-specific lists will also get filled out 
			according to the element type of each entry in the given list
			@param XMLReference non-attribute's XMLReferences
		*/
		virtual void									SetAllNodeList (const XMLReference&) = 0;

		/**	Accessor for list of non-attributes selected, filtered
			@param sortedList [OUT] parameter containing the filtered list from the selection
		 */
		virtual void									GetFilteredAllNodeList(IXMLNodeTarget::XMLNodeFilterType, K2Vector<XMLReference>& sortedList) const = 0;

		/** Accessor for count of non-attributes in selected list
			@return int32 non-attribute count
		*/
		virtual int32									GetAllCount() const = 0;

		/** Accessor for non-attribute by index
			@param index location of non-attribute of interest
			@return XMLReference to non-attribute at given location
		*/
		virtual const XMLReference&						GetNthNode(int32 index) const = 0;

		
		/**	Accessor for database associated with selection	
			@return database ptr (see the Initialize method)
		 */
		virtual IDataBase*								GetDataBase() const = 0;

		/**	Accessor to determine if the target is populated or not
		 */
		virtual bool16									HasContent(void) const = 0;

		/**     Initialize
				@param	db		Database the target is associated with. 
		*/

			virtual void            Initialize      (IDataBase* db) = 0;
	};

#endif // _IXMLNodeTarget_