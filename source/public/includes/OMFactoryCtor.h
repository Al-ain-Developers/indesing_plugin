//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/OMFactoryCtor.h $
//  
//  Owner: Zak_Williamson
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

#ifndef __OMFACTORYCTOR__
#define __OMFACTORYCTOR__

#include "OMTypes.h"

class IDataBase;
class IPMUnknown;
class IPMStream;
#ifdef DEBUG
typedef IPMUnknown * ( *InterfaceProxyConstructor)(IPMUnknown *pInterfaceImpl,const int32 ProxyID,IPMUnknown *boss);
#endif
#ifdef USE_ALLOCATE_WITH_BOSS
typedef void *(*InterfaceConstructor)(void *buffer, IPMUnknown *boss);
#else
typedef void *(*InterfaceConstructor)(IPMUnknown *boss);
#endif
typedef int32 (*InterfaceSizeOf)();
typedef void *(*BossConstructor)(ClassID clsID);
typedef void (*InterfaceDestructor)(void *deleteMe);
typedef void (*InterfaceReadWrite)(IPMUnknown *obj, IPMStream *s, ImplementationID prop, int32 length);
typedef void (*InterfaceResetViewFun)(IPMUnknown *obj, ImplementationID prop);
#endif
