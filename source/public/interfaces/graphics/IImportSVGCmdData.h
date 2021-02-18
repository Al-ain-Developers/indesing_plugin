//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IImportSVGCmdData.h $
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
//========================================================================================

#pragma once
#ifndef __IImportSVGCmdData__
#define __IImportSVGCmdData__

#include "IPMUnknown.h"

class IDataBase;
class IPMStream;
class PMReal;

/** Settings for the command data to import an EPS - kImportSVGCmdBoss
*/
class IImportSVGCmdData : public IPMUnknown
{
public:
	/**	Set method for all parameters
	@param db IN the database for the EPS
	@param uid IN the UID of the EPS
	@param targetRes IN the target display resolution
	@param pStreamToImport IN the stream to the EPS
	@param uiFlags IN the current UI flags
	@param bAddProColor IN add process colors - currently unsupported don't use
	@param bImportDCS IN import nested DCS - currently unsupported don't use
	@param bReadOPI IN read nested OPI comments
	@param bCreateFrame IN create frame from clipping path
	@param uidPreview IN UID of the EPS proxy preview
	*/
	virtual void Set(IDataBase* db,
		const UID uid,
		const PMReal& targetRes,
		IPMStream* pStreamToImport,
		const UIFlags uiFlags,
		const bool16 bAddProColor,
		const bool16 bImportDCS,
		const bool16 bReadOPI,
		const bool16 bCreateFrame,
		UID uidPreview) = 0;

	/**	Get EPS database
	@return IDataBase* pointer to the database
	*/
	virtual IDataBase* GetSVGDB() const = 0;

	/**	Get EPS UID
	@return UID of the EPS page item
	*/
	virtual UID GetSVGUID() const = 0;

	/**	Get the target resolution
	@return PMReal the target resolution
	*/
	virtual PMReal GetTargetRes() const = 0;

	/**	Get the EPS stream to import
	@return IPMStream* pointer to the EPS import stream
	*/
	virtual IPMStream* GetStream() const = 0;

	/**	Get the current UI flags
	@return UIFlags current UI flags
	*/
	virtual UIFlags GetUIFlags() const = 0;

	/**	Get add process colors - currently unsupported don't use
	@return bool16 whether to add process colors or not
	*/
	virtual bool16 GetAddProColor() const = 0;

	/**	Get import nested DCS - currently unsupported don't use
	@return bool16 whether to import nested DCS or not
	*/
	virtual bool16 GetImportDCS() const = 0;

	/**	Get read nested OPI comments
	@return bool16 whether to read OPI comments or not
	*/
	virtual bool16 GetReadOPI() const = 0;

	/**	Get create frame from clipping path
	@return bool16 whether to create clipping path frame or not
	*/
	virtual bool16 GetCreateFrame() const = 0;

	/**	Get UID for the EPS proxy preview
	@return UID for the EPS proxy
	*/
	virtual UID GetPreview() const = 0;
};

#endif
