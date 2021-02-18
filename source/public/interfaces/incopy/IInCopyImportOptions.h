//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IInCopyImportOptions.h $
//  
//  Owner: craig rainwater
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
#ifndef __IInCopyImportOptions__
#define __IInCopyImportOptions__

#include "IPMUnknown.h"
#include "IXMLOutStream.h"
#include "IInCopyImportSupport.h"

#include "InCopySharedID.h"


/**------------------------------------------------------------------------------------------------
//	Class IInCopyImportOptions
//
//	This class is used to control the import of various elements that might exist in an InCopy
//	file.
//
//	By setting ImportStyleTable(), ImportSwatchList() or ImportXMLTagList() to kFalse, the InCopy
//	import code will skip the data associated with those elements in the InCopy file.
//
//	For more information on usage/purpose of ImportSupport() please see IInCopyImportSupport.h.
//	The IInCopyImportSupport interface provides alternate methods to match style/swatch names that
//	are encountered in the InCopy story but not found in the style/swatch lists.
//
//	ImportXMPData() value is ignored by the import code.
//------------------------------------------------------------------------------------------------
*/
class IInCopyImportOptions : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IINCOPYIMPORTOPTIONS };

		//----------------------------------------------------------------------------------------

		/**	Set method to set the options
			@param importStyleTable kTrue to import, kFalse to ignore
			@param importSwatchList kTrue to import, kFalse to ignore
			@param importXMPData Default to kTrue, Not used for version 2.0, always import xmp data
			@param importXMLTagList Default to kTrue, kTrue to import, kFalse to ignore
			@param importSupport Default to nil
		 */
		virtual void Set(
			bool16 importStyleTable,		
			bool16 importSwatchList,		 
			bool16 importXMPData = kTrue,	 
			bool16 importXMLTagList = kTrue, 
			IInCopyImportSupport* importSupport = nil
			) = 0;

/**	Set the IInCopyImportSupport* value, can be nil
	@param importSupport 
 */
        virtual void ImportSupport(
			IInCopyImportSupport* importSupport
			) = 0;

/**	Get the IInCopyImportSupport* value, may be nil
	@param none
	@return IInCopyImportSupport* 
	*/
		virtual IInCopyImportSupport* ImportSupport() const = 0;

/**	Get value of import style table flag
	@param importStyleTable 
	*/
		virtual void ImportStyleTable(
			bool16 importStyleTable
			) = 0;

 /** Get value of import style table flag, kTrue to import, kFalse to ignore
	@param none
	@return bool16 
 */
		virtual bool16 ImportStyleTable() const = 0;

/**	Set value of import swatch list flag, kTrue to import, kFalse to ignore
	@param importSwatchList 
 */
		virtual void ImportSwatchList(
			bool16 importSwatchList
			) = 0;

/**	Get value of import swatch list flag, kTrue to import, kFalse to ignore
	@param none
	@return bool16 
 */
		virtual bool16 ImportSwatchList() const = 0;
		
/**	Set value of import xmp data flag
	Not used, always import xmp data if it exists
	@param importXMPData kTrue to import, kFalse to ignore
 */
		virtual void ImportXMPData(
			bool16 importXMPData
			) = 0;

/** Get value of import xmp data flag, kTrue to import, kFalse to ignore
	Not used, always import xmp data if it exists
	@param none
	@return bool16 
 */
		virtual bool16 ImportXMPData() const = 0;

/**	Get value of import xml tag list flag, kTrue to import, kFalse to ignore
	@param none
	@return bool16 
 */
		virtual bool16 ImportXMLTagList() const = 0;
};
#endif // __IInCopyImportOptions__