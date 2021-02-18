//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/IndexTopicEntryNode.h $
//  
//  Owner: Michel Hutinel
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
//  comments: Data class to carry one Index Topic entry node.
//  
//========================================================================================

#pragma once
#ifndef __INDEXTOPICENTRYNODE__
#define __INDEXTOPICENTRYNODE__

#include "WideString.h"
#include "LanguageID.h"
#ifdef qME
#include "IIndexHeaderSet.h"
#include "PreferenceUtils.h"
#endif

/** Models a topic node with all it's properties.
	A topic node has a level, display string, sort string and a language.
	The display string is the string that will show up in the index.
	The sort string is used in the topic sorting process.
	The language specifies the language of this topic.
*/
class IndexTopicEntryNode
{
	public:
		typedef object_type data_type;

		/** Constructs an empty topic node.
		*/
#ifdef qME
		IndexTopicEntryNode():
			fLevel()
			{
				InterfacePtr<const IIndexHeaderSet> pPrefsTopicListHeaderSet((IIndexHeaderSet*)::QuerySessionPreferences(IID_IINDEXHEADERSET));
				fLanguage = pPrefsTopicListHeaderSet->GetLanguageID();
			}
#else
		IndexTopicEntryNode():
			fLevel(),
			fLanguage(kLanguageUserDefault)
			{}
#endif

		/** Equality test operator.
		*/
		bool16 operator==(const IndexTopicEntryNode& other) const
		{
			// We don't compare fIndexEntryList
			return ( (fLevel == other.fLevel) && 
				     (fDisplayString == other.fDisplayString) && 
				     (fSortString == other.fSortString) &&
					 (fLanguage == other.fLanguage)); 
		}

		/** Assignment operator.
		*/
		IndexTopicEntryNode& operator=(const IndexTopicEntryNode& other)
		{
			if (this != &other)
			{
				fLevel = other.fLevel;
				fDisplayString = other.fDisplayString;
				fSortString = other.fSortString;
				fLanguage = other.fLanguage;	
			}
			return *this;
		}

		/** Accessor for the sort string.
			@return the sort string for this topic node.
		*/
		const WideString& GetSortString() const
		{
			return (fSortString.Length() != 0 ? fSortString : fDisplayString);
		}

		/** Accessor for the sort language.
			@return the sort language.
		*/
		const LanguageID& GetSortLanguage() const
		{
			return fLanguage;
		}

		/** Accessor for the level property.
			@return the level for this topic.
		*/
		const int16 & GetLevel() const { return fLevel;} ;

		/** Accessor for the level property.
			@return a modifiable reference to the level property.
		*/
		int16 & GetLevel() { return fLevel;} ;
		
		/** Accessor for the display string property.
			@return a modifiable reference to the display string.
		*/
		WideString & GetDisplayString() {return fDisplayString;} ;

		/** Accessor for the display string property.
			@return the display string.
		*/
		const WideString & GetDisplayString() const {return fDisplayString;} ;
		
		/** Accessor for the sort language property.
			@return a modifiable reference to the sort language.
		*/
		LanguageID & GetLanguage() {return fLanguage;} ;

		/** Accessor for the sort language property.
			@return the sort language for this topic node.
		*/
		const LanguageID & GetLanguage() const { return fLanguage;};
		
		/** Accessor for the sort string property.
			@return a modifiable reference to the sort string.
		*/
		WideString & GetSortStringReference() {return fSortString;};

		/** Accessor for the sort string property.
			@return the sort string for this topic node.
		*/
		const WideString & GetSortStringReference() const {return fSortString;};

protected:
		int16			fLevel;				// Level of the Node
		WideString		fDisplayString;		// String used to display the topic
		WideString		fSortString;		// String used to sort the topic
		LanguageID		fLanguage;			// Language of topic
};

#endif // __INDEXTOPICENTRYNODE__