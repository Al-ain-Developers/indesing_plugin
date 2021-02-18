//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/AGMGraphicsContextWith.h $
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
#ifndef __AGMGraphicsContextWith__
#define __AGMGraphicsContextWith__

#include "IGraphicsContext.h"
#include "AcquireViewPort.h"
#include "K2Assert.h"
#include "IDVOffscreenPortData.h"

class IControlView;
class IViewPort;
class ITransform;
class IGraphicsContext;
class PMMatrix;

/**
 A class template that sets up the coordinate system and clip for a given view 
 or view port. The template requires two parameters, a class that sets up the
 coordinate system and a class that sets up the clip. By using different 
 implementations for these you can build a graphic context for AGM on Mac, AGM 
 on Win, Quickdraw on Mac, or GDI on Win.
 
 The various constructor overrides allow flexibility in how the graphics 
 context is to be set up. Each installs this context as the current context in
 the graphics context arbitrator's stack of graphics contexts. The destructor
 then restores the prior context.
 
 @see IGraphicsContext
 @see IGraphicsContextArbitrator
 */
template <class AcquireCoordSys, class AcquireClip>
class AGMGraphicsContextWith : public IGraphicsContext
{
public:

	// ----- Initialization -----

#if 0 // OBSOLETE
	/** 
	 OBSOLETE AS OF CC - this API was based on direct drawing into a cached WindowPort.
	   For geometry calculations only (i.e. no drawing), NonMarkingAGMGraphicsContext should be used instead.
	   For cases where drawing took place consider: Invalidate or ForceRedraw from IControlView.
	 */
	AGMGraphicsContextWith(IControlView *controlView, SysRgn clipRgn = nil);
#endif
	
	/**
	 Constructs a graphics context based on a viewport, a control view, and an
	 optional clip region
	 
	 @param viewPort		IN The view port to base the context on
	 @param controlView		IN The control view to base the context on
	 @param clipRgn			IN The clipping region to use
	 @see IViewPort
	 @see IControlView
	 */
	AGMGraphicsContextWith(IViewPort* viewPort, IControlView *controlView, SysRgn clipRgn = nil);

	/**
	 Constructs a graphics context based on a viewport, a control view, and an
	 optional clip region
	 
	 @param viewPort		IN The view port to base the context on
	 @param xform			IN The optional transform to use
	 @param clipRgn			IN The clipping region to use
	 @see IViewPort
	 @see ITransform
	 */
	AGMGraphicsContextWith(IViewPort* viewPort, ITransform* xform = nil, SysRgn clipRgn = nil);
	
	/**
	 Constructs a graphics context based on a viewport, a matrix, and an optional
	 clip region
	 
	 @param viewPort		IN The view port to base the context on
	 @param theMatrix		IN The matrix to apply
	 @param clipRgn			IN The clipping region to use
	 @see IViewPort
	 */
	AGMGraphicsContextWith(IViewPort* viewPort, const PMMatrix& theMatrix, SysRgn clipRgn = nil);

	/**
	 Constructs a graphics context based on a viewport, a matrix, a control view,
	 and an optional clip region
	 
	 @param viewPort		IN The view port to base the context on
	 @param theMatrix		IN The matrix to apply
	 @param controlView		IN The control view to base the context on
	 @param clipRgn			IN The clipping region to use
	 @see IViewPort
	 @see IControlView
	 */
	AGMGraphicsContextWith(IViewPort* viewPort, const PMMatrix& theMatrix, IControlView *controlView, SysRgn clipRgn = nil);

	/**
	 Constructs a graphics context based on a viewport, a transform, a control view,
	 and an optional clip region
	 
	 @param viewPort		IN The view port to base the context on
	 @param xform			IN The transform to apply
	 @param controlView		IN The control view to base the context on
	 @param clipRgn			IN The clipping region to use
	 @see IViewPort
	 @see IControlView
	 */
	AGMGraphicsContextWith(IViewPort* viewPort, ITransform* xform, IControlView *controlView, SysRgn clipRgn = nil);
	
	/**
	 Destructs this graphics context
	 */
	virtual ~AGMGraphicsContextWith();

	// ----- Clipping -----
	
	/**
	 Gets the clipping region for this context
	 
	 @return The clip region
	 */
	virtual SysRgn				GetClip() const;
	
	/**
	 Gets the clipping region for this context, adjusted for the origin
	 
	 @return The origin-adjusted clip region
	 */
	virtual SysRgn				GetOriginAdjustedClip() const;

	// ----- Accessors -----
	
	/** Obsolete don't use
	 
	 Gets the system port for this graphics context
	 
	 @return The system port
	 */
	virtual SysPort				GetSysPort() const;
	
	/**
	 Gets the view port interface for this graphics context
	 
	 @return the view port
	 @see IViewPort
	 */
	virtual IViewPort*			GetViewPort() const;
	
	/**
	 Gets the transform matrix for this graphics context
	 
	 @return the transform matrix
	 */
	virtual const PMMatrix&		GetContentToViewTransform() const;

	/**
	 Gets the inverse transform matrix for this graphics context
	 
	 @return the inverse transform matrix
	 */
	virtual const PMMatrix&		GetViewToContentTransform() const;
	
	/**
	 Gets the control view for this graphics context, if any
	 
	 @return the control view
	 @see IControlView
	 */
	virtual IControlView*		GetView() const;

	/**
	 Gets the 'is current' flag for this graphics context. The context is 
	 current if it matches the current context maintained by the graphics 
	 context arbitrator
	 
	 @return kTrue if this graphics context is current
	 @see IGraphicsContextArbitrator
	 */
	bool16						IsCurrent() const;

	/** Internal use only */
	virtual dvaui::drawbot::Drawbot* GetDrawbot() const
	{
		InterfacePtr<IDVOffscreenPortData> offscreenPortData(this->GetViewPort(), IID_IDVOFFSCREENPORTDATA);
		if(offscreenPortData)
		{
			return offscreenPortData->GetDrawbot();
		}
		return NULL;
	}

private:

	// ----- Data fields -----
	
	// ----- Order is important. We need to acquire the view port, followed by the coordinate
	//		 system followed by the clip. [amb]
	
	InterfacePtr<IViewPort>		fVP;
	AcquireViewPort				fAcquireVP;
	AcquireCoordSys				fAcquireCoordSys;
	AcquireClip					fAcquireClip;
};

template <class AcquireCoordSys, class AcquireClip>
inline SysRgn AGMGraphicsContextWith<AcquireCoordSys, AcquireClip>::GetClip() const
{
	return fAcquireClip.GetClip();
}

template <class AcquireCoordSys, class AcquireClip>
inline SysRgn AGMGraphicsContextWith<AcquireCoordSys, AcquireClip>::GetOriginAdjustedClip() const
{
	return fAcquireClip.GetOriginAdjustedClip();
}

/**
 Obsolete don't use
 
 It will cause a assert if called
 */
template <class AcquireCoordSys, class AcquireClip>
inline SysPort AGMGraphicsContextWith<AcquireCoordSys, AcquireClip>::GetSysPort() const
{
	return nil;
}

template <class AcquireCoordSys, class AcquireClip>
inline IViewPort* AGMGraphicsContextWith<AcquireCoordSys, AcquireClip>::GetViewPort() const
{
	return fAcquireCoordSys.GetViewPort();
}

template <class AcquireCoordSys, class AcquireClip>
inline const PMMatrix& AGMGraphicsContextWith<AcquireCoordSys, AcquireClip>::GetContentToViewTransform() const
{
	return fAcquireCoordSys.GetTransform();
}

template <class AcquireCoordSys, class AcquireClip>
inline const PMMatrix& AGMGraphicsContextWith<AcquireCoordSys, AcquireClip>::GetViewToContentTransform() const
{
	return fAcquireCoordSys.GetInverseTransform();
}

template <class AcquireCoordSys, class AcquireClip>
inline IControlView* AGMGraphicsContextWith<AcquireCoordSys, AcquireClip>::GetView() const
{
	return fAcquireCoordSys.GetView();
}

#ifdef _INCLUDE_TPP_IN_H_
	#include "AGMGraphicsContextWith.tpp"
#endif //_INCLUDE_TPP_IN_H_
#endif
