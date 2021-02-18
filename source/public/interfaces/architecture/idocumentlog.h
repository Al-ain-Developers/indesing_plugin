//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/idocumentlog.h $
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
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __IDocumentLog__
#define __IDocumentLog__

#include "IEnvironment.h"
#include "IPMUnknown.h"
#include "ISession.h"
#include "ShuksanID.h"
#include "FormatID.h"
#include "LocaleSetting.h"


/**	This interface records a little bit of information about major events that have happened to a document. 
	The document log maintains information about a certain set of events. The document log has 2 sets of information about these events.
	1) It knows whether the document has ever experienced a certain event.
	2) It keeps a list of the most recent events, with additional information about each of them. This list is finite length to avoid growing the log too much.
		This means that you cannot rely on the document log still having information about any particular event. For example, you can't count on using the
		document log to determine what version of InDesign a document was created in, because the creation event may no longer be available.
	
	It's sometimes useful to examine this information when a document is discovered that has some problems. 
	If you open a document in InDesign or InCopy, you can view the document log by holding down cmd/cntrl and bringing up the
	'About InDesign...' or 'About InCopy...' dialog. Click the 'Write Log File' button to get a text file with this log information written to it.
*/
class IDocumentLog : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDOCUMENTLOG };

	enum PlatformType
	{
		kMacintosh = 0,				/** 32 bit on the apple Macintosh platform */
		kWindows = 1,				/** 32 bit on the Microsoft windows platform */
		kMacintoshX64 = 2,			/** 64 bit on the apple Macintosh platform - not used in CS4 or earlier */
		kWindowsX64 = 3,			/** 64 bit on the Microsoft windows platform - new in CS4 - not used in CS3 or earlier */
		
	};

	enum EventType
	{
		/** kFirstEventType not a real event type */
		kFirstEventType = 0,
		/** kNoEvent not a real event type */
		kNoEvent = kFirstEventType,
		/** kRecoveredFile the file was recovered after a crash or power failure */
		kRecoveredFile = 1,
		/** kRecoveredFile the minsave file for this document was recovered after a crash or power failure */
		kRecoveredMiniSave = 2,
		/** kConverted the document was converted from one version to another */
		kConverted = 3,
		/** kOpenACopy a copy of the document was opened */
		kOpenACopy = 4,
		/** kOpenWithMissingPlugins the document was opened with missing plugins */
		kOpenWithMissingPlugins = 5,
		/** kSaveAs the document was saved to a new file*/
		kSaveAs = 6,
		/** kCreated the document was created*/
		kCreated = 7,
		/** kTransfered seems to be obsolete. It's not used. Perhaps it was intended to be used when a document was opened on the opposite platform, but it isn't. */
		kTransfered = 8,
		/** kConvertedFromQXP document was converted from a Quark XPress document */
		kConvertedFromQXP = 9,
		/** kConvertedFromPM document was converted from a PageMaker document */
		kConvertedFromPM = 10,
		/** kBookSync document involved in a book synchronization */
		kBookSync = 11,
		/** kBookSync document involved in a book re pagination */
		kBookRepage = 12,
		/** kConvertedFromINX document was converted from InDesign Interchange format */
		kConvertedFromINX = 13,
		/** kMostRecentSave This event preserves information about the most recent save of the document */
		kMostRecentSave = 14,
		/** kBookUpdateXRef document involved in updating cross-references for book */
		kBookUpdateXRef = 15,
		/** kOpenAClone a clone of the document was opened */
		kOpenAClone = 16,
		/** kContentDropper user made at least one drop */
		kUsedContentDropper = 17,
		/** kUsedLayoutAdjustment user used LA */
		kUsedLayoutAdjustment = 18,
		/** kExportedEPUB2 user made at least one EPUB2 export */
		kExportedEPUB2 = 19,
		/** kExportedEPUB3 user made at least one EPUB3 export */
		kExportedEPUB3 = 20,
		/** DEPRECATED: kExportedSWF user made at least one SWF export */
		//kExportedSWF = 21,
		/** kExportedHTMLFXL user made at least one HTML-Fixed-Layout export */
		kExportedHTMLFXL = 22,
		/** kCreatedInTWS the document was created in touch workspace */
		kCreatedInTWS = 23,
		/** kCreatedInComp the document was created in Comp & sent to ID via IDML route */
		kCreatedInComp = 24,

		/** kLastEventType not a valid event type
		NOTE: Do not simply just add an even without checking the ReadWrite()
		method in DocumentLog.cpp to see if a converter is required.
		*/		
		kLastEventType = 25
	};

	enum LineBreaking
	{
		/** kPlatformLineBreaks platform dependent line endings - "\r" on mac, "\n" on windows */		
		kPlatformLineBreaks,
		/** kCLineBreaks c-style line endings "\n" */		
		kCLineBreaks  
	};

public:
	/** DocEvent class - used to hold the events in the document log.
	*/
	class DocEvent
	{
	public:
	/** Various DocEvent constructors
	*/
		DocEvent()
		{
			fWhat = IDocumentLog::kNoEvent;
		#if defined(MACINTOSH)
			fPlatform = kMacintosh;
		#else
			#if defined(_M_AMD64)
				fPlatform = kWindowsX64;
			#else
				fPlatform = kWindows;			
			#endif
		#endif
			fBuild = 0;
			fSystemMajor = 0;
			fSystemMinor = 0;
			fTimePosted.CurrentTime();
			fAppFS = LocaleSetting::GetLocale().GetFeatureSetId();
		}
		DocEvent(EventType what);
		DocEvent(const DocEvent &other)
		{Copy(other);}
		
	/** Get the event type from this document event.
		@return the event type, i.e. kConverted
	*/
		EventType GetType() const
			{return fWhat;}
			
	/** Get the OS platform type from this document event.
		@return the OS platform type, i.e. kMacintosh
	*/
		PlatformType GetPlatform() const
			{return fPlatform;}

	/** Get the OS version from this document event.
		@return the OS version
	*/
		FormatID GetSystemVersion() const
			{return FormatID(fSystemMajor, fSystemMinor);}
			
	/** Get the highest AUM version of any plugin/library
		@return the  string for the highest AUM version of any plugin/library, i.e. "4.0.1.399"
	*/
		PMString GetHighestVersion() const
			{return fHighestVersionStr;}

	/** Get the feature set from this document event.
		@return the feature set. @see FeatureSets.h
	*/
		int16 GetFeatureSet() const
			{return fAppFS;}
			
	/** Get the build number from this document event.
		@return the build number of the app in use when this event was recorded.
	*/
		int16 GetBuildNumber() const
			{return fBuild;}

	/** Get the time from this document event.
		@return the time when this event was recorded. @see GlobalTime
	*/
		GlobalTime GetEventTime() const
			{return fTimePosted;}

	/** Assignment
	*/
		DocEvent &operator =(const DocEvent &other)
			{Copy(other); return *this;}
			
	/** Read/Write this event from/to the given stream
		@param s the stream to read/write from/to
	*/
		void ReadWrite(IPMStream *s);

	private:
		void Copy(const DocEvent &other);
		
	private:
		EventType					fWhat;
		PlatformType				fPlatform;
		int16						fSystemMajor;
		int16						fSystemMinor;
		int16						fAppFS;
		int16						fBuild;
		GlobalTime					fTimePosted;
		PMString					fHighestVersionStr;
	};

public:		
	/** Set the maximum number of entries that the log will keep
		@param maximumNumberOfEvents how many MRU entries to keep
	*/
	virtual void SetMaxEntries(int32 maximumNumberOfEvents) = 0;

	/**	Returns true if the log has been initialized & written to disk
		@return kTrue if the log has info
	*/
	virtual bool16 InfoIsAvailable() const = 0;

	/**	Add a new event to the log. May remove an old entry to make room for the new one.
		@param what type of new event to record
	*/
	virtual void AddEvent(EventType what) = 0;

	/**	Return the number of events in the log.
		@return count of available events
	*/
	virtual int32 EventCount() const = 0;

	/**	Return the number of events in the log of a certain type
		@param what type of event to count
		@return count of available events of the requested type
	*/
	virtual int32 EventCountOfType(EventType what) const = 0;

	/**	Return the n'th event
		@param i index of the event
		@return kFalse if the nth event was not found, else kTrue
	*/
	virtual bool16 GetEventInfo(int32 i, DocEvent &event) const = 0;

	/**	Return the n'th event of type what.
		@param what type of event to return
		@param i index of the event
		@return kFalse if the nth event of this type was not found, else kTrue
	*/
	virtual bool16 GetEventInfoOfType(EventType what, int32 i, DocEvent &event) const = 0;

	/**	Return true if there have ever been any events of this type. There may be events of
		 this type that were purged out of the log; if so, this will still return true.
		@param what type of event to check for
		@return kFalse if the requested event has never happened to this document. kTrue if it has.
	*/
	virtual bool16 HasHadEvent(EventType what) const = 0;

	/**	Return a human readable version of the log, written out into the stream.
		@param s the stream to write to
		@param lineBreaks the style of linebreaks to put into the stream
	*/
	virtual void SerializeAsEventLog(IPMStream *s, IDocumentLog::LineBreaking lineBreaks) const = 0;

	/**	Return a human readable version of the event type
	*/
	virtual const char* GetEventDescription(EventType what) const = 0;
};

#endif // __IDocumentLog__
