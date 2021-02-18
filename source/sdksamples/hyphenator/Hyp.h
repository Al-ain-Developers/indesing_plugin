//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hyphenator/Hyp.h $
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

#ifndef __Hyp_h__
#define __Hyp_h__

#include "KeyValuePair.h"
class ILanguage;

/** Data types used by the Hyphenator plug-in to implement hyphenation.

@ingroup hyphenator
 */
namespace Hyp {
	/** Collection of hyphenation service boss objects (kHypHyphenationServiceBoss).
		A reference to the language (ILanguage) interface is maintained because the
		hyphenation manager (IHyphenationMgr, HypHyphenationMgr) locate services
		by language.
	 */
	typedef	K2Vector<InterfacePtr<ILanguage> >			HyphenationServices;

	/** Index in a word to a hyphenation point. 
		A hyphen index is the position before the hyphen.
		For example to indicate that the word kitten is hyphenated
		between the t's (kit-ten) it's hyphen index would be 2.
	 */
	typedef int32										HyphenIndex;

	/** The quality measure for a hypenation point takes
		one of the values given in IHyphenatedWord, kRegularHyphenPoint,
		kDiscretionaryHyphenPoint etc.
	 */
	typedef int32										HyphenQuality;

	/** Hypenation point represented as an index/quality pair
		with lookup by hyphen index (HyphenIndex).
	 */
	typedef	KeyValuePair<HyphenIndex, HyphenQuality>	HyphenationPoint;

	/** Collection of the hyphenation points for a word.
	 */
	typedef	K2Vector<HyphenationPoint>					HyphenationPoints; 
}

#endif // __Hyp_h__

// End, Hyp.h.


