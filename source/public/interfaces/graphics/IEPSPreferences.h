//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IEPSPreferences.h $
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
//  Stores the current EPS import preferences. These preferences should
//  be set using the kSetEPSPrefsCmdBoss command.	
//  
//========================================================================================

#pragma once
#ifndef __IEPSPreferences__
#define __IEPSPreferences__

#include "IPMUnknown.h"
#include "PMReal.h"

/** EPS Import Preferences - settings used when the EPS was imported.
	Use the kSetEPSPrefsCmdBoss command to set EPS import prefs!
*/
class IEPSPreferences : public IPMUnknown
{
public:	
	/** Used for EPS import settings
	*/
	enum 
	{
		/** Don't Change current setting - can be used for any setting
		*/
		kDontChange = 0,

		/** Import EPS as whole - only supported mode
		*/
		kImportWhole,
		/** Import EPS as pieces - not supported for file placement, 
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

		/** Create frame from clipping path, if EPS contains Photoshop clipping path
		*/
		kCreateFrameFromClipPath,
		/** Don't create frame from clipping path
		*/
		kDontCreateFrameFromClipPath,

		/** Never create proxy
		*/
		kNeverCreate,
		/** Create proxy if needed (i.e. EPS doesn't have TIFF or PICT preview)
		*/
		kCreateIfNeeded,
		/** Always create proxy from EPS
		*/
		kAlwaysCreate
	};

	/**	Set import preference for whole vs. pieces
		@param importPref IN kImportWhole or kImportPieces
	 */
	virtual void SetImportPref(const int32 importPref) = 0;

	/**	Set add process colors - currently unsupported - don't use
		@param addProColor IN kAddProcessColors or kDontAddProcessColors
	 */
	virtual void SetAddProcessColors(const int32 addProColor) = 0;

	/**	Set import nested DCS - currently unsupported - don't use
		@param importDCS IN kImportNestedDCS or kDontImportNestedDCS
	 */
	virtual void SetImportDCS(const int32 importDCS) = 0;

	/**	Set read nested OPI comments
		@param readOPI IN kReadOPIComments or kDontReadOPIComments
	 */
	virtual void SetReadOPI(const int32 readOPI) = 0;

	/**	Set create frame from clipping path
		@param createFrame IN kCreateFrameFromClipPath or kDontCreateFrameFromClipPath
	 */
	virtual void SetCreateFrame(const int32 createFrame) = 0;

	/**	Set display resolution
		@param displayRes IN value for the display resolution
	 */
	virtual void SetDisplayRes(const PMReal& displayRes) = 0;

	/**	Set create proxy mode
		@param createProxy IN kNeverCreate or kCreateIfNeeded or kAlwaysCreate
	 */
	virtual void SetCreateProxy(const int32 createProxy) = 0;
	
	/**	Get import preference for whole vs. pieces
		@return int32 - kImportWhole or kImportPieces
	 */
	virtual int32 GetImportPref() const = 0;

	/**	Get add process colors - currently unsupported - don't use
		@return int32 - kAddProcessColors or kDontAddProcessColors
	 */
	virtual int32 GetAddProcessColors() const = 0;

	/**	Get import nested DCS - currently unsupported - don't use
		@return int32 - kImportNestedDCS or kDontImportNestedDCS
	 */
	virtual int32 GetImportDCS() const = 0;

	/**	Get read nested OPI comments
		@return int32 - kReadOPIComments or kDontReadOPIComments
	 */
	virtual int32 GetReadOPI() const = 0;

	/**	Get create frame from clipping path
		@return int32 - kCreateFrameFromClipPath or kDontCreateFrameFromClipPath
	 */
	virtual int32 GetCreateFrame() const = 0;

	/**	Get display resolution
		@return PMReal - value for the display resolution
	 */
	virtual PMReal GetDisplayRes() const = 0;

	/**	Get create proxy mode
		@return int32 - kNeverCreate or kCreateIfNeeded or kAlwaysCreate
	 */
	virtual int32 GetCreateProxy() const = 0;
	
};

#endif
