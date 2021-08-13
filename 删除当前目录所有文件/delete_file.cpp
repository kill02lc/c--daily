#include <stdio.h>
#include <direct.h>
#include <iostream>
#include <io.h>
#include <string>
#include <vector>
using namespace std;

#define MAX_PATH 80

void getFiles(string path, vector<string>& files)
{
    long   hFile = 0;
    struct _finddata_t fileinfo;
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
    {
        do
        {
            if ((fileinfo.attrib & _A_SUBDIR))
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
            }
            else
            {
                files.push_back(p.assign(path).append("\\").append(fileinfo.name));
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}


int main()
{
    vector<string> files;
    char   buffer[MAX_PATH];
    _getcwd(buffer, MAX_PATH);

    char* filePath = buffer;
    getFiles(filePath, files);
    char str[30];
    int size = files.size();
    for (int i = 0; i < size; i++)
    { 
      remove(files[i].c_str());
       cout << files[i].c_str() << "  "<<"delete" << endl;
    }
    return 0;
}

