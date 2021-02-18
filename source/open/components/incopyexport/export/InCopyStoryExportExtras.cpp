//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/incopyexport/export/InCopyStoryExportExtras.cpp $
//  
//  Owner: Ben Park
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
//  This file contains the specific implementations of the InCopyStoryExportSuite that are specific to each CSB.  The majority
//  of the content is the same between them all - the only difference is in how the stories are collected for export.  The 
//  method GetExportableItemList is overriden in each case to deal with this.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IFormField.h"
#include "IGraphicFrameData.h"
#include "IHierarchy.h"
#include "ILayoutTarget.h"
#include "IMultiColumnTextFrame.h"
#include "ISelectionManager.h"
#include "ITableTarget.h"
#include "ITableTextContainer.h"
#include "ITextModel.h"
#include "ITextTarget.h"
#include "IEndnoteFacade.h"
#include "IBoolData.h"

// ----- Includes -----

#include "CInCopyStoryExportSuite.h"
#include "HelperInterface.h"
#include "UIDList.h"

// ----- Utility files -----

#include "IInCopyWorkFlowUtils.h"
#include "IPageItemTypeUtils.h"
#include "IStoryUtils.h"
#include "IXMLUtils.h"
#include "Utils.h"

// ----- ID.h files -----

#include "InCopyExportID.h"

static bool16 ShouldIncludeStory(UIDRef modelRef)
{
	Utils<Facade::IEndnoteFacade> endnoteFacade;
	bool isEndnoteAnchorOrEndnoteStory = endnoteFacade->IsEndnoteAnchorOrEndnoteStory(modelRef);

	if (Utils<IStoryUtils>()->IsAStory(modelRef) && isEndnoteAnchorOrEndnoteStory)
		return kTrue;

	return kFalse;
}

//================================================================================================
//	InCopyStoryTextExportSuite
//	
//	This class provides InCopy story specific export functionality.
//
//	Only here for one purpose: to get the list of stories needed to export.
//	This version is used for the Text and Galley Selections
//
//================================================================================================
class InCopyStoryTextExportSuite : public CInCopyStoryExportSuite
{
	public:
		InCopyStoryTextExportSuite ( IPMUnknown *boss );
		
	protected:
	// The only function that really needs to be overriden....
		virtual UIDList GetExportableItemList (IPMUnknown* targetboss) const;
};

CREATE_PMINTERFACE(InCopyStoryTextExportSuite, kICExportSuiteTextImpl)

InCopyStoryTextExportSuite::InCopyStoryTextExportSuite(  IPMUnknown *boss ) 
	: CInCopyStoryExportSuite(boss)
{}

// This should be the super easy one.  Simply Query the TextTarget (on the same boss) and return
// the story
UIDList InCopyStoryTextExportSuite::GetExportableItemList (IPMUnknown* targetboss) const
{
	// Query the TextTarget
	InterfacePtr<ITextTarget> target (this, UseDefaultIID());
	ASSERT(target);

	// Now return it.  Wasn't that easy?
	RangeData range = target->GetRange();
	UIDRef modelRef = target->GetTextModel();
	UIDList finalList(modelRef.GetDataBase());
	bool16 exportParentsOnly = kTrue; //preference?

	if (exportParentsOnly)
	{
		if (Utils<IInCopyWorkFlowUtils>())
			modelRef = Utils<IInCopyWorkFlowUtils>()->GetOutermostParentStory(modelRef, range);	//HH 8/25/04 We now want the outermost parent
	}

	// Only use the story if it hasn't already been exported AND
	// it isn't a form object AND
	// it doesn't contain XML which would be damaged by the export
	if ((!Utils<IStoryUtils>()->IsAStory(modelRef) || ShouldIncludeStory(modelRef))&&
		!Utils<IInCopyWorkFlowUtils>()->IsAFormObject(modelRef) &&
		Utils<IXMLUtils>()->IsExportableInCopyStory(modelRef)) {
		return modelRef;
	}

	// The story should not be exported - return an empty list
	return UIDList();
}


//================================================================================================
//	InCopyStoryTableExportSuite
//	
//	This class provides InCopy story specific export functionality.
//
//	Only here for one purpose: to get the list of stories needed to export.
//	This version is used for the Table Selections
//
//================================================================================================
class InCopyStoryTableExportSuite : public CInCopyStoryExportSuite
{
	public:
		InCopyStoryTableExportSuite ( IPMUnknown *boss );
		
	protected:
	// The only function that really needs to be overriden....
		virtual UIDList GetExportableItemList (IPMUnknown* targetboss) const;
};

CREATE_PMINTERFACE(InCopyStoryTableExportSuite, kICExportSuiteTableImpl)

InCopyStoryTableExportSuite::InCopyStoryTableExportSuite(  IPMUnknown *boss ) 
	: CInCopyStoryExportSuite(boss)
{}

// This should be the super easy one.  Simply Query the TableTarget (on the same boss) and return
// the story
UIDList InCopyStoryTableExportSuite::GetExportableItemList (IPMUnknown* targetboss) const
{
	// Query the TableTarget
	InterfacePtr<ITableTarget> target (this, UseDefaultIID());
	ASSERT(target);
	
	InterfacePtr<ITableTextContainer> tableTextContainer(target->GetModel(), UseDefaultIID());
	ASSERT(tableTextContainer);

	// Now return it.  Wasn't that easy?
	RangeData range = RangeData(tableTextContainer->GetAnchorTextIndex(), tableTextContainer->GetAnchorTextIndex(), RangeData::kLeanForward);
	UIDRef modelRef = tableTextContainer->GetTextModelRef();

	bool16 exportParentsOnly = kTrue; //preference?

	if (exportParentsOnly)
	{
		if (Utils<IInCopyWorkFlowUtils>())
			modelRef = Utils<IInCopyWorkFlowUtils>()->GetOutermostParentStory(modelRef, range);	//HH 8/25/04 We now want the outermost parent
	}

	// Only use the story if it hasn't already been exported AND
	// it isn't a form object AND
	// it doesn't contain XML which would be damaged by the export
	if ((!Utils<IStoryUtils>()->IsAStory( modelRef ) || ShouldIncludeStory(modelRef)) &&
		!Utils<IInCopyWorkFlowUtils>()->IsAFormObject( modelRef ) &&
		Utils<IXMLUtils>()->IsExportableInCopyStory( modelRef ))
		return modelRef;

	// The story should not be exported - return an empty list
	return UIDList();
}


//================================================================================================
//	InCopyStoryLayoutExportSuite
//	
//	This class provides InCopy story specific export functionality.
//
//	Only here for one purpose: to get the list of stories needed to export
//	This version is used for the Layout selection
//
//================================================================================================
class InCopyStoryLayoutExportSuite : public CInCopyStoryExportSuite
{
	public:
		InCopyStoryLayoutExportSuite ( IPMUnknown *boss );
		
	protected:
	// The only function that really needs to be overriden....
		virtual UIDList GetExportableItemList (IPMUnknown* targetboss) const;
};

CREATE_PMINTERFACE(InCopyStoryLayoutExportSuite, kICExportSuiteLayoutImpl)

InCopyStoryLayoutExportSuite::InCopyStoryLayoutExportSuite(  IPMUnknown *boss ) 
	: CInCopyStoryExportSuite(boss)
{}

// This one is a little more difficult - need to get the page items selected, and get the stories associated with them.
UIDList InCopyStoryLayoutExportSuite::GetExportableItemList (IPMUnknown* targetboss) const
{
	// Secondary Target doesn't seem to be working with threaded frames
	// So we'll try to use the primary target instead...

	Utils<IInCopyWorkFlowUtils> wfUtils;
	if (!wfUtils) return UIDList();

	InterfacePtr<ILayoutTarget>layoutTarget(this, UseDefaultIID());
	if ( layoutTarget && layoutTarget->HasContent() )
	{
		// get selected page items...
		const UIDList itemList( layoutTarget->GetUIDList(kStripStandoffs) );
		UIDList textFrameList( itemList.GetDataBase() );
		UIDList incopyItemList( itemList.GetDataBase() );
		bool16 exportParentsOnly = kTrue; //preference?
		
		// collect all text frames from page items...
		const int32 itemCount = itemList.Length();
		for( int32 i = 0; i < itemCount; ++i )
		{
			InterfacePtr<IGraphicFrameData> graphicData( itemList.GetRef(i), UseDefaultIID() );
			
			// Skip buttons or other form objects; the resulting incx file is not handled correctly in all cases by Firedrake.
			// Fixes Watson #1075724 [wtislar, 1/31/2005].
			
			bool16 itemIsAFormObject = kFalse;
			if (!exportParentsOnly || !Utils<IPageItemTypeUtils>()->IsInline(graphicData))
			{
				InterfacePtr<IHierarchy> itemHierarchy( graphicData, UseDefaultIID() );
				if ( itemHierarchy )
				{
					itemIsAFormObject = wfUtils->IsAFormObject(itemList.GetRef(i));
				}
			}
			else if (exportParentsOnly)
			{
				// See if the outermost story is exportable
				RangeData range(0,0,RangeData::kLeanForward);
				itemIsAFormObject = wfUtils->IsAFormObject(wfUtils->GetOutermostParentStory(itemList.GetRef(i), range));
			}
			
			if ( !Utils<IStoryUtils>()->IsAStory( itemList.GetRef(i) ) && graphicData && graphicData->IsGraphicFrame() && !itemIsAFormObject && graphicData->GetTextContentUID() == kInvalidUID )
			{
				UIDRef itemRef = itemList.GetRef(i);
				if (exportParentsOnly)
				{
					RangeData range(0,0,RangeData::kLeanForward);
					itemRef = wfUtils->GetOutermostParentStory(itemRef, range);	// We now want the outermost parent
				}

				bool16 containsATextFrame = kFalse;
				InterfacePtr<IHierarchy> itemHierarchy( itemRef, UseDefaultIID() );
				if ( itemHierarchy )
				{
					UIDList descendentList( itemList.GetDataBase() );
					itemHierarchy->GetDescendents( &descendentList, IMultiColumnTextFrame::kDefaultIID );
					if (!descendentList.IsEmpty())
					{
						// Add in the text frame children and set flag so
						// don't add in the outermost graphic frame; the text
						// stories can be managed but not the outer frame as
						// the frames of the story may not be fully contained 
						// in this graphic frame (i.e. threaded outside of 
						// this graphic frame).
						containsATextFrame = kTrue;
						textFrameList.Append( descendentList );
					}
				}

				if (!containsATextFrame)
					incopyItemList.Append(itemRef);
			}
			else
			{
				InterfacePtr<IHierarchy>itemHier( itemList.GetRef(i), UseDefaultIID() );
				if( itemHier )
				{
					UIDList tempUIDList( itemList.GetDataBase() );
					itemHier->GetDescendents( &tempUIDList, IMultiColumnTextFrame::kDefaultIID );
					if( tempUIDList.Length() )
						textFrameList.Append( tempUIDList );

					if (Utils<IPageItemTypeUtils>()->IsGroup(itemHier))
					{
						UIDList tempList( itemList.GetDataBase() );
						itemHier->GetDescendents( &tempList, IID_IGRAPHICFRAMEDATA );

						// add-in the graphic stories of a group
						int32 numGroupItems = tempList.Length();
						for (int32 p = 0; p < numGroupItems; ++p)
						{
							UIDRef itemRef = tempList.GetRef(p);
							InterfacePtr<IGraphicFrameData> graphicFrameData(itemRef, UseDefaultIID());
							// Again, skip buttons or other form objects when in InDesign. Fixes Watson #1075724 [wtislar, 1/31/2005].
							bool16 unexportableFormObject = kFalse;
							InterfacePtr<IHierarchy> itemHierarchy( graphicFrameData, UseDefaultIID() );
							if ( itemHierarchy )
								unexportableFormObject = wfUtils->IsAFormObject(itemRef);

							if ( graphicFrameData && graphicFrameData->IsGraphicFrame() && !unexportableFormObject && graphicFrameData->GetTextContentUID() == kInvalidUID )
							{
								if (!Utils<IStoryUtils>()->IsAStory(itemRef))
									incopyItemList.Append(itemRef);
							}
						}
					}
				}
			}
		}
			
		// collect all stories from text frames...
		const int32 frameCount = textFrameList.Length();
		for( int32 j = 0; j < frameCount; ++j )
		{
			const UIDRef& textFrameRef = textFrameList.GetRef(j);
			InterfacePtr<const IMultiColumnTextFrame>mcf( textFrameRef, UseDefaultIID() );
			ASSERT( mcf != nil );
			UID textModelUID = mcf->GetTextModelUID();
			
			if( incopyItemList.Location( textModelUID ) < 0 )
			{
				// Ok, one last check.  If it is already an InCopy Story, we don't append it.
				UIDRef modelRef(incopyItemList.GetDataBase(), textModelUID);

				if (exportParentsOnly)
				{
					RangeData range(0,0,RangeData::kLeanForward);
					modelRef = wfUtils->GetOutermostParentStory(modelRef, range);	// We now want the outermost parent
					textModelUID = modelRef.GetUID();
				}

				if ((!Utils<IStoryUtils>()->IsAStory( modelRef ) || ShouldIncludeStory(modelRef)) &&
					!wfUtils->IsAFormObject( modelRef ) &&
					Utils<IXMLUtils>()->IsExportableInCopyStory( modelRef ))
				{
					if (incopyItemList.Location(textModelUID) < 0)
						incopyItemList.Append(textModelUID);
				}
			}
		}
		return incopyItemList;
	}

	return UIDList();

}

//================================================================================================
//	InCopyStoryExportDefaultSuite
//	
//	This class provides InCopy story specific export functionality.
//
//	This one is only here really to help with scripting, since the script
//	architecture doesn't seem to handle this very well...
//
//================================================================================================
class InCopyStoryExportDefaultSuite : public CInCopyStoryExportSuite
{
	public:
		InCopyStoryExportDefaultSuite ( IPMUnknown *boss );
		
	protected:
	// The only function that really needs to be overriden....
		virtual UIDList GetExportableItemList (IPMUnknown* targetboss) const;
};

CREATE_PMINTERFACE(InCopyStoryExportDefaultSuite, kICExportSuiteDefaultImpl)

InCopyStoryExportDefaultSuite::InCopyStoryExportDefaultSuite(  IPMUnknown *boss ) 
	: CInCopyStoryExportSuite(boss)
{}

// Shouldn't be too bad.  Make a list of all the stories in the storylist, and return it
// Actually need to restrict list if targetboss is not a selection manager
UIDList InCopyStoryExportDefaultSuite::GetExportableItemList (IPMUnknown* targetboss) const
{	
	UIDList nullList;
	
	// If the targetboss is the selectionmanager, then we really don't want to do anything...
	InterfacePtr<ISelectionManager> selMgr (targetboss, UseDefaultIID());
	if (selMgr)
	{
		return nullList;
	}
	
	InterfacePtr<ITextModel> textModel(targetboss, UseDefaultIID());
	if (textModel)
	{
			UIDRef tmRef(GetUIDRef(textModel));
			if (Utils<IXMLUtils>()->IsExportableInCopyStory( tmRef ) &&
				!Utils<IInCopyWorkFlowUtils>()->IsAFormObject( tmRef ))
			{
				UIDList tmList(tmRef.GetDataBase());
				tmList.Append(tmRef.GetUID());
				return tmList;
			}
			else
				return UIDList();
	}
	

	InterfacePtr<ITextTarget> target(targetboss, UseDefaultIID());
	if (target)
	{
		UIDRef tm = target->GetTextModel();
		if (Utils<IXMLUtils>()->IsExportableInCopyStory( tm ) &&
			!Utils<IInCopyWorkFlowUtils>()->IsAFormObject( tm ))
		{
			UIDList storyRefs(tm.GetDataBase());
			storyRefs.Append(tm.GetUID());
			return storyRefs;
		}
		else
			return UIDList();
	}
	
	return nullList;
}

