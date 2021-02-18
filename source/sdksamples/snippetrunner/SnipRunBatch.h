//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/SnipRunBatch.h $
//  
//  Owner: Adobe Developer Technologies
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

#ifndef _SnipRunBatch_
#define _SnipRunBatch_

// Interface includes:

#include "IPMStream.h"

// Forward declarations:
class PMString;

/**	This feature has been disabled.

	Snippet script handler processes text files containing lines of snippet commands.
	For example a file containing the lines:
	;
	; Snippet Runner script file
	;
	newDoc 400 300
	placeFile myPic.gif

	would create a new document and place a file into it. 
	
	Characters following a ';' are ignored and can be used to comment scripts.
	Blank lines are ignored.

	@ingroup snippetrunner
	
*/
class SnipRunBatch
{
public:
	/**
		Pops a file browse dialog and handles the commands found in the selected script.
	*/
	SnipRunBatch();
	/** Destructor */
	virtual ~SnipRunBatch() {};
private:
	InterfacePtr<IPMStream> fStream;
	IDFile fSysFile;

private:
	/** Browse */
	ErrorCode Browse();

	/** OpenFileDialog */
	ErrorCode OpenFileDialog(IDFile& file);

	/** Handle */
	void Handle(void);

	/** GetLine */
	ErrorCode GetLine(PMString& line);

	/** GetSnippetNameAndParams */
	void GetSnippetNameAndParams(const PMString& line, PMString& snippetName, PMString& params);

	/** GetAbsolutePath */
	void  GetAbsolutePath(const IDFile& spec, PMString& name);

	/** Appends path separator to supplied path (: on Mac, \ on Win) 
	*/
	void AppendPathSeparator(PMString& path);

	/** takes the last element from the pathname described by fromthis.
		So "\this\that\file" becomes "\this\that"
		@param fromthis the string to be truncated by a path element.
	*/
	void RemoveLastElement(PMString& fromthis);

private:
	PMString fSnipRunPath;
};



#endif // _SnipRunBatch_


