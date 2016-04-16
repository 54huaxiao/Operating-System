#include"min_shell.h"
#define MAX_SIZE 500
minshell::minshell() {}

void minshell::run() {
	instruction();
	do {
		cout << "user @ " << pwd() << "#: ";
		get_command(command);
	} while (true);

}

void minshell::instruction() {
	cout << "Min_Shell [版本 1.0.0]" << endl;
	cout << "(c) By Mo Huaxiao in 2016/4/10" << endl;
	cout << "Usage: " << endl;
	cout << "#######################################################################################" << endl;
	cout << "#                                                                                     #" << endl;
	cout << "#pwd: show the route                                                                  #" << endl;
	cout << "#quit: quit the Min_Shell                                                             #" << endl;
	cout << "#min_shell a.txt:打开当前目录下的txt文件执行里面的指令                                #" << endl;
	cout << "#min_shell a.exe:打开当前目录下的exe程序                                              #" << endl;
	cout << "#Microsoft中cmd的绝大部分指令都可满足，如ping, cd, dir, 具体操作同cmd                 #" << endl;
	cout << "#                                                                                     #" << endl;
	cout << "#######################################################################################" << endl;
	cout << endl;
}

void minshell::quit() {
	cout << "shell is quiting";
	fflush(stdout);
	Sleep(500);
	cout << ".";
	fflush(stdout);
	Sleep(500);
	cout << ".";
	fflush(stdout);
	Sleep(500);
	cout << "." << endl;
	fflush(stdout);
}

string minshell::pwd() {
	return _getcwd(NULL, 0);
}

void minshell::get_command(string &command) {
	getline(cin, command);
	if (command == "pwd") {
		cout << "the current route is " << minshell::pwd() << endl;
		return;
	}
	else if (command == "quit") {
		quit();
		return;
	}
	if (command.length() > 10) {
		string prefix = command.substr(0, 9);
		if (prefix == "min_shell") {
			command = command.substr(10);
			if (command.substr(command.length() - 3, command.length()) == "exe") create_process(command);
			if (command.substr(command.length() - 3, command.length()) == "txt") exe_file(command);
		}
		else {
			system(command.c_str());
		}
	}
	else {
		system(command.c_str());
	}
}

void minshell::exe_file(const string& filepath) {
	ifstream ifile(filepath.c_str(), ios::in);
	if (!ifile) {
		cout << "Open file Failed, please check the path\n";
	}
	else {
		string content;
		while (getline(ifile, content)) {
			cout << content << endl;
			create_process(content);
		}
	}
	ifile.close();
}

void minshell::create_process(const string& command) {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	char command_buf[MAX_SIZE];
	sprintf_s(command_buf, "%s", command.c_str());

	// create child process
	if (!CreateProcess(NULL, // use command line
		command_buf, // use command line
		NULL, // don't inherit process handle
		NULL, // don't inherit thread handle
		FALSE, // disable handle inheritance
		0, // no creation flag
		NULL, // use parent's environment block
		NULL, // use parent's existing directory
		&si,
		&pi)) {
		fprintf(stderr, "no such command line\n");
	}

	// parent will wait for the child to complete
	WaitForSingleObject(pi.hProcess, INFINITE);

	// close handle
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

int main() {
	minshell cmd;
	cmd.run();
	return 0;
}