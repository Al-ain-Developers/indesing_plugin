//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPencilPrefs.h $
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
#ifndef __IPencilPrefs__
#define __IPencilPrefs__

#include "IPMUnknown.h"
#include "SplineID.h"

class IPencilPrefs : public IPMUnknown
{
	public:

	 	enum { kDefaultIID = IID_IPENCILPREFS };
 
		// ---- [mburbidg 7-10-02] Methods that return constants. This is to work around
		//		the fact that you can't declare non-integral constants in a header file.
		//		At one point these were declared as constants in the implementation, but
		//		then they couldn't be accessed outside the plug-in of the implementation.

		static PMReal GetDefaultPencilFidelity() { return 2.5; }
		static PMReal GetDefaultPencilSmoothness() { return 0.0; }
		static PMReal GetDefaultPencilEditTolerance() { return 12.0; }
		static bool16 GetDefaultPencilEditSelected() { return kTrue; }
		static bool16 GetDefaultPencilSelected() { return kTrue; }

		//Fidelity (point tolerance when fitting to curve)
		virtual void SetFidelity(const PMReal& fidelity) = 0;
		virtual PMReal GetFidelity() = 0;
		
		//Smoothness when fitting to curve
		virtual void SetSmoothness(const PMReal& smoothness) = 0;
		virtual PMReal GetSmoothness() = 0;

		///EditTolerance when edit curve
		virtual void SetEditTolerance(const PMReal& editTolerance) = 0;
		virtual PMReal GetEditTolerance() = 0;

		//Whether or not edit the newly-created spline is selected
		virtual void SetEditSelected(const bool16 editSelected) = 0;
		virtual bool16 GetEditSelected() = 0;

		//Whether or not the newly-created spline is selected
		virtual void SetSelected(const bool16 selected) = 0;
		virtual bool16 GetSelected() = 0;
};

#endif
