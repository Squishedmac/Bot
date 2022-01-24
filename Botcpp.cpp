#include<curl/curl.h>
#include<string>
#include<iostream>
#include <sstream>
#include<vector>


using namespace std;


vector<string> stringream(string &readBuffer, string check, int *pos)
{
    *pos = 0;
    int i = 0;
    int flag = 100;
    vector<string> c;
    istringstream iss(readBuffer);
    do
    {
        string word;

        iss >> word;
        if (word == check)
        {
            *pos = i;
            flag = 0;
        }
        c.push_back(word);
        flag++;
        i++;
        if (flag == 6)
            return c;
        

    } while (iss);
    return c;
}



static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

void main()
{
    string readBuffer;
    string MainPageurl = "https://eduserver.nitc.ac.in/login/index.php";
   
    string MPMC = "https://eduserver.nitc.ac.in/mod/attendance/view.php?id=90700";
    string EMFTA = "https://eduserver.nitc.ac.in/mod/attendance/view.php?id=89332";
    string EMFTB = "https://eduserver.nitc.ac.in/course/view.php?id=2364";
    string CTSB = "https://eduserver.nitc.ac.in/mod/attendance/view.php?id=90511";
    string MPMClab = "https://eduserver.nitc.ac.in/mod/attendance/view.php?id=91761";
    string test = "https://eduserver.nitc.ac.in/mod/attendance/view.php?id=97582";

    
    auto curl = curl_easy_init();
    

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64)");
        curl_easy_setopt(curl, CURLOPT_AUTOREFERER, 1);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, TRUE);
        curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "");
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");

        

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        curl_easy_setopt(curl, CURLOPT_URL, MainPageurl.c_str());

        curl_easy_perform(curl);
        

        
        vector<string> c,b,a,d;
        int pos;
        
        //using stringstream to split it into words
        string check = "name=\"logintoken\"" ;
        string check2 = "M.cfg";
        string check4 = "type=\"radio\"";
        string check3 = "attendance</a></td>";
        string token,sesskey;
        c = stringream(readBuffer,check, &pos);
        token = c[pos + 1];
        
        

       
        /*for (int i=0;i<c.size(); i++)
        {
            /// <summary>
            /// here we find the login token and session key required for the get and  post requests its a sentance so we iterate letter by letter as the size of these kets do not change
            /// </summary>
            if (c[i] == check)
                token = c[i + 1];
            
            else if (c[i] == check2)
                sesskey=c[i+2];
            
        }*/

        

        
        string finaltoken,Sesskey,id,ID;



        for (int i = token.size() - 3; i > 6; i--)
        {
            finaltoken = token[i]+finaltoken;
        }

        /// <summary>
        /// iterate the sentance to obtain the value required
        /// </summary>

        

        

        string adds = "logintoken="+finaltoken+"&username=b201071me&password=Jaikrishnan1*";
        readBuffer = "";
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, adds.c_str());
        curl_easy_perform(curl);
        
        readBuffer = "";

        curl_easy_setopt(curl, CURLOPT_URL, test.c_str());
        curl_easy_perform(curl);
        
        //we now find the nested link for the submit button
        
        string furl,finalURL,sessid;
        
       
        a = stringream(readBuffer,check3,&pos);
        furl = a[pos - 1];
        
        /*for (int i = 100; i < a.size(); i++)
        {
            if (a[i] == check3)
                furl = a[i - 1];
        }*/
        cout << furl;
        for (int i = 6; i <furl.size()-8; i++)
        {
            finalURL = finalURL + furl[i];
            
        }
        for (int i = 66; i < finalURL.size()-23; i++)
        {
            sessid = sessid + finalURL[i];
        }
        
        readBuffer = "";
        curl_easy_setopt(curl, CURLOPT_URL, finalURL.c_str());
        curl_easy_perform(curl);


        //we get the sessid for the submit form to post via the url
       
        b = stringream(readBuffer,check4,&pos);
        id = b[pos + 4];
        
        /*for (int i = 100; i < b.size(); i++)
        {
            if (b[i] == check4)
                id = b[i + 4];
        }*/

        for (int i = 14; i < id.size() - 1; i++)
        {
            ID = ID + id[i];
        }
        //This id is used to realise how to post the status, beacuse present doesnt have the same code across
        for (int i = 84; i < finalURL.size(); i++)
        {
            Sesskey = Sesskey + finalURL[i];
        }




        string form = "sessid="+sessid + "&"+"sesskey=" + Sesskey + "&"+"sesskey=" + Sesskey + "&_qf__mod_attendance_student_attendance_form=1&mform_isexpanded_id_session=1&status=" + ID + "&submitbutton=Save+changes";
        
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS,form.c_str());
        ///readBuffer = "";
        curl_easy_perform(curl);

        curl_easy_cleanup(curl);
    }
    cout<< readBuffer;
}