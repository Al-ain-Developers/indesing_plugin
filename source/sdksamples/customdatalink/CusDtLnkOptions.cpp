//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/CusDtLnkOptions.cpp $
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

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IPMStream.h"
#include "ICusDtLnkOptions.h"

// General includes:
#include "CPMUnknown.h"

#include <map>


/** Class to persist a list of options to the session workspace.
	CusDtLnkOptions is a persistent implementation of interface ICusDtLnkOptions.
	@ingroup customdatalink
*/
class CusDtLnkOptions : public CPMUnknown<ICusDtLnkOptions>
{
public:
	/**	Constructor.
		@param boss IN interface ptr from boss object on which this interface is aggregated.
	*/
	CusDtLnkOptions(IPMUnknown* boss);

	/** Destructor
	*/
	virtual ~CusDtLnkOptions() {}

	/** See ICusDtLnkOptions::AddKeyValuePair
	*/
	virtual void AddKeyValuePair(const WideString& key, const WideString& val);

	/**	See ICusDtLnkOptions::GetValueFromKey
	 */
	virtual WideString GetValueFromKey(const WideString& key) const;

	/** See ICusDtLnkOptions::GetKeyValuePairCount
	*/
	virtual int32 GetKeyValuePairCount() const { return static_cast<int32>(fMap.size()); }

	/** See ICusDtLnkOptions::GetNthKey
	*/
	virtual WideString GetNthKey(const int32 index) const;

	/** Persistence related method; reads from or writes to given stream
		@param s IN the persistent in and out stream.
		@param prop IN the implementation ID
	*/
	virtual void ReadWrite(IPMStream* s, ImplementationID prop);

private:

	std::map<WideString,WideString> fMap;
};

/*	CREATE_PERSIST_PMINTERFACE
	This macro creates a persistent class factory for the given class name
	and registers the ID with the host.
*/
CREATE_PERSIST_PMINTERFACE(CusDtLnkOptions, kCusDtLnkOptionsImpl)

/*	Constructor
	The preference state is set to kFalse for the application
	workspace. The preference state for a new document is set
	to the application preference state.
*/
CusDtLnkOptions::CusDtLnkOptions(IPMUnknown* boss) : CPMUnknown<ICusDtLnkOptions>(boss)
{
}

/*
*/
void CusDtLnkOptions::AddKeyValuePair(const WideString& key, const WideString& val)
{
	// Allow empty vals to be stored
	if(key.CharCount() > 0) {
		PreDirty ();
		// Remove an existing option with given key...
		// it doesn't overwrite with a new option if you don't,ut:
		// see http://www.sgi.com/tech/stl/UniqueAssociativeContainer.html
		std::map<WideString, WideString> :: iterator iter =
				this->fMap.find(key);
		if(iter != this->fMap.end()) {
			this->fMap.erase(iter);
		}

		this->fMap.insert(
				std::pair<WideString,WideString>(key, val));

     }

}

/*
*/
WideString CusDtLnkOptions::GetValueFromKey(const  WideString& key) const
{
	WideString retval;
	std::map<WideString, WideString> :: const_iterator iter =
		this->fMap.find(key);
	if(iter != this->fMap.end()) {
		retval = iter->second;
	}
return retval;

}

/*
*/
WideString CusDtLnkOptions::GetNthKey(int32 index) const
{
		std::map<WideString,WideString> :: const_iterator begin = this->fMap.begin();
		std::map<WideString,WideString> :: const_iterator end = this->fMap.end();
		std::map<WideString,WideString> :: const_iterator iter = begin;
		// Iterate the keys in the map, only as far as we need to.
		// API docs for std::map at http://www.sgi.com/tech/stl/Map.html
		if(index < std::distance(begin, end)) {
			for(int32 i=0; i < index && iter != end; i++, iter++) {
				TRACE("CusDtLnkOptions::GetNthKey: %d\n", i);
			}
		}

		if(iter != end) {
			return iter->first;
		}
		return WideString("");
}

/*
*/
void CusDtLnkOptions::ReadWrite(IPMStream* s, ImplementationID prop)
{
	/*
	//	REMINDER:
	//	If you change the arrangement of persistent data in this method,
	//	remember to update the format number in the PluginVersion resource.
	//	(See the CusDtLnkID.h file for the plug-in specific format numbers.)
	*/
	int32 numOptions;
	if (s->IsReading())
	{
		s->XferInt32(numOptions);
		for (int32 i = 0; i < numOptions; i++)
		{
			WideString k,v;
			// Read in from the stream
			k.ReadWrite(s);
			v.ReadWrite(s);
			// If entry exists, remove it, so we get the stored value
			std::map<WideString, WideString> :: iterator iter =
				this->fMap.find(k);
			if(iter != this->fMap.end()) {
				this->fMap.erase(iter);
			}
			this->fMap.insert(
				std::pair<WideString,WideString>(k, v));
		}
	}
	else
	{
		numOptions = static_cast<int32>(fMap.size());
		s->XferInt32(numOptions);
		std::map<WideString,WideString>::const_iterator iter;
		for(iter = this->fMap.begin();
			iter != this->fMap.end(); iter++) {
				WideString k = iter->first;
				WideString v = iter->second;
				// Write to stream
				k.ReadWrite(s);
				v.ReadWrite(s);
		}


	}
}

// End, CusDtLnkOptions.cpp.
