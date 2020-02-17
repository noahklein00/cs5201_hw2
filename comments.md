-5 m_vector declared in constructors unused and shadows member variable/default constructor declaration of m_data shadows member variable and leaves it uninitialized

-1 The type returned by your interpolation function should be independent of T

-2 op= should return reference

-1 exceptions should always be caught by reference

-2 vector constructor should accept by-reference parameter

-3 interpolation function should be const

-1 don't pollute global namespace

-2 Non-template code should be in cpp file

-4 Custom exception classes should inherit from std::exception

-2 Incomplete preconditions for template parameter

-4 Don't use linear search on sorted data

-1 In iterator-based for loop, use const whenever possible

-3 BoundErr has hardcoded member - should be templated

-1 UML missing directions (in/out)

Excellent use of iterators - consider "auto" so you don't have to type out "typename vector<tuple<T, T, T>>::iterator itr"

68
