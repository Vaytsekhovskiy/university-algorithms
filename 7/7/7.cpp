// 7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _CRT_SECURE_NO_WARNINGS   

#include <iostream>  
#include <vector>  
#include <cstdlib>  
#include <ctime>  
#include <stack>
#include <queue>
#include <string>

using namespace std;
int m, n;

// Вывод матрицы  
void printMatrix(const vector<vector<int>>& matrix) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        cout << "\n";
    }
}

struct Node {
	int data; // значение элемента
	Node* parent; // ссылка на родителя
	Node* left; // ссылка на левого ребёнка
	Node* right; // ссылка на правого ребёнка
	int color; // 1 -> Red, 0 -> Black
};

typedef Node* NodePtr; // Node -> NodePtr

// Красно-чёрное дерево
class RBTree {
private:
	NodePtr root;
	NodePtr TNULL; // нулевой аргумент-заглушка (лист)

	// initializes the nodes with appropirate values
	// all the pointers are set to point to the null pointer
	void initializeNULLNode(NodePtr node, NodePtr parent) {
		node->data = 0;
		node->parent = parent;
		node->left = nullptr;
		node->right = nullptr;
		node->color = 0;
	}

	void preOrderHelper(NodePtr node) {
		if (node != TNULL) {
			cout << node->data << " ";
			preOrderHelper(node->left);
			preOrderHelper(node->right);
		}
	}

	void inOrderHelper(NodePtr node) {
		if (node != TNULL) {
			inOrderHelper(node->left);
			cout << node->data << " ";
			inOrderHelper(node->right);
		}
	}

	void postOrderHelper(NodePtr node) {
		if (node != TNULL) {
			postOrderHelper(node->left);
			postOrderHelper(node->right);
			cout << node->data << " ";
		}
	}

	NodePtr searchTreeHelper(NodePtr node, int key) {
		if (key == node->data) {
			return node;
		}
		if (node == TNULL) {
			return TNULL;
		}

		if (key < node->data) {
			return searchTreeHelper(node->left, key);
		}
		return searchTreeHelper(node->right, key);
	}

	// балансирует дерево после удаления элемента
	void fixDelete(NodePtr x) { // узел, который встал на место удаляемого
		NodePtr s; // брат х
		while (x != root && x->color == 0) { // 0 = BLACK, если х - красный, перекрашиваем в чёрный, чтоб сбалансир.
			if (x == x->parent->left) { // брат справа
				s = x->parent->right;
				if (s->color == 1) { // если брат красный, то родитель - чёрный
					// покрасить брата в чёрный, родителя в красный, брат - родитель
					// case 3.1
					s->color = 0;
					x->parent->color = 1;
					leftRotate(x->parent);
					s = x->parent->right;
				}

				if (s->left->color == 0 && s->right->color == 0) {
					// case 3.2
					s->color = 1;
					x = x->parent;
				}
				else {
					if (s->right->color == 0) {
						// case 3.3
						s->left->color = 0;
						s->color = 1;
						rightRotate(s);
						s = x->parent->right;
					}

					// case 3.4
					s->color = x->parent->color;
					x->parent->color = 0;
					s->right->color = 0;
					leftRotate(x->parent);
					x = root;
				}
			}
			else { // брат слева
				s = x->parent->left;
				if (s->color == 1) {
					// case 3.1
					s->color = 0;
					x->parent->color = 1;
					rightRotate(x->parent);
					s = x->parent->left;
				}

				if (s->right->color == 0 && s->right->color == 0) {
					// case 3.2
					s->color = 1;
					x = x->parent;
				}
				else {
					if (s->left->color == 0) {
						// case 3.3
						s->right->color = 0;
						s->color = 1;
						leftRotate(s);
						s = x->parent->left;
					}

					// case 3.4
					s->color = x->parent->color;
					x->parent->color = 0;
					s->left->color = 0;
					rightRotate(x->parent);
					x = root;
				}
			}
		}
		x->color = 0;
	}

	// вырезает u, на его место вставляет v
	void rbTransplant(NodePtr u, NodePtr v) {
		if (u->parent == nullptr) {
			root = v;
		}
		else if (u == u->parent->left) {
			u->parent->left = v;
		}
		else {
			u->parent->right = v;
		}
		v->parent = u->parent;
	}

	void deleteNodeHelper(NodePtr node, int key) {
		// ищет элемент, содержащий данный ключ (бинарный поиск)
		NodePtr z = TNULL; // найденный узел
		NodePtr x, y; // x - узел, который встанет на место найденного, у - буфер
		while (node != TNULL) { // пока не дойдём до листа
			if (node->data == key) { // нашли узел
				z = node;
			}

			if (node->data <= key) {
				node = node->right;
			}
			else {
				node = node->left;
			}
		}

		if (z == TNULL) {
			cout << "Такого значения в дереве не существует" << endl;
			return;
		}

		y = z; // буфер
		int y_original_color = y->color;
		if (z->left == TNULL) {
			x = z->right;
			rbTransplant(z, z->right); // если у узла нет левого реб., меняем узел на правого ребёнка
		}
		else if (z->right == TNULL) {
			x = z->left;
			rbTransplant(z, z->left); // если у узла нет правого реб., меняем узел на правого ребёнка
		}
		else { // есть оба ребёнка
			y = minimum(z->right); // минимальный правый элемент (им заменим узел)
			// можно было менять на максимальный левый
			y_original_color = y->color;
			x = y->right; // буфер
			if (y->parent == z) { // если минимальный узел = правый ребёнок удаляемого
				x->parent = y;
			}
			else {
				rbTransplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}

			rbTransplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		delete z; // освобождение памяти
		if (y_original_color == 0) {
			// балансировка дерева
			fixDelete(x);
		}
	}

	// балансировка дерева
	void fixInsert(NodePtr k) {
		NodePtr u; // дядя
		while (k->parent->color == 1) { // 1 = RED
			if (k->parent == k->parent->parent->right) { // ищем дядю
				u = k->parent->parent->left; // дядя слева
				if (u->color == 1) {
					// второй случай
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				}
				else {
					// 4 или 5 случай
					if (k == k->parent->left) { // 4 случай левый зиг заг (4 случай переходит в пятый)
						k = k->parent;
						rightRotate(k);
					}
					// 5 случай
					k->parent->color = 0;
					k->parent->parent->color = 1;
					leftRotate(k->parent->parent);
				}
			}
			else {
				u = k->parent->parent->right; // дядя справа

				if (u->color == 1) {
					// второй случай обратный
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				}
				else {
					// 4 или 5 случай
					if (k == k->parent->right) { //4 случай правый зиг заг (4 случай переходит в пятый)
						k = k->parent;
						leftRotate(k);
					}
					// 5 случай
					k->parent->color = 0;
					k->parent->parent->color = 1;
					rightRotate(k->parent->parent);
				}
			}
			if (k == root) {
				break;
			}
		}
		root->color = 0;
	}

	

public:
	RBTree() { // конструктор класса RBTree, в нём инициализируется заглушка
		TNULL = new Node;
		TNULL->color = 0;
		TNULL->left = nullptr;
		TNULL->right = nullptr;
		root = TNULL;
	}

	// Pre-Order traversal
	// Node->Left Subtree->Right Subtree
	void preorder() {
		preOrderHelper(this->root);
	}

	// In-Order traversal
	// Left Subtree -> Node -> Right Subtree
	void inorder() {
		inOrderHelper(this->root);
	}

	// Post-Order traversal
	// Left Subtree -> Right Subtree -> Node
	void postorder() {
		postOrderHelper(this->root);
	}

	// search the tree for the key k
	// and return the corresponding node
	NodePtr searchTree(int k) {
		NodePtr node;
		node = searchTreeHelper(this->root, k);
		if (node == TNULL) printf("Узел %d не найден\n", k);
		else printf("Узел %d найден\n", k);
		return node;
	}

	// находит узел с минимальным значением
	NodePtr minimum(NodePtr node) {
		while (node->left != TNULL) {
			node = node->left;
		}
		return node;
	}

	// find the node with the maximum key
	NodePtr maximum(NodePtr node) {
		while (node->right != TNULL) {
			node = node->right;
		}
		return node;
	}

	// find the successor of a given node
	NodePtr successor(NodePtr x) {
		// if the right subtree is not null,
		// the successor is the leftmost node in the
		// right subtree
		if (x->right != TNULL) {
			return minimum(x->right);
		}

		// else it is the lowest ancestor of x whose
		// left child is also an ancestor of x.
		NodePtr y = x->parent;
		while (y != TNULL && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	// find the predecessor of a given node
	NodePtr predecessor(NodePtr x) {
		// if the left subtree is not null,
		// the predecessor is the rightmost node in the 
		// left subtree
		if (x->left != TNULL) {
			return maximum(x->left);
		}

		NodePtr y = x->parent;
		while (y != TNULL && x == y->left) {
			x = y;
			y = y->parent;
		}

		return y;
	}

	// поворачивает налево относительно х
	void leftRotate(NodePtr x) {
		NodePtr y = x->right; // буфер, запоминаем правого ребёнка
		x->right = y->left; // если у буфера есть дети
		if (y->left != TNULL) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		// обмен родителями
		if (x->parent == nullptr) { // если х - корень
			this->root = y;
		}
		else if (x == x->parent->left) { // если х левый ребёнок
			x->parent->left = y;
		}
		else {// если х правый ребёнок
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	// поворачивает направо относительно х
	void rightRotate(NodePtr x) {
		NodePtr y = x->left;
		x->left = y->right;
		if (y->right != TNULL) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->right) {
			x->parent->right = y;
		}
		else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	// вставляет значение в дерево на правильную позицию
	// после балансирует дерево
	void insert(int key) {
		NodePtr node = new Node;
		node->parent = nullptr;
		node->data = key;
		node->left = TNULL; // заглушка
		node->right = TNULL; // заглушка
		node->color = 1; // новый узел должен быть красным, т.к. это ломает меньше правил

		NodePtr y = nullptr; // родитель узла(nullptr эквивалентно null в Java)
		NodePtr x = this->root; // текущий элемент

		while (x != TNULL) { // пока не встретим листья (бинарный поиск)
			y = x;
			if (node->data < x->data) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}
		// после этой операции х указывает на заглушку в место, куда должен встать новый элемент
		// y родитель x
		node->parent = y;
		if (y == nullptr) {
			root = node; // если нет родителя, то нет никаких узлов до нового
		}
		// присваиваем родителю ссылку на новый элемент
		else if (node->data < y->data) {
			y->left = node;
		}
		else {
			y->right = node;
		}

		// если новый элемент - корень, возврат
		if (node->parent == nullptr) {
			node->color = 0; // 1 случай
			return;
		}

		// если дед ноль - возрат
		if (node->parent->parent == nullptr) {
			return;
		}

		// балансировка дерева
		fixInsert(node);
	}

	NodePtr getRoot() {
		return this->root;
	}

	// удаляет элемент из дерева
	void deleteNode(int data) {
		deleteNodeHelper(this->root, data);
	}

public:
	// Остальные методы класса...

	// Публичный метод для вызова вывода дерева в консоль
	void printTree() {
		NodePtr rot = root;
		stack<NodePtr> globalStack;
		globalStack.push(rot);
		int gaps = 32;
		bool isRowEmpty = false;
		string separator = "-----------------------------------------------------------------";
		cout << separator << endl;
		while (!isRowEmpty) {
			stack<NodePtr> localStack;
			isRowEmpty = true;

			for (int j = 0; j < gaps; j++)
				cout << ' ';
			while (!globalStack.empty()) {
				NodePtr temp = globalStack.top();
				globalStack.pop();
				if (temp != nullptr) {
					cout << temp->data << (temp->color == 0 ? "b" : "r");
					localStack.push(temp->left);
					localStack.push(temp->right);
					if (temp->left != nullptr || temp->right != nullptr)
						isRowEmpty = false;
				}
				else {
					cout << "__";
					localStack.push(nullptr);
					localStack.push(nullptr);
				}
				for (int j = 0; j < gaps * 2 - 2; j++)
					cout << ' ';
			}
			cout << endl;
			gaps /= 2;
			while (!localStack.empty())
				globalStack.push(localStack.top());
		}
		cout << separator << endl;
	}
	// рисует дерево на экран
	void prettyPrint() {
		if (root) {
			printHelper(this->root, "", true);
		}
	}
	void printHelper(NodePtr root, string indent, bool last) { // indent - отступ
		// рисует дерево на экран
		if (root != TNULL) {
			cout << indent;
			if (last) {
				cout << "R----";
				indent += "     ";
			}
			else {
				cout << "L----";
				indent += "|    ";
			}

			string sColor = root->color ? "RED" : "BLACK";
			cout << root->data << "(" << sColor << ")" << endl;
			printHelper(root->left, indent, false);
			printHelper(root->right, indent, true);
		}
		// cout<<root->left->data<<endl;
	}
};
int main()
{
	setlocale(LC_ALL, "Rus");
	printf("Введите кол-во строк: ");
	scanf("%d", &m);
	printf("Введите кол-во столбцов: ");
	scanf("%d", &n);
	vector<vector<int>> arrays(m, vector<int>(n));
	// заполняем массив случайными числами  
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			arrays[i][j] = rand() % 100 - 50;
		}
	}
	printMatrix(arrays);
	RBTree bst;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			bst.insert(arrays[i][j]);
		}
	}
	bst.prettyPrint();
	for (int i = 0; i < m; i += 2) {
		for (int j = 0; j < n; j += 2) {
			NodePtr node;
			node = bst.searchTree(arrays[i][j]);
		}
	}
	bst.searchTree(0);
	return 0;
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
