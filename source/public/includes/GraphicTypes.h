//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/GraphicTypes.h $
//  
//  Owner: jargast
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
#ifndef __GraphicTypes__
#define __GraphicTypes__

// Constants to use in IGraphicsPort and the graphic attributes

enum PMJoinType
{
	kPMMiterJoin = 0,
	kPMRoundJoin,	
	kPMBevelJoin	
};

enum PMEndCap
{
	kPMButtCap = 0,
	kPMRoundCap,		
	kPMSquareCap	
};

// Fitting
enum
{
	kPMNoFitting = 0,
	kPMFitContents = 1,
	kPMFitContentsProportionally = 2,
	kPMFillContentsProportionally = 3,
	kPMCenterContents = 4
};

// Hit testing
enum
{
	kPMNoHit = 0,
	kPMHit
};

// image flags
enum
{
	kPMImIsMask = 1
};

// color space
enum
{
	//kPMCsUndefined = -1,
	//kPMCsDeviceGray,
	//kPMCsDeviceRGB,
	//kPMCsDeviceCMYK,
	kPMCsUnused = 3,
	//kPMCsCalGray,
	kPMCsCalRGB = 5,
	kPMCsCalCMYK,
	kPMCsLab,
	kPMCsSeparation,
	kPMCsDeviceN = 9,
	//kPMCsIndexed,
	//kPMCsPattern,
	//kPMCsICCBased,
	//kPMCsUnknownProfile
    kPMCsCalHSB = 14
};

enum
{
	kPMCsMaxComponents = 32
};

// Gradient Type
enum GradientType
{
	kAxial = 1,
	kRadial
};
DECLARE_BASE_TYPE(GradientType);


// Blending modes
enum PMBlendingMode
{
	kPMBlendNormal,
	
	kPMBlendMultiply,
	kPMBlendScreen,
	kPMBlendOverlay,
	kPMBlendSoftLight,
	kPMBlendHardLight,
	
	kPMBlendColorDodge,
	kPMBlendColorBurn,
	
	kPMBlendDarken,
	kPMBlendLighten,
	kPMBlendDifference,
	kPMBlendExclusion,
	
	kPMBlendHue,
	kPMBlendSaturation,
	kPMBlendColor,
	kPMBlendLuminosity,
	
	kPMBlendNonZeroOverprint,
	
	kPMNumBlendingModes,
	kPMBlendingModeInvalid = -1,
	_MAX_PMBlendingMode = 0x40000000  /* force 32 bit enum */
} ;

enum PMDropShadowMode
{
	kDSMNone,
	kDSMBlurred,

	kDSMInvalid = -1,
	_MAX_PMDropShadowMode = 0x40000000  /* force 32 bit enum */
} ;

enum PMVignetteMode
{
	kVTMNone,
	kVTMRectangular,
	kVTMElliptical,
	kVTMFollowShape,
	
	kVTMInvalid = -1,
	_MAX_PMVignetteMode = 0x40000000  /* force 32 bit enum */
} ;

enum PMVignetteCorners
{
	kVTCSharp,
	kVTCSoft,
	kVTCDiffusion,	// i.e., AI-compatible
	
	kVTInvalidCorners = -1,
	_MAX_PMVignetteCorners = 0x40000000  /* force 32 bit enum */
};

enum PMGlowTechnique
{
	kGLTechniqueSofter,
	kGLTechniquePrecise,

	kGLTechniqueInvalid = -1,
	_MAX_PM = 0x40000000  /* force 32 bit enum */
};

enum PMInnerGlowSource
{
	kIGSourceCenter,
	kIGSourceEdge,
	
	kIGSourceInvalid = -1,
	_MAX_PMInnerGlowSource = 0x40000000  /* force 32 bit enum */
};

enum PMBevelEmbossStyle
{
	kBEStyleOuterBevel,
	kBEStyleInnerBevel,
	kBEStyleEmboss,
	kBEStylePillowEmboss,
	
	kBEStyleInvalid = -1,
	_MAX_PMBevelEmbossStyle = 0x40000000  /* force 32 bit enum */
};

enum PMBevelEmbossTechnique
{
	kBETechniqueSmooth,
	kBETechniqueChiselHard,
	kBETechniqueChiselSoft,

	kBETechniqueInvalid = -1,
	_MAX_BETechnique = 0x40000000  /* force 32 bit enum */
};

enum PMBevelEmbossDirection
{
	kBEDirectionUp,
	kBEDirectionDown,
	
	kBEDirectionInvalid = -1,
	_MAX_PMBevelEmbossDirection = 0x40000000  /* force 32 bit enum */
};

enum PMFollowShapeMode
{
	kFollowShapeNone,
	kFollowShapeLeadingEdge,
	kFollowShapeAllEdges,
	
	kFollowShapeInvalid = -1,
	_MAX_PMFollowShapeMode = 0x40000000  /* force 32 bit enum */
};

enum PMStrokeAlignment
{
	kStrokeAlignCenter,		// Align to path center (default)
	kStrokeAlignInside,
	kStrokeAlignOutside,

	kMAXPMStrokeAlignment = 0x40000000		// Force 32-bit enum (not a valid stroke alignment)
};

enum PMArrowHeadAlignment
{
	kArrowHeadInside = 0,
	kArrowHeadOutside
};

#endif
