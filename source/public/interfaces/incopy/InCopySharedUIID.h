//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/InCopySharedUIID.h $
//  
//  Owner: Cindy Chen
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

#ifndef __InCopySharedUIID__
#define __InCopySharedUIID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"
#include "FormatNumber.h"

#define kInCopySharedUIPrefix	 RezLong(0x1d700)	// reserved in AdobePrefix.h

// <PlugInID>
//---------------------------------------------------------------
//	PlugInID
//---------
#define kInCopySharedUIPlugInName					"InCopySharedUI"
DECLARE_PMID(kPlugInIDSpace, kInCopySharedUIPlugInID, kInCopySharedUIPrefix + 1)

// <Class ID>
//---------------------------------------------------------------
//	ClassIDs
//---------------------------------------------------------------

DECLARE_PMID(kClassIDSpace, kUIColorsDDListBoss,			kInCopySharedUIPrefix + 0)
DECLARE_PMID(kClassIDSpace, kUIColorDropDownElementBoss,	kInCopySharedUIPrefix + 1)
DECLARE_PMID(kClassIDSpace, kUIColorSwatchElementBoss,		kInCopySharedUIPrefix + 2)
DECLARE_PMID(kClassIDSpace, kUIColorNameElementBoss,		kInCopySharedUIPrefix + 3)
DECLARE_PMID(kClassIDSpace, kDeletedTextTrackerBoss,		kInCopySharedUIPrefix + 4)
DECLARE_PMID(kClassIDSpace,	kSetUserNameDialogBoss,			kInCopySharedUIPrefix + 5)
DECLARE_PMID(kClassIDSpace, kInCopySharedTestMenuBoss, 		kInCopySharedUIPrefix + 6)
DECLARE_PMID(kClassIDSpace, kUnavailableTextFrameAdornmentBoss, kInCopySharedUIPrefix + 7)
DECLARE_PMID(kClassIDSpace, kUnavailableGraphicFrameAdornmentBoss, kInCopySharedUIPrefix + 8)
DECLARE_PMID(kClassIDSpace, kGalleyDeleteStoryResponderBoss, kInCopySharedUIPrefix + 9)

// <Interface ID>
//---------------------------------------------------------------
//	IIDs
//---------------------------------------------------------------

DECLARE_PMID(kInterfaceIDSpace, IID_IUICOLORDDLIST, 		kInCopySharedUIPrefix + 0)

// <Implementation ID>
//---------------------------------------------------------------
//	ImplementationIDs
//---------------------------------------------------------------

DECLARE_PMID(kImplementationIDSpace, kUIColorDDListImpl,				kInCopySharedUIPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kUIColorSwatchElementViewImpl,		kInCopySharedUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kUIColorNameElementTextDataImpl,	kInCopySharedUIPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kDeletedTextTrackerImpl,			kInCopySharedUIPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kOffscreenScratchPadImpl,			kInCopySharedUIPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kSetUserNameDlgControllerImpl,		kInCopySharedUIPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kInCopySharedTestMenuImpl, 		kInCopySharedUIPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kUnavailableTextFrameAdornmentImpl, 	kInCopySharedUIPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kUnavailableGraphicFrameAdornmentImpl, kInCopySharedUIPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kGalleyDeleteStoryResponderImpl, kInCopySharedUIPrefix + 9)

// <Error ID's>
//---------------------------------------------------------------
//	Error ID's
//---------------------------------------------------------------

// <Message ID>
//---------------------------------------------------------------
//	MessageIDs
//---------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Service Provider IDs
//----------------------------------------------------------------------------------------

// <Widget ID>
//----------------------------------------------------------------------------------------
// Widget identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kWidgetIDSpace,	kSetUserNameDialogId,				kInCopySharedUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace,	kSetUserNameStaticWidgetID,			kInCopySharedUIPrefix + 2)
DECLARE_PMID(kWidgetIDSpace,	kSetUserNameWidgetID,				kInCopySharedUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace,	kUIColorDropDownParentWidgetID,		kInCopySharedUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace,	kUIColorSwatchElementWidgetID,		kInCopySharedUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace,	kUIColorNameElementWidgetID,		kInCopySharedUIPrefix + 6)

// <other #defines>
//---------------------------------------------------------------
//	other #defines
//---------------------------------------------------------------

#define kSetUserNameDialogRsrcID				1000
#define kUIColorDropDownElementRsrcID			2000

#endif // __InCopySharedUIID__



