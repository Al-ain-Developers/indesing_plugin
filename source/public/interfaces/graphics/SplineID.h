//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/SplineID.h $
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
//========================================================================================

#ifndef __SplineID__
#define __SplineID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"
#include "FormatNumber.h"

#define kSplinePrefix					RezLong(0x6200)

// PluginID
#define kSplinePluginName 				"Spline"
DECLARE_PMID(kPlugInIDSpace, kSplinePluginID, kSplinePrefix + 1)

// Rsrc IDs
#define kSplineStringsRsrcID 					1300
#define kSplineStringsNoTransRsrcID 			1400

// ClassIDs
//
DECLARE_PMID(kClassIDSpace, kSplineItemBoss, kSplinePrefix + 1)
//gap
DECLARE_PMID(kClassIDSpace, kCurveFitBoss, kSplinePrefix + 4)
//DECLARE_PMID(kClassIDSpace, kScissorsToolKBSCBoss, kSplinePrefix + 12) removed per Lance
//gap

// Commands
DECLARE_PMID(kClassIDSpace, kRemoveAllPathsCmdBoss, kSplinePrefix + 14)
// DECLARE_PMID(kClassIDSpace, kSelectAllPathsCmdBoss, kSplinePrefix + 15)	unused, removed 1/27/03 by richg
DECLARE_PMID(kClassIDSpace, kMoveRelativePathPointsCmdBoss, kSplinePrefix + 16)
DECLARE_PMID(kClassIDSpace, kSkewPathPointsCmdBoss, kSplinePrefix + 17)
DECLARE_PMID(kClassIDSpace, kScalePathPointsCmdBoss, kSplinePrefix + 18)
DECLARE_PMID(kClassIDSpace, kRotatePathPointsCmdBoss, kSplinePrefix + 19)
DECLARE_PMID(kClassIDSpace, kAddSplinePointsCmdBoss, kSplinePrefix + 20	)

DECLARE_PMID(kClassIDSpace, kRemoveSplinePointsCmdBoss, kSplinePrefix + 21)
DECLARE_PMID(kClassIDSpace, kModifyPathPointsCmdBoss, kSplinePrefix + 22)
DECLARE_PMID(kClassIDSpace, kOpenPathCmdBoss, kSplinePrefix + 23)
DECLARE_PMID(kClassIDSpace, kClosePathCmdBoss, kSplinePrefix + 24)
DECLARE_PMID(kClassIDSpace, kSplineM2MListenerServiceBoss, kSplinePrefix + 25)
DECLARE_PMID(kClassIDSpace, kSetSplineFramePointsCmdBoss, kSplinePrefix + 26)
//DECLARE_PMID(kClassIDSpace, kSelectAnchorCmdBoss, kSplinePrefix + 27)
DECLARE_PMID(kClassIDSpace, kReversePathCmdBoss, kSplinePrefix + 28)
DECLARE_PMID(kClassIDSpace, kMakeCompoundPathCmdBoss, kSplinePrefix + 29)
DECLARE_PMID(kClassIDSpace, kReleaseCompoundPathCmdBoss, kSplinePrefix + 30)

DECLARE_PMID(kClassIDSpace, kRemoveAllButOnePathCmdBoss, kSplinePrefix + 31)
DECLARE_PMID(kClassIDSpace, kReleasePathsCmdBoss, kSplinePrefix + 32)
DECLARE_PMID(kClassIDSpace, kRemovePathCmdBoss, kSplinePrefix + 33)
DECLARE_PMID(kClassIDSpace, kLinkChangedCmdBoss, kSplinePrefix + 34)
DECLARE_PMID(kClassIDSpace, kCurveFitCmdBoss, kSplinePrefix + 35)
DECLARE_PMID(kClassIDSpace, kSetPencilPrefsCmdBoss, kSplinePrefix + 36)
DECLARE_PMID(kClassIDSpace, kSetSmoothPrefsCmdBoss, kSplinePrefix + 37)
DECLARE_PMID(kClassIDSpace, kModifyMultiplePathPointsCmdBoss, kSplinePrefix +38)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kSplinePrefix + 39)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kSplinePrefix + 40)

// gap 41-60

DECLARE_PMID(kClassIDSpace, kSplineConversionProviderBoss, kSplinePrefix + 61)
DECLARE_PMID(kClassIDSpace, kSplineCodeConversionProviderBoss, kSplinePrefix + 62)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kSplinePrefix + 63)

// commands
DECLARE_PMID(kClassIDSpace, kTransformPathPointsCmdBoss, kSplinePrefix + 64)
DECLARE_PMID(kClassIDSpace, kReleaseClipboardPathCmdBoss, kSplinePrefix + 65)
DECLARE_PMID(kClassIDSpace, kConvertShapeCmdBoss, kSplinePrefix + 66)
DECLARE_PMID(kClassIDSpace, kJoinPathCmdBoss, kSplinePrefix + 67)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kSplinePrefix + 68)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kSplinePrefix + 69)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kSplinePrefix + 70)

//gap 71-80

//scripting
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kSplinePrefix + 81)
DECLARE_PMID(kClassIDSpace, kPathScriptProviderBoss, kSplinePrefix + 82)
DECLARE_PMID(kClassIDSpace, kPathScriptObjectBoss, kSplinePrefix + 83)
DECLARE_PMID(kClassIDSpace, kPointScriptProviderBoss, kSplinePrefix + 84)
DECLARE_PMID(kClassIDSpace, kPointScriptObjectBoss, kSplinePrefix + 85)

DECLARE_PMID(kClassIDSpace, kMergePathCmdBoss, kSplinePrefix + 86)

// Implementation IDs
//
DECLARE_PMID(kImplementationIDSpace, kSplinePageItemImpl, kSplinePrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kSplineDataImpl, kSplinePrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kSplineShapeImpl, kSplinePrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kSplineScriptImpl, kSplinePrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kSplineConversionProviderImpl, kSplinePrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kSplineItemFlattenerUsageImpl, kSplinePrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kGeometrySplineImpl, kSplinePrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kSplineM2MListenerImpl, kSplinePrefix + 8)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kSplinePrefix + 9)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kSplinePrefix + 10)

DECLARE_PMID(kImplementationIDSpace, kCurveFitImpl, kSplinePrefix + 11)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kSplinePrefix + 12)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kSplinePrefix + 13)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kSplinePrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kSplinePlaceBehaviorImpl, kSplinePrefix + 15)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kSplinePrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kSplineItemInkResourcesImpl, kSplinePrefix + 17)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kSplinePrefix + 18)
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kSplinePrefix + 19)

// Commands
DECLARE_PMID(kImplementationIDSpace, kAddSplinePointsCmdImpl, kSplinePrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kRemoveSplinePointsCmdImpl, kSplinePrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kModifyPathPointsCmdImpl, kSplinePrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kModifyPathPointsCmdDataImpl, kSplinePrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kOpenPathCmdImpl, kSplinePrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kClosePathCmdImpl, kSplinePrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kSetSplineFramePointsCmdImpl, kSplinePrefix + 26)
//DECLARE_PMID(kImplementationIDSpace, kSelectAnchorCmdImpl, kSplinePrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kSplineStateDocSignalProviderImpl, kSplinePrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kReversePathCmdImpl, kSplinePrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kMakeCompoundPathCmdImpl, kSplinePrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kReleaseCompoundPathCmdImpl, kSplinePrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kRemoveAllButOnePathCmdImpl, kSplinePrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kReleasePathsCmdImpl, kSplinePrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kRemovePathCmdImpl, kSplinePrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kLinkChangedCmdImpl, kSplinePrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kCurveFitCmdImpl, kSplinePrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kCurveFitCmdDataImpl, kSplinePrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kSetPencilPrefsCmdImpl, kSplinePrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kSetPencilPrefsCmdDataImpl, kSplinePrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kConvertShapeCmdImpl, kSplinePrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kConvertShapeCmdDataImpl, kSplinePrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kJoinPathPointCmdImpl, kSplinePrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kJoinPathPointsCmdDataImpl, kSplinePrefix + 43)


// KBSC
// available DECLARE_PMID(kImplementationIDSpace, kToggleAddDeletePointKBSCImpl, kSplinePrefix + 75)

//More implementations
DECLARE_PMID(kImplementationIDSpace, kSessionPencilPrefsImpl, kSplinePrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kDocPencilPrefsImpl, kSplinePrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kSessionSmoothPrefsImpl, kSplinePrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kDocSmoothPrefsImpl, kSplinePrefix + 86)
// gap
DECLARE_PMID(kImplementationIDSpace, kFreeformDlgControllerImpl, kSplinePrefix + 89)
DECLARE_PMID(kImplementationIDSpace, kSetSmoothPrefsCmdImpl, kSplinePrefix + 90		)
DECLARE_PMID(kImplementationIDSpace, kModifyMultiplePathPointsCmdImpl, kSplinePrefix + 94)
// gap
DECLARE_PMID(kImplementationIDSpace, kMoveRelativePathPointsCmdImpl, kSplinePrefix + 98)
DECLARE_PMID(kImplementationIDSpace, kTransformPathPointsCmdImpl, kSplinePrefix + 99)
// DECLARE_PMID(kImplementationIDSpace, kSelectAllPathsCmdImpl, kSplinePrefix + 100) 	unused, removed 1/27/03 by richg
DECLARE_PMID(kImplementationIDSpace, kRemoveAllPathsCmdImpl, kSplinePrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kReleaseClipboardPathCmdImpl, kSplinePrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kSplineUtilsImpl, kSplinePrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kSplinePasteBehaviorImpl, kSplinePrefix + 104)

//Scripting
DECLARE_PMID(kImplementationIDSpace, kPathScriptProviderImpl, kSplinePrefix + 180)
DECLARE_PMID(kImplementationIDSpace, kPathScriptImpl, kSplinePrefix + 181)
DECLARE_PMID(kImplementationIDSpace, kPathPointScriptUtilsImpl, kSplinePrefix + 182 )
DECLARE_PMID(kImplementationIDSpace, kPointScriptProviderImpl, kSplinePrefix + 183)
DECLARE_PMID(kImplementationIDSpace, kPointScriptImpl, kSplinePrefix + 184)
//gap
DECLARE_PMID(kImplementationIDSpace, kMergePathCmdImpl, kSplinePrefix + 187)
DECLARE_PMID(kImplementationIDSpace, kAlignedPathGeometryImpl, kSplinePrefix + 188)

// IIDs
//
DECLARE_PMID(kInterfaceIDSpace, IID_IMODIFYPATHPOINTSCMDDATA, kSplinePrefix + 1)
// gap
// gap
DECLARE_PMID(kInterfaceIDSpace, IID_ICURVEFIT, kSplinePrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_ICURVEFITCMDDATA, kSplinePrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IPENCILPREFS, kSplinePrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETPENCILPREFSCMDDATA, kSplinePrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ISMOOTHPREFS, kSplinePrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHDESELECTIONLIST, kSplinePrefix + 9)	//Used by kSelectAnchorCmdBoss to query for its second IPathSelectionList interface
DECLARE_PMID(kInterfaceIDSpace, IID_IOLDPATHSELECTIONLIST, kSplinePrefix + 10)	//Used by kSelectAnchorCmdBoss to query for its third IPathSelectionList interface
DECLARE_PMID(kInterfaceIDSpace, IID_ISPLINEUTILS, kSplinePrefix + 11)	
DECLARE_PMID(kInterfaceIDSpace, IID_IALIGNEDPATHGEOMETRY, kSplinePrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHPOINTSCRIPTUTILS, kSplinePrefix + 13 )
DECLARE_PMID(kInterfaceIDSpace, IID_ICONVERTSHAPECMDDATA, kSplinePrefix + 14 )
DECLARE_PMID(kInterfaceIDSpace, IID_IJOINPATHPOINTSCMDDATA, kSplinePrefix + 15 )

// <Widget ID>
//

// <Action ID>
//
//
//Script Element IDs
//

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kPathObjectScriptElement,					kSplinePrefix + 10)
DECLARE_PMID(kScriptInfoIDSpace, kPathPointObjectScriptElement,				kSplinePrefix + 11)
DECLARE_PMID(kScriptInfoIDSpace, kSplineItemObjectScriptElement,			kSplinePrefix + 12)

//Events
DECLARE_PMID(kScriptInfoIDSpace, kReverseMethodScriptElement,				kSplinePrefix + 90)
DECLARE_PMID(kScriptInfoIDSpace, kReversePathMethodScriptElement,			kSplinePrefix + 91)
DECLARE_PMID(kScriptInfoIDSpace, kJoinPathMethodScriptElement,				kSplinePrefix + 92)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kPathTypePropertyScriptElement,			kSplinePrefix + 160)
DECLARE_PMID(kScriptInfoIDSpace, kEntirePathPropertyScriptElement,			kSplinePrefix + 161)
DECLARE_PMID(kScriptInfoIDSpace, kPointTypePropertyScriptElement,			kSplinePrefix + 162)
DECLARE_PMID(kScriptInfoIDSpace, kLeftDirectionPropertyScriptElement,		kSplinePrefix + 163)
DECLARE_PMID(kScriptInfoIDSpace, kRightDirectionPropertyScriptElement,		kSplinePrefix + 164)
DECLARE_PMID(kScriptInfoIDSpace, kAnchorPropertyScriptElement,				kSplinePrefix + 165)
DECLARE_PMID(kScriptInfoIDSpace, kJoinOptionEnumScriptElement,				kSplinePrefix + 166)


//Enums
DECLARE_PMID(kScriptInfoIDSpace, kPathTypeEnumScriptElement,				kSplinePrefix + 221)
DECLARE_PMID(kScriptInfoIDSpace, kPointTypeEnumScriptElement,				kSplinePrefix + 222)


//GUIDS
// {496F0BD6-7834-11d2-AAF0-00C04FA37726}
#define kPath_CLSID { 0x496f0bd6, 0x7834, 0x11d2, { 0xaa, 0xf0, 0x0, 0xc0, 0x4f, 0xa3, 0x77, 0x26 } }
// {496F0BD7-7834-11d2-AAF0-00C04FA37726}
#define kPaths_CLSID { 0x496f0bd7, 0x7834, 0x11d2, { 0xaa, 0xf0, 0x0, 0xc0, 0x4f, 0xa3, 0x77, 0x26 } }
// {A3736548-4F5C-11d2-AB07-00C04FA349C7}
#define kPoint_CLSID { 0xa3736548, 0x4f5c, 0x11d2, { 0xab, 0x7, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {496F0BD8-7834-11d2-AAF0-00C04FA37726}
#define kPoints_CLSID { 0x496f0bd8, 0x7834, 0x11d2, { 0xaa, 0xf0, 0x0, 0xc0, 0x4f, 0xa3, 0x77, 0x26 } }
// {77617578-D3DE-11d1-AAA6-00C04FA349C7}
#define kOval_CLSID { 0x77617578, 0xd3de, 0x11d1, { 0xaa, 0xa6, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {77617579-D3DE-11d1-AAA6-00C04FA349C7}
#define kOvals_CLSID { 0x77617579, 0xd3de, 0x11d1, { 0xaa, 0xa6, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {7761757A-D3DE-11d1-AAA6-00C04FA349C7}
#define kRectangle_CLSID { 0x7761757a, 0xd3de, 0x11d1, { 0xaa, 0xa6, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {7761757B-D3DE-11d1-AAA6-00C04FA349C7}
#define kRectangles_CLSID { 0x7761757b, 0xd3de, 0x11d1, { 0xaa, 0xa6, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {7761757C-D3DE-11d1-AAA6-00C04FA349C7}
#define kLine_CLSID { 0x7761757c, 0xd3de, 0x11d1, { 0xaa, 0xa6, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {7761757D-D3DE-11d1-AAA6-00C04FA349C7}
#define kLines_CLSID { 0x7761757d, 0xd3de, 0x11d1, { 0xaa, 0xa6, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {7761757E-D3DE-11d1-AAA6-00C04FA349C7}
#define kPolygon_CLSID { 0x7761757e, 0xd3de, 0x11d1, { 0xaa, 0xa6, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {7761757F-D3DE-11d1-AAA6-00C04FA349C7}
#define kPolygons_CLSID { 0x7761757f, 0xd3de, 0x11d1, { 0xaa, 0xa6, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {BF2662C3-310F-4b2b-B0F7-044E172735A2}
#define kSplineItem_CLSID { 0xbf2662c3, 0x310f, 0x4b2b, { 0xb0, 0xf7, 0x4, 0x4e, 0x17, 0x27, 0x35, 0xa2 } }
// {DC775DDE-6039-4595-8F7C-7FB8FE06372C}
#define kSplineItems_CLSID { 0xdc775dde, 0x6039, 0x4595, { 0x8f, 0x7c, 0x7f, 0xb8, 0xfe, 0x6, 0x37, 0x2c } }

enum SplineScriptIDs
{
	c_Oval						= 'covl',	// cOval in AERegistry.h
	c_Ovals						= 'ovls',
	c_Rectangle					= 'crec',	// cRectangle in AERegistry.h
	c_Rectangles				= 'recs',
	c_GraphicLine				= 'glin',	// cGraphicLine in AERegistry.h
	c_GraphicLines				= 'lins',
	c_Polygon					= 'cpgn',	// cPolygon in AERegistry.h
	c_Polygons					= 'pgns',
	c_SplineItem				= 'SplI',
	c_SplineItems				= 'Spls',
} ;

#endif // __SplineID__
