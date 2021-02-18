//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xdocbookworkflow/XDocBkFacade.cpp $
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
#include "IBoolData.h"
#include "IClassIDData.h"
#include "IDocument.h"
#include "IExportProvider.h"
#include "IIDXMLElement.h"
#include "IImportXMLData.h"
#include "IIntData.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "IPMUnknownData.h"
#include "IWorkspace.h"
#include "IXDocBkFacade.h"
#include "IXDocBkOptions.h"
#include "IXMLAccess.h"
#include "IXMLExportHandlerData.h"
#include "IXMLExportOptions.h"
#include "IXMLHandler.h"
#include "IXMLImportOptions.h"
#include "IXMLImportOptionsPool.h"
#include "IXMLImportPreferences.h"
#include "IXMLStreamUtils.h"
#include "IXMLUtils.h"

// Impl includes
#include "LocaleSetting.h"
#include "ErrorUtils.h"
#include "UIDList.h"
#include "XMLID.h"
#include "XMLReference.h"
#include "XMLParserID.h"
#include "SDKFileHelper.h"
#include "CAlert.h"	 // test only, maybe better use TRACE
// project
#include "XDocBkConstants.h"




/** XDocBkFacade is an implementation of the command facade interface IXDocBkFacade.
	@ingroup xdocbookworkflow
*/
class XDocBkFacade : public CPMUnknown<IXDocBkFacade>
{
public:

	/** Constructor.
		@param boss IN interface ptr from boss object on which this interface is aggregated.
	*/
	XDocBkFacade(IPMUnknown* boss);

	/**	Destructor
	*/
	virtual ~XDocBkFacade() {}

	/** @see IXDocBkFacade::SetOptions
		@return kSuccess on success, other ErrorCode otherwise
	*/
	virtual ErrorCode SetOptions(const K2Vector<WideString>& optionsVec);

	/** @see IXDocBkFacade::AreOptionsSet
		@return kTrue if set, kFalse otherwise
	*/
	virtual bool16 AreOptionsSet();


	/** @see IXDocBkFacade::ResizeInlines
		@return kSuccess on success, other ErrorCode otherwise
	*/
	virtual ErrorCode ResizeInlines(const UIDRef& documentUIDRef);


	/** @see IXDocBkFacade::ImportXMLFile
		@return kSuccess on success, other ErrorCode otherwise
	*/
	virtual ErrorCode ImportXMLFile(const IDFile& xmlFile, const UIDRef& destDocumentUIDRef, const PMString& stylesheetPath);

	/** @see IXDocBkFacade::ExportXMLFile
		@return kSuccess on success, other ErrorCode otherwise
	*/
	virtual ErrorCode ExportXMLFile(const IDFile& sysFile, IDocument* doc, IPMUnknown* targetboss, const PMString& formatName, UIFlags uiFlags);


	/** @see IXDocBkFacade::GetTemplatePath
		@return template path, empty if not set up
	*/
	virtual PMString GetTemplatePath();

	/** @see IXDocBkFacade::GetDefaultTemplateFromFolder
		@return template path
	*/
	virtual PMString GetDefaultTemplateFromFolder(const IDFile& importingXMLFile);

	/** @see IXDocBkFacade::GetStylesheetPath
		@return stylesheet path, empty if not set up
	*/
	virtual PMString GetStylesheetPath();

	/** @see IXDocBkFacade::SetUseXMLTransformer
		@return kSuccess on success, other ErrorCode otherwise
	*/
	virtual ErrorCode SetUseXMLTransformer(bool16 newState);

	/** @see IXDocBkFacade::SetUsePostImportIterator
		@return kSuccess on success, other ErrorCode otherwise
	*/
	virtual ErrorCode SetUsePostImportIterator(bool16 newState);

	/** @see IXDocBkFacade::SetUseCALSContentHandler
		@return kSuccess on success, other ErrorCode otherwise
	*/
	virtual ErrorCode SetUseCALSContentHandler(bool16 newState);

	/** @see IXDocBkFacade::IsUsingXMLTransformer

		@return kTrue if feature enabled, kFalse if not
	*/
	virtual bool16 IsUsingXMLTransformer();

	/** @see IXDocBkFacade::IsUsingPostImportIterator
		@return kTrue if feature enabled, kFalse if not
	*/
	virtual bool16 IsUsingPostImportIterator();

	/** @see IXDocBkFacade::IsUsingCALSContentHandler
		@return kTrue if feature enabled, kFalse if not
	*/
	virtual bool16 IsUsingCALSContentHandler();

	/** @see IXDocBkFacade::SetDeleteNamespacedAttrs
		@return kSuccess on success, other ErrorCode otherwise
	*/
	virtual ErrorCode SetDeleteNamespacedAttrs(bool16 newState);

	/** @see IXDocBkFacade::IsDeleteNamespacedAttrs
		@return kTrue if feature enabled, kFalse if not
	*/
	virtual bool16 IsDeleteNamespacedAttrs();

	/** @see IXDocBkFacade::SetDeleteInboundStrucTableElements
		@return kSuccess on success, other ErrorCode otherwise

	*/
	virtual ErrorCode SetDeleteInboundStrucTableElements(bool16 newState);

	/** Determine if option to delete aid:xxx attrs is turned on
		@return kTrue if turned on, kFalse if turned off
	*/
	virtual bool16 IsDeleteInboundStrucTableElements();

	/** @see IXDocBkFacade::IsTaggingTable
		@return kTrue if feature enabled, kFalse if not
	*/
	virtual bool16 IsTaggingTable();


	/** @see IXDocBkFacade::SetTaggingTable
		@return kSuccess on success, other ErrorCode otherwise

	*/
	virtual ErrorCode SetTaggingTable(bool16 newState);

	/**
	*/
	virtual bool16 IsSuppliedXSLOverridingPI();

	/**
	*/
	virtual ErrorCode SetSuppliedXSLOverridingPI(bool16 newState);


	/** @see IXDocBkFacade::UnitTestFacade

	*/
	virtual void UnitTestFacade();

	/** @see IXDocBkFacade::AddPathSeparator

	*/
	virtual PMString AddPathSeparator(const PMString& path);

protected:
	bool16 GetBooleanServiceXMLImportPreference(const ServiceID& whichServiceID, const ClassID& whichClassID, int32 numPref);
	ErrorCode SetBooleanServiceXMLImportPreference(const ServiceID& whichServiceID, const ClassID& whichClassID,
												int32 whichPref,
												bool16 newValue);
	IXMLImportPreferences* QueryServiceXMLImportPrefs(const ServiceID& whichServiceID, const ClassID& whichClassID);
	bool16 GetBooleanXMLImportOptionFromPool(const WideString& key);
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(XDocBkFacade, kXDocBkFacadeImpl)

/*	Constructor
*/
XDocBkFacade::XDocBkFacade(IPMUnknown* boss) : CPMUnknown<IXDocBkFacade>(boss)
{
}

/* SetOptions
*/
ErrorCode XDocBkFacade::SetOptions(const K2Vector<WideString>& optionsVec)
{
	ErrorCode retval = kFailure;
	do
	{
		InterfacePtr<IWorkspace> sessionWorkspace(GetExecutionContextSession()->QueryWorkspace());
		ASSERT(sessionWorkspace);
		if (!sessionWorkspace) {
			break;
		}

		InterfacePtr<ICommand> modOptionsCmd(CmdUtils::CreateCommand(kXDocBkChangeOptionsCmdBoss));
		ASSERT(modOptionsCmd);
		if (!modOptionsCmd) {
			break;
		}
		modOptionsCmd->SetItemList(UIDList(sessionWorkspace));
		InterfacePtr<IXDocBkOptions> cmdData(modOptionsCmd, UseDefaultIID());
		ASSERT(cmdData);
		if (!cmdData) {
			break;
		}
		K2Vector<WideString>::const_iterator iter;
		for (iter = optionsVec.begin(); iter != optionsVec.end(); ++iter) {
			// http://www.sgi.com/tech/stl/distance.html
			cmdData->AddOption(*iter, std::distance(optionsVec.begin(),iter));	// template path etc
		}


		retval = CmdUtils::ProcessCommand(modOptionsCmd);
		ASSERT(retval == kSuccess);

	} while (kFalse);

	return retval;
}


/* ImportXMLFile
*/
ErrorCode XDocBkFacade::ImportXMLFile(const IDFile& xmlFile,
									  const UIDRef& destDocumentUIDRef,
									  const PMString& stylesheetPath)
{
	ErrorCode retval = kFailure;
	do
	{
		InterfacePtr<IDocument> iDocument(destDocumentUIDRef, UseDefaultIID());
		ASSERT(iDocument);
		if (!iDocument) {
			break;
		}

		InterfacePtr<ICommand> importCmd(CmdUtils::CreateCommand(kImportXMLFileCmdBoss));
		ASSERT(importCmd);
		if (!importCmd) {
			break;
		}

		// Make the import target the right element

		InterfacePtr<IIDXMLElement> idRootElem(Utils<IXMLUtils>()->QueryRootElement(iDocument));
		ASSERT(idRootElem);
		if (!idRootElem) {
			break;
		}
		// Verify the context we're importing into
		PMString tagString = idRootElem->GetTagString();
		bool16 correctContext = tagString == XDocBkConstants::k_ARTICLE_TAG;
		ASSERT(correctContext);
		if (!correctContext) {
			break;
		}

		XMLReference xmlRootRef = idRootElem->GetXMLReference();

		// set up the import data
		InterfacePtr<IImportXMLData> importData((IImportXMLData*)::CreateObject(kImportXMLDataBoss, IID_IIMPORTXMLDATA));
		ASSERT(importData);
		if (!importData) {
			break;
		}
		importData->Set(destDocumentUIDRef.GetDataBase(), xmlFile, xmlRootRef, kSuppressUI);

		// get the document's import options
		InterfacePtr<IXMLImportOptions> docOptions( iDocument->GetDocWorkSpace(), UseDefaultIID() );
		// set the import options
		InterfacePtr<IXMLImportOptions> importXMLOptions(importData, UseDefaultIID());
		if (!importXMLOptions) {
			break;
		}
		importXMLOptions->Copy(docOptions);

		InterfacePtr<IPMUnknownData> iPMUnknownData(importCmd, UseDefaultIID());
		iPMUnknownData->SetPMUnknown(importData);

		retval = CmdUtils::ProcessCommand(importCmd);
		//ASSERT(retval == kSuccess);
	} while (kFalse);

	return retval;
}

/* ResizeInlines
*/
ErrorCode XDocBkFacade::ResizeInlines(const UIDRef& docUIDRef)
{
	ErrorCode retval = kFailure;
	do
	{
		InterfacePtr<IDocument> iDocument(docUIDRef, UseDefaultIID());
		ASSERT(iDocument);
		if (!iDocument) {
			break;
		}


		InterfacePtr<ICommand> sizeInlinesCmd(CmdUtils::CreateCommand(kXDocBkImageSizerCmdBoss));
		ASSERT(sizeInlinesCmd);
		if (!sizeInlinesCmd) {
			break;
		}
		sizeInlinesCmd->SetItemList(UIDList(iDocument));
		retval = CmdUtils::ProcessCommand(sizeInlinesCmd);
		ASSERT(retval==kSuccess);

	} while (kFalse);

	return retval;
}


/* GetTemplatePath
*/
PMString XDocBkFacade::GetTemplatePath()
{
	PMString retval="";
	do
	{
		InterfacePtr<IWorkspace> sessionWorkspace(GetExecutionContextSession()->QueryWorkspace());
		ASSERT(sessionWorkspace);
		if (!sessionWorkspace) {
			break;
		}
		InterfacePtr<IXDocBkOptions> options(sessionWorkspace, UseDefaultIID());
		ASSERT(options);
		if (!options) {
			break;
		}
		retval = options->GetNthOption(cXDocBkTemplatePathIndex);
	} while (kFalse);
	return retval;
}

/* GetDefaultTemplateFromFolder
*/
PMString XDocBkFacade::GetDefaultTemplateFromFolder(const IDFile& srcFile)
{
	PMString retval="";
	do
	{
		SDKFileHelper importSourceFileHelper(srcFile);
		PMString currFolder(importSourceFileHelper.GetParentFolderAsString());
		currFolder = Utils<IXDocBkFacade>()->AddPathSeparator(currFolder);
		PMString defaultFilename("template.indt");
		PMString templatePath = currFolder + defaultFilename;
		SDKFileHelper testFileHelper(templatePath);
		if(testFileHelper.IsExisting()) {
			retval = testFileHelper.GetPath();
		}
	} while (kFalse);
	return retval;
}
/*
*/
PMString XDocBkFacade::GetStylesheetPath()
{
	PMString retval="";
	do
	{
		InterfacePtr<IWorkspace> sessionWorkspace(GetExecutionContextSession()->QueryWorkspace());
		ASSERT(sessionWorkspace);
		if (!sessionWorkspace) {
			break;
		}
		InterfacePtr<IXDocBkOptions> options(sessionWorkspace, UseDefaultIID());
		ASSERT(options);
		if (!options) {
			break;
		}
		retval = options->GetNthOption(cXDocBkStylesheetPathIndex);
	} while (kFalse);
	return retval;
}
/*
*/
ErrorCode XDocBkFacade::ExportXMLFile(const IDFile& targetFile, IDocument* document, IPMUnknown* targetBoss, const PMString& formatName, UIFlags uiFlags)
{

	ErrorCode err = kFailure;
	do {

		// +Preconditions
		ASSERT(document);
		if(!document) {
			break;
		}

		InterfacePtr<IIDXMLElement> element(
			Utils<IXMLUtils>()->QueryDocElement(document));
		ASSERT(element);
		if(!element) {
			break;
		}
		// -preconditions

		// Locate XML parser service to get IXMLAccess (visitor pattern).
		InterfacePtr<IK2ServiceRegistry> serviceRegistry(GetExecutionContextSession(), UseDefaultIID());
		ASSERT(serviceRegistry);
		InterfacePtr<IK2ServiceProvider> xmlParserServiceProvider
			(serviceRegistry->QueryServiceProviderByClassID(kXMLParserService,
					kXMLParserServiceBoss));
		ASSERT(xmlParserServiceProvider);
		if(!xmlParserServiceProvider) {
			break;
		}
		InterfacePtr<IXMLAccess> access(xmlParserServiceProvider, UseDefaultIID());
		ASSERT(access);
		if(!access) {
			break;
		}
		// Create instance of class with IXMLHandler interface
		InterfacePtr<IXMLHandler> xmlExportHandler(
			CreateObject2<IXMLHandler>(kXMLExportHandlerBoss));
		ASSERT(xmlExportHandler);
		if(!xmlExportHandler) {
			break;
		}

		InterfacePtr<IXMLExportHandlerData> handlerData(xmlExportHandler, UseDefaultIID());
		ASSERT(handlerData);
		if(!handlerData) {
			break;
		}
		// Determine current setting of encoding
		InterfacePtr<IXMLExportOptions> xmlExportOptions(document->GetDocWorkSpace(), UseDefaultIID());
		ASSERT(xmlExportOptions);
		if(!xmlExportOptions) {
			break;
		}
		// Must have the stream ... although we pass a IDFile to the method,
		// we need to set up the stream. This is something to do with image conversion.
		InterfacePtr<IXMLOutStream> xmlStream(
			Utils<IXMLStreamUtils>()->CreateXMLOutFileStream(targetFile,
			xmlExportOptions->GetEncodingType()));
		// Use the current encoding type, e.g. UTF16, UTF8 or ShiftJIS

		handlerData->SetStream(xmlStream);
		err = Utils<IXMLUtils>()->ExportElement(element,
			kTrue, // = do export DTD
			access,
			xmlExportHandler,
			targetFile,
			document,
			formatName,
			uiFlags);
		xmlStream->Close();
		ASSERT(err == kSuccess);

	} while(kFalse);
	return err;
}



/*
*/
bool16 XDocBkFacade::AreOptionsSet()
{
	bool16 templatePathSet = !(this->GetTemplatePath().empty());

	bool16 isInCopyProductFS = LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS);

	if (isInCopyProductFS)
	{
		// We aren't going to import into an InDesign template from within
		// InCopy right now.
		return kTrue;
	}
	return templatePathSet;
}

/*
*/
ErrorCode XDocBkFacade::SetUseXMLTransformer(bool16 newState)
{
	return this->SetBooleanServiceXMLImportPreference(kXMLImporterTransformerService, kXDocBkXMLTransformerBoss,0, newState);
}


ErrorCode XDocBkFacade::SetSuppliedXSLOverridingPI(bool16 newState)
{
	return this->SetBooleanServiceXMLImportPreference(kXMLImporterTransformerService, kXDocBkXMLTransformerBoss,1, newState);
}


/*
*/
ErrorCode XDocBkFacade::SetUseCALSContentHandler(bool16 newState)
{
	return this->SetBooleanServiceXMLImportPreference(kXMLContentHandlerService, kXDocBkCALSContentHandlerBoss,0, newState);
}


/*
*/
ErrorCode XDocBkFacade::SetDeleteNamespacedAttrs(bool16 newState)
{
	return this->SetBooleanServiceXMLImportPreference(kXMLPostImportIterationService, kXMLImporterPostImportMappingBoss,0, newState);
}


/*
*/
ErrorCode XDocBkFacade::SetUsePostImportIterator(bool16 newState)
{
	return this->SetBooleanServiceXMLImportPreference(kXMLPostImportIterationService, kXDocBkXMLPostImportIterationBoss,0, newState);
}

/*
*/
ErrorCode XDocBkFacade::SetDeleteInboundStrucTableElements(bool16 newState)
{
	return this->SetBooleanServiceXMLImportPreference(kXMLPostImportIterationService, kXDocBkXMLPostImportIterationBoss,1, newState);
}

/*
*/
ErrorCode XDocBkFacade::SetTaggingTable(bool16 newState)
{
	return this->SetBooleanServiceXMLImportPreference(kXMLPostImportIterationService, kXDocBkXMLPostImportIterationBoss,2, newState);
}

/*
*/
bool16 XDocBkFacade::IsDeleteNamespacedAttrs()
{
		return this->GetBooleanServiceXMLImportPreference(kXMLPostImportIterationService, kXMLImporterPostImportMappingBoss,0);
}

/*
*/
bool16 XDocBkFacade::IsUsingXMLTransformer()
{
	return this->GetBooleanServiceXMLImportPreference(kXMLImporterTransformerService, kXDocBkXMLTransformerBoss,0);
}

/*
*/
bool16 XDocBkFacade::IsSuppliedXSLOverridingPI()
{
	return this->GetBooleanServiceXMLImportPreference(kXMLImporterTransformerService, kXDocBkXMLTransformerBoss,1);
}

/*
*/
bool16 XDocBkFacade::IsDeleteInboundStrucTableElements()
{
	return this->GetBooleanServiceXMLImportPreference(kXMLPostImportIterationService, kXDocBkXMLPostImportIterationBoss,1);

}

/*
*/
bool16 XDocBkFacade::IsTaggingTable()
{
	return this->GetBooleanServiceXMLImportPreference(kXMLPostImportIterationService, kXDocBkXMLPostImportIterationBoss,2);

}

/*
*/
bool16 XDocBkFacade::IsUsingPostImportIterator()
{
	return this->GetBooleanServiceXMLImportPreference(kXMLPostImportIterationService, kXDocBkXMLPostImportIterationBoss,0);
}

/*
*/
bool16 XDocBkFacade::IsUsingCALSContentHandler()
{
	return this->GetBooleanServiceXMLImportPreference(kXMLContentHandlerService, kXDocBkCALSContentHandlerBoss,0);
}

/*
*/
bool16 XDocBkFacade::GetBooleanXMLImportOptionFromPool(const WideString& key)
{
	bool16 retval = kFalse;
	do {

		InterfacePtr<IWorkspace> sessionWorkspace(GetExecutionContextSession()->QueryWorkspace());
		ASSERT(sessionWorkspace);
		if (sessionWorkspace == nil) {
			break;
		}
		InterfacePtr<IXMLImportOptionsPool> pool(sessionWorkspace, UseDefaultIID());
		ASSERT(pool);
		if(!pool) {
			break;
		}
		bool16 succ = pool->GetValue(key,retval);
		//ASSERT(succ==kTrue);
		// This can fail if the value's not already in the pool,
		// so 'false' is good enough if its not ever been set
	} while(kFalse);
	return retval;
}


/*
*/
ErrorCode XDocBkFacade::SetBooleanServiceXMLImportPreference(
	const ServiceID& whichServiceID,
	const ClassID& whichClassID,
	int32 whichPref,
	bool16 newValue)
{
	ErrorCode err = kFailure;
	do {
		InterfacePtr<IWorkspace> sessionWorkspace(GetExecutionContextSession()->QueryWorkspace());
		ASSERT(sessionWorkspace);
		if (sessionWorkspace == nil) {
			break;
		}

		InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kXDocBkChangeServiceXMLImportPrefsCmdBoss));
		ASSERT(cmd);
		if(!cmd) {
			break;
		}
		cmd->SetItemList(UIDList(sessionWorkspace));
		// Because we use the same cmd to change prefs for the different services,
		// be sure that we maintain a different creator ID so that the command mgr
		// knows that these are "different" pieces of work.
		// Commands are buffered by the selectable dialog, similar to previewable dialog
		cmd->SetCreatorID(whichServiceID.Get() + whichClassID.Get() + whichPref);
		// Since a service may have more than one pref, allow each to be processed
		// Also, since the ClassID's are closely spaced, space these creatorIDs by
		// bringing the serviceID into the equation.
		// In general, if you have lots of cmds being processed in a single previewable/ selectable
		// dialog, you'd want a smarter method to guarantee unique creatorID than this
		InterfacePtr<IIntData> whichPrefIntData(cmd, UseDefaultIID());
		InterfacePtr<IBoolData> newValBoolData(cmd, UseDefaultIID());
		InterfacePtr<IIntData> whichServiceIntData(cmd, IID_IXDOCBKSERVICEIDINTDATA);
		InterfacePtr<IClassIDData> whichClassIDData(cmd, UseDefaultIID());
		bool16 canProceed = (whichPrefIntData && newValBoolData && whichServiceIntData && whichClassIDData);
		ASSERT(canProceed);
		if(!canProceed) {
			break;
		}
		whichPrefIntData->Set(whichPref);
		newValBoolData->Set(newValue);
		whichServiceIntData->Set(whichServiceID.Get());
		whichClassIDData->Set(whichClassID);
		err = CmdUtils::ProcessCommand(cmd);
		ASSERT(err == kSuccess);
	} while(kFalse);
	return err;
}

/*
*/
bool16 XDocBkFacade::GetBooleanServiceXMLImportPreference(const ServiceID& whichServiceID, const ClassID& whichClassID, int32 numPref)
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
IXMLImportPreferences* XDocBkFacade::QueryServiceXMLImportPrefs(const ServiceID& whichServiceID, const ClassID& whichClassID)
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
PMString XDocBkFacade::AddPathSeparator(const PMString& path)
{
	PMString retval(path);
#ifdef MACINTOSH
	retval.Append(kTextChar_Colon);
#else
	retval.Append(kTextChar_ReverseSolidus);
#endif
	return retval;
}


/*
*/
void XDocBkFacade::UnitTestFacade()
{
	int32 successes=0;
	int32 failures=0;
	do {
		bool16 a = this->IsDeleteInboundStrucTableElements();
		ErrorCode err = this->SetDeleteInboundStrucTableElements(!a);
		ASSERT(err == kSuccess);
		bool16 b = this->IsDeleteInboundStrucTableElements();
		bool16 predicate = (b == (!a));
		ASSERT(predicate);
		if(predicate) { successes++; } else { failures++;}
		// restore starting state
		err = this->SetDeleteInboundStrucTableElements(a);
		ASSERT(err == kSuccess);

		bool16 c = this->IsDeleteNamespacedAttrs();
		err  = this->SetDeleteNamespacedAttrs(!c);
		ASSERT(err == kSuccess);
		bool16 d = this->IsDeleteNamespacedAttrs();
		predicate=(d == (!c));
		ASSERT(predicate);
		if(predicate) { successes++; } else { failures++;}
		// restore starting state
		err  = this->SetDeleteNamespacedAttrs(c);
		ASSERT(err == kSuccess);

		bool16 e = this->IsTaggingTable();
		err = this->SetTaggingTable(!e);
		ASSERT(err == kSuccess);
		bool16 f = this->IsTaggingTable();
		predicate=(f == (!e));
		ASSERT(predicate);
		if(predicate) { successes++; } else { failures++;}
		// restore starting state
		err = this->SetTaggingTable(e);
		ASSERT(err == kSuccess);

		bool16 g = this->IsUsingCALSContentHandler();
		err = this->SetUseCALSContentHandler(!g);
		ASSERT(err == kSuccess);
		bool16 h = this->IsUsingCALSContentHandler();
		predicate=(h == (!g));
		ASSERT(predicate);
		if(predicate) { successes++; } else { failures++;}
		// restore starting state
		err = this->SetUseCALSContentHandler(g);
		ASSERT(err == kSuccess);

		bool16 i = this->IsUsingPostImportIterator();
		err = this->SetUsePostImportIterator(!i);
		ASSERT(err == kSuccess);
		bool16 j = this->IsUsingPostImportIterator();
		predicate=(j == (!i));
		ASSERT(predicate);
		if(predicate) { successes++; } else { failures++;}
		// restore starting state
		err = this->SetUsePostImportIterator(i);
		ASSERT(err == kSuccess);


		bool16 k = this->IsUsingXMLTransformer();
		err = this->SetUseXMLTransformer(!k);
		ASSERT(err == kSuccess);
		bool16 l = this->IsUsingXMLTransformer();
		predicate=(l == (!k));
		ASSERT(predicate);
		if(predicate) { successes++; } else { failures++;}
		// restore starting state
		this->SetUseXMLTransformer(k);
		ASSERT(err == kSuccess);

		WideString m(L"c:\\temp\\something.indt");
		K2Vector<WideString> optionsVec;
		PMString oldPath = this->GetTemplatePath();
		optionsVec.push_back(m);
		err = this->SetOptions(optionsVec);
		ASSERT(err == kSuccess);
		WideString n = WideString(this->GetTemplatePath());
		predicate=(m == n);
		ASSERT(predicate);
		if(predicate) { successes++; } else { failures++;}
		// restore starting state
		optionsVec.clear();
		optionsVec.push_back(WideString(oldPath));
		err = this->SetOptions(optionsVec);
		ASSERT(err == kSuccess);


	} while(kFalse);

	PMString pstr("Successes=");
	pstr.AppendNumber(successes);
	pstr += ", failures=";
	pstr.AppendNumber(failures);
	pstr.SetTranslatable(kFalse);
	CAlert::InformationAlert(pstr);

}


// End, XDocBkFacade.cpp.
