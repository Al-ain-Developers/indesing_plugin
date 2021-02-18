//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/chlinguistic/CHLServiceProvider.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "VCPlugInHeaders.h"		

// Interface includes:
#include "ILinguisticServiceData.h"

// General includes:
#include "CHLUtils.h"
#include "CServiceProvider.h"

// Project includes:
#include "CHLID.h"

/** Implements a linguistic service provider. When your IK2ServiceProvider:Install() method is
 *  called you should populate interface IID_ILINGUISTICDATA with appropriate data.
 *  
 * 	
 *  @ingroup chlinguistic
*/
class CHLServiceProvider : public CServiceProvider
{
	public:
		/**	Constructor.
		 *  @param boss interface ptr from boss object on which this interface is aggregated.
		*/
		CHLServiceProvider(IPMUnknown* boss);

		/** A service provider can choose to have one instance that is shared 
		 * 	by all requests for that service providers (this is the most 
		 * 	common case - kInstancePerSession), or a service provider may 
		 * 	choose to have a unique instance created on each request for the 
		 * 	service provider (kInstancePerUse).
		 * 	"Instance Per Session" service providers are created when first 
		 * 	requested and cached by the service registry as long as available 
		 * 	memory allows.
		 *  kInstancePerSessionPreload will cause a service provider to be
		 * 	constructed and cached at application startup.
		 * 	Furthermore, a "preload" service provider will not be unloaded 
		 * 	until application shutdown.
		 * 
		 * 	Note:  Since "preload" service providers are never unloaded, 
		 * 	they incur the memory overhead for the service and cause the 
		 * 	plug-in that contains the service to not be unloaded.
		 *  Therefore "preload" service providers should be avoided, when 
		 * 	possible. If you need to be called at startup and/or shutdown, 
		 * 	use a kStartupShutdownServiceID.
		 *  
		 * 	@return IK2ServiceProvider::kInstancePerSession
		*/
		virtual IK2ServiceProvider::InstancePerX GetInstantiationPolicy();
		
		/** For the majority of service providers this method should return 
		 * 	kFalse. However, if a specific service provider should always be
		 * 	the default for its service this can be set to kTrue.
		 * 
		 * 	@return kFalse
		*/
		virtual bool16 	IsDefaultServiceProvider();
		
		/** A service may optionally have a name.
		 * 	But the service registry does not use this name in any way.
		 * 
		 *  @param pName OUT Optionally service name.
		*/
		virtual void GetName(PMString* pName);
		
		/**	The ServiceID the boss this interface is aggregated into supports.
		 *  
		 *  @return kLinguisticService
		*/
		virtual ServiceID GetServiceID();

	protected:
		/**	We post the name of our service and the absolute path to the folder 
		 * 	that we expect to contain the files that support our linguistic service 
		 * 	in interface IID_ILINGUISTICDATA.
		*/
		virtual void Install();
		virtual IPlugIn::ThreadingPolicy GetThreadingPolicy() const
			{return IPlugIn::kMultipleThreads;}
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(CHLServiceProvider, kCHLServiceProviderImpl)


/* CHLServiceProvider constructor 
*/
CHLServiceProvider::CHLServiceProvider(IPMUnknown* boss) :
	CServiceProvider(boss)
{
	this->Install();
}

/* CHLServiceProvider::GetInstantiationPolicy
*/
IK2ServiceProvider::InstancePerX CHLServiceProvider::GetInstantiationPolicy()
{
	return IK2ServiceProvider::kInstancePerSession;
}

/* CHLServiceProvider::IsDefaultServiceProvider
*/
bool16 CHLServiceProvider::IsDefaultServiceProvider()
{
	return kFalse;
}

/* CHLServiceProvider::GetName
*/
void CHLServiceProvider::GetName(PMString* pName)
{
	ASSERT_MSG(pName != nil, "CHLServiceProvider - name is nil ");
	InterfacePtr<ILinguisticServiceData> pData(this, IID_ILINGUISTICDATA);
	*pName = pData->GetServiceName();

}

/* CHLServiceProvider::GetServiceID
*/
ServiceID CHLServiceProvider::GetServiceID()
{
	return kLinguisticService;
}

/* CHLServiceProvider::Install
*/
void CHLServiceProvider::Install()
{
	do
	{
		// We post the name of our service and the absolute path
		// to the folder that we expect to contain the files
		// that support our linguistic service in interface
		// IID_ILINGUISTICDATA.
		InterfacePtr<ILinguisticServiceData> iLinguisticServiceData(this, IID_ILINGUISTICDATA);
		if (iLinguisticServiceData == nil)
		{
			ASSERT_FAIL("CHLServiceProvider::Install() iLinguisticServiceData invalid");
			break;
		}
	
		// 1) Set the service name
		const PMString serviceName(kCHShortName);
		iLinguisticServiceData->SetServiceName(serviceName);	
	
		// 2) Set the absolute path to our data files

		// 2.1) Find the folder in which the application is installed.
		PMString applicationFolder;
		if (CHLUtils::GetApplicationFolder(applicationFolder) != kSuccess)
		{
			break;
		}

		// 2.2) The folder in which Code Hawgs linguistics files are installed
		// is a sub folder under the application folder. We build the
		// absolute path to this folder here.
		PMString codeHawgsLinguisticsFolder = applicationFolder;

		const PMString subFolder(kCHLinguisticFilesSubFolder);
		codeHawgsLinguisticsFolder.Append(subFolder);
		iLinguisticServiceData->SetPath(codeHawgsLinguisticsFolder);

	} while (false); // only do once
}

// End, CHLServiceProvider.cpp

