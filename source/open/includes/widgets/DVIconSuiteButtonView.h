//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/DVIconSuiteButtonView.h $
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
#ifndef __DVIconSuiteButtonView__
#define __DVIconSuiteButtonView__

#include "DVIconSuiteBaseView.h"

#ifdef DV_WIDGET_BUILD
#pragma export on
#endif

#include "PNGArt.h"
#include "IInterfaceColors.h"

class HandleButtonChange;

class DV_WIDGET_DECL DVIconSuiteButtonView : public DVIconSuiteBaseView
{
	typedef DVIconSuiteBaseView inherited;
public:
	DVIconSuiteButtonView(IPMUnknown *boss);
 	virtual ~DVIconSuiteButtonView();
	
	virtual void 		ReadWrite(IPMStream* s, ImplementationID prop);
	virtual void		Init(const WidgetID& widgetId, const PMRect& frame, RsrcID rsrcID);
	virtual void		DoPostCreate();
	
	virtual void		DV_Draw(dvaui::drawbot::Drawbot* drawbotP/*, float alpha*/) const;

	virtual void		Hilite(bool16 doHilite = kTrue);
	virtual void		Unhilite();
	//virtual void		OnValueChanged(dvaui::controls::UI_ControlChangedMessage* inMessage);

protected:
	
	virtual	void		LoadIcon(const RsrcID& iconRsrcID, const PluginID& pluginId);
	virtual void 		DrawUnselected(dvaui::drawbot::Drawbot* drawbotP);
	
	virtual void		SetIconDrawingState(EButtonState state);
	
	virtual void 		DrawWell(dvaui::drawbot::Drawbot* drawbotP) const;
	virtual void 		DrawBorder(dvaui::drawbot::Drawbot* drawbotP) const;
	
	virtual bool		ShouldDisplayContainer() const;
	virtual void		ChangeControls(bool16 notifyOfChange = kTrue);

	dvaui::controls::UI_PictureButton*	GetPictureButton();
	
	void				SetEraseImageBackground(bool16 doErase = kTrue) {fEraseImageBackground = doErase;}


private:	
	bool16				fEraseImageBackground;

	// Private implementation class
	class PrivateImpl;
	friend class HandleButtonChange;
};

class DV_WIDGET_DECL DVCachedIconSuiteButtonView : public DVIconSuiteButtonView
{
	typedef DVIconSuiteButtonView inherited; 

public: 
	DVCachedIconSuiteButtonView(IPMUnknown *boss); 
	virtual ~DVCachedIconSuiteButtonView() {}

	virtual void LoadIcon(const RsrcID& iconRsrcID, const PluginID& pluginID);
};

#pragma export off

#endif // __DVIconSuiteButtonView__
