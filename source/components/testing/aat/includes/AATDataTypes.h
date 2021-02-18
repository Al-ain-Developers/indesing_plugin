//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/aat/includes/AATDataTypes.h $
//  
//  Owner: Gregor Kaplan
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once
#ifndef __AATDataTypes__
	#define __AATDataTypes__

#include "QAMeasurement.h"
#include "VAATData.h"

#include "UIDList.h"
#include "qafile.h"
#include "AATArchID.h"

typedef PMString	ScarfData;

class AATLIB_DECL CAATData : public VAATData
{
	public:
		CAATData(void);
			
		CAATData(const ProdString &tag);
				
		CAATData(const ProdString &tag, const ProdString &uiString, ProdInt32 code);
		
		CAATData(const ProdString &tag, 
					const ProdString &uiString, 
					const ProdString &varName,
					ProdInt32 code);
				
		virtual ~CAATData() {}
		
		virtual void	Write(IXMLOutStream *stream, ProdBool asModel);
		virtual void	Read(const ProdString &localName, ISAXAttributes* attrs);
		
		virtual void	Copy(VAATData *srcData);
		
		virtual ProdInt32	GetIterationKey(void) const { return fIterKey; }
		virtual void	SetIterationKey(ProdInt32 val);
		virtual ProdBool	CanAssign(ProdInt32 iter);
		
		virtual ProdString	GetVariableName(void) { return fVarName; }
		virtual void	SetVariableName(const ProdString &str);
		
		virtual void	SetIsPosting(ProdBool post) { fIsPosting = post; }
		virtual ProdBool	GetIsPosting(void) { return fIsPosting; }
		
		virtual ProdString GetUITextString(void) { return fUIString; }
		virtual void SetUITextString(const ProdString &str) { fUIString = str; }
		
		virtual ProdString GetUIElementString(void); 
		virtual ProdInt32 GetUIElementCode(void); 
		virtual void SetUIElement(ProdInt32 code); 
		
		virtual ProdString GetTag(void) { return fTag; }
		virtual void SetTag(const ProdString &str) { fTag = str; }
		
		virtual void		SetGrouping(const ProdString &group) { fGrouping = group; }
		virtual ProdString	GetGrouping(void)	{ return fGrouping; }
		
		virtual ProdBool	IsEditable(void) { return fEditable; }
		virtual void	SetEditable(ProdBool edit) { fEditable = edit; }
		
		virtual ProdBool		AddAcceptableValue(const ProdString &str);
		virtual ProdBool		ReadAcceptableFromFile(void) { return fReadAcceptable; }
		virtual void		SetReadAcceptable(ProdBool readIt) { fReadAcceptable = readIt; }
		virtual ProdBool		WriteAcceptableToFile(void) { return fWriteAcceptable; }
		virtual void		SetWriteAcceptable(ProdBool writeIt) { fWriteAcceptable = writeIt; }
		
		virtual void		ClearAcceptableValues(void) { fAcceptableValues.clear(); }
		virtual void		SetValueFromAcceptableValues(ProdInt32 index);
		virtual ProdInt32		GetNumAcceptableValues(void);
		virtual ProdString* 	GetNthAcceptableValue(ProdInt32 index);
		
	protected:
		virtual void	PushHeader(IXMLOutStream *stream);
		virtual void	WriteVariable(IXMLOutStream *stream);
		virtual void	WriteUIData(IXMLOutStream *stream);
		virtual void	WriteValueList(IXMLOutStream *stream);
		
		ProdString		fVarName;	//Used when data is vairable - ie set through messaging
		ProdBool			fIsPosting;	//kTrue means this var should post, other wise receives.
		
		ProdString 		fTag;		//Tag for XML read/write
		
		ProdString		fUIString;	//String shown in UI as Hard text next to widget
		ProdInt32	fUICode;	//UI code for the UI widget to represent this item
		
		ProdInt32			fIterKey;	//Iteration Key for var.  Defaults to -1 which is accept any assignment
		ProdString		fGrouping;	//Which block should this be written in
		ProdBool			fEditable;	//Is the item editable - used to show or hide in UI
		
		K2Vector<ProdString> fAcceptableValues;	//A list of defualt values for an item - like the contents of a drop down list
		ProdBool			fReadAcceptable;		//Read in values from a test file.  Default is kTrue.
		ProdBool			fWriteAcceptable;
};


#define MAKE_QADATA_HEADER(a) \
class AATLIB_DECL QA_##a##_Data : public CAATData \
{ \
	public: \
		QA_##a##_Data(void); \
		QA_##a##_Data(a var); \
		QA_##a##_Data(a var, ProdString tag); \
		QA_##a##_Data(a var, ProdString tag, \
						ProdString varName, \
						ProdString uiString = "", \
						ProdInt32 code = kInvalidUICode); \
		QA_##a##_Data(const QA_##a##_Data &data); \
		\
		virtual ~QA_##a##_Data() {} \
		\
		virtual VirtualType GetType(void); \
		\
		void	Set(a val); \
		\
		a&	Get(void); \
		\
		QA_##a##_Data& 	operator=(const QA_##a##_Data& otherVal); \
		QA_##a##_Data& 	operator=(const a& otherVal); \
		QA_##a##_Data&	operator+=(const a &otherFace); \
		QA_##a##_Data&	operator+=(const QA_##a##_Data &otherFace); \
		ProdBool	operator==(const a &otherFace); \
		ProdBool	operator==(const QA_##a##_Data &otherFace); \
		ProdBool	operator!=(const a &otherFace); \
		ProdBool	operator!=(const QA_##a##_Data &otherFace); \
		a*		operator->(void); \
		a&		operator*(void); \
		operator a(void); \
 \
	protected: \
		a fFace;	\
}; 

#define MAKE_NONORDINAL_DATA_HEADER(a) \
class AATLIB_DECL QA_##a##_Data : public CAATData \
{ \
	public: \
		QA_##a##_Data(void); \
		QA_##a##_Data(a var) : fFace(var) {} \
		QA_##a##_Data(a var, ProdString tag, \
						ProdString varName, \
						ProdString uiString = "", \
						ProdInt32 code = kInvalidUICode) : fFace(var), CAATData(tag, uiString, varName, code) {} \
		QA_##a##_Data(const QA_##a##_Data &data) : fFace(data.fFace), CAATData(data.fTag, ProdString(""), kInvalidUICode) {} \
		\
		virtual ~QA_##a##_Data() {} \
		\
		virtual VirtualType GetType(void); \
		\
		void	Set(a val); \
		a&	Get(void); \
		\
		QA_##a##_Data& 	operator=(const QA_##a##_Data& otherVal); \
		QA_##a##_Data& 	operator=(const a& otherVal); \
		ProdBool	operator==(const a &otherFace); \
		ProdBool	operator==(const QA_##a##_Data &otherFace); \
		ProdBool	operator!=(const a &otherFace); \
		ProdBool	operator!=(const QA_##a##_Data &otherFace); \
		a*		operator->(void); \
		operator a(void); \
 \
	protected: \
		a fFace;	\
}; 

class AATLIB_DECL QA_Indeterminate_Data : public CAATData
{ 
	public: 
		QA_Indeterminate_Data(void); 
		QA_Indeterminate_Data(VAATData *var);
		QA_Indeterminate_Data(VAATData *var, ProdString tag, 
						ProdString varName, 
						ProdString uiString = "", 
						ProdInt32 code = kInvalidUICode);
		QA_Indeterminate_Data(const QA_Indeterminate_Data &data); 
		
		virtual ~QA_Indeterminate_Data();
		
		virtual void	Write(IXMLOutStream *stream, ProdBool asModel);
		virtual void	Read(const ProdString &localName, ISAXAttributes* attrs);
		
		virtual void	Copy(VAATData *srcData);
		
		virtual VirtualType GetType(void) { return kIndeterminateType; } 
		
		virtual void	CreateFace(VirtualType theType);
		
		void	Set(VAATData *val); 
		VAATData*	Get(void) { return fFace; } 
		
		QA_Indeterminate_Data& 	operator=(const QA_Indeterminate_Data &otherVal); 
		
		ProdBool	operator==(const QA_Indeterminate_Data &otherFace);
		
		ProdBool	operator!=(const QA_Indeterminate_Data &otherFace);
		
	protected: 
		VAATData *fFace;
		ProdBool			fInSubData;
};

class AATLIB_DECL QA_QAFile_Data : public CAATData 
{ 
	public: 
		QA_QAFile_Data(void); 
		QA_QAFile_Data(QAFile var) : fFace(var) {} 
		QA_QAFile_Data(QAFile var, ProdString tag, 
						ProdString varName, 
						ProdString uiString = "", 
						ProdInt32 code = kInvalidUICode) : fFace(var), CAATData(tag, uiString, varName, code) {} 
		QA_QAFile_Data(const QA_QAFile_Data &data) : fFace(data.fFace), CAATData(data.fTag, ProdString(""), kInvalidUICode) {}
		
		virtual ~QA_QAFile_Data() {} 
		
		virtual VirtualType GetType(void); 
		virtual void	Read(const ProdString &localName, ISAXAttributes* attrs);

		virtual void	Copy(VAATData *srcData);
		
		void	Set(QAFile val); 
		QAFile&	Get(void); 
		
		//These are used exclusively for converstion of old dual path/relative T_DATA instances
		void	SetRelativePath(const ProdString &relPath);
		void	SetFilePath(const ProdString &path);
		ProdString	GetRelativePath();
		
		QA_QAFile_Data& 	operator=(const QA_QAFile_Data& otherVal); 
		QA_QAFile_Data& 	operator=(const QAFile& otherVal); 
		ProdBool	operator==(const QAFile &otherFace); 
		ProdBool	operator==(const QA_QAFile_Data &otherFace); 
		ProdBool	operator!=(const QAFile &otherFace); 
		ProdBool	operator!=(const QA_QAFile_Data &otherFace); 
		QAFile*		operator->(void); 
		operator QAFile(void); 
 
	protected: 
		virtual void	PushHeader(IXMLOutStream *stream);
		QAFile fFace;	
		ProdString fRelativePath;
		ProdString fFilePath;
}; 

class AATLIB_DECL QA_ScarfData_Data : public CAATData
{ 
	public: 
		QA_ScarfData_Data(void); 
		QA_ScarfData_Data(ScarfData var); 
		QA_ScarfData_Data(ScarfData var, ProdString tag); 
		QA_ScarfData_Data(ScarfData var, ProdString tag, 
						ProdString varName, 
						ProdString uiString = "", 
						ProdInt32 code = kInvalidUICode); 
		QA_ScarfData_Data(const QA_ScarfData_Data &data); 
		
		virtual ~QA_ScarfData_Data() {} 
		
		virtual VirtualType GetType(void); 
		
		virtual void	Write(IXMLOutStream *stream, ProdBool asModel);
		
		void	Set(ScarfData val); 
		
		ScarfData&	Get(void); 
		
		QA_ScarfData_Data& 	operator=(const QA_ScarfData_Data& otherVal); 
		QA_ScarfData_Data& 	operator=(const ScarfData& otherVal);
		QA_ScarfData_Data&	operator+=(const ScarfData &otherFace); 
		QA_ScarfData_Data&	operator+=(const QA_ScarfData_Data &otherFace); 
		ProdBool	operator==(const ScarfData &otherFace); 
		ProdBool	operator==(const QA_ScarfData_Data &otherFace); 
		ProdBool	operator!=(const ScarfData &otherFace); 
		ProdBool	operator!=(const QA_ScarfData_Data &otherFace); 
		ScarfData*		operator->(void); 
		ScarfData&		operator*(void); 
		operator ScarfData(void); 
 
	protected: 
		ScarfData fFace;	
}; 

#define QADATA_INSTANCE(a) QA_##a##_Data




MAKE_QADATA_HEADER(PMReal)
MAKE_QADATA_HEADER(PMString)
MAKE_QADATA_HEADER(int32)
MAKE_QADATA_HEADER(uint32)
MAKE_QADATA_HEADER(char)
MAKE_QADATA_HEADER(bool16)
MAKE_QADATA_HEADER(QARect)
MAKE_QADATA_HEADER(QAPoint)
MAKE_QADATA_HEADER(QAMeasurement)
MAKE_NONORDINAL_DATA_HEADER(UID)
MAKE_NONORDINAL_DATA_HEADER(UIDRef)
MAKE_NONORDINAL_DATA_HEADER(UIDList)


typedef QADATA_INSTANCE(QAFile) qaQAFile;
typedef QADATA_INSTANCE(Indeterminate) qaIndeter;
typedef QADATA_INSTANCE(PMReal) qaReal;
typedef QADATA_INSTANCE(PMString) qaString;
typedef QADATA_INSTANCE(int32) qaInt32;
typedef QADATA_INSTANCE(uint32) qaUInt32;
typedef QADATA_INSTANCE(char) qaChar;
typedef QADATA_INSTANCE(bool16) qaBool16;
typedef QADATA_INSTANCE(QARect) qaQARect;
typedef QADATA_INSTANCE(QAPoint) qaPoint;
typedef QADATA_INSTANCE(QAMeasurement) qaQAMeasurement;
typedef QADATA_INSTANCE(UID) qaUID;
typedef QADATA_INSTANCE(UIDRef) qaUIDRef;
typedef QADATA_INSTANCE(UIDList) qaUIDList;
typedef QADATA_INSTANCE(ScarfData) qaScarfData;



#endif //__AATDataTypes__
