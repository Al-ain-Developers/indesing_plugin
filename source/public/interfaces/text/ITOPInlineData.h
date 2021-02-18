//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITOPInlineData.h $
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

#ifndef __TextOnPathID__
#include "TextOnPathID.h"
#endif
#include "IPMUnknown.h"

class PMMatrix;
class PMPoint;
class PMReal;
class IPathGeometry;
class IMainItemTOPData;

/** 
	@ingroup text_onpath
*/
class ITOPInlineData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITOPINLINEDATA };

	// YC 12/29/99: only for ILG in a Path Type (or TextOnPath)
	// . IsInTOPTextFrame and GetTOPFrameMatrix are only called by InlineTransform::GetInlineToFrameMatrix
	// . SetTOPFrameMatrix is only called by TOPSplineObserver. It update this matrix for kRecomposeBoss
	// before to recompose the text.

	virtual bool16		IsInTOPTextFrame() const = 0;
	virtual void		SetInTOPTextFrame( const bool16  isInTOPTextFrame ) = 0;

	virtual PMMatrix	GetTOPFrameMatrix() const = 0;
	virtual PMMatrix	GetInverseTOPFrameMatrix() const = 0;
	virtual void		SetTOPFrameMatrix( const PMMatrix&  newMatrix ) = 0;

	virtual void		UpdateInlineMatrix() = 0;

};

#endif
