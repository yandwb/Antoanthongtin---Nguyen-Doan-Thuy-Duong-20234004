#include <iostream>
#include <string>
using namespace std;

void ksa(int key[], int key_len, int S[], int n) {
    for (int i = 0; i < n; ++i) S[i] = i;
    int j = 0;
    for (int i = 0; i < n; ++i) {
        j = (j + S[i] + key[i % key_len]) % n;
        swap(S[i], S[j]);
    }
}

void prga(int S[], int n, int text_length, int keystream[]) {
    int i = 0, j = 0;
    for (int k = 0; k < text_length; ++k) {
        i = (i + 1) % n;
        j = (j + S[i]) % n;
        swap(S[i], S[j]);
        int t = (S[i] + S[j]) % n;
        keystream[k] = S[t];
    }
}

void rc4_encrypt(const string& plaintext, int key[], int key_len, int n) {
    int text_length = plaintext.length();
    int S[10]; 
    int keystream[13]; 
    int ciphertext[13];
    cout << "Ban ro (Text):  " << plaintext << endl;
    ksa(key, key_len, S, n);
    prga(S, n, text_length, keystream);
    cout << "Dong khoa K(t): [";
    for (int i = 0; i < text_length; ++i) {
        cout << keystream[i] << (i == text_length - 1 ? "" : ", ");
        ciphertext[i] = (int)plaintext[i] ^ keystream[i];
    }
    cout << "]" << endl;
    cout << "Ban ma C(t):    [";
    for (int i = 0; i < text_length; ++i) {
        cout << ciphertext[i] << (i == text_length - 1 ? "" : ", ");
    }
    cout << "]" << endl;
    cout << "Ban ma (Ky tu): ";
    for (int i = 0; i < text_length; ++i) {
        cout << (char)ciphertext[i]; 
    }
    cout << endl;
}

int main() {
    int n = 10; 
    int key[] = {2, 4, 1, 7};
    int key_len = 4;
    string plaintext = "cybersecurity";
    rc4_encrypt(plaintext, key, key_len, n);
    return 0;
}