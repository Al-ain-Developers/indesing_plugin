//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/paneltreeview/PnlTrvCustomView.cpp $
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
#include "IGraphicsPort.h"
#include "IImageStream.h"
#include "IImportProvider.h"
#include "IImportPreview.h"
#include "IK2ServiceRegistry.h"
#include "IK2ServiceProvider.h"
#include "IPMStream.h"
#include "ISysFileData.h"
#include "IInterfaceColors.h"

// General includes:
#include "AGMGraphicsContext.h"
#include "AutoGSave.h"
#include "StreamUtil.h"
#include "GraphicsExternal.h"	// _t_AGM...
#include "DVControlView.h"
#include "ProgressBar.h"
#include "AcquireModalCursor.h"
// Project includes:
#include "PnlTrvID.h"

  
/** Color space family from AGM, subsetted to meet our needs here.
	@ingroup paneltreeview
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

	
	@ingroup paneltreeview
*/

class PnlTrvCustomView : public DVControlView
{
	typedef DVControlView inhertied;
public:
	/** Constructor
	@param boss interface on boss object on which interface is being aggregated
	*/
	PnlTrvCustomView(IPMUnknown* boss);

	/** Destructor
	*/
	virtual ~PnlTrvCustomView();	

	/** Called when widget is being initialised.
	@param widgetId [IN] specifies WidgetID to associate with this widget
	@param frame [IN] specifies bounding box for the control
	@param rsrcID [IN] specifies resource to associate with this widget
	*/
	virtual void Init(
		const WidgetID& widgetId, const PMRect& frame, RsrcID rsrcID);

	/** Called when widget should draw.
	@param viewPort [IN] specifies viewport
	@param updateRgn [IN] specifies update region
	*/
	virtual void Draw(IViewPort* viewPort, SysRgn updateRgn);

private:
	void deleteBuffers();
	ErrorCode createPreview(
		const IDFile& previewFile, uint32 nWidthWidget, uint32 nHeightWidget, uint8 backGrey);

	AGMImageRecord *fpCurAGMImage;
	IDFile fCurImageSysFile;
	uint8* fDataBuffer;
	int32 fCachedImWidth;
	int32 fCachedImHeight;
};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PERSIST_PMINTERFACE(PnlTrvCustomView, kPnlTrvCustomViewImpl)


/* Constructor
*/
PnlTrvCustomView::PnlTrvCustomView(IPMUnknown* boss)
    : inhertied(boss),
      fpCurAGMImage(nil),
	  fDataBuffer(nil),
	  fCachedImWidth(0),
	 fCachedImHeight(0)
{
}


/* Destructor
*/
PnlTrvCustomView::~PnlTrvCustomView()
{
    deleteBuffers();
    
}

void PnlTrvCustomView::deleteBuffers()
{
	if(fpCurAGMImage) {
		//delete (uint8 *)fpCurAGMImage->baseAddr;
		delete [] fDataBuffer;
		delete fpCurAGMImage;
		fpCurAGMImage = nil;
	}

	
}

/* Init
*/
void PnlTrvCustomView::Init(
	const WidgetID& widgetId, const PMRect& frame, RsrcID rsrcID)
{
	inhertied::Init(widgetId, frame, rsrcID);
}


/* Draw
*/
void PnlTrvCustomView::Draw(IViewPort* viewPort, SysRgn updateRgn)
{
	
 	
	AGMGraphicsContext gc(viewPort, this, updateRgn);
	InterfacePtr<IGraphicsPort>
		gPort(gc.GetViewPort(), UseDefaultIID());	// IID_IGRAPHICSPORT);
	ASSERT(gPort);
	if(!gPort) {
		return;
	}

	AutoGSave autoGSave(gPort);

	do {
		ErrorCode resultOfCreatingPreview = kFailure;

		InterfacePtr<IInterfaceColors>
			iInterfaceColors(GetExecutionContextSession(), IID_IINTERFACECOLORS);
		ASSERT(iInterfaceColors);
		if(!iInterfaceColors){
			break;
		}
		RealAGMColor whiteFill;
		iInterfaceColors->GetRealAGMColor(kInterfaceWhite, whiteFill);
		RealAGMColor defaultGreyFill;
		iInterfaceColors->GetRealAGMColor(kInterfacePaletteFill, defaultGreyFill); 
		
		PMRect frame = GetFrame();
		frame.MoveTo(0, 0);             // get into local coordinates

		uint32 nWidthWidget=1;
		uint32 nHeightWidget=1;
	

		// Dropped the 3d border effect
		nWidthWidget = ToInt32(frame.Width());  
		nHeightWidget = ToInt32(frame.Height());
		
		// get filespec currently associated with widget
		InterfacePtr<ISysFileData> iImageSysFile(this, IID_ISYSFILEDATA);
		ASSERT(iImageSysFile);
		if(!iImageSysFile)
		{
			break;
		}
		IDFile previewFile = iImageSysFile->GetSysFile(); 
		
		if(fCurImageSysFile != previewFile) {
			// Take average greyvalue of what we're filling background to
			uint8 backgroundGrey = ToInt32(Round(
				255.0* (whiteFill.red +  whiteFill.green + whiteFill.blue)/3.0));
			// Create another preview, if we need to
			resultOfCreatingPreview = this->createPreview(previewFile, nWidthWidget, nHeightWidget, backgroundGrey);
			
		} else {
			// That's OK- assume safe to use the old one
			resultOfCreatingPreview = kSuccess;
		}
		
		// if we got an image, then display it
		// otherwise, draw a red diagonal line through the widget
		if (resultOfCreatingPreview == kSuccess) {
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
		else {
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
/*
*/
ErrorCode PnlTrvCustomView::createPreview(
	const IDFile& previewFile, 
	uint32 width, 
	uint32 height, 
	uint8 backGrey
	)
{
	do
	{
		// get source stream (image file to preview)
		InterfacePtr<IPMStream>
			fileStream(StreamUtil::CreateFileStreamRead(previewFile));

		if(fileStream == nil) {
			break;
		}
		InterfacePtr<IK2ServiceRegistry>	serviceRegistry(GetExecutionContextSession(), UseDefaultIID());
		ASSERT(serviceRegistry);
		if(!serviceRegistry) {
			break;
		}
		int	numHandlers = serviceRegistry->GetServiceProviderCount(kImportProviderService);
		for (int i = 0; i < numHandlers; i++) {

			InterfacePtr<IK2ServiceProvider> provider(
				serviceRegistry->QueryNthServiceProvider(kImportProviderService, i));
			InterfacePtr<IImportProvider> importProvider(provider, IID_IIMPORTPROVIDER);
			
			if (importProvider && 
				importProvider->CanImportThisStream(fileStream) == IImportProvider::kFullImport) {
			
				InterfacePtr<IImportPreview> preview(importProvider, IID_IIMPORTPREVIEW);
				if(preview) {
				

					
					bool16 reallocateNeeded = kTrue;
					// If the dimensions we're trying to write to have 
					// changed, do a realloc. This might happen for instance
					// if we decide to let the widget be resizable in some way,
					// either programmatically by us or by the end-user. But at
					// present (Mar 2005), the image widget is fixed dimension
					if( (this->fCachedImHeight == height) &&
						(this->fCachedImWidth == width)) {
							reallocateNeeded = kFalse;
						}

					if(reallocateNeeded) {
						// Trash any existing storage
						this->deleteBuffers();
					
						fpCurAGMImage = new AGMImageRecord;
						memset (fpCurAGMImage, 0, sizeof(AGMImageRecord));
						fpCurAGMImage->bounds.xMin 			= 0;
						fpCurAGMImage->bounds.yMin 			= 0;
						fpCurAGMImage->bounds.xMax 			= width;
						fpCurAGMImage->bounds.yMax 			= height;
						fpCurAGMImage->byteWidth 			= 3*width; //BYTES2ROWBYTES(3*width);
						fpCurAGMImage->colorSpace 			= kAGMCsRGB;
						fpCurAGMImage->bitsPerPixel 		= 24;
						fpCurAGMImage->decodeArray 			= 0;
						fpCurAGMImage->colorTab.numColors 	= 0;
						fpCurAGMImage->colorTab.theColors 	= nil;

						this->fDataBuffer =	new uint8[((fpCurAGMImage->byteWidth) * height)];
						ASSERT(this->fDataBuffer);
						fpCurAGMImage->baseAddr = static_cast<void *>(this->fDataBuffer);

						this->fCachedImHeight = height;
						this->fCachedImWidth = width;
					}
					ASSERT(fpCurAGMImage);
					//set the background to be grey
					::memset(fpCurAGMImage->baseAddr, backGrey, (fpCurAGMImage->byteWidth) * height);
			
					if (fpCurAGMImage->baseAddr) {
						AcquireWaitCursor busyCursor;
						preview->Create24bitRGBPreview( (uint8*)fpCurAGMImage->baseAddr,
							width, height, fileStream, kTrue );
						fCurImageSysFile = previewFile;
						// Exit, we don't need another handler
						
						return kSuccess;
					}
				}
			}
			// Be sure to reset the stream if we're trying out another handler
			fileStream->Seek(0,kSeekFromStart);
		} // i loop over handlers

		

	} while(false);
	
	return kFailure;
}

//	end, File:	PnlTrvCustomView.cpp
