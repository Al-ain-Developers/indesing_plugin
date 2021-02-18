//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ISpectrumAttributes.h $
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
#ifndef __ISpectrumAttributes__
#define __ISpectrumAttributes__

/**	Color bar attribute data interface specifying how the color bar is to be created.
	The color bar is a widget in the color space panel.
	There's no set methods because the attributes are specified via the resource file
	when defining the color bar widget.
*/
class ISpectrumAttributes : public IPMUnknown
{
public:
	// ----- Query -----
	
	/**	Return true if color bar widget includes the minimum and maximum swatch proxy.
		For color space color bar, minimum swatch proxy is a "white" color swatch proxy and
		the maximum swatch proxy is the "black" color swatch proxy.
	*/
	virtual bool16	GetAttribute() const = 0;
	/**	Return true if the color bar is a color space color bar. Otherwise kFalse
		indicates a transition color bar for minimum tint to maximum tint of a spcified
		color value.
	*/
	virtual bool16	GetSpectrumType() const = 0;
};

#endif
