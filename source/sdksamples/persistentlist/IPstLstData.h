//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlist/IPstLstData.h $
//  
//  Owner: Adobe Developer Technologies
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
//  Data interface for a Page Item.
//  
//========================================================================================

#ifndef __IPstLstData_h__
#define __IPstLstData_h__

#include "IPMUnknown.h"
#include "PstLstID.h"
#include "WideString.h"

/** This plug-in adds a UID list interface IPstLstUIDList to kDrawablePageItemBoss.
 * 	A user can create multiple kPstLstDataBoss items and associate them with a page item 
 * 	by maintaining a list of UIDs through the IPstLstUIDList interface.  
 * 	Unlike the BasicPersistentInterface sample, which adds a persistent data interface
 * 	directly to the kDrawablePageItemBoss, this sample allows more flexibility for 
 * 	adding custom data to a page item.	
 * 	@ingroup persistentlist
*/
class IPstLstData : public IPMUnknown
{
public:

	enum	{kDefaultIID = IID_IPSTLSTDATA};

	/** Sets the data in the persistent list item.
		@param theLabel The data member (name) to be set
	*/
	virtual void SetName(const WideString& theLabel) = 0;
	
	/** Gets the data in the persistent list item.
		@return The data member (name) carried by the persistent list item.
	*/
	virtual const WideString&	GetName() = 0;

	/** Set reference to the boss object that owns this boss object. 
		@param parent UID of the boss object that owns this boss.
	*/
	virtual void SetParent(const UID parent) = 0;
	
	/** Return reference to the boss object that owns this boss object.
		@return the UID of the boss object that owns this boss object.
	*/
	virtual UID	GetParent() const = 0;
};
#endif // __IPstLstData_h__
// End, IPstLstData.h.
