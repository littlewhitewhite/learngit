// 返回s中第一次出现的位置索引
// 引用形参occurs负责统计c出现的总次数
string::size_type find_char(const string &s, char c, string::size_type &occurs)
{
	auto ret = s.size();
	occurs = 0;
	for(decltype(ret) i = 0; i != s.size(); ++i) {
		if(s[i] == c) {
			if(ret == s.size())
				ret = i;
			++occurs;
		}
	}
	return ret;
}

/*
 * 和其他初始化过程一样，当用实参初始化形参时会忽略掉顶层const。当形参有顶层const时，传给它常量对象或非常量对象
 * 都是可以的。
 
 * 指针或引用形参与const：  我们可以使用非常量初始化一个底层const对象，但是反过来不行。同时一个普通的引用必须用
 * 同类型的对象初始化。
 
 * 尽量使用常量引用：使用引用而非常量引用也会极大地限制函数所能接收的实参类型。就像我们不能把const对象，
 * 字面值或者需要类型转换的对象传递给普通的引用形参。
*/


/*
 * 编译器分两步处理类：首先编译成员的声明，然后才轮到成员函数体。因此，成员函数体可以随意使用类中
 * 的其他成员而无需在意这些成员出现的次序。
 
 * 一般来说，执行输出任务的函数应该尽量减少对格式的控制，这样可以确保由用户代码来决定是否换行。
 
 * 构造函数不能被声明成const的，当我们创建类的一个const对象时，直到构造函数完成初始化过程对象才能真正取得
 *其常量属性。因此，构造函数在const对象的构造过程中可以向其写值。
 
 
 * 类封装有两个重要的优点： 确保用户代码不会无意间破坏封装对象的状态。被封装的类的具体实现细节可以随时改变，而无需
  调整用户级别的代码。
 
 
 
 * 一个可变数据成员mutable date member永远不会是const， 即使它是const对象的成员。因此，一个const成员函数可以改变一个可变成员的值。
 *     
*/
class Screen {
public:
	Screen() = default;
	void some_member() const 
	{
		++access_ctr;		// record the times called by member function
	}
	
	const Screen &display(std::ostream &os) const
	{
		do_display(os);		// pass const Screen& to do_display()
		return *thie;
	}
	Screen &display(std::ostream &os)
	{
		do_display(os);		// pass Screen& to do_display(); 并且调用do_display()时非常量this隐式的转换为常量this
		return *this;		// 因为返回的是*this，所以需要有display的重载版本
	}
private:
	std::string contents;
	mutable size_type access_ctr; // mutable data member, can be modified by const member function
	void do_display(std::ostream &os) const {os << contents;}
};

/*
 * 1）关于do_display（）函数在类内部，所以是内联函数inline，所以这个额外的函数调用不会增加任何开销。
 * 2）我们写函数一个基本的愿望是避免在多处使用同样的代码。
 * 3）我们预期随着类的规模发展，display函数有可能变得更加复杂，此时，把相应的操作卸载一处而非两处的作用就比较明显了。
*/

/*
 * 类还可以把其他的类定义成友元，也可以把其他类的成员函数定义成友元。
 * 如果一个类声明了友元类，则这个友元类的成员函数可以访问此类包括非公有成员在内的所有成员。
 
 
 * 每个类都会定义它自己的作用域。在类的作用域之外，普通的数据和函数成员只能由对象，引用或者指针使用成员访问运算符来访问。
 * 对于类类型成员则使用作用域运算符访问。
 
 * 委托构造函数的执行过程以及初始值列表的执行过程和顺序
*/



/***********************************************************************************************************************
 * 当对象被默认初始化或值初始化时自动执行默认构造函数。
 * 默认初始化在一下情况下发生：1）当我们在块作用域内不使用任何初始值定义一个非静态变量或数组时
 *							   2）当一个类本身含有类类型的成员且使用合成的默认构造函数时
 *							   3）当类类型的成员没有在构造函数初始值列表中被初始化时
 *
 *
 * 值初始化在以下情况下发生： 1）在数组初始化的过程中如果我们提供的初始值数量少于数组的大小时
 *							  2）当我们不使用初始值定义一个静态局部变量时
 *							  3）当我们通过书写形如T()的表达式显式地请求初始化时
***********************************************************************************************************************/


/*
 * 类的静态成员存在于任何对象之外，对象中不包含任何与静态数据成员有关的数据。
 * 静态成员函数也不与任何对象绑定在一起，他们不包含this指针。作为结果，
 * 静态成员函数不能声明成const的，而且我们也不能在static函数体内使用this指针。
 *
 * 和其他成员的定义一样，类的静态数据成员的定义也能使用类的私有成员。
 * 
 
 * 要使用内联函数的特性，需要在函数声明前和定义前加上关键字inline。
 * 通常做法是省略函数原型，将整个定义（即函数头和所有函数代码）放在本应提供原型的地方。
**/

/*
 * 拷贝和移动构造函数定义了当用同类型的另一个对象初始化本对象时做什么。
 
 *拷贝初始化和直接初始化的差异：当我们使用直接初始化时，我们实际上时要求编译器使用普通的函数匹配来选择与我们提供的参数最匹配的构造函数。
 *当我们使用拷贝初始化时，我们要求编译器将右侧运算对象拷贝到正在创建的对象中，如果需要的话还要进行类型转换。
 *拷贝初始化通常使用拷贝构造函数来完成。
 *拷贝初始化不仅在我们用=定义变量时发生，而且1）讲一个对象作为实参传递给一个非引用类型的形参
	* 2）从一个返回类型为非引用类型的函数返回一个对象
	* 3）用花括号列表初始化一个数组中的元素或一个聚合类中的成员
*/


/*
 * 某些运算符，包括赋值运算符，必须定义为成员函数。
 
 
 *在一个析构函数中，首先执行函数体，然后销毁成员。成员按初始化顺序的逆序销毁。
 *通常，析构函数释放对象在生存期分配到的所有资源。
 
 *无论何时一个对象呗销毁，就会自动调用其析构函数：1）变量在离开其作用域时被销毁
 2）当一个对象呗销毁时，其成员被销毁
 3）容器（无论是标准库容器还是数组）被销毁时，其元素被销毁
 4）对于动态分配的对象，当对指向它的指针应用delete运算符时被销毁。
 5）对于临时对象，当创建它的完整表达式结束时被销毁。
 
 *由于析构函数自动运行，我们的程序可以按需要分配资源，而无需担心何时释放这些资源。
*/


{
	Sales_data *p = new Sales_data;
	auto p2 = make_shared<Sales_data>();
	Sales_data item(*p);
	vector<Sales_data> vec;
	vec.push_back(*p2);
	delete p;
}

/*
 * 三五法则中：需要析构函数的类也需要拷贝和赋值操作。一般当我们决定一个类是否需要定义它自己版本的拷贝控制成员时，
 一个基本原则是首先确定这个类是否需要一个析构函数，通常对析构函数的需求要比对拷贝构造函数或赋值运算符的需求更为明显。
 如果这个类需要一个析构函数，我们几乎可以肯定它也需要一个拷贝构造函数和一个拷贝赋值运算符。
 
 第二个原则：如果一个类需要一个拷贝构造函数，几乎可以肯定它也需要一个拷贝赋值运算符。反之亦然。 
 但是，无论是否需要拷贝构造函数还是需要拷贝赋值运算符都不必意味着也需要析构函数。
 
 当我们在类内用=default修饰成员的声明时，合成的函数将隐式的声明为内联的。如果我们不希望合成的成员是内联函数，应该只对
 成员的类外定义使用=default。
 
 
 
 在新标准发布之前，类是通过将其拷贝构造函数和拷贝赋值运算符声明为private的来阻止拷贝：
 
*/

class PrivateCopy {
	// 拷贝控制成员时private的所以普通类用户无法访问。
	PrivateCopy(const PrivateCopy &);
	PrivateCopy &operator=(const PrivateCopy &);
public:
	PrivateCopy() = default;
	~PrivateCopy();
	/*
	*由于析构函数时public的，用户可以定义PrivateCopy类型的对象。但是由于拷贝构造函数和拷贝赋值运算符时private的，
	*用户代码不能拷贝这个类型的对象。但是，友元和成员函数仍旧可以拷贝对象，为了阻止成员函数和友元进行拷贝，
	*我们将这些拷贝控制成员声明为private的，但并不定义他们。
	*声明但不定义一个成员函数是合法的。试图访问一个未定义的成员将导致链接错误。通过声明但是不定义private的拷贝构造函数。
	*试图拷贝对象的用户代码将在编译阶段错误，成员函数或友元函数中的拷贝操作将会导致连接时错误。
	*/
};


/* 类值版本的HasPtr 
 
 *除了定义拷贝控制成员，管理资源的类通常还定义一个名为swap的函数。
 
 如果一个类定义了自己的swap，那么算法将使用类自定义版本。否则，算法将使用标准库定义的swap。
 
 可以在我们的类上自定义一个版本swap来重载swap的默认行为。
*/
class HasPtr {
public:
	HasPtr(const std::string &s = std::string()) :
		ps(new std::string(s)), i(0) {}
	HasPtr(const HasPtr &p) :
		ps(new std::string(*p.ps)), i(p.i) {}
	// 赋值运算符通常组合了析构函数和构造函数的操作。非常重要的是这些操作是以正确的顺序执行的，
	// 即使将一个对象赋予他自身，也保证正确。而且，如果可能，我们编写的赋值运算符还应该是异常
	// 安全的--当异常发生时能将左侧运算对象置于一个有意义的状态
	HasPtr &operator=(const HasPtr &);	// non inline function
	~HasPtr() {delete ps;}
	
	friend void swap(HasPtr &lhs, HasPtr &rhs);	// 参数不能是const的，因为需要更改内部数据成员
private:
	std::string *ps;
	int i;
};
HasPtr &HasPtr::operator=(const HasPtr &rhs)
{
	auto newp = new std::string(*rhs.ps);
	delete ps;
	ps = newp;
	i = rhs.i;
	return *this;
}

// 与拷贝控制成员不同，swap并不是必要的。由于swap的存在就是为了优化代码，我们将其声明为inline函数。//
// swap的函数体对给定对象的每个数据成员调用swap。
inline
void swap(HasPtr &lhs, HasPtr &rhs)
{
	using std::swap;
	swap(lhs.ps, rhs.ps);
	swap(lhs.i, rhs.i);
}


/**************************************************************************************************************
* 当编写赋值运算符时，有两点需要记住 1）如果将一个对象赋予他自身，赋值运算符必须能够正确工作
*	2）大多数赋值运算符组合了析构函数和拷贝构造函数的功能
**************************************************************************************************************/

/*
 *定义一个使用引用计数的类似指针的类
*/
class HasPtr {
public:
	HasPtr(const std::string &s = std::string()) :
		ps(new std::string(s)), i(0), use(new std::size_t(1)) {}
	HasPtr(const HasPtr &p) : 
		ps(p.ps), i(p.i), use(p.use) {++*use;}
	HasPtr &operator=(const HasPtr&);
	~HasPtr();
private:
	std::string *ps;
	int i;
	std::size_t use;
};
HasPtr & HasPtr::operator=(const HasPtr &rhs) 
{
	++*rhs.use;		// 先递增右侧use可以避免自赋值
	if(--*use == 0) {
		delete ps;
		delete use;
	}
	use = rhs.use;
	ps = rhs.ps;
	i = rhs.i;
	return *this;
}
~HasPtr()
{
	if(--*use == 0) {
		delete ps;
		delete use;
	}
}





/*
 *继承和动态绑定对程序的编写有两方面的影响：一是我们可以更容易的定义与其他类相似但不完全相同的新类；
											二是在使用这些彼此相似的类编写程序时，我们可以在一定程度上忽略掉他们的区别。

 *基类负责定义在层次关系中所有类共同拥有的成员，而每个派生类定义各自特有的成员。
 
 在C++语言中，基类将类型相关的函数与派生类不做改变直接继承的函数区分对待。对于某些函数，基类希望它的派生类各自定义适合自身的版本。
 此时基类就将这些函数声明成虚函数virtual function。派生类必须在其内部对所有重新定义的虚函数进行声明。
 
 在c++语言中，当我们使用基类的指针或引用调用一个虚函数时将发生动态绑定。
 当我们使用指针或引用调用虚函数时，该调用将被动态绑定。根据引用或指针所绑定的对象类型不同，
 该调用可能执行基类的版本，也可能执行某个派生类的版本。
 
 如果基类把一个函数声明成虚函数，则该函数在派生类中隐式的也是虚函数。
 
 
 
 
 * 派生列表中用到的访问说明符的作用是控制派生类从基类继承而来的成员是否对派生类的用户可见。
 如果一个派生时共有的，则基类的共有成员也是派生类接口的组成部分。
 
 
 *派生类经常（但不总是）覆盖它继承的虚函数。如果派生类没有覆盖其基类中的某个虚函数，则该虚函数的行为类似于其他的普通成员，
 派生类会直接继承在其基类中的版本。派生类可以在他覆盖的函数前使用virtual关键字，但不是非得这么做。
 
 派生类到基类的类型转换。基类指针指向派生类对象的基类部分。和其他类型转换一样，编译器会隐式的执行派生类到基类的转换。
 *
 
 除非我们特别之处，否则派生类对象的基类部分会像数据成员一样执行默认初始化。如果想使用其他的基类构造函数，
 我们需要以类名加圆括号内的实参列表的形式为构造函数提供初始值。这些实参将帮助编译器决定到底应该选用那个构造函数来初始化派生类对象的基类部分。
 首先初始化基类的部分，然后按照声明的顺序依次初始化派生类的成员。
 
 
 
 必须明确一点：每个类负责定义各自的接口。要想与类的对象交互必须使用该类的接口，即使这个对象是派生类的基类部分也是如此。
 
 
 
 C++11提供了一种防止继承发生的方法，即在基类名后跟一个关键字final。
 
 在c++中，当我们使用基类的引用或指针调用一个虚成员函数时会执行动态绑定。因为我们直到运行时才知道到底调用了哪个版本的虚函数，
 所以所有虚函数都必须有定义。通常情况下，如果我们不使用某个函数，则无须为该函数提供定义。但是我们必须为每一个虚函数都提
 供定义，而不管他是否被用到了，这是因为连编译器也无法确定到底会使用哪个虚函数。
 
 一个派生类的函数如果覆盖了某个继承而来的虚函数，则它的形参类型必须与被他覆盖的基类函数完全一致。
 同样，派生类中虚函数的返回类型也必须与基类函数匹配。
 派生类如果定义了一个函数与基类中虚函数的名字相同但是形参列表不同，这仍是合法的行为。
 编译器将认为新定义的这个函数与基类中原有的函数时相互独立的。这时派生类的函数并没有覆盖掉基类中的版本。
 就实际的编程习惯而言，这种声明往往意味着发生了错误，因为我们可能原本希望派生类能覆盖掉基类中的虚函数，但是吧形参列表弄错了。
 C++11的机制：如果我们使用override标记了某个函数，但该函数并没有覆盖已存在的虚函数，此时编译器将报错。
 
 
 
 在某些情况下，我们希望对虚函数的调用不要进行动态绑定，而是强迫其执行虚函数的某个特定版本。使用作用域运算符可以实现这一目的。
 eg:    double undiscounted = baseP->Quote::net_price(42);			使用了作用域Quote
 
 我们还能把某个函数指定为final，如果我们已经把函数定义成final了，则之后任何尝试覆盖该函数的操作都将引发错误。
 
 
 除非我们特别指出，否则派生类对象的基类部分会像数据成员一样执行默认初始化。
**/


/*
含有纯虚函数的类是抽象基类。抽象基类负责定义接口，而后续的其他类可以覆盖该接口。我们不能直接创建一个抽象基类的对象。



每个类分别控制自己的成员初始化过程，与之类似，每个类还分别控制着其成员对于派生类来说是否可访问accessible。

一个类使用protected关键字来声明哪些它希望派生类分享但是不想被公共访问使用的成员。protected说明符可以看做时public和private中和后的产物：
	**和私有成员类似，受保护的成员对于类的用户来说不可访问。
	**和公有成员类似，受保护的成员对于派生类的成员和友元来说是可以访问的。
	*****派生类的成员或友元只能通过派生类对象来访问基类的受保护成员。*****
	
	
	
	
	某个类对其继承而来的成员的访问权限受到两个因素影响：一是在基类中该成员的访问说明符，
	二是在派生类的派生列表中的访问说明符。
	
	派生类访问说明符的目的是控制派生类用户对于基类成员的访问权限。
	如果继承是公有的，则成员将遵循其原有的访问说明符。
	派生是私有的，则基类的成员在派生类中是私有的。
	派生是保护的，则基类的所有公有成员和保护成员在新定义的类中都是受保护的。
	
	
	
	
	和其他类一样，基类应该将其接口声明为公有的，同时将属于实现的部分分为两组：一组可供派生类访问，另一组只能由基类及基类的友元访问。
	对于前者应该声明为受保护的，这样派生类就能在实现自己的功能时使用基类的这些操作和数据。后者应该声明为私有的。
	
	在C++语言中，当我们使用基类的引用或指针调用一个虚函数时将发生动态绑定。
	如果一个派生是公有的，则基类的公有成员也是派生类接口的组成部分。
	
	
	
	
*/



/*
Complex *p = new  Complex(1, 2);	如果不释放，会造成内存泄漏，就是new指向的内存还在，但是控制它的指针p已经死亡，已经不能控制那块分配的内存。
分为3步骤：分配内存，类型强制转换， 调用构造函数（将p指针作为this指针传入构造函数中）
*/




/*
is a 关系和has a关系。  student类有string类表示姓名，valarray类表示一组成绩。如果 class Student : public string , public vararray<double> {  };即Student多重继承
string类和vararray<double>类，那么不符合is a关系。应该如下：
class Student 
{
private:
	string name;
	vararray<double> scores;
};
上述将数据成员声明为私有的，意味着student类的成员函数可以使用string和vararray的公有接口来访问和修改name和scores对象，但是在student类外不能访问name和scores的公有成员函数。
对于这种情况，通常被描述为student类获得了其成员对象的实现，但没有继承接口。

使用公有继承时，类可以继承接口，也可以继承实现。获得接口是is  a 关系的组成部分。
而使用组合。类可以获得实现，但不能获得接口。不继承接口是has a 关系的组成部分。

对于has a关系来说，类对象不能自动获得被包含对象的接口是一件好事。例如 string类将+运算符冲仔尾将两个字符串连接起来，但是从概念上说，将两个student对象连接起来是
没有意义的。这也是这里不使用公有继承的原因之一。
被包含对象的接口不是公有的，但可以在类方法中使用它。
















私有继承是C++另外一种实现has a关系的途径。使用私有继承，基类的公有成员和保护成员将成为派生类的私有成员。这意味着基类方法将不会成为派生对象公有接口的一部分，但是
可以在派生类的成员函数中使用它们。这种不完全继承正是has a关系的一部分。使用私有继承，类将继承实现。
例如如果从string类私有派生出Student类，后者将有一个string类组件，可以用于保存字符串。另外student方法可以使用string方法来访问string组件。
包含将对象作为一个命名的成员对象添加到类中，而私有继承将对象作为一个未被命名的组件添加到类中。因此，私有继承提供的特性与包含相同：即获得实现，但是在类外不获得接口。




*/

// Student.h -- defining a Student class using private inheritance
#ifndef _STUDENT_
#define _STUDENT_

using namespace std;

class Student : private string, private vararray<double>
{
	friend ostream &opetator<<(ostream &os, const Student &s);
public:

	Student(const char *str, const double *scores, int n) :
		string(str), ArrayDb(scores, n) { }
	Student(ostream &os = cout) : string("Null Student"), ArrayDb() 
		{ os << "default ctor was called." }
	explicit Student(int n) : string("Nuly"), ArrayDb(n) { }
	Student(const string &str, int n) : string(str), ArrayDb(n) { }
	explicit Student(const string &str) : string(str)
		{ cout << "vararray's ctor was called." }
	Student(const string &str, const ArrayDb &arr) : string(str), ArrayDb(arr) { }
	
	
	
	double Average() const
	{
		if( (int counts = ArrayDb::size() ) > 0)
			ArrayDb::sum() / counts;
		else 
			return 0.0;
	}
	
	/*
	 * 使用作用域运损福可以访问基类的方法，但如果要使用基类对象本身呢？？例如Student类的包含版本实现的Name方法通过返回string对象成员name。
	 *但使用私有继承时，该string对象没有名称，答案是使用强制类型转换。
	*/
	const string &Name() const
	{
		return (const string &)*this;	// 该方法返回一个引用，该引用指向用于调用该方法的派生类对象的基类string对象
	}
	
	doubel operator[](int i) const 
	{
		return ArrayDb::operator{}(i);
	}
private:
	typedef vararray<double> ArrayDb;
	ostream &arr_out(ostream &os) const;
};

// this pointer is passed by parameter
ostream &Student::arr_out(ostream &os) const
{
	int i;
	int lim = ArrayDb::size();
	if(lim > 0) {
		for(i = 0; i < lim; ++i) {
			os << ArrayDb::operator[](i) << "";
			if(i % 5 == 4)
				os << endl;
		}
		if(i % 5)
			os << endl;
	}
	
	return os;
}

ostream &operator<<(ostream &os, const Student &s)
{
	// 引用s不会自动转换为string类型的引用。根本原因在于，在私有继承中，未进行显式类型转换的派生类指针或引用无法自动赋值给基类引用或指针。
	
	// 在这个例子中就算是public继承，也必须强制转换，如果不强制转换。会在  os << s << endl;中继续调用operator<<函数，进而无限递归。
	// 并且就算转换，编译器也不知道转换为哪个基类，因为s有可能转换为string基类的引用，也有可能ArrayDb实现了operator<<运算符，进而转换为ArrayDb的引用。
	os << "Scores for " << (const string &)s << ":\n";
	
}


#endif

这个新版使用private继承，而不是包含类对象来实现。  客户代码使用这个类的接口时是始终不变的，所以可以让类的设计人员随意修改而不影响客户。

由于既可以使用包含，也可以使用private继承来建立has-a关系，那么使用哪种？？大多数c++程序员使用包含：首先它易于理解，类声明中包含表示含有对象的显式命名，代码可以
通过对象名来调用公有接口。
使用private继承会显得抽象，尤其是multiple inheritance。另外，包含能够包括多个同类的子对象。如果某个类需要3个string对象，可以使用包含声明3个独立的string成员。而继承
只能使用一个这样的对象（当对象没有名称时，将难以区分。）
当基类中有protected成员时，使用private继承可以在派生类定义中访问保护成员。但是使用包含时不可以在新定义的类中使用保护成员。因为在新定义的类中相当于在外面使用保护成员，
这是不允许的。





/*
类之间的关系：组合，委托delagation，派生



handle/implement设计模式


template method 模式：模板方法模式在一个方法中定义一个算法的框架（骨架），而将一些步骤延迟到子类中。
模板方法使得子类可以在不改变算法结构的情况下，重新定义算法中的某些步骤。

这可以确保算法的结构保持不变，同时由子类提供部分实现。
*/


/*
我们以相同的指令却调用了不同的函数这种性质称为polymorphism，编译器无法再编译时期判断pEmp->computePay（）到底是调用哪一个函数，
必须在执行期才能判断，这称为后期绑定late binding或动态绑定dynamic binding。至于C函数或C++的non-virtual函数，在编译时期就转换为一个
固定的地址调用，这称为前期绑定early binding或静态绑定static binding。

polymorphism的目的，就是要让处理“基类的对象”的程序代码，能够完全无障碍的继续适当处理派生类的对象。


纯虚函数不需要定义其实际操作，它的存在只是为了在派生类中被重新定义，只是为了提供一个多态接口。
只要是拥有纯虚函数的类，就是一种抽象类，它是不能够被实例化（instantiate）的，也就是说，你不能根据他产生一个对象。
*/


#include <iostream>

using std::cout;
using std::endl;

class CObject 
{
public:
	virtual void Serialize() { cout << "CObject::Serialize().\n"; }
};

class CDocument : public CObject
{
public:
	int m_data1;
	void func() 
	{
		cout << "CDocument::func()" << endl;
		Serialize();
	}
	virtual void Serialize() { cout << "CDocument::Serialize()\n"; }
};

class CMyDoc : public CDocument
{
public: 
	int m_date2;
	virtual void Serialize() { cout << "CMyDoc::Serialize()\n"; }
};

int main()
{
	CMyDoc myDoc;
	CMyDoc *pmydoc = new CMyDoc;
	
	myDoc.func();
	
	((CDocument*)&myDoc)->func();
	
	pmydoc->func();
	
	((CDocument)myDoc).func();
	
	return 0;
}

/* 由于static成员函数不需要借助任何对象，就可以被调用执行，所以编译器不会为它暗加上一个this指针。也正因为如此，
static成员函数无法处理类之中的non-static成员变量。

static成员变量并不是因为对象的实现才得以实现的，它本来就存在。只要access level允许，任何函数（包括全局函数，成员函数static或non-static都可以
存取static成员变量。但是如果你希望在产生任何object之前就存取其class的private static成员变量，则必须设计一个static成员函数）

static成员函数没有this参数的这种性质，正是我们的MFC应用程序在准备callback函数时所需要的。
 * 
 * 
*/


/*
 * dynamic_cast运算符是最常用的RTTI组件，它不能回答“指针指向的是哪类对象”这样的问题，
 但能够回答“是否可以安全的将对象的地址赋给特定类型的指针”这样的问题。
 该运算符的用途是，是的能够在类层次结构中进行向上转换（由于is-a关系，派生类是一种基类，这样的类转换时安全的），而不允许其他转换。
*/


/*
C允许在字符串中包含宏参数。 但是字符串中的宏参数不会被真实参数替代。eg：
	#define PSQR(X) printf("The square of X is %d/\n", ((X) * (X)));
	
	PSQR(8)
	结果会显示The square of X is 64;  而不会显示The sqare of 8 is 64.
	
	#号作为一个预处理运算符，可以把记号转换成字符串。例如 如果X是一个宏参数，那么#X就是转换为字符串“X”的形参名。这个过程称为字符串化。
	
	##运算符把两个记号组合成一个记号。
	eg：#define XNAME(x) X##n
	XNAME(4)  就会被替换为X4
	
	
	
	MFC的动态创建对象技术：从输入流或文件中读取对象名，然后创建对象。实现可以同时实现RTTI机制。
	
	
	
	将消息与表格中的元素比较，然后调用对应的处理程序，这种操作我们也称之为消息映射。
	
	
	MFC消息映射机制的具体实现方法是：在每个能接收和处理消息的类中，定义一个消息和消息函数静态对照表，即消息映射表。
	在消息映射表中，消息与对应的消息处理函数指针都是成对出现的。某个类能处理的所有消息及其对应的消息处理函数的地址都
	列在这个类对应的静态表中。当有消息需要处理时，程序只要搜索该消息静态表，查看表中是否含有该消息，就可知道该类能够处理此消息。
	如果能处理该消息，则同样依照静态表能很容易找到并调用对应的消息处理函数。
	
	
	
	
	
	
	
	
	窗口销毁时，与之对应的c++窗口类对象销毁与否，要看其生命周期是否结束。但c++窗口类对象销毁时，与之相关的窗口也将销毁，因为
	他们之间的纽带（m_hwnd）已经断了。另外，窗口也是一种资源，他也占据内存。这样，在c++窗口类对象析构时，也需要回收相关的
	窗口资源，即销毁这个窗口。
*/

#define PSQR(X) printf("The square of " #X " is %d.\n", ((X) * (X));




void download(const char *Url,const char *save_as)/*将Url指向的地址的文件下载到save_as指向的本地文件*/  
{  
	byte Temp[MAXBLOCKSIZE];  
	ULONG Number = 1;  
 
	FILE *stream;  
	HINTERNET hSession = InternetOpen("RookIE/1.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);  
	if (hSession != NULL)  
	{  
		HINTERNET handle2 = InternetOpenUrl(hSession, Url, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);  
		if (handle2 != NULL)  
		{  
 
 
			if( (stream = fopen( save_as, "wb" )) != NULL )  
			{  
				while (Number > 0)  
				{  
					InternetReadFile(handle2, Temp, MAXBLOCKSIZE - 1, &Number);  
 
					fwrite(Temp, sizeof (char), Number , stream);  
				}  
				fclose( stream );  
			}  
 
			InternetCloseHandle(handle2);  
			handle2 = NULL;  
		}  
		InternetCloseHandle(hSession);  
		hSession = NULL;  
	}  
}

/*
各个中断源如何向cpu提出中断请求    中断请求标记触发器
多个中断源同时提出 如何响应			中断源的优先级 用中断判优逻辑（分散在中断接口中或在cpu中）
中断服务程序入口地址的查询       硬件  中断向量
中断响应  在什么时间响应中断
在单重中断中 在中断服务程序中不允许中断  （硬件关中断  即中断允许出夫妻EINT失能）
保护现场和恢复现场
*/


//BEGIN_MESSAGE_MAP(CMyWnd, CFrameWnd)
//
//	ON_WM_LBUTTONDOWN()
//
//END_MESSAGE_MAP()



void CMyWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	UINT xpos = point.x;
	UINT ypos = point.y;
	UINT flags = nFlags;
	CString tmp;
	tmp.Format(_T("%d %d %d\n"), flags, xpos, ypos);
	CFrameWnd::OnLButtonDown(nFlags, point);
}

/*
头文件stdexcept定义了其他几个异常类。该文件定义了logic_error和runtime_error类，他们都是以公有方式从exception类派生而来的。
这些类的构造函数都接收一个string对象作为参数，该参数提供了方法what（）以C风格字符串方式返回的字符数据。
这两个新类被用作两个派生类系列的基类。异常类系列logic_error描述了典型的逻辑错误。总体而言，通过合理的编程可以避免这种错误，但实际上
这些错误还是可能发生的，每个类的名称指出了它用于报告的错误类型。
domain_error
invalid_argument
length_error
out_of_bounds



接下来 runtime_error异常系列描述了可能在运行期间发生但难以预计和防范的错误。每个类的名称指出了它用于报告的错误类型。
range_error
overflow_error
underflow_error

注意catch块的捕捉的异常类的顺序问题：派生类放在前面，基类放在后面能统一处理所有以此基类派生出来的任何继承类。



对于使用new导致的内存分配问题，c++最新处理方式是让new引发bad_alloc异常。头文件new包含bad_alloc类的声明，他是从exception类公有派生而来的。但是在以前，当
无法分配的内存量时，通过返回一个空指针代替。
很多代码都是在new在失败时返回空指针时编写的。为处理new的变化，有些编译器提供了一个标记开关，让用户选择所需的行为。当前c++标准提供了一种在失败时返回空指针的new，
用法如下：
pb = new (std::nothrow) Big[10000];
if(pb == 0) {
	cout << "Could not allocate memory.\n";
	exit(EXIT_FAILURE);
}

*/




















