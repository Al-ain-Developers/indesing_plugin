//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IControllingPageItem.h $
//  
//  Owner: Brendan O'Shea
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
//  Description : To set up a page item as a slave to another page item. Used in 
//  conjunction with IControlledPageItems.
//  
//========================================================================================

#pragma once
#ifndef __IControllingPageItem__
#define __IControllingPageItem__

#include "IPMUnknown.h"
#include "MasterPageID.h"
#include "K2Vector.h"



class IControllingPageItem : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICONTROLLINGPAGEITEM };

	virtual void SetControllingUID (UID id) = 0;

	/** return the UID of the controlling page item - kInvalidUID if not being controlled */
	virtual UID GetControllingUID () = 0;
	
	/** when a page item should no longer forward a particular IID, add it to this list */
	virtual void	DontForward(PMIID) = 0;

	/** to undo the 'DontForward', use RestartForwarding (i.e. cause this interface to be forwarded again) */
	virtual void	RestartForwarding(PMIID) = 0;
	
	/** kTrue if the given interface is already being forwarded */
	virtual bool16	IsForwarded(PMIID) = 0;

	/** return the list of all non forwarded interface ids */
	virtual void GetNonForwardedIIDs (K2Vector<PMIID>& list) = 0;

	/** set the list of all non forwarded interface ids */
	virtual void SetNonForwardedIIDs (const K2Vector<PMIID>& list) = 0;
};

#endif
