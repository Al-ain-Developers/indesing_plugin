//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CConversionProvider.h $
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
//  ADOBE CONFIDENTIAL
//  
//  Purpose of Interface:
//  Helper base class for writing file format converters.
//  
//  Interfaces -----
//  
//========================================================================================

#include "IConversionProvider.h"

// ----- Includes -----

#include "CPMUnknown.h"
#include "K2Vector.h"

// ----- ID.h files -----

#include "VersionID.h"


#pragma once


//---------------------------------------------------------------------------------------
//	CConversionProvider
//---------------------------------------------------------------------------------------

/** This class provides a useful base implementation of IConversionProvider. It handles
    most of the details of the rather complex interaction between IConversionMgr and
	IConversionProvider. A fully functional conversion provider can be written by 
	using the protected methods of this class to define the equivalent of Schema Directives
	and the overriding key IConversionProvider methods to perform data-based conversions.

	The public methods in this class are uncommented because they are documented in
	IConversionProvider.
	@see IConversionMgr
	@see IConversionProvider
*/
class  PUBLIC_DECL CConversionProvider : public CPMUnknown<IConversionProvider>
{
public:
	CConversionProvider(PluginID plugin, IPMUnknown *boss);
	virtual ~CConversionProvider();
	
	virtual int32 CountConversions() const = 0;
	virtual void GetNthConversion(int32 n, VersionID *fromVersion, VersionID *toVersion) const = 0;

	virtual int32 CountRemovedPlugins(const VersionID &fromVersion, const VersionID &toVersion) const;
	virtual PluginID GetNthRemovedPlugin(const VersionID &fromVersion, const VersionID &toVersion, int32 n) const;
	virtual int32 CountIgnoredPlugins(const VersionID &fromVersion, const VersionID &toVersion) const;
	virtual PluginID GetNthIgnoredPlugin(const VersionID &fromVersion, const VersionID &toVersion, int32 n) const;
	
	virtual int32 CountClassAliases() const;
	virtual int32 CountImplementationAliases() const;
	virtual void GetNthClassAlias(int32 n, ClassID &fromID, VersionID &fromVersion, ClassID &toID, VersionID &toVersion) const;
	virtual void GetNthImplementationAlias(int32 n, ImplementationID &fromID, VersionID &fromVersion, ImplementationID &toID, VersionID &toVersion) const;

	virtual int32 CountPlugins() const;
	virtual PluginID GetNthPlugin(int32 n) const;

	virtual bool16 DoesConversionRenumberClass(int32 conversionIndex) const;
	virtual bool16 DoesConversionRenumberImplementation(int32 conversionIndex) const;

	virtual IConversionProvider::ConversionStatus ShouldConvertImplementation(ImplementationID tag, ClassID context, int32 conversionIndex) const;
	virtual IConversionProvider::ConversionStatus ShouldConvertClass(ClassID clsID, ImplementationID context, int32 conversionIndex) const;

	virtual ImplementationID ConvertTag(ImplementationID tag, ClassID forClass, int32 conversionIndex, 
	                                    int32 inLength, IPMStream *oldData, IPMStream *newData, IterationStatus whichIteration);

	virtual ClassID ConvertClass(ClassID clsID, ImplementationID embeddedContext, int32 conversionIndex, 
	                             int32 inLength, IPMStream *oldData, IPMStream *newData, IterationStatus whichIteration);

protected:
	/** For use by subclasses to tell us when an implementation has been removed from a class.
	    @param implID IN Which implementation is being removed
		@param classID IN From which class
		@param majorFormat IN As of this major format number
		@param minorFormat IN and this minor format number
	*/
	void RemoveImplementation(ImplementationID implID, ClassID classID, int32 majorFormat, int32 minorFormat);

	/** For use by subclasses to tell us when a class has been removed.
		@param classID IN Which class is being removed
		@param majorFormat IN As of this major format number
		@param minorFormat IN and this minor format number
	*/
	void RemoveClass(ClassID classID, int32 majorFormat, int32 minorFormat)
		{RemoveImplementation(kInvalidImpl, classID, majorFormat, minorFormat);}

	/** For use by subclasses to tell us when a plugin has been removed.
		@param classID IN Which plugin is being removed
		@param majorFormat IN As of this major format number
		@param minorFormat IN and this minor format number
	*/
	void RemovePlugin(PluginID plugin, int32 majorFormat, int32 minorFormat);

	/** For use by subclasses to tell us when a plugin's priority should be set to "Ignored".
		@param classID IN Which plugin is being ignored
		@param majorFormat IN As of this major format number
		@param minorFormat IN and this minor format number
	*/
	void IgnorePlugin(PluginID plugin, int32 majorFormat, int32 minorFormat);
	
	/** For use by subclasses to tell us when a class has moved from another plugin.
	    It is implied that the class is moving to the plugin that contains this conversion provider.
	    @param fromClass IN Which class is being moved
		@param fromPlugin IN From which plugin
		@param fromMajorFormat IN The old plugin's major format number at the time of the move
		@param fromMinorFormat IN and its minor format number
		@param toClass IN The new class ID
		@param toMajorFormat IN This plugin's major format number at the time of the move
		@param toMinorFormat IN and its minor format number
	*/
	void MoveClass(ClassID fromClass, PluginID fromPlugin, int32 fromMajorFormat, int32 fromMinorFormat,
		           ClassID toClass, int32 toMajorFormat, int32 toMinorFormat);
	
	/** For use by subclasses to tell us when an implementation has moved from another plugin.
	    It is implied that the implementation is moving to the plugin that contains this conversion provider.
	    @param fromImpl IN Which implementation is being moved
		@param fromPlugin IN From which plugin
		@param fromMajorFormat IN The old plugin's major format number at the time of the move
		@param fromMinorFormat IN and its minor format number
		@param toImpl IN The new implementation ID
		@param toMajorFormat IN This plugin's major format number at the time of the move
		@param toMinorFormat IN and its minor format number
	*/
	void MoveImplementation(ImplementationID fromImpl, PluginID fromPlugin, int32 fromMajorFormat, int32 fromMinorFormat,
		                    ImplementationID toImpl, int32 toMajorFormat, int32 toMinorFormat);

private:
	static bool InRange(const VersionID &fromV, const VersionID &testV, const VersionID &toV)
		{return ((testV > fromV) && (testV <= toV));}

private:
	/** Private utility class - Stores information about implementation that this
	    conversion provider handles.
	*/
	class ImplInfo
	{
	public:
		typedef base_type data_type;
		ImplInfo()
			: fImplID(kInvalidImpl), fBossID(kInvalidClass), fFormat()
			{}
		ImplInfo(ImplementationID implID, ClassID bossID, const FormatID &format)
			: fImplID(implID), fBossID(bossID), fFormat(format)
			{}
		ImplInfo(const ImplInfo &other)
			: fImplID(other.fImplID), fBossID(other.fBossID), fFormat(other.fFormat)
			{}

		ImplementationID GetImplementation() const
			{return fImplID;}
		ClassID GetBoss() const
			{return fBossID;}
		const FormatID &GetFormat() const
			{return fFormat;}

		bool operator==(const ImplInfo &other) const
			{return((fImplID == other.fImplID) && (fBossID == other.fBossID) && (fFormat == other.fFormat));}

	private:
		ImplementationID	fImplID;		// Which Implementation was added or removed
		ClassID				fBossID;		// Boss was it added or removed to/from
		FormatID			fFormat;		// Format number when the implementation was added/removed
	};


	/** Private utility class - Stores information about plugins that this
	    conversion provider handles.
	*/
	class PluginInfo
	{
	public:
		typedef base_type data_type;

		PluginInfo()
			: fPlugin(kInvalidPlugin), fFormat()
			{}
		PluginInfo(PluginID plugin)
			: fPlugin(plugin), fFormat()
			{}
		PluginInfo(PluginID plugin, const FormatID &format)
			: fPlugin(plugin), fFormat(format)
			{}
		PluginInfo(const PluginInfo &other)
			: fPlugin(other.fPlugin), fFormat(other.fFormat)
			{}

		PluginID GetPlugin() const
			{return fPlugin;}
		const FormatID &GetFormat() const
			{return fFormat;}

		bool16 operator==(const PluginInfo &other) const
			{return (fPlugin == other.fPlugin);}

	private:
		PluginID	fPlugin;			// Removed plugin
		FormatID 	fFormat;			// Format number when it was removed
	};


	/** Private utility class - Stores information about class and implementation
	    alias conversions that this conversion provider handles.
	*/
	template <class T>
	class AliasInfo
	{
	public:
		typedef base_type data_type;
		
		AliasInfo(T fromID, const VersionID &from, T toID, const VersionID &to)
			: fFromID(fromID), fFromVersion(from), fToID(toID), fToVersion(to)
			{}
		
		T GetFromID() const
			{return fFromID;}
		T GetToID() const
			{return fToID;}
		const VersionID &GetFromVersion() const
			{return fFromVersion;}
		const VersionID &GetToVersion() const
			{return fToVersion;}
			
		bool operator ==(const AliasInfo &other) const
			{return (fFromID == other.fFromID) && (fFromVersion == other.fFromVersion) &&
			        (fToID == other.fToID) && (fToVersion == other.fToVersion);}
			
	private:
		T			fFromID;			// Former Class or Implementation ID
		VersionID	fFromVersion;		// Where did the ID move from?
		T			fToID;				// New Class or Implementation ID
		VersionID	fToVersion;			// Where did it move to?
	};

	typedef	K2Vector<ImplInfo>				ImplInfoVector;
	typedef AliasInfo<ClassID>				ClassAliasInfo;
	typedef	K2Vector<ClassAliasInfo>		ClassAliasVector;
	typedef AliasInfo<ImplementationID>		ImplAliasInfo;
	typedef	K2Vector<ImplAliasInfo>			ImplAliasVector;
	typedef	K2Vector<PluginInfo>			PluginInfoVector;

private:
	PluginID			fPlugin;
	ImplInfoVector		fImplList;
	ClassAliasVector	fClassAliasList;
	ImplAliasVector		fImplAliasList;
	PluginInfoVector	fRemoveList;
	PluginInfoVector	fIgnoreList;
};


