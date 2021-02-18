//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IInCopyUIColors.h $
//  
//  Owner: Kevin Van Wiel
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
//  (November 9 2000) IInCopyUIColors2 interface is added in InCopy v1.1 to provide
//  different shades of a user's chosen Note & Track Changes color for their note versus
//  their track change hilite.  This was necessary in order to be able to see the note
//  anchors within inserted text without having to hide the track change hilite.  This
//  interface and the corresponding GetNoteColor() and GetTrackChangeColor() methods
//  should be used instead of the GetColor() method.  GetColor() is still supported for
//  backward compatibility but will return the InCopy v1.0 color values.
//  
//  Used to store and retrieve some rgb colors for use in the notes and 
//  track changes UI. List is non-editable. The ordering of the list must
//  correspond to the color menu pop up list the notechangesprefs panel.
//  
//========================================================================================

#pragma once
#ifndef __IInCopyUIColors__
#define __IInCopyUIColors__

#include "IPMUnknown.h"
#include "IInterfaceColors.h"
#include "InCopySharedID.h"

/**	Interface with getter/setter methods for colors used by InCopy for user and prefs (track changes, galley, notes).
*/
class IInCopyUIColors : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IINCOPYUICOLORS };

	/**	Return number of colors in the list.
		@return int32 number of colors.
	*/
	virtual int32 GetColorCount() const = 0;

	/**	Get the color at a specific index.
		@param index of the color to get value for.
		@return RealAGMColor color value for the index specified, returns Black (0, 0, 0) if name is not found.
	*/
	virtual RealAGMColor GetColorValue(int32 index) const = 0;

	/**	Get the color values of the color with the given name.
		@param name of the color to get value for.
		@return RealAGMColor color value for the name specified, returns Black (0, 0, 0) if name is not found.
	*/
	virtual RealAGMColor GetColorValue(PMString name) const = 0;

	/**	Get the color name stored at a specific index.
		@param index of color for which to get the name.
		@return PMString the name of the color, empty string if not found.
	*/
	virtual PMString GetColorName(int32 index) const = 0;

	/**	Get the color name with the given color value.
		@param agmColor color to get the name of.
		@return PMString name of color, empty string if not found.
	*/
	virtual PMString GetColorName(RealAGMColor agmColor) const = 0;

	/**	Set default color.
		@param index of the color to set as default.
		@return bool true if successfully set default color.
	*/
	virtual bool SetDefault(int32 index) = 0;

	/**	Get the current default color.
		@return RealAGMColor default color.
	*/
	virtual RealAGMColor GetDefaultColor() const = 0;
	
	/**	Map an index to a scripting enumeration.
		@param index to map.
		@return ScriptID script enum the index mapped to.
	*/
	virtual ScriptID GetEnumeration(int32 index) const = 0;
	
	/**	Map a scripting enumeration to a color index.
		@param enumeration the scripting enum to map.
		@return int32 index the script enum mapped to, -1 is enum not found.
	*/
	virtual int32 GetEnumerationIndex(ScriptID enumeration) const = 0;

	/**	Get color Index.
	@param name of the color as PMString.
	@return Index of the color name in the Vector.
	*/
	virtual int32 GetColorIndex(const PMString & colorName) const = 0;
};

#endif // __IInCopyUIColors__
