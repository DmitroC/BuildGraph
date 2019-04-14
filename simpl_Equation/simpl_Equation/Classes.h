#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
const int const size_w[2]{ 1000,1000 };
const int const half_size_x = size_w[0] >> 1;
const int const half_size_y = size_w[1] >> 1;
void strcpy_c(char *when, char *source, int max);
struct cash
{
	cash() {};
	cash(int i, int val)
	{
		id = i;
		valuable = val;
	}
	cash(const cash&s) { id = s.id; valuable = s.valuable; };
	int id;  //idenficator
	double valuable;  // than exchange
};
double search_cash(int id,cash*s,int size_c); //search and return valuable
class ABC_variable
{
protected:
	ABC_variable(int id)
	{
		ident = id;
		qw = 1;
	}
	ABC_variable(int id,int qw)
	{
		ident = id;
		this->qw = qw;
	}
	int ident; //code or znak
	double qw;
	virtual ~ABC_variable() {};
public:
	void set_qw(double q) { this->qw = q; };
	void set_ident(int id) { ident = id; };
};
class usu_variable :ABC_variable
{
	int pow_v;
public:
	usu_variable():ABC_variable(0) {};
	usu_variable(int ident, int pow) :ABC_variable(ident),pow_v(pow) {};
	usu_variable(int ident, int pow, double qw) :ABC_variable(ident, qw),pow_v(pow) {};
	void inilisated(int ident, int pow);
	void inilisated(int ident, int pow, double qw);
	bool operator+(usu_variable& p);
	bool operator-(usu_variable& p);
	bool operator*(usu_variable& p);
	bool operator/(usu_variable& p);
	bool operator*(double n);
	bool operator/(double n);
	void operator=(usu_variable p);
	template<typename T>
	double operator()(T x) { return get_value(x); };
	template<typename T>
	double get_value(T x)
	{
		return pow(x, pow_v) * qw;
	}
	int id() { return ident; };
};
struct number
{
	bool operator*(number &s);  // возвращает true если умножение успешно(+присвоено значение)
	bool operator/(number &s);  // возвращает true если деление успешно(+присвоено значение)
	number& operator=(number s);
	bool empty1();
	bool empty2();
	double n;  // if know valuable(number in double)
	usu_variable *us;  // if unknow valuable
	number *other;  //if adress to other element
};
struct garbage_collector{
	garbage_collector() {};
	garbage_collector(number*s, number*w) { addres = s; whom = w; };
	number*addres;
	number*whom;
};
struct vec_g :std::vector<garbage_collector>
{
	int ind{};
	vec_g() :std::vector<garbage_collector>() {};
	vec_g(int qw);
	void resize(int qw);
	inline void cl();
	garbage_collector& operator[](int ind);
	void put(garbage_collector);
	void set_a_clean();
};
class p_variable  //with power = x
{
public:
};
class DE  //solver equation
{
	char *t;
	char *map;
	std::vector<usu_variable>unknow_v; 
	std::vector<number>nums;
	vec_g *g_c;
	int index_v; //qw unknow variables
	std::vector<number>read();  // читает символы из строки , и возвращает неизвестные переменные и значения
	double buff(const int s[], std::vector<double>&c, int ed);
	void def(char *t);    //define operation
	char* s_op(char *t);  //search operatoing signes and return their
	void perfor(char signs, char *op, int locate, int index);
	void clean_excess_n(); //nums
	void clean_excess_m(); //map
	double abstr(int i, cash *ar, int size_c, std::vector<number> &s);  // ищет элемент под иденфикатором (иначе возвр -89...)
	number* get_other(number*p);
	inline void set_cl(number *&s, std::vector<number>&numers, int i);//clean and set s
protected:
	const char const*get_t() { return t; };
public:
	~DE();
	DE():index_v(0)
	{};
	DE(char *ch):map(nullptr)
	{
		int n = strlen(ch)+1;
		t = new char[n];
		strcpy_s(t, n, ch);
		index_v = 0;
	}
	void simplifi();  // упрощает уравнение
	void set_Nchar(const char *t); //set new char array
	double calcul(cash *ar, int size);
};
class draw_rastr
{
	double changes_x;
	double changes_y;
	double history_x;
	double history_y;
	double Mpl; //must plus
	int qw;
public:
	draw_rastr() :changes_x(-503), changes_y(-503), qw(0), history_x(-503), history_y(-503)
	{};
	bool calcul(double x, double y, double &plus);
	void clear() { changes_x = -503; history_x = -503; changes_y = -503; history_y = -503; };
	double get_Mpl() { return Mpl; };
};
class AIO : DE  //All in on
{
	draw_rastr dr;
	sf::VertexArray v;
	int v_i;// index v
	int diapason[2];//x and y
	void new_point(double x, double y);
	double search_start(cash *arr,int size);
	double start_y; 
	double end_y;
public:
	AIO():DE(),diapason{size_w[0]/10,size_w[1]/10}
	{
		v.setPrimitiveType(sf::Points);
		v.resize(100);
		v_i = 0;
	}
	void show(sf::RenderWindow &w) { w.draw(v); };
	void operator()(const char*t);
	void perform(const char*t);
	virtual ~AIO() {};
	void increase_x(double x);
	void increase_y(double y);
	void set(const char *t){set_Nchar(t);simplifi();}
	int diap_x() { return diapason[0]; }
	int diap_y() { return diapason[1]; }
};
class grid
{
	sf::VertexArray lines;
	sf::Font f;
	std::vector<sf::Text> t;
	void set_position();
	int size_text;
	int qw;
public:
	grid() :qw(10), lines(sf::Lines, qw), size_text(10)
	{
		t.resize(qw);
		f.loadFromFile("FontC.ttf");
		change_size_text(size_text);
	};
	grid(int q);
	void set(float d_x, float d_y);
	void show(sf::RenderWindow &w)const {
		w.draw(lines); 
		for (int i = 0; i < t.size(); i++)
			w.draw(t[i]);
	};
	void set_qw(const int q);
	void change_size_text(const int sc);
	void set_color(sf::Color);
};
std::string d_to_string(double dl, int qw);