//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IHyperlinkUIFacade.h $
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
//  
//  Note: UI facade for hyperlink feature.
//  
//========================================================================================

#pragma once

#include "Utils.h"

// ----- Interfaces -----

// ----- ID.h files -----
#include "HyperlinkID.h"

namespace Facade
{
	/** A high level API for dealing with hyprelink UI actions.  To use this Facade, include
		this header file and use the following example syntax:
		result = Utils<Facade::IHyperlinkUIFacade>()->MoveHyperlink( ... );

	     @author Jianlan Song
	*/
	class IHyperlinkUIFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IHYPERLINKUIFACADE };

		/**	Moves list of hyperlinks before a specified hyperlink. After the move, the list of hyperlinks will be right before the 
			specified hyperlink in the order specified in the list.
		
			@param hyperlinks - Hyperlinks to be moved. 
			@param before - The hyperlink which the above hyperlinks will be moved in front of. if kInvalidUIDRef is passed, 
							the specified hyperlink list will be moved to the end of the hyperlink list.

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode MoveHyperlinks
							(
								UIDList hyperlinks,
								UIDRef before
							) = 0;
	};
}


