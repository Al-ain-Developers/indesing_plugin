//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/ViewPortAttributes.h $
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
#ifndef __ViewPortAttributes__
#define __ViewPortAttributes__

#include "IControlView.h"
#include "IViewPortAttributes.h"
#include "PMRect.h"
#include "HelperInterface.h"
#include <map>

#pragma export on


class PUBLIC_DECL ViewPortAttributes : public IViewPortAttributes
{
public:
	ViewPortAttributes(IPMUnknown * boss);
	virtual ~ViewPortAttributes();
	
	virtual void Initialize(IDataBase* db, IControlView *controlView);
		// Initializes the attributes available by the Get methods below.
		// A ViewPort should call Initialize() before each time it begins
		// to draw in order to be sure that the attributes are up to date.
		// The optional IDataBase argument can be used by initialize to get preference
		// settings from the given database, when it is known that the ViewPort
		// is drawing one document.
		// Note: Initialization of the ViewPortBounds must be done 
		// explicitly with SetViewPortBounds().

	virtual PMReal GetViewPortResolution(void) const;
	virtual void SetViewPortResolution(PMReal resolution);
		// Get/Set the resolution of the view port. Currently this is used
		// when importing an EPS because MPS requires the output device's
		// resolution when creating the display list.

	virtual bool16 GetViewPortOutputOPIComments(void) const;
	virtual void SetViewPortOutputOPIComments( bool16 b ) ;
		// Does the ViewPort want to output OPI comments?

	virtual bool16 GetViewPortCacheing(void) const;
	virtual void SetViewPortCacheing(bool16 cacheing);
		// Does the ViewPort want to optimize re-display by cacheing things
		// like images? Cacheing is most useful when diplaying on-screen;
		// for printing and exporting, it is typically not recommended.

	virtual int32 GetViewPortBitmapSampling(void) const;
	virtual void SetViewPortBitmapSampling(int32 sampling);
		// What type of bitmap data does the ViewPort want to display, export,
		// or print? Hi-res, low-res, or omit?

	virtual int32 GetViewPortVectorSampling(void) const;
	virtual void SetViewPortVectorSampling(int32 sampling);
		// What type of vector data does the ViewPort want to display, export,
		// or print? Hi-res, low-res, optimized or omit?

	virtual bool16 GetViewPortFilterContent(void) const;
	virtual void SetViewPortFilterContent(bool16 filter);
		// Does this view port want to filter content

	virtual PMReal GetViewPortLineScreen(void) const;
	virtual void SetViewPortLineScreen( const PMReal& n ) ;
		// Get the line screen of the view port. Currently this is used
		// when in the calculation of the desired resolution when BitmapSampling
		// is set to Optimize. Currently this is only set up for PS view ports.
	virtual bool16 GetViewPortTiling(void) const;
	virtual void SetViewPortTiling( bool16 b );
		// Does this ViewPort support IagmServer_Image tiling? Rather
		// than making separate IGraphicsPort::image() calls for each band
		// of a large image, one image() call can be made with an IagmServer_Image,
		// allowing the entire image to be accessed.
	virtual bool16 GetViewPortProofPrint(void) const;
	virtual void SetViewPortProofPrint(bool16 b);
		// Are we currently doing a proof print? Images, EPSs and PDFs draw
		// as gray box.
	virtual bool16 GetViewPortDisallowImageCrop(void) const;
	virtual void SetViewPortDisallowImageCrop(bool16 b);
		// Do we want to make sure that we get all the image data--even
		// what has been cropped by the frame?
	virtual bool16 GetViewPortOmitEPS(void) const;
	virtual void SetViewPortOmitEPS(bool16 b);
		// Should placed EPSs be omitted?
	virtual bool16 GetViewPortOmitPDF(void) const;
	virtual void SetViewPortOmitPDF(bool16 b);
		// Should placed PDFs be omitted?
	virtual bool16 GetViewPortOmitBitmapImages(void) const;
	virtual void SetViewPortOmitBitmapImages(bool16 b) ;
		// Should placed bitmap images be omitted?

	virtual void SetViewPortDrawPasteboardShadow (bool16 drawShadow);
	
	virtual bool16 GetViewPortDrawPasteboardShadow (void) const;
	
	virtual void SetViewPortDrawPageShadow (bool16 drawShadow);
	
	virtual bool16 GetViewPortDrawPageShadow (void) const;

	virtual bool16 GetViewPortIsPrintingPort (void) const;
	virtual void SetViewPortIsPrintingPort( bool16 b );
		// Indicates if screen drawing things should happen
		// or not. This is the same concept as IShape::kPrinting
		// which is passed to drawing methods, though at port level.

	virtual bool32 IsAttrDefined(VPAttrID attr) const;
	virtual void SetAttr(VPAttrID attr, int32 value);
	virtual void SetAttr(VPAttrID attr, PMReal value);
	virtual int32 GetAttr(VPAttrID attr, int32 defVal = 0) const;
	virtual PMReal GetAttrReal(VPAttrID attr, PMReal defVal = 0.) const;
	
protected:
	PMReal fViewPortResolution;
	PMReal fViewPortLineScreen;
	bool16 fViewPortOutputOPI;
	bool16 fViewPortDoCacheing;
	int32 fViewPortBitmapSampling;
	int32  fViewPortVectorSampling;
	bool16 fViewPortFilterContent;
	bool16 fViewPortDoTiling;
	bool16 fViewPortProofPrint;
	bool16 fViewPortDisallowImageCrop;
	bool16 fViewPortOmitPDF;
	bool16 fViewPortOmitEPS;
	bool16 fViewPortOmitBitmapImages;
	bool16 fViewPortDrawPasteboardShadow;
	bool16 fViewPortDrawPageShadow;
	bool16 fViewPortIsPrintingPort;
	
	typedef std::map<VPAttrID, PMReal> VPAttrMap;
	VPAttrMap fViewPortAttrMap;
	
DECLARE_HELPER_METHODS()
};

#pragma export off

#endif
