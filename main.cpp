#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include "math.h"
using namespace std;
/**
* Reads data from input file and saves it into vector.
*
* @param path      the path of the file.
* @param data      the container in which the data is saved rack of tiles to play from.
*/
void readFile(string path,vector<string>&data)
{
	ifstream inputFile;
	inputFile.open(path);
	string line;
	if (inputFile.is_open())
	{
		while (getline(inputFile, line))
		{
			data.push_back(line);
		}
	}
}
/**
 * Prints data into file.
 *
 * @param path      the path of the file.
 * @param data      the container which has the data we need to print.
 */
void printInFile(string Path, vector<string>data)
{
    ofstream outFile;
    outFile.open(Path);
    if (outFile.is_open())
    {
        for(int i=0;i<data.size();i++)
            outFile<<data[i]<<endl;
    }
}
/**
 * Converts stream of binary bits into character.
 *
 * @param binaryStream  the path of the file.
 *
 * @return character    the char corresponds to the stream.
 */
char binaryToChar(string binaryStream)
{
    int s;
    for (int i=7,j=0;i>=0,j<=7;i--,j++)
    {
        if(binaryStream[j]=='1')
            s+=pow(2,i);
    }
    return char(s);
}
/**
 * Initializes a map between A-Z charcter and their binary representation.
 *
 * @param binaryMap      the map (Sent by reference)
 */
void initCharMap(map <char,string>&binaryMap)
{
    for (int i = 'A'; i <= 'Z'; i++)
    {
        char x[33];
        string x2, frame;
        _itoa_s(i,x,2);
        x2 = x;
        for (int j = 0; j < 8 - x2.size(); j++)
            frame += '0';
        frame += x;
        binaryMap[i] = frame;
    }
}
/**
 * Calculates the number of ascii character in the payload and appends it to the
 * binary representation of the payload characters.
 *
 * @param binaryMap     the path of the file.
 *
 * @param words         list of payloads.
 *
 * @param frames        list of frames(Sent by reference).
 */
void char_count(map <char,string> binaryMap, vector<string>words, vector<string>&frames)
{
    for (int i = 0; i < words.size(); i++)
    {
        string frame="";
        char x[8]="0000000";
        string x2;
        int count_num = 2 + words[i].size();
        _itoa_s(count_num+48, x, 2);
        x2 = x;
        for (int i = 0; i < 8-x2.size();i++)
            frame += '0';
        frame += x;
        for (int j = 0; j < words[i].size(); j++)
        {
            frame += binaryMap[words[i][j]];
        }
        frames.push_back(frame);
    }
}
/**
 * Appends even parity to the frames.
 *
 * @param frames    the frames container(Sent by reference).
 */
void appendEvenParity(vector<string>&frames)
{
    int k,onesCnt = 0;
    for (int i = 0; i < frames.size(); i++)
    {
        for (int j = 0; j < 8; j++)
        {
            k = j,onesCnt=0;
            while (k < frames[i].size())
            {
                if (frames[i][k] == '1')
                    onesCnt++;
                k+=8;
            }
            if (onesCnt % 2 == 0)
                frames[i] += '0';
            else
                frames[i] += '1';
        }
    }
}
/**
 * Prints each byte of frames in [].
 *
 * @param frames        frames container
 */
void printFrames(vector<string>frames)
{
    for (int i = 0; i < frames.size(); i++)
    {
        cout << "[[";
        for (int j = 0; j < frames[i].size(); j++)
        {
            cout << frames[i][j];
            if ((j + 1) % 8 == 0 && j+1< frames[i].size())
                cout << "][";
            else if((j + 1) % 8 == 0)
                cout << "]]";
        }
        cout << endl;
    }
}
/**
 * Checks if parity in frames is true and prints the original payload.
 */
void printOriginalPayload()
{
    ofstream of("C:\\Users\\Sara\\CLionProjects\\NW_2\\result.txt");
    //Takes frames from frames FILE
    vector <string> f;
    readFile("C:\\Users\\Sara\\CLionProjects\\NW_2\\frames.txt",f);
    //Checks even parity for each frame
    for(int i=0;i<f.size();i++)
    {
        int k,onesCnt,flag=1;
        for (int j = 0; j < 8; j++)
        {
            k = j,onesCnt=0;
            while (k < f[i].size()-8)
            {
                if (f[i][k] == '1')
                    onesCnt++;
                k+=8;
            }
            if (onesCnt % 2 == 0 && f[i][f[i].size()-8+j]== '1')
            {
                flag=0;
            }
        }
        if(flag)
        {
            //If correct, print original payload
            int idx=8;
            string s;
            while (idx< f[i].size()-8)
            {
                s+=binaryToChar(f[i].substr(idx,8));
                idx+=8;
            }
            cout<<s<<endl;
            of<<s<<endl;
        }
        else
        {
            cout<<"ERROR"<<endl;
            of<<"ERROR"<<endl;
        }
    }
}
int main()
{
    vector<string> words;
    map <char, string> binaryMap;
    vector<string>frames;

    readFile("C:\\Users\\Sara\\CLionProjects\\NW_2\\input.txt",words);
    initCharMap(binaryMap);
    char_count(binaryMap,words,frames);
    appendEvenParity(frames);
    printFrames(frames);
    printInFile("C:\\Users\\Sara\\CLionProjects\\NW_2\\frames.txt",frames);
    printOriginalPayload();
}
