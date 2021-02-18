//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/textimportfilter/TxtImpFilter.cpp $
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
//  This is where the filter does all of the actual work.
//  This import provider imports text files with the .CPP extension, if multiple ImportProviders
//  import the same file type, the first import that returns "kFullImport" will import the
//  file, and the others will not get a chance - so I chose to import .cpp files for this
//  example.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// C/C++ includes
#ifdef MACINTOSH
#include <wchar.h>
#include <string.h>
using namespace std;
#endif

// API:
#include "CmdUtils.h"
#include "CoreResTypes.h"
#include "CPMUnknown.h"
#include "CreateObject.h"
#include "CTUnicodeTranslator.h"
#include "ErrorUtils.h"
#include "IApplication.h"
#include "ICommand.h"
#include "IFormatType.h"
#include "IImportProvider.h"
#include "IIntData.h"
#include "IK2ServiceProvider.h"
#include "IPMStream.h"
#include "IScrapItem.h"
#include "ISession.h"
#include "ITextModel.h"
#include "ITextUtils.h"
#include "LocaleSetting.h"
#include "PMLocaleId.h"
#include "PMString.h"
#include "ProgressBar.h"
#include "RsrcSpec.h"
#include "StreamUtil.h"
#include "SystemUtils.h"
#include "TextChar.h"
#include "UIDList.h"
#include "Utils.h"
#include "WideString.h"
#include "IFileStreamData.h"
#include "ILinkState.h"

// Project:
#include "TxtImpID.h"
#include "TxtImpUtils.h"
#include "ITxtImpFileReader.h"
#include "SDKFileHelper.h"


/**	Implements an import provider (Place provider, invoked from the File >> Place menu),
	which allows for external files to be placed into an InDesign document.
	Methods allow for getting information about supported file types, and the
	actual importing of the external files.

	@ingroup textimportfilter

*/
class TxtImpFilter : public CPMUnknown<IImportProvider>
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	TxtImpFilter(IPMUnknown* boss);

	/** Destructor
	*/
	virtual ~TxtImpFilter(void);

	/** Get the number of filetypes supported by the import provider. (File types are Mac-specific.)
	*/
	virtual int32 CountFileTypes(void);

	/** Get the Nth filetype supported by the import provider.
	*/
	virtual SysOSType GetFileType(int32 n);

	/**
		Get the number of file formats supported by the import provider.
		An example file format name would be "TIFF" or "MS Word 97".
	*/
	virtual int32 CountFormats();

	/**
		Get the Nth file format supported by the import provider.
	*/
	virtual PMString GetFormatName(int32 formatIndex);

	/** Get the number of extensions that correspond to each file
		format supported by the import provider.
		An example extension would be "DOC" or "TXT".  On the Mac,
		file extensions are only used for import provider selection
		for file of type 'TEXT', '    ', 'BINA', or null.
		Note the file extensions do not include a preceeding period '.'
	*/
	virtual int32 CountExtensionsForFormat(int32 formatIndex);

	/** Get the Nth extension that corresponds to the provided format (index).
	*/
	virtual PMString GetExtensionForFormat(int32 formatIndex, int32 extensionIndex);

	/**	Indicates whether the import provider can import the given file.
		There are three possible results -
		kFullImport: The filter can import this format.
		kPartialImport: The filter can import this file, but there may be a
			better match, only use this filter if no other returns kFullImport
		kCannotImport: This filter does not import this format.
	*/
	virtual ImportAbility CanImportThisType(IFormatType* formatType);

	/**	Indicates whether the import provider can import the given stream.
		In this method, we also check for the file extension, and on the Macintosh,
		we check for the file type as well.
		There are three possible results:
		kFullImport: The filter can import this format.
		kPartialImport: The filter can import this file, but there may be a
			better match, only use this filter if no other returns kFullImport
		kCannotImport: This filter does not import this format.
	*/
	virtual ImportAbility CanImportThisStream(IPMStream* stream);

	/** This method is the main entry point of the import provider.
		If the import fails, the global error code must be set, giving the reason why the import failed.
		To cancel an import, set the global error code to kCancel.
		Please note that the typographer's quotation marks will NOT be modified in this plug-in.
		@param db	The database where the objects are created.
		@param stream	The data to be imported.
		@param uiFlags	Flags to indicate whether the import provider to display or suppress it's user interface
		@param dataLink	Optional. When updating this will contain the original page item UID.  Providers should get their
						import preferences from this page item.  If the preferences are not available on this
						page item, use the default preferences.
		@param asFormat	Optional. Return parameter of the format just imported.  This string is displayed in the
						link information dialog. If the string is not filled in, the method GetFormatName(0) is
						used to get the format name.
		@param importedItem	Returns a UIDRef of the newly created imported item.  This may be a page item or a text story UID.
	*/
	virtual void ImportThis(IDataBase* db, IPMStream* stream, UIFlags uiFlags, UIDRef* importedItem, UIDRef* dataLink = nil, PMString* asFormat = nil);

	/** Gets internal flavor supported by import provider.
		(Flavors are used by clipboard/drag and drop)
	*/
	virtual PMFlavor GetInternalFlavor(void);

	/** Gets the number of external flavors supported by import provider.
		(Flavors are used by clipboard/drag and drop)
	*/
	virtual int32 CountExternalFlavors(void);

	/** Gets the Nth external flavor supported by import provider.
		(Flavors are used by clipboard/drag and drop)
	*/
	virtual ExternalPMFlavor GetExternalFlavor(int32 n);

private:

	/**	Called from ImportThis. This method reads the text from the file stream
		and converts it to UNICODE.
		This method allocates a UTF16TextChar array, and the caller is responsible
		for deleting the array after it is no longer needed.
	*/
	ErrorCode ReadFile(IPMStream* stream, const ITxtImpFileReader::Encoding encoding, UTF16TextChar** buf);

	/** Determines the encoding of the given stream.
		@param stream FileStream to examine.
		@return Encoding type.  See ITxtImpFileReader.h for enum values.
	*/
	ITxtImpFileReader::Encoding DetermineTextEncoding(IPMStream* stream);

	/** Get the file extension for the spec.
		@param spec the file whose extension we want.
	*/
	PMString GetExtension(const IDFile spec);

};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(TxtImpFilter, kTxtImpFilterImpl)


// definition of Implementation class TxtImpFilterFilter

/* Constructor
*/
TxtImpFilter::TxtImpFilter(IPMUnknown *boss)
 : CPMUnknown<IImportProvider>(boss)
{
}

/* Destructor
*/
TxtImpFilter::~TxtImpFilter(void)
{
}


/* CountFileTypes
*/
int32 TxtImpFilter::CountFileTypes(void)
{
	// This filter imports one type of file.
	return 1;
}

/* GetFileType
*/
SysOSType TxtImpFilter::GetFileType(int32 i)
{
	ASSERT_MSG(i == 0, "TxtImpFilter::GetFileType - i == 0");
	return kTxtImpFileType;
}

/* CountFormats
*/
int32 TxtImpFilter::CountFormats(void)
{
	// This filter imports one type of format.
	return 1;
}


/* GetFormatName
*/
PMString TxtImpFilter::GetFormatName(int32 formatIndex)
{
	ASSERT_MSG(formatIndex == 0, "formatIndex != 0?");

	//	SDK Text Import -> this shows up in the place dialog and is unique
	//	enough to stand out from the Text-Only import filter.
	PMString formatName(kTxtImpFormatNameKey);
	return formatName;
}

/* CountExtensionsForFormat
*/
int32 TxtImpFilter::CountExtensionsForFormat(int32 formatIndex)
{
	ASSERT_MSG(formatIndex == 0, "formatIndex out of range");
	return 1;
}

/* GetExtensionForFormat
*/
PMString TxtImpFilter::GetExtensionForFormat(int32 formatIndex, int32 extensionIndex)
{
	ASSERT_MSG(formatIndex == 0, "formatIndex != 0?");
	ASSERT_MSG(extensionIndex == 0, "TxtImpFilter extensionIndex != 0?");

    PMString extension(kTxtImpFileExtensionKey);

    return extension;
}

/* CanImportThisType
*/
IImportProvider::ImportAbility TxtImpFilter::CanImportThisType(IFormatType* formatType)
{
	SysOSType fileType = formatType->GetSysOSType();
	PMString extension(kTxtImpFileExtensionKey);
	PMString incoming_extension;
	formatType->GetExtension(incoming_extension);

	// If extension is matched, we can do full support
	if (incoming_extension.Compare(kFalse, extension) == 0)
		return IImportProvider::kFullImport;

	// Otherwise, if file type is matched, we can do partial support
	if (fileType == kTxtImpFileType)
		return IImportProvider::kPartialImport;


	return IImportProvider::kCannotImport;
}

/* CanImportThisStream
*/
IImportProvider::ImportAbility TxtImpFilter::CanImportThisStream(IPMStream* stream)
{
	// assume we can't import...
	IImportProvider::ImportAbility importAbility = kCannotImport;

	InterfacePtr<IFileStreamData> streamData(stream, IID_IFILESTREAMDATA);

	if (streamData)
	{
		const IDFile file = streamData->GetSysFile();

		PMString supportExtension(kTxtImpFileExtensionKey);

		PMString extension = this->GetExtension(file);

		// determine the text encoding in this stream
		ITxtImpFileReader::Encoding encoding = this->DetermineTextEncoding(stream);
		if (encoding != ITxtImpFileReader::kTxtImpEncodingInvalid)
		{
			/* NOTE:
				This code used to check the file type and creator for the
				Mac platform, however when run in tandem with the TextExportFilter
				sample plug-in on OS X, the stream output by the TextExportFilter
				does not have filetype 'TEXT' (instead it is '????'), so a test on the
				file type would result in a situation where this TextImportFilter can't
				import the exported file.  So, as a workaround, we have modified
				this code to only look at the extension on both platforms (Mac/Win).
			*/
			if (extension.Compare(false, supportExtension) == 0)
			{
				importAbility = IImportProvider::kFullImport;
			}
			else
			{
				/* file extension doesn't match what we expect - so maybe this isn't the right filter.
				   but mark it as "partial import".
				*/
				importAbility = IImportProvider::kPartialImport;
			}
		}
	}
	return importAbility;
}


/* ImportThis
*/
void TxtImpFilter::ImportThis(IDataBase* db, IPMStream* stream, UIFlags uiFlags, UIDRef* importedItem, UIDRef* dataLink, PMString* asFormat)
{
    ErrorCode rc = kFailure;
	UTF16TextChar* buf = nil;
	if (importedItem)
		*importedItem = UIDRef(nil, kInvalidUID);

	do
	{
		if (stream == nil)
		{
			ASSERT(stream);
			break;
		}

		ITxtImpFileReader::Encoding encoding = this->DetermineTextEncoding(stream);
		if (encoding == ITxtImpFileReader::kTxtImpEncodingInvalid)
		{
			ASSERT_FAIL("The text encoding in the file to import is not supported by this import provider");
			// NOTE: But, if it's a Unicode encoding that is not supported by this import provider
			// on this platform, the application's own text import provider may support it...
			break;
		}

		// at this point, the encoding should be valid, so we can proceed.

		// read the file
		rc = this->ReadFile(stream, encoding, &buf);

		if (!buf)
		{
			ASSERT_FAIL("TxtImpFilter::ReadFile returned a nil ptr for 'buf'.  Aborting import.");
			break;
		}
		if (rc != kSuccess)
		{
			ASSERT_FAIL(FORMAT_ARGS("TxtImpFilter::ReadFile returned %d.  Aborting import.", rc));
			break;
		}
		else
		{
			// copy buf to WideString and then set into textmodel

			WideString data;
			int32 theLength = static_cast<int32>(UTF16TextCharLength(buf));
			ASSERT_MSG(theLength, "TxtImpFilter::ImportThis : theLength is 0!");
			data.SetX16String(buf, theLength);

			// Add the text to the model, in 3 easy steps

			// (1) create a new story to which we can insert text.
			UID	newModel = Utils<ITextUtils>()->CreateNewStory(db);
			if (newModel == kInvalidUID)
			{
				ASSERT_FAIL("TxtImpFilter::ImportThis : could not create new story!");
				rc = kFailure;
				break;
			}

			// (2) get its text model
			InterfacePtr<ITextModel> model(static_cast<ITextModel *>(db->Instantiate(newModel, IID_ITEXTMODEL)));
			if (model == nil)
			{
				ASSERT_FAIL("TxtImpFilter::ImportThis : could not get text model!");
				rc = kFailure;
				break;
			}

			// (3) Insert the WideString in the beginning of the text model
			uint32 position = 0;
			// In InDesign 3.0, text edit commands automatically undoable
			// you don't need to track the UndoInfo anymore.
			// Furthermore, as of build 155, text model changes can only give you the option
			// of undoing only in the context of an auto undo redo command.  So we must pass in
			// kFalse in the first argument.
			// If you set it to kTrue, you will get this assert:
			// 	"Cannot request a reversible text model operation outside of the context of an auto undo command."
			model->Insert(position, &data);

			// get the global error code from
			rc = ErrorUtils::PMGetGlobalErrorCode();

			// If DoInsert succeeded, the file has been imported
			if (rc == kSuccess)
			{
   				if(importedItem != nil)
   				{
 					// set the UIDRef to return.
   					*importedItem = UIDRef(db, newModel);

 					// Since we can embed the data into the text model, the
 					// datalink isn't strictly needed.
 					// This allows us to embed the data.
 					InterfacePtr<ILinkState> linkState(db, newModel, UseDefaultIID());
 					if (linkState)
 					{
 						linkState->SetIsLinkNeeded(kFalse);
 					}
   				}
			}
			else
			{
				// When DoInsert fails there is some clean-up we need to do.

				// The the delete command will delete the story, but if there is a reference to the
				//	scrap item, which is part of the story, either the delete would fail - and leak, or
				//	the release of the scrap item would fail.
				// Therefore this code queries for the scrap item and releases it before the deleteStory command
				//	is executed.

				IScrapItem* storyScrap = static_cast<IScrapItem*>(model->QueryInterface(IID_ISCRAPITEM));
				InterfacePtr<ICommand> deleteStory(storyScrap->GetDeleteCmd());
				storyScrap->Release();
				CmdUtils::ProcessCommand(deleteStory);

			} // if (rc == kSuccess) // after InSert

		}// if (rc != kSuccess)...else... // after ReadFile

	} while (kFalse);

	// UTF16TextChar buffer no longer needed
	if (buf)
	{
		delete []buf;
		buf = nil;
	}

	if (rc != kSuccess)
	{
		// couldn't find the right encoding, user cancelled, or the DoInsert failed.
		ErrorUtils::PMSetGlobalErrorCode(rc);
	}
}

/* ReadFile
*/
ErrorCode TxtImpFilter::ReadFile(IPMStream* stream, const ITxtImpFileReader::Encoding encoding,  UTF16TextChar** buf)
{
    int32 fileSize = 0,
	      pos = 0;
	bool16 bDisplayProgress = kFalse;
	bool16 bWasCancelled = kFalse;

    *buf = nil;
    ITxtImpFileReader* reader = nil;
    ErrorCode rc = kSuccess;

	// get the ITxtImpFileReader implementation for the encoding
    reader = TxtImpUtils::QueryTxtImpFileReader(encoding);
    if (reader)
    {

		// rewind the stream to the beginning
		stream->Seek(0, kSeekFromStart);

		// open the file and get the size in bytes
		reader->SetStream(stream);
		fileSize = reader->GetFileSizeInBytes();

		// initialize progress bar, but show only if needed
		RangeProgressBar bar(kTxtImpProgressBarTitleKey, 1, fileSize, bDisplayProgress);

		// allocate a UTF16TextChar buffer big enough
		// NOTE: the caller is responsible for deletion
		*buf = new UTF16TextChar[fileSize+1];
		ASSERT_MSG(*buf, "TxtImpFilterr::ReadFiles : buf is nil!");

		// read the file! with progress bar
		if (bDisplayProgress)
		{
			bar.SetTaskText(kTxtImpInProgressStringKey); // Set the task title.
			bWasCancelled = kFalse;
		}

        const int32 kTxtImpUpdateInterval = 32;

        do
        {
			if (bDisplayProgress)
			{
				if (pos % kTxtImpUpdateInterval == 0)
				{
					// advance progress bar
					bar.SetPosition(pos);
				}
				if (bar.WasCancelled())
				{
					bWasCancelled = kTrue;
					break;
				}
			}

			// get the next character and stuff it into the buffer
			// NOTE: This is code NOT safe with UTF-16 surrogates
            UTF16TextChar nextChar = reader->GetNextTextChar();

			// conditionally insert the nextChar - remove CR in CR/LF
			if (pos == 0)
			{
				(*buf)[pos++] = nextChar;
            }
			else if (!(((*buf)[pos-1] == kTextChar_CR) &&
					   (nextChar == kTextChar_LF)))
			{
				(*buf)[pos++] = nextChar;
			}


			// check for loop break conditions
            if (nextChar == kTextChar_Null)
            {
                // end of file reached.
                break;
            }

        } while (kTrue);

        if (bDisplayProgress && bWasCancelled)
        {
			// aborted!  Roll back - don't import
			rc = kFailure;
        }

		// at this point,  pos is the number of UTF16TextChars read

		// ok, we are done with the file reader, so release it
		reader->Release();

    }
    else
    {
        ASSERT_FAIL("TxtImpFilter::ReadFile : There is no reader!!");
        rc = kFailure;
    }
    return rc;
}

/* DetermineTextEncoding
*/
ITxtImpFileReader::Encoding TxtImpFilter::DetermineTextEncoding(IPMStream* stream)
{
	uchar* buf = nil;
	// get the file size in bytes
	int32 curr = stream->Seek(0, kSeekFromCurrent);
	int32 fileSize = stream->Seek(0, kSeekFromEnd);
	stream->Seek(curr, kSeekFromStart);

	// allocate a buffer
	buf = new uchar[fileSize+1];
	ASSERT_MSG(buf, "TxtImpFilter::DetermineTextEncoding : couldn't allocate buf");

	// read the whole buffer into a uchar array
	stream->XferByte(buf, fileSize);

	// first try to see if it's a Japanese text file.
	ITxtImpFileReader::Encoding encoding =
		TxtImpUtils::DetectJapaneseEncodingType(buf, fileSize);

	// check if the file encoding variable is still EUC-JP
	if (encoding == ITxtImpFileReader::kTxtImpEncodingEUCJP)
	{
		// this encoding isn't supported.
		encoding = ITxtImpFileReader::kTxtImpEncodingInvalid;
	}

    if (buf)
	{
		delete [] buf;
	}

	return encoding;
}


/* GetInternalFlavor
*/
PMFlavor TxtImpFilter::GetInternalFlavor(void)
{
	return kNoFlavor;
}

/* CountExternalFlavors
*/
int32 TxtImpFilter::CountExternalFlavors(void)
{
	// no flavors!
	return 0;
}

/* GetExternalFlavor
*/
ExternalPMFlavor TxtImpFilter::GetExternalFlavor(int32 n)
{
	return kNoFlavor;
}

PMString TxtImpFilter::GetExtension(const IDFile spec)
{
	PMString extension;
	SDKFileHelper fileHelper(spec);
	PMString name = fileHelper.GetPath();

#ifdef MACINTOSH

	// We grab since we're only finding the extension
	// and won't be modifying the name.
	std::string sname = name.GetPlatformString();
	const char* pathName = sname.c_str();

	uint32 strLen = sname.length();
	uint32 currentPos = 0;

	if ( strLen > 0 && pathName != nil)
	{
		const char* endOfPath = pathName + strLen - 1;

		// Find the period.  It better be in one of the last
		// four positions
		while ( strLen > 0 && *endOfPath != '.' && currentPos < 4 )
		{
			endOfPath--;
			strLen--;
			currentPos++;
		}

		if ( *endOfPath == '.' )
		{
			endOfPath++;

			for ( uint32 strPos = 0; strPos < currentPos; strPos++ )
				extension.Append ((char)std::toupper(*endOfPath++));
		}
	}
#else		// Windows

	// We grab since we're only finding the extension
	// and won't be modifying the name.
	TCHAR* pathName = name.GrabTString();
	uint32 strLen = pathName ? static_cast<int32>(_tcslen(pathName)) : 0;
	uint32 currentPos = 0;

	//	NOTE: This loop is not multibyte safe (it works but ONLY because the only characters
	//	being searched for are below 0x40 and are thus unambiguous in CJK encodings.
	if ( strLen > 0 && pathName != nil)
	{
		TCHAR* endOfPath = pathName + strLen - 1;

		while (strLen > 0 && (*endOfPath == ' ' || *endOfPath == '"'))
		{
			endOfPath--;
			strLen--;
		}

		while ( strLen > 0 && *endOfPath != TEXT('.') )
		{
			endOfPath--;
			strLen--;
			currentPos++;
		}

		if ( *endOfPath == TEXT('.') )
		{
			endOfPath++;

			for ( uint32 strPos = 0; strPos < currentPos; strPos++ )
				extension.Append ((TCHAR)toupper(*endOfPath++));
		}
	}

#endif

	return extension;
}

// End, TxtImpFilter.cpp.



