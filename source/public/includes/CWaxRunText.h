//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CWaxRunText.h $
//  
//  Owner: Ric Kamicar
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
#ifndef __CWaxRunText__
#define __CWaxRunText__

#include "CPMUnknown.h"

#include "IWaxRunText.h"
#include "IWaxRunShape.h"
#include "IWaxLineShape.h"
#include "IGraphicsPort.h"

/** Base implementation for managing the Draw()ing of the text within this waxRun.  Use this implementation if you would like (at least partial) generic waxRun drawing.
*/
class PUBLIC_DECL CWaxRunText : public CPMUnknown<IWaxRunText>
{
public:
	CWaxRunText(IPMUnknown* boss) : CPMUnknown<IWaxRunText>(boss)
		{ }

	/** Default drawing of the wax run. Draws text and associated objects (i.e. adornments).
		This method first checks to see if the port is CreateOutlines mode

			If so, calls DrawRunForCreateOutlines(). If it returns kFalse, nothing else is done. Otherwise, the auxInfo returned is installed into the graphics port/data for the duration of this method.

		It then gathers all adornments that match this pass and calls their draw method.
		If the pass is kPassText, it calls the other Draw() method on this interface.

		@see IWaxRunText for details on this method, its parameters and return values..
	*/
	virtual void  Draw(GraphicsData* gd, int32 iShapeFlags, Text::DrawPassInfo::Pass pass, const PMRect* areaToDraw) const;

protected:
	/** Default drawing of the text associated with the waxRun. It is called when the public Draw() method on this interface is called with pass == kPassText.
		See that method for details on the parameters.

		 @note: WaxRuns must define this method themselves.  Typically this involves inspecting the IWaxRenderData and processing the IWaxGlyphs associated with this run, taking port modes of PDF and CreateOutlines into consideration.
	*/
	virtual void  Draw(GraphicsData* gd, int32 iShapeFlags, const PMRect* areaToDraw) const = 0;

	/** Checks for Create Outlines mode and prepares auxiliary information for the port if appropriate. It also further initializes the port for this particular waxRun.
		Called by the public Draw() method.

		@param gPort IN Where to draw.
		@param auxInfo OUT returned additional information which is needed for create outlines drawing.
		@return whether this run should be drawn (kTrue) or not.

		@note: This only pertains (and is only called) if the port is designated as Creating Outlines.
		@note: When this method is called, it may divide the waxRun into (potentially many) smaller runs to accomodate the CreateOutlines range and/or parameters.
	*/
	virtual bool16  DrawRunForCreateOutlines( IGraphicsPort* gPort, GPortAuxInfoParam& auxInfo ) const ;
	
private:
	void GetSelectionRects(GraphicsData* gd, IWaxRun* thisRun, K2Vector<PMRect> *selectedRects, K2Vector<PMRect> *unselectedRects) const;
	bool UseSelectionClip(bool hasSelection, ITextAdornment *adornment) const;
};

#endif
