//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IDocumentFieldOrder.h $
//  
//  Owner: Tim Wright
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
#ifndef __IDocumentFieldOrder_h__
#define __IDocumentFieldOrder_h__

#include "IPMUnknown.h"
#include "FormFieldID.h"
#include "K2Vector.h"

/** This class tracks the calculation order for form fields...
 These orderings are written to generated PDF files.

 A  tricky issue:

 What about the order for items that appear on multiple pages?
 (such as items on master pages and items that span pages)

 Ideally, such items would have an ordering for each page that
 they appear on.  Therefore we track not only the pageitem but the spread and
 page for each potential instance of the item on a page.

  The calc order is just a single list (vector),because the
 the calculation order is supposed to be document-wide.  Each item in the list
 is a spread/page/pageitem triplet to account for multiple appearances of the page
 item on different output pages.

 But I think for a first attempt at all this, I'm not going to worry about master pages
 and multipage spanning form fields.

 This means that for now,

  fSpread and fPage in ItemInstance will be ignored (but read and written)
  Every instance in the PDF output of the master page items and page items
  that span multiple pages will be ordered together.
  This should be okay, since multiple instances of items should not depend on
  eachother.

 I should be able to support any ordering of master page items, multipage spanning
 page items and normal page items later on without changing the file format.

 Though this level of control might not be needed...
 
 @see ISpreadFieldOrder
*/
class IDocumentFieldOrder : public IPMUnknown
{
public:
	struct ItemInstance
	{
		UID fSpread;
		UID fPage;
		UID fPageItem;
		ItemInstance(UID inSpread, UID inPage, UID inPageItem)
		:
			fSpread(inSpread), fPage(inPage), fPageItem(inPageItem)
		{}
	};

	typedef K2Vector<ItemInstance> FieldOrder;
	typedef K2Vector<ItemInstance> CalculationOrder;

	enum { kDefaultIID = IID_IDOCUMENTFIELDORDER };

	/** Called when a form field is added to a hierarchy
		in a document (really when it is added to a spread hierarchy, but it is smart
		enough to ignore the cases where its not in a spread).
		
		Takes care of entering inPageItem (if it's a form field) into the Calculation Order, and Tab Order
		(by calling through to ISpreadFieldOrder
		@param inPageItem Page item being added to hierarchy
		@param inSpread Spread the page item is being added to
	*/
	virtual void			FieldWasAddedToHierarchy(const UID& inPageItem, const UID& inSpread = kInvalidUID) = 0;


	/** Called when a field is removed from a hierarchy
		in a document (really when it is removed to a spread hierarchy, but it is smart
		enough to ignore the cases where its not in a spread).
		
		Takes care of removing inPageItem  (if it's a form field) from the Calculation Order, and Tab Order
		(by calling through to ISpreadFieldOrder
		@param inPageItem Page item being removed to hierarchy
		@param inSpread Spread the page item is being removed from
	*/
	virtual void 			FieldWillBeRemovedFromHierarchy(const UID& inPageItem, const UID& inSpread = kInvalidUID) = 0;

	/** Get Form Field Calculation Order for the document
	*/
	virtual CalculationOrder GetCalculationOrder() = 0;

	/** Set Form Field Calculation Order for the document
		@param inPageItemList an ordered list of form field UID/page/spread triplets
	*/
	virtual void SetCalculationOrder(const CalculationOrder& inPageItemList) = 0;
};

DECLARE_BASE_TYPE(IDocumentFieldOrder::ItemInstance);

#endif // __IDocumentFieldOrder_h__
