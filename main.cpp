#include <iostream>
#include <thread>
#include <sys/types.h>
#include <dirent.h>
#include <cstring>
#include <regex>
 
////////////////////////////////////////////////////////////////
void ListDirectory(const char* name_directory, const char* file_name);

////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) {
    const char* CONST_main_dir = "/";
    char file_name[256];

    std::cout << "Please enter enter the name of the file you are looking for.\n";
    std::cin >> file_name;
    std::cout << "\n";

    const char* f_name = file_name; 
    ListDirectory(CONST_main_dir,f_name);
    
    return 0;
}

////////////////////////////////////////////////////////////////
void ListDirectory(const char* name_directory, const char* file_name){
    DIR *dir;
    struct dirent *entry;  
    dir = opendir(name_directory);
    
    if (!dir)return;

    std::cmatch result;
    std::regex reqular("(\\.)([a-z][a-z]?[a-z]?$)");
    const char* CONST_split_dir = "/";
    
    while((entry = readdir(dir)) != NULL){        
        const char* CONST_d_name = entry->d_name;        
        if (strcmp(CONST_d_name, ".") == 0 || strcmp(CONST_d_name, "..") == 0 ) continue;

        char full_d_name[256] = "";

        strcat(full_d_name, name_directory);
        strcat(full_d_name, entry->d_name);         
        
        if (std::regex_search(CONST_d_name, result, reqular)){
            if (strcmp(CONST_d_name, file_name) == 0){
                std::cout << full_d_name << "\n";
            } 
            continue;
        } 
      
        strcat(full_d_name, CONST_split_dir);
        const char* CONST_sub_dir = full_d_name;
        
        //1 сформирова много поточность 
        // std::thread t_dir(ListDirectory(CONST_sub_dir, vec_directorys));
       
        //std::thread th(ListDirectory,CONST_sub_dir);
        //th.join();

        ListDirectory(CONST_sub_dir, file_name);
    }
    return;
}

////////////////////////////////////////////////////////////////

