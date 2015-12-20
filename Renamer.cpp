/*	Developed by Sudarshan Basumatary, sbasumatary34@gmail.com, two3eight@github
**	This program takes a fileName and renames the whole batch
**	format of renaming: title episode year quality extras extension.
**/

#include <bits/stdc++.h>

using namespace std;

string fileName, newName, title, preEp, remPhrase, insPhrase, episode, quality, year, extension, extras, buffer;
vector <string> exts, words, titleWords, remWords;
map <string, bool> extMap, remWordMap;
char delim;

/* 	SECTION 0
**	Utility functions
**	These functions provide utility
*/

void explode(vector <string> &space, const string &fileName) {
	string valid;
	int len = fileName.length();
	for(int i = 0; i < len; i++) {
		if(fileName[i] != delim)
			valid += fileName[i];
		else {
			if(valid.length())
				space.push_back(valid);
			valid = "";
		}
	}
	if(valid.length())
		space.push_back(valid);
}

bool hasAlNum(string str) {
	for(int i = 0; i < str.length(); i++)
		if(isalnum(str[i]))
			return true;
	return false;
}

/* 	SECTION 1
*  	Initialization functions
*	These functions initialize a given vector or map
*/

void initExtVector() {
	exts.push_back("mp4");
	exts.push_back("flv");
	exts.push_back("avi");
	exts.push_back("mkv");
	exts.push_back("wmv");
}

void initMap(map <string, bool> &mapper, vector <string> &mapIt) {
	for(int i = 0; i < mapIt.size(); i++) {
		transform(mapIt[i].begin(), mapIt[i].end(), mapIt[i].begin(), ::tolower);
		mapper[mapIt[i]] = true;
	}
}

/*	SECTION 2
*	String Preliminary Processing Functions
*	These functions remove unnecessary words or characters
*/

void trim(string &str) {
	int i = 0, strl = str.length();
	while(i < strl && str[i] == ' ') i++;
	str.erase(str.begin(), str.begin() + i);
	i = str.length() - 1;
	while(i >= 0 && str[i] == ' ') i--;
	str.erase(str.begin() + i + 1, str.end());
}

void removeWords() {
	string remTmp;
	for(int i = 0; i < words.size(); i++) {
		remTmp = words[i];
		transform(remTmp.begin(), remTmp.end(), remTmp.begin(), ::tolower);
		if(remWordMap[remTmp] || !hasAlNum(remTmp)) {
			words.erase(words.begin() + i);
			i--;
		}
	}
}

void removeExtraNos() {
	int wordLen;
	bool onlyDigit;
	for(int i = 0; i < words.size(); i++) {
		onlyDigit = true;
		wordLen = words[i].length();
		for(int j = 0; j < wordLen; j++)
			if(!isdigit(words[i][j])) {
				onlyDigit = false;
				break;
			}
		if(onlyDigit) {
			words.erase(words.begin() + i);
			i--;
		}
	}
}

void removeEpPrefix () {
	int preEpLen = preEp.length();
	for(int i = 0; i < words.size() && preEpLen; i++)
		if(words[i].length() > preEpLen && words[i].substr(0, preEpLen) == preEp) {
			words[i].erase(words[i].begin(), words[i].begin() + preEpLen);
			break;
		}
}

/*	SECTION 3
*	String processing functions
*	These functions process the given string and extracts relevant parts
*/

string getEpisode() {
	int slen, epNo;
	bool valid;
	string ret;
	for(int i = 0; i < words.size(); i++) {
		slen = words[i].length();
		epNo = 0;
		valid = true;
		for(int j = 0; j < slen; j++) {
			if(!isdigit(words[i][j])) {
				valid = false;
				break;
			}
			epNo = epNo * 10 + words[i][j] - '0';
		}
		if(valid && epNo < 1900) { //for removing conflicts between year number and episode number
			ret = " " + words[i];
			words.erase(words.begin() + i);
			return ret;
		}
	}
	return "";
}

string getQuality() {
	int slen;
	string ret;
	bool valid;
	for(int i = 0; i < words.size(); i++) {
		slen = words[i].length();
		valid = true;
		for(int j = 0; j < slen - 1; j++)
			if(!isdigit(words[i][j])) {
				valid = false;
				break;
			}
		if(valid && tolower(words[i][slen - 1]) == 'p') {
			ret = " @" + words[i].substr(0, slen - 1) + 'p';
			words.erase(words.begin() + i);
			return ret;
		}
	}
	return "";
}

string getYear() {
	int slen, year;
	bool valid;
	string ret;
	for(int i = 0; i < words.size(); i++) {
		slen = words[i].length();
		year = 0;
		valid = true;
		for(int j = 0; j < slen; j++) {
			if(!isdigit(words[i][j])) {
				valid = false;
				break;
			}
			year = year * 10 + words[i][j] - '0';
		}
		if(valid && year > 1900 && words[i].length() == 4) { //for removing conflicts between year and episode number
			ret = " (" + words[i] + ")";
			words.erase(words.begin() + i);
			return ret;
		}
	}
	return "";
}

string getExtras() {
	string ret = " - ", lowerTitleTest;
	for(int i = 0; i < words.size(); i++) {
		ret += words[i] + " ";
	}
	ret.erase(ret.end() - 1);
	if(ret.length() < 3)
		return "";
	return ret;
}

/*	SECTION 4
*	Main initiation functions
*	These functions initiate the renaming process and calls the relevant functions
*/

void renameFile(const string &fileName) {
	int len = fileName.length();
	explode(words, fileName);
	removeWords();
	removeEpPrefix();
	episode = getEpisode();
	quality = getQuality();
	year = getYear();
	removeExtraNos();
	extras = getExtras() + insPhrase; //this should be done last as this extracts all the words that are left
	newName = title + episode + year + quality + extras + "." + extension;
	if(episode == "")
		cout << fileName << " >> Parse Failed!" << endl;
	else {
		buffer = fileName + "." + extension;
		//cout << buffer << "  -->>  " << newName <<endl;
		if(rename(buffer.c_str(), newName.c_str()))
			cout << "Rename Fail >> " << fileName << endl;
	}
	words.clear();
}

void initiate() {
	char ch;
	int extDot;
	delim = ' ';
	locale loc;
	while((ch = getchar()) > 10) //get title
		title += ch;
	while((ch = getchar()) > 10) //get prefix before episode number
		preEp += ch;
	if(preEp == "ECHO is off.")
		preEp = "";
	while((ch = getchar()) > 10) //get phrase to remove
		remPhrase += ch;
	if(remPhrase == "ECHO is off.")
		remPhrase = "";
	while((ch = getchar()) > 10) //get phrase to insert at end [CASE SENSITIVE]
		insPhrase += ch;
	if(insPhrase == "ECHO is off.")
		insPhrase = "";
	if(insPhrase.length())
		insPhrase.insert(insPhrase.begin(), ' ');
	trim(title);
	trim(preEp);
	trim(remPhrase);
	trim(insPhrase);
	explode(titleWords, title);
	explode(remWords, remPhrase);
	initExtVector();
	initMap(extMap, exts);
	initMap(remWordMap, titleWords);
	initMap(remWordMap, remWords);
	ifstream fileList;
	fileList.open("filelist.txt");
	while(getline(fileList, fileName)) {
		extDot = fileName.rfind('.');
		if(extDot != -1) {
			extension = fileName.substr(extDot + 1);
			fileName = fileName.substr(0, extDot);
		}
		transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
		if(extMap[extension]) 
			renameFile(fileName);
	}
	fileList.close();
}

int main () {
	initiate();
	return 0;
}