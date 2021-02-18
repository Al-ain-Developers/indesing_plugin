//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/DVErasablePanelView.h $
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
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __DVErasablePanelView__
#define __DVErasablePanelView__

#include "DVPanelView.h"

#ifdef DV_WIDGET_BUILD
#pragma export on
#endif

/**	DVErasablePanelView is a ControlView container class that optionally erases (background fills) itself before drawing it's content and children.
		
		The member fEraseBeforeDraw, which defaults to kFalse, determines whether the view erases before drawing. Subclasses can change 
		the value of fEraseBeforeDraw. This flag is usually set from the view resource description file.
		
		The member fEraseToInterfaceColor, which defaults to kInterfacePaletteFill, determines what background color is drawn. 
		This flag is set from the view resource description file.
				
		In addition the drawing code checks for the presence of an IID_IDYNAMICERASEBEFOREDRAWFLAG (IBoolData) interface on the widget boss,
		if present both it and fEraseBeforeDraw must be set to kTrue for the erase/fill to take place.
		
	@see IControlView, PanelView
*/
class DV_WIDGET_DECL DVErasablePanelView : public DVPanelView
{
	typedef DVPanelView inherited;
	
public:
			 DVErasablePanelView( IPMUnknown *boss );
	
	virtual ~DVErasablePanelView( void );

	virtual void ReadWrite( IPMStream *s, ImplementationID prop );
	
	virtual void DV_Draw( dvaui::drawbot::Drawbot *drawbotP ) const;
	
protected:

	bool16	fEraseBeforeDraw;
	
	int32	fEraseToInterfaceColor;	
	
private:
	void Draw(IViewPort* viewPort, SysRgn updateRgn);  // no descendent should be calling draw on an erasable panel!!!
};

#pragma export off

#endif // __DVErasablePanelView__
