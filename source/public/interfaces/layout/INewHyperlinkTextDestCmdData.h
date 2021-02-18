//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/INewHyperlinkTextDestCmdData.h $
//  
//  Owner: Craig Rainwater
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
#ifndef	NEWHYPERLINKTEXTDESTCMDDATA_H
#define NEWHYPERLINKTEXTDESTCMDDATA_H

#include "HyperlinkID.h"
#include "IPMUnknown.h"

// ===================================================================================
//	class INewHyperlinkTextDestCmdData
// ===================================================================================
/** Command data interface, set/get the text destination data for the command kNewHyperlinkTextDestCmdBoss
*/
class INewHyperlinkTextDestCmdData : public IPMUnknown {

//-----------------------------------
//	Constants
//
public:
	enum {kDefaultIID = IID_INEWHYPERLINKTEXTDESTCMDDATA};

//-----------------------------------
//
public:

/**	Get method to get whether or not to add the text destination marker character to the model or use the existing
    character
	@param none
	@return bool16 kTrue = the create command should use the existing character (caller guarantees it is a valid character)
 */
	virtual bool16		GetShouldUseExistingCharacter() const = 0;

/**	Set method to set whether or not to add the text destination marker character to the model or use the existing
    character.  The caller who sets this to kTrue guarantees that the correct character is 
	in the text model at the location where the text destination marker should exist.
	@param shouldUse
 */
	virtual void		SetShouldUseExistingCharacter(const bool16 shouldUse) = 0;

/** Get whether or not the text destination is a paragraph destination
	@return bool16 kTrue = paragraph destination
*/
	virtual bool16 IsParagraphDestination() const = 0;

/** Set whether or not the text destination is a paragraph destination
	@param isParagraph - kTrue if the destination is a paragraph destination.
*/
	virtual void SetIsParagraphDestination(bool16 isParagraph) = 0;

/** Get whether or not a new destination is created by the command
	@return bool16 kTrue = new destination created
*/
	virtual bool16 NewDestCreated() const = 0;
	
/** Set whether or not a new destination is created.
	@param created - kTrue if a new destination is created.
*/
	virtual void SetNewDestCreated(bool16 created) = 0;

/**	Get destination unique key
	@return int32 unique key
 */
	virtual int32 GetUniqueKey() const = 0;
/**	Set unique key value
	@param uniqueKey unique key
 */
	virtual void SetUniqueKey(int32 uniqueKey) = 0;
		
};


#endif	// NEWHYPERLINKTEXTDESTCMDDATA_H
