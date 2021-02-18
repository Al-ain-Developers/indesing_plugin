//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/PSImportUIID.h $
//  
//  Owner: David Berggren
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
//  Contains IDs used by the PSD Image Import plug-in
//  
//========================================================================================

#ifndef __PSDImportUIID__
#define __PSDImportUIID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kPSImportUIPrefix	RezLong(0x1b700)

// PluginID
#define kPSImportUIPluginName	"Photoshop Import UI"

DECLARE_PMID(kPlugInIDSpace, kPSImportUIPluginID, kPSImportUIPrefix + 1)

// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kPSDPrefsDialogBoss, kPSImportUIPrefix + 1)
DECLARE_PMID(kClassIDSpace, kPSDLayerListBoxBoss, kPSImportUIPrefix + 2)
DECLARE_PMID(kClassIDSpace, kPSDLayerListBoxElementBoss, kPSImportUIPrefix + 3)
DECLARE_PMID(kClassIDSpace, kPSDLayerListNameBoss, kPSImportUIPrefix + 4)
DECLARE_PMID(kClassIDSpace, kPSDLayerListEyeballBoss, kPSImportUIPrefix + 5)
DECLARE_PMID(kClassIDSpace, kPSDLayerTreeViewWidgetBoss, kPSImportUIPrefix + 6)
DECLARE_PMID(kClassIDSpace, kPSDLayerTreeNodeWidgetBoss, kPSImportUIPrefix + 7)
DECLARE_PMID(kClassIDSpace, kPSDChangeLayerDialogBoss, kPSImportUIPrefix + 8)
DECLARE_PMID(kClassIDSpace, kPSDLayerEyeDEHandlerBoss, kPSImportUIPrefix + 9)
DECLARE_PMID(kClassIDSpace, kPSDTreeNodeTextWidgetBoss, kPSImportUIPrefix + 10)

// <Interface ID>
// Interface IDs
DECLARE_PMID(kInterfaceIDSpace, IID_IPSIMPORTUIUTILS, kPSImportUIPrefix + 1)

// <Implementation ID>
// ImplementationIDs
DECLARE_PMID(kImplementationIDSpace, kPSDPrefsDialogControllerImpl, kPSImportUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kPSDPrefsPanelCreatorImpl, kPSImportUIPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kPSDLayerListElementViewImpl, kPSImportUIPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kPSDLayerListNameViewImpl, kPSImportUIPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kPSDLayerListEyeballEHImpl, kPSImportUIPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kPSDLayerListBoxControllerImpl, kPSImportUIPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kPSDLayerTreeViewAdapterImpl, kPSImportUIPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kPSDLayerTreeViewWidgetMgrImpl, kPSImportUIPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kPSDLayerEyeballObserverImpl, kPSImportUIPrefix + 9)
//DECLARE_PMID(kImplementationIDSpace, kPSDLayerTreeNodeTipImpl, kPSImportUIPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kPSDChangeLayerDialogControllerImpl, kPSImportUIPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kPSDLayerEyeDEHandlerImpl, kPSImportUIPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kPSDLayerEyeDDSourceImpl, kPSImportUIPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kPSDLayerEyeDDTargetImpl, kPSImportUIPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kPSDLayerEyeEvtHandlerImpl, kPSImportUIPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kPSDChangeLayerDialogObserverImpl, kPSImportUIPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kPSDPrefsDialogObserverImpl, kPSImportUIPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kPSImportUIUtilsImpl, kPSImportUIPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kPSDLayerPreviewDlgErrHandlerImpl, kPSImportUIPrefix + 19)
//DECLARE_PMID(kImplementationIDSpace, kPSDChangeLayerTipImpl, kPSImportUIPrefix + 20)


// <Widget ID>
// Widget IDs for Image Import Dialog
DECLARE_PMID(kWidgetIDSpace, kPSDPrefsDialogWidgetId, kPSImportUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kPSDLayerTreeViewWidgetID, kPSImportUIPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kPSDLayerEyeballWidgetID, kPSImportUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kLayerNodeWidgetID, kPSImportUIPrefix + 4)

DECLARE_PMID(kWidgetIDSpace, kShowLayersGroupWidgetId, kPSImportUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kShowLayers_GroupLabelWidgetId, kPSImportUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kUpdateLinkOpGroupWidgetId, kPSImportUIPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kUpLink_GroupLabelWidgetId, kPSImportUIPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kUpLink_UpdateLinkLabelWidgetId, kPSImportUIPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kUpdateLinkDropDownWidgetId, kPSImportUIPrefix + 10)

DECLARE_PMID(kWidgetIDSpace, kLayerFolderIconWidgetId, kPSImportUIPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kLayerCompLabelWidgetId, kPSImportUIPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kLayerCompDropDownWidgetId, kPSImportUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kLayerCompInfoGroupWID, kPSImportUIPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kLayerCompInfoTextWID, kPSImportUIPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kLayerCompInfoScrollWID, kPSImportUIPrefix + 16)

DECLARE_PMID(kWidgetIDSpace, kPSDChangeLayerDialogParentWidgetID, kPSImportUIPrefix + 17)
//DECLARE_PMID(kWidgetIDSpace, kSlowPreviewWarningIconWidgetID, kPSImportUIPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kPSDSelDialogTreeNodeStaticTextWidgetID, kPSImportUIPrefix + 19)

// <Service ID>
// Service IDs

#endif

