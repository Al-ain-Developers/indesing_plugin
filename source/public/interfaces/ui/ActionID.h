//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ActionID.h $
//  
//  Owner: lance bushore
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
//  Contains IDs used by actions, menus, shortcuts.
//  
//========================================================================================

#ifndef __ActionID__
#define __ActionID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kActionPrefix	 RezLong(0xd200)
// note: we use 7 prefixes! d2,d3,d4,d5,d6,d7,d8 - we overflow our ActionIDs from one to the next willy-nilly
#define kActionPrefix8	 RezLong(0x19600)
#define kScriptMenuActionPrefixFirst	RezLong(0xff002000)
#define kScriptMenuActionPrefixLast		RezLong(0xff003F00)


// Resource IDs
#define kActionsStringResID				2100
#define kActionsStringsNoTransRsrcID	2200
#define kActionsErrorStringTableRsrcID	2300

// PluginID
#define kActionsPluginName 	"Actions"
DECLARE_PMID(kPlugInIDSpace, kActionsPluginID, kActionPrefix + 1)

// <Start IDC>
// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kActionManagerBoss,				kActionPrefix + 1)
DECLARE_PMID(kClassIDSpace, kTraceFlowTestMenuBoss,			kActionPrefix + 2)
DECLARE_PMID(kClassIDSpace, kMacOSXMenuFilterBoss,			kActionPrefix + 3)
DECLARE_PMID(kClassIDSpace, kDefaultShortcutContextBoss,	kActionPrefix + 4)
DECLARE_PMID(kClassIDSpace, kMacOSXActionFilterBoss,		kActionPrefix + 5)
DECLARE_PMID(kClassIDSpace, kActionInitializerBoss,			kActionPrefix + 6)
DECLARE_PMID(kClassIDSpace, kMenuInitializerBoss,			kActionPrefix + 7)
DECLARE_PMID(kClassIDSpace, kMenuActionScriptProviderBoss,	kActionPrefix + 8)
DECLARE_PMID(kClassIDSpace, kMenuActionScriptObjectBoss,	kActionPrefix + 9)
DECLARE_PMID(kClassIDSpace, kScriptMenuActionComponentBoss,	kActionPrefix + 10)
DECLARE_PMID(kClassIDSpace, kScriptPreActionComponentBoss,	kActionPrefix + 11)
DECLARE_PMID(kClassIDSpace, kScriptPostActionComponentBoss,	kActionPrefix + 12)
DECLARE_PMID(kClassIDSpace, kActionIDPoolInitializerBoss,	kActionPrefix + 13)
DECLARE_PMID(kClassIDSpace, kActionsErrorStringServiceBoss,	kActionPrefix + 14)
DECLARE_PMID(kClassIDSpace, kMenuElementScriptProviderBoss,	kActionPrefix + 15)
DECLARE_PMID(kClassIDSpace, kMenuElementScriptObjectBoss,	kActionPrefix + 16)
DECLARE_PMID(kClassIDSpace, kBaseActionComponentBoss,		kActionPrefix + 17)
DECLARE_PMID(kClassIDSpace, kBaseTestMenuBoss,				kActionPrefix + 18)


// <Message ID> // note - message ids conflict with class ids.
DECLARE_PMID(kMessageIDSpace, kMenuManagerMenuStatusChangeMessage, kActionPrefix + 100)
DECLARE_PMID(kMessageIDSpace, kChangeShortcutSetFileMessage, kActionPrefix + 101)
DECLARE_PMID(kMessageIDSpace, kMenuManagerPageSizesChangeMessage, kActionPrefix + 102)
DECLARE_PMID(kMessageIDSpace, kMenuManagerMenuAboutToOpen, kActionPrefix + 103)
DECLARE_PMID(kMessageIDSpace, kBeginPerformShortcutMessage, kActionPrefix + 104)
DECLARE_PMID(kMessageIDSpace, kMenuManagerMenuOpened, kActionPrefix + 105)

// <Implementation ID>
// ImplementationIDs
DECLARE_PMID(kImplementationIDSpace, kMenuMgrImpl,						kActionPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kActionManagerImpl,				kActionPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kShortcutManagerImpl,				kActionPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kActionsErrorStringServiceImpl,	kActionPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kMenuFilterProviderImpl,			kActionPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kActionIDToUIDDataImpl,			kActionPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kMenuRegisterProviderImpl,			kActionPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kActionFilterProviderImpl,			kActionPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kMacOS_X_MenuFilterImpl,			kActionPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kDynamicActionIDPoolImpl,			kActionPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kActionRegisterProviderImpl,		kActionPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kDefaultShortcutContextImpl,		kActionPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kShortcutContextProviderImpl,		kActionPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kShortcutContextIntegratorImpl,	kActionPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kTestMenuRegisterImpl,				kActionPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kMacOS_X_ActionFilterImpl,			kActionPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kActionInitializerImpl,			kActionPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kMenuInitializerImpl,				kActionPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kShortcutSetNamePrefImpl,			kActionPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kMenuActionScriptProviderImpl,		kActionPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kMenuActionScriptObjectImpl,		kActionPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kScriptMenuActionComponentImpl,	kActionPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kScriptPreActionComponentImpl,		kActionPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kScriptPostActionComponentImpl,	kActionPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kActionIDPoolInitializerImpl,		kActionPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kScriptMenuActionManagerImpl,		kActionPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kMenuElementScriptProviderImpl,	kActionPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kMenuElementScriptObjectImpl,		kActionPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kMenuActionScriptUtilsImpl,		kActionPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kMenuCustomizationDataImpl,		kActionPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kMenuCustomizationDialogDataImpl,	kActionPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kDynamicScriptMenuActionImpl,		kActionPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kMenuElementScriptEventTargetImpl,	kActionPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kShortcutSetAreaPrefImpl,			kActionPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kMenuActionShortcutSetObserverImpl,kActionPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kActionInfoImpl,					kActionPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kUserDefinedActionImpl,			kActionPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kMenuActionScriptEventTargetImpl,	kActionPrefix + 38)

// <Interface ID>
DECLARE_PMID(kInterfaceIDSpace, IID_IACTIONCOMPONENT,					kActionPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IACTIONMANAGER,						kActionPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ISHORTCUTMANAGER,					kActionPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IMENUMANAGER,						kActionPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_ISHORTCUTCONTEXT,					kActionPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IMENUREGISTER,						kActionPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IACTIONFILTER,						kActionPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IDYNAMICMENU,						kActionPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IACTIONIDTOUIDDATA,					kActionPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IMENUFILTER,						kActionPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IACTIONREGISTER,					kActionPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_ICURRENTSHORTCUTSETNAMEPREF,		kActionPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IDYNAMICACTIONIDPOOL,				kActionPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTMENUACTIONMANAGER,			kActionPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IMENUACTIONSCRIPTUTILS,				kActionPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IMENUCUSTOMIZATIONDATA,				kActionPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IMENUCUSTOMIZATIONDIALOGDATA,		kActionPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_ICURRENTSHORTCUTSETAREAPREF,		kActionPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_IACTIONINFO,						kActionPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_IUSERDEFINEDACTION,					kActionPrefix + 20)

// <Service ID>
DECLARE_PMID(kServiceIDSpace, kMenuRegisterService,				kActionPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kActionFilterService,				kActionPrefix + 2)
DECLARE_PMID(kServiceIDSpace, kMenuFilterService,				kActionPrefix + 3)
DECLARE_PMID(kServiceIDSpace, kActionRegisterService,			kActionPrefix + 4)
DECLARE_PMID(kServiceIDSpace, kShortcutContextService,			kActionPrefix + 5)

// note: we use 7 prefixes! d2,d3,d4,d5,d6,d7,d8 - we overflow our ActionIDs from one to the next willy-nilly

// <Action ID>
#ifdef ID_ENABLE_DEBUGGING
DECLARE_PMID(kActionIDSpace, kFirstTestMenuActionID,			kActionPrefix + 1)
// all the ids between kFirstTestMenuActionID and kLastTestMenuActionID are reserved.
DECLARE_PMID(kActionIDSpace, kLastTestMenuActionID,				kActionPrefix + 1701)
//gap?
DECLARE_PMID(kActionIDSpace, kFirstTraceCategoryActionID,		kActionPrefix8 + 1)
// ids in here reserved
DECLARE_PMID(kActionIDSpace, kLastTraceCategoryActionID,		kActionPrefix8 + 240)
DECLARE_PMID(kActionIDSpace, kTestSepActionID,					kActionPrefix8 + 241)
#endif
DECLARE_PMID(kActionIDSpace, kShowAllMenuItemsActionID,			kActionPrefix8 + 242)

DECLARE_PMID(kActionIDSpace, kFirstScriptMenuActionID,			kScriptMenuActionPrefixFirst + 0)
//intervening Action IDs are allocated dynamically by the IDynamicActionIDPool
DECLARE_PMID(kActionIDSpace, kLastScriptMenuActionID,			kScriptMenuActionPrefixLast + 255)

// <ErrorCode>
DECLARE_PMID(kErrorIDSpace, kUnableToDeleteActionError,				kActionPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kActionIsNotEnabledError,				kActionPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kUnableToDeleteMenuError,				kActionPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kDismissedPreviewableModalDialogError,	kActionPrefix + 4)

//
//Script Element IDs
//

//Events
DECLARE_PMID(kScriptInfoIDSpace, kOnInvokeEventScriptElement,				kActionPrefix + 0)
DECLARE_PMID(kScriptInfoIDSpace, kBeforeInvokeEventScriptElement,			kActionPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kAfterInvokeEventScriptElement,			kActionPrefix + 2)
DECLARE_PMID(kScriptInfoIDSpace, kBeforeDisplayEventScriptElement,			kActionPrefix + 3)

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kMenuActionObjectScriptElement,			kActionPrefix + 20)
DECLARE_PMID(kScriptInfoIDSpace, kScriptMenuActionObjectScriptElement,		kActionPrefix + 21)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kMenuObjectScriptElement,					kActionPrefix + 30)
DECLARE_PMID(kScriptInfoIDSpace, kMenuElementObjectScriptElement,			kActionPrefix + 31)
DECLARE_PMID(kScriptInfoIDSpace, kSubmenuObjectScriptElement,				kActionPrefix + 32)
DECLARE_PMID(kScriptInfoIDSpace, kMenuItemObjectScriptElement,				kActionPrefix + 33)
DECLARE_PMID(kScriptInfoIDSpace, kMenuSeparatorObjectScriptElement,			kActionPrefix + 34)

//Methods
DECLARE_PMID(kScriptInfoIDSpace, kCreateScriptMenuActionMethodScriptElement,kActionPrefix + 60)
DECLARE_PMID(kScriptInfoIDSpace, kInvokeMenuActionMethodScriptElement,		kActionPrefix + 61)
DECLARE_PMID(kScriptInfoIDSpace, kCreateSubmenuMethodScriptElement,			kActionPrefix + 62)
DECLARE_PMID(kScriptInfoIDSpace, kCreateMenuItemMethodScriptElement,		kActionPrefix + 63)
DECLARE_PMID(kScriptInfoIDSpace, kCreateMenuSeparatorMethodScriptElement,	kActionPrefix + 64)
DECLARE_PMID(kScriptInfoIDSpace, kSelectMenuMethodScriptElement,			kActionPrefix + 65)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kMenuActionAreaPropertyScriptElement,		kActionPrefix + 125)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kMenuActionCheckedPropertyScriptElement,	kActionPrefix + 127)
DECLARE_PMID(kScriptInfoIDSpace, kAssociatedMenuActionPropertyScriptElement,kActionPrefix + 128)
DECLARE_PMID(kScriptInfoIDSpace, kMenuActionTitlePropertyScriptElement,		kActionPrefix + 129)

//Enums

//ScriptIDs
enum
{
	c_MenuAction =				'Actn',
	c_MenuActions =				'Acts',
	c_ScriptMenuAction =		'SAcn',
	c_ScriptMenuActions =		'SAcs',
	c_Menu =					'MeNu',
	c_Menus =					'MeNs',
	c_MenuElement =				'MeEl',
	c_MenuElements =			'MeEs',
	c_Submenu =					'SbMe',
	c_Submenus =				'SbMs',
	c_MenuItem =				'MeIt',
	c_MenuItems =				'MeIs',
	c_MenuSeparator =			'MeSp',
	c_MenuSeparators =			'MeSs',
	c_MenuEvent =				'MeEv',

	e_Invoke =					'Invk',
	e_OnInvoke =				'OnIn',
	e_BeforeInvoke =			'BfIv',
	e_AfterInvoke =				'AfIv',
	e_BeforeDisplay =			'BfDs',

	p_Area =					'Area',
	p_Checked =					'Chkd',
	p_AssociatedMenuAction =	'AssA',

	LastMenuActionScriptID
} ;

//CLSIDs
// {FC2F7FA1-DF94-41ef-8C13-E7B51401C883}
#define kMenuAction_CLSID { 0xfc2f7fa1, 0xdf94, 0x41ef, { 0x8c, 0x13, 0xe7, 0xb5, 0x14, 0x1, 0xc8, 0x83 } }
// {81E98E8E-8825-4028-8FAD-51D5D4F68EBF}
#define kMenuActions_CLSID { 0x81e98e8e, 0x8825, 0x4028, { 0x8f, 0xad, 0x51, 0xd5, 0xd4, 0xf6, 0x8e, 0xbf } }
// {6EFFC754-5F78-43ae-9FBF-685A9CF33853}
#define kScriptMenuAction_CLSID { 0x6effc754, 0x5f78, 0x43ae, { 0x9f, 0xbf, 0x68, 0x5a, 0x9c, 0xf3, 0x38, 0x53 } }
// {31063219-95D9-4ad8-9BEC-0CE806787AF5}
#define kScriptMenuActions_CLSID { 0x31063219, 0x95d9, 0x4ad8, { 0x9b, 0xec, 0xc, 0xe8, 0x6, 0x78, 0x7a, 0xf5 } }

// {3EFBCAD9-5B7D-47cc-B966-D9BC596D5F41}
#define kMenu_CLSID { 0x3efbcad9, 0x5b7d, 0x47cc, { 0xb9, 0x66, 0xd9, 0xbc, 0x59, 0x6d, 0x5f, 0x41 } }
// {AE3848F5-26F9-425f-B6CB-63C9919DE0DA}
#define kMenus_CLSID { 0xae3848f5, 0x26f9, 0x425f, { 0xb6, 0xcb, 0x63, 0xc9, 0x91, 0x9d, 0xe0, 0xda } }
// {35383B77-080D-471e-B8FB-02D6457E4576}
#define kMenuElement_CLSID { 0x35383b77, 0x80d, 0x471e, { 0xb8, 0xfb, 0x2, 0xd6, 0x45, 0x7e, 0x45, 0x76 } }
// {9BC922A4-70B0-42e3-880F-FBB9218CBE44}
#define kMenuElements_CLSID { 0x9bc922a4, 0x70b0, 0x42e3, { 0x88, 0xf, 0xfb, 0xb9, 0x21, 0x8c, 0xbe, 0x44 } }
// {5ACF4641-B36D-407e-A146-279FB1B88830}
#define kSubmenu_CLSID { 0x5acf4641, 0xb36d, 0x407e, { 0xa1, 0x46, 0x27, 0x9f, 0xb1, 0xb8, 0x88, 0x30 } }
// {915BC743-5075-4ce1-B6A3-51CF28518A91}
#define kSubmenus_CLSID { 0x915bc743, 0x5075, 0x4ce1, { 0xb6, 0xa3, 0x51, 0xcf, 0x28, 0x51, 0x8a, 0x91 } }
// {9B1C9CB0-0E2C-49ff-AEAD-E0B2D04A4E0F}
#define kMenuItem_CLSID { 0x9b1c9cb0, 0xe2c, 0x49ff, { 0xae, 0xad, 0xe0, 0xb2, 0xd0, 0x4a, 0x4e, 0xf } }
// {94A76A14-D4F0-4639-BCB0-3C58CF08DC42}
#define kMenuItems_CLSID { 0x94a76a14, 0xd4f0, 0x4639, { 0xbc, 0xb0, 0x3c, 0x58, 0xcf, 0x8, 0xdc, 0x42 } }
// {5908717A-CC47-41f9-AFFA-D89AAAFA428F}
#define kMenuSeparator_CLSID { 0x5908717a, 0xcc47, 0x41f9, { 0xaf, 0xfa, 0xd8, 0x9a, 0xaa, 0xfa, 0x42, 0x8f } }
// {E959211D-7888-4a36-86B5-C0643A8AC530}
#define kMenuSeparators_CLSID { 0xe959211d, 0x7888, 0x4a36, { 0x86, 0xb5, 0xc0, 0x64, 0x3a, 0x8a, 0xc5, 0x30 } }

#endif // __ActionID__
