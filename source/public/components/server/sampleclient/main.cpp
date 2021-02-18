//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/components/server/sampleclient/main.cpp $
//  
//  Owner: Jeff Argast
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
//  SampleClient is sample application that demonstrates how to
//  communicate with InDesignServer via soap. InDesignServer
//  exposes a single soap entry point called RunScript which
//  allows you to send the server a script (JavaScript, AppleScript, VBScript) for execution.
//  SampleClient uses gSoap for its implementation of soap.
//  
//  SampleClient is designed by run from the commandline.  For
//  example a typical run would look like:
//  
//  sampleclient -host localhost:18383 c:\testscript.js
//  
//========================================================================================

#ifdef WIN32
#define _UNICODE
#include <tchar.h>
#endif

#include "soapH.h"
#include "SoapClientUtils.h"

// ---- Library Includes ----
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include <boost/lexical_cast.hpp>
using boost::lexical_cast;

static bool bDebugMode = false;

void echoScriptArg(const char *argN)
{
	cout << "script arg: " << argN << std::endl;
	
	const char *argPtr = argN;
	
	fprintf(stdout,"0x");
	for (; *argPtr; argPtr++) fprintf(stdout, "%2.2X ", (unsigned char)argPtr[0]);
	fprintf(stdout,"\n");
	
}

/** display_help
	Display a message that describes the proper usage of SampleClient.  Output is on stdout.
*/
void display_help()
{
	cout << "SampleClient runs one or multiple scripts through InDesign Server.  "
		"The server instance is on a specified host."
		<< std::endl << std::endl;
	cout << "usage 1: sampleclient -h" << std::endl;
	cout << "Requests the display of this help information." << std::endl;
	cout << std::endl;
	cout << "usage 2: sampleclient [options] <script> [script args]" << std::endl;
	cout << "<script> specifies the scripts to be run. " << std::endl;
	cout << "\tIf file extension is \".applescript\", script content is assumed to be Applescript" << std::endl;
	cout << "\tIf file extension is \".vbs\", script content is assumed to be VBScript" << std::endl;
	cout << "\tOtherwise, script content is assumed to be JavaScript" << std::endl;
	cout << "[script args] specify any arguments to be passed to the script." << std::endl;
	cout << "\tThe form of each arg is \"name=value\", including the quotation marks." << std::endl;
	cout << "\tNOTE: script arguments can't be used when multiple scripts are specified." << std::endl;
	cout << "General options..." << std::endl;
	cout << "\t-host <host> specifies the host.  <host> is an IP address" << std::endl;
	cout << "\t\tfollowed by a port, using the form ip:port.  If host and" << std::endl;
	cout << "\t\tclient are the same, use localhost:port.  The default is" << std::endl;
	cout << "\t\tlocalhost:18383." << std::endl;
	cout << "\t-server specifies that the script is in the server's (host's) file" << std::endl;
	cout << "\t\tsystem.  By default, the script is in the client's file system." << std::endl;
	cout << "\t-repeat specifies the number of times to execute the script." << std::endl;
	cout << "\t-batch specifies that the scripts should be run in a new context."  << std::endl;
	cout << std::endl;
}

/** report_error
	Display a specific error message if one is specified, otherwise display a message that describes
	the proper usage of SampleClient.  Output is on stderr.

	@param msg IN the string to display
*/
void report_error(const string& msg = "")
{
	if (!msg.empty())
	{
		std::cerr << "Error: " << msg << endl;
		std::cerr << "     : For usage, run sampleclient -h." << endl << endl;
	}

	display_help();
}

/** read_script_text
	Opens the script specified by path_name, extracts the text and returns it in script_text.

	@param path_name IN the full path name of the script to be executed.
	@param script_text OUT the text contents of the script.
	@return kTrue if the file could be opened.  kFalse otherwise.
*/
bool read_script_text(const string& path_name, string& script_text);

enum ContextFlags {	kNoContext = 0,	// No context is used
					kRunBatchInContext
};

struct ContextOptions
{
	ContextOptions() : mode(kNoContext), contextID(0)
	{}
	
	ContextFlags mode;
	unsigned int contextID;
};

typedef std::vector<IDSP_ScriptArg> ScriptArgs;				// Arguments for a string

struct ScriptInfo
{
	std::string scriptText;
	std::string scriptLanguage;
	std::string scriptFile;
	ScriptArgs scriptArgs;
};

typedef std::vector<std::string> ScriptPathArray;			// Array of script paths
typedef std::vector<ScriptInfo> ScriptInfoArray;		// Array of script info 

// Type adapter
void ToIDSPScriptParams(const ScriptInfo& scriptInfo, IDSP__RunScriptParameters& params)
{
	params.scriptText = const_cast<char*>(scriptInfo.scriptText.c_str());
	params.scriptLanguage = const_cast<char*>(scriptInfo.scriptLanguage.c_str());
	params.scriptFile = const_cast<char*>(scriptInfo.scriptFile.c_str());
	params.scriptArgs = const_cast<ScriptArgs*>(&scriptInfo.scriptArgs);
}

/** parse_args
	Parses and extracts the command line arguments passed to SampleClient.

	@param argc IN the number of command line arguments passed to SampleClient.
	@param argv IN a pointer to each individual command line argument.
	@param script OUT the path to the script.
	@param host OUT the name of the server (host) we want to send the script to.
	@param repeat OUT the number of times we want to execute the script.
	@param contextOptions OUT the context options in which the script should execute.
	@param specifyScriptFile OUT kTrue if the script needs to be read locally.  kFalse if script resides on the server.
	@param script_args OUT a vector of script arguments that will be passed to the script.  Script arguments are specified
	as "name=value". Script arguments can't be specified in the batch mode.
	@return 0, if processing of a script should continue; otherwise return -1.
*/
int parse_args(int argc, const char * argv[], ScriptPathArray& scripts, string& host, int &repeat,
			   ContextOptions& contextOptions, bool& specifyScriptFile, ScriptArgs& script_args)
{
	if (argc < 2 || strcmp(argv[1],"-h") == 0)
	{
		display_help();
		return(-1);
	}

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i],"-host") == 0)
			{
			host = argv[++i];
			if (bDebugMode) cout << "host set to \"" << host << "\"" << std::endl;
			}
		else if (strcmp(argv[i],"-server") == 0)
			{
			specifyScriptFile = false;
			if (bDebugMode) cout << "script on server set to TRUE" << std::endl;
			}
		else if (strcmp(argv[i],"-repeat") == 0)
		{
			if (argc < i + 2)
			{
				report_error("-repeat must be followed by an integer.");
				return(-1);
			}

			try
			{
				repeat = lexical_cast<int>(argv[++i]);
			}
			catch (...)
			{
				report_error("-repeat must be followed by an integer.");
				return(-1);
			}

			if (bDebugMode) cout << "repeat count set to " << repeat << std::endl;
		}
		else if (strcmp(argv[i],"-batch") == 0)
		{
			contextOptions.mode = kRunBatchInContext;
						
			if (bDebugMode) cout << "Run a batch of scripts in a new context" << std::endl;
		}
		else if (strcmp(argv[i],"-debug") == 0)
			bDebugMode = true;
		else
		{
			// -- Collect the set of script arguments.  If it is not a script argument it's assumed its the script itself.
			const char *equalsSignPtr = strchr(argv[i],'=');

			if (equalsSignPtr != NULL)
			{
				if (contextOptions.mode == kRunBatchInContext)
				{
					report_error("-batch can't be used when script arguments are also specified.");
					return  -1;
				}
				
				IDSP_ScriptArg script_arg;
				script_arg.name = string(argv[i]);
				script_arg.name.erase(script_arg.name.find('='));
				equalsSignPtr++;
				script_arg.value = string(equalsSignPtr);
				script_args.push_back(script_arg);
				if (bDebugMode) echoScriptArg(argv[i]);
			}
			else // Not a script argument
			{
				if (!scripts.empty() && contextOptions.mode != kRunBatchInContext)
				{
					// We already got a script and this is not a script argument or a recognized option: report and quit.
					string msg("\"");
					msg += scripts[0];
					msg += "\" was identified as the specified script;";
					msg += " then an unrecognizable argument was found:  \"";
					msg += argv[i];//arg;
					msg += "\".";
					report_error(msg);
					return(-1);					
				}
				
				scripts.push_back(argv[i]);
			}
		}

	}

	return(0);
}

/** main
	The main entry point.

	@param argc IN the number of command line arguments passed to SampleClient.
	@param argv IN a pointer to each individual command line argument.
	@return -1 if an error occurred. 0 if everything was successful.
*/
#ifdef MACINTOSH
#define sampleclient_main main
#endif

#ifdef WIN32
int sampleclient_main (int argc, const char *argv[]);
// because we have '_UNICODE' defined (above), command line arguments passed in are unicode; need to convert 
// them to UTF-8 before passing them to InDesign

//int main(int argc, const char **argv);

int _tmain(int argc, wchar_t *argv[])
{
	int			utf8Argc = 0;
	const char	**utf8Argv = (const char **)(new char *[argc]);

	for (int i = 0; i < argc; i++)
		{
		int bytesRequired = WideCharToMultiByte(CP_UTF8, 0, argv[i], -1, NULL, 0, NULL, NULL);

		if (bytesRequired > 0)
			{
			bytesRequired += 2;	// leave room for null terminator
			char *buffer = new char[bytesRequired];
			if (WideCharToMultiByte(CP_UTF8, 0, argv[i], -1, buffer, bytesRequired, NULL, NULL) != 0)
				utf8Argv[utf8Argc++] = buffer;
			}
		}

	return (sampleclient_main(utf8Argc, utf8Argv));
}

#endif

// Constructs the script info params
bool GetScriptsInfo(const ScriptPathArray& paths, const ScriptArgs& script_args, bool specifyScriptFile, ScriptInfoArray& scripts)
{
	// Can't have multiple scripts AND script args (which args go to which script?!)
	if(paths.size() > 1 && !script_args.empty())
	{
		assert(!"Can't have multiple scripts AND script args (which args go to which script");
		return false;
	}
	
	for (ScriptPathArray::const_iterator i(paths.begin()); i != paths.end(); ++i)
	{
		string scriptText;	// -- Used to hold the contents of the script
				
		ScriptInfo scriptInfo;
				
		if (!script_args.empty())
			scriptInfo.scriptArgs = script_args;
		
		scriptInfo.scriptLanguage = "javascript";		// javascript is default
		
		// Alias
		const std::string& scriptPath = *i;
		
		// see if we have an applescript or vbscript extension; set language accordingly
		if (scriptPath.rfind(".applescript") != scriptPath.npos)
			scriptInfo.scriptLanguage = "applescript";
		else if (scriptPath.rfind(".vbs") != scriptPath.npos) {
			scriptInfo.scriptLanguage = "visual basic";
		}
		
		if (specifyScriptFile)
		{
			if (read_script_text(scriptPath, scriptText))
			{
				scriptInfo.scriptText = const_cast<char*>(scriptText.c_str());
			}
			else
			{
				report_error("The script file specified can not be found");
				return false;
			}
		}
		else
		{
			scriptInfo.scriptFile = const_cast<char*>(scriptPath.c_str());
		}
		
		scripts.push_back(scriptInfo);
	}
	return true;
}

// Send over a script or multiple scripts
int DoScripts(soap& soap, const std::string& host, const ScriptInfoArray& scripts, const ContextOptions& contextOptions)
{
	int soapResults = SOAP_OK;
	
	for (ScriptInfoArray::const_iterator i(scripts.begin()); i != scripts.end(); ++i)
	{				
		if (contextOptions.mode == kRunBatchInContext)
		{
			//check if begin session succeeded
			if (contextOptions.contextID != 0)
			{
				// try to connect to an already existing session
				// Set the session ID in the header
				SOAP_ENV__Header* header = static_cast<SOAP_ENV__Header*>(soap_malloc(&soap, sizeof(SOAP_ENV__Header)));
				if (header)
				{
					header->IDSP__sessionID = contextOptions.contextID;
					soap.header = header;
				}
			}
		}
		
		// -- IDSP__RunScriptParameters is a soap type that we have defined for containing the information
		// -- necessary to ask the server to run a script.		
		IDSP__RunScriptParameters runScriptParams;
		ToIDSPScriptParams(*i, runScriptParams);
		
		// -- IDSP__RunScriptResponse is another soap type that we have defined to contain the results from running the script.
		IDSP__RunScriptResponse runScriptResponse;
		runScriptResponse.errorString = "";
		
		// -- soap_call_IDSP__RunScript is the server's entry point for running a script.
		soapResults = soap_call_IDSP__RunScript (&soap, host.c_str(), "", &runScriptParams, runScriptResponse);
		
		// -- If we are successful in sending the script via soap to the server and getting a return value
		// -- then soapResults will equal SOAP_OK.  Otherwise we use soap_print_fault to write out any soap
		// -- error messages to the console.
		if (soapResults == SOAP_OK)
		{
			// The SOAP result was OK, check the result from the script
			if (runScriptResponse.errorNumber == 0)
			{
				cout << "Script result";
				IDSP__Data* dataHolder = runScriptResponse.scriptResult;
				if (dataHolder)
				{
					ShowAny(dataHolder);
				}
				else
				{
					cout << ": No data." << std::endl;
				}
			}
			else
			{
				cout << "Error number: " << runScriptResponse.errorNumber << std::endl;
				if (runScriptResponse.errorString != NULL)
					cout << runScriptResponse.errorString<< std::endl;
				
				// Should we break if the script returns an error?
				soapResults = SOAP_ERR; // Not sure if this is the right value
				break;
			}
		}
		else
		{
			report_error("SOAP error message follows.");
			soap_print_fault(&soap, stderr);
			break;
		}
		
		soap_destroy(&soap);
		soap_end (&soap);
	}
	
	return soapResults;
}

int sampleclient_main (int argc, const char * argv[])
{
	ScriptPathArray scriptPaths;
	string host = "localhost:18383";	// -- The default host if one is not specified
	bool specifyScriptFile = true;		// -- By default we assume that we need to read the contents of the script file
	ScriptArgs script_args;
	int repeat = 1;
	ContextOptions contextOptions;
	bool exitWithError = false;

	int argsErrorCode(parse_args(argc, argv, scriptPaths, host, repeat, contextOptions, specifyScriptFile, script_args));
	if (argsErrorCode != 0)
	{
		exit(argsErrorCode);
	}

	struct soap soap;
    soap_init2(&soap, SOAP_IO_KEEPALIVE | SOAP_C_UTFSTRING, SOAP_IO_KEEPALIVE | SOAP_C_UTFSTRING);

	// -- If a script is not specified and no context options then we can not continue.
	int soapResults = SOAP_OK;
	if (scriptPaths.empty())
	{
		report_error("No script(s) was specified.");
		exit(-1);
	}
		
	if (contextOptions.mode == kRunBatchInContext)
	{
		assert (contextOptions.contextID == 0);
		
		// Initiate a new session
		cout << "Calling BeginSession: " << std::endl;
		soapResults = soap_call_IDSP__BeginSession(&soap, host.c_str(), "", contextOptions.contextID);
		if (soapResults != SOAP_OK)
		{
			soap_print_fault(&soap, stderr);
			exitWithError = true;
		}
		
		cout << "New session ID: " << contextOptions.contextID << std::endl;
	}

	ScriptInfoArray scripts;
	if (!exitWithError)
	{
		// Get the script infos (TODO: move this function inside of parse_args)
		exitWithError = !GetScriptsInfo(scriptPaths, script_args, specifyScriptFile, scripts);
	}
	
	// Send over the scripts if we have any
	for (int i = 0; i < repeat && !exitWithError && !scripts.empty(); ++i)
	{
		soapResults = DoScripts(soap, host, scripts, contextOptions);
		if (soapResults != SOAP_OK)
		{
			exitWithError = true;
		}
		soap_destroy(&soap);
		soap_end (&soap);
	}

	// Close context is a standalone command
	if (contextOptions.mode == kRunBatchInContext)
	{		
		//check if session was started successfully
		if(contextOptions.contextID != 0)
		{
			// try to connect to an already existing session
			// Set the session ID in the header
			SOAP_ENV__Header* header = static_cast<SOAP_ENV__Header*>(soap_malloc(&soap, sizeof(SOAP_ENV__Header)));
			if (header)
			{
				header->IDSP__sessionID = contextOptions.contextID;
				soap.header = header;
			}

			cout << "Calling EndSession with ID: " << contextOptions.contextID << std::endl;
			soapResults = soap_call_IDSP__EndSession(&soap, host.c_str(), "", contextOptions.contextID, 0);
			if (soapResults == SOAP_OK)
			{
				cout << "Successfully closed session with ID: " << contextOptions.contextID << std::endl;
			}
			else
			{
				soap_print_fault(&soap, stderr);
				exitWithError = true;
			}	
		}
	}	
	
	soap_destroy(&soap);
	soap_end (&soap);
	soap_done (&soap); // Cleanup soap context
	return exitWithError ? 1 : 0;
}
