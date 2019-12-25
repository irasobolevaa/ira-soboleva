#include <iostream>
#include <string>

using namespace std;

template<typename T>
class List
{
    public:
        List(); 
        ~List();

        void pop_front();
        void pop_back();
        void clear(); //освобождение данных динамического списка
        void push_back(T data); //вставить в конец списка
        void push_front(T data);
        void insert(T data, int index); //добавление элемента в список по указанному индексу
        void remove (int index);
        int GetSize() {return Size;} //размер списка
        T& operator[](const int index); //получение доступа к определенному элементу через оператор []; возвращаем ссылку на тип Т; index - принимаемый параметр, те номер того элемента, который мы должны вернуть

    private:

        template<typename T> //создание шаблонного класса Node; template указывает на то, что класс является шаблонным, typename указывает на то, что в этом классе будут использоваться обобщенные тип данных, буква Т - название обобщенного типа данных
        class Node // каждый элемент списка - узел списка
        {
            public:
                Node* pNext; //текущий узел содержит адрес на следующий элемент
                T data; //данные, которые добавляются в список
                Node(T data, Node* pNext = nullptr) // конструктор;присваиваем входящие параметры соответствующим полям класса Node 
                //при добавлении элемента в конец списка нужно учитываь, что в конструктор передеются только данные (без адреса), поэтому используем по умолчанию nullptr, те никуда не указывать

                {
                    this->data = data;
                    this->pNext = pNext;
                }

        };

    int Size;
    Node<T> *head; //указатель на первый элемент
};

template<typename T>
List<T>::List() //вынос конструктора
{
    Size = 0;
    head = nullptr; //создали пустой список
}

template<typename T>
List<T>::~List()//вынос деструктора
{
    clear();
}

template<typename T>
void List<T>::push_back(T data)
{
    if (head == nullptr) //проверяем, есть ли что-то в заголовке (не пустой ли элемент head)
    {
        head = new Node<T>(data); //создание элемента в динамической памяти
    }
    else
    {
        Node<T> *current = this-> head;//присваивание указателю значение заголовка head

        while(current-> pNext != nullptr) //идем по всем Node-ам и ищем последнюю
        {
            current = current->pNext; //присваиваем элементу следующий адрес текущему элементу  
        }

        current-> pNext = new Node<T>(data); //найден элеменет, который указывает на NULL и по этому адресу вставляем новый объект типа Node

    }
    Size++;
}

template<typename T>
void List<T>::push_front(T data)
{
    Node<T>* current = new Node<T>(data);
    current->pNext = this->head;
    this->head = current; 
        
    Size++;
}


template<typename T>
void List<T>::pop_front()
{
    Node<T>* temp = head; //хранит адрес head

    head = head-> pNext;// адрес следующего после head элемента
    delete temp;
    Size--;
}

template<typename T>
void List<T>::pop_back()
{
    Node<T>* current = this->head;
    while (current-> pNext != nullptr)
    {
        current = current->pNext;
    }
    delete current;
    Size--;
}

template<typename T>
void List<T>::clear()
{
    while (Size) //Size типа bool; пока Size != 0
    {
        pop_front(); 
    }
}


template<typename T>
T& List<T>::operator[](const int index) 
{
    int counter = 0; //счетчик
    Node<T> *current = this-> head; //переменная current показывает, в каком элементе мы сейчас находимся, чтобы проверить адрес следующего элемента
    while (current != nullptr)
    {
        if (counter == index)
        {
            return current-> data; //возвращаем найденный элемент;  забираем данные у current из поля data
        }
        current = current->pNext; //присваиваем адрес следующего элемента
        counter++;
    }
}

template<typename T>
void List<T>::insert(T data, int index)
{
    if (index == 0)
    {
        push_front(data);
    }
    else
    {
        Node<T>* previous = this->head; //временный указатель

        for(int i = 0; i < index - 1; i++) //ищем элемент с предшествующим индексом
        {
            previous = previous->pNext; //присваиваем указатель на следующую Node-у нашего списка
        }

        Node<T>* newNode = new Node<T>(data, previous->pNext); //значение адреса, содержащегося у предыдущего элемента, передаем вставляемому элементу
        previous->pNext = newNode; //добавляем адрес нового объекта к предыдущему старому объекту

        Size++;
    }
    
}

template<typename T>
void List<T>::remove(int index)
{
    if (index == 0)
    {
        pop_front();
    }
    else
    {
        Node<T>* previous = this->head; //ищем предыдущий элемент относительно указанного в указанном индексе
        for (int i = 0; i < index - 1; i++)
        {
            previous=previous->pNext;
        }
        Node<T>* toDelete = previous->pNext;
        previous->pNext = toDelete->pNext;
        delete toDelete;

        Size--;
    }
    
}


int main()
{
    List<int> lst;
    lst.push_back(5);
    lst.push_back(10);
    lst.push_back(12);

    int numbersCount;
    cin>>numbersCount;

    for (int i = 0; i < numbersCount; i++) //заполнение списка случайными числами
    {
        lst.push_back(rand() % 10);
    }

    for (int i = 0; i < lst.GetSize(); i++) //вывод списка
    {
        cout<<lst[i]<<endl;
    }

    lst.pop_front(); //выполнение метода удаления первого элемента списка

    lst.clear(); //удаление всех элементов списка

    cout<<lst.GetSize()<<endl; //вывод размера списка

    lst.insert(99, 1);

    return 0;
}
