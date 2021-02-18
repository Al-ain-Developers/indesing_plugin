//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IInterfaceColors.h $
//  
//  Owner: Mouhammad Fakhoury
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
//  User Interface Color table
//  
//========================================================================================

#pragma once
#ifndef __IInterfaceColors__
#define __IInterfaceColors__

#include "PMTypes.h"
#include "InterfaceColorDefines.h"
#include "IPMStream.h"
#include "WorkspaceID.h"

/** Class to define the data format for an AGM color.
*/
class RealAGMColor
{
public:
   	typedef base_type data_type;
	
	/** Default constructor
	*/
	RealAGMColor() :
		red(0.), green(0.), blue(0.)
		{ }
	
	/** Usual constructor
	*/
	RealAGMColor (double a, double b, double c) { red = a; green = b; blue = c; }
	
	/** Read or write the data to/from a stream
	*/
	void	ReadWrite(IPMStream *s)
			{
				s->XferRealNumber(red);
				s->XferRealNumber(green);
				s->XferRealNumber(blue);
			}
	PMReal red;
	PMReal green;
	PMReal blue;
};

/** Interface to provide access to standard UI color values.
*/
class IInterfaceColors : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IINTERFACECOLORS };
	enum { kNumColors = kInterfaceColorCount,
	       kFirstIndex = 0,
		   kLastIndex = kNumColors - 1 };

	/** @see InterfaceColorDefines.h for a list of color values. We use #defines because we need these to work in resource files
	*/
	typedef int32	InterfaceColor;

	/**	initialize colors from a resource table of int16 RGB colors. returns kTrue if success.
		@param interfaceColorTableRsrc the resource id for the color table to initialize from.
		@return kTrue if successful
	*/
	virtual	 bool16 Init(const RsrcID interfaceColorTableRsrc) = 0;

	/**	Get the color value for a particular color constant as a RealAGMColor
		@param index identifier of the color you want,  @see InterfaceColorDefines.h for a list of color values.
		@param outColor the color to be filled out
		@return kTrue if successful
	*/
	virtual  bool16 GetRealAGMColor(const InterfaceColor index, RealAGMColor& outColor)const = 0;

	/**	Get the color value for a particular color constant as an RGBColor
		@param index identifier of the color you want,  @see InterfaceColorDefines.h for a list of color values.
		@param outColor the color to be filled out
		@return kTrue if successful
	*/
	virtual  bool16 GetRGBColor(const InterfaceColor index, RGBColor& outColor)const = 0;

protected:
	/** The methods below are depracated and NO-OP. They will be removed in a future version. DO NOT USE THEM **/

	/**	set the value of one of the colors in the table from a RealAGMColor
		@param index color index to set. @see InterfaceColorDefines.h for a list of color values.
		@param inColor color value to set
		@return kTrue if successful
	*/
	virtual  bool16 SetRealAGMColor(const InterfaceColor index, const RealAGMColor& inColor) = 0;

	/**	set the value of one of the colors in the table from a RGBColor
		@param index color index to set. @see InterfaceColorDefines.h for a list of color values.
		@param inColor color value to set
		@return kTrue if successful
	*/
	virtual  bool16 SetRGBColor(const InterfaceColor index, const RGBColor& inColor) = 0;
};



#endif// __IInterfaceColors__
