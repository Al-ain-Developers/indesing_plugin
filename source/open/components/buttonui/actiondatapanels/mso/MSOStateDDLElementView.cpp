//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/mso/MSOStateDDLElementView.cpp $
//  
//  Owner: Michele Stutzman
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
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

// ----- Interfaces -----

#include "IAppearanceSuite.h"
#include "IIntData.h"
#include "IUIDData.h"
#include "IControlView.h"
#include "IGraphicsPort.h"
#include "IUIColorSpec.h"
#include "IWidgetParent.h"
#include "IWindow.h"

// ----- Includes -----

#include "AGMGraphicsContext.h"
#include "AutoGSave.h"
#include "DVOwnerDrawDropDownListView.h"
#include "FormFieldUIDefs.h"

// ----- Utility files -----

#include "DrawStringUtils.h"
#include "IFormFieldUtils.h"
#include "StringUtils.h"
#include "UserInterfaceUtils.h"
#include "IWidgetUtils.h"

// ----- ID.h files -----

#include "FormFieldUIID.h"


const int32 kMaxThumbnailMaxSize = 128;

class MSOStateDDLElementView : public DVDropDownElementView 
{
	typedef DVDropDownElementView inherited;
	
public:
	MSOStateDDLElementView(IPMUnknown *boss) : inherited(boss), fBGColorLoaded(kFalse) { ; }
	~MSOStateDDLElementView() { ; }
	
	virtual void Draw(IViewPort* viewPort, SysRgn updateRgn = nil); 
	virtual void WindowHidden();

protected:
	virtual void DrawContent(IViewPort *viewport, SysRgn updateRgn);

	virtual void DrawBackground(IGraphicsPort* gPort,const PMRect& frame);

private:
	void DrawTextContent(AGMGraphicsContext* gc, PMRect myFrame, PMReal textLeftEdge, PMReal textRowHeight);

	bool16 fBGColorLoaded;
	int32  fBGColor;
	int32  fHiliteBGColor;
};


// =============================================================================
// *** MSOStateDDLElementView impl ***
// -----------------------------------------------------------------------------

CREATE_PERSIST_PMINTERFACE(MSOStateDDLElementView, kMSOStateDDLElementViewImpl)

// -----------------------------------------------------------------------------
// borrowed from UIColorSwatchElementView.cpp

void MSOStateDDLElementView::DrawBackground(IGraphicsPort* gPort, const PMRect& frame)
{
	bool16 isHilited = IsElementHilited() && !IsDrawingAsDefaultItem();
	if (!fBGColorLoaded)
	{
		// First check if any ancestor has set the background color.
		InterfacePtr<IWidgetParent> parentHolder(this, UseDefaultIID());
		InterfacePtr<IUIColorSpec> ancestorColor((IUIColorSpec*) parentHolder->QueryParentFor(IID_IUICOLORSPEC));
		if (ancestorColor && (ancestorColor->GetBackgroundColorID() != kInvalidInterfaceColor))
			fBGColor = ancestorColor->GetBackgroundColorID();
		else	//  Not a valid color, use our default one.
			fBGColor = kInterfacePaletteFill;

				
		if (ancestorColor && (ancestorColor->GetBackgroundHiliteColorID() != kInvalidInterfaceColor))
			fHiliteBGColor = ancestorColor->GetBackgroundHiliteColorID();
		else	//  Not a valid color, use our default one.
			fHiliteBGColor = kInterfaceHighLight;
			
		fBGColorLoaded = kTrue;
	}

	RealAGMColor background;
	InterfacePtr<IInterfaceColors> icolors( GetExecutionContextSession(), IID_IINTERFACECOLORS );
	icolors->GetRealAGMColor(isHilited ? fHiliteBGColor : fBGColor, background);	
	AutoGSave autoGSave(gPort);
	gPort->setrgbcolor(background.red, background.green, background.blue);
	gPort->rectpath(frame);	
	gPort->fill();
} // end DrawBackground()

// -----------------------------------------------------------------------------

void MSOStateDDLElementView::Draw(IViewPort* viewPort, SysRgn updateRgn)
{	
	InterfacePtr<IUIDData> msoData(this, UseDefaultIID());

	IDataBase* db = nil;
	if (msoData)
		db = msoData->GetItemDataBase();
	if (db == nil) 
		return;
	
	inherited::Draw(viewPort, updateRgn);
} // end Draw()

void MSOStateDDLElementView::DrawContent(IViewPort* viewport, SysRgn updateRgn)
{
	AGMGraphicsContext gc(viewport, this, updateRgn);
	InterfacePtr<IGraphicsPort> gPort(gc.GetViewPort(), UseDefaultIID());
	AutoGSave gSave(gPort);
	InterfacePtr<const IWidgetParent> wp(this, UseDefaultIID());
	InterfacePtr<const IControlView> parentView((IControlView*)wp->QueryParentFor(IID_ICONTROLVIEW));

	PMRect myFrame = GetFrame();
	if (IsDrawingAsDefaultItem())
		myFrame = parentView->GetFrame();

	myFrame.MoveTo(4, 0);
	PMReal textLeftEdge = myFrame.Left();
	PMReal textRowHeight = myFrame.Height();

	if (!IsDrawingAsDefaultItem())		// Draw the thumbnail if the drop-down is open
	{
		AGMImageAccessor *thumbnail = nil;
		InterfacePtr<IUIDData> msoData(this, UseDefaultIID());
		InterfacePtr<IIntData> stateData(this, UseDefaultIID());
		bool bHaveThumb = Utils<IFormFieldUtils>()->GetAppearanceThumbnail(msoData->GetRef(), stateData->Get(),
			kMaxThumbnailMaxSize,
			kMaxThumbnailMaxSize, &thumbnail)
			== kSuccess;
		if (bHaveThumb)
		{
			// It's easy to move frame computation to another function but leaving it here for the sake of
			// ease of understanding.
			PMRect frameRect;
			frameRect.SetDimensions(kMSOStateMediumRowHeight, kMSOStateMediumRowHeight);
			frameRect.MoveTo(0, 0);						// get into local coordinates

			frameRect.Inset(3, 3);
			frameRect.Round();

			PMReal frameWidth = frameRect.Width();
			PMReal frameHeight = frameRect.Height();

			Int32Rect	bounds = thumbnail->GetBounds();
			int32 thumbWidth = bounds.right - bounds.left;
			int32 thumbHeight = bounds.bottom - bounds.top;

			PMReal scaleFactor = std::min(frameWidth / thumbWidth, frameHeight / thumbHeight);

			PMRect thumbRect;
			thumbRect.Left() = frameRect.Left() + (frameWidth - thumbWidth*scaleFactor) / 2.0;
			thumbRect.Top() = frameRect.Top() + (frameHeight - thumbHeight*scaleFactor) / 2.0;
			thumbRect = thumbRect.Round();
			thumbRect.Right() = thumbRect.Left() + thumbWidth*scaleFactor;
			thumbRect.Bottom() = thumbRect.Top() + thumbHeight*scaleFactor;
			thumbRect = thumbRect.Round();

			PMMatrix matrix(scaleFactor,
				0,
				0,
				scaleFactor,
				thumbRect.Left() + 1,
				thumbRect.Top() + 1
				);

			// Draw the thumbnail image
			gPort->setrgbcolor(PMReal(1.0), PMReal(1.0), PMReal(1.0));
			gPort->rectfill(thumbRect);
			gPort->image(const_cast<AGMImageRecord*>(thumbnail->GetAGMImageRecord()), matrix, 0);

			// ----- Frame the swatch.
			gPort->setrgbcolor(PMReal(0), PMReal(0), PMReal(0));
			gPort->rectstroke(thumbRect);

			// Destroy the thumbnail
			delete thumbnail;

			// position text to the right of the thumbnail
			textLeftEdge = frameRect.Right() + 4;
			textRowHeight = kMSOStateMediumRowHeight;
		}
	}

	DrawTextContent(&gc, myFrame, textLeftEdge, textRowHeight);
}

void MSOStateDDLElementView::DrawTextContent(AGMGraphicsContext* gc,PMRect myFrame, PMReal textLeftEdge, PMReal textRowHeight)
{
	// Get the name
	InterfacePtr<IUIDData> msoData(this, UseDefaultIID());
	InterfacePtr<IIntData> stateData(this, UseDefaultIID());
	PMString stateName(Utils<Facade::IAppearanceItemFacade>()->GetStateName(msoData->GetRef(), stateData->Get()));

	// Get the font to use
	InterfacePtr<IWidgetParent> wp(this, UseDefaultIID());
	InterfacePtr<const IWindow> window((IWindow*)wp->QueryParentFor(IID_IWINDOW));
	bool16 isHilited = IsHilited();
	InterfaceFontInfo const &fontInfo = (isHilited && !IsDrawingAsDefaultItem()) ? window->GetHiliteFont() : window->GetFont();

	PMReal yPosition = Utils<IWidgetUtils>()->GetViewYPosition(gc, fontInfo, textRowHeight);
	PMPoint drawPt(textLeftEdge, yPosition);

	PMReal textWidth(myFrame.Right() - drawPt.X());
	stateName = StringUtils::PMEllipsizeString(gc, textWidth, stateName, fontInfo);
	// Get the text color
	IInterfaceColors::InterfaceColor textColor = kInterfaceTextColor;
	if (isHilited)
		textColor = kInterfaceHighLightText;
	if (!this->IsEnabled())
		textColor = dv_utils::IsUIInterfaceBright() ? kInterfaceDisabledGray : kInterface32Gray;

	// Draw the text
	StringUtils::PMDrawString(gc, drawPt, stateName, fontInfo, textColor);
}

void MSOStateDDLElementView::WindowHidden()
{
	InterfacePtr<IUIDData> msoData(this, UseDefaultIID());
	if (msoData) 
		msoData->Set(nil, kInvalidUID);

	InterfacePtr<IIntData> stateData(this, UseDefaultIID());
	if (stateData)
		stateData->Set(-1);

	inherited::WindowHidden();
}