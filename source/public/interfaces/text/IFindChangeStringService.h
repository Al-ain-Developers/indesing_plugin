//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IFindChangeStringService.h $
//  
//  Owner: Tommy Donovan
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
#ifndef __IFindChangeStringService__
#define __IFindChangeStringService__

#include "TextWalkerServiceProviderID.h"
#include "IPMUnknown.h"
#include "FindChangeID.h"

class PMString;

/** An interface that allows a service provider to modify the find and replace
	strings prior to a find and replace through the Find and Change panel.
*/
class IFindChangeStringService : public IPMUnknown
{
public:
	/** Standard enum to for use with GetDefaultIID() method.
	*/
	enum { kDefaultIID = IID_IFINDCHANGESTRINGSERVICE };

	
	/** 	Modify the Find/Change strings by calling SetFindString & SetReplaceString.
			@param optionStringCmdBoss the ClassID indicating which command is about to be
				invoked. If optionStringCmdBoss is kFindStringCmd, theString will be the new
				find string. If optionStringCmdBoss is kReplaceStringCmd, theString will be the
				new replace string.
			@param theString is the PMString to be examined and modified if desired
			@return kTrue if the string was modified, otherwise return kFalse.
	*/
	virtual	bool16 ModifyFindChangeString(ClassID optionStringCmdBoss, PMString& theString) = 0;
};


#endif // __IFindChangeOptionsService__
