//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/aem/AEMExtensionContext.cpp $
//  
//  Owner: Harjot Singh
//  
//  $Author: vans $
//  
//  $DateTime: 2020/11/06 05:06:09 $
//  
//  $Revision: #1 $
//  
//  $Change: 1088554 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 2014 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#include "VCPlugInHeaders.h"
#include "CPMUnknown.h"

#include "IAemExtensionContext.h"
#include "UIDList.h"


//========================================================================================
// Class AEMExtensionContext
//========================================================================================
class AEMExtensionContext : public CPMUnknown<IAemExtensionContext>
{
public:
	typedef CPMUnknown<IAemExtensionContext> inherited;

	AEMExtensionContext(IPMUnknown* boss);

	virtual bool16				IsContextSet();
	virtual bool16				IsAfterExecutionContextSet();
	
	virtual void				ResetContext();
	virtual void				ResetAfterExecutionContext();

	virtual void				SetContext(LibraryContext context, const std::string& contextJson);
	virtual ErrorCode			GetContext(LibraryContext context, std::string& contextJson);

	virtual void				SetRelinkElementReceivedContext(const std::string& requestRef, int32 docID, UID linkUID, UID linkResourceUID, const UIDList& uidsToRelink);
	virtual ErrorCode			GetRelinkElementReceivedContext(std::string& requestRef, int32 &docID, UID& linkUID, UID& linkResourceUID, UIDList& uidsToRelink);
 
	virtual LibraryContext		GetCurrentContext();
	virtual LibraryContext		GetAfterExecutionContext();

private:

	void ResetData();
	void ResetAfterExecutionData();
	// Prevent copy construction and assignment.
	AEMExtensionContext(const AEMExtensionContext&);
	AEMExtensionContext& operator=(const AEMExtensionContext&);

	LibraryContext fContext;
	LibraryContext fAfterExecutionContext;
	std::string fContextJson;
	std::string fRelinkElementRequestRef;
	UIDList fUIDsToRelink;
	UID fLinkUID;
	UID fLinkResourceUID;
	int32 fDocID;
};

CREATE_PMINTERFACE(AEMExtensionContext, kAEMExtensionContextImpl)


AEMExtensionContext::AEMExtensionContext(IPMUnknown* boss)
: inherited(boss), fContext(kInvalidContext), fAfterExecutionContext(kInvalidContext),
fLinkUID(0), fLinkResourceUID(0), fDocID(-1)
{
}

bool16	AEMExtensionContext::IsContextSet()
{
	return fContext != kInvalidContext;
}

bool16	AEMExtensionContext::IsAfterExecutionContextSet()
{
	return fAfterExecutionContext != kInvalidContext;
}

void AEMExtensionContext::ResetData()
{
	fRelinkElementRequestRef.clear();
	fDocID = -1;
}

void AEMExtensionContext::ResetAfterExecutionData()
{
	fLinkUID = 0;
	fLinkResourceUID = 0;
}

void AEMExtensionContext::ResetContext()
{
	fContext = kInvalidContext;
	ResetData();
}

void AEMExtensionContext::ResetAfterExecutionContext()
{
	fAfterExecutionContext = kInvalidContext;
	ResetAfterExecutionData();
}

void AEMExtensionContext::SetContext(LibraryContext context, const std::string& contextJson)
{
	fContext = context;
	fContextJson = contextJson;
}

ErrorCode AEMExtensionContext::GetContext(LibraryContext context, std::string& contextJson)
{
	if (fContext != context)
		return kFailure;

	contextJson = fContextJson;
	return kSuccess;
}

void AEMExtensionContext::SetRelinkElementReceivedContext(const std::string& requestRef, int32 docID, UID linkUID, UID linkResourceUID, const UIDList& uidsToRelink)
{
	fAfterExecutionContext = kRelinkElementReceivedContext;
	fLinkUID = linkUID;
	fLinkResourceUID = linkResourceUID;
	fDocID = docID;
	fRelinkElementRequestRef = requestRef;
	fUIDsToRelink = uidsToRelink;
}

ErrorCode AEMExtensionContext::GetRelinkElementReceivedContext(std::string& requestRef, int32 &docID, UID& linkUID, UID& linkResourceUID, UIDList& uidsToRelink)
{
	if (fAfterExecutionContext != kRelinkElementReceivedContext)
		return kFailure;
	
	linkUID = fLinkUID;
	linkResourceUID = fLinkResourceUID;
	docID = fDocID;
	requestRef = fRelinkElementRequestRef;
	uidsToRelink = fUIDsToRelink;
	return kSuccess;
}

IAemExtensionContext::LibraryContext AEMExtensionContext::GetCurrentContext()
{
	return fContext;
}

IAemExtensionContext::LibraryContext AEMExtensionContext::GetAfterExecutionContext()
{
	return fAfterExecutionContext;
}
