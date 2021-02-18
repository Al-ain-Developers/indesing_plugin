//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/SplineUIID.h $
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
//  Contains IDs used by the polygon item plug-in
//  
//========================================================================================

#ifndef __SplineUIID__
#define __SplineUIID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"
#include "FormatNumber.h"

#define kSplineUIPrefix					RezLong(0x18500)
#define kSplineUIPluginName 				"Spline UI"

// PluginID
START_IDS()
DECLARE_PMID(kPlugInIDSpace, kSplineUIPluginID, kSplineUIPrefix + 1)

// ClassIDs
//

DECLARE_PMID(kClassIDSpace, kPathComponentBoss, kSplineUIPrefix + 1)
//gap
DECLARE_PMID(kClassIDSpace, kConvertShapeComponentBoss, kSplineUIPrefix + 3)
DECLARE_PMID(kClassIDSpace, kSetSplineStateCmdBoss, kSplineUIPrefix + 4)
DECLARE_PMID(kClassIDSpace, kSplineStateOpenDocResponderBoss, kSplineUIPrefix + 5)

// Tools
DECLARE_PMID(kClassIDSpace, kEraseToolBoss, kSplineUIPrefix + 10)
DECLARE_PMID(kClassIDSpace, kSplinePenToolBoss, kSplineUIPrefix + 11)
DECLARE_PMID(kClassIDSpace, kSplineAddPointToolBoss, kSplineUIPrefix + 12)
DECLARE_PMID(kClassIDSpace, kSplineRemovePointToolBoss, kSplineUIPrefix + 13)
DECLARE_PMID(kClassIDSpace, kSplineDirectionToolBoss, kSplineUIPrefix + 14)
DECLARE_PMID(kClassIDSpace, kScissorsToolBoss, kSplineUIPrefix + 15)
DECLARE_PMID(kClassIDSpace, kPencilToolBoss, kSplineUIPrefix + 16)
DECLARE_PMID(kClassIDSpace, kSmoothToolBoss, kSplineUIPrefix + 17)

// Trackers
DECLARE_PMID(kClassIDSpace, kPencilSliderTrackerBoss, kSplineUIPrefix + 20)
DECLARE_PMID(kClassIDSpace, kPencilCreationTrackerBoss, kSplineUIPrefix + 21)
DECLARE_PMID(kClassIDSpace, kSplineTrackerRegisterBoss, kSplineUIPrefix + 22)
DECLARE_PMID(kClassIDSpace, kSplinePathResizeTrackerBoss, kSplineUIPrefix + 23)
DECLARE_PMID(kClassIDSpace, kSplineCreationTrackerBoss, kSplineUIPrefix + 24)
DECLARE_PMID(kClassIDSpace, kSplineAddPointTrackerBoss, kSplineUIPrefix + 25)
DECLARE_PMID(kClassIDSpace, kSplineRemovePointTrackerBoss, kSplineUIPrefix + 26)
DECLARE_PMID(kClassIDSpace, kSplineDirectionTrackerBoss, kSplineUIPrefix + 27)
DECLARE_PMID(kClassIDSpace, kRemovePointTrackerBoss, kSplineUIPrefix + 28)
DECLARE_PMID(kClassIDSpace, kAddPointTrackerBoss, kSplineUIPrefix + 29)
DECLARE_PMID(kClassIDSpace, kConvertDirectionTrackerBoss, kSplineUIPrefix + 30)
DECLARE_PMID(kClassIDSpace, kScissorsTrackerBoss, kSplineUIPrefix + 31)
DECLARE_PMID(kClassIDSpace, kSplineScissorsTrackerBoss, kSplineUIPrefix + 32)
DECLARE_PMID(kClassIDSpace, kSmoothTrackerBoss, kSplineUIPrefix + 33)
DECLARE_PMID(kClassIDSpace, kEraseTrackerBoss, kSplineUIPrefix + 34)

// Dialogs
DECLARE_PMID(kClassIDSpace, kPencilDlgBoss, kSplineUIPrefix + 40)
DECLARE_PMID(kClassIDSpace, kSmoothDlgBoss, kSplineUIPrefix + 41)

// Widgets
DECLARE_PMID(kClassIDSpace, kPencilFidelitySliderWidgetBoss, kSplineUIPrefix + 50)
DECLARE_PMID(kClassIDSpace, kPencilSmoothnessSliderWidgetBoss, kSplineUIPrefix + 51)
DECLARE_PMID(kClassIDSpace, kPencilFidelityEditBoxWidgetBoss, kSplineUIPrefix + 52)
DECLARE_PMID(kClassIDSpace, kPencilSmoothnessEditBoxWidgetBoss, kSplineUIPrefix + 53)
DECLARE_PMID(kClassIDSpace, kPencilEditSelectionCheckBoxWidgetBoss, kSplineUIPrefix + 54)
DECLARE_PMID(kClassIDSpace, kPencilWithinEditBoxWidgetBoss, kSplineUIPrefix + 55)
DECLARE_PMID(kClassIDSpace, kPencilWithinSliderWidgetBoss, kSplineUIPrefix + 56)
DECLARE_PMID(kClassIDSpace, kPathFinderButtonsPanelBoss, kSplineUIPrefix + 57)
DECLARE_PMID(kClassIDSpace, kPathFinderPropPanelBoss, kSplineUIPrefix + 58)

// Palette panel
DECLARE_PMID(kClassIDSpace, kPathFinderPanelBoss, kSplineUIPrefix + 60)


// Implementation IDs
//

DECLARE_PMID(kImplementationIDSpace, kPathComponentImpl, kSplineUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kSplineItemEventActionImpl, kSplineUIPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kSplineStateSelectionObserverImpl, kSplineUIPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kGroupItemEventActionImpl, kSplineUIPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kSplineHandleShapeImpl, kSplineUIPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kSplineRectHandleShapeImpl, kSplineUIPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kConvertShapeComponentImpl, kSplineUIPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kSplinePlaceBehaviorUIImpl, kSplineUIPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kSplineStateImpl, kSplineUIPrefix + 9)

// Tools
DECLARE_PMID(kImplementationIDSpace, kSplinePenToolImpl, kSplineUIPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kSplineAddPointToolImpl, kSplineUIPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kSplineRemovePointToolImpl, kSplineUIPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kSplineDirectionToolImpl, kSplineUIPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kScissorsToolImpl, kSplineUIPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kPencilToolImpl, kSplineUIPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kSmoothToolImpl, kSplineUIPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kEraseToolImpl, kSplineUIPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kSetSplineStateCmdImpl, kSplineUIPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kSplineStateMotionPageItemDataImpl, kSplineUIPrefix + 19)

// Cursor providers
DECLARE_PMID(kImplementationIDSpace, kEraseCursorProviderImpl, kSplineUIPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kSmoothCursorProviderImpl, kSplineUIPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kPencilCursorProviderImpl, kSplineUIPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kSplineCreationCursorProviderImpl, kSplineUIPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kSplineAddCursorProviderImpl, kSplineUIPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kSplineRemoveCursorProviderImpl, kSplineUIPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kSplineDirectionCursorProviderImpl, kSplineUIPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kScissorsCursorProviderImpl, kSplineUIPrefix + 27)

// Trackers
DECLARE_PMID(kImplementationIDSpace, kPencilCreationTrackerImpl, kSplineUIPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kSplineTrackerRegisterImpl, kSplineUIPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kSplineResizeTrackerImpl, kSplineUIPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kSplineCreationTrackerImpl, kSplineUIPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kSplineAddPointTrackerImpl, kSplineUIPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kSplineRemovePointTrackerImpl, kSplineUIPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kSplineDirectionTrackerImpl, kSplineUIPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kRemovePointTrackerImpl, kSplineUIPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kAddPointTrackerImpl, kSplineUIPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kConvertDirectionTrackerImpl, kSplineUIPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kScissorsTrackerImpl, kSplineUIPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kSplineScissorsTrackerImpl, kSplineUIPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kPencilSliderTrackerImpl, kSplineUIPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kSmoothTrackerImpl, kSplineUIPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kEraseTrackerImpl, kSplineUIPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kPencilSpriteImpl, kSplineUIPrefix + 45)

DECLARE_PMID(kImplementationIDSpace, kSplineStateSignalResponderImpl, kSplineUIPrefix + 49)

// Dialogs
DECLARE_PMID(kImplementationIDSpace, kPencilDlgControllerImpl, kSplineUIPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kPencilDlgObserverImpl, kSplineUIPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kSmoothDlgControllerImpl, kSplineUIPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kSmoothDlgObserverImpl, kSplineUIPrefix + 53)

// Widgets
DECLARE_PMID(kImplementationIDSpace, kPencilFidelitySliderObserverImpl, kSplineUIPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kPencilSmoothnessSliderObserverImpl, kSplineUIPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kPencilWithinSliderObserverImpl, kSplineUIPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kPencilFidelityEditBoxObserverImpl, kSplineUIPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kPencilSmoothnessEditBoxObserverImpl, kSplineUIPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kPencilWithinEditBoxObserverImpl, kSplineUIPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kPencilEditSelCheckBoxObserverImpl, kSplineUIPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kPencilToolPanelProviderImpl, kSplineUIPrefix + 67)

DECLARE_PMID(kImplementationIDSpace, kPathFinderButtonObserverImpl, kSplineUIPrefix + 68)

// Utils
DECLARE_PMID(kImplementationIDSpace, kSplineUIUtilsImpl, kSplineUIPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kDoubleClickFitDetectHelperImpl, kSplineUIPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kMSOEventActionImpl, kSplineUIPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kPathFinderPropPanelActiveKitImpl, kSplineUIPrefix + 73)

// IIDs
//
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHFINDERBUTTONOBSERVER, kSplineUIPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTPATHENDPOINTMSG,	   kSplineUIPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ISPLINEUIUTILS, kSplineUIPrefix + 3)	
DECLARE_PMID(kInterfaceIDSpace, IID_IDOUBLECLICKFITDETECTHELPER, kSplineUIPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_ISPLINESTATE, kSplineUIPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_ISPLINESTATEMOTIONPAGEITEMDATA, kSplineUIPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ISPLINESTATESELECTIONOBSERVER, kSplineUIPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IUPDATEMOTIONITEMBOOLDATA, kSplineUIPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IDELETEMOTIONITEMBOOLDATA, kSplineUIPrefix + 9)

// <Widget ID>
//

DECLARE_PMID(kWidgetIDSpace, kSplinePenToolWidgetId, kSplineUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kSplineDirectionToolWidgetId, kSplineUIPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kSplineRemovePointToolWidgetId, kSplineUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kSplineAddPointToolWidgetId, kSplineUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kScissorsToolWidgetId, kSplineUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kPencilToolWidgetId, kSplineUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kSmoothToolWidgetId, kSplineUIPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kEraseToolWidgetId, kSplineUIPrefix + 8)

DECLARE_PMID(kWidgetIDSpace, kPencilDlgWidgetId, kSplineUIPrefix + 10)

DECLARE_PMID(kWidgetIDSpace, kPencilTolerancesGroupWidgetId, kSplineUIPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kPencilTolerancesTextWidgetId, kSplineUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kPencilOptionsGroupWidgetId, kSplineUIPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kPencilOptionsTextWidgetId, kSplineUIPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kPencilSelectionCheckWidgetId, kSplineUIPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kPencilSmoothnessEditBoxWidgetId, kSplineUIPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kPencilSmoothnessTitleWidgetId, kSplineUIPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kPencilFidelityEditBoxWidgetId, kSplineUIPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kPencilFidelityTitleWidgetId, kSplineUIPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kPencilPixelsTitleWidgetId, kSplineUIPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kPencilPercentTitleWidgetId, kSplineUIPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kPencilFidelitySliderWidgetId, kSplineUIPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kPencilSmoothnessSliderWidgetId, kSplineUIPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kPencilDefaultsButton_WidgetId, kSplineUIPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kSmoothDlgWidgetId, kSplineUIPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kPencilEditSelectionCheckWidgetId, kSplineUIPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kPencilOptionsWithinTitleWidgetId, kSplineUIPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kPencilWithinEditBoxWidgetId, kSplineUIPrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kPencilWithinPixelsTitleWidgetId, kSplineUIPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kPencilWithinSliderWidgetId, kSplineUIPrefix + 31)

// Path Finder panel
// Pathfinder widget ids
DECLARE_PMID(kWidgetIDSpace, kPathFinderPanelWidgetID, kSplineUIPrefix + 41)
DECLARE_PMID(kWidgetIDSpace, kPathFinderSubPanelWidgetID, kSplineUIPrefix + 42)
DECLARE_PMID(kWidgetIDSpace, kPathFinderUnionWidgetID, kSplineUIPrefix + 43)
DECLARE_PMID(kWidgetIDSpace, kPathFinderSubtractWidgetID, kSplineUIPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kPathFinderIntersectWidgetID, kSplineUIPrefix + 45)
DECLARE_PMID(kWidgetIDSpace, kPathFinderXorWidgetID, kSplineUIPrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kPathFinderMinusBackWidgetID, kSplineUIPrefix + 47)

// Convert shape widget ids
DECLARE_PMID(kWidgetIDSpace, kPathFinderRectWidgetID, kSplineUIPrefix + 48)				
DECLARE_PMID(kWidgetIDSpace, kPathFinderRoundedRectWidgetID, kSplineUIPrefix + 49)			
DECLARE_PMID(kWidgetIDSpace, kPathFinderBevelRectWidgetID, kSplineUIPrefix + 50)			
DECLARE_PMID(kWidgetIDSpace, kPathFinderInverseRoundedRectWidgetID, kSplineUIPrefix + 51)			
DECLARE_PMID(kWidgetIDSpace, kPathFinderEllipseWidgetID, kSplineUIPrefix + 52)				
DECLARE_PMID(kWidgetIDSpace, kPathFinderTriangleWidgetID, kSplineUIPrefix + 53)			
DECLARE_PMID(kWidgetIDSpace, kPathFinderPolygonWidgetID, kSplineUIPrefix + 54)				
DECLARE_PMID(kWidgetIDSpace, kPathFinderLineWidgetID, kSplineUIPrefix + 55)				
DECLARE_PMID(kWidgetIDSpace, kPathFinderOrthogonalLineWidgetID, kSplineUIPrefix + 56)			

// Path widget ids
DECLARE_PMID(kWidgetIDSpace, kPathFinderOpenPathWidgetID, kSplineUIPrefix + 57)			
DECLARE_PMID(kWidgetIDSpace, kPathFinderClosePathWidgetID, kSplineUIPrefix + 58)			
DECLARE_PMID(kWidgetIDSpace, kPathFinderReversePathWidgetID, kSplineUIPrefix + 59)			

// Other widget ids
DECLARE_PMID(kWidgetIDSpace, kPathFinderPathfinderTitleWidgetID, kSplineUIPrefix + 60)			
DECLARE_PMID(kWidgetIDSpace, kPathFinderConvertShapeTitleWidgetID, kSplineUIPrefix + 61)			
DECLARE_PMID(kWidgetIDSpace, kPathFinderSeparator1WidgetID, kSplineUIPrefix + 62)			
DECLARE_PMID(kWidgetIDSpace, kPathFinderSeparator2WidgetID, kSplineUIPrefix + 63)			
DECLARE_PMID(kWidgetIDSpace, kPathFinderPathsTitleWidgetID, kSplineUIPrefix + 64)			
DECLARE_PMID(kWidgetIDSpace, kPathFinderSeparator3WidgetID, kSplineUIPrefix + 65)
DECLARE_PMID(kWidgetIDSpace, kPathFinderJoinWidgetID, kSplineUIPrefix + 66)
DECLARE_PMID(kWidgetIDSpace, kPathFinderConvertPointTitleWidgetID, kSplineUIPrefix + 67)			
// gap

// Convert Point widget ids
DECLARE_PMID(kWidgetIDSpace, kPathFinderEndPointWidgetID, kSplineUIPrefix + 70)			
DECLARE_PMID(kWidgetIDSpace, kPathFinderCornerPointWidgetID, kSplineUIPrefix + 71)			
DECLARE_PMID(kWidgetIDSpace, kPathFinderSmoothPointWidgetID, kSplineUIPrefix + 72)			
DECLARE_PMID(kWidgetIDSpace, kPathFinderSmoothSymmetricalPointWidgetID, kSplineUIPrefix + 73)	

//Properties Panel : Pathfinder Kit
DECLARE_PMID(kWidgetIDSpace, kPathFinderKitWidgetID, kSplineUIPrefix + 74)

// <Action ID>
//

DECLARE_PMID(kActionIDSpace, kMakeCompoundPathActionID, kSplineUIPrefix + 1)
DECLARE_PMID(kActionIDSpace, kReleaseCompoundPathActionID, kSplineUIPrefix + 2)
DECLARE_PMID(kActionIDSpace, kReversePathActionID, kSplineUIPrefix + 3)

DECLARE_PMID(kActionIDSpace, kSplinePenToolActionID, kSplineUIPrefix + 4)
DECLARE_PMID(kActionIDSpace, kSplineAddPointToolActionID, kSplineUIPrefix + 5)
DECLARE_PMID(kActionIDSpace, kSplineRemovePointToolActionID, kSplineUIPrefix + 6)
DECLARE_PMID(kActionIDSpace, kPencilToolActionID, kSplineUIPrefix + 7)
DECLARE_PMID(kActionIDSpace, kEraseToolActionID, kSplineUIPrefix + 8)
DECLARE_PMID(kActionIDSpace, kSplineDirectionToolActionID, kSplineUIPrefix + 9)
DECLARE_PMID(kActionIDSpace, kScissorsToolActionID, kSplineUIPrefix + 10)
DECLARE_PMID(kActionIDSpace, kSmoothToolActionID, kSplineUIPrefix + 11)

DECLARE_PMID(kActionIDSpace, kToggleToAddAnchorPointActionID, kSplineUIPrefix + 12)
DECLARE_PMID(kActionIDSpace, kToggleToDeleteAnchorPointActionID, kSplineUIPrefix + 13)

 
DECLARE_PMID(kActionIDSpace, kIntersectPathActionID, kSplineUIPrefix + 15)
DECLARE_PMID(kActionIDSpace, kUnionPathActionID, kSplineUIPrefix + 16)
DECLARE_PMID(kActionIDSpace, kDifferencePathActionID, kSplineUIPrefix + 17)
DECLARE_PMID(kActionIDSpace, kReverseDiffPathActionID, kSplineUIPrefix + 18)
DECLARE_PMID(kActionIDSpace, kXorPathActionID, kSplineUIPrefix + 19)

DECLARE_PMID(kActionIDSpace, kCompoundPathsSepActionID, kSplineUIPrefix + 20)

DECLARE_PMID(kActionIDSpace, kConvertToNormalRectActionID, kSplineUIPrefix + 21)
DECLARE_PMID(kActionIDSpace, kConvertToRoundedRectActionID, kSplineUIPrefix + 22)
DECLARE_PMID(kActionIDSpace, kConvertToBevelRectActionID, kSplineUIPrefix + 23)
DECLARE_PMID(kActionIDSpace, kConvertToInverseRoundedRectActionID, kSplineUIPrefix + 24)
DECLARE_PMID(kActionIDSpace, kConvertToFancyRectActionID, kSplineUIPrefix + 25)
DECLARE_PMID(kActionIDSpace, kConvertToEllipseActionID, kSplineUIPrefix + 26)
DECLARE_PMID(kActionIDSpace, kConvertToTriangleActionID, kSplineUIPrefix + 27)
DECLARE_PMID(kActionIDSpace, kConvertToPolygonActionID, kSplineUIPrefix + 28)
DECLARE_PMID(kActionIDSpace, kConvertToStraightLineActionID, kSplineUIPrefix + 29)
DECLARE_PMID(kActionIDSpace, kConvertToOrthogonalLineActionID, kSplineUIPrefix + 30)

DECLARE_PMID(kActionIDSpace, kConvertToOpenPathActionID, kSplineUIPrefix + 31)
DECLARE_PMID(kActionIDSpace, kConvertToClosedPathActionID, kSplineUIPrefix + 32)

DECLARE_PMID(kActionIDSpace, kConvertToLineEndPointActionID, kSplineUIPrefix + 33)
DECLARE_PMID(kActionIDSpace, kConvertToCornerPointActionID, kSplineUIPrefix + 34)
DECLARE_PMID(kActionIDSpace, kConvertToSmoothPointActionID, kSplineUIPrefix + 35)
DECLARE_PMID(kActionIDSpace, kConvertToSymmetricalPointActionID, kSplineUIPrefix + 36)

DECLARE_PMID(kActionIDSpace, kJoinEndPointActionID, kSplineUIPrefix + 37)
DECLARE_PMID(kActionIDSpace, kEndPathDrawingActionID, kSplineUIPrefix + 38)


// Path finder panel
DECLARE_PMID(kActionIDSpace, kPathFinderPanelActionID, kSplineUIPrefix + 39) 
DECLARE_PMID(kActionIDSpace, kCompoundPathSepActionID, kSplineUIPrefix + 40) 

DECLARE_PMID(kActionIDSpace, kDeletePointsActionID, kSplineUIPrefix + 41)

//---------------------------------------------------
// InvalHandlerTypeID
//---------------------------------------------------
DECLARE_PMID(kInvalHandlerIDSpace, kSplineStateInvalHandlerID, kSplineUIPrefix + 1)

 
END_IDS()
#endif // __SplineUIID__
