//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalinkui/CusDtLnkUITreeDataNode.cpp $
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

// Interface includes

// Other API includes
#include "K2Vector.tpp"
#include "SDKFileHelper.h"
#include "URI.h"
// Project includes
#include "CusDtLnkUITreeDataNode.h"
#include "CusDtLnkID.h"



/**
	@ingroup customdatalinkui
*/

/* Constructor
*/
CusDtLnkUITreeDataNode::CusDtLnkUITreeDataNode() : fParent(nil)
{
}


/* Destructor
*/
CusDtLnkUITreeDataNode::~CusDtLnkUITreeDataNode()
{
}


/* Copy constructor
*/
CusDtLnkUITreeDataNode::CusDtLnkUITreeDataNode(const CusDtLnkUITreeDataNode& rhs) : fParent(nil)
{
	deepcopy(rhs);
}

/* Overloaded =
*/
CusDtLnkUITreeDataNode& CusDtLnkUITreeDataNode::operator=(const CusDtLnkUITreeDataNode& rhs)
{
	deepcopy(rhs);
	return *this;
}


/* Overloaded ==
*/
bool CusDtLnkUITreeDataNode::operator==(const CusDtLnkUITreeDataNode& rhs) const
{
	return		this->fParent == rhs.fParent &&
				this->fUniqueKey == rhs.fUniqueKey &&
				this->fChildren == rhs.fChildren &&
				this->fNodeType == rhs.fNodeType &&
				this->fAssetRecordValues == rhs.fAssetRecordValues &&
				this->fAssetDataBasePath == rhs.fAssetDataBasePath;
}


/* deepcopy
*/
void CusDtLnkUITreeDataNode::deepcopy(const CusDtLnkUITreeDataNode& rhs)
{
	this->fChildren.clear();
	this->fAssetRecordValues.clear();
	//Can we replace by:
	// this->fChildren = rhs.fChildren;
	this->fChildren.assign( rhs.fChildren.begin(), rhs.fChildren.end());
	this->fParent = rhs.fParent;
	this->fUniqueKey = rhs.fUniqueKey;

	// Assignment operator: see http://www.sgi.com/tech/stl/Map.html
	this->fAssetRecordValues = rhs.fAssetRecordValues;

	this->fNodeType = rhs.fNodeType;
	this->fAssetDataBasePath = rhs.fAssetDataBasePath;
}


/* GetNthChild
*/
const CusDtLnkUITreeDataNode& CusDtLnkUITreeDataNode::GetNthChild(
	int32 indexInParent) const
{
	return this->fChildren.at(indexInParent);
}


/* AddChild
*/
void CusDtLnkUITreeDataNode::AddChild(const CusDtLnkUITreeDataNode& o)
{
	this->fChildren.push_back(o);
}


/* RemoveChild
*/
void CusDtLnkUITreeDataNode::RemoveChild(const CusDtLnkUITreeDataNode& o)
{
	K2Vector<CusDtLnkUITreeDataNode>::iterator result = std::find(fChildren.begin(),
													fChildren.end(), o);

	if(result != fChildren.end())
	{
		fChildren.erase(result);
	}
}


/* GetParent
*/
CusDtLnkUITreeDataNode* CusDtLnkUITreeDataNode::GetParent() const
{
	return this->fParent;
}


/* SetParent
*/
void CusDtLnkUITreeDataNode::SetParent(const CusDtLnkUITreeDataNode* p)
{
	this->fParent = const_cast<CusDtLnkUITreeDataNode* >(p);
}


/* ChildCount
*/
int32 CusDtLnkUITreeDataNode::ChildCount() const
{
	return this->fChildren.size();
}


/* SetData
*/
void CusDtLnkUITreeDataNode::SetUniqueKey(const PMString& uk)
{
	ASSERT(uk.CharCount()>0);
	this->fUniqueKey = uk;
}


/* GetData
*/
PMString CusDtLnkUITreeDataNode::GetUniqueKey() const
{
	return this->fUniqueKey;
}


CusDtLnkUITreeDataNode::TreeDataNodeType CusDtLnkUITreeDataNode::GetNodeType() const
{
	return this->fNodeType;
}

void CusDtLnkUITreeDataNode::SetNodeType(CusDtLnkUITreeDataNode::TreeDataNodeType typ)
{
	this->fNodeType = typ;
}


void CusDtLnkUITreeDataNode::SetAssetDataBasePath(const PMString& dbPath)
{
	this->fAssetDataBasePath = dbPath;
}

PMString CusDtLnkUITreeDataNode::GetAssetDataBasePath() const
{
	return this->fAssetDataBasePath;
}

void CusDtLnkUITreeDataNode::AddAssetRecordValue(const PMString& name, const PMString& val)
{
	this->fAssetRecordValues.insert(std::pair<PMString,PMString>(name,val));
}

int32 CusDtLnkUITreeDataNode::GetAssetRecordFieldCount() const
{
	return static_cast<int32>(this->fAssetRecordValues.size());
}


PMString CusDtLnkUITreeDataNode::GetNthAssetRecordFieldName(int32 index) const
{
	std::map<PMString,PMString> :: const_iterator begin = fAssetRecordValues.begin();
	std::map<PMString,PMString> :: const_iterator end = fAssetRecordValues.end();
	std::map<PMString,PMString> :: const_iterator iter = begin;
	if(index < distance(begin, end)) {
		for(int32 i=0; i < index && iter != end; i++, iter++) {
			// NOP
			// Deliberately do nothing
		}
	}

	if(iter != end) {
		return iter->first;
	}
	return PMString("");
}

PMString CusDtLnkUITreeDataNode::GetAssetRecordFieldValue(const PMString& key) const
{
	PMString retval;
	std::map<PMString,PMString> :: const_iterator iter = this->fAssetRecordValues.find(key);
	if(iter != this->fAssetRecordValues.end()) {
		retval = iter->second;
	}
	return retval;
}

IDFile CusDtLnkUITreeDataNode::ResolveAssetPath() const
{
	IDFile retval;
	do {
		// Please don't call this if your node is not eAssetType
		bool16 correctContext = (this->GetNodeType() == eAssetType);
		ASSERT(correctContext);
		if(!correctContext) {
			break;
		}

		SDKFileHelper dbFileHelper(this->GetAssetDataBasePath());
		ASSERT(dbFileHelper.IsExisting());
		PMString assetFieldName(kCusDtLnkAssetDataBaseAssetPathFieldNameKey, PMString::kTranslateDuringCall);
		PMString assetVal = this->GetAssetRecordFieldValue(assetFieldName);
		//ASSERT(!assetVal.empty());
		// If it is empty, then the asset path field is not what we think
		if(assetVal.empty()) {
			break;
		}
		retval = dbFileHelper.GetAbsoluteFromRelative(assetVal);

	} while(kFalse);

	return retval;
}

URI CusDtLnkUITreeDataNode::GetURIFromNode() const
{
	PMString	dbPath = this->GetAssetDataBasePath();
	PMString	recordIDFieldName(kCusDtLnkAssetDataBaseRecordIDFieldNameKey, PMString::kTranslateDuringCall);
	PMString	recordID = this->GetAssetRecordFieldValue(recordIDFieldName);
	URI	uri;
	uri.SetComponent(URI::kScheme, WideString(kCusDtLnkScheme));
	uri.SetComponent(URI::kPath, WideString(dbPath));
	uri.SetComponent(URI::kQuery, WideString(recordID));
	return uri;
}

CusDtLnkUITreeDataNode::AssetState CusDtLnkUITreeDataNode::GetAssetState() const
{
	CusDtLnkUITreeDataNode::AssetState retval = CusDtLnkUITreeDataNode::eStateProvisional;

	do {
		PMString stateFieldName(kCusDtLnkAssetDataBaseStatusFieldNameKey, PMString::kTranslateDuringCall);
		PMString stateVal = this->GetAssetRecordFieldValue(stateFieldName);
		// If it is empty, then the lock-state field is not what we think
		if(stateVal.empty()) {
			break;
		}
		stateVal.ToLower();

		const PMString phSymb("placeholder");
		const PMString provSymb("provisional");
		const PMString finSymb("final");
		bool16 isPH = (stateVal.Compare(kFalse, phSymb) == 0);
		if(isPH) {
			retval = eStatePlaceholder;
			break;
		}
		bool16 isProv = (stateVal.Compare(kFalse, provSymb) == 0);
		if(isProv) {
			retval = eStateProvisional;
			break;
		}
		bool16 isFin = (stateVal.Compare(kFalse, finSymb) == 0);
		if(isFin) {
			retval = eStateFinal;
			break;
		}

	} while(kFalse);

	return retval;
}

PMString CusDtLnkUITreeDataNode::GetDescription() const
{
	PMString descFieldName(kCusDtLnkAssetDataBaseDescriptionFieldNameKey, PMString::kTranslateDuringCall);
	return this->GetAssetRecordFieldValue(descFieldName);
}


//	end, File:	CusDtLnkUITreeDataNode.cpp
