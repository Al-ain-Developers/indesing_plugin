//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IStyleSignalData.h $
//  
//  Owner: Frank Rubino
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
//  Purpose:	Data sent with style import and export signals
//  
//========================================================================================

#pragma once
#ifndef __IStyleSignalData__
#define __IStyleSignalData__

// ----- Interfaces -----

#include "IPMUnknown.h"

// ----- ID.h files -----

#include "GenericSettingsID.h"


class ICommand;

/** IStyleSignalData is an interface used in sending signals when styles have been
	imported from or exported to sysfiles. A responder can take some action on the 
	target file when a style is  imported or exported
 */

class IStyleSignalData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGENSTLSIGNALDATA };
	
	/**
		 Sets the file that was imported from or exported to
		 @param file IN the file containing the style
		 @return void
	   */
	virtual void Set(const IDFile &file) = 0;
	
	
	/**
		 Gets the file that was imported from or exported to
		 @return IDFile representing the file containing the style
	   */
	virtual const IDFile &GetFile() const = 0;			// the associated file
};

#endif // __IStyleSignalData__

