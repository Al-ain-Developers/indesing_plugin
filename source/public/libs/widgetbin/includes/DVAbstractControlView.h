//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/DVAbstractControlView.h $
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
#ifndef __DVAbstractControlView__
#define __DVAbstractControlView__

#include "DVHostedWidgetView.h"


#ifdef DV_WIDGET_BUILD
#pragma export on
#endif

class ICMSProofing;

/**	DVAbstractControlView is, not surprisingly, an abstract ControlView class. 
 It's purpose is to bridge the drawing environments of drover's drawbot and IControlView's IGraphicsPort.
 When DV_Draw is called, DVAbstractControlView sets up an offscreen drawing environment for AGM-based
 drawing clients and calls their traditional Draw method. Before returning DV_Draw blits the offscreen
 pixels back into the hosts drawing environment.
 
 Internal use Only: DVAbstractControlView cannot be subclassed by external clients since it requires a
 drover based implementation class. 
 External clients should use a concrete class like DVControlView, AGMDrawPanelView, DVPanelView, etc. instead.
 
 @see IControlView, DVHostedWidgetView
 */
class DV_WIDGET_DECL DVAbstractControlView : public DVHostedWidgetView
{
	typedef DVHostedWidgetView inherited;
public:
	// ----- Initialization -----
	
	DVAbstractControlView(IPMUnknown *boss); 
	virtual ~DVAbstractControlView();
	
	/** override of IControlView::Draw, the traditional ControlView drawing method. */
	virtual void Draw(IViewPort* viewPort, SysRgn updateRgn);
	
	/** override of DVHostedWidgetView::DV_Draw, the droverized ControlView drawing method. 
	 Intended for internal use only, but a few simple drawing primitives are available in DVPublicUtilities.h.
	 This implementation sets up an offscreen graphics port and calls the traditional Draw method.
	 */
	virtual void DV_Draw(dvaui::drawbot::Drawbot* drawbotP) const;
	
	/**@name  For Internal Use Only  */
	//@{-----------------------------------------------------------------------------
	static void PreDraw(IViewPort *viewPort, IControlView* iView, int32& setupFlagsOut, ICMSProofing* cmsProof);
	static void PostDraw(IViewPort *viewPort, IControlView* iView, int32 setupFlagsIn, ICMSProofing* cmsProof);
	
	class AGMOffscreenSetup_Impl;
	class DV_WIDGET_DECL AGMOffscreenSetup
	{
	  public:
		AGMOffscreenSetup(const IControlView* view, dvaui::drawbot::Drawbot* drawbot, IViewPort** offscreenViewPortP, SysRgn* clipRgnP);
		~AGMOffscreenSetup();
		
	  private:
		AGMOffscreenSetup_Impl* fImpl;
	};
	//@}-----------------------------------------------------------------------------
	
private:
};

#pragma export off

#endif

