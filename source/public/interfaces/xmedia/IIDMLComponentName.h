//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IIDMLComponentName.h $
//  
//  Owner: Lin Xia
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

#ifndef __IIDMLComponentName_h__
#define __IIDMLComponentName_h__

#include "INXCoreID.h"

/**
	An interface on PerInstance objects (defined by the m_INXPackageSubFile_PerInstance metadata) in an IDML package.
	For this kind of objects, each instance is exported as a separate sub file inside an IDML package.
	Currently these objects include MasterSpread, Spread, and Story.

	During export, an object's IDMLComponent name is used as the base file name (appended by ".xml")
	of the corresponding sub file in an IDML package.
	It also apperas in the reference to the sub file in the main file designmap.xml.

	If no IDMLComponentName has been specified for an object, a default name is used during export.
	Since the default name contains an object's UID, it could change after a document is
	exported and re-imported.

	The file name and the reference to a sub file in an IDML package can be modified externally.
	During import, the modified name will be used to update the object's IDMLComponentName,
	if the name is valid and unique.
*/

class IIDMLComponentName : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IIDMLCOMPONENTNAME };

	/**
	Determines if a name already exists, if not a default name will be generated 
	by appending the object UID to the scripting object type (e.g. 
	Spread_UID or Story_UID).
	@param name OUT A unique name for the component.
	*/
	virtual void Get(WideString& name) = 0;

	/**
	Tests to see whether the new name is valid and unique among the same type of 
	objects in the current document. 
	If the name is valid and unique the new name will be stored and the interface will be dirtied. 
	If it is not valid or not unique, the name will not be changed.

	A name is invalid if it contains these reserved characters for file names:
		'/', '\', '?', '%', '*', ':', '|', '"', '<', '>', '.'
	In order to avoid conflict with default names, a name that starts with the script object name, 
	followed by '_', followed by a 'u' or 'U', followed by one or more hex digits, 
	and followed by nothing, is INVALID.
	e.g. Spread_u10f is not a valid component name for a spread but Spread_u10f_Transformed is valid.

	@param newName IN The new name. Pass an empty newName to use the default name.
	@return kINXCoreInvalidComponentName if newName is not valid;
			kItemWithThisNameAlreadyExistsError if newName is not unique;
			kSuccess if successful.
	*/
	virtual ErrorCode Set(const WideString& newName) = 0;
};

#endif	// __IIDMLComponentName_h__
