//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/utils/FormFieldUIUtils.h $
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
//  Comments: Miscellaneous useful functions that deal with form page items.
//  
//========================================================================================

#pragma once
#ifndef __FormFieldUIUtils_h__
#define __FormFieldUIUtils_h__

#include "BehaviorTypes.h"
#include "FormFieldTypes.h"

//------------------------------------------------------------
class UIDList;
class IFormFieldSuite;
class IAppearanceSuite;
class IPanelControlData;
class IDropDownListController;
class IGraphicStyleAttributeBossList;
class IGraphicAttributeSuite;
class IFormFieldUIFactory;
class IPMUnknown;
class ISelectionManager;
class IUIDData;

namespace FormFieldUIUtils
{
	IAppearanceSuite* QueryAppearanceSuite();
	IFormFieldSuite* QueryFormSuite();

	bool SelectionHasContentInAnyState();
	bool SelectionHasContentInActiveState();
	bool SelectionHasStates(ClassID inFormFieldType);
	bool SelectionIsForm(ClassID inFormFieldType);

	//returns factory for selection suite, or currently selected tool if selection suite doesn't know.
	IFormFieldUIFactory* QuerySelectionUIFactory(IFormFieldSuite* inFormSuite);

	void AdjustStylePresetMenu( const PMString& inStyleLibName, IPanelControlData* inPanelData,
				WidgetID inPopupWidget, bool16 supportsNone );
	void SelectStylePresetMenu( const PMString& inStyleLibName, IDropDownListController* inPopup,
				bool16 supportsNone );
	ActionEvent GetSelectedEvent(const IPMUnknown *relatedWidget);
	IUIDData *QueryActiveBehavior(void);
	void UpdateShowPreviewWidget( IPanelControlData* inPanelData, ISelectionManager* currentSelection );

	PMString GetBehaviorName(const UIDRef& behaviorRef);
}

//------------------------------------------------------------


class FormWidgetBlocker
{
public:
	FormWidgetBlocker();
	~FormWidgetBlocker();
	static bool Blocked();
};

//------------------------------------------------------------

#endif // __FormFieldUIUtils_h__

// End, FormFieldUIUtils.h.

