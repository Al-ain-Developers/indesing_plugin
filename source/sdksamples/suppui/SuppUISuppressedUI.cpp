//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/suppui/SuppUISuppressedUI.cpp $
//  
//  Owner: Adobe Developer Technologies
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
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----
#include "IControlView.h"
#include "IDragDropTarget.h"
#include "IWidgetParent.h"


// ----- Includes -----
#include "CPMUnknown.h"
#include "SuppUISuppressedUI.h"
#include "SuppressedUIXMLDefs.h"

// ----- Utility files -----

// ----- ID.h files -----
#include "SuppUIID.h"
#include "StylePanelID.h"
#include "TextFrameOptionsID.h"
#include "TextStylePanelID.h"
#include "widgetid.h"


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(SuppUISuppressedUI, kSuppUISuppressedUIImpl)

// Actual flags for menu states
bool16 SuppUISuppressedUI::gSuppressStyleChages = kFalse;
bool16 SuppUISuppressedUI::gSuppressFontAndSizeMenus = kFalse;
bool16 SuppUISuppressedUI::gSuppressOpenFileDialogControls = kFalse;
bool16 SuppUISuppressedUI::gSuppressParaStyleQuickApply = kFalse;

/* SuppUISuppressedUI Constructor
*/
SuppUISuppressedUI::SuppUISuppressedUI(IPMUnknown *boss) :
	CPMUnknown<ISuppressedUI>(boss)
{
}

/* SuppUISuppressedUI Destructor
*/
SuppUISuppressedUI::~SuppUISuppressedUI()
{
}

/* IsWidgetDisabled
*/
bool16	SuppUISuppressedUI::IsWidgetDisabled( const IControlView* widget ) const
{
	// Check to see if we are suppressing style changes
	if( gSuppressStyleChages )
	{
		// See if it's one of the widgets we want to suppress
		WidgetID widgetID = GetWidgetID(widget);
		switch( widgetID.Get() )
		{
		case kCharStyleIconWidgetID:
		case kParaStyleIconWidgetID:
		case kNewCharStyleButtonWidgetID:
		case kNewParaStyleButtonWidgetID:
		case kDeleteCharStyleButtonWidgetID:
		case kDeleteParaStyleButtonWidgetID:
		case kNewCharStyleGroupButtonWidgetID:
		case kNewParaStyleGroupButtonWidgetID:


			return kTrue;
		}
	}

	return kFalse;
}

/* IsWidgetHidden
*/
bool16	SuppUISuppressedUI::IsWidgetHidden( const IControlView* widget ) const
{
	// Check to see if we are suppressing style changes
	if( gSuppressStyleChages )
	{
		// See if it's one of the widgets we want to suppress
		WidgetID widgetID = GetWidgetID(widget);
		switch( widgetID.Get() )
		{
		case kPreviewButtonWidgetID:
		case kOKButtonWidgetID:
			{
				WidgetID parentWidgetID = GetParentWidgetID(widget);
				if( parentWidgetID == kStyleCharParentWidgetID || parentWidgetID == kStyleParaParentWidgetID
					|| parentWidgetID == kStyleGroupOptionsDialogBoss )
					return kTrue;
			}
		}
	}

	return kFalse;
}

/* IsDragDropDisabled
*/
bool16	SuppUISuppressedUI::IsDragDropDisabled( const IDragDropTarget* target, DataObjectIterator* data, const IDragDropSource* source ) const
{
	// Check to see if we are suppressing style changes
	if( gSuppressStyleChages )
	{
		// See if it's one of the widgets we want to suppress
		InterfacePtr<IControlView> widget(target, UseDefaultIID());
		
		WidgetID widgetID = GetWidgetID(widget);
		switch( widgetID.Get() )
		{
		case kNewCharStyleButtonWidgetID:
		case kNewParaStyleButtonWidgetID:
		case kDeleteCharStyleButtonWidgetID:
		case kDeleteParaStyleButtonWidgetID:
		case kNewCharStyleGroupButtonWidgetID:
		case kNewParaStyleGroupButtonWidgetID:

		case kParaStyleTreeViewWidgetID:
		case kParaStyleListParentWidgetId:
		case kCharStyleTreeViewWidgetID:
		case kCharStyleListParentWidgetId:

			return kTrue;
		}
	}

	return kFalse;
}

/* IsActionDisabled
*/
bool16	SuppUISuppressedUI::IsActionDisabled( ActionID action ) const
{	
	// Check to see if we are suppressing style changes
	if( gSuppressStyleChages )
	{
		// See if it's one of the actions we want to suppress
		switch (action.Get())
		{
			case kLoadParaStylesActionID:
			case kParaLoadAllStylesActionID:
			case kRedefineParaStyleActionID:
			case kNewParaStyleActionID:
			case kDeleteParaStyleActionID:
			case kParaStyleOptionsActionID:
			case kDuplicateParaStyleActionID:
			case kParaNewStyleGroupActionID:
			case kParaCreateStyleGroupActionID:
			case kParaCopyToStyleGroupActionID:
			case kContextMenuStyleOptionsActionID:
			case kContextMenuDuplicateStyleActionID:
			case kContextMenuDeleteStyleActionID:
			case kContextMenuRedefineStyleActionID:
			case kContextMenuDuplicateStyleGroupActionID:
			case kContextMenuDeleteStyleGroupActionID:
			case kContextMenuCopyToStyleGroupActionID:
			case kContextMenuCreateStyleGroupActionID:
			case kContextMenuCreateStyleInGroupActionID:
			
				return kTrue;

			break;

		}
	}

	return kFalse;
}

/* IsActionHidden
*/
bool16	SuppUISuppressedUI::IsActionHidden( ActionID action ) const
{
	// Check to see if we are suppressing style changes
	if( gSuppressStyleChages )
	{
		// See if it's one of the actions we want to suppress
		switch (action.Get())
		{
			case kLoadCharStylesActionID:
			case kCharLoadAllStylesActionID:
			case kRedefineCharStyleActionID:
			case kNewCharStyleActionID:
			case kDeleteCharStyleActionID:
			case kCharStyleOptionsActionID:
			case kDuplicateCharStyleActionID:
			case kCharNewStyleGroupActionID:
			case kCharCreateStyleGroupActionID:
			case kCharCopyToStyleGroupActionID:
			
				return kTrue;

			break;

		}
	}

	return kFalse;
}

/* IsSubMenuDisabled
*/
bool16	SuppUISuppressedUI::IsSubMenuDisabled( const PMString& untranslatedSubMenuName ) const
{
	if( gSuppressFontAndSizeMenus )
	{
		if( untranslatedSubMenuName.IsEqual("Main:&Type:&Font") )
			return kTrue;
	}
	return kFalse;
}

/* IsSubMenuHidden
*/
bool16	SuppUISuppressedUI::IsSubMenuHidden( const PMString& untranslatedSubMenuName ) const
{
	if( gSuppressFontAndSizeMenus )
	{
		if( untranslatedSubMenuName.IsEqual("Main:&Type:Size") )
			return kTrue;
	}
	return kFalse;
}

/* IsPlatformDialogControlSuppressed
*/
bool16	SuppUISuppressedUI::IsPlatformDialogControlSuppressed( const PMString& platformDialogControlIdentifier ) const
{
	if ( gSuppressOpenFileDialogControls ) 
	{
		// Look for kAllOpenDocDialogCustomControlsValue to suppress all custom controls.
		// Look for kAdobeFileDialogOpenDialogButtonValue to suppress the Adobe dialog 
		// and the "Use Adobe Dialog" button.
		if(platformDialogControlIdentifier.IsEqual(SuppressedUIXMLDefs::kAdobeFileDialogOpenDialogButtonValue )||
		   platformDialogControlIdentifier.IsEqual(SuppressedUIXMLDefs::kAllOpenDocDialogCustomControlsValue ))
		{
			return kTrue;
		}
	}

	return kFalse;
}

/* Reset
*/
void	SuppUISuppressedUI::Reset(  ) 
{
	// The Reset() method is useful if you cache the suppressed items.
	// This is not useful when the widgets you're supressing are  hardcoded.
	// See the "Working With The ISuppressedUI API" section in the Suppressed UI
	// technote (#10102) for more information.
}

/* GetWidgetID
*/
WidgetID SuppUISuppressedUI::GetWidgetID(const IControlView* widget) const
{
	if( widget )
	{
		return widget->GetWidgetID();
	}

	return kInvalidWidgetID;
}

/* GetParentWidgetID
*/
WidgetID SuppUISuppressedUI::GetParentWidgetID(const IControlView* widget) const
{
	InterfacePtr<IWidgetParent> parentHolder(widget, IID_IWIDGETPARENT);
	if(parentHolder)
	{
		InterfacePtr<IControlView> parentView((IControlView*)parentHolder->QueryParentFor(IID_ICONTROLVIEW));
		if( parentView  )
		{
			return parentView->GetWidgetID();
		}
	}

	return kInvalidWidgetID;
}

