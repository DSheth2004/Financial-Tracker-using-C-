/*
Problem Statement:
Build a personal finance tracker that allows users to log expenses, categorize them, and generate
reports.
Requirements:
 Data Structure: Select an appropriate data structure(s) and justify their need.
 Functionality:
o add_expense(Date date, String category, double amount, String description):
Adds a new expense.
o remove_expense(int expenseId): Deletes an expense entry.
o get_expenses_by_category(String category): Returns a list of expenses under a
specified category.
o generate_monthly_report(Date month): Summarizes expenses for a given month
by category.
o get_total_expenses(): Returns the total amount of all recorded expenses.
 Other Features:
o Implement a feature to set budget limits for each category and alert users when
they exceed them.
o Provide visualization of spending trends over time.
*/
#include <bits/stdc++.h>
using namespace std;
// The below date class is for entering the date of a particular transaction.
class Date {
public:
    int day, month, year;
    Date (): day(0),month(0),year(0){}
    Date(int d, int m, int y) : day(d), month(m), year(y) {}
};


// This is a basic node structure used in the building of this tracker
class Node {
public:
    Date date; // Date object
    string category;
    double amount;
    string description;
    int expenseId;
    Node* next;

    Node(Date date1, string category1, double amount1, string description1, int expenseId1)
        : date(date1), category(category1), amount(amount1), description(description1), expenseId(expenseId1), next(nullptr) {}
    ~Node() = default;
};


// The below function helps to add expense in the finance tracker with the necessary parameters
Node* add_expense(Node* root, Date date, string category, double amount, string description,map<string,double>&category_all,map<string,double>&expense_sum_by_category,double &total_expense) {


    // Checks for the budget
    if ((expense_sum_by_category[category]+amount) > category_all[category]) { // category_all contains budget for each category
        cout<<"Amount exceeded....\n.Can't do transaction for "<<category<<endl;
        return root;
    }

    // Addition of expenses in each category sum and total expense variable
    expense_sum_by_category[category]+=amount;
    total_expense+=amount;


    static int id = 1; // Incrementing ID for each new expense

    // Creating a newnode
    Node* newnode = new Node(date, category, amount, description, id++);

    // If there is no entry then create linked list
    if (root == nullptr) {
        return newnode;
    }

    // Duplicating pointer in another pointer
    Node* temp = root;

    // Traversing to the last node
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    // Adding new node at the end of the linked list
    temp->next = newnode;

    // Returning the root
    return root;
}

// This function removes an expense by ID given total expense variable, and map of expense_sum_by_category
Node* remove_expense(int expenseId, Node* root,double&total_expense,map<string,double>&expense_sum_by_category) {
    if (root == nullptr) {
        cout << "The finance model is empty..." << endl;
        return nullptr;
    }

    Node* temp = root;
    Node* prev = nullptr;
    while (temp != nullptr) {
        if (temp->expenseId == expenseId) { // The correct expenseId is found
            if (prev == nullptr) { // Removing the root node
                root = root->next;
            } else {
                prev->next = temp->next;
            }
            total_expense-=(temp->amount); // Decrementing the expenseId's amount from total expense and map
            expense_sum_by_category[temp->category]-=temp->amount;
            delete temp; // Manually deleting that particular found node
            return root; // Returning the head of the linked list.
        }
        // Traversing the linked list
        prev = temp;
        temp = temp->next;
    }
    // If expenseId is not found:
    cout << "Expense with ID " << expenseId << " not found." << endl;
    return root;
}

// Printing expenses by category
void get_expenses_by_category(string category, Node* root) {
    Node* temp = root;
    bool found = false;  // Boolean variable to check if the category exists or not. It is initialised as false.
    while (temp != nullptr) {
        if (temp->category == category) {
            found = true; // As the category is found, true is assigned to found
            cout << "Expense ID: " << temp->expenseId << ", Date: " << temp->date.day << "/" << temp->date.month << "/" << temp->date.year
                 << ", Amount: " << temp->amount << ", Description: " << temp->description << endl;
        }
        // Traversing the linked list
        temp = temp->next;
    }

    // If the category is not found, that is, found is equal to found, print below Message
    if (!found) {
        cout << "No expenses found in category: " << category << endl;
    }
}


// This function prints all the expenses happened till date
void print_all_expenses(Node* root) {
    Node* temp = root;
    while (temp != nullptr) {
        cout << "Expense ID: " << temp->expenseId << ", Date: " << temp->date.day << "/" << temp->date.month << "/" << temp->date.year
             << ", Category: " << temp->category << ", Amount: " << temp->amount << ", Description: " << temp->description << endl;
        temp = temp->next;
    }
}

// This functions prints category wise total of a particular month
void summarize_expenses_by_category_month(Node* root, int month) {
    map<string, double> category_totals; // A map is created to count the total amount for each category

    Node* temp = root;
    while (temp != nullptr) {
        if (temp->date.month == month) { // If given month is found, increment it in its particular property
            category_totals[temp->category] += temp->amount;
        }
        temp = temp->next;
    }

    // Printing category and its total for that month
    for(auto it:category_totals){
        cout<<it.first<<" "<<it.second<<endl;
    }

}



// This functions prints category wise total of a particular year
void summarize_expenses_by_category_year(Node* root, int y) {
    map<string, double> category_totals; // A map is created to count the total amount for each category

    Node* temp = root;
    while (temp != nullptr) {
        if (temp->date.year == y) { // If given month is found, increment it in its particular property
            category_totals[temp->category] += temp->amount;
        }
        temp = temp->next;
    }


    // Printing category and its total for that month
    for(auto it:category_totals){
        cout<<it.first<<" "<<it.second<<endl;
    }

}


// This function sets the budget for a particular category
void set_budget(map<string,double>&category_all,string category,int val){
    category_all[category]=val;
}


int main() {
    Node* root = nullptr;
    double total_expense=0;
    map<string,double>expense_sum_by_category;
    map<string,double>category_all;
    int choice;
    int  id, mon, y2, budg, budg1;
    double amt;
    string cat, des, cat1, cat2;
    Date date1;
    do{
        cout<<"*************************************************\n\n";
        cout<<"Enter the choice as follows: "<<endl;
        cout<<"1. Add expense"<<endl;
        cout<<"2. Remove expense"<<endl;
        cout<<"3. Get Expenses by category"<<endl;
        cout<<"4. Change the budget of the category"<<endl;
        cout<<"5. Summary of all expenses category and month wise"<<endl;
        cout<<"6. Summary of all expenses category and year wise"<<endl;
        cout<<"7. Total expenses"<<endl;
        cout<<"8. Total expenses of a particular category"<<endl;
        cout<<"9. Display all expenses"<<endl;
        cin>>choice;
        switch(choice){
            case 1:

                cout<<"Enter the date of transaction (dd mm yy): "<<endl;
                cin>>date1.day>>date1.month>>date1.year;
                while(date1.day<1||date1.day>31){
                    cout<<"Enter the day in the proper range :- 1 to 31\n Re-enter the day: "<<endl;
                    cin>>date1.day;
                }
                while(date1.month<1||date1.month>12){
                    cout<<"Enter the month in the proper range :- 1 to 12\n Re-enter the month: "<<endl;
                    cin>>date1.month;
                }
                while(date1.year<2000||date1.year>3000){
                    cout<<"Enter the year in the proper range :- 0 to 3000\n Re-enter the year: "<<endl;
                    cin>>date1.year;
                }
                cout<<"Enter the category of transaction: "<<endl;
                cin.ignore();
                getline(cin,cat);
                if(category_all.find(cat)==category_all.end()){
                    cout<<"Enter the limit for "<<cat<< " category: "<<endl;
                    int budg;
                    cin>>budg;
                    set_budget(category_all,cat,budg);
                }
                cout<<"Enter the amount of the transaction: "<<endl;
                cin>>amt;
                cin.ignore();
                cout<<"Enter the description of transaction: "<<endl;
                getline(cin,des);
                root=add_expense(root,date1,cat,amt,des,category_all,expense_sum_by_category,total_expense);
                break;

            case 2:

                cout<<"Enter the expenseID for the transaction to be deleted: "<<endl;
                cin>>id;
                root=remove_expense(id,root,total_expense,expense_sum_by_category);
                break;

            case 3:

                cout<<"Enter the category of the transaction: "<<endl;
                cin>>cat1;
                get_expenses_by_category(cat1,root);
                break;

            case 4:

                cout<<"Enter the category for which you want to change budget: "<<endl;
                cin>>cat2;
                if(category_all.find(cat2)==category_all.end()){
                    cout<<cat2<< " does not exist"<<endl;
                }
                else{
                    cout<<"Enter the new budget for "<<cat2<<": "<<endl;
                    cin>>budg1;
                    if(budg1>category_all[cat2]) cout<<"The budget is incremented from new entries"<<endl;
                    else cout<<"The budget is decremented from new entries"<<endl;
                    set_budget(category_all,cat2,budg1);
                }
                break;

            case 5:

                cout<<"Enter the month for the summary of each category: "<<endl;
                cout<<"1. January"<<endl;
                cout<<"2. February"<<endl;
                cout<<"3. March"<<endl;
                cout<<"4. April"<<endl;
                cout<<"5. May"<<endl;
                cout<<"6. June"<<endl;
                cout<<"7. July"<<endl;
                cout<<"8. August"<<endl;
                cout<<"9. September"<<endl;
                cout<<"10. October"<<endl;
                cout<<"11. November"<<endl;
                cout<<"12. December"<<endl;
                do{
                    cin>>mon;
                    if(mon<1 || mon>12) cout<<"Invalid month. Please enter a number between 1 and 12"<<endl;
                }while(mon<1||mon>12);
                summarize_expenses_by_category_month(root,mon);
                break;

            case 6:

                cout<<"Enter the year for the summary of each category: "<<endl;
                cin>>y2;
                summarize_expenses_by_category_year(root,y2);
                break;

            case 7:

                cout<<"Total amount of all recorded expenses "<<total_expense<<endl;
                break;

            case 8:
                for(auto it:expense_sum_by_category){
                    cout<<it.first<<" "<<it.second<<endl;
                }
                break;

            case 9:
                print_all_expenses(root);
                break;

        }
        cout<<"*************************************************\n\n";
    }while(choice>=1&&choice<=9);
    delete root;
    root = nullptr;
    return 0;
}