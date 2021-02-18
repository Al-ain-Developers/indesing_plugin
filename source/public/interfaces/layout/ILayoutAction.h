//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ILayoutAction.h $
//  
//  Owner: Robin Briggs
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
//  An interface off the document, manages the list of document-wide layers.
//  
//========================================================================================

#pragma once
#ifndef __ILayoutAction__
#define __ILayoutAction__

#include "IPMUnknown.h"
#include "LayoutUIID.h"
#include "UIDRef.h"

class ILayoutControlData;

class ILayoutAction : public IPMUnknown
{
public:
	virtual void SetSpread(ILayoutControlData *layout, const UIDRef& spreadInWindow) = 0;
	virtual void RemoveSpread(ILayoutControlData *layout, const UIDRef& spreadInWindow) = 0;
	virtual void SetDocument(ILayoutControlData *layout, const UIDRef& docInWindow) = 0 ;
	virtual void RemoveDocument(ILayoutControlData *layout, const UIDRef& docInWindow) = 0;
};

#endif	// __ILayoutAction__

