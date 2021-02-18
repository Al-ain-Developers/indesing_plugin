//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/SpreadHistoryID.h $
//  
//  Owner: tdonovan
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
//  Contains IDs used by the Go Forward/Go Back item plug-in
//  
//========================================================================================

#ifndef __SpreadHistoryID__
#define __SpreadHistoryID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kSpreadHistoryPrefix	 RezLong(0x5900)

// <Start IDC>
// PluginID
#define kSpreadHistoryPluginName 			"Spread History"
DECLARE_PMID(kPlugInIDSpace, kSpreadHistoryPluginID, kSpreadHistoryPrefix + 1)

// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kSpreadHistoryMenuActionBoss, kSpreadHistoryPrefix + 1)
DECLARE_PMID(kClassIDSpace, kSpreadHistoryPlugInBoss, kSpreadHistoryPrefix + 2)
//gap
DECLARE_PMID(kClassIDSpace, kSpreadHistoryLayoutActionBoss, kSpreadHistoryPrefix + 4)

// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_ISPREADHISTORYDATA, kSpreadHistoryPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ISPREADHISTORYFLAGDATA, kSpreadHistoryPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTCONTROLDATAOBSERVER, kSpreadHistoryPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IHISTLAYOUTSPREADLISTOBSERVER, kSpreadHistoryPrefix + 4)

// <Implementation ID>
// ImplementationIDs
DECLARE_PMID(kImplementationIDSpace, kSpreadHistoryDataImpl, kSpreadHistoryPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kSpreadHistoryFlagDataImpl, kSpreadHistoryPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kSpreadHistoryMenuActionImpl, kSpreadHistoryPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kCSpreadHistoryObserverImpl, kSpreadHistoryPrefix + 4)
//gap
DECLARE_PMID(kImplementationIDSpace, kSpreadHistoryLayoutActionImpl, kSpreadHistoryPrefix + 6)

// <Action ID>
// ActionIDs
DECLARE_PMID(kActionIDSpace, kSpreadHistorySepActionID, kSpreadHistoryPrefix + 1)
DECLARE_PMID(kActionIDSpace, kGoBackActionID, kSpreadHistoryPrefix + 2)
DECLARE_PMID(kActionIDSpace, kGoForwardActionID, kSpreadHistoryPrefix + 3)

#endif // __SpreadHistoryID__




