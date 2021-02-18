//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/DVPalettePanelView.h $
//  
//  Owner: Dave Burnard
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
#ifndef __DVPalettePanelView__
#define __DVPalettePanelView__

#include "DVErasablePanelView.h"

#ifdef DV_WIDGET_BUILD
#pragma export on
#endif

/**	DVPalettePanelView is a ControlView class that is a convenient starting place for palette panels.

	The member fDrawDropShadow, which defaults to kFalse, determines whether the view draws a bevel shadow and highlight. 
	This flag is set from the view resource description file.

	@see IControlView, CIDErasablePanelView, PanelView
*/
class DV_WIDGET_DECL DVPalettePanelView : public DVErasablePanelView
{
	typedef DVErasablePanelView inherited;
	
public:
	DVPalettePanelView(IPMUnknown* boss);
	virtual ~DVPalettePanelView();
	
	virtual void		ReadWrite(IPMStream *s, ImplementationID prop);
	virtual void		DV_Draw(dvaui::drawbot::Drawbot* drawbotP) const;
	
private:
	bool16				fDrawDropShadow;
};

#pragma export off

#endif
