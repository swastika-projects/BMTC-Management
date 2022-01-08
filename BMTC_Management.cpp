#include<iostream>
#include<string>
#include<bits/stdc++.h>
using namespace std;

#define FARE 5
#define MIN_BAL 50
#define MAX_LOAD 5


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

    RFID card;
    person() {}
    person(string nm, string p, int n, float b, int s){
        name = nm;
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

class bus{
public:
   static int load;
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
       bus_no = bn;
       src = s;
       dst = d;
       currentStop = crr;
   }
   void updateLoad(int en, int ex){
       load = load - ex + en;
       cout << "TOTAL PASSENGERS : "<< load << endl;
   }
   int overloadCheck(){
       return load <= MAX_LOAD ? 1 : 0;
   }
   int RFID_Scan();
   void updateStatus(int);
};

int bus :: load = 0;
int bus :: currentStop = 1;

int bus :: RFID_Scan(){

    int rfid;
    float b;
    cout << "RFID : ";
    cin >> rfid;
    cout << "BAL : ";
    cin >> b;

    person p("ALICE","987654987",rfid, b, currentStop);
    //RFID r = new RFID(rfid, b, currentStop);
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
        cout << "\n................CHOOSE RFID TO EXIT...................\n";
        map<int, int>::iterator itr;
        for(itr = passengers.begin(); itr!= passengers.end(); itr++){
            cout << itr->first << endl;
        }
        for(int i=0;i<exit;i++){
            int temp;
            cin >> temp;
            passengers.erase(temp);
        }
    }

    if(overloadCheck()){
        cout << "\n................ENTERING PASSENGER'S DETAILS...................\n";
        for(int i=0;i<enter;i++){
            int chk = RFID_Scan();
            if(!chk){
                load-=1;
            }
        }
    }
    else{
        cout << "\nXXXXXXXXXXXXXXXXXX OVERLOAD!!! XXXXXXXXXXXXXXXXXXX\n";
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

    cout << "----------------------WELCOME------------------------\n";
    cout << "ENTER THE BUS NO : ";
    bus b;
    cin >> busNo;
    cout << "THIS BUS STARTS FROM SOURCE : 1 TO DESTINATION : 5\nLICENSE NO : " << b.license << "\nBUS NUMBER : " << busNo << endl;

    cout << "PRESS 0 TO START THE BUS\n";
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
        cout << "..............BUS STOP NO : " << i << "..............." << endl;
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
        cout << "\n\n......BUS IS MOVING.......\n\n";
        cin >> flag;

    }

    return 0;
}
