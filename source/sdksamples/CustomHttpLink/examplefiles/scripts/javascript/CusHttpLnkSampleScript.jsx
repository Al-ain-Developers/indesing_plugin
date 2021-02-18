// This script requires a native plugin (in this case, CustomHttpLink) to be installed which handles the HTTP Links of given scheme.

var str = '{"username":"admin","password":"admin"}';

// Connect to server
app.httpLinkConnectionManager.httpConnect("myhost://localhost:3000", str);

// Check if connected
alert(app.httpLinkConnectionManager.isConnected("myhost://localhost:3000"));

// To change the default HTTP Links rendition type
app.linkingPreferences.httpLinksRenditionType = LinkResourceRenditionType.FPO;

// Place an HTTP Link
var doc0 					= 	app.documents.add();
var rectframe0				=	doc0.rectangles.add();
rectframe0.geometricBounds 	= [10,10,30,30];
var file1 					= "myhost://localhost:3000/image/asset1.jpg" ;
rectframe0.place(file1);

// Replace with original
if(app.activeDocument.links[0].renditionData == LinkResourceRenditionType.FPO)
	app.activeDocument.links[0].replaceWithOriginal();

// Logout from server
app.httpLinkConnectionManager.logout("myhost://localhost:3000");