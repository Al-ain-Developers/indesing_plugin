//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IXRefFormatCmdData.h $
//  
//  Owner: Jianlan Song
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

#include "IPMUnknown.h"
#include "HyperlinkID.h"

#include "XRefBuildingBlock.h"

/** Abstract interface to cross reference format command data.
	@see kXRefBuildingBlockBoss 
*/
class IXRefFormatCmdData : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_IXREFFORMATCMDDATA };

	/**	Set the name of the format
		@param formatName - The new name to use
	 */
	virtual void			SetName(const PMString & formatName) = 0;
	/**	Get the name of the format 
		@return PMString - The name of the format
	 */
	virtual PMString		GetName() const = 0;
	/**	Return kTrue if we are changing the name
		@return bool16 - kTrue if name is changed
	 */
	virtual bool16			ChangingName() const = 0;
	
	/**	Set the character style of the format
		@param charStyle - The new character style to use
	 */
	virtual void			SetCharStyle(UID charStyle) = 0;
	/**	Get the character style of the format 
		@return UID - The character style UID of the format
	 */
	virtual UID			GetCharStyle() const = 0;
	/**	Return kTrue if we are changing the character style
		@return bool16 - kTrue if character style is changed
	 */
	virtual bool16			ChangingCharStyle() const = 0;
		
	/**	Set the building blocks list to the format
		@param buildingBlocks - building blocks list
	 */
	virtual void SetBuildingBlocks(const K2Vector<XRefBuildingBlock>& buildingBlocks) = 0;
	/**	Get the building blocks list of the format
		@param K2Vector<XRefBuildingblock>& - [OUT]list of building blocks
	*/
	virtual void GetBuildingBlocks(K2Vector<XRefBuildingBlock>& buildingBlocks) const = 0;
	/** Return kTrue if we are changing building blocks
		@return bool16 - kTrue if building blocks are changed
	*/
	virtual bool16	ChangingBuildingBlocks() const = 0;
};



