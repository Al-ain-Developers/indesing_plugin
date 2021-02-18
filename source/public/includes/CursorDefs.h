//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CursorDefs.h $
//  
//  Owner: Dave Burnard
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

#pragma once
#ifndef __CURSORDEFS__
#define __CURSORDEFS__

// NOTE: CursorIDs should all be less than kSnapToCrsrOffset (5000)
//		 Any snap versions of the cursors are then the same ID + 5000

// Offset from regular CursorID to snapped version (if it exists).
const int32 kSnapToCrsrOffset = 5000;
const int32 kHIDPICrsrOffset = 3000;
const int32 kHIDPI150CrsrOffset = 4000;

const CursorID kCrsrNone_SetByPlatform = 	-3;	// Used on Win for regions where Win sets the cursor
const CursorID kCrsrNone 		= 	-2;
const CursorID kCrsrTool 		= 	-1;
const CursorID kCrsrPointer 	= 	0;
const CursorID kCrsrWatch	 	= 	4;
const CursorID kCrsrAnimatedWait = 	5;
const CursorID kCrsrGrabberHand	= 	270;
const CursorID kCrsrSelectionArrow	= 	271;
const CursorID kCrsrPlaceText	= 	272;
const CursorID kCrsrDragCopy	=	275;
const CursorID kCrsrDrag		=	276;
const CursorID kNorthSouthPointer =	 277;
const CursorID kEastWestPointer =	278;
const CursorID kNESWPointer 	=	279;
const CursorID kNWSEPointer 	=	280;
const CursorID kCrsrPlaceEPS = 282;
const CursorID kCrsrPlaceGraphic = 	283;
const CursorID kCrsrAutoText	= 	285;
const CursorID kCrsrSemiAutoText = 286;
const CursorID kCrsrCrosshair 	= 	287;
const CursorID kCrsrIBeam 		= 	288;			// Used by Public
const CursorID kCrsrRotation	= 	290;
const CursorID kCrsrZoomIn		= 	291;
const CursorID kCrsrZoomOut		= 	292;

// Cursors #s 293-296 appear to be used by inlines
const CursorID kCrsrObjectSelect = 297;
const CursorID kCrsrObjectDirectSelect = 298;
const CursorID kCrsrNoZoom		= 	300;
const CursorID kCrsrLocked 		= 301;
const CursorID kCrsrClosedPath = 302;
const CursorID kCrsrDirectSelect = 303;
const CursorID kCrsrGroupSelect = 304;
const CursorID kCrsrConvertDirection = 307;
const CursorID kCrsrRightMouse = 308;
const CursorID kCrsrItemCreation = 309;
const CursorID kCrsrItemTransform = 310;
const CursorID kCrsrAnchorDirectSelect = 311;
const CursorID kCrsrControlDirectSelect = 312;
const CursorID kCrsrSegmentDirectSelect = 313;
const CursorID kCrsrSelectSelection = 314;

const CursorID kCrsrPlaceTextIntoSemiAuto   = 369;
const CursorID kCrsrOpenHand   = 370;
const CursorID kCrsrClosedHand = 371;
const CursorID kCrsrBadDropTarget = 372;
const CursorID kCrsrClosedHandCopy = 373;
const CursorID kCrsrPlaceBadDropTarget = 377;
const CursorID kCrsrPlaceTextInto = 378;
const CursorID kCrsrPlaceImageInto = 379;
const CursorID kCrsrPlaceEPSInto = 380;
const CursorID kCrsrPlaceVerticalText = 381;
const CursorID kCrsrPlaceVerticalTextInto = 382;
const CursorID kCrsrPlaceVerticalTextAuto = 383;
const CursorID kCrsrLinkFrames = 384;
const CursorID kCrsrUnlinkFrames = 385;
const CursorID kCrsrSplitter = 386;
const CursorID kCrsrPlaceTextIntoAuto = 387;
const CursorID kCrsrPlaceVerticalTextIntoAuto = 388;
const CursorID kCursorLock = 389;
const CursorID kCursorADBE3DButton = 390;

const CursorID kCrsrTOPStartBracket		= 391;
const CursorID kCrsrTOPEndBracket		= 392;
const CursorID kCrsrTOPCenterBracket	= 393;

const CursorID kCrsrSemiAutoVerticalText = 394;
const CursorID kCrsrPlaceVerticalTextIntoSemiAuto = 395;
const CursorID kCrsrVerticalSplitter = 396;

const CursorID kCrsrPlaceTextAutoStop = 397;
const CursorID kCrsrPlaceTextIntoAutoStop = 398;
const CursorID kCrsrPlaceTextAutoStopVertical = 399;
const CursorID kCrsrPlaceTextIntoAutoStopVertical = 400;

const CursorID kAnimCrsrWatch_First = 401;
const CursorID kAnimCrsrWatch_1 = 401;
const CursorID kAnimCrsrWatch_2 = 402;
const CursorID kAnimCrsrWatch_3 = 403;
const CursorID kAnimCrsrWatch_4 = 404;
const CursorID kAnimCrsrWatch_5 = 405;
const CursorID kAnimCrsrWatch_6 = 406;
const CursorID kAnimCrsrWatch_7 = 407;
const CursorID kAnimCrsrWatch_8 = 408;
const CursorID kAnimCrsrWatch_Last = 408;

const CursorID kCrsrDragText			= 410;
const CursorID kCrsrDragCopyText		= 411;
const CursorID kCrsrDragToNewFrame		= 412;
const CursorID kCrsrDragCopyToNewFrame	= 413;
const CursorID kCrsrDragTextLocked		= 414;
const CursorID kCrsrDragTextBadDropTarget = kCrsrPlaceBadDropTarget;	// Reuse this cursor

const CursorID kCrsrDragApplyToStroke	= 415;
const CursorID kCrsrDragApplyToFill		= 416;

const CursorID kCrsrPlaceFileInto		= 417;
const CursorID kCrsrPlaceFile			= 418;

const CursorID kCrsrDragUnformattedText					= 419;
const CursorID kCrsrDragCopyUnformattedText				= 420;
const CursorID kCrsrDragUnformattedTextToNewFrame		= 421;
const CursorID kCrsrDragCopyUnformattedTextToNewFrame	= 422;

const CursorID kCrsrPointyHand			= 423;
const CursorID kCrsrPointyHandCopy		= 424;

const CursorID kCrsrCascadePlace = 	425;
const CursorID kCrsrDropLoadGun = 	426;

const CursorID kCrsrPlaceSnippet = 	427;
const CursorID kCrsrPlaceSnippetOrigLoc = 428;
const CursorID kCrsrClosedHandZoomScroll   = 429;
const CursorID kCrsrLinkVerticalFrames = 432;

// ME
const CursorID kCrsrAutoMEText = 450;
const CursorID kCrsrPlaceMETextIntoAuto = 451;
const CursorID kCrsrSemiAutoMEText = 452;
const CursorID kCrsrPlaceMETextIntoSemiAuto = 453;
const CursorID kCrsrPlaceMEText = 454;
const CursorID kCrsrPlaceMETextInto = 455;
const CursorID kCrsrPlaceMETextAutoStop = 456;
const CursorID kCrsrPlaceMETextIntoAutoStop = 457;
const CursorID kCrsrLinkMEFrames = 458;
const CursorID kCrsrUnlinkMEFrames = 459;
//end ME

const CursorID kCrsrGapToolVertical =	480;
const CursorID kCrsrGapToolHorizontal =	481;
const CursorID kCrsrGapToolNoGap =		482;

const CursorID kCrsrUnlock = 483;
const CursorID kCrsrPageToolNotOverPage = 484;
const CursorID kCrsrMotionPath = 485;
const CursorID kCrsrPageToolOverPage = 486;
const CursorID kCrsrPresentationNext	= 	487;
const CursorID kCrsrPresentationPrevious	= 	488;

const CursorID kCrsrScrub		= 	489;	
const CursorID kCrsrScrubResizeHorz = 490;
const CursorID kCrsrButtonTrigger = 491;

const CursorID kCrsrCircle = 492;

const CursorID kCrsrContentGrabber = 493;
const CursorID kCrsrContentDropper = 494;
const CursorID kCrsrContentDropperAdHoc = 495;
const CursorID kCrsrContentDropperNeedful = 496;

const CursorID kCrsrDummy		= 497;

const CursorID kCrsrDragTablesHover = 498;
const CursorID kCrsrDragTables = 499;
const CursorID kCrsrDragDuplicateTables = 500;

// These CursorIDs match their corresponding cursor but have kSnapToCrsrOffset added.
const CursorID kCrsrPlaceTextSnap			= (kCrsrPlaceText + kSnapToCrsrOffset);
const CursorID kCrsrDragCopySnap			= (kCrsrDragCopy + kSnapToCrsrOffset);
const CursorID kCrsrDragSnap				= (kCrsrDrag + kSnapToCrsrOffset);
const CursorID kNorthSouthPointerSnap		= (kNorthSouthPointer + kSnapToCrsrOffset);
const CursorID kEastWestPointerSnap			= (kEastWestPointer + kSnapToCrsrOffset);
const CursorID kNESWPointerSnap				= (kNESWPointer + kSnapToCrsrOffset);
const CursorID kNWSEPointerSnap				= (kNWSEPointer + kSnapToCrsrOffset);
const CursorID kCrsrPlaceEPSSnap			= (kCrsrPlaceEPS + kSnapToCrsrOffset);
const CursorID kCrsrPlaceGraphicSnap		= (kCrsrPlaceGraphic + kSnapToCrsrOffset);
const CursorID kCrsrAutoTextSnap			= (kCrsrAutoText + kSnapToCrsrOffset);
const CursorID kCrsrSemiAutoTextSnap		= (kCrsrSemiAutoText + kSnapToCrsrOffset);
const CursorID kCrsrCrosshairSnap			= (kCrsrCrosshair + kSnapToCrsrOffset);
const CursorID kCrsrRotationSnap			= (kCrsrRotation + kSnapToCrsrOffset);
const CursorID kCrsrItemCreationSnap		= (kCrsrItemCreation + kSnapToCrsrOffset);
const CursorID kCrsrPlaceVerticalTextSnap	= (kCrsrPlaceVerticalText + kSnapToCrsrOffset);
const CursorID kCrsrPlaceVerticalTextAutoSnap	= (kCrsrPlaceVerticalTextAuto + kSnapToCrsrOffset);
const CursorID kCrsrSemiAutoVerticalTextSnap = (kCrsrSemiAutoVerticalText + kSnapToCrsrOffset);
const CursorID kCrsrPlaceTextAutoStopSnap		= (kCrsrPlaceTextAutoStop + kSnapToCrsrOffset);
const CursorID kCrsrPlaceTextIntoAutoStopSnap	= (kCrsrPlaceTextIntoAutoStop + kSnapToCrsrOffset);
const CursorID kCrsrPlaceTextAutoStopVerticalSnap = (kCrsrPlaceTextAutoStopVertical + kSnapToCrsrOffset);
const CursorID kCrsrPlaceTextIntoAutoStopVerticalSnap = (kCrsrPlaceTextIntoAutoStopVertical + kSnapToCrsrOffset);
const CursorID kCrsrPlaceFileSnap = (kCrsrPlaceFile + kSnapToCrsrOffset);
const CursorID kCrsrCascadePlaceSnap		= (kCrsrCascadePlace + kSnapToCrsrOffset);
const CursorID kCrsrDropLoadGunSnap		= (kCrsrDropLoadGun + kSnapToCrsrOffset);
const CursorID kCrsrPlaceSnippetSnap		= (kCrsrPlaceSnippet + kSnapToCrsrOffset);
const CursorID kCrsrPlaceSnippetOrigLocSnap = (kCrsrPlaceSnippetOrigLoc + kSnapToCrsrOffset);
const CursorID kCrsrContentDropperSnap = (kCrsrContentDropper + kSnapToCrsrOffset);
const CursorID kCrsrContentDropperAdHocSnap = (kCrsrContentDropperAdHoc + kSnapToCrsrOffset);
const CursorID kCrsrContentDropperNeedfulSnap = (kCrsrContentDropperNeedful + kSnapToCrsrOffset);

// ME
const CursorID kCrsrAutoMETextSnap	= (kCrsrAutoMEText + kSnapToCrsrOffset);
const CursorID kCrsrSemiAutoMETextSnap	= (kCrsrSemiAutoMEText + kSnapToCrsrOffset);
const CursorID kCrsrPlaceMETextSnap = (kCrsrPlaceMEText + kSnapToCrsrOffset);
const CursorID kCrsrPlaceMETextAutoStopSnap = (kCrsrPlaceMETextAutoStop + kSnapToCrsrOffset);
const CursorID kCrsrPlaceMETextIntoAutoStopSnap = (kCrsrPlaceMETextIntoAutoStop + kSnapToCrsrOffset);
//end ME

const CursorID kCrsrPageToolNotOverPageSnap = (kCrsrPageToolNotOverPage + kSnapToCrsrOffset);
const CursorID kCrsrMotionPathSnap = (kCrsrMotionPath + kSnapToCrsrOffset);
const CursorID kCrsrPageToolOverPageSnap = (kCrsrPageToolOverPage + kSnapToCrsrOffset);

//HiDPI
const CursorID kCrsrGrabberHandHIDPI = (kCrsrGrabberHand + kHIDPICrsrOffset);
const CursorID kCrsrOpenHandHIDPI   = (kCrsrOpenHand + kHIDPICrsrOffset);
const CursorID kCrsrPresentationNextHIDPI   = (kCrsrPresentationNext + kHIDPICrsrOffset);
const CursorID kCrsrPresentationPreviousHIDPI   = (kCrsrPresentationPrevious + kHIDPICrsrOffset);
const CursorID kCrsrPointyHandCopyHIDPI   = (kCrsrPointyHandCopy + kHIDPICrsrOffset);
const CursorID kCrsrScrubHIDPI   = (kCrsrScrub + kHIDPICrsrOffset);
const CursorID kCrsrClosedHandHIDPI   = (kCrsrClosedHand + kHIDPICrsrOffset);
const CursorID kCrsrClosedHandCopyHIDPI   = (kCrsrClosedHandCopy + kHIDPICrsrOffset);
const CursorID kCrsrClosedHandZoomScrollHIDPI   = (kCrsrClosedHandZoomScroll + kHIDPICrsrOffset);
const CursorID kCrsrPlaceTextSnapHIDPI   = (kCrsrPlaceTextSnap + kHIDPICrsrOffset);
const CursorID kCrsrDragCopySnapHIDPI   = (kCrsrDragCopySnap + kHIDPICrsrOffset);
const CursorID kCrsrDragSnapHIDPI   = (kCrsrDragSnap + kHIDPICrsrOffset);
const CursorID kCrsrSemiAutoTextHIDPI   = (kCrsrSemiAutoText + kHIDPICrsrOffset);
const CursorID kCrsrSemiAutoTextSnapHIDPI   = (kCrsrSemiAutoTextSnap + kHIDPICrsrOffset);
const CursorID kCrsrPlaceTextIntoSemiAutoHIDPI   = (kCrsrPlaceTextIntoSemiAuto + kHIDPICrsrOffset);
const CursorID kCrsrAutoTextSnapHIDPI   = (kCrsrAutoTextSnap + kHIDPICrsrOffset);
const CursorID kCrsrPlaceTextAutoStopHIDPI   = (kCrsrPlaceTextAutoStop + kHIDPICrsrOffset);
const CursorID kCrsrPlaceTextAutoStopSnapHIDPI   = (kCrsrPlaceTextAutoStopSnap + kHIDPICrsrOffset);
const CursorID kCrsrPlaceTextIntoAutoStopHIDPI   = (kCrsrPlaceTextIntoAutoStop + kHIDPICrsrOffset);
const CursorID kCrsrPlaceTextIntoAutoStopSnapHIDPI   = (kCrsrPlaceTextIntoAutoStopSnap + kHIDPICrsrOffset);
const CursorID kCrsrPlaceVerticalTextHIDPI   = (kCrsrPlaceVerticalText + kHIDPICrsrOffset);
const CursorID kCrsrPlaceVerticalTextSnapHIDPI   = (kCrsrPlaceVerticalTextSnap + kHIDPICrsrOffset);
const CursorID kCrsrPlaceVerticalTextIntoHIDPI   = (kCrsrPlaceVerticalTextInto + kHIDPICrsrOffset);
const CursorID kCrsrTOPStartBracketHIDPI   = (kCrsrTOPStartBracket + kHIDPICrsrOffset);
const CursorID kCrsrTOPEndBracketHIDPI   = (kCrsrTOPEndBracket + kHIDPICrsrOffset);
const CursorID kCrsrTOPCenterBracketHIDPI   = (kCrsrTOPCenterBracket + kHIDPICrsrOffset);
const CursorID kCrsrSemiAutoVerticalTextHIDPI   = (kCrsrSemiAutoVerticalText + kHIDPICrsrOffset);
const CursorID kCrsrSemiAutoVerticalTextSnapHIDPI   = (kCrsrSemiAutoVerticalTextSnap + kHIDPICrsrOffset);
const CursorID kCrsrPlaceVerticalTextIntoSemiAutoHIDPI   = (kCrsrPlaceVerticalTextIntoSemiAuto + kHIDPICrsrOffset);
const CursorID kCrsrPlaceVerticalTextAutoHIDPI   = (kCrsrPlaceVerticalTextAuto + kHIDPICrsrOffset);
const CursorID kCrsrPlaceVerticalTextAutoSnapHIDPI   = (kCrsrPlaceVerticalTextAutoSnap + kHIDPICrsrOffset);
const CursorID kCrsrPlaceVerticalTextIntoAutoHIDPI   = (kCrsrPlaceVerticalTextIntoAuto + kHIDPICrsrOffset);
const CursorID kCrsrPlaceTextAutoStopVerticalHIDPI   = (kCrsrPlaceTextAutoStopVertical + kHIDPICrsrOffset);
const CursorID kCrsrPlaceTextAutoStopVerticalSnapHIDPI   = (kCrsrPlaceTextAutoStopVerticalSnap + kHIDPICrsrOffset);
const CursorID kCrsrPlaceTextIntoAutoStopVerticalHIDPI   = (kCrsrPlaceTextIntoAutoStopVertical + kHIDPICrsrOffset);
const CursorID kCrsrPlaceTextIntoAutoStopVerticalSnapHIDPI   = (kCrsrPlaceTextIntoAutoStopVerticalSnap + kHIDPICrsrOffset);
const CursorID kCrsrPlaceMETextHIDPI   = (kCrsrPlaceMEText + kHIDPICrsrOffset);
const CursorID kCrsrPlaceMETextSnapHIDPI   = (kCrsrPlaceMETextSnap + kHIDPICrsrOffset);
const CursorID kCrsrPlaceMETextIntoHIDPI   = (kCrsrPlaceMETextInto + kHIDPICrsrOffset);
const CursorID kCrsrAutoMETextHIDPI   = (kCrsrAutoMEText + kHIDPICrsrOffset);
const CursorID kCrsrAutoMETextSnapHIDPI   = (kCrsrAutoMETextSnap + kHIDPICrsrOffset);
const CursorID kCrsrPlaceMETextIntoAutoHIDPI   = (kCrsrPlaceMETextIntoAuto + kHIDPICrsrOffset);
const CursorID kCrsrSemiAutoMETextHIDPI   = (kCrsrSemiAutoMEText + kHIDPICrsrOffset);
const CursorID kCrsrSemiAutoMETextSnapHIDPI   = (kCrsrSemiAutoMETextSnap + kHIDPICrsrOffset);
const CursorID kCrsrPlaceMETextIntoSemiAutoHIDPI   = (kCrsrPlaceMETextIntoSemiAuto + kHIDPICrsrOffset);
const CursorID kCrsrPlaceMETextAutoStopHIDPI   = (kCrsrPlaceMETextAutoStop + kHIDPICrsrOffset);
const CursorID kCrsrPlaceMETextAutoStopSnapHIDPI   = (kCrsrPlaceMETextAutoStopSnap + kHIDPICrsrOffset);
const CursorID kCrsrPlaceMETextIntoAutoStopHIDPI   = (kCrsrPlaceMETextIntoAutoStop + kHIDPICrsrOffset);
const CursorID kCrsrPlaceMETextIntoAutoStopSnapHIDPI   = (kCrsrPlaceMETextIntoAutoStopSnap + kHIDPICrsrOffset);
const CursorID kCrsrPlaceEPSHIDPI   = (kCrsrPlaceEPS + kHIDPICrsrOffset);
const CursorID kCrsrPlaceEPSSnapHIDPI   = (kCrsrPlaceEPSSnap + kHIDPICrsrOffset);
const CursorID kCrsrPlaceEPSIntoHIDPI   = (kCrsrPlaceEPSInto + kHIDPICrsrOffset);
const CursorID kCrsrPlaceImageIntoHIDPI   = (kCrsrPlaceImageInto + kHIDPICrsrOffset);
const CursorID kCrsrPlaceGraphicHIDPI   = (kCrsrPlaceGraphic + kHIDPICrsrOffset);
const CursorID kCrsrPlaceGraphicSnapHIDPI   = (kCrsrPlaceGraphicSnap + kHIDPICrsrOffset);
const CursorID kCrsrBadDropTargetHIDPI   = (kCrsrBadDropTarget + kHIDPICrsrOffset);
const CursorID kCrsrGapToolNoGapHIDPI   = (kCrsrGapToolNoGap + kHIDPICrsrOffset);
const CursorID kCrsrPointyHandHIDPI = (kCrsrPointyHand + kHIDPICrsrOffset);
const CursorID kCursorADBE3DButtonHIDPI = (kCursorADBE3DButton + kHIDPICrsrOffset);
const CursorID kCrsrDragCopyHIDPI = (kCrsrDragCopy + kHIDPICrsrOffset);
const CursorID kCrsrDragHIDPI = (kCrsrDrag + kHIDPICrsrOffset);
const CursorID kCrsrPlaceTextIntoAutoHIDPI = (kCrsrPlaceTextIntoAuto + kHIDPICrsrOffset);
const CursorID kCrsrAutoTextHIDPI = (kCrsrAutoText + kHIDPICrsrOffset);
const CursorID kCrsrCircleHIDPI = (kCrsrCircle + kHIDPICrsrOffset);
const CursorID kCrsrAnchorDirectSelectHIDPI = (kCrsrAnchorDirectSelect + kHIDPICrsrOffset);
const CursorID kCrsrDirectSelectHIDPI = (kCrsrDirectSelect + kHIDPICrsrOffset);
const CursorID kCrsrConvertDirectionHIDPI = (kCrsrConvertDirection + kHIDPICrsrOffset);
const CursorID kCrsrNoZoomHIDPI = (kCrsrNoZoom + kHIDPICrsrOffset);
const CursorID kCrsrPlaceTextIntoHIDPI = (kCrsrPlaceTextInto + kHIDPICrsrOffset);
const CursorID kCrsrPlaceTextHIDPI = (kCrsrPlaceText + kHIDPICrsrOffset);
const CursorID kCrsrCrosshairHIDPI = (kCrsrCrosshair + kHIDPICrsrOffset);
const CursorID kCrsrItemCreationHIDPI = (kCrsrItemCreation + kHIDPICrsrOffset);
const CursorID kEastWestPointerHIDPI = (kEastWestPointer + kHIDPICrsrOffset);
const CursorID kNWSEPointerHIDPI = (kNWSEPointer + kHIDPICrsrOffset);
const CursorID kNESWPointerHIDPI = (kNESWPointer + kHIDPICrsrOffset);
const CursorID kNorthSouthPointerHIDPI = (kNorthSouthPointer + kHIDPICrsrOffset);
const CursorID kCrsrSelectionArrowHIDPI = (kCrsrSelectionArrow + kHIDPICrsrOffset);
const CursorID kCrsrVerticalSplitterHIDPI = (kCrsrVerticalSplitter + kHIDPICrsrOffset);
const CursorID kCrsrSplitterHIDPI = (kCrsrSplitter + kHIDPICrsrOffset);
const CursorID kCrsrRotationHIDPI = (kCrsrRotation + kHIDPICrsrOffset);
const CursorID kCrsrZoomInHIDPI = (kCrsrZoomIn + kHIDPICrsrOffset);
const CursorID kCrsrZoomOutHIDPI = (kCrsrZoomOut + kHIDPICrsrOffset);
const CursorID kCrsrObjectSelectHIDPI = (kCrsrObjectSelect + kHIDPICrsrOffset);
const CursorID kCrsrSelectSelectionHIDPI = (kCrsrSelectSelection + kHIDPICrsrOffset);
const CursorID kCrsrObjectDirectSelectHIDPI = (kCrsrObjectDirectSelect + kHIDPICrsrOffset);

const CursorID kCrsrGapToolHorizontalHIDPI = (kCrsrGapToolHorizontal + kHIDPICrsrOffset);
const CursorID kCrsrGapToolVerticalHIDPI = (kCrsrGapToolVertical + kHIDPICrsrOffset);
const CursorID kNESWPointerSnapHIDPI = (kNESWPointerSnap + kHIDPICrsrOffset);
const CursorID kNorthSouthPointerSnapHIDPI = (kNorthSouthPointerSnap + kHIDPICrsrOffset);
const CursorID kNWSEPointerSnapHIDPI = (kNWSEPointerSnap + kHIDPICrsrOffset);
const CursorID kEastWestPointerSnapHIDPI = (kEastWestPointerSnap + kHIDPICrsrOffset);
const CursorID kCrsrScrubResizeHorzHIDPI = (kCrsrScrubResizeHorz + kHIDPICrsrOffset);
const CursorID kCrsrCrosshairSnapHIDPI = (kCrsrCrosshairSnap + kHIDPICrsrOffset);
const CursorID kCrsrPageToolOverPageHIDPI = (kCrsrPageToolOverPage + kHIDPICrsrOffset);
const CursorID kCrsrPageToolOverPageSnapHIDPI = (kCrsrPageToolOverPageSnap + kHIDPICrsrOffset);
const CursorID kCrsrPageToolNotOverPageHIDPI = (kCrsrPageToolNotOverPage + kHIDPICrsrOffset);
const CursorID kCrsrPageToolNotOverPageSnapHIDPI = (kCrsrPageToolNotOverPageSnap + kHIDPICrsrOffset);
const CursorID kCrsrContentGrabberHIDPI = (kCrsrContentGrabber + kHIDPICrsrOffset);
const CursorID kCrsrDragCopyTextHIDPI = (kCrsrDragCopyText + kHIDPICrsrOffset);
const CursorID kCrsrDragCopyUnformattedTextHIDPI = (kCrsrDragCopyUnformattedText + kHIDPICrsrOffset);
const CursorID kCrsrDragCopyToNewFrameHIDPI = (kCrsrDragCopyToNewFrame + kHIDPICrsrOffset);
const CursorID kCrsrDragCopyUnformattedTextToNewFrameHIDPI = (kCrsrDragCopyUnformattedTextToNewFrame + kHIDPICrsrOffset);
const CursorID kCrsrDragTextHIDPI = (kCrsrDragText + kHIDPICrsrOffset);
const CursorID kCrsrDragTextLockedHIDPI = (kCrsrDragTextLocked + kHIDPICrsrOffset);
const CursorID kCrsrButtonTriggerHIDPI = (kCrsrButtonTrigger + kHIDPICrsrOffset);
const CursorID kCrsrDragApplyToFillHIDPI = (kCrsrDragApplyToFill + kHIDPICrsrOffset);
const CursorID kCrsrDragToNewFrameHIDPI = (kCrsrDragToNewFrame + kHIDPICrsrOffset);
const CursorID kCrsrDragApplyToStrokeHIDPI = (kCrsrDragApplyToStroke + kHIDPICrsrOffset);
const CursorID kCrsrDragUnformattedTextHIDPI = (kCrsrDragUnformattedText + kHIDPICrsrOffset);
const CursorID kCrsrDragUnformattedTextToNewFrameHIDPI = (kCrsrDragUnformattedTextToNewFrame + kHIDPICrsrOffset);
const CursorID kCrsrContentDropperHIDPI = (kCrsrContentDropper + kHIDPICrsrOffset);
const CursorID kCrsrContentDropperSnapHIDPI = (kCrsrContentDropperSnap + kHIDPICrsrOffset);
const CursorID kCrsrMotionPathSnapHIDPI = (kCrsrMotionPathSnap + kHIDPICrsrOffset);
const CursorID kCrsrDropLoadGunHIDPI = (kCrsrDropLoadGun + kHIDPICrsrOffset);
const CursorID kCrsrDropLoadGunSnapHIDPI = (kCrsrDropLoadGunSnap + kHIDPICrsrOffset);
const CursorID kCrsrPlaceFileSnapHIDPI = (kCrsrPlaceFileSnap + kHIDPICrsrOffset);
const CursorID kCrsrPlaceFileIntoHIDPI = (kCrsrPlaceFileInto + kHIDPICrsrOffset);
const CursorID kCrsrPlaceSnippetOrigLocHIDPI = (kCrsrPlaceSnippetOrigLoc + kHIDPICrsrOffset);
const CursorID kCrsrPlaceSnippetOrigLocSnapHIDPI = (kCrsrPlaceSnippetOrigLocSnap + kHIDPICrsrOffset);
const CursorID kCrsrPlaceSnippetHIDPI = (kCrsrPlaceSnippet + kHIDPICrsrOffset);
const CursorID kCrsrPlaceSnippetSnapHIDPI = (kCrsrPlaceSnippetSnap + kHIDPICrsrOffset);
const CursorID kCrsrContentDropperAdHocHIDPI = (kCrsrContentDropperAdHoc + kHIDPICrsrOffset);
const CursorID kCrsrContentDropperAdHocSnapHIDPI = (kCrsrContentDropperAdHocSnap + kHIDPICrsrOffset);
const CursorID kCrsrContentDropperNeedfulHIDPI = (kCrsrContentDropperNeedful + kHIDPICrsrOffset);
const CursorID kCrsrContentDropperNeedfulSnapHIDPI = (kCrsrContentDropperNeedfulSnap + kHIDPICrsrOffset);
const CursorID kCrsrUnlockHIDPI = (kCrsrUnlock + kHIDPICrsrOffset);

const CursorID kCrsrClosedPathHIDPI = (kCrsrClosedPath + kHIDPICrsrOffset);
const CursorID kCrsrItemTransformHIDPI = (kCrsrItemTransform + kHIDPICrsrOffset);
const CursorID kCrsrItemCreationSnapHIDPI = (kCrsrItemCreationSnap + kHIDPICrsrOffset);
const CursorID kCursorLockHIDPI = (kCursorLock + kHIDPICrsrOffset);
const CursorID kCrsrMotionPathHIDPI = (kCrsrMotionPath + kHIDPICrsrOffset);
const CursorID kCrsrPlaceFileHIDPI = (kCrsrPlaceFile + kHIDPICrsrOffset);

const CursorID kCrsrControlDirectSelectHIDPI = (kCrsrControlDirectSelect + kHIDPICrsrOffset);
const CursorID kCrsrSegmentDirectSelectHIDPI = (kCrsrSegmentDirectSelect + kHIDPICrsrOffset);
const CursorID kAnimCrsrWatch_1HIDPI = (kAnimCrsrWatch_1 + kHIDPICrsrOffset);
const CursorID kAnimCrsrWatch_2HIDPI = (kAnimCrsrWatch_2 + kHIDPICrsrOffset);
const CursorID kAnimCrsrWatch_3HIDPI = (kAnimCrsrWatch_3 + kHIDPICrsrOffset);
const CursorID kAnimCrsrWatch_4HIDPI = (kAnimCrsrWatch_4 + kHIDPICrsrOffset);
const CursorID kAnimCrsrWatch_5HIDPI = (kAnimCrsrWatch_5 + kHIDPICrsrOffset);
const CursorID kAnimCrsrWatch_6HIDPI = (kAnimCrsrWatch_6 + kHIDPICrsrOffset);
const CursorID kAnimCrsrWatch_7HIDPI = (kAnimCrsrWatch_7 + kHIDPICrsrOffset);
const CursorID kAnimCrsrWatch_8HIDPI = (kAnimCrsrWatch_8 + kHIDPICrsrOffset);

const CursorID kCrsrGroupSelectHIDPI = (kCrsrGroupSelect + kHIDPICrsrOffset);
const CursorID kCrsrIBeamHIDPI = (kCrsrIBeam + kHIDPICrsrOffset);
const CursorID kCrsrRotationSnapHIDPI = (kCrsrRotationSnap + kHIDPICrsrOffset);
const CursorID kCrsrLinkFramesHIDPI = (kCrsrLinkFrames + kHIDPICrsrOffset);
const CursorID kCrsrLinkMEFramesHIDPI = (kCrsrLinkMEFrames + kHIDPICrsrOffset);
const CursorID kCrsrLinkVerticalFramesHIDPI = (kCrsrLinkVerticalFrames + kHIDPICrsrOffset);
const CursorID kCrsrUnlinkFramesHIDPI = (kCrsrUnlinkFrames + kHIDPICrsrOffset);
const CursorID kCrsrUnlinkMEFramesHIDPI = (kCrsrUnlinkMEFrames + kHIDPICrsrOffset);
const CursorID kCrsrLockedHIDPI = (kCrsrLocked + kHIDPICrsrOffset);
const CursorID kCrsrPlaceBadDropTargetHIDPI = (kCrsrPlaceBadDropTarget + kHIDPICrsrOffset);
const CursorID kCrsrCascadePlaceHIDPI = (kCrsrCascadePlace + kHIDPICrsrOffset);
const CursorID kCrsrCascadePlaceSnapHIDPI = (kCrsrCascadePlaceSnap + kHIDPICrsrOffset);

const CursorID kCrsrDragTablesHoverHIDPI = (kCrsrDragTablesHover + kHIDPICrsrOffset);
const CursorID kCrsrDragTablesHIDPI	= (kCrsrDragTables + kHIDPICrsrOffset);
const CursorID kCrsrDragDuplicateTablesHIDPI = (kCrsrDragDuplicateTables + kHIDPICrsrOffset);

//End HiDPI

#ifdef WINDOWS
// 1.5x HIDPI
const CursorID kCrsrGrabberHandHIDPI150 = (kCrsrGrabberHand + kHIDPI150CrsrOffset);
const CursorID kCrsrOpenHandHIDPI150   = (kCrsrOpenHand + kHIDPI150CrsrOffset);
const CursorID kCrsrPresentationNextHIDPI150   = (kCrsrPresentationNext + kHIDPI150CrsrOffset);
const CursorID kCrsrPresentationPreviousHIDPI150   = (kCrsrPresentationPrevious + kHIDPI150CrsrOffset);
const CursorID kCrsrPointyHandCopyHIDPI150   = (kCrsrPointyHandCopy + kHIDPI150CrsrOffset);
const CursorID kCrsrScrubHIDPI150   = (kCrsrScrub + kHIDPI150CrsrOffset);
const CursorID kCrsrClosedHandHIDPI150   = (kCrsrClosedHand + kHIDPI150CrsrOffset);
const CursorID kCrsrClosedHandCopyHIDPI150   = (kCrsrClosedHandCopy + kHIDPI150CrsrOffset);
const CursorID kCrsrClosedHandZoomScrollHIDPI150   = (kCrsrClosedHandZoomScroll + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceTextSnapHIDPI150   = (kCrsrPlaceTextSnap + kHIDPI150CrsrOffset);
const CursorID kCrsrDragCopySnapHIDPI150   = (kCrsrDragCopySnap + kHIDPI150CrsrOffset);
const CursorID kCrsrDragSnapHIDPI150   = (kCrsrDragSnap + kHIDPI150CrsrOffset);
const CursorID kCrsrSemiAutoTextHIDPI150   = (kCrsrSemiAutoText + kHIDPI150CrsrOffset);
const CursorID kCrsrSemiAutoTextSnapHIDPI150   = (kCrsrSemiAutoTextSnap + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceTextIntoSemiAutoHIDPI150   = (kCrsrPlaceTextIntoSemiAuto + kHIDPI150CrsrOffset);
const CursorID kCrsrAutoTextSnapHIDPI150   = (kCrsrAutoTextSnap + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceTextAutoStopHIDPI150   = (kCrsrPlaceTextAutoStop + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceTextAutoStopSnapHIDPI150   = (kCrsrPlaceTextAutoStopSnap + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceTextIntoAutoStopHIDPI150   = (kCrsrPlaceTextIntoAutoStop + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceTextIntoAutoStopSnapHIDPI150   = (kCrsrPlaceTextIntoAutoStopSnap + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceVerticalTextHIDPI150   = (kCrsrPlaceVerticalText + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceVerticalTextSnapHIDPI150   = (kCrsrPlaceVerticalTextSnap + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceVerticalTextIntoHIDPI150   = (kCrsrPlaceVerticalTextInto + kHIDPI150CrsrOffset);
const CursorID kCrsrTOPStartBracketHIDPI150   = (kCrsrTOPStartBracket + kHIDPI150CrsrOffset);
const CursorID kCrsrTOPEndBracketHIDPI150   = (kCrsrTOPEndBracket + kHIDPI150CrsrOffset);
const CursorID kCrsrTOPCenterBracketHIDPI150   = (kCrsrTOPCenterBracket + kHIDPI150CrsrOffset);
const CursorID kCrsrSemiAutoVerticalTextHIDPI150   = (kCrsrSemiAutoVerticalText + kHIDPI150CrsrOffset);
const CursorID kCrsrSemiAutoVerticalTextSnapHIDPI150   = (kCrsrSemiAutoVerticalTextSnap + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceVerticalTextIntoSemiAutoHIDPI150   = (kCrsrPlaceVerticalTextIntoSemiAuto + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceVerticalTextAutoHIDPI150   = (kCrsrPlaceVerticalTextAuto + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceVerticalTextAutoSnapHIDPI150   = (kCrsrPlaceVerticalTextAutoSnap + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceVerticalTextIntoAutoHIDPI150   = (kCrsrPlaceVerticalTextIntoAuto + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceTextAutoStopVerticalHIDPI150   = (kCrsrPlaceTextAutoStopVertical + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceTextAutoStopVerticalSnapHIDPI150   = (kCrsrPlaceTextAutoStopVerticalSnap + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceTextIntoAutoStopVerticalHIDPI150   = (kCrsrPlaceTextIntoAutoStopVertical + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceTextIntoAutoStopVerticalSnapHIDPI150   = (kCrsrPlaceTextIntoAutoStopVerticalSnap + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceMETextHIDPI150   = (kCrsrPlaceMEText + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceMETextSnapHIDPI150   = (kCrsrPlaceMETextSnap + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceMETextIntoHIDPI150   = (kCrsrPlaceMETextInto + kHIDPI150CrsrOffset);
const CursorID kCrsrAutoMETextHIDPI150   = (kCrsrAutoMEText + kHIDPI150CrsrOffset);
const CursorID kCrsrAutoMETextSnapHIDPI150   = (kCrsrAutoMETextSnap + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceMETextIntoAutoHIDPI150   = (kCrsrPlaceMETextIntoAuto + kHIDPI150CrsrOffset);
const CursorID kCrsrSemiAutoMETextHIDPI150   = (kCrsrSemiAutoMEText + kHIDPI150CrsrOffset);
const CursorID kCrsrSemiAutoMETextSnapHIDPI150   = (kCrsrSemiAutoMETextSnap + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceMETextIntoSemiAutoHIDPI150   = (kCrsrPlaceMETextIntoSemiAuto + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceMETextAutoStopHIDPI150   = (kCrsrPlaceMETextAutoStop + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceMETextAutoStopSnapHIDPI150   = (kCrsrPlaceMETextAutoStopSnap + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceMETextIntoAutoStopHIDPI150   = (kCrsrPlaceMETextIntoAutoStop + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceMETextIntoAutoStopSnapHIDPI150   = (kCrsrPlaceMETextIntoAutoStopSnap + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceEPSHIDPI150   = (kCrsrPlaceEPS + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceEPSSnapHIDPI150   = (kCrsrPlaceEPSSnap + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceEPSIntoHIDPI150   = (kCrsrPlaceEPSInto + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceImageIntoHIDPI150   = (kCrsrPlaceImageInto + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceGraphicHIDPI150   = (kCrsrPlaceGraphic + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceGraphicSnapHIDPI150   = (kCrsrPlaceGraphicSnap + kHIDPI150CrsrOffset);
const CursorID kCrsrBadDropTargetHIDPI150   = (kCrsrBadDropTarget + kHIDPI150CrsrOffset);
const CursorID kCrsrGapToolNoGapHIDPI150   = (kCrsrGapToolNoGap + kHIDPI150CrsrOffset);
const CursorID kCrsrPointyHandHIDPI150 = (kCrsrPointyHand + kHIDPI150CrsrOffset);
const CursorID kCursorADBE3DButtonHIDPI150 = (kCursorADBE3DButton + kHIDPI150CrsrOffset);
const CursorID kCrsrDragCopyHIDPI150 = (kCrsrDragCopy + kHIDPI150CrsrOffset);
const CursorID kCrsrDragHIDPI150 = (kCrsrDrag + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceTextIntoAutoHIDPI150 = (kCrsrPlaceTextIntoAuto + kHIDPI150CrsrOffset);
const CursorID kCrsrAutoTextHIDPI150 = (kCrsrAutoText + kHIDPI150CrsrOffset);
const CursorID kCrsrCircleHIDPI150 = (kCrsrCircle + kHIDPI150CrsrOffset);
const CursorID kCrsrAnchorDirectSelectHIDPI150 = (kCrsrAnchorDirectSelect + kHIDPI150CrsrOffset);
const CursorID kCrsrDirectSelectHIDPI150 = (kCrsrDirectSelect + kHIDPI150CrsrOffset);
const CursorID kCrsrConvertDirectionHIDPI150 = (kCrsrConvertDirection + kHIDPI150CrsrOffset);
const CursorID kCrsrNoZoomHIDPI150 = (kCrsrNoZoom + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceTextIntoHIDPI150 = (kCrsrPlaceTextInto + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceTextHIDPI150 = (kCrsrPlaceText + kHIDPI150CrsrOffset);
const CursorID kCrsrCrosshairHIDPI150 = (kCrsrCrosshair + kHIDPI150CrsrOffset);
const CursorID kCrsrItemCreationHIDPI150 = (kCrsrItemCreation + kHIDPI150CrsrOffset);
const CursorID kEastWestPointerHIDPI150 = (kEastWestPointer + kHIDPI150CrsrOffset);
const CursorID kNWSEPointerHIDPI150 = (kNWSEPointer + kHIDPI150CrsrOffset);
const CursorID kNESWPointerHIDPI150 = (kNESWPointer + kHIDPI150CrsrOffset);
const CursorID kNorthSouthPointerHIDPI150 = (kNorthSouthPointer + kHIDPI150CrsrOffset);
const CursorID kCrsrSelectionArrowHIDPI150 = (kCrsrSelectionArrow + kHIDPI150CrsrOffset);
const CursorID kCrsrVerticalSplitterHIDPI150 = (kCrsrVerticalSplitter + kHIDPI150CrsrOffset);
const CursorID kCrsrSplitterHIDPI150 = (kCrsrSplitter + kHIDPI150CrsrOffset);
const CursorID kCrsrRotationHIDPI150 = (kCrsrRotation + kHIDPI150CrsrOffset);
const CursorID kCrsrZoomInHIDPI150 = (kCrsrZoomIn + kHIDPI150CrsrOffset);
const CursorID kCrsrZoomOutHIDPI150 = (kCrsrZoomOut + kHIDPI150CrsrOffset);
const CursorID kCrsrObjectSelectHIDPI150 = (kCrsrObjectSelect + kHIDPI150CrsrOffset);
const CursorID kCrsrSelectSelectionHIDPI150 = (kCrsrSelectSelection + kHIDPI150CrsrOffset);
const CursorID kCrsrObjectDirectSelectHIDPI150 = (kCrsrObjectDirectSelect + kHIDPI150CrsrOffset);

const CursorID kCrsrGapToolHorizontalHIDPI150 = (kCrsrGapToolHorizontal + kHIDPI150CrsrOffset);
const CursorID kCrsrGapToolVerticalHIDPI150 = (kCrsrGapToolVertical + kHIDPI150CrsrOffset);
const CursorID kNESWPointerSnapHIDPI150 = (kNESWPointerSnap + kHIDPI150CrsrOffset);
const CursorID kNorthSouthPointerSnapHIDPI150 = (kNorthSouthPointerSnap + kHIDPI150CrsrOffset);
const CursorID kNWSEPointerSnapHIDPI150 = (kNWSEPointerSnap + kHIDPI150CrsrOffset);
const CursorID kEastWestPointerSnapHIDPI150 = (kEastWestPointerSnap + kHIDPI150CrsrOffset);
const CursorID kCrsrScrubResizeHorzHIDPI150 = (kCrsrScrubResizeHorz + kHIDPI150CrsrOffset);
const CursorID kCrsrCrosshairSnapHIDPI150 = (kCrsrCrosshairSnap + kHIDPI150CrsrOffset);
const CursorID kCrsrPageToolOverPageHIDPI150 = (kCrsrPageToolOverPage + kHIDPI150CrsrOffset);
const CursorID kCrsrPageToolOverPageSnapHIDPI150 = (kCrsrPageToolOverPageSnap + kHIDPI150CrsrOffset);
const CursorID kCrsrPageToolNotOverPageHIDPI150 = (kCrsrPageToolNotOverPage + kHIDPI150CrsrOffset);
const CursorID kCrsrPageToolNotOverPageSnapHIDPI150 = (kCrsrPageToolNotOverPageSnap + kHIDPI150CrsrOffset);
const CursorID kCrsrContentGrabberHIDPI150 = (kCrsrContentGrabber + kHIDPI150CrsrOffset);
const CursorID kCrsrDragCopyTextHIDPI150 = (kCrsrDragCopyText + kHIDPI150CrsrOffset);
const CursorID kCrsrDragCopyUnformattedTextHIDPI150 = (kCrsrDragCopyUnformattedText + kHIDPI150CrsrOffset);
const CursorID kCrsrDragCopyToNewFrameHIDPI150 = (kCrsrDragCopyToNewFrame + kHIDPI150CrsrOffset);
const CursorID kCrsrDragCopyUnformattedTextToNewFrameHIDPI150 = (kCrsrDragCopyUnformattedTextToNewFrame + kHIDPI150CrsrOffset);
const CursorID kCrsrDragTextHIDPI150 = (kCrsrDragText + kHIDPI150CrsrOffset);
const CursorID kCrsrDragTextLockedHIDPI150 = (kCrsrDragTextLocked + kHIDPI150CrsrOffset);
const CursorID kCrsrButtonTriggerHIDPI150 = (kCrsrButtonTrigger + kHIDPI150CrsrOffset);
const CursorID kCrsrDragApplyToFillHIDPI150 = (kCrsrDragApplyToFill + kHIDPI150CrsrOffset);
const CursorID kCrsrDragToNewFrameHIDPI150 = (kCrsrDragToNewFrame + kHIDPI150CrsrOffset);
const CursorID kCrsrDragApplyToStrokeHIDPI150 = (kCrsrDragApplyToStroke + kHIDPI150CrsrOffset);
const CursorID kCrsrDragUnformattedTextHIDPI150 = (kCrsrDragUnformattedText + kHIDPI150CrsrOffset);
const CursorID kCrsrDragUnformattedTextToNewFrameHIDPI150 = (kCrsrDragUnformattedTextToNewFrame + kHIDPI150CrsrOffset);
const CursorID kCrsrContentDropperHIDPI150 = (kCrsrContentDropper + kHIDPI150CrsrOffset);
const CursorID kCrsrContentDropperSnapHIDPI150 = (kCrsrContentDropperSnap + kHIDPI150CrsrOffset);
const CursorID kCrsrMotionPathSnapHIDPI150 = (kCrsrMotionPathSnap + kHIDPI150CrsrOffset);
const CursorID kCrsrDropLoadGunHIDPI150 = (kCrsrDropLoadGun + kHIDPI150CrsrOffset);
const CursorID kCrsrDropLoadGunSnapHIDPI150 = (kCrsrDropLoadGunSnap + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceFileSnapHIDPI150 = (kCrsrPlaceFileSnap + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceFileIntoHIDPI150 = (kCrsrPlaceFileInto + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceSnippetOrigLocHIDPI150 = (kCrsrPlaceSnippetOrigLoc + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceSnippetOrigLocSnapHIDPI150 = (kCrsrPlaceSnippetOrigLocSnap + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceSnippetHIDPI150 = (kCrsrPlaceSnippet + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceSnippetSnapHIDPI150 = (kCrsrPlaceSnippetSnap + kHIDPI150CrsrOffset);
const CursorID kCrsrContentDropperAdHocHIDPI150 = (kCrsrContentDropperAdHoc + kHIDPI150CrsrOffset);
const CursorID kCrsrContentDropperAdHocSnapHIDPI150 = (kCrsrContentDropperAdHocSnap + kHIDPI150CrsrOffset);
const CursorID kCrsrContentDropperNeedfulHIDPI150 = (kCrsrContentDropperNeedful + kHIDPI150CrsrOffset);
const CursorID kCrsrContentDropperNeedfulSnapHIDPI150 = (kCrsrContentDropperNeedfulSnap + kHIDPI150CrsrOffset);
const CursorID kCrsrUnlockHIDPI150 = (kCrsrUnlock + kHIDPI150CrsrOffset);

const CursorID kCrsrClosedPathHIDPI150 = (kCrsrClosedPath + kHIDPI150CrsrOffset);
const CursorID kCrsrItemTransformHIDPI150 = (kCrsrItemTransform + kHIDPI150CrsrOffset);
const CursorID kCrsrItemCreationSnapHIDPI150 = (kCrsrItemCreationSnap + kHIDPI150CrsrOffset);
const CursorID kCursorLockHIDPI150 = (kCursorLock + kHIDPI150CrsrOffset);
const CursorID kCrsrMotionPathHIDPI150 = (kCrsrMotionPath + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceFileHIDPI150 = (kCrsrPlaceFile + kHIDPI150CrsrOffset);

const CursorID kCrsrControlDirectSelectHIDPI150 = (kCrsrControlDirectSelect + kHIDPI150CrsrOffset);
const CursorID kCrsrSegmentDirectSelectHIDPI150 = (kCrsrSegmentDirectSelect + kHIDPI150CrsrOffset);
const CursorID kAnimCrsrWatch_1HIDPI150 = (kAnimCrsrWatch_1 + kHIDPI150CrsrOffset);
const CursorID kAnimCrsrWatch_2HIDPI150 = (kAnimCrsrWatch_2 + kHIDPI150CrsrOffset);
const CursorID kAnimCrsrWatch_3HIDPI150 = (kAnimCrsrWatch_3 + kHIDPI150CrsrOffset);
const CursorID kAnimCrsrWatch_4HIDPI150 = (kAnimCrsrWatch_4 + kHIDPI150CrsrOffset);
const CursorID kAnimCrsrWatch_5HIDPI150 = (kAnimCrsrWatch_5 + kHIDPI150CrsrOffset);
const CursorID kAnimCrsrWatch_6HIDPI150 = (kAnimCrsrWatch_6 + kHIDPI150CrsrOffset);
const CursorID kAnimCrsrWatch_7HIDPI150 = (kAnimCrsrWatch_7 + kHIDPI150CrsrOffset);
const CursorID kAnimCrsrWatch_8HIDPI150 = (kAnimCrsrWatch_8 + kHIDPI150CrsrOffset);

const CursorID kCrsrGroupSelectHIDPI150 = (kCrsrGroupSelect + kHIDPI150CrsrOffset);
const CursorID kCrsrIBeamHIDPI150 = (kCrsrIBeam + kHIDPI150CrsrOffset);
const CursorID kCrsrRotationSnapHIDPI150 = (kCrsrRotationSnap + kHIDPI150CrsrOffset);
const CursorID kCrsrLinkFramesHIDPI150 = (kCrsrLinkFrames + kHIDPI150CrsrOffset);
const CursorID kCrsrLinkMEFramesHIDPI150 = (kCrsrLinkMEFrames + kHIDPI150CrsrOffset);
const CursorID kCrsrLinkVerticalFramesHIDPI150 = (kCrsrLinkVerticalFrames + kHIDPI150CrsrOffset);
const CursorID kCrsrUnlinkFramesHIDPI150 = (kCrsrUnlinkFrames + kHIDPI150CrsrOffset);
const CursorID kCrsrUnlinkMEFramesHIDPI150 = (kCrsrUnlinkMEFrames + kHIDPI150CrsrOffset);
const CursorID kCrsrLockedHIDPI150 = (kCrsrLocked + kHIDPI150CrsrOffset);
const CursorID kCrsrPlaceBadDropTargetHIDPI150 = (kCrsrPlaceBadDropTarget + kHIDPI150CrsrOffset);
const CursorID kCrsrCascadePlaceHIDPI150 = (kCrsrCascadePlace + kHIDPI150CrsrOffset);
const CursorID kCrsrCascadePlaceSnapHIDPI150 = (kCrsrCascadePlaceSnap + kHIDPI150CrsrOffset);

const CursorID kCrsrDragTablesHoverHIDPI150 = (kCrsrDragTablesHover + kHIDPI150CrsrOffset);
const CursorID kCrsrDragTablesHIDPI150	= (kCrsrDragTables + kHIDPI150CrsrOffset);
const CursorID kCrsrDragDuplicateTablesHIDPI150 = (kCrsrDragDuplicateTables + kHIDPI150CrsrOffset);

// End 1.5x HIDPI
#endif

#endif		// __Cursordefs__
