//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IZoomCmdData.h $
//  
//  Owner: robin briggs
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
//  
//  Data interface for ZoomToCmd
//  
//========================================================================================

#pragma once
#ifndef __IZoomCmdData__
#define __IZoomCmdData__

#include "widgetid.h"

class IControlView;
class PMPoint;

const double kMaxZoom = 40.0;
const double kMinZoom = 0.05;
const double kDragOutMaxZoom = 40.0;
const double kDragOutMinZoom = 0.05;

class IZoomCmdData : public IPMUnknown
{
public:
		enum { kDefaultIID = IID_IZOOMCMDDATA };

		typedef enum { kZoomVisibleSpread_True, kZoomVisibleSpread_False } ZoomVisibleType;
		virtual void Set(IControlView *view, PMReal scaleFactor, const PMPoint& centerPoint, 
						 bool16 zoomToPoint = kTrue, ZoomVisibleType visible = kZoomVisibleSpread_False) = 0;
		virtual void Set(IControlView *view, PMReal scaleFactor) = 0;

		virtual IControlView	*GetControlView() const = 0;
		virtual PMReal			GetScaleFactor() const = 0;
		virtual PMPoint			GetCenterPoint() const = 0;
		virtual bool16			GetZoomToPointFlag() const = 0;
		virtual ZoomVisibleType	GetZoomToCurrentVisibleSpread() const = 0;
};

#endif // __IZoomCmdData__
