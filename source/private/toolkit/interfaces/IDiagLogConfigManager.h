//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/private/toolkit/interfaces/IDiagLogConfigManager.h $
//  
//  Owner: rbriggs 
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
#ifndef __IDiagLogConfigManager__
#define __IDiagLogConfigManager__

#include "IPMUnknown.h"
#include "IEvent.h"

#include "DiagnosticLogID.h"

#define kDiagLogOutputFileName "DiagnosticLogOutput"
#define kDiagLogConfigFileName "DiagnosticLogConfiguration"
#define kDiagLogRTEnvironmentFileName "DiagnosticLogRTEnvironment.xml"


/**
	This interface contains various data which control the behavior DiagnosticLog.
*/
class IDiagLogConfigManager: public IPMUnknown 
{
public:
	enum { kDefaultIID = IID_IDIAGLOGCONFIGMANAGER };

	/**
		Logging category. Allow user to control logging output.
	*/
	typedef enum { 
		kDiagLogAction = 0,
		kDiagLogCommand,
		kDiagLogIdleTask,
		kDiagLogObserver,
		kDiagLogResponder,
		kDiagLogEvents,

		kDiagLogTracking,
		kDiagLogTransaction,
		kDiagLogMemoryPurge,
		kDiagLogGlobalErrorState,
		kDiagLogTextDamageMark,

		kDiagLogLastCategory
	} DiagLogCategory;

	/**
		Logging output detail level for each category. Please refer to DiagnosticLog tool document.
	*/
	typedef enum { 
		kDiagLogMinimum = 0,
		kDiagLogMedium,
		kDiagLogMaximum
	} DiagLoggingLevel;

	/**
		Some categories use these two lists to filter output. Please refer to DiagnosticLog tool document.
	*/
	enum ListType { kIncludeList, kExcludeList };

	// load and save config to xml file
	/**	
		Load configuration file.

		@return	bool16 kTrue if config file load correctly
	*/
	virtual bool16 Load() = 0;
	/**	
		Save configuration file.
	*/
	virtual void Save() = 0;

	// file location
	/**	
		Get folder location of configuration file.

		@return	IDFile folder which contain configuration file
	*/
	virtual IDFile GetConfigFilePath() = 0;
	/**	
		Get folder location of output file.

		@return	IDFile folder which contain output file
	*/
	virtual IDFile GetOutputPath() = 0;
	/**	
		Set folder location of output file.

		@param path full path of the folder contains output file
	*/
	virtual void SetOutputPath(const PMString & path) = 0;

	// ID database
	/**	
		Get ID database file name.

		@return file name for ID database
	*/
	virtual PMString GetIDDatabaseName() = 0;
	/**	
		Set ID database file name.

		@param name  file name for ID database
	*/
	virtual void SetIDDatabaseName(const PMString & name) = 0;
	/**	
		Get load ID database flag.

		@return	kTrue if we want to load ID database
	*/
	virtual bool16 GetLoadIDDatabase() = 0;
	/**	
		Set load ID database flag.

		@param load boolean flag if ID database should be loaded
	*/
	virtual void SetLoadIDDatabase(bool16 load) = 0;

	// master switch for logging
	/**	
		Get master switch for logging. This flag overrides the setting for 
		individual category.

		@return	kTrue if switch is on
	*/
	virtual bool16 GetLogging() = 0;
	/**	
		Set master switch for logging.

		@param log boolean flag for logging master switch
	*/
	virtual void SetLogging(bool16 log) = 0;
	/**	
		Get the logging level. This flag controls the detail level of logging.

		@return	enum DiagLoggingLevel { kDiagLogMinimum, kDiagLogMedium, kDiagLogMaximum }
	*/
	virtual DiagLoggingLevel GetLoggingLevel() const = 0;
	/**	
		Set the logging level.

		@param level member of enum DiagLoggingLevel
	*/
	virtual void SetLoggingLevel(DiagLoggingLevel level) = 0;

	/**	
		This flag controls if timing information will be logged for each context.

		@return	kTrue if logging timing information
	*/
	virtual bool16 GetLoggingTimeInfo() = 0;
	/**	
		Set if logging timing information flag.

		@param timing kTrue if logging timeing information
	*/
	virtual void SetLoggingTimeInfo(bool16 timing) = 0;
	/**	
		Determine timing information threshold. If recorded timing value is below this 
		value, it will not be logged. Usually this value is determined by resolution 
		of clock.

		@return	int32 threshold in 1/1000 second
	*/
	virtual int32 GetLoggingTimeThreshold() const = 0;
	/**	
		Set timing threshold.

		@param threshold timeing threshold in 1/1000 second
	*/
	virtual void SetLoggingTimeThreshold(int32 threshold) = 0;

	// switch for category
	/**	
		Determine if this category should be logged. Category flag is override by master
		logging flag.

		@param category member of enum DiagLogCategory
	*/
	virtual bool16 GetCategoryLogging(DiagLogCategory category) = 0;
	/**	
		Set logging flag for category.

		@param category member of enum DiagLogCategory
		@param log boolean flag for category logging status
	*/
	virtual void SetCategoryLogging(DiagLogCategory category, bool16 log) = 0;
	/**	
		Determine if this id in category should be logged. When id = 0, this function is the 
		same as GetCategoryLogging. When id != 0, it will check include and exclude list to
		determine if this id should be logged.

		@param category member of enum DiagLogCategory
		@param id value of ID. ID could be boss id, interface id et al. It is dependent on how include and exclude list are defined.
	*/
	virtual bool16 GetCategoryLogID(DiagLogCategory category, int32 id = 0) = 0;
	/**	
		Add a id into category list. Some category has two lists: include and exclude list.

		@param category member of enum DiagLogCategory
		@param lType member of enum ListType
		@param id integer value of ID
	*/
	virtual void AddCategoryList(DiagLogCategory category, ListType lType, int32 id) = 0;
	/**	
		Remove a id from category list.

		@param category member of enum DiagLogCategory
		@param lType member of enum ListType
		@param id integer value of ID
	*/
	virtual void RemoveCategoryList(DiagLogCategory category, ListType lType, int32 id) = 0;

	// individual event
	/**	
		Determine if this individual event type should be logged. Event category logging flag 
		override flag for individual event

		@param eventType member of enum IEvent::EventType
	*/
	virtual bool16 GetLogEvent(IEvent::EventType eventType) = 0;
	/**	
		Set logging flag for individual event.

		@param eventType member of enum IEvent::EventType
		@param bLog boolean flag for this event type logging status
	*/
	virtual void SetLogEvent(IEvent::EventType eventType, bool16 bLog) = 0;	
	/**	
		Set logging flag for individual event.

		@param eventName name of event corresponding to IEvent::EventType
		@param log boolean flag for this event type logging status
	*/
	virtual void SetLogEvent(PMString eventName, bool16 bLog) = 0;

	// utility
	/**	
		Translate event type to string name

		@param eventType member of enum IEvent::EventType
		@return	PMString name of this event
	*/
	virtual PMString GetEventName(IEvent::EventType eventType) = 0;
};

#endif // __IDiagLogConfigManager__