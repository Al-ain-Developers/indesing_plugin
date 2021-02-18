//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/pictureicon/PicIcoPictureWidgetEH.cpp $
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

// Interfaces
#include "IControlView.h"
#include "IBooleanControlData.h"
#include "IUIFontSpec.h"
// General includes:
#include "DVControlEventHandler.h"
// Project includes:
#include "PicIcoID.h"


/** 
	Traps LButtonDn events.

	The only method that is overridden by this class is
	LButtonDn; this is to create a picture-based button which can use
	Mac PICT or Windows BITMAP resources rather than just icons as in the
	other buttons in the widget set.
	The implementation is quite sparse in that there are only two different
	pictures for the selected and uselected states. There is
	none of the sophistication of the real iconic buttons such as
	being able to display a highlighted state when the end-user is clicking on the
	button.

	@ingroup pictureicon

	
	DV_Note: As a widget eventhandler this should now derive from DVControlEventHandler rather than CEventHandler	
*/

class PicIcoPictureWidgetEH : public DVControlEventHandler
{
	typedef DVControlEventHandler inherited;
public:

	/**
		ctor. 
		@param boss interface ptr on the boss object to which the interface implemented here belongs.
	*/	
	PicIcoPictureWidgetEH(IPMUnknown *boss);
	
	/**
		Destructor
	*/	
	virtual ~PicIcoPictureWidgetEH(){}

	/**
		Handle left button down events.
		Change the data model, and also change the picture displayed.
		This is because there is no platform peer that knows how to change its visual representation
		so we have to do it ourselves.

		@param e event of interest.
	*/
	virtual bool16 LButtonDn(IEvent* e);
};

CREATE_PMINTERFACE( PicIcoPictureWidgetEH, kPicIcoPictureWidgetEHImpl)

	
PicIcoPictureWidgetEH::PicIcoPictureWidgetEH(IPMUnknown *boss) :
	inherited(boss)
{
}

bool16 PicIcoPictureWidgetEH::LButtonDn(IEvent* e)
{

	do {
		int32 rsrcID = 0;

		InterfacePtr<IBooleanControlData> controlData(this, IID_IBOOLEANCONTROLDATA); // no kDefaultIID
		if(controlData==nil) {
			ASSERT_FAIL("PicIcoPictureWidgetEH::LButtonDn - No IBooleanControlData found on this boss.");
			break;
		}
		InterfacePtr<IUIFontSpec> fontSpec(this, IID_IUIFONTSPEC); // no kDefaultIID
		if(fontSpec==nil) {
			ASSERT_FAIL("PicIcoPictureWidgetEH::LButtonDn - No IUIFontSpec found on this boss.");
			break;
		}
		bool16 isPressedIn = controlData->IsSelected();
		if(isPressedIn == kTrue) {
			controlData->Deselect();	
			rsrcID = fontSpec->GetFontID();
		} else {
			controlData->Select();
			rsrcID =fontSpec->GetHiliteFontID();
		}

		InterfacePtr<IControlView> myView(this, UseDefaultIID());
		if(myView == nil) {
			ASSERT_FAIL("PicIcoPictureWidgetEH::LButtonDn - No IControlView found on this boss.");
			break;
		}
		if(rsrcID != 0) {
			myView->SetRsrcID(rsrcID);
		
		}
		return kTrue;
		// early return as here we have already
		// handled the event and do not need to
		// delegate any processing to the base class.
	} while(0);

	return inherited::LButtonDn(e);
}



