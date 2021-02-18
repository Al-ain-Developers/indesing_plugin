//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/SchemaUtils.h $
//  
//  Owner: Steve Pellegrin
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
//  Adobe patent application tracking # P409, entitled 'Schema-based file Conversion',
//  inventors: Robin Briggs, Steve Pellegrin
//  
//========================================================================================

#pragma once
#if !defined(__SchemaUtils__)
#define __SchemaUtils__

// ----- Includes -----

#include <algorithm>
#include <cmath>
#include "K2Vector.h"
#include "SchemaTypes.h"
#include "SimpleLink.h"
#include <map>

// ----- ID.h files -----

#include "FormatID.h"
#include "VersionID.h"


class IPMStream;
class NameInfo;
class PMMatrix;
class PMPoint;
class PMReal;
class PMRect;
class PMString;
class WideString;
class URI;
struct IDResource;


namespace Schemas
{
	//========================================================================================
	//	TYPE DEFINITIONS
	//========================================================================================
	typedef	K2Vector<ClassID>						ClassIDVector;
	typedef	K2Vector<ImplementationID>				ImplIDVector;
	typedef	K2Vector<int32>							MajorFormatVector;
	typedef	K2Vector<PluginID>						PluginVector;
	class Version;
	typedef K2Vector<Version>						VersionVector;
	class SchemaInfo;
	typedef	K2Vector<SchemaInfo>					SchemaInfoVector;
	class IteratorSchemaInfo;
	typedef	K2Vector<IteratorSchemaInfo>			IteratorSchemaInfoVector;
	class PathStep;
	typedef	K2Vector<PathStep>						PathStepVector;
	class Implementation;
	typedef	K2Vector<Implementation>				ImplVector;
	class Field;
	typedef K2Vector<Field>							FieldVector;
	class FieldValue;
	typedef K2Vector<FieldValue>					ValueVector;
	class Conversion;
	typedef	K2Vector<Conversion>					ConversionVector;
	class Directive;
	typedef	K2Vector<Directive *>					DirectivePtrVector;


	//========================================================================================
	//	CLASS DECLARATIONS
	//========================================================================================
	//________________________________________________________________________________________
	//	Version
	//________________________________________________________________________________________
	/** This is a private utility class referenced only by private method or data of
	    other public classes. It is not intended to be used directly by outside developers.
		@author Steve Pellegrin
		@see CContentIteratorReg
	*/
	class Version: public VersionID
	{
	public:
		typedef  base_type data_type;
		
		Version()
			: VersionID(kInvalidPlugin, -1, -1), fForced(kFalse)
			{}

		Version(const VersionID &version, bool16 forced = kFalse)
			: VersionID(version), fForced(forced)
			{}

		Version(PluginID pluginID, const FormatID &format, bool16 forced = kFalse)
			: VersionID(pluginID, format), fForced(forced)
			{}

		bool16 WasForced() const
			{return fForced;}

	private:
		bool16		fForced;
	};
	
	
	//________________________________________________________________________________________
	//	Conversion
	//________________________________________________________________________________________
	/** This is a private utility class referenced only by private method or data of
	    other public classes. It is not intended to be used directly by outside developers.
		@author Steve Pellegrin
		@see CContentIteratorReg
	*/
	class Conversion
	{
	public:
		typedef	base_type data_type;
		Conversion()
			{}
		Conversion(const Version &from, const Version &to)
			: fFromVersion(from), fToVersion(to)
			{}
			
		Version GetFromVersion() const
			{return fFromVersion;}
		Version GetToVersion() const
			{return fToVersion;}
		
		bool16 operator==(const Conversion& other) const
			{return (fFromVersion == other.fFromVersion) && (fToVersion == other.fToVersion);}			
		
	private:
		Version		fFromVersion;
		Version		fToVersion;
	};
	
	
	//________________________________________________________________________________________
	//	FieldValue
	//________________________________________________________________________________________
	/** This is a private utility class referenced only by private method or data of
	    other public classes. It is not intended to be used directly by outside developers.
		@author Steve Pellegrin
		@see CContentIteratorReg
	*/
	class PUBLIC_DECL FieldValue
	{
	public:
		class DataBlob
		{
		public:
			DataBlob()
				: fType(kInvalidField), fBuffer(nil), fBufferSize(0)
				{}
			DataBlob(FieldType type)
				: fType(type), fBuffer(nil), fBufferSize(0)
				{}
			DataBlob(const DataBlob &other)
				: fType(other.fType), fBuffer(nil), fBufferSize(0)
				{Copy(other);}

			~DataBlob()
				{SetSize(0);}

			int32 GetSize() const
				{return fBufferSize;}
			IPMStream *QueryReadStream();
			void ReadWrite(IPMStream *s);
		
			bool16 operator==(const DataBlob& other) const;
			DataBlob & operator=(const DataBlob &other)
				{Copy(other); return *this;}

		public:
			static bool16 IsDataBlobType(FieldType t)
				{return ((t == kDataBlob16) || (t == kDataBlob32) || (t == kDataBlob8));}

		private:
			void SetSize(int32 size);
			void Copy(const DataBlob &other);

		private:
			FieldType		fType;
			int32			fBufferSize;
			uchar *			fBuffer;
		};

	public:
		typedef	object_type data_type;
		
		FieldValue()
			: fType(kInvalidField)
			{SetUnionType(fType, fValue);}
		FieldValue(FieldType type)
			: fType(type)
			{SetUnionType(fType, fValue);}
		FieldValue(FieldType type, IPMStream *s);
		FieldValue(const FieldValue &other);
		
		~FieldValue();
		
		FieldType GetType() const
			{return fType;}
			
		bool16 GetBool8(bool8 &v) const;
		bool16 GetBool16(bool16 &v) const;
		bool16 GetInt8(int8 &v) const;
		bool16 GetUint8(uint8 &v) const;
		bool16 GetInt16(int16 &v) const;
		bool16 GetUint16(uint16 &v) const;
		bool16 GetInt32(int32 &v) const;
		bool16 GetUint32(uint32 &v) const;
		bool16 GetReal(PMReal &v) const;
		bool16 GetClassID(ClassID &v) const;
		bool16 GetImplementationID(ImplementationID &v) const;
		bool16 GetInterfaceID(PMIID &v) const;
		bool16 GetServiceID(ServiceID &v) const;
		bool16 GetWidgetID(WidgetID &v) const;
		bool16 GetPluginID(PluginID &v) const;
		bool16 GetErrorID(ErrorCode &v) const;
		bool16 GetObject(UID &v) const;
		bool16 GetReference(UID &v) const;
		bool16 GetPMString(PMString &v) const;
		bool16 GetPMPoint(PMPoint &v) const;
		bool16 GetPMRect(PMRect &v) const;
		bool16 GetPMMatrix(PMMatrix &v) const;
		bool16 GetNameInfo(NameInfo &v) const;
		bool16 GetDataBlob(DataBlob **v) const;
		bool16 GetWideString(WideString &v) const;
		bool16 GetURI(URI &v) const;

		void SetInt16(int16 v)
		{
			ASSERT(fType == kInt16);
			fValue.dInt16 = v;
		}
		
		void ReadWrite(IPMStream *s);
		bool16 CopyValue(const FieldValue &other);
		
		bool16 operator==(const FieldValue& other) const;
		FieldValue & operator=(const FieldValue &other);

	private:
		union ValueUnion
		{
			bool8				dBool8;
			bool16				dBool16;
			int8				dInt8;
			uint8				dUint8;
			int16				dInt16;
			uint16				dUint16;
			int32				dInt32;
			uint32				dUint32;
			uint32				dIDValue;
			PMReal *			dReal;
			PMString *			dPMString;
			PMPoint *			dPMPoint;
			PMRect *			dPMRect;
			PMMatrix *			dPMMatrix;
			NameInfo *			dNameInfo;
			DataBlob *			dDataBlob;
			WideString *		dWideString;
			URI *				dURI;
		};

	private:
		static void SetUnionType(FieldType newT, ValueUnion &v, FieldType oldT = kInvalidField);
		static void ClearUnion(FieldType t, ValueUnion &v)
			{SetUnionType(kInvalidField, v, t);}
		static bool16 ConvertValue(FieldType sType, const ValueUnion &sValue, FieldType tType, ValueUnion &tValue);
		static bool16 ConvertBool8(bool8 sValue, FieldType tType, ValueUnion &tValue);
		static bool16 ConvertBool16(bool16 sValue, FieldType tType, ValueUnion &tValue);
		static bool16 ConvertInt8(int8 sValue, FieldType tType, ValueUnion &tValue);
		static bool16 ConvertUint8(uint8 sValue, FieldType tType, ValueUnion &tValue);
		static bool16 ConvertInt16(int16 sValue, FieldType tType, ValueUnion &tValue);
		static bool16 ConvertUint16(uint16 sValue, FieldType tType, ValueUnion &tValue);
		static bool16 ConvertInt32(int32 sValue, FieldType tType, ValueUnion &tValue);
		static bool16 ConvertUint32(uint32 sValue, FieldType tType, ValueUnion &tValue);
		static bool16 ConvertReal(const PMReal &sValue, FieldType tType, ValueUnion &tValue);
		static bool16 ConvertID(uint32 sValue, FieldType tType, ValueUnion &tValue);
		static bool16 ConvertPMString(const PMString &sValue, FieldType tType, ValueUnion &tValue);
		static PMReal MakePMReal(IPMStream *s);
		static PMString MakePMString(IPMStream *s);
		static WideString MakeWideString(IPMStream *s);
		static URI MakeURI(IPMStream *s);
	
	private:
		void ReadDefaultValue(IPMStream *s);
		
	private:
		FieldType		fType;
		ValueUnion		fValue;
	};
	
	
	//________________________________________________________________________________________
	//	Instance
	//________________________________________________________________________________________
	/** This is a private utility class referenced only by private method or data of
	    other public classes. It is not intended to be used directly by outside developers.
		@author Steve Pellegrin
		@see CContentIteratorReg
	*/
	class PUBLIC_DECL Instance
	{
	public:
		typedef	uint32		InstanceValue;
		
	public:
		Instance()
			: fValueList()
			{}
		Instance(const Instance &other)
			: fValueList(other.fValueList)
			{}
			
		void PushLevel(InstanceValue v = 0)
			{fValueList.push_back(v);}
		void PopLevel()
			{fValueList.pop_back();}
		void SetValue(InstanceValue v)
			{fValueList.back() = v;};
	
		bool16 operator==(const Instance& other) const
			{return (fValueList == other.fValueList);}
		bool16 operator<(const Instance& other) const;

		Instance &operator=(const Instance &other)
			{fValueList = other.fValueList; return *this;}
		
	private:
		typedef	K2Vector<InstanceValue>	InstanceVector;
	
	private:
		InstanceVector		fValueList;
	};
		
		
	//________________________________________________________________________________________
	//	FieldKey
	//________________________________________________________________________________________
	/** This is a private utility class referenced only by private method or data of
	    other public classes. It is not intended to be used directly by outside developers.
		@author Steve Pellegrin
		@see CContentIteratorReg
	*/
	class PUBLIC_DECL FieldKey
	{
	public:
		FieldKey(FieldID id = kInvalidFieldID)
			: fID(id), fInstance()
			{}
		FieldKey(FieldID id, const Instance &i)
			: fID(id), fInstance(i)
			{}
		FieldKey(const FieldKey &other)
			: fID(other.fID), fInstance(other.fInstance)
			{}

		FieldID GetID() const
			{return fID;}
		const Instance &GetInstance() const
			{return fInstance;}
		bool16 IsValid() const
			{return fID != kInvalidFieldID;}

		void SetID(FieldID id)
			{fID = id;}
		void SetInstance(const Instance &i)
			{fInstance = i;}
		void Invalidate()
			{SetID(kInvalidFieldID);}

		bool16 operator<(const FieldKey &other) const
			{return (fID == other.fID) ? (fInstance < other.fInstance) : (fID < other.fID);}
		bool16 operator==(const FieldKey &other) const
			{return ((fID == other.fID) && (fInstance == other.fInstance));}

		FieldKey &operator=(const FieldKey &other)
			{fID = other.fID; fInstance = other.fInstance; return *this;}

	private:
		FieldID		fID;
		Instance	fInstance;
	};
		
		
	//________________________________________________________________________________________
	//	Field
	//________________________________________________________________________________________
	/** This is a private utility class referenced only by private method or data of
	    other public classes. It is not intended to be used directly by outside developers.
		@author Steve Pellegrin
		@see CContentIteratorReg
	*/
	class PUBLIC_DECL Field
	{
	public:
		typedef	object_type data_type;
		
		Field()
			: fKey(kInvalidFieldID), fType(kInvalidField)
			{}
		Field(FieldID id, const FieldValue &fv)
			: fKey(id), fType(kInvalidField)
			{AddValue(fv);}
		Field(const FieldValue &fv)
			: fKey(kInvalidFieldID), fType(kInvalidField)
			{AddValue(fv);}
		Field(FieldID id, const Instance &instance, FieldType type = kInvalidField)
			: fKey(id, instance), fType(type)
			{}
		Field(const Field &other)
			: fType(other.fType), fKey(other.fKey), fValueList(other.fValueList)
			{}
		Field(const Field &other, const Instance &instance)
			: fType(other.fType), fKey(other.fKey.GetID(), instance), fValueList(other.fValueList)
			{}
		Field(IPMStream *s, FieldType t);
		
		void ReadWrite(IPMStream *s, uint32 skipCount = 0, uint32 getCount = kMaxUInt32);
		bool16 CopyValue(const Field &other, uint32 skipCount = 0, uint32 getCount = kMaxUInt32);
		const FieldKey &GetKey() const
			{return fKey;}

		FieldType GetType() const
			{return fType;}

		uint32 GetValueCount() const
			{return fValueList.size();}
		ValueVector::const_iterator Begin() const
			{return fValueList.begin();}
		ValueVector::const_iterator End() const
			{return fValueList.end();}
		void AddValue(const FieldValue &v);
		
		bool16 operator==(const Field& other) const
			{return ((fType == other.fType) && (fKey == other.fKey) && (fValueList == other.fValueList));}
		Field &operator=(const Field &other)
			{fType = other.fType; fKey = other.fKey; fValueList = other.fValueList; return *this;}
		
	private:
		void ProcessIterationCount(FieldValue &count, IPMStream *s);
		void AddDataBlob(IPMStream *s);
		void ReadDefaultValue(FieldType t, IPMStream *s);

	private:
		FieldType			fType;
		FieldKey			fKey;
		ValueVector			fValueList;
	};


	//________________________________________________________________________________________
	//	Schema
	//________________________________________________________________________________________
	/** This is a private utility class referenced only by private method or data of
	    other public classes. It is not intended to be used directly by outside developers.
		@author Steve Pellegrin
		@see CContentIteratorReg
	*/
	class PUBLIC_DECL Schema
	{
	public:
		Schema()
			{}
		Schema(IPMStream *s)
			{Read(s);}
		Schema(const Schema &other)
			: fFieldList(other.fFieldList)
			{}

		void Read(IPMStream *s);

		FieldVector::const_iterator GetBeginIterator() const
			{return fFieldList.begin();}
		FieldVector::const_iterator GetEndIterator() const
			{return fFieldList.end();}
			
		bool16 IsEmpty() const
			{return (fFieldList.size() < 2);}
		bool16 ContainsFieldType(FieldType type) const;
				
		bool16 operator==(const Schema& other) const
			{return (fFieldList == other.fFieldList);}
		bool16 operator!=(const Schema& other) const
			{return !(*this == other);}
			
		Schema &operator=(const Schema &other)
			{fFieldList = other.fFieldList; return *this;}
		
	private:
		void ProcessFields(int16 count, IPMStream *s);
		void ProcessFieldArray(IPMStream *s);

	private:
		FieldVector	fFieldList;
	};
	
	
	//________________________________________________________________________________________
	//	SchemaInfo
	//________________________________________________________________________________________
	/** This is a private utility class referenced only by private method or data of
	    other public classes. It is not intended to be used directly by outside developers.
		@author Steve Pellegrin
		@see CContentIteratorReg
	*/
	class PUBLIC_DECL SchemaInfo
	{
	public:
		typedef object_type data_type;

		SchemaInfo()
			: fIsClass(kFalse), fIDValue(0)
			{}
		SchemaInfo(ClassID id, const Version &version)
			: fIsClass(kTrue), fIDValue(id.Get()), fVersion(version)
			{}
		SchemaInfo(ImplementationID id, const Version &version)
			: fIsClass(kFalse), fIDValue(id.Get()), fVersion(version)
			{}
		SchemaInfo(const SchemaInfo &other)
			{Copy(other);}

		bool16 AppliesTo(ClassID id) const
			{return AppliesTo(kTrue, id.Get());}
		bool16 AppliesTo(ImplementationID id) const
			{return AppliesTo(kFalse, id.Get());}
		bool16 AppliesTo(bool16 isClass, uint32 idValue) const
			{return (fIsClass == isClass) && (idValue == fIDValue);}
			
		bool16 Below(ClassID id) const
			{return Below(kTrue, id.Get());}
		bool16 Below(ImplementationID id) const
			{return Below(kFalse, id.Get());}
		bool16 Below(bool16 isClass, uint32 idValue) const
			{return (fIsClass == isClass) ? (fIDValue < idValue) : (fIsClass < isClass);}
			
		bool16 Above(ClassID id) const
			{return Above(kTrue, id.Get());}
		bool16 Above(ImplementationID id) const
			{return Above(kFalse, id.Get());}
		bool16 Above(bool16 isClass, uint32 idValue) const
			{return (fIsClass == isClass) ? (fIDValue > idValue) : (fIsClass > isClass);}
			
		uint32 GetIDValue() const
			{return fIDValue;}
		const Version &GetVersion() const
			{return fVersion;}
		const Schema &GetSchema() const
			{return fSchema;}
			
		void ReadSchema(IPMStream *s)
			{fSchema.Read(s);}

		SchemaInfo & operator=(const SchemaInfo &other);
		bool16 operator==(const SchemaInfo &other) const;
		bool16 operator<(const SchemaInfo &other) const;

	private:
		void Copy(const SchemaInfo &other)
			{fIsClass = other.fIsClass; fIDValue = other.fIDValue;
			 fVersion = other.fVersion; fSchema = other.fSchema;}


	private:
		bool16			fIsClass;
		uint32			fIDValue;
		Version			fVersion;
		Schema 			fSchema;
	};


	//________________________________________________________________________________________
	//	IteratorSchemaInfo
	//________________________________________________________________________________________
	/** This is a private utility class referenced only by private method or data of
	    other public classes. It is not intended to be used directly by outside developers.
		@author Steve Pellegrin
		@see CContentIteratorReg
	*/
	class IteratorSchemaInfo
	{
	public:
		typedef base_type data_type;
		
		IteratorSchemaInfo()
			: fIsClass(false), fIDValue(0), fFormat(), fSchemaInfo(nil)
			{}
		IteratorSchemaInfo(ClassID clsID, const FormatID &format, const SchemaInfo *info = nil)
			: fIsClass(true), fIDValue(clsID.Get()), fFormat(format), fSchemaInfo(info)
			{}
		IteratorSchemaInfo(ImplementationID implID, const FormatID &format, const SchemaInfo *info = nil)
			: fIsClass(false), fIDValue(implID.Get()), fFormat(format), fSchemaInfo(info)
			{}
		IteratorSchemaInfo(bool16 isClass, uint32 idValue, const FormatID &format, const SchemaInfo *info = nil)
			: fIsClass(isClass), fIDValue(idValue), fFormat(format), fSchemaInfo(info)
			{}
		IteratorSchemaInfo(const IteratorSchemaInfo &other)
			{Copy(other);}

		const Schema * GetSchema() const
			{return (fSchemaInfo == nil) ? nil : &fSchemaInfo->GetSchema();}

		bool16 operator==(const IteratorSchemaInfo& other) const
			{return ((fIsClass == other.fIsClass) && (fIDValue == other.fIDValue) && (fFormat == other.fFormat));}

		IteratorSchemaInfo & operator=(const IteratorSchemaInfo &other)
			{Copy(other); return *this;}

	private:
		void Copy(const IteratorSchemaInfo &other)
			{fIsClass = other.fIsClass; fIDValue = other.fIDValue;
			 fFormat = other.fFormat; fSchemaInfo = other.fSchemaInfo;}
		
	private:
		bool16				fIsClass;
		uint32				fIDValue;
		FormatID			fFormat;
		const SchemaInfo *	fSchemaInfo;
	};


	//________________________________________________________________________________________
	//	Directive
	//________________________________________________________________________________________
	/** This is a private utility class referenced only by private method or data of
	    other public classes. It is not intended to be used directly by outside developers.
		@author Steve Pellegrin
		@see CContentIteratorReg
	*/
	class Directive
	{
	public:
		typedef	base_type data_type;
		Directive()
			{}
		Directive(int16 type, const Version &version)
			: fType(type), fVersion(version)
			{}
			
		virtual int16 GetType() const
			{return fType;}
		virtual const Version & GetVersion() const
			{return fVersion;}

		bool16 InRange(const VersionID &fromV, const VersionID &toV) const;
		
	private:
		int16			fType;
		Version			fVersion;
	};


	//________________________________________________________________________________________
	//	ClassDirective
	//________________________________________________________________________________________
	/** This is a private utility class referenced only by private method or data of
	    other public classes. It is not intended to be used directly by outside developers.
		@author Steve Pellegrin
		@see CContentIteratorReg
	*/
	class ClassDirective: public Directive
	{
	public:
		typedef	base_type data_type;
		ClassDirective()
			{}
		ClassDirective(int16 type, ClassID classID, const Version &version)
			: Directive(type, version), fOldClassID(classID), fNewClassID(kInvalidClass)
			{}
		ClassDirective(int16 type, ClassID oldClassID, ClassID newClassID, const Version &version)
			: Directive(type, version), fOldClassID(oldClassID), fNewClassID(newClassID)
			{}
			
		ClassID GetClassID() const
			{return fOldClassID;}
		ClassID GetOldClassID() const
			{return fOldClassID;}
		ClassID GetNewClassID() const
			{return fNewClassID;}
		
	private:
		ClassID		fOldClassID;
		ClassID		fNewClassID;
	};


	//________________________________________________________________________________________
	//	ImplementationDirective
	//________________________________________________________________________________________
	/** This is a private utility class referenced only by private method or data of
	    other public classes. It is not intended to be used directly by outside developers.
		@author Steve Pellegrin
		@see CContentIteratorReg
	*/
	class ImplementationDirective: public Directive
	{
	public:
		typedef	base_type data_type;
		ImplementationDirective()
			{}
		ImplementationDirective(int16 type, ClassID context, ImplementationID implID, const Version &version)
			: Directive(type, version), fContext(context), fOldImplID(implID), fNewImplID(kInvalidImpl)
			{}
		ImplementationDirective(int16 type, ClassID context, ImplementationID oldImplID, ImplementationID newImplID, const Version &version)
			: Directive(type, version), fContext(context), fOldImplID(oldImplID), fNewImplID(newImplID)
			{}
			
		ClassID GetContext() const
			{return fContext;}
		ImplementationID GetImplID() const
			{return fOldImplID;}
		ImplementationID GetOldImplID() const
			{return fOldImplID;}
		ImplementationID GetNewImplID() const
			{return fNewImplID;}
		
	private:
		ClassID					fContext;
		ImplementationID		fOldImplID;
		ImplementationID		fNewImplID;
	};


	//________________________________________________________________________________________
	//	MoveDirective(s)
	//________________________________________________________________________________________
	/** This is a private utility class referenced only by private method or data of
	    other public classes. It is not intended to be used directly by outside developers.
		@author Steve Pellegrin
		@see CContentIteratorReg
	*/
	template <class T>
	class MoveDirective: public Directive
	{
	public:
		typedef	base_type data_type;
		
		MoveDirective()
			{}
		MoveDirective(int16 type, T fromID, const Version &fromVersion, T toID, const Version &toVersion, const Version &myVersion)
			: Directive(type, myVersion), fFromID(fromID), fFromVersion(fromVersion), fToID(toID), fToVersion(toVersion)
			{}
			
		T GetFromID() const
			{return fFromID;}
		T GetToID() const
			{return fToID;}
		const Version & GetFromVersion() const
			{return fFromVersion;}
		const Version & GetToVersion() const
			{return fToVersion;}

		bool operator==(const MoveDirective<T>&) const
			{ASSERT_FAIL("appease K2Vector.Location"); return false;}
		
	private:
		T					fFromID;
		Version				fFromVersion;
		T					fToID;
		Version				fToVersion;
	};
	
	typedef MoveDirective<ClassID>			ClassMoveDirective;
	typedef MoveDirective<ImplementationID>	ImplementationMoveDirective;

	//________________________________________________________________________________________
	//	PluginDirective
	//________________________________________________________________________________________
	/** This is a private utility class referenced only by private method or data of
	    other public classes. It is not intended to be used directly by outside developers.
		@author Steve Pellegrin
		@see CContentIteratorReg
	*/
	class PluginDirective: public Directive
	{
	public:
		typedef	base_type data_type;
		PluginDirective()
			{}
		PluginDirective(int16 type, PluginID pluginID, const Version &version)
			: Directive(type, version), fFromVersion(pluginID, FormatID(0, 0)), fToVersion()
			{}
		PluginDirective(int16 type, const Version &fromVersion, const Version &toVersion, const Version &myVersion)
			: Directive(type, myVersion), fFromVersion(fromVersion), fToVersion(toVersion)
			{}
			
		PluginID GetPluginID() const
			{return fFromVersion.GetPluginID();}
		
	private:
		Version					fFromVersion;
		Version					fToVersion;
	};


	//________________________________________________________________________________________
	//	PathStep
	//________________________________________________________________________________________
	/** This is a private utility class referenced only by private method or data of
	    other public classes. It is not intended to be used directly by outside developers.
		@author Steve Pellegrin
		@see CContentIteratorReg
	*/
	class PathStep
	{
	public:
		typedef	base_type data_type;
		PathStep()
			{}
		PathStep(int32 version, int32 predecessor)
			: fVersion(version), fPredecessor(predecessor)
			{}
			
		int32 GetVersion() const
			{return fVersion;}
		int32 GetPredecessor() const
			{return fPredecessor;}
			
		bool16 operator==(const PathStep& other) const
			{return ((fVersion == other.fVersion) && (fPredecessor == other.fPredecessor));}			
		
	private:
		int32		fVersion;
		int32		fPredecessor;
	};


	//________________________________________________________________________________________
	//	Implementation
	//________________________________________________________________________________________
	/** This is a private utility class referenced only by private method or data of
	    other public classes. It is not intended to be used directly by outside developers.
		@author Steve Pellegrin
		@see CContentIteratorReg
	*/
	class Implementation
	{
	public:
		typedef base_type data_type;
		Implementation()
			{}
		Implementation(PluginID provider, ClassID boss, ImplementationID tag = kInvalidImpl)
			: fProvider(provider), fBoss(boss), fTag(tag)
			{}
		Implementation(const ClassDirective &d)
			: fProvider(d.GetVersion().GetPluginID()), fBoss(d.GetClassID()), fTag(kInvalidImpl)
			{}
		Implementation(const ImplementationDirective &d)
			: fProvider(d.GetVersion().GetPluginID()), fBoss(d.GetContext()), fTag(d.GetImplID())
			{}
			
		PluginID GetProvider() const
			{return fProvider;}
		ClassID GetBoss() const
			{return fBoss;}
		ImplementationID GetTag() const
			{return fTag;}
			
		bool16 operator==(const Implementation& other) const
			{return ((fProvider == other.fProvider) && (fBoss == other.fBoss) && (fTag == other.fTag));}			
		
	private:
		PluginID			fProvider;
		ClassID				fBoss;
		ImplementationID	fTag;
	};


	//________________________________________________________________________________________
	//	ConvertInfo
	//________________________________________________________________________________________
	/** This is a private utility class referenced only by private method or data of
	    other public classes. It is not intended to be used directly by outside developers.
		@author Steve Pellegrin
		@see CContentIteratorReg
	*/
	class PUBLIC_DECL ConvertInfo
	{
	private:
		enum Mode
		{
			kDontConvert,
			kConvert,
			kRemove,
			kReplace
		};

	public:
		typedef base_type data_type;
		
		ConvertInfo()
			: fMode(kDontConvert), fIDValue(0), fContextValue(0), fConversionIndex(-1), fSourceInfo(), fTargetInfo(), fNewIDValue(0)
			{}
		ConvertInfo(ImplementationID impl, ClassID context, int32 cIndex)
			: fMode(kDontConvert), fIsClass(kFalse),fIDValue(impl.Get()), fContextValue(context.Get()), fConversionIndex(cIndex), fSourceInfo(), fTargetInfo(), fNewIDValue(0)
			{}
		ConvertInfo(ClassID cls, ImplementationID context, int32 cIndex)
			: fMode(kDontConvert), fIsClass(kTrue),fIDValue(cls.Get()), fContextValue(context.Get()), fConversionIndex(cIndex), fSourceInfo(), fTargetInfo(), fNewIDValue(0)
			{}
		ConvertInfo(bool16 isClass, uint32 idValue, uint32 contextValue, int32 cIndex)
			: fMode(kDontConvert), fIsClass(isClass),fIDValue(idValue), fContextValue(contextValue), fConversionIndex(cIndex), fSourceInfo(), fTargetInfo(), fNewIDValue(0)
			{}


		const SchemaInfo * GetSourceSchemaInfo() const
			{return fSourceInfo;}
		const SchemaInfo * GetTargetSchemaInfo() const
			{return fTargetInfo;}
		uint32 GetNewID() const
			{return fNewIDValue;}

		void SetRemove()
			{fMode = kRemove;}
		void SetReplace(uint32 newIDValue)
			{fMode = kReplace; fNewIDValue = newIDValue;}
		void SetConvert(const SchemaInfo *sInfo, const SchemaInfo *tInfo)
			{fMode = kConvert; fSourceInfo = sInfo; fTargetInfo = tInfo;}
		bool16 NoConversion() const
			{return (fMode == kDontConvert);}
		bool16 ShouldRemove() const
			{return (fMode == kRemove);}
		bool16 ShouldReplace() const
			{return (fMode == kReplace);}
		bool16 ShouldConvert() const
			{return (fMode == kConvert);}
			
		bool16 operator==(const ConvertInfo& other) const;
		bool16 operator<(const ConvertInfo& other) const;
		bool16 operator>(const ConvertInfo& other) const;
		
	private:
		const SchemaInfo *	fSourceInfo;
		const SchemaInfo *	fTargetInfo;
		Mode				fMode;
		uint32				fIDValue;
		uint32				fContextValue;
		int32				fConversionIndex;
		uint32				fNewIDValue;
		bool16				fIsClass;
	};


	//________________________________________________________________________________________
	//	DataSet
	//________________________________________________________________________________________
	/** This is a private utility class referenced only by private method or data of
	    other public classes. It is not intended to be used directly by outside developers.
		@author Steve Pellegrin
		@see CContentIteratorReg
	*/
	class PUBLIC_DECL DataSet
	{
	public:
		DataSet();
		DataSet(const Schema &schema, IPMStream *stream);
		DataSet(const Schema &schema, DataSet &data);

		// To fill the DataSet from a schema.
		void Fill(const Schema &schema, IPMStream *stream);

		// To fill the DataSet manually with a simple field.
		void AppendField(const Field &f);

		// To fill the DataSet manually with a simple field.
		Schemas::FieldValue AppendSimpleField(Schemas::FieldType type,
												FieldID id, IPMStream* stream);

		// To fill the DataSet manually for an Attribute boss list
		void AppendAttributeBossList(FieldID id, FieldType countType,
									FieldType dataType, IPMStream* stream);

		bool16 IsEmpty() const
			{return fFieldList.empty();}

		FieldVector::iterator Begin()
			{return fFieldList.begin();}
		FieldVector::iterator End()
			{return fFieldList.end();}

		bool16 HasError() const
			{return fErrorFieldKey.IsValid();}
		void Write(IPMStream *s);
		const Field *FindField(Field &goal);
		
	private:
		// *****
		// Helper classes: Fetch a value from some source and store it in a Field.
		// *****
		class ValueSource
		{
		public:
			ValueSource()
				{}
			virtual ~ValueSource()
				{}
				
			virtual bool16 GetValue(Field &f, uint32 skipCount = 0, uint32 getCount = kMaxUInt32) = 0;
		};

		class StreamValueSource : public ValueSource
		{
		public:
			StreamValueSource(IPMStream *s)
				: fStream(s)
				{}
			virtual ~StreamValueSource()
				{}
				
			virtual bool16 GetValue(Field &f, uint32 skipCount, uint32 getCount);
			
		private:
			IPMStream *		fStream;
		};

		class DataValueSource : public ValueSource
		{
		public:
			DataValueSource(DataSet &d)
				: fData(&d)
				{}
			virtual ~DataValueSource()
				{}
				
			virtual bool16 GetValue(Field &f, uint32 skipCount, uint32 getCount);
			
		private:
			DataSet *		fData;
		};

		// *****
		//	Helper: Map to lookup Fields by ID/Instance.
		// *****
		typedef std::map<FieldKey, const Field *>			FieldIDMap;
		
	private:
		void Initialize(const Schema &schema, ValueSource &vs);
		FieldVector::const_iterator ProcessFields(Instance &inst, int16 count, FieldVector::const_iterator pF, ValueSource &vs);
		FieldVector::const_iterator ProcessSimpleField(Instance &inst, FieldVector::const_iterator pF, ValueSource &vs);
		FieldVector::const_iterator ProcessFieldArray(Instance &inst, FieldVector::const_iterator pF, ValueSource &vs);
		FieldVector::const_iterator ProcessAttributeBoss(Instance &inst, FieldVector::const_iterator pF, ValueSource &vs);
		FieldVector::const_iterator ProcessAttributeBossList(Instance &inst, FieldVector::const_iterator pF, ValueSource &vs);
		FieldVector::const_iterator SkipFields(int16 count, FieldVector::const_iterator pF);
		FieldVector::const_iterator SkipFieldArray(FieldVector::const_iterator pF);
		void BuildMap();
		const Field *FindFieldInList(Field &goal) const;
		const Field *FindFieldInMap(Field &goal) const;

	private:
		FieldVector		fFieldList;
		FieldKey		fErrorFieldKey;
		bool16			fMappingDecisionMade;
		FieldIDMap		fFieldMap;
	};

	
}	// End Schemas namespace


//________________________________________________________________________________________
//	SchemaManager
//________________________________________________________________________________________
/** This is a private utility class referenced only by private method or data of
	other public classes. It is not intended to be used directly by outside developers.
	@author Steve Pellegrin
	@see CContentIteratorReg
*/
class PUBLIC_DECL SchemaManager
{
public:
	SchemaManager()
		: fPluginID(kInvalidPlugin)
		{}
	SchemaManager(PluginID p)
		{BuildSchemaList(p);}
		
	void SetPluginID(PluginID p)
		{BuildSchemaList(p);}
	PluginID GetPluginID() const
		{return fPluginID;}

	void GetVersions(Schemas::VersionVector &v) const;

	bool16 HasSchemas(ClassID id) const
		{return HasSchemas(kTrue, id.Get());}
	bool16 HasSchemas(ImplementationID id) const
		{return HasSchemas(kFalse, id.Get());}
	bool16 HasSchemas(bool16 isClass, uint32 idValue) const;

	const Schemas::SchemaInfo *FindClosestSchema(ClassID id, const Schemas::Version &version, const Schemas::MajorFormatVector &path) const
		{return FindClosestSchema(kTrue, id.Get(), version, path);}
	const Schemas::SchemaInfo *FindClosestSchema(ImplementationID id, const Schemas::Version &version, const Schemas::MajorFormatVector &path) const
		{return FindClosestSchema(kFalse, id.Get(), version, path);}
	const Schemas::SchemaInfo *FindClosestSchema(bool16 isClass, uint32 idValue, const Schemas::Version &version, const Schemas::MajorFormatVector &path) const;
	
private:
	void BuildSchemaList(PluginID p);
	void ProcessSchema(IPMStream *s);
	void ProcessVersionList(IPMStream *s);
	bool16 FindSchemaVersion(const Schemas::Version &version) const;
	bool IndividualSchemaStreamCallback(IDResource r, void* userData);
	bool SchemaListStreamCallback(IDResource r, void* userData);
	bool VersionListResourceCallback(IDResource r, void* userData);
	
private:
	PluginID					fPluginID;
	Schemas::SchemaInfoVector	fIDList;
};


//________________________________________________________________________________________
//	DirectiveManager
//________________________________________________________________________________________
/** This is a private utility class referenced only by private method or data of
	other public classes. It is not intended to be used directly by outside developers.
	@author Steve Pellegrin
	@see CContentIteratorReg
*/
class PUBLIC_DECL DirectiveManager
{
public:
	DirectiveManager()
		: fPluginID(kInvalidPlugin)
		{}
	DirectiveManager(PluginID p)
		{BuildDirectiveList(p);}
	~DirectiveManager()
		{ClearDirectiveList();}
		
	void SetPluginID(PluginID p)
		{BuildDirectiveList(p);}
	PluginID GetPluginID() const
		{return fPluginID;}
		
	void GetAllVersions(Schemas::VersionVector &v) const;
	void GetPluginVersions(PluginID plugin, int16 dirType, Schemas::VersionVector &v) const;
	void GetVersions(int16 dirType, Schemas::VersionVector &v) const
		{GetPluginVersions(kInvalidPlugin, dirType, v);}
	const Schemas::ClassDirective * HaveDirectiveForClass(int16 dirType, ClassID classID, const Schemas::Conversion &conv) const;
	const Schemas::ImplementationDirective * HaveDirectiveForImplementation(int16 dirType, ClassID context, ImplementationID implID, const Schemas::Conversion &conv) const;
	
	void GetDirectivesOfType(int16 dirType, Schemas::DirectivePtrVector &list) const;
	
private:
	bool DirectiveListCallback(IDResource r, void* userData);
	void BuildDirectiveList(PluginID p);
	void ClearDirectiveList();
	
private:
	PluginID						fPluginID;
	Schemas::DirectivePtrVector		fDirectivePtrList;
};


//________________________________________________________________________________________
//	PathManager
//________________________________________________________________________________________
/** This is a private utility class referenced only by private method or data of
	other public classes. It is not intended to be used directly by outside developers.
	@author Steve Pellegrin
	@see CContentIteratorReg
*/
class PUBLIC_DECL PathManager
{
public:
	PathManager()
		: fPluginID(kInvalidPlugin)
		{}
	PathManager(PluginID p)
		{BuildStepList(p);}
		
	void SetPluginID(PluginID p)
		{BuildStepList(p);}
	PluginID GetPluginID() const
		{return fPluginID;}
		
	bool16 GetPath(int32 fromVersion, int32 toVersion, Schemas::MajorFormatVector &list) const
		{return FindPath(fromVersion, toVersion, &list);}
	bool16 PathExists(int32 fromVersion, int32 toVersion) const
		{return FindPath(fromVersion, toVersion);}
	bool16 FindBestPath(const Schemas::Version &from, const Schemas::Version &to, Schemas::MajorFormatVector &path) const;

public:
	static bool16 IsReachable(int32 fromVersion, int32 toVersion, const Schemas::MajorFormatVector &path);

private:
	bool StepListCallback(IDResource r, void* userData);
	void BuildStepList(PluginID p);
	void AddImplicitSteps(int32 fromVersion, int32 toVersion) const;
	bool16 ExplicitStepsExist(int32 version) const;
	bool16 FindPath(int32 fromVersion, int32 toVersion, Schemas::MajorFormatVector *list = nil) const;
	bool16 FindSubpath(int32 fromVersion, int32 toVersion, Schemas::MajorFormatVector *resultList, bool16 reversed) const;
	void ClearList(Schemas::MajorFormatVector *list) const
		{if (list != nil) list->clear();}
	void AddToList(Schemas::MajorFormatVector *list, int32 step, bool16 reversed) const
		{if (list != nil) {if (reversed) list->insert(list->begin(), step); else list->push_back(step);}}
	void RemoveLastFromList(Schemas::MajorFormatVector *list, bool16 reversed) const
		{if (list != nil) {if (reversed) list->erase(list->begin()); else list->pop_back();}}

private:
	static Schemas::MajorFormatVector::const_iterator FindInPath(Schemas::MajorFormatVector::const_iterator pStart,
	                                                             Schemas::MajorFormatVector::const_iterator pEnd, int32 majorVersion);

private:
	PluginID							fPluginID;
	mutable Schemas::PathStepVector		fStepList;
};


//________________________________________________________________________________________
//	PluginManager
//________________________________________________________________________________________
/** This is a private utility class referenced only by private method or data of
	other public classes. It is not intended to be used directly by outside developers.
	@author Steve Pellegrin
	@see CContentIteratorReg
*/
class PUBLIC_DECL PluginManager
{
public:
	PluginManager()
		{}
	PluginManager(const Schemas::VersionVector& versions)
		{CollectPlugins(versions);}

	void SetPluginID(PluginID p)
		{fPluginID = p;}
		
	void SetVersionList(const Schemas::VersionVector& versions)
		{CollectPlugins(versions);}
	void SetDirectiveMgr(DirectiveManager &dm)
		{BuildDirectiveList(dm);}
		
	int32 CountPlugins() const
		{return fPluginList.size();}
	PluginID GetNthPlugin(int32 n) const;
	bool16 GetPluginVersion(Schemas::Version &v) const;

	int32 CountRemovedPlugins(const VersionID &fromVersion, const VersionID &toVersion) const;
	PluginID GetNthRemovedPlugin(const VersionID &fromVersion, const VersionID &toVersion, int32 n) const;
	int32 CountIgnoredPlugins(const VersionID &fromVersion, const VersionID &toVersion) const;
	PluginID GetNthIgnoredPlugin(const VersionID &fromVersion, const VersionID &toVersion, int32 n) const;
	
public:
	static PluginID GetPluginID(IPMUnknown *tag);

private:
	void CollectPlugins(const Schemas::VersionVector& versions);
	void BuildDirectiveList(DirectiveManager &dm);

private:
	PluginID						fPluginID;
	Schemas::PluginVector			fPluginList;
	Schemas::DirectivePtrVector		fDirectivePtrList;
};


#endif	// __SchemaUtils__
