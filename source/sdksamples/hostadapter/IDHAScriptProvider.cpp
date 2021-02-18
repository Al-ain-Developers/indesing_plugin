#include "VCPlugInHeaders.h"

// Interface includes:
#include "IScript.h"
#include "IScriptRequestData.h"
#include "IScriptUtils.h"
#include "IMetaDataAccess.h"
#include "IDocument.h"
#include "IPMStream.h"
#include "IAsciiEncodingUtils.h"
#include "IStandAloneDoc.h"
#include "IInCopyStoryList.h"
#include "ITextModel.h"
#include "IItemLockData.h"
#include "IInCopyWorkFlowUtils.h"

// General includes:
//#include "CAlert.h"
#include "CScriptProvider.h"
#include "StreamUtil.h"
#include "LocaleSetting.h"

// Project includes:
#include "IDHAScriptingDefs.h"
#include "IDHAID.h"
#include "IDHAMemoryXferBytes.h"
#include "StringUtils.h"


/** 
	Extends the Document script object to add the property 'xmpString'.
    @ingroup idhostadapter
*/
class IDHAScriptProvider : public CScriptProvider
{
public:
	/** Constructor.
	@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	IDHAScriptProvider(IPMUnknown* boss) : CScriptProvider(boss) {};

	/** Destructor. Does nothing.
	*/
	~IDHAScriptProvider() {}

	/** This method is called if a provider can handle a property.
	@param propID identifies the ID of the property to handle.
	@param data identifies an interface pointer used to extract data.
	@param parent identifies an interface pointer on the script object representing the parent of the application object.
	*/
	virtual ErrorCode AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* parent);

private:
	/** This method delegated to handle the p_XMPString property. 
	@param data identifies an interface pointer used to extract data.
	@param parent identifies an interface pointer on the script object representing the parent of the application object.
	*/
	virtual ErrorCode AccessXMPString(ScriptID propID, IScriptRequestData* data, IScript* script);

	/** This method handles the management of the InDesign logic.
	@param data identifies an interface pointer used to extract data.
	@param parent identifies an interface pointer on the script object representing the parent of the application object.
	*/
	virtual ErrorCode ManageInDesignAccess(IScriptRequestData* data, IScript* script, ScriptID propID);

	/** This method handles the management of the InCopy logic.
	@param data identifies an interface pointer used to extract data.
	@param parent identifies an interface pointer on the script object representing the parent of the application object.
	*/
	virtual ErrorCode ManageInCopyAccess(IScriptRequestData* data, IScript* script, ScriptID propID);

	/** This method handles the retrieval of the XMP metadata.
	@param iMetaDataAccess The MetaData access object.
	@param data identifies an interface pointer used to extract data.
	*/
	virtual ErrorCode HandleGetRequest(InterfacePtr<IMetaDataAccess> iMetaData, IScriptRequestData* data, IScript* script, ScriptID propID);

	/** This method handles the setting of the XMP metadata with the newly passed content.
	@param iMetaDataAccess The MetaData access object.
	@param data identifies an interface pointer used to extract data.
	*/
	virtual ErrorCode HandleSetRequest(InterfacePtr<IMetaDataAccess> iMetaData, IScriptRequestData* data, ScriptID propID);

	/** Serializes the Metadata into an XMP packet
	@param metaData	The MetaData block
	@param utf8String	The string in which to write the xmp metadata
	@param package		If package is kTrue then when the MetaData block is saved to the stream it will be packaged in a MetaData package.
	@param allowInPlaceModification	If kTrue it means it will keep changes made externally to any external property.
	@param expandable	If expandable is kTrue then when the package is written out pad bytes will be included so that external entities can add MetaData properties to the packet.	
	*/
	virtual bool16 SerializeXMP(IMetaDataAccess* metaData, PMString& utf8String, const bool16& package = kFalse, const bool16& allowInPlaceModification = kFalse, const bool16& expandable = kFalse);

	virtual IMetaDataAccess* QueryCoreMetaData(IScriptRequestData* data, IScript* script);
	virtual IMetaDataAccess* QueryCoreMetaData(ITextModel* textModel);
};


/* CREATE_PMINTERFACE
Binds the C++ implementation class onto its ImplementationID 
making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(IDHAScriptProvider, kIDHAScriptProviderImpl)


/* AccessProperty
*/
ErrorCode IDHAScriptProvider::AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* parent)
{
	ErrorCode status = kFailure;

	switch (propID.Get())
	{
	case p_XMPString:
		status = AccessXMPString(propID, data, parent);
		break;

    default:
		status = CScriptProvider::AccessProperty(propID, data, parent);
    }

    return status;
}


/* AccessXMPString
*/
ErrorCode IDHAScriptProvider::AccessXMPString(
	ScriptID propID, IScriptRequestData* data, IScript* script)
{
	ErrorCode status = kFailure;
	bool16 isInCopy = LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS);

	if (isInCopy)
	{
		status = ManageInCopyAccess(data, script, propID);
	}
	else
	{
		status = ManageInDesignAccess(data, script, propID);

	}
	return status;
}

//----------------------------------------------------------------------------------------
// IDHAScriptProvider::ManageInDesignAccess
//----------------------------------------------------------------------------------------
ErrorCode IDHAScriptProvider::ManageInDesignAccess(IScriptRequestData* data, IScript* script, ScriptID propID)
{
	ErrorCode status = kFailure;

	InterfacePtr<IDocument> document(Utils<IScriptUtils>()->QueryDocumentFromScript(script, data->GetRequestContext()));
	if (document)
	{
		// retrieve the MetaData access from the Document
		InterfacePtr<IMetaDataAccess> iMetaDataAccess(document, UseDefaultIID());
		
		if (iMetaDataAccess)
		{
			// determine Get or Set request
			if (data->IsPropertyGet())
			{
				InterfacePtr<IMetaDataAccess> iMetaData(nil);
				iMetaData.reset(iMetaDataAccess.forget());
				status = HandleGetRequest(iMetaData, data, script, propID);

			}
			else if (data->IsPropertyPut())
			{
				status = HandleSetRequest(iMetaDataAccess, data, propID);
			}

		}
	}
	return status;
}

//----------------------------------------------------------------------------------------
// IDHAScriptProvider::ManageInCopyAccess
//----------------------------------------------------------------------------------------
ErrorCode IDHAScriptProvider::ManageInCopyAccess(IScriptRequestData* data, IScript* script, ScriptID propID)
{
	ErrorCode status = kFailure;

	InterfacePtr<IMetaDataAccess> iMetaDataAccess(QueryCoreMetaData(data, script), UseDefaultIID());

	if (iMetaDataAccess)
	{
		// determine Get or Set request
		if (data->IsPropertyGet())
		{
			
			InterfacePtr<IMetaDataAccess> iMetaData(nil);
			iMetaData.reset(iMetaDataAccess);
			status = HandleGetRequest(iMetaData, data, script, propID);

		}
		else if (data->IsPropertyPut())
		{
			status = HandleSetRequest(iMetaDataAccess, data, propID);
			iMetaDataAccess->Release();
		}
	}
	return status;
}

//----------------------------------------------------------------------------------------
// IDHAScriptProvider::ProcessGetRequest
//----------------------------------------------------------------------------------------
ErrorCode IDHAScriptProvider::HandleGetRequest(InterfacePtr<IMetaDataAccess> iMetaData, IScriptRequestData* data, IScript* script, ScriptID propID)
{
	ErrorCode status = kFailure;
	
	PMString utf8String;
	const int32 kBufferSize = 512;

	status = SerializeXMP(iMetaData, utf8String, kTrue, kFalse, kFalse); // read the xmp and append to the utf8String PMSting.

	// construct response
	ScriptData scriptData;

	scriptData.SetPMString(utf8String);
	utf8String.SetTranslatable(kFalse);
	data->AppendReturnData( script, propID, scriptData ) ;
	status = kSuccess;
	
	return status;
}

//----------------------------------------------------------------------------------------
// IDHAScriptProvider::ProcessSetRequest
//----------------------------------------------------------------------------------------
ErrorCode IDHAScriptProvider::HandleSetRequest(InterfacePtr<IMetaDataAccess> iMetaDataAccess, IScriptRequestData* data, ScriptID propID)
{
	ErrorCode status = kFailure;

	const int32 kBufferSize = 512;

	// attempt to write the data to the XMP packet
	ScriptData scriptData;
	PMString packet;

	if (data->HasRequestData(propID))
	{
		status = data->ExtractRequestData(propID, scriptData); // extract the passed data from the request
		if (status != kSuccess) return status;

		status = scriptData.GetPMString(packet); // extract the xmp data packet
		if (status != kSuccess) return status;

		std::string utf8Packet; // UTF8 encode the passed xmp data
		StringUtils::ConvertWideStringToUTF8(WideString (packet), utf8Packet);
		PMString reserializedData; // store the updated XMP contents
		// populate a stream with the passed XMP metadata
		InterfacePtr<IPMStream> readStream(StreamUtil::CreatePointerStreamRead(const_cast<char*>(utf8Packet.c_str()), utf8Packet.length())); 

		iMetaDataAccess->LoadFromStream(readStream); // update the document with the new XMP metadata
		if (SerializeXMP(iMetaDataAccess, reserializedData))
		{
			// successfully retrieved the updated contents
			iMetaDataAccess->NoteMetaDataChanged(); // notify that metadata has changed
			status = kSuccess;
		}
	}

	return status;
}
//----------------------------------------------------------------------------------------
// IDHAScriptProvider::SerializeXMP
//----------------------------------------------------------------------------------------
bool16 IDHAScriptProvider::SerializeXMP(IMetaDataAccess* metaData, PMString& utf8String, const bool16& package, const bool16& allowInPlaceModification, const bool16& expandable)
{
	const int32 kBufferSize = 512;
	
	IDHAMemoryXferBytes xferBytes;
	InterfacePtr<IPMStream> writeStream(StreamUtil::CreateMemoryStreamWrite(&xferBytes));
	if (metaData->SaveToStream(writeStream, package, allowInPlaceModification, expandable))
	{
		xferBytes.Seek(0, kSeekFromStart);
		InterfacePtr<IPMStream> readStream(StreamUtil::CreateMemoryStreamRead(&xferBytes));

		char buffer[kBufferSize];
		int32 bytesRead = readStream->XferByte((uchar*) buffer, kBufferSize);
		while (bytesRead > 0)
		{					
			utf8String.Append(buffer, bytesRead);
			bytesRead = readStream->XferByte((uchar*) buffer, kBufferSize);
		}
		return kTrue;
	}
	return kFalse;
}

//----------------------------------------------------------------------------------------
// IDHAScriptProvider::QueryCoreMetaData
//----------------------------------------------------------------------------------------
IMetaDataAccess* IDHAScriptProvider::QueryCoreMetaData(IScriptRequestData* data, IScript* script)
{
	//For InCopy 2.0, we have two MetaDataPreferences objects--on the Document object and on the Story object
	//If you have a stand-alone InCopy document, the Document object's MetaDataPreferences object 
	// is the Story's MetaDataPreferences object, which can be edited.
	//
	//If you have an InDesign document, you can access the Document object's MetaDataPreferences object and 
	// each Story's MetaDataPreferences object, but you can only edit a story's MetaDataPreferences object.

	//First check whether we're dealing with the Document object's MetaDataPrferences object
	InterfacePtr<IMetaDataAccess> iMetaDataAccess(nil);

	InterfacePtr<IDocument> document(Utils<IScriptUtils>()->QueryDocumentFromScript(script, data->GetRequestContext()));
	if (document)
	{
		InterfacePtr<IStandAloneDoc> standAlone(document, UseDefaultIID()) ;
		if (standAlone && standAlone->IsStandAloneDoc())
		{
			//If we're a stand-along InCopy document, we actually want to return our story's MetaDataPrefs object
			InterfacePtr<IInCopyStoryList> storyList(document, UseDefaultIID());
			ASSERT( storyList != nil && storyList->GetStoryCount() == 1 ) ;
			InterfacePtr<ITextModel> textModel( storyList->GetNthStoryRef(0), UseDefaultIID() ) ;
			// Traverse through the Document until the ITextModel is available
			iMetaDataAccess.reset(QueryCoreMetaData(textModel));
		}
		else
		{
			InterfacePtr<IMetaDataAccess> iMDA(document, UseDefaultIID());
			iMetaDataAccess.reset(iMDA.forget());
		}
	}

	InterfacePtr<ITextModel> textModel((ITextModel*) script->QueryParent( IID_ITEXTMODEL, data->GetRequestContext())) ;
	if (textModel)
		iMetaDataAccess.reset(QueryCoreMetaData(textModel));

	return iMetaDataAccess.forget();
}
//----------------------------------------------------------------------------------------
// IDHAScriptProvider::QueryCoreMetaData
//----------------------------------------------------------------------------------------
IMetaDataAccess* IDHAScriptProvider::QueryCoreMetaData(ITextModel* textModel)
{
	if (textModel)
	{
		// Retrieve the metadata from the InCopy's ITextModel
		InterfacePtr<IItemLockData> textLock(textModel, IID_IITEMLOCKDATA);
		bool16 createIfNeeded = (textLock && !textLock->GetInsertLock());
		Utils<IInCopyWorkFlowUtils> inCopyWorkFlowUtils;
		InterfacePtr<IPMUnknown> iUnknown(inCopyWorkFlowUtils->QueryTextMetaDataBoss( textModel, kTrue));
		InterfacePtr<IMetaDataAccess> iMetaDataAccess(iUnknown, UseDefaultIID());
		return iMetaDataAccess.forget();
	}
	return nil;
}

//  Code generated by DollyXs code generator
