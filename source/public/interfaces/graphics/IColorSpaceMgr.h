//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IColorSpaceMgr.h $
//  
//  Owner: fhaberma
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
#ifndef __IColorSpaceMgr__
#define __IColorSpaceMgr__

#include "IPMUnknown.h"
#include "ICMSSettings.h"
#include "ICMSProfile.h"
#include "BravoForwardDecl.h"

class PMString;
class IDocument;
class IColorXFormData;
class ICMSProfile;
class IColorData;

const int32 kGetCSFlagForceCalibrated		= (1L<<4);	// I.e., ignore doc/obj cms on/off setting
const int32 kGetCSFlagForceUncalibrated		= (1L<<5);  // I.e., ignore doc/obj cms on/off setting
const int32 kGetCSFlagHasAlpha				= (1L<<6);
const int32 kGetCSFlagDocDefaultCalibrated	= (1L<<7);	// By default doc default is uncalibrated.

// Flags for GetAGMProfileForCategory
const int32 kCSMGetProfileNoSimulation		= (1L<<2);	// Don't include sim profile for monitor
const int32 kCSMGetProfileTryWeakly			= (1L<<3);	// If category not set up, don't force it
const int32 kCSMGetProfilePrefsIntent		= (1L<<4);	// Use rendering intent from prefs

class IColorSpaceMgr : public IPMUnknown
{
public:

		enum gamutAbility { kDoesNotImplement=0, kSimpleYesNo, kDistance};

		/**
			Returns a default document colorspace by color family (csType).  If you don't
			specify a particular RI, generally use-gstate-ri will be used; the exception
			is for some image cases where the RI is known *and* a profile is assigned such
			that we can return an appropriate colorspace with the RI hard-coded in.  In
			general one should use gstate RI unless there's a specific reason not to.  If
			you need a consistent RI in the colorspace you should also pass 
			kGetCSFlagDocDefaultCalibrated as a flag in order to force a calibration for
			otherwise would-be-uncal spaces.

			@param csType: kPMCs* from GraphicTypes.h.
			@param doc: The document whose profile you want.
			@param agmPrivateData: Obsolete.  Pass nil.
			@param getColorSpaceFlags: kGetCSFFlag* flags.
			@return A refcounted AGMColorSpace object pointer.  Be sure to release this 
					with ColorSpaceRelease when you're done with it!
		*/
		virtual AGMColorSpace *GetColorSpace
			(
				uint32 csType, 
				IDocument *doc, 
				void *agmPrivateData=nil, 
				int32 getColorSpaceFlags = 0,
				ICMSSettings::renderingIntent intent = ICMSSettings::kOther,
                bool16 isHSB = kFalse  			
			) = 0;		

		/**
			Returns a colorspace for a specific page item and colorspace.  If the object
			has an ICMSSettings interface on it and that interface returns a profile of the
			same colorspace, a colorspace for that settings is returned.  In all other cases
			the document profile for the colorspace is returned.
			
			@param csType: kPMCs* from GraphicTypes.h.
			@param obj: The object whose profile you want.
			@param agmPrivateData: Obsolete.  Pass nil.
			@param getColorSpaceFlags: kGetCSFFlag* flags.
			@return A refcounted AGMColorSpace object pointer.  Be sure to release this 
					with ColorSpaceRelease when you're done with it!
		*/
		virtual AGMColorSpace *GetColorSpace
			(
				uint32 csType, 
				IPMUnknown* obj, 
				void *agmPrivateData=nil, 
				int32 getColorSpaceFlags = 0,
				ICMSSettings::renderingIntent intent = ICMSSettings::kOther,
                bool16 isHSB = kFalse
			) = 0;		

		/**
			Returns a colorspace for a particular profile.
			
			@param cmsProfile: The profile you want a colorspace for.
			@param agmPrivateData: Obsolete.  Pass nil.
			@param getColorSpaceFlags: kGetCSFFlag* flags.
			@return A refcounted AGMColorSpace object pointer.  Be sure to release this 
					with ColorSpaceRelease when you're done with it!
		*/
		virtual AGMColorSpace *GetColorSpace
			(
				ICMSProfile* cmsProfile, 
				ICMSSettings::renderingIntent intent, 
				int32 getColorSpaceFlags = 0,
                bool16 isHSB = kFalse
			) = 0;		

		/**
			Returns a colorspace for a category (and in most cases, document).
			
			For source categories (RGB/CMYK/LAB) this will return a colorspace for the
			corresponding colorspace and document.  However, it will be uncalibrated 
			and the rendering intent ignored unless you specify kGetCSFlagDocDefaultCalibrated
			as one of the flags.  This is generally NOT recommended for any drawing that
			should use the document profile, which is most drawing -- ie if you don't
			provide user interface to select a specific profile, you should use the
			document profiles.  That's because if the user selects "preserve numbers"
			at output time, your drawing's numbers will NOT be preserved if you ask
			for a calibrated profile.
			
			If you need a specific rendering intent but want to default to the document
			profile while still making preserve numbers work as expected, use gstate RI.
			That is, use IGraphicsPort::SetRenderingIntent to specify the RI, get the
			profile via this call (or the one that takes csType, above), and draw.  This
			will ensure that your drawing will use the document profile and your desired
			rendering intent.
			
			Note that for monitor profile rendering intent isn't usually interesting
			because the monitor is the last profile in the rendering sequence.  The
			document is ignored since the monitor profile is global.
			
			@param doc: The document from which to pull profiles.
			@param category: The category you want.
			@param intent: The intent you want to use, if calibrated.
			@param getColorSpaceFlags: kGetCSFFlag* flags.
			@return A refcounted AGMColorSpace object pointer.  Be sure to release this 
					with ColorSpaceRelease when you're done with it!
		*/
			
		virtual AGMColorSpace *GetColorSpace
			(
				IDocument *doc, 
				ICMSProfile::profileCategory category, 
				ICMSSettings::renderingIntent intent = ICMSSettings::kUseGStateRI,
				int32 getColorSpaceFlags = 0,
                bool16 isHSB = kFalse
			) = 0;		

		/**
			Returns a colorspace corresponding to a specific ICC representation.
			
			@param csType: The color familiy of the profile (kPMCs*).
			@param iccData: Points to the ICC profile data.
			@param iccSize: The size of the ICC data, in bytes.
			@param intent: The rendering intent to use when converting from this space to the next.
			@param getColorSpaceFlags: kGetCSFFlag* flags.  Currently ignored.
			@return A refcounted AGMColorSpace object pointer.  Be sure to release this 
					with ColorSpaceRelease when you're done with it!
		*/			
		virtual AGMColorSpace *GetColorSpace
			(
				uint32 csType,
				void *iccData,
				int32 iccSize,
				ICMSSettings::renderingIntent intent,
				int32 getColorSpaceFlags = 0,
                bool16 isHSB = kFalse
			) = 0;

		/**
			Release colorspace obtained by any of the above GetColorSpace methods.
			
			@param cs: The colorspace to release.
		*/
		virtual void ColorSpaceRelease
			(
				AGMColorSpace *cs
			) = 0;
		
		/**
			Returns the ICC profile data attached to the space, assuming there is
			a profile attached to the space.  If there is a profile, a pointer to
			the data is returned; YOU then own the pointer.  The size is optionally
			returned in "profileSize" and will be zero if no profile is available.
			
			@param cs: The color space you want to pull the profile data from.
			@param profileSize: Returns the size of the data returned.
			@return Pointer to profile data; be sure to ReleaseProfileData() when done.
		*/
		virtual const void *GetProfileData
			(
				AGMColorSpace *cs, 
				uint32 *profileSize = nil
			) = 0;		
		
		/**
			Release profile data returned from GetProfileData.
		*/
		virtual void ReleaseProfileData
			(
				void *profileData
			) = 0;		

		/**
			Tests the colorIn to see if its with the Gamut of the device specified by 
			the boss containing IColorXFormData (by default it will test within
			the gamut of the Separations space). Returns true iff its within gamut. 
			If its not within gamut, colorOut components will contain how far each
			component is outside of gamut. Please also see the description of 
			IColorXFormData to have all options explained. Warning: Some colorspacemgr's
			may not have this implemented, and will always return true. You can pass 
			in a parameter for doesImplement, which tells you whether it implements
			this or not.
			Whether or not colorIn is within gamut, if colorNearest is non-nil it will
			be filled with the nearest color to colorIn within the gamut.  Of course,
			if the color is in gamut, colorNearest = colorIn. 
			NOTE: If colorOut == nil, then GamutTest will put the result into colorIn. 
			This is useful if you want to reuse memory already allocated and
			don't care about its contents getting overwritten with the results.
			ANOTHER NOTE: doc holds any profiles used for gamut testing (such as the 
			separations profile). If no profiles are initialized for the passed in 
			document, GamutTest will return true. If doc==nil, the default document 
			will be perused for profiles. 
			
			@param colorIn: The input (non-gamut-clipped) color values.
			@param colorOut: The distance the color is from in-gamut.
			@param colorNearest: The nearest in-gamut color.
			@param doc: The document to use for profile gathering.
			@param doesImplement: Returns whether the function is implemented.
			@return kTrue if in gamut, kFalse if not.
		*/
		virtual bool8 GamutTest
			(
				IColorData* colorIn, 
				IColorData* colorOut, 
				IColorData *colorNearest, 
				IDocument *doc, 
				IColorSpaceMgr::gamutAbility& doesImplement
			) = 0;

		/**
			This is used to get AGM color profiles, which can be selected into ports/devices.

			Note: there are several ways of obtaining a rendering intent for the profile.
			First, you can specify the RI directly via param intent.  Or, you can use the
			default kOther and specify kCSMGetProfilePrefsIntent to automatically grab
			the document's vector RI.  Finally, you can leave it as kOther and not specify
			any flags, and you'll get kUseGStateRI, meaning the RI will use whatever's in the
			gstate at the time of the conversion.

			@param doc: The document from which to pull the profiles; nil for CSF default.
			@param category: The category, typically RGB/CMYK/LAB but can also be Monitor.
			@param flags: kCSMGetProfile* flags.
			@param intent: Specific rendering intent to apply, if desired.
		*/
		virtual AGMColorProfile *GetAGMProfileForCategory
			(
				IDocument *doc,
				ICMSProfile::profileCategory category,
				int32 flags = 0,
				ICMSSettings::renderingIntent intent = ICMSSettings::kOther
			) = 0;	

		/**
			Release the profile returned from GetAGMProfileForCategory.
		*/
		virtual void ReleaseAGMProfile(AGMColorProfile *pAGMProfile) = 0;		

		/**
			For internal use only.
		*/
		virtual bool16 SetScreenIntentMode(bool16 bUseScreenIntent) = 0;

		/**
			For internal use only.
		*/
		virtual bool16 GetScreenIntentMode() = 0;
	
#ifdef DEBUG
	virtual void DumpToDebugWindow() = 0;
	virtual void Test1() = 0;
#endif
	
};

#endif
