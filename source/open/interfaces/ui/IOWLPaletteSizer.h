//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/ui/IOWLPaletteSizer.h $
//  
//  Owner: lance bushore
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
#ifndef __IOWLPaletteSizer_h__
#define __IOWLPaletteSizer_h__

#include "IPMUnknown.h"
#include "AppUIID.h"

/** Interface to communicate palette size changes to OWL. Specifically handles telling OWL new min and max sizes for the palette.
*/

class IOWLPaletteSizer : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IOWLPALETTESIZER };

	/** Calculate the min and max size for this palette, and pass that information to OWL.
	*/
	virtual void UpdateOWLPaletteSizes( ) const = 0;
	
	/** Calculate the number of panel detail states, and pass that information to OWL.
	*/
	virtual void UpdateOWLStateCounts() const = 0;

};

#endif // __IOWLPaletteSizer_h__

