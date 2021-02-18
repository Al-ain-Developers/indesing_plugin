//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hiddentext/HidTxtStoryThread.cpp $
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
#include "ITextStoryThread.h"
#include "IParcelList.h"
#include "ITextModel.h"
#include "IHidTxtModel.h"

// General includes:
#include "Trace.h"

// Projecr includes:
#include "HidTxtID.h"


/** Implements the story thread (ITextStoryThread) that represents
	hidden text.

	
	@ingroup hiddentext
	@see ITextStoryThread
 */
class HidTxtStoryThread : public CPMUnknown<ITextStoryThread>
{
	public:
		/** Constructor.
			@param boss
		 */
		HidTxtStoryThread(IPMUnknown* boss);
		
		/** Destructor.
		 */
		virtual ~HidTxtStoryThread();	

	public:		
		/** @return the parcel list associated with the story thread.
		 */
        virtual IParcelList*	QueryParcelList() const;
        
        /** @return the UID of the associated story thread dictionary (ITextStoryThreadDict)
         */
        virtual UID				GetDictUID() const;
        
        /** @return kHidTxtStoryThreadDictKey, there is only one story thread in 
        	the story thread dictionary for hidden text, it has a fixed key.
         */
        virtual uint32			GetDictKey() const;
        
        /** @see ITextStoryThread::GetTextStart.
         */
        virtual TextIndex		GetTextStart(int32* pSpan) const;
        
        /** @see ITextStoryThread::GetTextEnd.
         */
        virtual TextIndex		GetTextEnd(TextIndex* pStart) const;
        
        /** @see ITextStoryThread::GetTextSpan.
         */
        virtual int32			GetTextSpan(TextIndex* pStart) const;
        
        /** @see ITextStoryThread::QueryTextModel.
         */
        virtual ITextModel*		QueryTextModel() const;
        
        /** @see ITextStoryThread::GetTextStyle.
         */
		virtual UID				GetTextStyle() const;

        /** @see ITextStoryThread::QueryParent.
         */
		virtual IScript*		QueryParent(const ScriptInfo::RequestContext& context) const;

        /** @see ITextStoryThread::GetAdjustedTextStart.
         */
		virtual TextIndex		GetAdjustedTextStart(const ScriptInfo::RequestContext& context, int32* pAdjustedSpan) const;

	private:
		virtual bool16			GetThreadRange(TextIndex& start, int32& span) const;
};

/*
*/
CREATE_PMINTERFACE(HidTxtStoryThread, kHidTxtStoryThreadImpl)

/*
*/
HidTxtStoryThread::HidTxtStoryThread(IPMUnknown* boss) : CPMUnknown<ITextStoryThread>(boss)
{
	TRACEFLOW("HiddenText", "HidTxtStoryThread::Constructor()-->In/Out\n");
}

/*
*/
HidTxtStoryThread::~HidTxtStoryThread()
{
	TRACEFLOW("HiddenText", "HidTxtStoryThread::Destructor()-->In/Out\n");
}

/*
*/
IParcelList* HidTxtStoryThread::QueryParcelList() const
{
	TRACEFLOW("HiddenText", "HidTxtStoryThread::QueryParcelList()-->In\n");
	// Ideally we should be able to have a story thread without
	// a parcel list. But the app is not happy if we don't provide
	// a stub parcel list implementation, so we do.
	InterfacePtr<IParcelList> parcelList(this, UseDefaultIID());
	ASSERT(parcelList != nil);
	TRACEFLOW("HiddenText", "HidTxtStoryThreadDict::QueryThread()-->Out, parcelList=0x%x\n", parcelList.get());
	return parcelList.forget();
}

/*
*/
UID HidTxtStoryThread::GetDictUID() const
{
	TRACEFLOW("HiddenText", "HidTxtStoryThread::GetDictUID()-->In\n");
	UID result = ::GetUID(this);
	ASSERT(result != kInvalidUID);
	TRACEFLOW("HiddenText", "HidTxtStoryThread::GetDictUID()-->Out\n");
	return result;
}

/*
*/
uint32 HidTxtStoryThread::GetDictKey() const
{
	TRACEFLOW("HiddenText", "HidTxtStoryThread::GetDictKey()-->In/Out\n");
	return kHidTxtStoryThreadDictKey;
}

/*
*/
TextIndex HidTxtStoryThread::GetTextStart(int32* pSpan = nil) const
{
	TRACEFLOW("HiddenText", "HidTxtStoryThread::GetTextStart()-->In\n");
	TextIndex result = kInvalidTextIndex;
	do {
		TextIndex start = kInvalidTextIndex;
		int32 span = 0;
		if (this->GetThreadRange(start, span) != kTrue) {
			break;
		}
		if (pSpan != nil) {
			*pSpan = span;
		}
		result = start;
	} while(false);
	TRACEFLOW("HiddenText", "HidTxtStoryThread::GetTextStart()-->Out result=%d\n", result);
	return result;
}

/*
*/
TextIndex HidTxtStoryThread::GetTextEnd(TextIndex* pStart = nil) const
{
	TRACEFLOW("HiddenText", "HidTxtStoryThread::GetTextEnd()-->In\n");
	TextIndex result = kInvalidTextIndex;
	do {
		TextIndex start = kInvalidTextIndex;
		int32 span = 0;
		if (this->GetThreadRange(start, span) != kTrue) {
			break;
		}
		if (pStart != nil) {
			*pStart = start;
		}
		result = start + span;
	} while(false);
	TRACEFLOW("HiddenText", "HidTxtStoryThread::GetTextEnd()-->Out result=%d\n", result);
	return result;
}

/*
*/
int32 HidTxtStoryThread::GetTextSpan(TextIndex *pStart = nil) const
{
	TRACEFLOW("HiddenText", "HidTxtStoryThread::GetTextSpan()-->In\n");
	int32 result = 0;
	do {
		TextIndex start = kInvalidTextIndex;
		int32 span = 0;
		if (this->GetThreadRange(start, span) != kTrue) {
			break;
		}
		if (pStart != nil) {
			*pStart = start;
		}
		result = span;
	} while(false);
	TRACEFLOW("HiddenText", "HidTxtStoryThread::GetTextSpan()-->Out result=%d\n", result);
	return result;
}

/*
*/
ITextModel* HidTxtStoryThread::QueryTextModel() const
{
	TRACEFLOW("HiddenText", "HidTxtStoryThread::QueryTextModel()-->In\n");
	ITextModel* result = nil;
	do {
		InterfacePtr<IHidTxtModel> hidTxtModel(this, UseDefaultIID());
		ASSERT(hidTxtModel != nil);
		if (hidTxtModel == nil) {
			break;
		}
		result = hidTxtModel->QueryTextModel();
	} while(false);
	TRACEFLOW("HiddenText", "HidTxtStoryThread::QueryTextModel()-->Out result=0x%x\n", result);
	return result;
}

/*
*/
bool16 HidTxtStoryThread::GetThreadRange(TextIndex& start, int32& span) const
{
	TRACEFLOW("HiddenText", "HidTxtStoryThread::GetThreadRange()-->In\n");
	bool16 result = kFalse;
	do {
		InterfacePtr<IHidTxtModel> hidTxtModel(this, UseDefaultIID());
		ASSERT(hidTxtModel != nil);
		if (hidTxtModel == nil) {
			break;
		}
		result = hidTxtModel->GetHiddenTextRange(start, span);
	} while(false);
	TRACEFLOW("HiddenText", "HidTxtStoryThread::GetThreadRange()-->Out result=%d, start=%d, span=%d\n",
		result,
		start,
		span);
	return result;
}

/*
*/
UID HidTxtStoryThread::GetTextStyle() const
{
	return kInvalidUID;
}

/*
*/
IScript* HidTxtStoryThread::QueryParent(const ScriptInfo::RequestContext& context) const
{
	//
	// Our story threads are not a host to generic Text Script Objects (words,
	// lines, etc) so we don't need to return anything for this.
	//
	return nil;
}

/*
*/
TextIndex HidTxtStoryThread::GetAdjustedTextStart(const ScriptInfo::RequestContext& context, int32* pAdjustedSpan) const
{
	return GetTextStart(pAdjustedSpan);
}

// End, HidTxtStoryThread.cpp
