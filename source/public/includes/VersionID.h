//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/VersionID.h $
//  
//  Owner: Robin Briggs
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
//  Purpose of Interface:
//  Specifies version numbers for file format conversion.
//  
//========================================================================================

#ifndef __VersionID__
#define __VersionID__

// ----- Interfaces -----

#include "IPMStream.h"

// ----- ID.h files -----

#include "FormatID.h"


#pragma export on
class PUBLIC_DECL VersionID : public FormatID
{
public:
   	typedef base_type data_type;

	VersionID() :
		FormatID(),
		fPluginID(kInvalidPlugin)
		{}
	VersionID(PluginID plugInID, const FormatID &format) :
		FormatID(format),
		fPluginID(plugInID)
		{}		
	VersionID(PluginID plugInID, int32 majorNumber, int32 minorNumber) :
		FormatID(majorNumber, minorNumber),
		fPluginID(plugInID)
		{}
	VersionID(IPMStream *s)
		: FormatID()
		{if (s->IsReading()) ReadWrite(s);}

	PluginID GetPluginID() const
		{ return fPluginID; }
	void SetPluginID(PluginID id)
		{fPluginID = id;}

	void SetFormat(const FormatID &format)
		{SetMajorVersion(format.GetMajorVersion()); SetMinorVersion(format.GetMinorVersion());}
		
	bool16 PluginMatches(const VersionID& other) const
		{return (fPluginID == other.fPluginID) || (fPluginID == kInvalidPlugin) || (other.fPluginID == kInvalidPlugin);}

	bool16 operator <(const VersionID& other) const
		{return PluginMatches(other) ? (((FormatID)*this) < (FormatID)other) : (fPluginID < other.fPluginID);}
	bool16 operator >(const VersionID& other) const
		{return PluginMatches(other) ? (((FormatID)*this) > (FormatID)other) : (fPluginID > other.fPluginID);}
	bool16 operator ==(const VersionID& other) const
		{return PluginMatches(other) ? (((FormatID)*this) == (FormatID)other) : (fPluginID == other.fPluginID);}
	bool16 operator !=(const VersionID& other) const
		{return !(*this == other);}		
	bool16 operator <=(const VersionID& other) const
		{return !(*this > other);}
	bool16 operator >=(const VersionID& other) const
		{return !(*this < other);}
		
	void ReadWrite(IPMStream *s)
		{FormatID::ReadWrite(s);
		 s->XferInt32((int32 &)fPluginID);}

private:
	PluginID	fPluginID;
};
#pragma export off

#endif // __VersionID__

