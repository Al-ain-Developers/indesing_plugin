//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hiddentext/HidTxtCommands.h $
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

#ifndef __HidTxtCommands_h__
#define __HidTxtCommands_h__

class WideString;
class IHidTxtModel;
class ITextModel;

/**	Utility class that processes commands for the manipulation of hidden text. 

	
	@ingroup hiddentext
 */
class HidTxtCommands
{
	public:
		/** Constructor.
		 */
		HidTxtCommands();
		/** Destructor.
		 */
		virtual ~HidTxtCommands();

	public:
		/** Process kHidTxtModelCreateCmdBoss to create an empty hidden text model.
			@param textModel refers to the text model in which the hidden text should be embedded.
			@param anchorTextIndex gives the index in the text model where the hidden text should
				be anchored.
			@return interface pointer to the created hidden text model, nil on failure.
		 */
		virtual IHidTxtModel*	Create(ITextModel* textModel, const TextIndex& anchorTextIndex) const;
		
		/** Return the hidden text model (IHidTxtModel) associated with the given anchorTextIndex or
				nil if there is no hidden text associated.
			@param textModel refers to the text model to be examined.
			@param anchorTextIndex refers to the TextIndex to be examined to see if it has hidden text
				associated.
			@return the hidden text model (IHidTxtModel) associated with the given anchorTextIndex or
				nil if there is no hidden text associated.
		 */
		virtual IHidTxtModel*	Query(ITextModel* textModel, const TextIndex& anchorTextIndex) const;
		
		/** Process kHidTxtModelModifyTextCmdBoss to update the stored hidden text.
			@param hidTxtModel refers to the hidden text model to be changed.
			@param text gives the string that should replace whatever is currently stored.
			@return kSuccess on success, kFailure otherwise.
		 */
		virtual ErrorCode		ModifyHiddenText(IHidTxtModel* hidTxtModel, const WideString& text) const;
		
		/** Apply the root paragraph style [No paragraph style] and root character style
			[No character style] to the hidden text. The text sub-system assumes all text
			in the text model has associated style information so this method is provided
			to apply such styles to hidden text.
			@param hidTxtModel refers to the hidden text model to be changed.
			@return kSuccess on success, kFailure otherwise.
		 */
		virtual ErrorCode		ClearHiddenTextStyle(IHidTxtModel* hidTxtModel) const;
		
		/** Delete hidden text by using ITextModelCmds::DeleteCmd to delete the character
			on which the hidden text is anchored. The text sub-system will call 
			HidTxtMemento to remove the associated hidden text.
			@param hidTxtModel refers to the hidden text model to be deleted.
			@return kSuccess on success, kFailure otherwise.
		 */
		virtual ErrorCode		Delete(IHidTxtModel* hidTxtModel) const;
};

#endif

// End, HidTxtCommands.h