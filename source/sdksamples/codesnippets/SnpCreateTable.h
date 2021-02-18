//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpCreateTable.h $
//  
//  Owner: Adobe Developer Technologies
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

#ifndef __SnpCreateTable_h__
#define __SnpCreateTable_h__

/** 
	\li	Creates a new table using ITableUtils.

  	@ingroup sdk_snippet
  	@ingroup sdk_table
	
  	@see kNewTableCmdBoss
 */
class SnpCreateTable
{
	public:
		/**
			Checks if a table can be created (added for 1026750).
			@param storyRef references the story the table is to be created inside
			@param at where to insert the table in the story
			@return kTrue if a table can be created, kFalse otherwise.
		 */
		bool16 CanCreateTable(const UIDRef& storyRef, const TextIndex at);

		/**
			Method that attempts to create a table
			@return kSuccess on success, kFailure otherwise.
		*/
		ErrorCode CreateTable(const UIDRef& storyRef, 
								const TextIndex at,
							  const int32 numRows = 2, 
							  const int32 numCols = 3,
							  const PMReal rowHeight = 60.0,
							  const PMReal colWidth = 100.0,
							  const CellType cellType = kTextContentType);

};



#endif // __SnpCreateTable_h__

//End, SnpCreateTable.h


