#include "pch.h"
#include "Classes.h"
#include <algorithm>
double search_cash(int id,cash*c, int size_c)
{
	for (int i = 0; i < size_c; i++)
	{
		if (c[i].id == id)
			return c[i].valuable;
	}
	return -858993460;
}
#define numbers std::vector<number>
void DE::simplifi()
{
	nums = read();
	def(t);
}
void usu_variable::inilisated(int ident, int pow)
{
	set_ident(ident);
	set_qw(1);
	pow_v =pow;
}
void usu_variable::inilisated(int ident, int pow,double qw)
{
	set_ident(ident);
	set_qw(qw);
	pow_v = pow;
}
#define clean()\
tochka = 0;\
minus = 1;\

#define check_size_n()\
if(o_sign != 0)\
{\
	index++;\
	int size_n = nums.size();\
if (index >= size_n)\
{\
		size_n <<= 1;\
		nums.resize(size_n);\
}\
}
#define fs (now >= 97 && now <= 122)||(now >= 65 && now <= 90)
numbers DE::read()
{
	int o_sign{};  //sign not appearing number
	int i = 0;
	numbers nums; //numbers or signes
	int index = 0; //index nums
	nums.resize(strlen(t));
	int minus{ 1 };
	std::vector<double>bufer;
	bufer.resize(10);
	int size_b = bufer.size();
	bool tochka{};
	for (; i < strlen(t); i++)
	{
		char now = t[i];
		if (now >= '0' && now <= '9')
		{
			int size_pp[2] = { 0,0 };
			int &j = size_pp[1];
			for (;; i++, j++)
			{
				now = t[i];
				if (j >= size_b)
					bufer.resize(j + 10);
				if (now >= '0' && now <= '9')
				{
					if (!tochka)
						size_pp[0]++;
					bufer[j] = now - '0';
				}
				else if (now == '.' || now == ',')
				{
					bufer[j] = 0.1;
					tochka = 1;
				}
				else break;
			}
			tochka = 0;
			check_size_n();
			nums[index].n = buff(size_pp, bufer, minus);
		}
		else if (now == '-')
		{
			char now = t[i + 1];
			if ((now >= '0' && now <= '9') || (now == '-') || fs)
			{
				minus *= -1;
			}
			else {
				clean(); o_sign++;
			}
		}
		else if (now == ' ')//because faster need
			goto sp;
		else if (fs)
		{
			check_size_n();//в следующую буфер ячейку
			if (index_v >= unknow_v.size())
			{
				unknow_v.resize(unknow_v.size() + 10);
			}
			unknow_v[index_v].inilisated(now,1,1 * minus);
			nums[index].us = &unknow_v[index_v];
			index_v++;
			clean();
			o_sign = 1;
		}
		else
		{
			sp:
			clean();
			o_sign++;
		}
	}
	nums.resize(index+1);
	return nums;
}
void  DE::set_Nchar(const char *ts)
{
	if (t != nullptr)
		delete[]t;
	t = new char[strlen(ts) + 1];
	strcpy_s(t, strlen(ts)+1,ts);
}
double DE::abstr(int i, cash *ar, int size_c, std::vector<number> &s)
{
	double n;
	number*el = get_other(&s[i]);
	if (el->us != nullptr)
	{
		n = search_cash(el->us->id(), ar, size_c);
		if (n == -858993460)
			return -858993460;
		return el->us->get_value(n);
	}
	else return el->n;
}
number* DE::get_other(number*p)
{
	number *s = p;
	while (s->other != nullptr)
	{
		s = s->other;
	}
	return s;
}
double DE::calcul(cash *ar, int size_c)
{
	double mult1;
	double mult2;
	std::vector<number>numers(nums.size());
	numers = nums;
	number *s = nullptr;
	bool was{};
	for (int i = 0; i < strlen(map); i++)  //multiply and divide
	{
		switch (map[i])
		{
		case '*':
			mult1 = abstr(i, ar, size_c,numers);
			mult2 = abstr(i + 1, ar, size_c, numers);
			set_cl(s, numers, i);
			s->n = mult1 * mult2;
			break;
		case '/':
			mult1 = abstr(i, ar, size_c, numers);
			mult2 = abstr(i + 1, ar, size_c, numers);
			set_cl(s, numers, i);
			s->n = mult1 / mult2;
			break;
		}
		was = 1;
	}
	for (int i = 0; i < strlen(map); i++)
	{
		switch (map[i])
		{
		case '+':
			mult1 = abstr(i, ar, size_c, numers);
			mult2 = abstr(i+1, ar, size_c, numers);
			set_cl(s, numers, i);
			s->n = mult1 + mult2;
			break;
		case '-':
			mult1 = abstr(i, ar, size_c, numers);
			mult2 = abstr(i + 1, ar, size_c, numers);
			set_cl(s, numers, i);
			s->n = mult1 - mult2;
			break;
		default:

			break;
		}
		was = 1;
	}
	if (was == 0)
		return abstr(0, ar, size_c, numers);
	return numers[0].n;
}
inline void DE::set_cl(number *&s, numbers& numers, int i)
{
	numers[i].us = nullptr;
	s = get_other(&numers[i]);
	numers[i + 1].other = s;
}
void DE::def(char *t)    //define operation
{
	std::vector<number> si(nums.size());
	char *op = s_op(t);
	{
		int str = strlen(op) + 2;
		map = new char[str];
		strcpy_c(map, op, str - 1);
	}
	vec_g gar_coll(10);
	g_c = &gar_coll;
	int sch = 0;  //перед знаком уже стоит одно число
	bool was[2]{ 0,0 };
	char signs[2] = { '*','/' };
	for (int i = 0,j = 0; i < strlen(op); i++)
	{
		if (op[i] == '*' || op[i] == '/')
		{
			char sign = op[i];
			if (sign == '*') was[0] = 1;
			else was[1] = 1;
			if (was[0] && was[1])  //если было умножени , а стало деление или наоборот
			{
				gar_coll.set_a_clean(); was[0] = 0; was[1] = 0;
			}
			perfor(sign, op, i, sch);
		}
		else 
		{
			if (was != 0)
			{
				gar_coll.set_a_clean();
			}
		}
		sch++;
	}
	clean_excess_n();
	clean_excess_m();
	delete[]op;
}
void DE::perfor(char signs, char *op,int locate,int index)
{
	number * first = &nums[index];
	if (first->empty1())
	{
		if (!first->empty2())
			first = first->other;
		else return;
	}	
	number * last;
	char sign;
	for (int i = locate,j = 1;; i++,j++)
	{
		if (op[i] != signs)
			break;
		last = &nums[index + j];
		if (!last->empty2())
			last = last->other;
		sign = op[i];
		if (!last->empty1())
		{
			if (sign == '*')
			{
				if (*first * (*last))
				{
					nums[index + j].n = -9.2559631349317831;
					nums[index + j].us = nullptr;
					map[i] = ' ';
					g_c->put(garbage_collector(&nums[index + j], &nums[index]));
				}
			}
			else
			{
				if (*first / (*last))
				{
					nums[index + j].n = -9.2559631349317831;
					nums[index + j].us = nullptr;
					map[i] = ' ';
					g_c->put(garbage_collector(&nums[index + j], &nums[index]));
				}
			}
		}
	}
}
DE::~DE()
{
	if (map != nullptr)
		delete[]map;
	if (t != nullptr)
		delete[]t;
}
char* DE::s_op(char *t)
{
	char *op;
	char *c = new char[strlen(t)+1];
	int j = 0;
	for (int i = 0; i < strlen(t); i++)
	{
		if (t[i] == '*' || t[i] == '/' || t[i] == '+')
		{
			sp:
			c[j] = t[i];
			j++;
		}
		else if (t[i] == '-')
		{
			char now = t[i + 1];
			if ((now < '0' || now > '9') && !fs)
				goto sp;
		}
	}
	c[j] = '\0';
	int str = strlen(c) + 2;
	op = new char[str];
	strcpy_c(op, c, str - 1);
	return op;
}
double DE::buff(const int s[], std::vector<double>&c, int ed)//s 
{
	double win{};
	double st{};
	int s2 = s[0]-1;
	int o{};
	if (ed == -1)
		o = 1;
	for (int p = 0; p < s[1] - o; p++, s2--)
	{
		st = pow(10, s2);
		if (c[p] == 0.1)
		{
			s2 = 0;
			continue;
		}
		if (c[p] == -9.2559631349317831)
			break;
		win += st * c[p];
	}
	return win * ed;
}
void DE::clean_excess_n()
{
	for (int i = 0; i < nums.size(); i++)
	{
		if (nums[i].other != nullptr)
		{
			nums.erase(nums.begin() + i);
			i--;
		}
	}
}
void DE::clean_excess_m()
{
	int size_m = strlen(map);
	char *map2 = new char[size_m + 1];
	int j = 0;
	for (int i = 0; i < size_m; i++)
	{
		if (map[i] != ' ')
		{
			map2[j] = map[i];
			j++;
		}
	}
	map2[j] = '\0';
	if (size_m != j)
	{
		char *map3 = new char[j + 2];
		strcpy_c(map3, map2, j + 1);
		delete[]map2;
		map2 = map3;
	}
	delete[]map;
	map = map2;
}
bool usu_variable::operator*(usu_variable& p)
{
	if (this->ident == p.ident)
	{
		this->pow_v += p.pow_v;
		this->qw *= p.qw;
		return true;
	}
	else return false;
}
bool usu_variable::operator+(usu_variable& p)
{
	if (this->ident = p.ident)
	{
		this->qw += p.qw;
		return true;
	}
	return false;
}
bool usu_variable::operator-(usu_variable& p)
{
	if (this->ident = p.ident)
	{
		this->qw -= p.qw;
		return true;
	}
	return false;
}
void usu_variable::operator=(usu_variable p)
{
	pow_v = p.pow_v;
	ident = p.ident;
	qw = p.qw;
}
bool usu_variable::operator/(usu_variable& p)
{
	if (this->ident == p.ident)
	{
		this->qw /= p.qw;
		pow_v -= p.pow_v;
		return true;
	}
	return false;
}
bool usu_variable::operator*(double n)
{
	this->qw *= n;
	return true;
}
bool usu_variable::operator/(double n)
{
	if (n != 0) {
		this->qw /= n;
		return true;
	}
	else return false;
}
void strcpy_c(char *when, char *source, int max)
{
	for (int i = 0; i < max; i++)
	{
		when[i] = source[i];
		if (when[i] == '\0')
			break;
	}
}
bool number::empty1()
{
	if (n == -9.2559631349317831 && us == nullptr)
		return true;
	return false;
}
bool number::empty2()
{
	if (other == nullptr)
		return true;
	return false;
}
number& number::operator=(number s)
{
	n = s.n;
	us = s.us;
	other = s.other;
	return *this;
}
bool number::operator/(number &s)
{
	if (this->us == nullptr)
	{
		if (s.us == nullptr)
		{
			n /= s.n;
		}
		else return false;
	}
	else
	{
		if (s.us == nullptr)
		{
			if (!us->operator/(s.n))
				return false;
		}
		else
		{
			if (!us->operator/(*s.us))
				return false;
		}
	}
	return true;
}
bool number::operator*(number &s)
{
	if (this->us == nullptr)
	{
		if (s.us == nullptr)
		{
			n *= s.n;
		}
		else {
			if (s.us->operator*(n))
			{
				n = 0;
				us = s.us;
			}
			else return false;
		}
	}
	else
	{
		if (s.us == nullptr)
		{
			if (!us->operator*(s.n))
				return false;
		}
		else
		{
			if (!us->operator*(*s.us))
				return false;
		}
	}
	return true;
}
#define v std::vector<garbage_collector>::operator[]
inline void vec_g::cl()
{
	garbage_collector *s;
	for (int i = 0; i < size(); i++)
	{
		s = &v(i);
		s->addres = nullptr;
		s->whom = nullptr;
	}
}
vec_g::vec_g(int qw) :std::vector<garbage_collector>(qw)
{
	cl();
}
void vec_g::resize(int qw)
{
	std::vector<garbage_collector>::resize(qw);
	cl();
}
garbage_collector& vec_g::operator[](int ind)
{
	if (ind >= size())
	{
		resize(ind + 5);
	}
	return v(ind);
}
void vec_g::set_a_clean()
{
	number*e1;
	number*e2;
	for (int i = 0; i < size(); i++)
	{
		e1 = v(i).addres;
		e2 = v(i).whom;
		if (e2 != nullptr && e1 != nullptr)
			e1->other = e2;
		else break;
		v(i).addres = nullptr;
		v(i).whom = nullptr;
	}
	ind = 0;
}
void vec_g::put(garbage_collector g)
{
	if (ind >= size())
		resize(ind + 5);
	v(ind) = g;
	ind++;
}

#undef fs
#undef v
//AIO
#define p size_w[0]/2
#define p1 diapason[0]/2
#define fs2 y >= start_y && y <= end_y
void AIO::perform(const char*t)
{
	double y;
	cash arr[1] = { {120,0} };
	double x = search_start(arr, 1);
	double plus;
	double siz_x;
	double siz_y;
	{
		double x1 = static_cast<double>(size_w[0]) / static_cast<double>(diapason[0]);
		double y1 = static_cast<double>(size_w[1]) / static_cast<double>(diapason[1]);
		siz_x = x1;
		siz_y = y1;
		plus = 1 / (sqrt(x1 * x1 + y1 * y1));
		arr[0].valuable = x;
		y = calcul(arr, 1);
		dr.calcul(x, y, plus); 
		x += plus;
	}
	for (; x < p1; x += plus)
	{
		arr[0].valuable = x;
		y = calcul(arr, 1);
		if (y >= start_y && y <= end_y)
		{
			if (dr.calcul(x, y, plus))
			{
				new_point(x * siz_x, y * siz_y);
				x-=dr.get_Mpl();
				continue;
			}
			new_point(x * siz_x, y * siz_y);
		}
	}
	dr.clear();
	v.resize(v_i);
	v_i = 0;
}
double AIO::search_start(cash *arr,int size)
{
	double x = -p1;
	double y;
	start_y = -diapason[1] / 2;
	end_y = -start_y;
	int it = 0;
	for (double plus = 1; x < p1; x+=plus)
	{
		arr[0].valuable = x;
		y = calcul(arr, size);
		if (fs2)
		{
			x -= plus; plus /= 10;
			it++;
		}
		if (it >= 5)
			break;
	}
	return x;
}
#undef p
#undef p1
#undef fs2
void AIO::increase_x(double x)
{
	diapason[0] += x;
	if (diapason[0] == 600)
		std::cout << "S";
	if(diapason[0]<=0 || diapason[0]>size_w[0])
		diapason[0]-=x;
}
void AIO::increase_y(double y)
{
	diapason[1] += y;
	if (diapason[1] <= 0 || diapason[1] > size_w[1])
		diapason[1] -= y;
}
void AIO::new_point(double x, double y)
{
	if (v_i >= v.getVertexCount())
	{
		v.resize(v_i + 100);
	}
	v[v_i].position = sf::Vector2f(x + half_size_x, half_size_y-y);
	v_i++;
}
//draw rastr
bool draw_rastr::calcul(double x, double y, double &plus)
{
	if (qw == 0)
	{
		if (history_x != -503)
		{
			changes_x = abs(history_x - x);
			changes_y = abs(history_y - y);
			if (changes_y >= changes_x + plus)
			{
				Mpl = plus;
				plus = plus / (static_cast<double>(changes_y) / static_cast<double>(changes_x));
				qw = Mpl / plus;
				return true;
			}
		}
	}
	else
	{
		qw--;
		if (qw == 0)
		{
			plus = Mpl;
		}
	}
	history_x = x;
	history_y = y;
	return false;
}

//grid
grid::grid(int q) :qw(q<<1), lines(sf::Lines, qw), size_text(10)
{
	t.resize(q);
	f.loadFromFile("FontC.ttf");
	lines.resize(qw);
	change_size_text(size_text);
	set_position();
}
void grid::set_position()
{
	int qwD2 = qw >> 2;
	float s1 = size_w[0] / qwD2;
	float s2 = size_w[1] / qwD2;
	float sum{};
	int j = 0;
	int t_i = 0;
	for (t_i=0; j < qw >> 1; j++,t_i++)
	{
		sum += s1;
		t[t_i].setPosition(sf::Vector2f(sum, half_size_y));
		t[t_i].setFont(f);
		lines[j].position = sf::Vector2f(sum, 0);
		j++;
		lines[j].position = sf::Vector2f(sum, size_w[1]);
	}
	sum = 0;
	for (; j < qw; j++,t_i++)
	{
		sum += s2;
		t[t_i].setPosition(sf::Vector2f(half_size_x, sum));
		t[t_i].setFont(f);
		lines[j].position = sf::Vector2f(0, sum);
		j++;
		lines[j].position = sf::Vector2f(size_w[0], sum);
	}
}
void grid::set_qw(int q)
{
	qw = q<<1;
	t.resize(q);
	lines.resize(qw);
	set_position();
}
void grid::set(float d_x, float d_y)
{
	double qw2 = qw >> 2;
	double d[2]{ d_x / qw2,d_y/ qw2 };
	double sum{-(d_x/2)};
	int i = 0;
	for (int j = 0; j < 2; j++,qw2+=qw2) {
		for (; i < qw2; i++)
		{
			sum += d[j];
			t[i].setString(d_to_string(sum,5));
		}
		sum = -(d_y / 2);
	}
}
void grid::change_size_text(const int sc)
{
	size_text = abs(sc);
	float loc = size_text >> 1;
	for (int i = 0; i < qw>>1; i++)
	{
		t[i].setCharacterSize(size_text);
		t[i].setOrigin(sf::Vector2f(loc, loc));
	}
}
void grid::set_color(sf::Color c)
{
	for (int i = 0; i < qw; i++)
	{
		lines[i].color = c;
	}
}

std::string d_to_string(double dl, int qw)
{
	std::string pk;
	int minus{};
	int dop;
	int c = static_cast<int>(dl);
	int index{};          // Кол-во элементов в pk 
	bool int_or_fl = c == dl;  //int - true
	for (int j = 0;; j++)
	{
		std::string p;
		if (index >= qw)
			break;
		if (c < 0)
		{
			dop = c * -1;
			minus += 1;
		}
		else
			dop = c;
		while (dop > 9)
		{
			p += dop % 10 + '0';
			dop /= 10;
		}
		p += dop + '0';
		if (minus == 1)
		{
			p += '-';
			minus++;
		}
		int size_p = p.size();
		int i{};
		for (int a = size_p - 1; i < size_p; i++, a--)
		{
			pk += p[a];
			if (i >= qw)
				break;
			if (i + 1 == size_p)
				if (j == 0 && int_or_fl == 0)
				{
					pk += '.';
				}
		}
		index += i;
		if (int_or_fl)
			break;
		dl -= static_cast<double>(c);
		dl *= pow(10, qw - index);
		c = dl;
	}
	if (pk[index - 1] == '.')
		index--;
	return pk;
}