//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/colormgmt/ICMSProofing.h $
//  
//  Owner: James Jardee-Borquist
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

#ifndef __ICMSProofing__
#define __ICMSProofing__

#if PRAGMA_ONCE
#pragma once
#endif

#include "ICMSSettings.h"
#include "IPMUnknown.h"
#include "BravoForwardDecl.h"

#include "ACEColorMgmtID.h"

class ICMSProfile;
class IRasterPort;

//========================================================================================
// CLASS ICMSProofing
//========================================================================================

class ICMSProofing : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICMSPROOFING };
	
	enum ProofingType {
		kCustom,
		kSimulateDocCMYK,
		kSimulateWorkingCMYK,
		kSimulateMacintoshRGB,
		kSimulateWindowsRGB,
		kSimulateMonitorRGB
	};
	
	virtual bool16 GetIsProofingOn() const = 0;
	virtual void SetIsProofingOn(bool16 isProofingOn) = 0;
	
	virtual ProofingType GetProofingType() const = 0;
	virtual void SetProofingType(ProofingType proofingType) = 0;
	
	/** Obtains the current settings.  All of these use the custom
	*/
	virtual bool32 GetEffectivePreserveNumbers() const = 0;
	virtual bool32 GetEffectivePaperWhite() const = 0;
	virtual bool32 GetEffectiveInkBlack() const = 0;

	/** Gets and sets the CUSTOM preserve-numbers setting.
	*/
	virtual bool32 GetPreserveNumbers() const = 0;
	virtual void SetPreserveNumbers(bool32 preserveEm) = 0;
	
	virtual ICMSProfile *QueryProfile() = 0;
	virtual void SetProfile(ICMSProfile *profile) = 0;
	
	/** Returns the proof profile, preconfigured with the appropriate RI given the current
		PW/IB settings.  Does *not* include any other profiles for the sequence to the monitor,
		only the proof space.
	*/
	virtual AGMColorProfile* GetProofProfile() = 0;
	virtual void ReleaseProfile(AGMColorProfile* spc) = 0;

	// GetProfileName
	// 
	// Returns the name of the currently selected proofing profile. Will be the string "Simulate 
	// Composite" or "Simulate Separation" when the current proofing type is kSimulateComposite or 
	// kSimulateSeparation. Use GetCustomProfileName to get the name of the custom profile even if 
	// the current proofing type is not kCustom.
	virtual void GetProfileName(PMString &profileName) const = 0;
	
	// GetCustomProfileName
	// SetCustomProfileName
	// 
	// Returns/sets the name of the custom proofing profile even if the current proofing type is not 
	// kCustom. Use GetProfileName to get the name of the current proofing profile.
	virtual void GetCustomProfileName(PMString &customProfileName) const = 0;
	virtual void SetCustomProfileName(const PMString& customProfileName) = 0;
	
	/** Note: These get and set the CUSTOM settings, which may or may not be in use depending
		on the proofing type.  If you want to know the current in-use type, use GetEffective* above.
	*/
	virtual bool32 GetSimulatePaperWhite() const = 0;
	virtual bool32 GetSimulateInkBlack() const = 0;
	virtual void SetSimulatePaperWhite(bool32 sim) = 0;
	virtual void SetSimulateInkBlack(bool32 sim) = 0;
	
	virtual void SetupProofingForGlobalOffscreens() = 0;
	virtual void RestoreProofingForGlobalOffscreens() = 0;
	
	virtual void SetupProofing(IRasterPort *iRasterPort) = 0;
	virtual void RestoreProofing(IRasterPort *iRasterPort) = 0;
};

#endif // __ICMSProofing__

// End, ICMSProofing.h.
