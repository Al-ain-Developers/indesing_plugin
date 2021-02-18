//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IBookPaginateOptions.h $
//  
//  Owner: Yeming Liu
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
#ifndef __IBOOKPAGINATEOPTIONS__
#define __IBOOKPAGINATEOPTIONS__

#include "IPMUnknown.h"
#include "BookID.h"

/** This interface is used to define the pagination options. 
	@ingroup layout_book
*/
class IBookPaginateOptions : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IBOOKPAGINATEOPTIONS };

		/**
			Enum value for book repagination.
			kNextPage: such as 1,2,3,4...
			kOdd: such as 1,3,5,7...
			kEven: such as 2,4,6,8...
		*/
		typedef enum { kNextPage, kOdd, kEven } Options;

		/**	Get the paginate option.
			@param none
			@return IBookPaginateOptions::Options the pagination option.
		*/
		virtual IBookPaginateOptions::Options GetPaginateOptions() = 0;

		/**	Set the paginate option.
			@param option IN the paginate option to set
		*/
		virtual void SetPaginateOptions(IBookPaginateOptions::Options option) = 0;

		/** Get the flag about if we should insert blank page or not when the 
		    paginate option is set as kOdd or kEven.
			@param none
			@return bool16 kTrue means we will insert blank page when paginate option 
			        is kOdd or kEven, otherwise, return kFalse.
		*/
		virtual bool16 GetInsertBlankPage() = 0;

		/**	Set the flag about insert blank page.
			@param insertBlankPage IN the flag to be set.
		*/
		virtual void SetInsertBlankPage(bool16 insertBlankPage) = 0;

		/**	Get the UIDRef of the current book.
			@param none
			@return UIDRef the current book.
		*/
		virtual UIDRef GetCurrentBookUIDRef() = 0;

		/**	Set the current book.
			@param bookUIDRef IN the UIDRef of book to be set as current book.
		*/
		virtual void SetCurrentBookUIDRef(UIDRef& bookUIDRef) = 0;

		/**	Get the flag about auto repagination.
			@param none
			@return bool16 kTrue means we will to auto repagination when the chapters 
			        in the book are modified(add/delete/reorder/replace), otherwise 
					kFalse.
		*/
		virtual bool16 GetAutoRepaginateFlag() = 0;

		/**	Set the auto repagination flag.
			@param autoRepaginate IN the flag to be set.
		*/
		virtual void SetAutoRepaginateFlag(bool16 autoRepaginate) = 0;
};


#endif //__IBOOKPAGINATEOPTIONS__