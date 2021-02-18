//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/GenericSettingsID.h $
//  
//  Owner: Chris Jones
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
//  Contains IDs used by the EPSExportUI plug-in
//  
//========================================================================================

#ifndef __GenericSettingsID__
#define __GenericSettingsID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kGenericSettingsPrefix  RezLong(0x13D00)

// <Start IDC>
// PluginID
#define kGenericSettingsPluginName			"Generic Settings"

START_IDS()
#if 1
DECLARE_PMID(kPlugInIDSpace, kGenericSettingsPluginID, kGenericSettingsPrefix + 1)

// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kGenericSettingsBoss,               kGenericSettingsPrefix + 1)
DECLARE_PMID(kClassIDSpace, kGenericSettingsGroupBoss,          kGenericSettingsPrefix + 2)
DECLARE_PMID(kClassIDSpace, kGenericSettingsAttributeBoss,      kGenericSettingsPrefix + 3)
DECLARE_PMID(kClassIDSpace, kHumanTextOutputStrategyBoss,       kGenericSettingsPrefix + 4)
DECLARE_PMID(kClassIDSpace, kGenericSettingsExportCmdDataBoss,  kGenericSettingsPrefix + 5)
DECLARE_PMID(kClassIDSpace, kGenericSettingsExportCmdBoss,      kGenericSettingsPrefix + 6)

// ---- Move from Generic Style Editor plug-in
DECLARE_PMID(kClassIDSpace, kGenStlEdtExportStylesCmdBoss, 		kGenericSettingsPrefix + 7)
DECLARE_PMID(kClassIDSpace, kGenStlEdtImportStylesCmdBoss, 		kGenericSettingsPrefix + 8)
DECLARE_PMID(kClassIDSpace, kGenStlSignalMgrBoss,				kGenericSettingsPrefix + 9)
// ---- end move.

// <Interface ID>
// Interface IDs
DECLARE_PMID(kInterfaceIDSpace, IID_IGENERICSETTINGS,               kGenericSettingsPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IGENERICSETTINGSGROUP,          kGenericSettingsPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IGENERICSETTINGSATTRIBUTE,      kGenericSettingsPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IGENERICSETTINGSOUTPUTSTRATEGY, kGenericSettingsPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IGENERICSETTINGSEXPORTCMDDATA,  kGenericSettingsPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_ISUMMARYUTILS,  				kGenericSettingsPrefix + 6)

// ---- Move from Generic Style Editor plug-in
DECLARE_PMID(kInterfaceIDSpace, IID_IGENSTLEDTCMDDATA,				kGenericSettingsPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IGENSTLSIGNALDATA,				kGenericSettingsPrefix + 8)
// ---- end move.

// <Implementation ID>
// ImplementationIDs
DECLARE_PMID(kImplementationIDSpace, kGenericSettingsImpl,              kGenericSettingsPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kGenericSettingsGroupImpl,         kGenericSettingsPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kGenericSettingsAttributeImpl,     kGenericSettingsPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kHumanTextOutputStrategyImpl,      kGenericSettingsPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kGenericSettingsExportCmdDataImpl, kGenericSettingsPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kGenericSettingsExportCmdImpl,     kGenericSettingsPrefix + 6)
//DECLARE_PMID(kImplementationIDSpace, kGenSetSaveFileDialogImpl,         kGenericSettingsPrefix + 7)	// moved to Generic Style Editor
DECLARE_PMID(kImplementationIDSpace, kSummaryUtilsImpl,         		kGenericSettingsPrefix + 8)

// ---- Move from Generic Style Editor plug-in
DECLARE_PMID(kImplementationIDSpace, kGenStlEdtExportStylesCmdImpl,	kGenericSettingsPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kGenStlEdtImportStylesCmdImpl,	kGenericSettingsPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kGenStlEdtCmdDataImpl,			kGenericSettingsPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kGenStlSignalDataImpl,			kGenericSettingsPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kBeforeImportStyleSignalResponderServiceImpl,	kGenericSettingsPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kAfterImportStyleSignalResponderServiceImpl,	kGenericSettingsPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kBeforeExportStyleSignalResponderServiceImpl,	kGenericSettingsPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kAfterExportStyleSignalResponderServiceImpl,	kGenericSettingsPrefix + 16)
// ---- end move.

// <Widget ID>
// Widget IDs for EPS Export Dialog

// <Service ID>
// Service IDs

DECLARE_PMID(kServiceIDSpace, kBeforeImportStyleSignalResponderService,		kGenericSettingsPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kAfterImportStyleSignalResponderService,		kGenericSettingsPrefix + 2)
DECLARE_PMID(kServiceIDSpace, kBeforeExportStyleSignalResponderService,		kGenericSettingsPrefix + 3)
DECLARE_PMID(kServiceIDSpace, kAfterExportStyleSignalResponderService,		kGenericSettingsPrefix + 4)
#endif
END_IDS()

#endif

