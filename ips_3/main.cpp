#include <iostream>
#include <math.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include <cilk/reducer_max.h>
#include <cilk/reducer_min.h>
#include <cilk/reducer_vector.h>
#include <cilk/reducer_opadd.h>
#include <chrono>
using namespace std::chrono;

using namespace std;
/*
функция, интеграл
** param double x значение x
*/
double integral(double x)
{
	return 6/sqrt(x*(2-x));
}

/*double central_rectangle(double a, double b,double h, int n){
	double result = 0.0;
	int i = 0;
	cilk_for(i = 1; i <= n; i++){
		result = result + h *integral(a + h * (i - 0.5));
	}
	return result;
}
*/

double trapeze(double a, double b, double h, int n){
	cilk::reducer_opadd<double> result (0.0);
		double total = h * (integral(a) + integral(b)) / 2.0;
	//int i = 0;
	cilk_for(int i = 0; i <= n - 1; i++){
		*result += h * integral(a + h * i);
	}
	return result.get_value()+ total;
}



int main()
{
	/*
	** int i   счетчик
	** double a отрезок интегрирования
	** double b отрезок интегрирования
	** double h шаг интегрирования
	** int n число разбиений 
	*/
	int i, n;
	double a = 0.5, b = 1.0, h = 0.0000001;

	n = (b - a) / h;

	cout << "trapeze = " << trapeze(a, b, h, n) << "\n";
	
	system("pause");






	// разные функции реализации
	//cout << "central_rectangle = " << central_rectangle(a,b,h,n) << "\n";
	/*
	// вычисляем интеграл по формуле центральных прямугольников
	result = 0.0;
	for (i = 1; i <= n; i++)
		result = result + h *integral(a + h * (i - 0.5));
	cout << "I1 = " << result << "\n";

	// вычисляем интеграл по формуле трапеций
	result = h * (integral(a) + integral(b)) / 2.0;
	for (i = 1; i <= n - 1; i++)
		result = result + h * integral(a + h * i);
	cout << "I2 = " << result << "\n";

	// вычисляем интеграл по формуле центральных прямугольников
	result = h * (integral(a) + integral(b)) / 6.0;
	for (i = 1; i <= n; i++)
		result = result + 4.0 / 6.0 * h * integral(a + h * (i - 0.5));
	for (i = 1; i <= n - 1; i++)
		result = result + 2.0 / 6.0 * h * integral(a + h * i);
	cout << "I3 = " << result << "\n";
	*/
	
}