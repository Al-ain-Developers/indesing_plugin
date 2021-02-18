//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IOpenedFileInfo.h $
//  
//  Owner: Matt Joss
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
#ifndef __IOpenedFileInfo__
#define __IOpenedFileInfo__

#include "DocFrameworkID.h"


/** Interface for keeping information about the file when it was opened
	Templates and converted documents open as new files which lose information
	such as file path.  At this point, only file path is being preserved.
*/
class IOpenedFileInfo : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IOPENEDFILEINFO };

	/** 
		Called when a file is opened to store data data about the opened file on the document
		@param filePath the full path of the file that was opened
	*/
	virtual void		FileOpened( const IDFile& filePath ) = 0;

	/** 
		Returns the file path of the file that was opened
		@return the file path of the file that was opened
	*/
	virtual IDFile		GetOpenedFilePath( ) const = 0;

};

#endif //__IOpenedFileInfo__
