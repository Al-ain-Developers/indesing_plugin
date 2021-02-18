//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/DVLayerElementView.cpp $
//  
//  Owner: Mainak Ghosh
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
//  Copyright 2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interfaces:
#include "IGraphicsPort.h"
#include "IPanelControlData.h"
#include "IWidgetParent.h"
#include "IBoolData.h"
#include "IViewPort.h"

// Includes:
#include "LayerPanelDefs.h"
#include "DVTreeNodeControlView.h"
#include "LocaleSetting.h"
#include "AutoGSave.h"

// Utility files:
#include "Utils.h"
#include "IWidgetUtils.h"

// ID.h files:
#include "LayerPanelID.h"

#include "DVAPublicIncludes.h"
#include "DVPublicUtilities.h"

//----------------------------------------------------------------------------------------
// Class definition
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Class DVLayerElementView
//----------------------------------------------------------------------------------------

class DVLayerElementView : public DVTreeNodeControlView
{
	typedef DVTreeNodeControlView inherited;
	
public:
			 DVLayerElementView(IPMUnknown *boss) : inherited(boss) { ; }
	virtual ~DVLayerElementView() { ; }

	virtual void DV_Draw(dvaui::drawbot::Drawbot *drawbotP) const;

	virtual void DrawBackground(dvaui::drawbot::Drawbot* drawbotP) const;

private:
			void DrawBorder(dvaui::drawbot::Drawbot *drawbotP, const PMRect& frame) const;
			void DrawSeparatorOnRight(IControlView* widget, RealAGMColor color, dvaui::drawbot::Drawbot *drawbotP, int32 offsetFromRight) const;
};

#pragma mark DVLayerElementView implementation

CREATE_PERSIST_PMINTERFACE(DVLayerElementView, kLayerElementViewImpl)

void DVLayerElementView::DV_Draw(dvaui::drawbot::Drawbot *drawbotP) const
{
	PMRect frame( this->GetInnerContentFrame() );

	InterfacePtr<IPanelControlData>	myData(this, UseDefaultIID());
	IControlView* layerSwatchView = myData->FindWidget(kLayerListElementSwatchWidgetID);

	frame.Left()  = 1;

	if ( layerSwatchView )
		frame.Right() = layerSwatchView->GetFrame().Right() + 1;
	
	inherited::DV_Draw(drawbotP);
	
	DrawBorder(drawbotP, frame);
}

void DVLayerElementView::DrawBorder( dvaui::drawbot::Drawbot *drawbotP, const PMRect& frame ) const
{
	InterfacePtr<const IWidgetParent> wp(this,UseDefaultIID());
	InterfacePtr<const IBoolData> rowSizeBool((IBoolData*)wp->QueryParentFor( IID_ISMALLPALETTEROWSBOOLDATA));
	bool16 bSmallRows =  rowSizeBool ? rowSizeBool->GetBool() : false;

	InterfacePtr<IInterfaceColors> colors(GetExecutionContextSession(), UseDefaultIID());
	RealAGMColor bevelAGMColor;
	colors->GetRealAGMColor(kInterfaceBlack, bevelAGMColor);

	if (colors)
	{
#if defined (MACINTOSH)
        int32 offsetFromRight = 0;
#else
        int32 offsetFromRight = 1;
#endif
		colors->GetRealAGMColor(kInterfaceSeparatorColor, bevelAGMColor);
		InterfacePtr<IPanelControlData>	myData(this, UseDefaultIID());

		IControlView* eyeballView = myData->FindWidget(kLayerListElementEyeballWidgetID);	
		DrawSeparatorOnRight(eyeballView, bevelAGMColor, drawbotP, offsetFromRight);

		
		IControlView* lockView = myData->FindWidget(kLayerPageItemElementPencilWidgetID);
		if (!lockView)
			lockView = myData->FindWidget(kLayerListElementPencilWidgetID);
		if (lockView->IsVisible())
			DrawSeparatorOnRight(lockView, bevelAGMColor, drawbotP, offsetFromRight);

		IControlView* layerSwatchView = myData->FindWidget(kLayerListElementSwatchWidgetID);
		DrawSeparatorOnRight(layerSwatchView, bevelAGMColor, drawbotP, offsetFromRight);
	}
}

// This draws a separator line on the right side of the widget. The offsetFromRight is just used so as to center the icon equally.
void DVLayerElementView::DrawSeparatorOnRight(IControlView* widget, RealAGMColor color, dvaui::drawbot::Drawbot *drawbotP, const int32 offsetFromRight) const
{
	if (widget)
	{
		PMRect widgetFrame(widget->GetFrame());
		PMPointList bevelPts1;
		widgetFrame.Inset(0.0f, -0.5f);
		bevelPts1.push_back(PMPoint(widgetFrame.Right() + offsetFromRight, widgetFrame.Top()));	//moveto
		bevelPts1.push_back(PMPoint(widgetFrame.Right() + offsetFromRight, widgetFrame.Bottom()));   //lineto

		dv_utils::DVStrokePath(drawbotP, color, bevelPts1, dv_utils::kDefaultStrokeWidth);
	}
}

// have to override this method because we don't want the hilight to extend over the swatch/eye/pencil icons.
void DVLayerElementView::DrawBackground(dvaui::drawbot::Drawbot* drawbotP) const
{	
	InterfacePtr<IPanelControlData>    myData(this, UseDefaultIID()); 
	IControlView* layerSwatchView = myData->FindWidget(kLayerListElementSwatchWidgetID); 

	if (layerSwatchView)
	{
		PMRect frame( this->GetInnerContentFrame() );

		frame.Left() = layerSwatchView->GetFrame().Right() + 1; 

		if (IsHilited()) 
		{
			RGBColor background;
			InterfacePtr<IInterfaceColors> colors(GetExecutionContextSession(), UseDefaultIID());
			
			if (colors)
			{
				colors->GetRGBColor(kInterfaceHighLight, background);
				dv_utils::DVFillRect(drawbotP, background, frame);
			}
		}
		else
			Utils<IWidgetUtils>()->DrawPaletteFill(this, drawbotP, &frame);
	}
}
