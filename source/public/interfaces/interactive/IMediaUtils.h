//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IMediaUtils.h $
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
#ifndef __IMediaUtils_h__
#define __IMediaUtils_h__

#include "IPMUnknown.h"
#include "IMediaAdornmentInfo.h"
#include "IMediaAttributes.h"
#include "IURIData.h"

#include "MediaID.h"
#include "UIDList.h"
#include "Utils.h"

class PMRect;
class ILinkResource;
class ILinkManager;
class IHierarchy;
class IMediaReadFormat;
class MediaLocation;

/**
	This interface defines utility methods for working with media page items.
*/
class IMediaUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IMEDIAUTILS };
	
	/** Adds top and bottom adornments to a spline item.
		@param db valid pointer to the IDataBase interface of the spline item.
		@param itemUID UID of the spline item.
		@param info valid pointer to an IMediaAdornmentInfo interface which will provide the adornment info.
		@return kSuccess if successful; kFailure if unable to add the adornments.
	*/
	virtual ErrorCode	AddAdornments( IDataBase * db, UID itemUID, IMediaAdornmentInfo *info ) = 0;

	/** Attaches a media page item to a graphic frame. Existing children in the graphic frame's
		IHierarchy are destroyed.
		@param db valid pointer to the IDataBase interface of the page item to be added.
		@param mediaUID UID of the page item to be added.
		@param frameUID UID of a graphic frame.
		@param alignComponents if kTrue, aligns the media page item with the frame and the poster with the
		media page item. The media page item is resized if it has no intrinsic bounds.
		@precondition if alignComponents is kTrue, make sure IMediaAttributes::enIntrinsicBounds is
		set before calling this method in order to ensure proper alignment and sizing.
		@return kSuccess if successful; kFailure if the page item could not be added.
	*/
	virtual ErrorCode	AddMediaPIToGraphicFrame( IDataBase * db, UID mediaUID, UID frameUID, bool16 alignComponents = kFalse ) = 0;

	/** Aligns the poster with its parent media page item and the media page item with its
	    parent frame.  For media with no intrinsic bounds, resizes the media page item
		according to the rule: if the poster exists, the media page	item is sized to the
		poster bounds; otherwise, the media page item is sized to the parent frame's bounds.
		@param mediaRef a valid reference to the media page item.
		@precondition For correct alignment and sizing, make sure IMediaAttributes::enIntrinsicBounds
		is set before calling this method.
		@return kSuccess if successful, otherwise an ErrorCode (not necessarily kFailure).
	*/
	virtual ErrorCode AlignMediaComponents( UIDRef mediaRef ) = 0;

	/** Determines if a candidate page item can be converted into a media frame.
		@param candidateRef UIDRef of the page item to test for conversion.
		@return kTrue if the candidate can be converted; kFalse otherwise.
	*/
	virtual bool16		CanConvertToMediaFrame( UIDRef candidateRef ) = 0;

	/** Changes the location of media content from a specified filter. Changes the poster if it originated
		from the media.
		@param mediaRef valid UIDRef of existing media page item.
		@param newLocation specifies the new MediaLocation; if empty, clears the current location.
		@param readFormat IMediaReadFormat interface that is accessed to obtain the poster IPMStream
		and media attributes from the media filter (e.g., intrinsic bounds, whether a poster is
		available, etc); may be nil.
		@param customPosterFromMedia if True, the poster obtained from IMediaReadFormat is a custom poster from the media source.
		@param preservePoster if True, does not change the poster
		@precondition if readFormat is non-nil, it must be open before calling this method.
		@return kSuccess if successful; kFailure if the content could not be replaced.
		@postcondition Caller is responsible for closing readFormat.
	*/
	virtual ErrorCode ChangeMediaLocation( UIDRef mediaRef, const MediaLocation & newLocation = MediaLocation(), IMediaReadFormat * readFormat = nil, bool16 customPosterFromMedia = kFalse, bool16 preservePoster = kFalse ) = 0;

	/** Changes the media poster page item to a specified PosterType. If the change is made, the
		resulting poster page item will have a new UID.
	
		This method has no affect and returns kSuccess if the current poster already meets
		the call specifications (see also the description of the customPosterFromMedia param, below).
		To force a poster change, first call this method with the newPosterType set to IMediaAttributes::eNone.
		
		@param mediaRef the UIDRef of the parent media page item.
		@param newPosterType the desired IMediaAttributes::PosterType.
		@param posterImageFile a valid pointer to the poster image IDFile, required when
		newPosterType is IMediaAttributes::eProxyImage.
		@param posterFromMediaStream specifies the IPMStream to a media poster. This parameter
		is referenced when newPosterType is IMediaAttributes::eFromMedia. If nil, the poster is
		taken directly from the media content of the parent media page item specified by mediaRef.
		@param customPosterFromMedia boolean flag that indicates that the poster is a custom poster
		selected from the media content (e.g., an arbitrary frame in a movie). This flag is referenced
		only when newPosterType is IMediaAttributes::eFromMedia. The poster is always taken from
		the specified posterFromMediaStream and always results in a new poster page item. It is
		an error for this flag to be set to kTrue when posterFromMediaStream is nil.
		@param setUndoable specifies whether the changePoster command is undoable.
		@return kSuccess if the change was successful or if no change was necessary; an error code is returned if
		an error occurred during the change.
	*/
	virtual ErrorCode ChangePoster( UIDRef mediaRef,
									IMediaAttributes::PosterType newPosterType,
									const IDFile * posterImageFile = nil,
									IPMStream * posterFromMediaStream = nil,
									bool16 customPosterFromMedia = kFalse,
									int32 posterTime = 0,
									bool setUndoable=false) = 0;

	/** Changes the media poster page item to a specified PosterType using the image from the imageStream.
		@param mediaRef the UIDRef of the parent media page item.
		@param newPosterType must be set to IMediaAttributes::eFromMedia.
		@param imageStream read stream to the poster image data.
		@return kSuccess if the change was successful; an error code other than kSuccess is
		returned if an error occurred. kFailure is returned if one or more arguments are invalid.
	*/
	virtual ErrorCode ChangePoster( UIDRef mediaRef, IMediaAttributes::PosterType newPosterType, IPMStream * imageStream ) = 0;


	/** Creates a media page item of a specified classID, under a specified frame item,
		and the same size as the frame.
		@param classID the ClassID of the media page item to create.
		@param db valid pointer to an IDataBase instance. 
		@param frameUID the UID of the frame that will contain the new page item. This method will fail if
						the frameUID is invalid.
		@param outMediaUID upon successful return, this is populated with the UID of the new page item.
		@return kSuccess if successful; kFailure if the page item could not be created.
	*/
	virtual ErrorCode	CreateMediaPageItem( ClassID classID, IDataBase * db, UID frameUID, UID & outMediaUID ) = 0;

	/** Creates a media page item of a specified classID, under a specified frame item with
		the specified bounds.
		@param classID
		@param db valid pointer to an IDataBase instance.
		@param frameUID the UID of the frame that will contain the new page item, or kInvalidUID.
		@param bounds the PMRect of the new page item bounds.
		@param outMediaUID upon successful return, this is populated with the UID of the new page item.
		@return kSuccess if successful; kFailure if the page item could not be created.
	*/
	virtual ErrorCode	CreateMediaPageItem( ClassID classID, IDataBase * db, UID frameUID, PMRect bounds, UID & outMediaUID ) = 0;

	/** Creates a media page item with a default poster (standard poster or poster from the media if available).
		@param mediaClassID valid ClassID of the media page item to create.
		@param db valid IDataBase pointer.
		@param outMediaUID set to the new media page item UID upon successful return.
		@param frameUID	if valid, attaches the new media page item to the frame as a child page item.
		@param mediaLocation specifies the location of the media content (optional).
		@param formatClassID specifies the ClassID of the filter boss capable of reading the mediaImportStream. Required if
		mediaImportStream is non-nil.
		@param mediaImportStream a stream to the media content; if non-nil, formatClassID must specify a valid filter boss.
		@param uriData pass the link URI data if the linked media item is not a file.
		@return creation status; if successful, returns kSuccess.
	*/
	virtual ErrorCode	CreateMediaWithDefaultPoster(ClassID mediaClassID, IDataBase * db, UID & outMediaUID, const ClassID formatClassID = kInvalidClass, IPMStream * mediaImportStream = nil, IURIData* uriData=nil) = 0;

	/** Creates a read stream to the poster's low-res image (for thumbnails).
		@param mediaRef valid UIDRef to a media page item containing a poster page item.
		@return a valid pointer to an IPMStream object, or nil if an image could not be found.
	*/
	virtual IPMStream * CreatePosterLoResReadStream( UIDRef mediaRef ) = 0;

	/** Extracts an appropriate media name attribute from a MediaLocation.
		@param loc a MediaLocation object.
		@return PMString media name (may be a null string).
	*/
	virtual PMString ExtractMediaName( const MediaLocation & loc ) = 0;

	/** Finds the UID of the Media page item under the specified root.
		@param rootUIDRef valid UIDRef of IHierarchy root containing a Media page item.
		@return a valid UID if found; kInvalidUID if not found.
		@see IHierarchy.
	*/
	virtual UID	FindMediaUID( UIDRef & rootUIDRef ) = 0;

	virtual UIDRef GetMediaContentRef( const UIDRef & mediaRef ) = 0;

	/** Retrieves the parent of a Media page item.
		@param db valid pointer to an IDataBase instance. 
		@param mediaUID valid UID of a media page item.
		@return a valid UID if found; kInvalidUID if not found.
	*/
	virtual UID	GetMediaParentUID( IDataBase * db, UID mediaUID ) = 0;

	/** Retrieves the UID of the graphic frame parent of a Media page item.
		@param mediaRef valid UIDRef of a media page item.
		@return a valid UID if found; kInvalidUID if not found.
	*/
	virtual UID GetParentGraphicFrameUID( const UIDRef & mediaRef ) = 0;

	/** Tests if a specified spline item has media adornments.
		@param itemUID valid UID of spline item to test.
		@param db valid pointer to an IDataBase instance.
		@param info valid pointer to an IMediaAdornment instance.
		@return kTrue if media adornments were found on the spline item; kFalse if not.
	*/
	virtual bool16 HasAdornments( UID itemUID, IDataBase * db, IMediaAdornmentInfo *info ) = 0;

	/** Invalidates media frame page item caches; if mediaUID is not a frame, then invalidates
	    the caches of its parent frame. This utility should be called whenever a change affects
	    the size of media frame adornments.
		@param db valid pointer to an IDataBase instance.
		@param mediaUID valid UID of a media page item.
	*/
	virtual void InvalidateMediaFrameCaches( IDataBase * db, UID mediaUID ) = 0;

	/** Tests if a specified page item is a Media page item of a specified ClassID.
		@param classID the ClassID (boss ID) of a media page item boss based on the
		kMediaPageItemBoss.
		@param itemUID valid UID of the page item to test.
		@param db valid pointer to an IDataBase instance.
		@return kTrue if the item satisfies the condition; kFalse if not.
	*/
	virtual bool16	IsMediaItem( ClassID classID, UID itemUID, IDataBase * db ) = 0;
	
	/** Retrieves the media file for a specified media page item that can is compatible
		with the export format (assumed to be SWF for now).
		@param mediaRef refers to the UIDRef of an existing media page item.
		@param outFile is set to the media file to use for export. For example, if the original
			placed media file is an MPEG, outFile will refer to the equivalent FLV file.
		@return kTrue if a file is available; kFalse otherwise.
	*/
	virtual bool16 GetExportableMediaFile( UIDRef mediaRef, IDFile & outFile /*, todo: specify export format*/ ) = 0;

	/**
	 Retrieves the URL for a specified media page item that is compatible with the export
	 format (assumed to be SWF for now).
	 
	 @param mediaRef	[IN] The UIDRef of an existing media page item.
	 @param url			[OUT] The URL of the media page item, if any.
	 @return kTrue if a URL is available; kFalse otherwise.
	 */
	virtual bool16 GetExportableMediaURL(UIDRef const &mediaRef, PMString &url) const = 0;
	
	/**
	 Identifiers that denote a media's format type.
	 */
	enum MediaFormatType {
		/** Media format is an audio format. */
		kAudio = 0,
		/** Media format is a video format. */
		kVideo,
		/** Media format is not known or not applicable. */
		kUnknown
	};

	/**
	 Retrieves the location of the folder where video skins are stored.
	 
	 @param skins		[OUT] Vector of IDFiles, one per installed skin
	 @return true if successful, else false
	 */
	virtual bool GetInstalledVideoSkins(K2Vector<IDFile> &skins) const = 0;
	
	/**
	 Resolves a skin name to its location on disk.
	 
	 @param skin		[IN] The name of the skin to resolve
	 @param file		[OUT] The location of the skin file on disk
	 @return true if successful, else false
	 */
	virtual bool ResolveSkinNameToFile(PMString const &skin, IDFile &file) const = 0;

	/**
	 Determines the media page item is legacy media.
	 @param mediaRef [IN] The UIDRef of an existing media page item.
	 @return true if the page item is legacy media, else false.
	 */
	virtual bool IsLegacyMediaItem(UIDRef mediaRef) const = 0;

	/** Finds the IMediaReadFormat instance for a specified ClassID.
		@param readFormatClassID the ID of a boss aggregating the IMediaReadFormat interface.
		@return valid pointer to an IMediaReadFormat instance, if available; nil if not found.
	*/
	virtual IMediaReadFormat* FindMediaReadFormatForClassID( ClassID readFormatClassID ) = 0;

	/** Finds the IMediaReadFormat instance that can read from a specified MediaLocation.
		@param loc a MediaLocation to media content.
		@return valid pointer to an IMediaReadFormat instance which can access the URL and
		recognize the content. Returns nil if Internet access is not available, or there
		is no filter available which recognizes the content.
	*/
	virtual IMediaReadFormat* FindMediaReadFormatForLocation( const MediaLocation & loc ) = 0;
		
	/** Finds an IMediaReadFormat capable of reading media content from a stream.
		@param mediaType is either enMovie or enSound.
		@param iPMStream is a stream capable of reading the media content.
		@return valid pointer to an IMediaReadFormat instance if a format filter exists
		that recognizes the content; nil if a filter was not found.  
	*/ 
	virtual IMediaReadFormat* FindMediaReadFormatForStream( MediaType mediaType, IPMStream* iPMStream ) = 0;
	
	/** Verifies that a media location can be accessed for a MediaType. This method is 
		especially usefulfor checking whether URLs, though well-formed, can nevertheless
		be supported.
		@param loc a MediaLocation to media content.
		@param mediaType is either enMovie or enSound.
		@return kSuccess if the MediaLocation can be accessed, else an ErrorCode that
				describes why the MediaLocation can not be accessed.
	*/
	virtual ErrorCode CanAccess( const MediaLocation & loc, const MediaType mediaType ) = 0;
	
	/** Schedules a command to place a URL-based media item. The command is executed after the
		media format is decoded and attributes are available.
		@param mediaRef valid existing UIDRef.
		@param loc is set to the URL. Currently restricted to FLV and F4V video.
		@param bool if true, the existing poster is preserved; if false, the existing poster may be replaced
			as necessary.
		@param bool if true, decode attributes from the media file as needed; if false, does not decode.
		@return kSuccess if the command was scheduled; kFailure otherwise.
	*/
	virtual ErrorCode SchedulePlaceMediaFromURL( UIDRef mediaRef, const MediaLocation & loc, bool preserveExistingPoster = false, bool allowDecoding = true ) = 0;
	
	/** Schedules a command to replace the media poster with an image from the media. The
		poster is replaced when the image is decoded and the command completes.
		@param mediaRef valid existing UIDRef.
		@return kSuccess if the command was scheduled; kFailure otherwise. 
	*/
	virtual ErrorCode SchedulePosterFromMedia( UIDRef mediaRef ) = 0;

	/** Determines the media resource is in a flash only format that is unsupported(e.g. flv, f4v and swf).
	@param iResource the resource whose format to check.
	@return true if the resource is in an unsupported media format; false otherwise.
	*/
	virtual bool IsFlashOnlyMedia(ILinkResource* iResource) = 0;

	/** Directs to the APE removal GoURL which consists of information regarding the removal of flash
	and flash based formats(e.g. flv, f4v and swf) from InDesign.
	*/
	virtual void GoToAPERemovalURL() = 0;

	/** Modifies the extension format of flash based formats(e.g. flv, f4v and swf) by appending .unsupported(translated) in the end
	of the URI in order to trigger the missing links workflow.
	@param resourceUID valid existing UID of the imported file.
	@param iLinkMgr valid existing object of LinkManager class.
	@return kSuccess if the rename is succesful; kFailure otherwise.
	*/
	virtual ErrorCode ChangeFlashFormatExtension(UID resourceUID, ILinkManager* iLinkMgr) = 0;

	/** Verifies if the extension contains .unsupported(translated) append in the end of the URI of the imported file.
	@param iResource is the resource file to be verified.
	@return true if the resource has .unsupported extension; false otherwise.
	*/
	virtual bool HasUnsupportedExtension(ILinkResource * iResource) = 0;

};

#endif // __IMediaUtils_h__

