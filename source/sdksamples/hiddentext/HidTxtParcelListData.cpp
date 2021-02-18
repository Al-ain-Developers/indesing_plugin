//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hiddentext/HidTxtParcelListData.cpp $
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
#include "ITextParcelListData.h"
#include "ITextStoryThread.h"
#include "ITextModel.h"
#include "IParcelList.h"

// General includes:
#include "CPMUnknown.h"

// Project includes:
#include "HidTxtID.h"
#include "IHidTxtModel.h"

/**	Stub ITextParcelListData implementation, display of composed
	hidden text is not supported.


	@ingroup hiddentext
	@see ITextParcelListData
 */
class HidTxtParcelListData : public CPMUnknown<ITextParcelListData>
{
	public:
		/** Constructor
			@param boss refers to boss class on which this interface is aggregated

		 */
				HidTxtParcelListData(IPMUnknown* boss);

		/** Destructor.
		 */
		virtual	~HidTxtParcelListData();

		// This is a stub, no documentation comments are provided.
		// See IParcelList for all further information.
	public:
		virtual IDataBase*			GetDataBase() const;
		virtual UID					GetTextModelUID() const;
		virtual UID					GetFrameListUID() const;
		virtual ITextStoryThread*	QueryStoryThread() const;
		virtual bool16				GetParcelIsDamaged(ParcelKey key) const;// Renamed at InDesign CS 2.0 (was GetIsDamaged)
		virtual void				SetParcelDamaged(ParcelKey key); // Renamed at InDesign CS 2.0 (was SetDamage)
		virtual void				ClearParcelDamage(ParcelKey key); // Added at InDesign CS 2.0
		virtual bool16				GetParcelNeedsWrapCheck(ParcelKey key) const; // Add at InDesign CS 3.0
		virtual void				SetParcelNeedsWrapCheck(ParcelKey key); // Add at InDesign CS 3.0
		virtual void				ClearParcelNeedsWrapCheck(ParcelKey key); // Add at InDesign CS 3.0

		virtual TextIndex			GetParcelTextStart(ParcelKey key) const; // Renamed at InDesign CS 2.0 (was GetTextStart)
		virtual int32				GetParcelTextSpan(ParcelKey key) const; // Renamed at InDesign CS 2.0 (was GetTextSpan)
		virtual void				SetParcelTextSpan(ParcelKey key, TextIndex span); // Renamed at InDesign CS 2.0 (was SetTextSpan)
		virtual ParcelKey			GetParcelContaining(TextIndex at) const;

		virtual void				GetParcelVContentBounds(ParcelKey key, PMReal* pTop, PMReal* pBottom) const;
		virtual void				SetParcelVContentBounds(ParcelKey key, PMReal top, PMReal bottom);
		virtual bool16				GetParcelHasPositionDependentContent(ParcelKey key) const; // Renamed at InDesign CS 3.0 (was GetParcelHasPositionDependentWax)
		virtual void				SetParcelHasPositionDependentContent(ParcelKey key, bool16 v); // Renamed at InDesign CS 3.0 (was SetParcelHasPositionDependentWax)
		virtual bool16				GetParcelHasKeepsOn(ParcelKey key) const; 
		virtual void				SetParcelHasKeepsOn(ParcelKey key, bool16 v); 
		virtual bool16				GetParcelHasBeenVJed(ParcelKey key) const;
		virtual void				SetParcelHasBeenVJed(ParcelKey key, bool16 vj);
		virtual bool16				GetParcelHasGridAlignedWax(ParcelKey key) const;
		virtual void				SetParcelHasGridAlignedWax(ParcelKey key, bool16 v);
 		virtual bool16				GetParcelHasNeedsPostProcessWax(ParcelKey key) const; // Added at InDesign CS 2.0
 		virtual void				SetParcelHasNeedsPostProcessWax(ParcelKey key, bool16 v); // Added at InDesign CS 2.0
		virtual ParcelKey			GetFirstLogicalParcelKey(int32* pIndex) const;
		virtual ParcelKey			GetNextLogicalParcelKey(ParcelKey key, int32* pIndex) const;
		virtual ParcelKey			GetNextLogicalParcelKeyByType(ParcelKey key, ITextParcelListData::nextParcelType pType, int32* pIndex) const; // Added at InDesign CS 3.0
		virtual ParcelKey			GetPreviousLogicalParcelKey(ParcelKey key, int32* pIndex) const; // Added at InDesign CS 2.0
		virtual ParcelKey			GetLastLogicalParcelKey(int32* pIndex) const;
		virtual ParcelKey			GetLastLogicalNonOversetParcelKey(int32* pIndex) const; // Added at InDesign CS 3.0
		virtual Text::FirstLineOffsetMetric GetParcelFirstLineOffsetMetric(ParcelKey key) const;
		virtual PMReal				GetParcelMinFirstLineOffset(ParcelKey key) const;
		virtual bool16				GetIsVertical() const;
		virtual bool16				GetIsRightToLeft() const;
		virtual PMReal				GetParcelMaxSoftBottomHeight(ParcelKey key) const;
 		virtual void				SetParcelMaxSoftBottomHeight(ParcelKey key, PMReal maxHeight); // Added at InDesign CS 2.0
		virtual bool16				GetParcelIsValidStartBreakLocation(ParcelKey key, Text::StartBreakLocation mode) const;
		virtual bool16				GetHasAnyValidStartBreakLocation() const;
		virtual bool16				GetParcelSupportsWrap(ParcelKey key) const; // Added at InDesign CS 3.0
		virtual bool16				GetParcelIgnoringWrap(ParcelKey key) const; // Added at InDesign CS 3.0
 		virtual int32				GetWaxAnchoredElementCount() const;// Added at InDesign CS 2.0
 		virtual int32				GetWaxAnchoredElementIndex(UID uid) const;// Added at InDesign CS 2.0
		virtual void				InsertNthWaxAnchoredElement(int32 n, UID uid);// Added at InDesign CS 2.0
 		virtual void				RemoveNthWaxAnchoredElement(int32 n);// Added at InDesign CS 2.0
 		virtual UID					GetNthWaxAnchoredElementUID(int32 n) const;// Added at InDesign CS 2.0
 		virtual ParcelKey			GetNthWaxAnchoredElementParcelKey(int32 n) const;// Added at InDesign CS 2.0
		virtual void				SetNthWaxAnchoredElementParcelKey(int32 n, ParcelKey key);// Added at InDesign CS 2.0
		virtual int32				GetWaxAnchoredElementsIn(ParcelKey key, UIDList* list) const; // Added at InDesign CS 2.0
		virtual ParcelKey			GetFirstDamagedParcel() const;
		virtual void				GetFirstKeyIndexes(int32& damagedKeyIndex, int32& needWrapCheckKeyIndex) const; // Added at InDesign CS 3.0
		virtual bool16				ShouldFakeTabAlignToChar() const;
		virtual void				InvalidateParcelComposedState(ParcelKey key); // Added at InDesign CS 2.0
		virtual void				NotifyParcelParentInkBoundsChanged(ParcelKey key); // Added at InDesign CS 2.0
		virtual int32				GetParcelsOnSpread(const ISpread* spread, K2Vector<ParcelKey>& keyList) const; // Added at InDesign CS 3.0
		virtual int32				GetNonInlineWrapsForParcel(ParcelKey key, TextWrapRefList& sodList) const; // Added at InDesign CS 3.0
		virtual void				AddParcelWrap(ParcelKey key, const TextWrapRef& sodRef, bool16 isActive, bool16 isNonInline, bool16 isInlineToParcel); // Added at InDesign CS 3.0
		virtual bool16				GetParcelWrapActive(ParcelKey, const TextWrapRef& sodRef) const; // Added at InDesign CS 3.0
		virtual void				SetParcelWrapActive(ParcelKey key, const TextWrapRef& sodRef); // Added at InDesign CS 3.0
		virtual void				ClearParcelWrapActive(ParcelKey key, const TextWrapRef& sodRef); // Added at InDesign CS 3.0
		virtual bool16				GetParcelWrapIsNonInline(ParcelKey, const TextWrapRef& sodRef) const; // Added at InDesign CS 3.0
		virtual bool16				GetParcelWrapIsInlineToParcel(ParcelKey, const TextWrapRef& sodRef) const; // Added at InDesign CS 3.0
		virtual bool16				GetParcelWrapHasOverlappedRange(ParcelKey key, const TextWrapRef& sodRef) const; // Added at InDesign CS 3.0
		virtual void				GetParcelWrapOverlappedRange(ParcelKey key, const TextWrapRef& sodRef, PMReal& waxYTop, PMReal& waxYBottom) const; // Added at InDesign CS 3.0
		virtual void				SetParcelWrapOverlappedRange(ParcelKey key, const TextWrapRef& sodRef, const PMReal& waxYTop, const PMReal& waxYBottom); // Added at InDesign CS 3.0
		virtual bool16				GetParcelHasWraps(ParcelKey key) const; // Added at InDesign CS 3.0
		virtual int32				GetParcelWraps(ParcelKey key, TextWrapRefList& sodList) const; // Added at InDesign CS 3.0
		virtual bool16				GetParcelHasActiveNonInlineWraps(ParcelKey key) const; // Added at InDesign CS 3.0
		virtual int32				GetParcelActiveNonInlineWraps(ParcelKey key, TextWrapRefList& sodList) const; // Added at InDesign CS 3.0
		virtual bool16				GetParcelHasActiveInlineWraps(ParcelKey key) const; // Added at InDesign CS 3.0
		virtual int32				GetParcelActiveInlineWraps(ParcelKey key, TextWrapRefList& sodList) const; // Added at InDesign CS 3.0
		virtual void				RemoveParcelWrap(ParcelKey key, const TextWrapRef& sodRef); // Added at InDesign CS 3.0
		virtual bool16				GetSupportsColumnSpanType(ICompositionStyle::SpanColumnsTypeOptions spanType) const; // Added at INDesign CS 5.0

};

/*
*/
CREATE_PMINTERFACE(HidTxtParcelListData, kHidTxtParcelListDataImpl)

/*
*/
HidTxtParcelListData::HidTxtParcelListData(IPMUnknown* boss) : CPMUnknown<ITextParcelListData>(boss)
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::Constructor()-->In/Out\n");
}

/*
*/
HidTxtParcelListData::~HidTxtParcelListData()
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::Destructor()-->In/Out\n");
}

/*
*/
IDataBase* HidTxtParcelListData::GetDataBase() const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetDataBase()-->In/Out\n");
	return ::GetDataBase(this);
}

/*
*/
UID HidTxtParcelListData::GetTextModelUID() const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetTextModelUID()-->In\n");
	UID result = kInvalidUID;
	do {
		InterfacePtr<IHidTxtModel> hidTxtModel(this, UseDefaultIID());
		if (hidTxtModel == nil) {
			break;
		}
		InterfacePtr<ITextModel> textModel(hidTxtModel->QueryTextModel());
		if (textModel == nil) {
			break;
		}
		result = ::GetUID(textModel);
	} while(false);
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetTextModelUID()-->Out result=0x%x\n", result.Get());
	return result;
}

/*
*/
UID HidTxtParcelListData::GetFrameListUID() const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetFrameListUID()-->In/Out\n");
	return kInvalidUID;
}

/*
*/
ITextStoryThread* HidTxtParcelListData::QueryStoryThread() const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::QueryStoryThread()-->In/Out\n");
	InterfacePtr<ITextStoryThread> storyThread(this, UseDefaultIID());
	return storyThread.forget();
}

/*
*/
bool16 HidTxtParcelListData::GetParcelIsDamaged(ParcelKey key) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetIsDamaged()-->In/Out\n");
	return kFalse;
}

/*
*/
void HidTxtParcelListData::SetParcelDamaged(ParcelKey key)
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::SetDamage()-->In/Out\n");
}

/*
*/
void HidTxtParcelListData::ClearParcelDamage(ParcelKey key)
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::ClearParcelDamage()-->In/Out\n");
}

/*
*/
TextIndex HidTxtParcelListData::GetParcelTextStart(ParcelKey key) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetParcelTextStart()-->In\n");
	TextIndex result = kInvalidTextIndex;
	InterfacePtr<ITextStoryThread> storyThread(this, UseDefaultIID());
	ASSERT(storyThread != nil);
	if (storyThread != nil) {
		result = storyThread->GetTextStart(nil);
	}
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetParcelTextStart()-->Out result=%d\n", result);
	return result;
}

/*
*/
int32 HidTxtParcelListData::GetParcelTextSpan(ParcelKey key) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetParcelTextSpan()-->In\n");
	int32 result = 0;
	InterfacePtr<ITextStoryThread> storyThread(this, UseDefaultIID());
	ASSERT(storyThread != nil);
	if (storyThread != nil) {
		result = storyThread->GetTextSpan(nil);
	}
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetParcelTextSpan()-->Out result=%d\n", result);
	return result;
}

/*
*/
void HidTxtParcelListData::SetParcelTextSpan(ParcelKey key, TextIndex span)
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::SetParcelTextSpan()-->In/Out\n");
}

/*
*/
ParcelKey HidTxtParcelListData::GetParcelContaining(TextIndex at) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetParcelContaining()-->In/Out\n");
	return ParcelKey();
}

/*
*/
void HidTxtParcelListData::GetParcelVContentBounds(ParcelKey key, PMReal* pTop, PMReal* pBottom) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetParcelVContentBounds()-->In\n");
	ASSERT(pTop != nil);
	if (pTop != nil) {
		*pTop = 0.0;
	}
	ASSERT(pBottom != nil);
	if (pBottom != nil) {
		*pBottom = 0.0;
	}
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetParcelVContentBounds()-->Out\n");
}

/*
*/
void HidTxtParcelListData::SetParcelVContentBounds(ParcelKey key, PMReal top, PMReal bottom)
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::SetParcelVContentBounds()-->In/Out\n");
}

/*
*/
bool16 HidTxtParcelListData::GetParcelHasPositionDependentContent(ParcelKey key) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetParcelHasPositionDependentContent()-->In/Out\n");
	return kFalse;
}

/*
*/
void HidTxtParcelListData::SetParcelHasPositionDependentContent(ParcelKey key, bool16 v)
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::SetParcelHasPositionDependentContent()-->In/Out\n");
}

/*
*/
bool16 HidTxtParcelListData::GetParcelHasKeepsOn(ParcelKey key) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetParcelHasKeepsOn()-->In/Out\n");
	return kFalse;
}

/*
*/
void HidTxtParcelListData::SetParcelHasKeepsOn(ParcelKey key, bool16 v)
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::SetParcelHasKeepsOn()-->In/Out\n");
}

/*
*/
bool16 HidTxtParcelListData::GetParcelHasGridAlignedWax(ParcelKey key) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetParcelHasGridAlignedWax()-->In/Out\n");
	return kFalse;
}

/*
*/
void HidTxtParcelListData::SetParcelHasGridAlignedWax(ParcelKey key, bool16 v)
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::SetParcelHasGridAlignedWax()-->In/Out\n");
}

/*
*/
bool16 HidTxtParcelListData::GetParcelHasNeedsPostProcessWax(ParcelKey key) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetParcelHasNeedsPostProcessWax()-->In/Out\n");
	return kFalse;
}

/*
*/
void HidTxtParcelListData::SetParcelHasNeedsPostProcessWax(ParcelKey key, bool16 v)
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::SetParcelHasNeedsPostProcessWax()-->In/Out\n");
}

/*
*/
ParcelKey HidTxtParcelListData::GetFirstLogicalParcelKey(int32* pIndex) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetFirstLogicalParcelKey()-->In/Out\n");
	InterfacePtr<const IParcelList>	pl(this, UseDefaultIID());
	const int32		parcelCount = pl->GetParcelCount();
	int32			index;
	ParcelKey		retKey;

	if (parcelCount)
	{
		index = 0;
		retKey = pl->GetNthParcelKey(index);
	}
	else
	{
		index = -1;
		ASSERT(!retKey.IsValid());
	}

	if (pIndex)
		*pIndex = index;

	return retKey;
}

/*
*/
ParcelKey HidTxtParcelListData::GetNextLogicalParcelKey(ParcelKey key,
														int32* pIndex) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetNextLogicalParcelKey()-->In/Out\n");

	InterfacePtr<const IParcelList>	pl(this, UseDefaultIID());
	const int32			parcelCount = pl->GetParcelCount();
	int32				index = parcelCount;
	ParcelKey			retKey;

	ASSERT(!retKey.IsValid());

	if (key.IsValid())
	{
		const int32	parcelIndex = pl->GetParcelIndex(key);
		if ((parcelIndex + 1) < parcelCount)
		{
			index = (parcelIndex + 1);
			retKey = pl->GetNthParcelKey(index);
		}
	}

	if (pIndex)
		*pIndex = index;

	return retKey;
}

/*
*/
ParcelKey HidTxtParcelListData::GetNextLogicalParcelKeyByType(ParcelKey key,
											ITextParcelListData::nextParcelType pType,
											int32* pIndex) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetNextLogicalParcelKeyByType()-->In/Out\n");

	InterfacePtr<const IParcelList>	pl(this, UseDefaultIID());
	const int32			parcelCount = pl->GetParcelCount();
	int32				index = parcelCount;
	ParcelKey			retKey;

	ASSERT(!retKey.IsValid());

	if (key.IsValid())
	{
		switch (pType)
		{
			case ITextParcelListData::npt_box:
				if ((retKey = pl->GetNextBoxParcelKey(key)).IsValid())
					index = pl->GetParcelIndex(retKey);
				break;

			case ITextParcelListData::npt_anypage:
				if ((retKey = pl->GetNextPageParcelKey(key)).IsValid())
					index = pl->GetParcelIndex(retKey);
				break;

			case ITextParcelListData::npt_oddpage:
				if ((retKey = pl->GetNextOddPageParcelKey(key)).IsValid())
					index = pl->GetParcelIndex(retKey);
				break;

			case ITextParcelListData::npt_evenpage:
				if ((retKey = pl->GetNextEvenPageParcelKey(key)).IsValid())
					index = pl->GetParcelIndex(retKey);
				break;

			default:
				break;
		}
	}

	if (pIndex)
		*pIndex = index;

	return retKey;
}

/*
*/
ParcelKey HidTxtParcelListData::GetPreviousLogicalParcelKey(ParcelKey key,
															int32* pIndex) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetPreviousLogicalParcelKey()-->In/Out\n");

	int32		index = -1;
	ParcelKey	retKey;

	ASSERT(!retKey.IsValid());

	if (key.IsValid())
	{
		InterfacePtr<const IParcelList>	pl(this, UseDefaultIID());
		const int32						parcelIndex = pl->GetParcelIndex(key);

		if (parcelIndex > 0)
		{
			index = (parcelIndex - 1);
			retKey = pl->GetNthParcelKey(index);
		}
	}

	if (pIndex)
		*pIndex = index;

	return retKey;
}

/*
*/
ParcelKey HidTxtParcelListData::GetLastLogicalParcelKey(int32* pIndex) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetLastLogicalParcelKey()-->In/Out\n");
	InterfacePtr<const IParcelList>	pl(this, UseDefaultIID());
	const int32						parcelCount = pl->GetParcelCount();
	int32							index;
	ParcelKey						retKey;

	if (parcelCount)
	{
		index = (parcelCount - 1);
		retKey = pl->GetNthParcelKey(index);
	}
	else
	{
		index = 0;
		ASSERT(!retKey.IsValid());
	}

	if (pIndex)
		*pIndex = index;

	return retKey;
}

/*
*/
ParcelKey HidTxtParcelListData::GetLastLogicalNonOversetParcelKey(int32* pIndex) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetLastLogicalNonOversetParcelKey()-->In/Out\n");

	return GetLastLogicalParcelKey(pIndex);
}

/*
*/
Text::FirstLineOffsetMetric HidTxtParcelListData::GetParcelFirstLineOffsetMetric(ParcelKey key) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetParcelFirstLineOffsetMetric()-->In/Out\n");
	return Text::kFLOLeading;
}

/*
*/
PMReal HidTxtParcelListData::GetParcelMinFirstLineOffset(ParcelKey key) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetParcelMinFirstLineOffset()-->In/Out\n");
	return 0.0;
}

/*
*/
bool16 HidTxtParcelListData::GetIsVertical() const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetIsVertical()-->In/Out\n");
	return kFalse;
}

/*
*/
bool16 HidTxtParcelListData::GetIsRightToLeft() const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetIsRightToLeft()-->In/Out\n");
	return kFalse;
}

/*
*/
bool16 HidTxtParcelListData::GetParcelIsValidStartBreakLocation(ParcelKey key, Text::StartBreakLocation mode) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetParcelIsValidStartBreakLocation()-->In/Out\n");
	return kFalse;
}

/*
*/
bool16 HidTxtParcelListData::GetHasAnyValidStartBreakLocation() const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetHasAnyValidStartBreakLocation()-->In/Out\n");
	return kFalse;
}

/*
*/
bool16 HidTxtParcelListData::GetParcelSupportsWrap(ParcelKey key) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetParcelSupportsWrap()-->In/Out\n");
	return kFalse;
}

/*
*/
bool16 HidTxtParcelListData::GetParcelIgnoringWrap(ParcelKey key) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetParcelIgnoringWrap()-->In/Out\n");
	return kTrue;
}

/*
*/
int32 HidTxtParcelListData::GetWaxAnchoredElementCount() const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetWaxAnchoredElementCount()-->In/Out\n");
	return 0;
}

/*
*/
int32 HidTxtParcelListData::GetWaxAnchoredElementIndex(UID uid) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetWaxAnchoredElementIndex()-->In/Out\n");
	return -1;
}

/*
*/
void HidTxtParcelListData::InsertNthWaxAnchoredElement(int32 n, UID uid)
{
	ASSERT_FAIL("No WaxAnchoredElements");
}

/*
*/
void HidTxtParcelListData::RemoveNthWaxAnchoredElement(int32 n)
{
	ASSERT_FAIL("No WaxAnchoredElements");
}

/*
*/
UID HidTxtParcelListData::GetNthWaxAnchoredElementUID(int32 n) const
{
	ASSERT_FAIL("No WaxAnchoredElements");
	return kInvalidUID;
}

/*
*/
ParcelKey HidTxtParcelListData::GetNthWaxAnchoredElementParcelKey(int32 n) const
{
	ASSERT_FAIL("No WaxAnchoredElements");
	return ParcelKey();
}

/*
*/
void HidTxtParcelListData::SetNthWaxAnchoredElementParcelKey(int32 n, ParcelKey key)
{
	ASSERT_FAIL("No WaxAnchoredElements");
}

/*
*/
int32 HidTxtParcelListData::GetWaxAnchoredElementsIn(ParcelKey key, UIDList* list) const
{
	ASSERT_FAIL("No WaxAnchoredElements");
	return 0;
}

/*
*/
ParcelKey HidTxtParcelListData::GetFirstDamagedParcel() const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetFirstDamagedParcel()-->In/Out\n");
	return ParcelKey();
}

/*
*/
void HidTxtParcelListData::GetFirstKeyIndexes(int32& damagedKeyIndex, int32& needWrapCheckKeyIndex) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetFirstKeyIndexes()-->In/Out\n");
	damagedKeyIndex = -1;
	needWrapCheckKeyIndex = -1;
}


/*
*/
PMReal HidTxtParcelListData::GetParcelMaxSoftBottomHeight(ParcelKey key) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetParcelMaxSoftBottomHeight()-->In/Out\n");
	return 0.0;
}


/*
*/
void HidTxtParcelListData::SetParcelMaxSoftBottomHeight(ParcelKey key, PMReal maxHeight)
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::SetParcelMaxSoftBottomHeight()-->In/Out\n");
}

/*
*/
bool16 HidTxtParcelListData::GetParcelHasBeenVJed(ParcelKey key) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetParcelHasBeenVJed()-->In/Out\n");
	return kFalse;
}

/*
*/
void HidTxtParcelListData::SetParcelHasBeenVJed(ParcelKey key, bool16 vj)
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::SetParcelHasBeenVJed()-->In/Out\n");
}

/*
*/
bool16 HidTxtParcelListData::ShouldFakeTabAlignToChar() const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::ShouldFakeTabAlignToChar()-->In/Out\n");
	return kFalse;
}

/*
*/
void HidTxtParcelListData::InvalidateParcelComposedState(ParcelKey key)
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::InvalidateParcelComposedState()-->In/Out\n");
}

/*
*/
void HidTxtParcelListData::NotifyParcelParentInkBoundsChanged(ParcelKey key)
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::NotifyParcelParentInkBoundsChanged()-->In/Out\n");
}

/*
*/
int32 HidTxtParcelListData::GetParcelsOnSpread(const ISpread* spread, K2Vector<ParcelKey>& keyList) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetParcelsOnSpread()-->In/Out\n");
	return 0;
}

/*
*/
int32 HidTxtParcelListData::GetNonInlineWrapsForParcel(ParcelKey key, TextWrapRefList& sodList) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetNonInlineWrapsForParcel()-->In/Out\n");
	return 0;
}

/*
*/
void HidTxtParcelListData::AddParcelWrap(ParcelKey key, const TextWrapRef& sodRef, bool16 isActive, bool16 isNonInline, bool16 isInlineToParcel)
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::AddParcelWrap()-->In/Out\n");
}

/*
*/
bool16 HidTxtParcelListData::GetParcelWrapActive(ParcelKey key, const TextWrapRef& sodRef) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetParcelWrapActive()-->In/Out\n");
	ASSERT_FAIL("Bad wrap");
	return kFalse;
}

/*
*/
void HidTxtParcelListData::SetParcelWrapActive(ParcelKey key, const TextWrapRef& sodRef)
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::SetParcelWrapActive()-->In/Out\n");
	ASSERT_FAIL("Bad wrap");
}

/*
*/
void HidTxtParcelListData::ClearParcelWrapActive(ParcelKey key, const TextWrapRef& sodRef)
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::ClearParcelWrapActive()-->In/Out\n");
	ASSERT_FAIL("Bad wrap");
}

/*
*/
bool16 HidTxtParcelListData::GetParcelWrapIsNonInline(ParcelKey key, const TextWrapRef& sodRef) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetParcelWrapIsNonInline()-->In/Out\n");
	ASSERT_FAIL("Bad wrap");
	return kFalse;
}

/*
*/
bool16 HidTxtParcelListData::GetParcelWrapIsInlineToParcel(ParcelKey key, const TextWrapRef& sodRef) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetParcelWrapIsInlineToParcel()-->In/Out\n");
	ASSERT_FAIL("Bad wrap");
	return kFalse;
}

/*
*/
bool16 HidTxtParcelListData::GetParcelNeedsWrapCheck(ParcelKey key) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetParcelNeedsWrapCheck()-->In/Out\n");
	ASSERT_FAIL("Bad wrap");
	return kFalse;
}

/*
*/
void HidTxtParcelListData::SetParcelNeedsWrapCheck(ParcelKey key)
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::SetParcelNeedsWrapCheck()-->In/Out\n");
	ASSERT_FAIL("Bad wrap");
}

/*
*/
void HidTxtParcelListData::ClearParcelNeedsWrapCheck(ParcelKey key)
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::ClearParcelNeedsWrapCheck()-->In/Out\n");
	ASSERT_FAIL("Bad wrap");
}

/*
*/
bool16 HidTxtParcelListData::GetParcelWrapHasOverlappedRange(ParcelKey key, const TextWrapRef& sodRef) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetParcelWrapHasOverlappedRange()-->In/Out\n");
	ASSERT_FAIL("Bad wrap");
	return kFalse;
}

/*
*/
void HidTxtParcelListData::GetParcelWrapOverlappedRange(ParcelKey key, const TextWrapRef& sodRef, PMReal& waxYTop, PMReal& waxYBottom) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetParcelWrapOverlappedRange()-->In/Out\n");
	ASSERT_FAIL("Bad wrap");
}

/*
*/
void HidTxtParcelListData::SetParcelWrapOverlappedRange(ParcelKey key, const TextWrapRef& sodRef, const PMReal& waxYTop, const PMReal& waxYBottom)
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::SetParcelWrapOverlappedRange()-->In/Out\n");
	ASSERT_FAIL("Bad wrap");
}

/*
*/
bool16 HidTxtParcelListData::GetParcelHasWraps(ParcelKey key) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetParcelHasWraps()-->In/Out\n");
	return kFalse;
}

/*
*/
int32 HidTxtParcelListData::GetParcelWraps(ParcelKey key, TextWrapRefList& sodList) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetParcelWraps()-->In/Out\n");
	return 0;
}

/*
*/
bool16 HidTxtParcelListData::GetParcelHasActiveNonInlineWraps(ParcelKey key) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetParcelHasActiveNonInlineWraps()-->In/Out\n");
	return kFalse;
}

/*
*/
int32 HidTxtParcelListData::GetParcelActiveNonInlineWraps(ParcelKey key, TextWrapRefList& sodList) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetParcelActiveNonInlineWraps()-->In/Out\n");
	return 0;
}

/*
*/
bool16 HidTxtParcelListData::GetParcelHasActiveInlineWraps(ParcelKey key) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetParcelHasActiveInlineWraps()-->In/Out\n");
	return kFalse;
}

/*
*/
int32 HidTxtParcelListData::GetParcelActiveInlineWraps(ParcelKey key, TextWrapRefList& sodList) const
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::GetParcelActiveInlineWraps()-->In/Out\n");
	return 0;
}

/*
*/
void HidTxtParcelListData::RemoveParcelWrap(ParcelKey key, const TextWrapRef& sodRef)
{
	TRACEFLOW("HiddenText", "HidTxtParcelListData::RemoveParcelWrap()-->In/Out\n");
	ASSERT_FAIL("Bad wrap");
}


bool16 HidTxtParcelListData::GetSupportsColumnSpanType(ICompositionStyle::SpanColumnsTypeOptions spanType) const
{
	return (spanType == ICompositionStyle::kSingleColumn);
}

// End, HidTxtParcelListData.cpp
