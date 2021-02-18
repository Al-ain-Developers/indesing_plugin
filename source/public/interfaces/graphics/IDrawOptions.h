//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IDrawOptions.h $
//  
//  Owner: Dave Stephens
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
//  Description:
//  The purpose of this interface is to provide a central location for the various
//  display settings which have an effect on performance.  These settings do NOT affect
//  printed output and hence do not include settings such as multi vs single line
//  composition.
//  
//  There are 3 standard sets of settings (kFast, kNormal, kHighQuality) allowing
//  the user to quickly switch between their own definition of these sets as defined
//  by the settings within the set.  The interface is extensible in that third parties
//  can add their own sets identified by their own setID (which should be their pluginID
//  plus a constant).
//  
//========================================================================================

#pragma once
#ifndef __IDrawOptions__
#define __IDrawOptions__

#include "IPMUnknown.h"

class DrawOptionsSet;
/**
	IDrawOptions
	Use this class to control the drawing quality of page items to a port.  Each type of
	graphics port interface lives on a boss with a corresponding IID_IDRAWOPTIONS interface.
	That is, each port has its own IDrawOptions which control the drawing quality of page
	items into that port.
*/
class IDrawOptions : public IPMUnknown
{
public:	
	/** default IID enumerator */
 	enum { kDefaultIID = IID_IDRAWOPTIONS };
 
	/** Standard Application defined Set IDs
		kUseDefault				Local override value
		kFastGroup				Disable anti-aliasing and transparency; draw gray boxes for images; greek text
		kTypicalGroup			Enable anti-aliasing and medium transparency, draw proxy images, greek small text
		kHighQualityGroup		Enable anti-aliasing and high quality transparency, draw all images at high quality
		kNavigatorGroup			Private draw options for the Navigator panel
		kFastScrollGroup		Private draw options when in "fast scroll" mode
		kSepPrvGroup			Private draw options for Separations Preview mode
		kFlatPrvGroup			Private draw options for Flattener Preview mode
		kSnapshotUtilsPrvGroup	Private draw options for SnapshotUtils
	*/
	enum
	{
		kUseDefault = kMaxUInt32,
		kFastGroup = 0,	
		kTypicalGroup,
		kHighQualityGroup,
		kNavigatorGroup,
		kFastScrollGroup,
		kSepPrvGroup,
		kFlatPrvGroup,
		kSnapshotUtilsPrvGroup
	};

	/**
		Raster specific settings
		kRasterGrayOut	Images draw as a gray box
		kRasterProxy	Force proxy to draw at proxy resolution
		kRasterHighRes	High Res image
	*/
	typedef enum 
	{
		kRasterGrayOut = 0,
		kRasterProxy,
		kRasterHighRes
	} RasterDisplay;
	
	/**
		Vector graphic (placed PDF, PICT, EPS, WMF) specific settings
		kVectorGrayOut	Images draw as a gray box
		kVectorProxy	Force proxy to draw at proxy resolution
		kDisplayList	High Res Display list
	*/
	typedef enum 
	{
		kVectorGrayOut = 0,
		kVectorProxy,
		kDisplayList
	} VectorDisplay;

	/**
		Transparency specific settings
		kXPOff
		kXPLow			Crude approximations of transparency effects, blends honored
		kXPMedium		Low quality transparency effects, no page isolation set
		kXPHigh			Normal
		kXPMaximum		Resolution independent transparency effects (may not be implemented)
	*/
	typedef enum
	{
		kXPOff = 0,
		kXPLow,
		kXPMedium,
		kXPHigh,
		kXPMaximum
	} Transparencies;


	/** Return the number of DrawOption sets that have been defined.
	*/
	virtual int32 GetCount(void) const = 0;

	/** Set all the options for a given Set.  If a set does not exist with the same setID
		then it will be added. If you are adding your own set, then define the set's setID 
		to be your pluginID plus a constant to avoid conflicts with other 3rd party sets.
		@param set - IN: custom set to add to the list of DrawOption sets.
	*/
	virtual void SetSet(const DrawOptionsSet& set) = 0;

	/** Remove the DrawOptions set whose DrawOptionsSet.setID matches the setID paramater.
		@param setID - IN: ID of the custom set to remove.
	*/
	virtual void RemoveSet(uint32 setID) = 0;

	/** Set the active DrawOptions set that will be used when drawing to the associated port.
		@param setID - IN: setID fo the DrawOptionsSet to set as the active set.
	*/
	virtual bool8 SetActiveSetID(uint32 setID) = 0;	// returns kTrue if successful

	/** Return the active DrawOptions set that will be used when drawing to the associated port.
	*/
	virtual uint32 GetActiveSetID(void) const = 0;

	/** Get the DrawOptionsSet with the given setID
		@param setID - IN: setID of the DrawOptionsSet we are interested in.
		@param result - OUT: Pointer to the DrawOptionsSet with the associated setID.
		@return kTrue if successful
	*/
	virtual bool8 GetSetByID(uint32 setID, DrawOptionsSet* result) const = 0;

	/** Get the nth, zero-based DrawOptionsSet.  This routine is useful when iterating over all of the
		DrawOptionsSets.
		@param setIndex - IN: zero-based index.
		@return The DrawOptionsSet with the associated setID.
	*/
	virtual DrawOptionsSet GetSetByIndex(int32 setIndex) const = 0;
	
	/** Set the "Ignore Local Overrides" setting
		@param ignore - IN: kTrue to ignore local overrides, kFalse to honor them.
	*/
	virtual void SetIgnoreOverrides(bool8 ignore) = 0;
	
	/** Return the "Ignore Local Overrides" setting, which is kFalse by default.
	*/
	virtual bool8 GetIgnoreOverrides(void) const = 0;

	/** Determines whether local display overrides are saved in the document, or merely kept
		in memory and lost on doc close.
		@param save - IN: kTrue to persist the local overrides.  Not recommended.
	*/
	virtual void SetSaveLocalOverrides(bool8 save) = 0;
	
	/** 
		Return kTrue if the local overrides setting on page items is persisted.
	*/
	virtual bool8 GetSaveLocalOverrides() const = 0;

};

/** Default settings for kFastGroup
*/
const IDrawOptions::RasterDisplay kDefaultFastRaster = IDrawOptions::kRasterGrayOut;
const IDrawOptions::VectorDisplay kDefaultFastVector = IDrawOptions::kVectorGrayOut;
const IDrawOptions::Transparencies kDefaultFastXP = IDrawOptions::kXPOff;
const bool16 kDefaultFastAntiAlias = kFalse;
const double kDefaultFastGreekBelow = 7.0;

/** Default settings for kTypicalGroup
*/
const IDrawOptions::RasterDisplay kDefaultTypicalRaster = IDrawOptions::kRasterProxy;
const IDrawOptions::VectorDisplay kDefaultTypicalVector = IDrawOptions::kVectorProxy;
const IDrawOptions::Transparencies kDefaultTypicalXP = IDrawOptions::kXPMedium;
const bool16 kDefaultTypicalAntiAlias = kTrue;
const double kDefaultTypicalGreekBelow = 7.0;

/** Default settings for kHighQualityGroup
*/
const IDrawOptions::RasterDisplay kDefaultHighQualityRaster = IDrawOptions::kRasterHighRes;
const IDrawOptions::VectorDisplay kDefaultHighQualityVector = IDrawOptions::kDisplayList;
const IDrawOptions::Transparencies kDefaultHighQualityXP = IDrawOptions::kXPHigh;
const bool16 kDefaultHighQualityAntiAlias = kTrue;
const double kDefaultHighQualityGreekBelow = 7.0;

/** Default settings for kNavigatorGroup
*/
const IDrawOptions::RasterDisplay kDefaultNavigatorRaster = IDrawOptions::kRasterProxy;
const IDrawOptions::VectorDisplay kDefaultNavigatorVector = IDrawOptions::kVectorProxy;
const IDrawOptions::Transparencies kDefaultNavigatorXP = IDrawOptions::kXPOff;
const bool16 kDefaultNavigatorAntiAlias = kFalse;
const double kDefaultNavigatorGreekBelow = 7.0;

/** Default settings for kFastScrollGroup
*/
const IDrawOptions::RasterDisplay kDefaultFastScrollRaster = IDrawOptions::kRasterProxy;
const IDrawOptions::VectorDisplay kDefaultFastScrollVector = IDrawOptions::kVectorProxy;
const IDrawOptions::Transparencies kDefaultFastScrollXP = IDrawOptions::kXPOff;
const bool16 kDefaultFastScrollAntiAlias = kTrue;
const double kDefaultFastScrollGreekBelow = 7.0;

/** DrawOptionsSet
	Simple class containing the various draw settings.  The group of settings is referred to as a 
	Set.  These sets can be identified by a unique ID, called a setID.  DrawOptionsSets are passed to
	an IDrawOptions interface to set the drawing characterists for a given port.
*/
class DrawOptionsSet {
public:
	/** including a base_type allows this class to be stored in a vector.
	*/
	typedef base_type data_type;  
	
	/** Copy constructor
	*/
	DrawOptionsSet& operator = (const DrawOptionsSet& copy)
	{
		if ( this != &copy )
		{
			setID = copy.setID;
			raster = copy.raster;
			vector = copy.vector;
			xp = copy.xp;
			antiAlias = copy.antiAlias;
			greekBelow = copy.greekBelow;
		}
		
		return *this;
	}

	/** Testing for equality
	*/
	bool16 operator == (const DrawOptionsSet& other) const
	{
		return 
			setID == other.setID
			&& raster == other.raster
			&& vector == other.vector
			&& xp == other.xp
			&& antiAlias == other.antiAlias
			&& greekBelow == other.greekBelow;
	}

	/** Unique ID for this class instance.
	*/
	uint32							setID;
	/** Defines how raster images will draw (gray box, proxy, or high-res).
	*/
	IDrawOptions::RasterDisplay		raster;
	/** Defines how vector images will draw (gray box, proxy, or high-res).
	*/
	IDrawOptions::VectorDisplay		vector;
	/** Defines transparency quality.
	*/
	IDrawOptions::Transparencies	xp;
	/** At what effective point size do we start greeking the text.
	*/
	PMReal							greekBelow;
	/** Is anti-aliasing enabled? */
	bool16							antiAlias;
};

#endif
