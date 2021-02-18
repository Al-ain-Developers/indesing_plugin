//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PNGIcon.h $
//  
//  Owner: Dave Burnard
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
//  An icon class that draws itself (via AGM) without a widget
//  
//  This is a class that will draw an PNG based icon with the specified resource id.
//	(Refactored from the old PlatformIconClass, after we dropped platform icon resources)
//  
//========================================================================================

#pragma once
#ifndef __PNGIcon__
#define __PNGIcon__

#ifdef WIDGET_BUILD
#pragma export on
#endif

#include "PNGArt.h"
class IViewPort;

/** This class encapsulates loading & drawing a PNG based icon. */
/** Supports hires and dark UI icons. */

class WIDGET_DECL PNGIcon {
public:
	PNGIcon();
 	~PNGIcon();
	
	/** Read or write this object to the given stream.
		@param s the stream to read or write from/to
		@param prop ignored
	*/
	void 		ReadWrite(IPMStream* s, ImplementationID prop);

	/** Load an icon into this object for later drawing.
		@param pid the plugin the icon is coming from
		@param iconRsrcID the icon/PNG resource id within the plugin
		@param brightnessAware if true, the icon switches according to UI brightness at
		                       drawing time. Else bright UI icon is always drawn.
	*/
	void		LoadIcon(const PluginID & pid, const RsrcID& iconRsrcID, bool brightnessAware = true);

	/** Draw the icon previously loaded into this object
		@param viewPort the port to draw into
		@param bbox the rect to draw into
		@param drawDisabled a boolean indicating if the icon should be drawn with a disabled look
	*/
	void		Draw(IViewPort* viewPort, const SysRect& bbox, bool drawDisabled);
	
	/** API from old PlatformIcon class */
	static PNGIcon *CreateIcon(const PMRsrcID& inRsrcID, bool brightnesssAware = true);
	ErrorCode	DrawIcon(IGraphicsPort* graphicsPort);
	SysRect		GetBounds();

	RsrcID		GetRsrcID(){ return fIconRsrcID; }
	PluginID	GetRsrcPluginID(){ return fPid; }
	bool		IsLoaded();

protected:
	PluginID	fPid;
	RsrcID		fIconRsrcID;
	
private:
	void		LoadIcon(const PluginID & pid, const RsrcID& iconRsrcID, bool brightnessAware, float desiredRes);

	PNGArt		fPNGArt;
	float		fLoadedRes;
	float		fDesiredRes;
	bool		fBrightnessAware;
	bool		fLoadedForBrightUI;
};

#pragma export off

#endif // __PNGIcon__
