//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IWaxGlyphsTOPTransform.h $
//  
//  Owner: Michel Hutinel
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
#ifndef __IWaxGlyphsTOPTransform__
#define __IWaxGlyphsTOPTransform__

#include "IPMUnknown.h"
#include "TextOnPathID.h"
#include "CTextEnum.h"

class PMMatrix;
class PMPoint;
class PMReal;
class IPathGeometry;
class IMainItemTOPData;
class IWaxRun;

/** 
	@ingroup text_onpath
	@ingroup text_wax
*/
class IWaxGlyphsTOPTransform : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IWAXGLYPHSTOPTRANSFORM };

		virtual bool16				IsTopRun() const = 0;

		virtual void				GetGlyphTransforms(	PMReal xPosition, PMReal yPosition,
														PMReal glyphWidth, PMReal glyphXOffset,
														PMMatrix& glyphMatrix, PMMatrix& caretMatrix, 
														PMPoint& offset) = 0;

		virtual const PMMatrix *	PeekGlyphTransformArray() const = 0;

		virtual const PMPoint *		PeekGlyphOffsetArray() const = 0;
		virtual const PMPoint *		PeekSelectionOffsetArray() const = 0;

		virtual bool16				PointOnPathToAbscissa(const PMPoint pt, PMReal* abs, int32* hitTest) = 0;

		// If we're using the "new" (March 29, 2001) transformations, TOP applies matrix transformations onto each glyph in the wax.
		virtual void				ApplyPerGlyphTransforms() = 0;
		virtual PMPoint 			TransformRunPointToSpline(const PMPoint &pointToTransform) = 0;
};

#endif
