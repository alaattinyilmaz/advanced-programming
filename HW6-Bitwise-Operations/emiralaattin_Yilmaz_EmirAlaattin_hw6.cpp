/*
EMÝR ALAATTÝN YILMAZ 19705 / Sabanci University 27.11.2016
This program takes a message as an
array of integer elements, and (bitwise) XOR each element with 
the corresponding element of a key,
and also replicates the key whenever the
message size is larger than the key in bytes. 
*/

#include <iostream>
#include <string>

using namespace std;

typedef unsigned int ui;

template <class itemType> // Allows us to use this function more than one datatype for key variable
ui Encrypt(ui msg, itemType & key) 
// This function takes a message and key and it XOR message and key according to some conditions
{

	short msgsize = sizeof(msg);
	short keysize = sizeof(key);

	ui ciphertext = 0; 

	if (msgsize > keysize) // Checking if message size bigger than key size in byte
	{
		for(unsigned int i = 1; i < (msgsize/keysize); i++)
		{
			ciphertext = ciphertext << keysize*8; // Shifting ciphertext to the left 
			ciphertext = ciphertext ^ key; // XOR'ing 
		}
	}

	ui criptographic = msg ^ key; // Creating our criptographic data 
	ciphertext = ciphertext << keysize*8; // Shifting ciphertext
	ciphertext = criptographic ^ ciphertext; // Adding it to the last bits by XOR operation

	return ciphertext;
}

template <class keyType>
void Print(ui * message_array, ui no_ints, keyType & key, ui *ciphertext, ui *plaintext)
{
	for(int i = 0; i < no_ints; i++)
	{
		ciphertext[i] = Encrypt(message_array[i], key); // Putting into ciphertext array all the encrypted datas
		plaintext[i] = Encrypt(ciphertext[i], key); // Putting into plaintext array by encrypting the encrypted data which is actually decrypting
	}

	cout << "Ciphertext is: ";
	for(int i = 0; i < no_ints; i++) // Printing all the ciphertexts elements
	{cout << ciphertext[i] << " ";}

	cout << endl << "Plain text is: ";
	for(int i = 0; i < no_ints; i++) // Printing all the plaintexts elements
	{cout << plaintext[i] << " ";}

}

int main() {
	cout << "\nJust for FYI --------------------------" << endl;
	cout << "size of unsigned char is " << sizeof(char) << endl;
	cout << "size of unsigned short is " << sizeof(short) << endl;
	cout << "size of unsigned int is " << sizeof(int) << endl;
	cout << "---------------------------------------\n\n\n";

	ui* message_array;
	ui* ciphertext;
	ui* plaintext;

	cout << "Size of the message array is ";
	ui no_ints;  cin >> no_ints;
	message_array = new ui[no_ints];
	cout << "Enter the message array integers one after another by pressing enter after each number:" << endl;
	for(int i = 0; i < no_ints; i++) {
		cin >> message_array[i];
	}
	cout << "Type of key is unsigned ";
	string key_type;
	cin >> key_type;

	if(key_type != "char" && key_type != "int" && key_type != "short") // InputCheck of key_type
	{
		cout << "Key Type is not valid." << endl;
		return 0;
	}

	ciphertext = new ui[no_ints]; // Allocating memory from heap
	plaintext = new ui[no_ints];

	cout << "Type value of the key is ";

	// The if else checks below creates a key variable that is according to key_type
	if(key_type == "char") 
	{
		unsigned char key;
		cin >> key;
		Print(message_array, no_ints, key, ciphertext, plaintext);
	}
	else if (key_type == "short")
	{
		unsigned short key;
		cin >> key;
		Print(message_array, no_ints, key, ciphertext, plaintext);
	}
	else 
	{
		ui key;
		cin >> key;
		Print(message_array, no_ints, key, ciphertext, plaintext);
	}


	return 0;
}
