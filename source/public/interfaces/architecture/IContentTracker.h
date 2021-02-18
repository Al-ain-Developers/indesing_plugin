//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IContentTracker.h $
//  
//  Owner: robin briggs
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
#ifndef __IContentTracker__
#define __IContentTracker__

#include "ShuksanID.h"
#include "IPMStream.h"

/** This interface is used by the system to keep track of content added to a database.
    IContentTracker is found on Bosses that include an implementation of IPMStream.
	The effect is to keep the Content Manager updated as to what is being written into
	the database.
	@see IPMStream
	@see IContentMgr
*/
class IContentTracker : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ICONTENTTRACKER };

		/** Notify the Content Manager that an implementation has been written
		    to the database.
			@param tag IN The implementation ID
		*/
		virtual void AddTag(ImplementationID tag) = 0;

		/** Notify the Content Manager that a class has been written
		    to the database.
			@param clsID IN The class ID
		*/
		virtual void AddClass(ClassID clsID) = 0;

		/** Notify the Content Manager that we are starting to process data
		    that belongs to the specified class.
			@param context IN The ID of the class that owns the data
		*/
		virtual void PushClassContext(ClassID context) = 0;

		/** Notify the Content Manager that we are starting to process data
		    that belongs to the specified implementation.
			@param context IN The ID of the implementation that owns the data
		*/
		virtual void PushImplementationContext(ImplementationID context) = 0;

		/** Notify the Content Manager that we are leaving the most
		    recently established class or implementation context.
		*/
		virtual void PopContext() = 0;
		
		/** Open the specified database for tracking.
		    @param db IN The database
			@param id IN The UID of the database's Content Manager
		*/
		virtual void Open(IDataBase *db, UID id) = 0;

		/** Close the database */
		virtual void Close() = 0;
};


/** This is a stack-based helper class that will push an
    appropriate class or implementation context when constructed
	and pop the context when destructed.
	@see IContentTracker
*/
class ContentTrackerEnabler
{
public:
	/** Establishes a new class context, if possible.
	    @param stream IN The stream being written into
		@param context IN The class context to establish
	*/
	ContentTrackerEnabler(IPMStream *stream, ClassID context)
	{
		fTracker = (IContentTracker *)stream->QueryInterface(IID_ICONTENTTRACKER);
		if (fTracker != nil)
		{
			fTracker->PushClassContext(context);
		}
	}

	/** Establishes a new implementation context, if possible.
	    @param stream IN The stream being written into
		@param context IN The implementation context to establish
	*/
	ContentTrackerEnabler(IPMStream *stream, ImplementationID context)
	{
		fTracker = (IContentTracker *)stream->QueryInterface(IID_ICONTENTTRACKER);
		if (fTracker != nil)
		{
			fTracker->PushImplementationContext(context);
		}
	}

	/** Pops the most recent context, if any.
	*/
	~ContentTrackerEnabler()
	{
		if (fTracker != nil)
		{
			fTracker->PopContext();
			fTracker->Release();
		}
	}

	/** Returns an unreferenced interface pointer to the
	    IContentTracker begin used, if any.
		@return The interface pointer
	*/
	IContentTracker *GetTracker() const
	{
		return fTracker;
	}

private:
	IContentTracker *	fTracker;
};


#endif // __IContentTracker__
