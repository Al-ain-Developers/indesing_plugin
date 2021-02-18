//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/DocumentID.h $
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
//  Contains IDs used by document sub-system.
//  
//========================================================================================

#ifndef __DocumentID__
#define __DocumentID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kDocumentPrefix	 RezLong(0xE00)

// <Start IDC>
// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kDocBoss, kDocumentPrefix + 1 )
DECLARE_PMID(kClassIDSpace, kDocumentListBoss, kDocumentPrefix + 2)
#ifdef ID_DEPRECATED
DECLARE_PMID(kClassIDSpace, kDocumentComponentBoss, kDocumentPrefix + 3) 	// Moving to DocumentUIID.h
DECLARE_PMID(kClassIDSpace, kNewDocCmdBoss, kDocumentPrefix + 4)	// Moving to DocumentActionsID.h
DECLARE_PMID(kClassIDSpace, kOpenDocCmdBoss, kDocumentPrefix + 5) // Moving to DocumentActionsID.h
DECLARE_PMID(kClassIDSpace, kCloseDocCmdBoss, kDocumentPrefix + 6) // Moving to DocumentActionsID.h
DECLARE_PMID(kClassIDSpace, kSaveDocCmdBoss, kDocumentPrefix + 7) // Moving to DocumentActionsID.h
DECLARE_PMID(kClassIDSpace, kSaveAsDocCmdBoss, kDocumentPrefix + 8) // Moving to DocumentActionsID.h
#endif
DECLARE_PMID(kClassIDSpace, kSetDocNameCmdBoss, kDocumentPrefix + 9)
DECLARE_PMID(kClassIDSpace, kSetFrontDocCmdBoss, kDocumentPrefix + 10)
DECLARE_PMID(kClassIDSpace, kSaveAsAsciiCmdBoss, kDocumentPrefix + 11)
DECLARE_PMID(kClassIDSpace, kSetDocProtectionPrefsCmdBoss, kDocumentPrefix + 12)
DECLARE_PMID(kClassIDSpace, kSetDocMiniSavePrefsCmdBoss, kDocumentPrefix + 13)
DECLARE_PMID(kClassIDSpace, kStartRecoveryCmdBoss, kDocumentPrefix + 14)
#ifdef ID_DEPRECATED
DECLARE_PMID(kClassIDSpace, kRecoverDocumentCmdBoss, kDocumentPrefix + 15) // Moving to DocumentActionsID.h
#endif
DECLARE_PMID(kClassIDSpace, kPlaceFileDialogBoss, kDocumentPrefix + 16)
DECLARE_PMID(kClassIDSpace, kOpenFileDialogBoss, kDocumentPrefix + 17)
DECLARE_PMID(kClassIDSpace, kSaveFileDialogBoss, kDocumentPrefix + 18)
DECLARE_PMID(kClassIDSpace, kDocTestMenuBoss, kDocumentPrefix + 19)	/* debug only */
#ifdef ID_DEPRECATED
DECLARE_PMID(kClassIDSpace, kSaveACopyCmdBoss, kDocumentPrefix + 20) // Moving to DocumentActionsID.h
DECLARE_PMID(kClassIDSpace, kRecentDocsComponentBoss, kDocumentPrefix + 21) // Moving to DocumentUIID.h
#endif
DECLARE_PMID(kClassIDSpace, kDocErrorStringServiceBoss, kDocumentPrefix + 22)
// DECLARE_PMID(kClassIDSpace, kNewDocSignalMgrBoss, kDocumentPrefix + 23) Obsolete
// DECLARE_PMID(kClassIDSpace, kOpenDocSignalMgrBoss, kDocumentPrefix + 24) Obsolete
#ifdef ID_DEPRECATED
DECLARE_PMID(kClassIDSpace, kDocFileHandlerBoss, kDocumentPrefix + 25) // Moving to DocumentUIID.h
#endif
// DECLARE_PMID(kClassIDSpace, kNewScrapDocSignalMgrBoss, kDocumentPrefix + 26) Obsolete
DECLARE_PMID(kClassIDSpace, kOpenDocDialogBoss, kDocumentPrefix + 27)
DECLARE_PMID(kClassIDSpace, kSelectFolderDialogBoss, kDocumentPrefix + 28)
DECLARE_PMID(kClassIDSpace, kDocumentSignalMgrBoss, kDocumentPrefix + 29)
DECLARE_PMID(kClassIDSpace, kSetDocTempFolderCmdBoss, kDocumentPrefix + 30)
#ifdef ID_DEPRECATED
DECLARE_PMID(kClassIDSpace, kPreRevertDocCmdBoss, kDocumentPrefix + 31) // Moving to DocumentActionsID.h
DECLARE_PMID(kClassIDSpace, kOpenRevertedDocCmdBoss, kDocumentPrefix + 32)
#endif

DECLARE_PMID(kMessageIDSpace, kMRUFileListChangedMessage, kDocumentPrefix + 33)	// The MRU filelist has changed (all bets are off as to how)
DECLARE_PMID(kMessageIDSpace, kMRUFileListAddedFileMessage, kDocumentPrefix + 34)	// A file was added to the MRU filelist
DECLARE_PMID(kMessageIDSpace, kMRUFileListRemovedFileMessage, kDocumentPrefix + 35)	// A file was removed from the MRU filelist

DECLARE_PMID(kClassIDSpace, kSaveDocDialogBoss, kDocumentPrefix + 36)

#ifdef MACINTOSH
DECLARE_PMID(kClassIDSpace, kOpenPanelPopupBoss, kDocumentPrefix + 37)
DECLARE_PMID(kClassIDSpace, kSavePanelPopupBoss, kDocumentPrefix + 38)
#endif

// New for 3.0 (DragonTail)
DECLARE_PMID(kClassIDSpace, kSetDocSavePrefsCmdBoss, kDocumentPrefix + 100)

DECLARE_PMID(kClassIDSpace, kINXImportSignalMgrBoss, kDocumentPrefix + 101)
DECLARE_PMID(kClassIDSpace, kOpenDocCloneCmdBoss, kDocumentPrefix + 102) // Moving to DocumentActionsID.h
DECLARE_PMID(kClassIDSpace, kCloseDocCloneCmdBoss, kDocumentPrefix + 103) // Moving to DocumentActionsID.h
DECLARE_PMID(kClassIDSpace, kCloneDocCmdBoss, kDocumentPrefix + 104) // Moving to DocumentActionsID.h

DECLARE_PMID(kMessageIDSpace, kMRUFileListReorderedFileMessage, kDocumentPrefix + 105)	// A file was reordered (removed and added) from the MRU filelist
#ifdef ID_DEPRECATED
DECLARE_PMID(kClassIDSpace, kVerifierBasedRecoverDocumentCmdBoss, kDocumentPrefix + 106) // Moving to DocumentActionsID.h
#endif

// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCUMENTLIST, kDocumentPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCUMENT, kDocumentPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ISYSFILEDATA, kDocumentPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ICLOSEWINCMDDATA, kDocumentPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IRESIZEWINCMDDATA, kDocumentPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IZOOMWINCMDDATA, kDocumentPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCPROTECTIONPREFS, kDocumentPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCMINISAVEPREFS, kDocumentPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCPROTECTIONPREFSCMDDATA, kDocumentPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCMINISAVEPREFSCMDDATA, kDocumentPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IRECOVERYLIST, kDocumentPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_INEWDOCACTION, kDocumentPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_ISAVEFILEDIALOG, kDocumentPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IRECOVERDOCUMENTCMDDATA, kDocumentPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IOPENDOCACTION, kDocumentPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IFILELIST, kDocumentPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_ISYSFILELISTDATA, kDocumentPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_IOPENFILEDIALOG, kDocumentPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCUMENTSNAPSHOTINFO, kDocumentPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_IPLACEOPTIONS, kDocumentPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_INEWDOCCMDDATA, kDocumentPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCUMENTPRIVATE , kDocumentPrefix + 23)
// DECLARE_PMID(kInterfaceIDSpace, IID_IOPENDOCSIGNALDATA, kDocumentPrefix + 24) Obsolete
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCFILEHANDLER, kDocumentPrefix + 25)
//DECLARE_PMID(kInterfaceIDSpace, IID_INEWSCRAPDOCSIGNALDATA, kDocumentPrefix + 26) 	Obsolete
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCOPTIMIZER, kDocumentPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_IVOIDPTRLISTDATA, kDocumentPrefix + 28)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTFOLDERDIALOG, kDocumentPrefix + 29) Obsolete. Use IID_IOPENFILEDIALOG
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCUMENTSIGNALDATA, kDocumentPrefix + 30)

DECLARE_PMID(kInterfaceIDSpace, IID_IDOCTEMPFOLDER, kDocumentPrefix + 31)

DECLARE_PMID(kInterfaceIDSpace, IID_IUIFLAGDATA, kDocumentPrefix + 32)

// New for 3.0 (DragonTail)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCCONSISTENCYOBSERVER, kDocumentPrefix + 33)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCCONSISTENCYCHECK, kDocumentPrefix + 34)
//DECLARE_PMID(kInterfaceIDSpace, IID_IDOCWINDOWTITLEPROVIDER, kDocumentPrefix + 35) // FIXME_OWL2: obsolete in CS4 - needs recipe

DECLARE_PMID(kInterfaceIDSpace, IID_IDOCSAVEPREFSCMDDATA, kDocumentPrefix + 100)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCSAVEPREFS, kDocumentPrefix + 101)

DECLARE_PMID(kInterfaceIDSpace, IID_IPLACEDIALOG, kDocumentPrefix + 102)

#ifdef MACINTOSH
DECLARE_PMID(kInterfaceIDSpace, IID_IOPENPANELPOPUP, kDocumentPrefix + 103)
DECLARE_PMID(kInterfaceIDSpace, IID_ISAVEPANELPOPUP, kDocumentPrefix + 104)
#endif
DECLARE_PMID(kInterfaceIDSpace, IID_ISUPPRESSIDMLINSAVEDLGDATA, kDocumentPrefix + 105)
DECLARE_PMID(kInterfaceIDSpace, IID_IUNTITLEDDOCCOUNT, kDocumentPrefix + 106)
DECLARE_PMID(kInterfaceIDSpace, IID_IREPAIRLIST, kDocumentPrefix + 107)
DECLARE_PMID(kInterfaceIDSpace, IID_IVERIFIERBASEDRECOVERDOCUMENTCMDDATA, kDocumentPrefix + 108)

// <Implementation ID>
// ImplementationIDs
DECLARE_PMID(kImplementationIDSpace, kDocumentListImpl, kDocumentPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kDocumentImpl, kDocumentPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kDocWindowListImpl, kDocumentPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kDocObserverImpl, kDocumentPrefix + 4)
#ifdef ID_DEPRECATED
DECLARE_PMID(kImplementationIDSpace, kDocumentComponentImpl, kDocumentPrefix + 5) //Moving to DocumentUIID.h
DECLARE_PMID(kImplementationIDSpace, kNewDocCmdImpl, kDocumentPrefix + 6) //Moving to DocumentActionsID.h
DECLARE_PMID(kImplementationIDSpace, kCloseDocCmdImpl, kDocumentPrefix + 7) //Moving to DocumentActionsID.h
DECLARE_PMID(kImplementationIDSpace, kSaveDocCmdImpl, kDocumentPrefix + 8) //Moving to DocumentActionsID.h
DECLARE_PMID(kImplementationIDSpace, kSaveAsDocCmdImpl, kDocumentPrefix + 9)  //Moving to DocumentActionsID.h
#endif
DECLARE_PMID(kImplementationIDSpace, kSaveAsAsciiCmdImpl, kDocumentPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kSetDocNameCmdImpl, kDocumentPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kSetFrontDocCmdImpl, kDocumentPrefix + 12)
#ifdef ID_DEPRECATED
DECLARE_PMID(kImplementationIDSpace, kOpenDocCmdImpl, kDocumentPrefix + 13) //Moving to DocumentActionsID.h
#endif
DECLARE_PMID(kImplementationIDSpace, kDocTestMenuComponentImpl, kDocumentPrefix + 15)

DECLARE_PMID(kImplementationIDSpace, kDocProtectionPrefsImpl, kDocumentPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kDocMiniSavePrefsImpl, kDocumentPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kDocProtectionPrefsCmdDataImpl, kDocumentPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kSetDocProtectionPrefsCmdImpl, kDocumentPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kDocMiniSavePrefsCmdDataImpl, kDocumentPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kSetDocMiniSavePrefsCmdImpl, kDocumentPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kStartRecoveryCmdImpl, kDocumentPrefix + 22)
#ifdef ID_DEPRECATED
DECLARE_PMID(kImplementationIDSpace, kRecoverDocumentCmdImpl, kDocumentPrefix + 23) //Moving to DocumentActionsID.h
#endif
DECLARE_PMID(kImplementationIDSpace, kRecoverDocumentCmdDataImpl, kDocumentPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kRecoveryListImpl, kDocumentPrefix + 25)

DECLARE_PMID(kImplementationIDSpace, kIDThreadRecoveryListProxyImpl, kDocumentPrefix + 26) 
DECLARE_PMID(kImplementationIDSpace, kDocumentSnapshotInfoImpl, kDocumentPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kOpenFileDialogImpl, kDocumentPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kSaveFileDialogImpl, kDocumentPrefix + 29)
#ifdef ID_DEPRECATED
DECLARE_PMID(kImplementationIDSpace, kSaveACopyCmdImpl, kDocumentPrefix + 30) //Moving to DocumentActionsID.h
DECLARE_PMID(kImplementationIDSpace, kRecentDocsComponentImpl, kDocumentPrefix + 31) //Moving to DocumentUIID.h
#endif
DECLARE_PMID(kImplementationIDSpace, kFileListImpl, kDocumentPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kPlaceFileDialogImpl, kDocumentPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kPlaceOptionsImpl, kDocumentPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kCNewDocCmdDataImpl, kDocumentPrefix + 35)

DECLARE_PMID(kImplementationIDSpace, kDocErrorStringServiceImpl, kDocumentPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kDocumentPrivateImpl, kDocumentPrefix + 37)

// DECLARE_PMID(kImplementationIDSpace, kOpenDocSignalDataImpl, kDocumentPrefix + 38) Obsolete
#ifdef ID_DEPRECATED
DECLARE_PMID(kImplementationIDSpace, kDocFileHandlerImpl, kDocumentPrefix + 39) //Moving to DocumentUIID.h
#endif
DECLARE_PMID(kImplementationIDSpace, kDocWindowZoomObserverImpl, kDocumentPrefix + 40)
// DECLARE_PMID(kImplementationIDSpace, kNewScrapDocSignalDataImpl, kDocumentPrefix + 41) Obsolete
// DECLARE_PMID(kImplementationIDSpace, kNewScrapDocSignalRespServiceImpl, kDocumentPrefix + 42) Obsolete
DECLARE_PMID(kImplementationIDSpace, kVoidPtrListDataImpl, kDocumentPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kOpenDocDialogImpl, kDocumentPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kSelectFolderImpl, kDocumentPrefix + 45)

// FileSignalResponders (Added for 2.0)
DECLARE_PMID(kImplementationIDSpace, kDocumentSignalDataImpl, kDocumentPrefix + 46)
//	NewDoc
DECLARE_PMID(kImplementationIDSpace, kBeforeNewDocSignalRespServiceImpl, kDocumentPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kDuringNewDocSignalRespServiceImpl, kDocumentPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kAfterNewDocSignalRespServiceImpl, kDocumentPrefix + 49)
//	OpenDoc
DECLARE_PMID(kImplementationIDSpace, kBeforeOpenDocSignalRespServiceImpl, kDocumentPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kDuringOpenDocSignalRespServiceImpl, kDocumentPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kAfterOpenDocSignalRespServiceImpl, kDocumentPrefix + 52)
//	SaveDoc
DECLARE_PMID(kImplementationIDSpace, kBeforeSaveDocSignalRespServiceImpl, kDocumentPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kAfterSaveDocSignalRespServiceImpl, kDocumentPrefix + 54)
//	SaveAsDoc
DECLARE_PMID(kImplementationIDSpace, kBeforeSaveAsDocSignalRespServiceImpl, kDocumentPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kAfterSaveAsDocSignalRespServiceImpl, kDocumentPrefix + 56)
//	SaveACopyDoc
DECLARE_PMID(kImplementationIDSpace, kBeforeSaveACopyDocSignalRespServiceImpl, kDocumentPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kDuringSaveACopyDocSignalRespServiceImpl, kDocumentPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kAfterSaveACopyDocSignalRespServiceImpl, kDocumentPrefix + 59)
//	RevertDoc
DECLARE_PMID(kImplementationIDSpace, kBeforeRevertDocSignalRespServiceImpl, kDocumentPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kAfterRevertDocSignalRespServiceImpl, kDocumentPrefix + 61)
//	CloseDoc
DECLARE_PMID(kImplementationIDSpace, kBeforeCloseDocSignalRespServiceImpl, kDocumentPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kAfterCloseDocSignalRespServiceImpl, kDocumentPrefix + 63)
//	NewScrapDoc
DECLARE_PMID(kImplementationIDSpace, kDuringNewScrapDocSignalRespServiceImpl, kDocumentPrefix + 64)


DECLARE_PMID(kImplementationIDSpace, kDocTempFolderImpl, kDocumentPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kSetDocTempFolderCmdImpl, kDocumentPrefix + 66)

DECLARE_PMID(kImplementationIDSpace, kUIFlagDataImpl, kDocumentPrefix + 67)
#ifdef ID_DEPRECATED
DECLARE_PMID(kImplementationIDSpace, kPreRevertDocCmdImpl, kDocumentPrefix + 68) //Moving to DocumentActionsID.h
DECLARE_PMID(kImplementationIDSpace, kOpenRevertedDocCmdImpl, kDocumentPrefix + 69) //Moving to DocumentActionsID.h
#endif

// New for 3.0 (DragonTail)
DECLARE_PMID(kImplementationIDSpace, kDocConsistencyObserverImpl, kDocumentPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kDocConsistencyCheckImpl, kDocumentPrefix + 71)

//	DocSetupChange
DECLARE_PMID(kImplementationIDSpace, kAfterDocSetupChangeDocSignalRespServiceImpl, kDocumentPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kBeforeDocSetupChangeDocSignalRespServiceImpl, kDocumentPrefix + 81)

DECLARE_PMID(kImplementationIDSpace, kDocSavePrefsImpl, kDocumentPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kDocSavePrefsCmdDataImpl, kDocumentPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kSetDocSavePrefsCmdImpl, kDocumentPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kDocSurrogateRegistryImpl_Obsolete, kDocumentPrefix + 103)

DECLARE_PMID(kImplementationIDSpace, kDocumentMRUListObserverImpl, kDocumentPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kSaveDocDialogImpl, kDocumentPrefix + 105)

DECLARE_PMID(kImplementationIDSpace, kAfterINXImportSignalRespServiceImpl, kDocumentPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kOpenDocCloneCmdImpl, kDocumentPrefix + 111) //Moving to DocumentActionsID.h
DECLARE_PMID(kImplementationIDSpace, kCloseDocCloneCmdImpl, kDocumentPrefix + 112) //Moving to DocumentActionsID.h
DECLARE_PMID(kImplementationIDSpace, kCloneDocCmdImpl, kDocumentPrefix + 113) //Moving to DocumentActionsID.h

#ifdef MACINTOSH
DECLARE_PMID(kImplementationIDSpace, kOpenPanelPopupImpl, kDocumentPrefix + 114)
DECLARE_PMID(kImplementationIDSpace, kSavePanelPopupImpl, kDocumentPrefix + 115)
#endif

DECLARE_PMID(kImplementationIDSpace, kRecentFileListImpl, kDocumentPrefix + 116)
DECLARE_PMID(kImplementationIDSpace, kRepairListImpl, kDocumentPrefix + 117)

#ifdef ID_DEPRECATED
DECLARE_PMID(kImplementationIDSpace, kVerifierBasedRecoverDocumentCmdImpl, kDocumentPrefix + 118) //Moving to DocumentActionsID.h
#endif
DECLARE_PMID(kImplementationIDSpace, kVerifierBasedRecoverDocumentCmdDataImpl, kDocumentPrefix + 119)

// <Service ID>
// Service IDs

// ID's 1-3 Obsolete (Used in 1.0 and 1.5 only)
// Obsolete ID's renamed to kDuringXXXDocSignalResponderService - see below, new data interfaces, too.
//DECLARE_PMID(kServiceIDSpace, kNewDocSignalResponderService, kDocumentPrefix + 1)
//DECLARE_PMID(kServiceIDSpace, kOpenDocSignalResponderService, kDocumentPrefix + 2)
//DECLARE_PMID(kServiceIDSpace, kNewScrapDocSignalResponderService, kDocumentPrefix + 3)

//ID's 4-9 Available

// FileSignalResponders (Added for 2.0)
//	NewDoc
DECLARE_PMID(kServiceIDSpace, kBeforeNewDocSignalResponderService, kDocumentPrefix + 10)
DECLARE_PMID(kServiceIDSpace, kDuringNewDocSignalResponderService, kDocumentPrefix + 11)
DECLARE_PMID(kServiceIDSpace, kAfterNewDocSignalResponderService, kDocumentPrefix + 12)
//	OpenDoc
DECLARE_PMID(kServiceIDSpace, kBeforeOpenDocSignalResponderService, kDocumentPrefix + 13)
DECLARE_PMID(kServiceIDSpace, kDuringOpenDocSignalResponderService, kDocumentPrefix + 14)
DECLARE_PMID(kServiceIDSpace, kAfterOpenDocSignalResponderService, kDocumentPrefix + 15)
//	SaveDoc
DECLARE_PMID(kServiceIDSpace, kBeforeSaveDocSignalResponderService, kDocumentPrefix + 16)
DECLARE_PMID(kServiceIDSpace, kAfterSaveDocSignalResponderService, kDocumentPrefix + 17)
//	SaveAsDoc
DECLARE_PMID(kServiceIDSpace, kBeforeSaveAsDocSignalResponderService, kDocumentPrefix + 18)
DECLARE_PMID(kServiceIDSpace, kAfterSaveAsDocSignalResponderService, kDocumentPrefix + 19)
//	SaveACopyDoc
DECLARE_PMID(kServiceIDSpace, kBeforeSaveACopyDocSignalResponderService, kDocumentPrefix + 20)
DECLARE_PMID(kServiceIDSpace, kDuringSaveACopyDocSignalResponderService, kDocumentPrefix + 21)
DECLARE_PMID(kServiceIDSpace, kAfterSaveACopyDocSignalResponderService, kDocumentPrefix + 22)
//	RevertDoc
DECLARE_PMID(kServiceIDSpace, kBeforeRevertDocSignalResponderService, kDocumentPrefix + 23)
DECLARE_PMID(kServiceIDSpace, kAfterRevertDocSignalResponderService, kDocumentPrefix + 24)
//	CloseDoc
DECLARE_PMID(kServiceIDSpace, kBeforeCloseDocSignalResponderService, kDocumentPrefix + 25)
DECLARE_PMID(kServiceIDSpace, kAfterCloseDocSignalResponderService, kDocumentPrefix + 26)
// DocSetup
DECLARE_PMID(kServiceIDSpace, kBeforeDocSetupChangeDocSignalResponderService, kDocumentPrefix + 27)
DECLARE_PMID(kServiceIDSpace, kAfterDocSetupChangeDocSignalResponderService, kDocumentPrefix + 28)

//
// ID 29 Available
//
//	NewScrapDoc
DECLARE_PMID(kServiceIDSpace, kDuringNewScrapDocSignalResponderService, kDocumentPrefix + 30)
DECLARE_PMID(kServiceIDSpace, kDocWindowTitleModifyService, kDocumentPrefix + 31)

DECLARE_PMID(kServiceIDSpace, kAfterINXImportSignalResponderService, kDocumentPrefix + 35)

// <Error ID>
// Error Codes
// NOTE:  The offset is used to find the corresponding error string
// Look in ApplStrings.fr resource UserErrorTable( kDocErrorStringTableRsrcID ) for the string definitions.
DECLARE_PMID(kErrorIDSpace, kDatabaseError, kDocumentPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kSaveToOpenFileError, kDocumentPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kNewDocFailedError, kDocumentPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kOpenDocFailedError, kDocumentPrefix + 4)
DECLARE_PMID(kErrorIDSpace, kRecoverDocFailedError, kDocumentPrefix + 5)
DECLARE_PMID(kErrorIDSpace, kSaveDocFailedError, kDocumentPrefix + 6)
DECLARE_PMID(kErrorIDSpace, kSaveAsDocFailedError, kDocumentPrefix + 7)
DECLARE_PMID(kErrorIDSpace, kReadFailedError, kDocumentPrefix + 8)
DECLARE_PMID(kErrorIDSpace, kWriteFailedError, kDocumentPrefix + 9)
DECLARE_PMID(kErrorIDSpace, kNewUIDFailedError, kDocumentPrefix + 10)
DECLARE_PMID(kErrorIDSpace, kDeleteFailedError, kDocumentPrefix + 11)
DECLARE_PMID(kErrorIDSpace, kSaveACopyFailedError, kDocumentPrefix + 12)
DECLARE_PMID(kErrorIDSpace, kCannotConvertFileError, kDocumentPrefix + 13)
DECLARE_PMID(kErrorIDSpace, kSaveDocCouldntShowUIError, kDocumentPrefix + 14)
DECLARE_PMID(kErrorIDSpace, kSaveDocPreviewFailedError, kDocumentPrefix + 15)
DECLARE_PMID(kErrorIDSpace, kDocHasPrereleaseContentError, kDocumentPrefix + 16)
DECLARE_PMID(kErrorIDSpace, kDynamicConversionFailure, kDocumentPrefix + 17)
DECLARE_PMID(kErrorIDSpace, kSaveDocModeSwitchFailedError, kDocumentPrefix + 18)
DECLARE_PMID(kErrorIDSpace, kDefaultsConsistencyError, kDocumentPrefix + 19)
DECLARE_PMID(kErrorIDSpace, kSaveCanceledDueToLowDiskSpace, kDocumentPrefix + 20)
DECLARE_PMID(kErrorIDSpace, kOpenDocFailedDueToNoContentMgr, kDocumentPrefix + 21)
//ID 22 - DO NOT REMOVE THIS, used for internally analysing specific corrupt docs
//DECLARE_PMID(kErrorIDSpace, kFileSizeTooLessOpenFailedError, kDocumentPrefix + 22)

#endif // __DocumentID__

