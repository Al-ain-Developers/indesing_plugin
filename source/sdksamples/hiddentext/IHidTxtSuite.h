//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hiddentext/IHidTxtSuite.h $
//  
//  Owner: Adobe Developer Technologies
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

#ifndef _IHidTxtSuite_
#define _IHidTxtSuite_

// Interface includes:
#include "IPMUnknown.h"

// Forward declarations:
class WideString;

/** From SDK sample; abstract suite interface that extends the capability of selection 
	so that it can manipulate hidden text.

	
	@ingroup hiddentext
*/
class IHidTxtSuite : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IHIDTXTSUITE };

	public:
		/** @return kTrue if hidden text can be created, kFalse otherwise.
		 */
		virtual bool16			CanCreateHiddenText() const = 0;
		
		/** Create hidden text.
			@param text the hidden text to be stored.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		virtual ErrorCode		CreateHiddenText(const WideString& text) = 0;
		
		/** @return kTrue if hidden text can be accessed, kFalse otherwise.
		 */		
		virtual bool16			CanGetHiddenText() const = 0;
		
		/** Get hidden text.
			@param text the retrieved hidden text.
		 */
		virtual void			GetHiddenText(WideString& text) const = 0;
		
		/** @return kTrue if hidden text can be modified, kFalse otherwise.
		 */			
		virtual bool16			CanModifyHiddenText() const = 0;
		
		/** Modify hidden text.
			@param text this string completely replaces the current hidden text.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		virtual ErrorCode		ModifyHiddenText(const WideString& text) = 0;
		
		/** @return kTrue if hidden text can be deleted, kFalse otherwise.
		 */	
		virtual bool16			CanDeleteHiddenText() const = 0;
		
		/** Delete hidden text.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		virtual ErrorCode		DeleteHiddenText() = 0;
};

#endif // _IHidTxtSuite_
