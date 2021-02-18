//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CXMLImportOptionsService.h $
//  
//  Owner: Ryan Gano
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

#include "IXMLImportOptionsService.h"

#include "K2Pair.h"
#include "K2Vector.tpp"

/**
This is used to store a list of selected states for
popup/radio groups and checkboxes.
*/
typedef K2Pair<int32, bool16> StoredValuePair;

/**
This is used to store a list of filetype data
*/
typedef K2Pair<PMString, PMString> FileTypeData;

//----------------------------------------------------------------------------------------
// XMLImportOptionsDefaultServiceProvider
//----------------------------------------------------------------------------------------
class PUBLIC_DECL CXMLImportOptionsServiceProvider : public CPMUnknown<IXMLImportOptionsService>
{
public:	
	CXMLImportOptionsServiceProvider(IPMUnknown *boss);
	
	// Use this to set each piece of data listed below
	virtual void Initialize(IDocument *doc);
	virtual K2Vector<int32> WarnOfChange(IXMLImportOptionsService *changedService, IControlView *controlView, int32 which);
	virtual void CommitChanges();
	
	virtual PMString GetGroupName() const {return fGroupName;}
	virtual int32 GetUIElementsCount() const {return fUIElementCount;}
	virtual bool16 IsNthElementEnabled(int32 n) const {return fStoredEnableState[n];}
	virtual IXMLImportOptionsService::kUIElementType GetNthElementType(int32 n) const {return static_cast<IXMLImportOptionsService::kUIElementType>(fStoredType[n]);}
	virtual PMString GetNthElementName(int32 n) const {return fElementName[n];}

	// Used for getting/setting the stored bool value (checkbox)
	virtual bool16 GetNthElementBoolValue(int32 n) const {return fStoredValue[n].second;}
	virtual void SetNthElementBoolValue(int32 n, bool16 newValue) {fStoredValue[n].second = newValue;}

	// Used for getting/setting the stored int value (popup or radio group)
	virtual int32 GetNthElementIntValue(int32 n) const {return fStoredValue[n].first;}
	virtual void SetNthElementIntValue(int32 n, int32 selected) {fStoredValue[n].first = selected;}

	// Used for getting/setting the filename (filename group)
	virtual IDFile GetNthElementFileName(int32 n) const {return fStoredFileName[n];}
	virtual void SetNthElementFileName(int32 n, IDFile fileName) {fStoredFileName[n] = fileName;}

	// Used for getting the default text (filename group)
	virtual PMString GetNthElementDefaultText(int32 n) const {return fStoredDefaultText[n];}

	virtual void GetNthFileTypeInfo(int32 n, PMString &typeName, PMString &extension) const
	{
		typeName = fStoredFileType[n].first;
		extension = fStoredFileType[n].second;
	}

	// Used to determine whether the control should be indented
	virtual bool16 ShouldIndentNthControl(int32 n) const {return fIndented[n];}

	// Used for only the popup
	virtual void GetNthElementPopupValueList(int32 n, K2Vector<PMString> &valueList) const {valueList = fValueList[n];}

protected:
	// Use the following methods to quickly add new UI elements or to clear the list of known elements
	void AddCheckbox(const PMString &name, bool16 enabled, bool16 state, bool16 indent = kFalse);
	void AddPopup(const PMString &name, const K2Vector<PMString> &values, bool16 enabled, int32 selection, bool16 indent = kFalse);
	void AddRadioGroup(const PMString &name, const K2Vector<PMString> &values, bool16 enabled, int32 selection, bool16 indent = kFalse);
	void AddFileName(const PMString name, const IDFile &fileName, const PMString &defaultText, const PMString &fileTypeFamily, const PMString &fileTypeExtension, bool16 enabled, bool16 state, bool16 indent);
	void ClearData();

	// These store the state information for each of the controls this service is in charge of
	// These values can be changed while the dialog is running
	mutable K2Vector<StoredValuePair>	fStoredValue;			// Store the current value or selected state
	K2Vector<bool16>					fStoredEnableState;		// Store whether this element is currently enabled or not
	K2Vector<IDFile>					fStoredFileName;		// Store the fiilename information for each object
	K2Vector<PMString>					fStoredDefaultText;		// Store the default text information for each object
	K2Vector<FileTypeData>				fStoredFileType;		// Store the filetype information for files

	// These values cannot be changed while the dialog is running
	K2Vector<int32>						fStoredType;			// Store what type of element this is
	PMString							fGroupName;				// Store the name of the group this service represents
	int32								fUIElementCount;		// Store the number of elements in this group
	K2Vector<PMString>					fElementName;			// Store the name of each element
	K2Vector<K2Vector<PMString> >		fValueList;				// Store the value list for popups and radio buttons
	K2Vector<bool16>					fIndented;				// Store whether or not this control should be indented

private:
	int32 AddDefaultElement(IXMLImportOptionsService::kUIElementType type, bool16 enabled, bool16 indent);
};	