#include <cstdlib>
#include <cstring>
#include <vector>

#include <Acorn/Templates/ArrayList.hpp>
#include <Acorn/Templates/UniquePtr.hpp>
#include <Acorn/Templates/String.hpp>

#include "RuntimeTests.hpp"
#include "UnitTest.hpp"

namespace Acorn
{
    bool compareArrayList(std::vector<int>& vec, ArrayList<int>& arr)
    {
        if (vec.size() != arr.getSize())
            return false;

        for (size_t i = 0; i < vec.size(); ++i)
        {
            if (vec[i] != arr[i])
                return false;
        }

        return true;
    }

    void addRuntimeTests(UnitTester& tester)
    {
        srand(time(nullptr));

        tester.addTest(UnitTest
        {
            .name = "ArrayList list initializer constructor test",
            .testFn = []() -> bool
            {
                std::vector<int> a{{10, 20, 30}};
                ArrayList<int> b{{10, 20, 30}};

                return a.size() == b.getSize() &&
                       a.capacity() == b.getCapacity();
            }
        });

        tester.addTest(UnitTest
        {
            .name = "ArrayList capacity constructor test",
            .testFn = []() -> bool
            {
                size_t size = rand() % 99 + 1;

                ArrayList<int> l{};
                l.setCapacity(size);

                return l.getCapacity() == size;
            }
        });

        tester.addTest(UnitTest
        {
            .name = "ArrayList simple insertion test",
            .testFn = []() -> bool
            {
                std::vector<int> vec{};
                ArrayList<int> arr{};

                for (size_t i = 0; i < 10; ++i)
                {
                    int val = rand() % 100;
                    vec.push_back(val);
                    arr.append(val);
                }

                for (size_t i = 0; i < 10; ++i)
                {
                    size_t idx = rand() % vec.size();
                    int val = rand() % 200;

                    vec.insert(vec.begin() + idx, val);
                    arr.insert(idx, val);
                }

                return compareArrayList(vec, arr);
            }
        });

        tester.addTest(UnitTest
        {
            .name = "ArrayList iterator insertion test",
            .testFn = []() -> bool
            {
                std::vector<int> vec{};
                ArrayList<int> arr{};

                for (size_t i = 0; i < 10; ++i)
                {
                    int val = rand() % 100;
                    vec.push_back(val);
                    arr.append(val);
                }

                std::vector<int> insertVec{};
                for (size_t i = 0; i < 10; ++i)
                    insertVec.push_back(rand() % 150);

                ArrayList<int> insertList{};
                for (const auto& val: insertVec)
                    insertList.append(val);

                if (!compareArrayList(insertVec, insertList))
                    return false;

                size_t pos = rand() % vec.size();
                vec.insert(vec.begin() + pos, insertVec.begin(), insertVec.end());
                arr.insert(pos, insertList.begin(), insertList.end());

                return compareArrayList(vec, arr);
            }
        });

        tester.addTest(UnitTest
        {
            .name = "ArrayList simple copy operator test",
            .testFn = []() -> bool
            {
                ArrayList<int> l{};
                for (size_t i = 0; i < 10; ++i)
                    l.append(rand() % 50);

                ArrayList<int> other = l; // Copy

                // Maybe this test could be extended
                return memcmp(&l[0], &other[0], l.getSize() * sizeof(int)) == 0;
            }
        });

        tester.addTest(UnitTest
        {
            .name = "ArrayList simple move operator test",
            .testFn = []() -> bool
            {
                ArrayList<int> l{};
                for (size_t i = 0; i < 10; ++i)
                    l.append(rand() % 100);

                const size_t oldSize = l.getSize();

                ArrayList<int> stealer = std::move(l);

                return l.getData() == nullptr &&
                       l.getCapacity() == 0 &&
                       l.getSize() == 0 &&
                       stealer.getSize() == oldSize;
            }
        });

        tester.addTest(UnitTest
        {
            .name = "UniquePtr ownership transfer test",
            .testFn = []() -> bool
            {
                UniquePtr<int> myInt = mem_new<int>(10);
                UniquePtr<int> stealer = std::move(myInt);

                return !myInt && (*stealer == 10);
            }
        });

        tester.addTest(UnitTest
        {
            .name = "UniquePtr copy test",
            .testFn = []() -> bool
            {
                UniquePtr<int> myInt = UniquePtr<int>::create(10);
                UniquePtr<int> clone = myInt;

                return myInt.getPtr() != nullptr && *myInt == 10 && *clone == 10 && myInt.getPtr() != clone.getPtr();
            }
        });

        tester.addTest(UnitTest
        {
            .name = "String const char* initialization test",
            .testFn = []() -> bool
            {
                String str = "Hello, World!";

                return str.getSize() == 13 && strcmp(str.getData(), "Hello, World!") == 0;
            }
        });

        tester.addTest(UnitTest
        {
            .name = "String append test",
            .testFn = []() -> bool
            {
                String str = "Hello, Worl";
                str.append('d');
                str.append('!');

                return strcmp(str.getData(), "Hello, World!") == 0;
            }
        });

        tester.addTest(UnitTest
        {
            .name = "String concatenation test",
            .testFn = []() -> bool
            {
                String str = "Hello";
                str += ", World";
                str += "!";

                return strcmp(str.getData(), "Hello, World!") == 0;
            }
        });

        tester.addTest(UnitTest
        {
            .name = "String substring test",
            .testFn = []() -> bool
            {
                String str = "Hello, World!";
                std::string realStr = "Hello, World!";

                auto subStr1 = str.substring(7, 6);
                auto subStr2 = realStr.substr(7, 6);

                return strcmp(subStr1.getData(), subStr2.c_str()) == 0;
            }
        });
    }
}
