//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/MetadataLabelEVEInfo.cpp $
//  
//  Owner: lance bushore
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
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

#include "IEveInfo.h"	
#include "LinksUIID.h"
#include "EveInfo.fh"
#include "IWidgetUtils.h"

class MetadataLabelEVEInfo : public CPMUnknown<IEveInfo>
{
public:
				MetadataLabelEVEInfo(IPMUnknown *boss);
	virtual uint32 GetHeight() const;
	virtual uint32 GetWidth() const;
	virtual void AppendEveDescriptionForControl(PMString* dialogDesc) const;
	virtual void ApplyEVELayoutToWidget(const PMPoint& newTopLeft, const PMReal& newWidth, const PMReal& newHeight);
	virtual uint32 GetChildArrangement() const { return kEVEArrangeChildrenInRow; }
	virtual void SetChildArrangement(uint32 ) { }
	virtual uint32 GetChildAlignment() const { return kEVEChildAlignLeft; }
	virtual uint32 GetChildSpaceAfter() const { return kEVEChildNoSpaceAfter; }
	virtual uint32 GetMargin() const { return kEVENoMargin; }
	virtual void SetMargin(uint32) {}
	virtual uint32 GetSpaceAfter() const { return kEVERegularSpaceAfter; }
	virtual void SetSpaceAfter(uint32) { }
	virtual uint32 GetAlignment() const { return kEVEAlignLeft; }
	virtual bool16 GetIncludeForFirstColumnAlignment() const { return kFalse;}
	virtual bool16 GetDoNotIncludeForAlignmentOfLables() const { return kFalse;}
	virtual bool16 HasEVEInfo() const { return kTrue; }
	virtual void AppendEveDescriptionForControlToStdString(std::stringstream &dialogDesc) const;

};

CREATE_PMINTERFACE( MetadataLabelEVEInfo, kMetadataLabelEVEInfoImpl)

MetadataLabelEVEInfo::MetadataLabelEVEInfo(IPMUnknown *boss) :
	CPMUnknown<IEveInfo>(boss)
{

}

uint32 MetadataLabelEVEInfo::GetHeight() const
{
	InterfacePtr<IEveInfo> myEveInfo(this,IID_IALTEVEINFO);
	return myEveInfo->GetHeight();	
}

uint32 MetadataLabelEVEInfo::GetWidth() const
{
	InterfacePtr<const IEveInfo> metadataDropdownEveInfo((IEveInfo*)Utils<IWidgetUtils>()->QueryRelatedWidget(this,kCaptionMetadataDropDownWidgetID,IID_IEVEINFO));
	return metadataDropdownEveInfo->GetWidth();	
}

void MetadataLabelEVEInfo::AppendEveDescriptionForControl(PMString* dialogDesc) const
{
	InterfacePtr<IEveInfo> myEveInfo(this,IID_IALTEVEINFO);
	myEveInfo->AppendEveDescriptionForControl(dialogDesc);	
}

void MetadataLabelEVEInfo::AppendEveDescriptionForControlToStdString(std::stringstream &dialogDesc) const
{
	InterfacePtr<IEveInfo> myEveInfo(this, IID_IALTEVEINFO);
	myEveInfo->AppendEveDescriptionForControlToStdString(dialogDesc);
}

void MetadataLabelEVEInfo::ApplyEVELayoutToWidget(const PMPoint& newTopLeft, const PMReal& newWidth, const PMReal& newHeight)
{
	InterfacePtr<IEveInfo> myEveInfo(this,IID_IALTEVEINFO);
	myEveInfo->ApplyEVELayoutToWidget(newTopLeft, newWidth, newHeight);	
}