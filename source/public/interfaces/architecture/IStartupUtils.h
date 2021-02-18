//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IStartupUtils.h $
//  
//  Owner: Matt Joss
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
#ifndef __IStartupUtils__
#define __IStartupUtils__

#include "AppFrameworkID.h"
#include "Utils.h"

/** Utility interface for Startup related methods
*/
class IStartupUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISTARTUPUTILS };

	/** 
		Can be called at Startup to determine if files will be opened when the app starts up.  Modal
		dialogs that are opened upon startup should not be opened when opening files.  This is called
		from scheduled startup commands to determine whether or not to show their dialog.  Calling this too
		early may not function correctly
	*/
	virtual bool16			WillFilesBeOpenedAtStartup(  ) const = 0;
};

#endif //__IStartupUtils__
