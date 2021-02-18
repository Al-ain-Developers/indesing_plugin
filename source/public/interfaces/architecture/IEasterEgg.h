//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IEasterEgg.h $
//  
//  Owner: emenning
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
#ifndef __IEasterEgg__
#define __IEasterEgg__

#include "IPMUnknown.h"
#include "ShuksanID.h"

class IWindow;

/** Not the most supported interface, the IEasterEgg interface
	is a service provider interface (kEasterEggService) that can
	be called when a certain key string is typed when the about box
	is open. IT MIGHT BE UNSUPPORTED RIGHT NOW.
*/
class IEasterEgg : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IEASTEREGG };

		/** What sequence of keys must be typed before your
			easter egg is displayed? The strings are combined into
			a single state-machine that looks for matches.
			@return the sequence of characters to match. */
		virtual const char* GetKeyString() = 0;

		/** When the user types the necessary key string, the
			about box will call this method, passing in a pointer
			to the IWindow interface of the about box. Do what
			you will. Caveat Emptor and all that.
			@param window is the window to display your handiwork in. */
		virtual void ShowEasterEgg(IWindow *window) = 0;

		/** The object that calls ShowEasterEgg should call this before closing
			the window. This will give the egg an opportunity to stop any idle tasks
			it has running and gracefully shutdown.*/
		virtual void CloseEasterEgg() = 0;
};

#endif
		//__IEasterEgg__
