//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IStaticMultiLineTextAttr.h $
//  
//  Owner: Rich Gartland
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
#ifndef __IStaticMultiLineTextAttr__
#define __IStaticMultiLineTextAttr__

#include "IControlView.h"

/**	Interface for getting the attributes of a StaticMultiLineTextAttr widget.
*/
class IStaticMultiLineTextAttr : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISTATICMULTILINETEXTATTR };

	/**	Get the widgetID of the associated scrollbar.
		@return the widgetID for the scrollbar associated with this static multi-line text widget.
	*/
	virtual WidgetID	GetScrollBarWidgetID() const = 0;
	
	/**	Get the font ID for the widget.
		@return the fontID for the widget's text output.
	*/
	virtual int32		GetFontID() const = 0;

	/**	Get the number of pixels between lines in the widget.
		@return the number of pixels.
	*/
	virtual int32		GetNumPixelsBetweenLines() const = 0;
	
	/** Get the x and y inset for the text display within the widget frame.
		@return a PMPoint containing the x and y insets (positive values).
	*/
	virtual PMPoint		GetInset() const = 0;

	/**	Get the widgetID of the associated scrollbar.
		Note: Setting the widgetID does not automatically cause the static multi-line text widget to 
		redraw. To ensure that the new widget is used, you must force the dialog to re-layout.
		@return the widgetID for the scrollbar associated with this static multi-line text widget.
	*/
	virtual void	SetScrollBarWidgetID(const WidgetID& widgetID) = 0;

};

#endif
