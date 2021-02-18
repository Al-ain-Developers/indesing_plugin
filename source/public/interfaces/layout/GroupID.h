//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/GroupID.h $
//  
//  Owner: Robin_Briggs
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
//  Contains IDs used by the group item plug-in
//  
//========================================================================================

#ifndef __GroupID__
#define __GroupID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kGroupPrefix	 RezLong(0x400)

// <Start IDC>
// PluginID
#define kGroupPluginName			"Group"
DECLARE_PMID(kPlugInIDSpace, kGroupPluginID, kGroupPrefix + 1)

// Conversion
// For pub conversion constants see GroupConversionID.h

// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kGroupItemBoss, kGroupPrefix + 1)
//gap
DECLARE_PMID(kClassIDSpace, kUngroupCmdBoss, kGroupPrefix + 4)
DECLARE_PMID(kClassIDSpace, kGroupCmdBoss, kGroupPrefix + 5)
DECLARE_PMID(kClassIDSpace, kGroupConversionProviderBoss, kGroupPrefix + 6)
DECLARE_PMID(kClassIDSpace, kGroupM2MListenerServiceBoss, kGroupPrefix + 7)
// gap
DECLARE_PMID(kClassIDSpace, kTransformGroupContentsCmdBoss, kGroupPrefix + 14)

// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IGROUPCMDDATA, kGroupPrefix + 1 )

// <Implementation ID>
// ImplementationIIDs
DECLARE_PMID(kImplementationIDSpace, kGroupPageItemImpl, kGroupPrefix + 1 )
DECLARE_PMID(kImplementationIDSpace, kGeometryGroupImpl, kGroupPrefix + 2 )
DECLARE_PMID(kImplementationIDSpace, kCGroupFillImpl_obsolete, kGroupPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kCGroupStrokeImpl_obsolete, kGroupPrefix + 4 )
DECLARE_PMID(kImplementationIDSpace, kGroupShapeImpl, kGroupPrefix + 5 )
DECLARE_PMID(kImplementationIDSpace, kUngroupCmdImpl, kGroupPrefix + 9 )
DECLARE_PMID(kImplementationIDSpace, kGroupCmdImpl, kGroupPrefix + 10 )
DECLARE_PMID(kImplementationIDSpace, kGroupCmdDataImpl, kGroupPrefix + 11 )
DECLARE_PMID(kImplementationIDSpace, kGroupTransformImpl, kGroupPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kGroupToPolygonImpl, kGroupPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kGroupVisitorHelperImpl, kGroupPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kTransformGroupContentsCmdImpl, kGroupPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kGroupPlaceBehaviorImpl, kGroupPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kGroupM2MListenerImpl, kGroupPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kGroupNameImpl, kGroupPrefix + 24)

// <Widget ID>
// WidgetID

// <Global ID>
// ActionID

#endif // __GroupID__
