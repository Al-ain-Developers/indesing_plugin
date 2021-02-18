//========================================================================================
//
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/CustomHttpLink/CusHttpLnkLinkResourceConnection.cpp $
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
//  ADOBE CONFIDENTIAL
//  
//  Copyright 2019 Adobe
//  All Rights Reserved.
//
//  NOTICE: Adobe permits you to use, modify, and distribute this file in
//  accordance with the terms of the Adobe license agreement accompanying
//  it. If you have received this file from a source other than Adobe,
//  then your use, modification, or distribution of it requires the prior
//  written permission of Adobe. 
//
//========================================================================================

#include "VCPlugInHeaders.h"

#include "CPMUnknown.h"
#include "CustomHttpLinkID.h"

// Interfaces
#include "IHTTPLinkResourceConnection.h"
#include "IHTTPLinkManager.h"

#include "IJsonUtils.h"

/**
     Provide methods to authorize connection to server
 
     @ingroup customhttplink.sdk
 */

class CusHttpLnkLinkResourceConnection : public CPMUnknown<IHTTPLinkResourceConnection>
{
public:
    typedef CPMUnknown<IHTTPLinkResourceConnection> inherited;

    /**
     Constructor
     */
    CusHttpLnkLinkResourceConnection(IPMUnknown* boss);
    
    /**
     Destructor
     */
    ~CusHttpLnkLinkResourceConnection();

    /**
     Shuts down the current connection
     @return kTrue if the Http Connection is shutdown else kFalse
     */
    virtual bool16 Shutdown();

    /**
     Checks if the current connection is connected
     @return kTrue if the Http Connection is connected else kFalse
     */
    virtual bool16 IsConnected() const;

    /**
     Checks if the current connection is authorized
     @return kTrue if the Http Connection is authorized else kFalse.
     */
    virtual bool16 Connect();

    /**
     Creates/Logs-in the current connection
     @return kTrue if connection is created/logged-in successfully else kFalse.
     */
    virtual bool16 IsAuthorized() const;

    /**
     Reconnects the current connection
     @return kTrue if re-connection is successful else kFalse
     */
    virtual bool16 Reconnect();

    /**
     Disconnects the current connection
     @return kTrue if the connection is diconnected else kFalse
     */
    virtual bool16 Disconnect();

    /**
     Fetches the connection ID for the current connection
     @return ConnectionId for the current connection
     */
    virtual IHTTPLinkResourceConnection::ConnectionId GetConnectionId();

    
    /**
     Gets the login credentials for the given connection
     @param loginInformation        [OUT]  The login information that requires to be set for the given connection
     @return kFalse if credentials could not be encoded, else kTrue
     */
    virtual bool16 GetLoginCredentials(std::stringstream& loginInformation) const;

    /**
     Sets the login credentials for the given connection
     @param loginInformation        [IN]  The login information that requires to be set for the given connection
     @return kTrue if credentials are set
     */
    virtual bool16 SetLoginCredentials(const std::stringstream& loginInformation);

	/**
	** For internal purpose only
	*/
	virtual void ReadWriteSnapshotForBackgroundThread(IPMStream* s)
	{
        XferStdString(s, fLoginInfo.fToken);
        XferStdString(s, fLoginInfo.fUsername);
        XferStdString(s, fLoginInfo.fPassword);
	}
    
private:
    struct LoginInfo
    {
        std::string fToken;
        std::string fUsername;
        std::string fPassword;
    };
    
    // LoginInfo represents the login information
    // between client and server
    LoginInfo fLoginInfo;
    
    void XferStdString(IPMStream* s, std::string& str)
    {
        PMString pmString;
        if (s->IsReading())
        {
            pmString.ReadWrite(s);
            str = pmString.GetUTF8String();
        }
        else
        {
            pmString.SetUTF8String(str);
            pmString.ReadWrite(s);
        }
    }
    
    // Private Utility functions
    
    /**
     * Generates the session token using the API wrapper
     * @param token[OUT] The login token which is generated
     * @return true if token is generated successfully, otherwise false
     */
    bool16 GenerateToken(std::string &token);
    
    /**
     * Converts LoginInfo to JSON
     * @param loginInfo [IN] input logininfo object
     * @param json[OUT] output json object
     */
    static void convertLoginInfoToJson(LoginInfo loginInfo, JSON& json);
    
    /**
     * Converts json object to LoginInfo object
     * @param loginInfo [OUT] output login info object
     * @param json [IN] input json object
     */
    static bool16 convertJsonToLoginInfo(LoginInfo &loginInfo, JSON& json);
};

CREATE_PMINTERFACE(CusHttpLnkLinkResourceConnection, kCusHttpLnkLinkResourceConnectionImpl)


/* Constructor
*/
CusHttpLnkLinkResourceConnection::CusHttpLnkLinkResourceConnection(IPMUnknown* boss)
: inherited(boss)
{
}

/* Destructor
 */
CusHttpLnkLinkResourceConnection::~CusHttpLnkLinkResourceConnection()
{
}

/* Shutdown
 */
bool16 CusHttpLnkLinkResourceConnection::Shutdown()
{
    // Clear the token in case connection is shutdown
    fLoginInfo.fToken = "";
    return kTrue;
}

/* IsConnected
 */
bool16 CusHttpLnkLinkResourceConnection::IsConnected() const
{
    // If the token is empty, we are not connected to server
    if (fLoginInfo.fToken == "")
        return kFalse;
    return kTrue;
}

/* Connect
 */
bool16 CusHttpLnkLinkResourceConnection::Connect()
{
    // If the login credentials have not been set
    // we cannot connect to server
    if (fLoginInfo.fUsername == "" || fLoginInfo.fPassword == "" )
        return kFalse;
    // Generate token using the login credetials
    return GenerateToken(fLoginInfo.fToken);
}

/* IsAuthorized
 */
bool16 CusHttpLnkLinkResourceConnection::IsAuthorized() const
{
    // If the login credentials have not been set
    // the user is not authorized to connect to server
    if (fLoginInfo.fUsername == "" || fLoginInfo.fPassword == "" )
        return kFalse;
	return kTrue;
}

/* Reconnect
 */
bool16 CusHttpLnkLinkResourceConnection::Reconnect()
{
	return this->Connect();
}

/* Disconnect
 */
bool16 CusHttpLnkLinkResourceConnection::Disconnect()
{
    // Clear token and login credentials
    fLoginInfo.fToken = "";
    fLoginInfo.fUsername = "";
    fLoginInfo.fPassword = "";

	return kTrue;
}

/* GetConnectionId
 */
IHTTPLinkResourceConnection::ConnectionId CusHttpLnkLinkResourceConnection::GetConnectionId()
{
	return ConnectionId();
}

/* GetLoginCredentials
 */
bool16 CusHttpLnkLinkResourceConnection::GetLoginCredentials(std::stringstream& loginInformation) const
{
    JSON json;
    convertLoginInfoToJson(fLoginInfo, json);
    json.write_json(loginInformation);
    return kTrue;
}

/* SetLoginCredentials
 */
bool16 CusHttpLnkLinkResourceConnection::SetLoginCredentials(const std::stringstream& loginInformation)
{
    JSON json;
    std::stringstream loginstr(loginInformation.str());
    json.read_json(loginstr);
    return convertJsonToLoginInfo(fLoginInfo, json);
}


bool16 CusHttpLnkLinkResourceConnection::GenerateToken(std::string &token)
{
    // Generate token from API wrapper
    InterfacePtr<IHTTPLinkManager> httpLinkManager(GetExecutionContextSession(), UseDefaultIID());
    URI uri;
    WideString scheme(kCusHttpLnkScheme);
    uri.SetComponent(URI::kScheme, scheme);
    IHTTPLinkResourceServerAPIWrapper* serverAPIWrapper = httpLinkManager->GetHTTPLinkResourceServerAPIWrapper(uri);
    if (serverAPIWrapper->GenerateSessionToken(this, fLoginInfo.fToken))
    {
        return kTrue;
    }
    return kFalse;
}

void CusHttpLnkLinkResourceConnection::convertLoginInfoToJson(LoginInfo loginInfo, JSON& json)
{
    json.addValue(username_key, loginInfo.fUsername);
    json.addValue(password_key, loginInfo.fPassword);
    json.addValue(token_key, loginInfo.fToken);
}

bool16 CusHttpLnkLinkResourceConnection::convertJsonToLoginInfo(LoginInfo &loginInfo, JSON& logindetails)
{
    try {
        
        std::string username    = logindetails.GetString(username_key);
        std::string password    = logindetails.GetString(password_key);
        std::string token = "";
        //This is an optional parameter
        if (logindetails.checkKey(token_key))
            logindetails.GetString(token_key);
        
        loginInfo.fUsername     = username;
        loginInfo.fPassword     = password;
        loginInfo.fToken        = token;
        
        return kTrue;
        
    } catch (...) {
        ASSERT_FAIL("Invalid login credentials");
    }
    return kFalse;
}
