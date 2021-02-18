//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ICreateOutlinesUtils.h $
//  
//  Owner: Bryce Morsello
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
#ifndef __ICreateOutlinesUtils__
#define __ICreateOutlinesUtils__

#include "IPMUnknown.h"
#include "charpathid.h"

#include "TableTypes.h"
#include "UIDList.h"
#include "Utils.h"

class ICommand ;
class IGraphicsPort ;
class ITableModel ;
class ITextModel ;

/**
	Utility methods related to creating outlines.
	<pre>
	Utils&lt;ICreateOutlinesUtils&gt;()->CreateCOTextCmd(...) ;
	</pre>
	@ingroup text_util 
*/
class ICreateOutlinesUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICREATEOUTLINESUTILS } ;

	/**
		Used at draw time to determine whether a graphics port is being drawn into for the purpose of creating outlines
		@param gPort is the graphics port to test
		@return kTrue if the graphics port is for creating outlines.
	*/
	virtual bool16 IsCreateOutlinesPort( IGraphicsPort* gPort ) const = 0 ;

	/**
		Create a command to create outlines from text
		@param textModel is the story containing the text to convert to outlines
		@param start is the start offset of the text in the story
		@param end is the end offset of the text in the story
		@param deleteOriginal whether to delete the text converted to outlines and replace it within the outlines as inline objects
		@return the unexecuted command
	*/
	virtual ICommand* CreateCOTextCmd( const UIDRef& textModel,
									   TextIndex start, 
									   TextIndex end, 
									   bool16 deleteOriginal ) const = 0 ;

	/**
		Returns a command to create outlines from all the text in one or more frames
		@param frames is the list of text frames containing the text to convert to outlines
		@param deleteOriginal whether to delete the frames converted to outlines
		@return the unexecuted command
	*/
	virtual ICommand* CreateCOFrameCmd( const UIDList& frames,
									    bool16 deleteOriginal ) const = 0 ;

	/**
		Returns a command to create outlines from text in a table
		@param tableModel is the table
		@param gridArea is the cells containing the text to convert to outlines
		@param deleteOriginal whether to delete the text in the cells converted to outlines and replace it within the outlines as inline objects
		@return the unexecuted command
	*/
	virtual ICommand* CreateCOTableCmd( const UIDRef& tableModel,
										const GridArea& gridArea,
										bool16 deleteOriginal ) const = 0 ;

	/**
		Filter a list of UIDs for valid text frames (called by CreateCOFrameCmd)
		@param sourceList is the list to filter IN
		@return is the filtered list
	*/
	virtual UIDList FilterUIDList( const UIDList& sourceList ) const = 0 ;
} ;

#endif
