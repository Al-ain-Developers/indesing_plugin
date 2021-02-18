//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/pictureicon/PicIcoActionComponent.cpp $
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
// Interfaces:
#include "IActiveContext.h"
#include "IControlView.h"
#include "IPanelControlData.h"
#include "IWidgetUtils.h"
#include "IPalettePanelUtils.h"

// General includes:
#include "CActionComponent.h"
#include "CAlert.h"

// Project includes:
#include "PicIcoID.h"
#include "IconRsrcDefs.h"


/** PicIcoActionComponent
	implements the actions that are executed when the plug-in's
	menu items are selected.

	PicIcoActionComponent implements IActionComponent based on
	the partial implementation CActionComponent.

	@ingroup pictureicon
	
*/
class PicIcoActionComponent : public CActionComponent
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		PicIcoActionComponent(IPMUnknown* boss);

		/**
			Responds to user actions
			@param context Active Document, View, and Selection information -- the context.
			@param actionID identifies the menu item that was selected.
		*/
		void DoAction(IActiveContext* context, ActionID actionID, GSysPoint mousePoint, IPMUnknown *widget);

	private:
		/** Shows the "About this plug-in" dialog. */
		void DoAbout();

		/** For the RotatePicture menu item. */
		void DoRotatePicture(IPMUnknown *widget);

		/** For the RotateIcon menu item. */
		void DoRotateIcon(IPMUnknown *widget);
		
		/**
			Determine which picture to display next.
		*/		
		void calcNextPictureRsrcID();
		
		/**
			Determine which icon to display next.
		*/		
		void calcNextIconRsrcID();

		RsrcID fCurrPictureRsrcID;
		RsrcID fCurrIconRsrcID;

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(PicIcoActionComponent, kPicIcoActionComponentImpl)

/* PicIcoActionComponent Constructor
*/
PicIcoActionComponent::PicIcoActionComponent(IPMUnknown* boss)
: CActionComponent(boss),
	fCurrPictureRsrcID(kPicIcoFirstPictureRsrcID),
	fCurrIconRsrcID(kPicIcoButCapIconRsrcID)
{
}

/* DoAction 
*/
void PicIcoActionComponent::DoAction(IActiveContext* context, ActionID actionID, GSysPoint mousePoint, IPMUnknown *widget)
{
	switch (actionID.Get())
	{
		case kPicIcoPopupAboutThisActionID:
		case kPicIcoAboutActionID:
		{
			this->DoAbout();
			break;
		}

		case kPicIcoRotatePictureActionID:
		{
			this->DoRotatePicture(widget);
			break;
		}

		case kPicIcoRotateIconActionID:
		{
			this->DoRotateIcon(widget);
			break;
		}

	
		default:
		{
			break;
		}
	}
}

/* DoAbout 
*/
void PicIcoActionComponent::DoAbout()
{
	CAlert::ModalAlert
	(
	   kPicIcoAboutBoxStringKey,			// Alert string
	   kOKString, 							// OK button
	   kNullString, 						// No second button
	   kNullString, 						// No third button
	   1,									// Set OK button to default
	   CAlert::eInformationIcon				// Information icon.
	);
}

/* DoRotatePicture
*/
void PicIcoActionComponent::DoRotatePicture(IPMUnknown *widget)
{
	do {
		
		InterfacePtr<IPanelControlData>
				panelControlData( 
					Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kPicIcoPanelWidgetID));
		ASSERT(panelControlData);
		if(!panelControlData) {
			break;
		}

		IControlView* pictureView = panelControlData->FindWidget(kPicIcoPictureWidgetId);
		ASSERT(pictureView);
		if(!pictureView) {
			break;
		}
		
		this->calcNextPictureRsrcID();
		pictureView->SetRsrcID(this->fCurrPictureRsrcID);
		pictureView->Invalidate();
		
		InterfacePtr<IControlView> panelView(panelControlData, UseDefaultIID());
		ASSERT(panelView);
		if(!panelView) {
			break;
		}
		panelView->Invalidate();
	} while(0);
}

/* DoRotateIcon
*/
void PicIcoActionComponent::DoRotateIcon(IPMUnknown *widget)
{
	do {
		
		InterfacePtr<IPanelControlData>
				panelControlData( 
					Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kPicIcoPanelWidgetID));
		ASSERT(panelControlData);
		if(!panelControlData) {
			break;
		}

		IControlView* iconView = panelControlData->FindWidget(kPicIcoIconSuiteWidgetId);
		ASSERT(iconView);
		if(!iconView) {
			break;
		}

		this->calcNextIconRsrcID();
		iconView->SetRsrcID(this->fCurrIconRsrcID);
		iconView->Invalidate();
		
		InterfacePtr<IControlView> panelView(panelControlData, UseDefaultIID());
		ASSERT(panelView);
		if(!panelView) {
			break;
		}
		panelView->Invalidate();
	} while(0);
}


void  PicIcoActionComponent::calcNextPictureRsrcID()
{
	fCurrPictureRsrcID++;
	if(fCurrPictureRsrcID > kPicIcoLastPictureRsrcID) {
		fCurrPictureRsrcID = kPicIcoFirstPictureRsrcID;
	}
}


void  PicIcoActionComponent::calcNextIconRsrcID()
{
	// hard coded 
	switch (fCurrIconRsrcID)
	{
	case kPicIcoButCapIconRsrcID:
		fCurrIconRsrcID = kPicIcoRoundCapIconRsrcID; 
		break;
	case kPicIcoRoundCapIconRsrcID:
		fCurrIconRsrcID = kPicIcoProjectingCapIconRsrcID; 
		break;
	case kPicIcoProjectingCapIconRsrcID:
		fCurrIconRsrcID = kPicIcoMiterJoinIconRsrcID; 
		break;
	case kPicIcoMiterJoinIconRsrcID:
		fCurrIconRsrcID = kPicIcoRoundedJoinIconRsrcID; 
		break;
	case kPicIcoRoundedJoinIconRsrcID:
		fCurrIconRsrcID = kPicIcoBevelJoinIconRsrcID; 
		break;
	case kPicIcoBevelJoinIconRsrcID:
		fCurrIconRsrcID = kPicIcoButCapIconRsrcID;
		break;
	}

}


// End, PicIcoActionComponent.cpp.


