//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/VOSSavedData.h $
//  
//  Owner: EricM
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
#ifndef __VOSSavedData__
#define __VOSSavedData__

#include "K2Vector.h"
#include "UIDRef.h"
#include "UIDList.h"
#include "KeyValuePair.h"
#include "AttributeBossList.h"
#include "K2SmartPtr.h"
#include "ErrorUtils.h"
#include "IStrand.h"
#include "ITextModelMemento.h"

class VOS_Object;
class IVOSDiskPage;
class VOS_Cursor;
class IStrandPastePiece;
class ICommand;
class PasteData;
class PasteDataXRefContext;
class IStyleRefConvSession;

typedef struct _ComboKey
{
	_ComboKey() : uid (kInvalidUID), key(0) {}
	_ComboKey(UID uidIn) : uid(uidIn), key(0) {}
	_ComboKey(UID uidIn, int32 keyIn) : uid(uidIn), key(keyIn) {}
	bool  operator==(const _ComboKey& y) const
	{
		return (uid == y.uid && key == y.key);
	}

	bool  operator<(const _ComboKey& y) const
	{
		if (uid == y.uid)
			return (key < y.key);
		else
			return (uid < y.uid);
	}

	UID uid;
	int32 key;
}ComboKey;

class PUBLIC_DECL VOS_SavedData INHERITFROM
{
	public:
		typedef enum { kTerminated, kNonterminated } VSD_ExtraInfo;

		VOS_SavedData(IStrand *whichStrand);
		VOS_SavedData(IDataBase *db, ClassID objectClass, ClassID strandClass);

		virtual ~VOS_SavedData();

		VOS_SavedData(const VOS_SavedData &) = delete;
		VOS_SavedData &operator =(const VOS_SavedData &) = delete;

		virtual int32 GetDataLength() const
			{ return fDataLength; }

		void ReadWrite(IPMStream *str);

		void RemovePage(UID pageUID);

		void AddPage(IVOSDiskPage *page);
		void AddPage (ClassID clsid, IDataBase *db, UID pageUID, int32 pageLen);
		void AddSuffix(VOS_Object *data, bool16 copy = kTrue);
		void AddPrefix(VOS_Object *data, bool16 copy = kTrue);
		void InsertPrefix(VOS_Object *data, bool16 copy = kTrue);

		void SetExtraInformation(VSD_ExtraInfo info, VOS_Object *settings = nil);
		VSD_ExtraInfo GetExtraInformation() const
			{ return fExtraInfo; }
		VOS_Object* TakeExtraSettings();
		IDataBase* GetDataBase() const
			{ return fDB; }
		ClassID GetStrandClass() const
			{ return fStrandClassID; }
		ClassID GetObjectClass() const
			{ return fObjectClassID; }

			// Ensures that that there always one or more prefixes in addition
			// to either (zero Suffixes) OR (one or more Suffixes AND zero or
			// more Pages). Or in other words, if you have pages then you have
			// prefixes and suffixes.
		void Normalize();
		void UsedUpData();
		virtual void DeletePages();
		virtual void UndeletePages();
		virtual ErrorCode OnCopy();
		virtual ErrorCode OnPaste();

		virtual ErrorCode PreTransferTo(PasteDataXRefContext* /*xRefContext*/);
		virtual ErrorCode TransferTo(PasteDataXRefContext* xRefContext);

		int32 PrefixLength() const
			{ return (int32)fPrefixList.size(); }
		int32 SuffixLength() const
			{ return (int32)fSuffixList.size(); }
		int32 PagesLength() const
			{ return fPages.size(); }

		VOS_Object* PrefixObj(int32 n) const
			{ return fPrefixList[n]; }
		VOS_Object* SuffixObj(int32 n) const
			{ return fSuffixList[n]; }
		UID PageUID(int32 n) const
			{ return fPages[n]; }

	protected:
			//
			// These internal helper methods are used by the TrasferPagesTo()
			// and TransferPagesByDuplicateTo() to handle the process of
			// duplicating or moving a VOSDiskPage to a new Story.
			//

			/**
			This method uses the StreamUtils::CreateDBStreamCopy() to duplicate
			the page.
			@param sourceStory
			@param destStory
			*/
		virtual void DuplicatePagesHelperUsingStreamCopy(PasteDataXRefContext* xRefContext);

			/**
			This method creates an empty VOSDiskPage and then uses
			TranferObjectTo() to create new VOSObjects for the new VOSDiskPage
			the page.
			@param xRefContext
			*/
		virtual void DuplicatePagesHelperUsingTransferObject(PasteDataXRefContext* xRefContext);

			/**
			This method will transfer VOSDiskPages by merely updating the
			Strand. The internal VOSObjects are not touched.
			@param xRefContent
			*/
		virtual void TransferPagesHelperNoTransferObject(PasteDataXRefContext* xRefContext);

			/**
			This method will transfer VOSDiskPages by calling TransferObjectTo()
			for each VOSObject.
			@param xRefContent
			*/
		virtual void TransferPagesHelperUsingTransferObject(PasteDataXRefContext* xRefContext);

			/**
			This method is called for each transfered Page from
			TransferPagesHelperNoTransferObject(),
			TransferPagesHelperUsingTransferObject(),
			DuplicatePagesHelperUsingStreamCopy(), and
			DuplicatePagesHelperUsingTransferObject() after processing is
			complete.
			@param page
			*/
		virtual void PageTransferred(IVOSDiskPage* /* page */)
			{ }

			//
			// TransferTo() transfers Prefixes and Suffixes via this method. The
			// implementation is responsible for determining when it is valid
			// to return oldObj and when it must create a new object.
			//
		virtual VOS_Object*	TransferObjectTo(PasteDataXRefContext* xRefC,
												VOS_Object* oldObj);

			//
			// TransferTo() transfers Cut data within the same story or to the
			// same DataBase via this method.
			//
		virtual void	TransferPagesTo(PasteDataXRefContext* xRefContext)
			{ TransferPagesHelperNoTransferObject(xRefContext); }

			//
			// TransferTo() transfers CopyRange data via this method. Note that
			// it is invalid to transfer Cut data between different DataBases,
			// it must be implemented as CopyRange/Delete.
			//
		virtual void	TransferPagesByDuplicateTo(PasteDataXRefContext* xRefContext)
			{
			DuplicatePagesHelperUsingStreamCopy(xRefContext);
			}

		ClassID							fObjectClassID;
		ClassID							fStrandClassID;
		IDataBase						*fDB;
		int32							fDataLength;
		int32							fSubRange;

	protected:

		K2Vector<VOS_Object *>			fPrefixList;
		K2Vector<VOS_Object *>			fSuffixList;
		K2Vector<UID>					fPages;
		VOS_Object						*fExtraSettings;
		ClassID							fClassOfPages;
		VSD_ExtraInfo					fExtraInfo;
		bool16							fPagesDeleted;
		bool16							fPagesAreAliases;
};


class PUBLIC_DECL PasteData
{
	public:
								PasteData(const UIDRef& story);
								PasteData(const UIDRef& fromStory, TextIndex start, int32 len);

		virtual					~PasteData();

		int32					AddSubrange();
		void					RemoveSubrange(int32 srIndex);

		void					SetSubDataRange(int32 srIndex,
											TextIndex start, int32 len)
			{ fSubrangeList[srIndex].SetDataRange(start, len); }

		void					AddMapping(int32 srIndex, ClassID cls,
											IStrandPastePiece *d);

		int32					MapCount(int32 srIndex) const
			{ return fSubrangeList[srIndex].fPasteList.size(); }

		ClassID					GetMapKey(int32 srIndex, int32 i) const
			{ return fSubrangeList[srIndex].fPasteList[i].Key(); }

		int32					Location(int32 srIndex, ClassID klas) const
			{ return FindLocation(fSubrangeList[srIndex].fPasteList, klas); }

		IStrandPastePiece*		PeekMapValue(int32 srIndex, int32 i) const
			{ return fSubrangeList[srIndex].fPasteList[i].Value(); }

		ErrorCode			CopyDone(PasteDataXRefContext* xRefContext);
		ErrorCode			CopyDone();
		ErrorCode			TransferTo(PasteDataXRefContext* xRefContext);
		ErrorCode			TransferTo(const UIDRef& toStory);
		ErrorCode			PastedAllSavedData(TextIndex start);

		const UIDRef&	GetStoryRef() const
			{ return fStoryRef; }
		void			SetStoryRef(const UIDRef& story)
			{ fStoryRef = story; }
		TextIndex		GetDataStart() const
			{ return fDataStart; }
		void			SetDataStart(TextIndex start)
			{ fDataStart = start; }
		int32			GetDataLength() const
			{ return fDataLength; }
		void			SetDataLength(int32 len)
			{ fDataLength = len; }
		int32			GetNetDataLength() const;
		void			AddMemento(const InterfacePtr<ITextModelMemento>& m);
		void			XRefBind(UID uidInSrcStory,
											UID uidInDestStory);
		void			XRefBind(UID uidInSrcStory, int32 subKeyInSrcStory,
											UID uidInDestStory, int32 subKeyInDestStory);
		bool16			XRefLookup(UID uidInSrcStory,
											UID* uidInDestStory) const;
		bool16			XRefLookup(UID uidInSrcStory, int32 subKeyInSrcStory,
											UID* uidInDestStory, int32* subKeyInDestStory) const;
		int32			GetSubrangeCount() const
			{ return fSubrangeList.size(); }
		TextIndex		GetSubrangeDataStart(int32 srIndex) const
			{ return fSubrangeList[srIndex].GetDataStart(); }
		int32			GetSubrangeDataLength(int32 srIndex) const
			{ return fSubrangeList[srIndex].GetDataLength(); }
		void			SetSubrangeDataRange(int32 srIndex,
											TextIndex start,
											int32 len)
			{ fSubrangeList[srIndex].SetDataRange(start, len); }

		AttributeBossList* GetRootStyleTransferAttributes(PMIID& whichIID);
		UID& 				GetDestRootStyle(PMIID& whichIID);
		AttributeBossList* GetDest_SrcRootStyleDiffs(PMIID& whichIID);

  		TextIndex		GetFirstRemainingTextIndex() const;
	private:
		void UpdateRootStyleConvAttrs(IDataBase* srcDB, IDataBase* destDB, InterfacePtr<IStyleRefConvSession> &styleConvSession);

		class SubRange
		{
		public:
			typedef object_type data_type;
			SubRange() : fStart(0), fLength(0), fPasteList() {}

			TextIndex GetDataStart() const
				{ return fStart; }
			int32 GetDataLength() const
				{ return fLength; }
			void SetDataRange(TextIndex start, int32 length)
				{ fStart = start; fLength = length; }
			K2Vector<KeyValuePair<ClassID, IStrandPastePiece*> >	fPasteList;
		private:
			TextIndex fStart;
			int32 fLength;
		};
		UIDRef							fStoryRef;
		TextIndex						fDataStart;
		int32							fDataLength;
		K2Vector<SubRange>				fSubrangeList;
		IStrand::MementoList						fMementoList;
		K2Vector<KeyValuePair<UID, int32>	 >	fMementoLookupList;
		K2Vector<KeyValuePair<ComboKey, ComboKey> >		fXRefLookup;
		bool16							fFromCopyRange;
		bool16							fDidTransfer;

		AttributeBossList 	fCharRootStyleTransferAttributes;
		AttributeBossList 	fParaRootStyleTransferAttributes;
		AttributeBossList	fCharDest_SrcRootStyleDiffs;
		AttributeBossList	fParaDest_SrcRootStyleDiffs;
		IDataBase*			fDB;
		UID					fCharRootStyle;
		UID 				fParaRootStyle;
};

//===================================================================================
//	class TextPasteDataXRefContext
//
//	Abstract base class for VASD XRef context.
//===================================================================================
class PasteDataXRefContext INHERITFROM
{
public:
	virtual bool16			GetIsMyContext(const PasteData* vasd) const = 0;
	virtual const UIDRef&	GetSrcStoryRef() const = 0;
	virtual const UIDRef&	GetDestStoryRef() const = 0;
	virtual void			XRefBind(UID uidInSrcStory, UID uidInDestStory) = 0;
	virtual void			XRefBind(UID uidInSrcStory, int32 subKeyInSrcStory, UID uidInDestStory, int32 subKeyInDestStory) = 0;
	virtual bool16			XRefLookup(UID uidInSrcStory, UID* uidInDestStory) const = 0;
	virtual bool16			XRefLookup(UID uidInSrcStory, int32 subKeyInSrcStory, UID* uidInDestStory, int32* subKeyInDestStory) const = 0;
};



#endif		// __VOSSavedData__
