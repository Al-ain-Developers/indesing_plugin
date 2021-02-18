//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IXPAttributeSuite.h $
//  
//  Owner: SusanCL
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
#ifndef __IXPAttributeSuite__
#define __IXPAttributeSuite__

#include "ISelectionMessages.h"
#include "IXPSetVignetteCmdData.h"
#include "IXPSetBasicAttributesCmdData.h"
#include "IXPSetDropShadowCmdData.h"
#include "IOpacityGradientStops.h"
#include "GraphicTypes.h"
#include "K2Vector.h"
#include "PMPoint.h"

#include "XPID.h"

/**	These constants specifies the various default settings for related transparency attributes.
	kDefaultBasicBlendMode			default blending mode is normal
	kDefaultBasicOpacity			default opacity value is 100%
	kDefaultBasicKnockoutGroup		default knockout group setting is set to false
	kDefaultBasicKnockoutGroup		default isolation setting is set to false
	kDefaultDSMode					default dropshadow apply mode is none
	kDefaultDSBlendMode				default dropshadow blending mode is multiply
	kDefaultDSOpacity				default dropshadow opacity value is 75%
	kDefaultDSOffsetX				default dropshadow x offset value 7
	kDefaultDSOffsetY				default dropshadow y offset value 7
	kDefaultDSBlurRadius			default dropshadow blur radius value 5
	kDefaultDSColorUID				default dropshadow color is none
	kDefaultDSSpread				default dropshadow spread value 0
	kDefaultDSNoise					default dropshadow noise value 0
	kDefaultVignetteMode			default feather apply mode is none 
	kDefaultVignetteWidth			default feather width is 9
	kDefaultVignetteOuterOpacity	default feather outer opacity is 0
	kDefaultVignetteInnerOpacity	default feather inner opacity is 100%
	kDefaultVignetteCorners			default feather corner type is diffusion 
	kDefaultVignetteNoise			default feather noise is 0 
*/
const PMReal			kDefaultRealNumberValue	= 0.0;
const int32				kDefaultInt32Value		= 0;

const PMBlendingMode	kDefaultBasicBlendMode			= kPMBlendNormal;
const PMReal			kDefaultBasicOpacity			= 100.0;
const bool32			kDefaultBasicKnockoutGroup		= kFalse;
const bool32			kDefaultBasicIsolationGroup		= kFalse;
const PMDropShadowMode	kDefaultDSMode					= kDSMNone;
const PMBlendingMode	kDefaultDSBlendMode				= kPMBlendMultiply;
const PMReal			kDefaultDSOpacity				= 75.;
const PMReal			kDefaultDSOffsetX				= 7.;
const PMReal			kDefaultDSOffsetY				= 7.;
const PMReal			kDefaultDSBlurRadius			= 5.;
const PMReal			kDefaultDSSpread				= 0.;
const PMReal			kDefaultDSNoise					= 0.;
const UID				kDefaultDSColorUID				= kInvalidUID;
const PMVignetteMode	kDefaultVignetteMode			= kVTMNone;
const PMReal			kDefaultVignetteWidth			= 9.;
const PMReal			kDefaultVignetteOuterOpacity	= 0.;
const PMReal			kDefaultVignetteInnerOpacity	= 100.;
const PMVignetteCorners	kDefaultVignetteCorners			= kVTCDiffusion;
const PMReal			kDefaultVignetteNoise			= 0.;

const PMReal			kXPInvalidRealNumberValue	= -1.0;
const int32				kXPInvalidInt32Value		= -1;

class IGraphicStyleAttributeBossList;

/**	This is the high level transparency attribute suite for the current selection.
	Transparency attributes are graphic attributes and they are a subset of graphic attributes.
	Each transparency attribute ClassID mapped into a IXPAttributeSuite::AttributeType.
	Transparency attributes are furthered classified into groups: basic, drop shadow,
	feather/vignette, inner glow, etc.
	
	Only transparency attributes defined in XPID.h are handled by this suite.
	All other graphic attributes are ignored.
	
	@see also XPID.h
	@see also IGraphicStyleAttributeBossList
	@see also IGraphicAttributeInfo
*/
class IXPAttributeSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXPATTRIBUTESUITE };
	
	//________________________________________________________________________________________
	//	Data Types
	//________________________________________________________________________________________
	
	/** Transparency attributes can be applied to page items, stroke, fill, and content, independently.
	*/

	enum AttributeTarget
	{
		kTargetInvalid,

		kTargetPageItem,
		kTargetStroke,
		kTargetFill,
		kTargetContent,
		
		kMaxTarget
	};

	/**	Transparency attributes are arranged into groups, as follows.
	*/

	enum AttributeGroup
	{
		kGroupInvalid = -1,

		kGroupBlending,
		kGroupDropShadow,
		kGroupFeather,
		kGroupInnerShadow,
		kGroupOuterGlow,
		kGroupInnerGlow,
		kGroupBevelEmboss,
		kGroupSatin,
		kGroupDirectionalFeather,
		kGroupGradientFeather,
		
		kMaxGroup
	};

	/** The following data types are used for transparency attribute values.
	*/
	enum AttributeDataType
	{										// Class					Attribute Type
		kDataTypeInvalid = -1,				// ------------------------ ---------------
		kDataTypeColor,						// UID (of swatch)			PersistUID
		kDataTypeBoolean,					// bool16					Boolean
		kDataTypeReal,						// PMReal					RealNumber
		kDataTypePMBlendingMode,			// PMBlendingMode			int32
		kDataTypePMDropShadowMode,			// PMDropShadowMode			int32
		kDataTypePMVignetteMode,			// PMVignetteMode			int32
		kDataTypePMVignetteCorners,			// PMVignetteCorners		int32
		kDataTypePMGlowTechnique,			// PMGlowTechnique			int32
		kDataTypePMInnerGlowSource,			// PMInnerGlowSource		int32
		kDataTypePMBevelEmbossStyle,		// PMBevelEmbossStyle		int32
		kDataTypePMBevelEmbossTechnique,	// PMBevelEmbossTechnique	int32
		kDataTypePMBevelEmbossDirection,	// PMBevelEmbossDirection	int32
		kDataTypePMFollowShapeMode,			// PMFollowShapeMode		int32
		kDataTypeGradientType,				// GradientType				int32
		kDataTypeOpacityGradientStops,		// OpacityGradientStops		OpacityGradientStops
		kDataTypePoint						// PMPoint					PMPoint
	};

	/** The following are the kinds of real values that are used in transparency attributes.
		These are used to control formatting, min/max values, and so on.
	*/
	typedef enum
	{
		kRealKindInvalid,

		kRealKindXOffset,
		kRealKindYOffset,
		kRealKindDistance,
		kRealKindPercentage,
		kRealKindBlurWidth,
		kRealKindAngle,
		kRealKindAltitude,
		kRealKindEmbossDepth,
		kRealKindSoftenAmount,
		kRealKindFeatherWidth

	} AttributeRealKind;

	/** Helper class to carry any possible attribute value.  Cuts down on the need to have
		different get/set calls for each type of attribute, since there are so many different
		attributes.
	*/
	class AttributeValue
	{
	public:
		typedef object_type data_type;

	private:
		AttributeDataType		fDataType;
		int32					fInt32Value;
		PMReal					fRealValue;
		UID						fUIDValue;
		bool16					fBoolValue;
		IOpacityGradientStops*	fGradientValue;
		PMPoint					fPointValue;

	public:
		AttributeValue()							: fDataType(kDataTypeInvalid), fInt32Value(0), fRealValue(0), fUIDValue(kInvalidUID), fBoolValue(kFalse), fGradientValue(nil) {}
		AttributeValue(const AttributeValue& x)		: fGradientValue(nil) { *this = x; }
		AttributeValue(UID x)						: fDataType(kDataTypeColor), fUIDValue(x), fInt32Value(0), fRealValue(0), fBoolValue(kFalse), fGradientValue(nil) {}
		AttributeValue(bool16 x)					: fDataType(kDataTypeBoolean), fBoolValue(x), fInt32Value(0), fRealValue(0), fUIDValue(kInvalidUID), fGradientValue(nil) {}
		AttributeValue(PMReal x)					: fDataType(kDataTypeReal), fRealValue(x), fInt32Value(0), fUIDValue(kInvalidUID), fBoolValue(kFalse), fGradientValue(nil) {}
		AttributeValue(PMBlendingMode x)			: fDataType(kDataTypePMBlendingMode), fInt32Value((int32)x), fRealValue(0), fUIDValue(kInvalidUID), fBoolValue(kFalse), fGradientValue(nil) {}
		AttributeValue(PMDropShadowMode x)			: fDataType(kDataTypePMDropShadowMode), fInt32Value((int32)x), fRealValue(0), fUIDValue(kInvalidUID), fBoolValue(kFalse), fGradientValue(nil) {}
		AttributeValue(PMVignetteMode x)			: fDataType(kDataTypePMVignetteMode), fInt32Value((int32)x), fRealValue(0), fUIDValue(kInvalidUID), fBoolValue(kFalse), fGradientValue(nil) {}
		AttributeValue(PMVignetteCorners x)			: fDataType(kDataTypePMVignetteCorners), fInt32Value((int32)x), fRealValue(0), fUIDValue(kInvalidUID), fBoolValue(kFalse), fGradientValue(nil) {}
		AttributeValue(PMGlowTechnique x)			: fDataType(kDataTypePMGlowTechnique), fInt32Value((int32)x), fRealValue(0), fUIDValue(kInvalidUID), fBoolValue(kFalse), fGradientValue(nil) {}
		AttributeValue(PMInnerGlowSource x)			: fDataType(kDataTypePMInnerGlowSource), fInt32Value((int32)x), fRealValue(0), fUIDValue(kInvalidUID), fBoolValue(kFalse), fGradientValue(nil) {}
		AttributeValue(PMBevelEmbossStyle x)		: fDataType(kDataTypePMBevelEmbossStyle), fInt32Value((int32)x), fRealValue(0), fUIDValue(kInvalidUID), fBoolValue(kFalse), fGradientValue(nil) {}
		AttributeValue(PMBevelEmbossTechnique x)	: fDataType(kDataTypePMBevelEmbossTechnique), fInt32Value((int32)x), fRealValue(0), fUIDValue(kInvalidUID), fBoolValue(kFalse), fGradientValue(nil) {}
		AttributeValue(PMBevelEmbossDirection x)	: fDataType(kDataTypePMBevelEmbossDirection), fInt32Value((int32)x), fRealValue(0), fUIDValue(kInvalidUID), fBoolValue(kFalse), fGradientValue(nil) {}
		AttributeValue(PMFollowShapeMode x)			: fDataType(kDataTypePMFollowShapeMode), fInt32Value((int32)x), fRealValue(0), fUIDValue(kInvalidUID), fBoolValue(kFalse), fGradientValue(nil) {}
		AttributeValue(GradientType x)				: fDataType(kDataTypeGradientType), fInt32Value((int32)x), fRealValue(0), fUIDValue(kInvalidUID), fBoolValue(kFalse), fGradientValue(nil) {}
		AttributeValue(IOpacityGradientStops* x)	: fDataType(kDataTypeOpacityGradientStops), fInt32Value(0), fRealValue(0), fUIDValue(kInvalidUID), fBoolValue(kFalse), fGradientValue(x) { if (x) x->AddRef(); }
		AttributeValue(const PMPoint& x)			: fDataType(kDataTypePoint), fPointValue(x), fRealValue(0), fInt32Value(0), fUIDValue(kInvalidUID), fBoolValue(kFalse), fGradientValue(nil) {}

		~AttributeValue() { if (fGradientValue) fGradientValue->Release(); }
		
	public:
		/** These can be used to set up in a manual fashion.. not really recommended, though, 
			except for internal code, since it doesn't use type information to your advantage
			the way the constructors do.  It's possible to set up invalid combinations through
			these API.
		*/
		void SetDataType(AttributeDataType t) { fDataType = t; }
		void SetInt32Data(int32 x) { fInt32Value = x; }
		void SetRealData(PMReal x) { fRealValue = x; }
		void SetBooleanData(bool16 x) { fBoolValue = x; }
		void SetUIDData(UID x) { fUIDValue = x; }
		void SetOpacityGradientStopsData(IOpacityGradientStops* x) { if (fGradientValue) fGradientValue->Release(); fGradientValue = x; if (x) x->AddRef(); }
		void SetPointData(const PMPoint& x) { fPointValue = x; }

	public:
		AttributeDataType GetDataType() const { return fDataType; }
		int32 GetInt32Data() const { return fInt32Value; }
		PMReal GetRealData() const { return fRealValue; }
		bool16 GetBooleanData() const { return fBoolValue; }
		UID GetUIDData() const { return fUIDValue; }
		const PMPoint& GetPointData() const { return fPointValue; }

	public:
		UID						GetColor()					const { if (fDataType == kDataTypeColor) return fUIDValue; ASSERT_FAIL("Wrong type."); return kInvalidUID; }
		bool16					GetBoolean()				const { if (fDataType == kDataTypeBoolean) return fBoolValue; ASSERT_FAIL("Wrong type."); return kFalse; }
		PMReal					GetReal()					const { if (fDataType == kDataTypeReal) return fRealValue; ASSERT_FAIL("Wrong type."); return 0; }
		PMBlendingMode			GetPMBlendingMode()			const { if (fDataType == kDataTypePMBlendingMode) return (PMBlendingMode)fInt32Value; ASSERT_FAIL("Wrong type."); return (PMBlendingMode)-1; }
		PMDropShadowMode		GetPMDropShadowMode()		const { if (fDataType == kDataTypePMDropShadowMode) return (PMDropShadowMode)fInt32Value; ASSERT_FAIL("Wrong type."); return (PMDropShadowMode)-1; }
		PMVignetteMode			GetPMVignetteMode()			const { if (fDataType == kDataTypePMVignetteMode) return (PMVignetteMode)fInt32Value; ASSERT_FAIL("Wrong type."); return (PMVignetteMode)-1; }
		PMVignetteCorners		GetPMVignetteCorners()		const { if (fDataType == kDataTypePMVignetteCorners) return (PMVignetteCorners)fInt32Value; ASSERT_FAIL("Wrong type."); return (PMVignetteCorners)-1; }
		PMGlowTechnique			GetPMGlowTechnique()		const { if (fDataType == kDataTypePMGlowTechnique) return (PMGlowTechnique)fInt32Value; ASSERT_FAIL("Wrong type."); return (PMGlowTechnique)-1; }
		PMInnerGlowSource		GetPMInnerGlowSource()		const { if (fDataType == kDataTypePMInnerGlowSource) return (PMInnerGlowSource)fInt32Value; ASSERT_FAIL("Wrong type."); return (PMInnerGlowSource)-1; }
		PMBevelEmbossStyle		GetPMBevelEmbossStyle()		const { if (fDataType == kDataTypePMBevelEmbossStyle) return (PMBevelEmbossStyle)fInt32Value; ASSERT_FAIL("Wrong type."); return (PMBevelEmbossStyle)-1; }
		PMBevelEmbossTechnique	GetPMBevelEmbossTechnique()	const { if (fDataType == kDataTypePMBevelEmbossTechnique) return (PMBevelEmbossTechnique)fInt32Value; ASSERT_FAIL("Wrong type."); return (PMBevelEmbossTechnique)-1; }
		PMBevelEmbossDirection	GetPMBevelEmbossDirection()	const { if (fDataType == kDataTypePMBevelEmbossDirection) return (PMBevelEmbossDirection)fInt32Value; ASSERT_FAIL("Wrong type."); return (PMBevelEmbossDirection)-1; }
		PMFollowShapeMode		GetPMFollowShapeMode()		const { if (fDataType == kDataTypePMFollowShapeMode) return (PMFollowShapeMode)fInt32Value; ASSERT_FAIL("Wrong type."); return (PMFollowShapeMode)-1; }
		GradientType			GetGradientType()			const { if (fDataType == kDataTypeGradientType) return (GradientType)fInt32Value; ASSERT_FAIL("Wrong type."); return (GradientType)-1; }
		IOpacityGradientStops*	GetOpacityGradientStops() 	const { return fGradientValue; }
		IOpacityGradientStops*	QueryOpacityGradientStops() const { if (fGradientValue) fGradientValue->AddRef(); return fGradientValue; }
		const PMPoint&			GetPMPoint()				const { ASSERT(fDataType == kDataTypePoint); return fPointValue; }

	public:
		AttributeValue& operator=(const AttributeValue& rhs) 
			{ 
				fDataType = rhs.fDataType;
				fInt32Value = rhs.fInt32Value;
				fRealValue = rhs.fRealValue;
				fUIDValue = rhs.fUIDValue;
				fBoolValue = rhs.fBoolValue;
				fPointValue = rhs.fPointValue;
				
				if (fGradientValue) fGradientValue->Release();
				fGradientValue = rhs.fGradientValue;
				if (fGradientValue) fGradientValue->AddRef();
				
				return *this;
			};

		bool operator==(const AttributeValue& rhs) const
			{
				if (fDataType != rhs.fDataType) return kFalse;
				switch(fDataType)
				{
					case kDataTypeColor:
						return fUIDValue == rhs.fUIDValue;
					case kDataTypeBoolean:
						return fBoolValue == rhs.fBoolValue;
					case kDataTypeReal:
						return fRealValue == rhs.fRealValue;
					case kDataTypePMBlendingMode:
					case kDataTypePMDropShadowMode:
					case kDataTypePMVignetteMode:
					case kDataTypePMVignetteCorners:
					case kDataTypePMGlowTechnique:
					case kDataTypePMInnerGlowSource:
					case kDataTypePMBevelEmbossStyle:
					case kDataTypePMBevelEmbossTechnique:
					case kDataTypePMBevelEmbossDirection:
					case kDataTypePMFollowShapeMode:
					case kDataTypeGradientType:
						return fInt32Value == rhs.fInt32Value;
					case kDataTypeOpacityGradientStops:
						return ((fGradientValue == rhs.fGradientValue)
								|| (fGradientValue && rhs.fGradientValue && fGradientValue->Equals(rhs.fGradientValue))
								|| (fGradientValue && fGradientValue->Equals(rhs.fGradientValue))
								|| (rhs.fGradientValue && rhs.fGradientValue->Equals(fGradientValue)));
					case kDataTypePoint:
						return fPointValue == rhs.fPointValue;
					case kDataTypeInvalid:
						return kTrue;
				}
				return kTrue;
			};

		bool operator!=(const AttributeValue& rhs) const
			{ return !(*this == rhs); }

	};

	#define XP_MAX_ATTRS 100	// maximum number of attributes (per group)
	#define XP_MAX_GROUPS 100	// maximum number of groups (per target)
	#define BASE_XP_ATTR(t,x) ((int32)(x) * XP_MAX_ATTRS + (int32)(t) * XP_MAX_ATTRS * XP_MAX_GROUPS )

	enum AttributeType
		{
		kUnknownAttrType = -1,
		
		// Basic attributes, drop shadow attributes, vignette attributes:
		// Note: In principle these should all be rearranged and ordered
		// to put them in the correct group, but since this is a public 
		// header and they've had these values for a long time, I don't 
		// want to change them.  The remaining attributes are all clustered
		// so it's easy to determine which group they're in, plus we can add
		// new group-specific attributes without having to put them at the
		// end of the whole list.

										// AttributeDataType
										// --------------------------------
		kBSOpacity = 0,					// kDataTypeReal
		kBSBlendMode,					// kDataTypePMBlendingMode
		kBSKnockoutGroup,				// kDataTypeBoolean
		kBSIsolationGroup,				// kDataTypeBoolean
		kDSMode,						// kDataTypePMDropShadowMode
		kDSOffsetX,						// kDataTypeReal
		kDSOffsetY,						// kDataTypeReal
		kDSGray_Obsolete,				// obsolete; don't use
		kDSOpacity,						// kDataTypeReal
		kDSBlendMode,					// kDataTypePMBlendingMode
		kDSBlurRadius,					// kDataTypeReal
		kVTMode,						// kDataTypeVignetteMode
		kVTWidth,						// kDataTypeReal
		kVTOuterOpacity,				// obsolete; don't use
		kVTInnerOpacity,				// obsolete; don't use
		kVTCorners,						// kDataTypePMVignetteCorners
		kDSColor,						// kDataTypeColor
		kDSSpread,						// kDataTypeReal
		kDSNoise,						// kDataTypeReal
		kVTNoise,						// kDataTypeReal
	
		kDropShadowBaseID = BASE_XP_ATTR(kTargetPageItem, kGroupDropShadow),

		kDropShadowUseGlobalLight,		// kDataTypeBoolean
		kDropShadowKO,					// kDataTypeBoolean
		kDropShadowHonorFX,				// kDataTypeBoolean

		kFeatherBaseID = BASE_XP_ATTR(kTargetPageItem, kGroupFeather),

		kFeatherChoke,

		kInnerShadowBaseID = BASE_XP_ATTR(kTargetPageItem, kGroupInnerShadow), 

		kInnerShadowApply,				// kDataTypeBoolean
		kInnerShadowColor,				// kDataTypeColor
		kInnerShadowBlendMode,			// kDataTypePMBlendingMode
		kInnerShadowOpacity,			// kDataTypeReal
		kInnerShadowAngle,				// kDataTypeReal
		kInnerShadowDistance,			// kDataTypeReal
		kInnerShadowUseGlobalLight,		// kDataTypeBoolean
		kInnerShadowChoke,				// kDataTypeReal
		kInnerShadowSize,				// kDataTypeReal
		kInnerShadowNoise,				// kDataTypeReal

		kOuterGlowBaseID = BASE_XP_ATTR(kTargetPageItem, kGroupOuterGlow),

		kOuterGlowApply,				// kDataTypeBoolean
		kOuterGlowBlendMode,			// kDataTypePMBlendingMode
		kOuterGlowOpacity,				// kDataTypeReal
		kOuterGlowNoise,				// kDataTypeReal
		kOuterGlowColor,				// kDataTypeColor
		kOuterGlowTechnique,			// kDataTypePMGlowTechnique
		kOuterGlowSpread,				// kDataTypeReal
		kOuterGlowSize,					// kDataTypeReal

		kInnerGlowBaseID = BASE_XP_ATTR(kTargetPageItem, kGroupInnerGlow), 

		kInnerGlowApply,				// kDataTypeBoolean
		kInnerGlowBlendMode,			// kDataTypePMBlendingMode
		kInnerGlowOpacity,				// kDataTypeReal
		kInnerGlowNoise,				// kDataTypeReal
		kInnerGlowColor,				// kDataTypeColor
		kInnerGlowTechnique,			// kDataTypePMGlowTechnique
		kInnerGlowSpread,				// kDataTypeReal
		kInnerGlowSize,					// kDataTypeReal
		kInnerGlowSource,				// kDataTypePMInnerGlowSource

		kBevelEmbossBaseID = BASE_XP_ATTR(kTargetPageItem, kGroupBevelEmboss),

		kBevelEmbossApply,				// kDataTypeBoolean
		kBevelEmbossStyle,				// kDataTypePMBevelEmbossStyle
		kBevelEmbossTechnique,			// kDataTypePMBevelEmbossTechnique
		kBevelEmbossDepth,				// kDataTypeReal
		kBevelEmbossDirection,			// kDataTypePMBevelEmbossDirection
		kBevelEmbossSize,				// kDataTypeReal
		kBevelEmbossSoften,				// kDataTypeReal
		kBevelEmbossAngle,				// kDataTypeReal
		kBevelEmbossAltitude,			// kDataTypeReal
		kBevelEmbossUseGlobalLight,		// kDataTypeBoolean
		kBevelEmbossHighlightColor,		// kDataTypeColor
		kBevelEmbossHighlightBlendMode,	// kDataTypePMBlendingMode
		kBevelEmbossHighlightOpacity,	// kDataTypeReal
		kBevelEmbossShadowColor,		// kDataTypeColor
		kBevelEmbossShadowBlendMode,	// kDataTypePMBlendingMode
		kBevelEmbossShadowOpacity,		// kDataTypeReal

		kSatinBaseID = BASE_XP_ATTR(kTargetPageItem, kGroupSatin),

		kSatinApply,					// kDataTypeBoolean
		kSatinColor,					// kDataTypeColor
		kSatinBlendMode,				// kDataTypePMBlendingMode
		kSatinOpacity,					// kDataTypeReal
		kSatinAngle,					// kDataTypeReal
		kSatinDistance,					// kDataTypeReal
		kSatinSize,						// kDataTypeReal
		kSatinInvert,					// kDataTypeBoolean
		
		kDirectionalFeatherBaseID = BASE_XP_ATTR(kTargetPageItem, kGroupDirectionalFeather),

		kDirectionalFeatherApply,		// kDataTypeBoolean
		kDirectionalFeatherWidthLeft,	// kDataTypeReal
		kDirectionalFeatherWidthRight,	// kDataTypeReal
		kDirectionalFeatherWidthTop,	// kDataTypeReal
		kDirectionalFeatherWidthBottom,	// kDataTypeReal
		kDirectionalFeatherAngle,		// kDataTypeReal
		kDirectionalFeatherFollowShape,	// kDataTypeBoolean
		kDirectionalFeatherNoise,		// kDataTypeReal
		kDirectionalFeatherChoke,		// kDataTypeReal
		
		kGradientFeatherBaseID = BASE_XP_ATTR(kTargetPageItem, kGroupGradientFeather),
		
		kGradientFeatherApply,			// kDataTypeBoolean
		kGradientFeatherType,			// kDataTypeGradientType
		kGradientFeatherOpacityStops,	// kDataTypeOpacityGradientStops
		kGradientFeatherAngle,			// kDataTypeReal
		kGradientFeatherLength,			// kDataTypeReal
		kGradientFeatherCenter,			// kDataTypePoint
		kGradientFeatherRadius,			// kDataTypeReal
		kGradientFeatherHiliteAngle,	// kDataTypeReal
		kGradientFeatherHiliteLength,	// kDataTypeReal

		kStrokeBlendingBaseID = BASE_XP_ATTR(kTargetStroke, kGroupBlending),

		kStrokeBlendingOpacity,
		kStrokeBlendingBlendMode,
		kStrokeBlendingKnockoutGroup,
		kStrokeBlendingIsolationGroup,

		kStrokeDropShadowBaseID = BASE_XP_ATTR(kTargetStroke, kGroupDropShadow),

		kStrokeDropShadowMode,
		kStrokeDropShadowOffsetX,
		kStrokeDropShadowOffsetY,
		kStrokeDropShadowOpacity,
		kStrokeDropShadowBlendMode,
		kStrokeDropShadowBlurRadius,
		kStrokeDropShadowSpread,
		kStrokeDropShadowNoise,
		kStrokeDropShadowColor,
		kStrokeDropShadowUseGlobalLight,
		kStrokeDropShadowKO,
		kStrokeDropShadowHonorFX,

		kStrokeFeatherBaseID = BASE_XP_ATTR(kTargetStroke, kGroupFeather),

		kStrokeFeatherMode,
		kStrokeFeatherWidth,
		kStrokeFeatherCorners,
		kStrokeFeatherNoise,
		kStrokeFeatherChoke,

		kStrokeInnerShadowBaseID = BASE_XP_ATTR(kTargetStroke, kGroupInnerShadow), 

		kStrokeInnerShadowApply,				// kDataTypeBoolean
		kStrokeInnerShadowColor,				// kDataTypeColor
		kStrokeInnerShadowBlendMode,			// kDataTypePMBlendingMode
		kStrokeInnerShadowOpacity,				// kDataTypeReal
		kStrokeInnerShadowAngle,				// kDataTypeReal
		kStrokeInnerShadowDistance,				// kDataTypeReal
		kStrokeInnerShadowUseGlobalLight,		// kDataTypeBoolean
		kStrokeInnerShadowChoke,				// kDataTypeReal
		kStrokeInnerShadowSize,					// kDataTypeReal
		kStrokeInnerShadowNoise,				// kDataTypeReal

		kStrokeOuterGlowBaseID = BASE_XP_ATTR(kTargetStroke, kGroupOuterGlow),

		kStrokeOuterGlowApply,					// kDataTypeBoolean
		kStrokeOuterGlowBlendMode,				// kDataTypePMBlendingMode
		kStrokeOuterGlowOpacity,				// kDataTypeReal
		kStrokeOuterGlowNoise,					// kDataTypeReal
		kStrokeOuterGlowColor,					// kDataTypeColor
		kStrokeOuterGlowTechnique,				// kDataTypePMGlowTechnique
		kStrokeOuterGlowSpread,					// kDataTypeReal
		kStrokeOuterGlowSize,					// kDataTypeReal

		kStrokeInnerGlowBaseID = BASE_XP_ATTR(kTargetStroke, kGroupInnerGlow), 

		kStrokeInnerGlowApply,					// kDataTypeBoolean
		kStrokeInnerGlowBlendMode,				// kDataTypePMBlendingMode
		kStrokeInnerGlowOpacity,				// kDataTypeReal
		kStrokeInnerGlowNoise,					// kDataTypeReal
		kStrokeInnerGlowColor,					// kDataTypeColor
		kStrokeInnerGlowTechnique,				// kDataTypePMGlowTechnique
		kStrokeInnerGlowSpread,					// kDataTypeReal
		kStrokeInnerGlowSize,					// kDataTypeReal
		kStrokeInnerGlowSource,					// kDataTypePMInnerGlowSource

		kStrokeBevelEmbossBaseID = BASE_XP_ATTR(kTargetStroke, kGroupBevelEmboss),

		kStrokeBevelEmbossApply,				// kDataTypeBoolean
		kStrokeBevelEmbossStyle,				// kDataTypePMBevelEmbossStyle
		kStrokeBevelEmbossTechnique,			// kDataTypePMBevelEmbossTechnique
		kStrokeBevelEmbossDepth,				// kDataTypeReal
		kStrokeBevelEmbossDirection,			// kDataTypePMBevelEmbossDirection
		kStrokeBevelEmbossSize,					// kDataTypeReal
		kStrokeBevelEmbossSoften,				// kDataTypeReal
		kStrokeBevelEmbossAngle,				// kDataTypeReal
		kStrokeBevelEmbossAltitude,				// kDataTypeReal
		kStrokeBevelEmbossUseGlobalLight,		// kDataTypeBoolean
		kStrokeBevelEmbossHighlightColor,		// kDataTypeColor
		kStrokeBevelEmbossHighlightBlendMode,	// kDataTypePMBlendingMode
		kStrokeBevelEmbossHighlightOpacity,		// kDataTypeReal
		kStrokeBevelEmbossShadowColor,			// kDataTypeColor
		kStrokeBevelEmbossShadowBlendMode,		// kDataTypePMBlendingMode
		kStrokeBevelEmbossShadowOpacity,		// kDataTypeReal

		kStrokeSatinBaseID = BASE_XP_ATTR(kTargetStroke, kGroupSatin),

		kStrokeSatinApply,						// kDataTypeBoolean
		kStrokeSatinColor,						// kDataTypeColor
		kStrokeSatinBlendMode,					// kDataTypePMBlendingMode
		kStrokeSatinOpacity,					// kDataTypeReal
		kStrokeSatinAngle,						// kDataTypeReal
		kStrokeSatinDistance,					// kDataTypeReal
		kStrokeSatinSize,						// kDataTypeReal
		kStrokeSatinInvert,						// kDataTypeBoolean
				
		kStrokeDirectionalFeatherBaseID = BASE_XP_ATTR(kTargetStroke, kGroupDirectionalFeather),

		kStrokeDirectionalFeatherApply,			// kDataTypeBoolean
		kStrokeDirectionalFeatherWidthLeft,		// kDataTypeReal
		kStrokeDirectionalFeatherWidthRight,	// kDataTypeReal
		kStrokeDirectionalFeatherWidthTop,		// kDataTypeReal
		kStrokeDirectionalFeatherWidthBottom,	// kDataTypeReal
		kStrokeDirectionalFeatherAngle,			// kDataTypeReal
		kStrokeDirectionalFeatherFollowShape,	// kDataTypeBoolean
		kStrokeDirectionalFeatherNoise,			// kDataTypeReal
		kStrokeDirectionalFeatherChoke,			// kDataTypeReal

		kStrokeGradientFeatherBaseID = BASE_XP_ATTR(kTargetStroke, kGroupGradientFeather),
		
		kStrokeGradientFeatherApply,			// kDataTypeBoolean
		kStrokeGradientFeatherType,				// kDataTypeGradientType
		kStrokeGradientFeatherOpacityStops,		// kDataTypeOpacityGradientStops
		kStrokeGradientFeatherAngle,			// kDataTypeReal
		kStrokeGradientFeatherLength,			// kDataTypeReal
		kStrokeGradientFeatherCenter,			// kDataTypePoint
		kStrokeGradientFeatherRadius,			// kDataTypeReal
		kStrokeGradientFeatherHiliteAngle,		// kDataTypeReal
		kStrokeGradientFeatherHiliteLength,		// kDataTypeReal

		kFillBlendingBaseID = BASE_XP_ATTR(kTargetFill, kGroupBlending),

		kFillBlendingOpacity,
		kFillBlendingBlendMode,
		kFillBlendingKnockoutGroup,
		kFillBlendingIsolationGroup,

		kFillDropShadowBaseID = BASE_XP_ATTR(kTargetFill, kGroupDropShadow),

		kFillDropShadowMode,
		kFillDropShadowOffsetX,
		kFillDropShadowOffsetY,
		kFillDropShadowOpacity,
		kFillDropShadowBlendMode,
		kFillDropShadowBlurRadius,
		kFillDropShadowSpread,
		kFillDropShadowNoise,
		kFillDropShadowColor,
		kFillDropShadowUseGlobalLight,
		kFillDropShadowKO,
		kFillDropShadowHonorFX,

		kFillFeatherBaseID = BASE_XP_ATTR(kTargetFill, kGroupFeather),

		kFillFeatherMode,
		kFillFeatherWidth,
		kFillFeatherCorners,
		kFillFeatherNoise,
		kFillFeatherChoke,

		kFillInnerShadowBaseID = BASE_XP_ATTR(kTargetFill, kGroupInnerShadow), 

		kFillInnerShadowApply,					// kDataTypeBoolean
		kFillInnerShadowColor,					// kDataTypeColor
		kFillInnerShadowBlendMode,				// kDataTypePMBlendingMode
		kFillInnerShadowOpacity,				// kDataTypeReal
		kFillInnerShadowAngle,					// kDataTypeReal
		kFillInnerShadowDistance,				// kDataTypeReal
		kFillInnerShadowUseGlobalLight,			// kDataTypeBoolean
		kFillInnerShadowChoke,					// kDataTypeReal
		kFillInnerShadowSize,					// kDataTypeReal
		kFillInnerShadowNoise,					// kDataTypeReal

		kFillOuterGlowBaseID = BASE_XP_ATTR(kTargetFill, kGroupOuterGlow),

		kFillOuterGlowApply,					// kDataTypeBoolean
		kFillOuterGlowBlendMode,				// kDataTypePMBlendingMode
		kFillOuterGlowOpacity,					// kDataTypeReal
		kFillOuterGlowNoise,					// kDataTypeReal
		kFillOuterGlowColor,					// kDataTypeColor
		kFillOuterGlowTechnique,				// kDataTypePMGlowTechnique
		kFillOuterGlowSpread,					// kDataTypeReal
		kFillOuterGlowSize,						// kDataTypeReal

		kFillInnerGlowBaseID = BASE_XP_ATTR(kTargetFill, kGroupInnerGlow), 

		kFillInnerGlowApply,					// kDataTypeBoolean
		kFillInnerGlowBlendMode,				// kDataTypePMBlendingMode
		kFillInnerGlowOpacity,					// kDataTypeReal
		kFillInnerGlowNoise,					// kDataTypeReal
		kFillInnerGlowColor,					// kDataTypeColor
		kFillInnerGlowTechnique,				// kDataTypePMGlowTechnique
		kFillInnerGlowSpread,					// kDataTypeReal
		kFillInnerGlowSize,						// kDataTypeReal
		kFillInnerGlowSource,					// kDataTypePMInnerGlowSource

		kFillBevelEmbossBaseID = BASE_XP_ATTR(kTargetFill, kGroupBevelEmboss),

		kFillBevelEmbossApply,					// kDataTypeBoolean
		kFillBevelEmbossStyle,					// kDataTypePMBevelEmbossStyle
		kFillBevelEmbossTechnique,				// kDataTypePMBevelEmbossTechnique
		kFillBevelEmbossDepth,					// kDataTypeReal
		kFillBevelEmbossDirection,				// kDataTypePMBevelEmbossDirection
		kFillBevelEmbossSize,					// kDataTypeReal
		kFillBevelEmbossSoften,					// kDataTypeReal
		kFillBevelEmbossAngle,					// kDataTypeReal
		kFillBevelEmbossAltitude,				// kDataTypeReal
		kFillBevelEmbossUseGlobalLight,			// kDataTypeBoolean
		kFillBevelEmbossHighlightColor,			// kDataTypeColor
		kFillBevelEmbossHighlightBlendMode,		// kDataTypePMBlendingMode
		kFillBevelEmbossHighlightOpacity,		// kDataTypeReal
		kFillBevelEmbossShadowColor,			// kDataTypeColor
		kFillBevelEmbossShadowBlendMode,		// kDataTypePMBlendingMode
		kFillBevelEmbossShadowOpacity,			// kDataTypeReal

		kFillSatinBaseID = BASE_XP_ATTR(kTargetFill, kGroupSatin),

		kFillSatinApply,						// kDataTypeBoolean
		kFillSatinColor,						// kDataTypeColor
		kFillSatinBlendMode,					// kDataTypePMBlendingMode
		kFillSatinOpacity,						// kDataTypeReal
		kFillSatinAngle,						// kDataTypeReal
		kFillSatinDistance,						// kDataTypeReal
		kFillSatinSize,							// kDataTypeReal
		kFillSatinInvert,						// kDataTypeBoolean
		
		kFillDirectionalFeatherBaseID = BASE_XP_ATTR(kTargetFill, kGroupDirectionalFeather),

		kFillDirectionalFeatherApply,			// kDataTypeBoolean
		kFillDirectionalFeatherWidthLeft,		// kDataTypeReal
		kFillDirectionalFeatherWidthRight,		// kDataTypeReal
		kFillDirectionalFeatherWidthTop,		// kDataTypeReal
		kFillDirectionalFeatherWidthBottom,		// kDataTypeReal
		kFillDirectionalFeatherAngle,			// kDataTypeReal
		kFillDirectionalFeatherFollowShape,		// kDataTypeBoolean
		kFillDirectionalFeatherNoise,			// kDataTypeReal
		kFillDirectionalFeatherChoke,			// kDataTypeReal

		kFillGradientFeatherBaseID = BASE_XP_ATTR(kTargetFill, kGroupGradientFeather),
		
		kFillGradientFeatherApply,			// kDataTypeBoolean
		kFillGradientFeatherType,			// kDataTypeGradientType
		kFillGradientFeatherOpacityStops,	// kDataTypeOpacityGradientStops
		kFillGradientFeatherAngle,			// kDataTypeReal
		kFillGradientFeatherLength,			// kDataTypeReal
		kFillGradientFeatherCenter,			// kDataTypePoint
		kFillGradientFeatherRadius,			// kDataTypeReal
		kFillGradientFeatherHiliteAngle,	// kDataTypeReal
		kFillGradientFeatherHiliteLength,	// kDataTypeReal

		kContentBlendingBaseID = BASE_XP_ATTR(kTargetContent, kGroupBlending),

		kContentBlendingOpacity,
		kContentBlendingBlendMode,
		kContentBlendingKnockoutGroup,
		kContentBlendingIsolationGroup,

		kContentDropShadowBaseID = BASE_XP_ATTR(kTargetContent, kGroupDropShadow),

		kContentDropShadowMode,
		kContentDropShadowOffsetX,
		kContentDropShadowOffsetY,
		kContentDropShadowOpacity,
		kContentDropShadowBlendMode,
		kContentDropShadowBlurRadius,
		kContentDropShadowSpread,
		kContentDropShadowNoise,
		kContentDropShadowColor,
		kContentDropShadowUseGlobalLight,
		kContentDropShadowKO,
		kContentDropShadowHonorFX,

		kContentFeatherBaseID = BASE_XP_ATTR(kTargetContent, kGroupFeather),

		kContentFeatherMode,
		kContentFeatherWidth,
		kContentFeatherCorners,
		kContentFeatherNoise,
		kContentFeatherChoke,

		kContentInnerShadowBaseID = BASE_XP_ATTR(kTargetContent, kGroupInnerShadow), 

		kContentInnerShadowApply,					// kDataTypeBoolean
		kContentInnerShadowColor,					// kDataTypeColor
		kContentInnerShadowBlendMode,				// kDataTypePMBlendingMode
		kContentInnerShadowOpacity,				// kDataTypeReal
		kContentInnerShadowAngle,					// kDataTypeReal
		kContentInnerShadowDistance,				// kDataTypeReal
		kContentInnerShadowUseGlobalLight,			// kDataTypeBoolean
		kContentInnerShadowChoke,					// kDataTypeReal
		kContentInnerShadowSize,					// kDataTypeReal
		kContentInnerShadowNoise,					// kDataTypeReal

		kContentOuterGlowBaseID = BASE_XP_ATTR(kTargetContent, kGroupOuterGlow),

		kContentOuterGlowApply,					// kDataTypeBoolean
		kContentOuterGlowBlendMode,				// kDataTypePMBlendingMode
		kContentOuterGlowOpacity,					// kDataTypeReal
		kContentOuterGlowNoise,					// kDataTypeReal
		kContentOuterGlowColor,					// kDataTypeColor
		kContentOuterGlowTechnique,				// kDataTypePMGlowTechnique
		kContentOuterGlowSpread,					// kDataTypeReal
		kContentOuterGlowSize,						// kDataTypeReal

		kContentInnerGlowBaseID = BASE_XP_ATTR(kTargetContent, kGroupInnerGlow), 

		kContentInnerGlowApply,					// kDataTypeBoolean
		kContentInnerGlowBlendMode,				// kDataTypePMBlendingMode
		kContentInnerGlowOpacity,					// kDataTypeReal
		kContentInnerGlowNoise,					// kDataTypeReal
		kContentInnerGlowColor,					// kDataTypeColor
		kContentInnerGlowTechnique,				// kDataTypePMGlowTechnique
		kContentInnerGlowSpread,					// kDataTypeReal
		kContentInnerGlowSize,						// kDataTypeReal
		kContentInnerGlowSource,					// kDataTypePMInnerGlowSource

		kContentBevelEmbossBaseID = BASE_XP_ATTR(kTargetContent, kGroupBevelEmboss),

		kContentBevelEmbossApply,					// kDataTypeBoolean
		kContentBevelEmbossStyle,					// kDataTypePMBevelEmbossStyle
		kContentBevelEmbossTechnique,				// kDataTypePMBevelEmbossTechnique
		kContentBevelEmbossDepth,					// kDataTypeReal
		kContentBevelEmbossDirection,				// kDataTypePMBevelEmbossDirection
		kContentBevelEmbossSize,					// kDataTypeReal
		kContentBevelEmbossSoften,					// kDataTypeReal
		kContentBevelEmbossAngle,					// kDataTypeReal
		kContentBevelEmbossAltitude,				// kDataTypeReal
		kContentBevelEmbossUseGlobalLight,			// kDataTypeBoolean
		kContentBevelEmbossHighlightColor,			// kDataTypeColor
		kContentBevelEmbossHighlightBlendMode,		// kDataTypePMBlendingMode
		kContentBevelEmbossHighlightOpacity,		// kDataTypeReal
		kContentBevelEmbossShadowColor,			// kDataTypeColor
		kContentBevelEmbossShadowBlendMode,		// kDataTypePMBlendingMode
		kContentBevelEmbossShadowOpacity,			// kDataTypeReal

		kContentSatinBaseID = BASE_XP_ATTR(kTargetContent, kGroupSatin),

		kContentSatinApply,						// kDataTypeBoolean
		kContentSatinColor,						// kDataTypeColor
		kContentSatinBlendMode,					// kDataTypePMBlendingMode
		kContentSatinOpacity,						// kDataTypeReal
		kContentSatinAngle,						// kDataTypeReal
		kContentSatinDistance,						// kDataTypeReal
		kContentSatinSize,							// kDataTypeReal
		kContentSatinInvert,						// kDataTypeBoolean
		
		kContentDirectionalFeatherBaseID = BASE_XP_ATTR(kTargetContent, kGroupDirectionalFeather),

		kContentDirectionalFeatherApply,		// kDataTypeBoolean
		kContentDirectionalFeatherWidthLeft,	// kDataTypeReal
		kContentDirectionalFeatherWidthRight,	// kDataTypeReal
		kContentDirectionalFeatherWidthTop,		// kDataTypeReal
		kContentDirectionalFeatherWidthBottom,	// kDataTypeReal
		kContentDirectionalFeatherAngle,		// kDataTypeReal
		kContentDirectionalFeatherFollowShape,	// kDataTypeBoolean
		kContentDirectionalFeatherNoise,		// kDataTypeReal
		kContentDirectionalFeatherChoke,		// kDataTypeReal

		kContentGradientFeatherBaseID = BASE_XP_ATTR(kTargetContent, kGroupGradientFeather),
		
		kContentGradientFeatherApply,			// kDataTypeBoolean
		kContentGradientFeatherType,			// kDataTypeGradientType
		kContentGradientFeatherOpacityStops,	// kDataTypeOpacityGradientStops
		kContentGradientFeatherAngle,			// kDataTypeReal
		kContentGradientFeatherLength,			// kDataTypeReal
		kContentGradientFeatherCenter,			// kDataTypePoint
		kContentGradientFeatherRadius,			// kDataTypeReal
		kContentGradientFeatherHiliteAngle,		// kDataTypeReal
		kContentGradientFeatherHiliteLength,	// kDataTypeReal

		kMaxNumberAttrTypes
		};
			
	/** Encapsulates a complete attribute: type and value.  This is used primarily to pass
		arrays of attributes, such as a set of drop shadow attributes.
	*/
	class AttributeTypeAndValue
	{
	public:
		typedef object_type data_type;

		AttributeTypeAndValue()
			: fType(kUnknownAttrType) {}
		AttributeTypeAndValue(AttributeType type, const AttributeValue& x)
			: fType(type), fValue(x) {}
		AttributeTypeAndValue(AttributeType type, UID x) 
			: fType(type), fValue(x) {}
		AttributeTypeAndValue(AttributeType type, bool16 x) 
			: fType(type), fValue(x) {}
		AttributeTypeAndValue(AttributeType type, PMReal x) 
			: fType(type), fValue(x) {}
		AttributeTypeAndValue(AttributeType type, PMBlendingMode x) 
			: fType(type), fValue(x) {}
		AttributeTypeAndValue(AttributeType type, PMDropShadowMode x) 
			: fType(type), fValue(x) {}
		AttributeTypeAndValue(AttributeType type, PMVignetteMode x) 
			: fType(type), fValue(x) {}
		AttributeTypeAndValue(AttributeType type, PMVignetteCorners x) 
			: fType(type), fValue(x) {}
		AttributeTypeAndValue(AttributeType type, PMGlowTechnique x) 
			: fType(type), fValue(x) {}
		AttributeTypeAndValue(AttributeType type, PMInnerGlowSource x) 
			: fType(type), fValue(x) {}
		AttributeTypeAndValue(AttributeType type, PMBevelEmbossStyle x) 
			: fType(type), fValue(x) {}
		AttributeTypeAndValue(AttributeType type, PMBevelEmbossTechnique x) 
			: fType(type), fValue(x) {}
		AttributeTypeAndValue(AttributeType type, PMBevelEmbossDirection x) 
			: fType(type), fValue(x) {}
		AttributeTypeAndValue(AttributeType type, PMFollowShapeMode x) 
			: fType(type), fValue(x) {}
		AttributeTypeAndValue(AttributeType type, GradientType x) 
			: fType(type), fValue(x) {}
		AttributeTypeAndValue(AttributeType type, IOpacityGradientStops* x) 
			: fType(type), fValue(x) {}

	public:
		AttributeType GetType() const { return fType; }
		const AttributeValue& GetValue() const { return fValue; }

	public:
		AttributeTypeAndValue& operator=(const AttributeTypeAndValue& rhs) 
			{ fType = rhs.GetType(); fValue = rhs.GetValue(); return *this; }
		int32 operator==(const AttributeTypeAndValue& rhs)
			{ return fType == rhs.fType && fValue == rhs.fValue; }
		int32 operator!=(const AttributeTypeAndValue& rhs)
			{ return !(*this == rhs); }
	private:
		AttributeType fType;
		AttributeValue fValue;
	};

	typedef K2Vector<AttributeTypeAndValue> AttributeList;

	/** A partial angle, distance, xoffset, yoffset record.  The purpose of this class
		is to record the application of a single pseudo-attribute which doesn't match
		the attribute arrangement of the effect.  For example, it's possible in the UI
		to specify only a new angle value for drop shadow, without specifying the distance.
		But drop shadows don't measure their offset in terms of angle in distance; they
		measure in terms of X and Y offsets.  So you can't set up a set-attributes command
		the way you need to.  This class permits this kind of partial angle/distance/x/y 
		(ADXY) setup.
	*/

	class PartialADXY
	{
	public:
		typedef object_type data_type;
		typedef enum { kInvalid, kAngle, kDistance, kXOffset, kYOffset } WhichParameter;

		/** Basic constructor.
			@param target IN The target (object vs stroke vs fill vs content).
			@param group IN The effect group: must be drop shadow, inner shadow.
			@param param1 IN Which of the four parameters to set.  Must be an "opposing" parameter
							from the "natural" attributes the effect supports (eg angle for
							drop shadow, which has a natural x/y offset attribute).
			@param value1 IN The value of the parameter to set.
			@param param2 IN Optional second parameter, for the unusual cases where the user has
							specified one attribute from column A and one from column B.
			@param value2 IN The value of the second parameter to set.
		*/
		PartialADXY
			(
				IXPAttributeSuite::AttributeTarget target,
				IXPAttributeSuite::AttributeGroup group,
				WhichParameter param1,
				const PMReal& value1,
				WhichParameter param2 = kInvalid,
				const PMReal& value2 = 0
			) :
			fTarget(target),
			fGroup(group)
		{
			if (param1 == kInvalid)
			{
				ASSERT_FAIL("IXPSetAttributesCmdData::Sorry, param1 has to be valid.");
			}
			else if (param1 == kXOffset || param1 == kYOffset)
			{
				fParamXY = param1;
				fValueXY = value1;
				ASSERT(param2 == kAngle || param2 == kDistance || param2 == kInvalid);
				fParamAD = param2;
				fValueAD = value2;					
			}
			else 
			{
				fParamAD = param1;
				fValueAD = value1;
				ASSERT(param2 == kXOffset || param2 == kYOffset || param2 == kInvalid);
				fParamXY = param2;
				fValueXY = value2;
			}
			
			Validate();
		}

		PartialADXY
			(
				IXPAttributeSuite::AttributeTarget target,
				IXPAttributeSuite::AttributeGroup group
			) :
			fTarget(target),
			fGroup(group),
			fParamXY(kInvalid),
			fValueXY(0),
			fParamAD(kInvalid),
			fValueAD(0)
		{
		}

		/** Copy-constructor.
			@param rhs IN The right hand side.
		*/
		PartialADXY(const PartialADXY& rhs) 
		{
			*this = rhs; 
		}
		
		/** Checks a completed partial for sanity.
			@param assert IN True to assert on an invalid configuration (debug only).
			@return kTrue if it's OK, kFalse otherwise.  Invalid partials won't be applied.
		*/
		bool32 Validate(bool32 assert = kFalse)
		{
			bool32 ok = kTrue;

			if (fGroup != IXPAttributeSuite::kGroupDropShadow 
				&& fGroup != IXPAttributeSuite::kGroupInnerShadow)
			{
				if (assert) 
				{
					ASSERT_FAIL("PartialADXY::Validate: Only drop shadows and inner shadows are supported groups.");
				}
				ok = kFalse;
			}

			if ((fGroup == IXPAttributeSuite::kGroupDropShadow && fParamAD == kInvalid)
				|| (fGroup == IXPAttributeSuite::kGroupInnerShadow && fParamXY == kInvalid))
			{
				if (assert) 
				{
					ASSERT_FAIL("PartialADXY::Validate: Drop shadows must specify at least angle or distance "
								"(since they're XY based), and inner shadows must specify at least x or y "
								"(since they're AD based).");
				}
				ok = kFalse;
			}

			if (!(IsSingleParameter() 
				   || fParamAD != kAngle 
				   || ((fValueAD == 0 || fValueAD == 180) && fParamXY == kYOffset && fValueXY == 0)
				   || ((fValueAD == 90 || fValueAD == -90 || fValueAD == 270) && fParamXY == kXOffset && fValueXY == 0)))
			{
				if (assert) 
				{
					ASSERT_FAIL("PartialADXY::Validate: Multiple-parameter combinations involving angle require "
								"an orthogonal angle and corresponding zero in the applied X/Y field.");
				}
				ok = kFalse;
			}
			
			if(!(IsSingleParameter() 
				   || fParamAD != kDistance
				   || abs(fValueAD) >= abs(fValueXY)))
			{
				if (assert) 
				{
					ASSERT_FAIL("PartialADXY::Validate: Multiparameter combos involving distance require that the "
								"abs of the distance be greater than the abs of the x/y parameter (can't have a "
								"hypotenuse greater than a leg of a right triangle).");
				}
				ok = kFalse;
			}

			return ok;
		}

		/** Assignment operator.
			@param rhs IN The right hand side.
			@return A reference to the lhs.
		*/
		PartialADXY& operator=(const PartialADXY& rhs)
		{
			fTarget = rhs.fTarget; 
			fGroup = rhs.fGroup; 
			fParamXY = rhs.fParamXY; 
			fValueXY = rhs.fValueXY; 
			fParamAD = rhs.fParamAD; 
			fValueAD = rhs.fValueAD; 
			return *this;
		}

		bool32 IsSingleParameter() const
		{
			return fParamXY == kInvalid || fParamAD == kInvalid;
		}
					
	public:
		IXPAttributeSuite::AttributeTarget fTarget;
		IXPAttributeSuite::AttributeGroup fGroup;
		WhichParameter fParamXY, fParamAD;
		PMReal fValueXY, fValueAD;
	};

	typedef K2Vector<PartialADXY> PartialADXYVector;

public:

	//________________________________________________________________________________
	//________________________________________________________________________________

	/**	Returns the number of unique attributes of the specified attribute class
		@param attrClass the transparency attribute class
		@return attribute count
	*/
	virtual uint16 			GetAttributeCount (ClassID attrClass) = 0;
	/**	Returns the number of unique attributes of the specified transparency attribute type
		@param attrType the transparency attribute type
		@return attribute count
	*/
	virtual uint16 			GetAttributeCount (AttributeType attrType) = 0;
	
	//	Attribute value accessors
	//________________________________________________________________________________
	/**	Return kTrue if attribute class is enabled.
		@param attrClass the transparency attribute class
		@return kTrue if enabled otherwise kFalse
	*/
	virtual bool16 				IsAttributeEnabled					(ClassID attrClass) = 0;
	/**	Return kTrue if transparency attribute type is enabled.
		@param attrType the transparency attribute type
		@return kTrue if enabled otherwise kFalse
	*/
	virtual bool16 				IsAttributeEnabled 					(AttributeType attrType) = 0;

	/**	Returns the nth attribute specified by the attribute class ID
		@param whichAttribute is the nth attribute starting from 0.
		@param attrClass the transparency attribute class.
		@param interfaceID the requested interface pointer.
		This is typically IID_IGRAPHICATTR_INFO or a persistent data interface IID.
		@return IPMUnknown to the requested interface pointer or nil.
		This can be cast to the type of IID.
	*/
	virtual const IPMUnknown* 	QueryAttribute				(uint32 whichAttribute, ClassID attrClass, const PMIID& interfaceID = IID_IUNKNOWN) = 0;
	
	/**	Returns a copy of the nth attribute specified by the attribute class ID
		@param whichAttribute is the nth attribute starting from 0.
		@param attrClass the transparency attribute class.
		@param interfaceID the requested interface pointer.
		This is typically IID_IGRAPHICATTR_INFO or a persistent data interface IID.
		@return IPMUnknown* to the requested interface pointer or nil.
		This can be cast to the type of IID.
	*/
	virtual IPMUnknown* 	CreateAttributeCopy				(uint32 whichAttribute, ClassID attrClass, const PMIID& interfaceID = IID_IUNKNOWN) = 0;
	
	/**	Copy the content of iAttribute to the nth attribute
		@param whichAttribute is the nth attribute starting from 0.
		@param iAttribute the content of transparency attribute to be copied.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode	 	CopyIntoAttribute				(uint32 whichAttribute, IPMUnknown* iAttribute) = 0;
	
	//________________________________________________________________________________
	//	Returns the nth specific attribute value
	//________________________________________________________________________________	
	/**	Returns the real number attribute value of the nth attribute of the specified attribute type.
		@param whichAttribute is the nth attribute starting from 0.
		@param attrType the transparency attribute type.
		@return a real number value. Returns kInvalidRealNumberValue if attrType is not a real number attribute.
	*/
	virtual PMReal			GetRealNumberAttributeValue 	(uint32 whichAttribute, AttributeType attrType) = 0;
	/**	Returns the boolean attribute value of the nth attribute of the specified attribute type.
		@param whichAttribute is the nth attribute starting from 0.
		@param attrType the transparency attribute type.
		@return a bool16 value. Returns kFalse if attrType is not a boolean attribute.
	*/
	virtual bool16			GetBooleanAttributeValue 		(uint32 whichAttribute, AttributeType attrType) = 0;
	/**	Returns the long integer attribute value of the nth attribute of the specified attribute type.
		@param whichAttribute is the nth attribute starting from 0.
		@param attrType the transparency attribute type.
		@return a int32 value. Returns kInvalidInt32Value if attrType is not a integer attribute.
	*/
	virtual int32			GetInt32AttributeValue			(uint32 whichAttribute, AttributeType attrType) = 0;
	/**	Returns the UID attribute value of the nth attribute of the specified attribute type.
		@param whichAttribute is the nth attribute starting from 0.
		@param attrType the transparency attribute type.
		@return a UID value. Returns kInvalidUID if attrType is not a UID attribute.
	*/
	virtual UID				GetUIDAttributeValue			(uint32 whichAttribute, AttributeType attrType) = 0;

	/**	The general form of Get-Value that leverages the AttributeValue helper class.
		@param whichAttribute Is the nth attribute starting from 0.
		@param attrType The transparency attribute type.
		@param value OUT Receives the value of the nth attribute.
	*/
	virtual void			GetAttributeValue				(uint32 whichAttribute, AttributeType attrType, AttributeValue& value) = 0;

	/** Obtains a list of all combinations of attributes given the current selection.  This is needed
		for determining how multiple x/y and angle/distance pairs should be presented in the UI.  Or
		maybe some other purpose; it's a pretty general API.

		You pass in an array of attribute types, which represent the attributes you're interested in.  For
		example, in the case of drop shadows we'd normally pass in the X and Y offset attributes.

		You also pass in an array of attribute lists.  This method fills in those lists with all of the
		values from the selection.  For example, if you had two objects selected, there would be two entries
		in the list, and the first entry in each list would correspond to the first selected object, and the
		second entry in the list would correspond to the second selected object.

		Note that this differs significantly from how attributes are typically reported, which has been 
		condensed into lists of only the unique attributes.  Thus you could have two objects, one with X,Y = 1,2
		and the other with X,Y = 2,1.  In both cases the other methods here would report that there are X
		values of 1 and 2 and Y values of 1 and 2, but you wouldn't know if it was (1,2),(2,1) or (1,1),(2,2).
		Which is fine for most UI but in the case of x/y/a/d we need to know which angles and distances are
		unique, which requires correlation with the original data sets.

		@param attrCount IN The size of the following two arrays.
		@param attrTypeArray IN An array of attribute types.  Must be at least as large as attrCount.
		@param attrListArray OUT An array of attribute lists to be filled in.  These are emptied prior to appending.
									Must be at least as large as attrCount.  Nil pointers are tolerated.
	*/
	virtual void			GetAttributeValueLists			(uint32 attrCount, const AttributeType* attrTypeArray, AttributeList** attrListArray) = 0;

	//________________________________________________________________________________
	//________________________________________________________________________________
	/**	Return kTrue if the attribute specified by the attribute class ID and the attribute type
		is unique
		@param attrClass the transparency attribute class ID.
	*/
	virtual bool16			IsAttributeUnique 				(ClassID attrClass) = 0;
	/**	@see IsAttributeUnique
		@param attrType the transparency attribute type.
	*/
	virtual bool16			IsAttributeUnique				(AttributeType attrType) = 0;

	/**	Apply the specified transparency attr list (and other optional odds and ends) to the current selection.

		@param iAttrList the attribute list to apply. Only transparency attributes from the list are applied.
		@param partialADXYs IN If non-nil, the list of partial ADXY values to apply.
		@param autoInitializeGradientFeatherGeometry IN If true, and the list of attributes includes any of 
								those related to opacity gradients, the command will initialize any currently-
								uninitialized attributes related to the geometry of the feather.  Otherwise
								you'd have to do all those computations yourself and set up the appropriate
								attributes.
		@return kSuccess if successful; otherwise returns an error code.
	*/
	virtual ErrorCode		ApplyAttributes					(IGraphicStyleAttributeBossList* iAttrList, 
															const PartialADXYVector* partialADXYs = nil,
															bool32 autoInitializeGradientFeatherGeometry = kFalse) = 0;

	/**	Apply the specified set of attributes (and other optional odds and ends) to the current selection.

		@param attrList The list of type/value pairs to apply.
		@param partialADXYs IN If non-nil, the list of partial ADXY values to apply.
		@param autoInitializeGradientFeatherGeometry IN If true, and the list of attributes includes any of 
								those related to opacity gradients, the command will initialize any currently-
								uninitialized attributes related to the geometry of the feather.  Otherwise
								you'd have to do all those computations yourself and set up the appropriate
								attributes.
		@return kSuccess if successful otherwise returns an error code.
	*/
	virtual ErrorCode		ApplyAttributes					(const AttributeList& attrList,
															const PartialADXYVector* partialADXYs = nil,
															bool32 autoInitializeGradientFeatherGeometry = kFalse) = 0;

	/**	Apply the spcified set of basic transparency attributes to the current selection.
		Only those data specified by the attrTypeList are applied.
		@param basicData the basic transparency data
		@param attrTypeList the list of basic transparency attribute types to apply.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode		ApplyBasicAttributes			(BasicAttributesData* basicData, const K2Vector<AttributeType>& attrTypeList) = 0;
	/**	Apply the spcified set of drop shadow attributes to the current selection.
		Only those data specified by the attrTypeList are applied.
		@param dropshadowData the dropshadow data to apply
		@param attrTypeList the list of dropshadow attribute types to apply.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode		ApplyDropShadowAttributes		(DropShadowData* dropshadowData, const K2Vector<AttributeType>& attrTypeList) = 0;
	/**	Apply the spcified set of feather attributes to the current selection.
		Only those data specified by the attrTypeList are applied.
		@param featherData the feather data
		@param attrTypeList the list of feather attribute types to apply.
		@return kSuccess if successfull otherwise returns an error code.
	*/
	virtual ErrorCode		ApplyVignetteAttributes			(VignetteData* featherData, const K2Vector<AttributeType>& attrTypeList) = 0;

	/**	Get the selected image's true bounding box. This is the bbox of the
		entire image. Returns only a valid bbox iff one single image is selected.
		Otherwise, returns an empty rect.
		This is called when an selected image is cropped and caller need to know the
		image's entire bbox. 
		This method only make sense for LayoutCSB.
		@param featherData the feather data
		@param attrTypeList the list of feather attribute types to apply.
		@return a PMRect or an empty rect.
	*/
	virtual PMRect			GetImageTrueBBox				(void) = 0;
	
	/**	Check if there are items selected that can have transparency attributes applied.
		@return kTrue if items can have attribute applied.
	*/
	virtual bool16			CanApplyAttributes				(void) = 0;
	/**	Check if there are items selected that can have the specified attributes applied.
		@return kTrue if items can have attribute applied.
	*/
	virtual bool16			CanApplyAttributes				(const AttributeList& attrList) = 0;
	/**	Check if there are items selected that can have attributes of the specified group applied.
		Note that this works for any of the AttributeGroups; the above methods are 'legacy' 
		versions before we had so many different groups.
		@return kTrue if items can have attribute applied.
	*/
	virtual bool16			CanApplyAttributes				(AttributeGroup grp) = 0;
	/**	Check if there are items selected that can have basic transparency attributes applied.
		@return kTrue if items can have attribute applied.
	*/
	virtual bool16			CanApplyBasicAttributes			(void) = 0;
	/**	Check if there are items selected that can have drop shadow attributes applied.
		@return kTrue if items can have attribute applied.
	*/
	virtual bool16			CanApplyDropShadowAttributes	(void) = 0;
	/**	Check if there are items selected that can have feather attributes applied.
		@return kTrue if items can have attribute applied.
	*/
	virtual bool16			CanApplyVignetteAttributes		(void) = 0;

};

DECLARE_BASE_TYPE(IXPAttributeSuite::AttributeType);


#endif	// __IXPAttributeSuite__

