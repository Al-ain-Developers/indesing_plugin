//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/msopanel/MSOPanelStateThumbnailView.cpp $
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
#include "IDataBase.h"
#include "IGraphicsPort.h"
#include "IImageCache.h"
#include "IMediaInfo.h"
#include "ITreeNodeIDData.h"
#include "IWidgetParent.h"

// ----- Includes -----

#include "AGMGraphicsContext.h"
#include "AutoGSave.h"
#include "DVControlView.h"
#include "MSOStateNodeID.h"

// ----- Utility files -----

#include "FormFieldUIUtils.h"
#include "IThumbnailUtils.h"
#include "Utils.h"
#include "IWidgetUtils.h"
#include "DVPublicUtilities.h"
#include "IThumbnailUtils.h"

// ----- ID.h files -----

#include "FormFieldUIID.h"


class MSOPanelStateThumbnailView : public DVControlView 
{
public:
	typedef  DVControlView inherited;
	MSOPanelStateThumbnailView(IPMUnknown* boss);
	virtual ~MSOPanelStateThumbnailView();
	
	virtual void Draw(IViewPort* viewPort, SysRgn updateRgn = nil);

private:
	PMRect GetDrawRect();
	bool GetThumbnailAGMRecord(AGMImageAccessor** pOutAGMImage, const Form::AppearanceState& appearance);
};

// =============================================================================
// *** MSOPanelStateThumbnailView impl ***
// -----------------------------------------------------------------------------

CREATE_PERSIST_PMINTERFACE(MSOPanelStateThumbnailView, kMSOPanelStateThumbnailViewImpl)


MSOPanelStateThumbnailView::MSOPanelStateThumbnailView(IPMUnknown *boss) :
	inherited(boss)
{
} // end constructor

MSOPanelStateThumbnailView::~MSOPanelStateThumbnailView() 
{ 
} // end destructor

//----------------------------------------------------------------------------------------

PMRect MSOPanelStateThumbnailView::GetDrawRect()
{
	PMRect swatchRt = GetFrame();
	swatchRt.MoveTo(0, 0);						// get into local coordinates

	swatchRt.Inset(3, 3);
	return swatchRt;
} // end GetDrawRect()

//----------------------------------------------------------------------------------------
// This is the maximum x and y dimension of a thumbnail image
const int32 kMaxThumbnailMaxSize = 128;

//----------------------------------------------------------------------------------------

void MSOPanelStateThumbnailView::Draw(IViewPort* viewPort, SysRgn updateRgn)
{
	InterfacePtr<IWidgetParent> thumbnailWidget(this, UseDefaultIID());
	InterfacePtr<IWidgetParent> treeNodeWidget(thumbnailWidget->GetParent(), UseDefaultIID());

	InterfacePtr<const ITreeNodeIDData> nodeData(treeNodeWidget, UseDefaultIID());
	if (!nodeData || !nodeData->Get().IsValid()) return;

	TreeNodePtr<MSOStateNodeID> msoStateNode(nodeData->Get());
	IDataBase* db = msoStateNode->GetDataBase();
	if (db == nil) return;

	AGMImageAccessor *thumbnail = nil;

	//FormWidgetBlocker blocker;
	PMRect frameRect = GetDrawRect().Round();
	bool bHaveThumb = GetThumbnailAGMRecord(&thumbnail, msoStateNode->GetAppearance());
    // No thumbnail, no nonsense. Abort.
	if ( !bHaveThumb )
        return;

    Utils<IThumbnailUtils>()->DrawAGMImageAccessorThumbnail(viewPort, this, updateRgn, thumbnail, frameRect, kTrue /* drawThumbnail*/);
    
    /*Relying on the previous version because there we delete this if we were drawing something. Since, we bailed out early in case of
        no thumbnail, we should be safe here to delete this unconditionallly.*/
    delete thumbnail;
} // end Draw()

//----------------------------------------------------------------------------------------

bool MSOPanelStateThumbnailView::GetThumbnailAGMRecord(AGMImageAccessor** pOutAGMImage, const Form::AppearanceState& appearance)
{
	InterfacePtr<IAppearanceSuite> appearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
	if (appearanceSuite)
	{
		ErrorCode err = appearanceSuite->GetAppearanceThumbnail(appearance, kMaxThumbnailMaxSize, kMaxThumbnailMaxSize, pOutAGMImage);
		return err == kSuccess;
	}
	
	return false;
} // end GetThumbnailAGMRecord()
