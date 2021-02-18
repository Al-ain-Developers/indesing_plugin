//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ISmoothPrefs.h $
//  
//  Owner: Tashana Landray
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
#ifndef __ISmoothPrefs__
#define __ISmoothPrefs__

#include "IPMUnknown.h"
#include "SplineID.h"

/**
 	ISmoothPrefs is a preference interface on the session workspace. It is used to access all 
	the variables related to smooth operation.
*/

class ISmoothPrefs : public IPMUnknown
{
	public:

 	enum { kDefaultIID = IID_ISMOOTHPREFS };
 
	
		// ---- [mburbidg 7-10-02] Methods that return constants. This is to work around
		//		the fact that you can't declare non-integral constants in a header file.
		//		At one point these were declared as constants in the implementation, but
		//		then they couldn't be accessed outside the plug-in of the implementation.
		
		/**	
			Return the default smooth's fidelity value.
			@return PMReal the default fidelity.
		*/
		static PMReal GetDefaultSmoothFidelity() { return 2.5; }

		/**	
			Return the default smooth's smoothness value.
			@return PMReal the default smoothness
		*/
		static PMReal GetDefaultSmoothSmoothness() { return 2.5; }

		/**	
			Return the default selection status.
			@return bool16 the default selection status.
		*/
		static bool16 GetDefaultSmoothSelected() { return kTrue; }

		/**	
			Set the preference value for fidelity(point tolerance when fitting to curve).
			@param fidelity the new fidelity value to set.
		*/
		virtual void SetFidelity(const PMReal& fidelity) = 0;

		/**	
			Get the current preference value for fidelity(point tolerance when fitting to curve).
			@return const PMReal& the current fidelity value.
		*/
		virtual PMReal GetFidelity() = 0;

		/**	
			Set the preference value for smoothness(when fitting to curve).
			@param smoothness the new smoothness value to set.
		*/
		virtual void SetSmoothness(const PMReal& smoothness) = 0;

		/**	
			Get the current preference value for smoothness(when fitting to curve).
			@return const PMReal& the current smoothness value.
		*/
		virtual PMReal GetSmoothness() = 0;

		//Whether or not the newly-created spline is selected

		/**	
			Set the preference value for selection status. 
			@param selected the bool16 flag to set.
		*/
		virtual void SetSelected(const bool16 selected) = 0;

		/**	
			Get the current preference value for selection status.
			@return const bool16 the current selection status.
		*/
		virtual bool16 GetSelected() = 0;
};

#endif
