#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class Book {
public:
    string title_;
    string author_;

    Book(const string& title, const string& author)
        : title_(title), author_(author) {
    }
};

class BookManager {
private:
    vector<Book> books_; // 책 목록 저장

public:
    // 책 추가 메서드
    void AddBook(const string& title, const string& author) {
        books_.push_back(Book(title, author)); // push_back 사용
        cout << "책이 추가되었습니다: " << title << " by " << author << endl;
    }

    // 모든 책 출력 메서드
    void DisplayAllBooks() const {
        if (books_.empty()) {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }

        cout << "현재 도서 목록:" << endl;
        for (Book book : books_) { // 일반적인 for문 사용
            PrintBook(book);
        }
    }

    //책 제목과 작가를 출력하는 메서드
    void PrintBook(Book book) const
    {
        cout << "- " << book.title_ << " by " << book.author_ << endl;
    }

    //검색한 책 제목과 일치하는 책의 정보를 출력
    //일치하는 책이 없다면 오류 메시지 출력
    void SerchByTitle(string title) const
    {
        bool is_exist = false;
        for (Book book : books_)
        {
            if (book.title_ == title)
            {
                cout << "검색하신 제목과 일치하는 책의 정보입니다.\n";
                PrintBook(book);
                is_exist = true;
                break;
            }
        }

        if (!is_exist)
            cout << "찾으시는 책이 없습니다.\n";
    }

    //검색한 작가 명과 일치하는 책의 정보를 출력
    //일치하는 책이 없다면 오류 메시지 출력
    void SerchByAuthor(string author) const
    {
        bool is_exist = false;
        for (Book book : books_)
        {
            if (book.author_ == author)
            {
                PrintBook(book);
                is_exist = true;
            }
        }

        if (!is_exist)
            cout << "찾으시는 책이 없습니다.\n";
    }
};

int main() {
    BookManager manager;

    // 도서관 관리 프로그램의 기본 메뉴를 반복적으로 출력하여 사용자 입력을 처리합니다.
    // 프로그램 종료를 선택하기 전까지 계속 동작합니다.
    while (true) {
        cout << "\n도서관 관리 프로그램" << endl;
        cout << "1. 책 추가" << endl; // 책 정보를 입력받아 책 목록에 추가
        cout << "2. 모든 책 출력" << endl; // 현재 책 목록에 있는 모든 책 출력
        cout << "3. 책 제목 검색" << endl; // 현재 책 목록에서 검색한 제목의 책이 있는지 확인
        cout << "4. 작가 이름 검색" << endl; // 현재 책 목록에서 검색한 작가의 책이 있는지 확인
        cout << "5. 종료" << endl; // 프로그램 종료
        cout << "선택: ";

        int choice; // 사용자의 메뉴 선택을 저장
        cin >> choice;

        if (choice == 1) {
            // 1번 선택: 책 추가
            // 사용자로부터 책 제목과 저자명을 입력받아 BookManager에 추가합니다.
            string title, author;
            cout << "책 제목: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title); // 제목 입력 (공백 포함)
            cout << "책 저자: ";
            getline(cin, author); // 저자명 입력 (공백 포함)
            manager.AddBook(title, author); // 입력받은 책 정보를 추가
        }
        else if (choice == 2) {
            // 2번 선택: 모든 책 출력
            // 현재 BookManager에 저장된 책 목록을 출력합니다.
            manager.DisplayAllBooks();
        }
        else if (choice == 3) {
            // 3번 선택: 책 제목 검색
            // 현재 BookManager에 저장된 책 목록 중 검색한 제목의 책이 있다면 출력합니다.
            string title;
            cout << "책 제목: ";
            cin.ignore();
            getline(cin, title);
            manager.SerchByTitle(title);
        }
        else if (choice == 4) {
            // 4번 선택: 작가 이름 검색
            // 현재 BookManager에 저장된 책 목록 중 검색한 작가명의 책이 있다면 출력합니다.
            string author;
            cout << "작가 이름: ";
            cin.ignore();
            getline(cin, author);
            manager.SerchByAuthor(author);
        }
        else if (choice == 5) {
            // 5번 선택: 종료
            // 프로그램을 종료하고 사용자에게 메시지를 출력합니다.
            cout << "프로그램을 종료합니다." << endl;
            break; // while 루프 종료
        }
        else {
            // 잘못된 입력 처리
            // 메뉴에 없는 번호를 입력했을 경우 경고 메시지를 출력합니다.
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        }
    }

    return 0; // 프로그램 정상 종료
}