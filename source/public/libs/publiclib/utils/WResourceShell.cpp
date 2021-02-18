//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/utils/WResourceShell.cpp $
//  
//  Owner: Michael Burbidge, Mouhammad Fakhoury, lance bushore
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

#include "VCPublicHeaders.h"

#include "WResourceShell.h"

// ----- Interface Includes -----

#include "WPublicLibGlobals.h"

// ----- Implementation Includes -----



//========================================================================================
// STRUCTS
//========================================================================================

struct MacStyleHandle
{
	void * resourceData;
	int32 resourceSize;
};

struct EnumResStruct
{
	int16 currentIndex;
	int16 desiredIndex;
	LPTSTR resourceName;
};


#define WTOOLBOX

//========================================================================================
// ----- GetResource
//========================================================================================
SysHandle WResourceShell::GetWinResource(LPTSTR  rsrcType, LPTSTR  id)
{
	HMODULE hModule = (HMODULE)PublicLibGlobals::WinEnvironment::GetResourceHandle();

	return WResourceShell::GetWinResource(hModule, rsrcType, id);
}

SysHandle WResourceShell::GetWinResource(HMODULE hModule, LPTSTR  rsrcType, LPTSTR  id)
{
	HRSRC hrsrc = ::FindResource(hModule, id, rsrcType);
	
	if (hrsrc)
	{
		HGLOBAL hMem = ::LoadResource(hModule,hrsrc);	
		ASSERT_MSG(hMem != nil, "WResourceShell::GetResource - hMem != nil");
		if (hMem)
		{
			MacStyleHandle* macHandle = new MacStyleHandle();
			macHandle->resourceData = ::LockResource(hMem);
			macHandle->resourceSize = ::SizeofResource(hModule,hrsrc);	
			return (SysHandle) macHandle;
		}

	}

	return nil;
}

//========================================================================================
// Global routines
//========================================================================================

static BOOL CALLBACK EnumResourceNamesProc(HANDLE, LPCTSTR, LPTSTR, LONG_PTR pEnumResStruct);
BOOL CALLBACK EnumResourceNamesProc(HANDLE, LPCTSTR, LPTSTR resName, LONG_PTR pEnumResStruct)
{
	EnumResStruct* resStruct = reinterpret_cast<EnumResStruct*>(pEnumResStruct);
	resStruct->currentIndex = resStruct->currentIndex + 1;
	resStruct->resourceName = resName;
	
	if (resStruct->desiredIndex && (resStruct->desiredIndex == resStruct->currentIndex))
	 	return FALSE;

	return TRUE;
}

//========================================================================================
// METHODS WResourceShell
//========================================================================================

//========================================================================================
// ----- GetSizeofResource
//========================================================================================
int32 WResourceShell::GetSizeofResource( const SysHandle sysHandle)
{
	if(sysHandle)
		return ((MacStyleHandle*) sysHandle)->resourceSize;
	else
		return 0;
}


//========================================================================================
// ----- ReleaseResource
//========================================================================================
void WResourceShell::ReleaseResource(const SysHandle rsrcHandle)
{
	delete (MacStyleHandle*) rsrcHandle;
}


//========================================================================================
// ----- CountResources
//========================================================================================
int16 WResourceShell::CountResources(RsrcType rsrcType)
{
	HRSRC hModule = PublicLibGlobals::WinEnvironment::GetResourceHandle();

	EnumResStruct resStruct;
	resStruct.currentIndex = resStruct.desiredIndex = 0;
	
	::EnumResourceNames((HMODULE)hModule, MAKEINTRESOURCE(rsrcType), (ENUMRESNAMEPROC)EnumResourceNamesProc, reinterpret_cast<LONG_PTR>(&resStruct));	
	return resStruct.currentIndex;
}

//========================================================================================
// ----- GetResourceByIndex
//========================================================================================
SysHandle WResourceShell::GetResourceByIndex(RsrcType rsrcType, RsrcID index)
{
	HRSRC hModule = PublicLibGlobals::WinEnvironment::GetResourceHandle();

	EnumResStruct resStruct;
	resStruct.currentIndex = 0;
	resStruct.desiredIndex = (int16)index;
	resStruct.resourceName = nil;
	
	::EnumResourceNames((HMODULE)hModule, MAKEINTRESOURCE(rsrcType), (ENUMRESNAMEPROC)EnumResourceNamesProc, reinterpret_cast<LONG_PTR>(&resStruct));	
	
	if (resStruct.resourceName != nil)
		return GetWinResource(MAKEINTRESOURCE(rsrcType), resStruct.resourceName);
	
	return nil;
}
