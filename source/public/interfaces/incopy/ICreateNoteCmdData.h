//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/ICreateNoteCmdData.h $
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
#ifndef	CREATENOTECMDDATA_H
#define CREATENOTECMDDATA_H

#include "NoteID.h"
#include "PMRect.h"
#include "WideString.h"
#include "PMString.h"
#include "IPMUnknown.h"
#include "RangeData.h"

// ===================================================================================
//	class ICreateNoteCmdData
// ===================================================================================
/** Command data interface, set/get the Note data for the command kCreateNoteCmdBoss
*/
class ICreateNoteCmdData : public IPMUnknown {

//-----------------------------------
//	Constants
//
public:
	enum {kDefaultIID = IID_ICREATENOTECMDDATA};

//-----------------------------------
//
public:


/**	Get methose to get the author of the Note
	@param none
	@return const 
 */
	virtual const WideString& GetAuthor() const = 0;


/**	Get method to get the collapsed state for the Note
	@param none
	@return bool16 kTrue = Note will be collapsed
 */
	virtual bool16		GetCollapse() const = 0;


/**	Set method to set the collapsed state for the Note
	@param collapse 
 */
	virtual void		SetCollapse(const bool16 collapse) = 0;


/**	Set the author and collapsed state for the Note
	@param author 
	@param collapsedState kTrue = Note will be collapsed
 */
	virtual void		Set(const WideString& author, bool16 collapsedState) = 0;


/**	Get method to get the range of text going into the Note
	@param start 
	@param end 
 */
	virtual void		GetNoteContentRange(TextIndex& start, TextIndex& end) = 0;
				

/** Set method to set the range of text going into the Note
	@param start 
	@param end 
 */
	virtual void		SetNoteContentRange(TextIndex start, TextIndex end) = 0;

/**	Get method to get whether or not to add the note character to the model or use the existing
    character
	@param none
	@return bool16 kTrue = the create command should use the existing character (caller guarantees it is a valid "note" character)
 */
	virtual bool16		GetShouldUseExistingCharacter() const = 0;

/**	Set method to set whether or not to add the note character to the model or use the existing
    character.  The caller who sets this to kTrue guarantees that the special "note" character exists 
	in the text model at the location where the note is being anchored.
	@param shouldUse
 */
	virtual void		SetShouldUseExistingCharacter(const bool16 shouldUse) = 0;
};


#endif	// CREATENOTECMDDATA_H
