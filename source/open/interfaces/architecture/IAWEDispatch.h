//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/architecture/IAWEDispatch.h $
//  
//  Owner: Steve Flenniken
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
#ifndef __IAWEDispatch__
#define __IAWEDispatch__

#include "awe.h"

enum aweDispatch {aweGoToAdobe, aweGoToURL, aweDoAWEPrefs, aweDisplayTopIssues,
					aweDisplayDownloadables, aweDoOnlineRegistration, 
					aweDisplayCorporateNews, 
					aweDoNotification, aweDoOnlineRegistrationStart
};

// IID_IAWEDISPATCH interface

class IAWEDispatch : public IPMUnknown
{
public:
	virtual AWE_error_code Dispatch(aweDispatch what, const char *str = NULL) = 0;
	virtual bool16 AWENewDownloadsExist() = 0;
	virtual uint16 GetBookMarkCountAndSize(uint16 *size, AWE_BookMarks whichmenu) = 0;
	virtual void GetBookMarkNames(char *buffer, AWE_BookMarks whichmenu) = 0;
	virtual void GotoBookMark(int16 bookMarkLocation, AWE_BookMarks whichMenu) = 0;
	virtual AWE *GetAWEInstance() = 0;
	virtual void InitializeAdobeOnline() = 0;
	virtual void ShutdownAdobeOnline() = 0;
};

void GlobalShutdownAdobeOnline();

#endif // __IAWEDispatch__
