//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/external/afl/includes/AErrors.h $
//  
//  Owner: Michael Easter
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
#ifndef __AErrors__
#define __AErrors__

#include "ATypes.h"

#ifdef MACINTOSH
#include <CoreServices/CoreServices.h>
#endif

namespace adobe {
namespace afl {

#ifdef WINDOWS
typedef uint32	AOSErr;	// DWORD
#elif defined MACINTOSH
/** Macintosh system error code. */
typedef OSErr	AOSErr;
#endif

/** AFL error code. */
typedef uint32	AError;

/** Denotes operation succeeded. */
const AError kAFLSuccess = 0;
/** Denotes operation failed. */
const AError kAFLFailure = 1;
/** Denotes an alias could not be resolved. */
const AError kAFLResolveAliasError = 2;

}	// namespace afl
}	// namespace adobe

#endif	// __AErrors__
