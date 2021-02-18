//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IGeneralXMLPreferences.h $
//  
//  Owner: Ryan Gano
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
//  This interface is used for action components to update the state of their actions.
//  It is NOT a standard boss interface - it does not inherit from IPMUnknown!
//  
//========================================================================================

#pragma once
#ifndef __IGeneralXMLPreferences__
#define __IGeneralXMLPreferences__

#include "XMLID.h"

/**
	Used to store tagging presets. These presets are used to determine
	what names and colors to use when autotagging tables, cells, and stories
*/
class IGeneralXMLPreferences : public IPMUnknown 
{
public:
	enum { kDefaultIID = IID_IGENERALXMLPREFERENCES };
	
	/** Used to indicate which type of preset you are getting or setting
		NOTE: this is used in persisted data. Do not alter values of existing data.
		Additions are fine
	*/
	typedef enum {
		/** Used to indicate the story preset */
		kStoryLocation = 0, 
		/** Used to indicate the table preset */
		kTableLocation, 
		/** Used to indicate the table row preset */
		kRowLocation, 
		/** Used to indicate the table cell preset */
		kCellLocation, 
		/** Used to indicate the image preset */
		kImageLocation,
		/** Used to indicate table header preset */
		kTableHeaderLocation,
		/** Used to indicate table body preset */
		kTableBodyLocation,
		/** Used to indicate table footer preset */
		kTableFooterLocation,
		/** Used to indicate the count of element types. Do not add types after this */
		kEndElementType
		} kElementType;

	/**
		Initialize the settings of this object from the settings of the 'data' object.
		@param data - The object whose settings you want to use
		@return error code
	*/
	virtual ErrorCode Set(IGeneralXMLPreferences *data) = 0;

	/**
		Set up one of the tag presets. These presets are used to 
		@param which - The preset you want to setup
		@param name - The name this preset should use
		@param color - The color to be used
	*/
	virtual void SetData(IGeneralXMLPreferences::kElementType which, const WideString &name, UID color) = 0;

	/**
		Used to get appropriate data for a given preset
		@param which - The preset you want information about
		@param name - Gets filled with the name to use. Can be nil to skip
		@param color - Gets filled with the color to use. Can be nil to skip
	*/
	virtual void GetData(IGeneralXMLPreferences::kElementType which, WideString *name, UID *color) const = 0;

	/**
		Used to get the name of a given preset
		@param which - The preset you wnat information about
		@return - The name to use for the tag
	*/
	virtual WideString GetName(IGeneralXMLPreferences::kElementType which) const = 0;

	/**
		Used to get the color of a given preset
		@param which - The preset you wnat information about
		@return - The color to use for the tag
	*/
	virtual UID GetColor(IGeneralXMLPreferences::kElementType which) const = 0;

	/**
		Used to get the default name of a given preset. This may be different from the current
		stored name if the user has changed their presets. If you want to add a tag with the
		name that the user chose call GetName. If you want to get the factory presets call this
		method.
		@param which - The preset you want information about
		@return - The default name to use for the tag
	*/
	virtual WideString GetDefaultName(IGeneralXMLPreferences::kElementType which) const = 0;

	/**
		Used to get the index of a default color for a given preset. This may be different from the current
		stored color if the user has changed their presets. If you want to add a tag with the
		color that the user chose call GetName. If you want to get the factory presets call this
		method.
		NOTE: This is only an index into the color list and must be used in conjunction with
		@see IUIColorUtils::GetUIColor
		@param which - The preset you want information about
		@return - The index of the default color to use for the tag
	*/
	virtual int32 GetDefaultColor(IGeneralXMLPreferences::kElementType which) const = 0;
	/**
		Used to determine if two objects are the same
		@param o - The object you want to compair this one to
		@return - kTrue if the objects are the same
	*/
	virtual bool16 operator==(const IGeneralXMLPreferences &o) = 0;
};

#endif // __IIGeneralXMLPreferences__