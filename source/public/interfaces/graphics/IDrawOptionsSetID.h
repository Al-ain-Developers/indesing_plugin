//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IDrawOptionsSetID.h $
//  
//  Owner: Dave Stephens
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
//  Description:
//  The purpose of this interface is to store the ID of the active DrawOptionsSet for
//  a given view.
//  
//========================================================================================

#ifndef __IDrawOptionsSetID__
#define __IDrawOptionsSetID__

#include "IPMUnknown.h"
#include "IDrawOptions.h"
#include "ShuksanID.h"

/** IDrawOptionsSetID is an interface off of the layout's view which indicates which of
	the IDrawOptions to use when drawing page items in the view.  Options include:
	IDrawOptions::kFastGroup, IDrawOptions::kTypicalGroup, IDrawOptions::kHighQualityGroup,
	and IDrawOptions::kNavigatorGroup.  You can also pass in one of your own custom draw
	option sets.  This interface is useful when you want to temporarily change the display
	settings in order to gain better performance.
	
	From the UI, users are able to customize all but the kNavigator group via the
	Display Performance Preferences dialog.
	
	@see IDrawOptions
*/
class IDrawOptionsSetID : public IPMUnknown
{
	public:
		/** Default IID
		*/
		enum { kDefaultIID = IID_IDRAWOPTIONSSETID };
		
		/** Set the ID of the IDrawOptions set to use when drawing in the view associated with this interface.
			@param id - IN - one of IDrawOptions::kFastGroup, IDrawOptions::kTypicalGroup, IDrawOptions::kHighQualityGroup,
				and IDrawOptions::kNavigatorGroup.
			@param bDoInvalView - IN - pass kTrue to automatically invalidate the view if the ID setting has changed.
			@return none
		*/			
		virtual void SetID(uint32 id, bool8 bDoInvalView = kTrue) = 0;
		
		/** Get the current display setting for the view associated with this interface.
		*/
		virtual uint32 GetID() const = 0;
};

#endif

