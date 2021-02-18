//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/AttributeChecker.h $
//  
//  Owner: Eric Menninga
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
//  Class Descriptions:
//  
//  This file contains definition of a class designed for use 
//  with the IGlobalRecompose::GlobalAttributeDamage(). The
//  methods checks if a range of text contains attributes specified
//  in the argument boss list.  A subsequent damage will occur to the
//  range of text if such attribute is found in text.
//  
//========================================================================================

#pragma once
#ifndef __AttributeChecker__
#define __AttributeChecker__

class IDrawingStyle;
class IWaxLine;
class AttributeBossList;
class IStoryOptions;

// destructors live in PMTextUtils.cpp


#pragma export on

/** This class is used to test ranges of text for recomposition by IGlobalRecompose.
	@see IGlobalRecompose
*/
class PUBLIC_DECL AttributeChecker // : public unary_function<IDrawingStyle*, bool16>
{
	public:
		AttributeChecker() : fOnlyCheckParaAttrs(kFalse) {}
		virtual ~AttributeChecker();

		/** 
			@param style is the compressed summary of all text attributes.
			@param story is the story being examined.
			@param start is the beginning position of the range in question.
			@param length is the length of the range.
			@return kTrue if the desired range should be damaged, kFalse to leave the range alone.
		*/
		virtual bool16 operator()(IDrawingStyle *style, UID story, TextIndex start, int32 length) const = 0;

		bool16	OnlyCheckParaAttrs() const
			{ return fOnlyCheckParaAttrs; }
			
	protected:
		bool16	fOnlyCheckParaAttrs;
};
//----------------------------------------------------


/** This class is used to test wax lines for recomposition by IGlobalRecompose.
	@see IGlobalRecompose
*/
class PUBLIC_DECL WaxLineChecker // : public unary_function<IWaxLine*, bool16>
{
	public:
		virtual ~WaxLineChecker();

		/** 
			@param line is the wax line in question.
			@param story is the story being examined.
			@param start is the beginning position of the line in question.
			@param length is the length of the line.
			@return kTrue if the desired line should be damaged, kFalse to leave the line alone.
		*/
		virtual bool16 operator()(IWaxLine *line, UID story, TextIndex start, int32 length) const= 0;
};
//----------------------------------------------------


/** This class is used to test ranges of text for recomposition by IGlobalRecompose.
	This class uses the styles & local overrides directly, unlike AttributeChecker, which
	only gets the summarized IDrawingStyle version of the text attributes.
	@see IGlobalRecompose
*/
class PUBLIC_DECL ModelChecker
{
	public:
		virtual ~ModelChecker();

		/** 
			@param storyThreadStyle is the style applied to the entire story thread.
			@param paraStyle is the paragraph style applied to the range.
			@param paraOver is the list of overrides to the paragraph attributes.
			@param charStyle is the applied character style.
			@param charOver is the character attribute overrides applied to the range.
			@param story is the story being examined.
			@param start is the beginning position of the range in question.
			@param length is the length of the range.
			@return kTrue if the desired range should be damaged, kFalse to leave the range alone.
		*/
		virtual bool16 operator()( UID storyThreadStyle,
								UID paraStyle, const AttributeBossList *paraOver, 
								UID charStyle, const AttributeBossList *charOver,
								UID story, TextIndex start, int32 length) const= 0;
};
//----------------------------------------------------


/** This class is used to test story options for recomposition by IGlobalRecompose.
	@see IGlobalRecompose
*/
class PUBLIC_DECL StoryOptionsChecker
{
	public:
		virtual ~StoryOptionsChecker();

		/** 
			@param storyOptions is the storyOptions for the story in question.
			@param story is the story being examined.
			@param start is the beginning position of the line in question.
			@param length is the length of the line.
			@return kTrue if the desired story should be damaged, kFalse to leave the story alone.
		*/
		virtual bool16 operator()(IStoryOptions *storyOptions, UID story, TextIndex start, int32 length) const= 0;
};
//----------------------------------------------------


#pragma export off


#endif
		// __AttributeChecker__
