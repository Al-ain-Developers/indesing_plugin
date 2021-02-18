//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IChangesReviewSuite.h $
//  
//  Owner: Michele Goodwin
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

#pragma once
#ifndef _IChangesReviewSuite_
#define _IChangesReviewSuite_

#include "TrackChangesUIID.h"
	
/** IChangesReviewSuite
	This suite provides methods to check track change actions enablement.
*/
class IChangesReviewSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICHANGESREVIEWSUITE };

	/** Is accept change enabled for current selection?
		@return bool16 whether or not accept change is enabled.
	*/
	virtual bool16		IsAcceptChangeEnabled() = 0;
	
	/** Is reject change enabled for current selection?
		@return bool16 whether or not reject change is enabled.
	*/
	virtual bool16		IsRejectChangeEnabled() = 0;
	
	/** Is accept all changes in the story enabled?
		@return bool16 whether or not accept all changes in the story is enabled.
	*/
	virtual bool16		IsAcceptAllChangesEnabled() = 0;
	
	/** Is reject all changes in the story enabled?
		@return bool16 whether or not reject all changes in the story is enabled.
	*/
	virtual bool16		IsRejectAllChangesEnabled() = 0;
	
	/** Is accept all changes in the document enabled?
		@return bool16 whether or not accept all changes in the document is enabled.
	*/
	virtual bool16		IsAcceptAllDocChangesEnabled() = 0;
	
	/** Is reject all changes in the document enabled?
		@return bool16 whether or not reject all changes in the document is enabled.
	*/
	virtual bool16		IsRejectAllDocChangesEnabled() = 0;
	
	/** Is next change enabled for current selection?
		@return bool16 whether or not previous change is enabled.
	*/
	virtual bool16		IsPreviousChangeEnabled() = 0;
	
	/** Is previous change enabled for current selection?
		@return bool16 whether or not next change is enabled.
	*/
	virtual bool16		IsNextChangeEnabled() = 0;
	
	/** Does this story have any track changes?
		@return bool16 whether or not the story has changes.
	*/
	virtual bool16		StoryHasChanges() = 0;

};

#endif //_IChangesReviewSuite_
