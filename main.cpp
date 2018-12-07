/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Beau
 *
 * Created on December 2, 2018, 10:26 AM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Node {
    string elem;
    int count = 1;
    void add(){
        count++;
    }
};

int main() {
    int twoAmount = 0;
    int threeAmount = 0;
    string output;
    ifstream input;
    
    input.open("input.txt");
    vector<string> lines;
    
    if (input.is_open()){
        while (!input.eof()){
            getline(input, output);
            lines.push_back(output);
        }
        
        string current = "";
        bool two = false;
        bool three = false;
        
        //Per line
        for (int x = 0; x < lines.size(); x++){
            vector<Node*> repeating;
            Node* head = new Node();
            head->elem = "-1";
            repeating.push_back(head);
            
            //Per character
            for (int y = 0; y < lines[x].size(); y++){
                current = lines[x][y];
                Node* tmp = new Node();
                tmp->elem = current;
                int size = repeating.size();
                
                //Per repeating character
                int inPos = 0;
                bool ifOne = false;
                bool ifTwo = false;;
                
                //Checks whether the string exists in the vector of nodes
                for (int z = 0; z < size; z++){
                    if (repeating.size() == 0 || repeating[z]->elem != current){
                        ifOne = true;
                    } else if (repeating[z]->elem == current) {
                        ifTwo = true;
                        inPos = z;
                    }
                }
                
                //Either pushes new Node or adds to the Node count
                if (ifOne && !ifTwo){
                    repeating.push_back(tmp);
                }
                if (ifTwo){
                    repeating[inPos]->add();
                }
            }
  
            two = false;
            three = false;
            
            //Check if string of size 2 and/or 3 exist
            for (int y = 0; y < repeating.size(); y++){
                if (repeating[y]->count == 2){
                    two = true;
                }
                if (repeating[y]->count == 3){
                    three = true;
                }
            }
            if (two)
                twoAmount += 1;
            if (three)
                threeAmount += 1;
            
            //Sanitizing the Nodes
            while (repeating.size() > 0){
                delete repeating.back();
                repeating.pop_back();
            }
            
            //Cleans up the repeating
            repeating.clear();
        }
        
        vector<string> common;

        //Creates a vector of type string showing the common characters
        //x = position of first repeating being checked
        for (int x = 0; x < lines.size(); x++){
            //y = position of second repeating being checked
            for (int y = x+1; y < lines.size(); y++){
                common.push_back("");
                //z = index being compared
                for (int z = 0; z < lines[x].size(); z++){
                    if (lines[x][z] == lines[y][z]){
                        common.back() += lines[x][z];
                    }
                }
            }
        }
        
        string buffer;
        string largest;
        
        //Determines which common string is largest
        for (int x = 0; x < common.size(); x++){
            for (int y = x+1; y < common.size(); y++){
                if (common[x].size() > common[y].size()){
                    buffer = common[x];
                }
                if (common[x].size() < common[y].size()){
                    buffer = common[y];
                }
                if (buffer.size() > largest.size()){
                    largest = buffer;
                }
            }
        }
        
        cout << "This is the largest common: " << largest << endl;

        
        int result = twoAmount * threeAmount;
        
        cout << "twoAmount is " << twoAmount << endl;
        cout << "threeAmount is " << threeAmount << endl;
        cout << "The checksum amount is " << result << endl;
    }

    return 0;
}

