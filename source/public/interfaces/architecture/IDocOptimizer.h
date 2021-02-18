//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IDocOptimizer.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __IDocOptimizer__
#define __IDocOptimizer__

#include "IPMUnknown.h"
#include "DocumentID.h"

class IDocument;
class PMString;
class ProgressBarAccessor;
class ICommand;

/*
	The IDocOptimizer is used in ServicerImportProvider.cpp for optimizing text wrap of imported Quark documents.
	For more details see my build notes for change list 14893, job000799 from 05/11/1999:

	Integration of Quark Import Wrap Optimizer

	I created a new interface IDocOptimizer, that is used by the ServicerImportProvider
	after the document is imported. Only the QX3Reader and QX4Reader support IDocOptimizer.
	They use the ZOrderWrapOptimizer implementation which is provided by the StandOff 
	plugin. The source for ZOrderWrapOptimizer is basically the old test menu code that
	has been tested by QA. I only added support for the progress bar.
	The text that shows up during ZOrderWrapOptimizer::CreateOptimizeCommand() is:
	"Converting text wrap...".	
*/

/**
	IDocOptimizer is used by the ServicerImportProvider for optimizing text wrap of Quark documents 
	after the document is imported. Only the QX3Reader and QX4Reader support IDocOptimizer. 
	They use the ZOrderWrapOptimizer implementation which is provided by the StandOff plugin. 
	The text that shows up during ZOrderWrapOptimizer::CreateOptimizeCommand() is: "Converting text wrap...".	
*/
class IDocOptimizer : public IPMUnknown
{
	public:
	
		enum { kDefaultIID = IID_IDOCOPTIMIZER };
	
		/**
			Returns the parent file URL of a file URL.
			@param pDocument IN. Document to optimize.
			@param pFlags optional IN. Optimization flags, free format.
			@return nil or optimizer command. Returned ICommand is addref'ed.
		*/
		virtual ICommand *CreateOptimizeCommand( IDocument *pDocument, const PMString *pFlags = nil ) const = 0;
};

#endif	//__IDocOptimizer__


