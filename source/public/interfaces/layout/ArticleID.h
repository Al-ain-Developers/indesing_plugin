//========================================================================================
//  
//  ADOBE CONFIDENTIAL
//   
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ArticleID.h $
// 
//  Owner: Paresh Goel
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 2010 Adobe Systems Incorporated
//  All Rights Reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//  Comments: Contains IDs used by the Article architecture.
//  
//========================================================================================

#ifndef __ARTICLEID__
#define __ARTICLEID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

// TODO
#define kArticlePrefix	 				RezLong(0x21B00)

// PluginID
#define kArticlePluginName 				"Article"
DECLARE_PMID(kPlugInIDSpace, kArticlePluginID, kArticlePrefix + 1)

// <Start IDC>
// <Class ID>
DECLARE_PMID(kClassIDSpace, kArticleBoss, kArticlePrefix + 1)
DECLARE_PMID(kClassIDSpace, kCreateArticleCmdBoss, kArticlePrefix + 2)
DECLARE_PMID(kClassIDSpace, kAddArticleCmdBoss, kArticlePrefix + 3)
DECLARE_PMID(kClassIDSpace, kSetArticleNameCmdBoss, kArticlePrefix + 4)
DECLARE_PMID(kClassIDSpace, kMoveArticleCmdBoss, kArticlePrefix + 5)
DECLARE_PMID(kClassIDSpace, kRemoveArticleCmdBoss, kArticlePrefix + 6)
DECLARE_PMID(kClassIDSpace, kDeleteArticleCmdBoss, kArticlePrefix + 7)

DECLARE_PMID(kClassIDSpace, kAddArticleMemberCmdBoss, kArticlePrefix + 8)
DECLARE_PMID(kClassIDSpace, kRemoveArticleMemberCmdBoss, kArticlePrefix + 9)
DECLARE_PMID(kClassIDSpace, kMoveArticleMemberCmdBoss, kArticlePrefix + 10)

DECLARE_PMID(kClassIDSpace, kAddChildrenToArticleGroupCmdBoss, kArticlePrefix + 11)
DECLARE_PMID(kClassIDSpace, kRemoveChildrenFromArticleGroupCmdBoss, kArticlePrefix + 12)
DECLARE_PMID(kClassIDSpace, kMoveChildrenInArticleGroupCmdBoss, kArticlePrefix + 13)
DECLARE_PMID(kClassIDSpace, kArticleScriptProviderBoss, kArticlePrefix + 14)
DECLARE_PMID(kClassIDSpace, kArticleErrorStringServiceBoss,	kArticlePrefix + 15)
//--gap--
DECLARE_PMID(kClassIDSpace, kArticleMemberScriptBoss,	kArticlePrefix + 18)
DECLARE_PMID(kClassIDSpace, kArticleChildScriptBoss,	kArticlePrefix + 19)
DECLARE_PMID(kClassIDSpace, kArticleReferenceListM2MListenerServiceBoss, kArticlePrefix + 20)

DECLARE_PMID(kClassIDSpace, kArticleMemberListM2MListenerServiceBoss, kArticlePrefix + 21)
DECLARE_PMID(kClassIDSpace, kArticleChildListM2MListenerServiceBoss, kArticlePrefix + 22)
DECLARE_PMID(kClassIDSpace, kArticleReferenceReferenceConverterBoss, kArticlePrefix + 23)
DECLARE_PMID(kClassIDSpace, kArticleReferenceScrapDataBoss, kArticlePrefix + 24)
DECLARE_PMID(kClassIDSpace, kArticleReferenceFixupPasteFromScrapCmdBoss, kArticlePrefix + 25)
DECLARE_PMID(kClassIDSpace, kArticleChildListFixupDuplicationCmdBoss, kArticlePrefix + 26)
DECLARE_PMID(kClassIDSpace, kSetArticleExportStatusCmdBoss, kArticlePrefix + 27)

//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kArticlePrefix + 28)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kArticlePrefix + 29)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kArticlePrefix + 30)


// <Interface ID>
DECLARE_PMID(kInterfaceIDSpace, IID_IARTICLEMEMBERLIST, kArticlePrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IARTICLENAME, kArticlePrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IARTICLELIST, kArticlePrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IARTICLECHILDLIST, kArticlePrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IARTICLEREFERENCELIST, kArticlePrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOPOSITION, kArticlePrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IARTICLEFACADE, kArticlePrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IARTICLEOBSERVER, kArticlePrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IARTICLEREFERENCESCRAPDATA, kArticlePrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IARTICLEREFERENCESCRAPDATALIST, kArticlePrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IISARTICLEUSEDFOREXPORT, kArticlePrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IARTICLEUTILS, kArticlePrefix + 12)

//DECLARE_PMID(kInterfaceIDSpace, IID_MYFANCYNEWIID, kArticlePrefix + 13)
//DECLARE_PMID(kInterfaceIDSpace, IID_MYFANCYNEWIID, kArticlePrefix + 14)
//DECLARE_PMID(kInterfaceIDSpace, IID_MYFANCYNEWIID, kArticlePrefix + 15)
//DECLARE_PMID(kInterfaceIDSpace, IID_MYFANCYNEWIID, kArticlePrefix + 16)
//DECLARE_PMID(kInterfaceIDSpace, IID_MYFANCYNEWIID, kArticlePrefix + 17)
//DECLARE_PMID(kInterfaceIDSpace, IID_MYFANCYNEWIID, kArticlePrefix + 18)
//DECLARE_PMID(kInterfaceIDSpace, IID_MYFANCYNEWIID, kArticlePrefix + 19)
//DECLARE_PMID(kInterfaceIDSpace, IID_MYFANCYNEWIID, kArticlePrefix + 20)


// <Implementation ID>
//DECLARE_PMID(kImplementationIDSpace, kArticleNameImpl, kArticlePrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kArticleMemberListImpl, kArticlePrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kArticleListImpl, kArticlePrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kArticleReferenceListImpl, kArticlePrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kArticleChildListImpl, kArticlePrefix + 5)

DECLARE_PMID(kImplementationIDSpace, kCreateArticleCmdImpl, kArticlePrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kAddArticleCmdImpl, kArticlePrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kSetArticleNameCmdImpl, kArticlePrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kMoveArticleCmdImpl, kArticlePrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kRemoveArticleCmdImpl, kArticlePrefix + 10)

DECLARE_PMID(kImplementationIDSpace, kDeleteArticleCmdImpl, kArticlePrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kAddArticleMemberCmdImpl, kArticlePrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kRemoveArticleMemberCmdImpl, kArticlePrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kMoveArticleMemberCmdImpl, kArticlePrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kAddChildrenToArticleGroupCmdImpl, kArticlePrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kRemoveChildrenFromArticleGroupCmdImpl, kArticlePrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kMoveChildrenInArticleGroupCmdImpl, kArticlePrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kArticleFacadeImpl, kArticlePrefix + 18)
//scripting related
DECLARE_PMID(kImplementationIDSpace, kArticleScriptProviderImpl,			kArticlePrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kArticleErrorStringServiceImpl,		kArticlePrefix + 20)

DECLARE_PMID(kImplementationIDSpace, kArticleScriptImpl,		kArticlePrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kArticleMemberScriptImpl,			kArticlePrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kArticleChildScriptImpl,			kArticlePrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kArticleReferenceReferenceConverterImpl,			kArticlePrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kArticleReferenceScrapDataImpl,	kArticlePrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kArticleScrapPersistUIDListDataImpl,			kArticlePrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kArticleReferenceListM2MListenerImpl,		kArticlePrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kArticleMemberListM2MListenerImpl,		kArticlePrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kArticleChildListM2MListenerImpl,		kArticlePrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kArticleReferenceFixupPasteFromScrapCmdImpl,			kArticlePrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kArticleChildListFixupDuplicationCmdImpl,			kArticlePrefix + 31)

DECLARE_PMID(kImplementationIDSpace, kSetArticleExportStatusCmdImpl,		kArticlePrefix + 32)

DECLARE_PMID(kImplementationIDSpace, kArticleUtilsImpl,		kArticlePrefix + 33)

//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,			kArticlePrefix + 34)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,			kArticlePrefix + 35)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,			kArticlePrefix + 36)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,			kArticlePrefix + 37)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,			kArticlePrefix + 38)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl,			kArticlePrefix + 39)

//error code
DECLARE_PMID(kErrorIDSpace, kInvalidArticleParameterError,		kArticlePrefix + 1)
DECLARE_PMID(kErrorIDSpace, kInvalidMemberParameterError,		kArticlePrefix + 2)
DECLARE_PMID(kErrorIDSpace, kParentGroupNotPartofArticleError,	kArticlePrefix + 3)
DECLARE_PMID(kErrorIDSpace, kItemsBelongToDifferentGroupsError,	kArticlePrefix + 4)
DECLARE_PMID(kErrorIDSpace, kInvalidChildParameterError,		kArticlePrefix + 5)

//ScriptInfoIDs:
//objects
DECLARE_PMID(kScriptInfoIDSpace, kArticleObjectScriptElement, kArticlePrefix + 0)
DECLARE_PMID(kScriptInfoIDSpace, kMemberObjectScriptElement, kArticlePrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kArticleChildObjectScriptElement, kArticlePrefix + 2)

//properties
DECLARE_PMID(kScriptInfoIDSpace, kPageItemRefScriptElement, kArticlePrefix + 3)
DECLARE_PMID(kScriptInfoIDSpace, kArticlesPropertyScriptElement, kArticlePrefix + 4)
DECLARE_PMID(kScriptInfoIDSpace, kGroupArticleChildrenPropertyScriptElement, kArticlePrefix + 5)
DECLARE_PMID(kScriptInfoIDSpace, kExportStatusPropertyScriptElement, kArticlePrefix + 9)

//methods
DECLARE_PMID(kScriptInfoIDSpace, kAddArticleMethodScriptElement, kArticlePrefix + 6)
DECLARE_PMID(kScriptInfoIDSpace, kAddMemberMethodScriptElement, kArticlePrefix + 7)
DECLARE_PMID(kScriptInfoIDSpace, kPopulateArticleMethodScriptElement, kArticlePrefix + 8)

#define kArticleStringsRsrcID				100
#define kArticleStringsNoTransRsrcID		200
#define kArticleErrorStringsRsrcID			300

#endif //__ARTICLEID__
