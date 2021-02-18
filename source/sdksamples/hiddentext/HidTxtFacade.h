//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hiddentext/HidTxtFacade.h $
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

#ifndef __HidTxtFacade_h__
#define __HidTxtFacade_h__

class UIDRef;
class WideString;

/**	Facade for the manipulation of hidden text. Suites should manipulate
	hidden text through this API.

	
	@ingroup hiddentext
 */
class HidTxtFacade
{
	public:
		/** Constructor.
			@param textModelUIDRef references story in which the hidden text is stored.
			@param anchorTextIndex index in the text model when the hidden text is anchored.
		 */
		HidTxtFacade(const UIDRef& textModelUIDRef, const TextIndex& anchorTextIndex);
		
		/** Destructor.
		 */
		virtual ~HidTxtFacade();

	public:
		/** @return kTrue if hidden text can be created, kFalse otherwise.
		 */
		virtual bool16			CanCreateHiddenText();
		
		/** Create hidden text.
			@param text the hidden text to be stored.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		virtual ErrorCode		CreateHiddenText(const WideString& text);
		
		/** @return kTrue if hidden text can be accessed, kFalse otherwise.
		 */			
		virtual bool16			CanGetHiddenText();

		/** Get hidden text.
			@param text the retrieved hidden text.
		 */
		virtual ErrorCode		GetHiddenText(WideString& text);

		/** @return kTrue if hidden text can be modified, kFalse otherwise.
		 */			
		virtual bool16			CanModifyHiddenText();

		/** Modify hidden text.
			@param text this string completely replaces the current hidden text.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		virtual ErrorCode		ModifyHiddenText(const WideString& text);

		/** @return kTrue if hidden text can be deleted, kFalse otherwise.
		 */	
		virtual bool16			CanDeleteHiddenText();

		/** Delete hidden text.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		virtual ErrorCode		DeleteHiddenText();

	private:
		const UIDRef fTextModelUIDRef;
		const TextIndex fAnchorTextIndex;
		UIDRef fHidTxtModelUIDRef;
		
	private:
		/** @return kTrue if hidden text can be changed, kFalse otherwise.
		 */			
		virtual bool16			CanChangeHiddenText();
		
		/** @return kTrue if the text modek is locked, kFalse otherwise.
		 */			
		virtual bool16			IsTextLocked();	
};

#endif

// End, HidTxtFacade.h