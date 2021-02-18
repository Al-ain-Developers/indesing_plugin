//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/plugins/WPlugInMain.cpp $
//  
//  Owner: mohammed fakhoury
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

#include "PlugIn.h"
#include "PMTypes.h"


bool16 gFalse = kFalse;
void DontDeadStrip();

extern "C" BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved);

//
// DllMain; DLL entry point
//
extern "C" BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	switch( dwReason ){
	  	case DLL_PROCESS_ATTACH:
		{
			DontDeadStrip();	// force static constructors & destructors 
								// to be linked in
			
			TCHAR pathName[_MAX_PATH];
			::GetModuleFileName(hInstance, pathName, sizeof( pathName ) / sizeof ( TCHAR ));	
			IDFile spec;
			spec.SetTString(pathName);
			ResourceEnabler::SetResourceFile( &spec );
		}
		break;

	};

	return TRUE; 
}

