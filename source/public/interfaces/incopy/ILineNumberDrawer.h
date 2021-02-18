//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/ILineNumberDrawer.h $
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
#ifndef __ILineNumberDrawer__
#define __ILineNumberDrawer__

#include "IPMUnknown.h"

#include "WritingModeUIID.h"
#include "PMString.h"
#include "PMRect.h"
#include "Command.h"


class IGraphicsContext;
class IWaxLine;
class IDataBase;
class LineDescription;

/** 
	This interface is used to control the drawing of the line information at the
	left side of galley and story views. In the info column or paragraph style column as it is called in InDesign.
	Probably, the only parts relevant to external parties is the SetDisplayInfoColumn() and GetDisplayInfoColumn()
	routines.
*/
class ILineNumberDrawer : public IPMUnknown
{
	public:	
		enum { kDefaultIID = IID_ILINENUMBERDRAWER };
				
		/**
			Turn on or off the display of line numbers (also paragraph style names). Collapses the whole info column or expands it to it's previous
			state.
			@param display - kTrue to uncollapse and kFalse to collapse it.
			@return none
		**/
		virtual void SetDisplayInfoColumn(bool16 display) = 0;
		
		/**
			Get the current display state of the info column.
			@return kTrue if the Info Column is showing
		**/
		virtual bool16 GetDisplayInfoColumn() = 0;

		/**
			Draw a line number at the proper position for a specific line in the view. This applies to galley view only story view
			does not display line numbers. The line numbers are for lines as they would display if they were in layout view. This routine
			will also call the DrawParagraphName routine below.
			@param gc - context to draw into
			@param flags - standard draw flags (same as for page items etc.). Used to tell if currently printing. Use 0 for a standard screen draw
			@param at - galley view line index to draw a line number for.
			@return none
		**/
		virtual void DrawLineNumber(IGraphicsContext* gc, int32 flags, int32 at) = 0;
	
		/**
			Draw a paragraph style name in the info column. These would draw only on lines that start a paragraph
			@param gc - context to draw into
			@param flags - standard draw flags (same as for page items etc.). Used to tell if currently printing. Use 0 for a standard screen draw
			@param at - line index to draw a line number for will only draw if the line starts a new paragraph.
			@param overflow - are we in overset text when drawing this.
			@return no longer relavent (ignore).
		**/
		virtual PMReal DrawParagraphName(IGraphicsContext* gc, int32 flags, int32 at, bool16 overflow = kFalse) = 0;
};

#endif 		// __ILineNumberDrawer__
