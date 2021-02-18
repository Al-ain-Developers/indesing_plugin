//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/TrackChangesAutoDisabler.h $
//  
//  Owner:Chris Parrish
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
#ifndef __TrackChangesAutoDisabler__
#define __TrackChangesAutoDisabler__

#pragma export on

/** 	A stack based class that disables track changes on the specified story during construction and re-enables if necessary on destruction.
*/
class PUBLIC_DECL TrackChangesAutoDisabler
{
public:
	/** Constructor - disables track changes on specified story.
	*/
	TrackChangesAutoDisabler(const UIDRef& storyRef);
	/** Destructor - re-enables track changes.
	*/
	~TrackChangesAutoDisabler();

private:
	UIDRef		fStoryRef;
	bool		fReEnableChanges;
};

#pragma export off
#endif //__TrackChangesAutoDisabler__
