//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IDupSpreadSignalData.h $
//  
//  Owner: Patrick Lau
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
//  Purpose:	Data send with the DuplicateSpread signal
//  
//========================================================================================

#pragma once
#ifndef __IDUPLICATESPREADSIGNALDATA__
#define __IDUPLICATESPREADSIGNALDATA__

#include "IPMUnknown.h"
#include "SpreadID.h"
#include "UIDList.h"
class ICommand;

class IDuplicateSpreadSignalData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDUPLICATESPREADSIGNALDATA };
	
    virtual void Set(ICommand *DuplicateSpreadCmd) = 0; // keep it for old user
    virtual void Set(ICommand *DuplicateSpreadCmd, UIDList& itemList, UIDList& destinationSpreadList) = 0; // keep it for old user
	virtual ICommand *GetDuplicateSpreadCmd() = 0;  // may be nil
	virtual const UIDList& GetSourceUIDList() const = 0; //Could be pageList or Spread
	virtual const UIDList& GetDestUIDList() const = 0;
	virtual const bool16& GetSignalResponderFlag() = 0;
	virtual void SetSignalResponderFlag(const bool16& flag) = 0;
};

#endif // __IDUPLICATESPREADSIGNALDATA__

