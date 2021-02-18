//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/LayoutID.h $
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
//  Contains IDs used by the Layout Widget plug-in
//  
//========================================================================================

#ifndef __LAYOUTID__
#define __LAYOUTID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kLayoutPrefix	 RezLong(0x800)

// <Start IDC>
// PluginID
#define kLayoutPluginName 				"Layout"
DECLARE_PMID(kPlugInIDSpace, kLayoutPluginID, kLayoutPrefix + 1)

// <Class ID>
// ClassIDs

DECLARE_PMID(kClassIDSpace, kSetRulerPrefsCmdBoss, kLayoutPrefix + 1)
DECLARE_PMID(kClassIDSpace, kSetRulerCoordPrefsCmdBoss, kLayoutPrefix + 2)

DECLARE_PMID(kClassIDSpace, kLayoutConversionProviderBoss, kLayoutPrefix + 3)

DECLARE_PMID(kClassIDSpace, kSetPatientUserPrefsCmdBoss, kLayoutPrefix + 9)

// ---- Moved from the Generic Page Item plug-in
DECLARE_PMID(kClassIDSpace, kLayoutSelectionServiceBoss, kLayoutPrefix + 10)
// ---- end move.

//DECLARE_PMID(kClassIDSpace, kPageThumbnailIdleTaskBoss, kLayoutPrefix + 20)

// -- these are not really classes! just messages!
// <Message ID>
// Message IDs (start at 200)

// <Interface ID>
// IIDs

DECLARE_PMID(kInterfaceIDSpace, IID_IRULERPREFERENCES, kLayoutPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IRULERPREFSCMDDATA, kLayoutPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IRULERCOORDINATEPREFERENCES, kLayoutPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IRULERCOORDPREFSCMDDATA, kLayoutPrefix + 4)

DECLARE_PMID(kInterfaceIDSpace, IID_IPATHSELECTIONLIST, kLayoutPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IPATIENTUSERPREFSCMDDATA, kLayoutPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_IDEFAULTREFPOINTPOSITION, kLayoutPrefix + 29)
//DECLARE_PMID(kInterfaceIDSpace, IID_IGEOMETRYSUITE_OLD, kLayoutPrefix + 44)
//DECLARE_PMID(kInterfaceIDSpace, IID_ITRANSFORMSUITE_OLD, kLayoutPrefix + 45)
//DECLARE_PMID(kInterfaceIDSpace, IID_IBOUNDSCONSTRAINTSUITE, kLayoutPrefix + 47)
DECLARE_PMID(kInterfaceIDSpace, IID_IBOUNDSDATA, kLayoutPrefix + 48)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTUTILS, kLayoutPrefix + 50)
//DECLARE_PMID(kInterfaceIDSpace, IID_IPATHINFO, kLayoutPrefix + 51)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREVIEWPREFS, kLayoutPrefix + 55)
DECLARE_PMID(kInterfaceIDSpace, IID_IPATIENTUSERPREFERENCE, kLayoutPrefix + 62)
//DECLARE_PMID(kInterfaceIDSpace, IID_MYFANCYNEWIID, kLayoutPrefix + 63)

DECLARE_PMID(kInterfaceIDSpace, IID_IPAGETHUMBNAIL_QUEUE, kLayoutPrefix + 70)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGETHUMBNAIL_DOCOBSERVER, kLayoutPrefix + 71)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGETHUMBNAIL_IDLETASK, kLayoutPrefix + 72)
DECLARE_PMID(kInterfaceIDSpace, IID_IARRANGEFACADE, kLayoutPrefix + 73)
#ifdef DRAW_COLORIZED_TEXT_HIGHLIGHT
DECLARE_PMID(kInterfaceIDSpace, IID_ISHOWTEXTHIGHLIGHTDATA, kLayoutPrefix + 74)
#endif
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGETHUMBNAIL_ASYNC_TASK_MGR, kLayoutPrefix + 75)

// <Implementation ID>
// Implementation IIDs

DECLARE_PMID(kImplementationIDSpace, kCRulerPrefsImpl, kLayoutPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kSessionRulerPrefsImpl, kLayoutPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kDocRulerPrefsImpl, kLayoutPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kSetRulerPrefsCmdImpl, kLayoutPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kRulerPrefsCmdDataImpl, kLayoutPrefix + 5)

DECLARE_PMID(kImplementationIDSpace, kCRulerCoordinatePrefsImpl, kLayoutPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kSessionRulerCoordinatePrefsImpl, kLayoutPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kDocRulerCoordinatePrefsImpl, kLayoutPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kSetRulerCoordPrefsCmdImpl, kLayoutPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kRulerCoordPrefsCmdDataImpl, kLayoutPrefix + 10)

DECLARE_PMID(kImplementationIDSpace, kSetPatientUserPrefsCmdImpl, kLayoutPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kPatientUserPrefsCmdDataImpl, kLayoutPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kDefaultRefPointPersIntDataImpl, kLayoutPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kPatientUserPreferenceImpl, kLayoutPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kCPreviewPrefsImpl, kLayoutPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kSessionPreviewPrefsImpl, kLayoutPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kDocPreviewPrefsImpl, kLayoutPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kLayoutUtilsImpl, kLayoutPrefix + 134)

DECLARE_PMID(kImplementationIDSpace, kPreviewOptionalDrawPassImpl, kLayoutPrefix + 61)


// ---- Moved from the Generic Page Item plug-in
DECLARE_PMID(kImplementationIDSpace, kLayoutUniformTargetFactoryImpl, kLayoutPrefix + 135)
// ---- end move.

DECLARE_PMID(kImplementationIDSpace, kLayoutPathInfoImpl, kLayoutPrefix + 136)
DECLARE_PMID(kImplementationIDSpace, kArrangeSuiteLayoutCSBImpl, kLayoutPrefix + 137 )
DECLARE_PMID(kImplementationIDSpace, kConvertShapeSuiteLayoutCSBImpl, kLayoutPrefix + 138 )

DECLARE_PMID(kImplementationIDSpace, kPageThumbnailIdleTaskImpl, kLayoutPrefix + 150 )
DECLARE_PMID(kImplementationIDSpace, kPageThumbnailQueueImpl, kLayoutPrefix + 151 )
DECLARE_PMID(kImplementationIDSpace, kPageThumbnailDocObserverImpl, kLayoutPrefix + 152 )
DECLARE_PMID(kImplementationIDSpace, kArrangeFacadeImpl, kLayoutPrefix + 153)
DECLARE_PMID(kImplementationIDSpace, kPageThumbAsyncTaskMgrImpl, kLayoutPrefix + 154)

// <Service ID>
// Service Providers

// <Widget ID>
// Widget IDs

// <Action ID>
// Action IDs

//---------------------------------------------------
// InvalHandlerTypeID
//---------------------------------------------------
DECLARE_PMID(kInvalHandlerIDSpace, kLayoutStateInvalHandlerID,	kLayoutPrefix + 1)
DECLARE_PMID(kInvalHandlerIDSpace, kScreenInvalHandlerID,		kLayoutPrefix + 2)
DECLARE_PMID(kInvalHandlerIDSpace, kDVScreenInvalHandlerID,		kLayoutPrefix + 3)
#endif // __LayoutID__
