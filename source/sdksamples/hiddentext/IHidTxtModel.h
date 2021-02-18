//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hiddentext/IHidTxtModel.h $
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

#ifndef __IHIDTXTMODEL__
#define __IHIDTXTMODEL__

#include "IPMUnknown.h"
#include "HidTxtID.h"

class ITextModel;

/** From SDK sample; signature interface for the hidden text model (kHidTxtModelBoss) that
	manages the hidden text.

	
	@ingroup hiddentext
 */
class IHidTxtModel : public IPMUnknown
{
	public:
		/** kDefaultIID */
		enum { kDefaultIID = IID_IHIDTXTMODEL };

	// Methods in this section can be called by any client.
	public:
		/** Return interface pointer to the text model that stores the hidden text.
			 @return interface pointer to the text model that stores the hidden text,
					nil if this is not known.
		 */
		virtual ITextModel*	QueryTextModel() const = 0;
		
		/** Provides the range of text in the text model on which the hidden text is anchored.
			@param start index in the text model where the hidden text is anchored.
			@param span currently always 1 since hidden text is anchored on a kTextChar_ZeroSpaceNoBreak character.
			@return kTrue on if data is available, kFalse otherwise.
		 */
		virtual bool16		GetAnchorTextRange(TextIndex& start, int32& span) const = 0;
		
		/** Provides the range of text in the text model in which the hidden text is stored.
			@param start index in the text model to the first character of hidden text
			@param span number of characters of hidden text stored (>= 1 since
				hidden text is always terminated by a kTextChar_CR character).
			@return kTrue on if data is available, kFalse otherwise.
		 */
		virtual bool16		GetHiddenTextRange(TextIndex& start, int32& span) const = 0;

	// Methods in this section can by called by commands that
	// manipulate the hidden text model or by implementations
	// that form part of the hidden text model.
	public:
		/** Associate this boss object with the given text model and anchor it on the given TextIndex.
			@param textModelUID
			@param anchorTextIndex
		*/
		virtual ErrorCode	AttachToTextModel(UID textModelUID, const TextIndex& anchorTextIndex) = 0;

		/** Disassociate this boss object from the text model.
	
		*/		
		virtual ErrorCode	DetachFromTextModel() = 0;
		
		/** @return kTrue if this boss object is associated with hidden text content in the text model,
				kFalse otherwise.
		 */
		virtual bool16		GetConnectedToTextContent() const = 0;
		
		/** Set or clear the ConnectedToTextContent flag; at certain stages during text model operations 
			the hidden text model may not be completely connected to the story thread in the text model that
			stores the hidden text.
			@param connected kTrue if this boss object is associated with hidden text content in the text model,
				kFalse otherwise.
		 */
		virtual void		SetConnectedToTextContent(bool16 connected) = 0;
};	

#endif // __IHIDTXTMODEL__

