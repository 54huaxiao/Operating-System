#pragma once
#ifndef MIN_SHELL_H
#define MIN_SHELL_H

#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<Windows.h>
#include<direct.h>
using namespace std;

class minshell {
public:
	void run();
	minshell();
private:
	string command;
	void instruction();
	void exe_file(const string& filepath);
	void create_process(const string& command);
	void get_command(string &command);
	void quit();
	string pwd();
};

#endif