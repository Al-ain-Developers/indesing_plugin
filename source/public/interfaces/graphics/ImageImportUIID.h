//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ImageImportUIID.h $
//  
//  Owner: Yeming Liu
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
//  Contains IDs used by the ImageImportUI plug-in
//  
//========================================================================================

#ifndef __ImageImportUIID__
#define __ImageImportUIID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kImageImportUIPrefix	 RezLong(0x9400)

// <Start IDC>
// PluginID
#define kImageImportUIPluginName		"Image Import UI"
DECLARE_PMID(kPlugInIDSpace, kImageImportUIPluginID, kImageImportUIPrefix + 1)

// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kImportSelectableDialogBoss, kImageImportUIPrefix + 1)
DECLARE_PMID(kClassIDSpace, kImageSettingsDialogBoss, kImageImportUIPrefix + 3)
DECLARE_PMID(kClassIDSpace, kImageImportUIDialogServiceBoss, kImageImportUIPrefix + 4)
DECLARE_PMID(kClassIDSpace, kImageObjectMenuActionBoss, kImageImportUIPrefix + 5)
//DECLARE_PMID(kClassIDSpace, kChangeGraphicLayerDialogBoss, kImageImportUIPrefix + 6)
DECLARE_PMID(kClassIDSpace, kChangeGraphicLayerOnOffWidgetBoss, kImageImportUIPrefix + 7)
DECLARE_PMID(kClassIDSpace, kImagePreviewWidgetBoss, kImageImportUIPrefix + 8)
DECLARE_PMID(kClassIDSpace, kImageTestMenuBoss, kImageImportUIPrefix + 9)
DECLARE_PMID(kClassIDSpace, kSlowPreviewWarningIconWidgetBoss, kImageImportUIPrefix + 10)


// <Interface ID>
// Interface IDs


// <Implementation ID>
// ImplementationIDs
DECLARE_PMID(kImplementationIDSpace, kImportSelDialogCreator, kImageImportUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kImageSettingsPanelController, kImageImportUIPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kImageSettingsPanelCreator, kImageImportUIPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kImageImportUIDialogServiceImpl,	kImageImportUIPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kImageImportUIDialogImpl,	kImageImportUIPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kImageObjectMenuActionImpl,	kImageImportUIPrefix + 8)
//DECLARE_PMID(kImplementationIDSpace, kChangeGraphicLayerDialogControllerImpl,	kImageImportUIPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kImportSelDialogControllerImpl,	kImageImportUIPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kImportSelDialogObserverImpl,	kImageImportUIPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kImagePreviewViewImpl,	kImageImportUIPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kImageSettingsPanelObserverImpl,	kImageImportUIPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kImageTestMenu, kImageImportUIPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kSlowPreviewWarningIconTipImpl, kImageImportUIPrefix + 15)


// <Widget ID>
// Widget IDs for Image Import Dialog
DECLARE_PMID(kWidgetIDSpace, kImportSelDialogId, kImageImportUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kImageSettingsDialogWidgetId, kImageImportUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kImageDisplayResEditBoxId, kImageImportUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kImageClippingPathCheckBoxWidgetId, kImageImportUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kResolutionTextWidgetId, kImageImportUIPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kGroupPanelTextWidgetID, kImageImportUIPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kDPITextWidgetId, kImageImportUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kAlphaLabelWidgetID, kImageImportUIPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kAlphaPopupWidgetID, kImageImportUIPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kGraphicLayerDialogParentWidgetID, kImageImportUIPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kChangeLayerOnCheckboxWidgetID, kImageImportUIPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kImagePreviewEnableDisableWidgetId, kImageImportUIPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kImagePlace_PreviewWidgetId, kImageImportUIPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kSlowPreviewWarningIconWidgetID, kImageImportUIPrefix + 20)

// <Action ID>
// Action IDs for Image Import Dialog
DECLARE_PMID(kActionIDSpace, kImageObjectLayerActionID, kImageImportUIPrefix + 1)

// <Service ID>
// Service IDs
DECLARE_PMID(kServiceIDSpace, kImportSelDialogService, kImageImportUIPrefix + 1)

#endif // __ImageImportUIID__

