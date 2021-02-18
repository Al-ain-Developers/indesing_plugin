//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IMainItemTOPData.h $
//  
//  Owner: Bertrand Lechevalier
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
#ifndef __IMainItemTOPData__
#define __IMainItemTOPData__

#include "TextOnPathID.h"	// for IID_IMAINITEMTOPDATA
#include "PMPoint.h"
#include "IScaleObject.h"
#include "TOPOptionsType.h"

class TOPDrawingData;
class TOPOptionsData;
class TOPPathGeometry;
class IWaxLine;

class IGeometry;
class ITOPFrameData;
class ITOPSplineData;
class IRasterPort;
class IGraphicsPort;
class IMultiColumnTextFrame;

/** 
	@ingroup text_onpath
*/
class IMainItemTOPData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IMAINITEMTOPDATA };

	virtual void		ReadWrite(IPMStream *s, ImplementationID prop) = 0;

	virtual IGeometry*		QueryTOPGeometry() = 0;
	virtual ITOPFrameData*	QueryTOPFrameData() = 0;
	virtual ITOPSplineData*	QueryTOPSplineData() = 0;

	virtual UID			GetTOPSplineItemUID() const = 0 ;
	virtual void		SetTOPSplineItemUID( UID nNewUID) = 0;

	virtual UID						GetTOPTextFrameColumnUID() const = 0;

	virtual UID						GetTOPMCTextFrameUID() const = 0;
	virtual IMultiColumnTextFrame*	QueryTOPMCTextFrame() const = 0;

	virtual void					GetTOPOptionsData( TOPOptionsData&  options ) const = 0;
	virtual const TOPOptionsData*	GetTOPOptionsData() const = 0;

	virtual void					GetTOPDrawingData( TOPDrawingData&  drawingData ) const = 0;
	virtual const TOPDrawingData*	GetTOPDrawingData() const = 0;

	virtual void					SetTextAlign( const TextAlignType textAlign ) = 0;
	virtual void					SetPathAlign( const PathAlignType pathAlign ) = 0;
	virtual void					InvertPathAlignment() = 0;
	virtual void					SetTypeEffect( const EffectType typeEffect ) = 0;
	virtual void					SetOverlapOffset( const int16  overlapOffset ) = 0;
	virtual void					SetFlip( const int16  flip ) = 0;
	virtual void					Scale(IScaleObject::ScaleContext& context) = 0;

	virtual void					SetVertical( const bool16 isVertical ) = 0;
	virtual void					SetStartHeight( const int32 startHeight ) = 0;
	virtual void					SetEndHeight( const int32 endHeight ) = 0;
	virtual void					SetRightToLeft( const bool16 isRightToLeft ) = 0;

	virtual const TOPPathGeometry*	GetCompositionPath() const = 0;
	virtual PMReal					GetCompositionLength() const = 0;

	// Compute all transforms about the glyphs on a curve

	virtual PMReal		GetGlyphsVerticalOffset(const IWaxLine* waxLine) const = 0;
	virtual void		GetGlyphAllTransforms(
							const PMMatrix initialGlyphPosition,	// A translation matrix that provides us a translation from the beginning of the line
							K2Vector<PMReal>& glyphWidths, // set of glyph widths-- we need a set in the case of ligatures
							const PMReal& glyphXOffset, // difference between left edge of glyph's space and its actual draw location
							const PMReal& glyphVerticalOffset,	// vertical offset associated to the glyph
							PMMatrix* glyphMatrix,			// OUT: matrix associated to the glyphs
							PMPointList& glyphPoints,		// new point positions to draw the glyphs
							PMPointList& selectionPoints	// new point positions to hilite the glyphs
						) = 0;// kTrue on last glyph of last run of line if no ignore trailing
						 
	typedef enum { kFromStart, kFromEnd} AbscissaAnchor;
	virtual void		GetTabRulerPoints( PMReal  absciss,  PMPointList&  tabRulerPoints, AbscissaAnchor anchor) = 0;

	virtual PMMatrix	GetCaretRotationMatrix( PMPoint  pt ) = 0;
	virtual PMReal		GetPointOnPathToAbscissa(PMPoint pt, PMReal* angle=nil) = 0;
	virtual bool16		PointIsInTOPTextArea(const PMPoint& innerPt, PMReal tolerance, PMReal* dist=nil ) = 0;


	// called by FrameThreadDrawHandler::DrawThreads and TextOversetMarkerAdornment::Inval

	virtual void	GetRectHandlePositions(IRasterPort* rPort, PMPoint* outPort, PMPointList* oversetPtList) = 0;
	virtual void	GetTextFrameHandlePositions(IRasterPort* rPort, PMPoint* inPort, PMPoint* outPort) = 0;
	virtual void	CreateAnchorPath(IGraphicsPort* gPort, IRasterPort* rPort,const bool16 startBracket, bool16 bApplyInnerToPasteboard = kTrue) = 0;
	virtual void	CreateTextLinkPath(IGraphicsPort* gPort, IRasterPort* rPort, const bool16 startBracket) = 0;

	// called by GraphicFrameEdgesAdornment::DrawOversetForTOP
	virtual void	CreateTextOversetPath(IGraphicsPort* gPort, IRasterPort* rPort) = 0;

	virtual void	GetAbscissae( PMReal* textStart, PMReal* textEnd, PMReal* arcLength = 0) const = 0;
	virtual void	SetAbscissae( PMReal textStart, PMReal textEnd) = 0;
	virtual void	InvertAbscissae( ) = 0;

} ;

#endif //__IMainItemTOPData__
