//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/Word97FilterID.h $
//  
//  Owner: Johnr 
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

#ifndef __Word97FilterID__
#define __Word97FilterID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kWord97FilterPrefix   RezLong(0x46500)

#define kWord97FilterPluginName           "Word 97-98 Import Filter"
DECLARE_PMID(kPlugInIDSpace, kWord97FilterPluginID, kWord97FilterPrefix + 1)

// <Interface ID>
DECLARE_PMID(kInterfaceIDSpace, IID_WORD_PREFERENCES, kWord97FilterPrefix + 2)

// <Class ID>
DECLARE_PMID(kClassIDSpace, kWord97FilterBoss, kWord97FilterPrefix + 1)
DECLARE_PMID(kClassIDSpace, kWord97ImportFilterStringRegisterBoss, kWord97FilterPrefix + 2)
DECLARE_PMID(kClassIDSpace, kWord97PreferencesScriptBoss, kWord97FilterPrefix + 3)
DECLARE_PMID(kClassIDSpace, kWord97PreferencesBoss, kWord97FilterPrefix + 4)
DECLARE_PMID(kClassIDSpace, kWord97ErrorStringServiceBoss, kWord97FilterPrefix + 5)

// <Implementation ID>
DECLARE_PMID(kImplementationIDSpace, kWord97ImportProvider, kWord97FilterPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kWord97ImportFilterStringRegister, kWord97FilterPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kWordPreferencesData, kWord97FilterPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kWord97PreferencesScriptProvider, kWord97FilterPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kWord97ErrorStringServiceImpl, kWord97FilterPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kWord97ScriptImpl, kWord97FilterPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kWord97OLERefCountImpl, kWord97FilterPrefix + 7)

#endif // __Word97FilterID__
