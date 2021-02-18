//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/aat/includes/IAATFactory.h $
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

#ifndef __IAATFactory__
	#define __IAATFactory__

#include "IPMUnknown.h"
#include "IXMLOutStream.h"

#include "AATArchID.h"
#include "ProductTypeDefs.h"

class VAATAction;
class IAATActionList;
class ITestSession;
class ISequenceList;
class IObjectFinder;
class ISequenceItem;
class IReadWriteTest;
class IReadWriteContainer;

#define AAT_FACTORY_ENTRY(a)  k##a##ID , &a::CreateAATAction

typedef VAATAction* (*Func) (void);

class IAATFactory : public IPMUnknown
{
	public:
		virtual ~IAATFactory() {}
		
		//Initialization
		virtual ProdBool Init(void) = 0;
		virtual ProdBool IsInited(void) = 0;
		
		//Access Any SequenceItem - can be filtered by ProdInterfaceID
		virtual ProdInt32			GetNumSequenceItems(ProdInterfaceID implID = kInvalidInterfaceID) = 0;
		virtual ISequenceItem*	QueryNthSequenceItem(ProdInt32 index, ProdInterfaceID implID = kInvalidInterfaceID) = 0;
		
		//Add/Remove Sequence List Types
		virtual ProdBool	AddSequenceList(ProdObjectID bossID) = 0;
		virtual ProdBool	RemoveSequenceList(ProdObjectID bossID) = 0;
		virtual ProdBool	RemoveSequenceList(ProdString listCode) = 0;
		
		virtual ProdInt32			GetNumSequenceLists() = 0;
		virtual ISequenceList* 	QueryNthSequenceList(ProdInt32 index) = 0;
		
		//Add/Remove Object Finder
		virtual ProdBool	AddObjectFinder(ProdObjectID bossID) = 0;
		virtual ProdBool	RemoveObjectFinder(ProdObjectID bossID) = 0;
		virtual ProdBool	RemoveObjectFinder(ProdUInt32 listCode) = 0;
		
		virtual ProdInt32			GetNumObjectFinders() = 0;
		virtual IObjectFinder* 	QueryNthObjectFinder(ProdInt32 index) = 0;
		
		//Add in IAATActionList id's and Bosses here
		virtual ProdBool 	AddAATActionList(ProdObjectID bossID) = 0;
		virtual ProdBool	RemoveAATActionList(const ProdString &listName) = 0;
		virtual ProdBool	RemoveAATActionList(ProdObjectID bossID) = 0;
		virtual ProdBool 	HasAATActionList(const ProdString &listName) = 0;
		
		//Create a new IAATActionList instance
		 
		// IAATActionList access methods
		virtual ProdInt32	GetNumAATActionLists() = 0;
		virtual IAATActionList* 	QueryNthAATActionList(ProdInt32 n) = 0; // returned list will be parentless
		 
		//Add/Remove a action creation method to the Factory
		virtual void	AddAATAction(const char *key, Func theFunc) = 0;
		virtual void	RemoveAATAction(const char *key) = 0;
		
		//Create a new AAT Action instance
		virtual VAATAction* 		NewAATAction(const char *key) = 0;
		virtual ProdBool		 	AATActionKeyExists(const char *key) = 0;
		virtual ProdBool			TranslateKey(const ProdString &oldID, ProdString &newID, const ProdReal &fileFormat) = 0;
		
		//Create new Sequence Items
		virtual IAATActionList* 		NewAATActionList(const ProdString &listName, ISequenceList *parent = nil) = 0;
		virtual ISequenceList*		NewSequence(const ProdString &str, const ProdString &seqType, ISequenceList *parent = nil) = 0;
		virtual ITestSession*		NewSession(const ProdString &str) = 0;
		virtual IObjectFinder*		NewObjectFinder(const ProdString &str, ProdUInt32 objType, ISequenceList *parent = nil) = 0;
		virtual IReadWriteContainer* 	NewReadWriteContainer(const ProdString &str, IReadWriteContainer* parent = nil) = 0;
		
		//Generic method to get an IReadWriteTest object.  Normally nameOrType is the Name of the object,
		//however, NewSequence requires a type and not a name, so for Sequences it must be 
		virtual IReadWriteTest*	NewReadWriteTestFromToken(const ProdString &tag, const ProdString &type = ProdString(""), const ProdString &name = ProdString(""), bool16 isNative = kTrue) = 0;
		
		//Write out an XML description of the model
		virtual void	WriteAATModel(IXMLOutStream *s) = 0;
};


#endif //__IAATFactory__



