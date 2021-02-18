//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicStyleNameTable.h $
//  
//  Owner: Michael_Martz
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
//  Interface Description:
//  
//  The graphic style name table interface manages a list of graphic styles
//  for a workspace. It is the interface that makes the list persistent.
//  
//  The interface on the session workspace contains the defaults for new
//  documents. The interface on document workspaces contain the graphic styles
//  created for that document's use. 
//  
//  Each name table has one special style, the "[No Style]" graphic style.
//  This style has a legitamite UID.
//  
//========================================================================================

#pragma once
#ifndef _IGRAPHIC_STYLE_NAMETABLE_
#define _IGRAPHIC_STYLE_NAMETABLE_

//________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________
	#include "IPMUnknown.h"
	#include "UIDRef.h"
//________________________________________________________________________________________
//	CLASS FORWARDS
//________________________________________________________________________________________
	class PMString;
//========================================================================================
//________________________________________________________________________________________
//	CLASS DECLARATIONS
//________________________________________________________________________________________

/**	The graphic style name table interface manages a list of graphic styles
	for a workspace. Each name table has one special style, the "[No Style]" graphic style.
	A graphic style is a kGraphicStyleBoss object.
*/
class IGraphicStyleNameTable : public IPMUnknown
	{
	//____________________________________________________________________________________
	//	Style Utilities
	//____________________________________________________________________________________
	public:
		/**	Find a graphic style in the style name table with the specified style name.
			@param styleName specifies the style name to find.
			@return a style UID with the style name. Returns kInvalidUID if no style is found.
		*/
		virtual UID			FindByName			(const PMString& styleName) const = 0;

		/**	Find a graphic style in the style name table with the specified style UID.
			@param styleUID specifies the style UID to find.
			@return an index in the table with the style name. Returns a -1 if not style
			with the UID is found.
		*/
		virtual	uint32		FindByUID			(const UID& styleUID) const = 0;
		
		/**	Returns the number of graphic styles in the style name table.
		*/
		virtual uint32 		GetStyleCount		(void) const = 0;
		/**	Returns the UID of the [No Style] graphic style in the style name table.
		*/
		virtual UID			GetNoStyleUID		(void) const = 0;

		/**	Add the specified new style to the style name table.
			@param newStyleUID specifies the new style UID to add.
		*/
		virtual void 		AddStyle			(const UID& newStyleUID) = 0;
		/**	Add the specified [No Style] to the style name table.
			@param noStyleUID specifies the [No Style] UID to add.
			@return an error code if [No Style] is already in the list.
		*/
		virtual ErrorCode	AddNoStyle			(const UID& noStyleUID) = 0;
		/**	Remove the specified style from the style name table.
			@param styleUID specifies the style UID to remove.
		*/
		virtual void 		RemoveStyle			(const UID& styleUID) = 0;

		/**	Return the nth style from the style name table.
			@param index specifies the nth style.
			@return the style UID that is the nth style.
		*/
		virtual UID 		GetNthStyle			(uint32 index) const = 0;
	};

#endif // _IGRAPHIC_STYLE_NAMETABLE_