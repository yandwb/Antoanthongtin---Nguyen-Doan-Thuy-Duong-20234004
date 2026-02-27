#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <utility> 

using namespace std;

// 1. Hàm tạo ma trận 5x5 từ Key
void buildKeySquare(string key, char keySquare[5][5]) {
    string uniqueChars = "";
    bool charSeen[26] = {false};
    charSeen['J' - 'A'] = true; // Xem J như I

    // Lọc các ký tự trong khóa
    for (char c : key) {
        if (isalpha(c)) {
            c = toupper(c);
            if (c == 'J') c = 'I';
            if (!charSeen[c - 'A']) {
                uniqueChars += c;
                charSeen[c - 'A'] = true;
            }
        }
    }
    
    // Thêm các ký tự còn lại của bảng chữ cái
    for (char c = 'A'; c <= 'Z'; c++) {
        if (!charSeen[c - 'A']) {
            uniqueChars += c;
        }
    }

    // Đổ chuỗi 25 ký tự vào ma trận 5x5
    int index = 0;
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 5; col++) {
            keySquare[row][col] = uniqueChars[index++];
        }
    }
}

// 2. Hàm định dạng bản rõ
string formatPlaintext(string rawText) {
    string filtered = "";
    // Xóa khoảng trắng và chuyển in hoa
    for (char c : rawText) {
        if (isalpha(c)) {
            c = toupper(c);
            filtered += (c == 'J') ? 'I' : c;
        }
    }

    string pairedText = "";
    int len = filtered.length();
    
    // Tách thành từng cặp và chèn 'X' nếu trùng
    for (int i = 0; i < len; i++) {
        pairedText += filtered[i];
        if (i + 1 < len && filtered[i] == filtered[i + 1]) {
            pairedText += 'X'; // Hai chữ cái giống nhau đứng liền -> chèn X
        } else if (i + 1 < len) {
            pairedText += filtered[i + 1];
            i++; // Bỏ qua ký tự tiếp theo vì đã ghép cặp
        }
    }
    
    // Đảm bảo số lượng ký tự luôn chẵn
    if (pairedText.length() % 2 != 0) {
        pairedText += 'X';
    }
    
    return pairedText;
}

// 3. Hàm tìm tọa độ (row, col) của ký tự
pair<int, int> getCoordinates(char keySquare[5][5], char target) {
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if (keySquare[r][c] == target) {
                return {r, c};
            }
        }
    }
    return {-1, -1}; // Trường hợp lỗi không tìm thấy (ít xảy ra)
}

// 4. Hàm mã hóa bản rõ
string processEncryption(string text, char keySquare[5][5]) {
    string cipherText = "";
    
    for (size_t i = 0; i < text.length(); i += 2) {
        pair<int, int> pos1 = getCoordinates(keySquare, text[i]);
        pair<int, int> pos2 = getCoordinates(keySquare, text[i + 1]);

        int r1 = pos1.first, c1 = pos1.second;
        int r2 = pos2.first, c2 = pos2.second;

        if (r1 == r2) {
            // Cùng hàng -> Dịch phải
            cipherText += keySquare[r1][(c1 + 1) % 5];
            cipherText += keySquare[r2][(c2 + 1) % 5];
        } else if (c1 == c2) {
            // Cùng cột -> Dịch xuống
            cipherText += keySquare[(r1 + 1) % 5][c1];
            cipherText += keySquare[(r2 + 1) % 5][c2];
        } else {
            // Hình chữ nhật -> Tráo góc
            cipherText += keySquare[r1][c2];
            cipherText += keySquare[r2][c1];
        }
    }
    return cipherText;
}

// 5. Hàm in ma trận để kiểm tra
void displayMatrix(char keySquare[5][5]) {
    cout << "--- Ma tran khoa Playfair (5x5) ---" << endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << keySquare[i][j] << " ";
        }
        cout << endl;
    }
    cout << "-----------------------------------" << endl;
}

int main() {
    string key = "MONARCHY";
    string plaintext = "DO YOU LIKE TO STUDY A CRYPTOGRAPHY COURSE";
    char keySquare[5][5];

    cout << "Khoa (Key): " << key << endl;
    cout << "Ban ro (Plaintext): " << plaintext << "\n\n";

    buildKeySquare(key, keySquare);
    displayMatrix(keySquare);

    string formattedText = formatPlaintext(plaintext);
    cout << "\nChuoi sau khi xu ly va chia cap: \n";
    for (size_t i = 0; i < formattedText.length(); i += 2) {
        cout << formattedText[i] << formattedText[i+1] << " ";
    }
    cout << "\n";

    string ciphertext = processEncryption(formattedText, keySquare);
    
    cout << "\n=> BAN MA (CIPHERTEXT): \n";
    for (size_t i = 0; i < ciphertext.length(); i += 2) {
        cout << ciphertext[i] << ciphertext[i+1] << " ";
    }
    cout << "\n";

    return 0;
}