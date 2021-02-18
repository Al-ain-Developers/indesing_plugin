//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PreflightObjectID.h $
//  
//  Owner: Matt Phillips
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

/** All preflight objects have a class, such as 'document' or 'spread' or 'text 
	marking operation.' An object model service provides hierarchy and mapping of 
	all preflight objects of that class.

	@see IPreflightObjectModel
	@see IPreflightObjectModelService
*/

typedef ClassID PreflightObjectClassID;

/** All preflight objects are associated with a database somewhere, typically a 
	document, or possibly a book. These in turn can be in memory or out on disk.
	(Out on disk in the case of a child document of a book, or perhaps if it's some
	data from a placed INDD.) 

	We need to gracefully handle the out-on-disk case plus we also want to be able 
	to determine whether we still have access to a document if we have a preflight 
	object from that document in the general case (ie, catching errors). Thus we 
	maintain a separate table in the preflight manager of documents and issue IDs 
	that can be used to determine whether the document still exists in memory, what 
	the path to the document is if not, and so on.

	@see IPreflightManager
*/
typedef uint32 PreflightDocumentID;

/** A preflight object is simply a collection of (a) the class of the object; (b) the
	document the object belongs to; and (c) the instance of that object in the doucment.
	The instance is just basically some variable sized array of bytes that only the
	preflight object model service for the class can interpret. The document ID is here
	simply because every single object needs to know this and we don't want to include
	the overhead of maintaining that in the instance data for all services.

	You can think of the preflight object ID as a kind of URL to something that can be
	anywhere from really big (a document, say) to something tiny (a single stroke).

	Generally you'll use this class directly just as intended -- as an opaque object.
	There are three things you can legitimately do with a PreflightObjectID that you
	don't 'own' (ie you're not an object model service and this is a ClassID you
	implement):

		- Get its class via GetClassID() and compare it to something you know about.
			For example, you can determine whether a given object is a document using
			(objid.GetClassID() == kPreflightOM_Document).

		- Get the document it's associated with and ask more information about that 
			document via IPreflightManager, which maintains the document ID map.

		- Get an IPreflightObject interface via the preflight object model and use 
			that to query other info interfaces and/or call GetModelRef() to get a 
			pointer into the InDesign object model.

	So for example if you have an PreflightObjectID it's fine to do something like this:

		PMString GetDocumentName(const PreflightObjectID& objID)
		{
			if (objID.GetClassID() == kPreflightOM_Document)
			{
				InterfacePtr<IPreflightObjectModel> iModel(Utils<IPreflightUtils>()->QueryObjectModel());
				InterfacePtr<IPreflightObject> iObj(iModel->QueryObject(objID));
				InterfacePtr<IDocument> iDoc(iObj->GetModelRef());
				ASSERT(iDoc);
				return iDoc->GetName();
			}

			ASSERT_FAIL("This isn't a document.");
			return PMString();
		}

	In the vast majority of cases the code that needs to use a PreflightObjectID is a rule
	implementation. Rules are passed the PreflightObjectID via IPreflightRuleVisitor::Visit.
	You can look at the object ID or query the object directly from the helper interface
	passed to that method.

	The other class of code that needs access to PreflightObjectIDs are object model services.
	If you're writing an object model service, ie a service that extends the preflight 
	object model to include custom objects (or simply objects it doesn't currently support),
	you can feel free to subclass PreflightObjectID to make packing and unpacking your
	private data easier. For example if your private data consists of a UID and an offset
	uint32, you might subclass PreflightObjectID with a setter (takes a UID and uint32 and
	calls SetInstanceData()) and a getter (calls GetInstanceData and returns a UID and uint32).
	But this would be purely optional, and you should not expose the details of your private
	data any wider than necessary. If it's necessary to allow other parties to create object
	IDs corresponding to your objects, you should create a utils function for that purpose.
	The "getter" for a PreflightObjectID should be the data interfaces it exposes via
	IPreflightObject.

	Finally, there are utilities that will create object IDs corresponding to known InDesign
	objects, should you need to do this (generally speaking, only object model services, but
	there may be other clients).
	@see IPreflightObjectModelUtils for this purpose.
*/
class PUBLIC_DECL PreflightObjectID
{
public:
	typedef object_type data_type;

	/** Any allocations that are this number of bytes or less do not require a separate
		data buffer. This is done for speed and to limit memory fragmentation. Most objects
		do not require a separate buffer.
	*/
	enum { kSmallInstanceDataSize = 16 };

private:
	char* fLargeInstanceDataPtr; // used for large instance data
	char fSmallInstanceData[kSmallInstanceDataSize]; // used for small instance data

	PreflightObjectClassID fClassID;
	PreflightDocumentID fDocID;

	uint32 fInstanceDataSize;

	uint32 fHash;

public:
	/** Constructs an empty/zero/invalid ID.
	*/
	PreflightObjectID();

	/** Constructs an ID with or without initial data. The only callers of this ctor should
		be object model services or their related utilities. Otherwise you run the risk of
		severely confusing the object model service that is the owner of that object class.

		@param classID IN The class ID of the object.
		@param docID IN The ID of the document this object is associated with.
		@param instanceDataSize IN The size of the instance data. If 0, there is no instance data.
		@param instanceData IN The instance data to copy in. If nil, the object's data is 
					initialized to zeros.
	*/
	PreflightObjectID
		(
			PreflightObjectClassID classID, 
			PreflightDocumentID docID, 
			uint32 instanceDataSize = 0, 
			const char* instanceData = nil
		);

	/** Constructs an ID directly from serialized data. Call this only if you know the data
		you're pointing at via serializedData was created via SerializeTo().

		@param serializedData IN The data buffer written out via SerializeTo().
		@param dataSize IN The size of the data buffer. This must match the size expected
							(ie GetSerializedSize()) and is used as extra insurance against
							inadvertent coding/buffer errors.
	*/
	PreflightObjectID(char* serializedData, uint32 dataSize);

	/** Constructs a copy of another ID. This is generally fast, but if the object has a lot
		of instance data it will force an extra malloc for the copy.

		@param other IN The preflight object ID to copy from.
	*/
	PreflightObjectID(const PreflightObjectID& other);

	/** Destructor. Will free the associated instance data buffer, if there is one.
	*/
	~PreflightObjectID();

public:
	/** @return true if the object is in a default (unconstructed) state; false if it is not.
	*/
	bool32 IsNil() const;

public:
	/** Get the class ID of the object.
		@return The class ID.
	*/
	PreflightObjectClassID GetClassID() const { return fClassID; }

	/** Set the class ID of the object. Like the instance data, only object model services
		and their related utilities should call this method.

		@param x IN The new class ID.
	*/
	void SetClassID(const PreflightObjectClassID& x) { fClassID = x; }

	/** Get the document ID of the object. From this, via the IPreflightManager, you can 
		obtain the actual database, IDocument, and/or path to the file. Note that you can
		have an object ID for an object in a document that is not currently open.

		@return The document ID.
	*/
	PreflightDocumentID GetDocumentID() const { return fDocID; }

	/** Set the document ID of the object. Like the instance data, only object model services
		and their related utilities should call this method.

		@see IPreflightManager::GetDocumentID().

		@param x IN The new document ID.
	*/
	void SetDocumentID(const PreflightDocumentID& x) { fDocID = x; }

public:
	uint32 GetHash() const { return fHash; }

public:
	/** Get the size of the instance data for this object. This simply returns the value 
		provided via SetInstanceData().

		@return The instance data size, in bytes.
	*/
	uint32 GetInstanceDataSize() const;

	/** Get a pointer to the instance data. This pointer is valid only as long as the object
		does AND its instance data remains constant (ie SetInstanceData may make an existing
		pointer invalid).

		Typically this is used ONLY by the object model service as part of its unpacking. For
		example if the object data is simply a uint32 you can cast the result to a const uint32*.

		@return A pointer to the instance data.
	*/
	const void* GetInstanceData() const;

	/** Sets the instance data by copying in new data.
		@param dataSize The new size of the data.
		@param pData The data to copy in. If nil, zeros out the new data.
		@return kTrue if sucessful; will fail only if we can't allocate memory, which would be odd.
	*/
	bool32 SetInstanceData(uint32 dataSize, const void* pData);

public:
	/** Replace all of the parameters (classID, docID, instanceData) with values from a 
		serialized storage buffer. That buffer must have been set up via SerializeTo().

		@param sizeOfData IN The number of bytes to read from the buffer. Must match the 
			expected size (ie GetSerializedSize()). The method will not read past this memory
			size but will fail if there is not the correct number of bytes in the buffer.
		@param serializedData IN The data buffer to read from. Can't be nil.
		@return kTrue if successful, or kFalse if there was a buffer problem.
	*/
	bool32 SerializeFrom(uint32 sizeOfData, const void* serializedData);

	/** @return the number of bytes required for serialization of this object.
	*/
	uint32 GetSerializedSize() const;

	/** Write the object's parameters out to a memory buffer.

		@param sizeOfData IN The number of bytes to write. This should be the same value as
			returned from GetSerializedSize() and is required here as extra insurance against
			buffer configuration logic errors.
		@param serializedData OUT Receives the serialized data.
		@return kTrue if successful or kFalse if there were size or nil ptr problems.
	*/
	bool32 SerializeTo(uint32 sizeOfData, char* serializedData) const;

public:
	/** The assignment operator is generally fast, although it may require an extra malloc 
		if the instance data exceeds the internal small buffer. May free memory as well if
		the instance data buffer is no longer needed.
	*/
	PreflightObjectID& operator=(const PreflightObjectID& other);

	/** Equality checks all parameters (ie class, doc, and instance data must match).
	*/
	int operator==(const PreflightObjectID& other) const;

	/** Inequality is always the inverse of equality.
	*/
	int operator!=(const PreflightObjectID& other) const;

	/** Less-than is provided to support sets and maps of object IDs.
	*/
	int operator<(const PreflightObjectID& other) const;

protected:
	/** Recalculates the internal hash value. Called automatically when any of the parameters
		or instance data are modified.
	*/
	void RecalcHash();

	/** Internal-only helper function.
	*/
	bool32 SetInstanceDataSize(uint32 dataSize, bool32 preserveData = kTrue);
};

/** Widely used vector, so declared here for general purposes.
*/
typedef K2Vector<PreflightObjectClassID> PreflightObjectClassIDVector;

/** Widely used vector, so declared here for general purposes.
*/
typedef K2Vector<PreflightObjectID> PreflightObjectIDVector;

