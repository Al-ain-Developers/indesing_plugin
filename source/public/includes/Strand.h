//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/Strand.h $
//  
//  Owner: robin briggs
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
#ifndef __STRAND__
#define __STRAND__

#include "IStrand.h"
#include "HelperInterface.h"
#include "CPMUnknown.h"
#include "VOSSavedData.h"
#include "IStrandPastePiece.h"

class StrandPastePiece;


#ifdef PUBLIC_BUILD
#pragma export on
#endif

class PUBLIC_DECL Strand : public IStrand
{
	public:
		Strand(IPMUnknown *boss);
			
		virtual UID	CreatePage () = 0;
		virtual UID GetFirstPage();
 		virtual UID SetFirstPage(UID firstPage);
			
		virtual ClassID GetObjectClass() const = 0;
		
		virtual ICommand* QueryRemoveFromDocumentCmd(UID textModelUID);

			// hardly any strands will care about damage. This does nothing
		virtual void ForceCompositionDamage(TextIndex position, int32 numChars);
    // hardly any strands will care about damage. This does nothing
    virtual void ForceContentDamage(TextIndex position, int32 numChars){}

		virtual UID GetOwningStoryUID() const;
		virtual void StrandAttachedToStory(UID textModelUID, int32 length);
		virtual void StrandDetachedFromStory(UID textModelUID);
		
		virtual void	InsertStoryThread(UID dictUID, uint32 dictKey,
								const WideString* data, TextIndex pos);
		virtual bool16		CreateStoryThreads(UID dictUID,
										const K2Vector<uint32>& dictKeyList,
										const K2Vector<int32>& lenList,
										TextIndex pos);
		virtual bool16		JoinStoryThreads(TextIndex start, int32 len);
		virtual void		IncreaseSpan(TextIndex at, int32 len);

		virtual void		CollectMementosForDelete(TextIndex pos, int32 len,
											MementoList& list)
			{ CollectMementos(pos, len, list); }
		virtual void		CollectMementosForCut(TextIndex pos, int32 len,
											MementoList& list)
			{ CollectMementos(pos, len, list); }
		virtual void		CollectMementosForCopyRange(TextIndex pos, int32 len,
											MementoList& list) const
			{ CollectMementos(pos, len, list); }
		virtual void		CollectMementosForReplace(TextIndex pos, int32 len,
											MementoList& list)
			{ CollectMementos(pos, len, list); }

		virtual void Delete(TextIndex startpos, int32 numchars);
		virtual void Replace(const boost::shared_ptr<ITextModel::ReplacementList  >& replList, bool16 clearNonContinuingAttrs);
		void ReadWrite(IPMStream *s, ImplementationID prop);
			
	protected:
		UID								CreatePage (ClassID pageClass);

		virtual void		CollectMementos(TextIndex pos, int32 len,
											MementoList& list) const;

		UID fStoryUID;
		
	private:
		UID fFirstPage;

DECLARE_HELPER_METHODS()
};



class PUBLIC_DECL StrandPastePiece : public CPMUnknown<IStrandPastePiece>
{
	public:
		StrandPastePiece(IPMUnknown* boss) :
			CPMUnknown<IStrandPastePiece>(boss),
			fVOSData(nil)
			{ }

		virtual	~StrandPastePiece()
			{ if (fVOSData) delete fVOSData; }

		//
		// Inherited methods.
		//
		virtual ClassID			GetStrandClassID() const
			{ return fStrandID; }

		virtual ErrorCode			OnCopyRange()
			{ return fVOSData? fVOSData->OnCopy() : kSuccess; }

		virtual ErrorCode			PreTransferTo(PasteDataXRefContext* xRefC)
			{ return fVOSData? fVOSData->PreTransferTo(xRefC) : kSuccess; }

		virtual ErrorCode			TransferTo(PasteDataXRefContext* xRefC)
			{ return fVOSData? fVOSData->TransferTo(xRefC) : kSuccess; }

		virtual ErrorCode			OnPaste()
			{ return fVOSData? fVOSData->OnPaste() : kSuccess; }

		//
		// Additional methods.
		//
		virtual void			SetStrandClassID(ClassID strandID)
			{ fStrandID = strandID; }
		virtual void			SetVOSData(VOS_SavedData *d)
			{
			if (fVOSData)
				delete fVOSData;
			fVOSData = d;
			}

		virtual VOS_SavedData*	PeekVOSData() const
			{ return fVOSData; }

	protected:
		ClassID				fStrandID;
		VOS_SavedData*		fVOSData;
};

// pre-2.0 IStrand implementations that derived from Strand only persisted
// the fFirstPage field. This conversion adds in a kInvalidUID fStoryUID
// field which will be initialized by a phase2 conversion call to
// IStrand::StrandAttachedToStory(newStoryUID, 0) from the Text plugin.
PUBLIC_DECL void ConvertCStrandImpl(IPMStream* inStream, IPMStream* outStream);


#ifdef PUBLIC_BUILD
#pragma export off
#endif


#endif		// __STRAND__
