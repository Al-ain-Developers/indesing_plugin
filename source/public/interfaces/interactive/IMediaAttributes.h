//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IMediaAttributes.h $
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
#ifndef __IMediaAttributes__
#define __IMediaAttributes__

#include "IPMUnknown.h"
#include "MediaID.h"
#include "MediaLocation.h"
#include "NamedAttribute.h"

/**
	WARNING: this interface may change!

    This class defines the interface for accessing persistent media page item attributes.
 
    How to use this interface:
 
    You can use the accessors or mutators for media-common attributes, or use the
    generic accessors and mutators for attributes specific to a type of media. For
    the latter, you need a list of attribute IDs that are unique for the type of media
    you want to access.
 
    Some attributes, such as poster UID and PosterType, are derived algorithmically;
    that is, they don't have a dedicated database field. These attributes do not have
    mutators, so the accessors are designated as "read-only".
*/

const bool16 kDoNotPrintPosterDefault = kFalse;

class ISetMediaAttrCmdData;

class IMediaAttributes : public IPMUnknown
{

public:
	enum { kDefaultIID = IID_IMEDIAATTRIBUTES };
	
	enum { kInvalidAttributeID = 0xffffffff };
	
	/** This enum defines the IDs for attributes common to all media types.*/
	enum MediaAttributeID
	{
		/** The media title of user-specified text; type is PMString. */
		enTitle						= kMediaPrefix + 0,

		/** A flag which when set, indicates that the title is frozen (may not
			be changed except by the user). */
		enTitleIsFrozen				= kMediaPrefix + 1,

		/** The media description of user-specified text; type is PMString. */				
		enDescription				= kMediaPrefix + 2,

		/** A bool16 flag; when kTrue, indicates that the poster is a custom image created from the media
		    content. If this flag is not set, and enPosterIsFromMedia is set, then the poster is the
			default image taken from the media content. For movies, the default image is usually the
			first frame, or it could be an image designated as the poster by the media file format (the
			QuickTime format, for example, supports a poster atom). Note that this flag can be set only
			if enPosterIsFromMedia is also set. */
		enCustomPosterFromMedia		= kMediaPrefix + 3,

		/** A bool16 flag; when kTrue, indicates that the media content is to be embedded in
		    the PDF file during PDF export. Note that this attribute has no affect when
			exporting the deprecated PDF Movie Annotation (pre PDF 1.5). */
		enEmbedOnPDFExport			= kMediaPrefix + 4,

		/** A bool16 flag; when kTrue, indicates that the media poster (if it exists) may not
			be printed. This flag has no affect when the poster is displayed in the app or
			exported to PDF. */
		enDoNotPrintPoster			= kMediaPrefix + 5,
		
		/** A bool16 flag; when kTrue, indicates that the media poster (if it exists) may not
			be include with print or export output. This attribute is the same as enDoNotPrintPoster;
			the wording has been changed to indicate that it has been generalized to all forms of
			output. */
		enDoNotIncludePosterWithOutput = enDoNotPrintPoster,
		
		/** A bool16 flag; when kTrue, indicates that the media item should be exported to
		    PDF so that it automatically starts playing when the page it is on is visible in
			the PDF viewer. */
		enPlayOnPageTurn			= kMediaPrefix + 6,
		
		/** A uint32; the point in time in the media (movie) at which the poster was taken. */
		enPosterTime				= kMediaPrefix + 7,
		
		/** A PMString for the name of the controller skin. */
		enControllerSkinName		= kMediaPrefix + 8,
		
		/** Reserved for internal use by Adobe only */
		enReserved1					= kMediaPrefix + 9,
		
		/** A uint32 specifying the time in 1/100 seconds to start playing the video (default is 0). */
		enPlayStartPoint			= kMediaPrefix + 10,
		
		/** A uint32 specifying the time in 1/100 seconds to stop playing the video (default is video total time). */
		enPlayEndPoint				= kMediaPrefix + 11,
		
		/** A bool16 flag; when kTrue, mousing over the video will show the controller. */
		enShowControllerOnRollover	= kMediaPrefix + 12,
		
		/** A bool16 flag; when kTrue, media stops playing when its page is turned. 
			Currently relevant only for sound (audio) media. */
		enStopPlayOnPageTurn		= kMediaPrefix + 13,
		
		/** A bool16 flag; when kTrue, media loops forever.
			Currently relevant only for sound (audio) media exported to SWF. */
		enLoopForever				= kMediaPrefix + 14,
		
		/** Obsolete */
		enPlayFullScreen_Obsolete	= kMediaPrefix + 15,
		
		/** Obsolete */
		enPageLoadDelay_Obsolete		= kMediaPrefix + 16,
		
		/** Obsolete */
		enShowControllerOnTap_Obsolete	= kMediaPrefix + 17,

		/** Obsolete */
		enControllerAssetFolder_Obsolete = kMediaPrefix + 18,
		
		/** This value must not be used as an attribute ID outside of the Media plugin. */
		enReserved					= kMediaPrefix + 0xff // For internal use
	};

	/** This enum defines the types of media posters. */
	enum PosterType
	{
		/** There is no poster. */
		eNone,
		/** Poster is a standard poster icon. */
		eStandard,
		/** Poster originated from the media location. */
		eFromMedia,
		/** Poster is an arbitrary proxy image not taken from the media content location. */
		eProxyImage
	};

	// --- Generic polymorphic attribute accessors for each supported value type:

	/** Retrieves an attribute of type int16.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value a variable to contain the attribute's value.
		@return kSuccess if the attribute exists; kFailure otherwise.
	*/
	virtual ErrorCode GetAttribute( uint32 attributeID, int16 & value ) const = 0;

	/** Retrieves the value of an attribute of type int32.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value a variable to contain the attribute's value.
		@return kSuccess if the attribute exists; kFailure otherwise.
	*/
	virtual ErrorCode GetAttribute( uint32 attributeID, int32 & value ) const = 0;

	/** Retrieves the value of an attribute of type uint32.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value a variable to contain the attribute's value.
		@return kSuccess if the attribute exists; kFailure otherwise.
	*/
	virtual ErrorCode GetAttribute( uint32 attributeID, uint32 & value ) const = 0;
	
	/** Retrieves the value of an attribute of type ClassID.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value a variable to contain the attribute's value.
		@return kSuccess if the attribute exists; kFailure otherwise.
	*/
	virtual ErrorCode GetAttribute( uint32 attributeID, ClassID & value ) const = 0;

	/** Retrieves the value of an attribute of type PMPoint.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value a variable to contain the attribute's value.
		@return kSuccess if the attribute exists; kFailure otherwise.
	*/
	virtual ErrorCode GetAttribute( uint32 attributeID, PMPoint & value ) const = 0;

	/** Retrieves the value of an attribute of type PMReal.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value a variable to contain the attribute's value.
		@return kSuccess if the attribute exists; kFailure otherwise.
	*/
	virtual ErrorCode GetAttribute( uint32 attributeID, PMReal & value ) const = 0;

	/** Retrieves the value of an attribute of type PMRect.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value a variable to contain the attribute's value.
		@return kSuccess if the attribute exists; kFailure otherwise.
	*/
	virtual ErrorCode GetAttribute( uint32 attributeID, PMRect & value ) const = 0;

	/** Retrieves the value of an attribute of type PMString.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value a variable to contain the attribute's value.
		@return kSuccess if the attribute exists; kFailure otherwise.
	*/
	virtual ErrorCode GetAttribute( uint32 attributeID, PMString & value ) const = 0;

	/** Retrieves the value of an attribute of type NamedInt32AttributeList.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value a variable to contain the attribute's value.
		@return kSuccess if the attribute exists; kFailure otherwise.
	*/
	virtual ErrorCode GetAttribute( uint32 attributeID, NamedUint32AttributeList & value ) const = 0;
	
	// --- Generic polymorphic attribute mutators for each supported value type:

	/** Sets the value of an attribute of type int16.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value the contents of this are copied to the attribute.
	*/
	virtual void SetAttribute( uint32 attributeID, int16 value ) = 0;

	/** Sets the value of an attribute of type int32.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value the contents of this are copied to the attribute.
	*/
	virtual void SetAttribute( uint32 attributeID, int32 value ) = 0;

	/** Sets the value of an attribute of type uint32.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value the contents of this are copied to the attribute.
	*/
	virtual void SetAttribute( uint32 attributeID, uint32 value ) = 0;
	
	/** Sets the value of an attribute of type ClassID.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value the contents of this are copied to the attribute.
	*/
	virtual void SetAttribute( uint32 attributeID, ClassID value ) = 0;

	/** Sets the value of an attribute of type PMPoint.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value the contents of this are copied to the attribute.
	*/
	virtual void SetAttribute( uint32 attributeID, const PMPoint & value ) = 0;

	/** Sets the value of an attribute of type PMReal.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value the contents of this are copied to the attribute.
	*/
	virtual void SetAttribute( uint32 attributeID, const PMReal & value ) = 0;

	/** Sets the value of an attribute of type PMRect.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value the contents of this are copied to the attribute.
	*/
	virtual void SetAttribute( uint32 attributeID, const PMRect & value ) = 0;

	/** Sets the value of an attribute of type PMString.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value the contents of this are copied to the attribute.
	*/
	virtual void SetAttribute( uint32 attributeID, const PMString & value ) = 0;

	/** Sets the value of an attribute of type NamedInt32AttributeList.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value the contents of this are copied to the attribute.
	*/
	virtual void SetAttribute( uint32 attributeID, const NamedUint32AttributeList & value ) = 0;
	
	// --- Methods for handling conditional attributes

	/** Tests if a flag attribute is set.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@return kTrue if the flag is set; kFalse otherwise.
	*/
	virtual bool16 IsFlagSet( uint32 attributeID ) const = 0;

	/** Sets or clears a flag attribute.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param b flag value; specify kTrue to set the flag, or kFalse to clear it.
	*/
	virtual void SetFlag( uint32 attributeID, bool16 b ) = 0;

	/** Applies all set attribute values to an ISetMediaAttrCmdData instance.
		@param destData valid pointer to an ISetMediaAttrCmdData to receive the attribute values.
	*/
	virtual ErrorCode ApplyAttributes( ISetMediaAttrCmdData * destData ) const = 0;

	/** Clears the value of an int16 attribute. When this method returns, the attribute will no longer be found.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
	*/
	virtual void ClearInt16Value( uint32 attributeID ) = 0;
	
	/** Clears the value of a PMPoint attribute. When this method returns, the attribute will no longer be found.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
	*/	
	virtual void ClearPMPointValue( uint32 attributeID ) = 0;

	/** Removes/Clears all Attributes.
	*/	
	virtual void ClearAllAttributes() = 0;

}; // end IMediaAttributes interface


#endif // __IMediaAttributes__