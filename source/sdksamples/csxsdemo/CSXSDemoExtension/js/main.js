
$(function() {
    var csInterface = new CSInterface();
	
	// add event listener to listen for events from native plug-in
	csInterface.addEventListener('com.adobe.indesign.html', function(event) {
		alert(event.data);
	});
	
	// send a CSXS event to the native plug-in
	$('#myButton').click(function(e) {
		var event = new CSEvent('com.adobe.indesign', 'APPLICATION', 'IDSN', 'Demo');
		event.data = '<payload>';
		event.data += 'Hello from HTML!';
		event.data += '</payload>';
		csInterface.dispatchEvent(event);
	});

});