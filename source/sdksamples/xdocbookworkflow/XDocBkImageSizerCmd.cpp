//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xdocbookworkflow/XDocBkImageSizerCmd.cpp $
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
#include "IGeometry.h"
#include "IHierarchy.h"
#include "IInlineData.h"
#include "IRefPointUtils.h"
#include "IStoryList.h"
#include "ITextModel.h"
#include "ITextParcelList.h"
#include "IGeometryFacade.h"

// General includes:
#include "CmdUtils.h"
#include "Command.h"
#include "ErrorUtils.h"
#include "K2Vector.tpp"
#include "OwnedItemDataList.h"

// Project includes
#include "XDocBkID.h"

/** Implementation of command to resize inlines to fit within the column that contains them. It leaves ones that are smaller
	than this width unaffected. 

	@ingroup xdocbookworkflow
*/
class XDocBkImageSizerCmd : public Command
{
public:
	/** Constructor.
		@param boss IN interface ptr from boss object on which this interface is aggregated.*/
	XDocBkImageSizerCmd(IPMUnknown* boss);
	
protected:
	/** @see Command::Do
	 */
	virtual void Do();

	

	/** @see Command::CreateName
	 */
	virtual PMString* CreateName();

	/**	Find all the in-lines in given story
		@param textModelUIDRef IN text model containing the inlines of interest
		@param outList OUT parameter holding the inline boss objects
	 */
	void CollectInlinesInStory(const UIDRef& textModelUIDRef, K2Vector<UIDRef>& outList);

	/**	Resize an inline in given text model (maybe, if it needs to be scaled to fit in column)
		@param textModelUIDRef IN text model in which inline is to be scaled to fit
		@param inlineBossUIDRef IN boss object of type kInlineBoss
	 */
	void ResizeInlineGraphicToFit(const UIDRef& textModelUIDRef, const UIDRef& inlineBossUIDRef);

	/**	Get the width of the column into which this inline is being placed
		@param textModelUIDRef IN text model of interest
		@param uidRef IN inline thing, we're going to query for IInlineData on this to find out where in the story the inline is
		@return PMReal composed width of column
	 */
	PMReal CalcColumnParcelWidth(const UIDRef& textModelUIDRef, const UIDRef& uidRef) const;

	/**	Method to calculate width to scale inline to if required
		@param uidRef IN the image whose width we'll get from its IGeometry
		@return PMReal the current width before scaling this image
	 */
	PMReal CalcInlineGraphicWidth(const UIDRef& uidRef) const;

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(XDocBkImageSizerCmd, kXDocBkImageSizerCmdImpl)

/* Constructor
*/
XDocBkImageSizerCmd::XDocBkImageSizerCmd(IPMUnknown* boss) : Command(boss)	
{
	this->SetUndoability(kAutoUndo);
}

/* Do
*/
void XDocBkImageSizerCmd::Do()
{
	ErrorCode retval = kFailure;
	do
	{
		const UIDList* itemList= this->GetItemList();
		ASSERT(itemList);
		UID docUID = itemList->First();
		IDataBase* db = itemList->GetDataBase();
		ASSERT(db);
		if (!db){
			break;
		}
		UIDRef docUIDRef(db,docUID);
		InterfacePtr<IStoryList> storyList(docUIDRef, UseDefaultIID());
		ASSERT(storyList);
		if (storyList == nil) {
			break;
		}

		int32 numStories = storyList->GetUserAccessibleStoryCount();
		for (int32 n = 0; n < numStories; n++) {
			K2Vector<UIDRef> inlinesList;
			UIDRef story = storyList->GetNthUserAccessibleStoryUID(n);
			this->CollectInlinesInStory(story, inlinesList);
			K2Vector<UIDRef>::const_iterator iter;
			for (iter = inlinesList.begin(); iter < inlinesList.end(); ++iter)
			{
				this->ResizeInlineGraphicToFit(story,*iter);
			}
		}
		retval = kSuccess;

	} while (kFalse);

	if (retval != kSuccess) {
		ErrorUtils::PMSetGlobalErrorCode(kFailure);
	}
}


/* CreateName
*/
PMString* XDocBkImageSizerCmd::CreateName()
{
	return new PMString(kXDocBkImageSizerCmdKey);
}

/* ResizeInlineGraphicToFit
*/
void XDocBkImageSizerCmd::ResizeInlineGraphicToFit(const UIDRef& textModelUIDRef, 
									   const UIDRef& inlineBossUIDRef)
{
	do
	{
		InterfacePtr<IHierarchy> hier(inlineBossUIDRef, UseDefaultIID());
		ASSERT(hier);
		if (!hier) {
			break;
		}
		if (hier->GetChildCount() < 1) {
			break;
		}
		UID uid = hier->GetChildUID(0);
		ASSERT(uid != kInvalidUID);
		if (uid == kInvalidUID) {
			break;
		}
		UIDRef placedThingUIDRef(inlineBossUIDRef.GetDataBase(),uid);

		PMReal colWidth = this->CalcColumnParcelWidth(textModelUIDRef, inlineBossUIDRef);
		PMReal inlineWidth = this->CalcInlineGraphicWidth(placedThingUIDRef);
		if (colWidth > inlineWidth) {
			// No need to scale
			break;
		}
		if (colWidth== PMReal(0.0) || inlineWidth == PMReal(0.0)) {
			break;
		}
		PMReal xFactor= colWidth / inlineWidth;
		PMReal yFactor = xFactor;

		InterfacePtr<IGeometry> pageItemGeometry(placedThingUIDRef, UseDefaultIID());
		ASSERT(pageItemGeometry);
		if (!pageItemGeometry) {
			break;
		}


		// This is why we need a command; the TransformCmdUtils impl. calls IUtils<IPageItemUtils>()->ScaleRect
		// which changes the model...
		//...actually IGeometryFacade::ResizeItems already uses a command internally

		ErrorCode err =  Utils<Facade::IGeometryFacade>()->ResizeItems( UIDList(placedThingUIDRef), 
							Transform::PasteboardCoordinates(), Geometry::PathBounds(),
							Transform::LeftTopLocation( Geometry::OuterStrokeBounds()), Geometry::MultiplyBy( xFactor, yFactor));
		ASSERT(err == kSuccess);
	} while (kFalse);
}

/* CollectInlinesInStory
*/
void XDocBkImageSizerCmd::CollectInlinesInStory(const UIDRef& textModelUIDRef,
										 K2Vector<UIDRef>& outList)
{
	do
	{
		InterfacePtr<ITextModel> textModel(textModelUIDRef, UseDefaultIID());
		ASSERT(textModel);
		if (!textModel) {
			break;
		}
		IDataBase* db = ::GetDataBase(textModel);
		OwnedItemDataList ownedList;
		Utils<ITextUtils>()->CollectOwnedItems(textModel,
											   0,
											   textModel->GetPrimaryStoryThreadSpan(), 
											   &ownedList);
		for (int32 i = 0; i < ownedList.size(); i++) {
			if ((ownedList[i].fClassID == kInlineBoss)) {
				outList.push_back(UIDRef(db, ownedList[i].fUID));
			}
		}

	} while (kFalse);
}


/* CalcColumnParcelWidth
*/
PMReal XDocBkImageSizerCmd::CalcColumnParcelWidth(const UIDRef& textModelUIDRef,
											const UIDRef& uidRef) const
{
	// uidRef refers to a kInlineBoss
	// so we can get e.g. an IInlineData from it
	PMReal retval=(0.0);
	do
	{
		InterfacePtr<ITextModel> textModel(textModelUIDRef, UseDefaultIID());
		ASSERT(textModel);
		if (!textModel) {
			break;
		}
		InterfacePtr<IInlineData> iInlineData(uidRef, UseDefaultIID());
		ASSERT(iInlineData);
		if (!iInlineData) {
			break;
		}
		// Find out where in the text the inline is anchored
		TextIndex ilgIndex = iInlineData->GetILGIndex();
		ASSERT(ilgIndex >= 0 && ilgIndex < textModel->GetPrimaryStoryThreadSpan());

		PMRect parcelCBounds;
		InterfacePtr<ITextParcelList> tpl(textModel->QueryTextParcelList(ilgIndex));
		ASSERT(tpl);
		if (!tpl){
			break;
		}
		// Calculate the column width based on the text frame this is being inserted into	
		bool16 canGetParcelBounds = Utils<ITextUtils>()->GetParcelContentBounds(tpl, ilgIndex, &parcelCBounds);
		if (!canGetParcelBounds) {
			break;
		}

		retval = parcelCBounds.Width();

	} while (kFalse);
	return retval;
}

/* calcInlineWIdth
*/
PMReal XDocBkImageSizerCmd::CalcInlineGraphicWidth(const UIDRef& uidRef) const
{
	PMReal retval = 0.0;
	do
	{
		// this type definitely aggregates an IGeometry
		InterfacePtr<IGeometry> iGeometry(uidRef, UseDefaultIID());
		ASSERT(iGeometry);
		if (!iGeometry) {
			break;
		}
		PMRect pmRect = iGeometry->GetStrokeBoundingBox();
		retval= pmRect.Width();
	} while (kFalse);
	return retval;
}

// End, XDocBkImageSizerCmd.cpp.
