//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/textexportfilter/TxtExpFilter.cpp $
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
//  
//  TxtExpFilter class implementation.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// API:
//#include "AutoPtr.h"
#include "CoreResTypes.h"
#include "CPMUnknown.h"
#include "CTUnicodeTranslator.h"
#include "ErrorUtils.h"
#include "IApplication.h"
#include "IComposeScanner.h"
#include "IDataBase.h"
#include "IDataExchangeHandler.h"
#include "IDialog.h"
#include "IDialogMgr.h"
#include "IDocument.h"
#include "CExportProvider.h"
#include "IImportProviderUtils.h"
#include "IIntData.h"
#include "IPMStream.h"
#include "ISelectionUtils.h"
#include "ITextFocus.h"
#include "ITextModel.h"
#include "ITextScrapData.h"
#include "ITextTarget.h"
#include "IFileStreamData.h"
#include "isignalmgr.h"
#include "IExportProviderSignalData.h"
#include "LocaleSetting.h"
#include "PMLocaleId.h"
#include "PMString.h"
#include "ProgressBar.h"
#include "RsrcSpec.h"
#include "StreamUtil.h"                   
#include "SystemUtils.h"
#include "RangeData.h"
#include "IDrawingStyle.h"
#include "IPMFont.h"
#include "WideString.h"

// Project:
#include "TxtExpID.h"
#include "ITxtExpFileWriter.h"
#include "TxtExpUtils.h"
#include "ITxtExpSuite.h"

// General includes
#ifdef WIN32
#include <minmax.h>
#else
#define min(a,b) ((a<b)?a:b)
#endif

/** TxtExpFilter
	implements export provider behavior for the TextExportFilter.
	
	TxtExpFilter implements IExportProvider.
	
	
	<B>A general note about the <I>IPMUnknown* targetBoss</I> parameter in 
	IExportProvider</B>:<BR>
	InDesign's Export Manager is the component responsible for obtaining 
	the current selection context, finding the right export provider for it, 
	and passing on the selection, "targetBoss".  The way it obtains the 
	"targetBoss" is by means of ISelectionUtils::QueryActiveSelection(),
	which returns ISelectionManager (aggregated on kAbstractSelectionBoss).<BR>
	However, since the type of "targetBoss" declared in the prototypes for 
	various methods in IExportProvider is IPMUnknown*, virtually any interface 
	pointer could be passed into it, especially if you query for your 
	own export provider.<BR>
	It is up to the export provider to determine if the given "targetBoss" and/or
	the front document can be exported. 
	

	@ingroup textexportfilter
	
*/
class TxtExpFilter : public CExportProvider
{
	public:
        /**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		TxtExpFilter(IPMUnknown* boss);

        /**
			Desstructor.
		*/
		virtual ~TxtExpFilter(void);

		/** (NEW) Export the current selection to a file using the given filename. 
			Generate the specified file format. The calling code verifies that the 
			file does not exist. 
			Note: Some export providers may display UI and may export more than just 
			the current selection (i.e. PDF export, EPS export, etc.)
		*/
		virtual void ExportToFile(const IDFile& sysFile, IDocument* doc, IPMUnknown* targetboss, const PMString& formatName, UIFlags uiFlags = kFullUI);

		
		/** (NEW) Export the current selection to a stream. 
			Note: Some export providers may display UI and may export more than just 
			the current selection (i.e. PDF export, EPS export, etc.)
			Please note that the typographer's quotation marks will NOT be modified in this plug-in. 
		*/
		virtual void ExportToStream(IPMStream* stream, IDocument* doc, IPMUnknown* targetboss, const PMString& formatName, UIFlags uiFlags = kFullUI);
			
        
   		/** (NEW) The provider indicates whether it can do normal file based exports.
		*/
		virtual bool16 CanExportToFile(void) const;
		
		/** (MODIFIED) The export provider indicates whether it can export the current 
			specifier in the specified file format (ex. a text export file would return 
			kFalse for a page item selection and kTrue for a text selection).
		*/
		virtual bool16 CanExportThisFormat(IDocument* doc, IPMUnknown* targetboss, const PMString& formatName);

		   
   		/** (NEW) The provider indicates whether it can do normal filebased exports. 
		*/
		virtual bool16 CanExportForExternalize(void) const;

		/** (NEW) For Clip/Drag operations, what internal flavor does this exporter operate on? 
		*/
		virtual PMFlavor GetInternalFlavor(void) const;
		
		/** (NEW) For Clip/Drag operations, what external flavors can this exporter produce?
			This method returns the number of supported external flavors.
		*/
		virtual int32 CountExternalFlavors(void) const;
		
		/** (NEW) For Clip/Drag operations, what external flavors can this exporter produce?
			This method returns the Nth supported external flavor.
		*/
		virtual ExternalPMFlavor GetExternalFlavor(int32 n) const;

		/** (NEW) For Clip/Drag operations, what format type, if any, would be used 
			to produce the desired external flavor?
		*/
		virtual bool16 CanExportThisFlavor(const ExternalPMFlavor& flavor, PMString& outFormatName) const;
			
		/** (NEW) Externalize the given data to a stream.
		*/
		virtual ErrorCode ExportForExternalize(IDataExchangeHandler* handler, const ExternalPMFlavor toWhichFlavor, IPMStream* stream);
			
		/**
            This member gets the name of the format at the passed in index value.
        */
		virtual PMString  	GetNthFormatName(int32 n);
		
		/**
            Counts the available formats of the filter
        */
		virtual int32   	CountFormats(void);
		
		/**
            Just gets the extension for the format.
            @param formatName Specifies the format name.
        */
		virtual PMString  	GetExtensionForFormatName(const PMString& formatName);

		/**
		 Returns the ScriptID for the given format's enumerator in the kExportFormatEnumScriptElement
		 @param formatName	IN Format name whose ScriptID to return
		 @param context is the scripting request context
		 @return the ScriptID (or kInvalidScriptID if this format is not supported by enum)
		 */
		virtual ScriptID GetScriptIDForFormatName(const PMString& formatName, const ScriptInfo::RequestContext& context) ;

private:
	/** Opens the dialog for getting the encoding option.
	*/
	void DoDialog(void);

	/** Send an export signal to responders
		@param service IN is the signal's service ID
		@param document IN is the target document
		@param sysFile IN is the file being exported
		@param formatName IN is the format being exported
		@param uiFlags IN are the ui flags
		@param bIsStandAlone IN is this a single-file export (kTrue), or part of a multi-file export(kFalse)
	*/
	virtual ErrorCode SendSignal( const ServiceID& service, IDocument* document, const IDFile& sysFile, const PMString& formatName, UIFlags uiFlags, bool8 bIsStandAlone = kTrue ) ;
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(TxtExpFilter, kTxtExpFilterImpl)


/* TxtExpFilter Constructor 
*/
TxtExpFilter::TxtExpFilter(IPMUnknown *boss)
 : CExportProvider(boss)
{
	// Get the IntData pointer for the encoding option, and initialize it
    IIntData* iEncoding = TxtExpUtils::GetEncodingIntData();
	if (iEncoding) 
	{
		iEncoding->Set((int32)ITxtExpFileWriter::kTxtExpEncodingInvalid);
	}
}

/*
*/
TxtExpFilter::~TxtExpFilter(void)
{
    // cleanup the encoding intdata interface
	bool16 release = kTrue;
	TxtExpUtils::GetEncodingIntData(release);
}


/* ExportToFile
	This method provides an implementation, but alternatively, 
	we could use CExportProvider::ExportToFile, which does the same thing 
	without the extra assert.
*/
void TxtExpFilter::ExportToFile(const IDFile& sysFile, IDocument* doc, IPMUnknown* targetboss, const PMString& formatName, UIFlags uiFlags)
{
	do 
	{
		InterfacePtr<IPMStream> stream(StreamUtil::CreateFileStreamWriteLazy(sysFile, kOpenOut | kOpenTrunc));
		if (!stream)
		{
			ASSERT_FAIL("TxtExpFilter::ExportToFile : couldn't open a stream. Skipping export.");
			break;
		}
		this->ExportToStream(stream, doc, targetboss, formatName, uiFlags);

	} while (kFalse);
}

/* ExportToStream 
*/
void TxtExpFilter::ExportToStream(IPMStream* stream, IDocument* doc, IPMUnknown* targetboss, const PMString& formatName, UIFlags uiFlags)
{
	// assume failure, check for success
	ErrorCode rc = kFailure;
	
	do 
	{
		ITxtExpFileWriter::Encoding encoding = ITxtExpFileWriter::kTxtExpEncodingInvalid;

		IIntData* iEncoding = TxtExpUtils::GetEncodingIntData();
		if (!iEncoding) 
		{
			ASSERT_FAIL("TxtExpFilter::ExportToStream : iEncoding is nil!");
			break;
		}

		if (uiFlags != kSuppressUI) 
		{
			// Popup a dialog asking for encoding types
			DoDialog();
			
			// get index for encoding selection
			
			encoding = (ITxtExpFileWriter::Encoding)(iEncoding->Get());
			if (encoding == ITxtExpFileWriter::kTxtExpEncodingInvalid) 
			{
				// user must have cancelled if the encoding is Invalid at this point.
				rc = kCancel;
				break;
			}
		}
		else
		{
			// If the dialog wasn't opened, set a default
            if (LocaleSetting::GetLocale().GetFeatureSetId() == kInDesignJapaneseFS)
			{
				encoding = ITxtExpFileWriter::kTxtExpEncodingShiftJIS;
			}
			else
			{
				encoding = ITxtExpFileWriter::kTxtExpEncodingASCII;
			}
		}

		if (!doc || !targetboss) 
		{
			ASSERT_MSG(doc != nil && targetboss != nil, "TxtExpFilter::ExportToStream : Called for no document or targetboss");
			break;
		}

		InterfacePtr<ITxtExpSuite> iTxtExpSuite
			(static_cast<ITxtExpSuite*>(Utils<ISelectionUtils>()->QuerySuite(ITxtExpSuite::kDefaultIID)));
		if(iTxtExpSuite && iTxtExpSuite->CanExportText(formatName))
		{
			IDFile outputFile;
			InterfacePtr<IFileStreamData> fileData(stream, IID_IFILESTREAMDATA);
			if (fileData != nil)
				outputFile = fileData->GetSysFile();

			rc = SendSignal(kBeforeExportSignalResponderService, doc, outputFile, formatName, uiFlags);
			if (rc == kSuccess)
			{
				rc = iTxtExpSuite->DoExportText(stream, encoding);
				ServiceID signal((rc == kSuccess)? kAfterExportSignalResponderService : kFailedExportSignalResponderService);
				SendSignal(signal, doc, outputFile, formatName, uiFlags);
			}
		}
	} while (kFalse);

	// Set the global error state upon a failed export
	if (rc != kSuccess)
	{
		ErrorUtils::PMSetGlobalErrorCode(rc);
	}
}
		
/* CanExportToFile 
*/
bool16 TxtExpFilter::CanExportToFile(void) const
{
	return kTrue;
}
		

/* CanExportThisFormat
*/
bool16 TxtExpFilter::CanExportThisFormat(IDocument* doc, IPMUnknown* targetboss, const PMString& formatName)
{
	do {

		if (!doc || !targetboss || formatName.empty()) 
		{
			ASSERT_FAIL("TxtExpFilter::CanExportThisFormat : doc or targetboss is nil or format is nil");
			break;
		}
	
		InterfacePtr<ITxtExpSuite> iTxtExpSuite
			(static_cast<ITxtExpSuite*>(Utils<ISelectionUtils>()->QuerySuite(ITxtExpSuite::kDefaultIID)));
		if (iTxtExpSuite)
		{
			return iTxtExpSuite->CanExportText(formatName);
		}
	} while (kFalse);

	return kFalse;
}


/* CanExportForExternalize
*/
bool16 TxtExpFilter::CanExportForExternalize(void) const
{
	// NOTE: Support for external drag and drop is in ExportForExternalize()
	return kTrue;
}

/* GetInternalFlavor
*/
PMFlavor TxtExpFilter::GetInternalFlavor(void) const
{
    return kTEXTFlavor;
}
		

/** This export filter supports 2 external flavors
*/
const int32 kTxtExpFilterFlavors = 2;

/* CountExternalFlavors
*/
int32 TxtExpFilter::CountExternalFlavors(void) const
{
	return kTxtExpFilterFlavors;
}

/* GetExternalFlavor
*/
ExternalPMFlavor TxtExpFilter::GetExternalFlavor(int32 n) const
{
	ExternalPMFlavor flavor = kNoExternalFlavor;
	if (n == 0)
	{
		// JIS, ShiftJIS, and ASCII are in this category.
		flavor = kTEXTExternalFlavor;
	}
	else if (n == 1)
	{
		// UNICODE text files have a different filetype on the Macintosh.
		flavor = kUNICODETEXTExternalFlavor;
	}
	return flavor;
}

/* CanExportThisFlavor
*/
bool16 TxtExpFilter::CanExportThisFlavor(const ExternalPMFlavor& flavor, PMString& outFormatName) const
{
	int32 n = CountExternalFlavors();
	int32 i = 0;
	bool16 bFound = kFalse;

	while ((bFound == kFalse) && (i < n))
	{
		if (flavor == GetExternalFlavor(i++)) 
		{
			bFound = kTrue;
		}
	}
	return bFound;
}
			
/* ExportForExternalize
	The DataExchangeHandlerFlavorHelper will tell us which type of a DataExchange handler
	we need to use (1st parameter).  If we can get the ITextScrapData interface
	from the handler, we know we are at least looking at some ITextModel.
*/
ErrorCode TxtExpFilter::ExportForExternalize(IDataExchangeHandler* handler, const ExternalPMFlavor toWhichFlavor, IPMStream* stream)
{
	// drag and drop support
	ErrorCode rc = kFailure;
	do {

		PMString formatName;
		if (!this->CanExportThisFlavor(toWhichFlavor, formatName))
		{
			ASSERT_FAIL("TxtExpFilter::ExportForExternalize : Can't export this flavor!");
			break;
		}
		
		InterfacePtr<ITextScrapData> tsd(handler, IID_ITEXTSCRAPDATA);
		if (!tsd)
		{
			ASSERT_FAIL("TxtExpFilter::ExportForExternalize : text scrap data is nil!");
			break;
		}
		
		TextIndex   threadStart = kInvalidTextIndex;
		int32       threadSpan = 0;
		
		InterfacePtr<ITextModel> model(tsd->GetStoryRef(), UseDefaultIID());
		if (!model)
		{
			ASSERT_FAIL("TxtExpFilter::ExportForExternalize : text model is nil!");
			break;
		}
		
		model->GetStoryThreadSpan(0, &threadStart, &threadSpan);
		int32  threadEnd = threadStart + threadSpan;
		UIDRef modelRef = ::GetUIDRef(model);
		
		InterfacePtr<ITextTarget> targetboss ((ITextTarget*)::CreateObject(kTextSuiteBoss, IID_ITEXTTARGET));
		if (targetboss)
		{
			targetboss->SetTextUnmanaged( modelRef, RangeData(threadStart, threadEnd));
		}
		
		IDataBase* db = ::GetDataBase(model);
		if (!db) 
		{
			ASSERT_FAIL("TxtExpFilter::ExportForExternalize : database is nil!");
			break;
		}
        
		InterfacePtr<IDocument> doc(db, db->GetRootUID(), IID_IDOCUMENT);
		if (!doc) 
		{
			ASSERT_FAIL("TxtExpFilter::ExportForExternalize : document is nil!");
			break;
		}

		// Turn around and call ExportToStream in this class.
		// See ExportToStream() about the UIflags options.
		this->ExportToStream(stream, doc, targetboss, formatName, kSuppressUI);

		rc = ErrorUtils::PMGetGlobalErrorCode();

	} while (kFalse);

	return rc;
}
			

/* GetNthFormatName
*/
PMString TxtExpFilter::GetNthFormatName(int32 n)
{
	PMString formatName(kTxtExpFormatNameKey);
	return formatName;	
}

/* CountFormats
*/
int32 TxtExpFilter::CountFormats(void)
{
	return 1;
}


/* GetExtensionForFormatName 
*/
PMString TxtExpFilter::GetExtensionForFormatName(const PMString& formatName)
{
	PMString extension("");
	do {
		PMString copyFormatName(formatName);
		copyFormatName.Translate();
		PMString ourFormatName(kTxtExpFormatNameKey, PMString::kTranslateDuringCall);

		// only return extension if this is the format name we are looking for
		// fix: 16-Apr-2003 sadahiro (resolves assert for text frame context menu)
		if (copyFormatName == ourFormatName) 
		{
			extension = kTxtExpFileExtensionKey;
		}
	} while (false);
	return extension;
}

/** GetScriptIDForFormatName
*/
ScriptID TxtExpFilter::GetScriptIDForFormatName(const PMString& formatName, const ScriptInfo::RequestContext& context)
{
	return kInvalidScriptID ;
}


/* DoDialog
*/
void TxtExpFilter::DoDialog(void)
{
	do
	{
		// Get the application interface and the DialogMgr.	
		InterfacePtr<IApplication> application(GetExecutionContextSession()->QueryApplication());
		if (!application)
		{
			ASSERT_FAIL("TxtExpActionComponent::DoAction: application invalid"); 
			break;
		}
		InterfacePtr<IDialogMgr> dialogMgr(application, UseDefaultIID());
		if (!dialogMgr)
		{ 
			ASSERT_FAIL("TxtExpActionComponent::DoAction: dialogMgr invalid"); 
			break;
		}
		IIntData* iEncoding = TxtExpUtils::GetEncodingIntData();
		if (!iEncoding) 
		{
			ASSERT_FAIL("TxtExpActionComponent::DoAction: iEncoding is nil!");
			break;
		}

		// Load the plug-in's resource.
		PMLocaleId nLocale = LocaleSetting::GetLocale();
		RsrcSpec dialogSpec
		(
			nLocale,					// Locale index from PMLocaleIDs.h. 
			kTxtExpPluginID,			// Our Plug-in ID from TxtExpID.h. 
			kViewRsrcType,				// This is the kViewRsrcType.
			kSDKDefDialogResourceID,	// Resource ID for our dialog.
			kTrue						// Initially visible.
		);

		// CreateNewDialog takes the dialogSpec created above, and also
		// the type of dialog being created (kMovableModal).
		IDialog* dialog = dialogMgr->CreateNewDialog(dialogSpec, IDialog::kMovableModal);
		if (!dialog)
		{ 
			ASSERT_FAIL("TxtExpActionComponent::DoDialog: can't create dialog"); 
			break;
		}
        
        // check to see what the encoding option is BEFORE (for debugging)
		TRACEFLOW("TextExportFilter", "TxtExpFilter::DoDialog : encoding IntData BEFORE dialog is %d\n", iEncoding->Get());
		
		// Open the dialog and wait.  Dialog manager will close it for us.
		dialog->Open(); 
		dialog->WaitForDialog();
		
		// check to see what the encoding option is AFTER (for debugging)
		TRACEFLOW("TextExportFilter", "TxtExpFilter::DoDialog : encoding IntData AFTER dialog is %d\n", iEncoding->Get());
	
	} while (false);			
}


ErrorCode TxtExpFilter::SendSignal( const ServiceID& service, IDocument* document, const IDFile& sysFile, const PMString& formatName, UIFlags uiFlags, bool8 bIsStandAlone )
{
	return CExportProvider::SendSignal(service, document, sysFile, formatName, uiFlags, bIsStandAlone);
}

// End, TxtExpFilter.cpp.
