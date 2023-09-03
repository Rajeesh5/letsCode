#include<iostream>
#include<tuple>
#include<variant>

using namespace std;


std::tuple<double, char, std::string> get_student(int id)
{
    if (id == 0) return std::make_tuple(3.8, 'A', "Lisa Simpson");
    if (id == 1) return std::make_tuple(2.9, 'C', "Milhouse Van Houten");
    if (id == 2) return std::make_tuple(1.7, 'D', "Ralph Wiggum");
    throw std::invalid_argument("id");
}





// WARNING: C++17 or above required
template <size_t I = 0, typename... Ts>
constexpr void printTuple(tuple<Ts...> tup)
{
    // If we have iterated through all elements
    //if constexpr (I == sizeof...(Ts)) or,
    if constexpr (I == tuple_size<decltype(tup)>::value)
    {
        // Last case, if nothing is left to
        // iterate, then exit the function
        return;
    }
    else {
        // Print the tuple and go to next element
        cout << get<I>(tup) << " ";

        // Going for next element.
        printTuple<I + 1>(tup);
    }
}


int main() {

    double gpa;
    char grade;
    std::string name;


    try {
        auto student0 = get_student(0);

        std::cout << "ID: 0, "
            << "GPA: "   << std::get<0>(student0) << ", "
            << "grade: " << std::get<1>(student0) << ", "
            << "name: "  << std::get<2>(student0) << endl;

        std::tie(gpa, grade, name) = get_student(1);
        
        
        int i = 0;
        // gpa = std::get<i>(student0);     // Complile time Error!! 
        // Required compile-time constant
        
        constexpr int j = 0;
        gpa = std::get<j>(student0);        //Valid.
        
        // tuple<double, char, std::string> student9 = get_student(9);     // Exception..
        
        std::tuple<std::string, double, double, int> t("123", 4.5, 6.7, 8);
        
        cout << std::get<std::string>(t) << endl;               // return based on type.
        // cout << std::get<double>(t) << endl;                 // if type duplicate, then NA. CompileTime error!!

        
        // Mergeand Iteration
        // Another common requirement is to merge two tuples, which can be done with std::tuple_cat:


        auto new_tuple = std::tuple_cat(get_student(1), std::move(t));

        // This will iterate over the tuple :


        printTuple(new_tuple);
        


    }
    catch (exception ex) {
        cout << ex.what() << endl;
    }

    return 0;

}