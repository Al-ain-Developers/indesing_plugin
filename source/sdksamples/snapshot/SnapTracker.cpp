//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snapshot/SnapTracker.cpp $
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

//Interface includes:
#include "IEvent.h"
#include "IControlView.h"
#include "ILayoutControlViewHelper.h"
#include "ILayoutControlData.h"
#include "ILayoutCmdData.h"
#include "IDataBase.h"
#include "IDocument.h"
#include "ISpread.h"
#include "IPanorama.h"
#include "IZoomCmdData.h"
#include "ISnapPrefsData.h"
#include "IWorkspace.h"
#include "IK2ServiceRegistry.h"
#include "IK2ServiceProvider.h"
#include "IImageWriteFormatInfo.h"
#include "ILayoutSelectionSuite.h"
#include "ISelectionManager.h"
#include "ISelectionUtils.h"
#include "IGeometryFacade.h"
#include "IImageStreamManager.h"
#include "IImageWriteFormat.h"
#include "IImageStream.h"
#include "IImageAttributes.h"
#include "ICreateCacheImageStreamData.h"

// General includes
#include "SDKFileHelper.h"
#include "JPEGFilterID.h"
#include "SplineID.h"
#include "ShuksanID.h"
#include "LayoutUIID.h"
#include "ILayoutUIUtils.h"
#include "IPathUtils.h"
#include "IPageItemUtils.h"
#include "IPasteboardUtils.h"
#include "PersistUtils.h"
#include "CAlert.h"
#include "CmdUtils.h"
#include "Trace.h"
#include "SelectUtils.h"
#include "ImageID.h"
#include "GIFFilterID.h"
#include "PNGFilterID.h"
#include "CTracker.h"
#include "SnapshotUtilsEx.h"
#include "JPEGFilterID.h"
#include "TIFFFilterID.h"
#include "StreamUtil.h"
#include "AGMImageAccessor.h"

// Project includes
#include "SnapID.h"
#include "ISnapPrefsData.h"
#include "ISnapSelectionSuite.h"

// Constants
static const PlatformChar k_UNIXDELCHAR('/');
static const PlatformChar k_MACDELCHAR(':');
static const PlatformChar k_WINDELCHAR('\\');


/**
	The Snapshot Tool's tracker. Snapshot creates images of spreads, pages
	and selections.

	The user must double click to take the snapshot.

	If a selection is set double clicking takes a snapshot of it.

	If no selection is set double clicking on the background of the spread creates a
	snapshot of the spread. Double clicking on a page creates a snapshot of the page.

	By selecting a frame with no fill or stroke you can create snapshots clipped to the
	bounds of this frame. Use the selection tool to drag the frame around and create
	snapshots of different areas.

	The tool has global preferences that allow the name of the output file, the file
	format, scale factor and various other parameters to be set.

	If the output file specified by the preferences is an absolute filenname it will
	be used. Otherwise the snapshot image file is created in the same folder as the 
	document from which snapshots are being made. 

 	This tracker completes all of its behaviour in a single call to BeginTracking().

	
	@ingroup snapshot
*/
class SnapTracker : public CTracker
{
	public:
		/**The constructor */ 
		SnapTracker(IPMUnknown* boss);

		/** Destructor*/
		~SnapTracker() {}

		/**
			 Invoked when the tool is selected and the user clicks the mouse. 
		*/
		virtual bool16 BeginTracking(IEvent* theEvent);
		
	protected:
		/** */
		virtual ErrorCode CreateAndProcessSetSpreadCmd(ISpread* iSpread, 
													   ILayoutControlData* iLayoutControlData);

		/** */
		UIDRef HitTestPoint(ISpread* spread, const PBPMPoint& where, PMRect & outBounds);

		/** Removes the last part of a path. 
		 * 	@param fromthis IN/OUT The path that needs to have the last 
		 * 			part (file or folder) removed.
		 */
		void RemoveLastElement(PMString& fromthis);
		
		/** Appends a platform specific path separator. 
		 * 	@param path IN/OUT The path to which you want to append a path separator.
		 */
		void AppendPathSeparator(PMString& path);

		/** Replaces substrings found in a string with something else.
		 * 	@param original IN/OUT Original string to search in.
		 * 	@param target IN Text to search for.
		 * 	@param replace IN Text to replace with.
		 */
		void Replace(PMString& original,
					 const PMString& target,
					 const PMString& replace);
					 
	private:

		ErrorCode Export(SnapshotUtilsEx* snapshot);		
		
		SnapshotUtilsEx* CreateSnapShot(ISpread* spread);

	private:
		PMPoint fStartPnt;						// Where the user clicked
		ISnapPrefsData* fSnapshotPrefsData;		// Pointer to our preferences
		PMReal fScale;							// Scale factor
		PMString fFilePath;						// Absolute path to snapshot file
		ClassID fFormatClass;					// write format class ID
		bool16 fAddAlpha;						// add alpha transparency to the exported image
};


/*
 CREATE_PMINTERFACE
 This macro creates a class factory for the given class name
 and registers the ID with the host.
*/
CREATE_PMINTERFACE(SnapTracker, kSnapTrackerImpl)


/*
 Constructor for SnapTracker class.
*/
SnapTracker::SnapTracker(IPMUnknown* boss) :
	CTracker(boss),
	fSnapshotPrefsData(nil),
	fScale(1.0),
	fFilePath(""),
	fFormatClass(kInvalidClass),
	fAddAlpha(kFalse)
{
	TRACEFLOW("SnapShot","SnapTracker constructor. \n");
}


/*
 Begin tracking, invoked when the tool is selected and the user clicks the mouse. 
*/
bool16 SnapTracker::BeginTracking(IEvent* theEvent)
{
	ErrorCode status = kFailure;
	fSnapshotPrefsData = nil;
	
	TRACEFLOW("SnapShot", "SnapTracker::BeginTracking\n");
	
	do
	{
		// Calculate the start point
		this->GlobalToPasteboard(theEvent->GlobalWhere(), fStartPnt);

		// Find the spread that was clicked
		InterfacePtr<ILayoutControlData> layoutControlData(fControlView, UseDefaultIID());
		InterfacePtr<ISpread> spread(Utils<IPasteboardUtils>()->QuerySpread(fControlView, fStartPnt));
		if (spread == nil)
		{
			ASSERT_FAIL("spread invalid");
			CAlert::ErrorAlert(kAlertSnapshotFailedKey);
			break;
		}

		// Change to the clicked spread if necessary
		if (::GetUIDRef(spread) != layoutControlData->GetSpreadRef())
		{
			status = CreateAndProcessSetSpreadCmd(spread, layoutControlData);
			if (status != kSuccess)
			{
				ASSERT_FAIL("CreateAndProcessSetSpreadCmd failed");
				CAlert::ErrorAlert(kAlertSnapshotFailedKey);
				break;
			}

			// Re-calculate the starting point
			this->GlobalToPasteboard(theEvent->GlobalWhere(), fStartPnt);
		}

		// Only take snapshots on double click
		IEvent::EventType eventType = theEvent->GetType();
		if (eventType != IEvent::kDoubleClick)
		{
			status = kSuccess;
			break;
		}
			
		// Acquire Snapshot preferences
		InterfacePtr<IWorkspace> workspace(GetExecutionContextSession()->QueryWorkspace());
		if (workspace == nil)
		{
			ASSERT_FAIL("workspace invalid");
			CAlert::ErrorAlert(kAlertSnapshotFailedKey);
			break;
		}
		fSnapshotPrefsData = (ISnapPrefsData*) workspace->QueryInterface(IID_ISNAPPREFSDATA);
		if (fSnapshotPrefsData == nil)
		{
			ASSERT_FAIL("fSnapshotPrefsData invalid");
			CAlert::ErrorAlert(kAlertSnapshotFailedKey);
			break;
		}
		
		// Get scale factor	
		fScale = fSnapshotPrefsData->GetScale();
		fFormatClass = fSnapshotPrefsData->GetFormatClassID();
		if (fFormatClass == kGIFImageWriteFormatBoss)
		{
			fAddAlpha = fSnapshotPrefsData->GetGIFTransparent();
		} else if (fFormatClass == kTIFFImageWriteFormatBoss)
		{
			fAddAlpha = fSnapshotPrefsData->GetTIFFTransparent();
		}
		
		// Do some diagnostic tracing and asserts to check the parameters
		// for the snapshot are OK.
		if (fFormatClass == kTIFFImageWriteFormatBoss)
		{
			TRACEFLOW("SnapShot", "TIF snapshot, transparent=%d, paletteType=%d\n",
				fSnapshotPrefsData->GetTIFFTransparent(),
				fSnapshotPrefsData->GetTIFFPaletteType()
			);
		}
		else if (fFormatClass == kGIFImageWriteFormatBoss)
		{
			ASSERT_MSG(fSnapshotPrefsData->GetGIFPaletteType() != SnapshotUtils::kNoPalette, "GIF must have a colour palette");
			TRACEFLOW("SnapShot", "GIF snapshot, transparent=%d, paletteType=%d\n",
				fSnapshotPrefsData->GetGIFTransparent(),
				fSnapshotPrefsData->GetGIFPaletteType()
			);
		}
		else if (fFormatClass == kJPEGImageWriteFormatBoss)
		{
			ASSERT_MSG(fAddAlpha == kFalse,"JPEG does not support alpha channel");
			TRACEFLOW("SnapShot", "JPEG snapshot, encoding=%d, quality=%d\n",
				fSnapshotPrefsData->GetJPEGEncoding(),
				fSnapshotPrefsData->GetJPEGQuality()
			);
		}
		TRACEFLOW("SnapShot", " scale=%f, resolution=%f, minimumResolution=%f, bleed=%f, drawingFlags=%d, fullResolutionGraphics=%d, drawGray=%d, addAlpha=%d\n",
				::ToDouble(fSnapshotPrefsData->GetScale()),				
				::ToDouble(fSnapshotPrefsData->GetResolution()),
				::ToDouble(fSnapshotPrefsData->GetMinimumResolution()),
				::ToDouble(fSnapshotPrefsData->GetBleed()),
				fSnapshotPrefsData->GetDrawingFlags(),
				fSnapshotPrefsData->GetFullResolutionGraphics(),
				fSnapshotPrefsData->GetDrawGray(),
				fAddAlpha
		);
		
		SnapshotUtilsEx* snapshot = CreateSnapShot(spread);
		if (snapshot == nil)
		{
			ASSERT_FAIL("snapshot invalid");
			CAlert::ErrorAlert(kAlertSnapshotFailedKey);
			break;
		}

		// We have to call Draw on the snapshot
		if( snapshot->Draw(IShape::kPreviewMode | IShape::kPrinting) != kSuccess)
			break;

		// Export the snapshot to a file		
		status = Export(snapshot);
		
		// Delete our snapshot
		delete snapshot;

		if (status != kSuccess)
			break;
			
		{
			PMString message(kAlertSnapshotTakenKey, PMString::kTranslateDuringCall);
			message.SetTranslatable(kFalse);
			fFilePath.SetTranslatable(kFalse);
			this->Replace(message, "^0", fFilePath);
			CAlert::InformationAlert(message);
		}

	} while (kFalse);
	
	// Release our preferences
	if (fSnapshotPrefsData != nil)
		fSnapshotPrefsData->Release();
		
	// Returning kFalse means the tracker will be released
	// We're finished...
	
	return kFalse;
}

SnapshotUtilsEx* SnapTracker::CreateSnapShot(ISpread* spread)
{
	InterfacePtr<ISnapSelectionSuite> snapSelectionSuite(
		static_cast<ISnapSelectionSuite*>(Utils<ISelectionUtils>()->QuerySuite (IID_ISNAPSELECTIONSUITE)));   
	if (snapSelectionSuite && snapSelectionSuite->SelectionIsEmpty() == kFalse)
	{
		// take a snapshot of the selection 
		return snapSelectionSuite->CreateSnapshot(spread);
	}
	else
	{
		// Otherwise take a snapshot of the spread or the spread clipped to a given page
		PMRect itemBounds;
		UIDRef itemUIDRef = HitTestPoint(spread, fStartPnt, itemBounds);
		// UIDRef() will construct to IDatabase*=nil, UID=kInvalidUID, 
		// i.e. an invalid UIDRef. The hit test returns a valid UIDRef
		// on a hit and an invalid one if there's no hit. The hit test 
		// is looking for the spread or page that underlies the click
		// point. But the user could click on the area outside the spread.
		// This test filters out such clicks.
		if (itemUIDRef == UIDRef())
			return nil;
			
		return new SnapshotUtilsEx(
								itemBounds, PMMatrix(),
								itemUIDRef,
								fSnapshotPrefsData->GetScale(),
								fSnapshotPrefsData->GetScale(),
								fSnapshotPrefsData->GetResolution(),
								fSnapshotPrefsData->GetMinimumResolution(),
								fSnapshotPrefsData->GetBleed(),
								fSnapshotPrefsData->GetDrawGray() ? SnapshotUtilsEx::kCsGray : SnapshotUtilsEx::kCsRGB,
								fAddAlpha
								);
	}
}


/* CreateAndProcessSetSpreadCmd
*/
ErrorCode SnapTracker::CreateAndProcessSetSpreadCmd(ISpread* iSpread, ILayoutControlData* iLayoutControlData)
{
	ErrorCode status = kFailure;
	do
	{
		InterfacePtr<ICommand> iSetSpreadCmd(CmdUtils::CreateCommand(kSetSpreadCmdBoss));
		if (iSetSpreadCmd == nil)
		{
			ASSERT_FAIL("Set spread command is invalid.");
			break;
		}
		InterfacePtr<ILayoutCmdData> iSetSpreadLayoutCmdData(iSetSpreadCmd, UseDefaultIID());
		if (iSetSpreadLayoutCmdData == nil)
		{
			ASSERT_FAIL("Set spread layout command data is invalid");
			break;
		}
		iSetSpreadLayoutCmdData->Set(::GetUIDRef(iLayoutControlData->GetDocument()), iLayoutControlData);
		iSetSpreadCmd->SetItemList(UIDList(::GetDataBase(iLayoutControlData->GetDocument()), ::GetUID(iSpread)));
		status = CmdUtils::ProcessCommand(iSetSpreadCmd);
	} while (kFalse);

	return status;
}


/* Export
 Export the given snapshot to a stream. The output file is
 created in the same folder as the document from which the
 snapshot is being taken. The filename and format to be
 used are taken from the preferences. The file extension,
 file type and creator for the file are obtained from 
 application's service registry. Each image write format
 registers the extension, type and creator to be used.
*/
ErrorCode SnapTracker::Export(SnapshotUtilsEx* snapshot)
{
	ErrorCode status = kFailure;
	do
	{				
		// Set up the path to our snapshot image file. 
		// If an absolute path is specified by the output filename
		// in our preferences use it. Otherwise create the snapshot
		// alongside the document.
		fFilePath = "";
#ifdef MACINTOSH
		const char separator = ':';
#else
		const char separator = '\\';
#endif
		if (fSnapshotPrefsData->GetName().IndexOf(separator) < 0)
		{
			// Find the path to the frontmost document. 
			// We'll create the snapshot there.
			IDocument* document = Utils<ILayoutUIUtils>()->GetFrontDocument();
			if (document == nil)
			{
				ASSERT_FAIL("document invalid");
				CAlert::ErrorAlert(kAlertSnapshotFailedKey);
				break;	
			}
			IDataBase* database = ::GetDataBase(document);
			if (database == nil) 
			{
				ASSERT_FAIL("database invalid");
				CAlert::ErrorAlert(kAlertSnapshotFailedKey);			
				break;
			}
			if (database->GetSysFile() == nil)
			{
				// Can't take snapshots of files that haven't been saved.
				// Don't assert on this condition just alert.
				CAlert::ErrorAlert(kAlertSaveFileKey);
				break;
			}
			IDFile databaseSysFile = *database->GetSysFile();
			SDKFileHelper fileHelper1(databaseSysFile);
			fFilePath = fileHelper1.GetPath();
			this->RemoveLastElement(fFilePath);
			this->AppendPathSeparator(fFilePath);
		}
		fFilePath.Append(fSnapshotPrefsData->GetName());	
		
		// Look up the image write format info in the registry
		// so we can setup the file extension, type and creator.
		InterfacePtr<IK2ServiceRegistry> registry(GetExecutionContextSession(), UseDefaultIID());
		if (registry == nil)
		{
			ASSERT_FAIL("registry invalid");
			CAlert::ErrorAlert(kAlertSnapshotFailedKey);
			break;
		}
		if (fFormatClass == kInvalidClass)
		{
			// Use the default image write format service if none is yet selected
			fFormatClass = registry->GetDefaultServiceProviderID(kImageWriteFormatService);
		}
		InterfacePtr<IK2ServiceProvider> service(registry->QueryServiceProviderByClassID(kImageWriteFormatService, fFormatClass));
		if (service == nil)
		{
			ASSERT_FAIL("service invalid");
			CAlert::ErrorAlert(kAlertSnapshotFailedKey);
			break;
		}
		InterfacePtr<IImageWriteFormatInfo> formatInfo(service, IID_IIMAGEWRITEFORMATINFO);
		if (formatInfo == nil)
		{
			ASSERT_FAIL("formatInfo invalid");
			CAlert::ErrorAlert(kAlertSnapshotFailedKey);
			break;
		}
		PMString extension;
		formatInfo->GetExtension(&extension);
		
		// Append a number to the image filename so we generate a new
		// file for each snapshot. For example a series of three JPEG format
		// snapshots would be named Snapshot1.jpg, Snapshot2.jpg, Snapshot3.jpg.
		// Loop round generating filenames and checking if they exist already.
		int32 i = 1;
		while (i <= 256)
		{
			PMString filename = fFilePath;
			filename.AppendNumber(i);
			filename.Append(".");
			filename.Append(extension);
			SDKFileHelper fileHelper2(filename);
			if (fileHelper2.IsExisting() == kFalse)
			{
				// Great we've found the filename to use
				break;
			}
			i++;
		}
		if (i > 256)
		{
			ASSERT_FAIL("failed to generate file number - max file number is 256");
			CAlert::ErrorAlert(kAlertBadFileNumberKey);
			break;
		}
		fFilePath.AppendNumber(i);
		fFilePath.Append(".");
		fFilePath.Append(extension);

		// Open a stream
		TRACEFLOW("SnapShot", "fFilePath %s\n", fFilePath.GetUTF8String().c_str());
		SDKFileHelper fileHelper3(fFilePath);
		IDFile fileSysFile = fileHelper3.GetIDFile();
		
		InterfacePtr<IPMStream> stream(StreamUtil::CreateFileStreamWrite(fileSysFile, 
																		 kOpenOut|kOpenTrunc, 
																		 formatInfo->GetFileType(), 
																		 formatInfo->GetCreator()));
		if (stream == nil)
		{
			ASSERT_FAIL("stream invalid");
			PMString message(kAlertBadFilenameKey, PMString::kTranslateDuringCall);
			message.SetTranslatable(kFalse);
			fFilePath.SetTranslatable(kFalse);
			this->Replace(message, "^0", fFilePath);
			CAlert::ErrorAlert(message);
			break;
		}

		// Export the bitmap to the right format
		if (fFormatClass == kJPEGImageWriteFormatBoss)
		{
			int32 encoding = fSnapshotPrefsData->GetJPEGEncoding();
			int32 quality = fSnapshotPrefsData->GetJPEGQuality();
			status = snapshot->ExportImageToJPEG(stream, 
									(SnapshotUtils::SSJPEGEncoding)encoding, 
									(SnapshotUtils::SSJPEGQuality)quality);
		} 
		else if (fFormatClass == kTIFFImageWriteFormatBoss)
		{
			status = snapshot->ExportImageToTIFF(
										stream, 
										(SnapshotUtils::PaletteType)fSnapshotPrefsData->GetTIFFPaletteType() );
		} 
		else if (fFormatClass == kGIFImageWriteFormatBoss)
		{
			status = snapshot->ExportImageToGIF(
										stream, 
										(SnapshotUtils::PaletteType)fSnapshotPrefsData->GetGIFPaletteType(), 
										fSnapshotPrefsData->GetGIFInterlaced() );
		}	
		else if (fFormatClass == kPNGImageWriteFormatBoss)
		{
			status = snapshot->ExportImageToPNG(stream);
		}
		else
		{
			status = snapshot->ExportImage(fFormatClass, stream, kFalse);
		}
		
		// Tidy up
		stream->Close();
			
	} while (false);
	return status;	
}

/*  HitTestPoint
*/
UIDRef SnapTracker::HitTestPoint(ISpread* spread, const PBPMPoint& where, PMRect & outBounds)
{
	UIDRef result;
	do
	{
		// Spread background hit test
		PMRect pagesBounds = spread->GetPagesBounds( Transform::PasteboardCoordinates());//XFSpreadIssue
		if (pagesBounds.PointIn(where) == kFalse)
		{
			// User clicked spread background
			outBounds = spread->GetPagesBounds(Transform::SpreadCoordinates());
			result = ::GetUIDRef(spread);
		}
		
		// Page hit test
		for (int32 p = 0; p < spread->GetNumPages(); p++)
		{
			InterfacePtr<IGeometry> pageGeometry(spread->QueryNthPage(p));
			if (pageGeometry == nil)
			{
				ASSERT_FAIL("invalid pageGeometry");
				break;
			}
			PMRect pageBounds = Utils<Facade::IGeometryFacade>()->GetItemBounds( ::GetUIDRef(pageGeometry), Transform::PasteboardCoordinates(), Geometry::OuterStrokeBounds());
			if (pageBounds.PointIn(where))
			{
				// User clicked this page.  Set the outBounds to the bounds of this
				// page in spread coordinates
				outBounds = Utils<Facade::IGeometryFacade>()->GetItemBounds( ::GetUIDRef(pageGeometry), Transform::SpreadCoordinates(), Geometry::OuterStrokeBounds());;
				result = ::GetUIDRef(spread);
				break;
			}
		}
	} while (false);
	return result;
}

/* RemoveLastElement
*/
void SnapTracker::RemoveLastElement(PMString& fromthis)
{
	// takes off the last element from the path. We search for the last delimeter and knock off the
	// stuff that comes after. We lose this data so beware!
	int lastpos = 0;
	for (int i = 0 ; i< fromthis.CharCount();i++)
		if ((fromthis[i] == k_MACDELCHAR) || (fromthis[i] == k_UNIXDELCHAR) || (fromthis[i] == k_WINDELCHAR))
			lastpos = i;
	// At this point lastpos should point to the last delimeter, knock off the rest of the string.
	fromthis.Truncate(fromthis.CharCount()-lastpos);

}

/* AppendPathSeparator
*/
void SnapTracker::AppendPathSeparator(PMString& path)
{
#ifdef MACINTOSH
	path.Append(k_MACDELCHAR);
#else
	path.Append(k_WINDELCHAR);
#endif
}

/* Replace
*/
void SnapTracker::Replace(PMString& original,
						  const PMString& target,
						  const PMString& replace)
{
	const int32 kTargetFoundPos = original.IndexOfString(target);
	if (kTargetFoundPos >= 0)
	{
		original.Remove(kTargetFoundPos, target.CharCount());
		original.Insert(replace, kTargetFoundPos);
	}
}

// End, SnapTracker.cpp.


