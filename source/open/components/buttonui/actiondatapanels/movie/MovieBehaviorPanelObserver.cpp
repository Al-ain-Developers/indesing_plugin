//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/movie/MovieBehaviorPanelObserver.cpp $
//  
//  Owner: Mark VerMurlen
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

// ----- Interface Includes -----

#include "IBehaviorData.h"
#include "IControlView.h"
#include "IDocument.h"
#include "IDropDownListController.h"
#include "IFormFieldSuite.h"
#include "IHierarchy.h"
#include "IListControlDataOf.h"
#include "IMovieActionData.h"
#include "INamedPageItemList.h"
#include "INavigationPoints.h"
#include "ISelectionUtils.h"
#include "ISpreadDynamicContentMgr.h"
#include "IDynamicTargetsFacade.h"
#include "IStringListControlData.h"
#include "ISubject.h"
#include "ITreeViewController.h"
#include "ITreeViewMgr.h"
#include "IUIDData.h"
#include "IWidgetUtils.h"

// ----- Implementation Includes -----

#include "CBehaviorPanelObserver.h"
#include "K2Pair.h"
#include "K2Vector.tpp"
#include "MovieListElement.h"

#include "BehaviorUIID.h"
#include "BehaviorUIDefs.h"

#include "ErrorUtils.h"
#include "FormFieldUIUtils.h"
#include "Utils.h"
#include "widgetid.h"

//========================================================================================
// CLASS MovieBehaviorPanelObserver
//========================================================================================

class MovieBehaviorPanelObserver : public CBehaviorPanelObserver
{
public:
	MovieBehaviorPanelObserver(IPMUnknown *boss);
	virtual ~MovieBehaviorPanelObserver();

	virtual void 	AutoAttach();
	virtual void 	AutoDetach();

protected:
	virtual void HandleSelectionUpdate
		(
		const ClassID&	inBossClassID, 
		ISubject* inSubject, 
		const PMIID& 	inProtocol,
		void* 			inMessage
		);
	virtual void	InitializeFieldsFromActionData(const IBehaviorData* inActionData);
	virtual bool	ApplyFieldsToActionData(IBehaviorData* inActionData);

private:
	void			LoadMovieChoices(const IBehaviorData* inActionData, IListControlDataOf<MovieListElement>* movieData);
	void			InitializeMovieChoice(const IBehaviorData *inActionData);
	
	void			LoadMovieOpChoices(IListControlDataOf< K2Pair<PMString, int32> >* movieOpData);
	void			InitializeMovieOpChoice(const IBehaviorData *inActionData);

	void			LoadMovieNavPointChoices(const IBehaviorData* inActionData, IListControlDataOf<MovieNavPointListElement>* navPointData);
	void			InitializeMovieNavPointChoice(const IBehaviorData *inActionData);

	void			UpdateBehaviorNode();

	bool	isAttached;
};

//========================================================================================
// METHODS MovieBehaviorPanelObserver
//========================================================================================

CREATE_PMINTERFACE(MovieBehaviorPanelObserver, kMovieBehaviorPanelObserverImpl)

//----------------------------------------------------------------------------------------
// MovieBehaviorPanelObserver constructor 
//----------------------------------------------------------------------------------------

MovieBehaviorPanelObserver::MovieBehaviorPanelObserver(IPMUnknown *boss) :
	CBehaviorPanelObserver(boss),
	isAttached(false)
{
}


//----------------------------------------------------------------------------------------
// MovieBehaviorPanelObserver::~MovieBehaviorPanelObserver
//----------------------------------------------------------------------------------------

MovieBehaviorPanelObserver::~MovieBehaviorPanelObserver()
{
}

//----------------------------------------------------------------------------------------
// MovieBehaviorPanelObserver::AutoAttach
//----------------------------------------------------------------------------------------

void MovieBehaviorPanelObserver::AutoAttach()
{
	if ( ! isAttached ) {
		
		CBehaviorPanelObserver::AutoAttach();
		
		AttachToWidget(kMovieWidgetID, IID_ISTRINGLISTCONTROLDATA);
		AttachToWidget(kOperationWidgetID, IID_ISTRINGLISTCONTROLDATA);
		AttachToWidget(kMovieNavPointWidgetID, IID_ISTRINGLISTCONTROLDATA);
	
		isAttached = true;
	}
}

//----------------------------------------------------------------------------------------
// MovieBehaviorPanelObserver::AutoDetach
//----------------------------------------------------------------------------------------

void MovieBehaviorPanelObserver::AutoDetach()
{
	if ( isAttached ) {
		
		CBehaviorPanelObserver::AutoDetach();
		
		DetachFromWidget(kMovieWidgetID, IID_ISTRINGLISTCONTROLDATA);
		DetachFromWidget(kOperationWidgetID, IID_ISTRINGLISTCONTROLDATA);
		DetachFromWidget(kMovieNavPointWidgetID, IID_ISTRINGLISTCONTROLDATA);
		
		isAttached = false;
	}
}

//----------------------------------------------------------------------------------------
// MovieBehaviorPanelObserver::HandleSelectionUpdate
//----------------------------------------------------------------------------------------

void MovieBehaviorPanelObserver::HandleSelectionUpdate
	(
	const ClassID&	inBossClassID, 
	ISubject* inSubject, 
	const PMIID& 	inProtocol,
	void* 			inMessage
	)
{
	InterfacePtr<IFormFieldSuite> iFormSuite( FormFieldUIUtils::QueryFormSuite() );
	
	if ( iFormSuite && !iFormSuite->IsDefaultSelection() && iFormSuite->IsFieldSelection() )
	{
		if ( inProtocol == IID_ISTRINGLISTCONTROLDATA )
		{
			CBehaviorPanelObserver::HandleSelectionUpdate(inBossClassID, inSubject, inProtocol, inMessage);
		}
		else
		{
			InitializeFieldsFromActionData(nil);
		}
		return;
	}

	ActiveSelectionObserver::HandleSelectionUpdate(inBossClassID, inSubject, inProtocol, inMessage);
}

//----------------------------------------------------------------------------------------
// MovieBehaviorPanelObserver::InitializeFieldsFromActionData
//----------------------------------------------------------------------------------------

void MovieBehaviorPanelObserver::InitializeFieldsFromActionData(const IBehaviorData* inActionData)
{
	if ( inActionData )
	{
		InitializeMovieChoice(inActionData);
		InitializeMovieOpChoice(inActionData);
		InitializeMovieNavPointChoice(inActionData);
	}
	else
	{
		InterfacePtr<IUIDData> activeBehavior(FormFieldUIUtils::QueryActiveBehavior());
		if ( activeBehavior )
		{
			InterfacePtr<IBehaviorData> iBehaviorData(activeBehavior->GetRef(), UseDefaultIID());
			if ( iBehaviorData )
				InitializeFieldsFromActionData(iBehaviorData);
		}
	}
}

//----------------------------------------------------------------------------------------
// MovieBehaviorPanelObserver::InitializeFieldsFromActionData
//----------------------------------------------------------------------------------------

bool MovieBehaviorPanelObserver::ApplyFieldsToActionData(IBehaviorData* inActionData)
{
	IMovieActionData* actionData = static_cast<IMovieActionData*>(inActionData);
	
	// Movie
	InterfacePtr<IDropDownListController> movieChoice((IDropDownListController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kMovieWidgetID, IID_IDROPDOWNLISTCONTROLLER));
	InterfacePtr< IListControlDataOf<MovieListElement> > movieData(movieChoice, IID_ILISTCONTROLDATA);
	int32 selection = movieChoice->GetSelected();

	bool bChanged(false), bChangedMovie(false), bChangedToPlayFromNavPoint(false);

	if (selection != IDropDownListController::kNoSelection)
	{
		if ( actionData->GetMovie() != (*movieData)[selection].GetMovieRef().GetUID() )
		{
			bChangedMovie = bChanged = true;
			actionData->SetMovie((*movieData)[selection].GetMovieRef().GetUID());
			actionData->SetNavigationPointID(INavigationPoints::kInvalidNavigationPointId);
			this->UpdateBehaviorNode();
		}
	}
	else if ( actionData->GetMovie() != kInvalidUID )
	{
		bChanged = true;
		actionData->SetMovie(kInvalidUID);
		actionData->SetNavigationPointID(INavigationPoints::kInvalidNavigationPointId);
		this->UpdateBehaviorNode();
	}

	// Operation
	InterfacePtr<IDropDownListController> operationChoice((IDropDownListController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kOperationWidgetID, IID_IDROPDOWNLISTCONTROLLER));
	InterfacePtr< IListControlDataOf< K2Pair<PMString, int32> > > operationData(operationChoice, IID_ILISTCONTROLDATA);
	
	if ( actionData->GetOperation() != (IMovieActionData::Operation) (*operationData)[operationChoice->GetSelected()].second )
	{
		bChanged = true;
		bChangedToPlayFromNavPoint = (IMovieActionData::Operation) (*operationData)[operationChoice->GetSelected()].second == IMovieActionData::kPlayFromNavigationPoint;
		actionData->SetOperation((IMovieActionData::Operation) (*operationData)[operationChoice->GetSelected()].second);
		actionData->SetNavigationPointID(INavigationPoints::kInvalidNavigationPointId);
	}

	if (!bChanged)
	{
		// perhaps Navigation Point
		InterfacePtr<IDropDownListController> navPointChoice((IDropDownListController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kMovieNavPointWidgetID, IID_IDROPDOWNLISTCONTROLLER));
		InterfacePtr< IListControlDataOf<MovieNavPointListElement> > navPointData(navPointChoice, IID_ILISTCONTROLDATA);
		int32 selectedNavPt = navPointChoice->GetSelected();

		if (selectedNavPt != IDropDownListController::kNoSelection)
		{
			if ( actionData->GetNavigationPointID() != (*navPointData)[selectedNavPt].second )
			{
				bChanged = true;
				actionData->SetNavigationPointID((*navPointData)[selectedNavPt].second);
			}
		}
		else if ( actionData->GetNavigationPointID() != INavigationPoints::kInvalidNavigationPointId )
		{
			bChanged = true;
			actionData->SetNavigationPointID(INavigationPoints::kInvalidNavigationPointId);
		}
	}
	else if ((bChangedMovie && actionData->GetOperation() == IMovieActionData::kPlayFromNavigationPoint) ||
		(bChangedToPlayFromNavPoint && selection != IDropDownListController::kNoSelection))
	{
		// Target object changed OR operation changed to Play from Nav Point.
		// Default to first navigation point.
		InterfacePtr<INavigationPoints> navPoints((*movieData)[selection].GetMovieRef(), UseDefaultIID());
		if (navPoints && navPoints->GetNumberOfNavigationPoints() > 0)
		{
			INavigationPoints::NavigationPoint navPoint;
			navPoints->GetNthNavigationPoint(0, navPoint);
			actionData->SetNavigationPointID(navPoint.fId);
		}
	}
	return bChanged;
}

//----------------------------------------------------------------------------------------
// MovieBehaviorPanelObserver::LoadMovieChoices
//----------------------------------------------------------------------------------------

void MovieBehaviorPanelObserver::LoadMovieChoices(const IBehaviorData* inActionData, IListControlDataOf<MovieListElement>* movieData)
{	
	movieData->Clear();

	if (!inActionData) return;

	IDataBase *db = ::GetDataBase(inActionData);
	InterfacePtr<IHierarchy /*const*/> pageitem(db, inActionData->GetOwner(), UseDefaultIID());
	
	if (pageitem)
	{
		const bool kIncludeMasterItems = true;
		std::vector<UID> itemList;
		if (Utils<Facade::IDynamicTargetsFacade> ()->GetTargetList (UIDRef (db, inActionData->GetOwner()), ISpreadDynamicContentMgr::kMovieItemType, itemList, kIncludeMasterItems))
		{
			for (std::vector<UID>::const_iterator i = itemList.begin(), end = itemList.end(); i != end; ++i)
			{
				movieData->Add(MovieListElement(UIDRef(db, *i)));
			}
		}

		if (movieData->Length() == 0)
			movieData->Add(MovieListElement(UIDRef::gNull));
	}
}

//----------------------------------------------------------------------------------------
// MovieBehaviorPanelObserver::InitializeMovieChoice
//----------------------------------------------------------------------------------------

void MovieBehaviorPanelObserver::InitializeMovieChoice(const IBehaviorData *inActionData)
{
	InterfacePtr<IDropDownListController> movieChoice((IDropDownListController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kMovieWidgetID, IID_IDROPDOWNLISTCONTROLLER));
	InterfacePtr< IListControlDataOf<MovieListElement> > movieData(movieChoice, IID_ILISTCONTROLDATA);
	
	LoadMovieChoices(inActionData, movieData);
	
	bool bUpdated = false;
	if (inActionData ==0)
	{
		if (movieData->Length() > 0)
		{
			bUpdated = true;
			movieChoice->Select(0, kTrue, kFalse);
		}
	}
	else
	{
		InterfacePtr<IMovieActionData> behaviorData(inActionData, UseDefaultIID());
		for (int32 i = 0; i < movieData->Length(); i++)
		{
			if ((*movieData)[i].GetMovieRef().GetUID() == behaviorData->GetMovie())
			{
				bUpdated = true;
				if ( !movieChoice->IsSelected(i) )
					movieChoice->Select(i, kTrue, kFalse);
				break;
			}
		}
	}

	if ( !bUpdated )
	{
		movieChoice->Deselect(kTrue, kFalse);
#ifdef DEBUG
		InterfacePtr<IMovieActionData const> behaviorData(inActionData, UseDefaultIID());
		if (behaviorData != nil && behaviorData->GetMovie() != kInvalidUID)
			ASSERT_FAIL(FORMAT_ARGS("Button has a movie target (uid %d) that is not on the same spread!", behaviorData->GetMovie().Get()));
#endif
	}
}

//----------------------------------------------------------------------------------------
// MovieBehaviorPanelObserver::LoadMovieOpChoices
//----------------------------------------------------------------------------------------

void MovieBehaviorPanelObserver::LoadMovieOpChoices(IListControlDataOf< K2Pair<PMString, int32> >* movieOpData)
{	
	if ( movieOpData->Length() != 4 )
	{
		movieOpData->Clear();
		
		movieOpData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/Movie/Play", IMovieActionData::kPlay));
		movieOpData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/Movie/Stop", IMovieActionData::kStop));
		movieOpData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/Movie/Pause", IMovieActionData::kPause));
		movieOpData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/Movie/Resume", IMovieActionData::kResume));
		movieOpData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/Movie/PlayFromNavPoint", IMovieActionData::kPlayFromNavigationPoint));
		//movieOpData->Add(K2Pair<PMString, int32>("$$$/Dialog/Behaviors/Movie/StopAll", IMovieActionData::kStopAll));
	}
}

//----------------------------------------------------------------------------------------
// MovieBehaviorPanelObserver::InitializeMovieOpChoice
//----------------------------------------------------------------------------------------

void MovieBehaviorPanelObserver::InitializeMovieOpChoice(const IBehaviorData *inActionData)
{
	InterfacePtr<IDropDownListController> operationChoice((IDropDownListController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kOperationWidgetID, IID_IDROPDOWNLISTCONTROLLER));
	InterfacePtr< IListControlDataOf< K2Pair<PMString, int32> > > operationData(operationChoice, IID_ILISTCONTROLDATA);
	
	LoadMovieOpChoices(operationData);
	
	bool bUpdated = false;

	if (inActionData == 0)
	{
		if (operationData->Length() > 0)
		{
			bUpdated = true;
			operationChoice->Select(0, kTrue, kFalse);
		}
	}
	else
	{
		InterfacePtr<IMovieActionData> actionData(inActionData, UseDefaultIID());
		for (int32 i = 0; i < operationData->Length(); i++)
		{
			if ((*operationData)[i].second == actionData->GetOperation())
			{
				bUpdated = true;
				if ( !operationChoice->IsSelected(i) )
					operationChoice->Select(i, kTrue, kFalse);
				break;
			}
		}
		
		//bool isStopAll = (actionData->GetOperation() == IMovieActionData::kStopAll);
		//InterfacePtr<IControlView> targetChoice((IControlView *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kMovieWidgetID, IID_ICONTROLVIEW));		
		//targetChoice->Enable(!isStopAll);

		bool isPlayFromNavPt = (actionData->GetOperation() == IMovieActionData::kPlayFromNavigationPoint);
		InterfacePtr<IControlView> navPointChoice((IControlView *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kMovieNavPointWidgetID, IID_ICONTROLVIEW));		
		navPointChoice->Enable(isPlayFromNavPt);
	}

	if ( !bUpdated )
		operationChoice->Deselect(kTrue, kFalse);

	ASSERT(operationChoice->GetSelected() != IDropDownListController::kNoSelection);
}

//----------------------------------------------------------------------------------------
// MovieBehaviorPanelObserver::LoadMovieNavPointChoices
//----------------------------------------------------------------------------------------

void MovieBehaviorPanelObserver::LoadMovieNavPointChoices(const IBehaviorData* inActionData, IListControlDataOf<MovieNavPointListElement>* navPointData)
{	
	navPointData->Clear();

	InterfacePtr<IMovieActionData const> actionData(inActionData, UseDefaultIID());
	if (actionData)
	{
		UIDRef movieRef = UIDRef(::GetDataBase(actionData), actionData->GetMovie());

		InterfacePtr<INavigationPoints> navPoints(movieRef, UseDefaultIID());
		if (navPoints == nil) return;

		uint32 numPoints = navPoints->GetNumberOfNavigationPoints();
		for (uint32 i = 0; i < numPoints; i++)
		{
			INavigationPoints::NavigationPoint navPoint;
			navPoints->GetNthNavigationPoint(i, navPoint);
			navPointData->Add(MovieNavPointListElement(movieRef, navPoint.fId));
		}

		if (numPoints == 0)
			navPointData->Add(MovieNavPointListElement(UIDRef::gNull, INavigationPoints::kInvalidNavigationPointId));
	}
}

//----------------------------------------------------------------------------------------
// MovieBehaviorPanelObserver::InitializeMovieNavPointChoice
//----------------------------------------------------------------------------------------

void MovieBehaviorPanelObserver::InitializeMovieNavPointChoice(const IBehaviorData *inActionData)
{
	InterfacePtr<IDropDownListController> navPointChoice((IDropDownListController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kMovieNavPointWidgetID, IID_IDROPDOWNLISTCONTROLLER));
	InterfacePtr< IListControlDataOf<MovieNavPointListElement> > navPointData(navPointChoice, IID_ILISTCONTROLDATA);

	LoadMovieNavPointChoices(inActionData, navPointData);
		
	bool bUpdated = false;
	if (inActionData ==0)
	{
		if (navPointData->Length() > 0)
		{
			bUpdated = true;
			navPointChoice->Select(0, kTrue, kFalse);
		}
	}
	else
	{
		InterfacePtr<IMovieActionData const> actionData(inActionData, UseDefaultIID());
		if (actionData)
		{
			for (int32 i = 0; i < navPointData->Length(); i++)
			{
				if ((*navPointData)[i].second == actionData->GetNavigationPointID())
				{
					bUpdated = true;
					if ( !navPointChoice->IsSelected(i) )
						navPointChoice->Select(i, kTrue, kFalse);
					break;
				}
			}
		}
	}

	if ( !bUpdated )
	{
		navPointChoice->Deselect(kTrue, kFalse);
#ifdef DEBUG
		InterfacePtr<IMovieActionData const> behaviorData(inActionData, UseDefaultIID());
		if (behaviorData != nil && behaviorData->GetNavigationPointID() != INavigationPoints::kInvalidNavigationPointId)
			ASSERT_FAIL(FORMAT_ARGS("Button has a movie nav point (uid %d) that does not exist!", behaviorData->GetNavigationPointID()));
#endif
	}
}

//----------------------------------------------------------------------------------------
// MovieBehaviorPanelObserver::UpdateBehaviorNode
//----------------------------------------------------------------------------------------

void MovieBehaviorPanelObserver::UpdateBehaviorNode()
{
	InterfacePtr<ITreeViewController> behaviorsCntlr((ITreeViewController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kBehaviorsTreeWidgetID, IID_ITREEVIEWCONTROLLER));
	if (behaviorsCntlr)
	{
		K2Vector<NodeID> selection;
		behaviorsCntlr->GetSelectedItems(selection);
		if (selection.size() == 1)
		{
			InterfacePtr<ITreeViewMgr> treeViewMgr(behaviorsCntlr, UseDefaultIID());
			treeViewMgr->NodeChanged(selection[0]);
		}
	}
}