//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IMediaContentData.h $
//  
//  Owner: wtislar
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
#ifndef __IMediaContentData__
#define __IMediaContentData__

#include "IPMUnknown.h"
#include "MediaID.h"
#include "MediaLocation.h"
#include "NamedAttribute.h"

/**
	This interface provides a convenient way to cache metadata for media content. There are two sets
	of methods: accessors and mutators (i.e., "getters" and "setters"). In general, mutators are
	invoked by media filters to store information about a specific media source. For example, an
	MPEG filter would store information about a particular MPEG movie file. This information could then
	be retrieved without the need to reinterpret the file. Since the attributes are stored as name/value
	pairs (i.e., they are "tagged"), it's not necessary for a filter to set all of the attributes; simply
	setting the relevant attributes is sufficient. Likewise, interface users that invoke the accessors,
	should allow for the fact that a value for a particular attribute ID may or may not exist, and that
	its absence is not necessarily an error.
*/

class IMediaContentData : public IPMUnknown
{

public:
	
	enum { kDefaultIID = IID_IMEDIACONTENTDATA };

	/** This enum defines the IDs for attributes common to all media types.*/
	enum MediaContentAttributeID
	{
		/** The ClassID of the media filter boss that aggregates the IID_IMEDIAREADFORMAT interface */
		enFormatClassID				= kMediaPrefix + 0,

		/** The intrinsic geometric bounds of the media item, which may be empty;
			type is PMRect. */
		enIntrinsicBounds			= kMediaPrefix + 1,

		/** A flag which when set, indicates that a poster image is available from
		    the media content. */
		enPosterImageIsAvailable	= kMediaPrefix + 2,

		/** The URL to the media content; type is PMString */
		enURL						= kMediaPrefix + 3,
		
		/** A flag that indicates (when set) that poster images can be taken from the media. */
		enCanChoosePosters			= kMediaPrefix + 4,
		
		/** A PMString of the encoded media file */
		enNameOfEncodedFile			= kMediaPrefix + 5,
		
		/** A PMReal representing seconds. */
		enDuration					= kMediaPrefix + 6,
		
		/** A uint32 representing the RGB background color (currently applies only to SWFs). */
		enBackgroundColor			= kMediaPrefix + 7,
		
		/** A NamedUint32AttributeList of navigation cue points from a video. */
		enNavigationCuePoints		= kMediaPrefix + 8,

		/** A NamedUint32AttributeList of event cue points from a video (not currently used). */
		enEventCuePoints			= kMediaPrefix + 9,
		
		/** A flag. When set, indicates that the media content is H.264 encoded. */
		enH264Encoded				= kMediaPrefix + 10,	
		
		/** This value must not be used as an attribute ID outside of the Media plugin. */
		enReserved					= kMediaPrefix + 0xff // For internal use		
	};


	// --- Generic polymorphic attribute accessors for each supported value type:

	/** Retrieves an attribute of type int16.
		@param attributeID may be either a MediaContentAttributeID or a media-specific ID.
		@param value a variable to contain the attribute's value.
		@return kSuccess if the attribute exists; kFailure otherwise.
	*/
	virtual ErrorCode GetAttribute( uint32 attributeID, int16 & value ) const = 0;

	/** Retrieves the value of an attribute of type int32.
		@param attributeID may be either a MediaContentAttributeID or a media-specific ID.
		@param value a variable to contain the attribute's value.
		@return kSuccess if the attribute exists; kFailure otherwise.
	*/
	virtual ErrorCode GetAttribute( uint32 attributeID, int32 & value ) const = 0;

	/** Retrieves the value of an attribute of type ClassID.
		@param attributeID may be either a MediaContentAttributeID or a media-specific ID.
		@param value a variable to contain the attribute's value.
		@return kSuccess if the attribute exists; kFailure otherwise.
	*/
	virtual ErrorCode GetAttribute( uint32 attributeID, ClassID & value ) const = 0;

	/** Retrieves the value of an attribute of type PMPoint.
		@param attributeID may be either a MediaContentAttributeID or a media-specific ID.
		@param value a variable to contain the attribute's value.
		@return kSuccess if the attribute exists; kFailure otherwise.
	*/
	virtual ErrorCode GetAttribute( uint32 attributeID, PMPoint & value ) const = 0;

	/** Retrieves the value of an attribute of type PMReal.
		@param attributeID may be either a MediaContentAttributeID or a media-specific ID.
		@param value a variable to contain the attribute's value.
		@return kSuccess if the attribute exists; kFailure otherwise.
	*/
	virtual ErrorCode GetAttribute( uint32 attributeID, PMReal & value ) const = 0;

	/** Retrieves the value of an attribute of type PMRect.
		@param attributeID may be either a MediaContentAttributeID or a media-specific ID.
		@param value a variable to contain the attribute's value.
		@return kSuccess if the attribute exists; kFailure otherwise.
	*/
	virtual ErrorCode GetAttribute( uint32 attributeID, PMRect & value ) const = 0;

	/** Retrieves the value of an attribute of type PMString.
		@param attributeID may be either a MediaContentAttributeID or a media-specific ID.
		@param value a variable to contain the attribute's value.
		@return kSuccess if the attribute exists; kFailure otherwise.
	*/
	virtual ErrorCode GetAttribute( uint32 attributeID, PMString & value ) const = 0;

	/** Retrieves the value of an attribute of type NamedInt32AttributeList.
		@param attributeID may be either a MediaContentAttributeID or a media-specific ID.
		@param value a variable to contain the attribute's value.
		@return kSuccess if the attribute exists; kFailure otherwise.
	*/
	virtual ErrorCode GetAttribute( uint32 attributeID, NamedUint32AttributeList & value ) const = 0;
	
	// --- Generic polymorphic attribute mutators for each supported value type:

	/** Sets the value of an attribute of type int16.
		@param attributeID may be either a MediaContentAttributeID or a media-specific ID.
		@param value the contents of this are copied to the attribute.
	*/
	virtual void SetAttribute( uint32 attributeID, int16 value ) = 0;

	/** Sets the value of an attribute of type int32.
		@param attributeID may be either a MediaContentAttributeID or a media-specific ID.
		@param value the contents of this are copied to the attribute.
	*/
	virtual void SetAttribute( uint32 attributeID, int32 value ) = 0;

	/** Sets the value of an attribute of type ClassID.
		@param attributeID may be either a MediaContentAttributeID or a media-specific ID.
		@param value the contents of this are copied to the attribute.
	*/
	virtual void SetAttribute( uint32 attributeID, ClassID value ) = 0;

	/** Sets the value of an attribute of type PMPoint.
		@param attributeID may be either a MediaContentAttributeID or a media-specific ID.
		@param value the contents of this are copied to the attribute.
	*/
	virtual void SetAttribute( uint32 attributeID, const PMPoint & value ) = 0;

	/** Sets the value of an attribute of type PMReal.
		@param attributeID may be either a MediaContentAttributeID or a media-specific ID.
		@param value the contents of this are copied to the attribute.
	*/
	virtual void SetAttribute( uint32 attributeID, const PMReal & value ) = 0;

	/** Sets the value of an attribute of type PMRect.
		@param attributeID may be either a MediaContentAttributeID or a media-specific ID.
		@param value the contents of this are copied to the attribute.
	*/
	virtual void SetAttribute( uint32 attributeID, const PMRect & value ) = 0;

	/** Sets the value of an attribute of type PMString.
		@param attributeID may be either a MediaContentAttributeID or a media-specific ID.
		@param value the contents of this are copied to the attribute.
	*/
	virtual void SetAttribute( uint32 attributeID, const PMString & value ) = 0;

	/** Sets the value of an attribute of type NamedInt32AttributeList.
		@param attributeID may be either a MediaContentAttributeID or a media-specific ID.
		@param value the contents of this are copied to the attribute.
	*/
	virtual void SetAttribute( uint32 attributeID, const NamedUint32AttributeList & value ) = 0;
	
	// --- Methods for handling conditional attributes

	/** Tests if a flag attribute is set.
		@param attributeID may be either a MediaContentAttributeID or a media-specific ID.
		@return kTrue if the flag is set; kFalse otherwise.
	*/
	virtual bool16 IsFlagSet( uint32 attributeID ) const = 0;

	/** Sets or clears a flag attribute.
		@param attributeID may be either a MediaContentAttributeID or a media-specific ID.
		@param b flag value; specify kTrue to set the flag, or kFalse to clear it.
	*/
	virtual void SetFlag( uint32 attributeID, bool16 b ) = 0;
		
}; // end IMediaContentData interface


#endif // __IMediaContentData__