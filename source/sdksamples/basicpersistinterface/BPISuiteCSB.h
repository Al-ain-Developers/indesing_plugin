//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicpersistinterface/BPISuiteCSB.h $
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

#ifndef __BPISuiteCSB_h__
#define __BPISuiteCSB_h__

class IBPISuite;
class WideString;

/** Base class for CSB (concrete selection boss) suite implementations of IBPISuite;  
	the CSB suites are responsible for doing all of the model specific work involved
	in accessing and manipulating IBPIData. 99% of the CSB suite implementation 
	of IBPISuite is provided here in this base class.

	Sub-classes implement BPISuiteCSB::GetTarget to examine the selection target for their CSB and determine the
	UID's of selected objects that have an IBPIData interface. For example BPISuiteLayoutCSB uses
	ILayoutTarget to get a UIDList of selected objects and BPISuiteTextCSB uses ITextTarget to
	get the range of text and the story that underlies the selection and it then figures out the
	UIDList of frame page items touched by the text selection that have IBPIData.
	
	Note that the client does not interact with the CSB suite directly, the client 
	interacts with the ASB only. The implementation of a CSB suite deals with the 
	selection format of its CSB.

	The CSB suite implementations are advanced i.e. they implement a selection extension. 
	A selection extension is needed to support notification when the selection changes 
	or a selection attribute (in this case IBPIData) changes. Please refer to the
	Selection fundamentals chapter in Programming Guide for more information on selection extensions. 

	@ingroup basicpersistinterface
	
	@see Selection fundamentals chapter in Programming Guide
*/
class BPISuiteCSB : public CPMUnknown<IBPISuite>
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	BPISuiteCSB (IPMUnknown* boss);
	
	/** Destructor. 
	 */
	virtual					~BPISuiteCSB (void);

//	Suite Member functions
public:
	/** See IBPISuite::CanApplyBPIData
	*/
	virtual bool16			CanApplyBPIData (void);

	/** See IBPISuite::ApplyBPIData
	*/
	virtual ErrorCode		ApplyBPIData(const WideString& value);

	/** See IBPISuite::CanGetBPIData
	*/
	virtual bool16			CanGetBPIData (void);

	/** See IBPISuite::GetBPIData
	*/
	virtual void			GetBPIData(K2Vector<WideString>& values);

//	Selection Extension functions 
public:
	/**
		This function is called when the selection sub-system starts up. Any suite initialization
		code can be placed in this funciton. Called for suites on the ASB and CSBs.
	*/
	virtual void				Startup			 					(void);

	/**
		This function is called when the selection sub-system shuts down. Any suite termination 
		code can be placed in this funciton. Called for suites on the ASB and CSBs.
	*/
	virtual void				Shutdown			 				(void);

	/**
		This function is called when an item is added to or removed from the selection.  Suites on the 
		changing CSB and the ASB are called.	
	*/
	virtual void				SelectionChanged 					(SuiteBroadcastData*, const PMIID&, void*);

	/**
		This function is called when an attribute of the selection has changed. It is only called on the CSB whose
		selection attribute has changed. For the layout CSB an ProtocolCollection must be supplied first.
	*/
	virtual void				SelectionAttributeChanged 			(SuiteBroadcastData*, const PMIID&, void*);

	/**
		This is only supported on the ASB and is rarely used.
	*/
	virtual void				HandleIntegratorSuiteMessage		(void*, const ClassID&, ISubject*, const PMIID&, void*);

	/**
		Each suite must define the protocols that contain the attributes that they care about. The Layout CSB's selection 
		attribute observer asks each suite with a selection extension for a list of protocols to observer on the document.  
		Thereby, allowing all suites to share a single observer. When a document broadcast occurs with the specified 
		protocol, the suite must first determine if the command affects the selection by comparing the commands target to 
		the LayoutTarget (This is necessary because all commands don't use the UIDList for page items.).	
	*/
	virtual ProtocolCollection*	CreateObserverProtocolCollection 	(void);

// Member functions to be overriden by each CSB sub-class.
protected:
	/** Each CSB suite examines its target interface (ILayoutTarget, ITextTarget etc.) and
		returns the list of objects that are selected and might have IBPIData.
		@return a list of the objects that are selected.
	*/
	virtual UIDList GetTarget(void) = 0;
	
private:
	/**	BPISuiteCSB::SelectionAttributeChanged will be called for all notifications broadcast
		by the model the CSB observes. Some of these changes may be for objects that are not
		selected. This method establishes if there is an intersection between the given list 
		of objects and the list of objects returned by BPISuiteCSB::GetTarget.
		@param itemList list of objects whose IBPIData have changed.
		@return kTrue if the given list of objects intersects the selection target.
	*/
	virtual bool16 IntersectsTarget(const UIDList& itemList);							
};

#endif