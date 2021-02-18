//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/DVDropDownElementView.h $
//  
//  Owner: Deepak Gupta
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2015 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __DVDropDownElementView__
#define __DVDropDownElementView__

#include "DVAbstractControlView.h"
#include "IGraphicsPort.h"

#ifdef DV_WIDGET_BUILD
#pragma export on
#endif

/******************************************************************************
 * class DVDropDownElementView
 ******************************************************************************/
class DVPanelDataReference;
class DV_WIDGET_DECL DVDropDownElementView : public DVAbstractControlView
{
	typedef DVAbstractControlView inherited;
public:
	DVDropDownElementView(IPMUnknown *boss, bool16 dropDownInContrastMode = false);
 	virtual ~DVDropDownElementView() {}
	
	/** override of IControlView::Draw, the traditional ControlView drawing method. 
		@param viewport, viewport for drawing
		@param updateRgn, clip region
	*/
	virtual void Draw(IViewPort *viewport, SysRgn updateRgn);

	/** Get DVPanelDataReference * of this element view 
		@return DVPanelDataReference *,  data interface for the owner draw list elements corresponding to this element view 
	*/
	virtual DVPanelDataReference *GetReference();

	/** Set the enable state for widget. Optionally causes invalidate. 
		@param doEnable, Enable the view if TRUE and Disable otherwise
		@param invalidate, invalidate the widget for drawing
	*/
	virtual void Enable(bool16 doEnable, bool16 invalidate);

	/** Set the widget to disabled state. Optionally causes invalidate. 
		@param invalidate, invalidate the widget for drawing
	*/
    virtual void Disable(bool16 invalidate);
    
protected:
	/** Checks if this item element is highlighted 
		@return TRUE is element is highlighted, FALSE otherwise
	*/
	virtual bool16 IsElementHilited() const;

	/** Checks if this item element is drawn as default item of drop down 
		@return TRUE is element is drawn as default, FALSE otherwise
	*/
	bool16 IsDrawingAsDefaultItem() const;

	/** Get the adjusted frame. 
		@return Client rect, If this item element is drawn as default item then adjusted frame would be smaller due to thumb drawn on one side
	*/
	PMRect GetAdjustedFrame()const;

	/**	Draws the content of owner-drawn dropdown element. This should be overridden by all the clients.
		The pure virtualness of Draw() has been removed and this has been made pure virtual because in Draw(), background drawing
		is pretty much the same - Get frame, get background color, fill the rect.
	*/
	virtual void DrawContent(IViewPort *viewport, SysRgn updateRgn) = 0;

	/**	Draws the background of the owner drawn items' background. This is something that all of the owner-drawn dropdowns do.
		This has been taken out from Draw(). SO effectively, Draw() = DrawBackground() followed by DrawContent().
		
		@Params viePort - viewPort for drawing. frameRect - frameRect for the background.
	*/
	virtual void DrawBackground(IGraphicsPort* gPort, const PMRect& frameRect);

	/*
		The default color to draw the background with. This will let the clients have a 
		custom color implementation instead of having to override the drawing.
	*/
	virtual int32 GetDefaultBackgroundColorID() const;

	/*
		The default color to use to hilite the elements on hover. This lets the clients choose 
		different color for hilite if they wish to.
	*/
	virtual int32 GetDefaultHiliteColorID() const;

	/*
		The content color with which the content should be drawn.
		To match this with Illustrator, we are using black color for now.
	*/

	virtual int32 GetDefaultContentColorID() const ;

private:
	float GetThumbWidth()const;
	float GetInset()const;
};

#pragma export off

#endif //__DVDropDownElementView__
