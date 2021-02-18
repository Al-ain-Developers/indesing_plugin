//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPDFAttributes.h $
//  
//  Owner: Michael Jordan
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
#ifndef __IPDFAttributes__
#define __IPDFAttributes__

#include "IPMUnknown.h"
#include "PMRect.h"
#include "UIDList.h"
#include "BravoForwardDecl.h"
#include "PDFID.h"

class IPMStream;

#define IDMAXENUM 0x40000000

// Flags to track whether page level transparency
// attributes need to be overriden.
typedef uint32 XPOverrideFlags;
enum {
	/** Override the page level blending space with one specified */
	kXPOverrideBlendSpace			= 1<<0,
	/** Override the page level isolation */
	kXPOverrideIsolate			= 1<<1,
	/** Override the page level knockout */
	kXPOverrideKnockout	= 1<<2,

	_MAX_XPOverrideOptions = IDMAXENUM  /* force 32 bit enum */
};

/**
 The IPDFAttributes interface stores information about a placed PDF file.
 */
class IPDFAttributes : public IPMUnknown
{
public:
	/* Default IID to be used by UseDefaultIID() */
	enum { kDefaultIID = IID_IPDFATTRIBUTES };

	enum {
		kDeviceBlendingNone = 0,
		kDeviceBlendingCMYK,
		kDeviceBlendingRGB,
		kDeviceBlendingGray,
	 
	 	// TODO: Obsolete these for InDesign 3.0
		kExportAuto = 0,
		kExportDL,
		kExportForm,

		// Process colors used in PDF
		kCyanUsed				= 0x01,
		kMagentaUsed			= 0x02,
		kYellowUsed				= 0x04,
		kBlackUsed				= 0x08,
		kAllProcessColorsUsed	= 0x0F
	};

	/**
	 Returns the index number of currently referenced page
	 */
	virtual uint32 GetPageIndex() const = 0;
	
	/**
	 Sets the index number of the currently referenced page.
	 
	 @param pageIndex		IN The page number of currently referenced page
	 */
	virtual void SetPageIndex(uint32 pageIndex) = 0;

	/**
	 Returns the background transparency for this PDF item.
	 */
	virtual bool16 GetTransparentBackground() const = 0;

	/**
	 Sets the background transparency for this PDF item.
	 
	 @param fTransparent	IN Flag indicating whether background is transparent
	 */
	virtual void SetTransparentBackground(bool16 fTransparent) = 0;

	/**
	 Returns the "preserve halftone screens" setting for this PDF item.
	 */
	virtual bool16 GetPreserveScreens() const = 0;

	/**
	 Sets the "preserve halftone screens" setting for this PDF item.
	 
	 @param fPreserve		IN Flag indicating whether to preserve halftone screens
	 */
	virtual void SetPreserveScreens(bool16 fPreserve) = 0;

	/**
	 Internal use only. Intentionally undocumented.
	 */
	virtual void SetUserEnteredPassword(bool16 enteredPassword) = 0;
	
	/**
	 Internal use only. Intentionally undocumented.
	 */
	virtual bool16 GetUserEnteredPassword() const = 0;
	
	/**
	 Creates a UIDList of color swatches used by the PDF. The existing list,
	 if any, is deleted and a new list is created. If a valid list is 
	 passed in, the new list contains it as its single entry; otherwise, the
	 new list is empty.
	 
	 @param pUIDList		IN Swatch UID list to create, or nil if the list is to be created empty
	 @return the newly created UIDList used to store color swatch UIDs for this PDF
	 */
	virtual const UIDList* CreateUsedColorUIDList(const UIDList* pUIDList) = 0;
	
	/**
	 Gets the existing UIDList of color swatches used by this PDF. If the list
	 does not exist, nil is returned.
	 
	 @return the existing UIDList used to store color swatch UIDs for this PDF
	 */
	virtual const UIDList* GetUsedColorUIDList() const = 0;

	/**
	 Gets the "crop to" setting for this PDF. 
	 
	 @return the current crop to setting to use for this PDF
	 @see IPDFPlacePrefs for the list of acceptable values
	 */
	virtual uint32 GetCropTo() const = 0;
	
	/**
	 Sets the "crop to" setting for this PDF.
	 
	 @param cropTo			IN The new crop to setting to use for this PDF
	 @see IPDFPlacePrefs for the list of acceptable values
	 */
	virtual void SetCropTo(uint32 cropTo) = 0;

	/**
	 Returns kTrue if this PDF contains transparency, else kFalse
	 */
	virtual bool16 GetContainsTransparency() const = 0;
	
	/**
	 Sets whether this PDF contains transparency.
	 
	 @param containsXP		IN The new value for whether this PDF contains transparency
	 */
	virtual void SetContainsTransparency( bool16 containsXP ) = 0;
	
	/**
	 Returns kTrue if this PDF contains OPI references, else kFalse
	 */
	virtual bool16 GetContainsOPIReferences() const = 0;
	
	/**
	 Sets whether this PDF contains OPI references
	 
	 @param containsOPI		IN The new value for whether this PDF contains OPI references
	 */
	virtual void SetContainsOPIReferences( bool16 containsOPI ) = 0;
	
	/**
	 Returns kTrue if this PDF contains overprint, else kFalse
	 */
	virtual bool16 GetContainsOverprint() const = 0;
	
	/**
	 Sets whether this PDF contains overprint.
	 
	 @param opd				IN The new value for whether this PDF contains overprint
	 */
	virtual void SetContainsOverprint(bool16 opd) = 0;

	/**
	 Returns kTrue if this PDF contains non-ink-preserving blend modes, else kFalse
	 */
	virtual bool16 GetContainsNIPBlendingModes() const = 0;
	
	/**
	 Sets whether this PDF contains non-ink-preserving blend modes.
	 
	 @param nips			IN The new value for whether this PDF contains non-ink-preserving blend modes
	 */
	virtual void SetContainsNIPBlendingModes(bool16 nips) = 0;

	/**
	 Returns kTrue if this PDF was previously flattened, else kFalse
	 */
	virtual bool16 GetXPPreviouslyFlattened() const = 0;
	
	/**
	 Sets whether this PDF was previously flattened.
	 
	 @param flat			IN The new value for whether this PDF was previously flattened
	 */
	virtual void SetXPPreviouslyFlattened(bool16 flat) = 0;
	
	/**
	 Returns kTrue if this PDF has page-level blending, else kFalse
	 */
	virtual bool16 HasPageBlending() const = 0;

	/**
	 Gets blending color space for this PDF. 
	 
	 Note: necessarily unusable by third-party developers due to use of internal 
	 type CAGMColorSpace
	 
	 @param isOverride		OUT If non-nil, set to kTrue if color space is an override, else kFalse
	 @return the blending color space for this PDF. 
	 */
	virtual CAGMColorSpace GetBlendingColorSpace(bool16 *isOverride = nil) = 0;
	
	/**
	 Sets the blending color space for this PDF.
	 
	 Note: necessarily unusable by third-party developers due to use of internal 
	 type CAGMColorSpace
	 
	 @param cs				IN The new blending color space
	 @param isOverride		IN The new is-override flag
	 */
	virtual void SetBlendingColorSpace(CAGMColorSpace cs, bool16 isOverride) = 0;

	/**
	 @param isOverride		OUT If non-nil, set to kTrue if page isolation setting is an override, else kFalse
	 @return kTrue if this PDF uses page isolation, else kFalse
	 */
	virtual bool16 GetPageIsolation(bool16 *isOverride = nil) const = 0;
	
	/**
	 Sets page isolation setting for this PDF.
	 
	 @param isolate			IN The new uses page isolation setting
	 @param isOverride		IN kTrue if setting is an override, else kFalse
	 */
	virtual void SetPageIsolation(bool16 isolate, bool16 isOverride) = 0;

	/**
	 @param isOverride		OUT If non-nil, set to kTrue if page knockout setting is an override, else kFalse
	 @return kTrue if this PDF uses page knockout, else kFalse
	 */
	virtual bool16 GetPageKnockout(bool16 *isOverride = nil) const = 0;

	/**
	 Sets page knockout setting for this PDF.
	 
	 @param knockout		IN The new uses page knockout setting
	 @param isOverride		IN kTrue if setting is an override, else kFalse
	 */
	virtual void SetPageKnockout(bool16 knockout, bool16 isOverride) = 0;

	/**
	 Set the user's choice for whether to allow color aliasing.
	 
	 @param apply			IN The new apply color aliases setting
	 */
	virtual void SetApplyColorAliases(bool16 apply) = 0;
	
	/**
	 Returns kTrue if the user chose to allow color aliasing, else kFalse
	 */
	virtual bool16 GetApplyColorAliases() const = 0;

	/**
	 Note: This API will be obsoleted in a future version. Do not use.
	 
	 @return the export strategy for this PDF file
	 */
	virtual int32 GetExportStrategy() const = 0;
	
	/**
	 Note: This API will be obsoleted in a future version. Do not use.

	 Sets the export strategy for this PDF.
	 
	 @param strategy		IN The new export strategy
	 */
	virtual void SetExportStrategy(int32 strategy) = 0;

	/**
	 Returns kTrue if page item was pasted from the system clipboard, else kFalse
	 */
	virtual bool16 IsFromClipboard() const = 0;
	
	/**
	 Sets whether this page item was pasted from system clipboard.
	 
	 @param fromClipboard	IN The new is from clipboard setting
	 */
	virtual void SetFromClipboard(bool16 fromClipboard) = 0;

	/**
	 Calculate whether this PDF has transparency.

	 Note: This method will do a fairly expensive calculation to determine if the
	 associated PDF has transparency or not.  In general, it should not be used.
	 Instead, IPDFAttributes.GetContainsTransparency should be used.  We use it
	 during document conversion, because in that case the value returned by
	 GetHasTransparency flag is not set correctly, since 1.5 docs didn't support
	 transparency.  After the 1.5 document is converted, however, everything 
	 should be fine.
	 
	 @param bTransparency	OUT Set to kTrue if PDF has transparency, else kFalse
	 @return kSuccess if method succeeds, else kFailure
     */
	virtual int32 CalculateHasTransparency( bool16& bTransparency ) = 0;

	/**
	 Returns kTrue if PDF contains one or more gradients, else kFalse
	 */
	virtual bool16 GetHasGradient() const = 0;
	
	/**
	 Sets whether PDF contains one or more gradients.
	 
	 @param hasGradient		IN The new value for has gradient setting
	 */
	virtual void SetHasGradient(bool16 hasGradient) = 0;

	/**
	 Returns kTrue if PDF contains one or more gradient meshes, else kFalse
	 */
	virtual bool16 GetHasGradientMesh() const = 0;

	/**
	 Sets whether PDF contains one or more gradient meshes.
	 
	 @param hasGradientMesh	IN The new value for has gradient mesh setting
	 */
	virtual void SetHasGradientMesh(bool16 hasGradientMesh) = 0;

	/**
	 Internal use only. Intentionally undocumented.
	 */
	virtual int32 GetExpectedPDFLibCancelCallbackCount() const = 0;

	/**
	 Internal use only. Intentionally undocumented.
	 */
	virtual void SetExpectedPDFLibCancelCallbackCount(int32 n) = 0;

	/**
	 Gets whether the PDF has been trapped. This is determined by reading the 
	 /Trapped key in the PDF.
	 
	 @return kTrue if the PDF was trapped, else kFalse
	 */
	virtual bool16 GetIsTrapped() const = 0;
	
	/**
	 Sets whether PDF was trapped. Should be based on whether /Trapped key in 
	 the PDF is set to true.
	 
	 @param bIsTrapped		IN The new is trapped setting
	 */
	virtual void SetIsTrapped(bool16 bIsTrapped) = 0;

	/**
	 Gets which process colors are used in the PDF. Return value is a bitfield
	 and will consist of a combination of one or more of the following values:
	 kCyanUsed, kMagentaUsed, kYellowUsed, or kBlackUsed, or it may be the 
	 special value kAllProcessColorsUsed.

	 @return bitfield indicating which process colors are used
	 */
	virtual uint32 GetProcessColorsUsed() const = 0;
	
	/**
	 Sets which process colors are used in the PDF. Input is a bitfield and 
	 should consist of a combination of one or more of the following values:
	 kCyanUsed, kMagentaUsed, kYellowUsed, or kBlackUsed, or it may be the 
	 special value kAllProcessColorsUsed.

	 @param processColorsUsed	IN Bitfield indicating which process colors are used
	 */
	virtual void SetProcessColorsUsed(uint32 processColorsUsed) = 0;
};

#endif // __IPDFAttributes__
