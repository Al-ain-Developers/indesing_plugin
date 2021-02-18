//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILibraryPanelData.h $
//  
//  Owner: Mark VerMurlen
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
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __ILibraryPanelData__
#define __ILibraryPanelData__

#include "ShuksanID.h"
#include "LibraryPanelID.h"

//========================================================================================
// Forward declarations
//========================================================================================

class ILibrary;
class ILibraryDisplayMgr;


//-------------- ILibraryPanelData Declaration ------------------
/**	Provides library information for the Library panel
*/
class  ILibraryPanelData : public IPMUnknown
{
	public:

		enum { kDefaultIID = IID_ILIBRARYDATA };

		/** Initializes the library data.
		*/
		virtual	void Initialize() = 0;
		
		/** Gets the interface to the library display manager.
			@return interface pointer to ILibraryDisplayMgr
		*/
		virtual ILibraryDisplayMgr* GetDisplayMgr() const = 0;
		
		/** Sets the interface to the library.
			@param library IN interface pointer to the library
		*/
		virtual void SetLibrary( ILibrary* library ) = 0;
		
		/** Get the interface to the library.
			@return interface pointer to the library
		*/
		virtual ILibrary* GetLibrary() const = 0;
};

#endif
