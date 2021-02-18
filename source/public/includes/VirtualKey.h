//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/VirtualKey.h $
//  
//  Owner: lance bushore
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
#ifndef __VirtualKey__
#define __VirtualKey__

#ifndef __ODFRC__

class IPMStream;

#pragma export on

/** This class encapsulates a platform independant way to handle 'virtual keys'. This allows us to do smart matching of
	keys that generate a plain character, as well as the tricker keys which generate extended characters or no characters. 
	This is mostly used in our keyboard shortcut handling code. Usually code that needs a virtual key either gets it passed in,
	or they get one by calling IEvent::
*/
class PUBLIC_DECL VirtualKey
{
	public:
		/** This type is a base type. It has no special copy semantics. @see K2Vector.h
		*/
   		typedef base_type data_type;   
   		
   		/** Various constructors. Just record the passed in keycode and character code.
   		*/
		VirtualKey():fChar(0),fDVKeyCode(0){}
		explicit VirtualKey(SysChar character);
		explicit VirtualKey(uint32 keyCode);
		
		VirtualKey(const VirtualKey &other)
			{
				fChar = other.fChar;
				fDVKeyCode = other.fDVKeyCode;
			}
		
   		/** Read or write this object from/to a stream
   			@param s the stream to read/write from/to
   		*/
		void ReadWrite(IPMStream *s);
		
   		/** Assignment
   			@param copy the object to copy into this one.
   		*/
		VirtualKey& operator = (const VirtualKey &copy)
			{ 
				if (&copy != this) 
				{
					fChar = copy.fChar;
					fDVKeyCode = copy.fDVKeyCode;
				}
				return *this;
			}
			
   		/** Less than operator. Implemented so that sorting of this object will work.
   			@param other the object to compare to.
   			@return kTrue if this object is logically less than the object passed in
   		*/
		bool16 operator < (const VirtualKey &other) const
			{
				return (fDVKeyCode < other.fDVKeyCode);
			}
			
   		/** Equality operator. Does intelligent matching on both mac and windows
   			@param s the object to compare to.
   			@return kTrue if this object is logically equal to the object passed in
   		*/
		bool16 operator == (const VirtualKey &s) const;

   		/** Inequality operator. Does intelligent matching on both mac and windows
   			@param s the object to compare to.
   			@return kTrue if this object is not logically equal to the object passed in
   		*/
		bool16 operator != (const VirtualKey &s) const { return !(*this == s); }

   		/** Get the character for this object. Return value is 0 if IsPlainChar is false.
   			@return the raw character
   		*/
		SysChar GetChar() const { return fChar; }

   		/** Check if this virtual key represents a plain printable character.
   			@return kTrue if this is a plain character. 
   		*/
		bool16 IsPlainChar() const;

   		/** Check if this virtual key is pressed down
   			@return kTrue if this key is down. 
   		*/
		bool16 IsPressed() const;

   		/** Get the drover key code for this object
   			@return the raw drover key code
   		*/
		uint32 GetDVKeyCode() const { return fDVKeyCode; }
	private:
		SysChar fChar;
		uint32 fDVKeyCode;
};
#pragma export off

#endif
#endif // __VirtualKey__
