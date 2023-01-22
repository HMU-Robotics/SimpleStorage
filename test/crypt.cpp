
#include <iostream>
std::string crypt(std::string salt , std::string password){
    int passLen = password.length();
    int saltLen = salt.length();
    int saltCount = 0;
    std::string hash;
    std::cout<<"Cryting password : "<<password<< " with salt : "<<salt<<std::endl;
    for(int i=0;i<passLen;i++){
        if(saltCount > saltLen)saltCount = 0;
        hash.push_back(password[i]+salt[saltCount]);
        if(password[i]%2) hash.push_back(salt[saltCount]-password[i]);
        if(password[i]%1) hash.push_back(salt[saltCount]-password[i]);
        if(password[i]%2 && saltCount > 1) hash.push_back(salt[saltCount-1] + password[i]);
        if(password[i]%2 && saltCount < saltLen-1) hash.push_back(salt[saltCount+1] + password[i]);
        // else password.pop_back();
        saltCount++;
    }

    return hash;
}


int main(int argc,char* argv[]){
    std::string password , salt;
    std::cout<<"Enter password >> ";
    std::cin>>password;
    std::cout<<"Enter salt >> ";
    std::cin>>salt;
    std::string hash = crypt(salt,password);
}