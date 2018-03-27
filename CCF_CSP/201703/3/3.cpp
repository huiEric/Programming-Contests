#include <bits/stdc++.h>

using namespace std;

void process_emphasis(string &line, int &p, bool top);
void process_link(string &line, int &p);

void process_emphasis(string &line, int &p, bool top) {
	cout << "<em>";
	p++;
	while(p<line.size()) {
		if(line[p]=='_') {		
			p++;
			cout << "</em>";
			return;
		}
		if(line[p]=='[' && top) {
			process_link(line,p);
		}
		cout << line[p];
		p++;
	}	
}

void process_link(string &line, int &p) {
	string text,link;
	int d=1;
	p++;
	while(d!=0) {
		if(line[p]=='[')
			d++;
		if(line[p]==']')
			d--;		
		if(d!=0)
			text.push_back(line[p]);
		p++;
	}
	p+=1;
	while(line[p]!=')') {
		link.push_back(line[p]);
		p++;
	}
	p++;
	cout << "<a href=\"" << link << "\">";
	int p1=0;
	while(p1<text.size()) {
		if(text[p1]=='_')
			process_emphasis(text,p1,false);
		cout << text[p1];
		p1++;
	}
	cout << "</a>";
}

int main() {
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("in.txt","r",stdin);
#endif
	string line,next_line;
	while(getline(cin,line)) {
		if(line.size()==0)
			continue;	
		if(line[0]=='#') {
			int depth=0;
			int p=0;
			while(line[p]=='#') {
				depth++;
				line.erase(p,1);
			}					
			while(line[p]==' ') {				
				line.erase(p,1);
			}
			string tag1,tag2;
			if(depth==1) {				
				tag1="<h1>";
				tag2="</h1>";
			}
			else if(depth==2) {
				tag1="<h2>";
				tag2="</h2>";
			}
			else if(depth==3) {
				tag1="<h3>";
				tag2="</h3>";
			}
			else if(depth==4) {
				tag1="<h4>";
				tag2="</h4>";
			}
			else if(depth==5) {
				tag1="<h5>";
				tag2="</h5>";
			}
			else if(depth==6) {
				tag1="<h6>";
				tag2="</h6>";
			}
			cout << tag1;
			while(p<line.size()) {
				if(line[p]=='_')
					process_emphasis(line,p,true);
				else if(line[p]=='[')
					process_link(line,p);
				else {
					cout << line[p];
					p++;
				}		
			}	
			cout << tag2 << endl;	
		}
		else if(line[0]=='*') {
			cout << "<ul>" << endl;
			int p=0;
			line.erase(p,1);				
			while(line[p]==' ') {				
				line.erase(p,1);
			}
					cout << "<li>";
					while(p<line.size()) {
						if(line[p]=='_')
							process_emphasis(line,p,true);
						else if(line[p]=='[')
							process_link(line,p);
						else {
							cout << line[p];
							p++;
						}		
					}	
					cout << "</li>" << endl;
			while(getline(cin,line)) {
				if(line.size()==0) {					
					break;
				}
				else {					
					int p=0;
					line.erase(p,1);				
					while(line[p]==' ') {				
						line.erase(p,1);
					}
					cout << "<li>";
					while(p<line.size()) {
						if(line[p]=='_')
							process_emphasis(line,p,true);
						else if(line[p]=='[')
							process_link(line,p);
						else {
							cout << line[p];
							p++;
						}		
					}	
					cout << "</li>" << endl;
				}
			}
			cout << "</ul>" << endl;
		}
		else {
			cout << "<p>";
			int p=0;
			while(p<line.size()) {
				if(line[p]=='_')
					process_emphasis(line,p,true);
				else if(line[p]=='[')
					process_link(line,p);
				else {
					cout << line[p];
					p++;
				}		
			}	
			while(getline(cin,line)) {
				if(line.size()==0) {					
					break;
				}
				else {					
					cout << endl;
					int p=0;
					while(p<line.size()) {
						if(line[p]=='_')
							process_emphasis(line,p,true);
						else if(line[p]=='[')
							process_link(line,p);
						else {
							cout << line[p];
							p++;
						}		
					}	
				}
			}
			cout << "</p>" << endl;	
		}
	}
	return 0;
}