//======================================================================================== 
//   
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/contentdropper/IContentDropperAppData.h $ 
//   
//  Owner: vaggarwa 
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
#ifndef __IContentDropperAppData__ 
#define __IContentDropperAppData__ 

// ----- Interfaces -----
#include "IContentDropperDocData.h"
#include "IDataBase.h"

// ----- Includes -----
#include "CCollection.h"
#include "UIDRef.h"

// ----- ID.h files -----
#include "ContentDropperID.h"



//======================================================================================== 
// class IContentDropperAppData 
//======================================================================================== 

class IContentDropperAppData : public IPMUnknown 
{

public:
	enum { kDefaultIID = IID_ICONTENTDROPPERAPPDATA }; 


	//Iterator to traverse through the collections
	class iterator
	{
		friend class IContentDropperAppData;
		public:
			typedef IContentDropperAppData* value_type;
			bool16 operator==(const iterator& rhs) const 
			{
				return (fIndex == rhs.fIndex && fIsExpanded == rhs.fIsExpanded);
			}
			bool16 operator!=(const iterator& rhs) const
			{
				return (fIndex != rhs.fIndex || fIsExpanded != rhs.fIsExpanded);
			}

			iterator& operator++() { ++fIndex; return *this;}
			//friend CCollection* operator*(iterator iter);
			CCollection* operator*() const
			{

				if(fIsExpanded)
				{
					int32 parentIndex = fAppData->GetIndexOfRootAtHead();
					const CCollection* coll = fAppData->GetNthCollection(parentIndex);
					int32 size = coll->GetNumberOfElements();
					return coll->GetNthElement(fIndex % size);
				}
				else
				{
					int32 size = fAppData->Size();
					return fAppData->GetNthCollection(fIndex % size);
				}
			}
		private:
			IContentDropperAppData* fAppData;
			int32 fIndex;
			bool16 fIsExpanded;
			iterator();
			iterator(IContentDropperAppData* appDataPtr, int32 index, bool16 expanded) : fAppData(appDataPtr),fIndex(index), fIsExpanded(expanded) {}
	};

	friend class iterator;


	iterator begin(){ return iterator(this,this->GetHeadIndex(), this->IsHeadExpanded()); }
	
	iterator end()
	{ 
		int32 endIndex = this->GetHeadIndex();
		if(IsHeadExpanded())
		{
			int32 parentIndex = this->GetIndexOfRootAtHead();
			const CCollection* coll = this->GetNthCollection(parentIndex);
			endIndex+=coll->GetNumberOfElements();
		}
		else
		{
			endIndex+=this->Size();
		}
		return iterator(this,endIndex,IsHeadExpanded());
	}
	
	iterator LastGrabbed()
	{ 
		int32 lastIndex;

		if(IsHeadExpanded())
		{
			int32 parentIndex = this->GetIndexOfRootAtHead();
			const CCollection* coll = this->GetNthCollection(parentIndex);
			lastIndex = coll->GetNumberOfElements() - 1;
		}
		else
		{
			lastIndex = this->Size() - 1;
		}
		return iterator(this,lastIndex, IsHeadExpanded());
	}

	virtual void Create() = 0;

	/**Clear simply removes data at App level. it does not destroy any Collections. 
	   So data can be built again by calling Create.
	*/
	virtual void Clear() = 0;
    
	virtual void GrabCollection(IDataBase* db, CCollection* collection) = 0;

	/**Checks if the UIDRef is already grabbed.
	   @param uidRef - uidRef of the item to be checked
	*/
	virtual bool16 Find(const UIDRef& uidRef) const = 0;
	
	virtual void RemoveAt(int32 at)  = 0;

	virtual int32 GetNextCaptureID() = 0;

	//iterator methods
	virtual int32 Size() const = 0;
	virtual CCollection* GetFirstCollection() const = 0;
	virtual CCollection* GetNthCollection(int32 nth) const = 0;
	virtual CCollection* GetNthCollectionAndDB(int32 nth, IDataBase*& dbPtr ) const = 0;


	virtual const CCollection* GetHeadCollection()  = 0;
	virtual IDataBase*	 GetHeadCollectionDB() const = 0;
	virtual int32		 MoveHead(int32 moveAhead) = 0;
	virtual int32		 MoveHeadToFirstCollection() = 0;
	virtual int32		 MoveHeadToLastCollection() = 0;
	virtual void		 ExpandHead() = 0;
	virtual void		 CollapseHead() = 0;
	virtual bool16		 IsHeadExpanded() const = 0;
	virtual void		 RemoveAtHead() = 0;
	virtual bool16		 CanExpandHead()  = 0;
	virtual bool16		 CanCollapseHead() = 0;
	virtual PMString	 GetDescriptionString() const = 0;
	virtual int32		 GetNumOfItemsInLevel() const = 0;
protected:
	virtual int32		 GetHeadIndex() = 0;
	virtual int32		 GetIndexOfRootAtHead() const  = 0;


};




#endif
