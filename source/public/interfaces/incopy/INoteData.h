//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/INoteData.h $
//  
//  Owner: Wai Cheuk
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
//  Comments: This interface saves the information about note data
//  
//========================================================================================

#pragma once
#ifndef __INOTEDATA__
#define __INOTEDATA__

#include "IPMUnknown.h"
#include "InCopySharedID.h"
#include "WideString.h"
#include "GlobalTime.h"

/**
   Represents the information of a Note object (kNoteDataBoss)

   In practice, every Note has an associated INoteData to tell who is the Author, the creation time, the modification time, and the collapsed state of the Note in galley/story view.
 */
class INoteData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_INOTEDATA };
		
		/**	Get the Author of the Note
			@param none
			@return WideString& of the Author
		*/
		virtual const		WideString& GetAuthor() const = 0;


		/**	Set the Author of the Note
			@param author WideString of the Author
		*/
		virtual void 		SetAuthor(const WideString& author) = 0;

		/**	Get the collapse state of the Note
			@param none
			@return  kTrue if the Note is collapsed
		*/
		virtual bool16 		GetCollapse() const = 0;
		
		/**	Set the collapse state of the Note
			@param collapsedState kTrue if the Note is collapsed
			@return  
		*/
		virtual void 		SetCollapse(bool16 collapsedState) = 0;

		/**	Get the creation time of the Note
			@param none
			@return GlobalTime the creation time of the Note
		*/
		virtual GlobalTime	GetCreationTime() const = 0;
		
		/**	Set the creation time of the Note
			@param newTime the creation time of the Note
		*/
		virtual void		SetCreationTime(const GlobalTime newTime) = 0;

		/**	Get the modified time of the Note
			@param none
			@return GlobalTime the modified time of the Note
		*/
		virtual GlobalTime	GetModifiedTime() const = 0;

		/**	Set the modified time of the Note
			@param newTime the modified time of the Note
		*/
		virtual void		SetModifiedTime(const GlobalTime newTime) = 0;
};

#endif // __INOTEDATA__