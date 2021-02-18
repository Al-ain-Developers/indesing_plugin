/**************************************************************************
 *                                                                        *
 *  Copyright 2014 Adobe Systems Incorporated                             *
 *  All Rights Reserved.                                                  *
 *                                                                        *
 * NOTICE:  All information contained herein is, and remains the property *
 * of Adobe Systems Incorporated and its suppliers, if any.               *
 * The intellectual and technical concepts contained herein are           *
 * proprietary to Adobe Systems Incorporated and its suppliers and may be *
 * covered by U.S. and Foreign Patents, patents in process, and are       *
 * protected by trade secret or copyright law.                            *
 * Dissemination of this information or reproduction of this material     *
 * strictly forbidden unless prior written permission is obtained from    *
 * Adobe Systems Incorporated.                                            *
 *                                                                        *
 **************************************************************************/

var escapeForJson = function(e) {
	var t=e;
	return t=t.replace(/\\/g,"\\\\"),t=t.replace(/"/g,'\\"'),t;
};

var getToolInfoInner = function() {
	var toolInfo = {};
	toolInfo.currentToolName = escapeForJson(app.toolBoxTools.currentToolName);
	toolInfo.currentToolHint = escapeForJson(app.toolBoxTools.currentToolHint);
	toolInfo.currentToolIconFilePath = escapeForJson("file:///" + app.toolBoxTools.currentToolIconFile.fsName);
	
	var jsonString = '{"currentToolName":"' + toolInfo.currentToolName + '","currentToolHint":"' +  toolInfo.currentToolHint + '","currentToolIconFilePath":"' + toolInfo.currentToolIconFilePath + '"}';
	return jsonString;
};

$._ext_IDSN={
    getToolInfo : function() {
    	return getToolInfoInner();
    }
};

$._ext_AICY={
    getToolInfo : function() {
    	return getToolInfoInner();
    }
};
