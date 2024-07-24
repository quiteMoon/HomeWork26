#include <iostream>

using namespace std;

template <typename T>
class Array {
private:
    T* data;
    int size;
    int capacity;
    int grow;

public:
    Array(int initialCapacity = 10, int initialGrow = 1)
        : size(0), capacity(initialCapacity), grow(initialGrow) {
        if (initialCapacity < 1 || initialGrow < 1) {
            throw invalid_argument("Capacity and grow must be positive integers.");
        }
        data = new T[capacity]();
    }

    Array(const Array& other)
        : size(other.size), capacity(other.capacity), grow(other.grow) {
        data = new T[capacity];
        std::copy(other.data, other.data + size, data);
    }

    Array(Array&& other) noexcept
        : data(other.data), size(other.size), capacity(other.capacity), grow(other.grow) {
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            grow = other.grow;
            data = new T[capacity];
            std::copy(other.data, other.data + size, data);
        }
        return *this;
    }

    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            capacity = other.capacity;
            grow = other.grow;
            other.data = nullptr;
            other.size = 0;
            other.capacity = 0;
        }
        return *this;
    }

    ~Array() {
        delete[] data;
    }

    int GetSize() const {
        return size;
    }

    void SetSize(int newSize, int newGrow = 1) {
        if (newSize < 0 || newGrow < 1) {
            throw invalid_argument("Size must be non-negative and grow must be a positive integer.");
        }
        if (newSize > capacity) {
            int newCapacity = capacity + (newSize - capacity + newGrow - 1) / newGrow * newGrow;
            T* newData = new T[newCapacity];
            std::copy(data, data + size, newData);
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }
        size = newSize;
        grow = newGrow;
    }

    int GetUpperBound() const {
        return size - 1;
    }

    bool IsEmpty() const {
        return size == 0;
    }

    void FreeExtra() {
        if (size < capacity) {
            T* newData = new T[size];
            std::copy(data, data + size, newData);
            delete[] data;
            data = newData;
            capacity = size;
        }
    }

    void RemoveAll() {
        delete[] data;
        size = 0;
        capacity = 10; 
        data = new T[capacity]();
    }

    T GetAt(int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range.");
        }
        return data[index];
    }

    void SetAt(int index, const T& value) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range.");
        }
        data[index] = value;
    }

    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range.");
        }
        return data[index];
    }

    void Add(const T& value) {
        if (size >= capacity) {
            SetSize(size + grow);
        }
        data[size++] = value;
    }

    void Append(const Array& other) {
        if (this == &other) {
            Array tmp(other);
            Append(tmp);
            return;
        }

        int newSize = size + other.size;
        SetSize(newSize);
        copy(other.data, other.data + other.size, data + size);
        size = newSize;
    }

    void InsertAt(int index, const T& value) {
        if (index < 0 || index > size) {
            throw out_of_range("Index out of range.");
        }
        if (size >= capacity) {
            SetSize(size + grow);
        }
        for (int i = size; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        ++size;
    }

    void RemoveAt(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range.");
        }
        for (int i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        --size;
    }

    T* GetData() const {
        return data;
    }
};

int main() {
    try {
        Array<int> arr;
        arr.Add(1);
        arr.Add(2);
        arr.Add(3);

        cout << "Array size: " << arr.GetSize() << endl;
        cout << "Element at index 1: " << arr.GetAt(1) << endl;

        arr.InsertAt(1, 10);
        cout << "After inserting 10 at index 1: ";
        for (int i = 0; i < arr.GetSize(); ++i) {
            cout << arr.GetAt(i) << " ";
        }
        cout << endl;

        arr.RemoveAt(2);
        cout << "After removing element at index 2: ";
        for (int i = 0; i < arr.GetSize(); ++i) {
            cout << arr.GetAt(i) << " ";
        }
        cout << endl;

        arr.SetSize(5);
        cout << "After resizing array to 5: ";
        for (int i = 0; i < arr.GetSize(); ++i) {
            cout << arr.GetAt(i) << " ";
        }
        cout << endl;

        Array<int> arr2;
        arr2.Add(100);
        arr2.Add(200);

        arr.Append(arr2);
        cout << "After appending arr2: ";
        for (int i = 0; i < arr.GetSize(); ++i) {
            cout << arr.GetAt(i) << " ";
        }
        cout << endl;

        arr.RemoveAll();
        cout << "After removing all elements: ";
        for (int i = 0; i < arr.GetSize(); ++i) {
            cout << arr.GetAt(i) << " ";
        }
        cout << endl;
    }
    catch (const exception& e) {
        cout << "Exception: " << e.what() << endl;
    }
}
