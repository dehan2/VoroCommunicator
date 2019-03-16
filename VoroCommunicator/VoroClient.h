#pragma once

#include <string>
#include <vector>
#include<thread>
#include <filesystem>

using namespace std;

class VoroClient
{
private:
	string m_commandFileName;
	string m_inputFileName;
	
	vector<int> m_input;

	vector<float> m_modifiedSolutions;
	vector<thread*> m_workingThreads;

	float m_finalSolution;

public:
	VoroClient();
	~VoroClient();

	void read_command(const string& commandFileName);
	void initialize();
	void modify_solutions();
	void compute_factorial(const int& index);

	void integrate_solutions();
};

