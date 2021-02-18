//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IViewPortArbitrator.h $
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
#ifndef __IViewPortArbitrator_h__
#define __IViewPortArbitrator_h__

#include "IPMUnknown.h"
#include "GraphicsID.h"

class IViewPort;
class IRasterPort;

/**
 IViewPortArbitrator is a singleton interface responsible for maintaining the 
 internal stack of view ports.
 
 Warning: This interface is intended for internal use only and may be removed
 in a future release
 
 @see IViewPort
 */
class IViewPortArbitrator : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IVIEWPORTARBITRATOR };
	/**
	 Pushes a port onto the stack of view ports and gives it the focus. The port
	 currently at the top of the stack, if any, is suspended.
	 
	 Note: the arbitrator will not take ownership of the port. The caller is
	 responsible for ensuring that it remains valid until a call to EndPortFocus
	 
	 @param port		IN The port to receive focus
	 @see IViewPort::BeginFocus
	 */
	virtual void 		BeginPortFocus(IViewPort* port) = 0;
	
	/**
	 Removes focus from port, which is assumed to be at the top of the stack, 
	 and pops it from the stack. The port at the top of the stack at this point, 
	 if any, is resumed
	 
	 @param port		IN The port to be removed from the stack
	 @see IViewPort::EndFocus
	 */
	virtual void		EndPortFocus(IViewPort* port) = 0;
	
	/**
	 Gets the port at the top of the port stack, if any. The returned pointer
	 is not AddRef'd
	 
	 @return The port with focus
	 */
	virtual IViewPort*	GetPortInFocus() const = 0;
	
	
	/**
	 Returns a raster based viewport. This viewport is not associated with a window, so any drawing to this port will not appear on screen.
	 Often used to draw into just to check which pixels would be colored by the drawing.
	 
	 @return a global non-marking raster viewport.
	 */
	virtual IRasterPort* QueryNonMarkingRasterViewPort() = 0;

	/**
	 Tells the ViewPortArbitrator to release internal caches. Internal use only.
	 */
	virtual void	ReleaseCaches() = 0;

};

#endif