//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/CustomHttpLinkUI/CustomHttpLinkUIObserver.cpp $
//  
//  Owner: swagarg
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
//  Copyright 2019 Adobe
//  All Rights Reserved.
//
//  NOTICE: Adobe permits you to use, modify, and distribute this file in
//  accordance with the terms of the Adobe license agreement accompanying
//  it. If you have received this file from a source other than Adobe,
//  then your use, modification, or distribution of it requires the prior
//  written permission of Adobe. 
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// General includes:
#include "CObserver.h"
#include "ISubject.h"
#include "IControlView.h"
#include "IEVEUtils.h"
#include "Utils.h"

// Interface includes
#include "IDropDownListController.h"
#include "IPanelControlData.h"
#include "IStringData.h"

// Project includes:
#include "CustomHttpLinkUIID.h"
#include "IStringListControlData.h"

//#include <dirent.h> // To read files in a given directory

/** Implementation of IObserver to respond to notification about changes
 to the Panel (kCustomHttpLinkUIPanelWidgetBoss) subject
 
	@ingroup customhttplinkui.sdk

*/
class CustomHttpLinkUIObserver : public CObserver
{
    typedef CObserver inherited;
    
public:
    /**
     Constructor.
     @param boss interface ptr from boss object on which this interface is aggregated.
    */
    CustomHttpLinkUIObserver(IPMUnknown* boss);

    /**
     Destructor
     */
    virtual ~CustomHttpLinkUIObserver() {}
    
    /**
     AutoAttach is only called for registered observers
     of widgets.  This method is called by the application
     core when the widget is shown.
     */
    virtual void AutoAttach();
    
    /**
     AutoDetach is only called for registered observers
     of widgets. Called when widget hidden.
     */
    virtual void AutoDetach();
    
    /**
     Update is called for all registered observers, and is
     the method through which changes are broadcast.
     @param theChange [IN] this is specified by the agent of change; it can be the class ID of the agent,
     or it may be some specialised message ID.
     @param theSubject [IN] provides a reference to the object which has changed; in this case, the button
     widget boss object that is being observed.
     @param protocol [IN] the protocol along which the change occurred.
     @param changedBy [IN] this can be used to provide additional information about the change or a reference
     to the boss object that caused the change.
     */
    virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);
		
private:
    
    /**
     Loads the list of file names in the dropdown menu
     */
    void loadFilesInDropdown();

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(CustomHttpLinkUIObserver, kCustomHttpLinkUIObserverImpl)

/* CustomHttpLinkUIObserver Constructor
*/
CustomHttpLinkUIObserver::CustomHttpLinkUIObserver(IPMUnknown* boss)
: CObserver(boss)
{
}

/* AutoAttach
 */
void CustomHttpLinkUIObserver::AutoAttach()
{
    InterfacePtr<IControlView> panelView(this, IID_ICONTROLVIEW);
    Utils<IEVEUtils>()->ApplyEveLayout(panelView);
    panelView->Invalidate();
    
    inherited::AutoAttach();
    
    loadFilesInDropdown();
}

/* AutoDetach
 */
void CustomHttpLinkUIObserver::AutoDetach()
{
   inherited::AutoDetach();
}

/* Update
 */
void CustomHttpLinkUIObserver::Update(const ClassID &theChange, ISubject *theSubject, const PMIID &protocol, void *changedBy)
{
}

/* loadFilesInDropdown
 */
void CustomHttpLinkUIObserver::loadFilesInDropdown()
{
    // Find the dropdown widget
    InterfacePtr<IPanelControlData> pcd(this, UseDefaultIID());
    IControlView* filesDropDown = pcd->FindWidget(kFileListWidgetID);
    InterfacePtr<IStringListControlData> iData(filesDropDown, IID_ISTRINGLISTCONTROLDATA);
    
    // Wipe out old entries
    iData->Clear();
    
    // Add the assets with these names to the image folder in localserver directory (localserver/image)
    // and their corresponding low res assets in (localserver/image/fpo) directory
    std::vector<std::string> assets = {
        "asset1.jpg",
        "asset2.jpg",
        "asset3.jpg",
        "asset4.jpg",
//        "asset5.jpg",
//        "asset6.jpg",
//        "asset7.jpg",
//        "asset8.jpg",
//        "asset9.jpg",
//        "asset10.jpg",
    };
    
    // Read all the file names and append to the listcontroldata
    for (int i = 0; i < assets.size(); i++) {
        std::string asset = assets[i];
        PMString str;
        str.SetUTF8String(asset);
        str.SetTranslatable(kFalse);
        
        iData->AddString(str, IStringListControlData::kEnd, kTrue, kFalse);
    }
    
    // Select first element
    InterfacePtr<IDropDownListController> dropDownListController(iData, IID_IDROPDOWNLISTCONTROLLER);
    dropDownListController->Select(0);
}

