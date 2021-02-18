//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IAddNoteDataCmdData.h $
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
//  
//  Comments: 
//  
//========================================================================================

#pragma once
#ifndef IADDNOTEDATACMDDATA_H
#define IADDNOTEDATACMDDATA_H

#include "IPMUnknown.h"
#include "NoteID.h"
#include "WideString.h"

/* Data interface for kAddNoteDataCmdBoss. Sets the properties of Note to be added.
*/
class IAddNoteDataCmdData : public IPMUnknown {

public:
		enum { kDefaultIID = IID_IADDNOTEDATACMDDATA }; 

		// IMPORTANT NOTE!
		// SHOULD NEVER HAVE TO SET THE STORY REFERENCE VIA THIS INTERFACE 
		// SINCE IT CAN BE QUERIED DIRECTLY FROM THE NOTE OWNED ITEM INTERFACE.
		// CALLING THESE TWO METHODS WILL RESULT IN ASSERTS AND kInvalidUID 
		// WILL RETURN IN GETTEXTMODEL.

/**	Not used
	@param none
	@return UID 
 */
		virtual const UID	GetTextModel() const = 0;

/**	Not used
	@param textModelUID 
 */
		virtual void		SetTextModel(const UID textModelUID) = 0;


/**	Get method for the author of the Note to be added
	@param none
	@return WideString& 
 */
		virtual const		WideString& GetAuthor() const = 0;

/**	Set method for the author of the Note to be added
	@param author 
	@return  
 */
		virtual void 		SetAuthor(const WideString& author) = 0;


/**	Get method for the collapsed state when inline Note displays
	@param none
	@return  
 */
		virtual bool16 		GetCollapse() const = 0;

/**	Set method for the collapsed state when inline Note displays
	@param collapsedState 
	@return  
 */
		virtual void 		SetCollapse(bool16 collapsedState) = 0;
};

#endif // IADDNOTEDATACMDDATA_H