//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/incopyfileactions/InCopyFileActionsID.h $
//  
//  Owner: Chris Parrish
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

#ifndef __InCopyFileActionsID__
#define __InCopyFileActionsID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kInCopyFileActionsPrefix			RezLong(0x17200)

//----------------------------------------------------------------------------------------
// Plug-in identifier
//----------------------------------------------------------------------------------------

#define kInCopyFileActionsPluginName 	"InCopyFileActions"
DECLARE_PMID(kPlugInIDSpace, kInCopyFileActionsPluginID, kInCopyFileActionsPrefix + 1)

//----------------------------------------------------------------------------------------
// Class identifiers
//----------------------------------------------------------------------------------------

//gap
DECLARE_PMID(kClassIDSpace,		kFileActionsOpenDocResponderBoss,		kInCopyFileActionsPrefix + 1)
//gap
DECLARE_PMID(kClassIDSpace,		kInCopyDocDetectContentHandlerBoss,		kInCopyFileActionsPrefix + 3)
//gap
DECLARE_PMID(kClassIDSpace,		kInCopyDocFileHandlerBoss,				kInCopyFileActionsPrefix + 12)
//DECLARE_PMID(kClassIDSpace,		kInCopyMRUListBoss,						kInCopyFileActionsPrefix + 13)
//DECLARE_PMID(kClassIDSpace,		kInCopySaveStoryCmdBoss,				kInCopyFileActionsPrefix + 14)
//DECLARE_PMID(kClassIDSpace,		kInCopyRevertStoryCmdBoss,				kInCopyFileActionsPrefix + 15)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 16)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 17)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 18)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 19)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 20)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 21)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 22)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 23)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 24)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 25)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 26)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 27)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 28)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 29)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 30)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 31)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 32)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 33)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 34)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 35)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 36)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 37)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 38)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 39)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 40)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 41)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 42)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 43)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 44)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 45)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 46)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 47)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 48)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 49)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 50)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 51)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 52)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 53)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 54)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 55)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 56)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 57)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 58)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 59)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 60)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 61)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 62)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 63)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 64)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 65)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 66)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 67)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 68)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 69)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 70)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 71)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 72)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 73)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 74)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 75)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 76)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 77)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 78)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 79)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 80)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 81)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 82)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 83)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 84)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 85)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 86)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 87)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 88)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 89)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 90)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 91)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 92)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 93)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 94)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 95)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 96)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 97)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 98)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 99)
//DECLARE_PMID(kClassIDSpace,		kFutureInCopyFileActionsBoss,	kInCopyFileActionsPrefix + 100)



//----------------------------------------------------------------------------------------
// Interface identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kInterfaceIDSpace,		IID_IDOCDETECTFILETYPEFOUND,	kInCopyFileActionsPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace,		IID_IDOCDETECTISINCOPYFILE,		kInCopyFileActionsPrefix + 2)
//DECLARE_PMID(kInterfaceIDSpace,		IID_IFUTUREINTERFACE,	kInCopyFileActionsPrefix + 3)
//DECLARE_PMID(kInterfaceIDSpace,		IID_IFUTUREINTERFACE,	kInCopyFileActionsPrefix + 4)
//DECLARE_PMID(kInterfaceIDSpace,		IID_IFUTUREINTERFACE,	kInCopyFileActionsPrefix + 5)
//DECLARE_PMID(kInterfaceIDSpace,		IID_IFUTUREINTERFACE,	kInCopyFileActionsPrefix + 6)
//DECLARE_PMID(kInterfaceIDSpace,		IID_IFUTUREINTERFACE,	kInCopyFileActionsPrefix + 7)
//DECLARE_PMID(kInterfaceIDSpace,		IID_IFUTUREINTERFACE,	kInCopyFileActionsPrefix + 8)
//DECLARE_PMID(kInterfaceIDSpace,		IID_IFUTUREINTERFACE,	kInCopyFileActionsPrefix + 9)
//DECLARE_PMID(kInterfaceIDSpace,		IID_IFUTUREINTERFACE,	kInCopyFileActionsPrefix + 10)
//DECLARE_PMID(kInterfaceIDSpace,		IID_IFUTUREINTERFACE,	kInCopyFileActionsPrefix + 11)
//DECLARE_PMID(kInterfaceIDSpace,		IID_IFUTUREINTERFACE,	kInCopyFileActionsPrefix + 12)
//DECLARE_PMID(kInterfaceIDSpace,		IID_IFUTUREINTERFACE,	kInCopyFileActionsPrefix + 13)
//DECLARE_PMID(kInterfaceIDSpace,		IID_IFUTUREINTERFACE,	kInCopyFileActionsPrefix + 14)
//DECLARE_PMID(kInterfaceIDSpace,		IID_IFUTUREINTERFACE,	kInCopyFileActionsPrefix + 15)
//DECLARE_PMID(kInterfaceIDSpace,		IID_IFUTUREINTERFACE,	kInCopyFileActionsPrefix + 16)
//DECLARE_PMID(kInterfaceIDSpace,		IID_IFUTUREINTERFACE,	kInCopyFileActionsPrefix + 17)
//DECLARE_PMID(kInterfaceIDSpace,		IID_IFUTUREINTERFACE,	kInCopyFileActionsPrefix + 18)
//DECLARE_PMID(kInterfaceIDSpace,		IID_IFUTUREINTERFACE,	kInCopyFileActionsPrefix + 19)
//DECLARE_PMID(kInterfaceIDSpace,		IID_IFUTUREINTERFACE,	kInCopyFileActionsPrefix + 20)


//----------------------------------------------------------------------------------------
// Implementation identifiers
//----------------------------------------------------------------------------------------

//gap
DECLARE_PMID(kImplementationIDSpace,		kFileActionsOpenDocResponderImpl,	kInCopyFileActionsPrefix + 2)
DECLARE_PMID(kImplementationIDSpace,		kInCopyDocUtilsImpl,				kInCopyFileActionsPrefix + 3)
DECLARE_PMID(kImplementationIDSpace,		kInCopyDocDetectContentHandlerImpl,	kInCopyFileActionsPrefix + 4)
DECLARE_PMID(kImplementationIDSpace,		kDocDetectFileTypeFoundImpl,		kInCopyFileActionsPrefix + 5)
DECLARE_PMID(kImplementationIDSpace,		kDocDetectIsInCopyFileImpl,			kInCopyFileActionsPrefix + 6)
DECLARE_PMID(kImplementationIDSpace,		kInCopyDocFileHandlerImpl,			kInCopyFileActionsPrefix + 10)
//GAP
//GAP
//GAP
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 17)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 18)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 19)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 20)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 21)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 22)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 23)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 24)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 25)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 26)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 27)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 28)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 29)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 30)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 31)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 32)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 33)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 34)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 35)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 36)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 37)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 38)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 39)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 40)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 41)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 42)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 43)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 44)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 45)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 46)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 47)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 48)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 49)
//DECLARE_PMID(kImplementationIDSpace,		kFutureImplementationID,	kInCopyFileActionsPrefix + 50)


//----------------------------------------------------------------------------------------
// Widget identifiers
//----------------------------------------------------------------------------------------
//DECLARE_PMID(kWidgetIDSpace,	kInCopyUserDialogId,			kInCopyFileActionsPrefix + 1)	// moved to Username
//DECLARE_PMID(kWidgetIDSpace,	kInCopyUserNameStaticWidgetID,	kInCopyFileActionsPrefix + 2)	// moved to Username
//DECLARE_PMID(kWidgetIDSpace,	kInCopyUserNameWidgetID,		kInCopyFileActionsPrefix + 3)	// moved to Username
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 4)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 5)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 6)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 7)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 8)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 9)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 10)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 11)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 12)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 13)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 14)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 15)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 16)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 17)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 18)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 19)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 20)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 21)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 22)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 23)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 24)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 25)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 26)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 27)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 28)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 29)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 30)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 31)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 32)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 33)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 34)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 35)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 36)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 37)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 38)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 39)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 40)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 41)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 42)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 43)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 44)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 45)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 46)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 47)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 48)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 49)
//DECLARE_PMID(kWidgetIDSpace,		kFutureWidgetID,	kInCopyFileActionsPrefix + 50)


//----------------------------------------------------------------------------------------
// Action identifiers
//----------------------------------------------------------------------------------------

//DECLARE_PMID(kActionIDSpace,		kUpdateDesignActionID,		kInCopyFileActionsPrefix + 1)
//DECLARE_PMID(kActionIDSpace,		kSaveOldActionID,			kInCopyFileActionsPrefix + 2)
//DECLARE_PMID(kActionIDSpace,		kUserActionID,				kInCopyFileActionsPrefix + 3)	// moved to Username
//DECLARE_PMID(kActionIDSpace,		kUserSepActionID,			kInCopyFileActionsPrefix + 4)	// moved to Username
//DECLARE_PMID(kActionIDSpace,		kFutureActionID,			kInCopyFileActionsPrefix + 5)
//DECLARE_PMID(kActionIDSpace,		kFutureActionID,			kInCopyFileActionsPrefix + 6)
//DECLARE_PMID(kActionIDSpace,		kFutureActionID,			kInCopyFileActionsPrefix + 7)
//DECLARE_PMID(kActionIDSpace,		kRevertActionID,			kInCopyFileActionsPrefix + 8)
//DECLARE_PMID(kActionIDSpace,		kFutureActionID,			kInCopyFileActionsPrefix + 9)
//DECLARE_PMID(kActionIDSpace,		kFutureActionID,			kInCopyFileActionsPrefix + 10)
//DECLARE_PMID(kActionIDSpace,		kFutureActionID,			kInCopyFileActionsPrefix + 11)
//DECLARE_PMID(kActionIDSpace,		kFutureActionID,			kInCopyFileActionsPrefix + 12)
//DECLARE_PMID(kActionIDSpace,		kFutureActionID,			kInCopyFileActionsPrefix + 13)
//DECLARE_PMID(kActionIDSpace,		kFutureActionID,			kInCopyFileActionsPrefix + 14)
//DECLARE_PMID(kActionIDSpace,		kFutureActionID,			kInCopyFileActionsPrefix + 15)
//DECLARE_PMID(kActionIDSpace,		kFutureActionID,			kInCopyFileActionsPrefix + 16)
//DECLARE_PMID(kActionIDSpace,		kFutureActionID,			kInCopyFileActionsPrefix + 17)
//DECLARE_PMID(kActionIDSpace,		kFutureActionID,			kInCopyFileActionsPrefix + 18)
//DECLARE_PMID(kActionIDSpace,		kFutureActionID,			kInCopyFileActionsPrefix + 19)
//DECLARE_PMID(kActionIDSpace,		kFutureActionID,			kInCopyFileActionsPrefix + 20)


//----------------------------------------------------------------------------------------
// Servide Provider IDs
//----------------------------------------------------------------------------------------

//DECLARE_PMID(kServiceIDSpace,		kFutureServiceID,	kInCopyFileActionsPrefix + 1)
//DECLARE_PMID(kServiceIDSpace,		kFutureServiceID,	kInCopyFileActionsPrefix + 2)
//DECLARE_PMID(kServiceIDSpace,		kFutureServiceID,	kInCopyFileActionsPrefix + 3)
//DECLARE_PMID(kServiceIDSpace,		kFutureServiceID,	kInCopyFileActionsPrefix + 4)
//DECLARE_PMID(kServiceIDSpace,		kFutureServiceID,	kInCopyFileActionsPrefix + 5)
//DECLARE_PMID(kServiceIDSpace,		kFutureServiceID,	kInCopyFileActionsPrefix + 6)
//DECLARE_PMID(kServiceIDSpace,		kFutureServiceID,	kInCopyFileActionsPrefix + 7)
//DECLARE_PMID(kServiceIDSpace,		kFutureServiceID,	kInCopyFileActionsPrefix + 8)
//DECLARE_PMID(kServiceIDSpace,		kFutureServiceID,	kInCopyFileActionsPrefix + 9)
//DECLARE_PMID(kServiceIDSpace,		kFutureServiceID,	kInCopyFileActionsPrefix + 10)
//DECLARE_PMID(kServiceIDSpace,		kFutureServiceID,	kInCopyFileActionsPrefix + 11)
//DECLARE_PMID(kServiceIDSpace,		kFutureServiceID,	kInCopyFileActionsPrefix + 12)
//DECLARE_PMID(kServiceIDSpace,		kFutureServiceID,	kInCopyFileActionsPrefix + 13)
//DECLARE_PMID(kServiceIDSpace,		kFutureServiceID,	kInCopyFileActionsPrefix + 14)
//DECLARE_PMID(kServiceIDSpace,		kFutureServiceID,	kInCopyFileActionsPrefix + 15)
//DECLARE_PMID(kServiceIDSpace,		kFutureServiceID,	kInCopyFileActionsPrefix + 16)
//DECLARE_PMID(kServiceIDSpace,		kFutureServiceID,	kInCopyFileActionsPrefix + 17)
//DECLARE_PMID(kServiceIDSpace,		kFutureServiceID,	kInCopyFileActionsPrefix + 18)
//DECLARE_PMID(kServiceIDSpace,		kFutureServiceID,	kInCopyFileActionsPrefix + 19)
//DECLARE_PMID(kServiceIDSpace,		kFutureServiceID,	kInCopyFileActionsPrefix + 20)


#endif // __InCopyFileActionsID__
