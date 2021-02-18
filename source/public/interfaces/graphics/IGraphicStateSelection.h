//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicStateSelection.h $
//  
//  Owner: Michael Martz
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
	#ifndef _IGraphicStateSelection_
	#define _IGraphicStateSelection_
//________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________
	#include "IPMUnknown.h"
	#include "GraphicStylesID.h"
//========================================================================================
//________________________________________________________________________________________
//	CLASS FORWARDS
//________________________________________________________________________________________
	class UIDList;
	
//________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________

/**	This interface is intended to be used on page items so that the 
	graphic state can determine what objects should be in the selection. If 
	the page item is a container, it will need to return a list of page items
	that can accept graphic attriubtes (i.e. has an IID_IGRAPHICSTYLE_IS_APPLICABLE
	interface.)
*/
class IGraphicStateSelection : public IPMUnknown
	{
	//____________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_IGRAPHICSTYLE_SELECTION };

	//____________________________________________________________________________________
	//	Member functions
	//____________________________________________________________________________________
	public:

		/**	Returns true if page item is a container.
		*/
		virtual bool16		IsContainer				(void) const = 0;

		/**	Create a list of page item UID's that include this page item and all of its
			children.
			@param pFlattenList contains the list of flattened page items.
		*/
		virtual void		CreateFlattenedList		(UIDList* pFlattenList) const = 0;
	};

#endif // _IGraphicStateSelection_