//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ExcelFilterID.h $
//  
//  Owner: Johnr 
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
//  Contains IDs used by the Excel import filter
//  
//========================================================================================

#ifndef __ExcelFilterID__
#define __ExcelFilterID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kExcelFilterPrefix   RezLong(0x46700)

// <Start IDC>
// PluginID
#define kExcelFilterPluginName 		      "Excel 97-98 Import Filter"
DECLARE_PMID(kPlugInIDSpace, kExcelFilterPluginID, kExcelFilterPrefix + 1)


// Excel Filter Resource 
// <Class ID>
DECLARE_PMID(kClassIDSpace, kExcelFilterBoss, kExcelFilterPrefix + 1)
DECLARE_PMID(kClassIDSpace, kExcelPreferencesScriptBoss, kExcelFilterPrefix + 2)
DECLARE_PMID(kClassIDSpace, kExcelPreferencesBoss, kExcelFilterPrefix + 3)
DECLARE_PMID(kClassIDSpace, kExcelImportFilterStringRegisterBoss, kExcelFilterPrefix + 4)
DECLARE_PMID(kClassIDSpace, kExcelErrorStringServiceBoss, kExcelFilterPrefix + 5)


// Excel Filter 
// <Implementation ID>
DECLARE_PMID(kImplementationIDSpace, kExcelImportProvider, kExcelFilterPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kExcel97Preferences, kExcelFilterPrefix + 2)

DECLARE_PMID(kImplementationIDSpace, kExcelAccess, kExcelFilterPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kExcelImportFilterStringRegister, kExcelFilterPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kExcelErrorStringServiceImpl, kExcelFilterPrefix + 5)

DECLARE_PMID(kImplementationIDSpace, kExcelScriptProviderImpl, kExcelFilterPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kExcelScriptImpl, kExcelFilterPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kExcelOLEAutoRefCountImpl, kExcelFilterPrefix + 8)

// Excel Filter 
// <Interface ID>
DECLARE_PMID(kInterfaceIDSpace, IID_EXCEL_97_PREFERENCES, kExcelFilterPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_EXCEL_ACCESS, kExcelFilterPrefix + 3)


#endif // __ExcelFilterID__


/******************************************************************************
 * $Log: /Source/Public/Interfaces/Text/ExcelFilterID.h $
 * 
 * 3     11/25/98 2:23p Johnr
 * win scripting IDS
 * 
 * 2     10/05/98 4:12p Stellad
 * Changes to move to Build 317
 * 
 * 4     8/04/98 6:46p Sdu
 * After merge /w Build 288 of K2
 * 
 * 15    7/24/98 2:26p Jeffreys
 * Moved Private Data Stuff
 * 
 * 14    7/15/98 5:06p Jeffreys
 * Changed ID Prefixes
 * 
 * 13    7/15/98 2:17p Jeffreys
 * Changing Prefix ID's
 * 
 * 12    7/15/98 2:07p Jeffreys
 * Private Data Stuff
 * 
 * 11    7/06/98 7:16p Stellad
 * Added in the IDs necessary for the ErrorStringService
 * 
 * 10    7/03/98 4:47p Davids
 * Added string registration IDs
 * 
 * 9     7/02/98 9:08a Craigw
 * Added kExcelAccess
 * 
 * 8     6/27/98 11:31a Craigw
 * 
 * 7     6/19/98 3:34 AM Craigw
 * changed kExcelFilterPluginName to match the specified plugin name.
 * 
 * 6     6/16/98 9:02 PM Craigw
 * Check-in after implementing the basics of scripting.
 * 
 * 5     6/5/98 1:47 PM Craigw
 * removed an interface that is not currently required
 * 
 * 4     5/20/98 1:10p Craigw
 * Adding IDs for scripting.
 * 
 * 3     4/09/98 1:41p Craigm
 * Merged with K2 source for build 218 (dated March 30, 1998).
 * 
 * 2     3/18/98 9:46a Craigw
 * Changes to support a K2 persistent object.
 * 
 * 1     3/10/98 10:31a Craigw
 * Filter ID for Excel
 * 
 * 1     3/06/98 3:50p Davids
 * First cut
 * 
 * 1     3/04/98 4:26p Craigm
 * Word 97 import filter plug in resource IDs.
 *****************************************************************************/




