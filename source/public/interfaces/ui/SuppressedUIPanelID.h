//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/SuppressedUIPanelID.h $
//  
//  Owner: Matt Joss
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
//  Contains IDs used by the Sample Code Test Plugin
//  
//========================================================================================

#ifndef __SuppressedUIPanelID__
#define __SuppressedUIPanelID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kSuppressedUIPanelPrefix					RezLong(0x1dd00)  

//----------------------------------------------------------------------------------------
// Plug-in identifier
//----------------------------------------------------------------------------------------

#define SuppressedUIPanelPluginName 	"SuppressedUIPanel"
DECLARE_PMID(kPlugInIDSpace, 		kSuppressedUIPanelPluginID, 				kSuppressedUIPanelPrefix + 1)

//----------------------------------------------------------------------------------------
// Class identifiers
//----------------------------------------------------------------------------------------
DECLARE_PMID(kClassIDSpace,		kSuppressedUIPanelPanelBoss,					kSuppressedUIPanelPrefix + 0)
DECLARE_PMID(kClassIDSpace,		kSuppressedUIPanelMenuTreeWidgetBoss,			kSuppressedUIPanelPrefix + 1)
DECLARE_PMID(kClassIDSpace,		kSuppressedUIPanelMenuFilterBoss,				kSuppressedUIPanelPrefix + 2)
DECLARE_PMID(kClassIDSpace,		kSuppressedUIPanelActionComponentBoss,			kSuppressedUIPanelPrefix + 3)
DECLARE_PMID(kClassIDSpace,		kSuppressedUIPanelDataBoss,						kSuppressedUIPanelPrefix + 4)
DECLARE_PMID(kClassIDSpace,		kTriStateEyeballCheckboxBoss,					kSuppressedUIPanelPrefix + 5)
DECLARE_PMID(kClassIDSpace,		kSuppressWidgetsPanelBoss,						kSuppressedUIPanelPrefix + 6)
DECLARE_PMID(kClassIDSpace,		kWhipWidgetBoss,								kSuppressedUIPanelPrefix + 7)
DECLARE_PMID(kClassIDSpace,		kWidgetTargetedMsg,								kSuppressedUIPanelPrefix + 8)
DECLARE_PMID(kClassIDSpace,		kSuppressedItemsTreeWidgetBoss,					kSuppressedUIPanelPrefix + 9)
DECLARE_PMID(kClassIDSpace,		kSuppressedUIWithXMLFileBoss,					kSuppressedUIPanelPrefix + 10)
//dd DECLARE_PMID(kClassIDSpace,		kDragDropFlavorDropDownListWidgetBoss,			kSuppressedUIPanelPrefix + 11)
DECLARE_PMID(kClassIDSpace,		kSuppressedUIInterceptDialogEHBoss,				kSuppressedUIPanelPrefix + 12)
DECLARE_PMID(kClassIDSpace,		kSuppressedUIPanelActionFilterBoss,				kSuppressedUIPanelPrefix + 13)
DECLARE_PMID(kClassIDSpace,		kSuppressedUIPanelStatupServiceBoss,			kSuppressedUIPanelPrefix + 14)
DECLARE_PMID(kClassIDSpace,		kSuppressedUISignalEndActionsCmdBoss,			kSuppressedUIPanelPrefix + 15)

//----------------------------------------------------------------------------------------
// Interface identifiers
//----------------------------------------------------------------------------------------
DECLARE_PMID(kInterfaceIDSpace,		IID_ISUPPRESSEDUIPANELDATA,					kSuppressedUIPanelPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace,		IID_ISUPPRESSEDUIPANELEVENTHANDLER,			kSuppressedUIPanelPrefix + 1)
//DECLARE_PMID(kInterfaceIDSpace,	IID_IMYFANCYNEWINTERFACE,					kSuppressedUIPanelPrefix + 2)
//DECLARE_PMID(kInterfaceIDSpace,	IID_IMYFANCYNEWINTERFACE,					kSuppressedUIPanelPrefix + 3)
//DECLARE_PMID(kInterfaceIDSpace,	IID_IMYFANCYNEWINTERFACE,					kSuppressedUIPanelPrefix + 4)
//DECLARE_PMID(kInterfaceIDSpace,	IID_IMYFANCYNEWINTERFACE,					kSuppressedUIPanelPrefix + 5)
//DECLARE_PMID(kInterfaceIDSpace,	IID_IMYFANCYNEWINTERFACE					kSuppressedUIPanelPrefix + 6)
//DECLARE_PMID(kInterfaceIDSpace,	IID_IMYFANCYNEWINTERFACE					kSuppressedUIPanelPrefix + 7)
//DECLARE_PMID(kInterfaceIDSpace,	IID_IMYFANCYNEWINTERFACE					kSuppressedUIPanelPrefix + 8)
//DECLARE_PMID(kInterfaceIDSpace,	IID_IMYFANCYNEWINTERFACE					kSuppressedUIPanelPrefix + 9)

//----------------------------------------------------------------------------------------
// Implementation identifiers
//----------------------------------------------------------------------------------------
DECLARE_PMID(kImplementationIDSpace,	kSuppressedUIPanelMenuFilterImpl,		kSuppressedUIPanelPrefix + 0)
DECLARE_PMID(kImplementationIDSpace,	kSuppressedUIPanelMenuTreeAdapterImpl,	kSuppressedUIPanelPrefix + 1)
DECLARE_PMID(kImplementationIDSpace,	kSuppressedUIPanelActionComponentImpl,	kSuppressedUIPanelPrefix + 2)
DECLARE_PMID(kImplementationIDSpace,	kSuppressedUIPanelDataImpl,				kSuppressedUIPanelPrefix + 3)
DECLARE_PMID(kImplementationIDSpace,	kMenuTreeViewWidgetMgrImpl,				kSuppressedUIPanelPrefix + 4)
DECLARE_PMID(kImplementationIDSpace,	kTriStateEyeballCheckboxEventHandlerImpl,kSuppressedUIPanelPrefix + 5)
DECLARE_PMID(kImplementationIDSpace,	kSuppressedUIPanelEyeballObserverImpl,	kSuppressedUIPanelPrefix + 6)
DECLARE_PMID(kImplementationIDSpace,	kSuppressWidgetsPanelObserverImpl,		kSuppressedUIPanelPrefix + 7)
DECLARE_PMID(kImplementationIDSpace,	kWhipEventHandlerImpl,					kSuppressedUIPanelPrefix + 8)
DECLARE_PMID(kImplementationIDSpace,	kSuppressUIComponentsObserverImpl,		kSuppressedUIPanelPrefix + 9)
DECLARE_PMID(kImplementationIDSpace,	kSuppressedItemsTreeAdapterImpl,		kSuppressedUIPanelPrefix + 10)
DECLARE_PMID(kImplementationIDSpace,	kSuppressedItemsTreeWidgetMgrImpl,		kSuppressedUIPanelPrefix + 11)
DECLARE_PMID(kImplementationIDSpace,	kTriStateEyeballViewImpl,				kSuppressedUIPanelPrefix + 12)
//dd DECLARE_PMID(kImplementationIDSpace,	kAllFlavorsDragDropTargetImpl,			kSuppressedUIPanelPrefix + 13)
DECLARE_PMID(kImplementationIDSpace,	kSuppressedUIInterceptDialogEHImpl,		kSuppressedUIPanelPrefix + 14)
DECLARE_PMID(kImplementationIDSpace,	kSuppressedUIPanelActionFilterImpl,		kSuppressedUIPanelPrefix + 15)
DECLARE_PMID(kImplementationIDSpace,	kSuppressedUISignalEndActionsCmdImpl,	kSuppressedUIPanelPrefix + 16)
DECLARE_PMID(kImplementationIDSpace,	kSuppressedUIStartupShutdownImpl,		kSuppressedUIPanelPrefix + 17)

//----------------------------------------------------------------------------------------
// Widget identifiers
//----------------------------------------------------------------------------------------
DECLARE_PMID(kWidgetIDSpace,	kSuppressedUIPanelPanelWidgetID,				kSuppressedUIPanelPrefix + 0)
DECLARE_PMID(kWidgetIDSpace,	kSuppressedUIPanelMenuTreeWidgetID,				kSuppressedUIPanelPrefix + 1)
DECLARE_PMID(kWidgetIDSpace,	kSuppressedUIPanelNodeWidgetID,					kSuppressedUIPanelPrefix + 2)
DECLARE_PMID(kWidgetIDSpace,	kTriStateEyeballWidgetID,						kSuppressedUIPanelPrefix + 3)
DECLARE_PMID(kWidgetIDSpace,	kSuppressedWidgetPopupWidgetId,					kSuppressedUIPanelPrefix + 4)
DECLARE_PMID(kWidgetIDSpace,	kSuppressedAncestorWidgetPopupWidgetId,			kSuppressedUIPanelPrefix + 5)
//dd DECLARE_PMID(kWidgetIDSpace,	kSuppressedFlavorPopupWidgetId,					kSuppressedUIPanelPrefix + 6)
DECLARE_PMID(kWidgetIDSpace,	kHideButton_WidgetID,							kSuppressedUIPanelPrefix + 7)
DECLARE_PMID(kWidgetIDSpace,	kDisableButton_WidgetID,						kSuppressedUIPanelPrefix + 8)
DECLARE_PMID(kWidgetIDSpace,	kDisableDropButton_WidgetID,					kSuppressedUIPanelPrefix + 9)
DECLARE_PMID(kWidgetIDSpace,	kWhipWidgetID,									kSuppressedUIPanelPrefix + 10)
DECLARE_PMID(kWidgetIDSpace,	kSuppressWidgetsPanelWidgetID,					kSuppressedUIPanelPrefix + 11)
DECLARE_PMID(kWidgetIDSpace,	kMenuOrWidgetPanelGroupPanelWidget,				kSuppressedUIPanelPrefix + 12)
DECLARE_PMID(kWidgetIDSpace,	kSuppressedItemsTreeWidgetWidgetID,				kSuppressedUIPanelPrefix + 13)
DECLARE_PMID(kWidgetIDSpace,	kChoosePanelPopupWidgetId,						kSuppressedUIPanelPrefix + 14)
DECLARE_PMID(kWidgetIDSpace,	kDeleteSuppressedWidgetsWidgetsID,				kSuppressedUIPanelPrefix + 15)
DECLARE_PMID(kWidgetIDSpace,	kTargetWidgetStaticTextWidgetId,				kSuppressedUIPanelPrefix + 16)
DECLARE_PMID(kWidgetIDSpace,	kQualifyingWidgetStaticTextWidgetId,			kSuppressedUIPanelPrefix + 17)
//DECLARE_PMID(kWidgetIDSpace,	kMyFancyNewWidgetID,				kSuppressedUIPanelPrefix + 18)
//DECLARE_PMID(kWidgetIDSpace,	kMyFancyNewWidgetID,				kSuppressedUIPanelPrefix + 19)
//DECLARE_PMID(kWidgetIDSpace,	kMyFancyNewWidgetID,				kSuppressedUIPanelPrefix + 20)
//DECLARE_PMID(kWidgetIDSpace,	kMyFancyNewWidgetID,				kSuppressedUIPanelPrefix + 21)
//DECLARE_PMID(kWidgetIDSpace,	kMyFancyNewWidgetID,				kSuppressedUIPanelPrefix + 22)

//----------------------------------------------------------------------------------------
// Action identifiers
//----------------------------------------------------------------------------------------
DECLARE_PMID(kActionIDSpace,	kSuppressedUIPanelActionID,						kSuppressedUIPanelPrefix + 0)
DECLARE_PMID(kActionIDSpace,	kSaveSuppressedUIFileActionID,					kSuppressedUIPanelPrefix + 1)
//DECLARE_PMID(kActionIDSpace,	kMyFancyNewActionID,							kSuppressedUIPanelPrefix + 2)
//DECLARE_PMID(kActionIDSpace,	kMyFancyNewActionID,							kSuppressedUIPanelPrefix + 3)
//DECLARE_PMID(kActionIDSpace,	kMyFancyNewActionID,							kSuppressedUIPanelPrefix + 4)
//DECLARE_PMID(kActionIDSpace,	kMyFancyNewActionID,							kSuppressedUIPanelPrefix + 5)
//DECLARE_PMID(kActionIDSpace,	kMyFancyNewActionID,							kSuppressedUIPanelPrefix + 6)
//DECLARE_PMID(kActionIDSpace,	kMyFancyNewActionID,							kSuppressedUIPanelPrefix + 7)
//DECLARE_PMID(kActionIDSpace,	kMyFancyNewActionID,							kSuppressedUIPanelPrefix + 8)
//DECLARE_PMID(kActionIDSpace,	kMyFancyNewActionID,							kSuppressedUIPanelPrefix + 9)


// <Ignore>
//========================================================================================
// ----- Tree Node ID types -----
//========================================================================================
#define kMenuNodeID					kSuppressedUIPanelPrefix + 1

// <Error ID>
//----------------------------------------------------------------------------------------
// Error Codes
//----------------------------------------------------------------------------------------

// -- SampleListTreeView --
//DECLARE_PMID(kErrorIDSpace,	kMyFancyNewError,								kSuppressedUIPanelPrefix + 0)

// -- SampleOutlineTreeView --
//DECLARE_PMID(kActionIDSpace,	kMyFancyNewError,								kSampleOutlineTreeViewPrefix + 0)



#endif // __SuppressedUIPanelID__
