//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/interactive/IAnimationAdornmentDrawer.h $
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
#ifndef __IAnimationAdornmentDrawer__
#define __IAnimationAdornmentDrawer__

#include "IPMUnknown.h"
#include "IAdornmentShape.h"
#include "IAdornmentHandleShape.h"
#include "DynamicDocumentsID.h"

class IShape;
class GraphicsData;
class IConcreteSelection;
class IHandleShape;

/**	A helper interface on all drawable page item with IID_IANIMATIONATTRIBUTEDATA.
	This draws an adornment on the page item shape indicating that the page item has animation applied.
*/
class IAnimationAdornmentDrawer : public IPMUnknown
{
public:

	enum { kDefaultIID = IID_IANIMATIONADORNMENTDRAWER };
	
	/** Draw an animation adornment for the page item.
		@param iShape is the owning page item.
		@param drawOrder is the current draw order bits. This adornment draws with kAfterShape.
		@param gd is the current GraphicsData.
		@param flags is the graphics's ports flags.
		@return the width of the animation proxy drawn. If animation proxy is not drawn, returns 0.
	*/
	virtual PMReal DrawAnimationAdornment (IShape* iShape, IAdornmentShape::AdornmentDrawOrder drawOrder, GraphicsData* gd, int32 flags) = 0;

	virtual PMRect GetPaintedProxyAdornmentHandleBounds (IHandleShape* iShape, IAdornmentHandleShape::AdornmentDrawOrder drawOrder, 
			const PMRect& rItem, const PMMatrix& innertoview) = 0;

	/** Draw an proxy of the animated object at runtime's end position.
		Only scale, rotation, and position are taken into account.
		@param iShape is the owning page item.
		@param gd is the current GraphicsData.
		@param concreteSelection is the selection boss.
		@param flags is the graphics's ports flags.
	*/
	virtual void DrawAnimationProxy (IHandleShape* iShape, IAdornmentHandleShape::AdornmentDrawOrder drawOrder, GraphicsData* gd, IConcreteSelection* concreteSelection, int32 flags) = 0;
};

#endif	//	__IAnimationAdornmentDrawer__
