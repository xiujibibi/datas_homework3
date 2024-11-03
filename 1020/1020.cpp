#include <iostream>
#include <list>
#include <forward_list>
#include <vector>
#include <algorithm>
#include <string>
#include <regex>

using namespace std;

struct Book {
    string title;
    string author;
    string id;
};

struct Borrower {
    string name;
    vector<string> borrowedBooks;
};

list<Book> books;
forward_list<Borrower> borrowers;

bool isValidBookId(const string& id) {
    regex pattern("^[A-Za-z][0-9]{4}$");
    return regex_match(id, pattern);
}
//1
void addBook() {
    Book book;
    do {
        cout << "輸入圖書編號(1位字母+4位數字): ";
        cin >> book.id;
        if (!isValidBookId(book.id)) {
            cout << "編號格式無效。再試一次!" << endl;
        }
    } while (!isValidBookId(book.id));
    cout << "輸入書名: ";
    cin >> book.title;
    cout << "輸入作者姓名: ";
    cin >> book.author;
    books.push_back(book);
    cout << "添加成功!" << endl << endl;
}
//2
void deleteBook() {
    string id;
    cout << "輸入要刪除的圖書編號(1位字母+4位數字): ";
    cin >> id;
    auto it = find_if(books.begin(), books.end(), [&id](const Book& book) { return book.id == id; });
    if (it != books.end()) {
        cout << "刪除圖書: " << it->title << " 作者: " << it->author << endl;
        char confirm;
        cout << "確認刪除? (y/n): ";
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            books.erase(it);
            cout << "刪除成功!" << endl << endl;
        }
        else {
            cout << "取消刪除。" << endl << endl;
        }
    }
    else {
        cout << "找不到圖書..." << endl << endl;
    }
}
//3
void searchBook() {
    string id;
    cout << "輸入要搜索的圖書編號: ";
    cin >> id;
    auto it = find_if(books.begin(), books.end(), [&id](const Book& book) { return book.id == id; });
    if (it != books.end()) {
        cout <<it->id << " - " << it->title << "  作者: " << it->author << endl<<endl;
    }
    else {
        cout << "找不到圖書..." << endl << endl;
    }
}
//4
void listBooks() {
    books.sort([](const Book& a, const Book& b) { return a.id < b.id; });
    for (const auto& book : books) {
        cout << book.id << " : " << book.title << " 作者: " << book.author << endl << endl;
    }
}
//5
void addBorrower() {
    Borrower borrower;
    cout << "輸入借閱人姓名: ";
    cin >> borrower.name;
    string bookId;
    while (true) {
        cout << "輸入借閱的圖書編號(輸入 '0' 結束借閱): ";
        cin >> bookId;
        if (bookId == "0") {
            break;
        }
        if (isValidBookId(bookId)) {
            auto it = find_if(books.begin(), books.end(), [&bookId](const Book& book) { return book.id == bookId; });
            if (it != books.end()) {
                cout << "書名: " << it->title << " 作者: " << it->author << endl << endl;
                borrower.borrowedBooks.push_back(bookId);
            }
            else {
                cout << "找不到圖書，請再試一次。" << endl << endl;
            }
        }
        else {
            cout << "無效的圖書編號，請再試一次。" << endl << endl;
        }
    }
    borrowers.push_front(borrower);
    cout << "借閱成功!" << endl << endl;
}
//6
void deleteBorrower() {
    string name;
    cout << "輸入要刪除的借閱人姓名: ";
    cin >> name;
    auto it = find_if(borrowers.begin(), borrowers.end(), [&name](const Borrower& borrower) { return borrower.name == name; });
    if (it != borrowers.end()) {
        cout << "借閱人: " << it->name << endl;
        char confirm;
        cout << "確認刪除? (y/n): ";
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            borrowers.remove_if([&name](const Borrower& borrower) { return borrower.name == name; });
            cout << "刪除成功!" << endl << endl;
        }
        else {
            cout << "取消刪除。" << endl << endl;
        }
    }
    else {
        cout << "找不到借閱人..." << endl << endl;
    }
}

//7
void searchBorrower() {
    string name;
    cout << "輸入要搜尋的借閱人姓名: ";
    cin >> name;
    auto it = find_if(borrowers.begin(), borrowers.end(), [&name](const Borrower& borrower) { return borrower.name == name; });
    if (it != borrowers.end()) {
        cout << it->name << endl;
        for (const auto& bookId : it->borrowedBooks) {
            auto bookIt = find_if(books.begin(), books.end(), [&bookId](const Book& book) { return book.id == bookId; });
                cout << "書籍編號: " << bookId << " 書名: " << bookIt->title << endl << endl;
        }
    }
    else {
        cout << "查無借閱人..." << endl << endl;
    }
}
//8
void listBorrowers() {
    for (const auto& borrower : borrowers) {
        cout << borrower.name << endl;
        for (const auto& bookId : borrower.borrowedBooks) {
            auto it = find_if(books.begin(), books.end(), [&bookId](const Book& book) { return book.id == bookId; });
            if (it != books.end()) {
                cout << "  編號: " << bookId << " 書名: " << it->title << " 作者: " << it->author << endl << endl;
            }
            else {
                cout << "  編號: " << bookId << " 書名: 未找到" << endl << endl;
            }
        }
    }
}


int main() {
    int choice;
    do {
        cout << "功能選項" << endl;
        cout << "1. 添加新圖書" << endl;
        cout << "2. 刪除圖書" << endl;
        cout << "3. 編號搜索圖書" << endl;
        cout << "4. 依照圖書編號排序列出所有圖書" << endl;
        cout << "5. 添加新借閱者" << endl;
        cout << "6. 刪除借閱者" << endl;
        cout << "7. 搜索借閱者" << endl;
        cout << "8. 列出所有借閱者及其借閱的圖書" << endl;
        cout << "9. 離開" << endl;
        cout << "輸入要執行的功能: ";
        cin >> choice;
        switch (choice) {
        case 1: addBook(); break;
        case 2: deleteBook(); break;
        case 3: searchBook(); break;
        case 4: listBooks(); break;
        case 5: addBorrower(); break;
        case 6: deleteBorrower(); break;
        case 7: searchBorrower(); break;
        case 8: listBorrowers(); break;
        case 9: break;
        default: cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 9);
    return 0;
}
