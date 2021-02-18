//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/SnpReferenceMacros.h $
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

#ifndef _SnpReferenceMacros_
#define _SnpReferenceMacros_

// ipaterso Fix Watson 1086461
// This is based on the pattern that CUnitTest used, except adapted
// so that we don't need to add into the xxxNoStrip.cpp of SnippetRunner itself
// each time we add a snippet.

// On the Mac, we cannot guarantee that the linker won't attempt to deadstrip
// static initialization code (as sometimes all project settings are updated at once),
// the only way can be sure our static instances of
// SnpRunnable derived classes don't get stripped is to create an artifical
// reference to them
// To Snippet CPP file, add DEFINE_SNIPPET(_SnpRunnerWhateverSnippetName)
// To SnpRunNoStrip.cpp file, add REFERENCE_SNIPPET(_SnpRunnerWhateverSnippetName)


#define DEFINE_SNIPPET(Class)			\
	void ReferenceSnp##Class();				\
	void ReferenceSnp##Class() {			\
		Class snp;							\
	}

#define REFERENCE_SNIPPET(Class)		\
	void ReferenceSnp##Class();				\
	ReferenceSnp##Class()


#endif // SnpReferenceMacros

// End, SnpReferenceMacros.h

