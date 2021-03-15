void listAll(const File* f, string path){ // two-parameter overload
    string curFile = path + "/" + f->name();
    cout << curFile << endl;
    
    const vector<File*>* files = f->files();
    if(files == nullptr) // if file isn't directory
        return;
    
    for(vector<File*>::const_iterator it = files->begin(); it != files->end(); ++it){
        listAll((*it), (curFile));
    }
}
