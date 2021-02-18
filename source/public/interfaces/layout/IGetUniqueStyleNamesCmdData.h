//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IGetUniqueStyleNamesCmdData.h $
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
//  
//  Comments: This interface is used to access the command data related to GetUniqueStyleNamesCmd.
//  
//========================================================================================

#pragma once
#ifndef __IGETUNIQUESTYLENAMESCMDDATA__
#define __IGETUNIQUESTYLENAMESCMDDATA__

#include "IBook.h"
#include "TOCID.h"

/** This command data interface is for accessing the data related to GetUniqueStyleNamesOfBookCmd.

    @see kGetUniqueStyleNamesOfBookCmdBoss.
*/
class IGetUniqueStyleNamesCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IGETUNIQUESTYLENAMESCMDDATA };

		/**	Get the name of the book where we collect all the unique styles from its documents/chapters. 
			@param none
			@return PMString& the book name.
		*/
		virtual PMString GetBookName() = 0;

		/**	Set the book name.
			@param bookName IN the book name to be set.
		*/
		virtual void SetBookName(const PMString& bookName) = 0;

		/**	Get the style type like IID_IPARASTYLEGROUPMANAGER or IID_ICHARSTYLEGROUPMANAGER.
			@param none
			@return PMIID the interface ID of the style type such as IID_IPARASTYLEGROUPMANAGER or IID_ICHARSTYLEGROUPMANAGER.
		*/
		virtual PMIID GetStyleType() = 0;

		/**	Set the style type like IID_IPARASTYLEGROUPMANAGER or IID_ICHARSTYLEGROUPMANAGER.
			@param styleType IN the interface ID of the style.
		*/
		virtual void SetStyleType(PMIID styleType) = 0;

		/**	Set the flag indicates that if we should include all the documents in the book when 
		    we do collecting unique styles.
			@param bInclude IN kTrue means include all the documents in the book.
		*/
		virtual void SetIncludeBook(const bool16 bInclude) = 0;

		/**	Get the flag indicates that if we should include all the documents in the book when 
		    we do collecting unique styles.
			@param none
			@return bool16 kTrue means we do include all the documents in book, otherwise kFalse.
		*/
		virtual bool16 GetIncludeBook() = 0;
};

#endif //__IGETUNIQUESTYLENAMESCMDDATA__