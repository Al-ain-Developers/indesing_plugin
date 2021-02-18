#targetengine "session"


app.addEventListener(Event.AFTER_SPREAD_LIST_CHANGED, spreadListChanged);
app.addEventListener(Event.AFTER_PARAGRAPH_STYLE_LIST_CHANGED, psListChanged);
app.addEventListener(Event.AFTER_CHARACTER_STYLE_LIST_CHANGED, csListChanged);

function spreadListChanged()
{
	alert("Spread List Changed");
}

function psListChanged()
{
	alert("PS List Changed");
}

function csListChanged()
{
	alert("CS List Changed");
}


