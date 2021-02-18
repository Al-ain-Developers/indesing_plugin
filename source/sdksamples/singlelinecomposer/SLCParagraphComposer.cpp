//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/singlelinecomposer/SLCParagraphComposer.cpp $
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

// Interface includes:
#include "IComposeScanner.h"
#include "IParagraphComposer.h"
//#include "ITextModel.h"

// General includes:
#include "CPMUnknown.h"
#include "textiterator.h"

// Project includes:
#include "SLC.h"
#include "SLCID.h"
#include "SLCLineMetrics.h"
#include "SLCTileMeasure.h"
#include "SLCGlyphNode.h"
#include "SLCTileManager.h"
#include "SLCGlyphNodeList.h"
#include "SLCLineBreaker.h"
#include "SLCLineFitter.h"


/** Composes a single line of text and as output generates a wax line (IWaxLine) 
	and associated wax runs (IWaxRun).

	There are two distinct roles that a paragraph composer(IParagraphComposer)
	performs:
	<ol>
	<li>Positioning the line and, if necessary, deciding where the text in the 
	line should break. This information is represented persistently in the 
	wax line. In this implementation this role is delegated by the Recompose
	method to SLCLineBreaker. <b><i>Features that affect line break decisions,
	hyphenation for example, belong here.</i></b>
	<li>Positioning glyphs in the line and, if necessary, adjusting their width. 
	This information is represented by a set of wax runs associated with 
	the wax line. Wax runs are not persistent and must be rebuilt for 
	display when a wax line is read from disc. In this implementation 
	this role is delegated by the RebuildLineToFit method to SLCLineFitter.
	<b><i>Features that affect glyph position, centre alignment, justification,
	word spacing, letter spacing, kerning for example, belong here.</i></b>
	</ol>

	Features supported by this implementation:
	<ul>
	<li>Roman text composition(baseline, leading, ascent, cap height);
	<li>Paragraph left indent, right indent and first line left indent;
	<li>Baseline grid alignment;
	<li>Unencoded glyphs(fonts with glyphs that have no corresponding Unicode character code);
	<li>Proportional width adjustment of trailing white space in the line;
	<li>Text wrap;
	<li>First baseline offset(allows the offset from top of a parcel to the first baseline
	 of text in the parcel to be controlled).
	 </ul>

	This implementation shows the basics involved in the composition of 
	Roman text. A production quality implementation would have to account
	for many more features (e.g. hyphenation, justification, kerning etc.).

  	@ingroup singlelinecomposer
  	
	@see SLCLineBreaker
	@see SLCLineFitter
	@see IWaxLine
	@see IWaxRun
*/
class SLCParagraphComposer : public CPMUnknown<IParagraphComposer>
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	SLCParagraphComposer(IPMUnknown* boss);

	/**
		Destructor
	*/
	virtual ~SLCParagraphComposer(void);

	/** Build IWaxLines using the specified helper.
	 * 	@param helper IN provides information to drive recomposition
	 * 	@return kTrue if the composer applied at least one line into the helper, 
	 * 		kFalse otherwise.
	*/
	virtual bool16 Recompose(IParagraphComposer::RecomposeHelper* helper);

	/*This is used to regenerate composed text data from the minimal data
	 * 	stored on disk. Can assume that the run consists of only characters
	 * 	of the same style (as reported). It is ok to return kFalse and not 
	 * 	do anything.
	 * 	@param helper IN provides information to drive the rebuild.
	 * 	@return kTrue if the composer rebuild the line, 
	 * 		kFalse otherwise.
	*/
	virtual bool16  RebuildLineToFit (IParagraphComposer::RebuildHelper* helper);
    
    virtual bool16 RebuildLineWithOverrides(IParagraphComposer::RebuildHelper* helper, const AttributeBossList *overrides, bool16 clearOverrides = kFalse){return kFalse;}
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(SLCParagraphComposer, kSLCParagraphComposerImpl)

/* Constructor.
*/
SLCParagraphComposer::SLCParagraphComposer(IPMUnknown* boss) 
: CPMUnknown<IParagraphComposer>(boss)
{
}

/* Destructor.
*/
SLCParagraphComposer::~SLCParagraphComposer(void)	
{
}

/*
*/
bool16 SLCParagraphComposer::Recompose(IParagraphComposer::RecomposeHelper* helper)
{
	bool16 result = kFalse;
	do
	{
		if (helper == nil)
		{
			ASSERT(helper);
			break;
		}

		TRACEFLOW("SingleLineComposer", "\nSingleline recompose requested at %d\n", helper->GetStartingTextIndex());

		SLCLineBreaker lineBreaker;
		result = lineBreaker.Recompose(helper);

	} while (false);
	return result;
}

/* RebuildLineToFit
*/
bool16 SLCParagraphComposer::RebuildLineToFit(IParagraphComposer::RebuildHelper* helper)
{
	bool16 result = kFalse;
	do
	{
		ASSERT(helper);
		if(!helper) {
			break;
		}

		SLCLineFitter lineFitter;
		result = lineFitter.RebuildLineToFit(helper);

	} while (false);
	return result;
}

// End, SLCParagraphComposer.cpp.

