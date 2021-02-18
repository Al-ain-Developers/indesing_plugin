//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/TextEditorModelID.h $
//  
//  Owner: Bernd Paradies
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

#ifndef __TextEditorModelID__
#define __TextEditorModelID__

#ifndef MAC_RESOURCE_INCLUDER
	#include "CrossPlatformTypes.h"
	#include "IDFactory.h"
#endif

#define kTextEditorModelPrefix	RezLong(0x1900)

// <Start IDC>
// PluginID
#define kTextEditorModelPluginName 	"Text Editor Model"

// <Plug-in ID>
//---------------------------------------------------------------
// Plug-in IDs
//---------------------------------------------------------------

DECLARE_PMID(kPlugInIDSpace, kTextEditorModelPluginID, kTextEditorModelPrefix + 1)

// <Service ID>
//---------------------------------------------------------------
// Service IDs
//---------------------------------------------------------------

// <Class ID>
//---------------------------------------------------------------
// Boss IDs
//---------------------------------------------------------------

DECLARE_PMID(kClassIDSpace, kFillFrameListCmdBoss, kTextEditorModelPrefix + 6)
DECLARE_PMID(kClassIDSpace, kSetTextToolBehaviorCmdBoss, kTextEditorModelPrefix + 38)
DECLARE_PMID(kClassIDSpace, kSetClickPrefsCmdBoss, kTextEditorModelPrefix + 39)
DECLARE_PMID(kClassIDSpace, kTextEditorModelErrorStringServiceBoss, kTextEditorModelPrefix + 40)

// <Interface ID>
//---------------------------------------------------------------
// Interface IDs
//---------------------------------------------------------------

DECLARE_PMID(kInterfaceIDSpace, IID_ISETTEXTTOOLBEHAVIORCMDDATA, kTextEditorModelPrefix + 16 )
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTCLICKBEHAVIOR, kTextEditorModelPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTMISCELLANYSUITE, kTextEditorModelPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTCARETPOSITIONDATA, kTextEditorModelPrefix + 19 )
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTPREFERENCESFACADE, kTextEditorModelPrefix + 20 )
DECLARE_PMID(kInterfaceIDSpace, IID_IAUTOFRAMEUTILS, kTextEditorModelPrefix + 21 )


// <Implementation ID>

DECLARE_PMID(kImplementationIDSpace, kFillFrameListCmdImpl, kTextEditorModelPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kTextCaretPositionDataImpl, kTextEditorModelPrefix + 5)
// DECLARE_PMID(kImplementationIDSpace, kFillFrameSubCmdImpl, kTextEditorModelPrefix + 50)
// DECLARE_PMID(kImplementationIDSpace, kPreventCompositionImpl_Obsolete, kTextEditorModelPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kTextClickBehaviorImpl, kTextEditorModelPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kSetClickPrefsCmdImpl, kTextEditorModelPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kSetTextToolBehaviorCmdImpl, kTextEditorModelPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kSetTextToolBehaviorCmdDataImpl, kTextEditorModelPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kTextMiscellanySuiteASBImpl, kTextEditorModelPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kTextMiscellanySuiteLayoutCSBImpl, kTextEditorModelPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kTextMiscellanySuiteTextCSBImpl, kTextEditorModelPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kTextEditorModelErrorStringServiceImpl, kTextEditorModelPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kTextPreferencesFacadeImpl, kTextEditorModelPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kAutoFrameUtilsImpl, kTextEditorModelPrefix + 88)

// <Error ID>
DECLARE_PMID(kErrorIDSpace, kCantDragDeletedTextError,		kTextEditorModelPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kCantDropIntoDeletedTextError,	kTextEditorModelPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kCantDragFootnoteMarkerError,	kTextEditorModelPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kCantDragILGMarkerError,		kTextEditorModelPrefix + 4)
DECLARE_PMID(kErrorIDSpace, kCantDragTableMarkerError,		kTextEditorModelPrefix + 5)
DECLARE_PMID(kErrorIDSpace, kCantDragNoteMarkerError,		kTextEditorModelPrefix + 6)

// <Widget ID>

// <Action ID>

#endif
