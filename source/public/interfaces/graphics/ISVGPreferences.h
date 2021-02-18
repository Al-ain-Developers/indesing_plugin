//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ISVGPreferences.h $
//  
//  Owner: Nitin Kumar
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2019 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//  
//  Purpose:
//  Stores the current SVG import preferences. These preferences should
//  be set using the kSetSVGPrefsCmdBoss command.	
//  
//========================================================================================

#pragma once
#ifndef __ISVGPreferences__
#define __ISVGPreferences__

#include "IPMUnknown.h"
#include "PMReal.h"

/** SVG Import Preferences - settings used when the SVG was imported.
	Use the kSetSVGPrefsCmdBoss command to set SVG import preferences!
*/
class ISVGPreferences : public IPMUnknown
{
public:	
	/** Used for SVG import settings
	*/
	enum 
	{
		/** Don't Change current setting - can be used for any setting
		*/
		kDontChange = 0,

		/** Import SVG as whole - only supported mode
		*/
		kImportWhole,
		/** Import SVG as pieces - not supported for file placement, 
			only through clipboard
		*/
		kImportPieces,

		/** Add process colors - currently unsupported - don't use
		*/
		kAddProcessColors,
		/** Don't add process colors - currently unsupported - don't use
		*/
		kDontAddProcessColors,

		/** Import nested DCS - currently unsupported - don't use
		*/
		kImportNestedDCS,
		/** Don't import nested DCS - currently unsupported - don't use
		*/
		kDontImportNestedDCS,

		/** Read embedded OPI comments - required to be on to perform OPI
			replacement during output
		*/
		kReadOPIComments,
		/** Don't read embedded OPI comments
		*/
		kDontReadOPIComments,

		/** Create frame from clipping path, if SVG contains Photoshop clipping path
		*/
		kCreateFrameFromClipPath,
		/** Don't create frame from clipping path
		*/
		kDontCreateFrameFromClipPath,

		/** Never create proxy
		*/
		kNeverCreate,
		/** Create proxy if needed (i.e. SVG doesn't have TIFF or PICT preview)
		*/
		kCreateIfNeeded,
		/** Always create proxy from SVG
		*/
		kAlwaysCreate
	};

	/**	Set import preference for whole vs. pieces
		@param importPref IN kImportWhole or kImportPieces
	 */
	virtual void SetImportPref(const int32 importPref) = 0;

	/**	Set create frame from clipping path
		@param createFrame IN kCreateFrameFromClipPath or kDontCreateFrameFromClipPath
	 */
	virtual void SetCreateFrame(const int32 createFrame) = 0;

	/**	Set create proxy mode
		@param createProxy IN kNeverCreate or kCreateIfNeeded or kAlwaysCreate
	 */
	virtual void SetCreateProxy(const int32 createProxy) = 0;
	
	/**	Get import preference for whole vs. pieces
		@return int32 - kImportWhole or kImportPieces
	 */
	virtual int32 GetImportPref() const = 0;

	/**	Get create frame from clipping path
		@return int32 - kCreateFrameFromClipPath or kDontCreateFrameFromClipPath
	 */
	virtual int32 GetCreateFrame() const = 0;

	/**	Get create proxy mode
		@return int32 - kNeverCreate or kCreateIfNeeded or kAlwaysCreate
	 */
	virtual int32 GetCreateProxy() const = 0;
	
};

#endif
