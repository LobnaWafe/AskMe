#include <iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;
struct Data
{
	int ID;
	string Name, Email, Passward;

};

struct QS
{
	string qa;
	int from, to,counter_qs;
};

struct QS_to_one_user
{
	int id_qs;
	string qs;
};

int number_of_users = 0;

vector<Data>v_d;
vector<QS>v_q;
vector<QS_to_one_user>v_a;

int id_curr = 0;


class File_data
{
	int count = 0;
public:
	fstream f_AN,f_QS;

	Data ob,ob1;
	File_data() {}
	void set_data(Data ob)
	{
		/////
		_clear_();
        /////
		fstream user;
		user.open("users_data.txt", ios::out | ios::app);
		user << ob.ID << "\n";
		user <<ob.Name << "\n";
		user << ob.Email << "\n";
		user << ob.Passward << "\n";
		user.close();
		count++;
	
		v_d.push_back(ob);
		number_of_users++;
	}
	void put_data()
	{
		/////
		//_clear_();
		/////
		fstream user;
		user.open("users_data.txt", ios::in);
		string s; int id;
		int count_line = 0;
		while (getline(user, s))
		{
			number_of_users++;
			if (count_line % 4 == 0)
			{
				ob1.ID = stoi(s);
				
			}
			else if (count_line % 4 == 1)
			{
				ob1.Name = s;
				
			}
			else if (count_line % 4 == 2)
			{
				ob1.Email = s;
				
			}
			else {
				ob1.Passward = s;
				v_d.push_back(ob1);
			}
			count_line++;
		}
		user.close();
	}


	void put_qs()
	{
		/////
		//_clear_();
		/////

		f_QS.open("question.txt", ios::in);
		string s; int i = 0;

		while (getline(f_QS, s))
		{
			QS q;
			if (i % 4 == 0) {
				q.counter_qs = stoi(s);

			}
			else if (i % 4 == 1) {
				q.from = stoi(s);
			}
			else if (i % 4 == 2) {
				q.to = stoi(s);

			}
			else {
				q.qa = s;
				v_q.push_back(q);

			}

			i++;
		}

		f_QS.close();
	}

	void put_answer()
	{
	
		/////
		//_clear_();
		/////
		QS_to_one_user qou1;
		int i = 0; string s_a;
		f_AN.open("Answers.txt", ios::in);
		while (getline(f_AN, s_a))
		{
			if (i % 2 == 0)
			{
				qou1.id_qs = stoi(s_a);

			}
			else
			{
				qou1.qs = s_a;
				v_a.push_back(qou1);
			}
			i++;
		}
		f_AN.close();
	}

	bool check_answer(int id_q)
	{
		/////
		_clear_();
		/////

		for (int i = 0; i < v_a.size(); i++)
		{
			if (v_a[i].id_qs == id_q)
				return true;
		}
		return false;
	}

	void _clear_()
	{

		v_d.clear(); v_a.clear(); v_q.clear();
		put_data();
		put_qs();
		put_answer();
	}

};


class Acount : public File_data
{
public:
	Acount(){}
	

	bool sign_up(Data ob)
	{
	

		/////
		_clear_();
		/////

		cout << "enter your ID\n"; cin >> ob.ID; 
		bool ch = false;
		if (ob.ID < 0)
		{
			return false;

		}
		else
		{
			for (int i = 0; i < v_d.size(); i++)
			{
				if (ob.ID == v_d[i].ID)
				{
					cout << "Invalid ID\n";
					return false;
				}
			}
		}
	
		id_curr = ob.ID;

		cout << "enter your name\n"; cin >> ob.Name;
		cout << "enter your email\n"; cin >> ob.Email;
		if (check_email(ob))
		{
			return false;
		}
		cout << "enter your passward\n"; cin >> ob.Passward;
		
		set_data(ob);
		return true;
	}
	bool sign_in()
	{	
		/////
		_clear_();
		/////

		 string email,passward;
		cout << "enter your email\n"; cin >> email; 

		if (!check_email_in(email))
		{
			cout << "your email is not exist\n";
			return false;
		}

		cout << "enter your passward\n"; cin >> passward;
		int i = 0; int ch = 0; int count_chance = 3;
		while (i < v_d.size())
		{
			if (v_d[i].Email == email)
			{
				id_curr = v_d[i].ID;
				if (v_d[i].Passward == passward)
				{
					ch = 1;
				}
				else
				{

					cout << "incorrect!! try again ,you have ("<<count_chance<<") chance\n";
					count_chance--;
					string p; cin >> p;
					passward = p;
					if (count_chance >= 1) {
						continue;
					}
					else
					{
						return false;
					}
				}
			}
			i++;
		}
		if (ch == 1)
		{
			cout << "found\n";
			return true;
		}
		else
		{
			cout << "not found\n";
			return false;
		}
	}

	void All_users()
	{
		/////
		_clear_();
		/////
	
		for (int i = 0; i < v_d.size(); i++)
		{
			cout << "ID : " << v_d[i].ID<<"\n";
			cout << "Name : " << v_d[i].Name << "\n";
			
		}
	}

	void all_user_without_curr()
	{
		/////
		_clear_();
		/////

		for (int i = 0; i < v_d.size(); i++)
		{
			if (id_curr != v_d[i].ID) {
				cout << "ID : " << v_d[i].ID << "\n";
				cout << "Name : " << v_d[i].Name << "\n";
			}

		}
	}

	bool check_users()
	{
		/////
		_clear_();
		/////

		if (v_d.size() == 1)
		{
			return false;
		}
		return true;
	}
	bool check_users_isfount(int to)
	{
		/////
		_clear_();
		/////

		bool check_to_user = false;
		for (int i = 0; i < v_d.size(); i++)
		{
			if (to == v_d[i].ID && to != id_curr)
			{
				check_to_user = true;
				break;
			}
		}
		if (check_to_user)
			return true;
		else
			return false;
	}

	bool check_email(Data ob_d)
	{
		_clear_();

		for (int i = 0; i < v_d.size(); i++)
		{
			if (ob_d.Email == v_d[i].Email)
			{
				cout << "this email used before\n";
				return true;
			}
		}
		return false;

	}

	bool check_email_in(string s)
	{
		_clear_();

		for (int i = 0; i < v_d.size(); i++)
		{
			if (s == v_d[i].Email)
			{
				return true;
			}
		}
		return false;
	}

};


class Questions_Answer :  public Acount 
{
	int count_qs = 1;
public:
	fstream f_QS;
	fstream f_AN;
	QS oq,qou2;
	QS_to_one_user qou,qou1;
	File_data uu;
	void set_question(int to, string qs_s)
	{
		/////
		_clear_();
		/////
		

				if (v_q.size()) {
					count_qs = v_q[v_q.size() - 1].counter_qs + 1;
					//cout << "f";
				}
				else
				{
					count_qs = 1; //cout << "z";
				}

				f_QS.open("Question.txt", ios::out|ios::app);
				oq.counter_qs = count_qs;
				oq.to = to;
				oq.qa = qs_s;
				oq.from = id_curr;
				f_QS << oq.counter_qs << "\n";
				f_QS << oq.from << "\n";
				f_QS << oq.to << "\n";
				f_QS << oq.qa << "\n";
				v_q.push_back(oq);
				f_QS.close();
				
	}

	/// ///////////////////////////
	
	bool qs_to_one_user()
	{
		/////
		_clear_();
		/////

		vector<QS>v__u;
		for (int i = 0; i < v_q.size(); i++)
		{
			if (v_q[i].to == id_curr)
			{
				qou2.counter_qs = v_q[i].counter_qs;
				qou2.qa = v_q[i].qa;
				qou2.from = v_q[i].from;
				qou2.to = v_q[i].to;
				v__u.push_back(qou2);
			}
		}
		if (v__u.size() == 0)
		{
			return false;
		}
		else {
			for (int i = 0; i < v__u.size(); i++)
			{
				cout << "question ID : " << v__u[i].counter_qs << "\n";
				cout << "from (" << v__u[i].from << ") to (" << v__u[i].to << ")\n";
				cout << "question : " << v__u[i].qa<< "\n";
				bool ch = false;
				for (int j = 0; j < v_a.size(); j++)
				{
					if (v__u[i].counter_qs == v_a[j].id_qs)
					{
						cout << "answer is : " << v_a[j].qs << "\n";
						ch = true;
					}
				}
				if (ch == false)
				{
					cout << "NO Answer\n";
				}

			}
			return true;
		}
	}

	void set_answer(int id_q,string s)
	{
		/////
		_clear_();
		/////

		qou1.id_qs = id_q;
		qou1.qs = s;
		f_AN.open("Answers.txt", ios::out | ios::app);
		f_AN << qou1.id_qs << "\n";
		f_AN << qou1.qs << "\n";
		f_AN.close();
		v_a.push_back(qou1);


	}

	bool check_answer(int id_q)
	{
		/////
		_clear_();
		/////
		bool ch = 0;
		for (int i = 0; i < v_q.size(); i++)
		{
			if (v_q[i].counter_qs == id_q&& id_curr==v_q[i].to)
			{
				ch = 1;
				break;
			}
		}
		if (ch == 1) {
			for (int i = 0; i < v_a.size(); i++)
			{
				if (v_a[i].id_qs == id_q) {
					cout << "this question already responed\n";
					return true;
				}
			}
			return false;
		}
		else
		{
			cout << "you enterd invalid question id\n";
			return true;
		}

	}
	


	bool qs_from_one_user()
	{
		/////
		_clear_();
		/////

		vector<QS>v__u;
		for (int i = 0; i < v_q.size(); i++)
		{
			if (v_q[i].from == id_curr)
			{
				qou2.counter_qs = v_q[i].counter_qs;
				qou2.qa = v_q[i].qa;
				qou2.from = v_q[i].from;
				qou2.to = v_q[i].to;
				v__u.push_back(qou2);
			}
		}
		if (v__u.size() == 0)
		{
			return false;
		}
		else {
			for (int i = 0; i < v__u.size(); i++)
			{

				cout << "question ID : " << v__u[i].counter_qs << "\n";
				cout << "from (" << v__u[i].from << ") to (" << v__u[i].to << ")\n";
				cout << "question : " << v__u[i].qa<< "\n";
				bool ch = false;
				for (int j = 0; j < v_a.size(); j++)
				{
					if (v__u[i].counter_qs == v_a[j].id_qs)
					{
						cout << "answer is : " << v_a[j].qs << "\n";
						ch = true;
					}
				}
				if (ch == false)
				{
					cout << "NO Answer\n";
				}
			}
			return true;
		}
	}

	void delete_question(int n)
	{
		/////
		_clear_();
		/////
		bool ch_id_q = 0;
		for (int i = 0; i < v_q.size(); i++)
		{
			if (n == v_q[i].counter_qs && id_curr==v_q[i].from)
			{
				ch_id_q = 1;
				break;
			}
		}
		if (ch_id_q == 0)
		{
			cout << "you entered invalid id question\n";
			return;
		}

		f_AN.open("Answers.txt", ios::out);
		int iii = 0; bool c = false;
		for (int i = 0; i < v_a.size(); i++)
		{
			if (n == v_a[i].id_qs)
			{
				c = true;
				iii = i;
				break;
			}
		}
		if (v_a.size() != 0&&c==true) {
			v_a.erase(v_a.begin() + iii);
		}
		for (int i = 0; i < v_a.size(); i++)
		{
			
				f_AN << v_a[i].id_qs << "\n";
				f_AN << v_a[i].qs << "\n";
			
		}
		f_AN.close();

		f_QS.open("question.txt", ios::out);
		int ii = 0;
		for (int i = 0; i < v_q.size(); i++)
		{
			if (n == v_q[i].counter_qs)
			{
				ii = i;
				break;
			}
		}
		if (v_q.size() != 0) {
			v_q.erase(v_q.begin() + ii);
		}

		for (int i = 0; i < v_q.size(); i++)
		{
			
				f_QS << v_q[i].counter_qs << "\n";
				f_QS << v_q[i].from << "\n";
				f_QS << v_q[i].to << "\n";
				f_QS << v_q[i].qa << "\n";
			
		}
		f_QS.close();

	}

	void feed()
	{
		/////
	_clear_();
		/////

		for (int i = 0; i < v_q.size(); i++)
		{
			cout << "Question ID : " << v_q[i].counter_qs << "\n";
			cout << "from (" << v_q[i].from << ") to (" << v_q[i].to << ")\n";
			cout << "Question : " << v_q[i].qa << "\n";
			bool ch = false;

			for (int j = 0; j < v_a.size(); j++)
			{
				if (v_q[i].counter_qs == v_a[j].id_qs)
				{
					cout << "Answer : " << v_a[j].qs << "\n"; cout << "\n"; ch = true;
				}
			}
			if (ch == false)
			{
				cout << "No Answer\n"; cout << "\n";
			}
		}
	}

	

};

void sign_in_up_menu()
{
	cout << "-enter 1 to sign up\n-enter 2 to sign in\n";
}

void menu()
{
	cout << "\nEnter :\n   -1 to view questions forwarded to you\n";
	cout << "   -2 to view questions you asked\n";
	cout << "   -3 to ask a question\n";
	cout << "   -4 to responed to a qestion\n";
	cout << "   -5 to list all the users in the systrem\n";
	cout << "   -6 to delete a question\n";
	cout << "   -7 to see all questions and answers\n";
	cout << "   -8 to log out of your account\n";
	cout << "   -0 to exit\n";
}

int main()
{
	Data ob_d;
	File_data ob,ob1; //class 
	Acount obb; //class
	Questions_Answer oq,oq1,o_p_q,o_p_a,fee; //class
	
	sign_in_up_menu();

	int exit = 1;
	while (exit != 0)
	{
	
		int num; cin >> num;
		if (num == 1)
		{

		
			if (!obb.sign_up(ob_d))
			{
			
				sign_in_up_menu();
				continue;
			}
	
			
		}
		else if (num == 2)
		{
			if (!obb.sign_in())
			{
				sign_in_up_menu();
				continue;
			}
		
		}
		else
		{
			cout << "Please enter (1 -> sign up)  or (2 -> sign in) \n";
			continue;
		}
		int number=1; 
		while (number != 0)
		{

			menu();
			 cin >> number;
			if (number == 1)
			{
				system("cls");

				if (!oq1.qs_to_one_user())
				{
					cout << "you have no question\n";
				}
			
			}
			else if (number == 2)
			{
		
				system("cls");

				if (!oq1.qs_from_one_user())
				{
					cout << "you didn't ask any question\n";
				}
			
			}
			else if (number == 3)
			{
				system("cls");

				if (!obb.check_users())
				{
					cout << "there is no users in the system\n";
				}
				else {
					
					obb.all_user_without_curr();
					cout << "enter id user you want ask\n";
					int to; cin >> to;

					if (obb.check_users_isfount(to)) 
					{
						cout << "write your question\n";
						string qs_s; cin.ignore();
						getline(cin, qs_s);
						oq.set_question(to, qs_s);
					}
					else
					{
						cout << "this user is not found\n";
					}
				}
			
				
			}
			else if (number == 4)
			{
				system("cls");
	
					if (!oq1.qs_to_one_user())
					{
						cout << "you have no question\n";
					}
					else {
						cout << "enter the id of question you want responed :"; int id_q; cin >> id_q; cout << "\n";
						if (!oq1.check_answer(id_q))
						{
							cout << "enter your answer\n"; string s; cin.ignore(); getline(cin, s);
							oq1.set_answer(id_q, s);
						}
					}
		

		
			}
			else if (number == 5)
			{
				system("cls");
				obb.All_users();

			}
			else if (number == 6)
			{
				system("cls");

				if (oq1.qs_from_one_user())
				{
					cout << "enter the id question you want delete\n";
					int n; cin >> n;
					oq1.delete_question(n);

				}
				else
				{
					cout << "you didn't ask any question\n";
				}

		

			}
			else if (number == 7)
			{
				system("cls");
				fee.feed();
			}
			else if (number == 8)
			{
			

				system("cls");
				sign_in_up_menu();
			
				break;
			}
			else if (number == 0)
			{
				return 0;
			}
			else 
			{
				system("cls");
				cout << "Please enter number from list\n";
			}
	    }
		exit = number;
	}


}
