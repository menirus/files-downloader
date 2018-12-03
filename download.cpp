#include<iostream>
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<curl/curl.h>

using namespace std;

// ToDo: Add a make file
// List down all the dependencies
// Have a todo list of features

void* download(void* ptr) {
    char* url = (char *)ptr;
    // START THE DOWNLOAD HERE
    CURL *curl;
    FILE *fp;
    CURLcode res;
    char outfilename[FILENAME_MAX] = "download.pdf";
    curl = curl_easy_init();                                                                                                                                                                                                                                                           
    if (curl)
    {   
        fp = fopen(outfilename,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }  
    return NULL;
}

int main(int argc, char** argv) {
    pthread_t tid;
    string url;

    if(argc == 1) {
        cin>>url;
    } else if(argc == 2) { // making it work for only one URL first
        url = string(argv[1]);
    }
    cout<<url<<endl;
    void * url_ptr = (void *)static_cast<const void *>(url.c_str());
    pthread_create(&tid, NULL, download, url_ptr);
    void *result;
    pthread_join(tid, &result);
    return 0;
}