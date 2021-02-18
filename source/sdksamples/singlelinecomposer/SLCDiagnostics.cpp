//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/singlelinecomposer/SLCDiagnostics.cpp $
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
#include "IWaxLine.h"
#include "IWaxRun.h"
#include "IWaxGlyphs.h"

// General includes:
#include "Trace.h"

// Project includes:
#include "SLCDiagnostics.h"


/* DumpWaxLine
*/
void SLCDiagnostics::DumpWaxLine(const char* category, const IWaxLine* waxLine) const
{
	TRACEFLOW(category, "SLCDiagnostics::DumpWaxLine()-->In\n");
	TRACEFLOW(category, "# GetXPosition, GetTargetWidth, GetTextSpanInTile\n");
	for (int32 i = 0; i < waxLine->GetNumberOfTiles(); i++)
	{
		TRACEFLOW(category, "%d, %f, %f, %d\n",
				  i,
				  ::ToDouble(waxLine->GetXPosition(i)),
				  ::ToDouble(waxLine->GetTargetWidth(i)),
				  waxLine->GetTextSpanInTile(i)); 
	}
	TRACEFLOW(category, "GetYPosition=%f, GetLineHeight=%f, GetTOFLineHeightMetric=%d, GetTOFLineHeight=%f\n",
			  ::ToDouble(waxLine->GetYPosition()),
			  ::ToDouble(waxLine->GetLineHeight()),
			  waxLine->GetTOFLineHeightMetric(),
			  ::ToDouble(waxLine->GetTOFLineHeight()));
#ifdef DEBUG
	PMString parcelStr = waxLine->GetParcelKey().ToDec();
#else
	PMString parcelStr("<unknown>");
#endif
	TRACEFLOW(category, "GetLeadingModel=%d, GetGridAlignmentMetric=%d, GetGridAlignmentMetricOffset=%f, GetParcelKey=%s\n",
			  waxLine->GetLeadingModel(),
			  waxLine->GetGridAlignmentMetric(),
			  ::ToDouble(waxLine->GetGridAlignmentMetricOffset()),
			  parcelStr.GetUTF8String().c_str());
	TRACEFLOW(category, "GetAtTOF=%d, GetParcelPositionDependent=%d, GetNoShuffle=%d\n",
			  waxLine->GetAtTOF(),
			  waxLine->GetParcelPositionDependent(),
			  waxLine->GetNoShuffle());
	TRACEFLOW(category, "SLCDiagnostics::DumpWaxLine()-->Out\n");
}

/* DumpWaxLineAndRuns
*/
void SLCDiagnostics::DumpWaxLineAndRuns(const char* category, const IWaxLine* line, int32 index) const
{
	TRACEFLOW(category, "Wax   |  #    |  X Pos  |  Y Pos  |  Width  |  Span  |\n");

	char indexBuf [32];
	if (index == -1)
	{
		sprintf(indexBuf, "    ");
	}
	else
	{
		sprintf(indexBuf, "%4d", index);
	}

	TRACEFLOW(category, "Line |  %s |  %-6.1f |  %-6.1f |  %-6.1f |  %-5d |\n",
			  indexBuf,
			  ::ToDouble(line->GetXPosition()),
			  ::ToDouble(line->GetYPosition()),
			  ::ToDouble(line->GetWidth()),
			  line->GetTextSpan()
			 );

	int32 runCount = line->GetRunCount();
	for (int32 i = 0; i< runCount; i++)
	{
		InterfacePtr<IWaxRun> run(line->QueryRun(i));
		this->DumpWaxRun(category, run, i);
	}
}

/* DumpWaxRun
*/
void SLCDiagnostics::DumpWaxRun(const char* category, const IWaxRun* run, int32 index) const
{
	InterfacePtr<IWaxGlyphs> glyphs(run, IID_IWAXGLYPHS);

	char indexBuf [32];
	if (index == -1)
	{
		sprintf(indexBuf, "    ");
	}
	else
	{
		sprintf(indexBuf, "%4d", index);
	}

	TRACEFLOW(category, " Run |  %s |  %-6.1f |  %-6.1f |  %-6.1f |  %-5d |             |\n",
			  indexBuf,
			  ::ToDouble(run->GetXPosition()),
			  ::ToDouble(run->GetYPosition()),
			  ::ToDouble(glyphs->GetWidth()),
			  glyphs->GetWaxSpan()
			 );
}

// End, SLCDiagnostics.cpp.

