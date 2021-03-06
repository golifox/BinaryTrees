#include "iostream"
#include "conio.h"
#include "stdio.h"
#include "ctime"
#include "locale.h"
#include "windows.h"

using namespace std;

int random(int min, int max) {
	return int(double(rand()) / RAND_MAX * (max - min)) + min;
}

struct tnode {
	int field; // поле данных
	struct tnode *left; // левый потомок
	struct tnode *right; // правый потомок
};

int searchmin(tnode *tree, int &min) {
	if (tree != NULL) {
		if (tree->field < min) { //если значение вершины меньше корня 
			min = tree->field;
		}
		searchmin(tree->left, min); //рекурсивная функция для продвижения по дереву вниз 
		searchmin(tree->right, min); //рекурсивная функция для продвижения по дереву вниз 
	}
	return min;
}

int kol(tnode *tree, int &k, int key) {
	if (tree != NULL) { //Пока не встретится пустой узел
		if (tree->field == key) k++;
		kol(tree->left, k, key); //Рекурсивная функция для левого поддерева
		kol(tree->right, k, key); //Рекурсивная функция для правого поддерева
	}
	return k;
}

void treeprint(tnode *tree) {
	if (tree != NULL) { //Пока не встретится пустой узел
		treeprint(tree->left); //Рекурсивная функция для левого поддерева
		treeprint(tree->right); //Рекурсивная функция для правого поддерева
		cout << tree->field << " "; //Отображаем корень дерева
	}
}

struct tnode * addnode(int x, tnode *tree) {
	if (tree == NULL) { // Если дерева нет, то формируем корень
		tree = new tnode; // память под узел
		tree->field = x; // поле данных
		tree->left = NULL;
		tree->right = NULL; // ветви инициализируем пустотой
	}
	else if (x <= tree->field) // условие добавление левого потомка
		tree->left = addnode(x, tree->left);
	else // условие добавление правого потомка
		tree->right = addnode(x, tree->right);
	return(tree);
}

struct tnode * deletenode(int x, tnode *tree, int &k)
{
	struct tnode *p, *p2;
	if (!tree) return tree;
	if (tree->field == x) {
		k++;
		if (tree->left == tree->right) {
			free(tree);
			return 0;
		}
		else if (tree->left == NULL) {
			p = tree->right;
			free(tree);
			return p;
		}
		else if (tree->right == NULL) {
			p = tree->left;
			free(tree);
			return p;
		}
		else {
			p2 = tree->right;
			p = tree->right;
			while (p->left) p = p->left;
			p->left = tree->left;
			free(tree);
			return p2;
		}
	}
	if (tree->field < x) tree->right = deletenode(x, tree->right, k);
	else tree->left = deletenode(x, tree->left, k);
	return tree;
}

void freemem(tnode *tree) {
	if (tree != NULL) {
		freemem(tree->left);
		freemem(tree->right);
		delete tree;
	}
}

int input(int &n, tnode * &root) {
	system("cls");

	root = NULL;
	cout << "1. Ввод рандом (от 0 до 100)" << endl;
	cout << "2. Ввод рандом с указанием границ" << endl;
	cout << "3. Ручной ввод" << endl;
	cout << "4. Выход в меню" << endl;
	int sel; cout << "Ваш выбор: "; cin >> sel;
	bool in = false;
	int info;
	switch (sel) {
	case 1:
		freemem(root);
		cout << "Введите количество чисел N (N>0): ";
		while (!(cin >> n) || (n < 0) || (n > 5000) || (cin.peek() != '\n')) //проверка на корректность ввода 
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Введенo недопустимое значение.Повторите попытку: ";
		}
		cout << endl;
		cout << "Рандомные значения: ";
		for (int i = 0; i < n; i++)
		{
			info = rand() % 50;
			cout << info << " ";
			root = addnode(info, root);
		}
		cout << endl;
		system("pause");
		break;
	case 2:
		freemem(root);
		int min, max;
		cout << "Введите количество чисел N (N>0): ";
		while (!(cin >> n) || (n < 0) || (n > 5000) || (cin.peek() != '\n')) //проверка на корректность ввода 
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Введенo недопустимое значение.Повторите попытку: ";
		}
		cout << endl;
		cout << "min:";
		while (!(cin >> min) || (min < -50000) || (n > 50000) || (cin.peek() != '\n')) //проверка на корректность ввода 
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Введенo недопустимое значение.Повторите попытку: ";
		}
		cout << "max:";
		while (!(cin >> max) || (max < min) || (max > 50000) || (cin.peek() != '\n')) //проверка на корректность ввода 
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Введенo недопустимое значение.Повторите попытку: ";
		}
		for (int i = 0; i < n; i++)
		{
			info = random(min, max + 1);
			root = addnode(info, root);
		}
		cout << endl;
		system("pause");
		break;
	case 3:
		freemem(root);
		cout << "Введите количество чисел N (N>0): ";
		while (!(cin >> n) || (n < 0) || (n > 5000) || (cin.peek() != '\n')) //проверка на корректность ввода 
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Введенo недопустимое значение.Повторите попытку: ";
		}
		cout << endl;
		for (int i = 0; i < n; i++) {
			cout << "[" << i + 1 << "] = ";
			while (!(cin >> info) || (info < -50000) || (info > 50000) || (cin.peek() != '\n')) //проверка на корректность ввода 
			{
				cin.clear();
				while (cin.get() != '\n');
				cout << "Введенo недопустимое значение.Повторите попытку: ";
			}
			root = addnode(info, root);
		}
		cout << endl;
		system("pause");
		break;
	case 4:
		break;
	}
	return 0;
}

int main()
{
	struct tnode *root = NULL;
	int N, ForDel, min, key, k;
	bool isin = false;

	setlocale(LC_ALL, "Russian");

	char select = 0;
	while (select != '5') {
		system("cls");
		cout << "1. Ввод данных" << endl;
		cout << "2. Постфиксный вывод дерева" << endl;
		cout << "3. Минимальное значение и кол-во листьев с ним" << endl;
		cout << "4. Удаление элемента из дерева" << endl;
		cout << "5. Выход" << endl;
		cout << "Ваш выбор: "; cin >> select;
		int k;
		switch (select) {
		case '1':
			input(N, root);
			isin = true;
			break;
		case '2':
			if (isin == false) {
				cout << "Дерева не создано! Выполните пукнт 1 в меню!" << endl << endl;
				system("pause");
			}
			else {
				cout << endl << "Постфиксный вид дерева: ";
				treeprint(root);
				cout << endl;
				system("pause");
			}
			break;
		case '3':
			if (isin == false) {
				cout << "Дерева не создано! Выполните пукнт 1 в меню!" << endl << endl;
				system("pause");
			}
			else {
				min = 10000;
				min = searchmin(root, min);
				k = 0;
				k = kol(root, k, min);
				cout << endl << "Минимальное значение в дереве = " << min << endl;
				cout << "Минимальное значение повторяется " << k << " раз " << endl;
				cout << endl;
				system("pause");
			}

			break;
		case '4':
			if (isin == false) {
				cout << "Дерева не создано! Выполните пункт 1!" << endl << endl;
				system("pause");
			}
			else {
				cout << "Введите число для удаления: ";
				cin >> ForDel;
				cout << endl;
				for (int i = 0; i < N; i++)
					root = deletenode(ForDel, root, k);
				if (k == 0) {
					cout << "Такого числа нет в дереве!" << endl;
				}
				cout << "Новое дерево: ";
				treeprint(root);
				cout << endl;
				system("pause");
			}

			break;
		case 5:
			break;
		default:
			cout << "";
			break;
		}
	}

	return 0;
}
