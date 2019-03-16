#include "VoroClient.h"
#include <fstream>
#include <iostream>


VoroClient::VoroClient()
{
}



VoroClient::~VoroClient()
{
}



void VoroClient::read_command(const string& commandFileName)
{
	cout << "Start to read command file" << endl;

	ifstream fin;
	fin.open(commandFileName.c_str());

	const char* seps = " \t\n:";
	char buffer[200];

	while (fin.getline(buffer, 200))
	{
		if (buffer[0] != '#')
		{
			string parameterName(strtok(buffer, seps));
			if (parameterName.compare("inputFile") == 0)
			{
				m_inputFileName = strtok(NULL, seps);
			}
		}
	};
	
	fin.close();
	cout << "Command File read finish - input file: "<< m_inputFileName << endl;
}



void VoroClient::initialize()
{
	cout << "Read input file" << endl;
	ifstream fin; 
	fin.open(m_inputFileName);
	
	const char* seps = " \t\n:";
	char buffer[200];

	fin.getline(buffer, 200);
	int numInputs = atoi(strtok(buffer, seps));
	fin.getline(buffer, 200);
	int input = atoi(strtok(buffer, seps));
	m_input.push_back(input);
	
	for (int i = 1; i < numInputs; i++)
	{
		input = atoi(strtok(NULL, seps));
		m_input.push_back(input);
	}

	fin.close();
	cout << "Read input finish: " <<m_input.size()<< endl;
}

void VoroClient::modify_solutions()
{
	cout << "Start modifying solutions" << endl;

	m_workingThreads.resize(m_input.size());
	m_modifiedSolutions.resize(m_input.size());

	for (int i = 0; i < m_input.size(); i++)
	{
		m_workingThreads.at(i) = new thread(&VoroClient::compute_factorial, this, i);
	}

	for (int i = 0; i < m_input.size(); i++)
	{
		m_workingThreads.at(i)->join();	//Wait until thread completed
		delete m_workingThreads.at(i);
		m_workingThreads.at(i) = nullptr;

		cout << "Thread[" << i << "] finish: " << m_modifiedSolutions.at(i) << endl;
	}

	cout << "Modifying solutions finish" << endl;
}



void VoroClient::compute_factorial(const int& index)
{
	cout << "Thread[" << index << "] start" << endl;
	int factorialEnd = m_input.at(index);
	float factorialResult = 1;
	for (int i = 2; i <= factorialEnd; i++)
	{
		factorialResult *= i;
	}
	m_modifiedSolutions.at(index) = factorialResult;
	cout << "Thread[" << index << "] end: " <<factorialResult<< endl;
}



void VoroClient::integrate_solutions()
{
	cout << "Integrate solutions" << endl;
	m_finalSolution = 0.0f;
	for (int i = 0; i < m_modifiedSolutions.size(); i++)
	{
		m_finalSolution += m_modifiedSolutions.at(i);
	}

	cout << "Final solution: " << m_finalSolution << endl;
}
