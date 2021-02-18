#targetengine "session"

app.removeEventListener(Event.AFTER_PARAGRAPH_STYLE_LIST_CHANGED, psListChanged);
app.removeEventListener(Event.AFTER_CHARACTER_STYLE_LIST_CHANGED, csListChanged);
