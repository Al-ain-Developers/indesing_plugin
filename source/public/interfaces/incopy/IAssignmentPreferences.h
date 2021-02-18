//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IAssignmentPreferences.h $
//  
//  Owner: Jon Pugh
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
#ifndef IASSIGNMENTPREFERENCES_H
#define IASSIGNMENTPREFERENCES_H

#include "IPMUnknown.h"
#include "AssignmentID.h"


/** Manages the state of the "Show Assigned Frames" View menu option. */
class IAssignmentPreferences : public IPMUnknown
{
	typedef IPMUnknown Inherited;

public:
	enum {kDefaultIID = IID_IASSIGNMENTPREFERENCES};

public:
	/**
		Whether or not assigned frames are highlighted in layout windows.
		@return - A boolean which is kTrue if assigned frames are being shown.
	*/
	virtual bool16 		GetShowAssignedFrames() const = 0;

	/**
		Set whether or not assigned frames are highlighted in layout windows.
		@param show - A boolean which is kTrue if assigned frames are being shown.
	*/
	virtual void		SetShowAssignedFrames(bool16 show) = 0;
};


#endif	// IASSIGNMENTPREFERENCES_H
