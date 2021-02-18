//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/PalettePanelView.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __PalettePanel__
#define __PalettePanel__

#include "DVPalettePanelView.h"

#ifdef WIDGET_BUILD
#pragma export on
#endif

/**	PalettePanelView is a ControlView class that is a convenient starting place for palette panels.
	PalettePanelView existed pre CC and was preserved as a convenience. 
	It is now based on DVPalettePanelView, and adds no functionality beyond it.
	@see IControlView, DVPalettePanelView
*/
class WIDGET_DECL PalettePanelView : public DVPalettePanelView
{
	typedef DVPalettePanelView inherited;
	
public:
	PalettePanelView(IPMUnknown* boss);
	virtual ~PalettePanelView();
	
};

#pragma export off

#endif
