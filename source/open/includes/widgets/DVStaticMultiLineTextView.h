//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/DVStaticMultiLineTextView.h $
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
//========================================================================================

#pragma once
#ifndef __DVDVStaticMultiLineTextView__
#define __DVDVStaticMultiLineTextView__

#include "DVStaticTextView.h"

/**
	DVStaticMultiLineTextView:
	Generic scrollable multiline static text view widget, based on A drover UI_ControlView wrapping a UI_StaticText 
*/
class DV_WIDGET_DECL DVStaticMultiLineTextView : public DVStaticTextView
{
	typedef DVStaticTextView inherited;
public:
	DVStaticMultiLineTextView(IPMUnknown *boss);
	virtual ~DVStaticMultiLineTextView();
	
	virtual void PreDrawGetText(); // Updates all of the text values.

	virtual void DoPostCreate();
	
	virtual void DoAutoAttach();
	virtual void DoAutoDetach();										

protected:
	virtual void GetFont(InterfaceFontInfo& fontInfo) const;
	virtual void UpdateChildBounds();

	virtual dvaui::controls::UI_StaticText* Get_UI_StaticText(); // override to return the wrapped UI_StaticText control
};


/**
	AGMOwnerDrawnStaticMultiLineTextView:
	Generic scrollable owner drawn multiline static text view widget, based the original code from StaticMultiLineTextView 
*/

class DV_WIDGET_DECL AGMOwnerDrawnStaticMultiLineTextView : public AbstractOwnerDrawnStaticTextView
{
	typedef AbstractOwnerDrawnStaticTextView inherited;
public:
	AGMOwnerDrawnStaticMultiLineTextView(IPMUnknown *boss);
	virtual ~AGMOwnerDrawnStaticMultiLineTextView();

	virtual void DoAutoAttach();
	virtual void DoAutoDetach();										

	// AGM based Drawing methods derived from the pre CC StaticMultiLineTextView
	virtual void Draw(IViewPort* viewPort, SysRgn updateRgn);
	virtual void Resize(const PMPoint& newDimensions, bool16 invalidate = kTrue);

protected:
	virtual void GetFont(InterfaceFontInfo& fontInfo) const;	// uses IStaticMultiLineTextAttr
	virtual EllipsizeStyle GetShouldEllipsize() const;			// DrawMultiLines does it for each line...

	// DV_Note: Clients noted that calculating the line breaks in draw caused performance hits in some cases, e.g. LoadStyleStaticMultiLineTextView in Load Object styles dialog.  
	//	So they tried moving the Create line break code the to Resize method, but some of the clients depend on Draw method to do calculation of line breaks.
	//	Now they can choose without overriding Draw or Resize.
	//	Currently this can only be enforced by the derived class AGMOwnerDrawnStaticMultiLineTextView, as drover's UI_StaticText class can only rebreak during Draw.
	enum LineBreakComputeTime {eDuringDraw, eDuringResize};
	virtual LineBreakComputeTime GetLineBreaksComputeTime() const {return eDuringDraw;} // defaults to eDuringDraw, override to choose eDuringResize.

	// called first, before text is drawn
	virtual void DrawBackgroundFill(IViewPort* viewPort, SysRgn updateRgn);					  
	// draw multiple lines, gotten from linebreaker interface
	virtual void DrawMultiLines (IGraphicsContext* gc, const PMString& str, 
								 PMRect frame, const InterfaceFontInfo& fontInfo,
								 const RealAGMColor& textColor);
};

#endif