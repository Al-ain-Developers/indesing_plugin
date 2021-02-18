//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/inxerrorlogging/SDKFileUtils.cpp $
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
#include "SDKFileUtils.h"


PMString SDKFileUtils::fErrorLogFilePath;
int32 SDKFileUtils::fNumFiles = 0;
 
void SDKFileUtils::GetNextFilePath(PMString& path)
{
	
	PMString tempPath(fErrorLogFilePath);
	CharCounter pos = fErrorLogFilePath.LastIndexOfCharacter('.');

	IDThreading::AtomicIncrement(fNumFiles); 
	
	PMString suffixPath("_");
	suffixPath.AppendNumber(fNumFiles);

	if(pos != -1)
		tempPath.Insert(suffixPath, pos);
	else
		tempPath.Append(suffixPath);

	path.SetString(tempPath);
}

void SDKFileUtils::SetBaseFilePath(const PMString& path)
{
	fErrorLogFilePath = path;
	fNumFiles = 0;
}

void SDKFileUtils::GetBaseFilePath(PMString& path)
{
	path.SetString(fErrorLogFilePath);
}