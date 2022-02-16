#pragma once
class List
{

private:

	class Node
	{

	private:

	public:

		Node	*m_ptrNext;
		int		m_numb;

		Node(int, Node*);
		~Node();

	};

	Node	*m_head;
	int		m_length;

public:

	List();
	~List();

	int &operator[](const int index);				//Перегрузка кв. скобок для доступа к эл.

	void pushBack(int numb);						//Добавление эл. в конец списка
	void pushFront(int numb);						//Добавление эл. в начало списка
	void popFront();								//Удаление первого эл. списка
	void popBack();									//Удаление последнего эл. списка
	void insert(int numb, int index);				//Вставка нового элемента по индексу
	void remove(int index);							//Удаление элемента по индексу
	void clear();									//Очистка списка
	int getLength(){ return m_length; };			//Получение длины списка

};



//START OF CONSTRUCTORS AND DESTRUCTORS

List::List(): m_length(0), m_head(nullptr)
{}

List::~List(){ clear(); }


List::Node::Node(int numb = 0, Node *ptrNext = nullptr)
	: m_numb(numb), m_ptrNext(ptrNext)
{}

List::Node::~Node()
{}

//END OF CONSTRUCTORS AND DESTRUCTORS



//START OF METHODS FOR LIST

void List::pushBack(int numb)
{

	if (m_head == nullptr)
	{

		m_head = new Node(numb);

	}

	else
	{

		Node *current = m_head;

		while (current -> m_ptrNext != nullptr)
		{

			current = current -> m_ptrNext;

		}

		current -> m_ptrNext = new Node(numb);

	}

	m_length++;

}

void List::pushFront(int numb)
{

	m_head = new Node(numb, m_head);

	m_length++;

}

void List::popFront()
{

	Node *temp = m_head;

	m_head = m_head -> m_ptrNext;

	delete temp;

	m_length--;

}

void List::popBack()
{

	remove(m_length - 1);

}

void List::insert(int numb, int index)
{

	if (index == 0)
	{

		pushFront(numb);

	}

	else
	{

		Node *previous = m_head;

		for (int i = 0; i < index - 1; i++)
		{

			previous = previous -> m_ptrNext;

		}

		Node *newNode = new Node(numb, previous -> m_ptrNext);

		previous -> m_ptrNext = newNode;

		m_length++;

	}
	
}

void List::remove(int index)
{

	if (index == 0)
	{

		popFront();

	}

	else
	{

		Node *previous = m_head;

		for (int i = 0; i < index - 1; i++)
		{

			previous = previous -> m_ptrNext;

		}

		Node *tmp = previous -> m_ptrNext;

		previous -> m_ptrNext = tmp -> m_ptrNext;

		delete tmp;

		m_length--;

	}

}

void List::clear()
{

	while (m_length)
	{

		popFront();

	}

}

//END OF METHODS FOR LIST



//START OF OVERLOADS

int &List::operator[](const int index)
{

	Node *current = this->m_head;

	int counter{ 0 };

	while (current != nullptr)
	{

		if (counter == index)
		{

			return current -> m_numb;

		}

		current = current->m_ptrNext;
		counter++;

	}

}

//END OF OVERLOADS


