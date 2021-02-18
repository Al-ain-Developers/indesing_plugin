//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ICSXSPlugPlugStartupShutdownService.h $
//  
//  Owner: Ramnik Singh
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
//  Copyright 2017 Adobe 
//  All Rights Reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in 
//  accordance with the terms of the Adobe license agreement accompanying 
//  it. If you have received this file from a source other than Adobe, 
//  then your use, modification, or distribution of it requires the prior 
//  written permission of Adobe.
//  
//========================================================================================

#include "IStartupShutdownService.h"
#include "CSXSID.h"

/**
Services that implement this interface and use kCSXSPlugPlugStartupShutdownProviderImpl as the service provider are started up when the CEP extensions ecosystem is 
intialized and extensions have registered and are shutdown when the CEP extensions ecosystem also shuts down.
*/
class ICSXSPlugPlugStartupShutdownService : public IStartupShutdownService
{
public:
	enum { kDefaultIID = IID_ICSXSPLUGPLUGSTARTUPSHUTDOWNSERVICE } ;

	/**	This API is invoked when the CEP extensions ecosystem has been initialized */
	virtual void Startup() = 0 ;

	/**	This API is invoked just before the CEP extensions ecosystem is terminated */
	virtual void Shutdown() = 0;
} ;


