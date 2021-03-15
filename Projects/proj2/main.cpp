//
//  main.cpp
//  Project 2
//
//  Created by Junho Choi on 1/20/21.
//

#include <iostream>
#include <cassert>
#include "Sequence.h"
using namespace std;

void nehaTest(){
    Sequence s;
      assert(s.empty());
      assert(s.size() == 0);
      assert(s.find(42) == -1);
      assert(s.insert(42) == 0);
      // sequence should be (42)
      s.dump();
      assert(s.size() == 1  &&  s.find(42) == 0);
      
      assert(s.insert(0, 41) == 0 && s.find(42) == 1);
      // sequence should be (41, 42)
      assert(s.insert(1, 6) == 1 && s.find(42) == 2);
      // sequence should be (41, 6, 42)
      s.dump();
      assert(s.insert(3, 12) == 3 && s.find(42) == 2);
      // sequence should be (41, 6, 42, 12)
      s.dump();
      assert(s.insert(7, 9) == -1 && s.find(41) == 0);
      
      assert(s.insert(57) == 4);
      // sequence should be (41, 6, 42, 12, 57)
      s.dump();
      assert(s.insert(37) == 0 && s.find(41) == 1);
      // sequence should be (37, 41, 6, 42, 12, 57)
      s.dump();
      assert(s.insert(39) == 1 && s.find(41) == 2);
      // sequence should be (37, 39, 41, 6, 42, 12, 57)
      s.dump();
      
      assert(s.erase(2) && s.find(41) == -1 && s.find(57) == 5);
      // sequence should be (37, 39, 6, 42, 12, 57)
      s.dump();
      assert(!(s.erase(7)));

      assert(s.insert(0, 42) == 0);
      assert(s.insert(7, 42) == 7);
      // sequence should be (42, 37, 39, 6, 42, 12, 57, 42)
      s.dump();
    
      assert(s.remove(42) == 3 && s.size() == 5);
      // sequence should be (37, 39, 6, 12, 57)
      s.dump();
      
      assert(s.remove(57) == 1 && s.size() == 4);
      // sequence should be (37, 39, 6, 12)
      s.dump();
      
      assert(s.remove(103) == 0);
      assert(s.remove(99) == 0);
      
      ItemType x;
      assert(s.get(0, x) && x == 37);
      assert(!(s.get(12, x)));
      
      assert(s.set(0, 6));
      // sequence should be (6, 39, 6, 12)
      s.dump();
      
      assert(!(s.set(12, 16)));
      // sequence should be (6, 39, 6, 12)
      s.dump();
      
      assert(s.find(6) == 0);
      assert(s.find(99) == -1);
      
      Sequence w;
      
      assert(w.insert(0, 12) == 0);
      assert(w.insert(1, 13) == 1);
      assert(w.insert(2, 14) == 2);
      
      w.swap(s);
      
      assert(w.size() == 4 && s.size() == 3 && w.find(6) == 0 && s.find(13) == 1);
      
      // s sequence should be (12, 13, 14)
      s.dump();
      // w sequence should be (6, 39, 6, 12)
      w.dump();
      
      Sequence h = s;
      assert(h.find(14) == 2);
      
      // h sequence should be (12, 13, 14)
      h.dump();
      
      s = w;
      assert(s.size() == w.size());
      assert(s.find(39) == w.find(39));
      // s and w sequence should be (6, 39, 6, 12)
      w.dump();
      s.dump();

    cout << "neha test passed :)" << endl;
}


void junhoTest1(){
    Sequence s;
    assert(s.insert(5) == 0);
    assert(s.insert(34) == 1);
    assert(s.insert(3) == 0);
    // s sequence should be (3, 5, 34)
    s.dump();
    
    assert(s.insert(7, 4) == -1);
    assert(s.insert(3, 23) == 3);
    // s sequence should be (3, 5, 34, 23)
    s.dump();
    
    assert(s.erase(0) && s.size() == 3);
    // s sequence should be (5, 34, 23)
    s.dump();
    
    Sequence t;
    assert(t.insert(4) == 0 && t.insert(3) == 0 && t.insert(25) == 2 && t.insert(1000) == 3);
    // t sequence should be (3, 4, 25, 1000)
    t.dump();
    
    ItemType a = 5;
    assert(t.set(1, a) && t.find(a) == 1);
    assert(t.insert(3, 32) == 3 && t.size() == 5);
    // t sequence should be (3, 5, 25, 32, 1000)
    t.dump();
    
    Sequence u;
    interleave(s, t, u);
    assert(u.size() == (s.size() + t.size()));

    ItemType b[] = {5, 3, 34, 5, 23, 25, 32, 1000};
    for(int i = 0; i < 8; ++i){
        ItemType c = 0;
        u.get(i, c);
        assert(c == b[i]);
    }
    // u sequence should be (5, 3, 34, 5, 23, 32, 1000)
    u.dump();
    
    assert(u.erase(u.find(1000)) && u.size() == 7);
    assert(u.insert(5) == 0 && u.insert(99) == 8);
    assert(u.remove(5) == 3);
    // u sequence should be (3, 34, 23, 25, 32, 99)
    u.dump();
    
    
    Sequence v(s);
    for(int i = 0; i < s.size(); ++i){
        ItemType c = 0;
        ItemType d = 0;
        s.get(i, c);
        v.get(i, d);
        assert(c == d);
    }
    v = t;
    for(int i = 0; i < t.size(); ++i){
        ItemType c = 0;
        ItemType d = 0;
        t.get(i, c);
        v.get(i, d);
        assert(c == d);
    }
    
    Sequence w;
    interleave(s, v, w);
    // w sequence should be (5, 3, 34, 5, 23, 32, 1000)
    w.dump();
    
    for(int i = 0; i < 8; ++i){
        ItemType c = 0;
        w.get(i, c);
        assert(c == b[i]);
    }
    
    w.swap(s);
    for(int i = 0; i < 8; ++i){
        ItemType c = 0;
        s.get(i, c);
        assert(c == b[i]);
    }
    // s sequence should be (5, 3, 34, 5, 23, 32, 1000)
    s.dump();
    
    Sequence x;
    interleave(w, v, x);
    for(int i = 0; i < 8; ++i){
        ItemType c = 0;
        x.get(i,c);
        assert(c == b[i]);
    }
    
    Sequence y;
    assert(y.insert(1) == 0 && y.insert(3) == 1 && y.insert(2) == 1 && y.insert(4) == 3);
    Sequence z;
    assert(z.insert(11) == 0 && z.insert(33) == 1 && z.insert(44) == 2 && z.insert(22) == 1);
    
    Sequence hi;
    interleave(y, z, hi);
    
    ItemType bye[] = {1, 11, 2, 22, 3, 33, 4, 44};
    for(int i = 0; i < 8; ++i){
        ItemType c = 0;
        hi.get(i, c);
        assert(c == bye[i]);
    }
    hi.swap(s);
    s.swap(hi);
    // hi sequence should be (1, 11, 2, 22, 3, 33, 4, 44)
    hi.dump();
    
    Sequence bro;
    interleave(hi, y, bro);
    // bro sequence should be (1, 1, 11, 2, 2, 3, 22, 4, 3, 33, 4, 44)
    bro.dump();
    
    std::cout << "junho test 1 passed :P" << endl;
    
    return;
}

void junhoTest2(){
    Sequence a;
    assert(a.insert(4) == 0 && a.insert(0) == 0 && a.insert(2, 52) == 2 && a.insert(64) == 3 && a.insert(64) == 3 && a.insert(0, 64) == 0);
    assert(a.remove(64) == 3);
    // a sequence should be (0, 4, 52)
    a.dump();
    
    ItemType z = 68;
    assert(a.erase(2) && a.insert(252) == 2 && a.insert(34) == 2 && a.insert(3, 242) == 3);
    assert(a.set(3, z) && a.insert(140) == 4);
    // a sequence should be (0, 4, 34, 68, 140, 252)
    a.dump();
    
    Sequence b;
    b = a;
    assert(b.erase(b.find(252)) && b.remove(68) == 1 && b.erase(3) && b.remove(25) == 0);
    // b sequence should be (0, 4, 34)
    b.dump();
    assert(subsequence(a, b) == 0);
    assert(a.insert(0) == 0);
    assert(subsequence(a, b) == 1);
    assert(b.insert(3, 35));
    assert(subsequence(a, b) == -1);
    
    Sequence c;
    c.swap(a);
    c.dump();
    // c sequence should be (0, 0, 4, 34, 68, 140, 252)
    a.dump();
    // a sequence should be ()
    a = c;
    for(int i = 0; i < c.size(); ++i){
        ItemType hey;
        ItemType bro;
        a.get(i, hey);
        c.get(i, bro);
        assert(hey == bro);
    }
    assert(a.insert(999) == 7 && a.insert(0) == 0 && a.insert(0) == 0);
    assert(subsequence(a, c) == 2);
    assert(subsequence(c, a) == -1);
    assert(subsequence(a, b) == -1);
    assert(a.erase(0) && a.erase(0) && a.erase(0) && a.erase(0));
    // a sequence should be (4, 34, 68, 140, 252, 999)
    a.dump();
    
    assert(subsequence(a, c) == -1);
    assert(a.insert(0) == 0 && a.insert(0) == 0 && a.remove(252) == 1 && a.remove(999) == 1);
    assert(subsequence(a, c) == -1);
    // a sequence should be (0, 0, 4, 34, 68, 140)
    a.dump();
    
    Sequence d(a);
    assert(d.insert(0) == 0 && d.insert(3) == 3 && d.insert(6) == 5);
    assert(d.insert(0) == 0 && d.insert(0, 0) == 0 && d.insert(0) == 0 && d.insert(0) == 0 && d.remove(3) == 1 && d.remove(6) == 1);
    assert(d.size() == 11);
    // d sequence should be (0, 0, 0, 0, 0, 0, 0, 4, 34, 68, 140)
    d.dump();
    
    d.swap(a);
    assert(subsequence(a, d) == 5);
    
    
    std::cout << "junho test 2 passed :O" << endl;
    return;
}
/*
void kevinTest(){
    Sequence ss;  // ItemType is std::string
           ss.insert(0, "aaa");
           ss.insert(1, "bbb");
           ss.insert(2, "ccc");
           ItemType x = "xxx";
           assert(!ss.get(3, x)  &&  x == "xxx");  // x is unchanged
           assert(ss.get(1, x)  &&  x == "bbb");

       Sequence s;
           s.insert(0, "dosa");
           s.insert(1, "pita");
           s.insert(2, "");
           s.insert(3, "matzo");
           assert(s.find("") == 2);
           s.remove("dosa");
           assert(s.size() == 3  &&  s.find("pita") == 0  &&  s.find("") == 1  &&
                       s.find("matzo") == 2);

       Sequence s1;
           s1.insert(0, "paratha");
           s1.insert(0, "focaccia");
           Sequence s2;
           s2.insert(0, "roti");
           s1.swap(s2);
       Sequence s3 = s1; //testing the copy constructor
       Sequence s4 = s2; //testing the copy constructor
       s = s4; //testing the assignment operator
       s = s; //testing self referential assignment operator
           assert(s1.size() == 1  &&  s1.find("roti") == 0  &&  s2.size() == 2  &&
                       s2.find("focaccia") == 0  &&  s2.find("paratha") == 1);
           assert(s3.size() == 1  &&  s3.find("roti") == 0  &&  s.size() == 2  &&
                   s.find("focaccia") == 0  &&  s.find("paratha") == 1);
       
       Sequence s5;
       s5.insert(0, "hi");
       s5.insert(0, "why");
       s5.insert(1, "say");
       assert(s5.find("say") == 1);

       
       Sequence kevin;
       //testing insert(value) order
       assert(kevin.insert("c") == 0 && kevin.insert("e") == 1 && kevin.insert("b") == 0 &&
              kevin.insert("a") == 0 && kevin.insert("d") == 3);
       //testing erase positions
       assert(kevin.erase(4) && kevin.erase(3) && kevin.erase(2) && kevin.size() == 2);
       //testing remove values
       assert(kevin.remove("a") == 1 && kevin.insert("a") == 0);
       
       //testing remove on multiple copies
       Sequence hellos;
       std::string hello = "helllo";
       for (int i = 0; i < 500; i++)
       {
           hellos.insert(hello);
       }
       assert(hellos.remove(hello) == 500 && hellos.size() == 0);
       
       Sequence myAlphabet;
       std::string alphabet[] = {"a","b","c","d","e","f","g"};
       for (int i = 0; i < 7; i++)
       {
           myAlphabet.insert(i,alphabet[i]);
       }
       assert(myAlphabet.set(3,"e") && myAlphabet.remove("e") == 2 && myAlphabet.find("f") == 3);
       
       
       //using itemType = int
       Sequence seq1;
       std::string array[] ={"30","21","63","42","17","63","17","29","8","32"};
       for (int i =0; i < 10; i++)
       {
           seq1.insert(i, array[i]);
       }
       Sequence seq2;
       std::string array2[] = {"63","17","29"};
       for (int i =0; i < 3; i++)
       {
           seq2.insert(i, array2[i]);
       }
       Sequence seq3;
       std::string array3[] ={"17","63","29"};
       for (int i =0; i < 3; i++)
       {
           seq3.insert(i, array3[i]);
       }
       assert(subsequence(seq1, seq2) == 5); //testing subsequence function according to spec
       assert(subsequence(seq1, seq3) == -1); //testing subsequence function according to spec
       assert(subsequence(seq1, seq1) == 0); //testing the same seequence with itself

       Sequence seq4;
       std::string array4[] = {"30","21","63","42","17","63"};
       for (int i =0; i < 6; i++)
       {
           seq4.insert(i, array4[i]);
       }

       Sequence seq5;
       std::string array5[] = {"42","63","84","19"};
       for (int i =0; i < 4; i++)
       {
           seq5.insert(i, array5[i]);
       }

       Sequence combinedSeq;
       interleave(seq4, seq5, combinedSeq); //create a combined sequence from two sequences
       assert(combinedSeq.find("21") == 2 && combinedSeq.find("63") == 3 &&
              combinedSeq.find("19") == 7 && combinedSeq.find("17") == 8); //correct output is given by spec sheet
       cout << "All tests passed" << endl;
}

void testtest(){
    Sequence a;
    a.insert("0");
    a.insert("4");

    cout << "success" << endl;
}*/

void junhoTest3(){
    Sequence s;

            /* For an empty Sequence */
            assert(s.size() == 0); // test size
            assert(s.empty()); // test empty
            assert(!s.erase(0)); // nothing to remove

            /* Inserting and deleting items */
            assert(s.insert(5) == 0); // insert to empty Sequence
            assert(s.size() == 1); // test to make sure size is 1 after inserting only one item.
            assert(s.insert(34) == 1); // test if correctly inserted at index 1 because 34 > 5
            assert(s.remove(34)); // test to see if 34 is found and erased.

            assert(s.find(34) == -1); // test to see that 34 no longer exists in s.
            assert(s.remove(5) == 1); // test to see that 5 is only found once.
            assert(s.size() == 0); // test to make sure that sequence is now empty.
            assert(s.insert(4, 45) == -1); // test to see if item can’t be inserted if pos > size.

            assert(s.insert(1) == 0); // insert to empty Sequence
            assert(s.insert(1) == 0); // insert repeated value
            assert(s.insert(1) == 0); // insert repeated value
            assert(s.insert(1) == 0); // insert repeated value
            assert(s.remove(1) == 4); // test removing repeated values

            /* Test Swap */
            assert(s.insert(6) == 0); // inserting to empty Sequence
            assert(s.insert(39) == 1); // test adding second item
            assert(s.insert(6) == 0); // test adding to 0th position to a non-empty Sequence.
            assert(s.insert(3, 12) == 3); // test adding to certain position

            Sequence w;
            assert(w.insert(0, 5) == 0); // inserting to empty Sequence
            assert(w.insert(13) == 1); // test adding second item
            assert(w.insert(35) == 2); // test adding third item
            assert(w.insert(3, 72) == 3); // test adding to certain position
            assert(w.insert(4545) == 4); // test adding big number (to the end)

            w.swap(s);
            assert(s.size() == 5 && s.find(13) == 1); // check to make sure s is now what w was
            assert(w.size() == 4 && w.find(6) == 0); //check to make sure w is now what s was

            s.swap(w); // make sure that swap works the other way around too.
            assert(s.size() == 4 && s.find(39) == 2); // check to make sure w is back to before the first swap
            assert(w.size() == 5 && w.find(72) == 3); // check to make sure s is back to before the first swap


            /* Test Find Get and Set */
            ItemType x;
            assert(s.get(0, x) && x == 6); // test getting first item
            assert(s.get(3, x) && x == 12); // test getting last item

            assert(w.get(1, x) && x == 13); // test getting second item
            assert(w.get(0, x) && x == 5); // test getting first item

            ItemType y = 5;
            assert(s.set(0, y) && s.get(0, x) && y == x); // test setting first item, and making sure it equals get value
            x = 24;
            assert(w.set(2, x) && w.get(2, y) && x == y); // test setting third item, and making sure it equals get value

            assert(w.find(24) == 2); // test finding previously set value of 24
            assert(w.find(5) == 0); // test finding 0th index of Sequence
            assert(s.find(6) == 1); // test finding 1st index of Sequence

            /* Test Subsequence */
            Sequence a;
            assert(a.insert(24) == 0); // test inserting to 0th index
            assert(a.insert(72) == 1);
            assert(a.insert(4545) == 2);
            assert(subsequence(w, a) == 2); // test valid subsequence

            assert(a.remove(24) == 1); // test removing all instances of 35
            assert(subsequence(w, a) == 3); // test valid subsequence

            assert(a.insert(21) == 0); // test inserting to 0th index
            assert(subsequence(w, a) == -1); // test invalid subsequence

            Sequence b;
            assert(subsequence(w, b) == -1); // test empty seq2
            assert(subsequence(a, w) == -1); // test seq2 larger than seq1

            /* Test Interleave */
            interleave(s, w, a); // test interleave
            ItemType test[] = {5, 5, 6, 13, 39, 24, 12, 72, 4545};
        for(int i = 0; i < 9; ++i){
            ItemType temp;
            assert(a.get(i, temp));
            assert(test[i] == temp);
        }
            
            interleave(s, b, a); // test result not empty and seq2 is empty
            for(int i = 0; i < 4; ++i){ // test seq1 should equal result
                ItemType temp1;
                ItemType temp2;
                assert(s.get(i, temp1)); // test get for every index
                assert(a.get(i, temp2)); // test get for every index
                assert(temp1 == temp2); // test interleave values are correct.
            }
        
}
int main(){
    
    nehaTest();
    junhoTest1();
    junhoTest2();
    junhoTest3();
//    kevinTest();
  //  testtest();


}
