//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightWaxInfo.h $
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
#include "IPMUnknown.h"
#include "PackageAndPreflightID.h"

class IWaxRun;

/**	This interface, in combination with IPreflightTextRangeInfo, provides information 
	about a particular wax (run or line) found in the document. This interface is used
	by preflight rules (IPreflightRuleVisitor) that inspect wax runs.

	Typical application (in IPreflightRuleVisitor::Visit):

		InterfacePtr<IPreflightObject> iObj(iInfo->QueryObject());
		InterfacePtr<IPreflightWaxInfo> iWaxInfo(iObj, UseDefaultIID());
		InterfacePtr<IPreflightTextRangeInfo> iTextRangeInfo(iObj, UseDefaultIID());

		// Use iWaxInfo and iTextRangeInfo to interrogate text attributes.
*/

class IPreflightWaxInfo : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTWAXINFO };

	/** Get the number of glyphs in this run.
		@return The number of glyphs in this run.
	*/
	virtual int32 GetNumGlyphs() const = 0;

	/** Query the run data.
		@note This will be valid as long as the IPreflightWaxInfo interface is valid; do not
			refcount it in such a way that its lifecycle is longer than this interface!
		@return A refcounted waxrun interface.
	*/
	virtual const IWaxRun* QueryRun() const = 0;

	/** Initialize based on preflight object ID. For internal use only.
	*/
	virtual void Initialize() = 0;
};

