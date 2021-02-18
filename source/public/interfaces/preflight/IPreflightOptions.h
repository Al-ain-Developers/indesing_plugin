//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightOptions.h $
//  
//  Owner: Matt Phillips
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

#include "IPMUnknown.h"
#include "PackageAndPreflightID.h"
#include "IPMStream.h"

/**	Data interface for preflight options. This interface sits on the document and application;
	the easiest way to get one is via IPreflightUtils::QueryPreflightOptions().

	Use extreme caution when changing the preflight options for a document directly, 
	because these need to be kept in sync with the active processes that are running in 
	the background. The safest ways to update this interface are via 
	IPreflightUtils::ApplyOptionsToDocument(), or better yet, using IPreflightFacade, which 
	does this through a command.
*/
class IPreflightOptions: public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTOPTIONS };

public:

	/**	Sets to true if disable preflight for all new/open and currently open documents.
		Note that this setting is only persistent at the application-level.
		@param onOff is true if to disable all preflights and false if to enable all preflights.
	*/
	virtual void SetPreflightOff (bool16 onOff) = 0;

	/**	@return true if preflight is disabled for all.
		Note that this is the application-wide preflight on/off setting.
	*/
	virtual bool16 GetPreflightOff () const = 0;

	/**	Defines the preflight profile policy when opening a document if preflight has been set to ON.
		This settings 
		kUseEmbeddedProfile indicates preflight using embedded profile if one exists.
		kUseWorkingProfile indicates preflight using a specified profile.
	*/
	typedef enum { kUseEmbeddedProfile = 0, kUseWorkingProfile } PreflightProfilePolicy;

	/**	Set the preflight profile policy for new/open documents when the preflight is enabled for all documents.
		Note that this setting only applies at the application-level.
		@param openPolicy specifies the policy to use.
	*/
	virtual void SetPreflightProfilePolicy (PreflightProfilePolicy profilePolicy) = 0;

	/**	@return the preflight profile policy for new/open document.
	*/
	virtual PreflightProfilePolicy GetPreflightProfilePolicy () const = 0;

	/**	Set the working preflight profile to use.
		Note that this setting only applies at the application-level.
		@see PreflightProfilePolicy
		@see SetPreflightProfilePolicy
		@param profileName specifies the name of the working preflight profile to use.
	*/
	virtual void SetUseProfile (const PMString& profileName) = 0;

	/**	@return the name of the working preflight profile to use.
	*/
	virtual PMString GetUseProfile () const = 0;

	/** Set whether the given document is using a document-embedded profile as opposed to an
		external (app-level) profile. This setting is only used at the document level and is
		nonpersistent.

		@param usingEmbedded IN kTrue for embedded; kFalse for application level.
	*/
	virtual void SetUsingEmbeddedProfile(bool16 usingEmbedded) = 0;

	/** Get whether the given document is using a document-embedded profile as opposed to an
		external (app-level) profile. This setting is only used at the document level and is
		nonpersistent.

		@return kTrue for embedded; kFalse for application level.
	*/
	virtual bool16 GetUsingEmbeddedProfile() const = 0;

	/**	Set whether to embed the working document in the new documet.
		Note that this setting only applies at the application-level.
		@param embed is true if the working profile (from GetUseProfile) should be embeded when
		creating a new document.
		@see GetUseProfile
	*/
	virtual void SetEmbedProfileInNewDocument (bool16 embed) = 0;

	/**	@return true if to embedded the working profile (from GetUseProfile) in the new document.
		@see GetUseProfile
	*/
	virtual bool16 GetEmbedProfileInNewDocument () const = 0;

	/**	Defines the options for including layers in the preflight.
		kAllLayers indicates that all layers are included.
		kVisibleLayers indicates that only visible layers are included.
		kVisibleAndPrintableLayers indicates that only visible and printable layers are included.
	*/
	typedef enum { kAllLayers = 0, kVisibleLayers, kVisiblePrintableLayers } LayerOptions;

	/**	Sets the layer optoins for preflight.
		Note that this setting only applies at the application-level.
		@param includLayerOption specified the layer option to use.
	*/
	virtual void SetIncludeLayers (LayerOptions includeLayerOption) = 0;

	/**	@return the preflight layer option.
	*/
	virtual LayerOptions GetIncludeLayers () const = 0;
	
	/**	Sets to true if include objects on the pasteboard for preflight.
		Note that this setting is only persistent at the application-level.
		@param onOff specifies either to include or exclude objects on the pasteboard.
		true if to include, otherwise excluded.
	*/
	virtual void SetIncludeObjectsOnPasteboard (bool16 onOff) = 0;
	
	/**	@return true if object included; otherwise false.
	*/
	virtual bool16 GetIncludeObjectsOnPasteboard () const = 0;
	
	/**	Sets to true if include non-printing objects for preflight.
		Note that this setting is only persistent at the application-level.
		@param onOff specifies either to include or exclude non-printing objects.
		true if to include, otherwise excluded.
	*/
	virtual void SetIncludeNonPrintingObjects (bool16 onOff) = 0;

	/**	@return true if object included; otherwise false.
	*/
	virtual bool16 GetIncludeNonPrintingObjects () const = 0;

	/**	Defines the preflighting scope.
		kAllPages indicates that all pages are included for preflight.
		kPageRanges indicates that only the specified page ranges are preflighted.
		Page ranges is accessed with SetPageRange and GetPageRage.
	*/
	typedef enum { kAllPages = 0, kPageRange } PreflightScope;

	/**	Sets the preflighting scope.
		This method only applies to documents.
		@param scope specified either to preflight all pages or a page range.
	*/
	virtual void SetScope (PreflightScope scope) = 0;
	
	/**
		This method only applies to documents.
		@return the preflighting scope.
	*/
	virtual PreflightScope GetScope () const = 0;

	/**	Sets the page range to preflight if the scope is set to kPageRanges.
		To specify a range, separate page numbers in the string with a hyphen (-). 
		To specify separate pages, separate page numbers in the string with a comma (,).
		This method only applies to documents.
		@param pageRange specified page ranges.
	*/
	virtual void SetPageRange (const PMString& pageRange) = 0;
	
	/**	
		This method only applies to documents.
		@return the string representing the page ranges for preflighting
	*/
	virtual PMString GetPageRange() const = 0;

	/**	Copy options data.
		@param iOther is the preflight option data to copy from.
	*/
	virtual void CopyFrom (const IPreflightOptions* iOther) = 0;
};


