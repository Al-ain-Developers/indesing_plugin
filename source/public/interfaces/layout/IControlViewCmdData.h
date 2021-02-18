//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IControlViewCmdData.h $
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
//  Command data interface for commands that operate on an 
//  ILayoutControlData.
//  
//========================================================================================

#pragma once
#ifndef __IControlViewCmdData__
#define __IControlViewCmdData__

#include "IPMUnknown.h"
#include "widgetid.h"

class IControlView;

class IControlViewCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICONTROLVIEWCMDDATA };

	virtual void Set(IControlView *view) = 0;
	virtual IControlView *GetControlView() const = 0;
	virtual IDataBase *GetControlViewData( UID* viewUID) const = 0;
};

#endif // __IControlViewCmdData__
