//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/INoteSettings.h $
//  
//  Owner: Jesse Jones (jejones)
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
//  Summary:	A persistent interface hanging off the doc used to store note settings.	
//  
//========================================================================================

#pragma once
#ifndef INOTESETTINGS_H
#define INOTESETTINGS_H

#include "IPMUnknown.h"
#include "InCopySharedID.h"


// ===================================================================================
//	class INoteSettings
// ===================================================================================
/** This interface is persistent in session's kWorkspaceBoss, indicates show/hide the Notes display
*/
class INoteSettings : public IPMUnknown {

	typedef IPMUnknown Inherited;

//-----------------------------------
//	Constants
//
public:
	enum {kDefaultIID = IID_INOTESETTINGS};

//-----------------------------------
//	New API
//
public:
	// ----- Hide Note Windows Flag -----

/**	Check if the Notes are hidden
	@return  kTrue means the Notes are hidden 
 */
	virtual bool16 		NotesAreHidden() const = 0;

/**	Set the show/hide state 
	@param hide kTrue means to hide the Notes display
 */
	virtual void 		SetHideNote(bool16 hide) = 0;
	

/**	Dirty the interface
 */
	virtual void		DummyDirtyDataBase() = 0;
};


#endif	// INOTESETTINGS_H
