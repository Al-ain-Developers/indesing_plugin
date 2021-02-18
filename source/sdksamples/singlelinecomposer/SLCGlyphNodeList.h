//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/singlelinecomposer/SLCGlyphNodeList.h $
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

#ifndef __SLCGlyphNodeList_h__
#define __SLCGlyphNodeList_h__

class IComposeScanner;
class IDrawingStyle;
class PMReal;

/** Intermediate representation of composed text in the line maintained as a
 * 	list of pointers to glyph nodes (SLCGlyphNode).
 *
 * 	@ingroup singlelinecomposer
 *
 * 	@see SLCGlyphNode
*/
class SLCGlyphNodeList
{
public:
	/** Create a new glyph node and add it to the list. The type of node
		to be created is determined by the type of character at the given
		startingIndex.
		@param composeScanner IN for the story.
		@param drawingStyle IN for the run of text.
		@param startingIndex IN into the text model of the first character in the run.
		@param xOffset IN relative to the left edge of the wax line.
		@return pointer to new SLCGlyphNode object, the list retains ownership
		of the object.
	*/
	SLCGlyphNode* CreateGlyphNode(IComposeScanner* composeScanner,
								  IDrawingStyle* drawingStyle,
								  TextIndex startingIndex,
								  const PMReal& xOffset);

	/** Clear the list.
	*/
	void Clear(void);

	/** @return the number of SLCGlyphNode's in the list.
	*/
	int32 Length(void) const
	{
		return static_cast<int32>(fGlyphNodeList.size());
	}

	/** Delete the indicated SLCGlyphNode.
		@param index of node to be deleted.
	*/
	void Remove(int32 index)
	{
		fGlyphNodeList.erase(fGlyphNodeList.begin() + index, fGlyphNodeList.begin() + index + 1);
	}

	/** @param index of required node.
		@return pointer to the requested SLCGlyphNode.
	*/
	SLCGlyphNode* operator[](int32 index) const
	{
		return fGlyphNodeList[index];
	}

	/**	Return the number of characters in the nodes in the
		list from the given index to last node in the list.
		@param fromIndex of node at which to start.
		@return the number of characters in the nodes.
	*/
	virtual int32 GetTextSpan(int32 fromIndex = 0) const;

	/**	Return the width of the characters in the nodes.
		@param fromIndex of node at which to start.
		@return the width of the characters in the nodes.
	*/
	PMReal GetWidth(int32 fromIndex) const;

	/** Return the width of the trailing white space.
		@param fromIndex search back from the end of the list to this index.
		@return the width of the trailing white space characters.
	*/
	PMReal GetTrailingWhiteSpaceWidth(int32 fromIndex) const;

	/** Adjust the width of any trailing white space in the node by
		the given scale factor.
		@param fromIndex IN fit from the end of the list to this index.
		@param widthScaleFactor IN The scaling factor of the trailing white space.
		@see SLCGlyphNode::FitTrailingWhiteSpace
	*/
	void FitTrailingWhiteSpace(int32 fromIndex, const PMReal& widthScaleFactor);

	/** Trace the nodes.
	*/
	virtual void Dump(int32 fromIndex = 0, const char* msg = "") const;

private:
	/** Vector of pointers to heap allocated nodes.
	*/
	K2Vector<SLCGlyphNode*> fGlyphNodeList;
};

#endif // __SLCGlyphNodeList_h__

// End, SLCGlyphNode.h

