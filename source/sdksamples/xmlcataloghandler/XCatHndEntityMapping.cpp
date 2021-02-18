//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmlcataloghandler/XCatHndEntityMapping.cpp $
//  
//  Owner: Ian Paterson
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
// Interface headers
#include "IPMStream.h"
#include "IXCatHndEntityMapping.h"
// General headers
#include "CPMUnknown.h"
#include <map>
// Project headers
#include "XCatHndID.h"

/** Implements IXCatHndEntityMapping

	@ingroup xmlcataloghandler
*/
class XCatHndEntityMapping : public CPMUnknown<IXCatHndEntityMapping>
{
public:

	/** Constructor
	*/
	XCatHndEntityMapping(IPMUnknown* boss);

	/** Destructor
	*/
	virtual ~XCatHndEntityMapping();

	/**	Add a PUBLIC/URI pair to the mapping
		@param publicID
		@param systemID
	 */
	virtual void AddMapping(const WideString& publicID, const WideString& systemID);

	/**	Retrieve a URI given a PUBLIC identifier
		@param publicID
		@return WideString containing associated URI, empty if none
	 */
	virtual WideString GetUri(const WideString& publicID) const ;

	/**	Return number of items in mapping
		@param none
		@return int32
	 */
	virtual int32 GetMapSize() const;

	/**	Return the PUBLIC identifier (key) at given index
		@param index
		@return WideString
	 */
	virtual WideString GetNthPublicIdentifier(int32 index) const;

	/**	Copy source mapping to this.
		@param srcMapping
	 */
	virtual void Copy(const IXCatHndEntityMapping* srcMapping);

	/** Persistence related method; reads from or writes to given stream
		@param s IN the persistent in and out stream.
		@param prop IN the implementation ID
	*/
	virtual void ReadWrite(IPMStream* s, ImplementationID prop);


	/**	Determine how many xml:base values we know about
		@return int32 giving count of xml:base values we have stored
	 */
	virtual int32 GetXMLBaseCount() const;

	/**	Retrieve the value of an xml:base value we have by index position
		@param n position in list of xml:base values we are storing
		@return WideString containing the xml:base value at given position
	 */
	virtual WideString GetNthXMLBase(int32 n) const;

	/**	Add another xml:base value to the list we are storing
		@param xmlBase to add
	 */
	virtual void AddXMLBase(const WideString& xmlBase);
private:
	std::map<WideString,WideString> fPublicSystemMap;
	K2Vector<WideString>	fXMLBases;

};


CREATE_PERSIST_PMINTERFACE(XCatHndEntityMapping, kXCatHndEntityMappingImpl)

XCatHndEntityMapping::XCatHndEntityMapping(IPMUnknown* boss) :
	CPMUnknown<IXCatHndEntityMapping>(boss)
{
}

XCatHndEntityMapping::~XCatHndEntityMapping()
{

}

/*
*/
void XCatHndEntityMapping::Copy(const IXCatHndEntityMapping* srcMapping)
{
	ASSERT(srcMapping);
	if(!srcMapping) {
		return;
	}

	PreDirty();

	fPublicSystemMap.clear();
	for(int32 i=0; i < srcMapping->GetMapSize(); i++) {
		WideString lhs = srcMapping->GetNthPublicIdentifier(i);
		WideString rhs = srcMapping->GetUri(lhs);
		this->fPublicSystemMap.insert(std::pair<WideString,WideString>(lhs, rhs));
	}
	this->fXMLBases.clear();
	for(int32 j=0; j < srcMapping->GetXMLBaseCount(); j++) {
		this->fXMLBases.push_back(srcMapping->GetNthXMLBase(j));
	}
}

/*
*/
void XCatHndEntityMapping::AddMapping(const WideString& lhs, const WideString& rhs)
{
	if(lhs.CharCount() > 0 && rhs.CharCount() > 0) {
		PreDirty ();
		this->fPublicSystemMap.insert(std::pair<WideString,WideString>(lhs, rhs));

	}
}

/*
*/
WideString XCatHndEntityMapping::GetUri(const WideString& publicID) const
{
	WideString retval;
	std::map<WideString,WideString> :: const_iterator iter = this->fPublicSystemMap.find(publicID);
	if(iter != this->fPublicSystemMap.end()) {
		retval = iter->second;
	}
	return retval;
}

/*
*/
int32 XCatHndEntityMapping::GetMapSize() const
{
	return static_cast<int32>(this->fPublicSystemMap.size());
}

/*
*/
WideString XCatHndEntityMapping::GetNthPublicIdentifier(int32 index) const
{
		std::map<WideString,WideString> :: const_iterator begin = fPublicSystemMap.begin();
		std::map<WideString,WideString> :: const_iterator end = fPublicSystemMap.end();
		std::map<WideString,WideString> :: const_iterator iter = begin;
		if(index < distance(begin, end)) {
			for(int32 i=0; i < index && iter != end; i++, iter++) {
				// NOP
			}
		}

		if(iter != end) {
			return iter->first;
		}
		return WideString("");
}



/*
*/
int32 XCatHndEntityMapping::GetXMLBaseCount() const
{
	return this->fXMLBases.size();
}

/*
*/
WideString XCatHndEntityMapping::GetNthXMLBase(int32 n) const
{
	if(n >=0 && n < this->fXMLBases.size()) {
		return this->fXMLBases[n];
	}
	return WideString("");
}

/*
*/
void XCatHndEntityMapping::AddXMLBase(const WideString& xmlBase)
{
	PreDirty ();
	this->fXMLBases.push_back(xmlBase);

}

/* ReadWrite
*/
void XCatHndEntityMapping::ReadWrite(IPMStream* s, ImplementationID prop)
{
	/*
	//	REMINDER:
	//	If you change the arrangement of persistent data in this method,
	//	remember to update the format number in the PluginVersion resource.
	//	(See the XCatHndID.h file for the plug-in specific format numbers.)
	*/

	//JB TODOX you might need to update the # defined in ID.h to use the new ones defined in SDKDef.h since this plugin is new
	// to firedrake, the format number should be 4.0
	int32 numEntries(0), numBases(0);
	if (s->IsReading())
	{
		s->XferInt32(numEntries);
		for (int32 i = 0; i < numEntries; i++)
		{
			WideString lhs, rhs;
			// Read in from the stream
			lhs.ReadWrite(s);
			rhs.ReadWrite(s);
			// We can't just call our mutators directly from here (as written)
			// as they call PreDirty() on the database
			// which we don't want when we're reading
			if(lhs.CharCount() > 0 && rhs.CharCount() > 0) {
				this->fPublicSystemMap.insert(std::pair<WideString,WideString>(lhs, rhs));
			}

		}
		s->XferInt32(numBases);

		for(int32 j=0; j < numBases; j++) {
			WideString xmlbase;
			xmlbase.ReadWrite(s);
			this->fXMLBases.push_back(xmlbase);
		}


	}
	else
	{
		// We're writing
		numEntries = this->GetMapSize();
		s->XferInt32(numEntries);
		for (int32 i=0; i < numEntries; i++)
		{
			WideString lhs = this->GetNthPublicIdentifier(i);
			WideString rhs = this->GetUri(lhs);
			lhs.ReadWrite(s);
			rhs.ReadWrite(s);

		}

		numBases = this->GetXMLBaseCount();
		s->XferInt32(numBases);
		for(int32 j=0; j < numBases; j++) {
			WideString xmlbase = this->GetNthXMLBase(j);
			xmlbase.ReadWrite(s);
		}


	}
}



//  Code generated by DollyXS code generator
