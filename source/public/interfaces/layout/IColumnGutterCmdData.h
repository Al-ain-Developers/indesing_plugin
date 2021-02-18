//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IColumnGutterCmdData.h $
//  
//  Owner: psorrick
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
#ifndef __IColumnGutterCmdData__
#define __IColumnGutterCmdData__

#include "IPMUnknown.h"
#include "SpreadID.h"
#include "PMReal.h"

class IDataBase;

/** Data interface for set columns command.
	@ingroup layout_column
	@see kSetColumnGutterCmdBoss 
*/
class IColumnGutterCmdData : public IPMUnknown
{
public:

	/**	Set the value of the new gutter width to be set in the kSetColumnGutterCmdBoss.
		@param gutter the value to use (in points).
	 */
	virtual void Set( const	PMReal&	gutter) = 0;

	/**	Return the gutter value from the data interface.
		@return PMReal& the gutter value (in points). 
	 */
	virtual const PMReal& GetGutter() const = 0;
};




#endif // __IColumnGutterCmdData__
