//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/DragDropID.h $
//  
//  Owner: Dave Burnard
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
//  Contains IDs for DragDrop classes, IIDs, and ImplementationIDs
//  
//========================================================================================

#ifndef __DragDropID__
#define __DragDropID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kDragDropPrefix	 RezLong(0x7500)

// <Start IDC>
// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kDragDropItemBoss, kDragDropPrefix + 1)
DECLARE_PMID(kClassIDSpace, kDragDropHandlerBoss, kDragDropPrefix + 2)

DECLARE_PMID(kClassIDSpace, kClipboardItemBoss, kDragDropPrefix + 3)
DECLARE_PMID(kClassIDSpace, kDataExchangeItemBoss, kDragDropPrefix + 4)

DECLARE_PMID(kClassIDSpace, kSimpleTextDEHandlerBoss, kDragDropPrefix + 10)
DECLARE_PMID(kClassIDSpace, kColorDEHandlerBoss, kDragDropPrefix + 11)
DECLARE_PMID(kClassIDSpace, kSysFileDEHandlerBoss, kDragDropPrefix + 12)

DECLARE_PMID(kClassIDSpace, kScrapDocBoss, kDragDropPrefix + 20)
// gap

DECLARE_PMID(kClassIDSpace, kSysFileDataExchHandlerDefaultHelperBoss, kDragDropPrefix + 32)
DECLARE_PMID(kClassIDSpace, kSysFileDataExchHandlerNetscapeHelperBoss, kDragDropPrefix + 33)
DECLARE_PMID(kClassIDSpace, kSysFileDataExchHandlerIE5HelperBoss, kDragDropPrefix + 34)
//gap
// <Message ID>
// ----- Message IDs -----
// Messages sent by various Data Objects
// -- these are ClassIDs but have no classes!
// -- they are only used for sending messages
DECLARE_PMID(kMessageIDSpace, kBeginDragDrop, kDragDropPrefix + 200)
DECLARE_PMID(kMessageIDSpace, kFinishDragDrop, kDragDropPrefix + 201)
DECLARE_PMID(kMessageIDSpace, kBeginDragDrop_BeforeCmdSequence, kDragDropPrefix + 202)
DECLARE_PMID(kMessageIDSpace, kFinishDragDrop_AfterCmdSequence, kDragDropPrefix + 203)

// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IDRAGDROPCONTROLLER, kDragDropPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IDRAGDROPSOURCE, kDragDropPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IDRAGDROPTARGET, kDragDropPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IPMDATAOBJECT, kDragDropPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IDATAEXCHANGEHANDLER, kDragDropPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IPMSTREAM_FLAVOR_READ, kDragDropPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IPMSTREAM_FLAVOR_WRITE, kDragDropPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IFLAVORDATA, kDragDropPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IDROPTARGETCALLBACK, kDragDropPrefix + 9)

DECLARE_PMID(kInterfaceIDSpace, IID_IDRAGDROPTARGETDOCUMENT, kDragDropPrefix + 10	)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IDATAEXCHANGECONTROLLER, kDragDropPrefix + 12	)

DECLARE_PMID(kInterfaceIDSpace, IID_ISIMPLETEXTDEDATA, kDragDropPrefix + 13)

DECLARE_PMID(kInterfaceIDSpace, IID_IDATAEXCHANGEHANDLERFLAVORHELPER, kDragDropPrefix + 15)

DECLARE_PMID(kInterfaceIDSpace, IID_ICLIPBOARDCONTROLLER, kDragDropPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRAPSUITEPASTEHELPER, kDragDropPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_IMACOSXSERVICESCONTROLLER, kDragDropPrefix + 22)

DECLARE_PMID(kInterfaceIDSpace, IID_IDROPDESKTOPFILECMDDATA, kDragDropPrefix + 30)

DECLARE_PMID(kInterfaceIDSpace, IID_IDRAGDROPSOURCECONTENTHELPER, kDragDropPrefix + 40)
DECLARE_PMID(kInterfaceIDSpace, IID_IDRAGDROPTARGETFLAVORHELPER, kDragDropPrefix + 41)

DECLARE_PMID(kInterfaceIDSpace, IID_IFILEDROP_PARENT, kDragDropPrefix + 50 )
DECLARE_PMID(kInterfaceIDSpace, IID_IFILEDROP_RIGHTSIBLING, kDragDropPrefix + 51 )

DECLARE_PMID(kInterfaceIDSpace, IID_IDDTARGETREGISTRAR, kDragDropPrefix + 52	)
DECLARE_PMID(kInterfaceIDSpace, IID_IMDV_DDEVENTHANDLERWRAPPER, kDragDropPrefix + 53	)

// <Implementation ID>
// ImplementationIDs
DECLARE_PMID(kImplementationIDSpace, kDragDropControllerImpl, kDragDropPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kDragDropSourceImpl, kDragDropPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kDragDropTargetImpl, kDragDropPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kDragDropDataObjectImpl, kDragDropPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kFlavorStreamReadImpl, kDragDropPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kFlavorStreamWriteImpl, kDragDropPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kFlavorDataImpl, kDragDropPrefix + 8)
//gap

DECLARE_PMID(kImplementationIDSpace, kSimpleTextDEHandlerImpl, kDragDropPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kSimpleTextDEDataImpl, kDragDropPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kColorDEHandlerImpl, kDragDropPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kPageItemDEHandlerImpl, kDragDropPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kSysFileDEHandlerImpl, kDragDropPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kAppFrameDDTargetImpl, kDragDropPrefix + 15)
// gap

DECLARE_PMID(kImplementationIDSpace, kMacOSXServicesControllerImpl, kDragDropPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kMacOSXServicesDataObjectImpl, kDragDropPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kMacOSXServicesFlavorStreamReadImpl, kDragDropPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kMacOSXServicesFlavorStreamWriteImpl, kDragDropPrefix + 43)

DECLARE_PMID(kImplementationIDSpace, kClipboardControllerImpl, kDragDropPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kClipboardDataObjectImpl, kDragDropPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kClipFlavorStreamReadImpl, kDragDropPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kClipFlavorStreamWriteImpl, kDragDropPrefix + 53)

DECLARE_PMID(kImplementationIDSpace, kSysFileDataExchHandlerHelperProviderImpl, kDragDropPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kSysFileDataExchHandlerDefaultHelperImpl, kDragDropPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kSysFileDEH_NetscapePromise_HelperImpl, kDragDropPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kSysFileDataExchHandlerIE5HelperImpl, kDragDropPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kWorkerThreadClipboardControllerImpl, kDragDropPrefix + 58)

DECLARE_PMID(kImplementationIDSpace, kDV_DDTargetRegistrarImpl, kDragDropPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kMDV_DDEventHandlerWrapperImpl, kDragDropPrefix + 60)
//gap
// <Error ID>
// Error Codes
// NOTE:  The offset is used to find the corresponding error string
DECLARE_PMID(kErrorIDSpace, kScrapInitializationError, kDragDropPrefix + 1)

// <Service ID>
// Service IDs
DECLARE_PMID(kServiceIDSpace, kSysFileDataExchHandlerHelperService, kDragDropPrefix + 1)

// WidgetIDs:
// ActionIDs:
#endif
