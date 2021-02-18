//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/INotePrefCmdData.h $
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
//========================================================================================

#pragma once
#ifndef __INotePrefCmdData__
#define __INotePrefCmdData__

#include "IPMUnknown.h"
#include "NotePrefID.h"
#include "INotePref.h"

class INotePref;

/** kNotePrefsCmdBoss Command data interface, sets the Notes preferences values.
*/
class INotePrefCmdData : public IPMUnknown
{
public:

/**	Set the values
	@param doc Not used, since the kNotePrefsCmdBoss sets the session Notes preferences, can be UIDRef::gNull
	@param colorIndex The color index the inline Note displayed
	@param showTips kTrue means to show inline Notes tips
	@param spellCheckNote kTrue means to spell/check the inline Notes content
	@param findReplaceNote kTrue means to find/replace the inline Notes content
	@param displayChoice The type of inline Notes background color to use
	@param noteColorChoice The type of inline Notes color to use
 */
	virtual void Set(const UIDRef& doc, 
					 int32 colorIndex,
					 bool16 showTips,
					 bool16 spellCheckNote,
					 bool16 findReplaceNote,
					 INotePref::BackgroundColorChoice displayChoice,
					 INotePref::NoteColorChoice noteColorChoice) = 0;	
						

/**	Set the document 
	@param doc 
 */
	virtual void SetDocument(const UIDRef& doc) = 0;

/**	Set the inline Notes color index
	@param val 
 */
	virtual void SetColorID(const int32 val) = 0;
	

/**	Get document
	@param none
	@return const 
 */
	virtual const UIDRef& GetDocument() const = 0;

/**	Get the color index
	@param none
	@return const 
 */
	virtual const int32 GetColorID() const = 0;

/**	Show inline Notes tips or not
	@param none
	@return const kTrue means to show inline Notes tips
 */
	virtual const bool16 GetShowNoteTips() const = 0;

/**	Spell/check the inline Notes content or not
	@param none
	@return const kTrue means to spell/check inline Notes content
 */
	virtual const bool16 GetSpellCheckContent() const = 0;

/**	Find/replace the inline Notes content or not
	@param none
	@return const kTrue means to find/change inline Notes content
 */
	virtual const bool16 GetFindReplaceContent() const = 0;

/**	Get the type of inline Notes background color to use
	@param none
	@return const 
 */
	virtual const INotePref::BackgroundColorChoice GetBackgroundColorChoice() const = 0;

/**	Get the type of inline Notes color to use
	@param none
	@return const 
 */
	virtual const INotePref::NoteColorChoice GetNoteColorChoice() const = 0;

};




#endif // __INotePrefCmdData__
