//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/external/afl/includes/WinFileUtils.h $
//  
//  Owner: Michael Easter
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
#ifndef __WinFileUtils__
#define __WinFileUtils__

// ----- Includes -----
#include "AFLDecl.h"
#include "AFile.h"
#include "AString.h"

namespace adobe {
namespace afl {

/**
 Windows specific utility class used to manipulate and obtain information
 for files and directories.
 @see AFile
 @see AString
 */
class AFL_DECL WinFileUtils
{
public:
	/**
	 Returns the UNC path of the file.
	 @param file	IN File to get the UNC path from.
	 @return The UNC path of the file.
			 An empty string if the the path is empty.
	 */
	static AString GetUNCPath(const AFile& file);
	
	/**
	 Returns the local drive path of the file.
	 The path returned may be a UNC path if no local drive mapping exists for the \\server\share. 
	 @param file	IN File to get the local drive path from.
	 @return The local drive path of the file.
			 An empty string if the call fails.
	 */
	static AString GetLocalPath(const AFile& file);

	/**
	 Returns the POSIX path of the file.
	 @param file	IN File to get the POSIX path from.
	 @return The POSIX path of the file.
			 An empty string if the call fails.
	 */
	static AString GetPosixPath(const AFile& file);

};

}	// namespace afl
}	// namespace adobe

#endif	// __WinFileUtils__
