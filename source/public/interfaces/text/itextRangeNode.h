//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/itextRangeNode.h $
//  
//  Owner: Jianlan Song
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

#ifndef __ITEXTRANGENODE__
#define __ITEXTRANGENODE__

#include "IPMUnknown.h"
#include "TextID.h"
#include "SBOSReference.h"

class ITextRangeNode;
typedef SBOSReference<ITextRangeNode> TextRangeReference;
typedef K2Vector<TextRangeReference> RangeRefList;

extern const TextRangeReference kInvalidTextRange;

/** This interface represents text range node on the text range Red-Black tree
	inside text range strand. Each node is a small boss object representing
	the text range and associated text object. The start index is used as key
	for each node.
*/
class INTERFACE_DECL ITextRangeNode : public IPMUnknown 
{
public:
	enum { kDefaultIID = IID_ITEXTRANGENODE };

	typedef struct _TextRange
	{
		_TextRange(TextIndex start, int32 length) : startIndex(start), rangeLength(length) {}
		
		TextIndex startIndex;
		int32 rangeLength;
	} TextRange;

	/** Initialize the text range node.
		@param range - text range of the node.
		@param baseUIDRef - UIDRef of the text object occupying the range. 
		@param subItemKey - sub key of the text object if it is not a UID based object.
	*/
	virtual void Initialize(ITextRangeNode::TextRange range, UIDRef baseUIDRef, uint32 subItemKey = 0) = 0;

	/** Gets the UIDRef of the text object.
		@return UIDRef - UIDRef of the text object occupying the range. 
	*/
	virtual UIDRef GetBaseUIDRef() const = 0;
	/** Gets the sub key of the text object.
		@return uint32 - sub key of the text object. 0 if the object is UID based object. 
	*/
	virtual uint32 GetSubKey() const = 0;
	/** Gets the owning story of the text object.
		@return UIDRef - story of the text object occupying the range. 
	*/
	virtual UIDRef GetOwningStoryUIDRef() const = 0;
	/** Sets the UIDRef and sub key of the text object.
		@param baseUIDRef - UIDRef of the text object occupying the range. 
		@param subItemKey - sub key of the text object. 0 for UID based object.
	*/
	virtual void SetObjectID(UIDRef baseUIDRef, uint32 subItemKey = 0) = 0;
	
	/** Gets the key/start index of the text range node. 
		@return TextIndex - start index of the text range. 
	*/
	virtual TextIndex GetKey() const = 0;
	virtual TextIndex GetStartIndex() const = 0;
	/** Sets the start index offset of the text range node from its parent. 
		@param newOffset - start index offset of the node. 
	*/
	virtual void SetStartIndexOffset(TextIndex newOffset) = 0;
	/** Sets the range length of the text range node. 
		@param length - length of the node. 
	*/
	virtual void SetRangeLength(int32 length) = 0;
	/** Gets the range length of the text range node. 
		@return int32 - length of the node. 
	*/
	virtual int32 GetRangeLength() const = 0;
	/** Gets the text range of the text range node. 
		@return TextRange - text range of the node. 
	*/
	virtual TextRange GetTextRange() const = 0;
	
	/** Gets the start index offset from the parent node. 
		@return TextIndex - start index offset of the node. 
	*/
	virtual TextIndex GetParentOffset() const = 0;
	/** Gets the absolute value of start index offset from the parent node. 
		@return TextIndex - absolute start index offset of the node. 
	*/
	virtual TextIndex GetAbsoluteParentOffset() const = 0; 
	
	/** Get/Set method of text range reference of the node, its parent and children. 
	*/
	virtual TextRangeReference GetSelfRef() const =0;
	virtual void SetSelfRef(TextRangeReference ref) =0;
	virtual TextRangeReference GetParentRef() const =0;
	virtual void SetParentRef(TextRangeReference ref) =0;
	virtual TextRangeReference GetLeftRef() const =0;
	virtual void SetLeftRef(TextRangeReference ref) =0;
	virtual TextRangeReference GetRightRef() const =0;
	virtual void SetRightRef(TextRangeReference ref) =0;

	/** Returns whevher the node is a red node. 
	*/
	virtual bool	IsRed() const = 0;
	/** Returns whevher the node's right child is a red node. 
	*/
	virtual bool	RightIsRed() const = 0;
	/** Returns whevher the node's left child is a red node. 
	*/
	virtual bool	LeftIsRed() const = 0;
	/** Returns whevher both children of the node are red nodes. 
	*/
	virtual bool IsThreeNode() const = 0;
	/** Mark the node as a red node. 
	*/
	virtual void	MakeRed() = 0;
	/** Mark the node as a black node. 
	*/
	virtual void	MakeBlack() = 0;
	/** Copy the color from the specified text range node. 
		@param from - text range node to copy color from.
	*/
	virtual void	CopyColor(const ITextRangeNode* from) = 0;
	virtual bool operator< ( const ITextRangeNode& t2 ) const = 0;
};

//DECLARE_BASE_TYPE(TextRangeReference);		// no special copy

#endif // __ITEXTRANGENODE__


