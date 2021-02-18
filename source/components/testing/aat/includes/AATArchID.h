//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/aat/includes/AATArchID.h $
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

#ifndef __AATArchID__
#define __AATArchID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"
#include "FormatNumber.h"

#define		kInvalidBuildNumber	-1
#define		kInvalidProductVers	-1.0

#define kAATArchPrefix		RezLong(0x3dc00)

// conversion/format IDs
#define kAATDTailMajorFormatNumber 		kDragontailMajorFormatNumber
#define kAATDTailInitialMinorFormatNumber kDragontailInitialMinorFormatNumber

#define kAATFDMajorFormatNumber 			kFiredrakeMajorFormatNumber
#define kAATFDInitialMinorFormatNumber 		kFiredrakeInitialMinorFormatNumber
#define kAATFDNoTimeStampMinorFN 			kAATFDInitialMinorFormatNumber + 1
#define kAATFDErrorPrefMinorFN 			kAATFDNoTimeStampMinorFN + 1
#define kAATFDBaseSessionPrefMinorFN 		kAATFDErrorPrefMinorFN + 1

#define kAATMajorFormatNumber 			kAATFDMajorFormatNumber
#define kAATMinorFormatNumber 			kAATFDBaseSessionPrefMinorFN

//file types IDs for this plugin
#define 	kSessionFileType 				 		kAATArchPrefix + 1
//#define 	kAATModelFileType					kAATArchPrefix + 2
#define 	kFileListFileType						kAATArchPrefix + 3
#define 	kParamListFileType						kAATArchPrefix + 4
#define 	kClassListFileType						kAATArchPrefix + 5
#define 	kValueMapFileType						kAATArchPrefix + 6
#define 	kSourceTreeFileType						kAATArchPrefix + 7
#define 	kKeyedConditionsListFileType			kAATArchPrefix + 8
#define 	kSynonymsListFileType					kAATArchPrefix + 9

//UI codes for this plugin, these are the std set.
#define kInvalidUICode								-1
#define kRealEditBoxCode 				 			kAATArchPrefix + 1
#define kInt32EditBoxCode 				 			kAATArchPrefix + 2
#define kTextEditBoxCode 				 			kAATArchPrefix + 3
#define kMultiLineTextEditBoxCode 				 	kAATArchPrefix + 4
#define kRadioClusterCode 				 			kAATArchPrefix + 5
#define kRadioButtonCode 				 			kAATArchPrefix + 6
#define kCheckBoxCode 				 				kAATArchPrefix + 7
#define kFileComboCode 				 				kAATArchPrefix + 8
#define kComboBoxCode 				 				kAATArchPrefix + 9
#define kDropDownListCode 				 			kAATArchPrefix + 10
#define kTextListBoxCode 				 			kAATArchPrefix + 11
#define kButtonCode 				 				kAATArchPrefix + 12
#define kTreeViewCode 				 				kAATArchPrefix + 13
#define kCheckBoxTreeViewCode 				 		kAATArchPrefix + 14
#define kChooseFileCode 				 			kAATArchPrefix + 15
#define kSaveAsFileCode 				 			kAATArchPrefix + 16
#define kChooseDirCode 				 				kAATArchPrefix + 17
#define kStaticTextCode 				 			kAATArchPrefix + 18
#define kIndeterminateCode 				 			kAATArchPrefix + 19
#define kRectCode 				 					kAATArchPrefix + 20
#define kPointCode 				 					kAATArchPrefix + 21
#define kMeasurementCode							kAATArchPrefix + 22
#define kSaveAsDependentFileCode 				 		kAATArchPrefix + 23
			
			
//---------------------------------------------------------------------
// Handy list of AAT lists and their testlett factory ID range - 
//					DO NOT CHANGE EXISTING VALUES
//---------------------------------------------------------------------
// Definition of individual IDs can be found in the various {Area}AATs.h files 

// DocAATActionList					00000001-000000FF	see DocAATs.h
// StoryAATActionList				00000100-000001FF
// PageItemAATActionList				00000200-000002FF
// SwatchAATActionList				00000300-000003FF
// ValidatorAATActionList			00000400-000004FF
// BookAATActionList				00000500-000005FF
// AppAATActionList					00000600-000006FF
// UndoRedoAATActionList				00000700-000007FF
// TableAATActionList				00000800-000008FF
// HyperlinkAATActionList			00000900-000009FF
// UIActionsAATActionList			00000A00-00000AFF
// PrintAATActionList 				00000B00-00000BFF
// OperationsAATActionList 			00000C00-00000CFF
// CustomAATActionList				00000D00-00000DFF
// AcquisitionAATActionList			00000E00-00000EFF
// WindowAATActionList	 			00000F00-00000FFF
// PageAATActionList				00001000-000010FF
// SpreadAATActionList				00001100-000011FF
// LayerAATActionList				00001200-000012FF
// BookMarkAATActionList				00001300-000013FF
// MasterAATActionList				00001400-000014FF
// FrameGridAATActionList			00001500-000015FF
// TextFrameAATActionList			00001600-000016FF
// TextColumnAATActionList			00001700-000017FF
// FormFieldAATActionList			00001800-000018FF
// SoundAATActionList				00001900-000019FF
// MovieAATActionList				00001A00-00001AFF
// GuideAATActionList				00001B00-00001BFF
// XMLAATActionList					00001C00-00001CFF
// ImportExportAATActionList			00001D00-00001DFF
// StylesAATActionList				00001E00-00001EFF
// ICBridgeAATActionList				00001F00-00001FFF
// NotesAATActionList				00002000-000020FF
// PackagePreflightAATActionList		00002100-000021FF
// TOCAATActionList 				00002200-000022FF
// TestingAATActionList				00002300-000023FF
// LibraryAATActionList				00002400-000024FF
// DialogsAndPanelsAATActionList		00002500-000025FF
// GenericAATActionList				00002600-000026FF

//gap

//	StylesAATActionList				00002A00-00002AFF

#define kAATFileFormatNumber 		2.3
#define kAATModelFileFormatNumber 1.0
#define kFileListFileFormatNumber		1.0
#define kParamListFileFormatNumber		1.0
#define kClassListFileFormatNumber		1.0
#define kValueMapFileFormatNumber		1.0
#define kUIXformFileFormatNumber		1.0



		
typedef  enum {
	kSequencePosition,
	kActionPosition,
	kAcquistionPosition,
	kLoadedFilesPosition,
	kDialogExtentionsPosition
} eTestItemGroupPositions;


// <Start IDC>
// PluginID
#define kAATArchPluginName 	"AAT Architecture"
DECLARE_PMID(kPlugInIDSpace, kAATArchPluginID, kAATArchPrefix + 1)


//---------------------------------------------------------------
// Resource IDs
//---------------------------------------------------------------



// <Class ID>
//---------------------------------------------------------------
// Boss IDs
//---------------------------------------------------------------
DECLARE_PMID(kClassIDSpace, kAATIdleTaskBoss,				kAATArchPrefix + 1)
DECLARE_PMID(kClassIDSpace, kTestSessionListBoss,		 			kAATArchPrefix + 2)
DECLARE_PMID(kClassIDSpace, kQAXMLDataEngineBoss,					kAATArchPrefix + 3)
DECLARE_PMID(kClassIDSpace, kQAXMLDataEngineCHandlerBoss,			kAATArchPrefix + 4)
DECLARE_PMID(kClassIDSpace, kReadWriteTestBoss,						kAATArchPrefix + 5)
DECLARE_PMID(kClassIDSpace, kCTestSessionBoss,						kAATArchPrefix + 6)
DECLARE_PMID(kClassIDSpace, kCSequenceListBoss,						kAATArchPrefix + 7)
DECLARE_PMID(kClassIDSpace, kCObjectFinderBoss,						kAATArchPrefix + 8)
DECLARE_PMID(kClassIDSpace, kCObjectLoopListBoss,	 				kAATArchPrefix + 9)
DECLARE_PMID(kClassIDSpace, kCFileLoopListBoss,	 					kAATArchPrefix + 10)
DECLARE_PMID(kClassIDSpace, kCIterativeLoopListBoss,	 			kAATArchPrefix + 11)
DECLARE_PMID(kClassIDSpace,	kCPermutationLoopListBoss,	 			kAATArchPrefix + 12)
DECLARE_PMID(kClassIDSpace,	kCStoryContentFinderBoss,	 			kAATArchPrefix + 13)
DECLARE_PMID(kClassIDSpace,	kCTableContentFinderBoss,	 			kAATArchPrefix + 14)
DECLARE_PMID(kClassIDSpace,	kCPrintPresetFinderBoss,	 			kAATArchPrefix + 15)
DECLARE_PMID(kClassIDSpace,	kFileListReaderBoss,		 			kAATArchPrefix + 16)
DECLARE_PMID(kClassIDSpace,	kAATReader_v1p0Boss,	 			kAATArchPrefix + 17)
DECLARE_PMID(kClassIDSpace,	kCLogicSequenceListBoss,	 			kAATArchPrefix + 18)
DECLARE_PMID(kClassIDSpace,	kCAATActionIDTransEntryBoss,	 		kAATArchPrefix + 19)
DECLARE_PMID(kClassIDSpace, kAcquisitionAATActionListBoss,		 	kAATArchPrefix + 20)
DECLARE_PMID(kClassIDSpace, kAATScriptResponderBoss,	 	kAATArchPrefix + 21)
DECLARE_PMID(kClassIDSpace, kQARegistriesBoss,	 					kAATArchPrefix + 22)
DECLARE_PMID(kClassIDSpace,	kCLogicClusterSequenceListBoss,	 		kAATArchPrefix + 23)
DECLARE_PMID(kClassIDSpace,	kCDoWhileSequenceListBoss,	 			kAATArchPrefix + 24)
DECLARE_PMID(kClassIDSpace, kDocAATActionListBoss,					kAATArchPrefix + 25)
DECLARE_PMID(kClassIDSpace, kStoryAATActionListBoss,				kAATArchPrefix + 26)
DECLARE_PMID(kClassIDSpace, kPageItemAATActionListBoss,				kAATArchPrefix + 27)
DECLARE_PMID(kClassIDSpace, kSwatchAATActionListBoss,				kAATArchPrefix + 28)
DECLARE_PMID(kClassIDSpace, kValidatorAATActionListBoss,			kAATArchPrefix + 29)
DECLARE_PMID(kClassIDSpace, kBookAATActionListBoss,					kAATArchPrefix + 30)
DECLARE_PMID(kClassIDSpace, kAppAATActionListBoss,					kAATArchPrefix + 31)
DECLARE_PMID(kClassIDSpace, kUndoRedoAATActionListBoss,				kAATArchPrefix + 32)
DECLARE_PMID(kClassIDSpace, kTableAATActionListBoss,				kAATArchPrefix + 33)
DECLARE_PMID(kClassIDSpace, kHyperlinkAATActionListBoss,			kAATArchPrefix + 34)
DECLARE_PMID(kClassIDSpace, kSelectFileDialogWatcherBoss,			kAATArchPrefix + 35)
DECLARE_PMID(kClassIDSpace, kPrintAATActionListBoss,				kAATArchPrefix + 36)
DECLARE_PMID(kClassIDSpace, kOperationsAATActionListBoss,			kAATArchPrefix + 37)
DECLARE_PMID(kClassIDSpace, kCustomAATActionListBoss,				kAATArchPrefix + 38)
DECLARE_PMID(kClassIDSpace, kCParameterLoopListBoss,				kAATArchPrefix + 39)
DECLARE_PMID(kClassIDSpace, kGenericAATActionListBoss,				kAATArchPrefix + 40)
//gap
DECLARE_PMID(kClassIDSpace, kPageAATActionListBoss,					kAATArchPrefix + 42)
DECLARE_PMID(kClassIDSpace, kSpreadAATActionListBoss,				kAATArchPrefix + 43)
DECLARE_PMID(kClassIDSpace, kLayerAATActionListBoss,				kAATArchPrefix + 44)
DECLARE_PMID(kClassIDSpace, kGuideAATActionListBoss,				kAATArchPrefix + 45)
DECLARE_PMID(kClassIDSpace, kBookmarkAATActionListBoss,				kAATArchPrefix + 46)
DECLARE_PMID(kClassIDSpace, kMasterAATActionListBoss,				kAATArchPrefix + 47)
DECLARE_PMID(kClassIDSpace, kFrameGridAATActionListBoss,			kAATArchPrefix + 48)
DECLARE_PMID(kClassIDSpace, kTextFrameAATActionListBoss,			kAATArchPrefix + 49)
DECLARE_PMID(kClassIDSpace, kTextColumnAATActionListBoss,			kAATArchPrefix + 50)
DECLARE_PMID(kClassIDSpace, kFormFieldAATActionListBoss,			kAATArchPrefix + 51)
DECLARE_PMID(kClassIDSpace, kSoundAATActionListBoss,				kAATArchPrefix + 52)
DECLARE_PMID(kClassIDSpace, kMovieAATActionListBoss,				kAATArchPrefix + 53)
DECLARE_PMID(kClassIDSpace, kXMLAATActionListBoss,					kAATArchPrefix + 54)
DECLARE_PMID(kClassIDSpace, kTypeKitVulcanAATBoss,					kAATArchPrefix + 55)

//gap
DECLARE_PMID(kClassIDSpace,	kAATArchConversionProviderBoss, kAATArchPrefix + 58)
DECLARE_PMID(kClassIDSpace,	kStylesAATActionListBoss, 				kAATArchPrefix + 59)
DECLARE_PMID(kClassIDSpace,	kICBridgeAATActionListBoss, 			kAATArchPrefix + 60)
DECLARE_PMID(kClassIDSpace,	kNotesAATActionListBoss, 				kAATArchPrefix + 61)
DECLARE_PMID(kClassIDSpace,	kCAlertWatcherListBoss,	 				kAATArchPrefix + 62)
DECLARE_PMID(kClassIDSpace,	kAATAlertHandlerBoss,	 			kAATArchPrefix + 63)
DECLARE_PMID(kClassIDSpace, kPackagePreflightAATActionListBoss,		kAATArchPrefix + 64)
DECLARE_PMID(kClassIDSpace,	kTOCAATActionListBoss, 					kAATArchPrefix + 65)
//gap
DECLARE_PMID(kClassIDSpace,	kParamListReaderBoss, 					kAATArchPrefix + 67)
DECLARE_PMID(kClassIDSpace,	kClassListReaderBoss, 					kAATArchPrefix + 68)
DECLARE_PMID(kClassIDSpace,	kValueMapReaderBoss, 					kAATArchPrefix + 69)
DECLARE_PMID(kClassIDSpace,	kAATStringListBoss, 				kAATArchPrefix + 70)
DECLARE_PMID(kClassIDSpace,	kAATClassStringListBoss, 			kAATArchPrefix + 71)
DECLARE_PMID(kClassIDSpace,	kAATStringPairListBoss, 			kAATArchPrefix + 72)
DECLARE_PMID(kClassIDSpace,	kUICodeRegistryBoss,		 			kAATArchPrefix + 73)
DECLARE_PMID(kClassIDSpace,	kCReadWriteContainerBoss,		 		kAATArchPrefix + 74)
DECLARE_PMID(kClassIDSpace, kLibraryAATActionListBoss,				kAATArchPrefix + 75)
DECLARE_PMID(kClassIDSpace, kAATReader_v2p0Boss,				kAATArchPrefix + 76)
DECLARE_PMID(kClassIDSpace, kAATActionIDTranslationListBoss,		kAATArchPrefix + 77)
DECLARE_PMID(kClassIDSpace, kAATKeyedConditionsListBoss,		kAATArchPrefix + 78)
DECLARE_PMID(kClassIDSpace, kKeyedConditionsListReaderBoss,			kAATArchPrefix + 79)
DECLARE_PMID(kClassIDSpace, kAATSynonymsListBoss,				kAATArchPrefix + 80)
DECLARE_PMID(kClassIDSpace, kSynonymsListReaderBoss,				kAATArchPrefix + 81)
DECLARE_PMID(kClassIDSpace, kTableCellStylesAATActionListBoss,		kAATArchPrefix + 82)
DECLARE_PMID(kClassIDSpace, kSyncAATActionListBoss,		kAATArchPrefix + 83)
DECLARE_PMID(kClassIDSpace, kTypeKitAATActionListBoss,		kAATArchPrefix + 84)
DECLARE_PMID(kClassIDSpace, kPublishAATActionListBoss, kAATArchPrefix + 85)

// <Interface ID>
//---------------------------------------------------------------
// Interface IDs
//---------------------------------------------------------------
DECLARE_PMID(kInterfaceIDSpace, IID_ITESTSESSIONLIST, 				kAATArchPrefix + 1)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IAATFACTORY, 				kAATArchPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IREADWRITETEST, 				kAATArchPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_ITESTSESSION, 					kAATArchPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ITESTSEQUENCELIST, 				kAATArchPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IAATALERTHANDLERDATA,		kAATArchPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IAATUTILS, 				kAATArchPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IAATSESSIONPROPERTIES, 	kAATArchPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IAATACTIONLIST, 				kAATArchPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IOBJECTFINDER, 					kAATArchPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IAATFILEFORMAT, 			kAATArchPrefix + 13)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IAATREADERLIST, 			kAATArchPrefix + 15)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IAATACTIONIDTRANSENTRY,          kAATArchPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_ICLASSSTRINGLIST, 				kAATArchPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTRINGPAIRLIST, 				kAATArchPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_IUICODETRANSLATIONLIST, 		kAATArchPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_UICODEREGISTRY, 				kAATArchPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IQAPROGRESSBARUTILS, 			kAATArchPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_IAATACTIONLISTADDON, 			kAATArchPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_IAATIDTRANSLATIONREG, 	kAATArchPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_IAATACTIONIDTRANSLIST,	 		kAATArchPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_IQACLASSLISTREGISTRY,		 	kAATArchPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_IQACOMMONREGISTRYLIST,		 	kAATArchPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_IPARAMLISTREGISTRY,		 		kAATArchPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_IBREAKSTATEDATA, 				kAATArchPrefix + 31)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IUICOLORLISTREGISTRY,		 	kAATArchPrefix + 33)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IAATPREFS,		 		kAATArchPrefix + 35)
DECLARE_PMID(kInterfaceIDSpace, IID_IPLATFORMPATHMAPREGISTRY,		kAATArchPrefix + 37)
DECLARE_PMID(kInterfaceIDSpace, IID_IAATFILEUTILS,			kAATArchPrefix + 38)
DECLARE_PMID(kInterfaceIDSpace, IID_IREADWRITECONTAINER,			kAATArchPrefix + 39)
DECLARE_PMID(kInterfaceIDSpace, IID_IKEYEDCONDITIONSLIST,			kAATArchPrefix + 40)
DECLARE_PMID(kInterfaceIDSpace, IID_ISYNONYMSLIST,					kAATArchPrefix + 41)


// <Implementation ID>
//---------------------------------------------------------------
// Implementation IDs
//---------------------------------------------------------------
DECLARE_PMID(kImplementationIDSpace, kCObjectFinderImpl, 					kAATArchPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kTestSessionListImpl, 					kAATArchPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kQAXMLDataEngineImpl,					kAATArchPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kQAXMLDataEngineCHandlerImpl,  			kAATArchPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kGenericAATActionListImpl,  			kAATArchPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kAATFactoryImpl, 						kAATArchPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kCReadWriteTestImpl, 					kAATArchPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kCTestSessionImpl, 					kAATArchPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kCSequenceListImpl, 					kAATArchPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kAATIdleTaskImpl,						kAATArchPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kAATReaderServiceImpl,					kAATArchPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kAATArchUtilsImpl,					kAATArchPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kScannerListImpl, 					kAATArchPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kAATSessionPropertiesImpl,				kAATArchPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kCObjectLoopListImpl, 					kAATArchPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kCFileLoopListImpl, 					kAATArchPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kCIterativeLoopListImpl, 				kAATArchPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kCPermutationLoopListImpl, 				kAATArchPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kCStoryContentFinderImpl, 				kAATArchPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kCTableContentFinderImpl, 				kAATArchPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kCAATFileFormatImpl,					kAATArchPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kCAATActionIDTransEntryImpl, 			kAATArchPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kCPrintPresetFinderImpl, 				kAATArchPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kAATFactoryServiceProviderImpl,			kAATArchPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kDocAATActionListImpl,					kAATArchPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kStoryAATActionListImpl,				kAATArchPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kPageItemAATActionListImpl,				kAATArchPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kSwatchAATActionListImpl,				kAATArchPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kValidatorAATActionListImpl,			kAATArchPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kBookAATActionListImpl,				kAATArchPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kAppAATActionListImpl,					kAATArchPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kUndoRedoAATActionListImpl,				kAATArchPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kTableAATActionListImpl,				kAATArchPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kHyperlinkAATActionListImpl,			kAATArchPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kAcquisitionAATActionListImpl,			kAATArchPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kPrintAATActionListImpl,				kAATArchPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kRunMenuEventWatcherImpl,				kAATArchPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kOperationsAATActionListImpl,			kAATArchPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kAATReaderListImpl,					kAATArchPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kAATClassStringListImpl,				kAATArchPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kAATStringPairListImpl,				kAATArchPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kCustomAATActionListImpl,				kAATArchPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kCBreakStateDataImpl,					kAATArchPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kSelectFileDialogWatcherImpl,			kAATArchPrefix + 44)
//gap
DECLARE_PMID(kImplementationIDSpace, kCParameterLoopListImpl,				kAATArchPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kCLogicSequenceListImpl,				kAATArchPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kCLogicClusterSequenceListImpl,			kAATArchPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kAATStringListImpl,					kAATArchPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kAATScriptResponderImpl,				kAATArchPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kQAProgressDlgControllerImpl,			kAATArchPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kQACancelEventWatcherImpl,				kAATArchPrefix + 52)
//gap
DECLARE_PMID(kImplementationIDSpace, kAATActionAddOnServiceProviderImpl,		kAATArchPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kParamListReaderImpl,					kAATArchPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kFileListReaderImpl,					kAATArchPrefix + 56)
//gap
DECLARE_PMID(kImplementationIDSpace, kPageAATActionListImpl,			kAATArchPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kSpreadAATActionListImpl,			kAATArchPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kLayerAATActionListImpl,			kAATArchPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kGuideAATActionListImpl,			kAATArchPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kBookmarkAATActionListImpl,		kAATArchPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kMasterAATActionListImpl,			kAATArchPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kFrameGridAATActionListImpl,		kAATArchPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kTextFrameAATActionListImpl,		kAATArchPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kTextColumnAATActionListImpl,		kAATArchPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kFormFieldAATActionListImpl,		kAATArchPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kSoundAATActionListImpl,			kAATArchPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kMovieAATActionListImpl,			kAATArchPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kClassListReaderImpl,  			kAATArchPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kQAClassListRegistryImpl,  		kAATArchPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kQACommonRegistryListImpl,  		kAATArchPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kParamListRegistryImpl,  			kAATArchPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kAATReader_v1p0Impl,			kAATArchPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kCDoWhileSequenceListImpl,			kAATArchPrefix + 76)
//gap
DECLARE_PMID(kImplementationIDSpace, kPanelActionListRegistryImpl,		kAATArchPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kUIColorListRegistryImpl,  		kAATArchPrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kXMLAATActionListImpl,				kAATArchPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kImportExportAATActionListImpl,	kAATArchPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kImportExportEventWatcherImpl,		kAATArchPrefix + 82)
//gap
DECLARE_PMID(kImplementationIDSpace, kAATPrefsImpl,				kAATArchPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kValueMapReaderImpl,				kAATArchPrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kPlatformPathMapRegistryImpl,		kAATArchPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kStylesAATActionListImpl,			kAATArchPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kAATFileUtilsImpl,			kAATArchPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kICBridgeAATActionListImpl,		kAATArchPrefix + 89)
DECLARE_PMID(kImplementationIDSpace, kNotesAATActionListImpl,			kAATArchPrefix + 90)
//gap
DECLARE_PMID(kImplementationIDSpace, kAATAlertHandlerImpl, 		kAATArchPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kAATAlertHandlerDataImpl, 	kAATArchPrefix + 93)
DECLARE_PMID(kImplementationIDSpace, kPackagePreflightAATActionListImpl,kAATArchPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kTOCAATActionListImpl,				kAATArchPrefix + 95)
//gap
DECLARE_PMID(kImplementationIDSpace, kAATUICodeServiceImpl,		kAATArchPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kUICodeTranslationListImpl, 		kAATArchPrefix + 98)
DECLARE_PMID(kImplementationIDSpace, kUICodeRegistryImpl, 				kAATArchPrefix + 99)
DECLARE_PMID(kImplementationIDSpace, kCReadWriteContainerImpl, 			kAATArchPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kLibraryAATActionListImpl,			kAATArchPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kAATReader_v2p0Impl,			kAATArchPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kAATActionIDTranslationServiceImpl,	kAATArchPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kAATActionIDTranslationRegistryImpl,	kAATArchPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kAATActionIDTranslationListImpl,		kAATArchPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kAATKeyedConditionsListImpl,	kAATArchPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kKeyedConditionsListReaderImpl,		kAATArchPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kAATSynonymsListImpl,			kAATArchPrefix + 108)
DECLARE_PMID(kImplementationIDSpace, kSynonymsListReaderImpl,			kAATArchPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kTableCellStylesAATActionListImpl,	kAATArchPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kSyncAATActionListImpl,	kAATArchPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kTypeKitAATActionListImpl,	kAATArchPrefix + 112)
DECLARE_PMID(kImplementationIDSpace, kPublishAATActionListImpl, kAATArchPrefix + 113)

// <Error ID>
//******ERROR IDs
DECLARE_PMID(kErrorIDSpace, kLogicFailureError, 					kAATArchPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kDisabledError, 						kAATArchPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kEnabledError, 							kAATArchPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kInvalidAATFileError, 					kAATArchPrefix + 4)
DECLARE_PMID(kErrorIDSpace, kCannotCreateFolderError, 				kAATArchPrefix + 5)



//---------------------------------------------------------------
//	Service IDS
//---------------------------------------------------------------
DECLARE_PMID(kServiceIDSpace, kAATFactoryService,				kAATArchPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kAATAddOnService,				kAATArchPrefix + 2)
DECLARE_PMID(kServiceIDSpace, kAATReaderService,				kAATArchPrefix + 3)
DECLARE_PMID(kServiceIDSpace, kAATUICodeService,				kAATArchPrefix + 4)
DECLARE_PMID(kServiceIDSpace, kAATActionIDTranslationService,		kAATArchPrefix + 5)
#endif // __AATArchID__
