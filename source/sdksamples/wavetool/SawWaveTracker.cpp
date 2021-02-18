//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/wavetool/SawWaveTracker.cpp $
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

// General includes:
#include "PMMatrix.h"

// Project includes:
#include "WaveTracker.h"
#include "WavTlID.h"

/** Creates spline page item in the shape of a saw tooth wave along the line 
	dragged by the user's mouse.

	@ingroup wavetool
	
 */
class SawWaveTracker : public WaveTracker
{
	public:
		/** Constructor
		 */
		SawWaveTracker(IPMUnknown *boss);

		/** Destructor.
		*/
		~SawWaveTracker();

		/** Describes the saw wave path.
		*/
		virtual void MakePath(const PMPoint& startPt, const PMPoint& endPoint, IPathGeometry* pathGeometry);

	private:
		/** Describes a saw tooth path then uses Transform to move
			orientate and scale the path dependent on the user's
			mouse gestures.
		*/
		void SawToothPath(const PMPoint& startPt, const PMPoint& endPoint, IPathGeometry* pathGeometry);

		/** Describes a box then uses Transform to move
			orientate and scale the path dependent on the user's
			mouse gestures. To try this code out modify MakePath to
			call it.
		*/
		void ScaledBoxOnDragLine(const PMPoint& startPt, const PMPoint& endPoint, IPathGeometry* pathGeometry);
};

/* Make the implementation available to the application.
*/
CREATE_PMINTERFACE(SawWaveTracker, kSawWaveTrackerImpl)

/*
*/
SawWaveTracker::SawWaveTracker(IPMUnknown *boss) :
	WaveTracker(boss)
{
}
		
/*
*/
SawWaveTracker::~SawWaveTracker()
{
}
	
/*
*/
void SawWaveTracker::MakePath(const PMPoint& startPt, const PMPoint& endPoint, IPathGeometry* pathGeometry)
{
	this->SawToothPath(startPt, endPoint, pathGeometry);
}

/*
*/
void SawWaveTracker::SawToothPath(const PMPoint& startPt, const PMPoint& endPoint, IPathGeometry* pathGeometry)
{
	const int32 kWaveHeight = 1;
	const int32 kWaveWidth = 2;
	const int32 kWaveCount = 8;
	const int32 kLength = kWaveWidth * kWaveCount;

	pathGeometry->RemoveAllPaths();
	pathGeometry->AddNewPath();
	pathGeometry->OpenPath(0);
	pathGeometry->AddPoint(0, PMPathPoint(PMPoint(0,0)));
	int32 y = -kWaveHeight;
	int32 x = kWaveWidth/2;
	for (int32 i = 0; i < kWaveCount; i++)
	{
		pathGeometry->AddPoint(0,PMPathPoint(PMPoint(x,y)));
		x = x + kWaveWidth;
		y = -y;
	}
	pathGeometry->AddPoint(0, PMPathPoint(PMPoint(kLength,0)));
	this->Transform(endPoint, kLength, pathGeometry);
}
	
/*
*/
void SawWaveTracker::ScaledBoxOnDragLine(const PMPoint& startPt, const PMPoint& endPoint, IPathGeometry* pathGeometry)
{
	const int32 kBoxWidth=100;
	pathGeometry->RemoveAllPaths();
	pathGeometry->AddNewPath();
	pathGeometry->OpenPath(0);
	PMPoint p1(kBoxWidth/2,kBoxWidth/2);
	PMPoint p2(-kBoxWidth/2,kBoxWidth/2);
	PMPoint p3(-kBoxWidth/2,-kBoxWidth/2);
	PMPoint p4(kBoxWidth/2,-kBoxWidth/2);
	pathGeometry->AddPoint(0,PMPathPoint(p1));
	pathGeometry->AddPoint(0,PMPathPoint(p2));	
	pathGeometry->AddPoint(0,PMPathPoint(p3));
	pathGeometry->AddPoint(0,PMPathPoint(p4));
	pathGeometry->ClosePath(0);
	this->Transform(endPoint, kBoxWidth, pathGeometry);
}

// End, SawWaveTracker.cpp.



