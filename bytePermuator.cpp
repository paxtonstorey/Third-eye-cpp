#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <bits/stdc++.h>

#define BITCOUNT 16
#define PERMUTATIONS pow(2, BITCOUNT)
std::string* bytes = new std::string[65536];
int p = 0;

//not including std namespace since someone told me it was a bad practice
//as if my program itself is already good practice lol :(
void printTheArray(int arr[], int n){
    std::string curByte = "";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
        curByte = curByte + std::to_string(arr[i]);
    }
    bytes[p] = curByte;
    p++;
    std::cout << std::endl;
}

//https://www.geeksforgeeks.org/generate-all-the-binary-strings-of-n-bits/
//man this was confusing so is cratched my precious implementation and googled. 
//Was introduced to the <bits/std++.h> helper file and 
//I also didn't even think about approaching this with recurssion. :(
void generateAllBinaryStrings(int n, int arr[], int i)
{
    if (i == n) {
        printTheArray(arr, n);
        return;
    }
    arr[i] = 0;
    generateAllBinaryStrings(n, arr, i + 1);

    arr[i] = 1;
    generateAllBinaryStrings(n, arr, i + 1);
}

void writeToFile(){
    std::ofstream byteFile;
    byteFile.open("bytePerms.txt");
    for(int x = 0; x < PERMUTATIONS;x++){
        byteFile << bytes[x] << std::endl;
    }
    byteFile.close();
}

void manchesterWrite(){
    std::ofstream manFile;
    manFile.open("manchesterFile.txt");
    int byteLength = 16;
    for(int i = 0; i < 65536; i++){
        bool validByte = true;
        char charArr[byteLength + 1];
        std::strcpy(charArr, bytes[i].c_str());
        for(int x = 1; x < byteLength-1; x++){
            if(charArr[x-1] == charArr[x] && charArr[x] == charArr[x+1]){
                validByte = false;
            }
        }
        if(validByte){
            manFile << bytes[i] << std::endl;
        }
    }
    manFile.close();
}

//Here we go!!!!
int main(){
    auto startTime = std::chrono::high_resolution_clock::now();
    int n = BITCOUNT; //No cin for debugging ease. probally should add it though
    int arr[n];
    generateAllBinaryStrings(n, arr, 0); // the zero is is the starting index, function is recursive.
    std::cout << "Permutations: " << PERMUTATIONS << std::endl;
    writeToFile();
    manchesterWrite();
    auto endTime = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
    printf("Time measured: %.5f seconds.\n", elapsed.count() * 1e-9);
    return EXIT_SUCCESS;
}