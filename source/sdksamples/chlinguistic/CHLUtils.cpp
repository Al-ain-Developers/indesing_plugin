//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/chlinguistic/CHLUtils.cpp $
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

#include "VCPlugInHeaders.h"

// Interface includes:
#include "ICoreFilename.h"
#include "ICoreFilenameUtils.h"

// General includes:
#include "SDKFileHelper.h"
#include "StreamUtil.h"
#include "FileUtils.h"

// Project includes:
#include "CHLUtils.h"

// Defines:
static const char k_UNIXDELCHAR = '/';
static const char  k_MACDELCHAR = ':';
static const char k_WINDELCHAR = '\\';


/* GetApplicationFolder
*/
ErrorCode CHLUtils::GetApplicationFolder(PMString& appFolder)
{
	ErrorCode status = kFailure;
	do
	{
		InterfacePtr<ICoreFilename> iExecutableCoreFilename((ICoreFilename*)::CreateObject(kCoreFilenameBoss, IID_ICOREFILENAME));
		if (iExecutableCoreFilename == nil)
		{
			ASSERT_FAIL("CHLUtils::GetApplicationFolder() iExecutableCoreFilename invalid");
			break;
		}

		InterfacePtr<ICoreFilenameUtils> iCoreFilenameUtils((ICoreFilenameUtils*)::CreateObject(kCoreFilenameUtilsBoss, IID_ICOREFILENAMEUTILS));
		if (iCoreFilenameUtils == nil)
		{
			ASSERT_FAIL("CHLUtils::GetApplicationFolder() iCoreFilenameUtils invalid");
			break;
		}

		iCoreFilenameUtils->GetExecutableName(iExecutableCoreFilename);
		
		const PMString* executableFilename = iExecutableCoreFilename->GetFullName();
		if ((executableFilename == nil) || (executableFilename->empty()))
		{
			break;
		}

		appFolder = *executableFilename;
		RemoveLastElement(appFolder);
		
#ifdef MACINTOSH
		// NOTE: The Plug-Ins folder is now 3 levels further up from the application folder
#ifdef DEBUG
		const PMString before = appFolder;
#endif		
		RemoveLastElement(appFolder);
		RemoveLastElement(appFolder);
		RemoveLastElement(appFolder);
#ifdef DEBUG
		const PMString after = appFolder;
#endif		
#endif
		status = kSuccess;

	} while (false); // only do once

	return status;

}

/* RemoveLastElement
*/
void CHLUtils::RemoveLastElement(PMString& fromthis)
{
	// takes off the last element from the path. We search for the last delimeter and knock off the
	// stuff that comes after. We lose this data so beware!
	int lastpos = 0;
	for (int i = 0 ; i< fromthis.CharCount();i++)
		if ((fromthis[i] == k_MACDELCHAR) || (fromthis[i] == k_UNIXDELCHAR) || (fromthis[i] == k_WINDELCHAR))
			lastpos = i;
	// At this point lastpos should point to the last delimeter, knock off the rest of the string.
	fromthis.Truncate(fromthis.CharCount()-lastpos);
}


/* CreateFileStreamRead
*/
IPMStream* CHLUtils::CreateFileStreamRead(const PMString& fullPath)
{
	ErrorCode status = kFailure;
	IPMStream* iDataFileStream = nil;
	do
	{
		IDFile dataFile(fullPath);

		iDataFileStream = StreamUtil::CreateFileStreamRead(dataFile);
		if (iDataFileStream == nil)
		{
			status = kFailure;
			break;
		}

		status = kSuccess;

	} while (false); // only do once

	return iDataFileStream;
}

/* FileExistsForRead
*/
ErrorCode CHLUtils::FileExistsForRead(const PMString& fullPath)
{
	ErrorCode status = kFailure;
	do
	{
		InterfacePtr<IPMStream> iDataFileStream(CHLUtils::CreateFileStreamRead(fullPath));
		if (iDataFileStream == nil)
		{
			break;
		}

		iDataFileStream->Close();

		status = kSuccess;

	} while (false); // only do once

	return status;
}

// End, CHLUtils.cpp.

