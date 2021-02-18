//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IKBSCData.h $
//  
//  Owner: Jonathan Brown
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
#ifndef __IKBSCData__
#define __IKBSCData__

#include "IPMUnknown.h"

#include "PMString.h"
#include "KBSCEditorDlgID.h"
#include "VirtualKey.h"

/** Interface for maintaining info about a shortcut. This is used to pass data about a selected
	shortcut in the shortcut editor, so the delete button knows which shortcut to delete.
*/
class IKBSCData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IKBSCDATA };

	/**  Set the new shortcut info
		@param context which context this shortcut will be active in @see IShortcutManager.h
		@param key the key for this shortcut
		@param mods the modifier keys for this shortcut. @see KBSCModifierDefs.h
	*/
	virtual void SetKey( const PMString& context,
							const VirtualKey& key,
						   	int16 mods) = 0 ;

	
	/**  Get a copy of the context string
		@return context string
	*/
	virtual PMString GetContext() const= 0 ;
	
	/**  Get a copy of the key for this shortcut
		@return key
	*/
	virtual VirtualKey GetKey() const= 0 ;

	/**  Get the modifiers for this shortcut. @see KBSCModifierDefs.h
		@return modifiers
	*/
	virtual int16 GetMods() const= 0 ;

	/**  Clear out all the data
	*/
	virtual void Clear( ) = 0 ;
} ;

#endif //__IKBSCData__
