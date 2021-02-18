//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicStateCmdData.h $
//  
//  Owner: SusanCL
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
	#ifndef _IGraphicStateCmdData_
	#define _IGraphicStateCmdData_
//===================================================================================
//___________________________________________________________________________________
//	INCLUDES
//___________________________________________________________________________________
	#include "IPMUnknown.h"
	#include "IGraphicStateData.h"
//===================================================================================
class IGraphicStateData;

//___________________________________________________________________________________
//	CLASS DECLARATION
//___________________________________________________________________________________

/**	A data interface for the graphic state commands.
*/
class IGraphicStateCmdData : public IPMUnknown
	{
	//___________________________________________________________________________
	//	Accessor memeber functions
	//___________________________________________________________________________
	public:
		enum {kDefaultIID = IID_IGRAPHICSTATE_CMDDATA};
		
		/**	Sets the desired graphic state UIDRef
			@param iDataBase is the database of the desired graphic state object
			@param gfxStateUID is the UID of the graphic state object
		*/
		virtual void							SetGraphicStateUIDRef			(IDataBase* iDataBase, UID gfxStateUID) = 0;

		/**	Returns the IPMUnknown* of the graphic state object.
		*/
		virtual IPMUnknown*						QueryGraphicStateDataInterface	(void) = 0;

		/**	Returns the database of the graphic state object.
		*/
		virtual IDataBase*						GetTargetDataBase				(void) = 0;
		
		/**	Sets the target for which the graphic state should be applied.
			@param targetType specifies the graphic state target. The target should be one of
			IGraphicStateData::TargetType. @see IGraphicStateData.h
			@param isTargetCurrent is true if target is the active current target
		*/
		virtual void							SetTarget						(IGraphicStateData::TargetType targetType, bool16 isTargetCurrent) = 0;

		/**	Returns the command's graphic state target type.
		*/
		virtual IGraphicStateData::TargetType	GetTargetType					(void) = 0;
		
		/**	Returns whether or not the specified target is current.
			@return true if target is current.
		*/
		virtual	bool16							GetTargetIsCurrent				(void) = 0;
	};
		
#endif // _IGraphicStateCmdData_
