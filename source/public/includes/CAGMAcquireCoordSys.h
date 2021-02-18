//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CAGMAcquireCoordSys.h $
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
#ifndef __CAGMAcquireCoordSys__
#define __CAGMAcquireCoordSys__

#include "CAcquireCoordSys.h"
#include "PMMatrix.h"

#ifdef PUBLIC_BUILD
#pragma export on
#endif

class IControlView;
class IViewPort;
class ITransform;

/**
 An object that sets up the coordinate system for a given view or port. This is 
 usually not used standalone but as a template parameter to AGMGraphicsContextWith.
 
 @see AGMGraphicsContextWith
 */
class PUBLIC_DECL CAGMAcquireCoordSys : public CAcquireCoordSys
{
public:

	// ----- Initialization -----
	
	/**
	 Constructs a coordinate system acquisition object based on a viewport 
	 and a control view

	 @param viewPort	The viewport to base the coordinate system on
	 @param controlView	The control view to base the coordinate system on
	 */
	CAGMAcquireCoordSys(IViewPort* viewPort, IControlView *controlView);

	/**
	 Constructs a coordinate system acquisition object based on a viewport 
	 and an optional transform

	 @param viewPort	The viewport to base the coordinate system on
	 @param xform		The transform to base the coordinate system on
	 */
	CAGMAcquireCoordSys(IViewPort* viewPort, ITransform* xform = nil);

	/**
	 Constructs a coordinate system acquisition object based on a viewport 
	 and a matrix

	 @param viewPort	The viewport to base the coordinate system on
	 @param theMatrix	The matrix to base the coordinate system on
	 */
	CAGMAcquireCoordSys(IViewPort* viewPort, const PMMatrix& theMatrix);

	/**
	 Constructs a coordinate system acquisition object based on a viewport, 
	 a matrix, and a control view

	 @param viewPort	The viewport to base the coordinate system on
	 @param theMatrix	The matrix to base the coordinate system on
	 @param controlView	The control view to base the coordinate system on
	 */
	CAGMAcquireCoordSys(IViewPort* viewPort, const PMMatrix& theMatrix, IControlView* controlView);

	/**
	 Constructs a coordinate system acquisition object based on a viewport, 
	 a transform, and a control view

	 @param viewPort	The viewport to base the coordinate system on
	 @param xform		The transform to base the coordinate system on
	 @param controlView	The control view to base the coordinate system on
	 */
	CAGMAcquireCoordSys(IViewPort* viewPort, ITransform* xform, IControlView* controlView);

	/**
	 Destructor
	 */
	~CAGMAcquireCoordSys();
		

	// ----- Accessors -----
	
	/**
	 Returns the viewport used to construct this object
	 */
	IViewPort*		GetViewPort() const;

	/**
	 Returns the matrix used to construct this object
	 */
	const PMMatrix&	GetTransform() const;

	/**
	 Returns the inverse of the matrix used to construct this object
	 */
	const PMMatrix&	GetInverseTransform() const;

	/**
	 Returns the control view used to construct this object
	 */
	IControlView*	GetView() const;

protected:
	/**
	 Common initialization routine
	 */
	void					CommonInit();
	
	/**
	 Common termination routine
	 */
	void					CommonTerm();

	/**
	 Called when this object is made the current coordinate system acquisition object
	 */
	virtual void			Resume();
	
	/**
	 Called when another object is made the current coordinate system acquisition object
	 */
	virtual void			Suspend();

	/**
	 Sets port's coordinate system
	 */
	void					Setup();
	
	/**
	 Tears down port's coordinate system
	 */
	void					TearDown();

	/**
	 Sets up the system coordinate system origin
	 */
	virtual void			SetupSysOrigin() = 0;

	/**
	 Tears down the system coordinate system origin
	 */
	virtual void			TearDownSysOrigin() = 0;

	// ----- Data fields -----
	
	IViewPort* 			fVP;
	PMMatrix			fXForm;
	PMMatrix			fInvXForm;
	bool16				fInverseValid;
	IControlView*		fView;
	PMMatrix			fOrigMatrix;
};

#pragma export off

inline IViewPort* CAGMAcquireCoordSys::GetViewPort() const
{
	return fVP;
}

inline const PMMatrix& CAGMAcquireCoordSys::GetTransform() const
{
	return fXForm;
}

inline IControlView* CAGMAcquireCoordSys::GetView() const
{
	return fView;
}

#endif
