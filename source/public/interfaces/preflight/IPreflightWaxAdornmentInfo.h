//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightWaxAdornmentInfo.h $
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
//  ADOBE CONFIDENTIAL
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
#include "IPMUnknown.h"
#include "PackageAndPreflightID.h"
class IWaxRun;

class ITextModel;

/**	This interface, in combination with IPreflightTextRangeInfo and IPreflightWaxInfo,
	provides information about an adornment on a particular wax (run or line) found in 
	the document. This interface is used by preflight rules (IPreflightRuleVisitor) that 
	inspect wax run adornments.

	Typical application (in IPreflightRuleVisitor::Visit):

		InterfacePtr<IPreflightObject> iObj(iInfo->QueryObject());
		InterfacePtr<IPreflightWaxInfo> iWaxInfo(iObj, UseDefaultIID());
		InterfacePtr<IPreflightWaxAdornmentInfo> iWaxAdornInfo(iObj, UseDefaultIID());

		if (iWaxAdornInfo && iWaxAdornInfo->GetAdornmentID() == kMyAdornmentOfInterest)
		{
			...
		}
*/

class IPreflightWaxAdornmentInfo : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTWAXADORNMENTINFO };

	/** Get the class ID of the adornment.
		@return The adornment's class ID.
	*/
	virtual ClassID GetAdornmentID() const = 0;

	/** Initialize based on preflight object ID. For internal use only.
	*/
	virtual void Initialize() = 0;
};

