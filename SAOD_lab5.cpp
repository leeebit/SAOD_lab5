#include <iostream>

// Класс для представления процедуры и ее типа (вызов или возврат)
class Procedure
{
public:
	const char* name;
	bool isCall;

	// Конструктор класса Procedure
	Procedure(const char* name, bool isCall) : name(name), isCall(isCall) {}
};

// Функция для проверки валидности трассировки
bool isTraceValid(Procedure trace[], int size)
{
	const char* callStack[100]; // Используем массив в качестве стека
	int top = -1; // Индекс вершины стека

	// Проходим по всем процедурам в трассировке
	for (int i = 0; i < size; i++)
		if (trace[i].isCall)
			callStack[++top] = trace[i].name; // Добавляем процедуру в стек
		else
		{
			if (top == -1 || strcmp(callStack[top], trace[i].name) != 0) {
				std::cout << "Ошибка: Процедура " << trace[i].name  << " завершилась до того, как была вызвана.\n";
				return false;
			}
			top--; // Удаляем процедуру из стека
		}


	// Если в конце трассировки стек не пуст, выводим сообщение об ошибке
	if (top != -1)
	{
		std::cout << "Ошибка: Не все процедуры были корректно завершены.\n";
		return false;
	}

	return true; // Если все процедуры были корректно вызваны и завершены, возвращаем true
}

int main()
{
	system("chcp 1251");

	// Создаем трассировку
	Procedure trace[] =
	{
	Procedure("main", true),
	Procedure("func1", true),
	Procedure("func1", false),
	Procedure("func2", true),
	Procedure("func2", false),
	Procedure("main", true)
	};

	// Проверяем валидность трассировки
	if (isTraceValid(trace, sizeof(trace) / sizeof(trace[0])))
		std::cout << "Трассировка соответствует правильной работе программы.\n";


	return 0;
}