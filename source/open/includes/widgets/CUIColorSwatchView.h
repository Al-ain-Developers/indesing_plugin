//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/CUIColorSwatchView.h $
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
#ifndef __CUIColorSwatchView__
#define __CUIColorSwatchView__

#include "DVControlView.h"

// Used to have the color swatch draw in a mixed state.
// Set the UIDData interface for the widget to this value.
const UID kMixedColorUID = 0xFFFFFFFF;
class IGraphicsPort;

class CUIColorSwatchView : public DVControlView
{
	typedef DVControlView inherited;
public:
	CUIColorSwatchView(IPMUnknown *boss);
	virtual ~CUIColorSwatchView();

	virtual void Init(const WidgetID& widgetId, const PMRect& frame, RsrcID rsrcID);
	virtual void Draw(IViewPort* viewPort, SysRgn updateRgn);
protected:
	virtual void DrawBorder(const PMRect&  adjustedFrame, IGraphicsPort* port, SysRgn updateRgn);
};

#endif
