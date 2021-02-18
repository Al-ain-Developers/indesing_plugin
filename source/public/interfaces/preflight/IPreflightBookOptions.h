//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightBookOptions.h $
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

#include "IPMUnknown.h"
#include "PackageAndPreflightID.h"
#include "IPMStream.h"
#include "IPreflightOptions.h"

/**	Data interface for book preflight options. Similar to IPreflightOptions but there's
	not a 1:1 correspondence and it would be kind of irritating to overload the other 
	interface. Persisted at the application level for defaults purposes.

	This interface sits on both the book root object to establish defaults; and on the
	in-memory book preflight object to represent the settings used for a particular 
	book preflight operation. (See IPreflightBookRef.)
*/
class IPreflightBookOptions: public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTBOOKOPTIONS };

public:
	/**	Sets whether to check all docs (as opposed to the selected docs).
		@param allDocs IN True for all docs, false for selection (ignored if no selection).
	*/
	virtual void SetCheckAllDocs(bool allDocs) = 0;

	/**	@return whether to check all docs (true) or only selected docs (false).
	*/
	virtual bool GetCheckAllDocs() const = 0;

	/**	Sets the layer options for preflight.
		@param layerOptions specified the layer option to use.
	*/
	virtual void SetLayerOptions (const IPreflightOptions::LayerOptions layerOptions) = 0;

	/**	@return the preflight layer option.
	*/
	virtual IPreflightOptions::LayerOptions GetLayerOptions () const = 0;
	
	/**	Sets to true if include objects on the pasteboard for preflight.
		@param onOff specifies either to include or exclude objects on the pasteboard.
		true if to include, otherwise excluded.
	*/
	virtual void SetIncludeObjectsOnPasteboard (const bool16 onOff) = 0;
	
	/**	@return true if object included; otherwise false.
	*/
	virtual bool16 GetIncludeObjectsOnPasteboard () const = 0;
	
	/**	Sets to true if include non-printing objects for preflight.
		@param onOff specifies either to include or exclude non-printing objects.
		true if to include, otherwise excluded.
	*/
	virtual void SetIncludeNonPrintingObjects (const bool16 onOff) = 0;

	/**	@return true if object included; otherwise false.
	*/
	virtual bool16 GetIncludeNonPrintingObjects () const = 0;

	/**	Set the preflight profile policy when preflighting book docs.
		Note that this setting only applies at the application-level.
		@param openPolicy specifies the policy to use.
	*/
	virtual void SetPreflightProfilePolicy(IPreflightOptions::PreflightProfilePolicy profilePolicy) = 0;

	/**	@return the preflight profile policy for new/open document.
	*/
	virtual IPreflightOptions::PreflightProfilePolicy GetPreflightProfilePolicy() const = 0;

	/**	Set the preflight profile to use by default or in the absence of a doc profile 
		(@see SetPreflightProfilePolicy).
		@param profileName specifies the name of the preflight profile to use.
	*/
	virtual void SetUseProfile (const PMString& profileName) = 0;

	/**	@return the name of the preflight profile to use by default or in the absence of a doc profile
		(@see SetPreflightProfilePolicy).
	*/
	virtual PMString GetUseProfile () const = 0;

	/** Set whether to generate a report when the preflight is done.
		@param reportOnly IN True to generate a report; false to simply exit back to user control.
	*/
	virtual void SetGenerateReportOnly(const bool16 reportOnly) = 0;

	/** @return whether to generate a report when the preflight is done.
	*/
	virtual bool16 GetGenerateReportOnly() const = 0;

	/**	Copy options data.
		@param iOther is the preflight option data to copy from.
	*/
	virtual void CopyFrom (const IPreflightBookOptions* iOther) = 0;
};

