#include <iostream>
#include <thread>
#include <sys/types.h>
#include <dirent.h>
#include <cstring>
#include <regex>
// constexpr глобал количество сред 
////////////////////////////////////////////////////////////////
void ListDirectory(const char* name_directory);

////////////////////////////////////////////////////////////////
int main() {
    const char* CONST_main_dir = "/home/dmiriy/";
    ListDirectory(CONST_main_dir);
    
    return 0;
}

////////////////////////////////////////////////////////////////
void ListDirectory(const char* name_directory){
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
            std::cout << CONST_d_name << " " << full_d_name << "\n";
            continue;
        } 
            
        strcat(full_d_name, CONST_split_dir);
        const char* CONST_sub_dir = full_d_name;
        
        //1 сформирова много поточность 
        // std::thread t_dir(ListDirectory(CONST_sub_dir, vec_directorys));
       
        //std::thread th(ListDirectory,CONST_sub_dir);
        //th.join();

        ListDirectory(CONST_sub_dir);
    }
    return;
}

////////////////////////////////////////////////////////////////

