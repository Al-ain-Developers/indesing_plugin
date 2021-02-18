//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/wavetool/SineWaveTracker.cpp $
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
#include "IPathGeometry.h"

// Project includes:
#include "WaveTracker.h"
#include "WavTlID.h"

/** Creates spline page item in the shape of a sine wave along the line 
	dragged by the user's mouse.

	@ingroup wavetool
	
*/
class SineWaveTracker : public WaveTracker
{
	public:
		/** Constructor.
		 */
		SineWaveTracker(IPMUnknown *boss);

		/** Destructor.
		 */
		~SineWaveTracker();

		/** Describes the sine wave path.
		 */
		virtual void MakePath(const PMPoint& startPt, const PMPoint& endPoint, IPathGeometry* pathGeometry);

	private:
		/**	Describes a sine wave path then uses WaveTracker::Transform to move
			orientate and scale the path dependent on the user's
			mouse gestures. 
		 */
		void SineWavePath(const PMPoint& startPt, const PMPoint& endPoint, IPathGeometry* pathGeometry);
};

/*  Make the implementation available to the application.
*/
CREATE_PMINTERFACE(SineWaveTracker, kSineWaveTrackerImpl)

/*
*/
SineWaveTracker::SineWaveTracker(IPMUnknown *boss) :
	WaveTracker(boss)
{
}
		
/*
*/
SineWaveTracker::~SineWaveTracker()
{
}

/*
*/
void SineWaveTracker::MakePath(const PMPoint& startPt, const PMPoint& endPoint, IPathGeometry* pathGeometry)
{
	this->SineWavePath(startPt,endPoint,pathGeometry);
}
	
/*
*/
void SineWaveTracker::SineWavePath(const PMPoint& startPt, const PMPoint& endPoint, IPathGeometry* pathGeometry)
{
	const int32 kWaveHeight = 1;
	const int32 kWaveWidth = 2;
	const int32 kWaveCount = 8;
	const int32 kLength = kWaveWidth * kWaveCount;

	pathGeometry->RemoveAllPaths();
	pathGeometry->AddNewPath();
	pathGeometry->OpenPath(0);
	int32 y = kWaveHeight;
	int32 x = -kWaveWidth/2;
	for (int32 i = 0; i <= kWaveCount; i++)
	{
		PMPathPoint p(
						kCS,						// point type is anchor point with continuing tangent.
						PMPoint(x,y),				// left direction point		
						PMPoint(x+(kWaveWidth/2),0),// anchor point
						PMPoint(x+kWaveWidth,-y)	// right direction point
					 );
		pathGeometry->AddPoint(0, p);
		x = x + kWaveWidth;
		y = -y;
	}
	this->Transform(endPoint, kLength, pathGeometry);
}

// End, SineWaveTracker.cpp.



