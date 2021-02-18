//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/InCopyWorkflowUIID.h $
//  
//  Owner: Chris Parrish
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

#ifndef __InCopyWorkflowUIID__
#define __InCopyWorkflowUIID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kInCopyWorkflowUIPrefix			RezLong(0x1d800)

//----------------------------------------------------------------------------------------
// Plug-in identifier
//----------------------------------------------------------------------------------------

#define kInCopyWorkflowUIPluginName 	"InCopyWorkflowUI"

DECLARE_PMID(kPlugInIDSpace,		kInCopyWorkflowUIPluginID,				kInCopyWorkflowUIPrefix + 0)

//----------------------------------------------------------------------------------------
// Class identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kClassIDSpace,			kICFontSpecStaticTextWidgetBoss, 		kInCopyWorkflowUIPrefix + 0)
DECLARE_PMID(kClassIDSpace,			kMapMissingDropdownListWidgetBoss, 		kInCopyWorkflowUIPrefix + 1)
DECLARE_PMID(kClassIDSpace,			kMapMissingListWidgetBoss,				kInCopyWorkflowUIPrefix + 2)
DECLARE_PMID(kClassIDSpace,			kMapMissingListItemWidgetBoss,			kInCopyWorkflowUIPrefix + 3)
DECLARE_PMID(kClassIDSpace,			kMapMissingStyleDialogBoss,				kInCopyWorkflowUIPrefix + 4)
//gap
DECLARE_PMID(kClassIDSpace,			kMapMissingSwatchDialogBoss,			kInCopyWorkflowUIPrefix + 6)
DECLARE_PMID(kClassIDSpace,			kInCopyWorkflowTestMenuComponentBoss,   kInCopyWorkflowUIPrefix + 7)

//----------------------------------------------------------------------------------------
// Interface identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kInterfaceIDSpace,		IID_IMISSINGIMPORTDATA,					kInCopyWorkflowUIPrefix + 0)

//----------------------------------------------------------------------------------------
// Implementation identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kImplementationIDSpace,	kMMPanelTreeViewAdapterImpl, 		kInCopyWorkflowUIPrefix + 0)
DECLARE_PMID(kImplementationIDSpace,	kMapMissingViewWidgetMgrImpl,		kInCopyWorkflowUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace,	kMapMissingNodeObserverImpl,		kInCopyWorkflowUIPrefix + 2)
DECLARE_PMID(kImplementationIDSpace,	kMapMissingStyleControllerImpl,		kInCopyWorkflowUIPrefix + 3)
DECLARE_PMID(kImplementationIDSpace,	kMissingSwatchDataImpl,				kInCopyWorkflowUIPrefix + 4)
DECLARE_PMID(kImplementationIDSpace,	kICMappingDialogObserverImpl,		kInCopyWorkflowUIPrefix + 5)
DECLARE_PMID(kImplementationIDSpace,	kMissingStyleDataImpl, 				kInCopyWorkflowUIPrefix + 6)
//gap
DECLARE_PMID(kImplementationIDSpace,	kMapMissingUtilsImpl, 				kInCopyWorkflowUIPrefix + 8)
DECLARE_PMID(kImplementationIDSpace,	kInCopyWorkflowActionImpl,			kInCopyWorkflowUIPrefix + 9)

//----------------------------------------------------------------------------------------
// Widget identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kWidgetIDSpace,	kMapMissingStyleDialogWidgetID,				kInCopyWorkflowUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace,	kMapMissingSwatchDialogWidgetID,			kInCopyWorkflowUIPrefix + 2)
DECLARE_PMID(kWidgetIDSpace,	kNodeDropDownWidgetID,						kInCopyWorkflowUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace,	kNodeNameWidgetID,							kInCopyWorkflowUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace,	kMapMissingListItemWidgetID,				kInCopyWorkflowUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace,	kMapMissingStylePanelID,					kInCopyWorkflowUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace,	kMapMissingListWidgetID,					kInCopyWorkflowUIPrefix + 7)
DECLARE_PMID(kWidgetIDSpace,	kMapMissingListPanelWidgetID,				kInCopyWorkflowUIPrefix + 8)
DECLARE_PMID(kWidgetIDSpace,	kMissingStyleTextWidgetID,					kInCopyWorkflowUIPrefix + 9)
DECLARE_PMID(kWidgetIDSpace,	kAvailableStylesTextWidgetID,				kInCopyWorkflowUIPrefix + 10)
//gap
DECLARE_PMID(kWidgetIDSpace,	kTagsColumnOuterPanelWidgetID,				kInCopyWorkflowUIPrefix + 19)
DECLARE_PMID(kWidgetIDSpace,	kTagsInnerPanelWidgetID,					kInCopyWorkflowUIPrefix + 20)
DECLARE_PMID(kWidgetIDSpace,	kStylesColumnOuterPanelWidgetID,			kInCopyWorkflowUIPrefix + 21)
DECLARE_PMID(kWidgetIDSpace,	kStylesInnerPanelWidgetID,					kInCopyWorkflowUIPrefix + 22)

#endif // __InCopyWorkflowUIID__
