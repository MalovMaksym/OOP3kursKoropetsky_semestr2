//1
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

double getValue(double x, int col) {
    string file = "dat_X_1_1.dat";
    if (x < -1.0) {
        x = -1.0 / x;
        file = "dat_X_1_00.dat";
    } else if (x > 1.0) {
        x = -1.0 / x;
        file = "dat_X_00_1.dat";
    }
    
    ifstream is(file.c_str());
    if (!is) {
        throw "Alg5";
    }
    
    double xi, ti, ui, xi_next, ti_next, ui_next;
    if (!(is >> xi >> ti >> ui)) {
        is.close();
        throw "Alg5";
    }
    
    if (x == xi) {
        is.close();
        return col == 1 ? ti : ui;
    }
    
    while (is >> xi_next >> ti_next >> ui_next) {
        if ((xi < x && x < xi_next) || (xi > x && x > xi_next)) {
            double res = col == 1 ? 
                ti + (ti_next - ti) * (x - xi) / (xi_next - xi) : 
                ui + (ui_next - ui) * (x - xi) / (xi_next - xi);
            is.close();
            return res;
        }
        if (x == xi_next) {
            is.close();
            return col == 1 ? ti_next : ui_next;
        }
        xi = xi_next;
        ti = ti_next;
        ui = ui_next;
    }
    
    is.close();
    return col == 1 ? ti : ui;
}

double T(double x) {
    return getValue(x, 1);
}

double U(double x) {
    return getValue(x, 2);
}

double Srz(double x, double y, double z) {
    if (x > y) return T(x) + U(z) - T(y);
    return T(y) + U(y) - U(z);
}

double Srs3(double x, double y, double z) {
    if (z > y) return Srz(x, y, z) + y * x;
    return y * z + Srz(z, x, y);
}

double Qrz3(double x, double y) {
    if (fabs(x) < 1.0) return x * Srs3(x, y, x);
    return x * Srs3(y, x, y);
}

double Rrz2(double x, double y, double z) {
    if (x > y) return y * Qrz3(y, z);
    return z * Qrz3(x, y);
}

double Krn_Alg4(double x, double y, double z) {
    return 83.1389 * Rrz2(x, y, z) + 4.838 * Rrz2(x, z, y);
}

double Srs2(double x, double y, double z) {
    if (z > y) return Srz(x, y, z) + y * x;
    return y * z + Srz(z, x, y);
}

double Qrz2(double x, double y) {
    if (fabs(x) < 1.0) return x * Srs2(x, y, x);
    return y * Srs2(y, x, y);
}

double Rrz_Alg3(double x, double y, double z) {
    if (x > y) return x * y * Qrz2(y, z);
    return y * z * Qrz2(x, y);
}

double Srs1_Alg2(double x, double y, double z) {
    if (z > y) return Srz(x, y, z) + 1.44 * y * z;
    return y + 1.44 * Srz(z, x, y);
}

double Qrz1(double x, double y) {
    if (fabs(y) < 1.0) return x * Srs1_Alg2(x, y, x);
    return y * Srs1_Alg2(y, x, y);
}

double Rrz_Alg2(double x, double y, double z) {
    if (x > y) return x * y * Qrz1(y, z);
    return x * z * Qrz1(x, y);
}

double Srs(double x, double y, double z) {
    if (z > y) {
        if (z * z + x * y <= 0) throw 2;
        return Srz(x, y, z) + y * sqrt(z * z + x * y);
    } else {
        if (x * x + z * y <= 0) throw 3;
        return y + Srz(z, x, y) * sqrt(x * x + z * y);
    }
}

double Srs1(double x, double y, double z) {
    if (z > y) {
        if (z * z + x * y <= 1.0) throw 2;
        return Srz(x, y, z) + y * log(z * z + x * y);
    } else {
        if (x * x + z * y <= 1.0) throw 4;
        return y + Srz(z, x, y) * sqrt(x * x + z * y);
    }
}

double Qrz(double x, double y) {
    if (fabs(x) < 1.0) return x * Srs(x, y, x);
    return y * Srs1(y, x, y);
}

double Rrz(double x, double y, double z) {
    try {
        if (x > y) return x * z * Qrz(y, z) - x;
        return y * x * Qrz(x, y) + y;
    } catch (int e) {
        if (e == 2) return Rrz_Alg2(x, y, z);
        if (e == 3) return Rrz_Alg3(x, y, z);
        throw;
    }
}

double Krn(double x, double y, double z) {
    try {
        return 73.1389 * Rrz(x, y, y) + 14.838 * Rrz(x - y, z, y);
    } catch (int e) {
        if (e == 4) return Krn_Alg4(x, y, z);
        throw;
    }
}

double fun(double x, double y, double z) {
    try {
        return x * Krn(x, y, z) + y * Krn(x, z, y) - z * Krn(x, z, y);
    } catch (const char* e) {
        return 4.349 * x * z + 23.23 * y - 2.348 * x * y * z;
    }
}

int main() {
    double x, y, z;
    if (cin >> x >> y >> z) {
        double result = fun(x, y, z);
        cout << result << endl;
    }
    return 0;
}


//2
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
class Matrix {
private:
    int rows;
    int cols;
    T** data;

public:
    Matrix(int r, int c) {
        rows = r;
        cols = c;
        data = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new T[cols];
        }
    }

    int fillFromKeyboard() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cin >> data[i][j];
            }
        }
        return 0;
    }

    int fillFromFile(const char* filename) {
        ifstream file(filename);
        if (file) {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    file >> data[i][j];
                }
            }
            file.close();
        }
        return 0;
    }

    int fillRandom() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] = (rand() % 100) + (T)(rand() % 100) / 100.0;
            }
        }
        return 0;
    }

    int print() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << data[i][j] << "\t";
            }
            cout << "\n";
        }
        cout << "\n";
        return 0;
    }
};

int main() {
    srand(time(0));
    
    int choice;
    cout << "1 - Random\n2 - Keyboard\n3 - File\nChoice: ";
    cin >> choice;

    Matrix<int> intMatrix(2, 3);
    Matrix<double> doubleMatrix(2, 3);

    if (choice == 1) {
        intMatrix.fillRandom();
        doubleMatrix.fillRandom();
    } else if (choice == 2) {
        intMatrix.fillFromKeyboard();
        doubleMatrix.fillFromKeyboard();
    } else if (choice == 3) {
        intMatrix.fillFromFile("data_int.txt");
        doubleMatrix.fillFromFile("data_double.txt");
    }

    cout << "\nInt Matrix:\n";
    intMatrix.print();
    
    cout << "Double Matrix:\n";
    doubleMatrix.print();

    return 0;
}
