//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlist/PstLstFactoryList.h $
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
//  
//  Each C++ implementation class in the plug-in and its corresponding ImplementationID
//  should be registered in this file.
//  
//  REGISTER_PMINTERFACE(PstLstActionComponent, kPstLstActionComponentImpl) // moved to UI plug-in
//  REGISTER_PMINTERFACE(PstLstDlgController, kPstLstDlgControllerImpl) // moved to UI plug-in
//  
//========================================================================================

REGISTER_PMINTERFACE(PstLstUIDList, kPstLstUIDListImpl)
REGISTER_PMINTERFACE(PstLstData, kPstLstDataImpl)
REGISTER_PMINTERFACE(PstLstDataPersist, kPstLstDataPersistImpl)
REGISTER_PMINTERFACE(PstLstLayoutCSB, kPstLstLayoutCSBImpl)
REGISTER_PMINTERFACE(PstLstASB, kPstLstASBImpl)
REGISTER_PMINTERFACE(PstLstNewDataCmd, kPstLstNewDataCmdImpl)
REGISTER_PMINTERFACE(PstLstModifyDataCmd, kPstLstModifyDataCmdImpl)
REGISTER_PMINTERFACE(PstLstDeleteDataCmd, kPstLstDeleteDataCmdImpl)
REGISTER_PMINTERFACE(PstLstDeletePageItemCmd, kPstLstDeletePageItemCmdImpl)
REGISTER_PMINTERFACE(PstLstDocObserver, kPstLstDocObserverImpl)
REGISTER_PMINTERFACE(PstLstDocResponder, kPstLstDocResponderImpl)
REGISTER_PMINTERFACE(PstLstDocServiceProvider, kPstLstDocServiceProviderImpl)
REGISTER_PMINTERFACE(PstLstReferenceConverter, kPstLstReferenceConverterImpl)
REGISTER_PMINTERFACE(SelectionExt<PstLstLayoutCSB>, kPstLstSuiteLayoutSelectionExtImpl)
REGISTER_PMINTERFACE(PstLstScriptProvider, kPstLstScriptProviderImpl)
REGISTER_PMINTERFACE(PstLstScript, kPstLstScriptImpl)
REGISTER_PMINTERFACE(PstLstErrorStringService, kPstLstErrorStringServiceImpl)
REGISTER_PMINTERFACE(PstLstPhase2Conversion, kPstLstPhase2ConversionImpl)

//  Generated by Dolly build 17: template "IfPanelMenu".
// End, PstLstFactoryList.h.
