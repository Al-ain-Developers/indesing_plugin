//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/InCopyCoreUIID.h $
//  
//  Owner: kvanwiel
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

#ifndef __InCopyCoreUIID__
#define __InCopyCoreUIID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kInCopyCoreUIPrefix	 RezLong(0x21200)	// reserved in AdobePrefix.h

//PlugInID
#define kInCopyCoreUIPlugInName				"InCopyCoreUI"
DECLARE_PMID(kPlugInIDSpace, kInCopyCoreUIPlugInID, kInCopyCoreUIPrefix + 1)

// ClassIDs
DECLARE_PMID(kClassIDSpace, kInCopyCoreViewMenuBoss,			kInCopyCoreUIPrefix + 14)
DECLARE_PMID(kClassIDSpace, kInCopyCoreEditMenuBoss,			kInCopyCoreUIPrefix + 20)


// Interface IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_ISTORYXMPINFOSUITE, kInCopyCoreUIPrefix + 21)

// Implementation IIDs
DECLARE_PMID(kImplementationIDSpace, kInCopyCoreViewMenuImpl,			kInCopyCoreUIPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kInCopyCoreEditMenuImpl,			kInCopyCoreUIPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kStoryXMPInfoSuiteASBImpl, kInCopyCoreUIPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kStoryXMPInfoTextSuiteCSBImpl, kInCopyCoreUIPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kStoryXMPInfoXMLSuiteCSBImpl, kInCopyCoreUIPrefix + 42)


// Action IDs
DECLARE_PMID(kActionIDSpace, kHideShowPagePreviewActionID,			kInCopyCoreUIPrefix + 1)
DECLARE_PMID(kActionIDSpace, kInCopyCoreSepActionID,				kInCopyCoreUIPrefix + 2)
DECLARE_PMID(kActionIDSpace, kTransposeActionID,					kInCopyCoreUIPrefix + 3)
DECLARE_PMID(kActionIDSpace, kInCopyCoreSep2ActionID,				kInCopyCoreUIPrefix + 4)
DECLARE_PMID(kActionIDSpace, kInCopyCoreSep3ActionID,				kInCopyCoreUIPrefix + 5)
DECLARE_PMID(kActionIDSpace, kInCopyCoreSep4ActionID,				kInCopyCoreUIPrefix + 6)
DECLARE_PMID(kActionIDSpace, kAddPageActionID,						kInCopyCoreUIPrefix + 7)
#endif	// __InCopyCoreUIID__
