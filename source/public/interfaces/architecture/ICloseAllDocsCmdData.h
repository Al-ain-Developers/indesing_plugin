//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ICloseAllDocsCmdData.h $
//  
//  Owner: Dave Burnard
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
#ifndef __ICloseAllDocsCmdData__
#define __ICloseAllDocsCmdData__

#include "AppFrameworkID.h"

#include "IDocumentUtils.h"

/**
	This interface is used for the close all documents commands:
		kCloseAllAndQuitCmdBoss, kCloseAllCmdBoss.
*/
class ICloseAllDocsCmdData : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_ICLOSEALLDOCSCMDDATA };

	/**
		Set whether the command may be canceled. Defaults to kTrue.
		@param whether the command may be canceled.
	*/
	virtual void SetAllowCancel( bool16 allowCancel ) = 0 ;

	/**
		Get whether the command may be canceled.
		@return whether the command may be canceled.
	*/
	virtual bool16 GetAllowCancel() const = 0 ;

	/**
		Set whether users should be allowed to save modified documents. Defaults to kAsk.
		@param promptForSave whether users should be allowed to save modified documents.
	*/
	virtual void SetPromptForSave( IDocumentUtils::PromptForSave promptForSave ) = 0 ;

	/**
		Get whether users should be allowed to save modified documents.
		@return whether users should be allowed to save modified documents.
	*/
	virtual IDocumentUtils::PromptForSave GetPromptForSave() const = 0 ;

	/**
		Set what to close (documents, books, libraries, etc.). Defaults to kCloseDocOnly.
		@param whatToClose what to close.
	*/
	virtual void SetWhatToClose( IDocumentUtils::WhatToClose whatToClose ) = 0 ;

	/**
		Get what to close (documents, books, libraries, etc.).
		@return what to close.
	*/
	virtual IDocumentUtils::WhatToClose GetWhatToClose() const = 0 ;
};

#endif // __ICloseAllDocsCmdData__
