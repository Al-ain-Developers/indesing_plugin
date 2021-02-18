//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/DVPanelView.h $
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
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2008 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once
#ifndef __DVPanelView__
#define __DVPanelView__


#include "DVBasePanelView.h"

#ifdef DV_WIDGET_BUILD
#pragma export on
#endif

/**	Drover-based widget equivalent for PanelView - the base container widget. This version does not
 * setup an AGM Graphics chain and should be used for PanelViews that dont need custom AGM drawing.
*/

class DV_WIDGET_DECL DVPanelView : public DVBasePanelView
{
	typedef DVBasePanelView inherited;
public:
			 DVPanelView(IPMUnknown *boss) ;
	virtual	~DVPanelView();

	virtual void DoPostCreate();

private:
	void Draw(IViewPort* viewPort, SysRgn updateRgn); // not supported by DVPanelView
};

/**	Drover-based widget equivalent for PanelView - the base container widget. This version sets up 
 * an AGM Graphics chain and should be used for PanelViews that need to do custom AGM drawing.
 */

class DV_WIDGET_DECL AGMDrawnPanelView : public DVBasePanelView
{
	typedef DVBasePanelView inherited;
public:
			 AGMDrawnPanelView(IPMUnknown *boss);
	virtual	~AGMDrawnPanelView();
	
	virtual void Draw(IViewPort* viewPort, SysRgn updateRgn); // supported by AGMDrawnPanelView
	virtual void DoPostCreate();
};

#pragma export off

#endif

