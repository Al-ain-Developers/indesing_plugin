//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/dialogs/OrderListControlData.h $
//  
//  Owner: Reena Agrawal
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


// ----- Implementation Includes -----

#include "OrderListElement.h"
#include "StringListBoxControlData.h"

class OrderListControlData : public StringListBoxControlData
{
public:
	typedef StringListBoxControlData inherited;

	OrderListControlData(IPMUnknown *boss);
	virtual ~OrderListControlData() {}

	// List Maintainence
	void	AddELement(const OrderListElement& item, int32 at = kEnd, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue);
	void	AddELement(const K2Vector<OrderListElement>& items, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue);
	void	ReplaceElement(const OrderListElement& item, int32 index, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue);
	virtual void	Remove(int32 index, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue);	
	virtual void	Clear(bool16 invalidate= kTrue, bool16 notifyOfChange = kTrue);

	// ----- List query -----
	OrderListElement	GetElementAt(int32 index) const;

private:
	mutable K2Vector<OrderListElement>   fOrderElementList;
};
