//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/incopyexport/ICExportPrefsScriptProvider.cpp $
//  
//  Owner: Jon Pugh
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

#include "VCPlugInHeaders.h"
#include "PrefsScriptProvider.h"

#include "InCopyExportID.h"

class ICExportPrefsScriptProvider : public PrefsScriptProvider
{
public:
	ICExportPrefsScriptProvider(IPMUnknown *boss);

	virtual ErrorCode AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script);
};

CREATE_PMINTERFACE(ICExportPrefsScriptProvider, kICExportPrefsScriptProviderImpl)

ICExportPrefsScriptProvider::ICExportPrefsScriptProvider(IPMUnknown *boss):
	PrefsScriptProvider(boss)
{
	DefinePreference(c_ICExportPref, p_ICExportPref);
}

ErrorCode ICExportPrefsScriptProvider::AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{
	switch (propID.Get())
	{
		case p_IncludeStyleTable:
		case p_IncludeSwatchList:
		case p_IncludeXMP:
		case p_Encoding:
			return kObsoleteScriptingRequestError ;
	}

	return PrefsScriptProvider::AccessProperty(propID, data, script);
}
