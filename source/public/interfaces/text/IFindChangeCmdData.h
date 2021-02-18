//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IFindChangeCmdData.h $
//  
//  Owner: Bryce Morsello
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
#ifndef __IFINDCHANGECMDDATA__
#define __IFINDCHANGECMDDATA__

#ifndef __IPMUnknown__
#include "IPMUnknown.h"
#endif

#include "ITextWalker.h"
#include "IFindChangeService.h"
#include "TextWalkerServiceProviderID.h"
class IFindChangeOptions;
class RangeProgressBar;
// Note: Overset Text control user interface is removed from Find/Change panel.  
// Its functionality always includes overset text.
// Wai 5/5/98

/** 
	@ingroup text_find
*/
class IFindChangeCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IFINDCHANGECMDDATA };

	/**	
		Gets find change result.

		@return IFindChangeService::FindChangeResult		Find change result in the command data.
	 */
	virtual IFindChangeService::FindChangeResult GetFindChangeResult() const = 0;
	/**	
		Sets find change result.

		@param nResult		Find change result to set in the command data.
	 */
	virtual void SetFindChangeResult(IFindChangeService::FindChangeResult nResult) = 0;

	/**	
		Returns text story range.

		@param first	[OUT] Start text index for the range.
		@param last	[OUT] End text index for the range.
		
		@return UIDRef&		Text story for the range retrieved.
	 */
	virtual UIDRef& GetRange( TextIndex& first, TextIndex& last) const = 0;
	/**	
		Sets text story range.

		@param textStory	Text story to set the range.
		@param first	Start text index for the range.
		@param last	End text index for the range.
	 */
	virtual void SetRange( const UIDRef& textStory, TextIndex first, TextIndex last) = 0;

	/**	
		Sets replacement count.

		@param nCount	Replacement count to set to.
	 */
	virtual void SetReplacementCount(int32 nCount) = 0;
	/**	
		Gets replacement count.

		@return int32	Replacement count returned.
	 */
	virtual const int32 GetReplacementCount() const = 0;

	/**	
		Gets text walker.

		@return ITextWalker*	Text walker retrieved.
	 */
	virtual ITextWalker* QueryTextWalker() = 0;
	/**	
		Sets text walker.

		@param TextWalker	Text walker to set to.
	 */
	virtual void SetTextWalker(ITextWalker* TextWalker) = 0;

};

#endif
