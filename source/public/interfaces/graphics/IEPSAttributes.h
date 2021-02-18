//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IEPSAttributes.h $
//  
//  Owner: David Berggren
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
//  Purpose:
//  Stores info about an EPS page item.
//  
//========================================================================================

#pragma once
#ifndef __IEPSAttributes__
#define __IEPSAttributes__

#include "IPMUnknown.h"
#include "PMRect.h"
#include "UIDList.h"
#include "K2Vector.h"
#include "EPSID.h"

/** EPSPSFlags mirrors MPSPSFlags defined in MPS headers.
*/
typedef uint32 EPSPSFlags;
enum {
	EPSFlagsIsPostScript		= 1 << 0,
	EPSFlagsIsEPS				= 1 << 1,
	EPSFlagsIsAI				= 1 << 2,
	EPSFlagsIsDSCCompliant		= 1 << 3,
	EPSFlagsHasComments			= 1 << 4,
	EPSFlagsHasBoundingBox		= 1 << 5,
	EPSFlagsHasColor			= 1 << 6,
	EPSFlagsNeedsProcSets		= 1 << 7,
	EPSFlagsIsDCSCompliant		= 1 << 8,

	// Non-MPSPSFlags
	EPSFlagsGeneratingPreview	= 1 << 15,		// We are generating a thumbnail preview for the place dialog
	EPSFlagsIsPhotoshopRaster	= 1 << 16,		// We have a raster based Photoshop EPS
	EPSFlagsTestedForRaster		= 1 << 17		// If 0, then EPSFlagsIsPhotoshopRaster == 0 does not
												// necessarily mean we do not have a raster.
};

/** Primarily this interface holds the settings that were used when the EPS was imported. These settings
	are reused when the link is updated.
*/
class IEPSAttributes : public IPMUnknown
{
public:
	/* Default IID to be used by UseDefaultIID() */
	enum { kDefaultIID = IID_IEPSATTRIBUTES };

	/** drawing options for the EPS
	*/
	typedef enum 
	{
		/** draw as normal
		*/
		kDrawEPSNormal,
		/** draw as gray box
		*/
		kDrawEPSGrayBox,
		/** draw EPS proxy
		*/
		kDrawEPSProxy,
		/** draw EPS display list
		*/
		kDrawEPSDispList
	} DrawEPSOption;

	/**	Set the bounding box.
		@param bbox IN the bounding box of the EPS
	 */
	virtual void SetBoundingBox (const PMRect& bbox) = 0;
	/**	Set the target display resolution.
		@param targetRes IN the target display resolution
	 */
	virtual void SetTargetRes (const PMReal& targetRes) = 0;
	/**	Set add process colors - currently unsupported don't use.
		@param bAddProColor IN whether to add the process colors
	 */
	virtual void SetAddProcessColors(const bool16 bAddProColor) = 0;
	/**	Set import nested DCS - currently unsupported don't use.
		@param bImportDCS IN whether to import the nested DCS
	 */
	virtual void SetImportDCS(const bool16 bImportDCS) = 0;
	/**	Set whether to read nested OPI comments.
		@param bReadOPI IN kTrue to read OPI comments in EPS, kFalse otherwise
	 */
	virtual void SetReadOPI(const bool16 bReadOPI) = 0;
	/**	Set whether to create frame from clipping path.
		@param bCreateFrame IN kTrue to create frame from clipping path, kFalse otherwise
	 */
	virtual void SetCreateFrame(const bool16 bCreateFrame) = 0;
	/**	Set the information about the EPS - see EPSPSFlags enum in this header file for more information.
		@param flags IN the EPSPSFlags settings
	 */
	virtual void SetEPSFlags (const EPSPSFlags flags) = 0;
	/**	Set the EPS draw option - see DrawEPSOption enum in this header file for more information.
		@param drawOption IN the draw option to use
	 */
	virtual void SetDrawEPSOption(DrawEPSOption drawOption) = 0;
	/**	Get the bounding box.
		@return PMRect of the bounding box of the EPS
	 */
	virtual PMRect GetBoundingBox () const = 0;
	/**	Get the target display resolution.
		@return PMReal of the target display resolution
	 */
	virtual PMReal GetTargetRes () const = 0;
	/**	Get add process colors - currently unsupported don't use.
		@return bool16 kTrue if adding the process colors, kFalse otherwise
	 */
	virtual bool16 GetAddProcessColors() const = 0;
	/**	Get import nested DCS - currently unsupported don't use.
		@return bool16 kTrue if importing the nested DCS, kFalse otherwise
	 */
	virtual bool16 GetImportDCS() const = 0;
	/**	Get whether to read nested OPI comments.
		@return bool16 kTrue if reading OPI comments in EPS, kFalse otherwise
	 */
	virtual bool16 GetReadOPI() const = 0;
	/**	Get whether to create frame from clipping path.
		@return bool16 kTrue if creating frame from clipping path, kFalse otherwise
	 */
	virtual bool16 GetCreateFrame() const = 0;
	/**	Get the EPSFlags about the EPS - see EPSPSFlags enum in this header file for more information.
		@return EPSPSFlags settings
	 */
	virtual EPSPSFlags GetEPSFlags () const = 0;
	/**	Get the EPS draw option - see DrawEPSOption enum in this header file for more information.
		@return DrawEPSOption draw option to use
	 */
	virtual DrawEPSOption GetDrawEPSOption() const = 0;

	/** The following 4 methods are used to manage the color swatches used by the EPS.
		Create/Append methods are only used during import.
		The two Get methods are to get the used color UID list and to
		get the name of the color originally imported. If the returned UIDList is nil,
		then there aren't any color used in the EPS.
	*/

	/**	Creates a UIDList of color swatches used by the EPS. The existing list,
		if any, is deleted and a new list is created. If a valid list is 
		passed in, the new list contains it as its single entry; otherwise, the
		new list is empty.
	 
		@param pUIDList		IN Swatch UID list to create, or nil if the list is to be created empty
		@return the newly created UIDList used to store color swatch UIDs for this EPS
	 */
	virtual const UIDList* CreateUsedColorUIDList(const UIDList* pUIDList) = 0;

	/**	Append a color swatch UID to the colors used list on the EPS
		@param colorUID the UID of the swatch color to append
	 */
	virtual void		AppendToUsedColorUIDList (const UID colorUID) = 0;
	
	/**	Gets the existing UIDList of color swatches used by this EPS. If the list
		does not exist, nil is returned.
		@return the existing UIDList used to store color swatch UIDs for this EPS
	 */
	virtual const UIDList* GetUsedColorUIDList() const = 0;

	/**	Replace a used color UID with a new used color UID - this API is not supported - don't use
		@param UID the from color UID
		@param UID the to color UID
	 */
	virtual void		ReplaceUsedColorUID (const UID, const UID) = 0;

	/**	Get the list of color names originally imported. Pointer may be nil if no colors imported.
		Caller needs to call delete on the returned string list.
		@return K2Vector<PMString>* pointer to a vector of original color names.
	 */
	virtual K2Vector<PMString>*	GetEPSOriginalyImportedColorNameList () = 0;

	/** Given the original color name, return the current swatch name mapped to this swatch.
		In none of the color used were merged, then the name returned should be the same as the name given.
		@param PMString& the original color name
		@return PMString current swatch name mapped to this swatch
	 */
	virtual PMString	GetEPSColorName (const PMString&) = 0;
};

#endif
