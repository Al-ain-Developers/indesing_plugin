//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ISetSpreadCommandData.h $
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
#ifndef __ISetSpreadCommandCmdData__
#define __ISetSpreadCommandCmdData__
//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________
	#include "IPMUnknown.h"
	#include "SpreadID.h"

/**	Flags to pass to Set method.
 */
	const bool16	kDeselect = kTrue;
	const bool16	kDontDeselect = kFalse;

/** 
	Command data interface for the kSetSpreadCmdBoss. The command data controls
	whether to deselect all items when executing this command. All items that are
	selected in the layout suite (ILayoutSelectionSuite) will be deselected.

	@see kSetSpreadCmdBoss
	@ingroup layout_spread
 */
class ISetSpreadCommandData : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_ISETSPREADCOMMANDDATA };

	/**
	 Further defines the IID_IACTIVESPREAD submessage broadcast in an int32 lazy cookie on IID_IACTIVESPREAD protocol.
	 May be retrieved in a LazyUpdate method for observers of the IID_IACTIVESPREAD protocol (Layout window subject).
	 For example, taken from a LazyUpdate observer method:
		case IID_IACTIVESPREAD:
		{
			int32 spreadChangedMessage = ISetSpreadCommandData::kActiveSpread_SpreadToSpreadType;
			const ListLazyNotificationData<int32>*  pListCookie = static_cast<const ListLazyNotificationData<int32>* > (data);
			if (pListCookie)
			{
				K2Vector<int32> itemsChanged;
				pListCookie->BreakoutChanges (nil, nil, &itemsChanged);
				for (int32 n = 0; n < itemsChanged.size (); n++)
					spreadChangedMessage |= itemsChanged[n];
			}
		}
	 This replaces the now obsolete IChangedSpreadKindData.h interface, which has been removed for CS3.
	 */
	enum MessageFlags
	{
		/**  Specifies active spread changed during initialization, no previous spread. */
		kActiveSpread_InitializationType	= 0x0000,
		/**  Specifies active spread changed from spread to spread. */
		kActiveSpread_SpreadToSpreadType	= 0x0001,
		 /**  Specifies active spread changed from master to master spread. */
		kActiveSpread_MasterToMasterType	= 0x0002,
		 /**  Specifies active spread changed from master to spread or spread to master. */
		kActiveSpread_MasterToSpreadType	= 0x0004,
		 /**  Same as above, just a synonym. */
		kActiveSpread_SpreadToMasterType	= 0x0004,
		 /**  Specifies active spread from within a set page command. Can appear with other flag values. */
		kActiveSpread_SetPageType			= 0x0008
	};
	
	/**
		Set - Sets the value of the command data. All items that are selected in the 
		layout suite (ILayoutSelectionSuite) will be deselected when set to kTrue.
	
		@param	bool16 - kTrue (kDeselect) to deselect, kFalse (kDontDeselect) to leave selection alone.
		@param	bool16 - kTrue if the SetSpreadCmd has been processed within (or by) a SetPageCmd, kFalse if SetSpreadCmd is executing by itself.
	*/
		virtual void 	Set (bool16 bDeselect, bool16 bWithinSetPageCmd = kFalse) = 0;

	/**
		Deselect - returns the value of the command data bDeselect parameter.
		@return	bool16 - kTrue to deselect, kFalse to leave selection alone.
	*/
		virtual bool16 	GetDeselect (void) const = 0;

	/**
		SetPage - returns the value of the command data bWithinSetPage parameter.
		@return	bool16 - kTrue if the SetSpreadCmd has been processed within (or by) a SetPageCmd, kFalse if SetSpreadCmd is executing by itself.
	*/
		virtual bool16 	GetWithinSetPageCmd (void) const = 0;
	};
	
	

#endif // __ISetSpreadCommandCmdData__
