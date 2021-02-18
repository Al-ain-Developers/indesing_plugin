//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/VOSRedline.h $
//  
//  Owner: Eric Menninga
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
//  ADOBE CONFIDENTIAL
//  
//  The following classes are defined: VOSRedlineChange, RedlineUndo, and VOS_RedlineObject.
//  Public because the RedlineIterator can return a VOSRedlineChange and VOS_RedlineObject;
//  however, the RedlineIterator should be considered the primary access to tracked changes.
//  
//========================================================================================

#pragma once
#ifndef __VOS_Redline__
#define __VOS_Redline__

#include "VOSObject.h"
#include "VOSCursor.h"
#include "K2Vector.h"
#include "WideString.h"
#include "K2Vector.h"
#include "XMLReference.h"

#ifdef DEBUG
#include "Trace.h"
#endif

class IRedlineDataStrand;
class ITextIndexIDList;
class ITextModel;


	// I didn't make this a virtual class with specializations for insert, delete, apply, etc. because
	// the stack of these changes wouldn't be able to hold pointers to virtual objects unless every
	// editing operation did a physical copy of every element. It was easier and more straightforward
	// to have the collect handle the copies with data.
class VOSRedlineChange
{
	public:
		typedef object_type data_type;
		typedef enum { kUnknown = 0, kDelete, kInsert, kApply } RedlineChangeType;
		// valid change types, kApply not used

		VOSRedlineChange(
			RedlineChangeType type,
			uint64 stamp,
			bool16 movedText,
			IDataBase *docDB = nil,
			IRedlineDataStrand *strand = nil,
			int32 len = 0);
		// constructor

		VOSRedlineChange()
			: fType(kUnknown)
			, fTimeStamp(0)
			, fIsMovedText(kFalse)
			, fUserName("")
			{}
		// default constructor

		VOSRedlineChange(const VOSRedlineChange &rhs);
		// copy constructor

		RedlineChangeType GetChangeType() const 
			{ return fType; }
	
		PMString GetUserName() const 
			{ return fUserName; }
		void SetUserName(const PMString& userName) 
			{ fUserName = userName; }
#ifdef DEBUG
		void PrintUser() const
			{ TRACE("(%s) ", fUserName.GetUTF8String().c_str()); }
		int32 GetUserID() const // obsolete, do not use!
			{ return -1; }
#endif

		uint64 GetTimeStamp() const
			{ return fTimeStamp; }
		void SetTimeStamp(uint64 i)
			{ fTimeStamp = i; }
			
		bool16 GetIsMovedText() const
			{ return fIsMovedText; }
		void SetIsMovedText(bool16 isMovedText)
			{ fIsMovedText = isMovedText; }

		bool16 GetIsDeletedText() const
			{ return fType == VOSRedlineChange::kDelete; }
		bool16 GetIsAddedText() const
			{ return fType == VOSRedlineChange::kInsert && !fIsMovedText; }

		bool16 operator==(const VOSRedlineChange& other) const
			{ return fTimeStamp == other.fTimeStamp && fType == other.fType && fUserName == other.fUserName && fIsMovedText == other.fIsMovedText; }
		// allows comparisons between objects of this type

	protected:
		uint64				fTimeStamp;			// time the change was created
		RedlineChangeType	fType;				// type of the change
		PMString			fUserName;			// name of the author that created the change
		bool16				fIsMovedText;		// flag to indicate if a kInsert type change is considered moved text 
												// - text pasted from within the same document or duplicated
};


typedef K2Vector<VOSRedlineChange>	RedlineChangeUndo;


class RedlineUndo
{
	public:
		RedlineUndo(int32 len, VOSRedlineChange::RedlineChangeType type);
		virtual void Undo(TextIndex start);
		
		void Target(const UIDRef& strand);

	private:
		UIDRef		fStrand;
		int32		fLength;	
#ifdef DEBUG
		VOSRedlineChange::RedlineChangeType		fType;
#endif
};


class RedlineUndo;
class IStrandPastePiece;

class VOS_RedlineObject : public VOS_Object
{
	protected:
		VOS_RedlineObject(const VOS_RedlineObject& copy)
			: VOS_Object(copy)
			, fLength(copy.fLength)
			, fChangeStack(copy.fChangeStack)
		{}

	public:
		VOS_RedlineObject(int32 length = 0)
			: VOS_Object()
			, fLength(length)
			, fChangeStack()
			{}
		VOS_RedlineObject(int32 length, const VOSRedlineChange& change);
		virtual ~VOS_RedlineObject();

		virtual int32 VirtualLength() const;
		virtual VOS_Object* Duplicate() const;
		virtual VOS_Object* Divide(int32 atOffset);
		virtual bool16 JoinWith(VOS_Object* next);
		virtual VOS_Object* Split() { return nil; }; // SNOWBIRD:TO:DO

		void SetLength(int32 len);
		void AdjustLength(int32 delta)
			{ PreDirty(); fLength += delta; AdjustObjectLength(delta); ASSERT_MSG(fLength > 0, "VOS_RedlineObject too small"); }
	
		int32 NumberOfChanges() const
			{ return fChangeStack.size(); }
		const VOSRedlineChange& GetChange(int32 n) const
			{ return fChangeStack[n]; }
		RedlineChangeUndo* AcceptThrough(const VOSRedlineChange& change, IRedlineDataStrand *redline);
		RedlineChangeUndo* RejectChange(const VOSRedlineChange& change, IRedlineDataStrand *redline, TextIndex start, bool16 *removeObj);
		void UndoChanges(RedlineChangeUndo *undo, bool16 undoReject, VOS_Cursor& cursor, int32 len);

		void ReadWrite(IPMStream *s, ImplementationID prop);

		static const PMString CurrentUser(VOS_RedlineObject *qThis);

		static void Insert(VOS_Cursor& cursor, IRedlineDataStrand *redline, int32 len, bool16 trackInsert, const VOSRedlineChange *useThisChange, bool16 pasting, bool16 isNoteChar, bool16 isTableContinuation = kFalse, bool16 isSaveBack = kFalse);
		static RedlineUndo* ChangeAttribute(VOS_Cursor& cursor, int32 len);
		static RedlineUndo* DoReplace(VOS_Cursor& cursor, IRedlineDataStrand *redline, TextIndex pos, int32 len, const WideString *newData);
		static IStrandPastePiece* Cut(VOS_Cursor& cursor, IRedlineDataStrand *redline, TextIndex pos, int32 len, bool16 trackThisEdit);
		static void InsertSavedData(VOS_Cursor& cursor, VOS_SavedData *data, IRedlineDataStrand *redline);
		static void UnreplaceSavedData(VOS_Cursor& cursor, VOS_SavedData *data);

		static bool16 CanApplyDeleteChange(VOS_Cursor& cursor, int32 len);
		// returns true when deleting text that was *not* inserted by the current user,
		// in that case do not want to create a delete change record; false otherwise

#ifdef DEBUG
		static void UndoSimpleChange(VOS_Cursor& cursor, int32 len, VOSRedlineChange::RedlineChangeType type);
#else
		static void UndoSimpleChange(VOS_Cursor& cursor, int32 len);
#endif

		// the following methods are used to move the change records on the end of
		// story character (if any) when entire story is moved;

		RedlineChangeUndo* MoveChangeRecord(VOS_Cursor& cursor);
		// removes this vos object's change records and moves the specified cursor's 
		// vos object change records to this vos object
		bool16 UndoMoveChangeRecord(RedlineChangeUndo* undo);
		// removes this vos object's change records and moves the change records 
		// in the specified undo to this vos object

		static bool16 CanApplyDeleteChange(VOS_Cursor& cursor, int32 len, const PMString& user);
		// returns true when deleting text that was *not* inserted by the specified user,
		// in that case do not want to create a delete change record; false otherwise
		
		void AppendChangeRecord(const VOSRedlineChange& change);
		// Append a record to the change stack
		void RemoveChangeRecord(int32 changeIndex);
		// Remove a record to the change stack
		void ClearChangeStack() { fChangeStack.clear(); }

	private:
		int32						fLength;		// length of this object
		K2Vector<VOSRedlineChange>	fChangeStack;	// list of change records on this object
};



#endif
		//  __VOS_Redline__
		
