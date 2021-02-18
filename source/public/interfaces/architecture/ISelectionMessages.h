//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ISelectionMessages.h $
//  
//  Owner: Michael Martz
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
//  Note:		This is not intended as an interface header. These are abstract C++ classes
//  which are used to communicate information from subjects to observers within the
//  selection architecture.
//  
//========================================================================================

#pragma once
	#ifndef _ISelectionMessages_
	#define _ISelectionMessages_
	
//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________
	//.......Interface headers....................................................................
	#include "IPMUnknown.h" 					// for the definition of INHERITFROM

	//.......Other headers........................................................................
	#include "K2SmartPtr.h"
	#include "K2Vector.h"
	#include "KeyValuePair.h"
	#include "TableTypes.h"
//________________________________________________________________________________________________
//	CLASS FORWARDS
//________________________________________________________________________________________________
	class ISubject;
	class SelectionSuiteData;
	class UIDList;
	class ITableModel;
	class XMLReference;
	class XMLAttributeReference;
	namespace InDesign { class TextRange;}
	class RangeData;
	class ITextSelectionSuite;
//________________________________________________________________________________________________
//	TYPEDEFS
//________________________________________________________________________________________________
	typedef K2Vector<KeyValuePair<PMIID,  boost::shared_ptr<SelectionSuiteData> > > SuiteBroadcastData; 	// sorted

	namespace Selection 
	{
		enum Action { kReplace, kAddTo, kRemoveFrom, kSetKeyObject };
		enum ScrollChoice { kDontScrollSelection, kScrollIntoView};
		enum LayoutScrollChoice { kDontScrollLayoutSelection, kScrollIntoViewIfNecessary, kAlwaysCenterInView };
	}


//________________________________________________________________________________________________
//	COMPILER DIRECTIVES
//________________________________________________________________________________________________
	#ifdef PUBLIC_BUILD
		#pragma export on
	#endif // PUBLIC_BUILD
//================================================================================================
//________________________________________________________________________________________________
//	CLASS DECLARATIONS
//________________________________________________________________________________________________ 
/**
	The internal selection message is used for communicating between the CSBs and the ASB. 
*/
class IInternalSelectionMessage INHERITFROM
	{
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		enum SelectionMessageType { kClientMessage, kASB_SuiteMessage, kSelectionChanged, kCSB_NeedsNotify };

	public:
		virtual ~IInternalSelectionMessage (void) {}
/**
				Return the message type of this message.
*/
		virtual SelectionMessageType GetMessageType (void) const = 0;

/**
				Return the ASB interface ID that is the destination of this message.

				Used only for messages of type: kASB_SuiteMessage
*/
		virtual PMIID GetASB_SuiteIID (void) const = 0;

/**
				Return the actual message. Unfortunately, a downcast based on 
					SelectionMessageType is necessary. For kClientMessage this is an 
					ISelectionMessage. It is ISuite specific for kASB_SuiteMessage.
*/
		virtual void* GetMessage (void) const = 0;
	
/**
			Return the CSB that is sending the message.
*/
		virtual ClassID GetCSB_ClassID (void) const = 0;

	};

/**
	When a ISuite broadcasts data to its client code, it must inherit from this class, so that
	the message object has a virtual destructor in order to de-allocate memory.
*/
class PUBLIC_DECL SelectionSuiteData INHERITFROM
	{
	public:
		typedef object_type data_type;
		virtual 	~SelectionSuiteData (void);
	};
/**
	This is the void* for kClientMessage. It is used when the selection or a selection attribute
	has changed. The suite on the CSB broadcasts the change and the ASB responds by broadcasting 
	to the client code. 
*/
class PUBLIC_DECL ISelectionMessage INHERITFROM
	{
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		virtual ~ISelectionMessage (void) {}
		/* 
		 ISelectionMessage had no explicit destructor, so the compiler created an empty **non-virtual** destructor for it.
		 The derived class SelectionMessage had a virtual destructor that deleted it's member suiteBroadcastData. This set up a nasty bug. 
		 If a SelectionMessage was deleted through a ISelectionMessage pointer the empty non-virtual destructor was called and the suiteBroadcastData 
		 was not freed. Sadly downstream code relied on it *not* being deleted. 
		 
		 Apple's clang compiler warns about deleting an object with a non virtual destructor, so I tried to fix the compiler warning by giving ISelectionMessage 
		 a virtual destructor, but then we started crashing in downstream code since the suiteBroadcastData was now being deleted.
		 
		 As far as I could tell, the SelectionMessage destructor was *never* called. In our codebase SelectionMessage instances are always allocated via operator new, are held
		 via an ISelectionMessage pointer and are deleted through that pointer. 
		 Allocation ony happens in SelectionManager.cpp, CConcreteSelection.cpp, and Default_CSB.cpp.
		 
		 As a result. I could work around this problem by declaring that SelectionMessage only holds a reference to the member suiteBroadcastData, rather than owning it.
		 Then I could add the missing virtual destructor to ISelectionMessage, make an empty destructor for SelectionMessage, and keep the compiler and downstream code happy.
		 
		 We really shouldnt be passing a naked ptr type for suiteBroadcastData through so many layers of code, with no clear indication (or an incorrect one) of who is responsible for deleting it.
		 Allocations like this should be wrapped in a boost::shared_ptr<ISelectionMessage> and then passed as a shared_ptr rather than passing the raw pointer. 
		 Practically though even fixing this one case is hard to retrofit into something as big as InDesign, and well beyond the scope of my clang compiler warnings task.
		 
		 In fact none of the abstract message classes in this file had declared virtual destructors, so I added one to each of them.
		 Thankfully this was the only one where a derived instance was being deleted through a pointer to the abstract baseclass.
		 
		 --djb 6/17/2012
		 */
		
		enum SelectionMessageType { kSelectionChanged, kSelectionAttributeChanged, kSelectionChanged_Frequent};

	public:
/**
			Return the message type of this message.
*/
		virtual SelectionMessageType GetMessageType (void) const = 0;

/**
				Was the suite affected by the change that caused this broadcast?
		
				Used by the kSelectionAttributeChanged message.
		
			kTrue / kFalse
*/
		virtual bool16 WasSuiteAffected (const PMIID&) const = 0;

/**
			Return the Suite data associated with this broadcast.
		
				Used by the kSelectionAttributeChanged message.
		
			Proprietary suite message (based on SelectionSuiteData)
*/
		virtual SelectionSuiteData*	GetSuiteBroadcastData (const PMIID&) const = 0;

/**
				Return the list of SuiteBroadcastData.
		
				Used by the IInternalSelectionMessage.
					DO NOT access the SuiteBroadcastData* directly.
		
		List of suite IID and Proprietary suite message pairs
*/
		virtual SuiteBroadcastData* GetSuiteBroadcastDataList (void) = 0;
	};

/**
This is the void* for IID_SELECTION_HIGHLIGHT_MESSAGE
*/
class PUBLIC_DECL ISelectionHighlightMessage INHERITFROM
	{
	public:
		virtual ~ISelectionHighlightMessage (void) {}
/**
				Return the CSB target of this message.
*/
		virtual ClassID GetCSB (void) const = 0;

/**
				Return the CSB-specific message data.
*/
		virtual void* GetMessage (void) const = 0;
	};

/**
//	This is the void* message in a SelectionHighlightMessage for a layout selection
*/
class PUBLIC_DECL ILayoutSelectionHighlightMessage INHERITFROM
	{
	public:
		virtual ~ILayoutSelectionHighlightMessage (void) {}
/**
			Return the list of items to deselect
*/
		virtual UIDList GetItemsToRemove (void) const = 0;

/**
			Return the list of items to add to the selection
*/
		virtual UIDList GetItemsToAdd (void) const = 0;

/**
			Return kTrue if the selection is a path selection
*/
		virtual bool16  IsPathSelection (void) const = 0;

/**
			Return kTrue if the suite should autoscroll.
*/
		virtual Selection::LayoutScrollChoice  GetAutoScroll (void) const = 0;
	};


/**
//	This is the void* message in a SelectionHighlightMessage for a layout selection
*/
class PUBLIC_DECL ISpreadSelectionHighlightMessage INHERITFROM
	{//SpreadSelectionSuite
	public:
		enum SpreadSelectionMessageType { kSelectionChanged, kKeyObjectChanged };
		
	public:
		virtual ~ISpreadSelectionHighlightMessage (void) {}
/**
			Return the list of items to deselect
*/
		virtual UIDList GetItemsToRemove (void) const = 0;

/**
			Return the list of items to add to the selection
*/
		virtual UIDList GetItemsToAdd (void) const = 0;

/**
			Return kTrue if the suite should autoscroll.
*/
		virtual Selection::LayoutScrollChoice  GetAutoScroll (void) const = 0;
		
		
		/**
		 Return the message type of this message.
		 */
		virtual SpreadSelectionMessageType GetMessageType(void) const = 0;
	};
	
	
/**
	Class used in ITextSelectionHighlightMessage to hold left and right track change deleted text highlight extension uid invormation.
*/
class SelectionExtension
	{
	public:
		SelectionExtension() : fLeftExtension(kInvalidUID), fRightExtension(kInvalidUID) { }
		SelectionExtension (UID leftExtension, UID rightExtension) { SetExtension (leftExtension, rightExtension); }
	
		
/**
			Set Extention
*/
		inline void SetExtension (UID leftExtension, UID rightExtension) { fLeftExtension = leftExtension; fRightExtension = rightExtension; }
		
/**
			Get Left Extention
*/
		inline UID GetLeftExtension () const { return fLeftExtension; }
/**
			Get Right Extention
*/
		inline UID GetRightExtension () const { return fRightExtension; }
		
	private:
		UID fLeftExtension;
		UID fRightExtension;
	};	

/**
	This is the void* message in a SelectionHighlightMessage for a text selection
*/
class PUBLIC_DECL ITextSelectionHighlightMessage INHERITFROM
	{
	public:
		virtual ~ITextSelectionHighlightMessage (void) {}
/**
		Return the previous range
*/
		virtual InDesign::TextRange GetOldRange (void) const = 0;

/**
		Return the new range
*/
		virtual InDesign::TextRange GetNewRange (void) const = 0;


		enum ScrollChoice { kDontScrollSelection, kScrollIntoView};
/**
		Get Auto scroll
*/
		virtual ScrollChoice GetAutoScroll( RangeData* ) const = 0;

/**
		Get Selection
*/
		virtual ITextSelectionSuite* GetSelection(void) const = 0;
		
/**
		Get Old Selection extension
*/
		virtual SelectionExtension GetOldSelectionExtension() const = 0;
/**
		Get New Selection extension
*/
		virtual SelectionExtension GeNewSelectionExtension() const = 0;
	};
	
/**
	This is the void* message in a SelectionHighlightMessage for a table selection
 You can pass in a nil table model for one of the table models if you only want to draw a new
		selection and not erase the old
*/
class PUBLIC_DECL ITableSelectionHighlightMessage INHERITFROM
	{
	public:
		virtual ~ITableSelectionHighlightMessage (void) {}
/**
				Returns the previous selection's table model
					Used to erase the old selection
*/
		virtual const ITableModel* GetPrevTableModel (void) const = 0;
/**
				Returns the cells previously selection
						Used to erase the old selection
*/
		virtual const GridArea GetPrevSelectedCells (void) const = 0;

/**
				Return the new selection's table model
					Used to draw the new selection
*/
		virtual const ITableModel* GetNewTableModel (void) const = 0;
/**
			Return the new end index
						Used to draw the new selection
*/
		virtual const GridArea GetNewSelectedCells  (void) const = 0;
	};

/**
	This is the void* message in a SelectionHighlightMessage for a layout selection
*/
class PUBLIC_DECL IXMLSelectionHighlightMessage INHERITFROM
	{
	public:
		virtual ~IXMLSelectionHighlightMessage (void) {}
/**
			Return the Elements to add to the selection
*/
		virtual const K2Vector<XMLReference>* GetElementsToAdd (void) const = 0;
/**
				Return the Elements to remove from the selection
*/
		virtual const K2Vector<XMLReference>* GetElementsToRemove (void) const = 0;

/**
				Return the Attributes to add to the selection
*/
		virtual const K2Vector<XMLAttributeReference>* GetAttributesToAdd (void) const = 0;
/**
				Return the Attributes to remove from the selection
*/
		virtual const K2Vector<XMLAttributeReference>* GetAttributesToRemove (void) const = 0;

	};

/**
	This is the void* object when the ASB broadcasts a SelectionChanged() message to the ISuites.
*/
class PUBLIC_DECL ISelectionChangedISuiteMessage INHERITFROM
	{
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		enum MessageType { kActiveCSBsChangedMessage };

	public:
		virtual ~ISelectionChangedISuiteMessage (void) {}
/**
				Return the message type.
*/
		virtual MessageType GetMessageType (void) const = 0;

/**
			Return a list of currently disabled CSBs. 
					(only valid for kActiveCSBsChangedMessage)
					The bool16 in the returned list has the enable value.
*/
		virtual const K2Vector<KeyValuePair<ClassID, bool16> >* GetEnabledCSBs (void) const = 0;

/**
			Return a list of enabled ISuites on the ASB.
						(only valid for kActiveCSBsChangedMessage)
*/
		virtual const K2Vector<PMIID>* GetEnabledSuiteInterfaces (void) const = 0;
	};

#pragma export off

#endif // _ISelectionMessages_