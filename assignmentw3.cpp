#include <iostream>
#include <iomanip>

using namespace std;

// Tìm bậc của đa thức
int poly_deg(int p) {
    if (p == 0) return -1;
    int deg = 0;
    while (p > 1) { 
        deg++; 
        p >>= 1; 
    }
    return deg;
}

// Nhân 2 đa thức trong GF(2)
int poly_mul(int a, int b) {
    int p = 0;
    while (b > 0) {
        if (b & 1) p ^= a;
        a <<= 1;
        b >>= 1;
    }
    return p;
}

// Thuật toán Euclidean mở rộng (bảng chuẩn 4 cột: r, q, v, w)
int extended_euclidean_gf2(int a, int m) {
    // Khởi tạo các giá trị cho r_{-1} và r_0
    int r_prev = m, r_curr = a;
    int v_prev = 1, v_curr = 0;
    int w_prev = 0, w_curr = 1;

    // In tiêu đề 4 cột
    cout << left 
         << setw(8) << "r" 
         << setw(8) << "q" 
         << setw(8) << "v" 
         << "w\n";
    cout << "---------------------------\n";

    // In dòng của r_{-1}
    cout << left 
         << setw(8) << r_prev 
         << setw(8) << "-" 
         << setw(8) << v_prev 
         << w_prev << "\n";
    
    // In dòng của r_0
    cout << left 
         << setw(8) << r_curr 
         << setw(8) << "-" 
         << setw(8) << v_curr 
         << w_curr << "\n";

    while (r_curr > 0) {
        int q = 0, r_new = r_prev;
        int deg_r_curr = poly_deg(r_curr);
        
        // Phép chia: tìm thương q và số dư r_new
        while (poly_deg(r_new) >= deg_r_curr) {
            int shift = poly_deg(r_new) - deg_r_curr;
            q ^= (1 << shift);
            r_new ^= (r_curr << shift);
        }

        // Cập nhật hệ số v và w
        int v_new = v_prev ^ poly_mul(q, v_curr);
        int w_new = w_prev ^ poly_mul(q, w_curr);
        
        // In ra dòng r_i hiện tại
        cout << left 
             << setw(8) << r_new 
             << setw(8) << q 
             << setw(8) << v_new 
             << w_new << "\n";

        // Dịch biến cho bước lặp tiếp theo
        r_prev = r_curr; 
        r_curr = r_new;
        v_prev = v_curr; 
        v_curr = v_new;
        w_prev = w_curr; 
        w_curr = w_new;
    }
    cout << "---------------------------\n";
    
    // Nghịch đảo của a mod m chính là w tại bước r = 1 (lúc này r_prev = 1)
    return (r_prev == 1) ? w_prev : 0;
}

int main() {
    int m = 1033; // Đa thức m(x) = x^10 + x^3 + 1
    
    cout << "=== TEST VECTOR 1: a = 523 ===\n";
    int inv_a = extended_euclidean_gf2(523, m);
    cout << "=> Nghich dao nhan cua 523 la: " << inv_a << "\n\n";
    
    cout << "=== TEST VECTOR 2: b = 1015 ===\n";
    int inv_b = extended_euclidean_gf2(1015, m);
    cout << "=> Nghich dao nhan cua 1015 la: " << inv_b << "\n";
    
    return 0;
}