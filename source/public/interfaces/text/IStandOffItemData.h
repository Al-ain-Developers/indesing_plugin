//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IStandOffItemData.h $
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
//========================================================================================

#pragma once
#ifndef __IStandOffItemData__
#define __IStandOffItemData__

#include "IPMUnknown.h"
#include "StandOffID.h"			// IID_ISTANDOFFITEMDATA 

class IGeometry;

/** IStandOffItemData is an interface of the kStandOffPageItemBoss.
	@ingroup text_wrap
*/
class IStandOffItemData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISTANDOFFITEMDATA };

	// --- SetPageItem sets the pageitem that is the 'home base' of the StandOff 
	virtual void					SetPageItem( IGeometry *pItem ) = 0;
	virtual IGeometry *				QueryPageItem() const = 0;
	
	// --- if IsVisible() == kFalse the StandOff won't Visible
	virtual void					SetVisible( bool16 bNew ) = 0;
	virtual bool16					IsVisible() const = 0;

	// --- if IsLocked() == kTrue you cannot edit the StandOff
	virtual void					SetLock( bool16 bNew ) = 0;
	virtual bool16					IsLocked() const = 0;
	
	// --- if IsUserPointList() == kTrue the user has modified the IGeometry's pointlist
	virtual void					SetUserPointList( bool16 bNew ) = 0;
	virtual bool16					IsUserPointList() const = 0;	
};

#endif

