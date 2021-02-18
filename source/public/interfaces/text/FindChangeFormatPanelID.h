//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/FindChangeFormatPanelID.h $
//  
//  Owner: Bernd Paradies
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

#ifndef __FindChangeFormatPanelID__
#define __FindChangeFormatPanelID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

//----------------------------------------------------------------------------------------
// Resource IDs
//----------------------------------------------------------------------------------------

// Prefix
#define kFindChangeFormatPanelPrefix				RezLong( 0x9000 ) 	/* doublecheck with AdobePrefix.h */
// 0x9000 Hex == 36864 Dec

// <Start IDC>
// PluginID
#define kFindChangeFormatPanelPluginName 			"Find Change Format Panel"
DECLARE_PMID(kPlugInIDSpace, kFindChangeFormatPanelPluginID, kFindChangeFormatPanelPrefix + 1)

// Resource ID of Panel Windows
//#define kFindChangeFormatPanelRsrcID				1000	// 36864 
//#define kFindChangeFormatDialogRsrcID 				1100	// 36865 
//#define kFindChangeFormatCoreDialogRsrcID 			1200	// 36866 
//#define kFindChangeFormatParaGeneralRsrcID 			1300	// 36867  
//#define kFindChangeFormatCharGeneralRsrcID 			1400	// 36868  
//#define kFindChangeFormatParaDialogRsrcID 			1500	// 36869  
//#define kFindChangeFormatParaCoreDialogRsrcID 		1600	// 36871 
//#define kFindChangeFormatCharCoreDialogRsrcID 		1700	// 36872 

#define kFindChangeFormatPanelStringsRsrcID			2000
#define kFindChangeFormatPanelStringsNoTransRsrcID			2100

//#define kFindChangeFormatPanelSelRsrcID					3000	// 36864 
//#define kFindChangeFormatDialogSelRsrcID 				3100	// 36865 
//#define kFindChangeFormatCoreDialogSelRsrcID 			3200	// 36866 
//#define kFindChangeFormatParaGeneralSelRsrcID 			3400	// 36867  
//#define kFindChangeFormatCharGeneralSelRsrcID 			3500	// 36868  
//#define kFindChangeFormatParaDialogSelRsrcID 			3600	// 36869  
//#define kFindChangeFormatParaCoreDialogSelRsrcID 		3700	// 36871 
//#define kFindChangeFormatCharCoreDialogSelRsrcID 		3800	// 36872 

//#define kFindChangeFormatSelectableRsrcID				3900


#define kFindFormatPanelRsrcID					4000	
#define kFindFormatDialogRsrcID 				4100	 
#define kFindFormatCoreDialogRsrcID 			4200	 
#define kFindFormatParaGeneralRsrcID 			4300	  
#define kFindFormatCharGeneralRsrcID 			4400	  
#define kFindFormatParaDialogRsrcID 			4500	  
#define kFindFormatParaCoreDialogRsrcID 		4600	 
#define kFindFormatCharCoreDialogRsrcID 		4700	 

#define kChangeFormatPanelRsrcID				5000	
#define kChangeFormatDialogRsrcID 				5100	
#define kChangeFormatCoreDialogRsrcID 			5200	
#define kChangeFormatParaGeneralRsrcID 			5300	
#define kChangeFormatCharGeneralRsrcID 			5400	
#define kChangeFormatParaDialogRsrcID 			5500	 
#define kChangeFormatParaCoreDialogRsrcID 		5600	 
#define kChangeFormatCharCoreDialogRsrcID 		5700	

#define kFindFormatDialogSelRsrcID 				5800	 
#define kFindFormatCoreDialogSelRsrcID 			5900	
#define kFindFormatParaGeneralSelRsrcID 		6000	 
#define kFindFormatCharGeneralSelRsrcID 		6100	  
#define kFindFormatParaDialogSelRsrcID 			6200	  
#define kFindFormatParaCoreDialogSelRsrcID 		6300	 
#define kFindFormatCharCoreDialogSelRsrcID 		6400	 

#define kFindFormatSelectableRsrcID				6500

#define kChangeFormatDialogSelRsrcID 				6600	 
#define kChangeFormatCoreDialogSelRsrcID 			6700	 
#define kChangeFormatParaGeneralSelRsrcID 			6800	 
#define kChangeFormatCharGeneralSelRsrcID 			6900	  
#define kChangeFormatParaDialogSelRsrcID 			7000	 
#define kChangeFormatParaCoreDialogSelRsrcID 		7100	 
#define kChangeFormatCharCoreDialogSelRsrcID 		7200	

#define kChangeFormatSelectableRsrcID				7300
#define kChangeFormatXMLRsrcID						7400
#define kChangeFormatXMLSelRsrcID					7500


#define kObjectFindFormatSelectableDialogRsrcID			7600
#define kObjectFindFormatDialogPanelOrderingRsrcID		7700
#define kObjectFindFormatGeneralRsrcID					7800
#define kObjectFindFormatGeneralCreatorRsrcID			7900

#define kObjectChangeFormatSelectableDialogRsrcID		8000
#define kObjectChangeFormatDialogPanelOrderingRsrcID	8100
#define kObjectChangeFormatGeneralRsrcID				8200
#define kObjectChangeFormatGeneralCreatorRsrcID			8300

#define kFCObjStylesSelDialogTreeNodeRsrcID				8400
#define kFCObjStylesSelDialogTreeNodeTreeStyle			8500

#define kFindFormatConditionRsrcID						8600
#define kFindFormatConditionSelRsrcID					8700
#define kChangeFormatConditionRsrcID					8800
#define kChangeFormatConditionSelRsrcID					8900
#define kFCConditionListElementRsrcID					9000
#define kFCAnyConditionListElementRsrcID				9100
#define kFCUnconditionalListElementRsrcID				9200

// <Class ID>
//----------------------------------------------------------------------------------------
// Boss IDs
//----------------------------------------------------------------------------------------

// Panel Bosses: 0 to 9
//DECLARE_PMID(kClassIDSpace, kFindChangeFormatPanelRegisterBoss, kFindChangeFormatPanelPrefix + 1)
//DECLARE_PMID(kClassIDSpace, kFindChangeFormatDialogBoss, kFindChangeFormatPanelPrefix + 2)	// starts the dialog
//DECLARE_PMID(kClassIDSpace, kFindChangeFormatParaGeneralHookBoss, kFindChangeFormatPanelPrefix + 4)	// hooks the General Options Dialog into the FindChangeFormatDialog and the StyleDialog
//DECLARE_PMID(kClassIDSpace, kFindChangeFormatCharGeneralHookBoss, kFindChangeFormatPanelPrefix + 5)	// hooks the General Options Dialog into the FindChangeFormatDialog and the StyleDialog
//DECLARE_PMID(kClassIDSpace, kFindChangeFormatParaDialogBoss, kFindChangeFormatPanelPrefix + 8)
//DECLARE_PMID(kClassIDSpace, kFindChangeFormatSelectableDialogBoss, kFindChangeFormatPanelPrefix + 10)
//gap
//DECLARE_PMID(kClassIDSpace, kFindChangeDlgControllerBoss, kFindChangeFormatPanelPrefix + 12)
DECLARE_PMID(kClassIDSpace, kFindFormatParaDialogBoss, kFindChangeFormatPanelPrefix + 13)
DECLARE_PMID(kClassIDSpace, kChangeFormatParaDialogboss, kFindChangeFormatPanelPrefix + 14)
DECLARE_PMID(kClassIDSpace, kFindFormatSelectableDialogBoss, kFindChangeFormatPanelPrefix + 15)
DECLARE_PMID(kClassIDSpace, kChangeFormatSelectableDialogBoss, kFindChangeFormatPanelPrefix + 16)
DECLARE_PMID(kClassIDSpace, kFindFormatDlgControllerBoss, kFindChangeFormatPanelPrefix + 17)
DECLARE_PMID(kClassIDSpace, kChangeFormatDlgControllerBoss, kFindChangeFormatPanelPrefix + 18)
DECLARE_PMID(kClassIDSpace, kFindFormatParaGeneralPanelBoss, kFindChangeFormatPanelPrefix + 19)
DECLARE_PMID(kClassIDSpace, kChangeFormatParaGeneralPanelBoss, kFindChangeFormatPanelPrefix + 20)
DECLARE_PMID(kClassIDSpace, kFindTextSelectableParaDialogBoss, kFindChangeFormatPanelPrefix + 21)
DECLARE_PMID(kClassIDSpace, kChangeTextSelectableParaDialogBoss, kFindChangeFormatPanelPrefix + 22)
DECLARE_PMID(kClassIDSpace, kFindParaStyleObserverBoss, kFindChangeFormatPanelPrefix + 23)
DECLARE_PMID(kClassIDSpace, kFindCharStyleObserverBoss, kFindChangeFormatPanelPrefix + 24)
DECLARE_PMID(kClassIDSpace, kChangeParaStyleObserverBoss, kFindChangeFormatPanelPrefix + 25)
DECLARE_PMID(kClassIDSpace, kChangeCharStyleObserverBoss, kFindChangeFormatPanelPrefix + 26)
DECLARE_PMID(kClassIDSpace, kChangeFormatParaDialogBoss, kFindChangeFormatPanelPrefix + 27)
DECLARE_PMID(kClassIDSpace, kChangeFormatXMLPanelBoss, kFindChangeFormatPanelPrefix + 28)
DECLARE_PMID(kClassIDSpace, kChangeTagObserverBoss, kFindChangeFormatPanelPrefix + 29)
DECLARE_PMID(kClassIDSpace, kObjectFindFormatSelectableDialogBoss, kFindChangeFormatPanelPrefix + 30)
DECLARE_PMID(kClassIDSpace, kObjectChangeFormatSelectableDialogBoss, kFindChangeFormatPanelPrefix + 31)
DECLARE_PMID(kClassIDSpace, kObjectFindFormatDialogGeneralPanelBoss, kFindChangeFormatPanelPrefix + 32)
DECLARE_PMID(kClassIDSpace, kObjectChangeFormatDialogGeneralPanelBoss, kFindChangeFormatPanelPrefix + 33)
DECLARE_PMID(kClassIDSpace, kFindObjectStyleObserverBoss, kFindChangeFormatPanelPrefix + 34)
DECLARE_PMID(kClassIDSpace, kChangeObjectStyleObserverBoss, kFindChangeFormatPanelPrefix + 35)
DECLARE_PMID(kClassIDSpace, kFCObjStylesSelDialogTreeViewWidgetBoss, kFindChangeFormatPanelPrefix + 36)
DECLARE_PMID(kClassIDSpace, kFCObjStylesSelDialogTreeNodeWidgetBoss, kFindChangeFormatPanelPrefix + 37)
DECLARE_PMID(kClassIDSpace, kFCObjStylesSelDialogTreeNodeTextWidgetBoss, kFindChangeFormatPanelPrefix + 38)
DECLARE_PMID(kClassIDSpace, kFindFormatConditionPanelBoss, kFindChangeFormatPanelPrefix + 39)
DECLARE_PMID(kClassIDSpace, kChangeFormatConditionPanelBoss, kFindChangeFormatPanelPrefix + 40)
DECLARE_PMID(kClassIDSpace, kFindConditionObserverBoss, kFindChangeFormatPanelPrefix + 41)
DECLARE_PMID(kClassIDSpace, kChangeConditionObserverBoss, kFindChangeFormatPanelPrefix + 42)
DECLARE_PMID(kClassIDSpace, kFCConditionListElementBoss, kFindChangeFormatPanelPrefix + 43)
// Observer Bosses: 100 to 200
//DECLARE_PMID(kClassIDSpace, kFindChangeCharStyleObserverBoss, kFindChangeFormatPanelPrefix + 117)
//DECLARE_PMID(kClassIDSpace, kFindChangeParaStyleObserverBoss, kFindChangeFormatPanelPrefix + 118)
//DECLARE_PMID(kClassIDSpace, kFindChangeFormatDoneObserverBoss, kFindChangeFormatPanelPrefix + 119)
//DECLARE_PMID(kClassIDSpace, kFindChangeFormatParaGeneralPanelBoss, kFindChangeFormatPanelPrefix + 252)
//DECLARE_PMID(kClassIDSpace, kFindChangeTextSelectableParaDialogBoss, kFindChangeFormatPanelPrefix + 254)
//DECLARE_PMID(kClassIDSpace, kFIndChangeTextSelectableCharDialogBoss, kFindChangeFormatPanelPrefix + 255)


// <Interface ID>
//----------------------------------------------------------------------------------------
// Interface IDs
//----------------------------------------------------------------------------------------

DECLARE_PMID(kInterfaceIDSpace, IID_IFINDCHANGEFORMATPANELMSG, kFindChangeFormatPanelPrefix + 0)
// gap
DECLARE_PMID(kInterfaceIDSpace, IID_IFINDCHANGEPARASTYLENAME, kFindChangeFormatPanelPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IFINDCHANGECHARSTYLENAME, kFindChangeFormatPanelPrefix + 3)

// <Implementation ID>
//----------------------------------------------------------------------------------------
// Implementation IDs
//----------------------------------------------------------------------------------------

// Panel Implementation: 0 to 9
//DECLARE_PMID(kImplementationIDSpace, kFindChangeFormatPanelImpl, kFindChangeFormatPanelPrefix + 1//available)
//DECLARE_PMID(kImplementationIDSpace, kFindChangeFormatPanelRegisterImpl, kFindChangeFormatPanelPrefix + 2)
// gap
//DECLARE_PMID(kImplementationIDSpace, kFindChangeFormatDialogImpl, kFindChangeFormatPanelPrefix + 4)
//DECLARE_PMID(kImplementationIDSpace, kFindChangeFormatDialogRsrcDataImpl, kFindChangeFormatPanelPrefix + 5	)
//DECLARE_PMID(kImplementationIDSpace, kFindChangeFormatCoreDialogRsrcDataImpl, kFindChangeFormatPanelPrefix + 6	)
//DECLARE_PMID(kImplementationIDSpace, kFindChangeFormatParaGeneralRsrcDataImpl, kFindChangeFormatPanelPrefix + 7)
//DECLARE_PMID(kImplementationIDSpace, kFindChangeFormatCharGeneralRsrcDataImpl, kFindChangeFormatPanelPrefix + 8	)
//DECLARE_PMID(kImplementationIDSpace, kFindChangeTargetServerImpl, kFindChangeFormatPanelPrefix + 10)
// gap
//DECLARE_PMID(kImplementationIDSpace, kFindChangeDlgControllerImpl, kFindChangeFormatPanelPrefix + 12)
// gap
//DECLARE_PMID(kImplementationIDSpace, kFindChangeFormatSelectableRsrcDataImpl, kFindChangeFormatPanelPrefix + 14)
// gap
DECLARE_PMID(kImplementationIDSpace, kFindFormatParaDialogRsrcDataImpl, kFindChangeFormatPanelPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kChangeFormatParaDialogRsrcDataImpl, kFindChangeFormatPanelPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kFindFormatDialogRsrcDataImpl, kFindChangeFormatPanelPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kChangeFormatDialogRsrcDataImpl, kFindChangeFormatPanelPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kFindFormatCoreDialogRsrcDataImpl, kFindChangeFormatPanelPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kChangeFormatCoreDialogRsrcDataImpl, kFindChangeFormatPanelPrefix + 20)

DECLARE_PMID(kImplementationIDSpace, kChangeFormatParaGeneralRsrcDataImpl, kFindChangeFormatPanelPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kFindFormatParaCoreDialogRsrcDataImpl, kFindChangeFormatPanelPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kChangeFormatParaCoreDialogRsrcDataImpl, kFindChangeFormatPanelPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kFindFormatCharCoreDialogRsrcDataImpl, kFindChangeFormatPanelPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kChangeFormatCharCoreDialogRsrcDataImpl, kFindChangeFormatPanelPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kChangeDlgControllerImpl, kFindChangeFormatPanelPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kChangeFormatSelectableRsrcDataImpl, kFindChangeFormatPanelPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kChangeTargetServerImpl, kFindChangeFormatPanelPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kFindDlgControllerImpl, kFindChangeFormatPanelPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kFindFormatSelectableRsrcDataImpl, kFindChangeFormatPanelPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kFindTargetServerImpl, kFindChangeFormatPanelPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kFindCharStyleObserverImpl, kFindChangeFormatPanelPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kFindParaStyleObserverImpl, kFindChangeFormatPanelPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kChangeCharStyleObserverImpl, kFindChangeFormatPanelPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kChangeParaStyleObserverImpl, kFindChangeFormatPanelPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kFindFormatParaGeneralRsrcDataImpl, kFindChangeFormatPanelPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kChangeFormatXMLRsrcDataImpl, kFindChangeFormatPanelPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kChangeTagObserverImpl, kFindChangeFormatPanelPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kObjectFindFormatSelDlgControllerImpl, kFindChangeFormatPanelPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kObjectFindFormatSelDlgCreatorImpl, kFindChangeFormatPanelPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kObjectFindFormatSelDlgObserverImpl, kFindChangeFormatPanelPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kObjectChangeFormatSelDlgControllerImpl, kFindChangeFormatPanelPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kObjectChangeFormatSelDlgCreatorImpl, kFindChangeFormatPanelPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kObjectChangeFormatSelDlgObserverImpl, kFindChangeFormatPanelPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kObjectFindFormatDialogGeneralPanelCreatorImpl, kFindChangeFormatPanelPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kObjectChangeFormatDialogGeneralPanelCreatorImpl, kFindChangeFormatPanelPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kObjectFindFormatDialogGeneralPanelObserverImpl, kFindChangeFormatPanelPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kObjectChangeFormatDialogGeneralPanelObserverImpl, kFindChangeFormatPanelPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kFCObjStylesSelDialogTreeViewWidgetMgrImpl, kFindChangeFormatPanelPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kFCObjStylesSelDialogTreeViewAdapterImpl, kFindChangeFormatPanelPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kFCObjStylesSelDialogTreeViewEHImpl, kFindChangeFormatPanelPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kFCObjStylesSelDialogTreeViewControllerImpl, kFindChangeFormatPanelPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kFCObjStylesSelDialogTreeNodeTipImpl, kFindChangeFormatPanelPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kFCTreeViewSelDlgSwitcherImpl, kFindChangeFormatPanelPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kFCObjStylesSelDialogObserverImpl, kFindChangeFormatPanelPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kObjectFindFormatGeneralPanelDataImpl, kFindChangeFormatPanelPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kObjectChangeFormatGeneralPanelDataImpl, kFindChangeFormatPanelPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kFindFormatConditionRsrcDataImpl, kFindChangeFormatPanelPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kChangeFormatConditionRsrcDataImpl, kFindChangeFormatPanelPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kFindChangeFormatConditionObserverImpl, kFindChangeFormatPanelPrefix + 60)

// Observer Bosses: 100 to 200
//DECLARE_PMID(kImplementationIDSpace, kFindChangeCharStyleObserverImpl, kFindChangeFormatPanelPrefix + 117)
//DECLARE_PMID(kImplementationIDSpace, kFindChangeParaStyleObserverImpl, kFindChangeFormatPanelPrefix + 118)
//DECLARE_PMID(kImplementationIDSpace, kFindChangeFormatDoneObserverImpl, kFindChangeFormatPanelPrefix + 119)

// <Widget ID>
DECLARE_PMID(kWidgetIDSpace, kFindChangeStyleTxtSettingsWidgetID, kFindChangeFormatPanelPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kFindChangeCharStyleWidgetID, kFindChangeFormatPanelPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kFindChangeParaStyleWidgetID, kFindChangeFormatPanelPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kFCCharStyleTextWidgetID, kFindChangeFormatPanelPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kFCParaStyleTextWidgetID, kFindChangeFormatPanelPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kFCFormatSettingsPopupGroupWidgetID, kFindChangeFormatPanelPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kFCFSeparator1WidgetID, kFindChangeFormatPanelPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kFCTagTextWidgetID, kFindChangeFormatPanelPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kFindChangeTagWidgetID, kFindChangeFormatPanelPrefix + 9)

DECLARE_PMID(kWidgetIDSpace, kObjectFindFormatSelectableDialogWidgetID, kFindChangeFormatPanelPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kObjectFindFormatSelectableDialogPanelWidgetID, kFindChangeFormatPanelPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kObjectFindFormatSelDialogRow1WidgetID, kFindChangeFormatPanelPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kObjectFindFormatSelDialogTreeViewWidgetID, kFindChangeFormatPanelPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kObjectFindFormatGenericWidget1WidgetID, kFindChangeFormatPanelPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kObjectFindFormatSelectableDialogRow1WidgetID, kFindChangeFormatPanelPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kObjectFindFormatGenericWidget2WidgetID, kFindChangeFormatPanelPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kObjectFindFormatGenericWidget3WidgetID, kFindChangeFormatPanelPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kObjectFindFormatSelectableDialogRow2WidgetID, kFindChangeFormatPanelPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kObjectFindFormatSelectableDialogRow3WidgetID, kFindChangeFormatPanelPrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kObjectFindFormatDialogGeneralPanelWidgetID, kFindChangeFormatPanelPrefix + 30)

DECLARE_PMID(kWidgetIDSpace, kObjectChangeFormatSelectableDialogWidgetID, kFindChangeFormatPanelPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kObjectChangeFormatSelectableDialogPanelWidgetID, kFindChangeFormatPanelPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kObjectChangeFormatSelDialogRow1WidgetID, kFindChangeFormatPanelPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kObjectChangeFormatSelDialogTreeViewWidgetID, kFindChangeFormatPanelPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kObjectChangeFormatGenericWidget1WidgetID, kFindChangeFormatPanelPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kObjectChangeFormatSelectableDialogRow1WidgetID, kFindChangeFormatPanelPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kObjectChangeFormatGenericWidget2WidgetID, kFindChangeFormatPanelPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kObjectChangeFormatGenericWidget3WidgetID, kFindChangeFormatPanelPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kObjectChangeFormatSelectableDialogRow2WidgetID, kFindChangeFormatPanelPrefix + 39)
DECLARE_PMID(kWidgetIDSpace, kObjectChangeFormatSelectableDialogRow3WidgetID, kFindChangeFormatPanelPrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kObjectChangeFormatDialogGeneralPanelWidgetID, kFindChangeFormatPanelPrefix + 41)
DECLARE_PMID(kWidgetIDSpace, kFCObjectStyleTextWidgetID, kFindChangeFormatPanelPrefix + 42)
DECLARE_PMID(kWidgetIDSpace, kFindChangeObjectStyleWidgetID, kFindChangeFormatPanelPrefix + 43)
DECLARE_PMID(kWidgetIDSpace, kFCObjStylesSelDialogTreeNodeStaticTextWidgetID, kFindChangeFormatPanelPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kFCObjStylesSelDialogTreeNodeWidgetID, kFindChangeFormatPanelPrefix + 45)
DECLARE_PMID(kWidgetIDSpace, kFCConditionTreeWidgetID, kFindChangeFormatPanelPrefix + 48)
DECLARE_PMID(kWidgetIDSpace, kFCConditionListElementNameWidgetID, kFindChangeFormatPanelPrefix + 49)
DECLARE_PMID(kWidgetIDSpace, kFCConditionListElementCheckboxWidgetID, kFindChangeFormatPanelPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kFCConditionListElementWidgetID, kFindChangeFormatPanelPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kFCAnyConditionElementWidgetID, kFindChangeFormatPanelPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kFCUnconditionalElementWidgetID, kFindChangeFormatPanelPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kChangeFormatApplyConditionChoiceWidgetID, kFindChangeFormatPanelPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kChangeFormatConditionReplaceWidgetID, kFindChangeFormatPanelPrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kChangeFormatConditionAppendWidgetID, kFindChangeFormatPanelPrefix + 56)
//DECLARE_PMID(kWidgetIDSpace, , kFindChangeFormatPanelPrefix + )

DECLARE_PMID(kImplementationIDSpace, kFindChangeFormatParaDialogRsrcDataImpl, kFindChangeFormatPanelPrefix + 250)
DECLARE_PMID(kImplementationIDSpace, kFindChangeFormatParaCoreDialogRsrcDataImpl, kFindChangeFormatPanelPrefix + 252)
DECLARE_PMID(kImplementationIDSpace, kFindChangeFormatCharCoreDialogRsrcDataImpl, kFindChangeFormatPanelPrefix + 253)

// <Service IDs>
DECLARE_PMID(kServiceIDSpace, kObjectFindFormatSelectableDialogService, kFindChangeFormatPanelPrefix + 252)
DECLARE_PMID(kServiceIDSpace, kObjectChangeFormatSelectableDialogService, kFindChangeFormatPanelPrefix + 253)
//DECLARE_PMID(kServiceIDSpace, kFindChangeParaDlgService, kFindChangeFormatPanelPrefix + 254)
DECLARE_PMID(kServiceIDSpace, kFindParaDlgService, kFindChangeFormatPanelPrefix + 255)
DECLARE_PMID(kServiceIDSpace, kChangeParaDlgService, kFindChangeFormatPanelPrefix + 256)

// <Message ID>
//----------------------------------------------------------------------------------------
// Message IDs
//----------------------------------------------------------------------------------------

DECLARE_PMID(kMessageIDSpace, kFindChangeFormatBasedOnChangedMessage, kFindChangeFormatPanelPrefix + 500)
DECLARE_PMID(kMessageIDSpace, kFindChangeFormatNextChangedMessage, kFindChangeFormatPanelPrefix + 501)
DECLARE_PMID(kMessageIDSpace, kFindChangeFormatSelectPrevMessage, kFindChangeFormatPanelPrefix + 502)
DECLARE_PMID(kMessageIDSpace, kFindChangeFormatSelectNextMessage, kFindChangeFormatPanelPrefix + 503)
DECLARE_PMID(kMessageIDSpace, kFindFormatDoneMessage, kFindChangeFormatPanelPrefix + 504)
DECLARE_PMID(kMessageIDSpace, kChangeFormatDoneMessage, kFindChangeFormatPanelPrefix + 505)

#define kFCObjStylesSelDialogNodeID    kFindChangeFormatPanelPrefix + 1

#endif // __FindChangeFormatPanelID__

