//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CRenderingObjectDrawer.h $
//  
//  Owner: SusanCL
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
#ifndef __CRenderingObjectDrawer__
#define __CRenderingObjectDrawer__

#include "IRenderingObjectDrawer.h"
#include "CPMUnknown.h"
#include "InterfaceFontInfo.h"

#pragma export on
class WIDGET_DECL CRenderingObjectDrawer : public CPMUnknown<IRenderingObjectDrawer>
{
public:

	enum
	{
		kRenderObjectSwatchStart = 4,
		kSwatchNameStart = kRenderObjectSwatchStart + 3,
		kIconInset = 3,
		kSwatchesPanelIconWidth = 13,
	};
	
	CRenderingObjectDrawer( IPMUnknown *boss );
	virtual ~CRenderingObjectDrawer( );

	virtual void DrawRenderObjectUI 		( IViewPort* viewPort, IControlView* view, SysRgn updateRgn, PMRect frame ) const;
	virtual void DrawRenderObjectUIName		( IGraphicsContext* gc, const InterfaceFontInfo& fontInfo, const PMRect& frame, const int16& alignment, const bool16& isHilited, const bool16& isEnabled) const;
	virtual void DrawRenderObjectUISwatch	( IGraphicsPort* gPort, const PMRect& frame ) const;
	virtual void DrawRenderObjectUIIcons	( IViewPort* viewPort, const SysRect& sysFrame, const bool16& brightnessAware = kTrue) const {};

protected:
	void		DrawNoEditIcon		( IViewPort* viewPort, const SysRect& bbox, const bool16& brightnessAware = kTrue) const;
	void		DrawBackground		( IGraphicsPort* gPort, const IControlView* widget, const PMRect& frame, const bool16& isHilited, const bool16& bInsetHilite ) const;
};
#pragma export off

#endif	// __CRenderingObjectDrawer__
