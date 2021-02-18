//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/dialogs/OrderListControlDataInst.cpp $
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

#include "VCPlugInHeaders.h"

// ----- Interface Includes ------
#include "IListBoxAttributes.h"

// ----- Implementation Includes -----

#include "FormFieldUIID.h"
#include "OrderListElement.h"
#include "OrderListControlData.h"

CREATE_PMINTERFACE(OrderListControlData, kOrderListControlDataImpl)

//----------------------------------------------------------------------------------------
// OrderListControlData constructor 
//----------------------------------------------------------------------------------------

OrderListControlData::OrderListControlData(IPMUnknown *boss) :
	StringListBoxControlData(boss)
{
}

//----------------------------------------------------------------------------------------
// OrderListControlData::AddELement:
//----------------------------------------------------------------------------------------

void OrderListControlData::AddELement(const OrderListElement& item, int32 at, bool16 invalidate, bool16 notifyOfChange)
{
	if (at == IStringListBoxControlData::kEnd)
		fOrderElementList.push_back(item);
	else
		fOrderElementList.insert(fOrderElementList.begin() + at, item);

	inherited::Add(item.GetName(), at, invalidate, notifyOfChange);
	inherited::Refresh();
}

//----------------------------------------------------------------------------------------
// OrderListControlData::AddELement:
//----------------------------------------------------------------------------------------

void OrderListControlData::AddELement(const K2Vector<OrderListElement>& items, bool16 invalidate, bool16 notifyOfChange)
{
	InterfacePtr<IListBoxAttributes> attrs(this, IID_ILISTBOXATTRIBUTES);

	if (attrs)
		attrs->MuteDrawing(kTrue);

	for (K2Vector<OrderListElement>::const_iterator i = items.begin(); i != items.end(); i++)
		AddELement(*i, IStringListBoxControlData::kEnd, invalidate, notifyOfChange);

	if (attrs)
		attrs->MuteDrawing(kFalse);

	inherited::NotifyOfChange(invalidate, notifyOfChange, kListItemAddedMessage);
}

//----------------------------------------------------------------------------------------
// OrderListControlData::Remove
//----------------------------------------------------------------------------------------
void OrderListControlData::Remove(int32 index, bool16 invalidate, bool16 notifyOfChange)
{
	fOrderElementList.erase(fOrderElementList.begin() + index);
	inherited::Remove(index, invalidate, notifyOfChange);
}

//----------------------------------------------------------------------------------------
// OrderListControlData::ReplaceElement
//----------------------------------------------------------------------------------------
void OrderListControlData::ReplaceElement(const OrderListElement& item, int32 index, bool16 invalidate, bool16 notifyOfChange)
{
	fOrderElementList[index] = item;
	inherited::Replace(item.GetName(), index, invalidate, notifyOfChange);	
}

//----------------------------------------------------------------------------------------
// OrderListControlData::Clear
//----------------------------------------------------------------------------------------
void OrderListControlData::Clear(bool16 invalidate, bool16 notifyOfChange)
{
	fOrderElementList.clear(); 
	inherited::Clear(invalidate, notifyOfChange);
}

//----------------------------------------------------------------------------------------
// OrderListControlData::GetElementAt: 
//----------------------------------------------------------------------------------------

OrderListElement OrderListControlData::GetElementAt(int32 index) const
{
	 return fOrderElementList[index];
}