//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/VOSObject.h $
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
#ifndef __VOSOBJECT__
#define __VOSOBJECT__

#include "IVOSDiskPage.h"
#include "PersistUtils.h"
#include "SnapshotInfo.h"

class scoped_snapshotdataref; 
class VOS_Cursor;
class VOS_SavedData;
class ISnapshotCache;
template <typename ItemIDType, typename ItemDataType> class ISaLRICache;

#pragma export on


/** VOS_Object is the basic object used to implement text model strands.
	Most Text Model strands are implemented as a list of VOSDiskPages, each
	containing an array of VOS_Object subclasses.
	A VOS_Cursor, returned from IVOSCache::Locate(), points to a VOS_Object.
	NOTE: This is a base class and is not derived from IPMUnknown.
	@ingroup text
	@see ITextModel
	@see IVOSCache
	@see VOS_SimpleCursor
	@see VOS_Cursor
	@see VOS_SavedData
*/
class PUBLIC_DECL VOS_Object
{
	protected:
		VOS_Object(const VOS_Object& copy);
	public:
		VOS_Object();
		VOS_Object& operator=(const VOS_Object& rhs) = delete;
		virtual ~VOS_Object();

	//-------------------------------------------------------------------------------
	/**@name 	Snapshot routines
		All snapshot routines are used by database snapshot for undo and SHOULD NOT be called directly.
	*/
	//@{-----------------------------------------------------------------------------
		SnapshotID GetSnapshotID() const;		
		void SetSnapshot(scoped_snapshotdataref& snapshot);
		bool16 IsSnapshotUptodate() const;
		void SetSnapshotNotuptodate();


	//@}-----------------------------------------------------------------------------


		/**	How many characters does this object represent?
			@return the number of characters.
		 */

		virtual int32 VirtualLength() const = 0;

		/**	Create a copy of the object. It is not placed in the data structures, only copied.
			@return a new copy.
		 */
		virtual VOS_Object* Duplicate() const = 0;

		/**	Splits the object in 2 and returns the bottom portion of the object.
			@param atOffset is the split point, 0 < atOffset < VirtualLength().
			@return the second half of the object.
		 */
		virtual VOS_Object* Divide(int32 atOffset) = 0;

		/**	Called during Write(), allows two adjacent objects that have become identical
			to combine.
			@param next is the object that occurs next in the data structure.
			@return true when the 2 objects should be joined. If so the next object isn't written out.
		 */
		virtual bool16 JoinWith(VOS_Object* next) = 0;

		/**	The object needs to read or write itself to disk.
			@param s is the IPMStream.
			@param prop is the implementationID of the object.
		 */
		virtual void ReadWrite(IPMStream *s, ImplementationID prop) = 0;

		/**	Decrement the object's ref count, may delete itself when the refcount falls below 1.
		 */
		virtual void Release();

		/**	Increment the object's ref count.
		 */
		virtual void AddRef();

		/**	PRIVATE: Used to set the object's pointer back to its container.
			@param block is the containing disk page.
		 */
		virtual void SetDiskPage(IVOSDiskPage *block);

		/**	Get without AddRef'ing the containing disk page.
			@return the containing disk page.
		 */
		IVOSDiskPage* GrabDiskPage()
			{ return fDiskPage; }

		/**	Get the relevant database.
			@return the database. Will return nil if the object isn't located in a story yet.
		 */
		IDataBase* GetDataBase() const
			{ return fDiskPage ? ::GetDataBase(fDiskPage) : nil; }

#ifdef DEBUG
		/**	Insert the object into the container in front of this object. Debug only.
			@param newone is the object to insert.
		 */
		virtual void InsertObj(VOS_Object *newone);
		/**	Append the object after the current object. Debug only.
			@param newone is the object to append.
		 */
		virtual void AppendObj(VOS_Object *newone);
#else
		/**	Insert the object into the container in front of this object.
			@param newone is the object to insert.
		 */
		void InsertObj(VOS_Object *newone)
			{ if (fDiskPage != nil) fDiskPage->InsertObj(newone, this); }

		/**	Append the object after the current object.
			@param newone is the object to append.
		 */
		void AppendObj(VOS_Object *newone)
			{ if (fDiskPage != nil) fDiskPage->AppendObj(newone, this); }
#endif


		/**	Inform the containing object that an object in the container has changed its length.
			@param delta is the adjustment to the length. Doesn't apply the delta to the object,
			just the container.
		 */
		void AdjustObjectLength(int32 delta)
			{ if (fDiskPage != nil) fDiskPage->AdjustLength(delta); }


		/**	Mark the object dirty.
		 */
		void PreDirty( bool8 dbModified = kTrue);

		/**	Is the object dirty?
			@return true if the object needs writing.
		 */
		bool16 IsDirty() const;


		/**	The VirtualKey is the absolute position of this object in a TextModel.
			@return the TextIndex of the start of this object.
		 */
		int32 VirtualKey() const
			{ return fDiskPage ? fDiskPage->LocateObjectStart(this) : 0; }


		/**	Insert the data contained in VOS_SavedData at the position specified by the cursor.
			@param cursor is the location to insert at.
			@param datalist is the data to insert.
		 */
		static void InsertSavedData(VOS_Cursor& cursor, VOS_SavedData *datalist);

	private:
		IVOSDiskPage	*fDiskPage;
		mutable int32	 fDiskPageRefCount;
		SnapshotID		fSnapshotID;
		ISnapshotCache*	fSnapshotCache;
		bool8			fSnapshotIsUptodate;
#ifdef INTERFACEPROXIES_SUPPORTED
		IVOSDiskPage	*fDiskPageProxy;
#endif
};

#pragma export off

#endif		// __VOSOBJECT__
