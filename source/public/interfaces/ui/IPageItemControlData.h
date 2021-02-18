//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IPageItemControlData.h $
//  
//  Owner: Bernd Paradies
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
//  IPageItemControlData is an interface of the PageItemWidget. It contains one or more
//  PageItems that are supported by the PageItemWidget: Add/Remove/Clear/Query/GetPageitem*.
//  If IsDrawContent() is true the PageItemWidgetControlView will draw its content.
//  The ItemID is the PMIID that identifies the supported pageitems.
//  
//========================================================================================

#pragma once
#ifndef __IPageItemControlData__
#define __IPageItemControlData__

#include "IPMUnknown.h"
#include "widgetid.h"

class IGeometry;

//========================================================================================
// CLASS IPageItemControlData
//========================================================================================

class IPageItemControlData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPAGEITEMCONTROLDATA };

	// --- multiple pageitem
	virtual bool16					AddPageItem( IGeometry *pItem ) = 0;
	virtual bool16					RemovePageItem( IGeometry *pItem ) = 0;
	virtual void					ClearPageItems() = 0;
	virtual int32					GetPageItemCount() const = 0;
	virtual IGeometry *				QueryNthPageItem( int32 nIndex ) = 0;
	virtual UID						GetNthPageItemUID( 	int32 nIndex ) const = 0;

	// --- If IsDrawContent() is true the PageItemWidgetControlView will draw its content
	virtual bool16					IsDrawContent() const = 0;
	virtual void					SetDrawContent( bool16 bDraw ) = 0;

	// --- The ItemID is the PMIID that identifies the supported pageitems (default: IID_IGEOMETRY)
	virtual const PMIID&			GetItemID() const = 0;
	virtual void					SetItemID( const PMIID& nId  ) = 0;
	
	// --- returns true if our widget is a child of the Layout.
	virtual bool16					IsChildOfLayout() const = 0;

#ifdef DEBUG
	// --- the Widget's debug mode: click the pageitem with pressed Control-Command-keys
	virtual bool16					IsInDebugMode() const = 0;
	virtual void					SetDebugMode( bool16 bNew ) = 0;
#endif
};

#endif
