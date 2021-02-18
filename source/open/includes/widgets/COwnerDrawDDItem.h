//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/COwnerDrawDDItem.h $
//  
//  Owner: Ben Park
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
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __COwnerDrawDDItem__
#define __COwnerDrawDDItem__

#include "IOwnerDrawItem.h"
#include "HelperInterface.h"

class WIDGET_DECL COwnerDrawDDItem : public IOwnerDrawItem
{
public:
	COwnerDrawDDItem(IPMUnknown* boss);
	
	virtual void		MeasureItem(int32 itemID,  uint16& itemWidth, uint16& itemHeight);
	virtual bool16		IsItemEnabled(int32 itemID);
	virtual void MeasureItemHeight(int32 itemID, uint16& itemHeight);
	DECLARE_HELPER_METHODS()
};

#endif //__COwnerDrawDDItem__
