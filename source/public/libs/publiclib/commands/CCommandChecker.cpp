//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/commands/CCommandChecker.cpp $
//  
//  Owner: Richard Rodseth
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
//  
//  Purpose: Base implementation of ICommandChecker. Subclasses should override DoCheckCommand
//  
//========================================================================================

#include "VCPublicHeaders.h"

#include "CCommandChecker.h"

DEFINE_HELPER_METHODS(CCommandChecker)

//----------------------------------------------------------------------------------------
// CCommandChecker constructor
//----------------------------------------------------------------------------------------

CCommandChecker::CCommandChecker(IPMUnknown *boss) :
	HELPER_METHODS_INIT(boss),
	fLastError(kSuccess),
	fSavedError(kSuccess),
	fUseSavedError(kFalse)
{
}

//----------------------------------------------------------------------------------------
// CCommandChecker destructor
//----------------------------------------------------------------------------------------

CCommandChecker::~CCommandChecker()
{
}

//----------------------------------------------------------------------------------------
// CCommandChecker::CheckCommand
//----------------------------------------------------------------------------------------

ErrorCode CCommandChecker::CheckCommand(bool16 saveError)
{	
	if (fUseSavedError == kFalse)
	{
		fLastError = this->DoCheckCommand();
		fUseSavedError = saveError;		
	}
	return fLastError;
}

//----------------------------------------------------------------------------------------
// CCommandChecker::ClearLastError
//----------------------------------------------------------------------------------------

void CCommandChecker::ClearLastError(bool16 saveError)
{
	fLastError = kSuccess;
	fUseSavedError = saveError;
}

//----------------------------------------------------------------------------------------
// CCommandChecker::SaveLastError
//----------------------------------------------------------------------------------------

void CCommandChecker::SaveLastError()
{
	fUseSavedError = kTrue;
}

//----------------------------------------------------------------------------------------
// CCommandChecker::GetLastError
//----------------------------------------------------------------------------------------

ErrorCode CCommandChecker::GetLastError()
{
	return fLastError;
}

//----------------------------------------------------------------------------------------
// CCommandChecker::SetError
//----------------------------------------------------------------------------------------
		
void CCommandChecker::SetError(const ErrorCode& error)
{
	fLastError = error;
	fUseSavedError = kTrue;
}

//----------------------------------------------------------------------------------------
// CCommandChecker::DoCheckCommand
//----------------------------------------------------------------------------------------

ErrorCode CCommandChecker::DoCheckCommand()
{
	// Overridden by subclasses
	return kSuccess;
}

