//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/DocumentContextID.h $
//  
//  Owner: Jack Kirstein
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

#ifndef __DocumentContextID__
#define __DocumentContextID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

// <Start IDC>
#define kDocumentContextPrefix	 RezLong(0x2900)

// <Message ID>
	// Draw Messages:
DECLARE_PMID(kMessageIDSpace, kDrawSpreadMessage, kDocumentContextPrefix + 4)
DECLARE_PMID(kMessageIDSpace, kBeginSpreadMessage, kDocumentContextPrefix + 5)
DECLARE_PMID(kMessageIDSpace, kEndSpreadMessage, kDocumentContextPrefix + 6)

DECLARE_PMID(kMessageIDSpace, kDrawSpreadPageMessage, kDocumentContextPrefix + 7)
DECLARE_PMID(kMessageIDSpace, kBeginSpreadPageMessage, kDocumentContextPrefix + 8)
DECLARE_PMID(kMessageIDSpace, kEndSpreadPageMessage, kDocumentContextPrefix + 9)

DECLARE_PMID(kMessageIDSpace, kDrawLayerMessage, kDocumentContextPrefix + 10)
DECLARE_PMID(kMessageIDSpace, kBeginLayerMessage, kDocumentContextPrefix + 11)
DECLARE_PMID(kMessageIDSpace, kEndLayerMessage, kDocumentContextPrefix + 12)

DECLARE_PMID(kMessageIDSpace, kDrawPageMessage, kDocumentContextPrefix + 13)
DECLARE_PMID(kMessageIDSpace, kBeginPageMessage, kDocumentContextPrefix + 14)
DECLARE_PMID(kMessageIDSpace, kEndPageMessage, kDocumentContextPrefix + 15)

DECLARE_PMID(kMessageIDSpace, kDrawGroupMessage, kDocumentContextPrefix + 16)
DECLARE_PMID(kMessageIDSpace, kBeginGroupMessage, kDocumentContextPrefix + 17)
DECLARE_PMID(kMessageIDSpace, kEndGroupMessage, kDocumentContextPrefix + 18)

DECLARE_PMID(kMessageIDSpace, kTextOffscreenCreationMessage, kDocumentContextPrefix + 19)

// GAP 20-21
DECLARE_PMID(kMessageIDSpace, kDrawShapeMessage, kDocumentContextPrefix + 22)
DECLARE_PMID(kMessageIDSpace, kBeginShapeMessage, kDocumentContextPrefix + 23)
DECLARE_PMID(kMessageIDSpace, kEndShapeMessage, kDocumentContextPrefix + 24)

DECLARE_PMID(kMessageIDSpace, kDrawMasterSpreadMessage, kDocumentContextPrefix + 25)
DECLARE_PMID(kMessageIDSpace, kBeginMasterSpreadMessage, kDocumentContextPrefix + 26)
DECLARE_PMID(kMessageIDSpace, kEndMasterSpreadMessage, kDocumentContextPrefix + 27)

DECLARE_PMID(kMessageIDSpace, kDrawMessage, kDocumentContextPrefix + 28)

DECLARE_PMID(kMessageIDSpace, kAbortCheckMessage, kDocumentContextPrefix + 29)
DECLARE_PMID(kMessageIDSpace, kFilterCheckMessage, kDocumentContextPrefix + 30)

	// Hit test Messages:
DECLARE_PMID(kMessageIDSpace, kBeforeSpreadHitTestMessage, kDocumentContextPrefix + 31)
DECLARE_PMID(kMessageIDSpace, kAfterSpreadHitTestMessage, kDocumentContextPrefix + 32)

DECLARE_PMID(kMessageIDSpace, kBeforeLayerHitTestMessage, kDocumentContextPrefix + 33)
DECLARE_PMID(kMessageIDSpace, kAfterLayerHitTestMessage, kDocumentContextPrefix + 34)

	// Inval Messages:
DECLARE_PMID(kMessageIDSpace, kBeforeSpreadInvalMessage, kDocumentContextPrefix + 35)
DECLARE_PMID(kMessageIDSpace, kAfterSpreadInvalMessage, kDocumentContextPrefix + 36)

DECLARE_PMID(kMessageIDSpace, kBeforeLayerInvalMessage, kDocumentContextPrefix + 37)
DECLARE_PMID(kMessageIDSpace, kAfterLayerInvalMessage, kDocumentContextPrefix + 38)

	// Iterate Messages:
DECLARE_PMID(kMessageIDSpace, kIterateMessage, kDocumentContextPrefix + 39)

DECLARE_PMID(kMessageIDSpace, kIterateSpreadMessage, kDocumentContextPrefix + 40)
DECLARE_PMID(kMessageIDSpace, kBeforeSpreadIterateMessage, kDocumentContextPrefix + 41)
DECLARE_PMID(kMessageIDSpace, kAfterSpreadIterateMessage, kDocumentContextPrefix + 42)

DECLARE_PMID(kMessageIDSpace, kIterateLayerMessage, kDocumentContextPrefix + 43)
DECLARE_PMID(kMessageIDSpace, kBeforeLayerIterateMessage, kDocumentContextPrefix + 44)
DECLARE_PMID(kMessageIDSpace, kAfterLayerIterateMessage, kDocumentContextPrefix + 45)

DECLARE_PMID(kMessageIDSpace, kIterateGroupMessage, kDocumentContextPrefix + 46)
DECLARE_PMID(kMessageIDSpace, kBeginGroupIterateMessage, kDocumentContextPrefix + 47)
DECLARE_PMID(kMessageIDSpace, kEndGroupIterateMessage, kDocumentContextPrefix + 48)

DECLARE_PMID(kMessageIDSpace, kIterateHierarchyMessage, kDocumentContextPrefix + 49)
DECLARE_PMID(kMessageIDSpace, kBeginHierarchyIterateMessage, kDocumentContextPrefix + 50)
DECLARE_PMID(kMessageIDSpace, kEndHierarchyIterateMessage, kDocumentContextPrefix + 51)

DECLARE_PMID(kMessageIDSpace, kIterateShapeMessage, kDocumentContextPrefix + 52)
DECLARE_PMID(kMessageIDSpace, kBeginShapeIterateMessage, kDocumentContextPrefix + 53)
DECLARE_PMID(kMessageIDSpace, kEndShapeIterateMessage, kDocumentContextPrefix + 54)

// Text draw messages
DECLARE_PMID(kMessageIDSpace, kBeforeFrameBackground, kDocumentContextPrefix + 55)
DECLARE_PMID(kMessageIDSpace, kBeforeFrameText, kDocumentContextPrefix + 56)
DECLARE_PMID(kMessageIDSpace, kBeforeFrameForeground, kDocumentContextPrefix + 57)
DECLARE_PMID(kMessageIDSpace, kAfterFrameForeground, kDocumentContextPrefix + 58)

// Layout selection messages
DECLARE_PMID(kMessageIDSpace, kBeforeLayoutSelection, kDocumentContextPrefix + 59)
DECLARE_PMID(kMessageIDSpace, kAfterLayoutSelection, kDocumentContextPrefix + 60)
DECLARE_PMID(kMessageIDSpace, kInvalLayoutSelection, kDocumentContextPrefix + 61)
DECLARE_PMID(kMessageIDSpace, kGetBBoxLayoutSelection, kDocumentContextPrefix + 62)
DECLARE_PMID(kMessageIDSpace, kHitTestHandlesLayoutSelection, kDocumentContextPrefix + 63)
DECLARE_PMID(kMessageIDSpace, kHitTestBBoxLayoutSelection, kDocumentContextPrefix + 64)
DECLARE_PMID(kMessageIDSpace, kHitTestItemsLayoutSelection, kDocumentContextPrefix + 65)

DECLARE_PMID(kMessageIDSpace, kIterateFilterCheckMessage, kDocumentContextPrefix + 66)

// These bracket the actual content layers (not page background or guides), and are
// always called even if drawing is interrupted.  Called at the spread gsave level.
DECLARE_PMID(kMessageIDSpace, kBeforeContentMessage, kDocumentContextPrefix + 67)
DECLARE_PMID(kMessageIDSpace, kAfterContentMessage, kDocumentContextPrefix + 68)

// These are called before the first and after the last spread in a window.  The changedBy
// for BeforeFirst is the first visible spread and the changedBy for AfterLast is the last
// visible spread.  The CTM is still the pasteboard coordinate system.
DECLARE_PMID(kMessageIDSpace, kBeforeFirstSpreadDrawMessage, kDocumentContextPrefix + 69)
DECLARE_PMID(kMessageIDSpace, kAfterLastSpreadDrawMessage, kDocumentContextPrefix + 70)

// These events are artificial begin-end contexts used when the spread is not necessarily
// going to be encountered as part of a draw -- e.g., when generating an image of a single
// page item.  By watching for these *or* a spread-begin/end message you should be assured
// that your event handler can properly bracket all artwork.  Note that these should be
// mutually exclusive with spread-level begin/end messages.
DECLARE_PMID(kMessageIDSpace, kBeforePartialSpreadDrawMessage, kDocumentContextPrefix + 71)
DECLARE_PMID(kMessageIDSpace, kAfterPartialSpreadDrawMessage, kDocumentContextPrefix + 72)

// Whenever the flattener is employed it accumulates artwork then dumps out the flattened
// version of that artwork into a destination port.  The destination port will receive
// these events immediately prior to and after the artwork coming from the flattener.
DECLARE_PMID(kMessageIDSpace, kBeforeFlattenerShowPage, kDocumentContextPrefix + 73)
DECLARE_PMID(kMessageIDSpace, kAfterFlattenerShowPage, kDocumentContextPrefix + 74)

// These bracket the graphic frame fill operations, including any fill adornments.
DECLARE_PMID(kMessageIDSpace, kBeginFrameFillDrawMessage, kDocumentContextPrefix + 75)
DECLARE_PMID(kMessageIDSpace, kEndFrameFillDrawMessage, kDocumentContextPrefix + 76)

// These bracket the graphic frame stroke, including any stroke adornments.
DECLARE_PMID(kMessageIDSpace, kBeginFrameStrokeDrawMessage, kDocumentContextPrefix + 77)
DECLARE_PMID(kMessageIDSpace, kEndFrameStrokeDrawMessage, kDocumentContextPrefix + 78)

// These bracket the graphic frame hierarchy.
DECLARE_PMID(kMessageIDSpace, kBeginFrameHierarchyDrawMessage, kDocumentContextPrefix + 79)
DECLARE_PMID(kMessageIDSpace, kEndFrameHierarchyDrawMessage, kDocumentContextPrefix + 80)

DECLARE_PMID(kMessageIDSpace, kDrawShapeAdornmentsMessage, kDocumentContextPrefix + 81)

DECLARE_PMID(kMessageIDSpace, kBeginMasterPageLayerMessage, kDocumentContextPrefix + 82)
DECLARE_PMID(kMessageIDSpace, kEndMasterPageLayerMessage, kDocumentContextPrefix + 83)
DECLARE_PMID(kMessageIDSpace, kBeforeTextSelectionDrawMessage, kDocumentContextPrefix + 84)
DECLARE_PMID(kMessageIDSpace, kAfterTextSelectionDrawMessage, kDocumentContextPrefix + 85)
#endif
