//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlist/PstLstScript.cpp $
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

// Interface includes:


// Implementation includes:
#include "CScript.h"
#include "PstLstID.h"
#include "PstLstScriptingDefs.h"
#include "IPstLstData.h"

/** Provides details as to what ScriptID is associated with this script object, 
	the "persistent list data item" object.
	@ingroup persistentlist
*/
class PstLstScript : public CScript
{
public:
	/**	Constructor 
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	PstLstScript(IPMUnknown* boss);

	/** Destructor.  
	*/
	virtual ~PstLstScript(void);

	/** Return the object's type.
	 * 	@return The object's ScriptID.
	 */
	virtual ScriptID GetObjectType( const RequestContext& context ) const;

	/**	Return the parent of this object in the script DOM hierarchy.
	 * 	IDOMElement::QueryParent delegates to this method. 
	 * 	@param iid IN IID of interest on the parent DOM object.
	 * 	@return An interface pointer to the IID of interest on the parent DOM object. 
	 */
	virtual IPMUnknown* QueryParent( const PMIID& iid, const RequestContext& context ) const ;

private:
	/** script ID (Object) of this script object */
	ScriptID fScriptClassID;
};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(PstLstScript, kPstLstScriptImpl)


/* PstLstScript Constructor
*/
PstLstScript::PstLstScript(IPMUnknown* boss)
: 	CScript(boss), 
	fScriptClassID(c_PstLstDataItem)
{
	// do nothing
}

/* PstLstScript Dtor
*/
PstLstScript::~PstLstScript(void)	
{
	// do nothing
}

/* GetObjectType
*/
ScriptID PstLstScript::GetObjectType( const RequestContext& context ) const
{
	return fScriptClassID;
}

/* QueryParent 
*/
IPMUnknown* PstLstScript::QueryParent( const PMIID& iid, const RequestContext& context ) const
{
	IPMUnknown* result = nil;
	do
	{
		// At InDesign CS2 a back reference was added to the data model for this plug-in
		// so that a kPstLstDataBoss object stores the UID of the boss object that owns it.
		// The scripting implementation uses it here to find the parent boss.
		InterfacePtr<IPstLstData> pstLstData(this, UseDefaultIID());
		ASSERT(pstLstData);
		if (!pstLstData) 
		{
			break;
		}
		InterfacePtr<IScript> parent(::GetDataBase(this), pstLstData->GetParent(), UseDefaultIID());
		ASSERT(parent);
		if (!parent) 
		{
			break;
		}
		result = parent;
		result->AddRef();
	} while (false);
	if (result == nil)
	{
		ASSERT_FAIL("PstLstScript::QueryParent - Could not determine the parent of a kPstLstDataBoss!!");
	}
	return result;
}

// End, PstLstScript.cpp.
