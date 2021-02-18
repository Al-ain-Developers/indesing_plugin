//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/PageItemScrapID.h $
//  
//  Owner: Robin_Briggs
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
//  Contains IDs used by the page item scrap sub-system
//  
//========================================================================================

#ifndef __PageItemScrapID__
#define __PageItemScrapID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kPageItemScrapPrefix	 RezLong(0xF00)

// <Start IDC>
// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kPageItemScrapHandlerBoss, kPageItemScrapPrefix + 1)
DECLARE_PMID(kClassIDSpace, kDeleteCmdBoss, kPageItemScrapPrefix + 2)
DECLARE_PMID(kClassIDSpace, kDeletePageItemCmdBoss, kPageItemScrapPrefix + 3)
DECLARE_PMID(kClassIDSpace, kCopyCmdBoss, kPageItemScrapPrefix + 4)
DECLARE_PMID(kClassIDSpace, kPasteCmdBoss, kPageItemScrapPrefix + 5)
DECLARE_PMID(kClassIDSpace, kCopyPageItemCmdBoss, kPageItemScrapPrefix + 6)
DECLARE_PMID(kClassIDSpace, kPasteInsideCmdBoss, kPageItemScrapPrefix + 7)
DECLARE_PMID(kClassIDSpace, kDeleteInsideCmdBoss, kPageItemScrapPrefix + 8)
DECLARE_PMID(kClassIDSpace, kCopyInsideCmdBoss, kPageItemScrapPrefix + 9)
//DECLARE_PMID(kClassIDSpace, kPageItemSpecifierBoss, kPageItemScrapPrefix + 10)
DECLARE_PMID(kClassIDSpace, kPageItemScrapRootBoss, kPageItemScrapPrefix + 11)
DECLARE_PMID(kClassIDSpace, kDuplicateCmdBoss, kPageItemScrapPrefix + 12)
//DECLARE_PMID(kClassIDSpace, kNoPageItemSpecifierBoss, kPageItemScrapPrefix + 13)
DECLARE_PMID(kClassIDSpace, kPageItemScrapDefaultPasteHelperBoss, kPageItemScrapPrefix + 14)

DECLARE_PMID(kClassIDSpace, kPageItemDataExchHandlerDefaultHelperBoss, kPageItemScrapPrefix + 15)
DECLARE_PMID(kClassIDSpace, kPageItemDataExchHandlerPDFHelperBoss, kPageItemScrapPrefix + 16)
DECLARE_PMID(kClassIDSpace, kPageItemDataExchHandlerImporterHelperBoss, kPageItemScrapPrefix + 17)
DECLARE_PMID(kClassIDSpace, kPageItemDataExchHandlerPICTHelperBoss, kPageItemScrapPrefix + 18)
DECLARE_PMID(kClassIDSpace, kFlavoredPointerStreamReadBoss, kPageItemScrapPrefix + 19)


// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_ICOPYCMDDATA, kPageItemScrapPrefix + 1)
//DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEITEMSELECTOR, kPageItemScrapPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEITEMSCRAPDATA, kPageItemScrapPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IDELETECLEANUP, kPageItemScrapPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEITEMLAYERDATA, kPageItemScrapPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEITEMDRAGOFFSET, kPageItemScrapPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IDUPLICATEPREFS, kPageItemScrapPrefix + 7)

// Sherpa
DECLARE_PMID(kInterfaceIDSpace, IID_IPRIVATECOPYCMDDATA, kPageItemScrapPrefix + 8)


DECLARE_PMID(kInterfaceIDSpace, IID_ICOPYDRAGBOOLDATA, kPageItemScrapPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRAPSUITENOVIEWPASTEHELPER, kPageItemScrapPrefix + 10)

// <Implementation ID>
// ImplementationIDs
//DECLARE_PMID(kImplementationIDSpace, kPageItemSelectorImpl, kPageItemScrapPrefix + 1)
//DECLARE_PMID(kImplementationIDSpace, kPageItemScrapSuiteImpl, kPageItemScrapPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kPageItemScrapDataImpl, kPageItemScrapPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kPageItemScrapHandlerImpl, kPageItemScrapPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kDeleteCmdImpl, kPageItemScrapPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kCopyCmdImpl, kPageItemScrapPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kCopyCmdDataImpl, kPageItemScrapPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kPasteCmdImpl, kPageItemScrapPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kPasteInsideCmdImpl, kPageItemScrapPrefix + 9	)
DECLARE_PMID(kImplementationIDSpace, kCopyPageItemCmdImpl, kPageItemScrapPrefix + 10	)
DECLARE_PMID(kImplementationIDSpace, kDeletePageItemCmdImpl, kPageItemScrapPrefix + 11	)
DECLARE_PMID(kImplementationIDSpace, kDeleteInsideCmdImpl, kPageItemScrapPrefix + 12	)
DECLARE_PMID(kImplementationIDSpace, kCopyInsideCmdImpl, kPageItemScrapPrefix + 13	)
DECLARE_PMID(kImplementationIDSpace, kDuplicateCmdImpl, kPageItemScrapPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kDeleteCleanupProviderImpl, kPageItemScrapPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kPageItemLayerDataImpl, kPageItemScrapPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kPrivateCopyCmdDataImpl, kPageItemScrapPrefix + 17)

DECLARE_PMID(kImplementationIDSpace, kPageItemScrapSuitePasteHelperProviderImpl, kPageItemScrapPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kPageItemScrapSuiteDefaultPasteHelperImpl, kPageItemScrapPrefix + 19)

DECLARE_PMID(kImplementationIDSpace, kPageItemDataExchHandlerHelperProviderImpl, kPageItemScrapPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kPageItemDataExchHandlerDefaultHelperImpl, kPageItemScrapPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kPageItemDataExchHandlerPDFHelperImpl, kPageItemScrapPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kPageItemDataExchHandlerImporterHelperImpl, kPageItemScrapPrefix + 23)

DECLARE_PMID(kImplementationIDSpace, kScrapSuiteLayoutCSBImpl, kPageItemScrapPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kPageItemDataExchHandlerPICTHelperImpl, kPageItemScrapPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kDuplicatePrefsImpl, kPageItemScrapPrefix + 26)

DECLARE_PMID(kImplementationIDSpace, kPageItemSSNoViewPasteHelperImpl, kPageItemScrapPrefix + 27)


// <Service ID>
// Service IDs:
DECLARE_PMID(kServiceIDSpace, kDeleteCleanupService, kPageItemScrapPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kPageItemScrapSuitePasteHelperService, kPageItemScrapPrefix +2)
DECLARE_PMID(kServiceIDSpace, kPageItemDataExchHandlerHelperService, kPageItemScrapPrefix +3)


#endif // __PageItemScrapID__




