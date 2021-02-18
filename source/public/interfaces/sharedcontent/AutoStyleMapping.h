//======================================================================================== 
//   
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/sharedcontent/AutoStyleMapping.h $ 
//   
//  Owner: Gaurav Bhargava
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
//  Copyright 2010 Adobe Systems Incorporated
//  All Rights Reserved.
//   
// NOTICE:  All information contained herein is, and remains
// the property of Adobe Systems Incorporated and its suppliers,
// if any.  The intellectual and technical concepts contained
// herein are proprietary to Adobe Systems Incorporated and its
// suppliers and are protected by trade secret or copyright law.
// Dissemination of this information or reproduction of this material
// is strictly forbidden unless prior written permission is obtained
// from Adobe Systems Incorporated. 
//   
//======================================================================================== 

#pragma once
#ifndef __AutoStyleMapping__ 
#define __AutoStyleMapping__

#include "IBoolData.h"
#include "IStyleMappings.h"
#include "IMappingSession.h"

/** Automatically turns on style mapping in the constructor and turns it off
    in the destructor so you do not have to explicitly call set & un-set calls.
    Just create an AutoStyleMapping stack object and you are done. Prevents 
    problems with early returns forgetting to un-set and leaving a session open.

	styleMappingItem param can be optionally used to set the style mapping data
	onto the session. If nil is passed in then the callee needs to set the data 
	separately.
*/

class AutoStyleMapping
{
public:

	/** Constructor
    */
	explicit AutoStyleMapping(bool16 map, const IPMUnknown* styleMappingItem, IDataBase *srcDB, IDataBase *destDB):
	fMap(map)
	{
		InterfacePtr<IMappingSession> mappingSession(GetExecutionContextSession(), UseDefaultIID());
		if(mappingSession && map)	
		{
			mappingSession->BeginMappingSession(srcDB, destDB);

			InterfacePtr<IStyleMappings> styleMappings(styleMappingItem, UseDefaultIID());
			if( styleMappings )
			{
				InterfacePtr<IStyleMappings> sessionStyleMappings(mappingSession,UseDefaultIID());
				ASSERT(sessionStyleMappings);
				sessionStyleMappings->ClearMappings();
				sessionStyleMappings->CopyFrom(styleMappings);		
			}
		}
	}

	/** Destructor
    */
	~AutoStyleMapping()
	{
		InterfacePtr<IMappingSession> mappingSession(GetExecutionContextSession(), UseDefaultIID());
		if(mappingSession && fMap)	
		{
			mappingSession->EndMappingSession();

			InterfacePtr<IStyleMappings> sessionStyleMappings(mappingSession,UseDefaultIID());
			ASSERT(sessionStyleMappings);
			sessionStyleMappings->ClearMappings();
		}

	}
private:
	bool16 fMap;
};


#endif //__AutoStyleMapping__