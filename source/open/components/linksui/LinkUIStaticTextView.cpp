//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinkUIStaticTextView.cpp $
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

#include "ILink.h"
#include "ILinksUIPanelPrefs.h"
#include "ILinkInfoProvider.h"
#include "ITextControlData.h"
#include "ILinkResource.h"
#include "IApplication.h"
#include "ICursorProvider.h"
#include "ICursorRegion.h"
#include "IStaticTextAttributes.h"

#include "ClickableStaticTextView.h"
#include "ILinksUIUtils.h"
#include "IMenuUtils.h"

class LinkUIStaticTextView : public ClickableStaticTextView
{
	typedef ClickableStaticTextView inherited;
public:
	LinkUIStaticTextView(IPMUnknown* boss);
	virtual ~LinkUIStaticTextView();
	
	virtual void	GetTextColors(RealAGMColor& enabledTextColor, RealAGMColor& disabledTextColor) const;
	virtual void	PreDrawGetText(); // Override since link status can change dynamically, so we should update text at draw time (as was done previously)
};

CREATE_PERSIST_PMINTERFACE(LinkUIStaticTextView, kLinkUIStaticTextViewImpl)


LinkUIStaticTextView::LinkUIStaticTextView(IPMUnknown *boss) :
	ClickableStaticTextView(boss)
{
	InterfacePtr<const IApplication> theApp(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<ICursorProvider> globalCursorProvider(theApp, IID_ILINKSROWELEMENTCURSORPROVIDER);
	InterfacePtr<ICursorRegion> myCursorRegion(this, UseDefaultIID());
	if(myCursorRegion && globalCursorProvider)
		myCursorRegion->SetCursorProvider(globalCursorProvider);

	SetClipToSelfEnabled(kTrue);
}

LinkUIStaticTextView::~LinkUIStaticTextView() 
{ 
}

void LinkUIStaticTextView::PreDrawGetText()
{
	inherited::PreDrawGetText();

	// Force the text color to update
	RealAGMColor enabledColor, disabledColor;
	this->GetTextColors(enabledColor, disabledColor);
	SetTextValue(enabledColor, disabledColor);

	// DV_Note: manually updating the text shouldn't be necessary, since GetTextColor below is updating the ITextControlData
	//	which calls SetTextValue.
}

void LinkUIStaticTextView::GetTextColors(RealAGMColor& enabledTextColor, RealAGMColor& disabledTextColor) const
{
	// DV_Note: It apears that the text color (and the info string) can change dynamically depending on link status.
	//	Rather than trying to split the old code into GetTextColor and GetText, this method effectively does both as it sets the ITextControlData's text when necessary.

	CIDStaticTextView::GetTextColors(enabledTextColor, disabledTextColor); // get the default text colors first
	
	InterfacePtr<const ILinkInfoProvider> infoProvider(Utils<ILinksUIUtils>()->QueryInfoProviderFromLinksUIWidget(this));
	if(infoProvider )
	{
		InterfacePtr<const ILink> link(Utils<ILinksUIUtils>()->QueryLinkFromLinksUIWidget(this));
		InterfacePtr<const ILinkResource> linkResource(Utils<ILinksUIUtils>()->QueryLinkResourceFromLinksUIWidget(this));
		if(link || linkResource)
		{
			if(infoProvider->IsLinkInfoDynamic())
			{
				PMString updatedInfoStr = infoProvider->GetUpdatedInfoForLink(link,linkResource,true);

				// Convert & to && if user-entered style name contains &.
				// Prevents it from being interpreted as an accelerator.
				if(!updatedInfoStr.IsTranslatable())
					Utils<IMenuUtils>()->InsertAmpersandForDisplay(&updatedInfoStr);

				InterfacePtr<ITextControlData> textData(this,UseDefaultIID());
				textData->SetString(updatedInfoStr,kFalse/* don't inval */);
				
	//			TRACEFLOW("Links:LinksUI","LinkUIStaticTextView fetching data at draw time for column %s\n",infoProvider->GetInfoDescriptionString().GrabCString());
			}

			InterfacePtr<IStaticTextAttributes> textAttributes(this, UseDefaultIID());
			if (textAttributes)
			{
				textAttributes->SetDrawUnderline(kFalse);
			}

			if(infoProvider->CanDoSingleClickAction(link,linkResource))
			{
				inherited::GetTextColors(enabledTextColor, disabledTextColor);
#if DEBUG
				PMString staticTextViewString;
				GetText(staticTextViewString);
#endif
				textAttributes->SetDrawUnderline(kTrue);
			}
		}
	}
}