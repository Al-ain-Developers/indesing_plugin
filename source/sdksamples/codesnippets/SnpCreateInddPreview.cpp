//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpCreateInddPreview.cpp $
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

// Interface includes:
#include "ICommand.h"
#include "IDataBase.h"
#include "IDocFileHandler.h"
#include "IDocument.h"
#include "IDocumentUtils.h"
#include "IInCopyDocUtils.h"
#include "IOpenFileCmdData.h"
#include "IPageList.h"
#include "IPMStream.h"
#include "ISession.h"
#include "IDocumentCommands.h"

// General includes:
#include "CmdUtils.h"
#include "ErrorUtils.h"
#include "FeatureSets.h"
#include "ILayoutUIUtils.h"
#include "LocaleSetting.h"
#include "OpenPlaceID.h"
#include "SDKFileHelper.h"
#include "SnapshotUtils.h"
#include "StreamUtil.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/** \li How to take a preview JPEG of an InDesign document
 * 
 * 	This snippet class uses SnapshotUtils to make a preview of
 * 	the 1st page of an InDesign document.  If there is a front
 *	document, it is used to create the preview, otherwise, user
 *	will be prompted to select a file, which will be open faceless.
 * 
 *	@ingroup sdk_snippet
 *	@ingroup sdk_graphic
*/
class SnpCreateInddPreview 
{
public:

	/** Constructor.  
	 */
	SnpCreateInddPreview() :  fSnapshotUtils(nil) {}

	/** Destructor.
	 * 	Cleans up the internal SnapshotUtils member.
	 */
	virtual ~SnpCreateInddPreview() {
		this->CleanUp();
	}

	/** Creates the preview of the first page of a document, and 
	 * 	immediately saves it to a JPEG format file. 
	 * 	@param docRef IN UIDRef for the document to preview. 
	 * 	@param faceless IN bool16 if the document is opened via a choose file dialog, it is not displayed in layout window.
	 * 	@param jpegFile IN IDFile for the JPEG file to save. 
	 * 	@param xScale IN Scale in the X-direction. Default = 1.0 (=100%)
	 * 	@param yScale IN Scale in the Y-direction. Default = 1.0 (=100%)
	 * 	@param desiredRes IN Desired resolution. Default = 36.0.
	 * 	@return kSuccess on success, kFailure otherwise.
	 */
    ErrorCode CreateFirstPagePreview(const UIDRef& docRef, 
									 const bool16& faceless, 
									 const IDFile& jpegFile,
									 const PMReal& xScale = 1.0, 
									 const PMReal& yScale = 1.0, 
									 const PMReal& desiredRes = 36.0);

private:
	/** Instantiates a SnapshotUtils class internally, and assigns the
	 * 	item (page or page item) to snapshot.
	 * 
	 * 	@param itemToSnapshot IN Pass in a UIDRef for the SnapshotUtils 
	 * 			constructor that accepts a UIDRef.
	 * 	@param xScale IN Scale in the X-direction. Default = 1.0 (=100%)
	 * 	@param yScale IN Scale in the Y-direction. Default = 1.0 (=100%)
	 * 	@param desiredRes IN Desired resolution. Default = 36.0.
	 * 	@return kSuccess on success, kFailure otherwise.
	 * 	@see SnapshotUtils
	 */
	ErrorCode SetPageToSnapshot(const UIDRef& itemToSnapshot,
								const PMReal& xScale = 1.0, 
								const PMReal& yScale = 1.0, 
								const PMReal& desiredRes = 36.0);

	/**	Exports the snapshot to JPEG file.
	 * 	@param jpegSysFile IN File to write.
	 * 	@return kSuccess on success, kFailure otherwise.
	 */
	ErrorCode ExportImageToJPEG(const IDFile& jpegSysFile);

	/** Deletes internal instance of SnapshotUtils.
	 */
	void CleanUp();


	/** Internal snapshot utils member
	 */
	SnapshotUtils* fSnapshotUtils;
};


/* CreateFirstPagePreview
*/
ErrorCode SnpCreateInddPreview::CreateFirstPagePreview(const UIDRef& docRef,
													   const bool16& docOpenFlag, 
													   const IDFile& jpegFile,
													   const PMReal& xScale, 
													   const PMReal& yScale, 
													   const PMReal& desiredRes)
{
	ErrorCode status = kFailure;
	do {
		if (docRef.ExistsInDB() == kFalse) 
		{
			ASSERT_FAIL("Invalid document!");
			break;
		}
		InterfacePtr<IDocument> doc(docRef, UseDefaultIID());
		if (doc == nil)
		{
			ASSERT_FAIL("Could not get IDocument");
			break;
		}

		// Get the 1st page
		InterfacePtr<IPageList> pageList(doc, UseDefaultIID());
		if (pageList == nil)
		{
			ASSERT_FAIL("Could not get IPageList. Is this really a document?");
			break;
		}
		UIDRef firstPageUIDRef(docRef.GetDataBase(), pageList->GetNthPageUID(0));
		if (firstPageUIDRef.ExistsInDB() == kFalse) 
		{
			ASSERT_FAIL("Invalid page!");
			break;
		}

		// export the snapshot to file
		// NOTE: this instantiates a SnapshotUtils
		status = this->SetPageToSnapshot(firstPageUIDRef, xScale, yScale, desiredRes);
		if (status != kSuccess) 
		{
			SNIPLOG("ERROR: SetPageToSnapshot failed!");
			break;
		}

		// reset the status (for break statements)
		status = kFailure;

		// export the snapshot to JPEG
		status = this->ExportImageToJPEG(jpegFile);
		if (status != kSuccess) 
		{
			SNIPLOG("ERROR: ExportImageToJPEG failed!");
			break;
		}

		// clean up the snapshot utils instance
		this->CleanUp();

		// if we get this far, set the status to success (it should be already...)
		status = kSuccess;
	
	} while (false);

	if (docOpenFlag) 
	{
		// close faceless document
        InterfacePtr<IDocumentUtils> docUtils(GetExecutionContextSession(), UseDefaultIID());
		ASSERT(docUtils);
        InterfacePtr<IDocFileHandler> docFileHandler(docUtils->QueryDocFileHandler(docRef));
		ASSERT(docFileHandler);
        if (docFileHandler->CanClose(docRef))
		{
			docFileHandler->Close(docRef, kSuppressUI);
		}
	}
	return status;
}

/* SetPageToSnapshot
*/
ErrorCode SnpCreateInddPreview::SetPageToSnapshot(const UIDRef& itemToSnapshot,
												  const PMReal& xScale, 
												  const PMReal& yScale, 
												  const PMReal& desiredRes)
{
	ErrorCode status = kFailure;
	do {
		// make sure item is valid
		if (itemToSnapshot.ExistsInDB() == kFalse) 
		{
			ASSERT(itemToSnapshot.ExistsInDB());
			break;
		}

		// Clean up first.
		this->CleanUp();

		PMReal minRes = desiredRes;
		// create a new snapshot utils instance
		fSnapshotUtils = new SnapshotUtils(itemToSnapshot, 
										   xScale,     // X Scale
										   yScale,     // Y Scale
										   desiredRes,    // desired resolution of resulting snapshot
										   minRes,    // minimum resolution of resulting snapshot
										   0,     // Extend the bounds of the area to be drawn by the given amount of bleed
										   IShape::kDrawFrameEdge,// Drawing flags (kPrinting suppresses drawing of margins and guides)
										   kTrue,    // kTrue forces images and graphics to draw at full resolution, kFalse to draw proxies
										   kFalse,    // kTrue to draw grayscale, kFalse to draw RGB
										   kFalse);    // kTrue to add an alpha channel, kFalse no alpha channel

		if (fSnapshotUtils == nil) 
		{
			ASSERT_FAIL("Could not create SnapshotUtils");
			break;
		}

#ifdef DEBUG
		// see if you can get an AGM image accessor out of this
		AGMImageAccessor* imageAccessor = fSnapshotUtils->CreateAGMImageAccessor();
		if (imageAccessor == nil) 
		{
			ASSERT_MSG(imageAccessor, "Couldn't get an AGMImageAccessor from SnapShotUtils");
			this->CleanUp();
			break;
		}
		else
		{
			// we don't need this anymore so delete it
			delete imageAccessor;
		}
#endif

		// if we got here, everything is good
		status = kSuccess;

	} while (false);
	return status;
}


/* ExportImageToJPEG
*/
ErrorCode SnpCreateInddPreview::ExportImageToJPEG(const IDFile& jpegSysFile)
{
	ErrorCode status = kFailure;
	do
	{
		if (fSnapshotUtils == nil) 
		{
			ASSERT_FAIL("fSnapshotUtils is nil!");
			break;
		}
		uint32 mode = kOpenOut|kOpenTrunc;
		OSType fileType = 'JPEG';
		OSType creator = kAnyCreator;

		// create a stream to write out
		InterfacePtr<IPMStream> jpegStream(StreamUtil::CreateFileStreamWrite(jpegSysFile, mode, fileType, creator));
		if (jpegStream == nil) 
		{
			ASSERT_FAIL("Could not create a stream to write, so we can't export");
			break;
		}

		// export to JPEG
		status = fSnapshotUtils->ExportImageToJPEG(jpegStream);
	
	} while (false);
	return status;
} 

/* CleanUp
*/
void SnpCreateInddPreview::CleanUp(void)
{
	
	if (fSnapshotUtils) 
	{
		// clean up snapshot utils
		delete fSnapshotUtils;
		fSnapshotUtils = nil;
	}
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

/** Makes the snippet SnpCreateInddPreview available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerCreateInddPreview : public SnpRunnable
{

public:
	// SnippetRunner framework hooks.

	/** Constructor.  
	 */
	_SnpRunnerCreateInddPreview(void);

	/** Destructor.
	 * 	Cleans up the internal SnapshotUtils member.
	 */
	virtual ~_SnpRunnerCreateInddPreview(void);

	/** Return kTrue if the snippet can run.
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kTrue if snippet can run, kFalse otherwise
	 */
	bool16			CanRun(ISnpRunnableContext* runnableContext);

	/** Run the snippet.
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode		Run(ISnpRunnableContext* runnableContext);
	
	/** 
		get the snippet context
		@return eSnpRunContextType for this snippet
	*/
	virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunNoContext;}
	

};

/* Constructor
*/
_SnpRunnerCreateInddPreview::_SnpRunnerCreateInddPreview()
 : SnpRunnable("CreateInddPreview")
{
	this->SetDescription("Saves a preview of the 1st page of an indd file as a jpeg file to disk");
	this->SetPreconditions("none");
	this->SetCategories("sdk_snippet, sdk_graphics");
}

/* Destructor
*/
_SnpRunnerCreateInddPreview::~_SnpRunnerCreateInddPreview()
{

}

/* Check if your preconditions are met.
*/
bool16 _SnpRunnerCreateInddPreview::CanRun(ISnpRunnableContext* runnableContext)
{
	// you can always run this. 
	return kTrue;
}


/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerCreateInddPreview::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;
	do
	{
		SnpCreateInddPreview instance;

		IDocument*	doc = Utils<ILayoutUIUtils>()->GetFrontDocument();
		UIDRef	docRef = ::GetUIDRef(doc);
		bool16 faceless = kFalse;
		PMString docFilenameString;
		if (docRef == UIDRef::gNull)
		{
			// select an InDesign document to open
			SDKFileDocumentChooser docFileChooser;
			docFileChooser.ShowDialog();
			if (!docFileChooser.IsChosen()) 
			{
				break;
			}
			IDFile documentFile = docFileChooser.GetIDFile();
			docFilenameString = docFileChooser.GetPath();
			if (docFilenameString.empty()) 
			{
				break;
			}
			faceless = kTrue;
			status = Utils<IDocumentCommands>()->Open(&docRef, documentFile,
				kSuppressUI, IOpenFileCmdData::kOpenOriginal, IOpenFileCmdData::kUseLockFile, kFalse);
			if (status != kSuccess)
				break;
		}

		// select JPEG file to save to
		SDKFileSaveChooser jpegFileChooser;
		jpegFileChooser.AddFilter(kJPEGFileTypeInfoID, "JPEG file(jpg)");
		jpegFileChooser.ShowDialog();
		if (jpegFileChooser.IsChosen() == kFalse) 
		{
			break;
		}
		IDFile jpegFile = jpegFileChooser.GetIDFile();
		PMString jpegFilenameString = jpegFileChooser.GetPath();
		if (jpegFilenameString.empty()) 
		{
			break;
		}

		// get resolution.
		Utils<ISnipRunParameterUtils> parameterUtils;
		PMString prompt("Specify desired resolution.", PMString::kEncodingASCII);
		PMReal defaultRes = 36.0;
		PMReal desiredRes = parameterUtils->GetPMReal(prompt, defaultRes);
		if (parameterUtils->WasDialogCancelled()) 
		{
			break;
		}
		
		// setup default scales
		PMReal xScale = 1.0, yScale = 1.0;

		// create the preview
		// NOTE: See defaults on member declaration
		status = instance.CreateFirstPagePreview(docRef, 
											  faceless, 
											  jpegFile, 
											  xScale, 
											  yScale, 
											  desiredRes);
		if (status != kSuccess) 
		{
			SNIPLOG("CreateFirstPagePreview failed!");
		}
		else
		{
			SNIPLOG("Saved 1st page preview of file %s at %s (Resolution = %.2f)", 
					docFilenameString.GetPlatformString().c_str(), 
					jpegFilenameString.GetPlatformString().c_str(),
					::ToDouble(desiredRes));
		}

	} while(false);

	return status;
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerCreateInddPreview instance_SnpRunnerCreateInddPreview;
DEFINE_SNIPPET(_SnpRunnerCreateInddPreview) 	
//End, SnpCreateInddPreview.cpp
