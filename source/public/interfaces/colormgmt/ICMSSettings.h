//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/colormgmt/ICMSSettings.h $
//  
//  Owner: fhaberma
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

#ifndef __ICMSSettings__
#define __ICMSSettings__

#if PRAGMA_ONCE
#pragma once
#endif

#include "IPMUnknown.h"
#include "ColorMgmtID.h"

class ICMSSettings : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICMSSETTINGS };

	enum renderingIntent
		{ 
			kImage = 0, 	// a.k.a. Perceptual
			kGraphic, 		// a.k.a. Saturation
			kRelative, 
			kAbsolute, 
			kOther,			// Generally an invalid state
			
			kUseCSFImageRI = 10,	// Points to current CSF (global) image RI
			kUseCSFVectorRI,		// Points to current CSF (global) vector/solid RI
			kUseCSFPostBlendRI,		// Points to current CSF (global) postblend RI
			
			kUseDocImageRI = 20,	// Points to current document image RI
			kUseDocVectorRI,		// Points to current document vector/solid RI
			kUseDocPostBlendRI,		// Points to current document postblend RI
			
			kUseGStateRI = 30		// Points to current port's gstate RI, which is by default the
									// document vector RI and controlled dynamically by 
									// IGraphicsPort::SetRenderingIntent.
		};	
	
	virtual bool16 IsCMSOn() const = 0;
		//Returns whether CMS is turned on for this document or item
	virtual void SetCMSOn(bool16 isOn)=0;	
		//Sets whether CMS is turned on for this document or item
	
	virtual void SetRenderingIntent(renderingIntent intent = kImage) = 0;
		//Sets the rendering intent for this item or document. Rendering intent is used when converting out-of-gamut colors
	virtual renderingIntent GetRenderingIntent() const = 0;
		//Returns the rendering intent for this item or document.

#ifdef DEBUG
	virtual void DumpToDebugWindow() = 0;
#endif
	
};

#endif // __ICMSSettings__

// End, ICMSSettings.h.

