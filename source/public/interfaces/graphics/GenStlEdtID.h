//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/GenStlEdtID.h $
//  
//  Owner: Matt Phillips
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

#ifndef __GenStlEdtID__
#define __GenStlEdtID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kGenStlEdtPrefix	 								RezLong(0xbc00)		//Refer also to AdobePrefix.h

// <Start IDC>
// PluginID
#define kGenStlEdtPluginName 								"Generic Style Editor"
DECLARE_PMID(kPlugInIDSpace, kGenStlEdtPluginID, kGenStlEdtPrefix + 1)

// <Class ID>
// ClassIDs (i.e. bosses)
//gap
DECLARE_PMID(kClassIDSpace, kGenStlEdtDialogBoss, kGenStlEdtPrefix + 2)
DECLARE_PMID(kClassIDSpace, kGenStlEdtAddStyleToListCmdBoss, kGenStlEdtPrefix + 3)
DECLARE_PMID(kClassIDSpace, kGenStlEdtDeleteStyleFromListCmdBoss, kGenStlEdtPrefix + 4)
DECLARE_PMID(kClassIDSpace, kGenStlEdtEditorBoss, kGenStlEdtPrefix + 5)
// remove kGenStlEdtNameDialogBoss
DECLARE_PMID(kClassIDSpace, kGenStlEdtImportDialogBoss, kGenStlEdtPrefix + 7)
DECLARE_PMID(kClassIDSpace, kGenStlEdtExportDialogBoss, kGenStlEdtPrefix + 8)
DECLARE_PMID(kClassIDSpace, kGenStlEdtErrorStringServiceBoss, kGenStlEdtPrefix + 9)
// gap
DECLARE_PMID(kClassIDSpace, kGenStlEdtStyleListBoxBoss, kGenStlEdtPrefix + 11)
DECLARE_PMID(kClassIDSpace, kGenericSettingsExportDialogBoss, kGenStlEdtPrefix + 12)
// gap

// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IGENSTLEDTEDITOR, kGenStlEdtPrefix + 1)
// remove IID_IGENSTLEDTNAMEDATA, kGenStlEdtPrefix + 2
DECLARE_PMID(kInterfaceIDSpace, IID_IGENSTLEDTOPENSAVEDATA, kGenStlEdtPrefix + 3)
// gap
DECLARE_PMID(kInterfaceIDSpace, IID_IGENSTYLELOCKINFO,  kGenStlEdtPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IEXPORTSTYLECMDDATA, kGenStlEdtPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IGENSTLEDTDYNMENUINFO , kGenStlEdtPrefix + 7)
// gap
DECLARE_PMID(kInterfaceIDSpace, IID_ISUMMARYUIUTILS, kGenStlEdtPrefix + 8)

// <Implementation ID>
// Implementation IIDs (i.e. C++ classes)
//gap
DECLARE_PMID(kImplementationIDSpace, kGenStlEdtDialogControllerImpl, kGenStlEdtPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kGenStlEdtDialogObserverImpl, kGenStlEdtPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kGenStlEdtEditorProviderImpl, kGenStlEdtPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kGenStlEdtEditorImpl, kGenStlEdtPrefix + 5)
// Remove kGenStlEdtNameDialogImpl, kGenStlEdtPrefix + 6
// Remove DECLARE_PMID(kImplementationIDSpace, kGenStlEdtNameDataImpl, kGenStlEdtPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kGSEOpenFileDialogImpl, kGenStlEdtPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kGSESaveFileDialogImpl, kGenStlEdtPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kGenStlEdtOpenSaveDataImpl, kGenStlEdtPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kGenStlEdtErrorStringServiceImpl, kGenStlEdtPrefix + 11)
// gap
// gap
DECLARE_PMID(kImplementationIDSpace, kGenStlEdtStyleListBoxEHImpl, kGenStlEdtPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kGenStlEdtStyleListBoxCtrlImpl, kGenStlEdtPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kGenStyleLockInfoImpl, kGenStlEdtPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kGenStlEditDynamicMenuImpl, kGenStlEdtPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kGenStlEdtMenuActionImpl, kGenStlEdtPrefix + 18)

DECLARE_PMID(kImplementationIDSpace, kGenSetSaveFileDialogImpl, kGenStlEdtPrefix + 19)	// moved from GenericSettings
DECLARE_PMID(kImplementationIDSpace, kSummaryUIUtilsImpl, kGenStlEdtPrefix + 20)	

// <Service ID>
//	Service IDs
DECLARE_PMID(kServiceIDSpace, kGenStlEdtEditorService, kGenStlEdtPrefix + 1)

// <Widget ID>

// Edit Styles Dialog
DECLARE_PMID(kWidgetIDSpace, kGenStlEdtDialogWID, kGenStlEdtPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kGenStlEdtListTitleWID, kGenStlEdtPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kGenStlEdtListWID, kGenStlEdtPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kGenStlEdtEditButtonWID, kGenStlEdtPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kGenStlEdtNewButtonWID, kGenStlEdtPrefix + 5)
//DECLARE_PMID(kWidgetIDSpace, kGenStlEdtRenameButtonWID, kGenStlEdtPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kGenStlEdtDeleteButtonWID, kGenStlEdtPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kGenStlEdtImportButtonWID, kGenStlEdtPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kGenStlEdtExportButtonWID, kGenStlEdtPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kGenStlEdtInfoGroupWID, kGenStlEdtPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kGenStlEdtInfoTextWID, kGenStlEdtPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kGenStlEdtInfoTitleWID, kGenStlEdtPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kGenStlEdtInfoScrollWID, kGenStlEdtPrefix + 13)

// <Error ID>
DECLARE_PMID(kErrorIDSpace, kSaveReadOnlyExportPresetsError, kGenStlEdtPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kGenericExportPresetsError, kGenStlEdtPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kWrongFormatImportPresetsError, kGenStlEdtPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kGenericImportPresetsError, kGenStlEdtPrefix + 4)

// Style Name Dialog
// remove DECLARE_PMID(kWidgetIDSpace, kGenStlEdtNameDialogWID, kGenStlEdtPrefix + 20)
// remove DECLARE_PMID(kWidgetIDSpace, kGenStlEdtNDNameLabelWID, kGenStlEdtPrefix + 21)
// remove DECLARE_PMID(kWidgetIDSpace, kGenStlEdtNDNameEditWID, kGenStlEdtPrefix + 22)

#endif // __GenStlEdtID__


