//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/ShellGraphicsContext.h $
//  
//  Owner: Brendan O'Shea
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
#ifndef __ShellGraphicsContext__
#define __ShellGraphicsContext__

#include "IGraphicsContext.h"
#include "K2Assert.h"
#include "PMMatrix.h"

class IControlView;
class IViewPort;
class ITransform;

#ifdef PUBLIC_BUILD
#pragma export on
#endif


//========================================================================================
// CLASS ShellGraphicsContext - A shell around an IGraphicsContext, holds the passed in
//								constructor parameters & returns them when asked. Most useful
//								for taking an existing AGMGraphicsContext & applying some
//								transformation to it (e.g. master pages).
//========================================================================================

class PUBLIC_DECL ShellGraphicsContext : public IGraphicsContext
{
public:

	// ----- Initialization -----
	
	ShellGraphicsContext(SysRgn clipRgn, SysRgn originAdjustedClip,
						SysPort	sysPort, IViewPort* viewPort, 
						ITransform* xform, IControlView *controlView);
						
	ShellGraphicsContext(SysRgn clipRgn, SysRgn originAdjustedClip,
						SysPort	sysPort, IViewPort* viewPort, 
						const PMMatrix& theMatrix, IControlView *controlView);

	// ----- Clipping -----
	
	virtual SysRgn				GetClip() const;
	virtual SysRgn				GetOriginAdjustedClip() const;
	
	// ----- Accessors -----
	
	virtual SysPort				GetSysPort() const;
	virtual IViewPort*			GetViewPort() const;
	virtual const PMMatrix&		GetContentToViewTransform() const;
	virtual const PMMatrix&		GetViewToContentTransform() const;
	virtual IControlView*		GetView() const;

	virtual bool16				IsCurrent() const;

	virtual dvaui::drawbot::Drawbot* GetDrawbot() const
	{
		return NULL;
	}

private:

	// ----- Data fields -----
	SysPort					fSysPort;
	IViewPort*				fViewPort;
	PMMatrix				fTransform;
	PMMatrix				fInvTransform;
	bool16					fInverseValid;
	IControlView*			fControlView;
	SysRgn					fClipRgn;
	SysRgn					fOriginAdjustedClip;
};

#pragma export off

#endif
