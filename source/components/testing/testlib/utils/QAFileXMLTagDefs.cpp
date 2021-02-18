//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/testlib/utils/QAFileXMLTagDefs.cpp $
//  
//  Owner: Gregor Kaplan
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

#include "QAFileXMLTagDefs.h"

#ifdef __GNUC__
	#define EXTERNAL __attribute__ ((visibility("default")))
#else
	#define EXTERNAL extern
#endif

//QA File tokens
EXTERNAL const char* kQAFolderToken("qa_folder");
EXTERNAL const char* kQABenchmarkToken("benchmark");
EXTERNAL const char* kQABenchmarkTestFilesToken("benchmark_testfiles");
EXTERNAL const char* kQABenchmarkMktgFilesToken("benchmark_mktgfiles");
EXTERNAL const char* kQATestFileFolderToken("testfiles");
EXTERNAL const char* kQALogsToken("logs");
EXTERNAL const char* kQAStatusToken("status");
EXTERNAL const char* kQASnapshotsToken("snapshots");
EXTERNAL const char* kQATrashToken("qa_trash");
EXTERNAL const char* kQAAppFolderToken("app_folder");
EXTERNAL const char* kQAAppInstallationFolderToken("app_install");
EXTERNAL const char* kQANotRelativeToken("not_relative");
EXTERNAL const char* kQAWorkFlowToken("workflow");
EXTERNAL const char* kQAAppLocalCachedDataFolderToken("app_data");			// called app_data for backwards compat with existing token
EXTERNAL const char* kQAAppRoamingDataFolderToken("roaming_app_data");
EXTERNAL const char* kQATestSetsFolderToken("test_sets");
EXTERNAL const char* kQARoundTripFolderToken("round_trip");
EXTERNAL const char* kQAPrefsToken("qa_prefs");
EXTERNAL const char* kQAScriptsToken("qa_scripts");
EXTERNAL const char* kQATrashForceLocalToken("qa_force_trash");
EXTERNAL const char* kQASharedFolderToken("qa_shared_folder");
EXTERNAL const char* kDesktopFolderToken("desktop_folder");
EXTERNAL const char* kDocumentsFolderToken("documents_folder");
EXTERNAL const char* kIoTFolderToken("iot_folder");
EXTERNAL const char* kBaseCampFolderToken("basecamp_folder");
