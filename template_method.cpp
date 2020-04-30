// template method
// 当我们设计模板方法模式时，我们概述子类：“不要调用我们，我们会调用你“。
// 这个模式很常见是因为对创建框架来说，这个模式很好。由框架控制如何做事情，而由子类（用户）指定框架算法中每个步骤的独立细节。
class AbstractClass {
public:
	void templateMethod()
	{
		boilWater();
		brew();	// 在派生类中重新实现，各个派生类的重新实现不同
		pourInCup();
		addCondiments();
	}
	virtual void brew() = 0;
	virtual void addCondiments() = 0;

	void boilWater()
	{
		cout << "boiling water.\n";
	}

	void pourInCup()
	{
		cout << "pouring water.";
	}
};

class Coffee : public AbstractClass {
public:
	void brew()
	{
		cout << "boiling coffee.\n";
	}
	void addCondiments()
	{
		cout << "add sugar.\n";
	}
};

class Tea : public AbstractClass {
public:
	void brew()
	{
		cout << "boiling tea.\n";
	}
	void addCondiments()
	{
		cout << "add lemon.\n";
	}
};

int main()
{
	Tea myTea;
	myTea.templateMethod();

	Coffee myCoffee;
	myCoffee.templateMethod();

	return 0;
}



CMyDoc derived;
cout << &derived << endl;

CDocument base(derived);	// 派生类初始化基类对象时调用基类的copyctor ，但是默认的copy ctor并没有直接复制虚表指针，而是改变了基类的虚表指针
cout << &base << endl;

CDocument base1(base);		// 基类对象初始化基类对象时调用copy ctor，并且两个基类对象的虚表指针一样。
cout << &base1 << endl;




/*
用户级线程的切换函数yield（）和线程创建函数createThread（）。
*/





