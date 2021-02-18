//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IDirectoryUtility.h $
//  
//  Owner: Robin_Briggs
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
#ifndef __IDIRECTORYUTILITY__
#define __IDIRECTORYUTILITY__
#include <boost/function.hpp>
/**
 Utility interface that iterates over a set of paths and returns the files contained
 by the paths.  The returned files may be filtered by a given filtering/match
 function.

 Note: aliases are resolved on the Mac, but shortcuts are NOT resolved on Windows.
 @see IDFile
 @see SysFileInfo
 */
class IDirectoryUtility	
{
public:
	/**
	 The caller may supply a filter function that filters files before
	 they are returned from Next. Only files that match will be returned.
	 */
	typedef ::boost::function1<bool16, IDirectoryUtility*> FileMatch;

	static bool16 DefaultFileMatchFun( IDirectoryUtility* ) {return kTrue;}
	/**
	 Constructor.
	 Constructs an IDirectoryUtility object.
	 @param matchFunc	IN Function used to filters file.
	 */
	IDirectoryUtility( FileMatch matchFunc ) :
		fMatchFunction( matchFunc ) {}
	
	/**
	 Destructor.
	 Destroys the IDirectoryUtility object.
	 */
	virtual ~IDirectoryUtility() { }

	/**
	 Add a new path to the list of items that will be iterated.
	 @param fileSpec	IN Path to add; may be a path to a directory or file.
	 */
	virtual void AddPath(const IDFile& fileSpec) = 0;
	
	/**
	 Test if the current file is a match.
	 @return kTrue the current file is a match, else kFalse.
	 */
	bool16 IsMatch()
		{ return (fMatchFunction)( this ); }
		
	/**
	 Gets the first matching file.
	 @param resultFile	OUT Pointer to an existing IDFile object that
							is set to the first matching file.
	 @return kTrue if a file was found, else kFalse.
	 */
	virtual bool16 First(IDFile *resultFile) = 0;

	/**
	 Gets next file matching file.
	 @param resultFile	OUT Pointer to an existing IDFile object that
							is set to the next matching file.
	 @return kTrue if a file was found, else kFalse.
	 */
	virtual bool16 Next(IDFile *resultFile) = 0;

	/**
	 Gets the current matching file.
	 @param resultFile	OUT Pointer to an existing IDFile object that
							is set to the current matching file.
	 @return kTrue if a file was found, else kFalse.
	 */
	virtual bool16 CurrentMatchFile(IDFile *resultFile) const = 0;

	/**
	 Callback parameter class used in ForEachFileInFolder().
	*/
	class OnSysFileFunction
	{
	public:
		virtual	bool16 OnSysFile( const IDFile &nextFile, int32 nthFile ) = 0 ;
	};

	/**
	 Iterates all the files in the files and folders added to this object
	 and calls onSysFile on them.
	 @param onSysFile	IN Class containing OnSysFile function to call.
	 */
	virtual void ForEachFileInFolder( OnSysFileFunction& onSysFile ) = 0 ;

	protected:
		/**
		 Function used to test for matching files.
		 */
		FileMatch fMatchFunction ;
};


#endif // __IDIRECTORYUTILITY__
