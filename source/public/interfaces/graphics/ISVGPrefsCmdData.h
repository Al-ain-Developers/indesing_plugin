//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ISVGPrefsCmdData.h $
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
//  Command data for setting the SVG import preferences. Used for
//  the kSetSVGPrefsCmdBoss command.	
//  
//========================================================================================

#pragma once
#ifndef __ISVGPrefsCmdData__
#define __ISVGPrefsCmdData__

#include "IPMUnknown.h"
#include "ISVGPreferences.h"

/** Command data interface to set ISVGPreferences values.
*/
class ISVGPrefsCmdData : public IPMUnknown
{
public:
	/**	All inclusive Set method. The SVG import preference values are defined 
		in ISVGPreferences.h. Use ISVGPreferences::kDontChange to prevent the mode from changing.

		@param importSVGmode IN import preference for whole vs. pieces
		@param importSVGCreateFrame IN create frame from clipping path
		@param importSVGCreateProxy IN create proxy mode
	 */
	virtual void Set(const int32 importSVGmode = ISVGPreferences::kDontChange,
						const int32 importSVGCreateFrame = ISVGPreferences::kDontChange,
						const int32 importSVGCreateProxy = ISVGPreferences::kDontChange) = 0;

	/**	Copy the values from the passed in interface copyPref.
		@param copyPref IN the ISVGPrefences interface to copy from
	 */
	virtual void CopyPrefs(ISVGPreferences * copyPref) = 0;

	/**	Set import preference for whole vs pieces.
		@param importPref IN kImportWhole or kImportPieces
	 */
	virtual void SetImportSVGMode(const int32 importSVGmode) = 0;

	/**	Set create frame from clipping path.
		@param createFrame IN kCreateFrameFromClipPath or kDontCreateFrameFromClipPath
	 */
	virtual void SetImportSVGCreateFrame(const int32 createFrame) = 0;

	/**	Set create proxy mode.
		@param createProxy IN kNeverCreate or kCreateIfNeeded or kAlwaysCreate
	 */
	virtual void SetImportSVGCreateProxy(const int32 createProxy) = 0;

	/**	Get import preference for whole vs pieces.
		@return int32 - kImportWhole or kImportPieces
	 */
	virtual int32 GetImportSVGMode(void) const = 0;

	/**	Get create frame from clipping path.
		@return int32 - kCreateFrameFromClipPath or kDontCreateFrameFromClipPath
	 */
	virtual int32 GetImportSVGCreateFrame(void) const = 0;

	/**	Get create proxy mode.
		@return int32 - kNeverCreate or kCreateIfNeeded or kAlwaysCreate
	 */
	virtual int32 GetImportSVGCreateProxy(void) const = 0;

};

#endif
