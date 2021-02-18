//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CCellContent.h $
//  
//  Owner: dwaterfa
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
#ifndef __CCellContent__
#define __CCellContent__

#include "ICellContent.h"
#include "CPMUnknown.h"
#include "ITableLayout.h"

#pragma export on

class PUBLIC_DECL CCellContent : public CPMUnknown<ICellContent>
{
public:
	CCellContent(IPMUnknown *boss);

	virtual void			SetTableModel(const UIDRef& tableModelRef)
		{ fTableModelRef = tableModelRef; }

	virtual UIDRef			GetTableModel() const
		{ return fTableModelRef; }

	virtual void			SetGridID(const GridID& gridID)
		{ fGridID = gridID; }

	virtual GridID			GetGridID() const
		{ return fGridID; }

	virtual void			SetGridAddress(const GridAddress& gridAddress)
		{ fGridAddress = gridAddress; }

	virtual GridAddress		GetGridAddress() const
		{ return fGridAddress; }

	virtual PMRect			GetCellPathBounds(ParcelKey key) const
		{
		InterfacePtr<const ITableLayout> layout(fTableModelRef, UseDefaultIID());
		return layout->GetCellParcelPathBounds(fGridAddress, key);
		}

	virtual UID				GetParcelFrameUID(ParcelKey key) const
		{
		InterfacePtr<const ITableLayout> layout(fTableModelRef, UseDefaultIID());
		return layout->GetParcelTextFrameUID(fGridAddress, key);
		}

	virtual PMMatrix		GetParcelToFrameMatrix(ParcelKey key) const
		{
		InterfacePtr<const ITableLayout> layout(fTableModelRef, UseDefaultIID());
		return layout->GetParcelToTextFrameMatrix(fGridAddress, key);
		}

	virtual bool16			GetParcelAcceptingInvals(ParcelKey key) const
		{
		InterfacePtr<const ITableLayout> layout(fTableModelRef, UseDefaultIID());
		return layout->GetParcelAcceptingInvals(fGridAddress, key);
		}

	virtual void			AddParcelPendingInval(ParcelKey key,
												const PMRect& invalRect)
		{
		InterfacePtr<ITableLayout> layout(fTableModelRef, UseDefaultIID());
		layout->AddParcelPendingInval(fGridAddress, key, invalRect);
		}

	virtual void			NotifyLayoutParcelDamageChanged(ParcelKey key,
															bool16 isDamaged)
		{
		InterfacePtr<ITableLayout> layout(fTableModelRef, UseDefaultIID());
		layout->NotifyParcelContentDamageChanged(fGridAddress, key, isDamaged);
		}

	virtual void			NotifyLayoutParcelPosDependentContentSet(ParcelKey key)
		{
		InterfacePtr<ITableLayout> layout(fTableModelRef, UseDefaultIID());
		layout->NotifyParcelPositionDependentContentSet(fGridAddress, key);
		}

	virtual void			NotifyLayoutParcelInkBoundsChanged(ParcelKey key)
		{
		InterfacePtr<ITableLayout> layout(fTableModelRef, UseDefaultIID());
		layout->NotifyParcelInkBoundsChanged(fGridAddress, key);
		}

	virtual void		InvalCellContent(ParcelKey key)
		{
		}

	virtual void			CollectParcelOwnedItems(ParcelKey key,
												OwnedItemDataList* rList) const
		{
		}

	virtual void			ConvertFromAnna(TableLayout* layout)
		{
		// Derived classes know if they existed in 2.0
		}

protected:
	//
	// These are NOT and should not be persisted.
	//
	UIDRef		fTableModelRef;
	GridID		fGridID;
	GridAddress	fGridAddress;

};

#pragma export off

#endif
