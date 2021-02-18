//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IDatalink.h $
//  
//  Owner: Steve Flenniken
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
//  This file defines an interface for linking to data.  The links UI
//  uses goes through this interface to get all the information it needs
//  about the link.  DataLink.cpp implements this interface for files
//  (Macintosh and Windows files in a core way).  Other implementations
//  could be written.  In the design I planned for URL files (files on 
//  the internet), OLE linked files, and "files" stored in a database.
//  
//  virtual int32 GetNameInfo(NameInfo *ni, PMString *formatName, uint32 *filetype) = 0;
//  GetNameInfo gets the name and type of a link.
//  
//  The ni parameter contains the Name, Volume and DirID that identifies
//  a link.	For Windows file links, name is the complete path name to 
//  the file. For Macintosh file links, name is the filename, Volume is 
//  the volume name	and DirID is the directory id of the file.  
//  
//  The ni object contains the ClassID of the boss that implements this
//  IDataLink interface.  For file links this is kDataLinkBoss.  
//  
//  The formatName parameter is a string that identifies the type of link.
//  This is the type string shown in the links information dialog. For file
//  links the type string is dependent on the filter used to import the
//  data. The string pointer returned is maintained by this interface and 
//  must not be freed.
//  
//  For Macintosh file links, the filetype parameter is the file type. For
//  Windows file links, filetype is 0.
//  
//  All parameters are optional, pass 0 when the information is not needed.
//  
//  The return value is 0 when the routine is successful.
//  
//  virtual StateType GetStoredState(uint64 *size, uint64 *time) = 0;
//  GetStoredState retrieves the link's size, time and state.  These values
//  are	stored with the object.  Size and time are optional, pass 0 when
//  they are not needed.
//  
//  virtual PMString *GetBaseName() = 0;
//  GetBaseName returns a string pointer to a short name that identifies
//  the link. This is the string shown in the links palette. For file
//  links the base name is the filename without any directory information.
//  The string pointer returned is maintained by this interface and must
//  not be freed.
//  
//  virtual PMString *GetFullName() = 0;
//  GetFullName returns a long name that identifies the link.
//  This is the string shown in the links information dialog. For file
//  links the full name is the complete path name.
//  The string pointer returned is maintained by this interface and must
//  not be freed.
//  
//  virtual int32 SetNameInfo(NameInfo *ni, PMString *formatName, uint32 filetype) = 0;
//  Sets the name and type for the link.
//  The return value is 0 when the routine is successful.
//  
//  virtual int32 SetStoredState(uint64 *size, uint64 *time, StateType state) = 0;
//  Sets the size, time and state information that is stored with the object.
//  The size and time parameters are optional, pass 0 and it will not
//  be set.
//  The return value is 0 when the routine is successful.
//  
//  virtual int32 Combine(NameInfo *dirname, NameInfo *newname) = 0;
//  Combine creates new name information for a link by combining
//  the current link's basename with the directory specified by the dirname
//  parameter.
//  Combine is used by the find missing command	to look for missing 
//  links in other directories.
//  The return value is 0 when the routine is successful.
//  
//  virtual bool16 CompareBaseName(NameInfo *ni) = 0;
//  CompareBaseName determines whether the given name information
//  has the same basename as the current link.
//  Compare returns true when ni specifies the same basename.
//  
//  virtual bool16 CompareDirectory(NameInfo *ni) = 0;
//  CompareDirectory determines whether the given directory is
//  the same the the current link.  The return value is true when they
//  are the same.
//  
//  virtual bool16 FindRelative(NameInfo *dirname, NameInfo *newname, ProgressParam *pp) = 0;
//  FindRelative looks for the current link by looking relative to the 
//  given directory.  This operation should be fairly fast.  Searching the 
//  whole disk is currently too slow. 'pp' specifies a callback routine 
//  that should be called to give the user feedback on slow operations.  
//  When the link is found, true is returned and newname is filled in with 
//  its name.
//  
//  virtual StateType GetCurrentState(NameInfo *ni, uint64 *size, uint64 *time, uint32 *filetype, ProgressParam *pp) = 0;
//  GetCurrentState gets the link's size, time and type by looking at the
//  link on disk.  When the ni parameter is 0, the current link is used,
//  otherwise the link specified by ni is used.	'pp' specifies a callback 
//  routine that should be called to give the user feedback on slow operations.
//  If the routine takes a lot of time and the user cancels it, the
//  StateType returned is the stored value (GetStoredState). The progress
//  status (kContinue, kStopProcessing, kSkipItem) is returned in the pp parameter.
//  All parameters are optional, pass 0 when the parameter is not 
//  needed. The	size parameter is the number of bytes of data that the 
//  link represents. The time parameter is the Windows time value, the 
//  number of milliseconds since January 1, 1601, the filetype parameter is
//  the Macintosh file type or 0.  
//  
//  virtual int32 Copy(NameInfo *dirname, ProgressParam *pp) = 0;
//  Copy is used to make a copy of a link in the specified directory.
//  pp' specifies a callback routine that should be called to give 
//  the user feedback on slow operations.
//  The return value is 0 when the routine is successful.
//  
//  Normal names are used where directory parameters are specified.
//  
//========================================================================================

#pragma once
#ifndef __IDATALINK__
#define __IDATALINK__

class NameInfo;
class PMString;

#include "K2Vector.h"
#include "LinksID.h"

/** Progress routine used by potentially slow routines in IDataLink.*/
typedef enum {
	/** Continue processing */
	kContinue = 0,
	/** Stop the slow process */
	kStopProcessing,
	/** Skip the slow item and continue with the next one. */
	kSkipItem
} ProgressStatus;

typedef ProgressStatus ProgressProc(double total, double processed, int32 index, void *data);

/** Parameter to allow callback for potentially slow routines in IDataLink.*/
typedef struct {
	/** ProgressProc callback routine */
	ProgressProc *proc;
	/** Arbitrary data passed to the ProgressProc as data parameter */
	void *data;
	/** Index of link in the links palette, or -1. The ProgressProc index parameter */
	int32 index;
	/** This value is filled and passed back by the routine */
	ProgressStatus status;
} ProgressParam;


/**  This file defines an interface for linking to data.  The links UI
  uses goes through this interface to get all the information it needs
  about the link.  DataLink.cpp implements this interface for files
  (Macintosh and Windows files in a core way).  Other implementations
  could be written.  In the design I planned for URL files (files on 
  the internet), OLE linked files, and "files" stored in a database.
*/
class IDataLink : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDATALINK };

	/** The current (or stored) state of a link. */
	enum StateType {
		/** The link is up-to-date and not missing. */
		kLinkNormal = 0, 
		/** The link has been modified but not updated. */
		kLinkOutOfDate, 
		/** The link could not be found. */
		kLinkMissing, 
		/** The file has been embedded in the InDesign document. */
		kEmbedded};
	
    /** Persistence related method; reads from or writes to given stream
        @param s [IN] the persistent in and out stream.
        @param prop [IN] the implementation ID
    */ 
	virtual void ReadWrite(IPMStream *s, ImplementationID prop) = 0;

	/** Gets the name and type of a link
		@param ni [OUT] The name info to be setup
		@param formatName [OUT] The format name of the linked file 
		@param filetype [OUT] The file type of the linked file
		@return Success or Failure (0 = success)
		*/
	virtual int32 GetNameInfo(NameInfo *ni, PMString *formatName, uint32 *filetype) = 0;

	/** If GetCurrentState takes a lot of time and the user cancels it this method can be used to get the state which was last set.
		@param size [OUT] The number of bytes of data that the link represents(Optional)
		@param time [OUT] The Windows time value, the number of milliseconds since January 1, 1601 (Optional)
		@return  The stored state of this link
		@see GetCurrentState
	*/
	virtual StateType GetStoredState(uint64 *size, uint64 *time) = 0;

	/** Returns a string pointer to a short name that identifies the link. 
		This is the string shown in the links palette. For file links the 
		base name is the filename without any directory information.
		@return The string containing the name of the link. 
		NOTE: The string pointer returned is maintained by this interface and must not be freed.
	*/
	virtual PMString *GetBaseName() = 0;

	/** Returns a long name that identifies the link. This is the string 
		shown in the links information dialog. For file links the full 
		name is the complete path name.
		@return The string containing the name of the link. 
		NOTE: The string pointer returned is maintained by this interface and must not be freed.
	*/
	virtual PMString *GetFullName() = 0;

	/** Sets the name and type for the link.
		@param ni [IN] The information to use when setting up the NameInfo
		@param formatName [IN] The format name for the link
		@param filetype [IN] The file type of the linked file
		@param fullPath [IN] The path to the file
		@return 0 when the routine is successful.
	*/
	virtual int32 SetNameInfo(NameInfo *ni, PMString *formatName, uint32 filetype, const PMString *fullPath = nil) = 0;
	
	/** Sets the size, time and state information that is stored with the object.
		@param size [IN] The number of bytes of data that the link represents (Optional)
		@param time [IN] The Windows time value, the number of milliseconds since January 1, 1601 (Optional)
		@param state [IN] The current state of this link
		@return 0 when the routine is successful.
	*/
	virtual int32 SetStoredState(uint64 *size, uint64 *time, StateType state) = 0;

	/** Creates new name information for a link by combining
		the current link's basename with the directory specified by the dirname
		parameter.	Combine is used by the find missing command	to look for missing 
		links in other directories.
		@param dirname [IN] The directory to prepend to the basename
		@param newName [OUT] The name created by adding dirname to basename
		@return 0 when the routine is successful.
	*/
	virtual int32 Combine(NameInfo *dirname, NameInfo *newname) = 0;

	/** Determines whether the given name information
		has the same basename as the current link.
		@param ni [IN] The NameInfo to compare this link's basename with
		@return kTrue when ni specifies the same basename.
	*/
	virtual bool16 CompareBaseName(NameInfo *ni) = 0;

	/**	Determines whether the given directory is the same the the current link.
		@param ni [IN] The NameInfo to compare this link's directory with
		@return  kTrue when ni specifies the same directory.
	*/
	virtual bool16 CompareDirectory(NameInfo *ni) = 0;

	/**	Looks for the current link by looking relative to the given directory. 
		This operation should be fairly fast. Searching the	whole disk is currently 
		too slow. 
		@param dirname [IN] The original nameinfo of the file we are looking for
		@param newname [OUT] Filled with the new name of a link if it is found
		@param pp Specifies a callback routine that should be called to give the user feedback on slow operations 
		@return kTrue indicates that the link was found.
	*/
	virtual bool16 FindRelative(NameInfo *dirname, NameInfo *newname, ProgressParam *pp) = 0;

	/**	GetCurrentState gets the link's size, time and type by looking at the link on disk.
		@param ni [OUT] The link to get info on. If this is 0 the current link will be used
		@param size [OUT] The number of bytes of data that the link represents
		@param time [OUT] The Windows time value, the number of milliseconds since January 1, 1601
		@param filetype [OUT] The Macintosh file type or 0
		@param pp Specifies a callback routine that should be called to give the user feedback on slow operations
		@return The current state of this link
		@see GetStoredState
	*/
	virtual StateType GetCurrentState(NameInfo *ni, uint64 *size, uint64 *time, uint32 *filetype, ProgressParam *pp) = 0;

	/**	Used to make a copy of a link in the specified directory.
		@param dirname [OUT] Will be filled with the link information
		@param pp specifies a callback routine that should be called to give the user feedback on slow operations.
		@return 0 when the routine is successful.
	*/
	virtual int32 Copy(NameInfo *dirname, ProgressParam *pp) = 0;
};
DECLARE_BASE_TYPE(IDataLink::StateType);

typedef K2Vector<IDataLink *> DataLinkPtrCollection;

#endif // __IDATALINK__
