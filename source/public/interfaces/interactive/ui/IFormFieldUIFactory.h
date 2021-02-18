//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/ui/IFormFieldUIFactory.h $
//  
//  Owner: Tim Wright
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
//  User-Interface related routines for a particular form field type.
//  (attached to the FormFieldService boss along with IFormFieldFactory)
//  
//========================================================================================

#ifndef __IFormFieldUIFactory_h__
#define __IFormFieldUIFactory_h__

#include "IPMUnknown.h"
#include "PMString.h"
#include "FormFieldTypes.h"
#include "FormFieldUIID.h"

//=============================================================================

class IDocument;
class IGraphicStyleAttributeBossList;
class IPanelControlData;
class IGraphicAttributeSuite;
class IDialogController;

/** Add-in interface for Form Field Factory that provides ui utility functions for a form field type
*/
class IFormFieldUIFactory : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IFORMFIELDUIFACTORY };
	
	/** @return a tool action id that corresponds to this form field type.
		 For example PushButtonUIFactory returns kPushButtonToolActionID */
	virtual ActionID GetToolActionID() const = 0;
	
	/** @return The widget id of panel that contains controls for field properties for this form field type */
	virtual WidgetID GetPropertiesWidget() const = 0;
	
	/** Do any validation of field-specific properties, return any invalid widget.
		@param inPanelData paneldata from main panel of Form Field Properties dialog
		@return any widget that contains an invalid value */
	virtual WidgetID ValidatePropertyFields( IPanelControlData* inPanelData ) = 0;

	/** @return a subpanel that contains controls that can be used to edit this form field type */	
	virtual IControlView* CreatePanel() const = 0;

	/** Initialize controls in inPanelData based on form field attribute values in inGraphicAttrSuite
		@param inPanelData paneldata from main panel of Form Field Properties dialog
		@param inGraphicAttrSuite graphic attributes for the current selection.
	*/	
	virtual void InitializePropertyFields( IPanelControlData* inPanelData,  IGraphicAttributeSuite* inGraphicAttrSuite ) = 0;

	/** Save attribute values to inGraphicAttrSuite, based on control values in inPanelData
		@param inPanelData paneldata from main panel of Form Field Properties dialog
		@param ioProperties an attribute list to populate
	*/	
	virtual void GetPropertyAttributes( IPanelControlData* inPanelData,  IGraphicStyleAttributeBossList* ioProperties ) = 0;
};

//=============================================================================

#endif //

//  IFormFieldUIFactory.h.
