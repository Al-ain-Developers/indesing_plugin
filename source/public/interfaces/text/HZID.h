//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/HZID.h $
//  
//  Owner: Zak_Williamson
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
//  Contains class IDs and IIDs unique to the HZ Text Engine plug-in.
//  
//========================================================================================

#ifndef __HZID__
#define __HZID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kHZPrefix_Obsolete				 RezLong(0x40200)
#define kHZPrefix						 RezLong(0x13800)

// <Start IDC>
// PluginID
#define kKFKerningPluginName 			"Optical Kerning"
DECLARE_PMID(kPlugInIDSpace, kKFKerningPluginID_Obsolete, kHZPrefix_Obsolete + 1)
DECLARE_PMID(kPlugInIDSpace, kKFKerningPluginID, kHZPrefix + 1)




// <Class ID>
// ClassID's

// *** Obsolete IDs based on the obsolete plugin prefix.
DECLARE_PMID(kClassIDSpace, kKFPairKerningBoss_Obsolete, kHZPrefix_Obsolete + 3)
DECLARE_PMID(kClassIDSpace, kKFOpticalSideBearingBoss_Obsolete, kHZPrefix_Obsolete + 4)

DECLARE_PMID(kClassIDSpace, kHZTextEngineBoss, kHZPrefix + 1)
DECLARE_PMID(kClassIDSpace, kHZTextWaxRunBoss, kHZPrefix + 2)
DECLARE_PMID(kClassIDSpace, kKFPairKerningBoss, kHZPrefix + 3)
DECLARE_PMID(kClassIDSpace, kKFOpticalSideBearingBoss, kHZPrefix + 4)
DECLARE_PMID(kClassIDSpace, kHZHyphenationBoss, kHZPrefix + 5)
DECLARE_PMID(kClassIDSpace, kKFKerningBoss, kHZPrefix + 6)
//gap
DECLARE_PMID(kClassIDSpace, kKFKerningConversionBoss, kHZPrefix + 8)


// <Interface ID>
// IID's
DECLARE_PMID(kInterfaceIDSpace, IID_IHZBREAKDATA, kHZPrefix + 1)
//DECLARE_PMID(kInterfaceIDSpace, IID_IUNUSEDIID, kHZPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IKERNINGONTHEFLY, kHZPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IKFSTYLEMAP, kHZPrefix + 4)

// <Implementation ID>
// ImplementationIIDs
DECLARE_PMID(kImplementationIDSpace, kHZTextComposerImpl, kHZPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kHZTextEngineServiceImpl, kHZPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kHZBreakDataImpl, kHZPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kHZHyphenationServiceImpl, kHZPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kHyphenationDictImpl, kHZPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kKFKerningOnTheFlyImpl, kHZPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kKerningOnTheFlyImpl, kHZPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kKFPairKernServiceImpl, kHZPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kkfPairKernDictImpl, kHZPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kKFOpSideBearServiceImpl, kHZPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kkfOpSideBearDictImpl, kHZPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kkfStyleMapImpl, kHZPrefix + 12)


#endif // __HZID__



