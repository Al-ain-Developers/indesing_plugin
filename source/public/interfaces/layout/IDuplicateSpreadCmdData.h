//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IDuplicateSpreadCmdData.h $
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
//  Data interface for new/delete pages.
//  
//========================================================================================

#pragma once
#ifndef __IDuplicateSpreadCmdData__
#define __IDuplicateSpreadCmdData__

#include "IPMUnknown.h"
#include "UIDRef.h"
#include "ISyncMasterPageData.h"

class IDuplicateSpreadCmdData : public IPMUnknown
{
public:
	virtual void Set(const UIDRef& sourceSpread, const UIDRef& destinationSpread) = 0;
	virtual const UIDRef& GetSourceSpread() const = 0;
	virtual const UIDRef& GetDestinationSpread() const = 0;
	virtual bool16 GetSignalResponderFlag() const = 0;
	virtual void SetSignalResponderFlag(const bool16& bSignalResponder) = 0;
	virtual const ISyncMasterPageData::SyncMasterPageOptions& GetDuplicateOption() const = 0;
	virtual void SetDuplicateOption(const ISyncMasterPageData::SyncMasterPageOptions& option) = 0;
};

#endif // __IDuplicateSpreadCmdData__
