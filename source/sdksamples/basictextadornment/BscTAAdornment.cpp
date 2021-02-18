//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basictextadornment/BscTAAdornment.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "VCPlugInHeaders.h"

// Interfaces:
#include "IAttrReport.h"
#include "IGlobalTextAdornment.h"
#include "IGraphicsPort.h"
#include "ITextAdornment.h"
#include "ITextAdornmentData.h"
#include "IWaxGlyphs.h"
#include "IWaxLineShape.h"
#include "IWaxRenderData.h"
#include "IWaxRun.h"
#include "IWaxGlyphsTOPTransform.h"

// General:
#include "BscTAID.h"
#include "CPMUnknown.h"
#include "PMLineSeg.h"

/**
	Provides a custom character adornment, a shade behind
	the text to which the corresponding custom attribute, introduced
	by the kBscTAAttrBoss, applies.
	See kBscTAAttrBoss and kBscTAAdornmentBoss.

	@ingroup basictextadornment

*/
class BscTAAdornment : public CPMUnknown<ITextAdornment>
{
	public:
		/** Constructor
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		BscTAAdornment(IPMUnknown *boss)
			: CPMUnknown<ITextAdornment>(boss)
		{}

		/** Returns the inkBounds and a flag indicating whether the adornment would draw
			on this run, see ITextAdornment::GetInkBounds.
		*/
		virtual void GetInkBounds(PMRect* inkBounds,
								  const PMRect& runInkBounds,
								  IWaxRun* run,
								  IWaxRenderData* renderData,
								  IWaxGlyphs* glyphs,
								  const ITextAdornmentData* data);

		/** Shade the text to which our character attribute applies,
			see ITextAdornment::GetInkBounds.
		*/
		virtual void Draw(GraphicsData* gd,
						  int32 iShapeFlags,
						  IWaxRun* run,
						  IWaxRenderData* renderData,
						  IWaxGlyphs* glyphs,
						  const ITextAdornmentData* data);

		/** Gets the drawing priority.
			@return the Draw priority of the adornment.
		*/
		virtual Text::DrawPriority GetDrawPriority(void);

		/** The adorned run is splitting: split the given data at the given offset.
			We are not really splitting the adornment, so we simply return nil.

			See ITextAdornment::SplitAt

		*/
		virtual ITextAdornmentData* SplitAt(
				int32 offsetInRun,
				IWaxRun* waxRun, IWaxRun* newWaxRun,
				ITextAdornmentData* data
			);

	protected:

		/**	Gets the run width (helper method).
			@param runGlyphs is the glyph of the wax run.
			@return the width of the run to be shade, adjusted for carriage return
		*/
		static PMReal GetRunWidth(IWaxGlyphs* runGlyphs);

		/**	Check if it is text on path or not
			@param waxRun is the wax line that owns the run.
			@return kTrue if the run is text on path (TOP)
		*/
		bool16 WaxIsPathType(const IWaxRun* waxRun);

		/**
			Figure out the selection path for the TOP, just in case the tags are inserted there
			@param gd is the graphic data that contains the graphic port where all the drawing will occur.
			@param run is the wax line that owns the run.
			@param waxGlyphs stores the identifier and width of each glyph in the run.
			@param selection
			@param index is the index of glyph run.
		*/
		void TOPGlyphSelectionPath(GraphicsData* gd, IWaxRun* run, IWaxGlyphs* waxGlyphs, const PMLineSeg& selection, int32 index);

		/** Draw bounds for one glyph.
			@param gPort
			@param runPosition
			@param position
			@param selection
			@param width
		*/
		void DrawBoundsForOneGlyph(IGraphicsPort* gPort, const PMReal& runPosition, PMMatrix& position, const PMLineSeg& selection, Fixed width);
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(BscTAAdornment, kBscTAAdornmentImpl)


/*	GetInkBounds
*/
void BscTAAdornment::GetInkBounds(
			PMRect* inkBounds,
			const PMRect& runInkBounds,
			IWaxRun* run,
			IWaxRenderData* renderData,
			IWaxGlyphs* glyphs,
			const ITextAdornmentData* data)
{
	TRACEFLOW("BasicTextAdornment", "BscTAAdornment::GetInkBounds()\n");
}

/*	Draw
*/
void BscTAAdornment::Draw(
			GraphicsData* gd,
			int32 flags,
			IWaxRun* run,
			IWaxRenderData* renderData,
			IWaxGlyphs* runGlyphs,
			const ITextAdornmentData* data)
{
	do {

		ASSERT(run);
		if (run == nil) {
			break;
		}

		// check if the run is TOP
		bool16	isTOP = WaxIsPathType(run);

		// Get the line of wax to be hilited.
		const IWaxLine* waxLine = run->GetWaxLine();
		ASSERT(waxLine);
		if (waxLine == nil) {
			break;
		}

		ASSERT(runGlyphs);
		if (runGlyphs == nil) {
			break;
		}
		// Get the width of the run.
		PMReal runWidth = GetRunWidth(runGlyphs);
		if (runWidth <= 0.0) {
			break;
		}

		// Calculate the rect to be hilited.
		PMReal xPosition = run->GetXPosition();
		InterfacePtr<IWaxLineShape> waxLineShape(waxLine, UseDefaultIID());
		ASSERT(waxLineShape);
		if (waxLineShape == nil) {
			break;
		}

		PMLineSeg selection;
		waxLineShape->GetSelectionLine(&selection);

		// Prepare to Draw
		IGraphicsPort* gPort = gd->GetGraphicsPort();
		ASSERT(gPort);
		if (gPort == nil) {
			break;
		}
		const PMReal kGreyLevel(0.8);
		if (isTOP) {
			// text on path
			int32	glyphCount = runGlyphs->GetWaxSpan();
			for (int32 i = 0; i < glyphCount; ++i) {
				TOPGlyphSelectionPath(gd, run, runGlyphs, selection, i);
				gPort->setrgbcolor(kGreyLevel, kGreyLevel, kGreyLevel);
				gPort->fill();
			}
		}
		else {
			gPort->newpath();
			gPort->rectpath(xPosition, selection.Top(), runWidth, selection.DeltaY());
			gPort->setrgbcolor(PMReal(0.8), PMReal(0.8), PMReal(0.8));
			gPort->fill();
		}
	} while (false);

}

/*	GetRunWidth
*/
PMReal BscTAAdornment::GetRunWidth(IWaxGlyphs* runGlyphs)
{
	PMReal runWidth;
	do {
		ASSERT(runGlyphs);
		if (runGlyphs == nil) {
			break;
		}
		// Get the width of the run to be hilited.
		runWidth = runGlyphs->GetWidth();

		// Adjust the width so we don't hilite the
		// paragraph mark that terminates a story.
		int32 numGlyphs = runGlyphs->GetGlyphCount();
		const Text::GlyphID* glyphArray = runGlyphs->PeekGlyphArray();
		const float* widthArray = runGlyphs->PeekWidthsArray();

		if (glyphArray[numGlyphs - 1] == kInvalidGlyphID) {
			runWidth -= widthArray[--numGlyphs];
		}

	} while (false);

	return runWidth;
}

/*	GetDrawPriority
*/
Text::DrawPriority BscTAAdornment::GetDrawPriority(void)
{
	// lowest defined priority (defined in IGlobalTextAdornment.h)
	return kTAPriHnJKeepsViolations;
}

/*	SplitAt
*/
ITextAdornmentData* BscTAAdornment::SplitAt(
				int32 offsetInRun,
				IWaxRun* waxRun, IWaxRun* newWaxRun,
				ITextAdornmentData* data
			)
{
    return nil;
}

/*	WaxIsPathType
*/
bool16 BscTAAdornment::WaxIsPathType(const IWaxRun *waxRun)
{
	//
	// first check if TextOnPath plugin is here
	//
	InterfacePtr<const IWaxGlyphsTOPTransform> iTOPTransform(waxRun, UseDefaultIID() );
	if( iTOPTransform == nil || !iTOPTransform->IsTopRun() )
		return  kFalse;

	//
	// If both arrays are nil, not a text on path run
	//
	const PMMatrix*  pTransformArray = iTOPTransform->PeekGlyphTransformArray();
	const PMPoint*  pOffsetArray = iTOPTransform->PeekSelectionOffsetArray();

	return (pTransformArray && pOffsetArray);
}


/*	DrawBoundsForOneGlyph
*/
void BscTAAdornment::DrawBoundsForOneGlyph(IGraphicsPort* gPort, const PMReal& runPosition, PMMatrix& position, const PMLineSeg& selection, Fixed width)
{
	position.Translate(runPosition, 0);
	PMPoint p1( 0 , selection.Top());
	PMPoint p2(p1.X() + ::ToPMReal(width), p1.Y());
	PMPoint p3(p2.X(), selection.Bottom());
	PMPoint p4(p1.X(), p3.Y());

	position.Transform(&p1);
	position.Transform(&p2);
	position.Transform(&p3);
	position.Transform(&p4);

	gPort->moveto(p1.X(), p1.Y());
	gPort->lineto(p2.X(), p2.Y());
	gPort->lineto(p3.X(), p3.Y());
	gPort->lineto(p4.X(), p4.Y());
	gPort->lineto(p1.X(), p1.Y());
}

/*	TOPGlyphSelectionPath
*/
void BscTAAdornment::TOPGlyphSelectionPath(GraphicsData* gd, IWaxRun *run, IWaxGlyphs *waxGlyphs, const PMLineSeg& selection, int32 index)
{
	if (gd && run && waxGlyphs) {
		InterfacePtr<IGraphicsPort> gPort(gd->GetGraphicsPort(), IID_IGRAPHICSPORT);

		PMReal	yRun;
		PMReal	xRun = run->GetXPosition();
		Fixed*	widthArray = ( Fixed *)waxGlyphs->PeekWidthsArray();
		gPort->newpath();
		PMMatrix position = waxGlyphs->GetGlyphDrawPosition(index);
		DrawBoundsForOneGlyph(gPort, xRun, position, selection, widthArray[index]);

		gPort->closepath();
	}
}

// End, BscTAAdornment.cpp.


