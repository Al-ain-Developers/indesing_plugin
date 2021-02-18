//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ISelectionExtension.h $
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
//  Note:		This is a sub-class of IPMUnknown that is used by the new selection manager to
//  be able to talk to the generic suites w/o knowing their specific types. You should
//  NOT emmulate this model without a very good reason. 
//  
//========================================================================================

#pragma once
	#ifndef _ISelectionExtension_
	#define _ISelectionExtension_
//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________
	#include "IPMUnknown.h"
	#include "ISelectionMessages.h"
//================================================================================================
//________________________________________________________________________________________________
//	CLASS FORWARDS
//________________________________________________________________________________________________
	class IControlView;
	class IDataBase;
	class ISelectionManager;
//________________________________________________________________________________________________
//	TYPEDEFS
//________________________________________________________________________________________________
		// ProtocolCollection is sorted
	typedef K2Vector<PMIID>	ProtocolCollection;

/**	ISelectionExtension extends a selection suite interface
*/
class ISelectionExtension : public IPMUnknown
	{
	//____________________________________________________________________________________________
	//	Member functions
	//____________________________________________________________________________________________
	public:
/**						When the selection changes (i.e. something was added to or removed from 
						the selection), the CSB's corresponding selection suite will update the 
						CSB's data interface and then call IConcreteSelection::SelectionChanged()
						which will notify each ISuite via this member function before broadcasting
						the change to the client code.
		
						A subclass should use this member fucntion to set a flag that any caches
						it has may have become stale. The next access to the suite would then 
						rebuild the cache. Do not rebuild the cache in response to this message
						there may not be any attached clients using your suite functionality.
		
						This is called on all ISuites that exist on the CSB which is changing and
						on Integrator suites (on the ASB). On CSBs the void* is not used and is
						nil.
						The ASB will send a selection changed message when the enabled CSBs have
						changed. It passes information in the void* of type 
						ISelectionChangedISuiteMessage. This does not pre-empt the normal selection
						change message that is always sent.
						
						@param x SuiteBroadcastData
						@param messageID PMIID
						@param y void star 
*/
		virtual void			SelectionChanged (SuiteBroadcastData*x, const PMIID& messageID, void*y) = 0;
		
/**						This member function is called whenever some attribute of the items that
						make up selection have changed. For instance if a page item is selected 
						and a script changes its color, an observer will see the change and call
						this member function. If the change doesn't affect your data, then your
						clients do not need to be updated.
							If the attribute change applies to the selection AND the suite wants
						to broadcast something to it's clients. It first checks to see if it already
						has an entry in SuiteBroadcastData*. If it does, it modifies the entry.
						Otherwise, it appends new data to the list.
							The void* is CSB specific. It contains the details of the update 
						message. For example, the LayoutCSB passes the parameters from Observer::Update 
						to this routine in a struct, IDocumentBroadcastMsg. The TableCSB and 
						TextCSB pass nil. The Graphic attribute caches on the CSBs also use this 
						member function in a proprietary way, so the message ID should always be
						checked prior to downcasting the void*.
		
						This is only called on suites that exist on CSBs. Integrator suites on the
						ASB do NOT use this member function.
		
						@param x SuiteBroadcastData
						@param messageID PMIID
						@param y void star 
*/
		virtual void	SelectionAttributeChanged (SuiteBroadcastData*x, const PMIID& messageID, void*y) = 0;

/**						This member function is called when a suite on a CSB sends an integrator
						message. The ASB decodes the message and forwards it onto the integrator
						suite.
		
						It is possible for a disabled integrator suite to receive a message.
						@param x void star
						@parma y classID
						@parma z ISubject
						@parma i PMIID
						@parma j void star
						@parma k ISelectionManager
*/
		virtual void				HandleIntegratorSuiteMessage (void* x, const ClassID& y, ISubject* z, const PMIID& i, void* j, ISelectionManager* k) = 0;

/**						Return the IIDs that this suite is interested in observering. Somewhat CSB
						specific. For instance, in the Layout CSB, the protocol collection is used
						when attaching a document observer. Thereby allowing only one document 
						observer to be shared by all suites.
						
						@return ProtocolCollection the protocol collection
*/
		virtual ProtocolCollection*	CreateObserverProtocolCollection (void) = 0;

/**						Called when the suite's owning boss is initialized.
*/
		virtual void	Startup (void) = 0;

/**						Called when the suite's owning boss is about to be released.
*/
		virtual void	Shutdown (void) = 0;

	};

#endif // _ISelectionExtension_
