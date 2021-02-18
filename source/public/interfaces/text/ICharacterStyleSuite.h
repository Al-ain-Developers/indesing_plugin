//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ICharacterStyleSuite.h $
//  
//  Owner: Zak Williamson
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
//  Notes:
//  
//========================================================================================

#pragma once
#ifndef __ICharacterStyleSuite__
#define __ICharacterStyleSuite__

#include "IPMUnknown.h"
#include "TextID.h"

class PMString;
class AttributeBossList;

/** 
	@ingroup text_suite
	@ingroup text_style
*/
class ICharacterStyleSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICHARACTERSTYLESUITE };

	/** Can a style be created.
		@return Returns true if a style can be 
	*/
	virtual bool16 CanCreateStyle() const = 0;


	/**  Creates a new style based on the current selection.
		@param	parentUID	[IN] UID of the parent group where the style is being created. kInvalidUID to create at root level
		@param	position	[IN] position with in the parent, where style is going to be created. -1 to create at the end.
		@return UID of the new style
		@postcondition A unique style name is auto generated.
	*/
	virtual UID CreateStyle(UID parentUID = kInvalidUID, int32 position = -1) = 0;

	/**  Can the style of the current selection be redefined based on selected overrides.
		@return It returns false if the selection contains mixed overrides, no overrides,
		or mixed styles.
	*/
	virtual bool16 CanRedefineStyle() const = 0;


	/**  Redefines the style of the current selection based on the text attributes
		of the current selection.  (Any overrides become part of the style.)	
		@return kSuccess on success otherwise an error.
	*/
	virtual ErrorCode RedefineStyle() = 0;

	/**  Can the style of the current selection be edited.
		@return It returns false if the style cannot be edited for some reason
	*/
	virtual bool16 CanEditStyle() const = 0;


	/**  Returns selected style UID.
		@return the style UID for the first character in the selection
	*/
	virtual UID GetStyleUID() const= 0;

	/**  Constructs an AttributeBossList for the style overrides for the first character in the selection.
		@return the style overrides for the first character in the selection
		@postcondition Caller is responsibe to delete returned AttributeBossList *.
	*/
	virtual AttributeBossList * NewStyleAttributeList() = 0;
};

#endif

