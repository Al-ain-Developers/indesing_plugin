//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/architecture/IURLAccess.h $
//  
//  Owner: Brendan O'Shea
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
//  IURLAccess is the abstract interface to a hyperlink
//  
//========================================================================================

#pragma once
#ifndef __IURLAccess__
#define __IURLAccess__

#include "IPMUnknown.h"
#include "AppInfo.h"

class PMString;

class IURLAccess : public IPMUnknown
{
public:
	//
	// Invoke the approriate application to jump to the specified URL; on the
	//	Mac this uses InternetConfig, ShellExecute on the PC.
	//	Returns kTrue if it appears to succeed; kFalse if the system functions
	//	return an error code.
	//
	virtual bool16	GoToURL(PMString *theURL, const AppInfo* appInfo = NULL) = 0;

	// Tear down & free any memory allocated
	virtual void	Shutdown() = 0;

	//
	// Check to see if there is an internet connection (only useful on Windows platform - always returns kTrue on Mac)
	//
	virtual bool16	HasInternetConnection() = 0;
};

#endif
