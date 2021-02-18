//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/uifactories/FormFieldUIFactory.h $
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
//  Comments:	 User interface associated with a form field type.
//  
//========================================================================================

#ifndef __FormFieldUIFactory_h__
#define __FormFieldUIFactory_h__

#include "IFormFieldUIFactory.h"

class IPanelControlData;
class IGraphicAttributeSuite;
class IGraphicStyleAttributeBossList;

class FormFieldUIFactory : public CPMUnknown<IFormFieldUIFactory>
{
public:
	FormFieldUIFactory(IPMUnknown * boss);

	ActionID GetToolActionID() const = 0; //Must override.
	WidgetID GetPropertiesWidget() const; //returns kInvalidWidgetID for no extra property panel
	WidgetID ValidatePropertyFields( IPanelControlData*  ); //returns kDefaultWidgetId for no validation.

	virtual IControlView* CreatePanel() const; //returns empty panel

	void InitializePropertyFields( IPanelControlData* inPanelData,  IGraphicAttributeSuite* inGraphicAttrSuite ); //does nothing
	void GetPropertyAttributes( IPanelControlData* inPanelData,  IGraphicStyleAttributeBossList* ioProperties ); //does nothing

protected:
	void InitializeTextPropertyFields( IPanelControlData* inPanelData,  IGraphicAttributeSuite* inGfxAttrSuite ); //for list/combobox/text fields
	void GetTextPropertyAttributes( IPanelControlData* inPanelData,  IGraphicStyleAttributeBossList* ioProperties );

	PMString GetTextControlValue( IPanelControlData*  inPanelData, WidgetID inWidget );

	WidgetID ValidateExportValue( IPanelControlData*  inPanelData, WidgetID inWidgetID, const PMString& inOrigExportValue );

	IGraphicStyleAttributeBossList* QueryDefaultAttributes();
};

#endif

