//========================================================================================
//  
//  $File:$
//  
//  Owner: Adobe Developer Technologies
//  
//  $Author:$
//  
//  $DateTime:$
//  
//  $Revision:$
//  
//  $Change:$
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#ifndef __ChartUIBrowseCSVFile_h__
#define __ChartUIBrowseCSVFile_h__


/** Browse the file system for a CSV file.

	@ingroup candlechartui
	
*/
class ChartUIBrowseCSVFile
{
public:
	/** Browse the file system for a comma separated values file.
		@param outFile OUT the CSV file that opens.
		@return kTrue if a CSV file is found, otherwise kFalse.
	*/
	static bool16 BrowseFile(IDFile& outFile);

};

#endif // __ChartUIBrowseCSVFile_h__

