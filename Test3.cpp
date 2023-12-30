#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

class User;
void NewDataUser(string n, string ic, string p, string mail);
void deleteDataUser(string n);

class User
{
private:
    string Name;
    string IC;
    string Phone;
    string Email;

public:
    User *next;
    User(string Name, string IC, string Phone, string Email)
        : Name(Name), IC(IC), Phone(Phone), Email(Email) {}

    string getName() const
    {
        return Name;
    }
    string getIC() const
    {
        return IC;
    }
    string getPhone() const
    {
        return Phone;
    }
    string getEmail() const
    {
        return Email;
    }

    void display() const
    {
        cout << setw(25) << "Name: " << Name << endl;
        cout << setw(42) << "Identification Number: " << IC << endl;
        cout << setw(33) << "Phone Number: " << Phone << endl;
        cout << setw(26) << "Email: " << Email << endl;
    }
};

class UserList
{
private:
    User *head;

public:
    UserList()
    {
        head = NULL;
    }

    bool isEmpty()
    {
        return head = NULL;
    }

    User *getHead() const
    {
        return head;
    }

    //* Insert value at the  start of the node
    User *insertFirstNodeUser(string n, string ic, string p, string mail)
    {
        int currIndex = 0;
        User *curr = head;
        User *prev = NULL;

        while (curr != NULL)
        {
            prev = curr;
            curr = curr->next;
            currIndex++;
        }

        User *newNode = new User(n, ic, p, mail);

        if (currIndex == 0)
        {
            newNode->next = head;
            head = newNode;
        }
        else
        {
            newNode->next = prev->next;
            prev->next = newNode;
        }

        return newNode;
    }

    //* Insert new value at the exact location
    User *insertMidNodeUser(string n, string ic, string p, string mail, int location)
    {
        if (location < 0)
        {
            cout << "Sorry Invalid Location." << endl;
            return 0;
        }

        int currIndex = 1;
        User *curr = head;
        User *prev = NULL;

        while (curr != NULL && currIndex < location)
        {
            prev = curr;
            curr = curr->next;
            currIndex++;
        }

        User *newNode = new User(n, ic, p, mail);

        if (currIndex == 1)
        {
            newNode->next = head;
            head = newNode;
        }
        else if (currIndex == location)
        {
            newNode->next = curr;
            prev->next = newNode;
        }
        else
        {
            cout << "Node number value is over the existing value. Value will be inserted at the end of the node." << endl;
            prev->next = newNode;
        }

        return newNode;
    }

    //* Insert new value at the end of the node
    User *insertEndNodeUser(string n, string ic, string p, string mail)
    {
        User *newNode = new User(n, ic, p, mail);

        if (head == NULL) //*If list is empty insert at head
        {
            head = newNode;
        }

        else
        {
            User *curr = head;

            while (curr->next != NULL)
            {
                curr = curr->next;
            }

            curr->next = newNode;
        }

        return newNode;
    }

    //* Delete node at the first Linked List
    void deleteFirstNodeUser()
    {
        User *temp = head;
        head = temp->next;

        deleteDataUser(temp->getIC());
        delete temp;
    }

    //* Delete node with specific value
    int deleteMidNodeUser(string n)
    {
        User *curr = head;
        User *prev = NULL;
        int currentIndex = 1;

        while (curr != NULL && (curr->getIC() != n))
        {
            prev = curr;
            curr = curr->next;
            currentIndex++;
        }

        if (curr != NULL)
        {
            if (prev != NULL)
            {
                prev->next = curr->next;
                delete curr;
            }
            else
            {
                head = curr->next;
                delete curr;
            }

            deleteDataUser(n);

            return currentIndex;
        }
        else
        {
            return 0;
        }
    }

    //* Delete node the end of the Linked List
    void deleteBackNodeUser()
    {
        User *temp = head;
        User *stay = NULL;

        while (temp->next != NULL)
        {
            stay = temp;
            temp = temp->next;
        }

        stay->next = NULL;
        deleteDataUser(temp->getIC());
        delete temp;
    }

    int findNodeUser(string n, string ic, string p, string mail)
    {
        int currentIndex = 1;
        User *curr = head;

        while (curr != NULL && (curr->getName() != n || curr->getIC() != ic || curr->getPhone() != p || curr->getEmail() != mail))
        {
            curr = curr->next;
            currentIndex++;
        }

        if (curr != NULL)
            return currentIndex;
        else
            return 0;
    }

    void displayListUser()
    {
        User *curr = head;
        while (curr != NULL)
        {
            cout << "Name: " << curr->getName() << endl
                 << "Identification Number: " << curr->getIC() << endl
                 << "Phone Number: " << curr->getPhone() << endl
                 << "Email: " << curr->getEmail() << endl;

            cout << endl;
            curr = curr->next;
        }
    }

    void updateCSVUser(string n, string ic, string p, string mail)
    {
        int currentIndex = 0;
        User *curr = head;
        User *prev = NULL;

        while (curr != NULL && (n > curr->getName() || (n == curr->getName() && ic > curr->getIC()) || (n == curr->getName() && ic == curr->getIC() && p > curr->getPhone()) || (n == curr->getName() && ic == curr->getIC() && p > curr->getPhone() && mail > curr->getEmail()) || (n == curr->getName() && ic == curr->getIC() && p > curr->getPhone() && mail > curr->getEmail())))
        {
            prev = curr;
            curr = curr->next;
            currentIndex++;
        }

        User *newNode = new User(n, ic, p, mail);

        if (head == NULL)
        {
            head = newNode;
        }
        else
        {
            User *current = head;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = newNode;
        }

        NewDataUser(n, ic, p, mail);
    }
};

void LoadFiles(vector<User> &users)
{
    ifstream userFile("data/user.csv");
    string lineUser;

    getline(userFile, lineUser); // skip the headings

    while (getline(userFile, lineUser))
    {
        string name, ic, phone, email;
        stringstream ss(lineUser); // get the whole line
        getline(ss, name, ',');
        getline(ss, ic, ',');
        getline(ss, phone, ',');
        getline(ss, email, ',');

        users.push_back(User(name, ic, phone, email));
    }

    userFile.close();
};

//* List function User
void NewDataUser(string n, string ic, string p, string mail)
{
    ofstream userfile("data/user.csv", ios::app);
    userfile.seekp(0, ios::end);
    userfile << "\n"
             << n << "," << ic << "," << p << "," << mail;

    userfile.seekp(0, ios::end);
    userfile.close();
};

void deleteDataUser(string n)
{
    ifstream inputfile("data/user.csv");
    ofstream tempfile("data/temp.csv");

    string line;
    getline(inputfile, line);

    tempfile << line << endl;

    while (getline(inputfile, line))
    {
        stringstream ss(line);
        string Name, IC, Phone, Email;

        getline(ss, Name, ',');
        getline(ss, IC, ',');
        getline(ss, Phone, ',');
        getline(ss, Email, ',');

        if (IC != n)
        {
            tempfile << line << endl;
        }
    }

    inputfile.close();
    tempfile.close();

    remove("data/user.csv");
    rename("data/temp.csv", "data/user.csv");
}

int main()
{
    vector<User> user;
    LoadFiles(user);
    UserList userList;

    // for (int i = 0; i < user.size(); i++)
    // {
    //     user[i].display();
    // }

    for (int i = 0; i < user.size(); i++)
    {
        userList.insertFirstNodeUser(user[i].getName(), user[i].getIC(), user[i].getPhone(), user[i].getEmail());
    }
    userList.displayListUser();

    // userList.insertEndNodeUser("Arif", "90280820", "01957783775", "arupan@emau.com");
    // userList.insertMidNodeUser("Arif", "90280820", "01957783775", "arupan@emau.com", 3);

    // userList.deleteFrontNodeUser();
    // userList.deleteMidNodeUser("123456789012");
    // userList.deleteBackNodeUser();

    userList.displayListUser();
}