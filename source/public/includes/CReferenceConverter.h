//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CReferenceConverter.h $
//  
//  Owner: Prakash Verma
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

#pragma once
#ifndef __CReferenceConverter__
#define __CReferenceConverter__

#include "IReferenceConverter.h"

class CReferenceConverter : public CPMUnknown<IReferenceConverter>
{
	public:
		CReferenceConverter(IPMUnknown *boss) : CPMUnknown<IReferenceConverter>(boss) {}
		virtual ~CReferenceConverter(){}	

		//override this method.
		virtual bool16 CanConvert(ClassID)
		{
			ASSERT_UNIMPLEMENTED();
			return kFalse;
		}

		//override this method.
		virtual UID ConvertReference(IDataBase*, UID, IDataBase*, IPMUnknown*)
		{
			ASSERT_UNIMPLEMENTED();
			return kInvalidUID;
		}

		//override this method.
		virtual bool16 ConvertAlways() const
		{
			ASSERT_UNIMPLEMENTED();
			return kFalse;
		}

		//override this method.
		virtual UID GetReference(IDataBase*, UID, IDataBase*) const
		{
			ASSERT_UNIMPLEMENTED();
			return kInvalidUID;
		}

		virtual bool16 IsMappingReference(IDataBase*, UID, IDataBase*) const
		{
			return kFalse;
		}

		virtual UID MapReference(IDataBase*, UID, IDataBase*, IPMUnknown*)
		{
			return kInvalidUID;
		}

		virtual UID GetMappedReference(IDataBase*, UID, IDataBase*)
		{
			return kInvalidUID;
		}
};

#endif // __CReferenceConverter__
