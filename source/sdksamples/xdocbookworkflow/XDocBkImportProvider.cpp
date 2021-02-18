//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xdocbookworkflow/XDocBkImportProvider.cpp $
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
#include "IFileStreamData.h"
#include "IFormatType.h"
#include "IImportProvider.h"
#include "IPMStream.h"
#include "IWorkspace.h"
#include "IXDocBkFacade.h"
#include "IFileStreamData.h"
#include "IXMLImportOptionsPool.h"
#include "IK2ServiceRegistry.h"
#include "IK2ServiceProvider.h"
#include "IXMLImportPreferences.h"

// General includes:
#include "CPMUnknown.h"
#include "ErrorUtils.h"
#include "SDKFileHelper.h"
#include "SDKLayoutHelper.h"
#include "Utils.h"
#include "XMLID.h"
#include "WideString.h"
#include "Swap.h"

// Project includes:
#include "XDocBkID.h"


/** Implements IImportProvider; opens a template to create a new document and 
	imports XML into this new document.

	@ingroup xdocbookworkflow
 */
class XDocBkImportProvider : public CPMUnknown<IImportProvider>
{
public:
	/** Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	XDocBkImportProvider(IPMUnknown* boss);

	/** Destructor
	 */
	virtual ~XDocBkImportProvider() {}
	

	/** Get the number of filetypes supported by the import provider. (File types are Mac-specific.)
		@see IImportProvider::CountFileTypes
	*/
	virtual int32 CountFileTypes(void);

	/** Get the Nth filetype supported by the import provider. 
		@see IImportProvider::GetFileType
		@param n IN The index.  Must be greater than 0, less than CountFileTypes().
		@return The Nth filetype.
	*/
	virtual SysOSType GetFileType(int32 n);

	/** Get the number of file formats supported by the import provider.
		An example file format name would be "TIFF" or "MS Word 97".
		@see IImportProvider::CountFormats
	*/  
	virtual int32 CountFormats(void);

	/** Get the Nth file format supported by the import provider.
		@see IImportProvider::GetFormatName
		@param n The index.  Must be greater than 0, less than CountFormats().
		@return The Nth formatname, as a PMString.
	*/  
	virtual PMString GetFormatName(int32 formatIndex);

	/** Get the number of extensions that correspond to each file 
		format supported by the import provider.  
		An example extension would be "DOC" or "TXT".  On the Mac,
		file extensions are only used for import provider selection
		for file of type 'TEXT', '    ', 'BINA', or null.
		Note the file extensions do not include a preceeding period '.'
		@see IImportProvider::CountExtensionsForFormat
		@param formatIndex Must be between 0 and CountFormats().
		@return The number of extensions supported by this import provider.
	*/
	virtual int32 CountExtensionsForFormat(int32 formatIndex);

	/** Get the Nth extension that corresponds to the provided format (index).
		@see IImportProvider::GetExtensionForFormat
		@param formatIndex Must be between 0 and CountFormats().
		@param extensionIndex Must be between 0 and CountExtensionsForFormat().
		@return The extension for the specified format.
	*/
	virtual PMString GetExtensionForFormat(int32 formatIndex, int32 extensionIndex);

	/**	Indicates whether the import provider can import the given file type (Mac only).
		There are three possible results - 
		\li IImportProvider::kFullImport: The filter can import this format.
		\li IImportProvider::kPartialImport: The filter can import this file, but there may be a 
			better match, only use this filter if no other returns kFullImport
		\li IImportProvider::kCannotImport: This filter does not import this format.
		@see IImportProvider::CanImportThisType
		@param formatType The format type to test.
		@return Whether or not this import provider could import this type. 
	*/
	virtual ImportAbility CanImportThisType(IFormatType* formatType);

	/**	Indicates whether the import provider can import the given stream.
		In this method, we also check for the file extension, and on the Macintosh, 
		we check for the file type as well.
		There are three possible results:
		\li IImportProvider::kFullImport: The filter can import this format.
		\li IImportProvider::kPartialImport: The filter can import this file, but there may be a 
			better match, only use this filter if no other returns kFullImport
		\li IImportProvider::kCannotImport: This filter does not import this format.
		@see IImportProvider::CanImportThisStream
		@param stream The stream to test.
		@return Whether or not this import provider could import this stream. 
	*/
	virtual ImportAbility CanImportThisStream(IPMStream* stream);

	/** This method is the main entry point of the import provider and does most of the work.
		@see IImportProvider::ImportThis
		@param db	The database where the objects are created.
		@param stream	The data to be imported.
		@param uiFlags	Flags to indicate whether the import provider to display or suppress it's user interface
		@param pDataLinkUIDRef	Optional. When updating this will contain the original page item UID.  Providers should get their
						import preferences from this page item.  If the preferences are not available on this
						page item, use the default preferences.
		@param asFormat	Optional. Return parameter of the format just imported.  This string is displayed in the
						link information dialog. If the string is not filled in, the method GetFormatName(0) is
						used to get the format name.
		@param importedItem	Returns a UIDRef of the newly created imported item.  This may be a page item or a text story UID.
	*/
	virtual void ImportThis(IDataBase* db, IPMStream* stream, UIFlags uiFlags, UIDRef* importedItem, UIDRef* pDataLinkUIDRef = nil, PMString* asFormat = nil);

	/** Gets internal flavor supported by import provider. 
		(Flavors are used by clipboard/drag and drop)
		@see IImportProvider::GetInternalFlavor 
	*/
	virtual PMFlavor GetInternalFlavor(void);

	/** Gets the number of external flavors supported by import provider. 
		(Flavors are used by clipboard/drag and drop)
		@see IImportProvider::CountInternalFlavors
	*/
	virtual int32 CountExternalFlavors(void);

	/** Gets the Nth external flavor supported by import provider. 
		(Flavors are used by clipboard/drag and drop)
		@see IImportProvider::GetExternalFlavor
	*/
	virtual ExternalPMFlavor GetExternalFlavor(int32 n);

private:
	
	// member variables
	UIDRef  fDocUIDRef;
	IDFile fXDocBkSysFile;
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(XDocBkImportProvider, kXDocBkImportProviderImpl)

/* 
*/
XDocBkImportProvider::XDocBkImportProvider(IPMUnknown* boss)
 : CPMUnknown<IImportProvider>(boss), fDocUIDRef(UIDRef::gNull)
{
}


/* 
*/
int32 XDocBkImportProvider::CountFileTypes(void)
{
	return 1;
}

/* 
*/
SysOSType XDocBkImportProvider::GetFileType(int32 i)
{
	ASSERT(i == 0);
	return kXDocBkFileOSType;
}

/* 
*/
int32 XDocBkImportProvider::CountExtensionsForFormat(int32 formatIndex)
{
	
	ASSERT(formatIndex == 0);
	return 1;
}

/* 
*/
int32 XDocBkImportProvider::CountFormats(void)
{
	
	return 1;
}

/* 
*/
PMString XDocBkImportProvider::GetExtensionForFormat(int32 formatIndex, int32 extensionIndex)
{
	ASSERT(formatIndex == 0);
	ASSERT(extensionIndex == 0);
	PMString extension(kXDocBkFileExtensionKey);

	return extension;
}

/* 
*/
PMString XDocBkImportProvider::GetFormatName(int32 formatIndex)
{   
	ASSERT(formatIndex == 0);

	PMString formatName(kXDocBkFormatKey, PMString::kTranslateDuringCall); // "SDK XDocBook format"
	return formatName;
}

/* 
*/
IImportProvider::ImportAbility XDocBkImportProvider::CanImportThisType(IFormatType* formatType)
{   
		// We require a DCBK extension for the import to happen
	PMString ourExtension(kXDocBkFileExtensionKey);
	PMString extension;
	formatType->GetExtension(extension);        
	if(extension.IsEqual(ourExtension, kFalse)) // Do case-insens compare
	{
		//if (!Utils<IXDocBkFacade>()->AreOptionsSet())
		//{
			// we can maybe import this but we're not yet set up right
		//	return IImportProvider::kPartialImport;
		//}
		return IImportProvider::kFullImport;
	}

	return IImportProvider::kCannotImport;
}

/* 
*/
IImportProvider::ImportAbility XDocBkImportProvider::CanImportThisStream(IPMStream* stream)
{
	ASSERT(stream);
	do {
		if(!stream) {
			break;
		}
		// We need to be reading from a file, and have the right extension on the file
		InterfacePtr<IFileStreamData> fileStreamData(stream, IID_IFILESTREAMDATA);
		if(!fileStreamData) {
			break;
		}

		IDFile importingIDFile = fileStreamData->GetSysFile();
		SDKFileHelper imprtingFileHelper(importingIDFile);
		PMString importingPath = imprtingFileHelper.GetPath();
		PMString ourExtension(kXDocBkFileExtensionKey);
		PMString newExt(ourExtension);
		// If we were being paranoid, we'd get the last dot and check the extension.
		// For now, I'm happy to just see if we have dcbk in the filename
		if(!importingPath.Contains(newExt)) {
			break;
		}
		if (!stream->IsReading()) {
			break;
		}

		// make sure we're at the beginning
		// The AXE parser handles diff't encodings on XML import
		// and I don't know of a way to ask it if it can do the import
		//
		stream->Seek(0, kSeekFromStart);
		// read out the first 5 bytes
		// This initially assumes UTF-8 encoding
		const int32 cCountCharsInXmlHeader =5;
		uchar buf[cCountCharsInXmlHeader+2];
		stream->XferByte(buf, 2);
		
		if(buf[0] == '<' && buf[1] == '?')
		{
			stream->XferByte(buf+2, cCountCharsInXmlHeader-2);
			buf[cCountCharsInXmlHeader] = '\0';
			// check for "<?xml" at the beginning of the file 
			if(WideString((ConstCString)buf) == WideString("<?xml"))
			{
				return IImportProvider::kFullImport;
			}
		}
		// We may have UTF 16, the first two bytes should be 0xfeff
		else if(buf[0] == 0xff && buf[1] == 0xfe)
		{
			// Now test for UTF-16 XML
			bool16 byteSwap = kFalse;
			
#if IS_BIG_ENDIAN_ARCH
			byteSwap = kTrue;
#endif
			WideString testHeader;
			for(int32 i = 0; i < cCountCharsInXmlHeader; i++) {
				int16 unswappedChar(0);
				bool16 readOK = stream->XferInt16(unswappedChar);
				if(!readOK) {
					break;
				}
				testHeader.Append(!byteSwap ? unswappedChar : ByteSwapReverse::SwapInt16(unswappedChar));
			}
			// check for "<?xml" at the beginning of the file 
			if (WideString("<?xml") == testHeader)
			{
				return IImportProvider::kFullImport;
			}
		}
	} while(kFalse);

	// Default: we don't know how to do this import
	return IImportProvider::kCannotImport;
}

/* 
*/
void XDocBkImportProvider::ImportThis(IDataBase* db, 
									  IPMStream* stream, 
									  UIFlags uiFlags, 
									  UIDRef* pNewDocUIDRef, 
									  UIDRef* pDataLinkUIDRef /* optional! */, 
									  PMString* asFormat /* ditto */)
{
	ErrorCode retval = kFailure;
	fDocUIDRef = UIDRef::gNull;
	bool16 oldUndoState = kTrue;
	SDKLayoutHelper layoutHelper;
	do
	{
		InterfacePtr<IFileStreamData> iFileStreamData(stream, IID_IFILESTREAMDATA);
		ASSERT(iFileStreamData);
		if (!iFileStreamData)
		{
			break;
		}
		fXDocBkSysFile = iFileStreamData->GetSysFile();

		Utils<IXDocBkFacade> xdocbkFacade;
		ASSERT(xdocbkFacade);
		if (!xdocbkFacade)
		{
			break;
		}
		PMString templatePath = xdocbkFacade->GetTemplatePath();
		if(templatePath.empty()) {
			templatePath = xdocbkFacade->GetDefaultTemplateFromFolder(fXDocBkSysFile);
		}
		ASSERT(!templatePath.empty());
		if (templatePath.empty()) {
			ErrorUtils::PMSetGlobalErrorCode(kXDocBkTemplateUninitializedErr);
			break;
		}
		SDKFileHelper fileHelper(templatePath);
		ASSERT(fileHelper.IsExisting());
		if (!fileHelper.IsExisting()) {
			break;
		}
		IDFile templateSysFile = fileHelper.GetIDFile();

		fDocUIDRef = layoutHelper.OpenDocument(templateSysFile);

		ASSERT(fDocUIDRef != UIDRef::gNull);
		if (fDocUIDRef == UIDRef::gNull)
		{
			break;
		}
		
		CmdUtils::AutoUndoSequencePtr seq(fDocUIDRef.GetDataBase());

		// Turn off CALS table support of InDesign core, to let our contentghandler do the job
		InterfacePtr<IDocument> document(fDocUIDRef, UseDefaultIID());
        InterfacePtr<IXMLImportOptionsPool> prefsPool( document->GetDocWorkSpace(), UseDefaultIID() );
		InterfacePtr<IK2ServiceRegistry> serviceRegistry(GetExecutionContextSession(), UseDefaultIID());
		InterfacePtr<IK2ServiceProvider> serviceProvider(serviceRegistry->QueryServiceProviderByClassID(kXMLImportMatchMakerSignalService, kXMLTableMatchMakerServiceBoss));
		ASSERT(serviceProvider);
		if(!serviceProvider)
		{
			break;
		}
		InterfacePtr<IXMLImportPreferences> prefs(serviceProvider, IID_IXMLIMPORTCALSPREFERENCES);
		XMLImportPreferencesInitializer initializer(prefs, prefsPool);
		bool16	importCALS = prefs->GetNthPrefAsBool(0);
		prefs->SetNthPref(0, kFalse); // set to false, and will reset it back
		prefs->CommitChanges();

		// This may be empty: if so we don't really care
		PMString stylesheetPath = xdocbkFacade->GetStylesheetPath();
		retval = xdocbkFacade->ImportXMLFile(this->fXDocBkSysFile, this->fDocUIDRef, stylesheetPath); 

		prefs->Initialize(prefsPool);
		prefs->SetNthPref(0, importCALS); // Reset back to original, and will reset it back
		prefs->CommitChanges();


		// TODO sa+ define kErrorIDSpace IDs and an error string service to pop warnings of errors
		// that can occur during open that you want to warn the user of.

		//ASSERT(retval == kSuccess);
		if (retval != kSuccess) {
			break;
		}


		retval = xdocbkFacade->ResizeInlines(this->fDocUIDRef);
		ASSERT(retval == kSuccess);
		if (retval != kSuccess)
		{
			break;
		}

		ASSERT(pNewDocUIDRef);
		if (!pNewDocUIDRef)
		{
			break;
		}
		*pNewDocUIDRef = fDocUIDRef;
		
		retval = kSuccess;

	} while (kFalse);


	if (retval == kFailure)
	{
		ErrorUtils::PMSetGlobalErrorCode(kFailure);
		//close the opened document/template
		layoutHelper.CloseDocument(fDocUIDRef, kFalse, kSuppressUI);
		*pNewDocUIDRef = UIDRef(nil, kInvalidUID);
	}

} // ImportThis



/*  
*/
PMFlavor XDocBkImportProvider::GetInternalFlavor(void)
{
	return kNoFlavor;
}

/*  
*/
int32 XDocBkImportProvider::CountExternalFlavors(void)
{
	return 0;
}

/* 
*/
ExternalPMFlavor XDocBkImportProvider::GetExternalFlavor(int32 n)
{
	return kNoFlavor;
}






// End, XDocBkImportProvider.cpp.


