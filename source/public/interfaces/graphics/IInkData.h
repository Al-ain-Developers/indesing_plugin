//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IInkData.h $
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
//  
//  Purpose:
//  Data interface for a K2 color's ink information.
//  
//========================================================================================

#pragma once
#ifndef __IInkData__
#define __IInkData__

#include "ColorSystemID.h"
#include "IColorData.h"
#include "IPMUnknown.h"

#include "K2Vector.h"

class PersistUIDList;

/**	An interface for InDesign color object.
*/
class IInkData : public IPMUnknown
{
	public:
		enum	{kDefaultIID = IID_IINKDATA};

		/** Identifies the ink types
		*/
		typedef enum 
			{
			/**	Used to specified an undefined ink type or ink type unchanged.
			*/
			kUndefinedInk = -1,
			/**	Used to specified a process ink type,
			*/
			kProcessInk,
			/**	Used to specified a spot ink type.
			*/
			kSpotInk,
			/**	Used to specified a registration ink type.
			*/
			kRegistrationInk,
			/**	Used to specified an mixed-ink ink type. There should be only one such ink type
				in a swatch list.
			*/
			kDeviceNInk			
			} InkType;


		/**	Returns the list of ink UIDs associated with the color definition.
			If color definition is a process ink, then this list should be empty.
			If color definition is a spot ink, then this list should have only one entry.
			If color definition is a deviceN ink, then this list should contain 2 or more inks.
			@return the color definition's ink UID list.
		*/
		virtual PersistUIDList GetInkUIDList() const = 0;
		
		/** Returns the number of ink components associated with the color definition.
			For process ink, this is 0.
			For spot ink, this number should be 1.
			For deviceN inks, this number is >= 2.
			@return the number of ink components.
		*/
		virtual int32 GetNumInkComponents() const = 0;
		
		/** Returns the color definition's ink type. This is one of kProcessInk,
			kSpotInk, kDeviceNInk, or kRegistrationInk.
			@return the ink type.
		*/
		virtual InkType GetInkType() const = 0;
				
		/** Sets the new inks associated for this color definition.
			If color definition is a process ink, then this list should be empty.
			If color definition is a spot ink, then this list should have only one entry.
			If color definition is a deviceN ink, then this list should contain 2 or more inks.
			@param uidInkList the ink list to set.
			Typically SetInkUIDList is set through either NewColorCmdBoss, ChangeColorCmdBoss,
			kNewMixedInkGroupCmdBoss, or kChangeMixedInkGroupCmdBoss.
			For deviceN ink, the client would specify a list of ink UIDs and set through command's
			IInkData interface. For spot ink, this should be left empty. The appropriate commands
			(NewColorCmdBoss or ChangeColorCmdBoss) will set this field.
		*/
		virtual void SetInkUIDList( const PersistUIDList& uidInkList ) = 0;

		/** Sets the ink type for the color definition.
			Ink type should be one of kProcessInk, kSpotInk, kDeviceNInk, or kRegistrationInk.
			Ink type should remained as kUndefinedInk if defining a color that is based on another.
			@param inkType the new ink type to set.
			Typically SetInkUIDList is set through either NewColorCmdBoss, ChangeColorCmdBoss,
			kNewMixedInkGroupCmdBoss, or kChangeMixedInkGroupCmdBoss.
		*/
		virtual void SetInkType( InkType inkType ) = 0;

		/** Returns kTrue if both IInkData* are equal.
			@param iInkData to compare with.
			@return kTrue if both IInkData* are equal.
		*/
		virtual bool16 IsEqual (const IInkData* iInkData) const = 0;

};
#endif