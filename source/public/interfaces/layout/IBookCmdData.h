//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IBookCmdData.h $
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
#ifndef __IBOOKCMDDATA__
#define __IBOOKCMDDATA__

#include "IBook.h"

/** Command data interface associated with book commands.
	@see kNewBookCmdBoss
	@see kOpenBookCmdBoss
	@ingroup layout_book
*/
class IBookCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IBOOKCMDDATA };

		/**	Get the book IDFile which the command will operate on.
			@param none
			@return IDFile the book.
		*/
		virtual IDFile GetSysFile() = 0;

		/**	Set the book IDFile.
			@param sysFile IN the book to be operated on.
		*/
		virtual void SetSysFile(const IDFile& sysFile) = 0;

		/**	Get the protection level when operate on the book(like open).
			@param none
			@return IDataBase::ProtectionLevel the protection level.
		*/
		virtual IDataBase::ProtectionLevel GetProtectionLevel() = 0;

		/**	Set the protection level for operating the book.
			@param protection IN the protection level.
		*/
		virtual void SetProtectionLevel(IDataBase::ProtectionLevel protection = IDataBase::kProtectMiniSave) = 0;

		/**	Get the open options, either open exclusive or shared.
			@param none
			@return IBook::openOptions the open option.
		*/
		virtual IBook::openOptions GetOpenOption() = 0;

		/**	Set the open book options.
			@param options IN the open option.
		*/
		virtual void SetOpenOption(IBook::openOptions options) = 0;

		/**	Get the open UI flag.
			@param none
			@return UIFlags the open UI flag.
		*/
		virtual const UIFlags GetOpenUIFlag() const = 0; 

		/**	Set the open UI flag.
			@param uiFlag IN the UI flag for open operation.
		*/
		virtual void SetOpenUIFlag(const UIFlags uiFlag) = 0;
};

#endif //__IBOOKCMDDATA__