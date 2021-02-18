//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/CJKLayoutID.h $
//  
//  Owner: Michiko Jessett
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

#ifndef __CJKLayoutID__
#define __CJKLayoutID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kCJKLayoutPrefix	RezLong(0x5100)

// <Start IDC>
// PluginID
#define kCJKLayoutPluginName 		"CJKLayout"
DECLARE_PMID(kPlugInIDSpace, kCJKLayoutPluginID, kCJKLayoutPrefix + 1)

// <Class ID>
//--------------------------------------------------------------
// class IDs
//--------------------------------------------------------------
//Ha measurement
DECLARE_PMID(kClassIDSpace, kHaBoss, kCJKLayoutPrefix + 1)

//Japanese Page Numbering
DECLARE_PMID(kClassIDSpace, kJapaneseSectionStylesServicesBoss_Obsolete,  kCJKLayoutPrefix + 7)

//Q measurement
DECLARE_PMID(kClassIDSpace, kQBoss, kCJKLayoutPrefix + 15)

//American Points measurement
DECLARE_PMID(kClassIDSpace, kAPBoss, kCJKLayoutPrefix + 17)

//Japanese Newspaper measurements
DECLARE_PMID(kClassIDSpace, kUBoss, kCJKLayoutPrefix + 18)
DECLARE_PMID(kClassIDSpace, kBaiBoss, kCJKLayoutPrefix + 19)
DECLARE_PMID(kClassIDSpace, kMilsBoss, kCJKLayoutPrefix + 20)


#ifdef DEBUG
DECLARE_PMID(kClassIDSpace, kCJKLayoutTestMenuBoss, kCJKLayoutPrefix + 100)
#endif


// <Interface ID>
//--------------------------------------------------------------
// IIDs
//--------------------------------------------------------------



// <Implementation ID>
//--------------------------------------------------------------
// Implementation IDs
//--------------------------------------------------------------
//Ha measurement
DECLARE_PMID(kImplementationIDSpace, kHaImpl, kCJKLayoutPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kHaUnitOfMeasureServiceImpl, kCJKLayoutPrefix + 2)

//Japanese Page Numbering
DECLARE_PMID(kImplementationIDSpace, kJapanesePageNumberConverterImpl_Obsolete, kCJKLayoutPrefix + 22)	// Moved to Section plug-in

//Q measurement
DECLARE_PMID(kImplementationIDSpace, kQImpl, kCJKLayoutPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kQUnitOfMeasureServiceImpl, kCJKLayoutPrefix + 24)

//American Points measurement
DECLARE_PMID(kImplementationIDSpace, kAPImpl, kCJKLayoutPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kAPUnitOfMeasureServiceImpl, kCJKLayoutPrefix + 27)

//Japanese Newspaper measurements
DECLARE_PMID(kImplementationIDSpace, kUImpl, kCJKLayoutPrefix + 28)
//DECLARE_PMID(kImplementationIDSpace, kUUnitOfMeasureServiceImpl, kCJKLayoutPrefix + 29)		// used generic kUnitOfMeasureService instead.
DECLARE_PMID(kImplementationIDSpace, kBaiImpl, kCJKLayoutPrefix + 30)
//DECLARE_PMID(kImplementationIDSpace, kBaiUnitOfMeasureServiceImpl, kCJKLayoutPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kMilsImpl, kCJKLayoutPrefix + 32)
//DECLARE_PMID(kImplementationIDSpace, kMilsUnitOfMeasureServiceImpl, kCJKLayoutPrefix + 33)

#ifdef DEBUG
DECLARE_PMID(kImplementationIDSpace, kCJKLayoutTestMenuImpl, kCJKLayoutPrefix + 100)
#endif

#endif // __CJKLayoutID__
