//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/SnpRunnableScript.cpp $
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
#include "IApplication.h"
#include "IDataBase.h"
#include "IPMUnknown.h"
#include "IStringData.h"

// General includes:
#include "CProxyScript.h" // includes IScript.h and IPMUnknown.h

// Project includes:
#include "SnipRunID.h"
#include "SnipRunScriptingDefs.h"

/** Implements IScript via partial implementation CProxyScript.
 * 	The main purpose is to declare the class ScriptID.
 * 
 * 	@ingroup snippetrunner
 * 	@author Ken Sadahiro
*/
class SnpRunnableScript : public CProxyScript
{
public:
	/** Constructor */
	SnpRunnableScript(IPMUnknown* boss);

	/** Destructor */
	virtual ~SnpRunnableScript(void);

	/** Returns the database related to this object.
	 * 	Since the SnippetRunner isn't persistent, we just return 
	 * 	the application database.
	 */
	virtual IDataBase* GetDataBase(const RequestContext &context) const;

	/** Return information for the object specifier. 
	 * 	@param context is the request context  
	 */
	virtual ScriptObject GetScriptObject(const RequestContext &context) const;

private:
	IDataBase* fDB;
};

/* Make the implementation available to the application.
*/
CREATE_PMINTERFACE(SnpRunnableScript, kSnpRunnableScriptImpl)

/* Constructor
*/
SnpRunnableScript::SnpRunnableScript(IPMUnknown* boss) : 
	CProxyScript(boss)	
{
	// NOTE: this ScriptID must match that used in the call to 
	// IScriptUtils::CreateProxyScriptObject in SnpRunnableScriptProvider::AppendNthObject.
	fObjectType = c_SnpRunnable;
	fDB = nil;
}

/* Destructor
*/
SnpRunnableScript::~SnpRunnableScript(void) 
{
	// Do nothing.
}

/* GetDataBase
// A safe way to determine the appropriate database for this object. Most implementations
// can simply inherit and use the default implementation { return ::GetDataBase( this ) ; }
// but some script bosses are non-persistent, and should therefore override this method.
*/
IDataBase* SnpRunnableScript::GetDataBase(const RequestContext &context) const
{
	if (fDB == nil)
	{
		InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
		if (app == nil)
		{
			ASSERT_FAIL("Could not query IApplication!");
		}
		else
		{
			const_cast<SnpRunnableScript*>(this)->fDB = ::GetDataBase(app);
		}
	}
	return fDB;
}

/* GetScriptObject
*/
ScriptObject SnpRunnableScript::GetScriptObject(const RequestContext& context) const
{
	// identify script object by name
	PMString snippetName="";
	do
	{
		InterfacePtr<IStringData> snippetNameData(this, IID_ISNIPPETNAME);
		if (snippetNameData == nil)
		{
			ASSERT(snippetNameData);
			break;
		}
		snippetName = snippetNameData->Get();
	} while (false);
	return ScriptObject(ScriptData(snippetName), GetObjectType( context ), kFormName);
}

// End, SnpRunnableScript.cpp.

