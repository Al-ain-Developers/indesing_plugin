//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IDrawDivider.h $
//  
//  Owner: Kevin Van Wiel  
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
#ifndef __IDrawDivider__
#define __IDrawDivider__

#include "IPMUnknown.h"
#include "ILayoutViewLineData.h"

#include "WritingModeUIID.h"
#include "UIDRef.h"

class IWaxLine;
class IGraphicsContext;
class LineDescription;
class IGraphicsPort;

/** 
	This interface is responsible for drawing the various type of dividers in story and galley views. Currently,
	dividers are only drawn in the InCopy version of story/galley. There is a story bar divider at the top of each
	story displayed in the view and in galley view there is a divider for each frame. Note this does not handle the
	overset divider line that draws in story view. That is handled by an internal interface not exposed at this time.
*/
class IDrawDivider : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IDRAWDIVIDER };

		/**
			Draw a divider line. Dividers are a line in the story galley view and have a textline associated with them
			@param description - a line description describing the divider
			@param lineIndex - the index of the line where the divider will draw
			@param gPort - port to draw the divider into
			@param flags - standard flags (same as page item draw routines). Used to tell if printing or not.
			@return none
		**/
		virtual void Draw(const LineDescription &description, int32 lineIndex, IGraphicsPort *gPort, int32 flags) = 0;
		
		/**
			Return a rectangle of the collapse rect portion of a story bar divider.
			@param description - a line description describing the divider
			@param lineRect - rectangle describing the entire divider
			@return rectangle describing the bounding box of the close icon in the story bar divider
		**/
		virtual PMRect GetCollapseRect(const LineDescription &description, const PMRect &lineRect) = 0;
		
		/**
			Return the index of a story of the related story bar if the point is in a story bar area if point is not.
			Used for hit testing.
			@param point - routine will check if this point intersects a story divider bar.
			@return returns the story index of a divider if it intersects with the point or -1 if no intersection.
		**/
		virtual int32 FindStoryIndexOfBar(PMPoint point) = 0;
		
		/**
			Draw a story divider. 
			@param lineRect - location and dimensions of story divider to draw
			@param storyName - name of the story divider (can be calculated with AssembleStoryLabel()).
			@param gPort - port to draw the divider into
			@return none
		**/
		virtual void DrawStoryBar(const PMRect &lineRect, const PMString &storyName, IGraphicsPort *gPort) = 0;
		
		/**
			For a given story index return the string to be displayed in the story bar (divider) 
			@param storyIndex - index of story to get the label for
			@return string that displays in the story divider bar at the top of each story in InCopy.
		**/		
		virtual PMString AssembleStoryLabel(int32 storyIndex) = 0;
};

#endif 		// __IDrawDivider__