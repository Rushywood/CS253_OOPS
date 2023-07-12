//210676_Nitesh_Kaushal


#include <bits/stdc++.h>
using namespace std;

// Constant for the calculation of price
const int K = 1000000000;

// Struct form for easy storage and access of dates
struct Date
{
    int dd;
    int mm;
    int yy;
}; 


//Parent Class: Planet which serve as travel destinations
class Planet { 
public:
int pos_x;
int pos_y;
int pos_z;
string name;
void setCoordinates(int x, int y , int z)
{
    pos_x=x;
    pos_y=y;
    pos_z=z;
}

void getCoordinates()
{
    cout << "x: " << pos_x << " " << "y: " << pos_y << " " << "z: " << pos_z << endl;
}
};

// Bonus // We make child classes of Planets that have different attributes like water,atmosphere etc;

class Terrestrial: public Planet{
public:
void setName(string s)
{
    name=s;
}
string getName()
{
    return name;
}
void getAtmosphereinfo()
{
    cout << "The atmosphere is hot and humid"<< endl;
}
void getWaterinfo()
{
    cout << "The water here is scarce but present"<< endl;
}
};

class Jovian: public Planet{
public:
bool ring;
void setName(string s)
{
    name=s;
}
string getName()
{
    return name;
}
void getAtmosphereinfo()
{
    cout << "The atmosphere is cold and windy"<< endl;
}
void getWaterinfo()
{
    cout << "The water here is negligible and frozen" << endl;
}
void getRinginfo()
{
    if (ring)
    cout << "The ring is present" << endl;
    else
    cout << "This planet has no ring" << endl;
}
};

class Satelite: public Planet{
public:
string ParentPlanet;
void setName(string s)
{
    name=s;
}
string getName()
{
    return name;
}
void getClimateinfo()
{
    cout << "The climate is extreme" << endl;
}
void getWaterinfo()
{
    cout << "The water here is not available as of now"<< endl;
}
void setParentPlanet(string s)
{
    ParentPlanet = s;
}
void getParentPlanet()
{
    cout << "Parent planet is " << ParentPlanet << endl;
}
};

// Here we keep the track of number of days in a particular month
const int Days_of_months[12]
    = { 31, 28, 31, 30, 31, 30, 
       31, 31, 30, 31, 30, 31 };
  
//Function to count the leap years b/w 2 dates
int countLeapYears(Date d)
{
    int years = d.yy;
  
    if (d.mm <= 2)
        years--;
  
    return years / 4 
           - years / 100
           + years / 400;
}

//The function to claculate remaining time
int remaining_time(Date date1, Date date2)
{
    
    long int n1 = date1.yy * 365 + date1.dd;
  
    
    for (int i = 0; i < date1.mm - 1; i++)
        n1 += Days_of_months[i];
  
    
    n1 += countLeapYears(date1);
  
    long int n2 = date2.yy * 365 + date2.dd;
    for (int i = 0; i < date2.mm - 1; i++)
        n2 += Days_of_months[i];
    n2 += countLeapYears(date2);
  
    return (n2 - n1);
}

// Here we calculate the distance between two planets for the calculation of price.
float distance(Planet d, Planet s)
{
    float dist = sqrt(pow(d.pos_x - s.pos_x, 2) + pow(d.pos_y - s.pos_y, 2) + pow(d.pos_z - s.pos_z, 2) * 1.0);
    return dist;
}

// Here we create a ticket class whose objects are ticket for inter-planetory journeys
class Ticket{

    private:
    int price;

    public:

    Planet source_planet;
    Planet destination_planet;
    string traveller;
    Date date_of_booking;
    Date date_of_travel;
    Date return_date;

    bool return_status;
    bool validity;
    bool ticket_cancellation;

    Ticket(){
        return_status=false;
        validity=false;
        ticket_cancellation=false;
    }

    void set_return_date(Date return_d)
    {
        return_date=return_d;
    }

    void book_ticket(Planet p1, Planet p2,Date d1, Date d2)
    {
        source_planet=p1;
        destination_planet=p2;
        date_of_booking.dd=d1.dd;
        date_of_booking.mm=d1.mm;
        date_of_booking.yy=d1.yy;
        date_of_travel.dd=d2.dd;
        date_of_travel.mm=d2.mm;
        date_of_travel.yy=d2.yy;
    }

    void check_validity(Date date_today)
    {
        int remtim = remaining_time(date_today,date_of_travel);
        if (remtim >= 0)
        validity = true;
    }

    void update_ticket(Planet p2, Date d2)
    {
        destination_planet=p2;
        date_of_travel=d2;
    }

    void get_price()
    {
        int remtim = remaining_time(date_of_booking,date_of_travel);
        price=K*distance(source_planet,destination_planet)/(remtim+1);
        if (return_status)
        cout << "The price of ticket is $" << 2*price << endl;
        else
        cout << "The price of ticket is $" << 2*price << endl;
    }

    void cancel_ticket()
    {
        ;
    }

    void set_traveller(string s)
    {
        traveller=s;
    }
};

// Parent Class: Traveeler for all those who will be involved in the space travel
class Traveller{
    public:
    string name;
    int id;

    void set_ID(int ID)
    {
        id=ID;
    }

    int get_id()
    {
        return id;
    }

    void verify_id(int ID)
    {
        if (id == ID)
        cout << "ID Verified!" << endl;
        else
        cout << "ID not Verified" << endl;
    }

    vector <Ticket> travel_tickets; 

    void add_travel(Ticket t)
    {
        travel_tickets.push_back(t);
    }
};

//First child class of Traveller: Passengers- The normal travellers that will travel
class Passenger : public Traveller{
    public:

    void set_name(string s)
    {
        name = s;
    }
    string getName()
    {
        return name; 
    }
    void set_id(int ID)
    {
        id=ID;
    }
    int get_id()
    {
        return id;
    }
};

//Second child class of Travellers: Astronaut- The travellers that will fly the aircraft
class Astronaut : public Traveller{
   
    public:
    int experience;
    int license_id;

    void set_name(string s)
    {
        name = s;
    }
    string getName()
    {
        return name; 
    }
    void check_experience()
    {
        cout << "The experience of Astronaut: " << name << "is of " << experience << "years." << endl;
    }
    void set_experience(int exp)
    {
         experience=exp;
    }
    void setLicenseid(int ID)
    {
         license_id=ID;
    }
    int getLicenseid()
    {
        return license_id;
    }

};

//Third child class of travellers: Commander- The travellers that will be incharge of the journey
class Commander : public Traveller{
    
    public:
    int experience;
    int license_id;

    void set_name(string s)
    {
        name = s;
    }
    string getName()
    {
        return name; 
    }
    void check_experience()
    {
        cout << "The experience of Astronaut: " << name << "is of " << experience << "years." << endl;
    }
    void set_experience(int exp)
    {
         experience=exp;
    }
    void setLicenseid(int ID)
    {
         license_id=ID;
    }
    int getLicenseid()
    {
        return license_id;
    }
};

//This is the class of Space Travels that take place when more than 2 passengers travel to same destination from same source on the same day
class SpaceTravel{

    public:
    Astronaut A;
    Commander C;
    int no_of_passengers;
    vector <string> pass_list;
    Planet source_planet;
    Planet destination_planet;
    Date dot;

    SpaceTravel()
    {
        no_of_passengers=0;
    }

    void set_date_of_travel(Date date)
    {
        dot.dd=date.dd;
        dot.mm=date.mm;
        dot.yy=date.yy;
    }

    void set_source_planet(Planet P)
    {
        source_planet=P;
    }

    void set_destination_planet(Planet P)
    {
        destination_planet=P;
    }

    void add_passenger(string p)
    {
        pass_list.push_back(p);
        no_of_passengers++;
    }

    void set_astronaut(Astronaut aa)
    {
        this->A=aa;
    }
    Astronaut get_astronaut()
    {
        return A;
    }
    void set_commander(Commander cc)
    {
        C=cc;
    }
    Commander get_commander()
    {
        return C;
    }
    void update_astronaut(Astronaut aa)
    {
        this->A=aa;
    }
    void update_commander(Commander cc)
    {
        this->C=cc;
    }
    void print_ST()
    {
        cout << "Commander of the travel is " << get_commander().name << endl;
        cout << "Astronaut of the travel is " << get_astronaut().name << endl;
        cout << "Date of travel is " << dot.dd << " " << dot.mm << " " << dot.yy << endl;
        cout << "Source planet is " << source_planet.name<< endl;
        cout << "Destination planet is " << destination_planet.name << endl;
        cout << "Passengers travelling are: " << endl;

        for (int i = 0;i<no_of_passengers;i++)
        {
            cout << pass_list[i] << endl;
        }
    }
};

vector <Ticket> all_tickets;

//This keeps the track that how many passengers are going together
int verify_travel(Ticket T)
{
    int same_pass=0;
    for (int i=0;i<all_tickets.size();i++)
    {
        if ((all_tickets[i].destination_planet.name == T.destination_planet.name) && (all_tickets[i].source_planet.name == T.source_planet.name) && (all_tickets[i].date_of_travel.dd ==T.date_of_travel.dd) && (all_tickets[i].date_of_travel.mm ==T.date_of_travel.mm) && (all_tickets[i].date_of_travel.yy ==T.date_of_travel.yy)){
            same_pass++;
        }

    }
return same_pass;
}

//This funcction adds all the passengers that are going on a particular air space travel
void Add_other_passengers(SpaceTravel &S)
{
    for (int i = 0;i<all_tickets.size();i++)
    {
        if((all_tickets[i].destination_planet.name==S.destination_planet.name) && (all_tickets[i].source_planet.name==S.source_planet.name) && (all_tickets[i].date_of_travel.dd==S.dot.dd) && (S.dot.mm==all_tickets[i].date_of_travel.mm) && (S.dot.yy==all_tickets[i].date_of_travel.yy))
        {
                S.add_passenger(all_tickets[i].traveller);
        }
    }
}

void ticket_cancel(Ticket t)
{
    for (int i = 0;i<all_tickets.size();i++)
    {
        if (all_tickets[i].traveller== t.traveller)
        {
            all_tickets.erase(all_tickets.begin() + i);
            break;
        }
    }
}

//Function to print the ticket
void print_ticket(Ticket t)
{
    cout << "Ticket" << endl;
    cout << "**********************************************************" << endl;
    cout << "This ticket is for Mr./Ms. " << t.traveller << " travelling from " << t.source_planet.name << " to " << t.destination_planet.name << endl;
    cout << "The travel date is " << t.date_of_travel.dd << "-" << t.date_of_travel.mm << "-" << t.date_of_travel.yy << endl;
    t.get_price();
    if (t.return_status)
    {
        cout << "The passenger is also scheduled to return on " << t.return_date.dd <<"-"<<t.return_date.mm << "-" << t.return_date.yy << endl;
    }
    cout << "**********************************************************" << endl;
    cout << endl;
}

//Fucntion to print the space travel details
void print_Spaceticket(SpaceTravel S)
{
    cout <<"Space Travel" << endl;
    cout << "**********************************************************" << endl;
    S.print_ST();
    cout << "**********************************************************" << endl;
    cout << endl;
}

//Bonus// //To check clashes of same commander/astronaut for diffenet space travels at the same time
void check_clashes(SpaceTravel S[], int n)
{
    for (int i = 0;i<n;i++)
    {
        for (int j = i+1;j<n;j++)
        {
            if (((S[i].dot.dd==S[j].dot.dd) && (S[i].dot.mm==S[j].dot.mm) && (S[i].dot.yy==S[i].dot.yy))  && ((S[i].get_astronaut().name == S[j].get_astronaut().name) || (S[i].get_commander().name == S[j].get_commander().name)))
            {
                cout << "There is error in assigning Commander/Astronaut, Kindly update!" << endl; 
            }
        }
    }
}


int main()
{
    // First we initialize all the planets
    cout << "Welcome to the Space Travel Platform" <<  endl;
    Jovian jupiter;
    jupiter.setName("Jupiter");
    jupiter.setCoordinates(46,32,-12);
    jupiter.ring=false;

    Terrestrial mars;
    mars.setName("Mars");
    mars.setCoordinates(4,-6,8);

    Satelite moon;
    moon.setName("Moon");
    moon.setCoordinates(1,0,2);
    moon.setParentPlanet("Earth");

    //Adding Passengers
    Passenger Joey;
    Joey.set_name("Joey");
    Joey.set_id(10001);
    Passenger Ross;
    Ross.set_name("Ross");
    Ross.set_id(10002);
    Passenger Rachel;
    Rachel.set_name("Rachel");
    Rachel.set_id(10003);
    Passenger Phoebe;
    Phoebe.set_name("Phoebe");
    Phoebe.set_id(10004);
    Passenger Monica;
    Monica.set_name("Monica");
    Monica.set_id(10005);
    Passenger Chandler;
    Chandler.set_name("Chandler");
    Chandler.set_id(10006);
    Passenger Barney;
    Barney.set_name("Barney");
    Barney.set_id(10007);
    Passenger Ted;
    Ted.set_name("Ted");
    Ted.set_id(10008);
    Passenger Marshal;
    Marshal.set_name("Marshal");
    Marshal.set_id(10009);
    Passenger Lily;
    Lily.set_name("Lily");
    Lily.set_id(10010);
    Passenger Robin;
    Robin.set_name("Robin");
    Robin.set_id(10011);

    //Adding Astronauts
    Astronaut Buzz;
    Buzz.set_name("Buzz");
    Buzz.setLicenseid(62631);
    Buzz.set_experience(10);
    Astronaut Aldrin;
    Aldrin.set_name("Aldrin");
    Aldrin.setLicenseid(62632);
    Aldrin.set_experience(12);

    //Adding Commanders
    Commander Sheldon;
    Sheldon.set_name("Sheldon");
    Sheldon.setLicenseid(40401);
    Sheldon.set_experience(7);

    Commander Leonard;
    Leonard.set_name("Leonard");
    Leonard.setLicenseid(40402);
    Leonard.set_experience(8);

    SpaceTravel Space_Travels[10]; //Dummy objects created for later initialization
    int No_of_space_travels=0;

    //We set some dates for our ease
    struct Date date1;
    date1.dd=2;
    date1.mm=4;
    date1.yy=2025;

    struct Date date2;
    date2.dd=8;
    date2.mm=5;
    date2.yy=2029;

    struct Date date3;
    date3.dd=7;
    date3.mm=11;
    date3.yy=2027;

    //To show the implementaion of our functions we use these 5 tickets as examples
    Ticket t1,t2,t3,t4,t5;

    t1.book_ticket(mars,moon,date1,date2);
    Joey.add_travel(t1);
    t1.set_traveller(Joey.getName());
    if (verify_travel(t1) < 2)
    cout << "Booked a ticket but more Travellers needed!" << endl;
    else if (verify_travel(t1) == 2)
    {
        // Creating new space travel object
        int i = No_of_space_travels;
        Space_Travels[i].set_astronaut(Buzz);
        Space_Travels[i].set_commander(Sheldon);
        Space_Travels[i].set_source_planet(t1.source_planet);
        Space_Travels[i].set_destination_planet(t1.destination_planet);
        Space_Travels[i].set_date_of_travel(t1.date_of_travel);
        Space_Travels[i].add_passenger(t1.traveller);
        Add_other_passengers(Space_Travels[i]);
        No_of_space_travels++;
        cout << "Space Travel created!" << endl;
    }
    else if (verify_travel(t1) > 2 && verify_travel(t1) <= 10)
    {
        int k = 0;
        for (int i = 0;i<No_of_space_travels;i++)
        {
            if((Space_Travels[i].destination_planet.name==t1.destination_planet.name) && (Space_Travels[i].source_planet.name==t1.source_planet.name) && (Space_Travels[i].dot.dd==t1.date_of_travel.dd) && (Space_Travels[i].dot.mm==t1.date_of_travel.mm) && (Space_Travels[i].dot.yy==t1.date_of_travel.yy))
            {
                k=i;
                break;
            }
        }
        Space_Travels[k].add_passenger(t1.traveller);
        cout << "Passenger added to Space Travel!" << endl;
        
    }
    else
    {
        cout << "Traveller Limit Reached!" << endl;
    }
    all_tickets.push_back(t1);

    t2.book_ticket(jupiter,moon,date1,date3);
    Barney.add_travel(t2);
    t2.set_traveller(Barney.getName());
    if (verify_travel(t2) < 2)
    cout << "Booked a ticket but more Travellers needed!" << endl;
    else if (verify_travel(t2) == 2)
    {
        // Creating new space travel object
        int i = No_of_space_travels;
        Space_Travels[i].set_astronaut(Buzz);
        Space_Travels[i].set_commander(Sheldon);
        Space_Travels[i].set_source_planet(t2.source_planet);
        Space_Travels[i].set_destination_planet(t2.destination_planet);
        Space_Travels[i].set_date_of_travel(t2.date_of_travel);
        Space_Travels[i].add_passenger(t2.traveller);
        Add_other_passengers(Space_Travels[i]);
        No_of_space_travels++;
        cout << "Space Travel created!" << endl;

    }
    else if (verify_travel(t2) > 2 && verify_travel(t2) <= 10)
    {
        int k = 0;
        for (int i = 0;i<No_of_space_travels;i++)
        {
            if((Space_Travels[i].destination_planet.name==t2.destination_planet.name) && (Space_Travels[i].source_planet.name==t2.source_planet.name) && (Space_Travels[i].dot.dd==t2.date_of_travel.dd) && (Space_Travels[i].dot.mm==t2.date_of_travel.mm) && (Space_Travels[i].dot.yy==t2.date_of_travel.yy))
            {
                k=i;
                break;
            }
        }
        Space_Travels[k].add_passenger(t2.traveller);
        cout << "Passenger added to Space Travel!" << endl;
    }
    else
    {
        cout << "Traveller Limit Reached!" << endl;
    }
    all_tickets.push_back(t2);

    t3.book_ticket(mars,moon,date1,date3);
    t3.return_status=true;
    t3.set_return_date(date2);
    Robin.add_travel(t3);
    t3.set_traveller(Robin.getName());
    if (verify_travel(t3) < 2)
    cout << "Booked a ticket but more Travellers needed!" << endl;
    else if (verify_travel(t3) == 2)
    {
        // Creating new space travel object
        int i = No_of_space_travels;
        Space_Travels[i].set_astronaut(Buzz);
        Space_Travels[i].set_commander(Sheldon);
        Space_Travels[i].set_source_planet(t3.source_planet);
        Space_Travels[i].set_destination_planet(t3.destination_planet);
        Space_Travels[i].set_date_of_travel(t3.date_of_travel);
        Space_Travels[i].add_passenger(t3.traveller);
        Add_other_passengers(Space_Travels[i]);
        No_of_space_travels++;
        cout << "Space Travel created!" << endl;
    }
    else if (verify_travel(t3) > 2 && verify_travel(t3) <= 10)
    {
        int k = 0;
        for (int i = 0;i<No_of_space_travels;i++)
        {
            if((Space_Travels[i].destination_planet.name==t3.destination_planet.name) && (Space_Travels[i].source_planet.name==t3.source_planet.name) && (Space_Travels[i].dot.dd==t3.date_of_travel.dd) && (Space_Travels[i].dot.mm==t3.date_of_travel.mm) && (Space_Travels[i].dot.yy==t3.date_of_travel.yy))
            {
                k=i;
                break;
            }
        }
        Space_Travels[k].add_passenger(t3.traveller);
        cout << "Passenger added to Space Travel!" << endl;
    }
    else
    {
        cout << "Traveller Limit Reached!" << endl;
    }
    all_tickets.push_back(t3);

    t4.book_ticket(jupiter,moon,date1,date3);
    Ross.add_travel(t4);
    t4.set_traveller(Ross.getName());
    if (verify_travel(t4) < 2)
    cout << "Booked a ticket but more Travellers needed!" << endl;
    else if (verify_travel(t4) == 2)
    {
        // Creating new space travel object
        int i = No_of_space_travels;
        Space_Travels[i].set_astronaut(Buzz);
        Space_Travels[i].set_commander(Sheldon);
        Space_Travels[i].set_source_planet(t4.source_planet);
        Space_Travels[i].set_destination_planet(t4.destination_planet);
        Space_Travels[i].set_date_of_travel(t4.date_of_travel);
        Space_Travels[i].add_passenger(t4.traveller);
        Add_other_passengers(Space_Travels[i]);
        No_of_space_travels++;
        cout << "Space Travel created!" << endl;
    }
    else if (verify_travel(t4) > 2 && verify_travel(t4) <= 10)
    {
        int k = 0;
        for (int i = 0;i<No_of_space_travels;i++)
        {
            if((Space_Travels[i].destination_planet.name==t4.destination_planet.name) && (Space_Travels[i].source_planet.name==t4.source_planet.name) && (Space_Travels[i].dot.dd==t4.date_of_travel.dd) && (Space_Travels[i].dot.mm==t4.date_of_travel.mm) && (Space_Travels[i].dot.yy==t4.date_of_travel.yy))
            {
                k=i;
                break;
            }
        }
        Space_Travels[k].add_passenger(t4.traveller);
        cout << "Passenger added to Space Travel!" << endl;
    }
    
    else
    {
        cout << "Traveller Limit Reached!" << endl;
    }
    all_tickets.push_back(t4);

    t5.book_ticket(jupiter,moon,date1,date3);
    Rachel.add_travel(t5);
    t5.set_traveller(Rachel.getName());
    if (verify_travel(t5) < 2)
    cout << "More Travellers Needed!" << endl;
    else if (verify_travel(t5) == 2)
    {
        int i = No_of_space_travels;
        Space_Travels[i].set_astronaut(Aldrin);
        Space_Travels[i].set_commander(Leonard);
        Space_Travels[i].set_source_planet(t5.source_planet);
        Space_Travels[i].set_destination_planet(t5.destination_planet);
        Space_Travels[i].set_date_of_travel(t5.date_of_travel);
        Space_Travels[i].add_passenger(t5.traveller);
        Add_other_passengers(Space_Travels[i]);
        No_of_space_travels++;
        cout << "Space Travel created!" << endl;
    }
    else if (verify_travel(t5) > 2 && verify_travel(t5) <= 10)
    {
        int k = 0;
        for (int i = 0;i<No_of_space_travels;i++)
        {
            if((Space_Travels[i].destination_planet.name==t5.destination_planet.name) && (Space_Travels[i].source_planet.name==t5.source_planet.name) && (Space_Travels[i].dot.dd==t5.date_of_travel.dd) && (Space_Travels[i].dot.mm==t5.date_of_travel.mm) && (Space_Travels[i].dot.yy==t5.date_of_travel.yy))
            {
                k=i;
                break;
            }
        }
        Space_Travels[k].add_passenger(t5.traveller);
        cout << "Passenger added to Space Travel!" << endl;
    }
    else
    {
        cout << "Traveller Limit Reached!" << endl;
    }
    all_tickets.push_back(t5);

    //You can print the tickets here
    for (int i = 0;i<all_tickets.size(); i++)
    {
        print_ticket(all_tickets[i]);
    }

    //You can print the SpaceTravels here
    for (int i = 0;i<No_of_space_travels; i++)
    {
        print_Spaceticket(Space_Travels[i]);
    }
    
    //update the astronaut and commander for any space travel example
    Space_Travels[0].update_astronaut(Buzz);
    Space_Travels[0].update_commander(Sheldon);

    // Cancel a ticket
    // Let us suppose we cancel the ticket t1
    ticket_cancel(t1);

    //You can print the SpaceTravelshere again to check the working of update function
    for (int i = 0;i<No_of_space_travels; i++)
    {
        print_Spaceticket(Space_Travels[i]);
    }
    //To check clashees of the particular commander/astronaut
    check_clashes(Space_Travels,No_of_space_travels);

    return 0;
}
