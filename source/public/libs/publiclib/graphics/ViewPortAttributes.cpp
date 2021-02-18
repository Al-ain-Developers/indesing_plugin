//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/graphics/ViewPortAttributes.cpp $
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

#include "VCPublicHeaders.h"
#include "ViewPortAttributes.h"
#include "PreferenceUtils.h"

#include "IDrawOptionsSetID.h"

// BP 05/03/01: moved to  .../source/components/public/PublicImpl.cpp
// CREATE_PMINTERFACE(ViewPortAttributes, kViewPortAttributesImpl)
DEFINE_HELPER_METHODS(ViewPortAttributes)

ViewPortAttributes::ViewPortAttributes(IPMUnknown * boss) :
	HELPER_METHODS_INIT(boss),
	fViewPortResolution(72),
	fViewPortLineScreen(0),
	fViewPortOutputOPI(kFalse),
	fViewPortDoCacheing(kTrue),
	fViewPortBitmapSampling(kViewPortBMSampleLowRes),
	fViewPortVectorSampling(kViewPortBMSampleLowRes),
	fViewPortFilterContent(kFalse),
	fViewPortDoTiling(kFalse),
	fViewPortProofPrint(kFalse),
	fViewPortDisallowImageCrop(kFalse),
	fViewPortOmitPDF(kFalse),
	fViewPortOmitEPS(kFalse),
	fViewPortOmitBitmapImages(kFalse),
	fViewPortDrawPasteboardShadow(kTrue),
	fViewPortDrawPageShadow(kTrue),
	fViewPortIsPrintingPort(kFalse)
{
}


ViewPortAttributes::~ViewPortAttributes()
{
}


void ViewPortAttributes::Initialize(IDataBase* db, IControlView *controlView)
{
	// For this base implementation of the ViewPortAttributes, we
	// want to initialize with the standard screen view port attributes.
	// This includes using the IDrawOptions and IDrawOptionsSet stored with the view. 
	// If we've been given an ILayoutController, get its draw options preferences, otherwise, we default
	// to low res.
	InterfacePtr<IDrawOptions> iDrawOptions((IDrawOptions*)::QuerySessionPreferences(IID_IDRAWOPTIONS));
	if ( iDrawOptions ) {
		DrawOptionsSet drawOptions;
		int32 setID = iDrawOptions->GetActiveSetID();
		
		if ( controlView ) {
			InterfacePtr<IDrawOptionsSetID> drawOptionsSetID(controlView, IID_IDRAWOPTIONSSETID);
			if ( drawOptionsSetID ) {
				setID = drawOptionsSetID->GetID();
			}
		}
		
		iDrawOptions->GetSetByID(setID, &drawOptions);
		
		fViewPortOmitBitmapImages = kFalse;
		
		switch ( drawOptions.raster ) {
		case IDrawOptions::kRasterGrayOut:
			fViewPortOmitBitmapImages = kTrue;
			fViewPortBitmapSampling = kViewPortBMSampleOmit_Inval;
			break;
		case IDrawOptions::kRasterProxy:
			fViewPortBitmapSampling = kViewPortBMSampleLowRes;
			break;
		case IDrawOptions::kRasterHighRes:
			fViewPortBitmapSampling = kViewPortBMSampleHiRes;
			break;
		}
		
		fViewPortOmitEPS = kFalse;
		fViewPortOmitPDF = kFalse;
		
		switch ( drawOptions.vector ) {
		case IDrawOptions::kVectorGrayOut:
			fViewPortOmitEPS = kTrue;
			fViewPortOmitPDF = kTrue;
			fViewPortVectorSampling = kViewPortBMSampleOmit_Inval;
			break;
		case IDrawOptions::kVectorProxy:
			fViewPortVectorSampling = kViewPortBMSampleLowRes;
			break;
		case IDrawOptions::kDisplayList:
			fViewPortVectorSampling = kViewPortBMSampleHiRes;
			break;
		}
	}
	
	// The other attributes (OPI, cacheing, etc.) are initialized during
	// construction.
	//
}


PMReal ViewPortAttributes::GetViewPortResolution() const
{
	return fViewPortResolution;
}

void ViewPortAttributes::SetViewPortResolution(PMReal resolution)
{
	fViewPortResolution = resolution;
}

PMReal ViewPortAttributes::GetViewPortLineScreen() const
{
	return fViewPortLineScreen;
}

void ViewPortAttributes::SetViewPortLineScreen( const PMReal& n ) 
{
	fViewPortLineScreen = n;
};

bool16 ViewPortAttributes::GetViewPortOutputOPIComments() const
{
	return fViewPortOutputOPI;
}

void ViewPortAttributes::SetViewPortOutputOPIComments( bool16 b ) 
{
	fViewPortOutputOPI = b;
};

bool16 ViewPortAttributes::GetViewPortCacheing() const
{
	return fViewPortDoCacheing;
}

void ViewPortAttributes::SetViewPortCacheing(bool16 cacheing)
{
	fViewPortDoCacheing = cacheing;
}

int32 ViewPortAttributes::GetViewPortBitmapSampling() const
{
	return fViewPortBitmapSampling;
}

void ViewPortAttributes::SetViewPortBitmapSampling(int32 sampling)
{
	fViewPortBitmapSampling = sampling;
}

int32 ViewPortAttributes::GetViewPortVectorSampling() const
{
	return fViewPortVectorSampling;
}

void ViewPortAttributes::SetViewPortVectorSampling(int32 sampling)
{
	fViewPortVectorSampling = sampling;
}

bool16 ViewPortAttributes::GetViewPortFilterContent(void) const
{
	return fViewPortFilterContent;
}

void ViewPortAttributes::SetViewPortFilterContent(bool16 filter)
{
	fViewPortFilterContent = filter;
}

bool16 ViewPortAttributes::GetViewPortTiling() const
{
	return fViewPortDoTiling;
}

void ViewPortAttributes::SetViewPortTiling( bool16 b ) 
{
	fViewPortDoTiling = b;
};

bool16 ViewPortAttributes::GetViewPortProofPrint() const
{
	return fViewPortProofPrint;
}

void ViewPortAttributes::SetViewPortProofPrint(bool16 b) 
{
	fViewPortProofPrint = b;
};

bool16 ViewPortAttributes::GetViewPortDisallowImageCrop() const
{
	return fViewPortDisallowImageCrop;
}

void ViewPortAttributes::SetViewPortDisallowImageCrop(bool16 b) 
{
	fViewPortDisallowImageCrop = b;
};

bool16 ViewPortAttributes::GetViewPortOmitEPS(void) const
{
	return fViewPortOmitEPS;
}

void ViewPortAttributes::SetViewPortOmitEPS(bool16 b) 
{
	fViewPortOmitEPS = b;
};

bool16 ViewPortAttributes::GetViewPortOmitPDF(void) const
{
	return fViewPortOmitPDF;
}

void ViewPortAttributes::SetViewPortOmitPDF(bool16 b) 
{
	fViewPortOmitPDF = b;
};

bool16 ViewPortAttributes::GetViewPortOmitBitmapImages(void) const
{
	return fViewPortOmitBitmapImages;
}

void ViewPortAttributes::SetViewPortOmitBitmapImages(bool16 b) 
{
	fViewPortOmitBitmapImages = b;
};

void ViewPortAttributes::SetViewPortDrawPasteboardShadow (bool16 drawShadow)
{
	fViewPortDrawPasteboardShadow = drawShadow;
}

bool16 ViewPortAttributes::GetViewPortDrawPasteboardShadow (void) const
{
	return fViewPortDrawPasteboardShadow;
}

void ViewPortAttributes::SetViewPortDrawPageShadow (bool16 drawShadow)
{
	fViewPortDrawPageShadow = drawShadow;
}

bool16 ViewPortAttributes::GetViewPortDrawPageShadow (void) const
{
	return fViewPortDrawPageShadow;
}

bool16 ViewPortAttributes::GetViewPortIsPrintingPort (void) const
{
	return fViewPortIsPrintingPort;
}

void ViewPortAttributes::SetViewPortIsPrintingPort( bool16 b ) 
{
	fViewPortIsPrintingPort = b;
};

bool32 ViewPortAttributes::IsAttrDefined(VPAttrID attr) const
{
	VPAttrMap::const_iterator entry = fViewPortAttrMap.find(attr);
	
	return (entry != fViewPortAttrMap.end());
}

int32 ViewPortAttributes::GetAttr(VPAttrID attr, int32 defVal) const
{
	int32 result = defVal;
	
	VPAttrMap::const_iterator entry = fViewPortAttrMap.find(attr);
	if (entry != fViewPortAttrMap.end()) result = ::ToInt32((*entry).second);
	
	return result;
}

PMReal ViewPortAttributes::GetAttrReal(VPAttrID attr, PMReal defVal) const
{
	PMReal result = defVal;
	
	VPAttrMap::const_iterator entry = fViewPortAttrMap.find(attr);
	if (entry != fViewPortAttrMap.end()) result = entry->second;
	
	return result;
}

void ViewPortAttributes::SetAttr(VPAttrID attr, PMReal value)
{
	fViewPortAttrMap[attr] = value;
}

void ViewPortAttributes::SetAttr(VPAttrID attr, int32 value)
{
	fViewPortAttrMap[attr] = PMReal(value);
}
