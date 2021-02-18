//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightArtworkOPIContext.h $
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

/**	This interface provides OPI context for a marking operation, group, or context. It's 
	quite minimal because the only thing it reports is its presence; ie if there is such
	a context, then the artwork is drawn within OPI.

	You probably never need to use this interface unless you're walking the artwork 
	context stack directly (see IPreflightArtworkContext). Normally you'd simply call 
	IPreflightArtworkContext::GetOPIContextDepth() to see if one of these contexts exists.
*/

class IPreflightArtworkOPIContext : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTARTWORKOPICONTEXT };

	/** Get the OPI depth; that is, how deep within nested OPI structures this node is. Typically
		this is either 0 or 1, but in theory they could be nested at export time.
	*/
	virtual int32 GetDepth() const = 0;

	/** Determine whether this particular node is an OPI context node.
	*/
	virtual bool IsOPINode() const = 0;
};

