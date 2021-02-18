//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/DataWrapper.h $
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
//  
//  A DataWrapper is a safe way of passing around information that is owned
//  by a persistent object. It maintains a reference to the persistent object
//  and a pointer to the data that is wanted. Thus, when the datawrapper leaves
//  scope, the persistent object is released, which allows the datawrapper's data
//  to be deleted.
//  
//========================================================================================

#pragma once
#ifndef __DATAWRAPPER__
#define __DATAWRAPPER__

#include "VOSObject.h"
#include "WideString.h"


/** The DataWrapper template object is used to hold data contained in the text system
	without making a copy.  It has the data pointer, and also the ref-counted object
	that owns the data.
	@see VOS_Object
	@see VOSDiskPage
*/
template <class DataT>
class DataWrapper
{
	public:
		DataWrapper() :fBlock(nil), fData(nil)
			{}
		DataWrapper(VOS_Object* block, const DataT* list) :fBlock(block), fData((DataT *)list)
			{ if (fBlock) fBlock->AddRef(); }

		DataWrapper(const DataWrapper<DataT>& copy) :fBlock(copy.fBlock), fData(copy.fData)
			{ if (fBlock) fBlock->AddRef(); }

		DataWrapper<DataT>& operator=(const DataWrapper<DataT>& copy);

		~DataWrapper()
			{ if (fBlock) fBlock->Release(); }

		/** Get the pointer to the data. It is const because you
			cannot change the data here, it is the model's data.
			@return a pointer to the data.
		*/
		operator const DataT* () const
			{ return fData; }

		/** Get the pointer to the data. It is const because you
			cannot change the data here, it is the model's data.
			@return a pointer to the data.
		*/
		const DataT* get() const
			{ return fData; }

	private:
		VOS_Object	*fBlock;
		DataT		*fData;
};



/** The specialized DataWrapper<textchar> object is used to hold text contained in the text system
	without making a copy.  It has the pointer to the text, and also the ref-counted object
	that owns the data.
	@see VOS_Object
	@see VOSDiskPage
*/
template <> class DataWrapper<textchar>
{
	public:
		DataWrapper() :fBlock(nil), fData(nil), fCharOffset(0)
			{}
		DataWrapper(VOS_Object* block, const WideString* str, int32 charOffset)
				 :fBlock(block), fData(str), fCharOffset(charOffset)
			{ if (fBlock) fBlock->AddRef(); }

		DataWrapper(const DataWrapper<textchar>& copy)
				 :fBlock(copy.fBlock), fData(copy.fData), fCharOffset(copy.fCharOffset)
			{ if (fBlock) fBlock->AddRef(); }

		DataWrapper<textchar>& operator=(const DataWrapper<textchar>& copy);

		~DataWrapper()
			{ if (fBlock) fBlock->Release(); }

			/** cast operator for this textchar version of DataWrapper -- get a pointer to the data.
				fCharOffset is actually unused at this time, and is only set by the constructor.
				@return a pointer to the text data. */
		operator const textchar*()
			{ return fData ? fData->GrabUTF16Buffer(nil) + fData->CodePointIndexToUTF16Index(fCharOffset) : nil; }

			/** convert this DataWrapper<textchar> into a WideStringIterator for walking over the text
				using iterator semantics.
				@see ITextIterator
				@param charOffset is the offset within this data to start iterating from.
				@return the iterator. */
		WideString::const_iterator GetIteratorAt(int32 charOffset) const;

			/** Clear the offset contained in this object. The offset isn't really used, so
				this function is pretty much useless. Will be removed. */
		void ClearOffset()
			{ fCharOffset = 0; }

			/** convert the character offset into a UTF16 buffer offset. Will return the offset when
					there are no surrogates.
				@param charOffset is the character offset.
				@return the number of UTF16 chars that the offset is equivalent to.
			*/
		int32 CharOffsetToUTF16Offset(int32 charOffset) const;

			/** Does the current data contain surrogate characters (32bit unicode values encoded using UTF16).
				@return kTrue if the buffer has multi-word unicode values. */
		bool16 HasSurrogates() const
			{ return fData->HasMultiWordUnicode(); }

			/** Accessor for the underlying string data.
			*/
		const WideString* GetData() const
			{ return fData; }

	private:
		DataWrapper<textchar>& operator+=(int32 /*charOffset*/);	// not provided -- make the compiler catch this bad call...
		DataWrapper<textchar>& operator-=(int32 /*charOffset*/);	// not provided -- make the compiler catch this bad call...

	private:
		VOS_Object		*fBlock;
		const WideString	*fData;
		int32			fCharOffset;
};



#endif
		// __DATAWRAPPER__

