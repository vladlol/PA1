#include "version.h"
#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;
string *parseUrl(string);
bool validateUrl(string);
static double version = 1.2;
int main()
{
// this comment servers no purpose	
	displayVersion(version);
    string url;
// get url from user
    cout << "Enter url: ";
    cin >> url;
// if url is valid then print out url components
    if((validateUrl(url)))
    {
        string * parsedUrl = new string[5];
        parsedUrl = parseUrl(url);
        cout << "Protocol: 	" << parsedUrl[0] << endl;
        cout << "Domain: 	" << parsedUrl[1] << endl;
        if(parsedUrl[2] != "")
            cout << "Port:		" << parsedUrl[2] << endl;

        cout << "File path:	" << parsedUrl[3] << endl;
        if(parsedUrl[4] != "")
            cout << "Parameters:	" << parsedUrl[4] << endl;
    }




    return 0;
}
// parse url into components
string * parseUrl(string url)
{

    string * parsedUrl = new string[5];
// find protocol
    parsedUrl[0] = url.substr(0, url.find(':'));
    url.erase(0, parsedUrl[0].length()+3);
// find Domain
    if(url.find(':') < 100000)
    {
        parsedUrl[1] = url.substr(0, url.find(':'));
        url.erase(0, parsedUrl[1].length()+1);
    }
    else
    {
        parsedUrl[1] = url.substr(0, url.find('/'));
        url.erase(0, parsedUrl[1].length());
    }

// find port
    if(url.length() > 0)
    {
        char check = url.at(0);

        if(isdigit(check))
        {
            parsedUrl[2] = url.substr(0, url.find('/'));
            url.erase(0, parsedUrl[2].length());
        }
        else
        {
            parsedUrl[2] = "";
        }
    }
    else
    {
        parsedUrl[2] = "";
    }
// find file path
    if(url.length() > 0)
    {
        parsedUrl[3] = url.substr(0, url.find('?'));
        url.erase(0, parsedUrl[3].length()+1);
    }
    else
    {
        parsedUrl[3] = "";
    }
// find parameters
    if(url.length() > 0)
    {
        parsedUrl[4] = url;
    }
    else
    {
        parsedUrl[4] = "";
    }



    return parsedUrl;

}
// check url components
bool validateUrl(string url)
{

    string * parsedUrl = parseUrl(url);
    bool valid = true;
    string word = "";
// get last part of domain
    for (auto x : parsedUrl[1])
    {
        if (x == '.')
        {
            word = "";
        }
        else
        {
            word = word + x;
        }
    }
// check protocol
    if(parsedUrl[0] != "http" && parsedUrl[0] != "https" && parsedUrl[0] != "ftp" && parsedUrl[0] != "ftps")
    {
        cout << "Invalid URL with following erroneous components:" << endl;
        cout << "Protocol:   	" << parsedUrl[0] << " is not a valid protocol." << endl;
        valid = false;
    }
    if(word != "com" && word != "net" && word != "edu" && word != "biz" && word != "gov")
    {
        if(!valid)
        {

            cout << "Domain:	    " << word << " is an invalid domain name." << endl;
        }
        else
        {
            cout << "Invalid URL with following erroneous components:" << endl;
            cout << "Domain:	    " << word << " is an invalid domain name." << endl;
            valid = false;
        }

    }
 // check port number
    if(parsedUrl[2] != "")
    {
        if(stoi(parsedUrl[2]) < 0 || stoi(parsedUrl[2]) > 65535)
        {
            if(!valid)
            {
                cout << "Port:		port number must be between 1 and 65535" << endl;
            }
            else
            {
                cout << "Invalid URL with following erroneous components:" << endl;
                cout << "Port:		port number must be between 1 and 65535" << endl;
                valid = false;
            }
        }
    }
// get ending of file path
    for (auto x : parsedUrl[3])
    {
        if (x == '.')
        {
            word = "";
        }
        else
        {
            word = word + x;
        }
    }
// check file path
    try
    {
        cout << "parsedURl: " << parsedUrl[3] << endl;
        cout << "word: " << word << endl;
        if(parsedUrl[3].at(0) != '/' || (word != "html" && word != "htm"))
        {
            if(!valid)
            {
                cout << "File path:	" << word << " is an invalid file path." << endl;
            }
            else
            {
                cout << "Invalid URL with following erroneous components:" << endl;
                cout << "File:	" << parsedUrl[3] << " is an invalid file path." << endl;
                valid = false;
            }
        }
    }
    catch(exception e)
    {
        if(!valid)
        {
            cout << "File path:	" << word << " is an invalid file path." << endl;
        }
        else
        {
            cout << "Invalid URL with following erroneous components:" << endl;
            cout << "File:	" << parsedUrl[3] << " is an invalid file path." << endl;
            valid = false;
        }
    }


    return valid;
}

