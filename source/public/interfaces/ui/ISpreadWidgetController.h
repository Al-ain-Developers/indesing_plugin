//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ISpreadWidgetController.h $
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
//========================================================================================

#pragma once
#ifndef __ISpreadWidgetController__
#define __ISpreadWidgetController__

#include "IPMUnknown.h"
#include "K2Vector.h"
#include "PagesPanelID.h"

class IControlView;

class ISpreadWidgetController : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISPREADWIDGETCONTROLLER };
	virtual bool16	AssignSpreadToWidget( const UIDRef& newSpread, K2Vector<IControlView *> *, bool16 bInval) = 0;
	virtual UIDRef GetAssignedSpread() = 0;
};

#endif
