void removeBad(list<Movie*>& li){
    list<Movie*>::iterator i = li.begin();
    while(i != li.end()){        
        if((*i)->rating() < 55){
            Movie* temp = *i;
            i = li.erase(i);
            delete temp;
        }
        i++;
    }
}
