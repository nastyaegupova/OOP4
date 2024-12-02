#include <cassert>
#include <iostream>
#include <sstream>
using namespace std;






class List {

private:

    class Node {
    public:
        int data;
        Node *next;
        explicit Node(int d) {
            data = d;
            next = nullptr;
        }
    };

    Node* head;
    int size;

    [[nodiscard]] Node* reverseList() const {
        Node* prev = nullptr;
        Node* current = head;
        while (current) {
            Node* newNode = new Node(current->data);
            newNode->next = prev;
            prev = newNode;
            current = current->next;
        }
        return prev;
    }



public:

    class iterator {
    private:
        Node* current;

    public:
        iterator() : current(nullptr) {}
        explicit iterator(Node* node) : current(node) {}
        iterator(const iterator& other) : current(other.current) {}

        iterator& operator++() {
            if (current) current = current->next;
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        int& operator*() {
            return current->data;
        }

        friend bool operator==(const iterator& lhs, const iterator& rhs) {
            return lhs.current == rhs.current;
        }

        friend bool operator!=(const iterator& lhs, const iterator& rhs) {
            return !(lhs == rhs);
        }
    };

    [[nodiscard]] Node * getHead() const {
        return head;
    }

    ~List() {
        delete head;
    }

    List() : head{nullptr}, size{0} {}

    List(const List& a) : head(nullptr), size(0) {
        Node * last = nullptr;
        for (Node * n = a.head; n != nullptr; n = n->next) {
            Node * item = new Node(n->data);
            if (!head) {
                head = item;
            } else {
                last->next = item;
            }
            last = item;
            ++size;
        }
    }

    List(List&& a) noexcept : size(a.size), head(a.head) {
        a.head = nullptr;
    }

    explicit List(size_t n) : head(nullptr), size(n) {
        Node* current = nullptr;
        for (size_t i = 0; i < n; i++) {
            Node* item = new Node(0);
            if (!head) {
                head = item;
                current = head;
            } else {
                current->next = item;
                current = current->next;
            }
        }
    }


    List(const int arr[], size_t n) : head(nullptr), size(0) {
        for (size_t i = 0; i < n; ++i) {
            Node* newNode = new Node(arr[i]);
            if (!head) {
                head = newNode;
            } else {
                Node* temp = head;
                while (temp->next) temp = temp->next;
                temp->next = newNode;
            }
            ++size;
        }
    }

    List(const iterator& begin, const iterator& end) : head(nullptr), size(0) {
        Node* last = nullptr;
        for (auto it = begin; it != end; ++it) {
            Node* newNode = new Node(*it);
            if (!head) {
                head = newNode;
            } else {
                last->next = newNode;
            }
            last = newNode;
            ++size;
        }
    }



    void clear() {
        while (head->next && head) {
            Node * temp = head;
            head = head->next;
            delete temp;
        }
        head = nullptr;
        size = 0;
    }

    int at(int ind) {
        if (ind < 0) {
            ind += size;
        }
        Node* current = head;
        if (ind < 0) {
            return current->data;
        } else if (ind >= size) {
            for (int i = 0; i < size && current->next != nullptr; i++) {
                current = current->next;
            }
        } else {
            for (int i = 0; i < ind; i++) {
                current = current->next;
            }
        }
        return current->data;
    }

    void resize(size_t n) {
        if (n < size) {
            Node* temp = head;
            for (size_t i = 0; i < n - 1 && temp != nullptr; i++) {
                temp = temp->next;
            }
            if (temp != nullptr) {
                Node* del = temp->next;
                temp->next = nullptr;
                while (del != nullptr) {
                    Node* nextNode = del->next;
                    delete del;
                    del = nextNode;
                }
            }
        } else if (n > size) {
            Node* temp = head;
            while (temp && temp->next != nullptr) {
                temp = temp->next;
            }
            for (size_t i = size; i < n; i++) {
                Node* newNode = new Node(0);
                if (temp) {
                    temp->next = newNode;
                } else {
                    head = newNode;
                }
                temp = newNode;
            }
        }
        size = n;
    }

    void assign(size_t count, int value) {
        if (count > size) {
            Node* current = head;
            for (size_t i = 0; i < size && current != nullptr; ++i) {
                current->data = value;
                current = current->next;
            }
            for (size_t i = size; i < count; ++i) {
                Node* newNode = new Node(value);
                if (current) {
                    current->next = newNode;
                } else {
                    head = newNode;
                }
                current = newNode;
            }
        } else if (count < size) {
            Node* current = head;
            for (size_t i = 0; i < count; ++i) {
                current->data = value;
                current = current->next;
            }
            while (current != nullptr) {
                Node* del = current;
                current = current->next;
                delete del;
            }
        } else {
            Node* current = head;
            for (size_t i = 0; i < size && current != nullptr; ++i) {
                current->data = value;
                current = current->next;
            }
        }
        size = count;
    }

    size_t length() {
        return size;
    }

    bool empty() {
        return size == 0;
    }

    void swap(List& a) {
        std::swap(a.size, size);
        std::swap(a.head, head);
    }

    List &operator=(const List& other) {
        if (this != &other) {
            Node* last = nullptr;
            for (Node* n = other.head; n != nullptr; n = n->next) {
                Node* item = new Node(n->data);
                if (!head) {
                    head = item;
                } else {
                    last->next = item;
                }
                last = item;
                ++size;
            }
        }
        return *this;
    }

    List &operator=( List&& other) noexcept {
        if (this != &other) {
            head = other.head;
            size = other.size;
            other.head = nullptr;
            other.size = 0;
        }
        return *this;
    }

    friend bool operator==(const List& a, const List& b) {
        if (a.size != b.size) return false;
        Node* cur1 = a.head;
        Node* cur2 = b.head;
        while (cur1 && cur2) {
            if (cur1->data != cur2->data) return false;
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
        return true;
    }

    friend bool operator!=(const List& a, const List& b) {
        return !(a == b);
    }

    friend bool operator<(const List& a, const List& b) {
        Node* cur1 = a.head;
        Node* cur2 = b.head;
        while (cur1 && cur2) {
            if (cur1->data < cur2->data) return true;
            if (cur1->data > cur2->data) return false;
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
        return a.size < b.size;
    }

    friend bool operator>(const List& a, const List& b) {
        return b < a;
    }

    friend bool operator<=(const List& a, const List& b) {
        return !(b < a);
    }

    friend bool operator>=(const List& a, const List& b) {
        return !(a < b);
    }

    int& operator[](size_t index) {
        Node* current = head;
        for (size_t i = 0; i < index; ++i) current = current->next;
        return current->data;
    }

    const int& operator[](size_t index) const {
        Node* current = head;
        for (size_t i = 0; i < index; ++i) current = current->next;
        return current->data;
    }

    friend std::ostream &operator<<(std::ostream& os, const List& a) {
        Node* current = a.head;
        while (current) {
            os << current->data << " ";
            current = current->next;
        }
        return os;
    }

    friend std::istream &operator>>(std::istream& is, List& a) {
        a.clear();
        int value;
        while (is >> value) {
            Node* newNode = new Node(value);
            if (!a.head) {
                a.head = newNode;
            } else {
                Node* cur = a.head;
                while (cur->next) {
                    cur= cur->next;
                }
                cur->next = newNode;
            }
            ++a.size;
        }
        return is;

    }

    [[nodiscard]] bool contains(int val) const {
        Node* current = head;
        while (current) {
            if (current->data == val) return true;
            current = current->next;
        }
        return false;
    }

    [[nodiscard]] size_t count(const int val) const {
        size_t cnt = 0;
        Node* current = head;
        while (current) {
            if (current->data == val) ++cnt;
            current = current->next;
        }
        return cnt;
    }

    auto begin() {
        return iterator(head);
    }


    auto end() {
        return iterator(nullptr);
    }

    auto rbegin() {
        return iterator(reverseList());
    }

    auto rend() {
        return iterator(nullptr);
    }

    static bool is_equal(const List& a, const List& b) {
        if (a.size != b.size) {
            return false;
        }

        Node* cur1 = a.head;
        Node* cur2 = b.head;
        while (cur1 && cur2) {
            if (cur1->data != cur2->data) {
                return false;
            }
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
        return true;
    }

    void assign(const iterator &begin, const iterator &end) {
        clear();
        Node* last = nullptr;
        for (auto it = begin; it != end; ++it) {
            Node* newNode = new Node(*it);
            if (!head) {
                head = newNode;
            } else {
                last->next = newNode;
            }
            last = newNode;
            ++size;
        }
    }
};




int main(int argc, char const *argv[]) {

    int array[] = {19, 47, 74, 91};

    List a(array, 4);
    for (auto it = a.begin(); it != a.end(); ++it) std::cout << *it << " ";
    cout << endl;

    List b(a.begin(), a.end());
    assert(List::is_equal(a, b));
    for (auto &&it : b) std::cout << it << " ";
    cout << endl;

    List c(b.begin(), b.end());
    assert(std::equal(c.begin(), c.end(), b.begin()));
    for (auto it = c.rbegin(); it != c.rend(); ++it) std::cout << *it << " ";
    cout << endl;

    List d(c.rbegin(), c.rend());
    for (auto &&it : d) std::cout << it << " ";
}