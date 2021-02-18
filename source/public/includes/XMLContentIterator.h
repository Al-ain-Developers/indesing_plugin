//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/XMLContentIterator.h $
//  
//  Owner: Lonnie Millett
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
#ifndef __XMLContentIterator__
#define __XMLContentIterator__

#include "IIDXMLElement.h"
#include "TextRange.h"

/** XMLContentIterator iterates over the content of an element and returns ranges of content
	in the same order as the DOM would return content.  Text ranges are specified using the TextRange
	class.  These can in turn be used to create TextIterators for iterating over the individual characters
	of the content.
	The constructors for this class are intended to be created with the factory methods begin and end of XMLElement.
*/
class PUBLIC_DECL XMLContentIterator
{
	public:

		typedef InDesign::TextRange value_type;
		typedef std::ptrdiff_t difference_type;
		typedef const value_type* pointer;
		typedef const value_type& reference;
		friend class const_iterator;
		typedef std::bidirectional_iterator_tag	iterator_category;

		/**	Default constructor
			
			@return  
		 */
		XMLContentIterator();

		/**	Copy constructor
		 */
		XMLContentIterator(const XMLContentIterator&);

		/**	Constructor
			@param element 
			@param position 
			
		 */
		XMLContentIterator(const IIDXMLElement* element, int32 position);

		/**	Destructor
		 */
		~XMLContentIterator();
		

		/**	Pointer dereference operator
			
			@return current TextRange 
		 */
		const InDesign::TextRange& operator * () const { ASSERT(fCurrent.IsValid()); return fCurrent;}

		/**	Member selection operator or 'smart pointer'
			
			@return ptr to current TextRange
		 */
		const InDesign::TextRange* operator -> () const { ASSERT(fCurrent.IsValid()); return &fCurrent;}

		/**	Assignment
			@param rhs object to copy state from
			@return result of assignment
		 */
		XMLContentIterator&	operator = (const XMLContentIterator& rhs);

		/**	Increment operator
			
			@return adjusted iterator
		 */
		XMLContentIterator& operator ++ ();

		/**	Increment by specified amount
			@return XMLContentIterator operator 
		 */
		XMLContentIterator operator ++ (int) {XMLContentIterator tmp(*this); ++(*this); return tmp;}

		/**	Operator decrement
			
			@return adjusted iterator 
		 */
		XMLContentIterator& operator -- ();

		/**	Operator decrement by specified amount
			@return adjusted iterator 
		 */
		XMLContentIterator operator -- (int) {XMLContentIterator tmp(*this); --(*this); return tmp;}

		/**	Addition-assignment operator
			@param n specifies number of positions to move iterator Position
			@return iterator adjusted appropriately 
		 */
		XMLContentIterator& operator += (int32 n);

		/**	Addition operator
			@param n 
			@return iterator adjusted appropriately  
		 */
		XMLContentIterator operator + (int32 n) const {return XMLContentIterator(*this) += n;}

		/**	Subtraction-assignment operator
			@param n 
			@return iterator adjusted appropriately  
		 */
		XMLContentIterator& operator -= (int32 n);

		/**	Substraction operator
			@param n 
			@return iterator adjusted appropriately 
		 */
		XMLContentIterator operator - (int32 n) const {return XMLContentIterator(*this) -= n;}

		/**	Accessor for location iterator starts from
			
			@return current location of iterator 
		 */
		int32 Position() const {return fPosition;}

		/**	Dereference operator for given Position
			@param i specifies Position of intereset
			@return TextRange marked up by given child element 
		 */
		//const InDesign::TextRange operator [] (int32 i) const  {XMLContentIterator tmp(*this); tmp += i; return *tmp;}

		/** Accessor for valid state of this

			@return whether this is valid
		*/
		bool16 IsValid() const { return fCurrent.IsValid(); }
	
		friend XMLContentIterator operator + (int32 n, const XMLContentIterator& rhs)     {return XMLContentIterator(rhs) += n;}
		friend bool operator ==(const XMLContentIterator& x, const XMLContentIterator& y) {return x.fCurrent.Start() == y.fCurrent.Start() && x.fCurrent.End() == y.fCurrent.End();}  
		friend bool operator !=(const XMLContentIterator& x, const XMLContentIterator& y) {return x.fCurrent.Start() != y.fCurrent.Start() || x.fCurrent.End() != y.fCurrent.End();}
		friend bool operator < (const XMLContentIterator& x, const XMLContentIterator& y) {return x.fPosition <  y.fPosition;}
		friend bool operator <=(const XMLContentIterator& x, const XMLContentIterator& y) {return x.fPosition <= y.fPosition;}
		friend bool operator > (const XMLContentIterator& x, const XMLContentIterator& y) {return x.fPosition >  y.fPosition;}
		friend bool operator >=(const XMLContentIterator& x, const XMLContentIterator& y) {return x.fPosition >= y.fPosition;}
	
	private:
		void CalcCurrentTextRange();
		bool16 GetElementMarkerPositions(ITextModel *textModel, IIDXMLElement *element, TextIndex *startIndex, TextIndex *endIndex);
		
		InterfacePtr<const IIDXMLElement> fElement;
		TextIndex fStartIndex;
		TextIndex fEndIndex;
		InDesign::TextRange fCurrent;
		int32 fPosition;
};

#endif
