//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/AGMGraphicsContextWith.tpp $
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

#ifndef __AGMGraphicsContextWith_TPP__
#define __AGMGraphicsContextWith_TPP__

#include "AGMGraphicsContextWith.h"

// ----- Interface Includes -----

#include "IGraphicsContextArbitrator.h"
#include "IControlView.h"
#include "ISession.h"

// ----- Implementation Includes -----

template <class AcquireCoordSys, class AcquireClip>
AGMGraphicsContextWith<AcquireCoordSys, AcquireClip>::AGMGraphicsContextWith(IViewPort* viewPort, IControlView *controlView, SysRgn clipRgn) :
	fVP(viewPort, UseDefaultIID()),
	fAcquireVP(fVP),
	fAcquireCoordSys(fVP, controlView),
	fAcquireClip(fVP, controlView, clipRgn)
{
	ASSERT_MSG(viewPort != nil, "AGMGraphicsContextWith::AGMGraphicsContextWith - viewPort is nil");
	ASSERT_MSG(controlView != nil, "AGMGraphicsContextWith::AGMGraphicsContextWith - controlView is nil");

	InterfacePtr<IGraphicsContextArbitrator> gca(GetExecutionContextSession(), IID_IGRAPHICSCONTEXTARBITRATOR);
	gca->SetContext(this);
}

template <class AcquireCoordSys, class AcquireClip>
AGMGraphicsContextWith<AcquireCoordSys, AcquireClip>::AGMGraphicsContextWith(IViewPort* viewPort, ITransform* xform, SysRgn clipRgn) :
	fVP(viewPort, UseDefaultIID()),
	fAcquireVP(fVP),
	fAcquireCoordSys(fVP, xform),
	fAcquireClip(fVP, clipRgn)
{
	ASSERT_MSG(viewPort != nil, "AGMGraphicsContextWith::AGMGraphicsContextWith - viewPort is nil");
	
	InterfacePtr<IGraphicsContextArbitrator> gca(GetExecutionContextSession(), IID_IGRAPHICSCONTEXTARBITRATOR);
	gca->SetContext(this);
}

template <class AcquireCoordSys, class AcquireClip>
AGMGraphicsContextWith<AcquireCoordSys, AcquireClip>::AGMGraphicsContextWith(IViewPort* viewPort, const PMMatrix& theMatrix, SysRgn clipRgn) :
	fVP(viewPort, UseDefaultIID()),
	fAcquireVP(fVP),
	fAcquireCoordSys(fVP, theMatrix),
	fAcquireClip(fVP, clipRgn)
{
	ASSERT_MSG(viewPort != nil, "AGMGraphicsContextWith::AGMGraphicsContextWith - viewPort is nil");

	InterfacePtr<IGraphicsContextArbitrator> gca(GetExecutionContextSession(), IID_IGRAPHICSCONTEXTARBITRATOR);
	gca->SetContext(this);
}

template <class AcquireCoordSys, class AcquireClip>
AGMGraphicsContextWith<AcquireCoordSys, AcquireClip>::AGMGraphicsContextWith(IViewPort* viewPort, const PMMatrix& theMatrix, IControlView* controlView, SysRgn clipRgn) :
	fVP(viewPort, UseDefaultIID()),
	fAcquireVP(fVP),
	fAcquireCoordSys(fVP, theMatrix, controlView),
	fAcquireClip(fVP, clipRgn)
{
	ASSERT_MSG(viewPort != nil, "AGMGraphicsContextWith::AGMGraphicsContextWith - viewPort is nil");

	InterfacePtr<IGraphicsContextArbitrator> gca(GetExecutionContextSession(), IID_IGRAPHICSCONTEXTARBITRATOR);
	gca->SetContext(this);
}

template <class AcquireCoordSys, class AcquireClip>
AGMGraphicsContextWith<AcquireCoordSys, AcquireClip>::AGMGraphicsContextWith(IViewPort* viewPort, ITransform* xform, IControlView* controlView, SysRgn clipRgn) :
	fVP(viewPort, UseDefaultIID()),
	fAcquireVP(fVP),
	fAcquireCoordSys(fVP, xform, controlView),
	fAcquireClip(fVP, clipRgn)
{
	ASSERT_MSG(viewPort != nil, "AGMGraphicsContextWith::AGMGraphicsContextWith - viewPort is nil");
	
	InterfacePtr<IGraphicsContextArbitrator> gca(GetExecutionContextSession(), IID_IGRAPHICSCONTEXTARBITRATOR);
	gca->SetContext(this);
}

template <class AcquireCoordSys, class AcquireClip>
AGMGraphicsContextWith<AcquireCoordSys, AcquireClip>::~AGMGraphicsContextWith()
{
	InterfacePtr<IGraphicsContextArbitrator> gca(GetExecutionContextSession(), IID_IGRAPHICSCONTEXTARBITRATOR);
	gca->RestorePriorContext();
}

template <class AcquireCoordSys, class AcquireClip>
bool16 AGMGraphicsContextWith<AcquireCoordSys, AcquireClip>::IsCurrent() const
{
	InterfacePtr<IGraphicsContextArbitrator> gca(GetExecutionContextSession(), IID_IGRAPHICSCONTEXTARBITRATOR);
	IGraphicsContext* result = gca->GetCurrentContext();
	return (IGraphicsContext*) this == result;
}
#endif //__AGMGraphicsContextWith_TPP__

