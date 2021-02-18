//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ILoadStyleCmdData.h $
//  
//  Owner: Wai Cheuk
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
#ifndef __ILOADSTYLECMDDATA__
#define __ILOADSTYLECMDDATA__

#ifndef __IPMUnknown__
#include "IPMUnknown.h"
#endif

class IStyleNameTable;
class IStyleGroupManager;

/**
	A data interface used for loading styles.
*/

class ILoadStyleCmdData : public IPMUnknown
{
public:

	/**
		The choices for loading styles
	*/
	enum LoadChoice
	{
		/** Load Paragraph styles */
		kLoadParagraphStyles = 0,
		/** Load Character styles */
		kLoadCharacterStyles,
		/** Load both Paragraph and Character styles */
		kLoadParaCharStyles ,
		/** Load Named Grids */
		kLoadNamedGridsTable,
		/** Load Mojikumi Table */
		kLoadMojikumiTable,
		/** Load Tsume Table */
		kLoadTsumeTable,
		/** Load Kinsoku Table */
		kLoadKinsokuTable,
		/** Load Composite Font Table */
		kLoadCompositeFontTable,
		/** Load All CJK Tables */
		kLoadAllCJKTables,
		/** Load TOC Styles */
		kLoadTOCStyles,
		/** Load Object styles */
		kLoadObjectStyles,
		/** Load Text Variables */
		kLoadTextVariableTable,
        
        /** Load Table styles */
		kLoadTableStyles,
		/** Load Cell styles */
		kLoadCellStyles,
		/** Load both Table and Cell styles */
		kLoadTableCellStyles,

		/** Load XRef formats */
		kLoadXRefFormats
		
	};


	/** Set the command data.
		@param srcStyleNameTable	IN	source style name table
		@param destStyleNameTable	IN	destination style name table
		@param srcStyleUID			IN	source style UID
		@param destStyleUID			IN	destination style UID
		@see IStyleNameTable
	 */
	virtual void Set(IStyleGroupManager* srcStyleNameTable,
					 IStyleGroupManager* destStyleNameTable,
					 UID srcStyleUID,
					 UID destStyleUID) = 0;

	/** Set the command data.
		@param srcStyleNameTable	IN	source style name table
		@param destStyleNameTable	IN	destination style name table
		@param srcStyleUID			IN	source style UID
		@param destStyleUID			IN	destination style UID
		@see IStyleNameTable
	 */
	virtual void Set(IStyleNameTable* srcStyleNameTable,
					 IStyleNameTable* destStyleNameTable,
					 UID srcStyleUID,
					 UID destStyleUID) = 0;

	/**	Get the source style name table
		@param none
		@return IStyleNameTable* the source style name table
	 */
	virtual IStyleNameTable* GetSrcStyleNameTable() = 0;

	/**	Get the source style name table
		@param none
		@return IStyleNameTable* the source style name table
	 */
	virtual IStyleGroupManager* GetSrcStyleSetManager() = 0;

	/**	Get the destination style name table
		@param none
		@return IStyleNameTable* the destination style name table
	 */
	virtual IStyleNameTable* GetDestStyleNameTable() = 0;

		/**	Get the destination style name table
		@param none
		@return IStyleNameTable* the destination style name table
	 */
	virtual IStyleGroupManager* GetDestStyleSetManager() = 0;

	/**	Get the source style UID
		@param none
		@return UID the source style UID
	 */
	virtual UID GetSrcStyleUID() = 0;

	/**	Get the destination style UID
		@param none
		@return UID the destination style UID
	 */
	virtual UID GetDestStyleUID() = 0;
};

#endif
