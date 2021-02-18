//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/KnowledgeBaseID.h $
//  
//  Owner: Rich Gartland
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
//  Contains IDs used by the knowledge base plug-in
//  
//========================================================================================

#ifndef __CKnowledgeBaseID__
#define __CKnowledgeBaseID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kKnowledgeBasePrefix	 RezLong(0x5700) 

// <Start IDC>
// PluginID
#define kKnowledgeBasePluginName 			"Knowledge Base"
DECLARE_PMID(kPlugInIDSpace, kKnowledgeBasePluginID, kKnowledgeBasePrefix + 1)


// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kKnowledgeBaseBoss, kKnowledgeBasePrefix + 1)
DECLARE_PMID(kClassIDSpace, kCLIPSKnowledgeBaseBoss, kKnowledgeBasePrefix + 2)

// <Interface ID>
// Interface IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IKNOWLEDGEBASE, kKnowledgeBasePrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IRULEABLE, kKnowledgeBasePrefix + 2)

// <Implementation ID>
// ImplementationIDs
DECLARE_PMID(kImplementationIDSpace, kKnowledgeBaseImpl, kKnowledgeBasePrefix + 1 )
DECLARE_PMID(kImplementationIDSpace, kCLIPSKnowledgeBaseImpl, kKnowledgeBasePrefix + 2 )

// <Error ID>
// Error Code IDs
DECLARE_PMID(kErrorIDSpace, kKnowledgeRuleBaseLoadError, kKnowledgeBasePrefix + 1)
DECLARE_PMID(kErrorIDSpace, kKnowledgeRuleBaseCommError, kKnowledgeBasePrefix + 2)
DECLARE_PMID(kErrorIDSpace, kKnowledgeRuleBaseRunError, kKnowledgeBasePrefix + 3)
DECLARE_PMID(kErrorIDSpace, kKnowledgeBaseUnknownError, kKnowledgeBasePrefix + 4)


#endif // __KnowledgeBaseID__








