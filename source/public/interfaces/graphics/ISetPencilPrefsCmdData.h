//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ISetPencilPrefsCmdData.h $
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
#ifndef __ISetPencilPrefsCmdData__
#define __ISetPencilPrefsCmdData__

#include "IPMUnknown.h"
#include "SplineID.h"

/**
	This is a command data interface of using SetPencilPrefsCmd and SetSmoothPrefsCmd.
	@see kSetPencilPrefsCmdBoss and kSetSmoothPrefsCmdBoss
*/
class ISetPencilPrefsCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ISETPENCILPREFSCMDDATA };

		/**	
			Set all those variables related to pencil preferences in the command data 
			that will finally pass to CurveFit.
			@param fidelity the value that indicates the point tolerance when fitting to curve)
			@param smoothness the value indicates how smooth the curve should be 
			@param editTolerance the value indicates how close to the curve shall we start to do edit.
			@param editSelected flag indicates if only edit the selected path or not.
			@param selected flag indicates if the newly created spline should be selected or not.
		*/
		virtual void Set ( const PMReal& fidelity, 
						   const PMReal& smoothness, 
						   const PMReal& editTolerance, 
						   const bool16 editSelected,	
	 					   const bool16 selected      
						  ) = 0; 



		/**	
			Get the fidelity value.
			@return const PMReal& the fidelity value.
		*/
		virtual const PMReal& GetFidelity() const = 0;

		/**	
			Get the smoothness value.
			@return const PMReal& the smoothness value.
		*/
		virtual const PMReal& GetSmoothness() const = 0;

		/**	
			Get the tolerance value.
			@return const PMReal& the tolerance value.
		*/
		virtual const PMReal& GetEditTolerance() const = 0;

		/**	
			Get the flag if we are going to edit the selected path or not.
			@return bool16 the flag indicates we are going to edit the selected path or not.
		*/
		virtual const bool16  GetEditSelected() const = 0;

		/**	
			Get the selection status flag related to the edited path.
			@return bool16 the selection status after we edit the path.
		*/
		virtual const bool16  GetSelected() const = 0;	
};

#endif