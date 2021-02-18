//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/chmlfilter/CHMLFiltExportProvider.cpp $
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

// Interfaces includes
#include "IExportProvider.h"
#include "IFileStreamData.h"
#include "isignalmgr.h"
#include "IExportProviderSignalData.h"

// General includes
#include "CExportProvider.h"
#include "StreamUtil.h"
#include "CPMUnknown.h"
// Project includes
#include "CHMLFiltID.h"
#include "CHMLFiltHelper.h"

/** Class that implements IExportProvider to enable the geometry and images in a layout to be exported. 
	@ingroup chmlfilter
*/
class CHMLFiltExportProvider : public CExportProvider
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	CHMLFiltExportProvider(IPMUnknown* boss);

    /** Destructor.
	*/
	virtual ~CHMLFiltExportProvider(void);

		/**  	Export the current selection to a file using the given filename. Generate the specified file
		format. The calling code verifies that the file does not exist. 

		@param sysFile IN specifies the location of file to export to
		@param doc IN document containing content to export
		@param targetboss IN means to acquire selection target (if not nil)
		@param formatName IN
		@param uiFlags IN
		@precondition doc should not be nil, formatName should be a format this provider understands
		@postcondition sysFile should contain exported content from doc subject to selection target content specified by
			targetBoss (nil if no selection)
	*/
	virtual void ExportToFile(const IDFile& sysFile, 
									IDocument* doc, 
									IPMUnknown* targetboss, 
									const PMString& formatName, 
									UIFlags uiFlags = kFullUI);

	/**  Export the current selection to a stream.

		@param stream IN stream to write to
		@param doc IN document containing content to export
		@param targetboss IN means to acquire selection target (if not nil)
		@param formatName IN identifies the format
		@param uiFlags IN what UI should be used
		@precondition doc should not be nil, formatName should be a format this provider understands
		@postcondition stream should contain exported content
	*/
	virtual void ExportToStream(IPMStream* stream,
												IDocument* doc, 
												IPMUnknown* targetboss, 
												const PMString& formatName, 
												UIFlags uiFlags = kFullUI);

	/**  The provider indicates whether it can do normal file based exports.
		@return kTrue if normal file-based export can be achieved, kFalse otherwise
		
	*/
	virtual bool16 CanExportToFile(void) const;

	/**  The export provider indicates whether it can export the current selection target in the
		specified file format.

		@param doc IN document containing content to export
		@param targetboss IN means to acquire selection target (if not nil)
		@param formatName IN identifies format for export
		
		@return kTrue if format can be exported, kFalse otherwise
		
	*/
	virtual bool16 CanExportThisFormat(IDocument* doc, IPMUnknown* targetboss, const PMString& formatName);
	/**  The provider indicates whether it export for externalize- i.e. data transfer (not supported by this implementation).	
		@return kTrue if this can export for externalize, kFalse
		
	*/
	virtual bool16 CanExportForExternalize(void) const;

	/**  For Clip/Drag operations, the internal flavor that this exporter operates on (not supported by this implementation).
		@return internal flavour supported by this export provider
	*/
	virtual PMFlavor GetInternalFlavor(void) const;

	/**  For Clip/Drag operations, the count of  external flavors that this exporter could produce 
		(not supported by this implementation).
		@return count of external flavours supported by this export provider
		
	*/
	virtual int32 CountExternalFlavors(void) const;

	/**  For Clip/Drag operations, acquire external flavor by index (not supported by this implementation).

		@param n IN index of external flavour of interest
		@precondition 0 <= n < CountExternalFlavors()
		@return external flavour at given index
		
	*/
	virtual ExternalPMFlavor GetExternalFlavor(int32 n) const;

	/**  For Clip/Drag operations, the format type, if any, 
		that would be used to produce the desired external flavor  (not supported by this implementation).

		@param flavor IN
		@param outFormatName IN
		@return kTrue if the given external flavour can be exported, kFalse otherwise
	*/
	virtual bool16 CanExportThisFlavor(const ExternalPMFlavor& flavor, PMString& outFormatName) const;

	/**  Externalize the given data to a stream (not supported by this implementation).

		@param handler IN 
		@param toWhichFlavor IN 
		@param stream OUT data is written to this stream

		@return kSuccess if could externalize, kFailure otherwise
		@postcondition content has been externalized to stream on success
	*/
	virtual ErrorCode ExportForExternalize(IDataExchangeHandler* handler, 
															const ExternalPMFlavor toWhichFlavor, 
															IPMStream* stream);

	/**  Returns the name (localized string) of the nth file format supported by this export provider.

		@param n IN specifies format index of interest
		@precondition n should lie in 0= < n < CountFormats()
		@return name, translated, of nth file format supported

	*/
	virtual PMString  	GetNthFormatName(int32 n);

	/**  Returns the number of file formats supported by this export provider.
		@return count of formats supported
	*/
	virtual int32   	CountFormats(void);

	/**  Returns the extension of the nth file format supported by this export provider.

		@param formatName IN name of format we're seeking extension for		
		@return extension associated with given format

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
CREATE_PMINTERFACE(CHMLFiltExportProvider, kCHMLFiltExportProviderImpl)


/* CHMLFiltExportProvider Constructor 
*/
CHMLFiltExportProvider::CHMLFiltExportProvider(IPMUnknown *boss)
	: CExportProvider(boss)
{

}

CHMLFiltExportProvider::~CHMLFiltExportProvider()
{

}

/* ExportToFile
*/
void CHMLFiltExportProvider::ExportToFile(const IDFile& sysFile, IDocument* doc, IPMUnknown* targetboss, const PMString& formatName, UIFlags uiFlags)
{
	do 
	{
		InterfacePtr<IPMStream> stream(StreamUtil::CreateFileStreamWriteLazy(sysFile, kOpenOut | kOpenTrunc));
		ASSERT(stream);
		if (!stream)
		{
			break;
		}
		this->ExportToStream(stream, doc, targetboss, formatName, uiFlags);
	} while (kFalse);
}

/* ExportToStream 
*/
void CHMLFiltExportProvider::ExportToStream(IPMStream* stream, IDocument* doc, IPMUnknown* targetboss, const PMString& formatName, UIFlags uiFlags)
{
	ASSERT(formatName == kCHMLFiltExportFormatNameKey);
	CHMLFiltHelper helper;
	
	// send export signal
	IDFile outputFile;
	InterfacePtr<IFileStreamData> fileData(stream, IID_IFILESTREAMDATA);
	if (fileData != nil)
		outputFile = fileData->GetSysFile();

	ErrorCode rc = SendSignal(kBeforeExportSignalResponderService, doc, outputFile, formatName, uiFlags);
	if (rc == kSuccess)
	{
		rc = helper.ExportLayout(stream,doc,targetboss);
		ServiceID signal((rc == kSuccess)? kAfterExportSignalResponderService : kFailedExportSignalResponderService);
		SendSignal(signal, doc, outputFile, formatName, uiFlags);
	}
}
		
/* CanExportToFile 
*/
bool16 CHMLFiltExportProvider::CanExportToFile(void) const
{
	return kTrue;
}
		

/* CanExportThisFormat
*/
bool16 CHMLFiltExportProvider::CanExportThisFormat(IDocument* doc, IPMUnknown* targetboss, const PMString& formatName)
{
	if(formatName == kCHMLFiltExportFormatNameKey) {
		return kTrue;
	}
	return kFalse;
}


/* CanExportForExternalize
*/
bool16 CHMLFiltExportProvider::CanExportForExternalize(void) const
{
	// NOTE: Support for external drag and drop is in ExportForExternalize()
	return kFalse;
}

/* GetInternalFlavor
*/
PMFlavor CHMLFiltExportProvider::GetInternalFlavor(void) const
{
    return kNoExternalFlavor;
}
		

/* CountExternalFlavors
*/
int32 CHMLFiltExportProvider::CountExternalFlavors(void) const
{
	return 0;
}

/* GetExternalFlavor
*/
ExternalPMFlavor CHMLFiltExportProvider::GetExternalFlavor(int32 n) const
{
	ExternalPMFlavor flavor =  kNoExternalFlavor;
	return flavor;
}

/* CanExportThisFlavor
*/
bool16 CHMLFiltExportProvider::CanExportThisFlavor(const ExternalPMFlavor& flavor, PMString& outFormatName) const
{
	return kFalse;
}
			
/* ExportForExternalize
*/
ErrorCode CHMLFiltExportProvider::ExportForExternalize(IDataExchangeHandler* handler, const ExternalPMFlavor toWhichFlavor, IPMStream* stream)
{
	// drag and drop support
	ErrorCode retval = kFailure;
	return retval;
}
			

/* GetNthFormatName
*/
PMString CHMLFiltExportProvider::GetNthFormatName(int32 n)
{
	PMString formatName(kCHMLFiltExportFormatNameKey);
	return formatName;	
}

/* CountFormats
*/
int32 CHMLFiltExportProvider::CountFormats(void)
{
	return 1;
}


/* GetExtensionForFormatName 
*/
PMString CHMLFiltExportProvider::GetExtensionForFormatName(const PMString& formatName)
{
	PMString extension(kCHMLFiltFileExtensionKey);
	return extension;
}


/** GetScriptIDForFormatName
*/
ScriptID CHMLFiltExportProvider::GetScriptIDForFormatName(const PMString& formatName, const ScriptInfo::RequestContext& context)
{
	return kInvalidScriptID ;
}

/* SendSignal 
*/
ErrorCode CHMLFiltExportProvider::SendSignal( const ServiceID& service, IDocument* document, const IDFile& sysFile, const PMString& formatName, UIFlags uiFlags, bool8 bIsStandAlone )
{
	return CExportProvider::SendSignal(service, document, sysFile, formatName, uiFlags, bIsStandAlone );
}

// End, CHMLFiltExportProvider.cpp.


