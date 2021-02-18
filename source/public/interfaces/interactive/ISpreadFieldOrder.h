//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/ISpreadFieldOrder.h $
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
#ifndef __ISpreadFieldOrder_h__
#define __ISpreadFieldOrder_h__

#include "IPMUnknown.h"
#include "FormFieldID.h"
#include "K2Vector.h"
#include "IDocumentFieldOrder.h"

/**
 This class tracks the tab order for form fields...
 These orderings are written to generated PDF files.

 A  tricky issue:

 What about the order for items that appear on multiple pages?
 (such as items on master pages and items that span pages)

 Ideally, such items would have an ordering for each page that
 they appear on.  Therefore we track not only the pageitem but the spread and
 page for each potential instance of the item on a page.

 For tab order, we track every spread with form fields,
 and every page within those spreads that contain form fields.

 But I think for a first attempt at all this, I'm not going to worry about master pages
 and multipage spanning form fields.

 This means that for now,

  The master page items will always be ordered
  before the normal page items (but master page items can be ordered among the
  other master page items).  Multipage spanning page items should have an order
  on each page.

 I should be able to support any ordering of master page items, multipage spanning
 page items and normal page items later on without changing the file format.

 Though this level of control might not be needed...
 @see IDocumentFieldOrder
*/
class ISpreadFieldOrder : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISPREADFIELDORDER };
	typedef K2Vector<UID> TabOrder;

	/** Get Form Field Tab Order for a page on this Spread
		@param inPage a page on this spread (ISpreadFieldOrder is an addin to the spread
	*/
	virtual TabOrder	GetTabOrder(UID inPage) = 0;
	
	/** Set Form Field Tab Order for a page on this Spread
		@param inPage a page on this spread (ISpreadFieldOrder is an addin to the spread
		@param inPageItemList an ordered list of form field UIDs
	*/
	virtual void		SetTabOrder(UID inPage, const TabOrder& inPageItemList) = 0;

	/** Called when a field is added to a hierarchy
		in a document (really when it is added to a spread hierarchy, but it is smart
		enough to ignore the cases where its not in a spread).
		
		Takes care of entering inPageItem (if it's a form field) into the Tab Order
		@param inPageItem Page item being added to hierarchy
	*/
	virtual void			FieldWasAddedToHierarchy(const UID& inPageItem) = 0;

	/** Called when a field is added to a hierarchy
		in a document (really when it is added to a spread hierarchy, but it is smart
		enough to ignore the cases where its not in a spread).
		Used when page uid is already known, so that page doesn't have to be looked up.
		
		Takes care of entering inPageItem (if it's a form field) into the Tab Order
		@param inPageUID Page of inPageItem being added to hierarchy
		@param inPageItem Page item being added to hierarchy
	*/
	virtual void			FieldWasAddedToHierarchy(UID inPageUID, const UID& inPageItem) = 0;

	/** Called when a field is to removed from a hierarchy
		in a document (really when it is removed from a spread hierarchy, but it is smart
		enough to ignore the cases where its not in a spread).
		
		Takes care of removing inPageItem (if it's a form field) from the page's Tab Order
		@param inPageItem Page item being removed to hierarchy
	*/
	virtual void 			FieldWillBeRemovedFromHierarchy(const UID& inPageItem) = 0;
};

#endif // __IFieldOrder_h__
