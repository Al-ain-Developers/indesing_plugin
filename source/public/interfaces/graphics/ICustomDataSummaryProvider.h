//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ICustomDataSummaryProvider.h $
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
//  Provider interface for allowing third parties a chance to add their own custom
//  settings to the Print and PDF summaries, if desired. The providers will be called 
//  when the summary is generated. Their summary information is appended to the end.
//  
//========================================================================================

#pragma once
#ifndef __ICustomDataSummaryProvider__
#define __ICustomDataSummaryProvider__

#include "PrintID.h"
#include "IPMUnknown.h"

class IDocument;
class IGenericSettingsGroup;
class IPrintData;
class IPDFExportPrefs;
class IPDFSecurityPrefs;

/**
	Provider interface for allowing third parties a chance to add their own custom
	settings to the Print and PDF summaries, if desired. The providers will be called 
	when the summary is generated. Their summary information is appended to the end.

	Third parties can call pRootGroup->AddGroup() to add their sub class of data. From 
	there, they can use APIs in ISummaryUtils to add each of their settings individually,
	passing in the IGenericSettingsGroup returned from AddGroup().

	Example code:
	{
		int32 myNumberValue = 52;
		Utils<ISummaryUtils> utilSummary;
		InterfacePtr<IGenericSettingsGroup> pMyGroup(pRootGroup->AddGroup("kMyGroupName", ""), UseDefaultIID());
		utilSummary->AddNumber(pMyGroup, "kMyNumberLabel", myNumberValue);
	}

	@see IGenericSettingsGroup
	@see ISummaryUtils
*/
class ICustomDataSummaryProvider : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICUSTOMDATASUMMARYPROVIDER };

	/**
	 Append third party custom Print data to the summary.
	 @param pRootGroup		IN the IGenericSettingsGroup interface to add your group to.
	 @param pData			IN the IPrintData interface being used.
	 @param pDoc			IN the IDocument interface of the pub. If working on a style, pointer will be nil!
	 @param bWorkingOnStyle	IN kTrue if working on a Print Preset, kFalse otherwise.
	 */
	virtual void ConvertToSummary(	IGenericSettingsGroup* pRootGroup,
									const IPrintData* pData,
									const IDocument* pDoc,
									bool16 bWorkingOnStyle
									) const = 0;

	/**
	 Append third party custom PDF data to the summary.
	 @param pRootGroup		IN the IGenericSettingsGroup interface to add your data to.
	 @param pData			IN the IPDFExportPrefs interface being used.
	 @param pSecurity		IN the IPDFSecurityPrefs interface being used - this pointer may be nil!
	 @param pDoc			IN the IDocument interface of the pub. If working on a style, pointer will be nil!
	 @param bIncludeDescriptionAndWarning	IN kTrue if warning text to be included, kFalse otherwise.
	 */
	virtual void ConvertToSummary(	IGenericSettingsGroup* pRootGroup,
									const IPDFExportPrefs* pData,
									const IPDFSecurityPrefs* pSecurity, 
									const IDocument* pDoc,
									bool16 bIncludeDescriptionAndWarning 
									) const = 0;
};

#endif
