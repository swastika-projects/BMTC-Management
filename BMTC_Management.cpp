#include<iostream>
#include<string>
#include<bits/stdc++.h>
using namespace std;

#define FARE 5
#define MIN_BAL 50
#define MAX_LOAD 5
#define MAXX 100

class RFID{
public:
    int RFID_no;
    float bal;
    int source, dest;

    RFID(){}
    RFID(int& n, float& b, int& s){
        RFID_no = n;
        bal = b;
        source = s;
        dest=0;
    }
    void updateDest(int d){
        dest = d;
    }
    float updateBal(){
        bal -= (dest-source)*FARE;
        return bal;
    }
};

class person{
public:
    string name, phone;
    string names[4] = {"MICHAEL SCOTT","DWIGHT SCHRUTE","JIM HALPERT","KEVIN MALONE"};

    RFID card;
    person() {}
    person(string p, int n, float b, int s){
        name = names[rand()%4];
        phone = p;
        //card(n,b,s);
        card.RFID_no=n;
        card.bal=b;
        card.source = s;
    }


    int minBalCheck(){
        return card.bal >= MIN_BAL ? 1 : 0;
    }
} ;


//GLOBAL PERSON ARRAY
person personArr[MAXX];

class bus{
public:
   static int load;
   int prev_load=0;
   int bus_no, license = 45632;
   int src, dst;
   int path[5] = {1,2,3,4,5};
   static int currentStop;
   map<int, int> passengers;

   bus() {load=0;}
  /* bus(int l, int bn, int s, int d, int crr){
       load +=l;
       bus_no = bn;
       src = s;
       dst = d;
       currentStop = crr;
   }*/
   void ctor(int l, int bn, int s, int d, int crr){
       load =l;
       prev_load=load;
       bus_no = bn;
       src = s;
       dst = d;
       currentStop = crr;
   }
   void updateLoad(int en, int ex){
       prev_load=load;
       load = load - ex + en;
       cout << "TOTAL PASSENGERS : "<< load << endl;
   }
   int overloadCheck(){
       int flag = 1;
       if(load>MAX_LOAD){
            flag=0;
            load=prev_load;
       }
       return flag;
   }
   int RFID_Scan();
   void updateStatus(int);
};

int bus :: load = 0;
int bus :: currentStop = 1;

int bus :: RFID_Scan(){

    int rfid;
    float b;
    cout << "\nRFID : ";
    cin >> rfid;
    cout << "BAL : ";
    cin >> b;

    person p("987654987",rfid, b, currentStop);

    personArr[rfid] = p;

    //UPDATING SOURCE ON THE CARD
    //personArr[rfid].card.source=currentStop;

    if(p.minBalCheck()){
        passengers[rfid] = b;
        return 1;
    }else{
        cout << "\nXXXXXXXXXXXXXXXXX NOT ENOUGH BALANCE!!! XXXXXXXXXXXXXXXXX\n";
    }
    return 0;
}
void bus :: updateStatus(int crr) {
    int enter, exit, rfid, b;

    currentStop = crr;

    cout << "EXIT : ";
    cin >> exit;
    cout << "ENTRY : ";
    cin >> enter;

    updateLoad(enter, exit);

    if(exit!=0){
        cout << "\n\t\t\t\t\tCHOOSE RFID TO EXIT\n";
        cout << "\t\t\t\t\t____________________\n";
        map<int, int>::iterator itr;
        for(itr = passengers.begin(); itr!= passengers.end(); itr++){
            cout << itr->first << "  ";
        }

        cout << endl;

        for(int i=0;i<exit;i++){
            int temp;
            cin >> temp;
            passengers.erase(temp);
            personArr[temp].card.dest=currentStop;
            personArr[temp].card.updateBal();
            cout << "\n\t\t\t\t| -----------------------------|\n";
            cout << "\t\t\t\t  NAME : "<< personArr[temp].name << endl;
            cout << "\t\t\t\t  RFID NO : " << personArr[temp].card.RFID_no << endl;
            cout << "\t\t\t\t  REMAINING BALANCE : " << personArr[temp].card.bal << endl;
            cout << "\t\t\t\t| -----------------------------|\n" << endl;
        }
    }

    if(overloadCheck()){
        cout << "\n\t\t\t\t\tENTERING PASSENGER'S DETAILS\n";
        cout << "\t\t\t\t\t_____________________________\n";
        for(int i=0;i<enter;i++){
            int chk = RFID_Scan();
            if(!chk){
                load-=1;
            }
        }
    }
    else{

        cout << "\n\t\t\tXXXXXXXXXXXXXXXXXX OVERLOAD!!! XXXXXXXXXXXXXXXXXXX\n\n";
        cout << "ENTER NO OF PASSENGERS AGAIN : ";
        cin >> enter;
        updateLoad(enter, exit);
        for(int i=0;i<enter;i++){
            int chk = RFID_Scan();
            if(!chk){
                load-=1;
            }
        }
    }
}



int main(){

    int busNo,ld = 0;
    int flag = 0;
    int curr = 1;

    cout << "\n\t\t\t\t----------------------WELCOME------------------------\n\n";
    cout << "ENTER THE BUS NO : ";
    bus b;
    cin >> busNo;
    cout << "\n---------------------------------------------------\n";
    cout << "THIS BUS STARTS FROM SOURCE : 1 TO DESTINATION : 5\nLICENSE NO : " << b.license << "\nBUS NUMBER : " << busNo;
    cout << "\n---------------------------------------------------\n";

    cout << "\nPRESS 0 TO START THE BUS\n";
    cin >> flag;
    // cout << "ENTER NO OF INCOMING PASSENGERS : ";
    // cin >> ld;
    // bus b(ld, busNo, 1, 5, 1);
    // cout << "THIS BUS STARTS FROM SOURCE : 1 TO DESTINATION : 5\nLICENSE NO : " << b.license;

    // if(b.overloadCheck()){
    //     cout << "\nBUS STARTS SOON. PRESS 1 TO STOP AT EVERY STOP\n";
    //     cout << "\n\n......BUS IS MOVING.......\n\n";
    //     cin >> flag;
    // }else{
    //     cout << "\nXXXXXXXXXXXXXXXXXX OVERLOAD!!! XXXXXXXXXXXXXXXXXXX\n";
    //     cout << "ENTER NO OF PASSENGERS AGAIN : ";
    //     cin >> ld;
    //     if(ld <= MAX_LOAD){
    //         cout << "\nBUS STARTS SOON. PRESS 1 TO STOP AT EVERY STOP\n";
    //         cout << "\n\n......BUS IS MOVING.......\n\n";
    //         cin >> flag;
    //     }
    // }
    for(int i=1;i<=5;i++){
        cout << "\n--------------------------------BUS STOP NO : " << i << "-----------------------------------------\n" << endl;
        if(i==1){
            //cout << "ENTER NO OF INCOMING PASSENGERS : ";
            //cin >> ld;
            b.ctor(0, busNo, 1, 5, 1);
            b.updateStatus(i);
        }
        //b.updateStatus(i);


        //bus stops
        if(flag == 1){
            flag = 0;
            //curr = i;
            b.currentStop = i;
            b.updateStatus(i);
        }
        cout << "\nBUS STARTS SOON. PRESS 1 TO STOP AT EVERY STOP\n";
        cout << "\n\n--------------------------------BUS IS MOVING--------------------------------------------\n\n";
        cin >> flag;

    }

    return 0;
}

