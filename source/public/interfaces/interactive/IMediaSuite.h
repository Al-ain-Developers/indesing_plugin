//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IMediaSuite.h $
//  
//  Owner: Bill Tislar
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
//  Comments:	Selection suite for multimedia page items
//  
//========================================================================================

#pragma once
#ifndef _IMediaSuite_
#define _IMediaSuite_

#include "MediaID.h"
#include "IMediaAttributes.h"
#include "IMediaContent.h"
#include "IMovieAttributes.h"
#include "INavigationPoints.h"
#include "ISetMediaAttrCmdData.h"

/** Selection suite for manipulating Media page items.
	
*/
class IObserver;

class IMediaSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IMEDIASUITE };

	/** Adds a new navigation point for a specified time.
		@param time identifies a frame of the video to seek to in 1/100s of a second.
		@return -1 if the add failed; otherwise the index of the added point.
	*/
	virtual int32 AddNavigationPoint( uint32 time ) = 0;

	/** Tests if a navigation point can be added.
		@return true if the navigation point can be added; false otherwise.
	*/
	virtual bool CanAddNavigationPoint() const = 0;
	
	/** Tests if the selection can be converted into a media page item.
		@return kTrue if the selection can be converted into a media page item.
	*/
	virtual bool CanConvertToMedia() const = 0;

	/** Tests if the navigation point at the specified index can be removed.
		@param indexAt specifies the index of an existing navigation point.
		@return true if the navigation point can be removed; false otherwise.
	*/
	virtual bool CanRemoveNavigationPoint( int32 indexAt ) const = 0;
	
	/** Tests if navigation points can be selected. 
		@return true if the navigation points can be selected; false otherwise.
	*/
	virtual bool CanSelectNavigationPoints() const = 0;

	/** Tests if a poster can be set for a poster selection option.
		Since an option may be strictly for information, this method should be called before
		attempting to change the poster.
		@param optionIndex is an index in the list of poster options obtained from GetPosterOptions().
		@return true if the poster can be set; false otherwise.
	*/
	virtual bool CanSetPosterForIndex( uint32 optionIndex ) const = 0;
	
	/** Tests if posters can be set. 
		@return true if posters can be set; false otherwise.
	*/
	virtual bool CanSetPosters() const = 0;
	
	/** Changes the display name for a navigation point.
		@param name is a navigation point display name.
		@param indexAt is the index of the navigation point in the range 0 to GetNumberOfNavigationPoints() - 1.
		@return kSuccess if the name was changed successfully; fFailure otherwise.
	*/	
	virtual ErrorCode ChangeNavigationPointDisplayName( const PMString & name, int32 indexAt ) = 0;
			
	/** Tests if the current selection has a missing link.
		@return true if the current selection has a link to a file and the link is missing; false otherwise.
	*/
	virtual bool HasMissingLink() const = 0;
	
	/** Retrieves the value of an attribute of type int16.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value a variable to contain the attribute's value.
		@return kSuccess if the attribute exists; kFailure otherwise.
	*/
	virtual ErrorCode GetAttribute( uint32 attributeID, int16 & value ) const = 0;
	
	/** Retrieves the value of an attribute of type PMString.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value a variable to contain the attribute's value.
		@return kSuccess if the attribute exists; kFailure otherwise.
	*/
	virtual ErrorCode GetAttribute( uint32 attributeID, PMString & value ) const = 0;

	/** Retrieves the list of controller options for the current selection.
		@param optionList is populated with the list of controller option PMStrings.
		@return the number of items in the list.
	*/
	virtual int GetControllerOptions( K2Vector<PMString> & optionList ) const = 0;
	
	/** Gets the model's current controller option index.
		@returns an index in the optionList provided by IMediaSuite::GetControllerOptions().
	*/
	virtual uint32 GetControllerOptionIndex() const = 0;

	/** Tests if a specific controller option is enabled.
		@param optionIndex is an index in the controller option list obtained by
			calling GetControllerOptions().
		@returns true if the option is enabled; false otherwise.
	*/
	virtual bool IsControllerOptionEnabled( uint32 optionIndex ) const = 0;
	
	/** Tests if controller selection is enabled.
		@returns true if the controller selection is enabled; false otherwise.
	*/
	virtual bool IsControllerSelectionEnabled() const = 0;
	
	/** Sets the controller option for the current selection.
		@param optionIndex index of an entry in the controller option list.
		@see method IMediaSuite::GetControllerOptions.
	*/
	virtual void SetControllerOption( uint32 optionIndex ) = 0;
					
	/** Obtains an existing empty frame that can be converted into a multimedia frame.
		@precondition A single empty frame must be selected; multiple selections are
					  not supported.
		@return UIDRef to a single empty frame.
	*/
	virtual UIDRef GetEmptyFrameRef() const = 0;

	/** Obtains the MediaLocation for the page item's content.
		@param outLocation is populated with the MediaLocation object.
		@return true if the location is available; false if not.
	*/
	virtual bool GetMediaLocation( MediaLocation & outLocation ) const = 0;

	/** Obtains the URL to the media page item's content.
		@param outLocation is populated with the URL.
		@return true if the location is available; false if not.
	*/
	virtual bool GetMediaURL( WideString & outURL ) const = 0;
	
	/** Gets the MultimediaType of the current selection. If the current selection consists of
		more than one page item or a non-multimedia page item, the MultimediaType is enUndefined.
		@return IMediaContent::MediaType.
	*/
	virtual IMediaContent::MediaType GetMediaType() const = 0;

	/** Retrieves the display name for a specified navigation point.
		@param indexAt is the index of the navigation point in the range 0 to GetNumberOfNavigationPoints() - 1.
		@param outName is populated with the display name.
		@return true if outName was populated; false otherwise.
	*/
	virtual bool GetNavigationPointDisplayName( int32 indexAt, PMString & outName ) = 0;

	/** Retrieves the next navigation point or none if iteration passed the end of the list.
		@param navPoint is populated with the next navigation point data.
		@return true if the next navigation point was available; otherwise returns false.
	*/
	virtual bool GetNextNavigationPoint( INavigationPoints::NavigationPoint & navPoint ) const = 0;

	/** Returns the number of navigation points currently defined.
		@return the number of navigation points.
	*/
	virtual uint32 GetNumberOfNavigationPoints() const = 0;

	/** Obtains the poster type associated with the media page item.
		@return the IMediaAttributes::PosterType.
	*/
	virtual IMediaAttributes::PosterType GetPosterType() const = 0;
	
	/** Tests if a media attribute may be enabled for changing by the UI.
		@return kTrue if enabled; kFalse otherwise.
	*/			
	virtual bool16 IsAttributeEnabled( uint32 attributeID ) const = 0;

	/** Tests if a flag attribute is set.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@return kTrue if the flag is set; kFalse otherwise.
	*/
	virtual bool16 IsFlagSet( uint32 attributeID ) const = 0;
		
	/** Tests the current selection for multimedia page items.
		@return true if the selection contains all multimedia page items (or default selection); false otherwise.
	*/
	virtual bool IsMediaSelection() const = 0;
	
	/** Removes one or more navigation points.
		@param indexList is a list of indices. Each index must be in the range 0 to GetNumberOfNavigationPoints() - 1.
		@return kSuccess indicating that a navigation point no longer exists for any index in the list; kFailure if
			one or more navigation points could not be removed.
	*/
	virtual ErrorCode RemoveNavigationPoints( const K2Vector<int32> & indexList ) = 0;	

	/** Resets the navigation point list interator so that the next call to GetNextNavigationPoint() will
		return the first navigation point in the list. 
	*/
	virtual void ResetNavigationPointsIterator() = 0;
		
	/** Sets the value of an attribute of type int16.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value the contents of this are copied to the attribute.
		@return kSuccess if the attribute was set; kFailure otherwise.
	*/	
	virtual ErrorCode SetAttribute( uint32 attributeID, int16 value ) = 0;

	/** Sets the value of an attribute of type PMString.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value the contents of this are copied to the attribute.
		@return kSuccess if the attribute was set; kFailure otherwise.
	*/
	virtual ErrorCode SetAttribute( uint32 attributeID, const PMString & value ) = 0;

	/** Sets the value of an attribute of type NamedUint32AttributeList.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value the contents of this are copied to the attribute.
		@return kSuccess if the attribute was set; kFailure otherwise.		
	*/
	virtual ErrorCode SetAttribute( uint32 attributeID, const NamedUint32AttributeList & value ) = 0;

	/** Sets one or more attributes taken from an ISetMediaAttrCmdData instance. This method
			has no effect if the ISetMediaAttrCmdData instance has no data.
		@param inData an ISetMediaAttrCmdData prepopulated with attribute data.
		@return kSuccess if all attributes were set; kFailure otherwise.
	*/
	virtual ErrorCode SetAttributes( const ISetMediaAttrCmdData * inData ) = 0;
		
	/** Sets the poster pageitem to a specified PosterType.
		@param posterType specifies the desired poster.
		@param time identifies the video frame to use as the poster for IMediaAttributes::eFromMedia.
		@return kSuccess if the method succeeded; otherwise returns an error code that may or may not be kFailure.
	*/
	virtual ErrorCode SetPoster( IMediaAttributes::PosterType posterType, int32 time ) = 0;

	/** Sets the poster pageitem to a specified image.
		@param file specifies an image file.
		@return kSuccess if the method succeeded; otherwise returns an error code that may or may not be kFailure.
	*/
	virtual ErrorCode SetPoster( IDFile & file ) = 0;

	/** Sets or clears a flag attribute.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param b flag value; specify kTrue to set the flag, or kFalse to clear it.
		@return kSuccess if the method succeeded; otherwise returns kFailure.		
	*/
	virtual ErrorCode SetFlag( uint32 attributeID, bool16 b = kTrue ) = 0;
	
	/** Sets the poster to a stream image. The image data is embedded in the poster page item.
		@param posterType specifies the type of poster to set.
		@param posterStream is a valid pointer to an IPMStream that will supply the poster image.
		@param setUndoable specifies whether the poster command is undoable.
		@return kSuccess if the method succeeded; otherwise returns an error code that may or may not be kFailure.
	*/
	virtual ErrorCode SetPoster( IMediaAttributes::PosterType posterType, IPMStream * posterStream, bool setUndoable = false) = 0;
	
	/** Retrieves the list of poster selection options.
		@param stringList is populated with the list of option PMStrings.
		@return the number of options.
	*/
	virtual int GetPosterOptions( K2Vector<PMString> & stringList ) const = 0;
	
	/** Gets the model's current poster option index.
		@returns an index in the stringList provided by IMediaSuite::GetPosterOptions().
	*/
	virtual uint32 GetPosterOptionIndex() const = 0;
	
	/** Tests if a poster option is enabled.
		@param optionIndex is a valid poster option index.
		@return true if the option is enabled; false otherwise. 
	*/
	virtual bool IsPosterOptionEnabled( uint32 optionIndex ) const = 0;
	
	/** Tests if a poster can be obtained from the current selection's media content (i.e, tests if a poster can be obtained
		from a frame of the video).
		@return true if a poster can be created from the media; false otherwise. 
	*/
	virtual bool IsPosterFromMediaEnabled() const = 0;
	
	/** Sets the IMediaContent::MediaType and location for the current selection.
		@param mediaType the IMediaContent::MediaType to set.
		@param a valid location which can be either a file path or a url.
		@param isURL if true, specifies that the location is a url.
		@return kSuccess if the location was changed; otherwise returns an error code.
	*/
	virtual ErrorCode SetMediaLocation( IMediaContent::MediaType mediaType, const WideString & loc, bool isURL = false ) = 0;
	
	/** Retrieves the index for the current floating window position choice for the current selection.
		@return the index of the floating window position option.
	*/
	virtual uint32 GetFloatingWindowPositionIndex() const = 0;
	
	/** Retrieves the index for the current floating window scale choice for the current selection.
		@return the index of the floating window scale option.
	*/
	virtual uint32 GetFloatingWindowScaleIndex() const = 0;
	
	/** Tests if navigation points are available for the current selection. Navigation points are
		currently available only for IMediaContent::enVideo.
		@return kTrue if navigation points are available; kFalse otherwise.
	*/
	virtual bool16 AreNavigationPointsEnabled() const = 0;
	
	/** Tests if PDF options can be changed for the current selection.
		@return kTrue if options can be changed; kFalse otherwise.
	*/
	virtual bool16 CanChangePDFOptions() const = 0;
	
	/** Tests if the current selection can be replaced by URL-based media.
		@return kTrue if the current selection can be replaced; kFalse otherwise.
	*/
	virtual bool16 CanPlaceMediaFromURL() const = 0;
	
	/** Retrieves the media name for the current selection. This is currently the base filename with extension.
		@param outName is set to the media name.
		@return true if the name is available; otherwise returns false.
	*/
	virtual bool GetMediaName( WideString & outName ) const = 0;
	
	/** Places a URL-based movie in an empty graphic frame or if the frame is not empty, replaces an
		existing movie.
		@param type must be IMediaContent::enVideo.
		@param url a valid url to an FLV or F4V video.
		@return kSuccess if the movie was replaced or created successfully; otherwise a failure code.
	*/
	virtual ErrorCode PlaceMediaFromURL( IMediaContent::MediaType type, const WideString & url ) = 0;
	
	/** Starts previewing the media content for the current selection in the media player. Does not reload
		the media the player if there is no change in selection or media location.
		@param type must be IMediaContent::enVideo, IMediaContent::enAudio or IMediaContent::enSWFAnimation.
		@param iObserver is an optional pointer to an IObserver to notify of player events. Notification occurs
			via IObserver::Update with protocol IID_IMEDIAPLAYERACCESS. The IObserver should update any widgets
			that depend on player functionality.
		@return kSuccess if the player loaded the content successfully; kFailure otherwise.
	*/
	virtual ErrorCode StartMediaPreview( IMediaContent::MediaType type, IObserver * iObserver = nil ) = 0;
	
	/** Stops previewing the media content for a specified media type.
		@param type must be IMediaContent::enVideo, IMediaContent::enAudio or IMediaContent::enSWFAnimation.
		@return kSuccess if the media was unloaded (or there was no media to unload); kFailure otherwise.
	*/
	virtual ErrorCode StopMediaPreview( IMediaContent::MediaType type ) = 0;

};


#endif // _IMediaSuite_