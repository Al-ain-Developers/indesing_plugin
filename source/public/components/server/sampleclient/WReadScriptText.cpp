//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/components/server/sampleclient/WReadScriptText.cpp $
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
//========================================================================================

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

bool read_script_text(const string& path_name, string& script_text);
bool read_script_text(const string& path_name, string& script_text)
{	
	ifstream 		scriptFile (path_name.c_str());
	if (scriptFile.rdstate() == ifstream::goodbit)
	{
		ostringstream 	scriptContent;
		
		scriptContent << scriptFile.rdbuf();
		script_text = scriptContent.str();

		// if the file has the UTF BOM, strip it off
		if (script_text.length() > 3) 
			{
			unsigned char c0 = script_text[0];
			unsigned char c1 = script_text[1];
			unsigned char c2 = script_text[2];

			if ((c0 == 0xEF) && (c1 == 0xBB) && (c2 == 0xBF))
				script_text.erase(0, 3);
			}
	
		return true;
	}
	else
		return false;
}

