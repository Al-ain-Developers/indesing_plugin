//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinkThumbnailView.cpp $
//  
//  Owner: lance bushore
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

#include "IGraphicsPort.h"
#include "IImageCache.h"
#include "IInterfaceColors.h"
#include "ILink.h"
#include "ILinkManager.h"
#include "ILinkObject.h"
#include "ILinkResource.h"
#include "ILinksUIUtils.h"
#include "IMediaContent.h"
#include "IMediaInfo.h"
#include "IStoryUtils.h"
#include "ITextModel.h"
#include "IThumbnailUtils.h"
#include "IUIColorSpec.h"
#include "IWidgetUtils.h"
#include "DVPublicUtilities.h"

#include "AGMGraphicsContext.h"

#include "AutoGSave.h"
#include "DVControlView.h"
#include "LinksUIResDefs.h"
#include "PNGIcon.h"
#include "URI.h"
#include "ILinkUtils.h"
#include "ITextFragmentLinkFacade.h"


class LinkThumbnailView : public DVControlView
{
	typedef DVControlView inherited;
public:
	LinkThumbnailView(IPMUnknown* boss);
	virtual ~LinkThumbnailView();
	
	// Should be overridden to render the contents of the view.
	virtual void Draw(IViewPort* viewPort, SysRgn updateRgn = nil);

private:
	void DrawThumbnail(IGraphicsPort* gPort, const PMRect &frame);
	void DrawBackground(IGraphicsPort* gPort, const PMRect &frame);
	void GetBackgroundColors();

	int32	fBGColor;
	int32	fHiliteBGColor;
};

CREATE_PERSIST_PMINTERFACE(LinkThumbnailView, kLinkThumbnailViewImpl)


LinkThumbnailView::LinkThumbnailView(IPMUnknown *boss) :
	inherited(boss),
	fBGColor(kInvalidInterfaceColor),
	fHiliteBGColor(kInvalidInterfaceColor)
{
}

LinkThumbnailView::~LinkThumbnailView() 
{ 
}

enum ThumbnailIconSize {kSmallThumbIconSize,kMediumThumbIconSize,kLargeThumbIconSize};
RsrcID GetPNGIconRsrcForLinkType(ThumbnailIconSize whichIcon, const ILink* link);


void LinkThumbnailView::Draw(IViewPort* viewPort, SysRgn updateRgn)
{
	AGMGraphicsContext gc(viewPort, this, updateRgn);
	InterfacePtr<IGraphicsPort> gPort(gc.GetViewPort(), IID_IGRAPHICSPORT);
    AutoGSave gSave(gPort);
	PMRect frame = GetFrame();
	frame.MoveTo(0,0);

	GetBackgroundColors();
	DrawBackground(gPort, frame);
//	Draw Thumbnail
    InterfacePtr<const ILink> link(Utils<ILinksUIUtils>()->QueryLinkFromLinksUIWidget(this));
    InterfacePtr<const ILinkResource> linkResource(Utils<ILinksUIUtils>()->QueryLinkResourceFromLinksUIWidget(this));
    InterfacePtr<IImageCache> iImageCache(Utils<ILinksUIUtils>()->QueryThumbnailForLink(link,linkResource));
    if (iImageCache)
    {
        
        AGMImageAccessor *accessor(iImageCache->GetImageAccessor());
        Utils<IThumbnailUtils>()->DrawAGMImageAccessorThumbnail(viewPort, this, updateRgn, accessor,frame, accessor == nil ? kFalse : kTrue);
    }
    else
    {
        //draw a PNG that shows the category of this thing.
        ThumbnailIconSize whichIcon = kLargeThumbIconSize;
        if(frame.Height() < 16)
            whichIcon = kSmallThumbIconSize;
        else if(frame.Height() < 24)
            whichIcon = kMediumThumbIconSize;
        
        RsrcID iconID = GetPNGIconRsrcForLinkType(whichIcon,link);
        if(iconID != kInvalidRsrcID)
        {
            PNGIcon thumbnailPNG;
            thumbnailPNG.LoadIcon(kLinksUIPluginID, iconID);
            thumbnailPNG.DrawIcon(gPort);
            gPort->setlinewidth(0.0);
            dv_utils::DrawInfoThumbnailBorder(gPort, thumbnailPNG.GetBounds(), this);
        }
    }
}


RsrcID GetPNGIconRsrcForLinkType(ThumbnailIconSize whichIcon, const ILink* link)
{
	if(link)
	{
		InterfacePtr<const ILinkObject> linkObj(::GetDataBase(link),link->GetObject(),UseDefaultIID());
		if(linkObj)
		{
			InterfacePtr<const ITextModel> textModel((ITextModel*)linkObj->QueryLinkedObject(IID_ITEXTMODEL));
			InterfacePtr<ILinkResource> iLinkResource(::GetDataBase(link), link->GetResource(), UseDefaultIID());
			
			
			if (iLinkResource && Utils<Facade::ITextFragmentLinkFacade>()->IsTextFragmentLinkObject(::GetUIDRef(linkObj)))
			{
				switch (whichIcon)
				{
				case kSmallThumbIconSize:
					return kLinksUIHTTPMetadataSmIconRsrcID;
				case kMediumThumbIconSize:
					return kLinksUIHTTPMetadataMdIconRsrcID;
				case kLargeThumbIconSize:
					return kLinksUIHTTPMetadataLgIconRsrcID;
				default:
					ASSERT_FAIL("Unknown icon size requested");
				}

			}
			else if(textModel)
			{
				switch(whichIcon)
				{
					case kSmallThumbIconSize:
						return kLinksUIGenericTextSmIconRsrcID;
					case kMediumThumbIconSize:
						return kLinksUIGenericTextMdIconRsrcID;
					case kLargeThumbIconSize:
						return kLinksUIGenericTextLgIconRsrcID;
					default:
						ASSERT_FAIL("Unknown icon size requested");
				}
			}
			else
			{
				InterfacePtr<const IMediaInfo> mediaInfo((IMediaInfo*)linkObj->QueryLinkedObject(IID_IMEDIAINFO));
				if(mediaInfo)
				{
					if(mediaInfo->GetMediaType() == enMovie)
					{
						
							switch(whichIcon)
							{
								case kSmallThumbIconSize:
									return kLinksUIGenericMovieSmIconRsrcID;
								case kMediumThumbIconSize:
									return kLinksUIGenericMovieMdIconRsrcID;
								case kLargeThumbIconSize:
									return kLinksUIGenericMovieLgIconRsrcID;
								default:
									ASSERT_FAIL("Unknown icon size requested");
							}
					}
					else if(mediaInfo->GetMediaType() == enSound)
					{
						switch(whichIcon)
						{
							case kSmallThumbIconSize:
								return kLinksUIGenericAudioSmIconRsrcID;
							case kMediumThumbIconSize:
								return kLinksUIGenericAudioMdIconRsrcID;
							case kLargeThumbIconSize:
								return kLinksUIGenericAudioLgIconRsrcID;
							default:
								ASSERT_FAIL("Unknown icon size requested");
						}
					}
				}
				else
				{
					if(Utils<IStoryUtils>()->IsAStoryLink(link))
					{
						switch(whichIcon)
						{
							case kSmallThumbIconSize:
								return kLinksUIInCopyGraphicStorySmIconRsrcID;
							case kMediumThumbIconSize:
								return kLinksUIInCopyGraphicStoryMdIconRsrcID;
							case kLargeThumbIconSize:
								return kLinksUIInCopyGraphicStoryLgIconRsrcID;
							default:
								ASSERT_FAIL("Unknown icon size requested");
						}
					
					
					}
				
				}
			}
		}
	}
	
	return kInvalidRsrcID;
}

void LinkThumbnailView::DrawThumbnail( IGraphicsPort* gPort, const PMRect &frame )
{

}

void LinkThumbnailView::DrawBackground(IGraphicsPort* gPort, const PMRect &frame)
{
	InterfacePtr<IInterfaceColors> colors(GetExecutionContextSession(), UseDefaultIID());

	if(colors)
	{
		PMRect myFrame = frame;
		if(myFrame.Height() > 12) // Regular/Large rows, leave room for the node separator.
			myFrame.Inset(1, 1);

		RealAGMColor background;
		colors->GetRealAGMColor(IsHilited() ? fHiliteBGColor : fBGColor, background);

		AutoGSave autoGSave(gPort);
		gPort->setrgbcolor(background.red, background.green, background.blue);
		gPort->rectpath(myFrame);
		gPort->fill();
	}
}

void LinkThumbnailView::GetBackgroundColors()
{ 
	if(fBGColor == kInvalidInterfaceColor)
	{
		InterfacePtr<const IUIColorSpec> ancestorColor(Utils<IWidgetUtils>()->QueryColorSpecForWidget(this));
		if(ancestorColor && (ancestorColor->GetBackgroundColorID() != kInvalidInterfaceColor))
			fBGColor = ancestorColor->GetBackgroundColorID();
		else    //  Not a valid color, use our default one.
			fBGColor = kInterfacePaletteFill;

		if(ancestorColor && (ancestorColor->GetBackgroundHiliteColorID() != kInvalidInterfaceColor))
			fHiliteBGColor = ancestorColor->GetBackgroundHiliteColorID();
		else    //  Not a valid color, use our default one.
			fHiliteBGColor = kInterfaceHighLight;
	}
}
