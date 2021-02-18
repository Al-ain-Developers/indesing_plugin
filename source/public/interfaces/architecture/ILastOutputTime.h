//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILastOutputTime.h $
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
//  
//  Description:
//  This class defines an interface used to hold the date and time the document was last
//  printed, or exported to PDF.
//  
//========================================================================================

#pragma once
#ifndef __ILastOutputTime__
#define __ILastOutputTime__

// ----- Includes -----
#include "IPMUnknown.h"
#include "DocFrameworkID.h"

class IDTime;


/**
 Interface used to hold the date and time the document was last
 printed, or exported to PDF.
 @see IDTime
 */
class ILastOutputTime : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILASTOUTPUTTIME };

	/**
	 Returns the last output time.
	 @return Last output time.
	 */ 
	virtual IDTime Get() const = 0;

	/**
	 Sets the last output time to the current time.
	 */ 
	virtual void Set() = 0;
};

#endif // __ILastOutputTime__
