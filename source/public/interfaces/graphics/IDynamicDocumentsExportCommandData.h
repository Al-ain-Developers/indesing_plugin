//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IDynamicDocumentsExportCommandData.h $
//  
//  Owner: Greg St. Pierre
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

#include "DynamicDocumentsID.h"
#include "DynamicDocumentsTypes.h"

class IPMStream;

/**
 Data interface for dynamic documents (Flash) export command
 */
class IDynamicDocumentsExportCommandData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDYNDOCSEXPORTCOMMANDDATA };
	
	/**
	 Sets the destination stream for the export. Will AddRef the stream.
	 
	 @param stream		The destination stream for the export
	 */
	virtual void SetStream(IPMStream *stream) = 0;
	
	/**
	 Gets the destination stream for the export. Does *not* AddRef return value.
	 
	 @return the destination stream for the export
	 */
	virtual IPMStream *GetStream() const = 0;
	
	/** 
	 Sets the UI flags for the export.
	 
	 @param				The UI flags for the export
	 */
	virtual void SetUIFlags(UIFlags flags) = 0;
	
	/**
	 Gets the UI flags for the export.
	 
	 @return the UI flags for the export
	 */
	virtual UIFlags GetUIFlags() const = 0;

	/** 
	 Sets the format name for the export.
	 
	 @param				The format name for the export
	 */
	virtual void SetExportFormatName(PMString const &formatName) = 0;
	
	/**
	 Gets the format name for the export.
	 
	 @return theformat name for the export
	 */
	virtual PMString GetExportFormatName() const = 0;

	/** 
	 Sets whether the export is a selection export.
	 
	 @param				Boolean denoting if the export is a selection export.
	 */
	virtual void SetExportSelection(bool bExportSelection) = 0;
	
	/**
	 Gets whether the export is a selection export.
	 
	 @return true if a selection export, else false.
	 */
	virtual bool GetExportSelection() const = 0;
};
