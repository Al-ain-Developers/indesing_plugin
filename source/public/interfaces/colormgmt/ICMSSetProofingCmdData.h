//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/colormgmt/ICMSSetProofingCmdData.h $
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
#ifndef __ICMSSetProofingCmdData__
#define __ICMSSetProofingCmdData__

#include "ColorMgmtID.h"
#include "ICMSProofing.h"

class ICMSSetProofingCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICMSSETPROOFINGCMDDATA };

	virtual bool32 GetIsProofingOn(bool32* setIt = nil) const = 0;
	virtual void SetIsProofingOn(bool32, bool32 setIt = kTrue) = 0;
	
	virtual ICMSProofing::ProofingType GetProofingType(bool32* setIt = nil) const = 0;
	virtual void SetProofingType(ICMSProofing::ProofingType, bool32 setIt = kTrue) = 0;
	
	virtual PMString GetProfileName(bool32* setIt = nil) const = 0;
	virtual void SetProfileName(PMString&, bool32 setIt = kTrue) = 0;
	
	virtual ICMSProfile* GetCMSProfile(bool32* setIt = nil) const = 0;
	virtual void SetCMSProfile(ICMSProfile*, bool32 setIt = kTrue) = 0;
	
	virtual bool32 GetSimulatePaperWhite(bool32* setIt = nil) const = 0;
	virtual void SetSimulatePaperWhite(bool32, bool32 setIt = kTrue) = 0;
	
	virtual bool32 GetSimulateInkBlack(bool32* setIt = nil) const = 0;
	virtual void SetSimulateInkBlack(bool32, bool32 setIt = kTrue) = 0;

	virtual bool32 GetPreserveNumbers(bool32* setIt = nil) const = 0;
	virtual void SetPreserveNumbers(bool32, bool32 setIt = kTrue) = 0;
};
#endif // __ICMSSetProofingCmdData__

// End, ICMSSetProofingCmdData.h.
