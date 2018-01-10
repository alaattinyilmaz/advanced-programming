struct StackNode

{
	char element;
	StackNode *next;
};


class DynStack{

private: 
	StackNode *head;

public:
	DynStack(void);
	void push(char);
	void pop(char &);
	bool IsEmpty(void);
	
};