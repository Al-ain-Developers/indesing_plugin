//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/RtfFilterID.h $
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

#ifndef __RtfFilterID__
#define __RtfFilterID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kRtfFilterPrefix   RezLong(0x46900)

// PluginID
#define kRtfFilterPluginName     "RTF Import Filter"
DECLARE_PMID(kPlugInIDSpace, kRtfFilterPluginID, kRtfFilterPrefix + 1)

// <Class ID>
DECLARE_PMID(kClassIDSpace, kRtfFilterBoss, kRtfFilterPrefix + 1)
DECLARE_PMID(kClassIDSpace, kRtfImportFilterStringRegisterBoss, kRtfFilterPrefix + 2)
DECLARE_PMID(kClassIDSpace, kRtfPreferencesScriptBoss, kRtfFilterPrefix + 3)
DECLARE_PMID(kClassIDSpace, kRtfPreferencesBoss, kRtfFilterPrefix + 4)
DECLARE_PMID(kClassIDSpace, kRtfErrorStringServiceBoss, kRtfFilterPrefix + 5)


// <Implementation ID>
DECLARE_PMID(kImplementationIDSpace, kRtfImportProvider, kRtfFilterPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kRtfImportFilterStringRegister, kRtfFilterPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kRtfPreferencesData, kRtfFilterPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kRtfPreferencesScriptProvider, kRtfFilterPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kRtfErrorStringServiceImpl, kRtfFilterPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kRtfScriptImpl, kRtfFilterPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kRtfOLERefCountImpl, kRtfFilterPrefix + 7)


// <Interface ID>
DECLARE_PMID(kInterfaceIDSpace, IID_RTF_PREFERENCES, kRtfFilterPrefix + 2)

#endif // __RtfFilterID__





/******************************************************************************
 * $Log: /Source/Public/Interfaces/Text/RtfFilterID.h $
 * 
 * 3     11/24/98 5:50p Johnr
 * 2 new impls for OLE automation
 * 
 * 2     10/05/98 4:12p Stellad
 * Changes to move to Build 317
 * 
 * 6     8/04/98 6:46p Sdu
 * After merge /w Build 288 of K2
 * 
 * 10    7/24/98 2:26p Jeffreys
 * Moved Private Data Stuff
 * 
 * 9     7/15/98 5:06p Jeffreys
 * Changed ID Prefixes
 * 
 * 8     7/15/98 2:17p Jeffreys
 * Changing Prefix ID's
 * 
 * 7     7/15/98 2:07p Jeffreys
 * Private Data Stuff
 * 
 * 6     7/06/98 7:16p Stellad
 * Added in the IDs necessary for the ErrorStringService
 * 
 * 5     7/02/98 1:15p Jeffreys
 * RTF Dialog
 * 
 * 4     6/30/98 5:20p Jeffreys
 * Reorganization of RTF/Word Plugins
 * 
 * 3     4/09/98 1:41p Craigm
 * Merged with K2 source for build 218 (dated March 30, 1998).
 * 
 * 2     3/30/98 8:56a Davids
 * Added Paradigm-standard headers and footers where missing, untabified.
 * 
 * 1     3/11/98 4:56p Davids
 * First cut.
 * 
 * 1     3/06/98 3:50p Davids
 * First cut
 * 
 * 1     3/04/98 4:26p Craigm
 * Word 97 import filter plug in resource IDs.
 *****************************************************************************/




