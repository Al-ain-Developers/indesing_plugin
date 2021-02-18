//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/singlelinecomposer/SLCLineMetrics.h $
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

#ifndef __SLCLineMetrics_h__
#define __SLCLineMetrics_h__

#include "Trace.h"
#include "IParcel.h"

/** Tracks metrics during composition of the line. The maximum value in the 
	line of metrics such as leading, ascent and cap height are tracked 
	during composition.

	The maximum value for leading is used to set the height of the line. 

	The maximum value of the appropriate metric is used to set the line height
	when the line falls at the top of a parcel. The offset of the first line
	of text in a parcel can be varied by a parameter called "first line offset",
	often abbreviated to FLO. This can take one of a number of metrics
	e.g. leading, ascent, cap height. Because of this the value of all of 
	these matrics must be tracked as the line is composed.

	kFLOFixedHeight note: We don't need to track the value of this metric
	as the line is composed. Fixed height is a property of the parcel
	that is not affected by the metrics of the text in the parcel. The tiler 
	handles kFLOFixedHeight. All we need to ensure is that we pass in a 
	non zero value for the top of frame height when asking for tiles. Fudge 
	this by maintaining the kFLOFixedHeight to be the same as ascent.
	 
  	@ingroup singlelinecomposer
    
*/
class SLCLineMetrics
{
public:
	/** Default Constructor.
	*/
	SLCLineMetrics(void)
	{
		SetLeading(0.0);
		SetAscent(0.0);
		SetCapHeight(0.0);
		SetXHeight(0.0);
	};

	/** Copy constructor.
	*/
	SLCLineMetrics(const SLCLineMetrics& h)
	{
		SetLeading(h.GetLeading());
		SetAscent(h.GetAscent());
		SetCapHeight(h.GetCapHeight());
		SetXHeight(h.GetXHeight());
	};

	/** Assignment operator.
	*/
	SLCLineMetrics& operator=(const SLCLineMetrics& h)
	{
		if (this != &h)
		{
			SetLeading(h.GetLeading());
			SetAscent(h.GetAscent());
			SetCapHeight(h.GetCapHeight());
			SetXHeight(h.GetXHeight());
		}
		return *this;
	};

	/** The value stored here by the composer is the maximum value 
		of all runs in the line.
	*/
	void SetLeading(const PMReal& leading)
	{
		fLineHeightMetricValues [Text::kFLOLeading] = leading;
	};

	/** Gets the leading value
	*/
	const PMReal& GetLeading(void) const
	{
		return fLineHeightMetricValues [Text::kFLOLeading];
	};

	/** The value stored here by the composer is the maximum value 
		of all runs in the line.
	*/
	void SetAscent(const PMReal& ascent) 
	{
		fLineHeightMetricValues [Text::kFLOAscent] = ascent; 
		// kFLOFixedHeight note: Fudge to ensure we pass
		// in a non zero value for the top of frame height when asking for tiles.
		// FixedHeight is a property of the parcel that is not affected by the
		// metrics of the text in the parcel.
		fLineHeightMetricValues [Text::kFLOFixedHeight] = ascent; 
	};

	/** Gets the ascent value.
	*/
	const PMReal& GetAscent(void) const
	{
		return fLineHeightMetricValues [Text::kFLOAscent];
	};

	/** The value stored here by the composer is the maximum value 
		of all runs in the line.
	*/
	void SetCapHeight(const PMReal& capHeight)
	{
		fLineHeightMetricValues [Text::kFLOCapHeight] = capHeight;
	};

	/** Gets the cap height
	*/
	const PMReal& GetCapHeight(void) const
	{
		return fLineHeightMetricValues [Text::kFLOCapHeight];
	};

	/** The value stored here by the composer is the maximum value 
		of all runs in the line.
	*/
	void SetXHeight(const PMReal& xHeight)
	{
		fLineHeightMetricValues [Text::kFLOxHeight] = xHeight;
	};

	/** Gets the "X" height.
	*/
	const PMReal& GetXHeight(void) const
	{
		return fLineHeightMetricValues [Text::kFLOxHeight];
	};

	/** Get the value of the given metric.
		@param metric IN the desired metric (leading or whatever).
		@return the value of the given metric.
	*/
	const PMReal& GetValue(const Text::FirstLineOffsetMetric& metric) const 
	{
		ASSERT_MSG(metric <= Text::kFLOFixedHeight, "Invalid metric");
		if (metric <= Text::kFLOFixedHeight)
		{
			return fLineHeightMetricValues [metric];            
		}
		return fLineHeightMetricValues [Text::kFLOLeading]; 
	};

	/** Dump the object to Trace.
	*/
	void Dump(const char* category, const char* msg)
	{
		TRACEFLOW(category, "%s leading %f, ascent %f, capHeight %f, xHeight %f\n",
				  msg,
				  ::ToDouble(GetLeading()),
				  ::ToDouble(GetAscent()),
				  ::ToDouble(GetCapHeight()),
				  ::ToDouble(GetXHeight())
				 );
	};
private:
	/** Stored in an array that parallels the metrics defined in CTextEnum.h.
	*/
	PMReal fLineHeightMetricValues [Text::kFLOCount];
};

#endif // __SLCLineMetrics__

// End of File SLCLineMetrics.h

