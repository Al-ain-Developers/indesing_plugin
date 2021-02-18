//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/IXReferenceUID.h $
//  
//  Owner: Edmund Lui
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
//  Data interface for copying page items.
//  
//========================================================================================

#ifndef __IXReferenceUID__
#define __IXReferenceUID__

#include "IPMUnknown.h"
#include "ShuksanID.h"
#include "ISession.h"

class ICommand;

/** IXReferenceUID is used during copy operations to keep track of the copy context.
	If you have an object A that contains a UID to B, then if you are doing a copy of 
	both A and B you would like for the resulting A' to reference B'. IXReferenceUID
	is the class that makes this happen for you.
	
	Here's how it works. You group your copy operations together into a copy session.
	You call BeginXRefSession to start a new session. The session keeps a mapping of
	source UID to destination UID for every object that has been copied via IScrapUtils,
	or one of the standard copy commands. If an object has already been copied, the
	UID gets fetched back from IXReferenceUID instead of creating a whole other object.
	If the object has not yet been copied, a copy is made and a mapping for it added
	to IXReferenceUID.
	
	<pre>
	InterfacePtr<IXReferenceUID> xRef(GetExecutionContextSession(), UseDefaultIID());
	xRef->BeginXRefSession(srcDB, destinationDB);

	// ... Your copy operations go here...

	xRef->EndXRefSession();
	</pre>
	
	Calls to BeginXRefSession/EndXRefSession may be nested. If the nested context has
	the same source and destination databases as the enclosing context, then the UIDs
	that are added in the nested context are still accessible to the enclosing context
	after the nested context has been ended (EndXRefSession called). But if the databases
	don't match, then the nested context supercedes the enclosing context until the
	EndXRefSession is called, at which point the UIDs added in the nested context are
	popped off and the enclosing context is restored.
	
	@see IScrapUtils
*/
class IXReferenceUID : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXREFERENCEUID };

	/** Start a new copy context.
		@param pSrcDB source database
		@param pDestDB destination database
		@return previous nesting level (first returns zero)
	*/
	virtual int32 BeginXRefSession(IDataBase *pSrcDB, IDataBase *pDestDB) = 0;
	
	/** End a copy context.
		@return  returns current nesting level (last returns zero)
	*/
	virtual int32 EndXRefSession() = 0;

	/** Return the source database of the current context, or nil if there's no context.
	*/
	virtual IDataBase *GetSrcDB() = 0;
	
	/** Return the destination database of the current context, or nil if there's no context.
	*/
	virtual IDataBase *GetDestDB() = 0;

	// Need to migrate the functionality below into a reponder the responds
	/** Get the destination UID that matches the source UID, if there is one. 
		@param pSrcDB source database
		@param pDestDB destination database
		@param srcID source UID
		@return destination UID the corresponds to the source, or kInvalidUID if there is none.
	*/
	virtual UID GetDestUID(IDataBase *pSrcDB, IDataBase *pDestDB, UID srcID) = 0;

	/** Add a new <sourceUID, destinationUID> mapping to the current context.
		@param pSrcDB source database
		@param pDestDB destination database
		@param srcID source UID
		@param destUID destination UID
	*/
	virtual void BindSrcAndDestUID(IDataBase *pSrcDB, IDataBase *pDestDB, UID srcUID, UID destUID) = 0;

	// NOT RECOMMENDED FOR CASUAL USE!
	// jwb 1/20/00: not yet ready for prime time; causes problems like 332917 and 334428
	// ddarling 7/9/04: Added back to the public interface for a nasty case with the object styles ref conversion which deletes 
	// 					a UID in a deferred command during the ending of the xref session.  The problem is when the UID is
	//					deleted we need to remove it from the XRef session cache
	virtual void UnbindSrcUID( IDataBase* pSrcDB, IDataBase* pDestDB, UID srcUID ) = 0 ;	
		
	/** A copy sesion may have commands associated with it that are waiting for a safe time to
		be processed. If there are deferred commands associated with the current context
		they will be processed when EndXRefSession is called for the context.
		@param pSrcDB source database
		@param pDestDB destination database
		@param srcID source UID
	*/
	virtual ICommand* GetDeferredCmd(IDataBase *pSrcDB, IDataBase *pDestDB, UID srcID) const = 0;

	/** Associate a command with the current context, to be processed when the context is ended.
		This is NOT a recommended way to solve problems, it is inherently fragile. 
		@param pSrcDB source database
		@param pDestDB destination database
		@param srcID source UID
		@param pCmd the command to defer
	*/
	virtual void BindDeferredCmd(IDataBase *pSrcDB, IDataBase *pDestDB, UID srcID, ICommand *pCmd) = 0;

} ;

/** A stack based object for handling nested calls to BeginXRefSession/EndXRefSession.
*/
class BeginEnd_XrefSession
{
	public:
		BeginEnd_XrefSession(IDataBase* srcDB, IDataBase* destDB):
		fXRef(GetExecutionContextSession(),IID_IXREFERENCEUID)
		{
			if ( fXRef )
			    fXRef->BeginXRefSession(srcDB, destDB);
		}
		~BeginEnd_XrefSession()
		{
			if ( fXRef )
				fXRef->EndXRefSession();
		}
	private:
		InterfacePtr<IXReferenceUID> fXRef; 
};

#endif // __IXReferenceUID__
