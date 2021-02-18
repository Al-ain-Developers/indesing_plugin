//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/ISetBoolCmdData.h $
//  
//  Owner: robin briggs
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
//  Purpose:
//  Data interface for storing booleans.
//  
//========================================================================================

#pragma once
#ifndef __ISetBoolCmdData__
#define __ISetBoolCmdData__

#include "IPMUnknown.h"
#include "XMLID.h"

class ISetBoolCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISETBOOLCMDDATA };

	virtual void Set(IPMUnknown *boss, PMIID pmIID, bool16 newValue) = 0;

	virtual IPMUnknown *GetDataBoss() const = 0;
	virtual PMIID GetPMIID() const = 0;
	virtual bool16 GetNewValue() const = 0;
	
};


#endif // __ISetBoolCmdData__
