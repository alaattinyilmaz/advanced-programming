struct QueueNode 
{

	char element;
	QueueNode *next;

	QueueNode(char value, QueueNode *ptr = nullptr)
	{
		element = value;
		next = ptr;
	}

};

class DynQ {

private:
	QueueNode *head;
	QueueNode *tail;
	
public:
	DynQ();
	void qadd(char);
	void qdrop(char &);
	bool IsEmpty() const;

};