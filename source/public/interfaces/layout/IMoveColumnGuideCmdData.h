//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IMoveColumnGuideCmdData.h $
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
//  
//  Data interface for MoveColumnGuideCmd
//  
//========================================================================================

#pragma once
#ifndef __IMoveColumnGuideCmdData__
#define __IMoveColumnGuideCmdData__

class PMReal;

/** Data interface for move column guide command.
	@ingroup layout_column
	@see kMoveColumnGuideCmdBoss 
*/
class IMoveColumnGuideCmdData : public IPMUnknown
{
public:
		/**	Set the new location value for the indicated column guide on the specified page. 
			Automatically adjusts the neighboring column guide (except for first and last column guide on a page,
			in which case it isn't necessary).
			@param pageUIDRef IN UIDRef& a UIDRef for the page that is targetted..
			@param columnIndex IN int32 the index of the column to change.
			@param columnLocation IN PMReal& the value to use (in points). Relative to left margin (or top of page for J columns).
		 */
		virtual void Set(const UIDRef& pageUIDRef,
						const int32 columnIndex,
						const PMReal& columnLocation) = 0;
		
		/**	Return the targetted page value from the data interface.
			@return UIDRef& a const reference to the targetted page. 
		 */
		virtual const UIDRef& GetPageUIDRef() const = 0;
		
		/**	Return the column index value from the data interface.
			@return int32 the column index. 
		 */
		virtual const int32 GetColumnIndex() = 0;
		
		/**	Return the column location value from the data interface.
			@return PMReal& the location value (in points).
		 */
		virtual const PMReal& GetColumnLocation() const = 0;
};

#endif // __IMoveColumnGuideCmdData__
