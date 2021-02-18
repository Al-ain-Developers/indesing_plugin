//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpManipulateArticles.cpp $
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
#include "ILayoutUIUtils.h"
#include "ILayoutTarget.h"
#include "IDocument.h"
#include "IArticleList.h"
#include "IArticleFacade.h"
#include "IArticleMemberList.h"
#include "IStringData.h"
#include "IPageItemNameFacade.h"

// General includes:
#include "Utils.h"
#include "KeyValuePair.h"
#include "K2Vector.h"
#include "K2Vector.tpp"
#include "UIDList.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/** 
	\li How to retrieve articles for a document,
	\li How to retrieve articles to which a page item belongs,
	\li How to add page items to existing articles,
	\li How to create new articles and add page items to them,
	\li How to remove page items from articles.	

	@ingroup sdk_snippet

 */
class SnpManipulateArticles
{
	public:
		/** Article UID and name mapping.
		*/
		typedef KeyValuePair< UID, PMString > ArticleInfo;
		typedef K2Vector< ArticleInfo > ArticleList;

		/** Constructor.
		*/
		SnpManipulateArticles() {}

		/** Destructor.
		*/
		virtual ~SnpManipulateArticles() {}

		/** Lists articles for a document.

			@param doc The document.
			@returns kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode ListArticles(IDocument* doc);

		/** Lists articles for specified page items.

			@param doc The document to which page items belong.
			@param layoutTarget ILayoutTarget for retrieving selected page items.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode ListArticlesForPageItems(IDocument* doc, ILayoutTarget* layoutTarget);

		/** Adds selected page items to an existing article.
		
			@param doc The document to which page items belong.
			@param layoutTarget ILayoutTarget for retrieving selected page items.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode AddToExistingArticle(IDocument* doc, ILayoutTarget* layoutTarget);

		/** Creates a new article and add selected page items to it.

			@param doc The document to which page items belong.
			@param layoutTarget ILayoutTarget for retrieving selected page items.
			@param articleName Name for the new article.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode AddToNewArticle(IDocument* doc, ILayoutTarget* layoutTarget, const PMString& articleName);

		/** Removes selected page items from an article.

			@param doc The document to which page items belong.
			@param layoutTarget ILayoutTarget for retrieving selected page items.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode RemoveFromArticle(IDocument* doc, ILayoutTarget* layoutTarget);

	private:

		/** Retrieves article list for the given document.
		
			@param doc The document whose article list is to be retrieved.
			@param articles The article list for the document.			
		*/
		void GetArticleList(const IDocument* doc, ArticleList& articles);

		/** Retrieves article list for the page item specified by the given UID.
		
			@param doc The document to which the page item belongs.
			@param uid UID of the page item whose article list is to be retrieved.
		*/
		void GetArticleList(const IDocument* doc, const UID& uid, ArticleList& articleList);

		/** Lists articles for a given page item.

			@param doc The document to which toe page item belongs.
			@param uid UID of the page item.			
		*/
		void ListArticlesForPageItem(IDocument* doc, const UID& uid);
};

ErrorCode SnpManipulateArticles::ListArticles(IDocument* doc)
{
	ErrorCode result = kFailure;
	do {
		PMString docName;
		doc->GetName(docName);

		SNIPLOG("Document %s has the following articles:", docName.GetPlatformString().c_str());

		ArticleList articleList;
		GetArticleList(doc, articleList);

		for (ArticleList::const_iterator it = articleList.begin(); it != articleList.end(); it++)
		{
			ArticleInfo info = *it;
			const PMString& name = info.Value();
			SNIPLOG("%s", name.GetPlatformString().c_str());
		}

		result = kSuccess;
	} while(false);

	return result;
}

ErrorCode SnpManipulateArticles::ListArticlesForPageItems(IDocument* doc, ILayoutTarget* layoutTarget)
{
	ErrorCode result = kFailure;

	do {		
		if (layoutTarget == nil)
		{
			SNIPLOG("No page item selected!");
			break;
		}
		UIDList uidList = layoutTarget->GetUIDList(kStripStandoffs);
		for (int32 i = 0; i < uidList.Length(); i++)
		{
			ListArticlesForPageItem(doc, uidList[i]);
		}

		result = kSuccess;
	} while(false);

	return result;
}

ErrorCode SnpManipulateArticles::AddToExistingArticle(IDocument* doc, ILayoutTarget* layoutTarget)
{
	ErrorCode result = kFailure;

	do {		
		if (layoutTarget == nil)
		{
			SNIPLOG("No page item selected!");
			break;
		}
		ArticleList articleList;
		GetArticleList(doc, articleList);
		if (articleList.empty())
		{
			SNIPLOG("No article.");
			break;
		}

		UIDList uidList = layoutTarget->GetUIDList(kStripStandoffs);

		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		
		K2Vector<UID> articleUIDList;
		for (ArticleList::const_iterator it = articleList.begin(); it != articleList.end(); it++)
		{
			ArticleInfo info = *it;
			UID& uid = info.Key();
			PMString& name = info.Value();
			articleUIDList.push_back(uid);
			choices.push_back(name);
		}

		int32 choice = parameterUtils->GetChoice("Add to which article?", choices);
		if (parameterUtils->WasDialogCancelled())
		{
			result = kCancel;
			break;
		}

		UID articleUID = articleUIDList[choice];

		result = Utils<Facade::IArticleFacade>()->AddMembers(UIDRef(uidList.GetDataBase(), articleUID), uidList);		
	} while(false);

	return result;
}

ErrorCode SnpManipulateArticles::AddToNewArticle(IDocument* doc, ILayoutTarget* layoutTarget, const PMString& articleName)
{
	ErrorCode result = kFailure;

	do {
		UIDRef docRef = ::GetUIDRef(doc);
		IDataBase* db = docRef.GetDataBase();
		UID articleUID = Utils<Facade::IArticleFacade>()->CreateArticle(db, articleName);
		result = Utils<Facade::IArticleFacade>()->AddArticle(UIDList(db, articleUID));
		if (result != kSuccess)
		{
			SNIPLOG("Error adding article.");
			break;
		}

		if (layoutTarget != nil)
		{
			UIDList uidList = layoutTarget->GetUIDList(kStripStandoffs);
			result = Utils<Facade::IArticleFacade>()->AddMembers(UIDRef(db, articleUID), uidList);		
		}
	} while(false);

	return result;
}

ErrorCode SnpManipulateArticles::RemoveFromArticle(IDocument* doc, ILayoutTarget* layoutTarget)
{
	ErrorCode result = kFailure;

	do {		
		if (layoutTarget == nil)
		{
			SNIPLOG("No page item selected!");
			break;
		}

		UIDList targetUIDList = layoutTarget->GetUIDList(kStripStandoffs);
		UID targetUID = targetUIDList[0];

		ArticleList articleList;
		GetArticleList(doc, targetUID, articleList);

		if (articleList.empty())
		{
			SNIPLOG("No article.");
			break;
		}		

		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		
		K2Vector<UID> articleUIDList;
		for (ArticleList::const_iterator it = articleList.begin(); it != articleList.end(); it++)
		{
			ArticleInfo info = *it;
			UID& uid = info.Key();
			PMString& name = info.Value();
			articleUIDList.push_back(uid);
			choices.push_back(name);
		}

		int32 choice = parameterUtils->GetChoice("Remove from which article?", choices);
		if (parameterUtils->WasDialogCancelled())
		{
			result = kCancel;
			break;
		}

		UID articleUID = articleUIDList[choice];
		
		result = Utils<Facade::IArticleFacade>()->RemoveMembers(UIDRef(targetUIDList.GetDataBase(), articleUID), UIDList(targetUIDList.GetDataBase(), targetUID));		
	} while(false);

	return result;
}

void SnpManipulateArticles::GetArticleList(const IDocument* doc, ArticleList& articles)
{
	UIDRef docUIDRef = ::GetUIDRef(doc);
	IDataBase* db = docUIDRef.GetDataBase();
	InterfacePtr<IArticleList> articleList(doc, UseDefaultIID());

	if (articleList != nil)
	{
		const int32 articleCount = articleList->CountArticles();
		for (int32 i = 0; i < articleCount; i++)
		{
			UID uid = articleList->GetNthArticleUID(i);
			InterfacePtr<IStringData> articleName(db, uid, IID_IARTICLENAME);
			const PMString& name = articleName->GetString();
			ArticleInfo info(uid, name);
			articles.push_back(info);				
		}
	}
}

void SnpManipulateArticles::GetArticleList(const IDocument* doc, const UID& uid, ArticleList& articleList)
{
	GetArticleList(doc, articleList);

	UIDRef docUIDRef = ::GetUIDRef(doc);
	IDataBase* db = docUIDRef.GetDataBase();

	for (ArticleList::iterator it = articleList.begin(); it != articleList.end();)
	{
		ArticleInfo info = *it;
		UID& articleUID = info.Key();
		InterfacePtr<IArticleMemberList> memberList(db, articleUID, IID_IARTICLEMEMBERLIST);

		int32 index = memberList->GetMemberPosition(uid);
		if (index < 0)
		{
			it = articleList.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void SnpManipulateArticles::ListArticlesForPageItem(IDocument* doc, const UID& uid)
{
	ArticleList articleList;
	GetArticleList(doc, uid, articleList);

	UIDRef docUIDRef = ::GetUIDRef(doc);
	IDataBase* db = docUIDRef.GetDataBase();

	PMString pageItemName = Utils<Facade::IPageItemNameFacade>()->GetDefaultPageItemName(UIDRef(db, uid));
	pageItemName.Translate();

	SNIPLOG("<%s> UID:0x%x belongs to the following articles:", pageItemName.GetPlatformString().c_str(), uid.Get());
	for (ArticleList::const_iterator it = articleList.begin(); it != articleList.end(); it++)
	{
		ArticleInfo info = *it;
		PMString& name = info.Value();
		SNIPLOG("%s", name.GetPlatformString().c_str());
	}
}

// --------------------------------- SnippetRunner framework hook ---------------------------------------------------

/** Makes the snippet SnpManipulateArticles available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerManipulateArticles : public SnpRunnable
{
	public:
		/** Constructor.
		 */
		_SnpRunnerManipulateArticles();

		/** Destructor.
		 */
		virtual			~_SnpRunnerManipulateArticles();

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

	private:

		/** Returns different choices based on the current selection.

			@param layoutTarget ILayoutTarget for retrieving selected page items.
			@param choices Labels for the choice items in the dialog.
			@param choiceTypes enum type for the choice items in the dialog.
		*/
		void GetChoices(ILayoutTarget* layoutTarget, K2Vector<PMString>& choices, K2Vector<int32>& choiceTypes);

	private:

		enum {kListArticles, kListArtclesForPageItem, kAddToArticle, kAddToNewArticle, kRemoveFromArticle};

};

/* Describe your snippet to the framework here.
*/
_SnpRunnerManipulateArticles::_SnpRunnerManipulateArticles() : SnpRunnable("ManipulateArticles")
{
	this->SetDescription("Provides a ManipulateArticles");
	this->SetPreconditions("none");
	this->SetCategories("sdk_snippet");
}

/* Destructor.
*/
_SnpRunnerManipulateArticles::~_SnpRunnerManipulateArticles()
{
}

/* Check if your snippet's preconditions are met here.
*/
bool16	_SnpRunnerManipulateArticles::CanRun(ISnpRunnableContext* runnableContext)
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
ErrorCode _SnpRunnerManipulateArticles::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		K2Vector<int32> choiceTypes;

		InterfacePtr<ILayoutTarget> layoutTarget(runnableContext, UseDefaultIID());

		GetChoices(layoutTarget, choices, choiceTypes);

		int32 choice = parameterUtils->GetChoice("What action to take?", choices);		
		if (parameterUtils->WasDialogCancelled())
		{
			break;
		}

		SnpManipulateArticles instance;
		IDocument* doc = Utils<ILayoutUIUtils>()->GetFrontDocument();

		choice = choiceTypes[choice];
		switch (choice)
		{
		case kListArticles:
			status = instance.ListArticles(doc);
			break;

		case kListArtclesForPageItem:
			status = instance.ListArticlesForPageItems(doc, layoutTarget);
			break;

		case kAddToArticle:
			status = instance.AddToExistingArticle(doc, layoutTarget);
			break;

		case kAddToNewArticle:
			{
				PMString articleName = parameterUtils->GetPMString("Name of the new article", "New Article");
				if (!parameterUtils->WasDialogCancelled())
				{
					status = instance.AddToNewArticle(doc, layoutTarget, articleName);
				}
			
				break;
			}

		case kRemoveFromArticle:
			status = instance.RemoveFromArticle(doc, layoutTarget);
			break;
		default:
			break;
		}
	} while(false);
	return (status);
}

void _SnpRunnerManipulateArticles::GetChoices(ILayoutTarget* layoutTarget, K2Vector<PMString>& choices, K2Vector<int32>& choiceTypes)
{
	choices.push_back(PMString("List Articles in the document"));
	choiceTypes.push_back(kListArticles);

	UIDList::size_type size = 0;
	if (layoutTarget)
	{
		UIDList targetList = layoutTarget->GetUIDList(kStripStandoffs);
		size = targetList.size();
	}

	if (size > 0)
	{
		choices.push_back(PMString("List Articles for selected page item(s)"));
		choices.push_back(PMString("Add selected page item(s) to an article"));
		choices.push_back(PMString("Add selected page item(s) to a new article"));
		choiceTypes.push_back(kListArtclesForPageItem);
		choiceTypes.push_back(kAddToArticle);
		choiceTypes.push_back(kAddToNewArticle);
	}
	
	if (size == 1)
	{
		choices.push_back(PMString("Remove selected page item from an article"));
		choiceTypes.push_back(kRemoveFromArticle);
	}
}
/*	Declare an instance to register the snippet hook with the framework.
*/
static _SnpRunnerManipulateArticles instance_SnpRunnerManipulateArticles;
DEFINE_SNIPPET(_SnpRunnerManipulateArticles) 	

// End, SnpManipulateArticles.cpp

