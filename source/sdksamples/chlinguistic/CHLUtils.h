//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/chlinguistic/CHLUtils.h $
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

#ifndef __CHLUtils_h__
#define __CHLUtils_h__

// Forward declarations:
class ICoreFilename;
class IPMStream;
class PMString;

/** Utility helper class used in this plug-in.

  @ingroup chlinguistic
*/
class CHLUtils
{
public:
	/** Gets the application folder. From this folder, you can get the
	 * 	"Plug-Ins" folder. 
	 * 
	 * 	NOTE: For the Macintosh platform, this returns the InDesign 
	 * 	installation folder path, not the path inside the package 
	 * 	folder where the actual InDesign application binary resides.
	 * 
	 * 	@param appFolder OUT The complete path to the application folder. 
	 * 	@return kSuccess if success, kFailure otherwise.
	 */
	static ErrorCode GetApplicationFolder(PMString& appFolder);

	/** Queries the ICoreFileName. Unimplemented.
	 */
	static ICoreFilename* QueryCoreFilename(const PMString& fullPath);

	/**	Removes the last element from the path. We search for the last 
	 * 	delimeter and knock off the stuff that comes after. 
	 * 	We lose this data so beware!
	 * 	@param fromthis IN/OUT Path from which you want to remove last element.
	 */
	static void RemoveLastElement(PMString& fromthis);
		
	/** Creates a file stream fo reading, using the given path.
	 * 	@param fullPath IN Full path to file to open for reading.
	 * 	@return IPMStream of the opened file. Nil if failure.
	 */
	static IPMStream* CreateFileStreamRead(const PMString& fullPath);

	/** Tests if the file exists and can be read.
	 * 	@param fullPath IN Full path to file to open for reading.
	 * 	@return kSuccess if file exists, kFailure otherwise.
	 */
	static ErrorCode FileExistsForRead(const PMString& fullPath);
};

#endif // __CHLUtils_h__

// End, CHLUtils.h

