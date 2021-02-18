//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IColorPickerWidgetProvider.h $
//  
//  Owner: SusanCL
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
#ifndef	__IColorPickerWidgetProvider__
#define __IColorPickerWidgetProvider__

#include "ColorPickerID.h"
#include "PMRect.h"

/**	A IColorPickerWIdgetProvider is a service provider interface that provides a sub panel
	that is used in InDesign to define a color.
	
	Some common properties:
	The dimension of the panel is typically 207 by 105.
	Such a panel should include the following widgets:
	Color sliders:
		Each slider represents a component in the color model defined by the panel.
		The frame of each slider should include the triangular sliding thumb
	Edit boxes:
		It contains the numeric value indicated by the sliding thumb.
		One for each slider.
	Color bar
		Displays the whole spectrum of the color model represented by the panel
	Proxy box
		This is used to preview the color that is defined in the panel.
	
	The base classes for each of the above components will attempt to draw all widgets
	defined in the panel unless a drawing proc is provided
*/
class IGraphicsPort;
class PMString;
class IControlView;

class IColorPickerWidgetProvider : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICOLORPICKERWIDGETPROVIDER };
	
	/**	Returns the number of sliders provided.
		For example, the number of silders in a RGB color picker panel is 3.
		@return the number of sliders.
	*/
	virtual const int16 GetNumSliders() const = 0;
	
	/**	Returns the base widget ID of the slider widgets provided by this picker.
		Slider widget ID must be consecutive. For example, the base slider widget id is
		defined for the red slider.
		@return the base widget ID of the slider widgets.
	*/
	virtual const int32 GetBaseSliderWidgetID() const = 0;
	
	/**	Returns the base widget ID of the edit box widgets provided by this picker.
		Edit box widget ID must be consecutive. For example, the base edit widget id is
		defined for the red edit box.
		@return the base widget ID of the edit box widgets for the sliders.
	*/
	virtual const int32 GetBaseEditBoxWidgetID() const = 0;

	/**	Returns the widget ID of this picker panel.
		@return the widget ID of the picker panel.
	*/
	virtual const int32 GetWidgetID() const = 0; 

	/**	Returns the color space ID of this picker panel.
		@return the color space of the picker panel.
	*/
	virtual const int32 GetColorSpace() const = 0;

	/**	Returns the name for the color space of this picker panel.
		This is used to build the menu component of the picker.
		Example, A RGB color picker's color model name is "RGB".
		@return a PMString for the name of color space.
	*/
	virtual const PMString& GetPickerModelName() const = 0;
	
	/**	The rendering function for the slider widgets.
		@param view specifies the view of the slider widget
		@param gPort is the graphic port in which the drawing occurs.
		@param updateRgn is the update region.
		@param frame is the rectangular frame for the slider widget.
		@return true if a rendering function is provided; otherwise returns false.
	*/
	virtual bool16 SliderDrawProc(IControlView* view, IGraphicsPort* gPort, SysRgn updateRgn, const PMRect& frame) = 0;

	/**	The rendering function for the color bar widget.
		@param view specifies the view of the color bar widget
		@param gPort is the graphic port in which the drawing occurs.
		@param updateRgn is the update region.
		@param frame is the rectangular frame for the color bar widget.
		@return kTrue if a rendering function is provided; otherwise returns kFalse.
	*/
	virtual bool16 SpectrumDrawProc(IControlView* view, IGraphicsPort* gPort, SysRgn updateRgn, const PMRect& frame) = 0;

	/**	The rendering function for the color proxy widget.
		@param view specifies the view of the color proxy widget
		@param gPort is the graphic port in which the drawing occurs.
		@param updateRgn is the update region.
		@param frame is the rectangular frame for the color prxy widget.
		@return kTrue if a rendering function is provided; otherwise returns kFalse.
	*/
	virtual bool16 ProxyDrawProc(IControlView* view, IGraphicsPort* gPort, SysRgn updateRgn, const PMRect& frame) = 0;
	
};

#endif	//__IColorPickerWidgetProvider__
