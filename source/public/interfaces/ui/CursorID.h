//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/CursorID.h $
//  
//  Owner: ???
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
//  DragDropID.h - Contains IDs for CursorMgr classes, IIDs, and ImplementationIDs
//  
//  1997 Adobe Corp.
//  
//========================================================================================

#ifndef __CursorID__
#define __CursorID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kCursorPrefix	 									RezLong(0x8000)

// <Start IDC>
// <Class ID>
// ClassIDs
//DECLARE_PMID(kClassIDSpace, kCursorRegionThreadBoss, kShuksanPrefix + 24)				(defined in ShuksanID.h)
DECLARE_PMID(kClassIDSpace, kCursorMgrMouseWatcherBoss, kCursorPrefix + 1)

DECLARE_PMID(kClassIDSpace, kWObscureCursorBoss, kCursorPrefix + 10)


// <Interface ID>
// IIDs
//DECLARE_PMID(kInterfaceIDSpace, IID_ICURSORMGR, kShuksanPrefix + 6)				(defined in ShuksanID.h)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICURSORMGR2, kShuksanPrefix + 113)			(defined in ShuksanID.h)

DECLARE_PMID(kInterfaceIDSpace, IID_ICURSORPROVIDER, kCursorPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ICURSORREGION, kCursorPrefix + 2)

DECLARE_PMID(kInterfaceIDSpace, IID_IARROWCURSORPROVIDER, kCursorPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IIBEAMCURSORPROVIDER, kCursorPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IWFRAMECURSORPROVIDER, kCursorPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IWPLATFORMCURSORPROVIDER, kCursorPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTIONARROWCURSORPROVIDER, kCursorPrefix + 14)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IWINDOWFRAMECURSORPROVIDER, kCursorPrefix + 20)

// <Implementation ID>
// ImplementationIDs
//DECLARE_PMID(kImplementationIDSpace, kCursorMgrImpl, kShuksanPrefix + 67)				(defined in ShuksanID.h)
//DECLARE_PMID(kImplementationIDSpace, kCursorMgrImpl2, kShuksanPrefix + 221)			(defined in ShuksanID.h)
//DECLARE_PMID(kImplementationIDSpace, kCursorRegionThreadImpl, kShuksanPrefix + 179)			(defined in ShuksanID.h)

//gap
DECLARE_PMID(kImplementationIDSpace, kSimpleCursorProviderImpl, kCursorPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kCursorRegionImpl, kCursorPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kPanelCursorRegionImpl, kCursorPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kCursorMgrMouseWatcherImpl, kCursorPrefix + 5)


DECLARE_PMID(kImplementationIDSpace, kCrossHairCursorProviderImpl, kCursorPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kIBeamCursorProviderImpl, kCursorPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kPointerCursorProviderImpl, kCursorPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kWFrameCursorProviderImpl, kCursorPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kWPlatformCursorProviderImpl, kCursorPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kSelectionArrowCursorProviderImpl, kCursorPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kCreationCursorProviderImpl, kCursorPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kWindowFrameCursorProviderImpl, kCursorPrefix + 17)

DECLARE_PMID(kImplementationIDSpace, kWObscureCursorImpl, kCursorPrefix + 20)


#endif

