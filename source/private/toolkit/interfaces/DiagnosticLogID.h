//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/private/toolkit/interfaces/DiagnosticLogID.h $
//  
//  Owner:
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
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#ifndef __DIAGNOSTICLOGID_H_
#define __DIAGNOSTICLOGID_H_


#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kDiagnosticLogPrefix	 					RezLong(0x1E500)

//----------------------------------------------------------------------------------------
// Plug-in identifier
//----------------------------------------------------------------------------------------
#define kDiagnosticLogPluginName	"DiagnosticLog"			// Name of this plug-in.				
DECLARE_PMID (kPlugInIDSpace,		kDiagnosticLogPluginID,		kDiagnosticLogPrefix + 1)


//----------------------------------------------------------------------------------------
// Class identifiers
//----------------------------------------------------------------------------------------
DECLARE_PMID (kClassIDSpace, kDiagLogStartupShutdownBoss,	kDiagnosticLogPrefix + 1)
DECLARE_PMID (kClassIDSpace, kXMLDiagnosticLoggerBoss,		kDiagnosticLogPrefix + 2)  
DECLARE_PMID (kClassIDSpace, kTextDiagnosticLoggerBoss,		kDiagnosticLogPrefix + 3)  
DECLARE_PMID (kClassIDSpace, kDiagLogConfigManagerBoss,		kDiagnosticLogPrefix + 4)
DECLARE_PMID (kClassIDSpace, kDiagLoggerManagerBoss,		kDiagnosticLogPrefix + 5)
DECLARE_PMID (kClassIDSpace, kDiagLogModifierBoss,			kDiagnosticLogPrefix + 6)
DECLARE_PMID (kClassIDSpace, kDiagnosticLogIdleTaskBoss,	kDiagnosticLogPrefix + 7)


//----------------------------------------------------------------------------------------
// Interface identifiers
//----------------------------------------------------------------------------------------
DECLARE_PMID(kInterfaceIDSpace, IID_IDIAGNOSTICLOG,			kDiagnosticLogPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IDIAGLOGIDDATABASE,		kDiagnosticLogPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IDIAGLOGCONFIGMANAGER,	kDiagnosticLogPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IDIAGLOGGERMANAGER,		kDiagnosticLogPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IDIAGNOSTICLOGGER,		kDiagnosticLogPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IDIAGLOGMODIFIER,		kDiagnosticLogPrefix + 6)


//----------------------------------------------------------------------------------------
// Implementation identifiers
//----------------------------------------------------------------------------------------
DECLARE_PMID (kImplementationIDSpace, kDiagLogStartupShutdownImpl,			kDiagnosticLogPrefix + 1)
DECLARE_PMID (kImplementationIDSpace, kDiagLogIDDatabaseImpl,				kDiagnosticLogPrefix + 2)
DECLARE_PMID (kImplementationIDSpace, kDiagLoggerServiceProviderImpl,		kDiagnosticLogPrefix + 3)
DECLARE_PMID (kImplementationIDSpace, kTextDiagnosticLoggerImpl,			kDiagnosticLogPrefix + 4)
DECLARE_PMID (kImplementationIDSpace, kXMLDiagnosticLoggerImpl,				kDiagnosticLogPrefix + 5)
DECLARE_PMID (kImplementationIDSpace, kDiagnosticLogImpl,					kDiagnosticLogPrefix + 6)
DECLARE_PMID (kImplementationIDSpace, kDiagLogModifierImpl,					kDiagnosticLogPrefix + 7)
DECLARE_PMID (kImplementationIDSpace, kDiagLogIDDBContentHandlerImpl,		kDiagnosticLogPrefix + 8)
DECLARE_PMID (kImplementationIDSpace, kDiagLogPrefsContentHandlerImpl,		kDiagnosticLogPrefix + 9)
DECLARE_PMID (kImplementationIDSpace, kDiagLogConfigManagerImpl,			kDiagnosticLogPrefix + 10)
DECLARE_PMID (kImplementationIDSpace, kDiagLoggerManagerImpl,				kDiagnosticLogPrefix + 11)
DECLARE_PMID (kImplementationIDSpace, kDiagLogModifierServiceProviderImpl,	kDiagnosticLogPrefix + 12)
DECLARE_PMID (kImplementationIDSpace, kDiagnosticLogIdleTaskImpl,			kDiagnosticLogPrefix + 13)


//----------------------------------------------------------------------------------------
// Widget identifiers
//----------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------
// Service identifiers
//----------------------------------------------------------------------------------------
DECLARE_PMID(kServiceIDSpace, kDiagnosticLoggerService,		kDiagnosticLogPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kDiagLogModifierService,		kDiagnosticLogPrefix + 2)


//----------------------------------------------------------------------------------------
// Message identifiers
//----------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------
// Action identifiers
//----------------------------------------------------------------------------------------

	
#endif // 


