
/* Class Declarations */
class Investment{
public:
    Investment(string name, int price):_name(name), _price(price){}
    virtual ~Investment(){};
    
    string name() const {return _name;}
    int purchasePrice() const {return _price;}
    
    virtual bool fungible() const = 0;
    virtual string description() const = 0;
    
private:
    string _name;
    int _price;
};

class Painting : public Investment{
public:
    Painting(string name, int price):Investment(name, price){};
    virtual ~Painting();
    
    virtual bool fungible() const {return false;}
    virtual string description() const;
};

class Stock : public Investment{
public:
    Stock(string name, int price, string ticker):Investment(name, price), _ticker(ticker){};
    virtual ~Stock();
    
    virtual bool fungible() const {return true;}
    virtual string description() const;
    
private:
    string _ticker;
};

class House : public Investment{
public:
    House(string address, int price):Investment(address, price){};
    virtual ~House();

    virtual bool fungible() const { return false; }
    virtual string description() const;
};

/* Painting Implementation */
Painting::~Painting(){
    cout << "Destroying " + Investment::name() + ", a painting" << endl;
}
string Painting::description() const{
    return "painting";
}

/* Stock Implementation */
Stock::~Stock(){
    cout << "Destroying " + Investment::name() + ", a stock holding" << endl;
}
string Stock::description() const {
    return "stock trading as " + _ticker;
}

/* House Implementation */
House::~House(){
    cout << "Destroying the house " + Investment::name() << endl;
}
string House::description() const {
    return  "house";
}
