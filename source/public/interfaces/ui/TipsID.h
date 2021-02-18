//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/TipsID.h $
//  
//  Owner: Craig Hotchkiss
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
//  Contains common IDs used by the Tips plugin.
//  
//========================================================================================

#ifndef __TipsID__
#define __TipsID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kTipsPrefix	RezLong(0x6400)

// <Start IDC>
// PluginID
#define kTipsPluginName 				"Tool Tips"
DECLARE_PMID(kPlugInIDSpace, kTipsPluginID, kTipsPrefix + 1)

// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kHideTipsEventWatcherBoss, kTipsPrefix + 1)
DECLARE_PMID(kClassIDSpace, kTipsConversionProviderBoss, kTipsPrefix + 2)
//gap
//gap
DECLARE_PMID(kClassIDSpace, kTipsStartupShutdownBoss, kTipsPrefix + 7)
//gap
DECLARE_PMID(kClassIDSpace, kTipsInitializerBoss, kTipsPrefix + 9)

// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_ITIP, kTipsPrefix + 1)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_ITIPMANAGER, kTipsPrefix + 4 )
DECLARE_PMID(kInterfaceIDSpace, IID_ITIPREGISTER, kTipsPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IALTLAYOUTTIP, kTipsPrefix + 8)

// <Implementation ID>
// Implementation IDs
DECLARE_PMID(kImplementationIDSpace, kHideTipsEventWatcherImpl, kTipsPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kTipsStartupShutdownImpl, kTipsPrefix + 6)
//gap
DECLARE_PMID(kImplementationIDSpace, kToolTipPreferencesImpl_obsolete, kTipsPrefix + 9 )
DECLARE_PMID(kImplementationIDSpace, kTipManagerImpl, kTipsPrefix + 10 )
//gap
DECLARE_PMID(kImplementationIDSpace, kNoToolTipImpl, kTipsPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kLayoutWidgetTipImpl, kTipsPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kCPanelTipImpl, kTipsPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kWidgetTipImpl, kTipsPrefix + 18)
//gap
DECLARE_PMID(kImplementationIDSpace, kTipsInitializerImpl, kTipsPrefix + 24)

// <Service ID>
// Service IDs
DECLARE_PMID(kServiceIDSpace, kTipRegisterService, kTipsPrefix + 1)

#endif // __TipsID__
