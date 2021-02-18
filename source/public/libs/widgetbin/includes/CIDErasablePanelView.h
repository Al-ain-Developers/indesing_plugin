//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/CIDErasablePanelView.h $
//  
//  Owner: Michael Mortimer
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2012 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __ErasablePanelView__
#define __ErasablePanelView__

#include "DVErasablePanelView.h"

class WIDGET_DECL CIDErasablePanelView : public DVErasablePanelView 
{ 
	typedef DVErasablePanelView inherited;

public: 
			 CIDErasablePanelView( IPMUnknown *boss ); 

	virtual ~CIDErasablePanelView( void );
};

#endif // __ErasablePanelView__
