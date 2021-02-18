//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ISetRepaginationCmdOptions.h $
//  
//  Owner: Pushp Agarwal
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

#ifndef __ISETREPAGINATIONCMDOPTIONS__
#define __ISETREPAGINATIONCMDOPTIONS__

#include "PMTypes.h"
#include "BookID.h"
#include "IPMUnknown.h"
/**
	Interface to set/get options to kSetRepaginationCmdBoss 
	@ingroup layout_book
*/
class ISetRepaginationCmdOptions: public IPMUnknown
{
public:
	enum
   {
       kDefaultIID = IID_ISETREPAGINATIONCMDOPTIONS
   };
	/**
		It specifies which numbering to be updated during command execution 
		It can be any combination of Page numbering, Chapter Numbering and Paragraph Numbering
	*/
	enum UpdateOptionsEnum 
	{
		/** Update page numbers */
		kUpdatePageNumbers = 1,
		/** Update chapter numbers */ 
		kUpdateChapterNumbers = 2,
		/** Update paragraph numbers */
		kUpdateParagraphNumbers = 4,
		/** Update chapter and paragraph numbers */
		kUpdateChapterAndParagrapghNumbers = kUpdateChapterNumbers|kUpdateParagraphNumbers,
		/** Update all numbering */
		kUpdateAll = 0xFF
		
	};

	/**
		Sets the update options i.e. specifies which numbering to be updated during  execution of
		kSetRepaginationCmdBoss
		@param	updateOptions [IN] combination of numbering to be updated in command
	*/
	virtual void SetUpdateOptions(ISetRepaginationCmdOptions::UpdateOptionsEnum updateOptions = kUpdatePageNumbers) = 0;
	/**
		Gets the update options i.e. retrieves combination of numberings to be updated during  execution of
		kSetRepaginationCmdBoss
		@return	updateOptions: combination of numbering to be updated in command
	*/
	virtual ISetRepaginationCmdOptions::UpdateOptionsEnum GetUpdateOptions() const = 0;
};

#endif // __ISETREPAGINATIONCMDOPTIONS__