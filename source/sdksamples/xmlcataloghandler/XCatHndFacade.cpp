//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmlcataloghandler/XCatHndFacade.cpp $
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

// Interface Includes
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "ISaxContentHandler.h"
#include "ISAXParserOptions.h"
#include "ISAXServices.h"
#include "ISession.h"
#include "IWorkspace.h"
#include "IXCatHndEntityMapping.h"
#include "IXCatHndFacade.h"
#include "IXMLImportPreferences.h"
#include "IXMLImportOptionsPool.h"
// General includes
#include "SDKFileHelper.h"
#include "ErrorUtils.h"
#include "UIDList.h"
#include "StreamUtil.h"
#include "StringUtils.h"
#include "FileUtils.h"



/** Facade (utility) interface.

	@ingroup xmlcataloghandler
*/
class XCatHndFacade : public CPMUnknown<IXCatHndFacade>
{
public:

	/** Constructor.
		@param boss IN interface ptr from boss object on which this interface is aggregated.
	*/
	XCatHndFacade(IPMUnknown* boss);

	/**	Destructor
	*/
	virtual ~XCatHndFacade() {}


	/**	@see IXCatHndFacade::ResolvePublicToUri
	 */
	virtual WideString ResolvePublicToUri(const WideString& publicId);

	/**	@see IXCatHndFacade::ResolvePublicToUri
	 */
	virtual ErrorCode AddPublicToUriMapping(const WideString& publicId, const WideString& uri);

	/**	@see IXCatHndFacade::ResolvePublicToUri
	 */
	virtual ErrorCode LoadCatalog(const IDFile& catalogName) const;

	/**	@see IXCatHndFacade::ResolvePublicToUri
	 */
	virtual  IDFile GetDefaultXMLCatalogFile() const;

	
	/**	@see IXCatHndFacade::IsUsingAcquirerFilter
	 */
	virtual bool16 IsUsingAcquirerFilter() const;

	virtual int32 GetXMLBaseCount() const;

	/** @see  IXCatHndFacade::GetNthXMLBase
	*/
	virtual WideString GetNthXMLBase(int32) const;

	/** @see  IXCatHndFacade::AddXMLBase
	*/
	virtual ErrorCode AddXMLBase(const WideString& xmlBase);

	/** @see  IXCatHndFacade::LoadPeerCatalog
	*/
	virtual ErrorCode LoadPeerCatalog(const IDFile& xmlFile);

	virtual  WideString TranslateURIToPlatformSpec(const WideString& uri) const;
	
protected:
	bool16 GetBooleanServiceXMLImportPreference(const ServiceID& whichServiceID, const ClassID& whichClassID, int32 numPref=0) const;
	IXMLImportPreferences* QueryServiceXMLImportPrefs(const ServiceID& whichServiceID, const ClassID& whichClassID) const;
private:
	PMString fLastPathLoaded;
	const static PMString k_platformDelimiter;
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(XCatHndFacade, kXCatHndFacadeImpl)

//JB TODOX This looks like a common define, would it make sense to move it to sdkdef.h?
#ifdef WINDOWS
const PMString XCatHndFacade::k_platformDelimiter("\\");
#endif
#ifdef MACINTOSH
const PMString XCatHndFacade::k_platformDelimiter(":");
#endif

/*	
*/
XCatHndFacade::XCatHndFacade(IPMUnknown* boss) : CPMUnknown<IXCatHndFacade>(boss)	
{
}

/*
*/
ErrorCode 	XCatHndFacade::AddPublicToUriMapping(const WideString& publicId, const WideString& uri)
{
	ErrorCode retval = kFailure;
	do {
		InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kXCatHndChangeEntityMappingCmdBoss));
		ASSERT(cmd);
		if (!cmd) {
			break;
		}
		
		InterfacePtr<IWorkspace> sessionWorkspace(GetExecutionContextSession()->QueryWorkspace());
		ASSERT(sessionWorkspace);
		if (!sessionWorkspace) {
			break;
		}
		InterfacePtr<IXCatHndEntityMapping> existingMapping(sessionWorkspace, UseDefaultIID());
		ASSERT(existingMapping);
		if (!existingMapping) {
			break;
		}
		cmd->SetItemList(UIDList(sessionWorkspace));
		InterfacePtr<IXCatHndEntityMapping> cmdData(cmd, UseDefaultIID());
		ASSERT(cmdData);
		if (!cmdData) {
			break;
		}
		cmdData->Copy(existingMapping);
		cmdData->AddMapping(publicId, uri);

		retval = CmdUtils::ProcessCommand(cmd);
		ASSERT(retval == kSuccess); 

	} while (kFalse);

	return retval;
}

/*
*/
WideString XCatHndFacade::ResolvePublicToUri(const WideString& publicId)
{
	WideString retval;
	do {

		InterfacePtr<IWorkspace> sessionWorkspace(GetExecutionContextSession()->QueryWorkspace());
		ASSERT(sessionWorkspace);
		if (!sessionWorkspace) {
			break;
		}
		InterfacePtr<IXCatHndEntityMapping> srcMapping(sessionWorkspace, UseDefaultIID());
		ASSERT(srcMapping);
		if(!srcMapping) {
			break;
		}
		
		retval = srcMapping->GetUri(publicId);

	} while(kFalse);
	return retval;
}

/*
*/
ErrorCode XCatHndFacade::LoadCatalog(const IDFile& catalogName) const
{
	ErrorCode retval = kFailure;
	do {

		InterfacePtr<IPMStream> readStream(StreamUtil::CreateFileStreamRead(catalogName));
		// Watson 1137554 
		// don't assert in general if we can't find a catalog, this is a benign condition
		// ASSERT(readStream);
		if (!readStream) {
			break;
		}
		
		// Get the SaxServices interface from the parser
		InterfacePtr<IK2ServiceRegistry> serviceRegistry(GetExecutionContextSession(), UseDefaultIID());
		InterfacePtr<IK2ServiceProvider> xmlProvider(serviceRegistry->QueryServiceProviderByClassID(kXMLParserService, kXMLParserServiceBoss));
		InterfacePtr<ISAXServices> saxServices(xmlProvider, UseDefaultIID());
		ASSERT(saxServices);
		if (!saxServices) {
			break;
		}

		// Set up out custom handler
		InterfacePtr<ISAXContentHandler> saxHandler( 
			::CreateObject2<ISAXContentHandler>(kXCatHndSAXContentHandlerServiceBoss) );
		saxHandler->Register(saxServices);
		

		InterfacePtr<ISAXParserOptions> parserOptions(saxServices, UseDefaultIID());
		ASSERT(parserOptions);
		if(!parserOptions) {
			break;
		}
		// These commitments: follow 
		// the existing ImportXMLFileCmd
		parserOptions->SetNamespacesFeature(kTrue);
		parserOptions->SetShowWarningAlert(kTrue);
		
		// Returns 0 if it succeeded....
		bool16 parseFailed = saxServices->ParseStream(readStream, saxHandler);
		if (parseFailed || ErrorUtils::PMGetGlobalErrorCode() != kSuccess)
		{
			// TODOX we have error string service now so prob have cleaner
			// way to do this

			// JB TODOX I am a little confused by this code at first place. 
			// Would using the error string service simplify this code? 
			// We are reporting some sensible error string. Also should 
			// ErrorUtils::PMSetGlobalErrorCode (kSuccess); be moved to the outside 
			// of this if loop before you call ParseStream? You wanted to clear the errors
			// BEFORE you call the ParseStream so that you can report the parsing error. 
			// Is that the intend?

			SDKFileHelper fileHelper(catalogName);
			PMString wsName = fileHelper.GetPath();
			wsName.SetTranslatable(kFalse);
			// We must clear whatever error was there, or else it'll take precedence
			ErrorCode errcode = ErrorUtils::PMGetGlobalErrorCode();
			// hkhalfal: changing error code a couple of lines down
			ErrorUtils::PMSetGlobalErrorCode (kSuccess);
			// There should be 1 param slot in this error string translation
			PMString errorString(kXCatHndInvalidCatalogFileKey, PMString::kTranslateDuringCall);
			::ReplaceStringParameters(&errorString, wsName);
			ErrorUtils::PMSetGlobalErrorCode (errcode, &errorString);
			break;
		}
		retval = kSuccess;
		

	} while(kFalse);
	return retval;
}


/*
*/
IDFile XCatHndFacade::GetDefaultXMLCatalogFile() const
{
	IDFile appDocumentFolder;
	PMString nullFolder;
	// NB This call doesn't create a subfolder for us
	bool16 gotAppFolder = FileUtils::GetAppRoamingDataFolder(&appDocumentFolder, nullFolder);
	ASSERT(gotAppFolder);
	SDKFileHelper appFolder(appDocumentFolder);

	PMString baseName = appFolder.GetPath() + k_platformDelimiter;
	PMString retfile(baseName); 
	retfile += kXCatHndDefaultXMLCatalogFileName;
	SDKFileHelper fileHelper(retfile);
	return fileHelper.GetIDFile();
}

/*
*/
bool16 XCatHndFacade::IsUsingAcquirerFilter() const
{
	return this->GetBooleanServiceXMLImportPreference(kAcquireXMLService, 
														kXCatHndAcquirerFilterServiceBoss);
}

//JB TODOX could we do some refactoring code work between those plug-ins? Do you think it's worth putting it in a helper class?
// I'd like to understand a little bit more on this.
// ipaterso TODOX this and method below are cloned from XDocBookWorkflow,
// can we put in helper
bool16 XCatHndFacade::GetBooleanServiceXMLImportPreference(const ServiceID& whichServiceID, const ClassID& whichClassID, int32 numPref) const
{
	bool16 retval = kFalse;
	do {
		InterfacePtr<IXMLImportPreferences> xmlImportPrefs(this->QueryServiceXMLImportPrefs(whichServiceID, whichClassID));
		ASSERT(xmlImportPrefs);
		if(!xmlImportPrefs) {
			break;
		}
		InterfacePtr<IWorkspace> workspace(GetExecutionContextSession()->QueryWorkspace());
		ASSERT(workspace);
		if(!workspace) {
			break;
		}
		InterfacePtr<IXMLImportOptionsPool> prefsPool(workspace, UseDefaultIID());
		ASSERT(prefsPool);
		XMLImportPreferencesInitializer initializer(xmlImportPrefs, prefsPool);

		retval = xmlImportPrefs->GetNthPrefAsBool(numPref);


	} while(kFalse);
	return retval;
}

/*
*/
IXMLImportPreferences* XCatHndFacade::QueryServiceXMLImportPrefs(const ServiceID& whichServiceID, const ClassID& whichClassID) const
{
	IXMLImportPreferences* retval = nil;
	do {

		InterfacePtr<IK2ServiceRegistry> serviceRegistry(GetExecutionContextSession(), UseDefaultIID());
		ASSERT(serviceRegistry);
		if (!serviceRegistry) {
			break;
		}
		InterfacePtr<IK2ServiceProvider> serviceProvider(
			serviceRegistry->QueryServiceProviderByClassID(whichServiceID, whichClassID));
		ASSERT(serviceProvider);
		if (!serviceProvider) {
			break;
		}
		InterfacePtr<IXMLImportPreferences> xmlImportPrefs(serviceProvider, UseDefaultIID());
		ASSERT(xmlImportPrefs);
		if (!xmlImportPrefs) {
			break;
		}

		retval = xmlImportPrefs.forget();
	} while(kFalse);

	return retval;
}


/*
*/
WideString XCatHndFacade::GetNthXMLBase(int32 n) const
{
	WideString retval;
	do {

		InterfacePtr<IWorkspace> sessionWorkspace(GetExecutionContextSession()->QueryWorkspace());
		ASSERT(sessionWorkspace);
		if (!sessionWorkspace) {
			break;
		}
		InterfacePtr<IXCatHndEntityMapping> srcMapping(sessionWorkspace, UseDefaultIID());
		ASSERT(srcMapping);
		if(!srcMapping) {
			break;
		}
		
		retval = srcMapping->GetNthXMLBase(n);

	} while(kFalse);
	return retval;
}

/*
*/
int32 XCatHndFacade::GetXMLBaseCount() const
{
	int32 retval=0;
	do {

		InterfacePtr<IWorkspace> sessionWorkspace(GetExecutionContextSession()->QueryWorkspace());
		ASSERT(sessionWorkspace);
		if (!sessionWorkspace) {
			break;
		}
		InterfacePtr<IXCatHndEntityMapping> srcMapping(sessionWorkspace, UseDefaultIID());
		ASSERT(srcMapping);
		if(!srcMapping) {
			break;
		}	
		retval = srcMapping->GetXMLBaseCount();

	} while(kFalse);
	return retval;
}

/*
*/
ErrorCode 	XCatHndFacade::AddXMLBase(const WideString& xmlBase)
{
	ErrorCode retval = kFailure;
	do {
		InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kXCatHndChangeEntityMappingCmdBoss));
		ASSERT(cmd);
		if (!cmd) {
			break;
		}
		
		InterfacePtr<IWorkspace> sessionWorkspace(GetExecutionContextSession()->QueryWorkspace());
		ASSERT(sessionWorkspace);
		if (!sessionWorkspace) {
			break;
		}
		InterfacePtr<IXCatHndEntityMapping> existingMapping(sessionWorkspace, UseDefaultIID());
		ASSERT(existingMapping);
		if (!existingMapping) {
			break;
		}
		cmd->SetItemList(UIDList(sessionWorkspace));
		InterfacePtr<IXCatHndEntityMapping> cmdData(cmd, UseDefaultIID());
		ASSERT(cmdData);
		if (!cmdData) {
			break;
		}
		cmdData->Copy(existingMapping);
		cmdData->AddXMLBase(xmlBase);

		retval = CmdUtils::ProcessCommand(cmd);
		ASSERT(retval == kSuccess); 

	} while (kFalse);

	return retval;
}

ErrorCode XCatHndFacade::LoadPeerCatalog(const IDFile& xmlFile)
{
	ErrorCode retvalErrCode = kSuccess;
	SDKFileHelper fileHelper(xmlFile);
	PMString retpath(fileHelper.GetParentFolderAsString());

	retpath += k_platformDelimiter;
	retpath += kXCatHndDefaultXMLCatalogFileName;
	
	SDKFileHelper retFileHelper(retpath);
	if(fLastPathLoaded != retpath) {
		// Don't attempt to reload same catalog we just loaded
		retvalErrCode = this->LoadCatalog(retFileHelper.GetIDFile());
		if(retvalErrCode == kSuccess) {
			fLastPathLoaded = retpath;
		}
	}
	return retvalErrCode;
}


WideString XCatHndFacade::TranslateURIToPlatformSpec(const WideString& uri) const
{
	//PMString retpstr = FileUtils::FileURLToPMString (pstr);
	// Didn't quite work the way I thought: prob needs file:///
	
	// http://www.sgi.com/tech/stl/basic_string.html
	std::basic_string<UTF16TextChar, 
		std::char_traits<UTF16TextChar>, 
			std::allocator<UTF16TextChar> > stduri(
				uri.GrabUTF16Buffer(nil), uri.CharCount());
		

#ifdef MACINTOSH
	// Don't need to do anything on windows
	
	// http://www.sgi.com/tech/stl/replace.html
	std::replace(stduri.begin(), stduri.end(),'/',':');
#endif
	WideString retval(stduri.c_str());
	return retval;
}

// End, XCatHndFacade.cpp.
