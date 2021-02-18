//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/PM65ReaderID.h $
//  
//  Owner: Stellad 
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

#ifndef __PM65FilterID__
#define __PM65FilterID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#include "PubConvIDs.h"



//*****************************************
// PM65 Reader
// This next line defined in PubConvIDs.h
//#define kPM65ReaderPrefix         kPubConvPrefix + 20

// ClassIDs
//#define kPM65ReaderBoss                   // defined in PubConvIDs.h
DECLARE_PMID(kClassIDSpace, kPM65ReaderStringRegisterBoss, kPM65ReaderPrefix + 2)
DECLARE_PMID(kClassIDSpace, kPM65ErrorStringServiceBoss, kPM65ReaderPrefix + 3)
DECLARE_PMID(kClassIDSpace, kPM65SFMServiceBoss, kPM65ReaderPrefix + 4)

// <Interface ID>
//
DECLARE_PMID(kInterfaceIDSpace, IID_ISFMSERVICE, kPM65ReaderPrefix + 1)

// ImplementationIIDs
DECLARE_PMID(kImplementationIDSpace, kPM65ReaderImportProvider, kPM65ReaderPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kPM65PublicationReader, kPM65ReaderPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kPM65ReaderStringRegister, kPM65ReaderPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kPM65ErrorStringServiceImpl, kPM65ReaderPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kSFMService, kPM65ReaderPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kPM65SFMServiceProviderImpl, kPM65ReaderPrefix + 6)

// <Service ID>
// ServiceID's
DECLARE_PMID(kServiceIDSpace, kService_SFM, kPM65ReaderPrefix + 1)

#endif // __PM65FilterID__


/*****************************************************************************
 * $Log: /Dev/Source/Components/Filters/PubConv/Reader/PM65/PM65ReaderID.h $
 * 
 * 3     9/01/98 10:21p Stellad
 * Incorporated error handling
 * 
 * 2     8/05/98 3:43p Marka
 * Error string services implemented
 * 
 * 1     4/02/98 5:18p Williamlin
 * ReaderPM65 initial SourceSafe deposit
 *****************************************************************************/
