//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IAdobeBasicJobMetaData.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __IAdobeBasicJobMetaData_h__
#define __IAdobeBasicJobMetaData_h__

#include "IPMUnknown.h"
#include "MetaDataID.h"
#include "K2Vector.h"

//========================================================================================
// CLASS IAdobeBasicJobMetaData
//========================================================================================
/**
	This interface encapsulates routines of the XMPToolkit for accessing XMP Basic Job Ticket Properties 
	defined in 'xapBJ' namespace.
	@see IAdobeCoreMetaData
	@see IAdobeMediaMgmtMetaData
	@see IAdobeRightsMgmtMetaData
	@see IMetaDataAccess
*/
class IAdobeBasicJobMetaData : public IPMUnknown
{
public:

	/** This class is used to store one Job definition.
	*/
	class Job
	{
	public:
		/** typedefs */
		typedef object_type data_type;
		/* Constructors */
		/** Constructs a Job from name and id.
			@param	name	IN	Job name. Default is blank.
			@param	id		IN	Job id. Default is blank.
		*/
		Job(const PMString& name = "", const PMString& id = "") : fName(name), fId(id) { }

		/** Copy Constructor.
			@param	other	IN	Job to copy from.
		*/
		Job(const Job& other) : fName(other.fName), fId(other.fId) { }

		/** Assignment operator.
			@param	other	IN	Job to assign from.
		*/
		Job& operator=(const Job& other)
		{
			if (this != &other)
			{
				fName = other.fName;
				fId = other.fId;
			}
			
			return *this;
		};
		
		/** Compares two jobs.
			@param	other	IN	Other job to compare.
			@return true if both are equal. false otherwise.
		*/
		bool operator==(const Job& other) const
		{
			return fName == other.fName && fId == other.fId;
		}
		
		/** Sets the name of the job.
			@param	name	IN	Job name to set.
		*/
		void SetName(const PMString& name) { fName = name; }

		/** Returns the job name.
			@return The job name.
		*/
		PMString GetName() const { return fName; }
		
		/** Sets the id of the job.
			@param	id	IN	Job id to set.
		*/
		void SetId(const PMString& id) { fId = id; }

		/** Returns the id of the job.
			@return	The job id.
		*/
		PMString GetId() const { return fId; }
		
	private:
		PMString fName;
		PMString fId;
	};
	
public:
	enum { kDefaultIID = IID_IADOBEBASICJOBMETADATA };

	// ----- xapBJ:JobRef
	/** Sets a list of jobs specified by 'xapBJ:JobRef' property.
		@param	jobs	IN	A list of jobs to set.
	*/
	virtual void			SetJobs(const K2Vector<Job>& jobs) = 0;

	/** Returns a list of jobs specified by 'xapBJ:JobRef' property.
		@return A list of jobs.
	*/
	virtual K2Vector<Job>	GetJobs() const = 0;
};


#endif // __IAdobeBasicJobMetaData_h__
