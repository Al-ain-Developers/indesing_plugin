//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IObjectStyleInfo.h $
//  
//  Owner: Yeming Liu
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

#ifndef _IOBJECTSTYLEINFO_
#define _IOBJECTSTYLEINFO_

// ----- Interface files -----

#include "IPMUnknown.h"

// ----- ID files -----

#include "GenericID.h"

class PMString;
class VirtualKey;

/** An interface to get object style's name and based on information.
*/
class IObjectStyleInfo : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IOBJECTSTYLEINFO };

		/**
			Timestamp field for style shortcut to be consistent with text style(IStyleInfo.h).
			It will be better to define them in one place. 
		*/
		enum { kInvalidTimeStamp = 0, kPubConvertedTimeStamp = 1, kRefConvertedTimeStamp = 2 };
		
		/**	Get the style UID which this style is based on.
			@return the UID which this style is based on.
		*/
		virtual UID		GetBasedOn() const = 0;

		/**	Set the style UID which this style is based on.
			@param newBaseStyleUID the style UID which this style is based on.
		*/
		virtual void 	SetBasedOn(const UID& newBaseStyleUID) = 0;

		/**	Returns the style name.
			@return the PMString.
		*/
		virtual const 	PMString& GetName() const = 0;

		/**	Set the style name.
			@param newStyleName the new style name.
		*/
		virtual void 	SetName(const PMString& newStyleName, bool16 translatable = kFalse) = 0;

		/** Set the keyboard shortcut that triggers this style.
			@param virtualKey is the key code.
			@param modifiers are the modifier keys.
			@see KeyboardDefs.h
		*/
		virtual void SetKeyboardShortcut(VirtualKey  virtualKey, int16 modifiers) = 0; 

		/** Get the keyboard shortcut that triggers this style.
			@param modifiers MAY NOT BE NIL.
			@return VirtualKey.
		*/
		virtual VirtualKey GetKeyboardShortcut(int16 *modifiers) const = 0; 

		/** Get the keyboard shortcut time stamp. If two styles share the same keyboard shortcut, the
			one with the newer time stamp is used.
		*/
		virtual GlobalTime GetKeyboardShortcutTimeStamp () const = 0;

		/** Set the keyboard shortcut time stamp. If two styles share the same keyboard shortcut, the
			one with the newer time stamp is used.
			@param gtime specifies the current time, used to compare conflicted shortcuts.
		*/
		virtual void SetKeyboardShortcutTimeStamp (GlobalTime gtime) = 0;

		/**
			Get based on style name. We don't persist this info and 
			it only facilitate the UI to use based on info, otherwise, 
			we may end up add more interfaces to pass around. 
			@return the PMString.
		*/
		virtual const PMString& GetBasedOnStyleName() const = 0;

		/**	Set based on style name. We don't persist this info and 
			it only facilitate the UI to use based on info, otherwise, 
			we may end up add more interfaces to pass around. 
			@param newStyleName the new style name.
		*/
		virtual void  SetBasedOnStyleName(const PMString& basedOnStyleName) = 0;
};

#endif // _IOBJECTSTYLEINFO_