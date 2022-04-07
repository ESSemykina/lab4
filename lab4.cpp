/*Создайте односвязный список из 10000 целых чисел и реализуйте в нем операцию вставки элемента k в конец списка. 
Выполните M = 1000 таких запросов.
Реализуйте такую же операцию для массива. Сравните производительность.
*/


#include <iostream>
#include<chrono>
#include<vector>
class Timer
{
private:
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_t> m_beg;

public:
	Timer() : m_beg(clock_t::now())
	{
	}

	void reset()
	{
		m_beg = clock_t::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};
struct T_List
{
	T_List* next;
	int x;
};
void ADD(T_List* head, int x)
{
	T_List* p = new T_List;
	p->x = x;
	p->next = head->next;
	head->next = p;
}
void PRINT(T_List* head)
{
	T_List* p = head->next;
	while (p != nullptr)
	{
		std::cout << p->x << std::endl;
		p = p->next;
	}
}
void CLEAR(T_List* head)
{
	T_List* tmp;
	T_List* p = head->next;
	while (p != nullptr)
	{
		tmp = p;
		p = p->next;
		delete tmp;
	}
}
//добавляем в конец с помощью списка
void InsertEnd1(T_List* head, int& k)
{

	T_List* p = head->next;
	while (p != nullptr)
	{
		if (p->next == nullptr)
		{
			T_List* q = new T_List;
			q->next = p->next;
			p->next = q;
			q->x = k;
			p = p->next;
		}
		p = p->next;
	}
}
//добавляем в конец с помощью вектора
void Insertend2(std::vector<int>& vec, int& k)
{

	vec.push_back(k);
}
int main()
{
	int N = 10000;
	int M = 1000;
	srand(time(0));
	int k = rand();
	T_List* head = new T_List;
	head->next = nullptr;
	for (int i = 0; i < N; i++)
	{

		ADD(head, rand() % 100);
	}
	/*PRINT(head);
	std::cout << "====" << std::endl;*/
	Timer t1;
	for (int i = 0; i < M; i++)
	{
		k = rand();
		InsertEnd1(head, k);
	}
	std::cout << "Time elapsed: " << t1.elapsed() << '\n';
	/*PRINT(head);*/
	CLEAR(head);
	delete head;
	std::cout << "======" << std::endl;
	std::vector<int> vec;
	for (int i = 0; i < N; i++)
	{
		vec.push_back(rand() % 100);
	}
	Timer t2;
	for (int i = 0; i < M; i++)
	{
		k = rand();
		Insertend2(vec, k);
	}
	std::cout << "Time elapsed: " << t2.elapsed() << '\n';
	/*for (int i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i] << std::endl;
	}*/
}
