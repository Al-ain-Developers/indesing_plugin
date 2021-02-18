//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/IEditMojikumiTableCmdData.h $
//  
//  Owner: Shinji Hiramatsu
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
#ifndef __IEDITMOJIKUMITABLECMDDATA__ 
#define __IEDITMOJIKUMITABLECMDDATA__

#include "IMojikumiTable.h"

/** Data associated with the EditMojikumiTableCmd
*/
class IEditMojikumiTableCmdData : public IPMUnknown
{
	public:
		/** Gets target UID for command
		@return UID of target
		*/
		virtual UID		GetTargetUID() const = 0;
		/** Sets target UID for command
		@param targetUID [IN] UID of target
		*/
		virtual void	SetTargetUID(UID targetUID) = 0;
		/** Adds one MojikumiOverrideSpacing to the command
		@param data [IN] the spacing settings
		*/
		virtual void	AddEditData(MojikumiOverrideSpacing& data) = 0;
		/** counts the number of spacing data objects
		@return number of spacing objects
		*/
		virtual int32	CountEditData() const = 0;
		/** Get one edit data
		@param index [IN] index of data
		@param data [OUT] data
		@return kTrue if success
		*/
		virtual bool16	GetEditData(const int32 index, MojikumiOverrideSpacing& data) const = 0;
		/** Gets flag that indicates if command will also recompose the text
		@return kTrue if will recompose
		*/
		virtual bool16	GetComposeFlag() const = 0;
		/** Sets flag that indicates if command will also recompose the text
		@param composeFlag [IN] kTrue if will recompose
		*/
		virtual void	SetComposeFlag(bool16 composeFlag) = 0;
};

#endif
