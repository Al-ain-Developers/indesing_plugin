//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpExportEPub.cpp $
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
//  Copyright 2011 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IEBookExport.h"
#include "IApplication.h"
#include "IDocumentList.h"
#include "IDocument.h"
#include "ILayoutUIUtils.h"
#include "SDKFileHelper.h"
#include "StreamUtil.h"
#include "ISelectionManager.h"
#include "IExportProvider.h"
#include "ISelectionUtils.h"
#include "IK2ServiceRegistry.h"
#include "IK2ServiceProvider.h"
#include "FileTypeRegistry.h"
#include "IArticleList.h"
#include "IArticleFacade.h"

// General includes:
#include "Utils.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/**
	\li Exports a document to a EPUB file.

	This snippet shows how to use the EPUB export service provider
	to export a document to EPUB file.

  	@ingroup sdk_snippet
	@ingroup sdk_export

	@see IExportProvider

 */
class SnpExportEPub
{
	public:
		/** Constructor.
		*/
		SnpExportEPub() {}

		/** Destructor.
		*/
		virtual ~SnpExportEPub() {}

		/** Export the specified document to EPUB.

			@param doc The document to export.
			@returns kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode ExportEPub(IDocument* doc);	
};

ErrorCode SnpExportEPub::ExportEPub(IDocument* doc)
{
	ErrorCode result = kFailure;
	do {
		SDKFileSaveChooser fileChooser;
		
		SysOSType macFileCreator = FileTypeRegistry::GetCurrentFileCreator(kPublicationFileTypeInfoID);
		
		PMString filter("epub");
		filter.SetTranslatable(kFalse);
		fileChooser.AddFilter(macFileCreator, 'EPUB', filter, filter);
		fileChooser.ShowDialog();

		if (fileChooser.IsChosen() == kFalse) 
		{
			result = kCancel;
			break;
		}
		IDFile file = fileChooser.GetIDFile();

		InterfacePtr<ISelectionManager> selection(Utils<ISelectionUtils>()->QueryActiveSelection());
		
		InterfacePtr<IK2ServiceRegistry> k2ServiceRegistry(GetExecutionContextSession(), UseDefaultIID());
		// Look for all service providers with kExportProviderService.
		int32 exportProviderCount = k2ServiceRegistry->GetServiceProviderCount(kExportProviderService);
		// Iterate through them.
		for (int32 i = 0; i < exportProviderCount; i++)
		{
			// get the service provider boss class
			InterfacePtr<IK2ServiceProvider> k2ServiceProvider
				(k2ServiceRegistry->QueryNthServiceProvider(kExportProviderService,	i));
			// Get the export provider implementation itself.
			InterfacePtr<IExportProvider> exportProvider(k2ServiceProvider, IID_IEXPORTPROVIDER);
			// Check to see if the current selection specifier can be exported by this provider.
			bool16 canExportByTarget = exportProvider->CanExportThisFormat(doc, selection, "EPUB");
			if (canExportByTarget)
			{				
				exportProvider->ExportToFile(file, doc, selection, "EPUB", kFullUI);
				result = kSuccess;
				break;
			}
		}

		result = kSuccess;
	} while(false);

	return result;
}

// --------------------------------- SnippetRunner framework hook ---------------------------------------------------

/** Makes the snippet SnpExportEPub available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerExportEPub : public SnpRunnable
{
	public:
		/** Constructor.
		 */
		_SnpRunnerExportEPub();

		/** Destructor.
		 */
		virtual			~_SnpRunnerExportEPub();

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

/* Describe your snippet to the framework here.
*/
_SnpRunnerExportEPub::_SnpRunnerExportEPub() : SnpRunnable("ExportEPub")
{	
	this->SetDescription("Provides a ExportEPub");
	this->SetPreconditions("none");
	this->SetCategories("sdk_snippet");
}

/* Destructor.
*/
_SnpRunnerExportEPub::~_SnpRunnerExportEPub()
{
}

/* Check if your snippet's preconditions are met here.
*/
bool16 _SnpRunnerExportEPub::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {		
		IDocument* doc = Utils<ILayoutUIUtils>()->GetFrontDocument();
		if (doc == nil)
		{
			break;
		}

		result = kTrue;
	} while(false);

	return result;
}

/* Set up and call your snippet here.
*/
ErrorCode _SnpRunnerExportEPub::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		SnpExportEPub instance;
		IDocument* doc = Utils<ILayoutUIUtils>()->GetFrontDocument();
		status = instance.ExportEPub(doc);
	} while(false);

	return (status);
}

/*	Declare an instance to register the snippet hook with the framework.
*/
static _SnpRunnerExportEPub instance_SnpRunnerExportEPub;
DEFINE_SNIPPET(_SnpRunnerExportEPub) 	
// End, SnpExportEPub.cpp

