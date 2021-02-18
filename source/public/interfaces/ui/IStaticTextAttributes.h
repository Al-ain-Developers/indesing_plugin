//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IStaticTextAttributes.h $
//  
//  Owner: Tom Taylor
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
#ifndef __IStaticTextAttributes__
#define __IStaticTextAttributes__

#include "IPMUnknown.h"
#include "WidgetDefs.h"
#include "widgetid.h"

/** Interface responsible for getting and setting various attributes of static text widgets
	@ingroup text_attr
	@see WidgetDefs.h
*/

class  IStaticTextAttributes : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISTATICTEXTATTRIBUTES };

	/** Set the alignment of the text within its bounding box.
		@param alignment one of {kAlignLeft,kAlignCenter,kAlignRight}, defined in WidgetDefs.h
	*/
	virtual void			SetAlignment(const int16 alignment) = 0;
	
	/** Get the alignment of the text within its bounding box.
		@return current alignment value. Should be one of {kAlignLeft,kAlignCenter,kAlignRight}, defined in WidgetDefs.h
	*/
	virtual int16			GetAlignment() const = 0;

	/** Set the ellipsize style of the text in case it does not fit within its bounding box.
		@param ellipsizeStyle one of {kDontEllipsize, kTrue,kEllipsizeEnd, kTruekEllipsizeBeginning,kEllipsizeMiddle}
	*/
	virtual void			SetEllipsizeStyle(const EllipsizeStyle ellipsizeStyle) = 0;
	
	/** Get the current ellipsize style of the text in case it does not fit within its bounding box.
		@return current ellipsize Style. Should be one of {kDontEllipsize, kTrue,kEllipsizeEnd, kTruekEllipsizeBeginning,kEllipsizeMiddle}.
	*/
	virtual EllipsizeStyle	GetEllipsizeStyle() const = 0;

	/** Set whether or not to convert ampersands to underline.
		@param convertAmpersands kTrue to convert ampersands to underline; otherwise, kFalse.
	*/
	virtual void			SetConvertAmpersandsToUnderline(const bool16 convertAmpersands) = 0;
	
	/** Get whether or not to convert ampersands to underline.
		@return current setting for convert ampersands to underline.
	*/
	virtual bool16			GetConvertAmpersandsToUnderline() const = 0;

	/** Set whether or not to draw an underline for the text
		@param drawUnderline kTrue to draw underline; otherwise, kFalse.
	*/
	virtual void			SetDrawUnderline(const bool16 drawUnderline) = 0;
	
	/** Get whether or not to convert to underline the text.
		@return current setting for underline.
	*/
	virtual bool16			GetDrawUnderline() const = 0;
};	

#endif // __IStaticTextAttributes__
