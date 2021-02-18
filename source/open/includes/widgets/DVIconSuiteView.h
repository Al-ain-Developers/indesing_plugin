//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/DVIconSuiteView.h $
//  
//  Owner: Vadim Tkachev
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
//  
//========================================================================================

#pragma once
#ifndef __DVIconSuiteView__
#define __DVIconSuiteView__

#include "DVIconSuiteBaseView.h"

#ifdef DV_WIDGET_BUILD
#pragma export on
#endif

#include "PNGArt.h"
#include "IInterfaceColors.h"

class ID_UI_StaticImage;
class DV_WIDGET_DECL DVIconSuiteView : public DVIconSuiteBaseView
{
	typedef DVIconSuiteBaseView inherited;
public:
	DVIconSuiteView(IPMUnknown *boss);
 	virtual ~DVIconSuiteView();
	
	virtual void 		ReadWrite(IPMStream* s, ImplementationID prop);
	virtual void		Init(const WidgetID& widgetId, const PMRect& frame, RsrcID rsrcID);
	virtual void		DoPostCreate();
	
	virtual void		DV_Draw(dvaui::drawbot::Drawbot* drawbotP) const;

protected:

	virtual	void		LoadIcon(const RsrcID& iconRsrcID, const PluginID& pluginId);
	virtual void		SetIconDrawingState(EButtonState state);
	
	virtual void 		DrawWell(dvaui::drawbot::Drawbot* drawbotP) const;
	virtual void 		DrawBorder(dvaui::drawbot::Drawbot* drawbotP) const;
	
	dvaui::controls::UI_StaticImage*	GetStaticImage();
	
	virtual void    DV_NodeChanged(int change);

private:

	// Private implementation class
	class PrivateImpl;
	friend class ID_UI_StaticImage;
};

#pragma export off

#endif // __DVIconSuiteView__
