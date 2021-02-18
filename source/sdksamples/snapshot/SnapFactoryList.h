//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snapshot/SnapFactoryList.h $
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
//========================================================================================

REGISTER_PMINTERFACE(SnapActionComponent, kSnapActionComponentImpl)
REGISTER_PMINTERFACE(SnapTool, kSnapToolImpl)
REGISTER_PMINTERFACE(SnapTracker, kSnapTrackerImpl)
REGISTER_PMINTERFACE(SnapTrackerRegister, kSnapTrackerRegisterImpl)
REGISTER_PMINTERFACE(SnapCursorProvider, kSnapCursorProviderImpl)
REGISTER_PMINTERFACE(SnapDialogController, kSnapDialogControllerImpl)
REGISTER_PMINTERFACE(SnapPrefsDataPersist, kSnapPrefsDataPersistImpl)
REGISTER_PMINTERFACE(SnapPrefsData, kSnapPrefsDataImpl)
REGISTER_PMINTERFACE(SnapSetPrefsCmd, kSnapSetPrefsCmdImpl)
REGISTER_PMINTERFACE(SnapIteratorRegister, kSnapIteratorRegisterImpl)
REGISTER_PMINTERFACE(SnapSelectionSuiteASB, kSnapSelectionSuiteASBImpl)
REGISTER_PMINTERFACE(SnapSelectionSuiteCSB, kSnapSelectionSuiteCSBImpl)
REGISTER_PMINTERFACE(SnapErrorStringService, kSnapErrorStringServiceImpl)
REGISTER_PMINTERFACE(SnapPrefsScriptProvider, kSnapPrefsScriptProviderImpl)

// End, SnapFactoryList.h.


