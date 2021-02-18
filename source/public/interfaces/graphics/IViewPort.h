//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IViewPort.h $
//  
//  Owner: jack_kirstein
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
#ifndef __IVIEWPORT__
#define __IVIEWPORT__

#include "GraphicsID.h"

/**
 IViewPort serves as a generic "handle" to a viewport boss.
 
 @see IViewPortArbitrator
 */
class IViewPort : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IVIEWPORT };
	
	/** The port's focus state */
	enum FocusState { kNotInFocus, kInFocus, kInFocusSuspended };
	
public:
	/**
	 Sets the port's owner. This may be any interface
	 
	 Note: Internal implementations do not take ownership of owner and will 
	 not call AddRef or Release on it
	 
	 @param owner	IN The port's owner
	 */
	virtual void 			SetOwner(IPMUnknown *owner) = 0;
	
	/**
	 Gets the port's owner. This may be any interface
	 
	 @return The port's owner
	 */
	virtual IPMUnknown*		GetOwner() = 0;

	/**
	 Called when this port becomes the target of graphic operations. This is 
	 called by the raster port arbitrator in its BeginPortFocus implementation.
	 
	 @see IViewPortArbitrator::BeginPortFocus
	 */
	virtual void			BeginFocus() = 0;
	
	/**
	 Called when this port is torn down by the raster port arbitrator. This is 
	 called by the raster port arbitrator in its EndPortFocus implementation.
	 
	 @see ViewPortArbitrator::EndPortFocus
	 */
	virtual void			EndFocus() = 0;

	/**
	 Called when this port has the focus and another port is about to receive
	 the focus
	 
	 @see IViewPortArbitrator::BeginPortFocus
	 */	 
	virtual void			SuspendFocus() = 0;
	
	/**
	 Called when this port is suspended and is once again about to receive the
	 focus

	 @see ViewPortArbitrator::EndPortFocus
	 */
	virtual void			ResumeFocus() = 0;
	
	/**
	 Returns the port's focus state
	 
	 @return the focus state
	 @see IViewPort::FocusState
	 */
	virtual FocusState		GetFocusState() const = 0;
};
#endif