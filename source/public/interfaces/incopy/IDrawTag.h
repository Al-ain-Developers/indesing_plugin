//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IDrawTag.h $
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
#ifndef __IDrawTag__
#define __IDrawTag__

#include "IPMUnknown.h"
#include "ILayoutViewLineData.h"

#include "WritingModeUIID2.h"
#include "UIDRef.h"

class IWaxLine;
class IGraphicsContext;
class RunDescription;
class IGraphicsPort;

/**
	IDrawTag an interface to draw tags such as inline notes, xml, and inline footnotes in galley and story view.
*/
class IDrawTag : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IDRAWTAG };

		/**
			Draw tag associated with the specified run.
			@param IN description a run description to get a cooresponding ITextRun for
			@param IN lineIndex a line index to get access the run
			@param IN gPort the port to draw into
			@param OUT runWidth the width of the tag that is drawn
			@param IN flags 0==normal mode (draw top and bottom borders), 1==draw in overlap mode (just draw bottom border)
			@param IN textThreadUID UID of the thread or kInvalidUID if primary story thread
			@return void
		**/
		virtual void Draw(const RunDescription &description, int32 lineIndex, IGraphicsPort *gPort, PMReal *runWidth, int32 flags, UID textThreadUID = kInvalidUID) = 0;
		/**
			Compute tag width of the specified run 
			@param IN description a run description to get a cooresponding ITextRun for
			@param OUT runWidth the width of the tag that is drawn
			@param IN textThreadUID UID of the thread or kInvalidUID if primary story thread
			@return void
		**/
		virtual void ComputeTagWidth(const RunDescription &description, PMReal *runWidth, UID textThreadUID = kInvalidUID) = 0;

		/**
			Draw png icon.
			@param IN topLeft the point at which to draw
			@param IN pid plugin id with the png art
			@param IN rid resource id of the png art
			@param IN gPort the port to draw into
			@return void
		**/
		virtual void DrawPngIcon(const PMPoint &topLeft, const PluginID & pid, const RsrcID & rid, IGraphicsPort *gPort) = 0;
		/**
			Gets the width of the png specified.
			@param IN pid plugin id with the png art
			@param IN rid resource id of the png art
			@return PMReal width of the png art
		**/
		virtual PMReal GetPngIconWidth(const PluginID & pid, const RsrcID & rid) = 0;
		/**
			Gets the height of the png specified.
			@param IN pid plugin id with the png art
			@param IN rid resource id of the png art
			@return PMReal height of the png art
		**/
		virtual PMReal GetPngIconHeight(const PluginID & pid, const RsrcID & rid) = 0;

};

#endif 		// __IDrawTag__