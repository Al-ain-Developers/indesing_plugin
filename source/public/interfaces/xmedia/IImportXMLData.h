//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IImportXMLData.h $
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
//  
//  This interface is used for action components to update the state of their actions.
//  It is NOT a standard boss interface - it does not inherit from IPMUnknown!
//  
//========================================================================================

#pragma once
#ifndef __IImportXMLData__
#define __IImportXMLData__

#include "XMLID.h"

class IDataBase;
class IDataLink;
class XMLReference;

/**
	A data interface used by XML import.
*/
class IImportXMLData : public IPMUnknown 
{
public:
	enum { kDefaultIID = IID_IIMPORTXMLDATA };
	
	/**
		Initialize the settings of this object from the settings of the 'data' object.
		@param data					In	The data object used for initialization.
	*/
	virtual void Set(IImportXMLData *data) = 0;

	/**
		Set import data.
		@param db					In	The database to be imported into.
		@param importSource			In	The source of the import.
		@param importDestination	In The element into which the source will be imported.
		@param flags				In pecifies how much UI to show during import
	*/
	virtual void Set(IDataBase *db, const IDFile &importSource, const XMLReference& importDestination, UIFlags flags) = 0;
	
	/**
		Set import destination.
		@param importDestination	In The element into which the source will be imported.
	*/
	virtual void SetImportDestination(const XMLReference& importDestination) = 0;

	/**
		Set the import source.
		@param importSource The import source.
	*/
	virtual void SetImportSource(const IDFile &importSource) = 0;

	/**
		Update the UIFlags
		@param flags The updated flags.
	*/
	virtual void SetFlags( UIFlags flags ) = 0;

	/**
		Accessor for the database.
		@return the database to be imported into.
	*/
	virtual IDataBase *GetDataBase() = 0;
	/**
		Accessor for the import source.
		@return the import source.
	*/
	virtual IDFile &GetImportSource() = 0;
	/**
		Accessor for the import destination.
		@return the XML element into which the source will be imported.
	*/
	virtual XMLReference &GetImportDestination() = 0;
	/**
		Accessor for the UI flag.
		@return the UI flag.
	*/
	virtual UIFlags GetFlags() = 0;		
};

#endif // __IImportXMLData__