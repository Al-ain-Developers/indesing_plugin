//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/interactive/ColorizedIcon.h $
//  
//  Owner: Tim Wright
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
//  Helper for form frame adorment...
//  
//========================================================================================

#pragma once
#ifndef __COLORIZEDICON__
#define __COLORIZEDICON__

//----------------------------------------------------------------------------------------
#include "BravoForwardDecl.h"
#include "IColorData.h"
#include "PMRect.h"
#include "PNGIcon.h"

#pragma export on

class ColorizedIcon
{
public:
	WIDGET_DECL ColorizedIcon( const PMRsrcID& inRsrcID );
 	WIDGET_DECL virtual ~ColorizedIcon();
	
	WIDGET_DECL ErrorCode Draw( IGraphicsPort * inGraphicsPort, const PMPoint& inIconTopLeft, const ColorArray& inColor );
	WIDGET_DECL PMRect GetBounds() const;
	WIDGET_DECL PMRect GetNonTransparentBounds(const ColorArray& inColor);
	WIDGET_DECL void UseOriginalAlpha(bool16 useIt=kTrue);

	WIDGET_DECL RsrcID GetRsrcID();
	WIDGET_DECL PluginID GetRsrcPluginID();

protected:
	enum eCheckColor {kDontCheckColor = 0, kDoCheckColor = 1};

	struct ImageData {
		uint8* fImagePixelStorage;
		int32 fImageRowBytes;
		int32 fImageWidth;
		int32 fImageHeight;
		float fImageRes;
	};

	// imageRes here is the scale for which we need the image. The value for imageRes is the 
	// current scale factor of the UI.
	ErrorCode GenerateImage(const ColorArray& inColor, eCheckColor inCheckColor, float imageRes);

	void Dispose();
	void DisposeImage(ImageData* image);
	
	void GetImage(const ImageData* image, AGMImageRecord* outAGMRecord) const;
	
	ErrorCode ImageIcon( ImageData* image );
	ErrorCode Colorize( ImageData* image, const ColorArray& inColor );

private:
	PNGIcon* fIcon;
	
	ImageData* fImageData_1x;
	bool fHaveIconImage_1x;

	ImageData* fImageData_hires;
	bool fHaveIconImage_hires;
	
	mutable bool fHaveNonTransparentBounds;
	mutable PMRect fNonTransparentBounds;
	ColorArray fImagedColor;
	bool16 fUseOriginalAlpha;
};

#pragma export off

#endif
