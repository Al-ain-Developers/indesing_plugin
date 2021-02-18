//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IStoryViewTableFacade.h $
//  
//  Owner: kvanwiel
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
#ifndef __IStoryViewTableFacade__
#define __IStoryViewTableFacade__

// ----- Interfaces -----

#include "IPMUnknown.h"
#include <vector>

// ----- Includes -----
#include "InCopySharedID.h"


/**   A high level API for tables in the story editor running InDesign or story and galley views running InCopy.  Facade is for features unique to story views
	such as collapsing the display of a table down to a icon. Please use the IStoryViewTableFacade 
	directly via the UtilsBoss if possible, see Utils.h:
	i.e. Utils<Facade::IStoryViewTableFacade>()->GetIsTableCollapsed(...);
	  @author Kevin Van Wiel
   */
namespace Facade
{
	class IStoryViewTableFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_ISTORYVIEWTABLEFACADE };
		
		/**     Set the collapsed state of a tables
			@param tableModelRefs [IN]: UID list of of tables to set collapsed or uncollapsed.
			@param collapsed [IN]: true to set tables to a collapsed view state, false to expand.
			@return kSuccess if successful. Otherwise an error code is returned.
		*/
		virtual ErrorCode SetCollapsed(const UIDList& tableModelRefs, bool collapsed) = 0;

		
		/**     Get whether tables are currently shown collapsed or expanded.
			@param tableModelRefs [IN]: UIDs of tables to retrieve collapse information for.
			@param collapsed [OUT]: list of tables collapsed view states. True value indicates table is collapsed and false uncollapsed.
			@return kSuccess if was able to retrieve collapse view states for tables in the list. Otherwise an error code is returned.
		*/
		virtual ErrorCode GetIsCollapsed(const UIDList& tableModelRefs, std::vector<bool> &collapsed) const = 0;
		
		
		/**	OrderType.
			Specifies the order in which table cells are displayed.
		*/
		enum OrderType 
		{ 
			/** kOrderByRows - Order table cell display in row order (i.e. display all of row 1 first then all of row 2 etc). */
			kOrderByRows, 
			
			/** kOrderByColumns - Order table cell display in column order. */
			kOrderByColumns 
		};
		
		
		/**     Set the order in which table cells are displayed for a set of tables
			@param tableModelRefs [IN]: UID list of of tables to set the display order of.
			@param order [IN]: Specify the order to set the table cell display order with this param.
			@return kSuccess if successful. Otherwise an error code is returned.
		*/
		virtual ErrorCode SetDisplayOrder(const UIDList &tableModelRefs, OrderType order) = 0;
		
		
		/**     Get the order in which table cells are displayed for a set of tables
			@param tableModelRefs [IN]: UID list of of tables to set the display order of.
			@param order [OUT]: A vector with an entry for each table specified in tableModelRefs, entry value specifies display order for a table
			@return kSuccess if successful. Otherwise an error code is returned.
		*/
		virtual ErrorCode GetDisplayOrder(const UIDList &tableModelRefs, std::vector<OrderType> &order) const = 0;

	};
}
#endif	// __IStoryViewTableFacade__
