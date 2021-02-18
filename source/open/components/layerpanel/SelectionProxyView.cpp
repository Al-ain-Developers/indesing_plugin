//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/SelectionProxyView.cpp $
//  
//  Owner: psorrick
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

#include "IDocumentLayer.h"
#include "ILayerList.h"
#include "IWidgetParent.h"
#include "IDocument.h"
#include "IBoolData.h"
#include "IGraphicsPort.h"
#include "ISpreadLayer.h"
#include "ILayoutUtils.h"
#include "IHierarchy.h"
#include "ITreeNodeIDData.h"
#include "ITreeViewHierarchyAdapter.h"
#include "ISelectionProxyDrawData.h"
#include "IWidgetUtils.h"
#include "iuicolorutils.h"

#include "AutoGSave.h"
#include "AGMGraphicsContext.h"
#include "LayerPanelDefs.h"
#include "LayerPanelID.h"
#include "LayerTreeUIDNodeID.h"
#include "PNGIcon.h"
#include "LayerPanelUtils.h"

#include "DVControlView.h"
#include "IInterfaceColors.h"
#include "DVPublicUtilities.h"
#include "SpectrumPublicCustomColorDefines.h"

//----------------------------------------------------------------------------------------
//
// Class definition
//
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Class SelectionProxyView
//----------------------------------------------------------------------------------------
class /* WIDGET_DECL */ SelectionProxyView : public DVControlView
{
	typedef DVControlView inherited;
	public:
		SelectionProxyView(IPMUnknown *boss);
		virtual ~SelectionProxyView();

	protected:
		void LoadPNGArt();
		void DrawNoDropIcon(IGraphicsPort *gPort);
		virtual void 	Draw(IViewPort* viewPort, SysRgn updateRgn);
		PNGIcon*		fPNGArt;
		ISelectionProxyDrawData::ProxyDrawType			fMostRecentDrawState;
};

CREATE_PERSIST_PMINTERFACE(SelectionProxyView, kSelectionProxyViewImpl)

SelectionProxyView::SelectionProxyView(IPMUnknown *boss) :
	inherited(boss),	fPNGArt(nil)
	//,fMostRecentDrawState(ISelectionProxyDrawData::kUnselected)

{
}


SelectionProxyView::~SelectionProxyView()
{
	if ( fPNGArt )
		delete fPNGArt;
}

void SelectionProxyView::LoadPNGArt()
{
	if ( !fPNGArt)
	{
		fPNGArt = new PNGIcon();
		fPNGArt->LoadIcon( kLayerPanelPluginID, kLayerProxyCantDropIcon);
	}
}

void SelectionProxyView::DrawNoDropIcon(IGraphicsPort *gPort)
{
	LoadPNGArt();

	if (fPNGArt)
	{
		PMRect iconBounds = fPNGArt->GetBounds();
		int32 tx = ::ToInt32((GetFrame().Width() - iconBounds.Width ()) / 2);
		int32 ty =  ::ToInt32((GetFrame().Height() - iconBounds.Height ()) / 2);

		iconBounds.MoveTo(tx, ty);
		InterfacePtr<IViewPort> viewPort(gPort, UseDefaultIID());
		fPNGArt->Draw(viewPort, ::ToSys(iconBounds), false);
	}
}

void SelectionProxyView::Draw(IViewPort* viewPort, SysRgn updateRgn)
{
	IDataBase * frontDocDB = LayerPanelUtils::GetCurrentLayerPanelDB(this);
	
	if (frontDocDB == nil)
		return;
	
	AGMGraphicsContext gc(viewPort, this, updateRgn);
	InterfacePtr<IGraphicsPort> gPort(gc.GetViewPort(), IID_IGRAPHICSPORT);
	AutoGSave autoGSave(gPort);

	PMRect proxyRect = GetFrame();
	proxyRect.MoveTo(0, 0);						// get into local coordinates

	InterfacePtr<const ISelectionProxyDrawData> drawData(this, UseDefaultIID());
	if(fMostRecentDrawState == ISelectionProxyDrawData::kNoDropAllowed)
	{
		// We draw a bigger icon for 'no drop allowed', so if we just drew that, we need to erase ourselves.
		InterfacePtr<IInterfaceColors> colors(GetExecutionContextSession(), IID_IINTERFACECOLORS);
		RealAGMColor background;
		colors->GetRealAGMColor(IsHilited() ? kInterfaceHighLight : kInterfacePaletteFill, background);	
		gPort->setrgbcolor(background.red, background.green, background.blue);
		gPort->rectpath(proxyRect);	
		gPort->fill();
	} 
//	TRACEFLOW("LayerPanel","SelectionProxyView::Draw draw state %d, this = 0x%x, size = %d, interface size = %d\n",drawData->GetDrawingMode(),this, sizeof(*this),SizeOfkSelectionProxyViewImpl_());
	
	if (drawData->GetDrawingMode() == ISelectionProxyDrawData::kDropOK || drawData->GetDrawingMode() == ISelectionProxyDrawData::kUnselected || drawData->GetDrawingMode() == ISelectionProxyDrawData::kChildSelected || drawData->GetDrawingMode() == ISelectionProxyDrawData::kSelected)
	{
		PMPoint midPoint(proxyRect.GetHCenter(), proxyRect.GetVCenter());
		PMRect drawRect(midPoint, midPoint);
		drawRect.Inset(-kLayerProxySize/2, -kLayerProxySize/2);

		// if the layer/page item is not selected, draw an empty box. If it is selected, draw a filled box.
		IInterfaceColors::InterfaceColor outlineColor = kInterfacePanelBorderColor;
		if(drawData->GetDrawingMode() == ISelectionProxyDrawData::kChildSelected || drawData->GetDrawingMode() == ISelectionProxyDrawData::kSelected)
		{
			// draw the filled rectangle
			ColorArray	proxySwatchColor = LayerPanelUtils::GetLayerColorForWidget(this);
			if(drawData->GetDrawingMode() == ISelectionProxyDrawData::kChildSelected)
			{
				proxySwatchColor =  Utils<IUIColorUtils>()->GetAdjustedUIColorValue(proxySwatchColor,0.35);
				drawRect.Inset(1,1);
			}


			// ----- Fill the proxy swatch.
			gPort->setrgbcolor(proxySwatchColor[IUIColorUtils::kRed], proxySwatchColor[IUIColorUtils::kGreen], proxySwatchColor[IUIColorUtils::kBlue]);
			gPort->rectpath(drawRect);	
			gPort->fill();

			outlineColor = kInterfaceBlack;
		}
		else if(drawData->GetDrawingMode() == ISelectionProxyDrawData::kDropOK)
		{
			outlineColor = kInterfaceBlack;
		}
		// ----- Frame the proxy swatch.
		gPort->setrgbcolor(kSpectrumBlack.red, kSpectrumBlack.green, kSpectrumBlack.blue);
		if (ID::os_utils::GetViewScaleFactorReal(NULL) == 1.5f)
		{
			gPort->setlinewidth(0.0);
		}
		else
		{
			gPort->setlinewidth(1.0f);
		}
		gPort->rectstroke(drawRect);
	}
	else
	{
		ASSERT_MSG(drawData->GetDrawingMode() == ISelectionProxyDrawData::kNoDropAllowed,"Unknown draw state");
		DrawNoDropIcon(gPort);
	}

	fMostRecentDrawState = drawData->GetDrawingMode();
}
