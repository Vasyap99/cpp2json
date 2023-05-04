#include <iostream>

#include <string>
#include <vector>


#include <sstream>
#include <fstream>

#include "kko_ObjectMapper.h"

class test{
public:
	string name;
	string login;
	string passw;
	test(){}
	test(string name,string login, string passw)
		:name(name),login(login), passw(passw)
	{}
};

int test1() {
	test t("user1","login1","pass1");
	
	kko::ObjectMapper om;
	stringstream json;
	om.writeValue(json, &t,"sss",{"name","login","pasw"});
	
	cout << json.str() << endl;
	
	fstream f("t.dat",std::ios::app);
	om.writeValue(f, &t,"sss",{"name","login","pasw"});
	
	//
	cout << endl;	
	stringstream json1("{\"name\":\"user1\",\"login\":\"login1\",\"pasw\":\"pass1\"}{\"name\":\"user2\",\"login\":\"login2\",\"pasw\":\"pass2\"}");

	while(!json1.eof()){
		cout << ">>>reading value:"<<endl;			
		test t2 = om.readValue<test>(json1,"sss");
		cout << endl;
	
		cout << t2.name << endl;
		cout << t2.login << endl;	
		cout << t2.passw << endl;
	}
	
	return 0;
}


class User {
public:
    string _name;
    string _login;
    string _pass;
    User(string n,string l,string p){_name=n;_login=l,_pass=p;}
    User(){}
};
class Message {
public:
    string _text;
    string _sender;
    string _receiver;
    Message(string t,string s,string r){_text=t;_sender=s;_receiver=r;}
    Message(){}
};

int main(int argc, char** argv) {
	kko::ObjectMapper om;

	{

	fstream f("Users.dat",std::ios::in);

	cout << "-----------reading Users:"<<endl;	
	
	while(f.peek() && !f.eof()){
		cout << ">>>reading value:"<<endl;			
		User t2 = om.readValue<User>(f,"sss");
		cout << endl;
	
		cout << t2._name << endl;
		cout << t2._login << endl;	
		cout << t2._pass << endl;
	}

	fstream m("Messages.dat",std::ios::in);

	cout << "-----------reading Messages:"<<endl;	
	
	while(m.peek() && !m.eof()){
		cout << ">>>reading value:"<<endl;			
		Message t3 = om.readValue<Message>(m,"sss");
		cout << endl;
	
		cout << t3._text << endl;
		cout << t3._sender << endl;	
		cout << t3._receiver << endl;
	}

	}

	User t1("user1","login1","pasw1");
	User t2("user2","login2","pasw2");
	fstream f("Users.dat",std::ios::app);
	om.writeValue(f, &t1,"sss",{"_name","_login","_pass"});
	om.writeValue(f, &t2,"sss",{"_name","_login","_pass"});

	fstream m("Messages.dat",std::ios::app);
	Message t3("text1","sender1","receiver1");
	Message t4("text2","sender2","receiver2");
	om.writeValue(m, &t3,"sss",{"_text","_sender","_receiver"});
	om.writeValue(m, &t4,"sss",{"_text","_sender","_receiver"});

	return 0;
}
