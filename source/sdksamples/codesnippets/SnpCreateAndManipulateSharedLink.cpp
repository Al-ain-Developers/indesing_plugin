//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpCreateAndManipulateSharedLink.cpp $
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
//  
//  Usage rights licenced to Adobe Inc. 1997 - 2010.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// General includes:
#include "LocaleSetting.h"
#include "ILayoutUtils.h"
#include "ISharedContentFacade.h"
#include "ILayoutTarget.h"
#include "IHierarchy.h"
#include "IGeometry.h"
#include "IPageItemTypeUtils.h"
#include "IPathUtils.h"
#include "IPathGeometry.h"
#include "ISpreadList.h"
#include "IDataBase.h"
#include "ILinkManager.h"
// SDK includes:
#include "SDKLayoutHelper.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "TransformUtils.h"
#include "SnipRunLog.h"


/** 
	\li	How to create an internal or external link for rectangle,
	\li	How to check the link type is internal or external,

  	@ingroup sdk_snippet
	@ingroup sdk_layout

 */
class SnpCreateAndManipulateSharedLink 
{
	public:

		/** Create a linked rectangle frame for the given rectangle frame.
			@param sourceRectangleFrameRef reference to the rectangle frame.
			@param outLinkUID reference to the link UID between source and target rectangle frame.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode CreateSharedContentLink(const UIDRef& sourceRectangleFrameRef, UID& outLinkUID);

		
		/** Check the link type for the given rectangle frame.
			@param sourceRectangleFrameRef reference to the rectangle frame.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode CheckLinkType(const UIDRef& sourceRectangleFrameRef);

		/** Return kTrue if the given frame is a rectangle frame, kFalse otherwise.
		@param graphicFrameUIDRef reference to the rectangle frame's kSplineItemBoss object.
		*/
		bool16		IsRectangleFrame(const UIDRef& graphicFrameUIDRef);


	public:

		/** Constructor.
		 */
		SnpCreateAndManipulateSharedLink(){};

		/** Destructor.
		 */
		virtual		~SnpCreateAndManipulateSharedLink(){};
};

/*
*/
/*
*/
ErrorCode SnpCreateAndManipulateSharedLink::CreateSharedContentLink(const UIDRef& sourceRectangleFrameRef, UID& outLinkUID)
{
	ErrorCode result = kFailure;

	do {
		IDataBase* db = nil;
		UIDRef targetRectangleFrameRef;

		K2Vector<PMString> choices;
		choices.push_back(PMString("kCreateInternalLink"));
		choices.push_back(PMString("kCreateExternalLink"));
		Utils<ISnipRunParameterUtils> parameterUtils;

		int32 linkType = parameterUtils->GetChoice("Create internal or external link?", choices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		if(linkType == 0)
		{
			//create a target rectangle for internal link
			InterfacePtr<IHierarchy> hierarchy(sourceRectangleFrameRef, UseDefaultIID());
			ASSERT(hierarchy);
			if (!hierarchy)
			{
				break;
			}
			//get the database of the source rectangle
			db = sourceRectangleFrameRef.GetDataBase();
			UIDRef parentUIDRef = UIDRef(db, hierarchy->GetLayerUID());
			//create a target rectangle frame
			SDKLayoutHelper layoutHelper;
			targetRectangleFrameRef = layoutHelper.CreateRectangleFrame(parentUIDRef, PMRect(10, 10, 100, 100));
		}
		else if (linkType == 1)
		{
			//create a target rectangle for external link
			SDKLayoutHelper layoutHelper;
			UIDRef documentUIDRef = layoutHelper.CreateDocument();
			layoutHelper.OpenLayoutWindow(documentUIDRef);

			InterfacePtr<ISpreadList> spreadList(documentUIDRef, UseDefaultIID());
			if(!spreadList) {
				break;
			}
			UIDRef spreadRef = UIDRef(documentUIDRef.GetDataBase(), spreadList->GetNthSpreadUID(0));
			UIDRef spreadLayerRef = layoutHelper.GetActiveSpreadLayerRef(spreadRef);
			//create a target rectangle 
			targetRectangleFrameRef = layoutHelper.CreateRectangleFrame(spreadLayerRef, PMRect(10, 10, 100, 100));
		}
		else
		{
			//error link type
			SNIPLOG("Error link type!");
			break;
		}
		
		if(Utils<Facade::ISharedContentFacade>()->CanCreateSharedContentLink(sourceRectangleFrameRef, targetRectangleFrameRef) )
		{
			ErrorCode errCode = Utils<Facade::ISharedContentFacade>()->CreateSharedContentLink(sourceRectangleFrameRef, targetRectangleFrameRef, outLinkUID);
			if(errCode != kSuccess)
			{
				break;
			}

			result = kSuccess;
		}
	} while(kFalse);
	
	return result;
}


/*
*/
ErrorCode SnpCreateAndManipulateSharedLink::CheckLinkType(const UIDRef& sourceRectangleFrameRef)
{
	ErrorCode result = kFailure;

	do
	{
		//Returns the ILink UIDRef of Shared Content link object passed
		UIDRef linkUIDRef = Utils<Facade::ISharedContentFacade>()->GetLinkForSharedContentLinkObject(sourceRectangleFrameRef);

		IDataBase* db = sourceRectangleFrameRef.GetDataBase();
		if(db == nil)
		{
			break;
		}

		InterfacePtr<const ILinkManager> linkManager(db, db->GetRootUID(), UseDefaultIID());
		InterfacePtr<ILink> link(linkManager->QueryLinkByUID(linkUIDRef.GetUID() ) );

		if(link == nil)
		{
			break;
		}

		//Checks if the link is a shared content link. 
		if(Utils<Facade::ISharedContentFacade>()->IsSharedContentLink(link) )
		{
			//Checks if the link is a shared content internal link. 
			if(Utils<Facade::ISharedContentFacade>()->IsSharedContentInternalLink(link))
			{
				SNIPLOG("This is an internal link!");
			}
			//Checks if the link is a shared content external link. 
			else if(Utils<Facade::ISharedContentFacade>()->IsSharedContentExternalLink(link))
			{
				SNIPLOG("This is an external link!");
			}
			else
			{
				SNIPLOG("No link or unknown link type!");
			}
			result = kSuccess;
		}

	}while(false);

	return result;
}
/*
*/
bool16 SnpCreateAndManipulateSharedLink::IsRectangleFrame(const UIDRef& graphicFrameUIDRef)
{
	bool16 result = kFalse;
	do
	{
		Utils<IPageItemTypeUtils> pageItemTypeUtils;
		InterfacePtr<IPathGeometry> pathGeometry(graphicFrameUIDRef, UseDefaultIID());
		if (pathGeometry == nil)
		{
			ASSERT(pathGeometry);
			break;
		}

		PMPageItemType pathType = Utils<IPathUtils>()->WhichKindOfPageItem(pathGeometry);
		
		if(pathType == kIsRectangle)
		{
			result = kTrue;
		}

	}while(false);

	return result;
}


// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

class _SnpRunnerCreateAndManipulateSharedLink : public SnpRunnable
{
	public:
		// SnippetRunner framework hooks.

		/** Constructor.
		 */
		_SnpRunnerCreateAndManipulateSharedLink();

		/** Destructor.
		 */
		virtual				~_SnpRunnerCreateAndManipulateSharedLink();

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

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

/* Constructor.
*/
_SnpRunnerCreateAndManipulateSharedLink::_SnpRunnerCreateAndManipulateSharedLink() : SnpRunnable("CreateAndManipulateSharedLink")
{
	this->SetDescription("Munipulate the link for page item, for example rectangle");
	this->SetPreconditions("Rectangle frame is selected");
	this->SetCategories("sdk_snippet, sdk_layout");
}

/* Destructor.
*/
_SnpRunnerCreateAndManipulateSharedLink::~_SnpRunnerCreateAndManipulateSharedLink()
{
}

/*
*/
bool16	_SnpRunnerCreateAndManipulateSharedLink::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {
		InterfacePtr<ILayoutTarget> layoutTarget(runnableContext, UseDefaultIID());
		if (!layoutTarget) {
			break;
		}
		UIDList itemList = layoutTarget->GetUIDList(kStripStandoffs);
		if (itemList.Length() != 1) {
			break;
		}
		SnpCreateAndManipulateSharedLink instance;
		if (instance.IsRectangleFrame(itemList.GetRef(0)) == kFalse) {
			break;
		}

		result = kTrue;
	} while(false);
	return result;
}

/*
*/
ErrorCode _SnpRunnerCreateAndManipulateSharedLink::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;
	do {
		SnpCreateAndManipulateSharedLink instance;
		// Find the selected rectangle frame.
		InterfacePtr<ILayoutTarget> layoutTarget(runnableContext, UseDefaultIID());
		if (!layoutTarget) {
			break;
		}
		UIDList itemList = layoutTarget->GetUIDList(kStripStandoffs);
		if (itemList.Length() != 1) {
			break;
		}
		UIDRef graphicFrameUIDRef = itemList.GetRef(0);
		if (instance.IsRectangleFrame(graphicFrameUIDRef) == kFalse) {
			break;
		}

		// Find the rectangle frame manipluation to be performed.
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		choices.push_back(PMString("CreateShareContentLink"));
		choices.push_back(PMString("CheckLinkType"));
		

		enum {kCreateShareContentLink, 
			  kCheckLinkType};

		int32 choice  = parameterUtils->GetChoice("operation?", choices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		// Apply the manipulation.
		switch (choice)
		{
		case kCreateShareContentLink:
			{
				UID linkUID;
				status = instance.CreateSharedContentLink(graphicFrameUIDRef, linkUID);
				break;
			}
		case kCheckLinkType:
			{
				status = instance.CheckLinkType(graphicFrameUIDRef);
				break;
			}
		default:
			{
				break;
			}
		}

		status = kSuccess;
	} while(false);

	return status;
}
/*	Declare an instance to register the snippet with the framework.
*/
_SnpRunnerCreateAndManipulateSharedLink instance_SnpRunnerCreateAndManipulateSharedLink;

// End, SnpCreateAndManipulateSharedLink.cpp
