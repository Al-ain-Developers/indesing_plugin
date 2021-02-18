//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/TextDrawInfo.h $
//  
//  Owner: ???
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
#ifndef __TEXT_DRAW_INFO__
#define __TEXT_DRAW_INFO__

#include "IWaxRenderData.h"
#include "IPMFont.h"
#include "GraphicsData.h"

class IParcelShape;
class IPMFont;

class PUBLIC_DECL TextDrawInfo INHERITFROM
{
public:	
	TextDrawInfo();
	~TextDrawInfo();

	void StartTextFrameShapeDraw(const GraphicsData* gd, const IParcelShape* parcel);
	void EndTextFrameShapeDraw (const GraphicsData* gd, const IParcelShape* parcel);

	void StartTableFrameShapeDraw();
	void EndTableFrameShapeDraw ();

	// Accessors	
	UID			GetNoneSwatchUID() const  		{ return fNoneSwatchUID;  	  	}
	bool16		IsCreatingOutlines() const		{ return fIsCreatingOutlines; 	}
	IPMFont*	QueryFont() const;

	bool16		IsColorInfoSame(const IWaxRenderData* currentRun, IDataBase* db) const;
	bool16 		IsFontInfoSame(const IWaxRenderData* currentRun) const;


	// Two kinds of run based optimization are currently supported.
	// 1. Avoid reinstalling rendeing objects for each text run.
	// 2. Avoid QueryFont from IWaxRenderData for each run.
	// EOptimization  lets you choose from these.
	//		eColorAndFont  	=> 1. & 2.		// currently used for drawing text
	//		eFontOnly		=> 2.			// currently used for greeking text
	enum EOptimize { eColorAndFont, eFontOnly };	
	void 		NotifyRunDrawn(EOptimize optimize, const IWaxRenderData* justDrawn, IPMFont* justDrawnFont);	

	// This call has an implicit meaning of eFontOnly. eg missing font & missing glyph adornments
	// Any color optimizations are maintained
	void 		NotifyRunFont(const IWaxRenderData* run, IPMFont* font);	

	// Clears color & font optimization.
	void		ClearRunDrawn();

	// Clears color optimization (rendering object installed) 
	// Font optimization if any will be maintained.
	void 		ClearRunRenderInfo();


private:
	// Not specific to a parcel or thread but to all text
	bool16								fNonParcelDataInitialized;
	bool16								fIsCreatingOutlines;
	UID	 								fNoneSwatchUID;

	// Specific to each run
	InterfacePtr<const IWaxRenderData> 	fColorRenderData;
	InterfacePtr<const IWaxRenderData> 	fFontRenderData;
	InterfacePtr<IPMFont>				fFont;
};

class PUBLIC_DECL AutoTextFrameDrawNotify
{
	public:
		AutoTextFrameDrawNotify(const GraphicsData* gd, const IParcelShape* parcel) :
			fGD(gd),
			fParcel(parcel)
		{
			gd->GetTextDrawInfo()->StartTextFrameShapeDraw(fGD, fParcel);
		}
		~AutoTextFrameDrawNotify()
		{
			fGD->GetTextDrawInfo()->EndTextFrameShapeDraw(fGD, fParcel);
		}
	private:
		const GraphicsData* fGD;
		const IParcelShape* fParcel;
};

class PUBLIC_DECL AutoTableFrameDrawNotify
{
	public:
		explicit AutoTableFrameDrawNotify(const GraphicsData* gd) :
			fGD(gd)
		{
			fGD->GetTextDrawInfo()->StartTableFrameShapeDraw();
		}
		~AutoTableFrameDrawNotify()
		{
			fGD->GetTextDrawInfo()->EndTableFrameShapeDraw();
		}
	private:
		const GraphicsData* fGD;
};

#endif //__TEXT_DRAW_INFO__
