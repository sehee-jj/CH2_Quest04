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
    vector<Book> books_; // å ��� ����

public:
    // å �߰� �޼���
    void AddBook(const string& title, const string& author) {
        books_.push_back(Book(title, author)); // push_back ���
        cout << "å�� �߰��Ǿ����ϴ�: " << title << " by " << author << endl;
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

    //�˻��� å ����� ��ġ�ϴ� å�� ������ ���
    //��ġ�ϴ� å�� ���ٸ� ���� �޽��� ���
    void SerchByTitle(string title) const
    {
        bool is_exist = false;
        for (Book book : books_)
        {
            if (book.title_ == title)
            {
                cout << "�˻��Ͻ� ����� ��ġ�ϴ� å�� �����Դϴ�.\n";
                PrintBook(book);
                is_exist = true;
                break;
            }
        }

        if (!is_exist)
            cout << "ã���ô� å�� �����ϴ�.\n";
    }

    //�˻��� �۰� ��� ��ġ�ϴ� å�� ������ ���
    //��ġ�ϴ� å�� ���ٸ� ���� �޽��� ���
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
            cout << "ã���ô� å�� �����ϴ�.\n";
    }
};

int main() {
    BookManager manager;

    // ������ ���� ���α׷��� �⺻ �޴��� �ݺ������� ����Ͽ� ����� �Է��� ó���մϴ�.
    // ���α׷� ���Ḧ �����ϱ� ������ ��� �����մϴ�.
    while (true) {
        cout << "\n������ ���� ���α׷�" << endl;
        cout << "1. å �߰�" << endl; // å ������ �Է¹޾� å ��Ͽ� �߰�
        cout << "2. ��� å ���" << endl; // ���� å ��Ͽ� �ִ� ��� å ���
        cout << "3. å ���� �˻�" << endl; // ���� å ��Ͽ��� �˻��� ������ å�� �ִ��� Ȯ��
        cout << "4. �۰� �̸� �˻�" << endl; // ���� å ��Ͽ��� �˻��� �۰��� å�� �ִ��� Ȯ��
        cout << "5. ����" << endl; // ���α׷� ����
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
            manager.DisplayAllBooks();
        }
        else if (choice == 3) {
            // 3�� ����: å ���� �˻�
            // ���� BookManager�� ����� å ��� �� �˻��� ������ å�� �ִٸ� ����մϴ�.
            string title;
            cout << "å ����: ";
            cin.ignore();
            getline(cin, title);
            manager.SerchByTitle(title);
        }
        else if (choice == 4) {
            // 4�� ����: �۰� �̸� �˻�
            // ���� BookManager�� ����� å ��� �� �˻��� �۰����� å�� �ִٸ� ����մϴ�.
            string author;
            cout << "�۰� �̸�: ";
            cin.ignore();
            getline(cin, author);
            manager.SerchByAuthor(author);
        }
        else if (choice == 5) {
            // 5�� ����: ����
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