//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/CommandID.h $
//  
//  Owner: Robin_Briggs
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
//  Contains IDs used by the group item plug-in
//  
//========================================================================================

#ifndef __COMMANDID__
#define __COMMANDID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kCommandPrefix		 RezLong(0x1000)

// <Start IDC>
// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kCommandProcessorBoss, kCommandPrefix + 1)
DECLARE_PMID(kClassIDSpace, kUndoRedoMenuBoss, kCommandPrefix + 2 )
// unused DECLARE_PMID(kClassIDSpace, kCompoundCmdBoss, kCommandPrefix + 3)
// unused DECLARE_PMID(kClassIDSpace, kPipelineCmdBoss, kCommandPrefix + 4)
	// Messages sent by CommandMgr
	// -- these are ClassIDs but have no classes!
	// -- they are only used for sending messages
DECLARE_PMID(kMessageIDSpace, kBeforeDoMessageBoss, kCommandPrefix + 5)
DECLARE_PMID(kMessageIDSpace, kAfterDoMessageBoss, kCommandPrefix + 6)
//DECLARE_PMID(kMessageIDSpace, kUnusedBoss, kCommandPrefix + 7)
//DECLARE_PMID(kMessageIDSpace, kUnusedBoss, kCommandPrefix + 8)
//DECLARE_PMID(kMessageIDSpace, kUnusedBoss, kCommandPrefix + 9)
//DECLARE_PMID(kMessageIDSpace, kUnusedBoss, kCommandPrefix + 10)
//DECLARE_PMID(kMessageIDSpace, kUnusedBoss, kCommandPrefix + 11)
DECLARE_PMID(kMessageIDSpace, kAfterJoinMessageBoss, kCommandPrefix + 12)
DECLARE_PMID(kMessageIDSpace, kBeforeDoImmediateMessageBoss, kCommandPrefix + 13)
DECLARE_PMID(kMessageIDSpace, kAfterDoImmediateMessageBoss, kCommandPrefix + 14)
// unused DECLARE_PMID(kClassIDSpace, kUnusedBoss, kCommandPrefix + 15)
// unused DECLARE_PMID(kClassIDSpace, kUnusedBoss, kCommandPrefix + 16)
// unused DECLARE_PMID(kClassIDSpace, kUnusedBoss, kCommandPrefix + 17)
// unused DECLARE_PMID(kClassIDSpace, kAbortCmdSequenceBoss, kCommandPrefix + 18)
// unused DECLARE_PMID(kClassIDSpace, kStartUndoCmdSequenceBoss, kCommandPrefix + 19)
// unused DECLARE_PMID(kClassIDSpace, kEndUndoCmdSequenceBoss, kCommandPrefix + 20)
// unused DECLARE_PMID(kClassIDSpace, kStartRedoCmdSequenceBoss, kCommandPrefix + 21)
// unused DECLARE_PMID(kClassIDSpace, kEndRedoCmdSequenceBoss, kCommandPrefix + 22)
DECLARE_PMID(kClassIDSpace, kCompoundSequenceCmdBoss, kCommandPrefix + 23)
DECLARE_PMID(kClassIDSpace, kPipelineSequenceCmdBoss, kCommandPrefix + 24)
DECLARE_PMID(kClassIDSpace, kNewUIDCmdBoss, kCommandPrefix + 25)

// Messages broadcasted on the cmd history subject
//DECLARE_PMID(kMessageIDSpace, kUnusedBoss, kCommandPrefix + 26)
DECLARE_PMID(kMessageIDSpace, kUndoCmdHistoryItemsMessage, kCommandPrefix + 27)
DECLARE_PMID(kMessageIDSpace, kRedoCmdHistoryItemsMessage, kCommandPrefix + 28)
DECLARE_PMID(kMessageIDSpace, kRemoveCmdHistoryItemsMessage, kCommandPrefix + 29)
DECLARE_PMID(kMessageIDSpace, kDisableCmdHistoryMessage, kCommandPrefix + 30)
DECLARE_PMID(kMessageIDSpace, kEnableCmdHistoryMessage, kCommandPrefix + 31)
DECLARE_PMID(kMessageIDSpace, kAddUndoCmdHistoryItemsMessage, kCommandPrefix + 32)
DECLARE_PMID(kMessageIDSpace, kAddUndoBackThreadHistoryItemsMessage, kCommandPrefix + 33)
DECLARE_PMID(kMessageIDSpace, kAddRedoBackThreadHistoryItemsMessage, kCommandPrefix + 34)

// More classes
//DECLARE_PMID(kClassIDSpace, kUnusedBoss, kCommandPrefix + 32)
DECLARE_PMID(kClassIDSpace, kDeleteUIDCmdBoss, kCommandPrefix + 33)
DECLARE_PMID(kClassIDSpace, kPipelineSequenceCmd2Boss, kCommandPrefix + 34)
DECLARE_PMID(kClassIDSpace, kSubCmdBoss, kCommandPrefix + 35)
DECLARE_PMID(kClassIDSpace, kBasicCommandProcessorBoss, kCommandPrefix + 36)
// <Interface ID>

// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMMAND, kCommandPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IINTDATA, kCommandPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IBOOLDATA, kCommandPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IUIDDATA, kCommandPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTCMDDATA, kCommandPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IUIDLISTDATA, kCommandPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTRINGDATA, kCommandPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IREALNUMBERDATA, kCommandPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOORDDATA, kCommandPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMMANDINTERCEPTOR, kCommandPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_ICPOINTDATA, kCommandPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IDYNAMICUPDATE, kCommandPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IPOINTLISTDATA, kCommandPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_DISPLAYCMDPROGRESSBAR, kCommandPrefix + 14 )
DECLARE_PMID(kInterfaceIDSpace, IID_ICMDCOLLECTION, kCommandPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IGLOBALTIMEDATA, kCommandPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMMANDPROCESSOR, kCommandPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMMANDMGR, kCommandPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOOLCMDDATA, kCommandPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTSCRAPCMDDATA, kCommandPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_IRANGEDATA, kCommandPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_IPMPOINTDATA, kCommandPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMMANDDATA, kCommandPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IPMUNKNOWNDATA, kCommandPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMMANDCHECKER, kCommandPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_ICMDHISTORY, kCommandPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMMANDPROCESSORPRIVATE, kCommandPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_IPOINTERDATA, kCommandPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_ICMDQUEUE, kCommandPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_IRANGEDATA2, kCommandPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_IUIDPAIRLISTDATA, kCommandPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_ISAVEALLDATA, kCommandPrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_IBOOLLISTDATA, kCommandPrefix + 33)
DECLARE_PMID(kInterfaceIDSpace, IID_ICLASSIDLISTDATA, kCommandPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_IPMRECTDATA, kCommandPrefix + 35)
DECLARE_PMID(kInterfaceIDSpace, IID_IDICTIONARYDATA, kCommandPrefix + 36)
DECLARE_PMID(kInterfaceIDSpace, IID_IINTCOUNTER, kCommandPrefix + 37)
DECLARE_PMID(kInterfaceIDSpace, IID_IPMREALLISTDATA, kCommandPrefix + 38)

//DECLARE_PMID(kInterfaceIDSpace, IID_IUNUSED, kCommandPrefix + 39)

//DECLARE_PMID(kInterfaceIDSpace, IID_IUNUSED	, kCommandPrefix + 40)	// same interface as IID_IDBOBSERVER
#ifdef DEBUG
	DECLARE_PMID(kInterfaceIDSpace, IID_ICMDDEBUGGER, kCommandPrefix + 41)
#endif
DECLARE_PMID(kInterfaceIDSpace, IID_IPERSISTUIDLISTDATA, kCommandPrefix + 42)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTRINGLISTDATA, kCommandPrefix + 43)
DECLARE_PMID(kInterfaceIDSpace, IID_ISUBCMDDATA, kCommandPrefix + 44)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTINDEXIDRANGE, kCommandPrefix + 45)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTINDEXID, kCommandPrefix + 46)
DECLARE_PMID(kInterfaceIDSpace, IID_IDATA_K2VECTOR_INT32, kCommandPrefix + 47)
DECLARE_PMID(kInterfaceIDSpace, IID_IDATA_K2VECTOR_UINT32, kCommandPrefix + 48)
DECLARE_PMID(kInterfaceIDSpace, IID_IDATA_UINT32, kCommandPrefix + 49)
DECLARE_PMID(kInterfaceIDSpace, IID_IINVALHANDLER, kCommandPrefix + 50)

DECLARE_PMID(kInterfaceIDSpace, IID_IUIDREFLISTDATA, kCommandPrefix + 51)
DECLARE_PMID(kInterfaceIDSpace, IID_IBOOLDATA2, kCommandPrefix + 52)
DECLARE_PMID(kInterfaceIDSpace, IID_IPREVIEWABLECHANGES, kCommandPrefix + 53)
DECLARE_PMID(kInterfaceIDSpace, IID_IWSTRINGDATA, kCommandPrefix + 55)
DECLARE_PMID(kInterfaceIDSpace, IID_IIDFILEDATA, kCommandPrefix + 56)
DECLARE_PMID(kInterfaceIDSpace, IID_ISNAPSHOTIDDATA, kCommandPrefix + 57)
DECLARE_PMID(kInterfaceIDSpace, IID_ISUPPRESSCHECKSTOPJOINING, kCommandPrefix + 58)
DECLARE_PMID(kInterfaceIDSpace, IID_IINT64DATA, kCommandPrefix + 59)

// <Implementation ID>
// Implementation IIDs
DECLARE_PMID(kImplementationIDSpace, kCommandMgrImpl, kCommandPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kCommandProcessorImpl, kCommandPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kWCmdQueueImpl, kCommandPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kBoolDataImpl, kCommandPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kCoordDataImpl, kCommandPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kCPointDataImpl, kCommandPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kIntDataImpl, kCommandPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kItemListDataImpl, kCommandPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kLayoutCmdDataImpl, kCommandPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kRealNumberDataImpl, kCommandPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kStringDataImpl, kCommandPrefix + 11)
//DECLARE_PMID(kImplementationIDSpace, kObsoleteSysHandleDataImpl, kCommandPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kUIDDataImpl, kCommandPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kRangeDataImpl, kCommandPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kDynamicUpdateImpl, kCommandPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kCmdCollectionImpl, kCommandPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kPipelineCmdImpl, kCommandPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kSysFileDataImpl, kCommandPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kPMUnknownData_SoftReference_Impl, kCommandPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kCommandMgrArbitratorObserverImpl, kCommandPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kCompoundCmdImpl, kCommandPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kPMPointDataImpl, kCommandPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kCommandDataImpl, kCommandPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kPMUnknownDataImpl, kCommandPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kUIDListDataImpl, kCommandPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kCmdHistoryImpl, kCommandPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kGlobalTimeDataImpl, kCommandPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kGlobalTimeDataPersistentImpl, kCommandPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kCmdQueueImpl, kCommandPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kSysFileListDataImpl, kCommandPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kUIDPairListDataImpl, kCommandPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kCompoundSequenceCmdImpl, kCommandPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kBoolListDataImpl, kCommandPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kClassIDListDataImpl, kCommandPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kPMRectDataImpl, kCommandPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kPipelineSequenceCmdImpl, kCommandPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kNewUIDCmdImpl, kCommandPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kCommandProcessorPrivateImpl, kCommandPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kCmdHistoryStubImpl, kCommandPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kDropDesktopFileCmdDataImpl, kCommandPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kPointerDataImpl, kCommandPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kDictionaryDataImpl, kCommandPrefix + 42)
#ifdef DEBUG
DECLARE_PMID(kImplementationIDSpace, kCmdDebuggerImpl, kCommandPrefix + 43)
#endif
DECLARE_PMID(kImplementationIDSpace, kDeleteUIDCmdImpl, kCommandPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kPersistUIDListDataImpl, kCommandPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kPipelineSequenceCmd2Impl, kCommandPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kStringListDataImpl, kCommandPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kSubCmdImpl, kCommandPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kSubCmdDataImpl, kCommandPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kTextIndexIDRangeImpl, kCommandPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kTextIndexIDImpl, kCommandPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kDataK2VectorInt32Impl, kCommandPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kDataK2VectorUInt32Impl, kCommandPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kDataUInt32Impl, kCommandPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kUIDRefListDataImpl, kCommandPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kMinusOneInitIntDataImpl, kCommandPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kPlusOneInitIntDataImpl, kCommandPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kPersistClassIDListDataImpl, kCommandPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kZeroInitRealNumberDataImpl, kCommandPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kPreviewableChangesIFaceImpl, kCommandPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kWStringDataImpl, kCommandPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kIDFileDataImpl, kCommandPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kSnapshotIDDataImpl, kCommandPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kIntCounterImpl, kCommandPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kMinusOneInitIntCounterImpl, kCommandPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kPlusOneInitIntCounterImpl, kCommandPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kPMRealListDataImpl, kCommandPrefix + 67)

#endif // __CommandID__
