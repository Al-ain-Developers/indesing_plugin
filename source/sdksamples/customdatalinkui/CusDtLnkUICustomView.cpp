//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalinkui/CusDtLnkUICustomView.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IBoolData.h"
#include "IGraphicsPort.h"
#include "IImageStream.h"
#include "IImportProvider.h"
#include "IImportPreview.h"
#include "IK2ServiceRegistry.h"
#include "IK2ServiceProvider.h"
#include "IPMStream.h"
#include "ISysFileData.h"

// General includes:
#include "StreamUtil.h"
#include "GraphicsExternal.h"	// _t_AGM...
#include "DVControlView.h"
#include "AcquireModalCursor.h"
#include "IInterfaceColors.h"

// Project includes:
#include "CusDtLnkUIID.h"

#include "AGMGraphicsContext.h"
#include "AutoGSave.h"

  
/** Color space family from AGM, subsetted to meet our needs here.
	@ingroup customdatalinkui
*/
enum SubsettedAGMColorSpaceFamily
{
	/** */
	kDontCare,
	/** */
	kAGMCsRGB
	/** */
};


/** Implements IControlView; provides custom control view for a widget.

	
	@ingroup customdatalinkui
*/

class CusDtLnkUICustomView : public DVControlView
{
	typedef DVControlView inherited;
	
public:
	/** Constructor
	@param boss interface on boss object on which interface is being aggregated
	*/
	CusDtLnkUICustomView(IPMUnknown* boss);

	/** Destructor
	*/
	virtual ~CusDtLnkUICustomView();	

	/** Called when widget is being initialised.
	@param widgetId [IN] specifies WidgetID to associate with this widget
	@param frame [IN] specifies bounding box for the control
	@param rsrcID [IN] specifies resource to associate with this widget
	*/
	virtual void Init(const WidgetID& widgetId, const PMRect& frame, RsrcID rsrcID);

	/** Called when widget should draw.
	@param viewPort [IN] specifies viewport
	@param updateRgn [IN] specifies update region
	*/
	virtual void Draw(IViewPort* viewPort, SysRgn updateRgn);

	/** Called when widget should draw.
	@param drawbotP [IN] specifies the drawbot object pointer to use
	*/
//	virtual void DV_Draw(dvaui::drawbot::Drawbot *drawbotP) const;

private:

	void deleteBuffers();
	ErrorCode createPreview(const IDFile& previewFile, const uint32 nWidthWidget, const uint32 nHeightWidget, const uint8 backGrey);

	int32			fCachedImWidth ;
	int32			fCachedImHeight ;
	AGMImageRecord *fpCurAGMImage;
	uint8		   *fDataBuffer;
	IDFile			fCurImageSysFile;
};

#pragma mark CusDtLnkUICustomView implementation

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PERSIST_PMINTERFACE(CusDtLnkUICustomView, kCusDtLnkUICustomViewImpl)

/* Constructor
*/
CusDtLnkUICustomView::CusDtLnkUICustomView(IPMUnknown* boss) :	inherited(boss),
																fpCurAGMImage(nil),
																fCachedImWidth(0),
																fCachedImHeight(0),
																fDataBuffer(nil)
{
}

/* Destructor
*/
CusDtLnkUICustomView::~CusDtLnkUICustomView()
{
    deleteBuffers();
}

void CusDtLnkUICustomView::deleteBuffers()
{
	if(fpCurAGMImage) 
	{
		delete [] fDataBuffer;
		delete fpCurAGMImage;
	
		fpCurAGMImage = nil;
	}
}

/* Init
*/
void CusDtLnkUICustomView::Init(const WidgetID& widgetId, const PMRect& frame, RsrcID rsrcID)
{
	inherited::Init(widgetId, frame, rsrcID);
}

/* Draw
*/
void CusDtLnkUICustomView::Draw(IViewPort* viewPort, SysRgn updateRgn)
{
	AGMGraphicsContext gc(viewPort, this, updateRgn);
	InterfacePtr<IGraphicsPort>	gPort(gc.GetViewPort(), UseDefaultIID());	// IID_IGRAPHICSPORT);
	ASSERT(gPort);
	if(!gPort) 
	{
		return;
	}

	AutoGSave autoGSave(gPort);

	do {
		ErrorCode resultOfCreatingPreview = kFailure;

		InterfacePtr<IInterfaceColors>iInterfaceColors(GetExecutionContextSession(), IID_IINTERFACECOLORS);
		ASSERT(iInterfaceColors);
		if(!iInterfaceColors)
		{
			break;
		}
		RealAGMColor whiteFill;
		iInterfaceColors->GetRealAGMColor(kInterfaceWhite, whiteFill);
		
		RealAGMColor defaultGreyFill;
		iInterfaceColors->GetRealAGMColor(kInterfacePaletteFill, defaultGreyFill); 
		
		PMRect frame( this->GetInnerContentFrame() );

		// Dropped the 3d border effect
		uint32 nWidthWidget = ToInt32(frame.Width());  
		uint32 nHeightWidget = ToInt32(frame.Height());
		
		// get filespec currently associated with widget
		InterfacePtr<ISysFileData> iImageSysFile(this, IID_ISYSFILEDATA);
		ASSERT(iImageSysFile);
		if(!iImageSysFile)
		{
			break;
		}
		IDFile previewFile = iImageSysFile->GetSysFile(); 
		
		if(!fpCurAGMImage || (fCurImageSysFile != previewFile)) 
		{
			// Take average greyvalue of what we're filling background to
			uint8 backgroundGrey = ToInt32(Round(255.0* (whiteFill.red +  whiteFill.green + whiteFill.blue)/3.0));
			// Create another preview, if we need to
			resultOfCreatingPreview = this->createPreview(previewFile, nWidthWidget, nHeightWidget, backgroundGrey);
			
		} 
		else 
		{
			// That's OK- assume safe to use the old one
			resultOfCreatingPreview = kSuccess;
		}
		
	
		// if we got an image, then display it
		// otherwise, draw a red diagonal line through the widget
		if (resultOfCreatingPreview == kSuccess) 
		{
			// Fill the background with white
			gPort->setrgbcolor(whiteFill.red, whiteFill.green, whiteFill.blue);
			gPort->rectpath(frame);
			gPort->fill();
			PMReal imageWidth = (fpCurAGMImage->bounds.xMax - fpCurAGMImage->bounds.xMin);
			PMReal imageHeight = (fpCurAGMImage->bounds.yMax - fpCurAGMImage->bounds.yMin);
			PMReal xOffset = frame.GetHCenter() - imageWidth/2;
			PMReal yOffset = frame.GetVCenter() - imageHeight/2;
			// Centered
			gPort->translate(xOffset, yOffset);
			PMMatrix theMatrix;	// No transform 
			ASSERT(fpCurAGMImage);
			gPort->image(fpCurAGMImage, theMatrix, 0);
		}
		else 
		{
			// Fill with the palette default background fill
			gPort->setrgbcolor(defaultGreyFill.red, defaultGreyFill.green, defaultGreyFill.blue);
			gPort->rectpath(frame);
			gPort->fill();
			// Render a red stroke over the background
			gPort->setrgbcolor(PMReal(1), PMReal(0), PMReal(0));
			gPort->setlinewidth(PMReal(2));
			gPort->setmiterlimit(PMReal(2));  // SPAM: what units does this use?
			gPort->moveto(frame.Left()+2, frame.Bottom()-2);
			gPort->lineto(frame.Right()-2, frame.Top()+2);
			gPort->stroke();
		}	
	} while(kFalse);
}

/* DV_Draw

#include "DVAPublicIncludes.h"
#include "DVPublicUtilities.h"
#include "dvaui::drawbot::Drawbot.h" //currently drawing drawbot requires some private headers

void CusDtLnkUICustomView::DV_Draw(dvaui::drawbot::Drawbot *drawbotP) const
{
	ErrorCode resultOfCreatingPreview = kFailure;

	InterfacePtr<IInterfaceColors> iInterfaceColors(GetExecutionContextSession(), UseDefaultIID());
	ASSERT(iInterfaceColors);
	
	if (!iInterfaceColors)
	{
		return;
	}
	
	RealAGMColor whiteFill, defaultGreyFill;

	iInterfaceColors->GetRealAGMColor(kInterfaceWhite,			whiteFill);
	iInterfaceColors->GetRealAGMColor(kInterfacePaletteFill,	defaultGreyFill); 
	
	PMRect frame(this->GetInnerContentFrame());

	uint32 nWidthWidget( ToInt32(frame.Width()) ), nHeightWidget( ToInt32(frame.Height()) );
	
	// get filespec currently associated with widget
	InterfacePtr<ISysFileData> iImageSysFile(this, IID_ISYSFILEDATA);
	ASSERT(iImageSysFile);

	if(!iImageSysFile)
	{
		return;
	}

	IDFile previewFile = iImageSysFile->GetSysFile(); 
	
	if (!fpCurAGMImage || (fCurImageSysFile != previewFile)) 
	{
		// Take average greyvalue of what we're filling background to
		uint8 backgroundGrey = ToInt32(Round(255.0f * (whiteFill.red + whiteFill.green + whiteFill.blue)/3.0f));
		
		// Create another preview, if we need to
		resultOfCreatingPreview = this->createPreview(previewFile, nWidthWidget, nHeightWidget, backgroundGrey);			
	} 
	else 
	{
		// That's OK- assume safe to use the old one
		resultOfCreatingPreview = kSuccess;
	}

	// get the drawbot drawing surface
	dvaui::drawbot::SurfaceInterface *surfaceP = drawbotP->GetSurface();

	
	// if we got an image, then display it
	// otherwise, draw a red diagonal line through the widget
	if (resultOfCreatingPreview == kSuccess) 
	{
		// Fill the background with white
		dv_utils::DVFillRect( drawbotP, whiteFill, frame );
	
		PMReal imageWidth( (fpCurAGMImage->bounds.xMax  - fpCurAGMImage->bounds.xMin));
		PMReal imageHeight( (fpCurAGMImage->bounds.yMax - fpCurAGMImage->bounds.yMin));
		PMReal xOffset( frame.GetHCenter() - imageWidth  * 0.5f);
		PMReal yOffset( frame.GetVCenter() - imageHeight * 0.5f);
		
		dvacore::geom::PointF32 imageDrawPoint( ToFloat(xOffset), ToFloat(yOffset) );
		
		dvaui::drawbot::SaveAndRestoreStateStack  gstackSave( surfaceP );

		ASSERT(fpCurAGMImage);
		surfaceP->DrawImage( fpCurAGMImage.baseAddr, imageDrawPoint, 1.0f ); 
	}
	else 
	{
		// Fill with the palette default background fill
		dv_utils::DVFillRect( drawbotP, defaultGreyFill, frame );

		// Render a red stroke over the background
		dvaui::drawbot::PenP  penP( *drawbotP, dvaui::drawbot::ColorRGBA(1.0f, 0.0f, 0.0d, 1.0f), 2.0f );
		dvaui::drawbot::PathP pathP( *drawbotP );
		
		pathP->MoveTo( dv_utils::ToPointF32(frame.Left()  + 2, frame.Bottom() - 2) );
		pathP->LineTo( dv_utils::ToPointF32(frame.Right() - 2, frame.Top()    + 2) );
		surfaceP->StrokePath( *penP, *pathP );
	}	
}
*/

/*
*/
ErrorCode CusDtLnkUICustomView::createPreview( const IDFile& previewFile, const uint32 width, const uint32 height, const uint8 backGrey )
{
	// get source stream (image file to preview)
	InterfacePtr<IPMStream>	fileStream(StreamUtil::CreateFileStreamRead(previewFile));

	if(fileStream == nil) 
	{
		return kFailure;
	}
	
	InterfacePtr<IK2ServiceRegistry>	serviceRegistry(GetExecutionContextSession(), UseDefaultIID());
	ASSERT(serviceRegistry);
	
	if(!serviceRegistry) 
	{
		return kFailure;
	}
	
	int	numHandlers = serviceRegistry->GetServiceProviderCount(kImportProviderService);
	
	for (int i = 0; i < numHandlers; i++) 
	{
		InterfacePtr<IK2ServiceProvider> provider(serviceRegistry->QueryNthServiceProvider(kImportProviderService, i));
		InterfacePtr<IImportProvider> importProvider(provider, IID_IIMPORTPROVIDER);
		
		if (importProvider && importProvider->CanImportThisStream(fileStream) == IImportProvider::kFullImport) 
		{
			InterfacePtr<IImportPreview> preview(importProvider, IID_IIMPORTPREVIEW);
			if(preview) 
			{
				bool16 reallocateNeeded = kTrue;
				
				if( (this->fCachedImHeight == height) && (this->fCachedImWidth == width)) 
				{
					reallocateNeeded = kFalse;
				}

				if(reallocateNeeded) 
				{
					// Trash any existing storage
					this->deleteBuffers();
					
					fpCurAGMImage = new AGMImageRecord;
					memset (fpCurAGMImage, 0, sizeof(AGMImageRecord));

					//create the preview		
					
					fpCurAGMImage->bounds.xMin 			= 0;
					fpCurAGMImage->bounds.yMin 			= 0;
					fpCurAGMImage->bounds.xMax 			= width;
					fpCurAGMImage->bounds.yMax 			= height;
					fpCurAGMImage->byteWidth 			= 3*width;
					// For optimal performance, the pixel dimensions should be multiples of
					// 4, then you can use:
						//fpCurAGMImage->byteWidth = BYTES2ROWBYTES(3*width);
					fpCurAGMImage->colorSpace 			= kAGMCsRGB;
					fpCurAGMImage->bitsPerPixel 		= 24;
					fpCurAGMImage->decodeArray 			= 0;
					fpCurAGMImage->colorTab.numColors 	= 0;
					fpCurAGMImage->colorTab.theColors 	= nil;

			
					this->fDataBuffer = new uint8[((fpCurAGMImage->byteWidth) * height)];
					ASSERT(this->fDataBuffer);
					fpCurAGMImage->baseAddr = static_cast<void *>(this->fDataBuffer);

				}

				ASSERT(fpCurAGMImage);
				if (fpCurAGMImage == NULL)
				{
					break;
				}
				//set the background to be grey
				::memset(fpCurAGMImage->baseAddr, backGrey, (fpCurAGMImage->byteWidth) * height);
		
				if (fpCurAGMImage->baseAddr) 
				{
					 AcquireWaitCursor busyCursor;

					preview->Create24bitRGBPreview( (uint8*)fpCurAGMImage->baseAddr, width, height, fileStream, kTrue );
					fCurImageSysFile = previewFile;
					return kSuccess;
				}
			}
		}
		// Be sure to reset the stream
		fileStream->Seek(0,kSeekFromStart);
	} // i loop ove handlers
	return kFailure;
}

//	end, File:	CusDtLnkUICustomView.cpp
