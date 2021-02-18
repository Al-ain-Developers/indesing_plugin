//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IEPSPrefsCmdData.h $
//  
//  Owner: DBerggren
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
//  Command data for setting the EPS import preferences. Used for
//  the kSetEPSPrefsCmdBoss command.	
//  
//========================================================================================

#pragma once
#ifndef __IEPSPrefsCmdData__
#define __IEPSPrefsCmdData__

#include "IPMUnknown.h"
#include "IEPSPreferences.h"

/** Command data interface to set IEPSPreferences values.
*/
class IEPSPrefsCmdData : public IPMUnknown
{
public:
	/**	All inclusive Set method. The EPS import preference values are defined 
		in IEPSPreferences.h. Use IEPSPreferences::kDontChange to prevent the mode from changing.

		@param importEPSmode IN import preference for whole vs. pieces
		@param importEPSAddProColor IN add process colors - currently unsupported - don't use
		@param importEPSImportDCS IN import nested DCS - currently unsupported - don't use
		@param importEPSReadOPI IN read nested OPI comments
		@param importEPSCreateFrame IN create frame from clipping path
		@param importEPSDisplayRes IN display resolution
		@param importEPSCreateProxy IN create proxy mode
	 */
	virtual void Set(	const int32 importEPSmode = IEPSPreferences::kDontChange, 
						const int32 importEPSAddProColor = IEPSPreferences::kDontChange,
						const int32 importEPSImportDCS = IEPSPreferences::kDontChange,
						const int32 importEPSReadOPI = IEPSPreferences::kDontChange,
						const int32 importEPSCreateFrame = IEPSPreferences::kDontChange,
						const PMReal& importEPSDisplayRes = IEPSPreferences::kDontChange,
						const int32 importEPSCreateProxy = IEPSPreferences::kDontChange) = 0;

	/**	Copy the values from the passed in interface copyPref.
		@param copyPref IN the IEPSPrefences interface to copy from
	 */
	virtual void CopyPrefs(IEPSPreferences * copyPref)=0;

	/**	Set import preference for whole vs pieces.
		@param importPref IN kImportWhole or kImportPieces
	 */
	virtual void SetImportEPSMode(const int32 importEPSmode) = 0; 

	/**	Set add process colors - currently unsupported - don't use.
		@param addProColor IN kAddProcessColors or kDontAddProcessColors
	 */
	virtual void SetImportEPSAddProColor(const int32 importEPSAddProColor) = 0; 

	/**	Set import nested DCS - currently unsupported - don't use.
		@param importDCS IN kImportNestedDCS or kDontImportNestedDCS
	 */
	virtual void SetImportEPSImportDCS(const int32 importEPSImportDCS) = 0; 

	/**	Set read nested OPI comments.
		@param readOPI IN kReadOPIComments or kDontReadOPIComments
	 */
	virtual void SetImportEPSReadOPI(const int32 importEPSReadOPI) = 0; 

	/**	Set create frame from clipping path.
		@param createFrame IN kCreateFrameFromClipPath or kDontCreateFrameFromClipPath
	 */
	virtual void SetImportEPSCreateFrame(const int32 createFrame) = 0; 

	/**	Set display resolution.
		@param displayRes IN value for the display resolution
	 */
	virtual void SetImportEPSDisplayRes(const PMReal& displayRes) = 0;

	/**	Set create proxy mode.
		@param createProxy IN kNeverCreate or kCreateIfNeeded or kAlwaysCreate
	 */
	virtual void SetImportEPSCreateProxy(const int32 createProxy) = 0;

	/**	Get import preference for whole vs pieces.
		@return int32 - kImportWhole or kImportPieces
	 */
	virtual int32 GetImportEPSMode(void) const = 0;

	/**	Get add process colors - currently unsupported - don't use.
		@return int32 - kAddProcessColors or kDontAddProcessColors
	 */
	virtual int32 GetImportEPSAddProColor(void) const = 0;

	/**	Get import nested DCS - currently unsupported - don't use.
		@return int32 - kImportNestedDCS or kDontImportNestedDCS
	 */
	virtual int32 GetImportEPSImportDCS(void) const = 0;

	/**	Get read nested OPI comments.
		@return int32 - kReadOPIComments or kDontReadOPIComments
	 */
	virtual int32 GetImportEPSReadOPI(void) const = 0;

	/**	Get create frame from clipping path.
		@return int32 - kCreateFrameFromClipPath or kDontCreateFrameFromClipPath
	 */
	virtual int32 GetImportEPSCreateFrame(void) const = 0;

	/**	Get display resolution.
		@return PMReal - value for the display resolution
	 */
	virtual PMReal GetImportEPSDisplayRes(void) const = 0;

	/**	Get create proxy mode.
		@return int32 - kNeverCreate or kCreateIfNeeded or kAlwaysCreate
	 */
	virtual int32 GetImportEPSCreateProxy(void) const = 0;

};

#endif
