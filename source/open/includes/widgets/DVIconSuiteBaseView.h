//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/DVIconSuiteBaseView.h $
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
//	Common baseclass for DVIconSuiteView and DVIconSuiteButtonView (Refactored  Jan 2013)
//  
//========================================================================================

#pragma once
#ifndef __DVIconSuiteBaseView__
#define __DVIconSuiteBaseView__

#include "DVHostedWidgetView.h"

#ifdef DV_WIDGET_BUILD
#pragma export on
#endif

#include "PNGArt.h"
#include "IInterfaceColors.h"

class SharedIconSuiteView_PrivateImpl;

/** Common baseclass for DVIconSuiteView and DVIconSuiteButtonView 
	For internal use only, do not subclass.
*/
class DV_WIDGET_DECL DVIconSuiteBaseView : public DVHostedWidgetView
{
	typedef DVHostedWidgetView inherited;
public:
	DVIconSuiteBaseView(IPMUnknown *boss);
 	virtual ~DVIconSuiteBaseView();
	
	virtual void 		ReadWrite(IPMStream* s, ImplementationID prop);
	virtual void		Init(const WidgetID& widgetId, const PMRect& frame, RsrcID rsrcID);
	virtual void		DoPostCreate();

	void SetRsrcID(const RsrcID &id);
	
	/** cached width and height of the latest loaded icon artwork. */
	int	GetIconWidth()  const {return fIconWidth;}
	int	GetIconHeight() const {return fIconHeight;}
protected:
	/** Called early in DV_Draw. Override this method to change the icon to be drawn.
		Better than overriding DrawDisabled, etc. if icon doesnt depend on specific drawing states.
		To change the icon, call SetRsrcID (and SetRsrcPluginID if necessary).
	*/
	virtual void		PreDrawDoIconChange();
	
	/**@name  For Internal Use Only  */
	//@{-----------------------------------------------------------------------------
	enum EButtonState
	{
		kNormal,		// up
		kPushed,		// down
		kDisabled,		// disabled
		kHilited
	};

	virtual	void		LoadIcon(const RsrcID& iconRsrcID, const PluginID& pluginId);
	virtual void		SetIconDrawingState(EButtonState state);
			void		DrawIcon(EButtonState state) {SetIconDrawingState(state);} //alias to the new method name
	
	virtual void		DrawPushed(dvaui::drawbot::Drawbot* drawbotP);
	virtual void 		DrawHilited(dvaui::drawbot::Drawbot* drawbotP);
	virtual void 		DrawSelected(dvaui::drawbot::Drawbot* drawbotP);
	virtual void 		DrawUnselected(dvaui::drawbot::Drawbot* drawbotP);
	virtual void 		DrawDisabled(dvaui::drawbot::Drawbot* drawbotP);
	
	virtual void 		DrawWell(dvaui::drawbot::Drawbot* drawbotP) const;
	virtual void 		DrawBorder(dvaui::drawbot::Drawbot* drawbotP) const;
	
			void		DrawBevel (	dvaui::drawbot::Drawbot* drawbotP,
									const PMRect & frame, 
									const IInterfaceColors::InterfaceColor &topColor, 
									const IInterfaceColors::InterfaceColor &bottomColor) const;

	virtual void		DrawIconAndBorder(dvaui::drawbot::Drawbot* drawbotP) const;

	virtual void		CommonInit();
	
	virtual void		ResetButtonImageSuppliers();
	virtual void		SetButtonImageSupplier(void* imageBuffer, size_t bufferSize, EButtonState state = kNormal);

	//@}-----------------------------------------------------------------------------

protected:
	int					fIconWidth;
	int					fIconHeight;
	
	PNGArt				fButtonUp;
	PNGArt				fButtonDown;
	
	float				fAlpha;
	//this flag checks for light color icons. there are certain cases where we always want to load the light version of the icon, even if a dark one exists.
	bool				fUseBrightRollOverIconOnly;

	// Private implementation class
	inline SharedIconSuiteView_PrivateImpl*	Impl() const {return fImpl;}
	SharedIconSuiteView_PrivateImpl*	fImpl;
};

#pragma export off

#endif // __DVIconSuiteView__
