//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/NonMarkingAGMGraphicsContext.h $
//  
//  Owner: Rishi Kumar
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
#ifndef __NonMarkingAGMGraphicsContext__
#define __NonMarkingAGMGraphicsContext__

#include "AGMGraphicsContext.h"
#include "IViewPortArbitrator.h"
#include "IRasterPort.h"

/*
 This class is constructed to mimic the construction and delayed destruction behavior of the stack based AGMGraphicsContext object behavior 
*/
class NonMarkingAGMGraphicsContext : public IGraphicsContext 
	{
	public:
		NonMarkingAGMGraphicsContext (IControlView* view) : 
		arbitrator(GetExecutionContextSession(), UseDefaultIID()),
		nonmarkingRasterPort(arbitrator->QueryNonMarkingRasterViewPort()),
		nonmarkingViewPort(nonmarkingRasterPort, IID_IVIEWPORT),
		gc(nonmarkingViewPort, view)
		{
		}
		
		virtual ~NonMarkingAGMGraphicsContext()
		{
		}
		
		// IGraphicsContext methods overrides 
		virtual SysRgn	GetClip() const {return gc.GetClip();}
		
		virtual SysRgn  GetOriginAdjustedClip() const {return gc.GetOriginAdjustedClip();}
		
		virtual SysPort	GetSysPort() const {return gc.GetSysPort();}
		
		virtual IViewPort*	GetViewPort() const {return gc.GetViewPort();}
		
		virtual const PMMatrix&	GetContentToViewTransform() const {return gc.GetContentToViewTransform();}
		
		virtual const PMMatrix&	GetViewToContentTransform() const {return gc.GetViewToContentTransform();}
		
		virtual IControlView*	GetView() const {return gc.GetView();}
		
		virtual bool16	IsCurrent() const {return gc.IsCurrent();}
		
		virtual dvaui::drawbot::Drawbot* GetDrawbot() const {return gc.GetDrawbot();}
		
	private:
		InterfacePtr<IViewPortArbitrator> arbitrator;
		InterfacePtr<IRasterPort> nonmarkingRasterPort;
		InterfacePtr<IViewPort> nonmarkingViewPort;
		AGMGraphicsContext gc;
		
	};
#endif
