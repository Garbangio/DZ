//евклида
#include <iostream>
using namespace std;

// Нахождение степени полинома (позиции старшего ненулевого бита)
int degree(unsigned int polynom)
{
	if (polynom == 0)
	{
		return -1; // Если полином равен 0, степень не определена (-1)
	}

	int deg = 0;
	while (polynom >>= 1) // Сдвигаем число вправо, пока не дойдём до 0, увеличивая степень
	{
		deg++;
	}
	return deg;
}

// Вычисление остатка от деления двух полиномов
unsigned int mod(unsigned int a, unsigned int b)
{
	int degA = degree(a);
	int degB = degree(b);

	if (degA < degB)
	{
		return a; // Если делимое меньше делителя, то остаток равен делимому
	}

	while (degA >= degB && a)
	{
		a ^= (b << (degA - degB)); // Вычитаем (XOR) делитель, сдвинутый на нужную степень
		degA = degree(a); // Обновляем степень текущего остатка
	}
	return a;
}

// Нахождение НОД двух полиномов по алгоритму Евклида
unsigned int nod(unsigned int a, unsigned int b)
{
	while (b)
	{
		unsigned int remainder = mod(a, b); // Находим остаток от деления a на b
		a = b; // b становится новым делимым
		b = remainder; // Остаток становится новым делителем
	}
	return a; // Когда b = 0, в a останется НОД
}

// Вывод полинома
void printPolynom(unsigned int polynom)
{
	if (polynom == 0)
	{
		cout << "0"; // Если полином 0, просто выводим "0"
		return;
	}

	bool FirstElem = true; // Флаг для правильного форматирования вывода
	for (int i = degree(polynom); i >= 0; --i)
	{
		if (polynom & (1U << i)) // Проверка на коэффициент при x^i
		{
			if (!FirstElem)
			{
				cout << " + "; // Добавляем + , если это не первый член
			}

			if (i == 0)
			{
				cout << "1"; // Если это свободный член, выводим "1"
			}
			else if (i == 1)
			{
				cout << "x"; // Если x^1, просто выводим "x"
			}
			else
			{
				cout << "x^" << i; // В остальных случаях x^i
			}

			FirstElem = false; // После первого члена начинаем добавлять +
		}
	}
}

int main()
{
	setlocale(LC_ALL, "RU");

	unsigned int polynom1, polynom2;

	// Ввод первого полинома
	cout << "Введите первое число (полином): ";//в десятичной форме числа 
	cin >> polynom1;

	// Ввод второго полинома
	cout << "Введите второе число (полином): ";
	cin >> polynom2;

	cout << "Полином 1: ";
	printPolynom(polynom1);
	cout << endl;

	cout << "Полином 2: ";
	printPolynom(polynom2);
	cout << endl;

	unsigned int result = nod(polynom1, polynom2); // Вычисляем НОД полиномов

	cout << "НОД: ";
	printPolynom(result);
	cout << endl;

	return 0;
}