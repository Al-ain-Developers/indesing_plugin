//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightVisitInfo.h $
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
#include "PreflightObjectID.h"

class IPreflightObject;
class IPreflightOptions;
class IPreflightResultRecord;

/**	Provides context, information, and results feedback to a preflight rule visitor.
	The only use this interface has in the API is as an argument to IPreflightRuleVisitor::Visit.

	Typical application:

		void MyRuleVisitor::Visit(IPreflightVisitInfo* iInfo)
		{
			InterfacePtr<IPreflightObject> iObj(iInfo->QueryObject());

			if (iInfo->GetObjectID().GetClassID() == kPreflightOM_PageItem)
			{
				// Query interfaces from iObj, and/or use iObj->GetModelRef()..

				if (error condition detected)
				{
					InterfacePtr<IPreflightResultRecord> iRec(iInfo->CreateResultRecord());
					iRec->SetCriteria(...);
					// etc
				}
			}
		}
*/
class IPreflightVisitInfo
{
public:
	/** Get the preflight options. Most of the time you don't care about this, in the sense that
		the upstream object model implementation strips out objects you shouldn't "care about."
		But if you're doing your own object model walking then you may need to honor the settings.

		@return A refcounted preflight options interface.
	*/
	virtual const IPreflightOptions* QueryOptions() const = 0;

	/** Get the object you're visiting.
		@return The preflight object ID of the object you're visiting.
	*/
	virtual const PreflightObjectID& GetObjectID() const = 0;

	/** Get a preflight object interface for the object you're visiting. This produces the same
		results as IPreflightObjectModel::QueryObject(GetObjectID()) but 

		@return A refcounted preflight object interface pointer.
	*/
	virtual IPreflightObject* QueryObject() const = 0;

	/** Create a preflight result record. This is a result that corresponds to an error condition.
		You can record the parameters of the failure here; they are automatically persisted in the
		database and can be retrieved later at results aggregation time.

		Note that the created record is owned by the PreflightVisitInfo object as part of its
		internal tables, so you wouldn't use the result to do arbitrary things with. If you 
		need a preflight result record with a life cycle you manage yourself, use 
		IPreflightAggregatedResultsUtils::CreatePreflightResultRecord.

		@return A refcounted results record.
	*/
	virtual IPreflightResultRecord* CreateResultRecord() = 0;
};

