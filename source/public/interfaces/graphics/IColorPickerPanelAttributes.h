//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IColorPickerPanelAttributes.h $
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
//  
//  Used to specify how color picker panel should be created.
//  
//========================================================================================

#pragma once
#ifndef __IColorPickerPanelAttributes__
#define __IColorPickerPanelAttributes__

#include "IPMUnknown.h"
#include "ColorPickerID.h"

/**	An interface specifying the color picker settings.
*/
class IColorPickerPanelAttributes : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICOLORPICKERPANELATTRIBUTES };
	
	/**	Returns true if the picker panels should send and receive broadcast to and from the
		graphic state directly.
		@return kTrue if picker panels should interact with graphic state directly; otherwise return kFalse.
	*/
	virtual bool16		GetGraphicStateInteraction() const = 0;

	/**	Returns widget ID of the menu widget. The menu widget could be a dropdown list or
		a flyout popup.
		@return menu widget ID
	*/
	virtual WidgetID	GetPopupWidgetID() const = 0;

	/**	Returns service ID of the picker panel.
		@return service ID of the picker panel.
	*/
	virtual ServiceID	GetServiceID() const = 0;

};

#endif
