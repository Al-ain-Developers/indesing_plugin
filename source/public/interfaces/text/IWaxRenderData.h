//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IWaxRenderData.h $
//  
//  Owner: Zak_Williamson
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
#ifndef __IWaxRenderData__
#define __IWaxRenderData__

#include "IPMUnknown.h"
#include "IFontMgr.h"
#include "IDrawingStyle.h"
#include "TextID.h"
#include "CTextEnum.h"

class PMMatrix;
class PMString;
class IPMFont;

/** Data interface that holds the drawing parameters for a COMPOSED run of text
	@ingroup text_wax
*/
class IWaxRenderData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IWAXRENDERDATA };

	typedef enum { kNone, kStrokeOnly, kFillOnly, kFillStroke } RenderMethod;

		/** return the font applied to this run */
	virtual IPMFont* QueryFont() const = 0;

	virtual void SetFontName(const PMString & name, bool16 missingFace = kFalse) = 0;
	virtual const PMString& GetFontName() const = 0;
	virtual bool16 FontFaceMissing() const = 0;
	virtual void SetFontWritingScript(int32 script) = 0;

	virtual Text::GlyphID GetSpaceGlyphID(Text::GlyphID* ideographicSpace = nil) const = 0;
	virtual Text::GlyphID GetHyphenGlyphID() const = 0;

	virtual const Fixed* GetDesignAxes(int32 * pNumAxes) const = 0;
	virtual void SetDesignAxes(int32 num, const Fixed* axes) = 0;

	virtual const PMMatrix& GetFontMatrix() const = 0;
	virtual void SetFontMatrix(const PMMatrix& matrix) = 0;
	virtual void SetJustificationGlyphScale(PMReal scale) = 0;
	virtual PMReal GetJustificationGlyphScale() const = 0;

	virtual PMReal GetLeading() const = 0;
	virtual void SetLeading(PMReal leading) = 0;

	virtual UID GetColorUID(bool16 stroke) const = 0;
	virtual void SetColorUID(bool16 stroke, UID newColor) = 0;
	virtual void SetTint(bool16 stroke, PMReal tint) = 0;
	virtual PMReal GetTint(bool16 stroke) const = 0;
	virtual void SetOverprint(bool16 stroke, bool16 over) = 0;
	virtual bool16 GetOverprint(bool16 stroke) const = 0;

	virtual void SetGradientAngle(bool16 stroke, PMReal angle) = 0;
	virtual PMReal GetGradientAngle(bool16 stroke) const = 0;
	virtual void SetGradientLength(bool16 stroke, PMReal length) = 0;
	virtual PMReal GetGradientLength(bool16 stroke) const = 0;
	virtual void SetGradientCenter(bool16 stroke, const PMPoint& center) = 0;
	virtual const PMPoint& GetGradientCenter(bool16 stroke) const = 0;

	virtual void SetOutlineWidth(PMReal width) = 0;
	virtual PMReal GetOutlineWidth() const = 0;

	virtual void SetMiterLimit(PMReal miterLimit) = 0;
	virtual PMReal GetMiterLimit() const = 0;

	virtual void SetStrokeAlignment(int32 align) = 0;
	virtual int32 GetStrokeAlignment() const = 0;

	virtual void SetOutlineJoin(int32 join) = 0;
	virtual int32 GetOutlineJoin() const = 0;

	// GetRenderMethod will return a RenderMethod of kNone if stroke or fill color is the none rendering UID
	// An an optimization client can pass in the noneRenderingUID if known. If a value other than kInvalidUID
	// is passed in then the database parameter may be nil.
	virtual RenderMethod GetRenderMethod(IDataBase* database, const UID noneRenderingUID = kInvalidUID) const = 0;

	virtual void SetFauxSmallCap(bool16 fakeSmallCaps, PMReal smallcapfactor = 1.0) = 0;
	virtual bool16 GetFauxSmallCap(PMReal *smallcapfactor = nil) const = 0;

		/** Copy ourselves into another run's render data */
	virtual bool16 CopyInto( IWaxRenderData* other ) const = 0 ;

	virtual bool16 IsColorInfoSame(const IWaxRenderData* other, IDataBase* db, UID noneRenderUID) const = 0;
	virtual bool16 	IsFontInfoSame(const IWaxRenderData* other) const = 0;
};

#endif
