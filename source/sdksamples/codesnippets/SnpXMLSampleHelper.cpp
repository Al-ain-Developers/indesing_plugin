//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpXMLSampleHelper.cpp $
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
#include "IApplication.h"
#include "IDocument.h"
#include "IIDXMLElement.h"
#include "IPageList.h"
#include "IPMStream.h"
#include "ISpreadList.h"
#include "IStyleNameTable.h"
#include "IStyleGroupManager.h"
#include "IStyleGroupHierarchy.h"
#include "IStyleInfo.h"
#include "ITableModel.h"
#include "ITableUtils.h"
#include "ITextModel.h"
#include "ITextModelCmds.h"
#include "IWorkspace.h"
// General includes:
#include "StreamUtil.h"
#include "FileUtils.h"
#include "SDKLayoutHelper.h"
#include "SDKFileHelper.h"
// Project includes
#include "SnipRunLog.h"
#include "SnpRunnable.h"
#include "SnpXMLSampleHelper.h"


int32 SnpXMLSampleHelper::nRectsCreated = (0);
int32 SnpXMLSampleHelper::nColsCreated = (0);

void SnpXMLSampleHelper::ResetRectCounts()
{
	nRectsCreated = 0;
	nColsCreated = 0;
}


/*
*/
UIDRef SnpXMLSampleHelper::AcquireCharStyle(const UIDRef& documentUIDRef, const PMString& name)
{
	return this->AcquireStyle(documentUIDRef, name, IID_ICHARSTYLEGROUPMANAGER, kCreateCharStyleCmdBoss);
}

/*
*/
UIDRef SnpXMLSampleHelper::AcquireParaStyle(const UIDRef& documentUIDRef, const PMString& name)
{
	return this->AcquireStyle(documentUIDRef, name, IID_IPARASTYLEGROUPMANAGER, kCreateParaStyleCmdBoss);
}

/*
*/
UIDRef SnpXMLSampleHelper::AcquireStyle(const UIDRef& documentUIDRef,
												  const PMString& name,
												  const PMIID& styleIID,
												  const ClassID& createCmdClassID)
{
	UIDRef retval;
	do {
		InterfacePtr<IDocument> document(documentUIDRef, UseDefaultIID());
		ASSERT(document);
		if(!document) {
			break;
		}
		
		InterfacePtr<IStyleGroupManager> styleNameTable(document->GetDocWorkSpace(),
														styleIID);
		ASSERT(styleNameTable);
		if(!styleNameTable) {
			break;
		}
		UID styleUID = styleNameTable->FindByName(name);
		if(styleUID == kInvalidUID) {
			InterfacePtr<ICommand> createStyleCmd(
				CmdUtils::CreateCommand(createCmdClassID));
			ASSERT(createStyleCmd);	
			
			InterfacePtr<IStyleInfo> styleInfo(createStyleCmd, UseDefaultIID());
			ASSERT(styleInfo);
			if(!styleInfo) {
				break;
			}
			styleInfo->SetName(name);
			styleInfo->SetIsStyleImported(kFalse);
			createStyleCmd->SetItemList(UIDList(document->GetDocWorkSpace()));
			
			ErrorCode retval = CmdUtils::ProcessCommand(createStyleCmd);
			ASSERT(retval == kSuccess);
			if(retval != kSuccess) {
				break;
			}
			
		}
		styleUID = styleNameTable->FindByName(name);
		ASSERT(styleUID != kInvalidUID);
		retval = UIDRef(documentUIDRef.GetDataBase(), styleUID);
	} while(kFalse);

	return retval;
}


/*
*/
UIDRef SnpXMLSampleHelper::CreateRectangleFrame(const UIDRef& documentUIDRef, const PMRect& rect,
							int32 spreadNum, int32 pageNum) 
{
	UIDRef retval;
	do {
		InterfacePtr<IDocument> document(documentUIDRef, UseDefaultIID());
		ASSERT(document);
		if(!document) {
			break;
		}

		
		InterfacePtr<ISpreadList> spreadList(documentUIDRef, UseDefaultIID());
		if(!spreadList) {
			break;
		}
		UIDRef spreadRef = UIDRef(documentUIDRef.GetDataBase(), spreadList->GetNthSpreadUID(spreadNum));
		SDKLayoutHelper layoutHelper;
		UIDRef spreadLayerRef = layoutHelper.GetActiveSpreadLayerRef(spreadRef);
		ASSERT(spreadLayerRef != UIDRef::gNull);

		InterfacePtr<IPageList> pageList(documentUIDRef, UseDefaultIID());
		if(!pageList) {
			break;
		}
		UIDRef pageUIDRef = UIDRef(documentUIDRef.GetDataBase(), pageList->GetNthPageUID(pageNum));
		ASSERT(pageUIDRef != UIDRef::gNull);
		
	
		retval = layoutHelper.CreateRectangleFrame(spreadLayerRef,
											layoutHelper.PageToSpread(pageUIDRef, rect));

		ASSERT(retval != UIDRef::gNull);

	} while(kFalse);
	return retval;
}


/*
*/
ErrorCode SnpXMLSampleHelper::CreateSampleDTD(const IDFile& sysFile)
{
	ErrorCode err = kFailure;
	do {

		InterfacePtr<IPMStream> stream(StreamUtil::CreateFileStreamWrite(sysFile, kOpenOut, 'TEXT', 'CWIE'));
		ASSERT(stream);
		if(!stream) {
			break;
		}
		stream->Open();
		if (stream->GetStreamState() == kStreamStateGood)
		{
			stream->SetEndOfStream();
			//
			SaveLineToStream(PMString("<?xml version=\"1.0\" encoding=\"UTF-8\"?>"), stream);
			SaveLineToStream(PMString("<!ELEMENT publication (article)+>"), stream);
			SaveLineToStream(PMString("<!ELEMENT article (article-title, body)>"), stream);
			SaveLineToStream(PMString("<!ELEMENT body (title | subhead | para)+>"), stream);
			SaveLineToStream(PMString("<!ELEMENT article-title (#PCDATA)>"), stream);
			SaveLineToStream(PMString("<!ELEMENT title (#PCDATA)>"), stream);
			SaveLineToStream(PMString("<!ELEMENT subhead (#PCDATA)>"), stream);
			SaveLineToStream(PMString("<!ELEMENT emphasis (#PCDATA)>"), stream);
			SaveLineToStream(PMString("<!ENTITY % pub.content \"#PCDATA\">"), stream);
			SaveLineToStream(PMString("<!ELEMENT para (%pub.content; | emphasis)* >"), stream);
			//
			stream->Flush();
			err = kSuccess;
		}
		stream->Close();
		
	} while(kFalse);
	return err;
}



/*
*/
ErrorCode SnpXMLSampleHelper::CreateSampleTaggedStory(const UIDRef& textModelUIDRef,
												bool16 noOptionalContent)
{
	ErrorCode err = kFailure;
	do {

		InterfacePtr<ITextModel> textModel(textModelUIDRef, UseDefaultIID());
		ASSERT(textModel);
		if(!textModel) {
			break;
		}
		this->TagStory(textModelUIDRef, PMString("article"));
		PMString pstr("Headline");

		TextIndex nextIndex = this->InsertTaggedText(textModelUIDRef, PMString("Headline"), 0, PMString("headline"));
		nextIndex = this->InsertTaggedText(textModelUIDRef, PMString("Byline"), nextIndex, PMString("byline"));
		
		if(!noOptionalContent) {
			nextIndex = this->InsertTaggedText(textModelUIDRef, PMString("Dateline"), nextIndex, PMString("dateline"));
			nextIndex = this->InsertTaggedText(textModelUIDRef, PMString("Copyright"), nextIndex, PMString("copyright"));
		}

		err= kSuccess;
	} while(kFalse);
	return err;
}

/*
*/
ErrorCode SnpXMLSampleHelper::CreateSampleXML(const IDFile& sysFile, bool16 isExtended)
{
	ErrorCode err = kFailure;
	do {

		InterfacePtr<IPMStream> stream(StreamUtil::CreateFileStreamWrite(sysFile, kOpenOut, 'TEXT', 'CWIE'));
		ASSERT(stream);
		if(!stream) {
			break;
		}
		stream->Open();
		if (stream->GetStreamState() == kStreamStateGood)
		{
			stream->SetEndOfStream();
			//
			SaveLineToStream(PMString("<?xml version=\"1.0\" encoding=\"UTF-8\"?>"), stream);
			SaveLineToStream(PMString("<article><headline>Another Disastrous Night for Scotland</headline>"), stream);
			SaveLineToStream(PMString("<byline>Chick O'Young</byline>"), stream);
			SaveLineToStream(PMString("<dateline>22 July 2004</dateline>"), stream);
			if(isExtended) {
				SaveLineToStream(PMString("<copyright>Dinner O'Boos Incorporated</copyright>"), stream);
			}
			SaveLineToStream(PMString("<body><para>Scotland's World Cup qualification hopes were dampened by the news that no-one in the current squad is fit to play for Scotland.</para></body>"), stream);
			SaveLineToStream(PMString("</article>"), stream);
			//
			stream->Flush();
			err = kSuccess;
		}
		stream->Close();
		
	} while(kFalse);
	return err;
}



/*
*/
UIDRef SnpXMLSampleHelper::CreateStoryThroughFrame(const UIDRef& documentUIDRef, const PMRect& rect,
							int32 spreadNum, int32 pageNum) 
{
	UIDRef retval;
	do {
		InterfacePtr<IDocument> document(documentUIDRef, UseDefaultIID());
		ASSERT(document);
		if(!document) {
			break;
		}

		InterfacePtr<ISpreadList> spreadList(documentUIDRef, UseDefaultIID());
		if(!spreadList) {
			break;
		}
		UIDRef spreadRef = UIDRef(documentUIDRef.GetDataBase(), spreadList->GetNthSpreadUID(spreadNum));
		SDKLayoutHelper layoutHelper;
		UIDRef spreadLayerRef = layoutHelper.GetActiveSpreadLayerRef(spreadRef);
		ASSERT(spreadLayerRef != UIDRef::gNull);

		InterfacePtr<IPageList> pageList(documentUIDRef, UseDefaultIID());
		if(!pageList) {
			break;
		}
		UIDRef pageUIDRef = UIDRef(documentUIDRef.GetDataBase(), pageList->GetNthPageUID(pageNum));
		ASSERT(pageUIDRef != UIDRef::gNull);
		ASSERT(pageUIDRef.GetUID() != kInvalidUID);
		if(pageUIDRef.GetUID() == kInvalidUID) {
			break;
		}
		UIDRef frameRef = layoutHelper.CreateTextFrame(spreadLayerRef,
											layoutHelper.PageToSpread(pageUIDRef, rect),
											1, kFalse,
											&retval);

		ASSERT(frameRef != UIDRef::gNull);
		ASSERT(retval != UIDRef::gNull);
	} while(kFalse);
	return retval;
}




/*
*/
ErrorCode SnpXMLSampleHelper::CreateTableThroughFrame(const UIDRef& documentUIDRef,
												const PMRect& rect,
												UIDRef& outTableModelUIDRef,
												UIDRef& outTextModelUIDRef,
												int32 nRows, int32 nCols)
{
	ErrorCode err = kFailure;
	do {
		InterfacePtr<IDocument> document(documentUIDRef, UseDefaultIID());
		if(!document) {
			break;
		}
		outTextModelUIDRef = this->CreateStoryThroughFrame(documentUIDRef,rect,0,0);
		InterfacePtr<ITextModel> textModel(outTextModelUIDRef, UseDefaultIID());
		ASSERT(textModel);
		if(!textModel) {
			break;
		}
		this->InsertText(outTextModelUIDRef,PMString(" some body text"), 0);
		TextIndex insertLocation =0;
		Utils<ITableUtils>()->InsertTable(textModel, 
											0, 
											0, 
											nRows, 
											nCols, 
											0.0, 
											50.0, 
											kTextContentType, 
											ITableUtils::eNoSelection);
	
		InterfacePtr<ITableModel> tableModel(
			Utils<ITableUtils>()->GetTableModel(textModel, insertLocation), UseDefaultIID());
		
		ASSERT(tableModel);	
		outTableModelUIDRef = ::GetUIDRef(tableModel);
		ASSERT(outTableModelUIDRef.GetUID() != kInvalidUID);
		err = kSuccess;
	} while(kFalse);
	return err;

}




/*
*/
void SnpXMLSampleHelper::GetNextRect(PMRect& outRect)
{
	const int32 maxCols=3;
	const int32 maxRects=3;

	PMReal h(200.0);
	PMReal w(150.0);
	PMReal nextY((1.0*nRectsCreated) * (1.1*h));
	PMReal nextX((1.0*nColsCreated) * (1.1*w));
	
	
	nRectsCreated ++;
	if(nRectsCreated >= maxRects) {
		nRectsCreated = 0;
		nColsCreated++;
	}

	if(nColsCreated >= maxCols) {
		nColsCreated = 0;
	}
	if(nextX < 0.0) nextX = 0.0;
	if(nextY < 0.0) nextY = 0.0;
	if(nextX > 10000.0) nextX = 0.0;
	if(nextY > 10000.0) nextY = 0.0;

	outRect.Left(nextX);
	outRect.Right(nextX+w);
	outRect.Top(nextY);
	outRect.Bottom(nextY+h);
}


/*
*/
IDFile SnpXMLSampleHelper::GetSampleFile(const PMString& extension)
{
#ifdef WINDOWS
	const PMString platformDelimiter("\\");
#endif
#ifdef MACINTOSH
	const PMString platformDelimiter(":");
#endif
	IDFile appDocumentFolder;
	PMString nullFolder;
	// This call doesn't create a subfolder for us
	bool16 gotAppFolder = FileUtils::GetAppRoamingDataFolder(&appDocumentFolder, nullFolder);
	ASSERT(gotAppFolder);
	SDKFileHelper appFolder(appDocumentFolder);

	PMString baseName = appFolder.GetPath() + platformDelimiter;
	PMString exportXMLFile(baseName); 
	exportXMLFile += ("sdksamp");
	if(extension.Contains(PMString("."))) {
		exportXMLFile += extension;
	} else {
		exportXMLFile += ".";
		exportXMLFile += extension;
	}
	SDKFileHelper fileHelper(exportXMLFile);
	return fileHelper.GetIDFile();
}

/*
*/
ErrorCode SnpXMLSampleHelper::InsertStyledLine(const UIDRef& textModelUIDRef, 
										const PMString& pstr, 
										const TextIndex& startIndex,
										const UIDRef& styleUIDRef,
										TextIndex& outNextTextIndex)
{
	ErrorCode err = kFailure;
	outNextTextIndex = startIndex;
	do {
		// Wrap the changes to be made in a command sequence.
		CmdUtils::SequenceContext seq;

		this->InsertText(textModelUIDRef,pstr,startIndex);
		TextIndex endIndex = startIndex + pstr.CharCount();
		PMString cr;
		cr.Append(kTextChar_CR);
		// Insert at end of where we've just added the text
		this->InsertText(textModelUIDRef, cr, endIndex);
		// Return the next index where we can insert text
		outNextTextIndex = (endIndex + 1);
		RangeData newRangeData(startIndex, endIndex);

		
		// now style the text we added
		ClassID strandBoss = kParaAttrStrandBoss;
		// apply the style
		InterfacePtr<ITextModelCmds> textModelCmds(textModelUIDRef, UseDefaultIID());
		ASSERT(textModelCmds);
		if(!textModelCmds) {
			break;
		}
		InterfacePtr<ICommand> applyStyleCmd(textModelCmds->ApplyStyleCmd(startIndex, 
																		pstr.CharCount(), 
																		styleUIDRef.GetUID(), 
																		strandBoss, 
																		kTrue	// Replace overrides (shouldn't be manually styling text anyhow)
																		));
		ASSERT(applyStyleCmd);
		err = CmdUtils::ProcessCommand(applyStyleCmd);
		ASSERT(err== kSuccess);

	} while(kFalse);
	return err;

}




/*
*/
void SnpXMLSampleHelper::SaveLineToStream(const PMString& str, IPMStream* stream)
{
	// Came out of SnipRunLog.cpp
	const uchar kInternalNewLine='\n';
#ifdef MACINTOSH
		const char* kExternalNewLine="\r";
#else
		const char* kExternalNewLine="\r\n";
#endif
	for (int32 i = 0; i < str.CharCount(); i++)
	{
		PlatformChar pc = str[i];

		// if dual-byte char, output as is, highbyte first.
		if (pc.IsTwoByte()) 
		{
			uchar	hb = pc.HighByte(), 
					lb = pc.LowByte();
			stream->XferByte(&hb, 1);
			stream->XferByte(&lb, 1);
		}
		else // non-dualbyte char
		{
			uchar c = pc.GetAsOneByteChar();
			if (c == kInternalNewLine)
			{
#ifdef MACINTOSH
			stream->XferByte((uchar*)kExternalNewLine, 1);
#else
			stream->XferByte((uchar*)kExternalNewLine, 2);
#endif
			}
			else
			{
				stream->XferByte(&c, 1);
			}
		}
	}
}



// --------------------------------- SnippetRunner framework hook ---------------------------------------------------

/** Makes the snippet SnpXMLSampleHelper available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerXMLSampleHelper : public SnpRunnable
{
	public:
		/** This constructor describes your snippet to the framework.
		 */
		_SnpRunnerXMLSampleHelper();

		/** Destructor.
		 */
		virtual			~_SnpRunnerXMLSampleHelper();

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
_SnpRunnerXMLSampleHelper::_SnpRunnerXMLSampleHelper() : SnpRunnable("XMLSampleHelper")
{
	this->SetDescription("Exercises helper methods in SnpXMLSampleHelper");
	this->SetPreconditions("open document");
	this->SetCategories("sdk_snippet, sdk_xmedia");
}

/* Destructor.
*/
_SnpRunnerXMLSampleHelper::~_SnpRunnerXMLSampleHelper()
{
}

/* Check if your snippet's preconditions are met here.
*/
bool16	_SnpRunnerXMLSampleHelper::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {
		ASSERT(runnableContext->GetActiveContext()); 
		if(!runnableContext->GetActiveContext()) {
			break;
		}
		IDocument* document = runnableContext->GetActiveContext()->GetContextDocument();
		result = document != nil;
	} while(false);
	return result;
}

/* Set up and call your snippet here.
*/
ErrorCode _SnpRunnerXMLSampleHelper::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode err = kCancel;

	do {
		UIDRef docUIDRef = ::GetUIDRef(runnableContext->GetActiveContext()->GetContextDocument());
	
		SnpXMLSampleHelper XMLSampleHelper;

		UIDRef cStyleUIDRef = XMLSampleHelper.AcquireCharStyle(docUIDRef, PMString("XMLSampleHelper-char-style"));
		ASSERT(cStyleUIDRef.GetUID() != kInvalidUID);
		SNIPLOG("Created instance of %s",
			XMLSampleHelper.GetClassFrom(cStyleUIDRef).GetPlatformString().c_str());
		UIDRef pStyleUIDRef = XMLSampleHelper.AcquireParaStyle(docUIDRef, PMString("XMLSampleHelper-para-style"));
		ASSERT(pStyleUIDRef.GetUID() != kInvalidUID);
		SNIPLOG("Created instance of %s",
			XMLSampleHelper.GetClassFrom(pStyleUIDRef).GetPlatformString().c_str());

		UIDRef tagUIDRef = XMLSampleHelper.AcquireTag(docUIDRef, PMString("XMLSampleHelper-tag"));
		ASSERT(tagUIDRef.GetUID() != kInvalidUID);
		SNIPLOG("Created instance of %s",
			XMLSampleHelper.GetClassFrom(tagUIDRef).GetPlatformString().c_str());
		IDFile dtdFile = XMLSampleHelper.GetSampleFile(".dtd");
		ErrorCode createErr = XMLSampleHelper.CreateSampleDTD(dtdFile);
		ASSERT(createErr == kSuccess);
		ErrorCode assocErr = XMLSampleHelper.AssociateDTD(docUIDRef, dtdFile);
		ASSERT(assocErr == kSuccess);
	
		
		PMString classFromTag = XMLSampleHelper.GetClassFrom(tagUIDRef);
		ASSERT(classFromTag == PMString("kXMLTagBoss"));
	
		XMLReference rootXMLRef = XMLSampleHelper.GetRootXMLReference(docUIDRef);
		SNIPLOG("Root element as string: %s", XMLSampleHelper.AsString(rootXMLRef).GetPlatformString().c_str());

		ErrorCode changeErr = XMLSampleHelper.ChangeTagName(tagUIDRef, PMString("XMLSampleHelper-changed-tag-name"));
		// This will fail next time around
		ASSERT(changeErr == kSuccess);
		if(changeErr != kSuccess) {
			break;
		}

		XMLSampleHelper.SetRootTag(docUIDRef, PMString("New-Root-Tag"));
		SNIPLOG("Root element as string after change: %s", XMLSampleHelper.AsString(rootXMLRef).GetPlatformString().c_str());

		err = kSuccess;
	} while(kFalse);
	return err;
}

/*	Declare an instance to register the snippet hook with the framework.
*/
static _SnpRunnerXMLSampleHelper instance_SnpRunnerXMLSampleHelper;
DEFINE_SNIPPET(_SnpRunnerXMLSampleHelper) 	

// End, SnpXMLSampleHelper.cpp

