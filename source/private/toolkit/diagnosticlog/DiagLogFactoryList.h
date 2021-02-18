//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/private/toolkit/diagnosticlog/DiagLogFactoryList.h $
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

REGISTER_PMINTERFACE(DiagnosticLog, kDiagnosticLogImpl)
REGISTER_PMINTERFACE(DiagLogConfigManager, kDiagLogConfigManagerImpl)
REGISTER_PMINTERFACE(DiagLogIDDatabase, kDiagLogIDDatabaseImpl)
REGISTER_PMINTERFACE(DiagLoggerManager, kDiagLoggerManagerImpl)
REGISTER_PMINTERFACE(DiagLogStartupShutdown, kDiagLogStartupShutdownImpl)
REGISTER_PMINTERFACE(DiagLogPrefsContentHandler, kDiagLogPrefsContentHandlerImpl)
REGISTER_PMINTERFACE(XMLDiagnosticLogger, kXMLDiagnosticLoggerImpl)
REGISTER_PMINTERFACE(TextDiagnosticLogger, kTextDiagnosticLoggerImpl)
REGISTER_PMINTERFACE(DiagLoggerServiceProvider, kDiagLoggerServiceProviderImpl)
REGISTER_PMINTERFACE(DiagLogIDDBContentHandler, kDiagLogIDDBContentHandlerImpl)
REGISTER_PMINTERFACE(DiagLogModifier, kDiagLogModifierImpl)
REGISTER_PMINTERFACE(DiagLogModifierServiceProvider, kDiagLogModifierServiceProviderImpl)
REGISTER_PMINTERFACE(DiagnosticLogIdleTask, kDiagnosticLogIdleTaskImpl)
//REGISTER_PMINTERFACE(ActivityLoggerData, kActivityLoggerDataImpl)
