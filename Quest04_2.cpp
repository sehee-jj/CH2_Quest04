#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>

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
    void AddBook(const Book book) {
        books_.push_back(book); // push_back 사용
        cout << "책이 추가되었습니다: " << book.title_ << " by " << book.author_ << endl;
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

    //책 이름으로 찾기
    Book* GetBookByTitle(string title)
    {
        for (int i=0; i<books_.size(); i++)
        {
            if (books_[i].title_ == title)
                return &books_[i];
        }

        return nullptr;
    }

    //작가이름으로 찾기
    Book* GetBookByAuthor(string author)
    {
        for (int i = 0; i < books_.size(); i++)
        {
            if (books_[i].author_ == author)
                return &books_[i];
        }

        return nullptr;
    }
};

class BorrowManager
{
private:
    unordered_map<string, int> stock_;
public:
    //새로운 책이 들어오면 책을 stock에 저장
    void InitializeStock(Book book, int quantity = 3)
    {
        stock_.insert({ book.title_, quantity });
    }

    //책 대여
    void BorrowBook(string title)
    {
        auto iter = stock_.find(title);
        if (iter != stock_.end())
        {
            if (iter->second > 0)
            {
                cout << "대여를 완료했습니다. 남은 수량: " << --iter->second << '\n';
            }
            else
            {
                cout << "남은 수량이 부족해 대여하지 못했습니다.\n";
            }
        }
        else
        {
            cout << "현재 도서 목록에 없는 책입니다.\n";
        }
    }

    //책 반납
    void ReturnBook(string title)
    {
        auto iter = stock_.find(title);
        if (iter != stock_.end())
        {
            iter->second++;
            cout << "도서 반납을 완료하였습니다.\n";
        }
        else
        {
            cout << "현재 도서 목록에 없는 책입니다.\n";
        }
    }

    //검색한 책의 대여가능한 수량을 출력함
    void SearchStock(string title) const
    {
        auto iter = stock_.find(title);
        if (iter != stock_.end())
        {
            cout << "==> 남은 수량: " << iter->second << '\n';
        }
        else
        {
            cout << "현재 도서 목록에 없는 책입니다.\n";
        }
    }
};

class Librarian
{
private:
    BookManager bookM_;
    BorrowManager borrowM_;

public:
    //책 추가 메서드
    //책 목록에 책을 추가하고, 재고 목록에도 추가함
    void AddBook(const string& title, const string& author)
    {
        Book book(title, author);
        bookM_.AddBook(book);
        borrowM_.InitializeStock(book);
    }

    //현재 책 목록 출력
    void PrintBookList() const
    {
        bookM_.DisplayAllBooks();
    }

    //책 검색
    Book* SearchBook(int type, string str)
    {
        Book* book = nullptr;
        if (type == 1) //책 이름 검색
        {
            book = bookM_.GetBookByTitle(str);
        }
        else if (type == 2) //작가명 검색
        {
            book = bookM_.GetBookByAuthor(str);
        }

        if (book != nullptr)
        {
            bookM_.PrintBook(*book);
            borrowM_.SearchStock(book->title_);
        }
        else
        {
            cout << "찾으시는 책이 없습니다.\n";
        }

        return book;
    }

    //책 대여
    void RentalBook(int type, string str)
    {
        Book* book = SearchBook(type, str);
        if (book != nullptr)
        {
            borrowM_.BorrowBook(book->title_);
        }
    }

    //책 반납
    void ReturnBook(string title)
    {
        borrowM_.ReturnBook(title);
    }
};

int main() {
    Librarian manager;

    manager.AddBook("그리스로마 신화", "둘리");
    manager.AddBook("죄와 벌", "하츄핑");
    manager.AddBook("코믹 메이플스토리", "공자");

    // 도서관 관리 프로그램의 기본 메뉴를 반복적으로 출력하여 사용자 입력을 처리합니다.
    // 프로그램 종료를 선택하기 전까지 계속 동작합니다.
    while (true) {
        cout << "***도서관 관리 프로그램***" << endl;
        cout << "1. 책 추가" << endl; // 책 정보를 입력받아 책 목록에 추가
        cout << "2. 모든 책 출력" << endl; // 현재 책 목록에 있는 모든 책 출력
        cout << "3. 책/작가 검색" << endl; // 현재 책 목록에서 검색한 제목의 책이 있는지 확인
        cout << "4. 책 대여" << endl; // 현재 책 목록에서 검색한 작가의 책이 있는지 확인
        cout << "5. 책 반납" << endl;
        cout << "6. 종료" << endl; // 프로그램 종료
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
            manager.PrintBookList();
        }
        else if (choice == 3) {
            // 3번 선택: 책/작가 검색
            int type;
            string str;
            cout << "검색 종류를 선택하시오. 1. 책 이름 / 2. 작가 이름 (숫자 선택)\n";
            cin >> type;
            cout << "이름을 입력하시오.\n";
            cin.ignore();
            getline(cin, str);
            manager.SearchBook(type, str);
        }
        else if (choice == 4) {
            // 4번 선택: 책 대여
            int type;
            string str;
            cout << "검색 종류를 선택하시오. 1. 책 이름 / 2. 작가 이름 (숫자 선택)\n";
            cin >> type;
            cout << "이름을 입력하시오.\n";
            cin.ignore();
            getline(cin, str);
            manager.RentalBook(type, str);
        }
        else if (choice == 5) {
            // 5번 선택: 책 반납
            string title;
            cout << "반납할 책 제목을 입력하시오.\n";
            cin.ignore();
            getline(cin, title);
            manager.ReturnBook(title);
        }
        else if (choice == 6) {
            // 6번 선택: 종료
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