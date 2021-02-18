//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IParaRulesAdornmentData.h $
//  
//  Owner: Ric Kamicar
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
#ifndef __IParaRulesAdornmentData__
#define __IParaRulesAdornmentData__

#include "IPMUnknown.h"
#include "TextAttrID.h"	// for IID_IPARARULESADORNMENTDATA
#include "ITextAttrStrokeType.h"

class PMPoint;
class PMReal;



/**
	@ingroup text_adorn
*/
class IParaRulesAdornmentData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IPARARULESADORNMENTDATA };


			/** Master "set" routine for paragraph rule data. This routine fills out the data for a paragraph rule text adornment.
				@param above means kTrue = above, kFalse = below.
				@param color is the color.
				@param tint is the line's tint.
				@param weight is the line's stroke weight.
				@param overprint specifies if the line overprints.
				@param strokeType is a stroke Type object.
				@param gapColor is the color of the gap for dashed lines.
				@param gapTint is the tint of the gap in dashed lines.
				@param gapOverprint specifies if the gap color should overprint.
			*/
		virtual void SetLineCharacteristics(bool16 above, UID color, const PMReal& tint, const PMReal& weight,
											bool16 overprint, const ICompositionStyle::StrokeType& strokeType,
											UID gapColor, const PMReal& gapTint, bool16 gapOverprint) = 0;

			/**  Paragraph rules can comprise multiple line segments.
				@param position is the relative position of the line from the line's beginning & baseline.
				@param length is the length in points of the line segment.
			*/
		virtual void AddLineSegment( const PMPoint& position, const PMReal& length ) = 0 ;

			/** Set a transform for the line. ONLY used to back out from the wax run to the wax line
				because we only have implemented wax run adornments, but this is really designed to be
				on a line.
				@param mat is the inverse matrix from the wax run to the wax line.
			*/
		virtual void SetTransform( const PMMatrix& mat ) = 0 ;
		virtual void SetNoLine() = 0;

		virtual int32 GetNumSegments() const = 0 ;
		virtual const PMPoint& GetNthPosition( int32 n ) const = 0 ;
		virtual const PMReal& GetNthLength( int32 n ) const = 0 ;

		virtual const PMReal& GetWeight() const = 0;
		virtual bool16 GetOverprint() const = 0;
		virtual const PMReal& GetTint() const = 0;
		virtual UID GetColor() const = 0;
		virtual ICompositionStyle::StrokeType GetStrokeType() const = 0;
		virtual bool16 GetAbove() const = 0;
		virtual bool16 GetGapOverprint() const = 0;
		virtual const PMReal& GetGapTint() const = 0;
		virtual UID GetGapColor() const = 0;

		virtual PMReal GetRuleOffset() const = 0;

		virtual const PMMatrix& GetTransform() const = 0 ;
			//We're an adornment on the first leaf waxrun on the waxline (see QueryParagraphRulesData in HLAdornments.cpp).
			//The port is in the waxrun's owner's coords at adornment draw time. We need to back out the matrix in the port
			//to waxline coords, then restore it after we draw our rule (see TextAdornmentParagraphRules::Draw).
};

#endif
