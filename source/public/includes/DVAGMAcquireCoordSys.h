//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/DVAGMAcquireCoordSys.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __DVAGMAcquireCoordSys__
#define __DVAGMAcquireCoordSys__

#include "CAGMAcquireCoordSys.h"
#include "DVAForwardDeclarations.h"

#ifdef PUBLIC_BUILD
#pragma export on
#endif

/**
 An object that sets up the coordinate system for a view or viewport. To be 
 used when you want to draw using AGM. This is usually not used standalone 
 but as a template parameter to AGMGraphicsContextWith.
 
 @see AGMGraphicsContext.h
 */
class PUBLIC_DECL DVAGMAcquireCoordSys : public CAGMAcquireCoordSys
{
public:
	// ----- Initialization -----
	
	/**
	 Constructs a coordinate system acquisition object based on a viewport 
	 and a control view

	 @param viewPort	The viewport to base the coordinate system on
	 @param controlView	The control view to base the coordinate system on
	 */
	DVAGMAcquireCoordSys(IViewPort* viewPort, IControlView *controlView);
	
	/**
	 Constructs a coordinate system acquisition object based on a viewport 
	 and an optional transform
	 
	 @param viewPort	The viewport to base the coordinate system on
	 @param xform		The transform to base the coordinate system on
	 */
	DVAGMAcquireCoordSys(IViewPort* viewPort, ITransform* xform = nil);
	
	/**
	 Constructs a coordinate system acquisition object based on a viewport, 
	 a transform, and a control view
	 
	 @param viewPort	The viewport to base the coordinate system on
	 @param xform		The transform to base the coordinate system on
	 @param controlView	The control view to base the coordinate system on
	 */
	DVAGMAcquireCoordSys(IViewPort* viewPort, ITransform* xform, IControlView* controlView);
	
	/**
	 Constructs a coordinate system acquisition object based on a viewport 
	 and a matrix
	 
	 @param viewPort	The viewport to base the coordinate system on
	 @param theMatrix	The matrix to base the coordinate system on
	 */
	DVAGMAcquireCoordSys(IViewPort* viewPort, const PMMatrix& theMatrix);
	
	/**
	 Constructs a coordinate system acquisition object based on a viewport, 
	 a matrix, and a control view
	 
	 @param viewPort	The viewport to base the coordinate system on
	 @param theMatrix	The matrix to base the coordinate system on
	 @param controlView	The control view to base the coordinate system on
	 */
	DVAGMAcquireCoordSys(IViewPort* viewPort, const PMMatrix& theMatrix, IControlView* controlView);
	
	/**
	 Destructor
	 */
	~DVAGMAcquireCoordSys();
	
protected:
	/**
	 Sets up the system coordinate system origin
	 */
	virtual void		SetupSysOrigin();
	
	/**
	 Tears down the system coordinate system origin
	 */
	virtual void		TearDownSysOrigin();

private:
	
	/**
	 Gets the system port for this graphics context
	 
	 @return The system port
	 */
	dvaui::drawbot::Drawbot *	GetSysPort() const;
};

#pragma export off

#endif
