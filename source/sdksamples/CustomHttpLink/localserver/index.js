// Import required modules
const express   = require('express')
const fs        = require('fs')
const app       = express()
const url       = require('url');
const md5File   = require('md5-file')
// Port number to listen to
const port      = 3000


/*  API Endpoint to get high resolution asset
    Sample request: GET http://localhost:3000/image/flower.jpg
    Returns 404 if asset is not found
*/
app.get('/image/:path', function(req, res) {
  // Search for asset in the given path
  var path = __dirname + '/image/' + req.params.path;
  console.log("Asset Path: " + path);
  if (fs.existsSync(path)) {
    // if asset exist, return it
  	res.download(path);
  } else {
    //otherwise, send 404:Not Found response
  	res.sendStatus(404);
  }
});


/* API Endpoint to get low res asset
   Sample request: GET http://localhost:3000/image/flower.jpg/fpo
    Returns 404 if asset is not found
*/
app.get('/image/:path/fpo', function(req, res) {
  // Search for asset in the given path
  var path = __dirname + '/image/fpo/' + req.params.path;
  console.log("Asset Path: " + path);
  if (fs.existsSync(path)) {
    // if asset exist, return it
    res.download(path);
  } else {
    //otherwise, send 404:Not Found response
    res.sendStatus(404);
  }
});



/*  API Endpoint to get status of a single asset
    Sample request: POST http://localhost:3000/assetstatus.json?path=image/flower.jpg
    Sample response:
    {
      "item": [
        {
          "path": "image/flower.jpg",
          "sha": "1e907a80ed1458994f25093b695ca88a",
          "size": 11333,
          "created_date": "2019-04-26T06:56:07.388Z"
        }
      ],
      "found": true
    }
*/
app.post('/assetstatus.json', function(req, res) {
	
  // Parse the request parameter path
	var parts = url.parse(req.url, true);
	var query = parts.query;
	var response = {}
	response.item = []
  console.log("Asset Status: " + query.path);

  // filepath on server
	var filepath = __dirname + '/' + query.path;

	var item = {}

	if (fs.existsSync(filepath)) {
    // get unique hash for file stream
		item.path = query.path;
		item.sha = md5File.sync(filepath);

    // FileSystem module to get parameters of file
		const stats = fs.statSync(filepath)
		item.size = stats.size;
    item.created_date = stats.birthtime
    response.item.push(item);
    response.found = true
	} else {
    //asset is missing
    response.found = false
  }
	res.json(response);

});



/*  API Endpoint to get status of a multiple assets
    Sample request: POST http://localhost:3000/batchassetstatus.json?path=/image/flower.jpg&path=/image/wp1.jpg
    Sample response:
    {
      "requested": 2,
      "items": [
          {
              "path": "/image/flower.jpg",
              "sha": "1e907a80ed1458994f25093b695ca88a",
              "size": 11333,
              "created_date": "2019-04-26T06:56:07.388Z"
          }
      ],
      "found": 1,
      "missing": 1
    }
*/
app.post('/batchassetstatus.json', function(req, res) {
	
  // Parse the request parameters
	var parts = url.parse(req.url, true);
	var paths = parts.query.path;
	var foundLinks = 0;
	var missinglinks = 0;
	var response = {}

  console.log("BatchAssetStatus: " + paths);

  // If we have single path, convert it to array
  if (!(paths instanceof Array)) {
    paths = []
    paths.push(parts.query.path)
  }

  response.requested = paths.length
  response.items = []

  // Traverse through the paths array
	for (var i = 0; i < paths.length; i++) {

		var filepath = __dirname + '/' + paths[i];
		var item = {}
		if (fs.existsSync(filepath)) {
			foundLinks++;
			item.path = paths[i];
      // get unique hash for file stream
			var file = fs.createReadStream(filepath);
			const hash = md5File.sync(filepath)
			item.sha = hash;

      // FileSystem module to get parameters of file
      const stats = fs.statSync(filepath)
      item.size = stats.size;
      item.created_date = stats.birthtime
      response.items.push(item);
		} else {
			missinglinks++;
		}
  }

	response.found = foundLinks;
	response.missing = missinglinks;
	res.json(response);

});


app.listen(port, (err) => {
  if (err) {
    return console.log('something bad happened', err)
  }
  console.log(`server is listening on ${port}`)
});

