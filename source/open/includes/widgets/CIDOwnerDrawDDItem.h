//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/CIDOwnerDrawDDItem.h $
//  
//  Owner: mortimer
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2013 Adobe Systems Incorporated. All rights reserved.
//
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __CIDOwnerDrawDDItem__
#define __CIDOwnerDrawDDItem__

#include "COwnerDrawDDItem.h"
#include "StdHeightWidthConstants.h"

#ifdef WIDGET_BUILD
#pragma export on
#endif

class WIDGET_DECL CIDOwnerDrawDDItem : public COwnerDrawDDItem
{
	typedef COwnerDrawDDItem inherited;
	
public:
			 CIDOwnerDrawDDItem(IPMUnknown* boss) : inherited( boss ) { ; }
	virtual ~CIDOwnerDrawDDItem() { ; }
	
	virtual void	MeasureItem(int32 itemID,  uint16& itemWidth, uint16& itemHeight);
	virtual bool16	IsItemBeingDrawnInsideWidget();

protected:
	/*
	The minimum and the maximum width of the owner drawn drop-downs is limited to kCC2016OwnerDrawDDItemMinHeight and kCC2016OwnerDrawDDItemMaxWidth respectively.
	These constants have been defined in StdHeightWidthConstants.h
	*/
	virtual void LimitHeightWidthToMinHeightWidth(uint16& itemWidth, uint16& itemHeight)
	{
		itemHeight = itemHeight > kCC2016OwnerDrawDDItemMinHeight ? itemHeight : kCC2016OwnerDrawDDItemMinHeight;
		itemWidth = itemWidth < kCC2016OwnerDrawDDItemMinWidth ? kCC2016OwnerDrawDDItemMinWidth : (itemWidth > kCC2016OwnerDrawDDItemMaxWidth ? kCC2016OwnerDrawDDItemMaxWidth : itemWidth);
	}
};

#pragma export off

#endif