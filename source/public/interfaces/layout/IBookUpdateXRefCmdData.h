//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IBookUpdateXRefCmdData.h $
//  
//  Owner: Jianlan Song
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

#include "HyperlinkID.h"

/** Command data interface associated with command to update cross references in book (kBookBoss). 
	The command will go through the cross references in all the documents inside the book and update 
	them if needed.

	@ingroup layout_book
	@see kBookUpdateXRefCmdBoss 
*/
class IBookUpdateXRefCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IBOOKUPDATEXREFCMDDATA };

		/**	Set command data.
			@param sysFile - the book file to be updated.
		*/
		virtual void Set(const IDFile& sysFile) = 0;

		/**	Get the book file to be updated.
			@return IDFile - the book file.
		*/
		virtual IDFile GetBookFile() = 0;

		/**	Set the book file.
			@param BookFile - the book file.
		*/
		virtual void SetBookFile(const IDFile& BookFile) = 0;
};

