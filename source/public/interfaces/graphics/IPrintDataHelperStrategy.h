//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPrintDataHelperStrategy.h $
//  
//  Owner: Michael Easter
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
#ifndef __IPrintDataHelperStrategy__
#define __IPrintDataHelperStrategy__

#include "IPMUnknown.h"
#include "IPrintData.h"

/**
 Interface allowing the override of the current locked and relevant states
 of print data items.

 Third parties can create a CServiceProvider interface which returns the ServiceID
 kPrintDataHelperStrategyService. If they put this service provider in a boss that
 also provides an implementation of this (IPrintDataHelperStrategy) interface, 
 the IsLocked() and IsRelevant() methods will be called for the print dialog ids.
 NOTE: the most restrictive interface wins - once someone sets an id to be locked,
 it is locked, and other implementations will not be called. The same is true for
 being relevant. Once someone returns kFalse for IsRelevant(), the id is locked 
 and disabled, and other implementations will not be called.

 This interface allows the locking of items that otherwise would not be locked
 by the print data helper.  Although an item's locked state can be partially
 controlled via this interface, print components are still free to change an
 item's value as necessary to maintain the print data in a consistent and valid
 context. This interface is ONLY a means of controlling the print dialog UI and
 print scripting.
 
 This interface also allows the setting of items to a non-relevant state that
 otherwise would be set to a relevant state by the print data helper.  Although
 an item's relevant state can be partially controlled via this interface, print
 components are still free to change an item's value as necessary to maintain the
 print data in a consistent and valid context.

 @see IPrintData
*/
class IPrintDataHelperStrategy : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPRINTDATAHELPERSTRATEGY };

	/**
	 Returns a boolean value denoting whether the print data item identified by
	 the given identifier is in a locked state.  Locked print data
	 items cannot be changed by the user, but are visible to the user.
	 The locked state is superseded by the relevant state - in other words, if
	 the id is not relevant, it is automatically locked and disabled.

	 @param printData	IN Pointer to print data containing the item
	 @param id			IN Identifier of the print data item
	 @return kTrue if the item is always locked, else kFalse
	 */
	virtual bool16 IsLocked(const IPrintData* printData, IPrintData::Id id) const = 0;

	/**
	 Returns a boolean value denoting whether the print data item identified by
	 the given identifier is in a relevant state.  Print data items that are
	 not relevant cannot be changed by the user, and are not visible to the user.
	 The relevant state superseds the locked state - in other words, if
	 the id is not relevant, it is automatically locked and disabled.

	 @param printData	IN Pointer to print data containing the item
	 @param id			IN Identifier of the print data item
	 @return kTrue if the item is relevant, else kFalse
	 */
	virtual bool16 IsRelevant(const IPrintData* printData, IPrintData::Id id) const = 0;
};

#endif	// __IPrintDataHelperStrategy__
