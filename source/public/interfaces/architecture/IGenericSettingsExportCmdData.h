//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IGenericSettingsExportCmdData.h $
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
#ifndef __IGenStlEdtCmdData__
#define __IGenStlEdtCmdData__

#include "IPMUnknown.h"
#include "K2Vector.h"
#include "IGenericSettings.h"
#include "IGenericSettingsOutput.h"

/** Parameter data for the GenericSettingsExportCmd which is used to write a file with
	the preset preferences in a human readable fashion.
	See ISummaryUtils::ExportHumanTextSummary.
*/
class IGenericSettingsExportCmdData: public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGENERICSETTINGSEXPORTCMDDATA };

public:
	/** Get the preset preferences.
		@return a pointer to the IGenericSettings interface. The pointer is valid
		as long as this object is valid.
	*/
	virtual IGenericSettings*               GetSettings()            = 0;

	/** Get the preset output strategy.
		@return a pointer to the IGenericSettingsOutputStrategy interface. The pointer is valid
		as long as this object is valid.
	*/
	virtual IGenericSettingsOutputStrategy* GetOutputStrategy()      = 0;

	/** Get the default filename of the file to write.
		@return the filename without path information.
	*/
	virtual const PMString&                 GetDefaultFilename()     = 0;

	/** Get title of dialog used to get the file to write.
		@return the title.
	*/
	virtual const PMString&                 GetExportDialogTitle()   = 0;

	/** Get file type string.
		@return the file type string.
	*/
	virtual const PMString&                 GetFileTypeString()      = 0;

	/** Get file extension string.
		@return the file extension string.
	*/
	virtual const PMString&                 GetFileTypeExtension()   = 0;


public:
	/** Specify which preset settings to write out.
		@param pSettings is a pointer to the preset preferences to use.
	*/
	virtual void SetSettings( IGenericSettings*               pSettings ) = 0;

	/** Specify the formatting to use when writing out the file.
		@param pStrategy is a pointer to the output strategy interface.
	*/
	virtual void SetStrategy( IGenericSettingsOutputStrategy* pStrategy ) = 0;

	/** Specify the default filename of the file to write.
		@param strSrc is the filename without path information.
	*/
	virtual void SetDefaultFilename( const PMString&          strSrc )    = 0;

	/** Specify the title of the dialog used to get the file to write.
		@param strSrc is the title.
	*/
	virtual void SetExportDialogTitle( const PMString&       strSrc )     = 0;

	/** Specify the file type string.
		@param str is the file type string.
	*/
	virtual void SetFileTypeString( const PMString& str    )              = 0;

	/** Specify the file type extension.
		@param str is the file type extension.
	*/
	virtual void SetFileTypeExtension( const PMString& str )              = 0;

};

#endif
