//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/CustomHttpLinkUI/CustomHttpLinkUIPlaceButtonObserver.cpp $
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
#include "ErrorUtils.h"
#include "EventUtilities.h"
#include "ILayoutUIUtils.h"
#include "ILinkFacade.h"
#include "IPasteboardUtils.h"
#include "IDocumentCommands.h"

#include "IApplication.h"
#include "IDocumentList.h"
#include "ISelectionUtils.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "IExportProvider.h"
#include "ISession.h"

// Interface includes:
#include "IActiveContext.h"
#include "IControlView.h"
#include "IDropDownListController.h"
#include "IImportExportFacade.h"
#include "IPanelControlData.h"
#include "IStringData.h"
#include "IStringListControlData.h"
#include "ISpread.h"
#include "ISubject.h"
#include "IWidgetParent.h"

#include "PMString.h"
#include "URI.h"

// Project includes:
#include "CustomHttpLinkUIID.h"
#include <IDocFileHandler.h>
#include <IDocumentUtils.h>
#include <persist.h>


// Tarek includes
#include <CkUpload.h>

/** Implementation of IObserver to respond to notification about changes
    to the Place Button (kPlaceButtonBoss) subject
 
	@ingroup customhttplinkui.sdk
*/

class CustomHttpLinkUIPlaceButtonObserver : public CObserver
{
public:

    /**
     Constructor for CustomHttpLinkUIPlaceButtonObserver class.
     @param interface ptr from boss object on which this interface is aggregated.
     */
    CustomHttpLinkUIPlaceButtonObserver(IPMUnknown* boss);

    /**
     Destructor
     */
    virtual ~CustomHttpLinkUIPlaceButtonObserver() {}
    
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
};

/* CREATE_PMINTERFACE
    Binds the C++ implementation class onto its
    ImplementationID making the C++ code callable by the
    application.
*/
CREATE_PMINTERFACE(CustomHttpLinkUIPlaceButtonObserver, kCustomHttpLinkUIPlaceButtonObserverImpl)

/**
 CustomHttpLinkUIPlaceButtonObserver Constructor
*/
CustomHttpLinkUIPlaceButtonObserver::CustomHttpLinkUIPlaceButtonObserver(IPMUnknown* boss)
: CObserver(boss)
{
}

/* AutoAttach
 */
void CustomHttpLinkUIPlaceButtonObserver::AutoAttach()
{
    InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
    if (subject && !subject->IsAttached(this, IID_IBOOLEANCONTROLDATA))
        subject->AttachObserver(this, IID_IBOOLEANCONTROLDATA);
}

/* AutoDetach
 */
void CustomHttpLinkUIPlaceButtonObserver::AutoDetach()
{
    InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
    if (subject && subject->IsAttached(this, IID_IBOOLEANCONTROLDATA))
        subject->DetachObserver(this, IID_IBOOLEANCONTROLDATA);
}

/* Update
 */
void CustomHttpLinkUIPlaceButtonObserver::Update(const ClassID &theChange, ISubject *theSubject, const PMIID &protocol, void *changedBy)
{

    ////////////////////////////Tarek Code Section
    

   /* ErrorCode result = kFailure;
    do {
        
        // Save the document to another file.
        //IDataBase* db = ::GetDataBase();
        IDocument* idoc = Utils<ILayoutUIUtils>()->GetFrontDocument();
      //  idoc->Save();
        IDataBase* db = ::GetDataBase(idoc);
        UIDRef documentUIDRef(db, db->GetRootUID());
        
       // UIDRef		documentUIDRef(::GetDataBase(Utils<ILayoutUIUtils>()->GetFrontDocument()));

        InterfacePtr<IDocFileHandler> docFileHandler(Utils<IDocumentUtils>()->QueryDocFileHandler(documentUIDRef));
        if (!docFileHandler) {
            break;
        }

        std::string urlToCopy("C:\\temp\\test.indd.bak");
        IDFile theCopyFileId;
        
        theCopyFileId.SetPath(urlToCopy);

        if (docFileHandler->CanSaveACopy(documentUIDRef)) {
            docFileHandler->SaveACopy(documentUIDRef, &theCopyFileId);
            result = ErrorUtils::PMGetGlobalErrorCode();

            if (result != kSuccess) {
                break;
            }
        }
    } while (false);*/

    ////////////////////////////////////Tarek code section for indesign save file 




    IDocument* doc = Utils<ILayoutUIUtils>()->GetFrontDocument();
    UIDRef	docRef = ::GetUIDRef(doc);
    PMString docFilenameString;
    docFilenameString = "C:\\temp\\Untitled-1.indd";
    IDFile datafile(docFilenameString);
    Utils<IDocumentCommands>()->SaveAs(docRef,
        datafile, kFullUI);



    //////////////////////////////Tarek Code section for indesign Export PDF file


    PMString PDFFormat("Adobe PDF");
    PDFFormat.SetTranslatable(kFalse);
    InterfacePtr<ISelectionManager> selection(Utils<ISelectionUtils>()->QueryActiveSelection());
    //IDocument* frontDoc = ::GetFrontDocument();
    
    InterfacePtr<IK2ServiceRegistry> k2ServiceRegistry(GetExecutionContextSession(), UseDefaultIID());
    // Look for all service providers with kExportProviderService.
    int32 exportProviderCount = k2ServiceRegistry->GetServiceProviderCount(kExportProviderService);
    // Iterate through them. bool found = kFalse;
    for (int32 exportProviderIndex = 0; exportProviderIndex < exportProviderCount; exportProviderIndex++) {
        // get the service provider boss class
        InterfacePtr<IK2ServiceProvider> k2ServiceProvider(k2ServiceRegistry->QueryNthServiceProvider(kExportProviderService, exportProviderIndex));
        // Get the export provider implementation itself.
        InterfacePtr<IExportProvider> exportProvider(k2ServiceProvider, IID_IEXPORTPROVIDER);
        // Check to see if the current selection specifier can be exported 
        // by this provider.
        bool16 canExportByTarget = exportProvider->CanExportThisFormat(doc, selection, PDFFormat);
        int found=0;
        if (canExportByTarget)
        {
            found = 1;
            // assume idFile is a valid IDFile to hold the soon to be created PDF

        docFilenameString = "C:\\temp\\Untitled-1.pdf";
        IDFile datafilepdf(docFilenameString);
            exportProvider->ExportToFile(datafilepdf, doc, selection, PDFFormat, kFullUI);
        }
        if (found==1)
            break;
        
    }
    /////////////////////////////////////////Tarek Upload file 

    CkUpload upload;

    //  Specify the page (ASP, ASP.NET, Perl, Python, Ruby, CGI, etc)
    //  that will receive and process the HTTP Upload.
    upload.put_Hostname("www.facebook.com");
    upload.put_Path("/index.php");

    //  Add one or more files to be uploaded.
    upload.AddFileReference("file1", "C:\\temp\\Untitled-1.pdf");
    upload.AddFileReference("file2", "C:\\temp\\Untitled-1.indd");
   // upload.AddFileReference("file3", "C:\\temp\\Untitled-1.pdf");


    //  Do the upload.  The method returns when the upload
    //  is completed.
    //  This component also includes asynchronous upload capability,
    //  which is demonstrated in another example.
    bool success = upload.BlockingUpload();
    


    if (success != true) {
        int msgboxID = MessageBox(
            NULL,
            (LPCWSTR)L""+ upload.get_ResponseStatus() ,
            (LPCWSTR)L"Account Details",
            MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
        );
    }
    else {
        int msgboxID = MessageBox(
            NULL,
            (LPCWSTR)L"success",
            (LPCWSTR)L"Account Details",
            MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
        );
    }


    
    /////////////////////////////////////////////////////////////////////

    
    /*
    if (theChange == kTrueStateMessage) {
        
        // Check for the widget id
        InterfacePtr<IControlView> view (this, UseDefaultIID());
        WidgetID widgetid = view -> GetWidgetID();
        
        if (widgetid == kChooseFileWidgetID) {
            
            // Go to parent widget to query for the selected item in dropdown
            InterfacePtr<IWidgetParent> iParentHolder(this, UseDefaultIID());
            InterfacePtr<IPanelControlData> pcd(iParentHolder->GetParent(),UseDefaultIID());
            if (!pcd)
                return;
            
            IControlView* filesDropDown = pcd->FindWidget(kFileListWidgetID);
            InterfacePtr<IStringListControlData> iData(filesDropDown, IID_ISTRINGLISTCONTROLDATA);
            InterfacePtr<IDropDownListController> dropDownListController(iData, IID_IDROPDOWNLISTCONTROLLER);
            
            // Create the URI for the asset to be placed
            int32 selectedFormatIndex = dropDownListController->GetSelected();
            PMString selectedFormatName = iData->GetString(selectedFormatIndex);
            std::string path = "/image/" + selectedFormatName.GetUTF8String();
            URI uri;
            uri.SetComponent(URI::kScheme, WideString(kCusHttpLnkScheme));
            uri.SetComponent(URI::kAuthority, WideString(kCusHttpLnkAuthority));
            uri.SetComponent(URI::kPath, WideString(path.c_str()));
            
            // Get active context
            IActiveContext* ac = GetExecutionContextSession()->GetActiveContext();
            IDocument* activeDoc = ac->GetContextDocument();
            IControlView* view = ac->GetContextView();
            if (!view)
               return;
            
            // Get current spread database
            GSysPoint globalPoint;
            globalPoint = ::GetGlobalMouseLocation();
            PMPoint convertedPoint = Utils<ILayoutUIUtils>()->ComputePasteboardPoint(globalPoint, view);
            InterfacePtr<ISpread> spread(Utils<IPasteboardUtils>()->QueryNearestSpread(view, convertedPoint));
            if (!spread)
                return;
            IDataBase* db = ::GetDataBase(spread);
            
            // Setting Default rendition type to kFPO
            ErrorCode err = Utils<Facade::ILinkFacade>()->SetHTTPLinksDefaultRenditionType(ILinkResourceRenditionData::kFPO);

            // Load the selected uri in place gun now!
            err = Utils<Facade::IImportExportFacade>()->ImportAndLoadPlaceGun(db, uri, kMinimalUI, kFalse, kFalse, kFalse, UID(kInvalidUID), IPlaceGun::kAddToFront);
        }
    }
    */
}
