//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/contentdropper/ContentDropperID.h $
//  
//  Owner: Varun Aggarwal
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
//  Contains IDs used by ContentDropper plug-in
//  
//========================================================================================

#ifndef __ContentDropperID__
#define __ContentDropperID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kContentDropperPrefix	 RezLong(0x22300)

// <Start IDC>
// PluginID
#define kContentDropperlPluginName 				"ContentDropper"
DECLARE_PMID(kPlugInIDSpace, kContentDropperPluginID, kContentDropperPrefix + 1)

// <Class ID>
DECLARE_PMID(kClassIDSpace, kGrabItemCmdBoss, kContentDropperPrefix + 1)
DECLARE_PMID(kClassIDSpace, kDropItemCmdBoss, kContentDropperPrefix + 2)
DECLARE_PMID(kClassIDSpace, kRemoveGrabbedItemCmdBoss, kContentDropperPrefix + 3)
DECLARE_PMID(kClassIDSpace, kContentDropperBeforeDocCloseResponderBoss, kContentDropperPrefix + 4)
DECLARE_PMID(kClassIDSpace, kContentDropperM2MListenerServiceBoss, kContentDropperPrefix + 5)
DECLARE_PMID(kClassIDSpace, kLoadPlaceHeadCmdBoss, kContentDropperPrefix + 6)
DECLARE_PMID(kClassIDSpace, kContentDropperNewDocResponderBoss, kContentDropperPrefix + 7)
DECLARE_PMID(kClassIDSpace, kContentDropperOpenDocResponderBoss, kContentDropperPrefix + 8)
DECLARE_PMID(kClassIDSpace, kContentPlaceScriptProviderBoss, kContentDropperPrefix + 9)
DECLARE_PMID(kClassIDSpace, kContentDropperOptionScriptBoss, kContentDropperPrefix + 10)
DECLARE_PMID(kClassIDSpace, kContentDropperErrorStringServiceBoss, kContentDropperPrefix + 11)
DECLARE_PMID(kClassIDSpace, kSetCDPrefsAfterPlaceOptionCmdBoss, kContentDropperPrefix + 12)
DECLARE_PMID(kClassIDSpace, kLoadPlaceHeadCmdForContinueTrackingBoss, kContentDropperPrefix + 13)
DECLARE_PMID(kClassIDSpace, kSetCDPrefsGrabAllTextFramesOptionCmdBoss, kContentDropperPrefix + 14)

// <Implementation ID>
DECLARE_PMID(kImplementationIDSpace, kContentDropperFacadeImpl, kContentDropperPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kContentDropperDocDataImpl, kContentDropperPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kContentDropperAppDataImpl, kContentDropperPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kGrabItemCmdImpl, kContentDropperPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kDropItemCmdImpl, kContentDropperPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kRemoveGrabbedItemCmdImpl, kContentDropperPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kContentDropperDocResponderImpl, kContentDropperPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kContentDropperM2MListenerImpl, kContentDropperPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kLoadPlaceHeadCmdImpl, kContentDropperPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kLoadPlaceHeadCmdForContinueTrackingImpl, kContentDropperPrefix + 9)
//gap
DECLARE_PMID(kImplementationIDSpace, kCGrabBehaviorImpl, kContentDropperPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kMultiFrameGrabBehaviorImpl, kContentDropperPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kFormFieldGrabBehaviorImpl, kContentDropperPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kGroupGrabBehaviorImpl, kContentDropperPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kSplineGrabBehaviorImpl, kContentDropperPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kListOfUIDListsImpl, kContentDropperPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kMediaGrabBehaviorImpl, kContentDropperPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kContentPlaceScriptProviderImpl, kContentDropperPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kContentDropperOptionScriptImpl, kContentDropperPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kLinkObjectsDataImpl, kContentDropperPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kLinkStoriesDataImpl, kContentDropperPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kMapStylesDataImpl, kContentDropperPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kContentDropperErrorStringServiceImpl, kContentDropperPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kContentDropperPreferencesImpl, kContentDropperPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kCSetContentDropperPrefsCmdImpl, kContentDropperPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kSetCDPrefsAfterPlaceOptionCmdImpl, kContentDropperPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kSetCDPrefsGrabAllTextFramesOptionCmdImpl, kContentDropperPrefix + 27)

//<Interface ID>

DECLARE_PMID(kInterfaceIDSpace, IID_ICONTENTDROPPERFACADE, kContentDropperPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTENTDROPPERDOCDATA, kContentDropperPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTENTDROPPERAPPDATA, kContentDropperPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IPLACEHEAD, kContentDropperPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTENTGRAB, kContentDropperPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTENTDROP, kContentDropperPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTENTDROPPERSOURCEUIDLISTDATA, kContentDropperPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTENTDROPPOLICYDATA, kContentDropperPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRABBEHAVIOR, kContentDropperPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_ILISTOFUIDLISTS, kContentDropperPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKITEMS, kContentDropperPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IMAPSTYLES, kContentDropperPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKOBJECTSDATA, kContentDropperPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKSTORIESDATA, kContentDropperPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IMAPSTYLESDATA, kContentDropperPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IRMVHIERARCHY, kContentDropperPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IUSEHEAD, kContentDropperPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IAFTERPLACE, kContentDropperPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTENTDROPPERPREFERENCES, kContentDropperPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOPYFULLSTORY, kContentDropperPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_IDUPLICATED_ITEMS_START_OUT_VISIBLE, kContentDropperPrefix + 20)


// <Widget ID>
// Character attribute widgets <1-50>

// <Message ID>
DECLARE_PMID(kMessageIDSpace, kDocumentItemsRemovedMessage,    kContentDropperPrefix + 1)
DECLARE_PMID(kMessageIDSpace, kItemsRotatedMessage,			   kContentDropperPrefix + 2)
DECLARE_PMID(kMessageIDSpace, kItemsExpandedCollapsedMessage,  kContentDropperPrefix + 3)

// <InvalHandler ID>
DECLARE_PMID(kInvalHandlerIDSpace, kContentDropperInvalHandlerID,    kContentDropperPrefix + 1 )


// <Service ID>
// Service IDs
DECLARE_PMID(kServiceIDSpace, kBeforeLoadPlaceHeadService, kContentDropperPrefix + 0)
DECLARE_PMID(kServiceIDSpace, kAfterLoadPlaceHeadService, kContentDropperPrefix + 1)

// <Action ID>
// Action IDs
//DECLARE_PMID(kActionIDSpace, kContentDropperToolActionID, kContentDropperPrefix + 1)

//<Icon IDs>

//script info
DECLARE_PMID(kScriptInfoIDSpace, kContentPlaceMethodScriptElement, kContentDropperPrefix + 0) 
DECLARE_PMID(kScriptInfoIDSpace, kContentPlaceOnSpreadMethodScriptElement, kContentDropperPrefix + 1) 
DECLARE_PMID(kScriptInfoIDSpace, kContentDropperObjectScriptElement, kContentDropperPrefix + 2) 
DECLARE_PMID(kScriptInfoIDSpace, kContentDropperPropertyScriptElement, kContentDropperPrefix + 3) 
DECLARE_PMID(kScriptInfoIDSpace, kContentDropperLoadedPropertyScriptElement, kContentDropperPrefix + 4) 
DECLARE_PMID(kScriptInfoIDSpace, kLoadContentDropperMethodScriptElement, kContentDropperPrefix + 5) 
DECLARE_PMID(kScriptInfoIDSpace, kContentDropperOptionObjectScriptElement, kContentDropperPrefix + 6) 
DECLARE_PMID(kScriptInfoIDSpace, kAddContentDropperOptionMethodScriptElement, kContentDropperPrefix + 7) 
DECLARE_PMID(kScriptInfoIDSpace, kLinkObjectsPropertyScriptElement, kContentDropperPrefix + 8)
DECLARE_PMID(kScriptInfoIDSpace, kLinkStoriesPropertyScriptElement, kContentDropperPrefix + 9)
DECLARE_PMID(kScriptInfoIDSpace, kMapStylesPropertyScriptElement, kContentDropperPrefix + 10)

DECLARE_PMID(kErrorIDSpace, kContentPlaceFailedError, kContentDropperPrefix + 0)
DECLARE_PMID(kErrorIDSpace, kLoadContentDropperFailedError, kContentDropperPrefix + 1)

//GUIDS
// {2953DFA5-A99F-477B-A075-162CEE929171}
#define kContentDropper_CLSID { 0x2953dfa5, 0xa99f, 0x477b, { 0xa0, 0x75, 0x16, 0x2c, 0xee, 0x92, 0x91, 0x71 } }

// {92F8E560-9A9E-42BA-BD89-854262DD825E}
#define kContentDropperOption_CLSID { 0x92f8e560, 0x9a9e, 0x42ba, { 0xbd, 0x89, 0x85, 0x42, 0x62, 0xdd, 0x82, 0x5e } }

// {81A029B5-3B66-4F4C-B10E-68C2B98A2A35}
#define kContentDropperOptions_CLSID { 0x81a029b5, 0x3b66, 0x4f4c, { 0xb1, 0xe, 0x68, 0xc2, 0xb9, 0x8a, 0x2a, 0x35 } };

enum ContentDropperScriptIDs
{
	e_ContentPlace				= 'copl',
	c_ContentDropper			= 'cCDn',
	p_ContentDropper			= 'pCDn',
	e_LoadContentDropper		= 'LCDr',
	c_ContentDropperOption		= 'cCDO',
	c_ContentDropperOptions		= 'cCDS',
	p_LinkObjects				= 'pLOO',
	p_LinkStories				= 'pLSO',
	p_MapStyles					= 'pMSO',
} ;

#endif
