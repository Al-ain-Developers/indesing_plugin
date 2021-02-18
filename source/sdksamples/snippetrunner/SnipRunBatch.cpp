//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/SnipRunBatch.cpp $
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
#include "IPMStream.h"
#include "IOpenFileDialog.h"

// General includes:
#include "PMString.h"
#include "K2Vector.h"
#include "TextChar.h"
#include "ShuksanID.h"
#include "StreamUtil.h"
#include "CreateObject.h"
#include "SysFileList.h"

// Project includes:
#include "SnipRunBatch.h"
#include "SnipRunLog.h"
#include "SnipRunID.h"

#include "FileUtils.h"
/*
*/
SnipRunBatch::SnipRunBatch() : fSnipRunPath()
{
	if (this->Browse() == kSuccess)
		this->Handle();
}

/*
*/
ErrorCode SnipRunBatch::Browse()
{
	ErrorCode status = kFailure;
	do
	{
		IDFile theFile;
		if (this->OpenFileDialog(theFile) != kSuccess)
			break;
		InterfacePtr<IPMStream> scriptStream
		(
			StreamUtil::CreateFileStreamRead
			(
				theFile,
				 kOpenIn, 
				 'TEXT', 
				 'CWIE' 
			)
		);
		if (scriptStream == nil)
			break;
		fStream = scriptStream;
		fSysFile = theFile;
		status = kSuccess;
	} while (false);
	return status;
}

/*
*/
ErrorCode SnipRunBatch::OpenFileDialog(IDFile& file)
{
	ErrorCode status = kFailure;
	do
	{
		SysFileList filesToOpen;
		InterfacePtr<IOpenFileDialog> openFileDialog
		(
			static_cast<IOpenFileDialog*>
			(
				::CreateObject
				(
					kOpenFileDialogBoss,
					IOpenFileDialog::kDefaultIID
				)
			)
		);
		if (openFileDialog == nil)
		{
			ASSERT_FAIL("create kOpenFileDialogBoss failed");
			break;
		}

#ifdef MACINTOSH
		openFileDialog->AddType('TEXT');
#endif

		if (openFileDialog->DoDialog
			(
				nil,		// No default file.
				filesToOpen, 
				kFalse,		// don't allow multiple files to be selected
				nil			// use the default dialog title
			) == kFalse)
			break;

		file = *filesToOpen.GetNthFile(0);
		status = kSuccess;
	} while (false);
	return status;
}

/*	
*/
void SnipRunBatch::Handle()
{
	// Set the path for SnipRun to be the path 
	// of the folder containing the script.
	PMString scriptFileName;
	this->GetAbsolutePath(fSysFile, scriptFileName);
	fSnipRunPath = scriptFileName;
	this->RemoveLastElement(fSnipRunPath);
	this->AppendPathSeparator(fSnipRunPath);

	// Loop round processing commands from the script.
	ErrorCode status = kFailure;
	int32 lineNumber = 0;
	SNIPLOG("Begin script %s, path %s", scriptFileName.GetPlatformString().c_str(), fSnipRunPath.GetPlatformString().c_str());
	do
	{
		// Get the next line from the file.
		PMString commandLine;
		status = this->GetLine(commandLine);
		if (status != kSuccess)
			continue;
		lineNumber++;

		// Skip over empty lines.
		if (commandLine.empty())
			continue;

		// Extract the name of the snippet to be run and its parameters from the line.
		PMString snippetName;
		PMString params;
		this->GetSnippetNameAndParams(commandLine, snippetName, params);

		// Run the snippet.
		status = kFailure;
		SNIPLOG(" feature currently disabled");
		SNIPLOG(" script failed at line %d", lineNumber);
	} while (status == kSuccess);
	SNIPLOG("End script %s", scriptFileName.GetPlatformString().c_str());
}


/*
	Reads from the stream into a string up till the next '\r' character,
	'\n' characters are ignored, characters following a ';' character
	are treated as comments and are ignored, leading and trailing white
	space is removed.
*/
ErrorCode SnipRunBatch::GetLine(PMString& line)
{
	ErrorCode status = kFailure;
	
	// Get a line from the stream
	uchar oneChar(0);
	line.Clear();
	
	StreamState streamState;

	// We'll use a do-while(false) to break out on bad pointers:
	do
	{
		// Scan the characters in the first line:
		fStream->XferByte(oneChar);
		bool16 comment = kFalse;
		while ((streamState = fStream->GetStreamState())==kStreamStateGood)
		{
			if (oneChar == '\r') // carriage return delimits line
				break;
			if (oneChar == ';') // ignore comments
				comment = kTrue;

			if (comment == kFalse && oneChar != '\n')
				line.Append((char)oneChar);
			
			// Read the next character
			fStream->XferByte(oneChar);
			
		} // end while streamstategood
		
	} while (false); // Only do once.
	
	line.StripWhiteSpace(PMString::kLeadingAndTrailingWhiteSpace);

	if (streamState == kStreamStateGood)
		status = kSuccess;
	if (streamState == kStreamStateEOF)
	{
		if (!line.empty())
		{
			status = kSuccess;
		}
		else
		{
			status = kSnipRunEOFErrorCode;
		}
	}

	return status;
	
}

/*
*/
void SnipRunBatch::GetSnippetNameAndParams(const PMString& line, PMString& snippetName, PMString& params)
{
	// Everything before the first space on the line
	// is the name of the snippet.
	snippetName.Clear();
	int32 i = 0;
	for (i = 0; i < line.CharCount(); i++)
	{
		if  (line [i] == kTextChar_Space)
		{
			break;
		}
		snippetName.Append(line [i]);
	}

	// Everything after the space is parameters.
	params.Clear();
	for (++i; i < line.CharCount(); i++)
	{
		params.Append(line [i]);
	}
	snippetName.StripWhiteSpace(PMString::kLeadingAndTrailingWhiteSpace);
	snippetName.SetTranslatable(kFalse);
	params.StripWhiteSpace(PMString::kLeadingAndTrailingWhiteSpace);
}

/*
	Determines the absolute path from a IDFile
*/
void  SnipRunBatch::GetAbsolutePath(const IDFile& spec, PMString& name)
{
	name.Clear();

#ifdef MACINTOSH
	FileUtils::IDFileToPMString(spec, name);
#else
	name.Append(spec.GetString());
#endif
}


void SnipRunBatch::RemoveLastElement(PMString& fromthis)
{
	// takes off the last element from the path. We search for the last delimeter and knock off the
	// stuff that comes after. We lose this data so beware!
	int lastpos = 0;
	for (int i = 0 ; i< fromthis.CharCount();i++)
		if ((fromthis[i] == ':') || (fromthis[i] == '/') || (fromthis[i] == '\\'))
			lastpos = i;
	// At this point lastpos should point to the last delimeter, knock off the rest of the string.
	fromthis.Truncate(fromthis.CharCount()-lastpos);
}

void SnipRunBatch::AppendPathSeparator(PMString& path)
{
#ifdef MACINTOSH
	path.Append(":");
#else
	path.Append("\\");
#endif
}

// End, SnipRunBatch.cpp.


