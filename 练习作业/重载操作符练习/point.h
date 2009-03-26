
class Point{
	double x,y;
	static int number;
public:
	Point(double ,double );
	void setx(const double);
	void sety(const double);
	double getx();
	double gety();
	void show() const;
	void showid() const;
	friend Point operator+(const Point & ,const Point &);
	Point operator*(const Point &) const;
};
