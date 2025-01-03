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
    vector<Book> books_; // å ��� ����

public:

    // å �߰� �޼���
    void AddBook(const Book book) {
        books_.push_back(book); // push_back ���
        cout << "å�� �߰��Ǿ����ϴ�: " << book.title_ << " by " << book.author_ << endl;
    }

    // ��� å ��� �޼���
    void DisplayAllBooks() const {
        if (books_.empty()) {
            cout << "���� ��ϵ� å�� �����ϴ�." << endl;
            return;
        }

        cout << "���� ���� ���:" << endl;
        for (Book book : books_) { // �Ϲ����� for�� ���
            PrintBook(book);
        }
    }

    //å ����� �۰��� ����ϴ� �޼���
    void PrintBook(Book book) const
    {
        cout << "- " << book.title_ << " by " << book.author_ << endl;
    }

    //å �̸����� ã��
    Book* GetBookByTitle(string title)
    {
        for (int i=0; i<books_.size(); i++)
        {
            if (books_[i].title_ == title)
                return &books_[i];
        }

        return nullptr;
    }

    //�۰��̸����� ã��
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
    //���ο� å�� ������ å�� stock�� ����
    void InitializeStock(Book book, int quantity = 3)
    {
        stock_.insert({ book.title_, quantity });
    }

    //å �뿩
    void BorrowBook(string title)
    {
        auto iter = stock_.find(title);
        if (iter != stock_.end())
        {
            if (iter->second > 0)
            {
                cout << "�뿩�� �Ϸ��߽��ϴ�. ���� ����: " << --iter->second << '\n';
            }
            else
            {
                cout << "���� ������ ������ �뿩���� ���߽��ϴ�.\n";
            }
        }
        else
        {
            cout << "���� ���� ��Ͽ� ���� å�Դϴ�.\n";
        }
    }

    //å �ݳ�
    void ReturnBook(string title)
    {
        auto iter = stock_.find(title);
        if (iter != stock_.end())
        {
            iter->second++;
            cout << "���� �ݳ��� �Ϸ��Ͽ����ϴ�.\n";
        }
        else
        {
            cout << "���� ���� ��Ͽ� ���� å�Դϴ�.\n";
        }
    }

    //�˻��� å�� �뿩������ ������ �����
    void SearchStock(string title) const
    {
        auto iter = stock_.find(title);
        if (iter != stock_.end())
        {
            cout << "==> ���� ����: " << iter->second << '\n';
        }
        else
        {
            cout << "���� ���� ��Ͽ� ���� å�Դϴ�.\n";
        }
    }
};

class Librarian
{
private:
    BookManager bookM_;
    BorrowManager borrowM_;

public:
    //å �߰� �޼���
    //å ��Ͽ� å�� �߰��ϰ�, ��� ��Ͽ��� �߰���
    void AddBook(const string& title, const string& author)
    {
        Book book(title, author);
        bookM_.AddBook(book);
        borrowM_.InitializeStock(book);
    }

    //���� å ��� ���
    void PrintBookList() const
    {
        bookM_.DisplayAllBooks();
    }

    //å �˻�
    Book* SearchBook(int type, string str)
    {
        Book* book = nullptr;
        if (type == 1) //å �̸� �˻�
        {
            book = bookM_.GetBookByTitle(str);
        }
        else if (type == 2) //�۰��� �˻�
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
            cout << "ã���ô� å�� �����ϴ�.\n";
        }

        return book;
    }

    //å �뿩
    void RentalBook(int type, string str)
    {
        Book* book = SearchBook(type, str);
        if (book != nullptr)
        {
            borrowM_.BorrowBook(book->title_);
        }
    }

    //å �ݳ�
    void ReturnBook(string title)
    {
        borrowM_.ReturnBook(title);
    }
};

int main() {
    Librarian manager;

    manager.AddBook("�׸����θ� ��ȭ", "�Ѹ�");
    manager.AddBook("�˿� ��", "������");
    manager.AddBook("�ڹ� �����ý��丮", "����");

    // ������ ���� ���α׷��� �⺻ �޴��� �ݺ������� ����Ͽ� ����� �Է��� ó���մϴ�.
    // ���α׷� ���Ḧ �����ϱ� ������ ��� �����մϴ�.
    while (true) {
        cout << "***������ ���� ���α׷�***" << endl;
        cout << "1. å �߰�" << endl; // å ������ �Է¹޾� å ��Ͽ� �߰�
        cout << "2. ��� å ���" << endl; // ���� å ��Ͽ� �ִ� ��� å ���
        cout << "3. å/�۰� �˻�" << endl; // ���� å ��Ͽ��� �˻��� ������ å�� �ִ��� Ȯ��
        cout << "4. å �뿩" << endl; // ���� å ��Ͽ��� �˻��� �۰��� å�� �ִ��� Ȯ��
        cout << "5. å �ݳ�" << endl;
        cout << "6. ����" << endl; // ���α׷� ����
        cout << "����: ";

        int choice; // ������� �޴� ������ ����
        cin >> choice;

        if (choice == 1) {
            // 1�� ����: å �߰�
            // ����ڷκ��� å ����� ���ڸ��� �Է¹޾� BookManager�� �߰��մϴ�.
            string title, author;
            cout << "å ����: ";
            cin.ignore(); // ���� �Է��� �ܿ� ���۸� ����
            getline(cin, title); // ���� �Է� (���� ����)
            cout << "å ����: ";
            getline(cin, author); // ���ڸ� �Է� (���� ����)
            manager.AddBook(title, author); // �Է¹��� å ������ �߰�
        }
        else if (choice == 2) {
            // 2�� ����: ��� å ���
            // ���� BookManager�� ����� å ����� ����մϴ�.
            manager.PrintBookList();
        }
        else if (choice == 3) {
            // 3�� ����: å/�۰� �˻�
            int type;
            string str;
            cout << "�˻� ������ �����Ͻÿ�. 1. å �̸� / 2. �۰� �̸� (���� ����)\n";
            cin >> type;
            cout << "�̸��� �Է��Ͻÿ�.\n";
            cin.ignore();
            getline(cin, str);
            manager.SearchBook(type, str);
        }
        else if (choice == 4) {
            // 4�� ����: å �뿩
            int type;
            string str;
            cout << "�˻� ������ �����Ͻÿ�. 1. å �̸� / 2. �۰� �̸� (���� ����)\n";
            cin >> type;
            cout << "�̸��� �Է��Ͻÿ�.\n";
            cin.ignore();
            getline(cin, str);
            manager.RentalBook(type, str);
        }
        else if (choice == 5) {
            // 5�� ����: å �ݳ�
            string title;
            cout << "�ݳ��� å ������ �Է��Ͻÿ�.\n";
            cin.ignore();
            getline(cin, title);
            manager.ReturnBook(title);
        }
        else if (choice == 6) {
            // 6�� ����: ����
            // ���α׷��� �����ϰ� ����ڿ��� �޽����� ����մϴ�.
            cout << "���α׷��� �����մϴ�." << endl;
            break; // while ���� ����
        }
        else {
            // �߸��� �Է� ó��
            // �޴��� ���� ��ȣ�� �Է����� ��� ��� �޽����� ����մϴ�.
            cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���." << endl;
        }
    }

    return 0; // ���α׷� ���� ����
}