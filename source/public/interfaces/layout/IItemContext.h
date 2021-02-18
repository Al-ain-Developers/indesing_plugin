//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IItemContext.h $
//  
//  Owner: Richard Rodseth
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
//  Purpose: An ItemContext represents the context of a selection, and provides a method
//  to create a specifier based on the selection.
//  
//========================================================================================

#pragma once
#ifndef __IITEMCONTEXT__
#define __IITEMCONTEXT__

#include "IPMUnknown.h"
#include "GenericID.h"

class ISnapTo;	
class IHierarchy;
class IControlView;


#ifdef ID_DEPRECATED

/** This class is obsolete. Do not use.
*/
class IItemContext : public IPMUnknown
{

public:		
		/** Obsolete.
		*/
		virtual ISnapTo* QuerySnapTo() = 0;
		
		/** Obsolete.
		*/
		virtual IHierarchy* QueryNewItemParent(IControlView* view) = 0;
			// Returns the IHierarchy to be used for new items inside
			// the context.
		
};

#endif // ID_DEPRECATED

#endif
