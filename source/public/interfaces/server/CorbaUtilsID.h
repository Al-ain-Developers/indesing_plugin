//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/server/CorbaUtilsID.h $
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
//  Contains IDs used by the generic page item plug-in
//  
//========================================================================================

#ifndef __CorbaUtilsID__
#define __CorbaUtilsID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"
#include "ScriptingID.h"
#define kCorbaUtilsIDPrefix	RezLong(0x1F200)

// <Plugin ID>
DECLARE_PMID(kPlugInIDSpace, kCorbaUtilsPluginID, kCorbaUtilsIDPrefix + 1)


// <Class ID>
DECLARE_PMID(kClassIDSpace, kCorbaAPIScriptMgrBoss,						kCorbaUtilsIDPrefix + 0)

// <Interface ID>

DECLARE_PMID(kInterfaceIDSpace, IID_ICORBA, 							kCorbaUtilsIDPrefix + 0)

// <Implementation ID>
DECLARE_PMID(kImplementationIDSpace, kCorbaAPIScriptMgrImpl, 			kCorbaUtilsIDPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kCorbaImpl, 						kCorbaUtilsIDPrefix + 1)

// <Script Element ID>
DECLARE_PMID(kScriptInfoIDSpace, kCorbaFrameworkSuiteScriptElement,		kCorbaUtilsIDPrefix + 1)

enum CorbaUtilsScriptIDs
{
	s_Framework =			'frwk',
} ;

#endif // __CorbaUtilsID__
