//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/ui/IColumnHeaderPanelData.h $
//  
//  Owner: Lance Bushore
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
#ifndef __IColumnHeaderPanelData__
#define __IColumnHeaderPanelData__

#include "IPMUnknown.h"
#include "widgetid.h"

class IColumnHeaderPanelData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICOLUMNHEADERPANELDATA };

	// gets the left & right sides of the column, which is sometimes handy to know. Left and right values are in content coordinates(i.e. they match IControlView->GetFrame())
	virtual void GetColumnBounds(int32 columnIndex, int32& outLeftX, int32& outRightX) const = 0;
	virtual void FindGapAndColumnForPoint(const SysPoint globalPt, int32& columnIndex, int32 & gapIndex) const = 0;

	virtual void SetColumnWidths(const K2Vector<int32>& inColumnWidths, bool16 doInval, bool16 doNotify) =0;
	virtual void GetColumnWidths(K2Vector<int32>& outColumnWidths) const =0;

	virtual void SetColumnGap(int32 newGap, bool16 doInval, bool16 doNotify) = 0;
	virtual int32 GetColumnGap() const = 0;

	virtual void SetColumnSort(int32 columnIndex,bool16 sortDescending) = 0;
	virtual bool16 IsSortedDescending() const = 0;
	virtual int32 GetSortedColumnIndex() const = 0;
	
	virtual void SetHeaderIndent(int32 newIndent, bool16 doInval, bool16 doNotify) = 0;
	virtual int32 GetHeaderIndent() const = 0;
	
	virtual void ReorderColumns(int32 oldColumn,int32 newColumnPos) = 0;

	virtual void ArrangeWidgetsIntoColumns() = 0;

	struct ColumnHeaderChangeInfo
	{
		int32 fOldColumnIndex;
		int32 fNewColumnIndex;
	};

};

#endif
