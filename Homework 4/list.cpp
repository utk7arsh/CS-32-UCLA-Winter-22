void listAll(string path, const Class* c)  // two-parameter overload
{
    if (c == nullptr)
        return;
    path += c->name();
    cout << path << endl;
    path += "=>";
    for (vector<Class*>::const_iterator it = c->subclasses().begin(); it != c->subclasses().end(); it++)
        listAll(path, *it);
}