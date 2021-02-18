//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IXPUtils.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __IXPUtils__
#define __IXPUtils__

#include "XPID.h"
#include "IPMUnknown.h"
#include "Utils.h"

#include "IXPManager.h"
#include "IFlattenerSettings.h"
#include "IViewPortAttributes.h"
#include "BravoForwardDecl.h"

class IDocument;
class IControlView;

/** Utilities related to transparency.
*/
class IXPUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXPUTILS };

	// Used for CreateFlattener() below
	typedef enum
	{
		kModeLegacy,		// Preserve spots/overprint
		kModeSimPress,		// Do OPP
		kModeSimScreen		// Without OPP (no spots declared)
	} FlattenOutputMode;

	// Used for CreateFlattener() below
	class FlattenSettings
	{
	public:
		PMReal	fLevel;
		PMReal	fInternalDPI;
		PMReal	fExternalDPI;
		PMReal	fMapDPI;
		PMReal	fPathDPI;

		// Note: if CreateFlattener() returns a non-nil value here, you're
		// responsible for releasing it via IXPUtils::ReleaseBlendSpace().
		// Otherwise you'll get a memory leak.
		AGMColorSpace* fBlendSpace; 
	};

	// QueryXPManager: Gets the transparency manager for the specified doc.  
	// Note: If doc == nil, fails (there is no xpmanager on the default doc).
	// The IDataBase form requires a non-nil iDB, which must be a doc DB.
	virtual IXPManager *QueryXPManager(IDocument *iDoc) = 0;
	virtual IXPManager *QueryXPManager(IDataBase *iDB) = 0;

	// Determines whether OPP is enabled in the specified view.
	virtual bool32 IsOPPEnabledInView(IControlView* iView) = 0;

	enum
	{
		// If not set, honors spread overrides.
		kXPCF_IgnoreSpreadOverrides					= (1L<<0),	
		
		// If not set, we'll tell the flattener to set up doc spots in
		// legacy and simPress modes.
		kXPCF_NoSpotSetup							= (1L<<1),	
		
		// Forces flattener to rasterize bad boy paints.
		kXPCF_RasterizeAGMPrintIncompatiblePaints	= (1L<<2),

		// Don't use page's doc for inklist, use active book's inklist.
		kXPCF_UseActiveBookInkList					= (1L<<3)
	};
	
	// CreateFlattener: This utility creates a flattening port using a flattening style
	// and applying any spread overrides (depending on 'kXPCF_IgnoreSpreadOverrides').  The
	// output mode determines whether spots will be added to the flattening port and
	// how various flags get set up.  If you need to know what the final settings were
	// you can pass a FlattenSettings object and this fn will fill it in for you.
	// NOTE: This method will return an invalid (nil) port if an error occurs OR if
	// the spread override says not to enable the flattener.
	virtual AGMPort* CreateFlattener(
			UIDRef pageRef,		// The page or spread you're exporting
			UID flatStyleUID,	// The UID of the global flattening style
			uint32 xpcfFlags,	// kXPCF_*
			IXPUtils::FlattenOutputMode mode,	// Determines spot and flag setup
			const PMRect& pgBounds,	// The drawing bounds
			IXPUtils::FlattenSettings* returnSettings = nil,
			void* pAGMFlattenerSettings = nil,
			AGMColorSpace* preferredBlendSpace = nil) = 0;

	// This is used to release the blend space optionally returned from CreateFlattener().
	virtual void ReleaseBlendSpace(AGMColorSpace* theBlendSpace) = 0;

	// This is used to obtain a suitable output profile to eliminate stitching
	// artifacts caused by a different blend and device  (and proofing, and
	// overprint simulation) profiles.  Pass in your profiles, and this will
	// return an appropriate new device profile to match the planar map vs non
	// planar mapped object path.  Note that you need to release the profile
	// via the appropriate BIB dereferencer or ReleaseProfile, below.
	virtual AGMColorProfile* CreateAntistitchingProfile
		(
			AGMColorProfile* profBlend,			// required; if not flattening, then don't call this function
			AGMColorProfile* profDevice,		// required
			AGMColorProfile* profCMYK = nil,	// nil = not doing overprint preview
			AGMColorProfile* profProof = nil	// nil = not proofing anything
		) = 0;

	virtual void ReleaseProfile(AGMColorProfile*) = 0;

	/**
	 * Retrieves the specified global flattener style definition.
	 */

	virtual IFlattenerSettings* QueryFlattenerSettings( IWorkspace* pWorkspace,
		                                                UID         uidFlatStyle ) = 0;

	/**
	 * Utility for retrieving the flattener settings for the specified workspace, and the override
	 * settings for the specified page item if applicable.
	 */

	virtual bool16 GetFlattenerSettings( IWorkspace* pWorkspace,
		                                 UID         uidFlatStyle,
										 bool16      bIgnoreSpreadOverrides,
		                                 UIDRef&     uidPageItem,
										 InterfacePtr<IFlattenerSettings>& pSettings,
										 InterfacePtr<IFlattenerSettings>& pOverrides ) = 0;

	/**
	 * Initializes the flattener output resolution appropriately for the specified view port.
	 */

	virtual bool16 SetupViewPortAttrs( IWorkspace*   pWorkspace,
		                               UID           uidFlatStyle, 
									   bool32        bIgnoreOverrides, 
									   UIDRef const& uidPage, 
									   IViewPortAttributes* iAttr) = 0;

	/**
	*	Obtains a paint server from an image.  Useful for creating alpha Servers.
	*
	*	@param imgRec IN	The image you want to turn into a paint server.  NOTE: This method
	*						makes a copy of the image data, so you can dispose your buffers
	*						if you want immediately following this call.
	*	@param m IN			The matrix that is attached to the paint server.
	*	@param flags IN		Image flags; not currently documented.  Set to 0 for now.
	*	@param theSpace IN	The colorspace for the image.  If you pass nil for this argument
	*						your paint server will be uncalibrated.
	*
	*	@return A refcounted AGMPaint object that can be passed to IGraphicsPort::SetPaintServer
	*				-- or, more interestingly, IGraphicsPort::SetAlphaServer.  Note that you must
	*				release your paint server via ReleasePaintServer once you're done with it.
	*				Which is normally after you've SetAlphaServer or SetPaintServer'd it.
	*/
	virtual AGMPaint* CreateImagePaintServer(	_t_AGMImageRecord* imgRec, 
												PMMatrix* m, 
												int32 flags, 
												AGMColorSpace* theSpace) = 0;

	/**
	*	Releases a paint server created via CreateImagePaint.
	*
	*	@param agmPaint IN The paint server you want to release.
	*/
	virtual void ReleasePaintServer(AGMPaint* agmPaint) = 0;

	/**
	*	Obtains a list of all placed graphics in the specified spread that are affected by 
	*	transparency.  Useful for when you want to do automated OPI swapping.  The 'styleName'
	*	and 'ignoreSpreadOverrides' allow you to match conditions used in a given export or
	*	print scenario, or the flattener preview itself.
	*
	*	NOTE: This can be an expensive operation if the spread contains a lot of objects.
	*
	*	@param spreadRef				IN	The spread you want to inspect.
	*	@param styleName				IN	The name of the flattener style to use.  If empty string, will use High Quality style.
	*	@param ignoreSpreadOverrides	IN	Whether to ignore spread overrides.
	*	@return				A newly allocated UIDList containing the images on the spread
	*						that are affected by transparency.  Returns NIL (rather than
	*						an empty list) if there are none.  Caller must delete this ptr.
	*/
	virtual UIDList* GetGraphicsAffectedByTransparency(UIDRef spreadRef, const PMString& styleName = PMString(), bool32 ignoreSpreadOverrides = kFalse) = 0;

	/** Examines the attributes on the given page item for the presence of any that would
		make the stroke transparent and thus reveal the fill beneath it.  This is important
		for retarding the fill path adjustment that occurs for solid strokes.  
		
		In particular the method returns true if the stroke is less than 100% opaque; has
		a blend mode other than normal; or has a feather (of any flavor) applied.  This 
		criteria may be adjusted in the future based on feature additions/changes.

		@param item		IN An interface pointer identifying the object (page item).
		@return True if the stroke attributes make the stroke transparent.
	*/

	virtual bool32 IsStrokeTransparent(IPMUnknown* item) = 0;
};


#endif	// __IXPUtils__
