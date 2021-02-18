//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PreflightStringConstants.h $
//  
//  Owner: Matt Phillips
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

// The purpose of this file is to define constants that are used at the model and UI level 
// in many places so any typos will end up being hard-to-find bugs. I'm not suggesting we put
// all UI strings in here, just the ones that are used in many places.

// The default name for a newly created profile.
static const PMString kNewProfileName("kNewProfileName");

// The name of the default profile (ie the one that is required to be there).
static const PMString kDefaultProfileName("kDefaultProfileName");

// The description of the default profile.
static const PMString kDefaultProfileDescription("kDefaultProfileDescription");

// The string that appears when there's no profile active: [None]
static const PMString kNoPreflightProfile("kNoPreflightProfile");

/** Rule categories, ie values you can use for IPreflightRuleInfo::Set/GetCategory(). */
static const char* kCategoryLinks = "kLinksRuleCategory";
static const char* kCategoryObjects = "kObjectsRuleCategory";
static const char* kCategoryText = "kTextRuleCategory";
static const char* kCategoryColor = "kColorRuleCategory";
static const char* kCategoryDocument = "kDocumentRuleCategory";
static const char* kCategoryTest = "kTestRuleCategory";

//	The following strings defines the data parameter keys for the native c++ rules.
//	Blank pages
static const char* kParamIgnoreMaster = "ignore_master";
static const char* kParamIgnoreNonprinting = "ignore_nonprinting";

//	Bleed and slug
static const char* kParamSlugEnabled = "slug_enabled";
static const char* kParamSlugComparisonType = "slug_comparison_type";
static const char* kParamSlugL = "slug_l";
static const char* kParamSlugR = "slug_r";
static const char* kParamSlugT = "slug_t";
static const char* kParamSlugB = "slug_b";
static const char* kParamSlugL2 = "slug_l_aux";
static const char* kParamSlugR2 = "slug_r_aux";
static const char* kParamSlugT2 = "slug_t_aux";
static const char* kParamSlugB2 = "slug_b_aux";
static const char* kParamBleedEnabled = "bleed_enabled";
static const char* kParamBleedComparisonType = "bleed_comparison_type";
static const char* kParamBleedL = "bleed_l";
static const char* kParamBleedR = "bleed_r";
static const char* kParamBleedT = "bleed_t";
static const char* kParamBleedB = "bleed_b";
static const char* kParamBleedL2 = "bleed_l_aux";
static const char* kParamBleedR2 = "bleed_r_aux";
static const char* kParamBleedT2 = "bleed_t_aux";
static const char* kParamBleedB2 = "bleed_b_aux";

// Bleed/Trim Hazard
static const char* kParamLiveAreaL = "live_l";
static const char* kParamLiveAreaR = "live_r";
static const char* kParamLiveAreaT = "live_t";
static const char* kParamLiveAreaB = "live_b";
static const char* kParamBindingEnabled = "binding_enabled";
static const char* kParamBindingSafeZoneWidth = "binding_width";
// Also uses kParamTolerance


//	CMY plates
//	None so far

//	Colorspaces
static const char* kParamNoRGB = "no_rgb";
static const char* kParamNoCMYK = "no_cmyk";
static const char* kParamNoGray = "no_gray";
static const char* kParamNoLAB = "no_lab";
static const char* kParamNoSpot = "no_spot";
static const char* kParamNoHSB = "no_hsb";

//	Cross-References
static const char* kParamXRefsOutOfDate = "xrefs_out_of_date";
static const char* kParamXRefsUnresolved = "xrefs_unresolved";

//	DPOE
//	None so far

//	Font usages
static const char* kParamNoOpenTypeCFF = "no_OpenTypeCFF";
static const char* kParamNoOpenTypeCID = "no_OpenTypeCID";
static const char* kParamNoOpenTypeTT = "no_OpenTypeTT";
static const char* kParamNoMultipleMaster = "no_MultipleMaster";
static const char* kParamNoType1 = "no_Type1";
static const char* kParamNoTrueType = "no_TrueType";
static const char* kParamNoCID = "no_CID";
static const char* kParamNoATC = "no_ATC";
static const char* kParamNoBitmap = "no_Bitmap";
static const char* kParamNoType3 = "no_Type3";
static const char* kParamNoProtected = "no_protected";
static const char* kObsoleteParamNoSVG = "no_SVG";

//	Image color management
static const char* kParamNoImageOverrides = "no_image_overrides";
static const char* kParamOverrideExcludeUncal = "overrides_exclude_uncal";
static const char* kParamNoCMYKProfiles = "no_cmyk_profiles";

//	Image resolution
static const char* kParamColorMinEnabled = "color_min_enabled";
static const char* kParamColorMinRes = "color_min_res";
static const char* kParamColorMaxEnabled = "color_max_enabled";
static const char* kParamColorMaxRes = "color_max_res";
static const char* kParamGrayMinEnabled = "gray_min_enabled";
static const char* kParamGrayMinRes = "gray_min_res";
static const char* kParamGrayMaxEnabled = "gray_max_enabled";
static const char* kParamGrayMaxRes = "gray_max_res";
static const char* kParamBWMinEnabled = "bw_min_enabled";
static const char* kParamBWMinRes = "bw_min_res";
static const char* kParamBWMaxEnabled = "bw_max_enabled";
static const char* kParamBWMaxRes = "bw_max_res";

//	Interactive content
static const char* kParamNoVideo = "no_Video";
static const char* kParamNoAudio = "no_Audio";
static const char* kParamNoAnimatedObject = "no_AnimatedObject";
static const char* kParamNoMSO = "no_MSO";
static const char* kParamNoButton = "no_Button";
static const char* kParamNoFlashIncompatible = "no_FlashIncompatible";
static const char* kParamNoFormField = "no_FormField";

//	Missing fonts
//	None so far

//	Links
static const char* kParamLinkMissing = "missing";
static const char* kParamLinkModified = "modified";

//	OPI
//	None so far

//	Overset text
//	None so far

//	Page count
static const char* kParamCountComparisonType = "comparison_type";
static const char* kParamCountComparisonValue = "comparison_value";
static const char* kParamCountComparisonValue2 = "comparison_value_aux";

//	Page size orientation
static const char* kParamTolerance = "tolerance";
static const char* kParamWidth = "width";
static const char* kParamHeight = "height";
static const char* kParamIgnoreOrientation = "ignore_orientation";

//	Placed content
static const char* kParamMaxDeltaE = "max_delta_e";
static const char* kParamNoSpaceMismatch = "no_space_mismatch";

//	Placed EPS
//	None so far

//	Placed PDF
//	None so far

//	Rich black
static const char* kBlackThreshold = "black_threshold";
static const char* kIndivThreshold = "indiv_threshold";
static const char* kTotalThreshold = "total_threshold";

//	Scaled type
static const char* kParamMaxScale = "max_scale";
static const char* kParamIgnoreJustificationScaling = "ignore_justification";

//	Small text
static const char* kParamMinSize = "minSize";
static const char* kParamMinSizeTrapSafeOnly = "minSize_trap_safe_only";
// static const char* kParamMinSizeTrapSafe = "min_size_trap_safe";

//	Spot color setup
static const char* kParamMaxSpotsEnabled = "max_spots_enabled";
static const char* kParamMaxSpots = "max_spots";
static const char* kParamLABSpotsEnabled = "lab_spots_enabled";
static const char* kParamLABSpots = "lab_spots";
// static const char* kParamPrefixEnabled = "spot_name_prefix_enabled";
// static const char* kParamPrefix = "spot_name_prefix";
// static const char* kParamSuffixEnabled = "spot_name_suffix_enabled";
// static const char* kParamSuffix = "spot_name_suffix";
// static const char* kParamMinSpotsEnabled = "min_spots_enabled";
// static const char* kParamMinSpots = "min_spots";

//	Stroke requirements
static const char* kParamMinWidth = "min_width";
static const char* kParamMinWidthTrapSafeOnly = "min_width_trap_safe_only";
// static const char* kParamMinWidthEnabled = "min_width_enabled";
// static const char* kParamMaxWidthEnabled = "max_width_enabled";
// static const char* kParamMaxWidth = "max_width";
// static const char* kParamMinWidthTrapSafeEnabled = "min_width_trap_safe_enabled";
// static const char* kParamMinWidthTrapSafe = "min_width_trap_safe";

//	Testing helper
//	None so far

//	Text overrides
static const char* kParamIgnoreFontOverrides = "ignore_font_overrides";
static const char* kParamIgnoreLanguageOverrides = "ignore_language_overrides";
static const char* kParamIgnoreKernTrackingOverrides = "ignore_kerning_tracking_overrides";
static const char* kParamIgnoreColorOverrides = "ignore_color_overrides";

//	Text and transparency
//	None so far

//	Transparency blending
static const char* kParamSpace = "space";

//	Transparency usage
//	None so far

//	Unused colors
//	None so far

//	White overprint
//	None so far
