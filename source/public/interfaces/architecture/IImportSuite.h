//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IImportSuite.h $
//  
//  Owner: Michael Martz
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

#pragma once
#ifndef _IImportSuite_
#define _IImportSuite_

#include "IPMUnknown.h"
#include "OpenPlaceID.h"

class IPlaceGun;
class URI;

/**
	Place file interface, caller speifies an URI that represents the file for import along with import options.
*/
class IImportSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IIMPORTSUITE };
		
	/**	Description: Can do import based on current selection?
		@param none
		@return bool16 kTrue / kFalse
	 */
	virtual bool16 CanImport() const = 0;
	
	/**	Description: Do import or do import/replace current selection
		@param uriToImport IN an URI that represents the file to import
		@param db IN the target database for the import
		@param replaceSelectedItem IN should import replace the selected item
		@param uiFlags IN what level of UI should be allowed during import
		@param retainFormat IN should import retain text format, applies to text import
		@param convertQuotes IN should import convert quotation mark types, applies to text import
		@param applyCJKGrid IN should import apply CJK grid if present, applies to text import
		@return bool16 kTrue if the import is successfule, otherwise, kFalse 
	 */
	virtual bool16 DoImport(const URI& uriToImport, IDataBase* db, bool16 replaceSelectedItem, UIFlags uiFlags, bool16 retainFormat, bool16 convertQuotes, bool16 applyCJKGrid) = 0;	
};

#endif // _IImportSuite_