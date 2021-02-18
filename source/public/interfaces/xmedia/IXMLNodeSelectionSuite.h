//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLNodeSelectionSuite.h $
//  
//  Owner: Ryan Gano
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
	#ifndef _IXMLNodeSelectionSuite_
	#define _IXMLNodeSelectionSuite_
//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________
#include "ShuksanID.h"
#include "IPMUnknown.h"
#include "XMediaUIID.h"
#include "XMLID.h"
#include "NodeID.h"
#include "ISelectionMessages.h"
#include "XMLAttributeReference.h"


//================================================================================================
//________________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________________
//#define IID_IXMLStructureSelection_ISUITE			kShuksanPrefix + 128

/** Methods to support selection on the structure view
*/
class IXMLNodeSelectionSuite : public IPMUnknown
	{
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_IXMLNODESELECTIONSUITE };

	//____________________________________________________________________________________________
	//	Member functions
	//____________________________________________________________________________________________
	public:

		/**	Select the specified item using the selectionMode.
			@param newItem item to be selected
			@param selectionMode specifies replace or add to existing selection
		 */
		virtual void 		SelectAttribute(const XMLAttributeReference& newItem, Selection::Action selectionMode) = 0;

		/**	Select the specified items using the selectionMode.
			@param newItems items to be selected
			@param selectionMode specifies replace or add to existing selection
		 */
		virtual void 		SelectAttribute(const K2Vector<XMLAttributeReference>* newItems, Selection::Action selectionMode) = 0;

		/**	Deselect the specified attributes.
			@param itemsToDeselect list of attributes to de-select
		 */
		virtual void 		DeselectAttribute(const K2Vector<XMLAttributeReference>* itemsToDeselect) = 0;
//		virtual void		DeselectAllAttributeExcept (const XMLAttributeReference&, bool16) = 0;
//		virtual void 		DeselectAllAttribute (bool16 drawit) = 0;


		/**	Select the specified item using the selectionMode.
			@param newItem specifies element to select
			@param selectionMode specifies replace or add to existing selection
		 */
		virtual void 		SelectElement(const XMLReference& newItem, Selection::Action selectionMode) = 0;

		/**	Select the specified items using the selectionMode.
			@param newItems items to select
			@param selectionMode specifies replace or add to existing selection
		 */
		virtual void 		SelectElement(const K2Vector<XMLReference>* newItems, Selection::Action selectionMode) = 0;

		/**	Deselect the specified elements.
			@param itemsToDeselect list of elements to be deslected
		 */
		virtual void 		DeselectElement(const K2Vector<XMLReference>* itemsToDeselect) = 0;
//		virtual void		DeselectAllElementExcept (const XMLReference&, bool16) = 0;
//		virtual void 		DeselectAllElement (bool16 drawit) = 0;


		/**	Select the specified items using the selectionMode.
			@param targetBoss items to select (Must be on the same boss as IXMLNodeTarget)
			@param selectionMode specifies replace or add to existing selection
		 */
		virtual void 		Select (IPMUnknown*	targetBoss, Selection::Action selectionMode) = 0;

		/**	Deselect everything in the selection.
			@param notifyofSelectionChange indicates whether to notify observers that the selection changed
		 */
		virtual void 		DeselectAll (bool8 notifyofSelectionChange = true) = 0;

		/**	Select everything in the selection.
		 */
		virtual void 		SelectAll (void) = 0;

		//	Selection Utilities

		/**	Is the specified element part of this selection?
			@param itemNode - The node to check for in the selection
			@return bool16 kTrue if element specified is selected, kFalse otherwise
		 */
		virtual bool16 		IsElementSelected (const XMLReference& itemNode) = 0;

		/**	Is the specified attribute part of this selection?
			@param itemNode - The node to check for in the selection
			@return bool16 kTrue if attribute selected, kFalse otherwise
		 */
		virtual bool16 		IsAttributeSelected (const XMLAttributeReference& itemNode) = 0;

		/**	Determine if the selection is empty.
			@return bool16 kTrue if selection empty, kFalse otherwise
		 */
		virtual bool16 		IsEmpty (void) const = 0;

		//	Structure Specific Utilities

		/**	Determine whether the selection contains multiple XML types.
			@return kTrue if the selection contains more than one 
			of the following types of items( element, attribute, text snippet) , kFalse otherwise
		 */
		virtual bool16 			IsMixedSelection () const = 0;


		/** Determine whether a non-attribute object is selected.
			@return kTrue if the selection contains non-attributes 
			(this includes element, comment, pi)
		*/
		virtual bool16			IsNonAttributeSelected() const = 0;

		/** Determine if the selection contains the given non-attribute
			@param itemNode - The node to check for in the selection
			@return kTrue if the selection contains the non-attribute passed in
		*/
		virtual bool16			IsNonAttributeSelected(const XMLReference& itemNode) const = 0;


		/**	Determine whether the selection only contains elements
			@return kTrue if all items in selection are elements, kFalse if there are anything else
		 */
		virtual bool16 			IsElementOnlySelection () const = 0;

		/** Determine whether the selection only contains a single element
			@return kTrue only if there is just 1 item selected and it is an element, kFalse otherwise
		 */
		virtual bool16 			IsSingleElementSelection () const = 0;


		/** Determine whether the selection only contains comments
			@return kTrue if all items in selection are comments. kFalse if there are anything else */
		virtual bool16			IsCommentOnlySelection() const = 0;

		/** Determine whether the selection only contains a single comment
			@return kTrue only if there is just 1 item selected and it's a comment. kFalse otherwise */
		virtual bool16			IsSingleCommentSelection() const = 0;


		/** Determine whether the selection only contains PIs
			@return kTrue if all items in selection are processing instructions. kFalse if there are anything else */
		virtual bool16			IsPIOnlySelection() const = 0;

		/** Determine whether the selection only contains a single PI
			@return kTrue only if there is just 1 item selected and it's a processing instruction. kFalse otherwise */
		virtual bool16			IsSinglePISelection() const = 0;


		/**	Determine whether the selection only contains attributesI
			@return kTrue if all items in selection are attributes, 
			kFalse if there are elements or text snippets 
		 */
		virtual bool16 			IsAttributeOnlySelection () const = 0;

		/**	Determine whether the selection only contains a single attribute
			@return kTrue only if there is just 1 item selected and it is an attribute 
		 */
		virtual bool16 			IsSingleAttributeSelection () const = 0;


		/**	Determine if there are text snippets in the selection
			
			@return kTrue if there are text snippets in the selection, kFalse if there are none 
		 */
		virtual bool16 			AreAnyTextSnippetsSelected () const = 0;


		/**	Determine whether the Document element is selected
			@return kTrue if the Doc element is one of the selected items, kFalse otherwise 
		 */
		virtual bool16 			IsDocElementSelected() const = 0;

		/**	Determine whether the Root element is selected
			@return kTrue if the Root element is one of the selected items, kFalse otherwise 
		 */
		virtual bool16 			IsRootElementSelected() const = 0;

		/**	Determine whether the DOCTYPE element is selected
			@return kTrue if the DOCTYPE element is one of the selected items, kFalse otherwise 
		 */
		virtual bool16 			IsDOCTYPEElementSelected() const = 0;
	};

/** Internal Use only */
class IXMLNodeSelectionSuiteMsgData INHERITFROM
	{
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		enum ActionType { kDeselectAll};
	
	//____________________________________________________________________________________________
	//	Member Functions
	//____________________________________________________________________________________________
		virtual ActionType	GetActionType (void) const = 0;
		virtual bool16	 	GetDrawIt (void) const = 0;
	};
	
#endif // _IXMLNodeSelectionSuite_