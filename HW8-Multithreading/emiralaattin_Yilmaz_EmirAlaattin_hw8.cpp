#define _VARIADIC_MAX 10
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <thread>
#include <fstream>
#include <mutex>

using namespace std;

typedef unsigned int uint;


struct transaction {

	uint current; // current transaction id
	uint prev; // hash of previous node
	uint rand; // solution
	thread::id threadid;

	transaction(){}
	transaction(unsigned int id, unsigned int prev, unsigned int solution, thread::id threadid):current(id), prev(prev), rand(solution),threadid(threadid){}

	transaction * next;
};


struct transactionChain {

public:
	transactionChain():head(nullptr), tail(nullptr){}


	void addtrans(transaction * trans) // Adding of transaction node
	{
		if(head==nullptr)
		{
			trans->next = head;
			head = trans;
			tail = head;
		}
		else 
		{
			tail->next = trans;
			trans->next = nullptr;
			tail = trans;
		}
	}

	~transactionChain() // Destructor of transaction chain
	{
		transaction * ptr = head;
		transaction * temp;

		while(ptr)
		{
			temp = ptr->next;
			delete ptr;
			ptr = temp;
		}

	}
	transaction * head;
	transaction * tail;
};

/* This function hashes a transaction to an unsigned integer value. 
It shifts curent value by 16, previous value by 8 and the random 
value by 1 bit to the left and uses std::hash to hash. */
uint hashTransaction(transaction * tran)
{
	uint result = (tran->current << 16) ^ (tran->prev << 8) ^ (tran->rand << 1);
	std::hash<uint> uint_hash;
	return uint_hash(result);
}

// This function checks if transactionchain is valid or not
bool transactionValidator(transactionChain & tChain, uint threshold) 
{
	transaction *temp = tChain.head->next;
	bool valid = true;

	while (temp != nullptr)
	{
		if (hashTransaction(temp) > threshold)
			valid = false;

		temp = temp->next;
	}
	return valid;

}

// Mine function 
void mine (transactionChain & translist, unsigned int * inputs, int size,unsigned int threshold, mutex & sharedmutex, int & tracker, bool & flag)
{

	uint bitcoins = 0; // A private unsigned integer for keeping track of the bitcoins mined by this thread.

	srand((hash<thread::id>()(this_thread::get_id())) ^ 2 % 10000); // We should use different seeds for each thread to find different random numbers.


	while(!flag) // Waiting until the flag is set.

	{
		this_thread::yield();
	}


	while(tracker < size)
	{

		unsigned int tsolution = rand(); // Generating random solution

		transaction * tran = new transaction(inputs[tracker], hashTransaction(translist.head), tsolution, this_thread::get_id());
		sharedmutex.lock();
		if(hashTransaction(tran) < threshold)
		{
			translist.addtrans(tran); // Accepting of transaction and adding to list
			bitcoins++; // This thread earned bitcoin
			tracker++;
		}

		else 
		{ 
			delete tran; // If it is not accepted it will be deleted
		}
		sharedmutex.unlock();
	}



	lock_guard<std::mutex> lock(sharedmutex); // Use of mutex to show the following line once 
	cout << "Thread " << this_thread::get_id() << " has " << bitcoins << " bitcoin(s)" << endl;

}

int main()
{

	int difficulty,numofminers,size;
	string filename;
	unsigned int lines;

	cout << "Enter difficulty level (between 0-10):";
	cin >> difficulty;
	unsigned int threshold = (1 << (31-(difficulty))); // Calculating of threshold by bitwise operators

	transactionChain translist;
	cout << threshold << " is the threshold."<< endl;

	
	cout << "Enter the filename of input file:";
	cin >> filename;

	ifstream input;
	input.open(filename.c_str());
	
	cout << "Enter the number of miners:";
	cin >> numofminers;

	input >> lines;

	size = lines;

	unsigned int * inputs = new unsigned int [size];

	for(int i = 0; i < size; i++)
	{
		input >> lines;
		inputs[i] = lines;
	}


	thread::id mainid = this_thread::get_id();
	transaction * maintrans = new transaction(0, 0, 0 , mainid);

	translist.addtrans(maintrans);

	vector <thread> miners; // Creating of a Miner thread vector

	bool flag = false; // Setting flag as false before thread creation

	mutex sharedmutex;

	int tracker = 0;

	// Creating of miner threads
	for (int i = 0; i < numofminers; i++)
	{
		miners.push_back(thread(mine,ref(translist),inputs,size,threshold, ref(sharedmutex), ref(tracker), ref(flag)));
	}

	flag = true; // Threads start racing 


	for (thread & miner: miners)
	{
		miner.join();
	}

	if(transactionValidator(translist, threshold)==true)
	{
		cout << "Transaction is valid.\n";
	}

	else
	{
		cout << "Transaction is not valid.\n";
	}




}