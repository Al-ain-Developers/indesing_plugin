//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpImportExportSnippet.cpp $
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
#include "IActiveContext.h"
#include "IDocument.h"
#include "IIDXMLElement.h"
#include "IINXInfo.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "IObjectModel.h"
#include "IPageList.h"
#include "IScript.h"
#include "IScriptEngine.h"
#include "IScriptManager.h"
#include "IScriptUtils.h"
#include "ISelectionManager.h"
#include "ISnippetExport.h"
#include "ISnippetImport.h"
#include "ISpreadLayer.h"
#include "ISpreadList.h"
#include "IStoryList.h"
#include "IStyleGroupManager.h"
#include "IStyleGroupHierarchy.h"
#include "ITextModel.h"
#include "IUIDIterator.h"
#include "IWorkspace.h"
#include "IXMLReferenceData.h"
#include "IXMLScriptUtils.h"
#include "IXMLUtils.h"

// ID Includes:
#include "StandOffID.h"

// General includes:
#include "StreamUtil.h"
#include "UIDList.h"
#include "Utils.h"
#include "SDKFileHelper.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "ISnipRunSuite.h"
#include "SnipRunLog.h"
#include "SnpXMLSampleHelper.h"
#include "SnpXMLResolutionHelper.h"
#if __INTEL_COMPILER || MACINTOSH
#include "K2Vector.tpp"
#endif

/** Code that demonstrates snippet import and export using the ISnippetExport interface.

 	@ingroup sdk_snippet
	@ingroup sdk_xmedia
 */
class SnpImportExportSnippet
{
public: 

	/**	Export an XML-tagged content item (in the layout) to specified path as a snippet
		@param contentUIDRef 
		@param whereTo 
		@return ErrorCode kSuccess on success, other ErrorCode otherwise
		@return ErrorCode kSuccess on success, other ErrorCode otherwise 
	 */
	ErrorCode ExportTaggedContentItem(const UIDRef& contentUIDRef, const IDFile& whereTo );

	
	/**	Export an InCopy Story to a file.
		@param uidList list of objects, IDOMElement can be instantiated from each
		@param idFile where to export to
		@param options INXOptions (traditional or expanded)
		@return ErrorCode kSuccess on success, other ErrorCode otherwise 
	 */
	ErrorCode ExportInCopyInterchangeToFile(const UIDList& uidList, const IDFile& idFile, INXOptions options );

	/**	Export UIDList of Page Items to a file

		@param uidList list of objects, IDOMElement can be instantiated from each
		@param idFile where to export to
		@return ErrorCode kSuccess on success, other ErrorCode otherwise 
	 */
	ErrorCode ExportPageitemsToFile(const UIDList& uidList, const IDFile& idFile );

	/**	Import a snippet as a child of a specified spread
		@param documentUIDRef specifies document of interest
		@param snippetFile 
		@param whichSpread spread index, zero based, within spreadlist (ISpreadList)
		@return ErrorCode kSuccess on success, other ErrorCode otherwise 
	 */
	ErrorCode ImportToSpreadElement(const UIDRef& documentUIDRef, const IDFile& snippetFile, int32 whichSpread=0);

	/**	Import as child of given scripting DOM element, IDOMElement
		@param domElementUIDRef specifies document of interest
		@param snippetFile 
		@return ErrorCode kSuccess on success, other ErrorCode otherwise 
	 */
	ErrorCode ImportToElement(const UIDRef& domElementUIDRef, const IDFile& snippetFile);

	/**	Import XML elements in snippet into logical structure
		@param docUIDRef specifies document of interest
		@param whereFrom snippet file
		@param whereTo location in logical structure from which IIDXMLElement can be instantiated
		@return ErrorCode kSuccess on success, other ErrorCode otherwise 
	 */
	ErrorCode ImportXMLElements(const UIDRef& docUIDRef, const IDFile& whereFrom, const XMLReference& whereTo);

	/**	Import XML elements in snippet into root of logical structure
		@param docUIDRef specifies document of interest
		@param whereFrom snippet file
		@return ErrorCode kSuccess on success, other ErrorCode otherwise 
	 */
	ErrorCode ImportXMLElementsToRoot(const UIDRef& docUIDRef, const IDFile& whereFrom);
};

/*
*/
ErrorCode SnpImportExportSnippet::ExportPageitemsToFile(const UIDList& uidList, const IDFile& idFile)
{
	ErrorCode result = kFailure;
	do {

		InterfacePtr<IPMStream> stream(StreamUtil::CreateFileStreamWrite(idFile, kOpenOut, 'TEXT', 'CWIE'));
		ASSERT(stream);
		if(!stream) {
			break;
		}
		stream->Open();
		if (stream->GetStreamState() != kStreamStateGood) {
			break;
		}
		
		stream->SetEndOfStream();
		result = Utils<ISnippetExport>()->ExportPageitems(stream, uidList);
		stream->Flush();
		ASSERT(result == kSuccess);
	
		stream->Close();

	} while(false);
	return result;
}

/*
*/
ErrorCode SnpImportExportSnippet::ExportInCopyInterchangeToFile(const UIDList& uidList, const IDFile& idFile, INXOptions options )
{
	ErrorCode result = kFailure;
	do {

		InterfacePtr<IPMStream> stream(StreamUtil::CreateFileStreamWrite(idFile, kOpenOut, 'TEXT', 'CWIE'));
		ASSERT(stream);
		if(!stream) {
			break;
		}
		stream->Open();
		if (stream->GetStreamState() != kStreamStateGood) {
			break;
		}
		
		stream->SetEndOfStream();
		ASSERT(options.IsExpandedStructure());
		result = Utils<ISnippetExport>()->ExportInCopyInterchange(stream, uidList);
		stream->Flush();
		ASSERT(result == kSuccess);
	
		stream->Close();

	} while(false);
	return result;
}

/*
*/
ErrorCode SnpImportExportSnippet::ExportTaggedContentItem(const UIDRef& contentItemUIDRef,
															const IDFile& whereTo ) 
{
	ErrorCode result = kFailure;
	
	do {
		InterfacePtr<IPMStream> stream(StreamUtil::CreateFileStreamWrite(whereTo, kOpenOut, 'TEXT', 'CWIE'));
		ASSERT(stream);
		if(!stream) {
			break;
		}
		K2Vector<XMLReference> elemRefList;

		InterfacePtr<IXMLReferenceData> xmlReferenceData(contentItemUIDRef, UseDefaultIID());
		ASSERT(xmlReferenceData);
		if(!xmlReferenceData) {
			// oops, not a content item
			break;
		}
		XMLReference ref = xmlReferenceData->GetReference();
		elemRefList.push_back(ref);

		stream->Open();
		if (stream->GetStreamState() == kStreamStateGood) {
			stream->SetEndOfStream();

			result = Utils<ISnippetExport>()->ExportXMLElements(stream, elemRefList);
			stream->Flush();
			ASSERT(result == kSuccess);
		}
		stream->Close();
	} while(kFalse);
	return result;
}

/*
*/
ErrorCode SnpImportExportSnippet::ImportXMLElementsToRoot(const UIDRef& docUIDRef, 
													const IDFile& whereFrom) 
{
	ErrorCode result = kFailure;
	
	do {
		InterfacePtr<IIDXMLElement> rootElement(
			Utils<IXMLUtils>()->QueryRootElement(docUIDRef.GetDataBase()));
		ASSERT(rootElement);
		if(!rootElement) {
			break;
		}
		XMLReference rootRef(rootElement->GetXMLReference());
		result = this->ImportXMLElements(docUIDRef, whereFrom, rootRef);
	} while(kFalse);
	return result;
}


/*
*/
ErrorCode SnpImportExportSnippet::ImportXMLElements(const UIDRef& docUIDRef, 
													const IDFile& whereFrom,
													const XMLReference& xmlRef) 
{
	ErrorCode result = kFailure;
	
	do {
		InterfacePtr<IPMStream> stream(static_cast<IPMStream*>(
			StreamUtil::CreateFileStreamRead(whereFrom, kOpenIn)));
		ASSERT(stream);
		if(!stream) {
			break;
		}

		InterfacePtr<IScriptManager> scriptMgr( Utils<IScriptUtils>()->QueryScriptManager( kINXTraditionalImportScriptManagerBoss ) ) ;
		InterfacePtr<IScriptEngine> scriptEngine( scriptMgr->QueryDefaultEngine() ) ;
		InterfacePtr<IScript> scriptElement(Utils<IXMLScriptUtils>()->CreateXMLItemProxyScriptObject(scriptEngine->GetRequestContext(), xmlRef));
		ASSERT(scriptElement);
		if(!scriptElement) {
			break;
		}
		InterfacePtr<IDOMElement> frag(scriptElement, UseDefaultIID());
		ASSERT(frag);
		if(!frag) {
			break;
		}
		result = Utils<ISnippetImport>()->ImportFromStream(stream, frag);

	} while(kFalse);
	return result;
}



/*
*/
ErrorCode SnpImportExportSnippet::ImportToSpreadElement(const UIDRef& documentUIDRef, const IDFile& snippetFile, 
								int32 whichSpread)
{
	ErrorCode result = kFailure;
	do {
		
		// + precondition
		InterfacePtr<IDocument> document(documentUIDRef, UseDefaultIID());
		ASSERT(document);
		if(!document) {
			break;
		}
		SDKFileHelper targetFileHelper(snippetFile);
		ASSERT(targetFileHelper.IsExisting());
		// -preconditions
		InterfacePtr<ISpreadList> spreadList(document, UseDefaultIID());
		ASSERT(spreadList);
		if(!spreadList) {
			break;
		}
		UIDRef spreadUIDRef(documentUIDRef.GetDataBase(), spreadList->GetNthSpreadUID(whichSpread));
		result = this->ImportToElement(spreadUIDRef, snippetFile);
		result = kSuccess;
	} while(false);
	return result;
}

/*
*/
ErrorCode SnpImportExportSnippet::ImportToElement(const UIDRef& domElementUIDRef, const IDFile& snippetFile)
{
	ErrorCode result = kFailure;
	do {

		InterfacePtr<IPMStream> stream(static_cast<IPMStream*>(
			StreamUtil::CreateFileStreamRead(snippetFile, kOpenIn)));
		ASSERT(stream);
		if(!stream) {
			break;
		}

		InterfacePtr<IDOMElement> xmlFragment(domElementUIDRef, UseDefaultIID());
		ASSERT(xmlFragment);
		if(!xmlFragment) {
			break;
		}
		result = Utils<ISnippetImport>()->ImportFromStream(stream, xmlFragment);
	} while(false);
	return result;
}


// --------------------------------- SnippetRunner framework hook ---------------------------------------------------

/** Makes the snippet SnpImportExportSnippet available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerImportExportSnippet : public SnpRunnable
{
	public:
		/** This constructor describes your snippet to the framework.
		 */
		_SnpRunnerImportExportSnippet();

		/** Destructor.
		 */
		virtual			~_SnpRunnerImportExportSnippet();

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
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunFrontDocContext;}
};

/* Describe your snippet to the framework here.
*/
_SnpRunnerImportExportSnippet::_SnpRunnerImportExportSnippet() : SnpRunnable("ImportExportSnippet")
{
	this->SetDescription("Supports export and import of XML snippets of various kinds");
	this->SetPreconditions("document open");
	this->SetCategories("sdk_snippet, sdk_layout, sdk_xmedia");

}

/* Destructor.
*/
_SnpRunnerImportExportSnippet::~_SnpRunnerImportExportSnippet()
{
}

/* Check if your snippet's preconditions are met here.
*/
bool16	_SnpRunnerImportExportSnippet::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {
		if(runnableContext->GetActiveContext()->GetContextDocument() != nil) {
			result = kTrue;
		}
	} while(false);
	return result;
}

/* Set up and call your snippet here.
*/
ErrorCode _SnpRunnerImportExportSnippet::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
	
		PMString exportSplineAsIDMS("ExportSplineAsIDMS");
		PMString importSplineAsIDMS("ImportSplineAsIDMS");
		PMString exportXMLAsIDMS("ExportTaggedContentItemAsIDMS");
		PMString importXMLAsIDMS("ImportTaggedContentItemAsIDMS");
		PMString exportInCopySnippetAsICML("ExportStoryAsInCopySnippetAsICML");

		PMString exportSplineAsINDS("ExportSplineAsINDS");
		PMString importSplineAsINDS("ImportSplineAsINDS");
		PMString exportXMLAsINDS("ExportTaggedContentItemAsINDS");
		PMString importXMLAsINDS("ImportTaggedContentItemAsINDS");
		
		PMString unitTest("UnitTestAll");

		K2Vector<PMString> choices;
		choices.push_back(exportSplineAsIDMS); //0
		choices.push_back(importSplineAsIDMS); //1
		choices.push_back(exportXMLAsIDMS); //2
		choices.push_back(importXMLAsIDMS); //3
		choices.push_back(exportInCopySnippetAsICML); //4

		choices.push_back(exportSplineAsINDS); //5
		choices.push_back(importSplineAsINDS); //6
		choices.push_back(exportXMLAsINDS); //7
		choices.push_back(importXMLAsINDS); //8

		choices.push_back(unitTest); //9 MOVE TO LAST ALWAYS
	
	
		SnpImportExportSnippet instance;
		Utils<ISnipRunParameterUtils> parameterUtils;
		int32 choice = parameterUtils->GetChoice(PMString("What action?"), choices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		SnpXMLSampleHelper xmlHelper;
		IDFile where = xmlHelper.GetSampleFile("-default.idms");
	
		UIDRef docUIDRef = ::GetUIDRef(
						runnableContext->GetActiveContext()->GetContextDocument());
		switch(choice) 
		{
		
			case 0:
			{
				where = xmlHelper.GetSampleFile("-spline.idms");
				SDKFileHelper fileHelper(where);
				PMRect rect(50,50,250,300);
				UIDRef splineUIDRef = xmlHelper.CreateRectangleFrame(docUIDRef,rect,0,0);
				status = instance.ExportPageitemsToFile(UIDList(splineUIDRef), where);
				SNIPLOG("\nThis scenario attempted to export rectangle page item (%s)",
					fileHelper.GetPath().GetPlatformString().c_str());
			}
			break;

			case 1:
			{
				where = xmlHelper.GetSampleFile("-spline.idms");
				SDKFileHelper fileHelper(where);
				bool16 fileExists = fileHelper.IsExisting();
				if(!fileExists) {
					SNIPLOG("ERROR: file to import does not yet exist; create by ExportSpline");
						break;
				}
				status = instance.ImportToSpreadElement(docUIDRef, where);
				SNIPLOG("\nThis scenario attempted to import a rectangle page item from  (%s) into spread",
					fileHelper.GetPath().GetPlatformString().c_str());
				
			}
			break;


			case 2:
			{
				
				PMRect rect(50,50,250,300);
				UIDRef storyUIDRef = xmlHelper.CreateStoryThroughFrame(docUIDRef,rect,0,0);
				xmlHelper.CreateSampleTaggedStory(storyUIDRef);
				where = xmlHelper.GetSampleFile("-xmlelems.idms");
				SDKFileHelper fileHelper(where);
			
				status = instance.ExportTaggedContentItem(storyUIDRef, where);
				SNIPLOG("\nThis scenario attempted to export XML tagged content item (%s)",
					fileHelper.GetPath().GetPlatformString().c_str());
			}
			break;

			case 3:
			{
				where = xmlHelper.GetSampleFile("-xmlelems.idms");
				SDKFileHelper fileHelper(where);
				bool16 fileExists = fileHelper.IsExisting();
				if(!fileExists) {
					SNIPLOG("ERROR: file to import does not yet exist; create by ExportTaggedContentItem");
						break;
				}
				status = instance.ImportXMLElementsToRoot(docUIDRef, where);
				SNIPLOG("\nThis scenario attempted to import XML tagged content item (%s)",
					fileHelper.GetPath().GetPlatformString().c_str());
			}
			break;

			case 4:
			{
				where = xmlHelper.GetSampleFile("-story.icml");
				SDKFileHelper fileHelper(where);
				PMRect rect(50,50,250,300);
				UIDRef storyUIDRef = xmlHelper.CreateStoryThroughFrame(docUIDRef,rect,0,0);
				PMString textData("Sample story content for InCopy export");
				PMString styleName("story-style");
				UIDRef styleUIDRef = xmlHelper.AcquireParaStyle(docUIDRef, styleName);
				TextIndex nextIndex;
				xmlHelper.InsertStyledLine(storyUIDRef,textData,0,styleUIDRef, nextIndex);
				status = instance.ExportInCopyInterchangeToFile(UIDList(storyUIDRef), where, kINXExpanded);
				SNIPLOG("\nThis scenario attempted to export story as InCopyInterchange (%s)",
					fileHelper.GetPath().GetPlatformString().c_str());		
			}
			break;		

			case 5:
			{
				where = xmlHelper.GetSampleFile("-spline.inds");
				SDKFileHelper fileHelper(where);
				PMRect rect(50,50,250,300);
				UIDRef splineUIDRef = xmlHelper.CreateRectangleFrame(docUIDRef,rect,0,0);
				status = instance.ExportPageitemsToFile(UIDList(splineUIDRef), where);
				SNIPLOG("\nThis scenario attempted to export rectangle page item (%s)",
					fileHelper.GetPath().GetPlatformString().c_str());
			}
			break;

			case 6:
			{
				where = xmlHelper.GetSampleFile("-spline.inds");
				SDKFileHelper fileHelper(where);
				bool16 fileExists = fileHelper.IsExisting();
				if(!fileExists) {
					SNIPLOG("ERROR: file to import does not yet exist; create by ExportSpline");
						break;
				}
				status = instance.ImportToSpreadElement(docUIDRef, where);
				SNIPLOG("\nThis scenario attempted to import a rectangle page item from  (%s) into spread",
					fileHelper.GetPath().GetPlatformString().c_str());
				
			}
			break;


			case 7:
			{
				
				PMRect rect(50,50,250,300);
				UIDRef storyUIDRef = xmlHelper.CreateStoryThroughFrame(docUIDRef,rect,0,0);
				xmlHelper.CreateSampleTaggedStory(storyUIDRef);
				where = xmlHelper.GetSampleFile("-xmlelems.inds");
				SDKFileHelper fileHelper(where);
			
				status = instance.ExportTaggedContentItem(storyUIDRef, where);
				SNIPLOG("\nThis scenario attempted to export XML tagged content item (%s)",
					fileHelper.GetPath().GetPlatformString().c_str());
			}
			break;

			case 8:
			{
				where = xmlHelper.GetSampleFile("-xmlelems.inds");
				SDKFileHelper fileHelper(where);
				bool16 fileExists = fileHelper.IsExisting();
				if(!fileExists) {
					SNIPLOG("ERROR: file to import does not yet exist; create by ExportTaggedContentItem");
						break;
				}
				status = instance.ImportXMLElementsToRoot(docUIDRef, where);
				SNIPLOG("\nThis scenario attempted to import XML tagged content item (%s)",
					fileHelper.GetPath().GetPlatformString().c_str());
			}
			break;

			case 9:
			{
				PMString snippetName("ImportExportSnippet");
				InterfacePtr<ISnipRunSuite> suite(
					runnableContext->GetActiveContext()->GetContextSelection(), UseDefaultIID());
				ASSERT(suite);
				if (!suite)
					break;

				if (suite->CanRun(snippetName))
				{
					// Check names above
					suite->Run(snippetName, exportSplineAsIDMS);
					suite->Run(snippetName, importSplineAsIDMS);
					suite->Run(snippetName, exportXMLAsIDMS);
					suite->Run(snippetName, importXMLAsIDMS);
					suite->Run(snippetName, exportInCopySnippetAsICML);
					suite->Run(snippetName, exportSplineAsINDS);
					suite->Run(snippetName, importSplineAsINDS);
					suite->Run(snippetName, exportXMLAsINDS);
					suite->Run(snippetName, importXMLAsINDS);
					// If we got here without crashes or asserts, consider
					// that a success
					status = kSuccess;
				} else {
					SNIPLOG("Can't run snippet self");
				}
			}
			break;
		} // end of switch
		
	} while(false);

	       
	return (status);
}

/*	Declare an instance to register the snippet hook with the framework.
*/
static _SnpRunnerImportExportSnippet instance_SnpRunnerImportExportSnippet;
DEFINE_SNIPPET(_SnpRunnerImportExportSnippet) 	

// End, SnpImportExportSnippet.cpp

