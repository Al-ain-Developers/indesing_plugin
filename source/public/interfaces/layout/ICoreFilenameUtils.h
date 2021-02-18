//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ICoreFilenameUtils.h $
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
//  ICoreFilenameUtils.h
//  
//========================================================================================

#pragma once
#ifndef __CoreFilenameUtils__
#define __CoreFilenameUtils__

class PMString;
class ICoreFilename;
class NameInfo;

/** ICoreFilenameUtils provides file utilities in a core way.
*/
class ICoreFilenameUtils : public IPMUnknown
{
public:
	/** Method to get the executable's name.
		@param cfn of the executable is returned.
	*/ 
	virtual void GetExecutableName(ICoreFilename *cfn) = 0;
};

#endif // __CoreFilenameUtils__
