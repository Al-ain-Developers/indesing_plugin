//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IOwnedItem.h $
//  
//  Owner: dwaterfa
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

#pragma once
#ifndef __IOwnedItem__
#define __IOwnedItem__

#include "IPMUnknown.h"
#include "TextID.h"
#include "K2Vector.h"
#include "IVisitorHelper.h"
#include "RangeData.h"		// for Text::StoryRangeList
#include "RequestContext.h"
#include "PMTextUtils.h"	// for Text::HIndexList
#include "textstoryaccesstypes.h"

class ICommand;
class IDocumentLayer;
class ITextModel;
class ITextModelMemento;
class ITextFrameColumn;
class IWaxLine;
class IWaxRun;
class IParcelList;
class IParagraphComposer;
class IScript;
class ITextStoryThread;
class ITextParcelList;

typedef K2Vector<InterfacePtr<IVisitorHelper> >	VisitorHelperList;

/**
	IOwnedItems are UID based bosses that are anchored to a specific text
	position in the ITextModel via a call to IItemStrand::SetOwnedUID(). All
	bosses anchored in this way are required to implement the IOwnedItem
	interface. This interface allows notification to the IOwnedItem about
	events within the ITextModel, such as composition, deletion, etc and to
	provide information to the Text subsytem about the properties of the
	IOwnedItem that affect the user experience.

	Some IOwnedItems, such as Inlines, Footnotes, Tables and Notes have one or
	more contiguous special characters that they insert which the IOwnedItem
	is anchored to. Some of these characters are findable though find/change,
	in the case of Inlines, Notes and Footnotes, and others are not in the
	case of Tables.

	IOwnedItems are not required to have special anchor characters. Hyperlinks
	simply attach themselves to the two ends of the desired range without
	inserting any special characters into the ITextModel.

	Notifcation of ITextModel events, such as delete, copy, paste, etc is done
	through the ITextModelMomento interface which the IOwnedItem is required
	to implement and return via the IOwnedItem::QueryMemento() method. This
	hooks allows the ITextModel to provide full context of the ITextModel
	operations and thus give the IOwnedItem flexibility to do what it needs
	to accomplish its goals.

	@see COwnedItem
	@see IItemStrand
	@see ITextFrameColumn
	@see ITextModel
	@see ITextStoryThread
	@see ITextModelMomento
	@ingroup text_owned
*/
class IOwnedItem : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IOWNEDITEM };

	/**
	The IItemStrand will maintain the UID of the IVOSDiskPage that
	holds onto this IOwnedItem while is it part of the strand.
	This information is used by the IOwnedItem::GetTextIndex() method to
	efficiently determine the TextIndex within the ITextModel where this
	IOwnedItem is anchored.
	@param diskPage UID of IVOSDiskPage that the IOwned
	*/
	virtual void				SetDiskPage(UID diskPage) = 0;

	/**
	Get the IVOSDiskPage that the IOwnedItem is mapped to.
	@return UID of IVOSDiskPage or kInvalidUID if not part of strand
	*/
	virtual UID					GetDiskPage() const = 0;

	/**
	Returns the TextIndex where the IOwnedItem is anchored in. If the IOwnedItem
	is not registered, that is it has kInvalidUID for the disk page, then
	the returned value will be kInvalidTextIndex.
	@return TextIndex in the ITextModel where the IOwnedItem is anchored.
	*/
	virtual TextIndex			GetTextIndex() const = 0;

	/**
	Returns the ITextModel the IOwnedItem is anchored in. If the IOwnedItem
	is not registered, that is it has kInvalidUID for the disk page, then
	the returned value will be kInvalidUID.
	@return UID of ITextModel that IOwnedItem is anchored in.
	*/
	virtual UID					GetTextModelUID() const = 0;

	/**
	Returns the ITextModel the IOwnedItem is anchored in. If the IOwnedItem
	is not registered, that is it has kInvalidUID for the disk page, then
	the returned value will be kInvalidUID.
	@return Pointer to ITextModel that IOwnedItem is anchored in.
	*/
	virtual ITextModel*			QueryTextModel() const = 0;

	/**
	The ITextFrameColumn the IOwnedItem is associated with based on the TextIndex
	returned by GetTextIndex(). If the anchoring position is in overset then
	the returned value will be invalid. 
	@return UIDRef of the ITextFrameColumn
	*/
	virtual UIDRef				GetFrameRef() const = 0;

	/**
	The ITextFrameColumn the IOwnedItem is associated with based on the TextIndex
	returned by GetTextIndex(). If the anchoring position is in ovrset then
	the returned value will be invalid.
	@return Pointer to ITextFrameColumn
	*/
	virtual ITextFrameColumn*	QueryFrame() const = 0;

	/**
	Returns the ink bounds of this IOwnedItem in Wax coordinates.
	Implementations that need any support for hittesting or cursors may simply
	return kZeroRect.
	@return bounds in local coords
	*/
	virtual PMRect				GetInkBounds(void) const = 0;

	/**
	When the ITextModel the IOwnedItem is anchored in is being deleted it
	will query the IOwnedItems via this method for Command to remove it
	from the document. At the time the returned command is executed the
	ITextModel will be in an indeterminate state and so it must not access
	it in any way. This includes calling IOwnedItem::GetDiskPage(),
	IOwnedItem::GetTextIndex(), IOwnedItem::QueryTextModel(),
	IOwnedItem::GetFrameRef() and IOwnedItem::QueryFrame().
	Further, this command should NOT remove any Text (ITextStoryThreads, etc)
	in the same ITextModel as a result of this operation - the entire ITextModel
	is processed at this time and anything in those ITextStoryThreads will be
	found. In addition, callees are NOT required to return a command if the
	IOwnedItem will be removed by another IOwnedItem in the same ITextModel.
	@return Pointer to remove from document command
	*/
	virtual ICommand*			QueryRemoveFromDocumentCmd() const = 0;

	/**
	The ITextModelMomento provides a mechanism for the ITextModel to notify
	the IOwnedItem about changes to the model that affect the IOwnedItem.
	@return Pointer to Memento for this IOwnedItem.
	*/
	virtual ITextModelMemento*	QueryMemento() const = 0;

	/**
	Special anchor characters are used by some IOwnedItems to anchor themselves
	into the ITextModel. The value returned by this method allows others to
	skip over the correct number of anchor characters when processing text
	containing the IOwnedItem.
	For example, Notes and Footnotes use one special anchor, Tables have a
	variable number and Hyperlinks and Indexes have no special anchors.
	*/
	virtual int32				GetNumSpecialAnchorChars() const = 0;

	/**
	IOwnedItems which manage other composed Text, such as Tables, or those
	that maintain links to the ISpread, such as Inlines, need to be informed
	when the IParcel that IOwnedItem is composed into has moved relative to
	the Pasteboard. Notification is done through the IOwnedItem::Moved() method.
	Note that
	IOwnedItems that return kFalse from this method may still get notified on
	occasion, but are not guaranteed to be in all circumstances.
	@return kTrue if the IOwnedItem requires notification, kFalse otherwise.
	*/
	virtual bool16				GetIsParcelPositionDependent() const = 0;

	/**
	Some IOwnedItems may manage portions of the same ITextModel that the
	IOwnedItem itself is in. Consider the example of Tables or Notes which
	create ITextStoryThreads to hold text data. This information is considered
	independent of composed state because it is model data.
	This method adds StoryRanges that are associated with this IOwnedItem
	to the result list. The ranges returned are in logical order (as the user
	perceives it) rather than in the order it appears in the ITextModel. So
	the callee is required to search for other IOwnedItems within it's range
	and call them.
	Note that adjacent IOwnedItems may simply be elements of a common object,
	such as in the case of Tables, so it is upto the implementation to decide
	how to deal with dividing up ownership of the common object between the
	various IOwnedItems.
	@see ITextUtils::CollectStoryRanges()
	@param rList The list to add ranges to. See ITextUtils::CollectStoryRanges()
	@param hIndex Hierarchy index. See ITextUtils::CollectStoryRanges()
	@param hIndexList Hierarchy list. See ITextUtils::CollectStoryRanges()
	*/
	virtual void				CollectStoryRanges(Text::StoryRangeList* rList,
										TextIndex hIndex = kInvalidTextIndex,
										Text::HIndexList* hIndexList = nil
												) const = 0;

	/**
	Get a list of visitable children of the IOwnedItem.
	@param rList VisitorHelperList to fill
	*/
	virtual void				CollectChildren(VisitorHelperList* rList) const = 0;

	/**
	Get a list of visitable children of the IOwnedItem based on a hit rectangle
	in local (not Wax) coordinates. 
	@param rList VisitorHelperList to fill
	@param pHitRect Pointer to PMRect in local coordinates to use as the point clicked
	@param useParcelInkBounds If kTrue, find the parcels using their inkbounds rather than their implicit bounding box. Only an issue when the IOwnedItem supports multiple children, for examples Tables or Footnotes.
	*/
	virtual	void				CollectChildren(VisitorHelperList* rList,
												const PMRect* pHitRect,
												const bool16 useParcelInkBounds
												) const = 0;
	/**
	Called when the IWaxLine containing the IOwnedItem is re-composed by
	shuffling rather than being re-created and Applied. The specified IWaxLine
	will be undamaged and have a valid ParcelKey.
	@param textModel The ITextModel containing the IOwnedItem
	@param pl IParcelList of the TextStoryThread containing the IWaxLine
	@param waxLine The IWaxLine containing the IOwnedItem
	@param ownedItemTextIndex The TextIndex of the IOwnedItem
	@param waxLineTextIndex	The TextIndex of the IWaxLine
	@return kTrue if the implementation affects WaxRun composition and it believes that it's composition may have changed, kFalse otherwise. Most implementations will return kFalse for this.
	*/
	virtual bool16				Moved(ITextModel* textModel,
										IParcelList* pl,
										const IWaxLine* waxLine,
										TextIndex ownedItemTextIndex,
										TextIndex waxLineTextIndex) = 0;

	/**
	Called when the IOwnedItem has been moved into overset. This may be called
	more than one during composition of the IWaxLine containing the IOwnedItem
	due to the need to handle ripple between IParcels.
	@param pl IParcelList of the ITextStoryThread containing the IWaxLine
	*/
	virtual void				MovedIntoOverset(IParcelList* pl) = 0;

	/**
	Called when the IWaxLine has been applied into the wax. This method is
	always called BEFORE Rebuilt(). The specified IWaxLine will be undamaged
	and have a valid ParcelKey.
	@param textModel The ITextModel containing the IOwnedItem
	@param pl IParcelList of the TextStoryThread containing the IWaxLine
	@param waxLine The IWaxLine containing the IOwnedItem
	@param ownedItemTextIndex The TextIndex of the IOwnedItem
	@param waxLineTextIndex	The TextIndex of the IWaxLine
	*/
	virtual void				Applied(ITextModel* textModel,
										IParcelList* pl,
										const IWaxLine* waxLine,
										TextIndex ownedItemTextIndex,
										TextIndex waxLineTextIndex) = 0;

	/**
	This method is called when the ITextStoryThread managing the range of Text containing the IOwnedItem is changed.
	@see ITextStoryThread
	@param newDictUID UID of managing ITextStoryThreadDict
	@param newDictKey Key assigned my managing ITextStoryThreadDict
	*/
	virtual void				StoryThreadChanged(UID newDictUID, uint32 newDictKey) = 0;

	/**
	This method is called when the story direction of the owning ITextStoryThread is changed. Implementations that compose their own text are expected to something appropriate for their situation to ensure that their composition appropriately reflects the new direction.
	*/
	virtual void				StoryDirectionChanged() = 0;
	
	/**
	This method is the trigger that allows an IOwnedItem to override the
	default IParagraphComposer of the IWaxLine that contains it. This method
	will be called if the IOwnedItem is a the first TextIndex of a damaged
	line, or is preceeded by zero or more occurances of
	kTextChar_ZeroSpaceNoBreak.
	Note that there are quite a few restrictions to this. For example, if
	the IParagraphComposer which owns the paragraph containing the IOwnedItem
	decides to compose the character the IOwnedItem is mapped to the
	IOwnedItem will never get called. Some work arounds to this problem are
	to either make sure your IOwnedItem is preceeded by a kTextChar_CR or
	kTextChar_SoftCR. In practice the only implementation supporting this is
	kWaxAnchorComposerImpl which supports the IWaxAnchorPt interface on the
	boss of the IOwnedItem. Tables rely on this mechanism.
	*/
	virtual IParagraphComposer*	QueryComposer() const = 0;

	/**
	This method is called when the containg story has its story access changed.
	Callees with nested Stories, such as Inline TextFrames, must change the
	story access of their nested Stories to match.
	@param access New TextStory_StoryAccess of the containing ITextModel.
	*/
	virtual void				StoryAccessChanged(TextStory_StoryAccess access) = 0;

	/**
	Some anchor characters are accessible through Find/Change. Table anchors
	are not, Footnotes and Notes are.
	@return kTrue if the anchor characters specified above (if non-zero) are accessable through Find/Change.
	*/
	virtual bool16				GetAreAnchorCharsFindable() const = 0;

	/**
	IOwnedItems that affect composition, such as Inlines with TextWrap, are
	considered to have a standoff.
	@return kTrue if the the IOwnedItem will cause TextWrap on other IWaxLines in the same ITextStoryThread.
	*/
	virtual bool16				GetHasStandOff() const = 0;

	/**
	Called when the IWaxRuns of the IWaxLine containing the IOwnedItem are
	re-built. Note that because during composition Rebuilt() will always be
	called before Moved(), Rebuilt() should not assume that the current position
	of the IWaxLine is the same as it was before.
	@param textModel The ITextModel containing the IOwnedItem
	@param pl IParcelList of the TextStoryThread containing the IWaxLine
	@param waxLine The IWaxLine containing the IOwnedItem
	@param waxRun The IWaxRun containing the IOwnedItem
	@param glyphIndex The index of the IOwnedItem within the IWaxRun
	@param ownedItemTextIndex The TextIndex of the IOwnedItem
	@param waxLineTextIndex	The TextIndex of the IWaxLine
	*/
	virtual void				Rebuilt(ITextModel* textModel,
										IParcelList* pl,
										const IWaxLine* waxLine,
										IWaxRun* waxRun,
										TextIndex ownedItemTextIndex,
										TextIndex waxLineTextIndex) = 0;

	/**
	Overloaded funtion
	Not necessary to implement, it will call
	virtual void				Rebuilt(ITextModel* textModel,
										IParcelList* pl,
										const IWaxLine* waxLine,
										IWaxRun* waxRun,
										TextIndex ownedItemTextIndex,
										TextIndex waxLineTextIndex) = 0;
	if implementation is not provided.

	Called when the IWaxRuns of the IWaxLine containing the IOwnedItem are
	re-built. Note that because during composition Rebuilt() will always be
	called before Moved(), Rebuilt() should not assume that the current position
	of the IWaxLine is the same as it was before.
	@param textModel The ITextModel containing the IOwnedItem
	@param pl IParcelList of the TextStoryThread containing the IWaxLine
	@param waxLine The IWaxLine containing the IOwnedItem
	@param waxRun The IWaxRun containing the IOwnedItem
	@param glyphIndex The index of the IOwnedItem within the IWaxRun
	@param ownedItemTextIndex The TextIndex of the IOwnedItem
	@param waxLineTextIndex	The TextIndex of the IWaxLine
	@param damagedBack It is used to detect if owned item has damaged back something, if yes
	then composition will come back again to build.
	while rebuilding
	*/
	virtual void				Rebuilt(ITextModel* textModel,
										IParcelList* pl,
										const IWaxLine* waxLine,
										IWaxRun* waxRun,
										TextIndex ownedItemTextIndex,
										TextIndex waxLineTextIndex,
										bool16* damagedBack) = 0;

	/**
	Called when the Parcel containing the IOwnedItem has changed its Layer.
	*/
	virtual void				LayerChanged(const IDocumentLayer* newDocLayer) = 0;

	/**
	Called when the Container of the Parcel containing the IOwnedItem changes its visibility.
	*/
	virtual void				VisibilityChanged() = 0;

	/**
	Called when the Parcel containing the IOwnedItem may have changed its
	ZOrder.
	*/
	virtual void				ZOrderChanged() = 0;

	/**
	Returns kTrue if the OwnedItem manages StoryRanges and any of these are
	overset.
	@return kTrue if any child StoryRanges are overset, kFalse otherwise.
	*/
	virtual bool16				GetContainsOversetContent() const = 0;

	/**
	Called when the Parcel containing the IOwnedItem has moved relative to
	the spread. Implementations must return kTrue for
	IOwnedItem::GetIsParcelPositionDependent() to guarantee that they will
	be called, although they should be prepared to be called even though they
	did not return kTrue. This is because the WaxLine that the IOwnedItem is
	composed into will notify all IOwnedItems on the same WaxLine if any of
	the IOwnedItems returned kTrue.
	*/
	virtual void				ParcelMoved() = 0;

	/**
	Called when the Parcel containing the IOwnedItem has been resized. This
	will only occur if the Parcel thinks there is position dependent content
	and that state will be cleared if the Parcel is moved, for example. Thus
	do not rely on this notification separate from a move.
	Implementations must return kTrue for
	IOwnedItem::GetIsParcelPositionDependent() to guarantee that they will
	be called, although they should be prepared to be called even though they
	did not return kTrue.
	*/
	virtual void				ParcelResized() = 0;

	/**
	Returns the ITextStoryThread the IOwnedItem is mapped to.
	@return Pointer to ITextStoryThread.
	*/
	virtual ITextStoryThread*	QueryStoryThread() const = 0;

	/**
	Returns the IParcelList associated with the ITextStoryThread the IOwnedItem
	is mapped to. May be nil.
	*/
	virtual IParcelList*		QueryParcelList() const = 0;

	/**
	Returns the ITextParcelList associated with the ITextStoryThread the
	IOwnedItem is mapped to. May be nil. To determine the ParcelKey of the
	Parcel the IOwnedItem is composed into get the TextIndex of the IOwnedItem
	and pass it into ITextParcelList::GetParcelContaining().
	*/
	virtual ITextParcelList*	QueryTextParcelList() const = 0;

	/**
	The OwnedItem is asked it supports Scripting - the object itself does not
	have to have an IScript, just that it will return an object that does if
	asked.
	@return kTrue if the OwnedItem can return an object with an IScript interfaces, kFalse otherwise.
	*/
	virtual bool16				GetCanReturnIScript() const = 0;

	/**
	The OwnedItem is asked to return an object associated with it that supports
	scripting. The OwnedItem does not necessarily have to have an IScript to do
	this - just that it returns something.
	asked.
	@return Pointer to boss with IScript interface
	*/
	virtual IScript*			QueryIScript(const ScriptInfo::RequestContext& context) const = 0;

};

#endif
