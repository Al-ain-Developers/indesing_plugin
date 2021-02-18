//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalinkui/CusDtLnkUISSService.cpp $
//  
//  Owner: Mark VerMurlen
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

#include "CServiceProvider.h"
#include "CusDtLnkUIID.h"

//___________________________________________________________________________________
//    CLASS DECLARATIONS
//___________________________________________________________________________________
class CusDtLnkUISSService : public CServiceProvider
{
    //___________________________________________________________________________
    //    Object Maintainance
    //___________________________________________________________________________
    public:
                                CusDtLnkUISSService(IPMUnknown*);
                                ~CusDtLnkUISSService();

    //___________________________________________________________________________
    //    Context Observer
    //___________________________________________________________________________
    public:
        virtual void            GetName(PMString*);
        virtual ServiceID        GetServiceID(void);
        virtual bool16             IsDefaultServiceProvider(void);

        virtual InstancePerX    GetInstantiationPolicy(void);
};

//___________________________________________________________________________________
//    SHUKSAN OBJECT MACROS
//___________________________________________________________________________________
CREATE_PMINTERFACE (CusDtLnkUISSService, kCusDtLnkUISSServiceImpl)


//===================================================================================
//___________________________________________________________________________________
//    DESCR:        Constructor
//___________________________________________________________________________________
CusDtLnkUISSService::CusDtLnkUISSService ( IPMUnknown* boss ) :
    CServiceProvider (boss)
{
}


//===================================================================================
//___________________________________________________________________________________
//    DESCR:        Destructor
//___________________________________________________________________________________
CusDtLnkUISSService::~CusDtLnkUISSService()
{
}


//___________________________________________________________________________________
//    DESCR:        Return the name of the service provider in "pName".
//___________________________________________________________________________________
void CusDtLnkUISSService::GetName( PMString*    pName )
{
    *pName = PMString ("CusDtLnkStartShutdownService");
    pName->Translate();
}

//___________________________________________________________________________________
//    DESCR:        Return the ServiceID of this provider.
//
//    RETURNS:    kStartupShutdownService
//___________________________________________________________________________________
ServiceID CusDtLnkUISSService::GetServiceID( void )
{
    return kStartupShutdownService;
}

//___________________________________________________________________________________
//    DESCR:        This is not the default startup/shutdown service provider.
//
//    RETURNS:    False
//___________________________________________________________________________________
bool16 CusDtLnkUISSService::IsDefaultServiceProvider( void )
{
    return kFalse;
}

//___________________________________________________________________________________
//    DESCR:        This provider should be instantiated only once per session.
//
//    RETURNS:    kInstancePerSession
//___________________________________________________________________________________
IK2ServiceProvider::InstancePerX CusDtLnkUISSService::GetInstantiationPolicy( void )
{
    return IK2ServiceProvider::kInstancePerSession;
}
