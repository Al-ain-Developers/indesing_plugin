//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ICMSAttributeSuite.h $
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
//  
//  Defines the interface for a CMS attribute suite to be used in the new selection architecture
//  
//========================================================================================

#pragma once
#ifndef __ICMSAttributeSuite__
#define __ICMSAttributeSuite__

// ----- Interface files
#include "IPMUnknown.h"

// ----- ID files
#include "ColorMgmtID.h"

#include "ICMSSettings.h"
#include "ICMSItemProfileSource.h"

class CMSMgrProfileFilter;
class ICMSAttributeSuite : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ICMSATTRIBUTESUITE };

		//________________________________________________________________________________________
		//	Accessors
		//________________________________________________________________________________________
		
		/**	Returns the profile color space. Valid color spaces are kPMCsCalRGB, kPMCsCalCMYK, and
			kPMCsLab. Returns kPMCsUnused if mixed selection.
			@return profile color space.
			@precondition CanApplyCMS() == kTrue. 
		*/
		virtual int32		GetProfileColorspace	() = 0;
		
		/**	Returns the current rendering intent in the parameter.
			Returns kTrue if there's an unique rendering intent in the selection. Otherwise returns kFalse.
			@param renderingIntent
			@precondition CanApplyCMS() == kTrue. 
		*/
		virtual bool16		GetRenderingIntent		(ICMSSettings::renderingIntent&) = 0;
		
		/**	Returns the current CMS enabling state in the parameter.
			Returns kTrue if there's an unique CMS enable state in the selection. Otherwise returns kFalse.
			@param onOffstate
			@precondition CanApplyCMS() == kTrue. 
		*/
		virtual bool16		GetCMSState				(bool16& onOffstate) = 0;
		
		/**	Returns the current profile name and type in the parameters. 
			The name is set to null if profile type is set to use the document default.
			It is also null if there's mixed selection.
			Returns kTrue if the profile is unique Otherwise returns kFalse.
			@param profileName.
			@param profileType.
			@precondition CanApplyCMS() == kTrue. 
		*/
		virtual bool16		GetProfileName			(PMString&, ICMSItemProfileSource::ProfileSourceType&) = 0;
		
		/**	Returns the embedded profile name in the parameter. There can be an embedded profile only if there's
			only one item in the selection. All other cases, the name is set to null.
			Returns kTrue if there's an embedded profile. Otherwise kFalse.
			@param embeddedrofileName.
			@precondition CanApplyCMS() == kTrue. 
		*/
		virtual bool16		GetEmbeddedProfileName	(PMString&) = 0;
		
		
		/**	Returns kTrue if CMS attributes can be applied.
			@precondition CanApplyCMS() == kTrue. 
		*/
		virtual bool16		CanApplyCMS				() = 0;
		
		/**	Returns kTrue if an embedded profile can be applied.
		*/
		virtual bool16		CanApplyEmbeddedProfile () = 0;
		
		/**	Returns kTrue if a profile filter can be created. A profile filter can only be created if the
			profile color space is one of (kPMCsCalRGB, kPMCsCalCMYK, or kPMCsLab).
		*/
		virtual bool16		CanCreateProfileFilter	() = 0;
		
		/**	Create a profile filter based on the current selection. Returns the profile filter in the parameter.
			@precondition CanCreateProfileFilter() == kTrue. 
		*/
		virtual bool16		CreateProfileFilter		(CMSMgrProfileFilter&) = 0;
		
		//________________________________________________________________________________________
		//	Apply attributes
		//________________________________________________________________________________________
		/**	Apply the specified rendering intent to the selection.
			@param renderingIntent the rendering intent to apply.
			@precondition CanApplyCMS() == kTrue. 
		*/
		virtual ErrorCode	ApplyRenderingIntent	(const ICMSSettings::renderingIntent&) = 0;
		
		/**	Apply the specified CMS on/off state to the selection.
			@param cmsOfOff on (kTrue) or off (kFalse).
			@precondition CanApplyCMS() == kTrue. 
		*/
		virtual ErrorCode	ApplyCMSState			(const bool16& cmsOnOff) = 0;
		
		/**	Apply the embedded profile to the selection.
			@precondition CanApplyEmbeddedProfile() == kTrue. 
		*/
		virtual ErrorCode	ApplyEmbeddedProfile	(void) = 0;
		
		/**	Apply the document's default profiles to the selection.
			@precondition CanApplyCMS() == kTrue. 
		*/
		virtual ErrorCode	ApplyDocDefaultProfile	(void) = 0;
		
		/**	Apply the specified profile to the selection.
			@param profileName the name of the profile to apply.
			@precondition CanApplyCMS() == kTrue. 
		*/
		virtual ErrorCode	ApplyExternalProfile	(const PMString&) = 0;
		
		/**	Returns the current profile name for embedded, read-only profiles. 
			Returns kTrue if selected items have embedded, read-only profiles; returns 
			kFalse if selected items do not have such profiles or if selection is mixed.

			@param name		The profile's name if present, read-only, and embedded
		*/
		virtual bool16		GetEmbeddedReadOnlyProfileName(PMString &name) = 0;

};

#endif		// __ICMSAttributeSuite__