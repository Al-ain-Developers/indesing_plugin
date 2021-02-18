//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpCreateCrossReference.cpp $
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
#include "ILayoutUIUtils.h"
#include "IDocument.h"
#include "IStoryList.h"
#include "IItemLockData.h"
#include "ITextModel.h"
#include "IAttributeStrand.h"
#include "IComposeScanner.h"
#include "ITextFocus.h"
#include "ITextTarget.h"
#include "IHyperlinkTable.h"
#include "IXRefFormat.h"
#include "IHyperlinkTextDestinationData.h"
#include "IHyperlinkDestination.h"
#include "IHyperlinkFacade.h"

// General includes:
#include "Utils.h"

// SDK includes:
#include "SDKLayoutHelper.h"
#include "K2Vector.h"
#include "K2Vector.tpp"

// Framework includes:
#include "SnpRunnable.h"
#include "SnipRunLog.h"
#include "ISnipRunParameterUtils.h"

/** \li How to create a cross-reference by hyperlink infrastructure
	\li How to get paragraph list in a document 
	\li How to get anchor list in a document 

	@ingroup sdk_snippet
	@ingroup sdk_text

  	@see IXRefFormat
	@see IHyperlinkTable	
	@see IHyperlinkDestination
	@see IHyperlinkFacade

 */
class SnpCreateCrossReference
{
public:
	
	/** a simple data structure to save paragraph data.
	*/
	struct ParaData
	{
		UID storyUID;		//UID of the story
		int32 start;		//start of text index
		int32 span;			//span of text
		WideString text;	//context
		typedef object_type data_type;					
	};
	
	/** a simple data structure to save anchor data.
	*/
	struct AnchorData
	{	
		UID anchorUID;		//UID of the anchor	
		PMString text;		//context
		typedef object_type data_type;					
	};
	
	/** a simple data structure to save XRefFormatData	 data.
	*/
	struct XRefFormatData
	{	
		UID xrefFormatUID;		//UID of the XRefFormat			
		PMString formatName;	//Name of format		
		typedef object_type data_type;					
	};
	
	
	/** 
	 get the anchor list
	 @param db see IDatabase for documentation.
	 @param allAnchors the list of anchor data.
	 */	
	void GetAnchorList(IDataBase* db, K2Vector<AnchorData>& allAnchors);
	
	/** 
	 get the paragraph list
	 @param db see IDatabase for documentation.
	 @param allParagraphs the list of paragrahs data.
	 */
	void GetParagraphList(IDataBase* db, K2Vector<ParaData>& allParagraphs);
	
	/** 
	 get the xRefFormatList list
	 @param db see IDatabase for documentation.
	 @param xRefFormatList the list of XRefFormat data.
	 */
	void GetXRefFormatList(IDataBase* db, K2Vector<XRefFormatData>& xRefFormatList);

};

/* GetAnchorList
*/
void SnpCreateCrossReference::GetAnchorList(IDataBase* db, K2Vector<AnchorData>& allAnchors)
{	
	do
	{	
		if(db == nil)
		{
			ASSERT_FAIL("db is nil!");
			break;	
		}
	
		//get the hyperlink table
		InterfacePtr<IHyperlinkTable> hyperlinkTable(db, db->GetRootUID(), IID_IHYPERLINKTABLE);
		if(hyperlinkTable == nil)
		{
			ASSERT_FAIL("hyperlinkTable is nil!");
			break;	
		}
		UniqueKeyToUIDMap::const_iterator first = hyperlinkTable->GetDestinationKeyToUIDMapBeginIter();
		UniqueKeyToUIDMap::const_iterator last = hyperlinkTable->GetDestinationKeyToUIDMapEndIter();

		for(; first != last; ++first)
		{
			UID destUID = first->second;

			//get the text destination data
			InterfacePtr<IHyperlinkTextDestinationData> textDestData(db, destUID, UseDefaultIID());
			if(textDestData && !textDestData->IsParagraphDestination())
			{
				AnchorData anchorData;
				InterfacePtr<IHyperlinkDestination> hyperlinkDest(textDestData, UseDefaultIID());
				hyperlinkDest->GetName(&(anchorData.text));
				anchorData.anchorUID = destUID;
				allAnchors.push_back(anchorData);
			}
		}
	}while(false);
}

/* GetParagraphList
*/
void SnpCreateCrossReference::GetParagraphList(IDataBase* db, K2Vector<ParaData>& allParagraphs)
{	
    do
	{
		//get the story list
		InterfacePtr<const IStoryList> storyList(db, db->GetRootUID(), UseDefaultIID());
		ASSERT(storyList);
		if(storyList == nil)
		{
			break;	
		}
	
		const int32 maxTextLen = 30;
		
		for (int32 i = (storyList->GetUserAccessibleStoryCount() - 1) ; i >= 0; i--)
		{
			const UIDRef storyUID = storyList->GetNthUserAccessibleStoryUID(i);

			InterfacePtr<ITextModel> textModel(storyUID, UseDefaultIID());

			InterfacePtr<IComposeScanner> scanner(textModel, UseDefaultIID());
			const int32 totalLength = textModel->TotalLength();
			//get attribute strand
			InterfacePtr<IAttributeStrand>  paraStrand(static_cast<IAttributeStrand*>(textModel->QueryStrand(kParaAttrStrandBoss, IID_IATTRIBUTESTRAND)));

			TextIndex	paraChunkStart = 0;
			int32		paraChunkLen;

			do
			{
				TextIndex	runBegin;

				//get style uid
				UID styleUID = paraStrand->GetStyleUID(paraChunkStart, &paraChunkLen, &runBegin);
				ASSERT(runBegin == paraChunkStart);
				TextIndex 	subParaStart = paraChunkStart;
				int32		subParaSpan;
				do
				{					
					TextIndex checkStart = scanner->FindSurroundingParagraph(subParaStart, &subParaSpan, kFalse);
					ASSERT(checkStart == subParaStart);
					ParaData paraData;
					paraData.storyUID = storyUID.GetUID();
					paraData.start = subParaStart;
					paraData.span = subParaSpan;
					
					scanner->CopyText(subParaStart, subParaSpan-1, &paraData.text);
					
					//push back the prargraph text
					if(paraData.text.Length() > maxTextLen)
					{
						WideString *subParaData = paraData.text.Substring(0, maxTextLen);
						paraData.text = *subParaData;
						delete subParaData;
						paraData.text.Append(WideString("..."));
					}
					
					if(paraData.text.Length() > 0)
					{
						allParagraphs.push_back(paraData);
					}

					subParaStart += subParaSpan;
				} while (subParaStart < (paraChunkStart + paraChunkLen));
				
				paraChunkStart += paraChunkLen;
			
			} while (paraChunkStart < totalLength);
		}
	}while(false);

}

/* GetXRefFormatList
*/
void SnpCreateCrossReference::GetXRefFormatList(IDataBase* db, K2Vector<XRefFormatData>& xRefFormatList)
{
	do
	{
		if(db == nil)
		{
			ASSERT_FAIL("db is nil!");
			break;	
		}
		
		//get the hyperlink table
		InterfacePtr<IHyperlinkTable> hyperlinkTable(db, db->GetRootUID(), IID_IHYPERLINKTABLE);
		if(hyperlinkTable == nil)
		{			
			ASSERT_FAIL("hyperlinkTable is nil!");
			break;	
		}
		for(int32 i = 0; i < hyperlinkTable->GetXRefFormatCount(); i++)
		{
			//get the nth xref format
			UID uid = hyperlinkTable->GetNthXRefFormat(i);
			InterfacePtr<IXRefFormat> xrefFormat(db, uid, UseDefaultIID());
			if(xrefFormat)
			{
				XRefFormatData xrefFormatData;
				xrefFormatData.formatName = xrefFormat->GetName();
				xrefFormatData.xrefFormatUID = uid;
				xRefFormatList.push_back(xrefFormatData);
			}
		}
	} while (false);
		
}

// --------------------------------- SnippetRunner framework hook ---------------------------------------------------

/** Makes the snippet SnpCreateCrossReference available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpCreateCrossReference : public SnpRunnable
{
public:
	/** This constructor describes your snippet to the framework.
	 */
	_SnpCreateCrossReference();

	/** Destructor.
	 */
	virtual			~_SnpCreateCrossReference();

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
	virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunTextSelectionTargetContext;}


};

/* Constructor.
*/
_SnpCreateCrossReference::_SnpCreateCrossReference() : SnpRunnable("CreateCrossReference")
{
	this->SetDescription("creates a Cross-Reference");
	this->SetPreconditions("some text must be selected");
	this->SetCategories("sdk_snippet, sdk_text");
}

/* Destructor.
*/
_SnpCreateCrossReference::~_SnpCreateCrossReference()
{
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpCreateCrossReference::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		IDocument* document = runnableContext->GetActiveContext()->GetContextDocument();
		IDataBase * db = ::GetDataBase(document);

		InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID());
		if (textTarget == nil) {
			break;
		}
		
		InterfacePtr<ITextFocus> textFocus(textTarget->QueryTextFocus());
		ASSERT(textFocus);
		if (textFocus == nil) {
			break;
		}

		InterfacePtr<ITextModel> textModel(textTarget->QueryTextModel ());
		if (textModel == nil) {
			break;
		}
		UIDRef storyRef = ::GetUIDRef(textModel);
		
		InterfacePtr<IHyperlinkTable> hyperlinkTable(db, db->GetRootUID(), IID_IHYPERLINKTABLE);
		ASSERT(hyperlinkTable);
		if(hyperlinkTable == nil)
			break;
		
		// Get parameters.
		Utils<ISnipRunParameterUtils> parameterUtils;
		
		//Declare variables to use for SnpCreateCrossReference
		SnpCreateCrossReference instance;

		K2Vector<PMString> choices;
		choices.push_back(PMString("Paragraph"));
		choices.push_back(PMString("Text Anchor"));
		int32 choice = (K2::UIFlags)(parameterUtils->GetChoice(PMString("Link To"), choices, 0 ));
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		UIDRef textDestRef = kInvalidUIDRef;
		choices.clear();
		if(choice == 0)
		{			
			//Get paragraph list
			K2Vector<SnpCreateCrossReference::ParaData> allParagraphs;
			instance.GetParagraphList(db, allParagraphs);
			
			for(int32 i = 0; i < allParagraphs.size(); i++)
			{
				choices.push_back(allParagraphs.at(i).text);
			}
			
			if(choices.size() > 0)
			{
				choice = (K2::UIFlags)(parameterUtils->GetChoice(PMString("Paragraph"), choices, 0 ));
				if (parameterUtils->WasDialogCancelled()) {
					break;
				}
				const SnpCreateCrossReference::ParaData& paraData = allParagraphs.at(choice);
				status = Utils<Facade::IHyperlinkFacade>()->CreateParagraphDestination(UIDRef(db, paraData.storyUID), paraData.start, &textDestRef);
				if(status != kSuccess)
					break;
			}
		}
		else if(choice == 1) //text anchor
		{
			
			K2Vector<SnpCreateCrossReference::AnchorData> allAnchors;
			instance.GetAnchorList(db, allAnchors);
		
			for(int32 i = 0; i < allAnchors.size(); i++)
			{
				choices.push_back(allAnchors.at(i).text);
			}
			
			choices.push_back("[None]");
			choice = (K2::UIFlags)(parameterUtils->GetChoice(PMString("Text Anchor"), choices, 0 ));
			if (parameterUtils->WasDialogCancelled()) {
				break;
			}
			
			if(choice >= 0 && choice < allAnchors.size())
			{
				textDestRef = UIDRef(db, allAnchors.at(choice).anchorUID);
			}
		}
		else
		{
			SNIPLOG("Invalid option. Skipping.");
			break;
		}

		choices.clear();

		K2Vector<SnpCreateCrossReference::XRefFormatData> xrefFormat;
		instance.GetXRefFormatList(db, xrefFormat);

		for(int32 i = 0; i < xrefFormat.size(); i++)
		{
			choices.push_back(xrefFormat.at(i).formatName);
		}
		
		choice = (K2::UIFlags)(parameterUtils->GetChoice(PMString("Format"), choices, 0 ));
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		UID xformatUID = xrefFormat.at(choice).xrefFormatUID;

		TextIndex startTextIndex = textFocus->GetStart(nil);
		TextIndex endTextIndex = textFocus->GetEnd();
		
		UIDRef textSourceRef = kInvalidUIDRef;
		status = Utils<Facade::IHyperlinkFacade>()->CreateXRefTextSource(storyRef,
																		startTextIndex,
																		endTextIndex - startTextIndex,
																		xformatUID, 
																		&textSourceRef);
		if(status != kSuccess)
			break;
		
		UIDRef hyperlinkRef;
		status = Utils<Facade::IHyperlinkFacade>()->CreateHyperlink(
															   textSourceRef, 
															   textDestRef, 
															   &hyperlinkRef);

	} while(false);
	
	return (status);
}


/* Check if your preconditions are met.
*/
bool16 _SnpCreateCrossReference::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {		
		InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID());
		if (textTarget == nil) {
			break;
		}
		InterfacePtr<ITextFocus> textFocus(textTarget->QueryTextFocus());
		ASSERT(textFocus);
		if (textFocus == nil) {
			break;
		}
		result = kTrue;
	} while(false);
	return result;
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpCreateCrossReference instance_SnpCreateCrossReference;
DEFINE_SNIPPET(_SnpCreateCrossReference) 	
// End, SnpCreateCrossReference.cpp

