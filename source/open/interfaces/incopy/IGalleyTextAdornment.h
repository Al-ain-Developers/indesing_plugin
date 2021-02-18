//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/incopy/IGalleyTextAdornment.h $
//  
//  Owner: Heath Horton
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
//  Proj:	
//  
//========================================================================================

#pragma once
#ifndef _H_IGalleyTextAdornment
#define _H_IGalleyTextAdornment

#include "IPMUnknown.h"
#include "WritingModeID.h"

class GraphicsData;
class PMRect;
class IParcelShape;
class ITextOptions;
class IGraphicsPort;
class ITextModel;
class RunDescription;
class ITextLines;

//	THIS IS A STEAL FROM IGlobalTextAdornments, no wax *see GlobalTextAdornments*

class IGalleyTextAdornment : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGALLEYTEXTADORNMENT };

	//
	// Returns the Draw priority of the adornment.
	//
	//virtual Text::DrawPriority GetDrawPriority() = 0;

	//
	// The purpose of this method is to give the Parcel a chance to avoid
	// passes and calling adornments that aren't needed. If, for example, a
	// particular adornment was the only one needing to be called on a
	// particular pass and the adornment wouldn't be drawing because of some
	// Galley state, by returning kFalse the pass could be avoided.
	//
	// Galley adornments which indicate they are not active will NOT be
	// called to Draw.
	//
	// NOTES
	//	parcelShape MAY NOT be a UID based object.
	//
	//	Two important IShape flags must be observed:
	//
	//		IShape::kPrinting		If set, indicates that we are printing.
	//
	//		IShape::kPreviewMode	If set, indicates that we are previewing
	//								printing to the screen, Galley adornments
	//								that do not draw when printing should not
	//								draw for this either
	// 
	virtual bool16 GetCheckIsActive() = 0;
	virtual bool16 GetIsActive(const IParcelShape *parcelShape, const ITextOptions *textOptions, int32 iShapeFlags, ITextLines *textLines) = 0;

	//
	// The Adornment is asked if it could like to draw on the particular run.
	//
	// This is NOT a question about whether the adornment is active or not,
	// rather if an adornment didn't want to draw on any of the runs in a 
	// particular parcel then that adornment would never be called.
	//
	// All non-Galley adornments by definition would like to draw because they
	// are attached to the runs so they never need to be asked this question.
	//
	// This method helps us optimize the calling of Galley adorments which are
	// implemented as "triggers" to things in the Wax. Take, for example, the
	// HnJViolations Galley adornment. It only wants to draw if the WaxLine has
	// HnJViolations AND the appropriate menu pick has occured. So it wants to
	// be able to avoid being called to draw when none of the WaxLines in the
	// frame have any violations even through the menu pick may be active.
	//	
	// NOTE: IWaxRenderData and IWaxGlyphs can be nil, meaning the WaxRun is
	//		 NOT a text run.
	//
	virtual bool16 GetCheckCouldDraw() = 0;
	//virtual bool16 GetCouldDraw(IWaxRun *, IWaxRenderData *, IWaxGlyphs *) = 0;

	//
	// The Adornment is asked if it has ink bounds.
	//
	// Again, this is NOT a question about whether the adornment is active or
	// not, rather if an adornment didn't want to draw on any of the runs in a 
	// particular parcel then that adornment would never be called.
	//
	// If the Adornment never creates ink that exceeds the standard ink bounds
	// of the run (ie the selection bounds) then it does not have to provide
	// ink bounds.
	//
	// NOTE: The inkBounds are passed in empty. If your adornment is guaranteed
	//		 to draw within the Text bounds of the run and the vertical
	//		 selection bounds of the line then you DO NOT have to return
	//		 anything for the inkBounds, just leave them unchanged (empty).
	//
	// NOTE: IWaxRenderData and IWaxGlyphs can be nil, meaning the WaxRun is
	//		 NOT a text run.
	//
	//virtual bool16 GetHasInkBounds() = 0;
	//virtual void GetInkBounds(PMRect *inkBounds, IWaxRun *, IWaxRenderData *, IWaxGlyphs *) = 0;

	//
	// The adornment is allowed to draw.
	//
	// NOTE: IWaxRenderData and IWaxGlyphs can be nil, meaning the WaxRun is
	//		 NOT a text run.
	//
	virtual void Draw(IGraphicsPort* gPort, ITextModel* model, RunDescription* rd, TextIndex runStart, int32 runLength, 
						const PMPoint &drawPt, float * xWidths, const PMReal& displaySize, 
						int32 lineIndex, int32 runIndex, ITextLines *textLines, const PMRect &runRect) = 0;

	//
	// Notification that the Parcel has started/finished the pass.
	//
	// Note that parcelShape MAY NOT be a UID based object.
	//
	//virtual void StartOfParcelDraw(GraphicsData* gd, int32 iShapeFlags, IParcelShape *parcelShape) = 0;
	//virtual void EndOfParcelDraw(GraphicsData* gd, int32 iShapeFlags, IParcelShape *parcelShape) = 0;

};


#endif
