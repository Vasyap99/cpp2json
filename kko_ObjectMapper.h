#pragma once

#include <ostream>
#include <iostream>


#include <string>
#include <vector>


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using namespace std;

namespace kko{
	using namespace std;
	class ObjectMapper{
	public:
		void writeValue(basic_iostream<char> &v, void*o,string dsc,vector<string>names){
			v<<"{";
			int ofs=0;
			int i;
			for(int j=0;j<dsc.length();j++){
				if(j>0) v<<',';
				switch(dsc[j]){
					case 'i':
						i=*((int*)(o+ofs));
						v << string(1,'"') << names[j] << '"' << ':' << i;
						ofs+=sizeof(int);						
						break;
					case 's':
						string &s=*((string*)(o+ofs));
						v << string(1,'"') << names[j] << '"' << ':' << '"' << s << '"';
						ofs+=sizeof(string);
						break;						
				}
			}
			v<<"}";			
		}
		void skipTill(basic_iostream<char> &v,char c){
			char b;
			while(true){
				b=v.peek();
				if(b==c) return;
				v.get();
			}
		}
		void skipSpaces(basic_iostream<char> &v){
			char b;
			while(true){
				b=v.peek();
				if(b!=' ' && b!=9 && b!=13 && b!=10) return;
				v.get();
			}
		}
		char readChar(basic_iostream<char> &v){
			return v.get();
		}
		int readInt(basic_iostream<char> &v){
			string s;
			char b;
			while(true){
				b=v.peek();
				if(b!='0' && b!='1' && b!='2' && b!='3' && b!='4' && b!='5' && b!='6' && b!='7' && b!='8' && b!='9' && b!='-')
					return stoi(s);					
				s+=v.get();
			}
			return stoi(s);
		}
		string readQuoted(basic_iostream<char> &v){
			char b;
			string s;
			v>>b;
			if(b=='"') while(true){
				v>>b;
				if(b=='"') return s;
				s+=b;
			}else if(b==39) while(true){ //'
				v>>b;
				if(b==39) return s;
				s+=b;
			}
			return s;
		}		
		char cur(basic_iostream<char> &v){
			return v.peek();
		}
		template<typename T>		
		T readValue(basic_iostream<char> &v,string dsc){
			T t;
			void*ofs=&t;
			//
			int i;
			skipTill(v,'{');
			readChar(v);
			for(int j=0;j<dsc.length();j++){
				readQuoted(v);
				skipTill(v,':');
				readChar(v); //:
				skipSpaces(v);
				switch(dsc[j]){
					case 'i':
						i=readInt(v);		cout<<i<<":";
						*((int*)ofs)=i;
						ofs+=sizeof(int);						
						break;
					case 's':
						string s=readQuoted(v);		cout<<s<<"::";
						*((string*)ofs)=s;
						ofs+=sizeof(string);
						break;						
				}
				skipSpaces(v);
				readChar(v); 
				skipSpaces(v);
				if(cur(v)=='}'){
					readChar(v); //}
					break;
				}
			}
			//
			return t;
		}	
	};
}
