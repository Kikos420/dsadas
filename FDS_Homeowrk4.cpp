#include <iostream>
#include <string>
#include <vector>
#include<unordered_set>
#include <algorithm>
using namespace std;
enum condition { New, Refurbished }; //we are making enum as global to have easier access 
//Vehicle class
class Vehicle {
private:
    unordered_set<string> listMake{ "Porsche","Subaru","Honda","Nissan","Lamborghini","Audi" }; //List of chosen cars we gonna use
    string carMaker; //carMaker
    string model;
    int year; //The year when car is published
public:
    Vehicle() { //Constructor
        carMaker = "";
        model = "";
        year = 0;
    }
    Vehicle(string modelMake, string modelName, int modelYear) {
        setMake(modelMake);
        model = modelName;
        setYear(modelYear);
    }
    void setMake(string n) {
        if (listMake.find(n) != listMake.end())
        {
            carMaker = n;
        }
        else
        {
            cout << "This car is not supported!" << endl;
        }
    }
    void setYear(int t) {
        if (t >= 1950 && t <= 2030) {
            year = t;
        }
        else {
            cout << "This production year is not supported!" << endl;
        }
    }
    int getYear() {
        return year;
    }
    string getModel() {
        return model;
    }
    string getMake() {
        return carMaker;
    }
};
class SparePart {
protected:

    string id;
    string name;
    string description;
    Vehicle* a;
    int occurrences;
    double price;
    float replacementTime;
    double replacementWage;
    string instructions;
    condition cond;
public:
    SparePart() {
       
        id = "";
        name = "";
        description = "";
        price = 0;
        replacementTime = 0;
        replacementWage = 0;
        instructions = "";
        occurrences = 0;
        cond = condition::New;
    }
    //We are using getters in this Constructor
    SparePart(string id1, string name1, string description1, Vehicle* v, double price1, condition c, float replacementtime1, float replacementwage1, int occurrences1, string instructions1) {
        id = id1;
        name = name1;
        description = description1;
        a = v;
        price = price1;
        cond = c;
        replacementTime = replacementtime1;
        replacementWage = replacementwage1;
        instructions = instructions1;
        occurrences = occurrences1;
    }
    int getWarranty() { //if the condition is new we give only 36 months  warranty otherwise we give only 3 months
        if (cond == New) {
            return 36;
        }
        else {
            return 3;
        }
    }
    virtual int SetOccurrences(int o)=0;
    virtual int GetOccurrences() = 0;
    virtual double getTotalPrice() = 0;  //Abstract method for total price
    
    
    


    string getId() {
        return id;
    }
    string getName() {
        return name;
    }
    string getDescription() {
        return description;
    }
    string getInstructions() {
        return instructions;
    }
    int getReplacementTime() {
        return replacementTime;
    }
    double getReplacementWage() {
        return replacementWage;
    }
    
   

    virtual void Output() = 0;
  


};
class AvailableSparePart : public SparePart {
private:
    int occurrences;
    int quantity;
    string location;

public:
    AvailableSparePart() :SparePart() {
        quantity = 0;
        location = "";
        occurrences;
    }
    //constructor
    AvailableSparePart(int w, string r, string id1, string name1, string description1, Vehicle* v, double price1, condition c, float replacementtime1, float replacementwage1, string instructions1) : SparePart(id1, name1, description1, v, price1, c, replacementtime1, replacementwage1, occurrences, instructions1)
    {
        occurrences = 0;
        quantity = w;
        location = r;
    }
    int getQuantity() { //we are using this getter for quantity
        return quantity;
    }
    string getLocation() { //we are using this getter for location
        return location;
    }
    double getTotalPrice() { //we are using this getter for price
        return (price + replacementTime * replacementWage);
    }
    int getDeliveryTime() { //we are using this getter for DeliveryTime
        return 0;
    }
    int GetOccurrences() {
        return occurrences;

    }
    int SetOccurrences(int o) {
        return occurrences;
    }
    void Output() {
        cout << "Quantity:" << endl;
        cout << "Location:" << endl;
        cout << getId() << endl;
        cout << getName() << endl;
        cout << getDescription() << endl;
        cout << getInstructions() << endl;
        cout << getReplacementTime() << endl;
        cout << getReplacementWage() << endl;
        cout << GetOccurrences() << endl;

        cout << getWarranty() << endl; //output 
    }
};
class ContractedSparePart : public SparePart { //inheriting class "SparePart class"
private:
    string vendor;
    double deliveryPrice;
    int deliveryTime;
public:
    ContractedSparePart() :SparePart() {
        vendor = "";
        deliveryPrice = 0;
        deliveryTime = 0;
    }
    //constructor
    ContractedSparePart(string vendor1, double dp, int dt, string id1, string name1, string description1, Vehicle* v, double price1, condition c, float replacementtime1, float replacementwage1, string instructions1) : SparePart(id1, name1, description1, v, price1, c, replacementtime1, replacementwage1,occurrences, instructions1)
    {
        vendor = vendor1;
        deliveryPrice = dp;
        deliveryTime = dt;
    }
    string getVendor() {
        return vendor;
    }
    double getDeliveryPrice() {
        return deliveryPrice;
    }
    int getDeliveryTime() {
        return deliveryTime;
    }
    double getTotalPrice() {

        return (price + replacementTime * replacementWage + deliveryPrice);
    }
    int GetOccurrences() {
        return occurrences;

    }
    int SetOccurrences(int o) {
        return occurrences;
    }
    void Output() {
        cout << vendor << endl;
        cout << getId() << endl;
        cout << getName() << endl;
        cout << getDescription() << endl;
        cout << getInstructions() << endl;
        cout << getReplacementTime() << endl;
        cout << getReplacementWage() << endl;
        cout << getWarranty() << endl;
        cout << GetOccurrences() << endl;
        cout << deliveryTime << endl;
        cout << deliveryPrice << endl;
    }
};


void badChar(string str, int size, int badchar[])
{
    int i;

    // Initialize all occurrences as -1
    for (i = 0; i < 256; i++)
        badchar[i] = -1;


    for (i = 0; i < 256; i++)
        badchar[(int)str[i]] = i;
}

void search(string txt, string pat)
{
    int m = pat.size();
    int n = txt.size();
    int occ = 0;

    int badchar[256];

    badChar(pat, m, badchar);

    int s = 0;
    while (s <= (n - m))
    {
        int j = m - 1;

        while (j >= 0 && pat[j] == txt[s + j])
            j--;

        if (j < 0)
        {
            occ++;

            s += (s + m < n) ? m - badchar[txt[s + m]] : 1;

        }

        else
            s += max(1, j - badchar[txt[s + j]]);
    }   
    
}
template<class Comparable>
void mergeSort(vector< Comparable>& a, vector<Comparable>& tmpArray, int left, int right)
{
    if (left < right) {
        int center = (left + right) / 2;
        mergeSort(a, tmpArray, left, center);
        mergeSort(a, tmpArray, center + 1, right);
        merge(a, tmpArray, left, center + 1, right);
    }
}
template<class Comparable>
void mergeSort(vector< Comparable>& a)
{
    vector<Comparable> tmpArray(a.size());
    mergeSort(a, tmpArray, 0, a.size() - 1);
}
template <class Comparable>
void merge(vector<Comparable>& a, vector<Comparable>& tmpArray, int leftPos, int rightPos, int rightEnd) {
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;
    while (leftPos <= leftEnd && rightPos <= rightEnd) // main loop
        if (a[leftPos]->GetOccurrences() <= a[rightPos]->GetOccurrences()) ///Compare the element
            tmpArray[tmpPos++] = a[leftPos++];
        else         tmpArray[tmpPos++] = a[rightPos++];
    while (leftPos <= leftEnd)// Copy the First Half
        tmpArray[tmpPos++] = a[leftPos++];
    while (rightPos <= rightEnd) // Copy The rest of right half
        tmpArray[tmpPos++] = a[rightPos++];
    for (int i = 0; i < numElements; i++, rightEnd--) // Copy tmpArray back     
        a[rightEnd] = tmpArray[rightEnd];
}


int main() { //Main function of driver
    vector <Vehicle*> vehicle;// Three pointers that we gonna use as requested
    vector <SparePart*>Parts;// Vector which holds pointers to istances of AbailbableSpareParts and ContractedParts
    vehicle.push_back(new Vehicle("Porsche", "911s", 1998));
    vehicle.push_back(new Vehicle("Subaru", "Impreza", 1998));
    vehicle.push_back(new Vehicle("Honda", "Civic Coupe Si (", 2020));
    vehicle.push_back(new Vehicle("Nissan", "370z", 2017));
    vehicle.push_back(new Vehicle("Lamborghini", "murcielago", 2006));
    vehicle.push_back(new Vehicle("Audi", "RS5", 2007));
    mergeSort(Parts);

    Parts.push_back(new AvailableSparePart(7, "London", "914", "Engine", "Dont try to replace it alone only in service", vehicle[1], 452.76, Refurbished, 45.46, 84.98, "When the yellow indicator lights up go to sercvice."));
    Parts.push_back(new AvailableSparePart(7, "Munich", "751", "Wheel", "Object that takes energy from engine to spin around and make the car drive forward or backward", vehicle[2], 241.26, New, .46, 75.45, "Can be replaced by yourself"));
    Parts.push_back(new AvailableSparePart(7, "Amsterdam", "842", "Head Lamp", "Object to illuminate the road ahead also takes energy from engine.", vehicle[3], 12.34, Refurbished, 62.66, 21.88, "You can controll using only the dashboard."));
    Parts.push_back(new ContractedSparePart("Sofia", 48.23, 6, "440", "AC", "Cooling device that takes energy from engine and fuel from the car to make you feel better while drivin", vehicle[4], 45.12, New, 10.45, 94.2, "Press the button on dashboard only works when radiator is on"));
    Parts.push_back(new ContractedSparePart("Tokyo", 38.45, 5, "29", "GearBox", "Tool which help the car to move and work properly while driving", vehicle[5], 854.6, New, 239.1, 26.8, "Only visible thing is the stick which helps you to change the gear"));
    string pattern;
    cout << "Enter a search key: ";
    cin >> pattern;

    for (int i = 0; i < Parts.size(); i++) {
        cout << Parts[i]->getName() << " for the price of: $" << Parts[i]->getDescription() << endl;
    }
    for (int i = 0; i < Parts.size(); i++) {
        cout << Parts[i]->getName() << " for the price of: $" << Parts[i]->GetOccurrences() << endl;
    }
    for (int i = 0; i < Parts.size(); i++);{
       
        Parts[i]->SetOccurrences(search(Parts[i]->getDescription(),pattern));
        return 0;
    }
