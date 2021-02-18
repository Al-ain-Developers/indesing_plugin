//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xdocbookworkflow/XDocBkTableHelper.h $
//  
//  Owner:	Ian Paterson
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

#ifndef __XDocBkTableHelper_H_DEFINED__
#define __XDocBkTableHelper_H_DEFINED__

class IStyleNameTable;

/**  Helper class that knows how to manipulate some properties of tables.

	@ingroup xdocbookworkflow
*/
class XDocBkTableHelper {

	public:

		/** Default constructor 
			@param UIDRef of table, instance of kTableModelboss
		*/
		XDocBkTableHelper(const UIDRef& tableModelUIDRef);
		
		/** Destructor */
		virtual ~XDocBkTableHelper();
	


		/**	Apply default table style

		 */
		void ApplyDefaultStyle();

		/**	Set text in given cell within rectangular table
			@param row IN
			@param col  IN
			@param text   IN specifies text to set 
		 */
		void SetTextContent(int32 row,
							int32 col,
							const WideString& text);


protected:
	
	/** Sets table level styles in the document.
	 */
	void SetTableLevelStyles();

	/** Set up a list of table level attributes to apply.
		@param outAttributes OUT 
	*/
	void ApplyTableAttributes(AttributeBossList& outAttributes);

	/** Apply styles to the text inside table cells.
	 */
	void SetLowerLevelStylesWithinTable();

	/** Applies styles to cells in a table. (Helper method for SetLowerLevelStylesWithinTable)
		@param gridAddress IN
		@param workspaceUIDRef IN
	 */
	void ApplyCellStyle(const GridAddress& gridAddress, 
					const UIDRef& workspaceUIDRef);

private:
	UIDRef fTableModelUIDRef;
};	







#endif // __XDocBkTableHelper_H_DEFINED__

