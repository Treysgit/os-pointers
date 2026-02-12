// compile: g++ -std=c++14 -o pointers pointers.cpp
#include <iostream>
#include <string>

#include <iomanip>

typedef struct Student {
    int id;
    char *f_name;
    char *l_name;
    int n_assignments;
    double *grades;
} Student;

int promptInt(std::string message, int min, int max);
double promptDouble(std::string message, double min, double max);
void calculateStudentAverage(void *object, double *avg);

int main(int argc, char **argv)
{
    Student student;

    // Sequence of user input -> store in fields of `student`
    // Call `CalculateStudentAverage(???, ???)`
    // Output `average`

    // Send args to prompt function. With proper max and min
    student.id = promptInt("Please enter the student's id number: ", 0, 999999999);

    // Since we can assume the first and last name are <128 chars, we can
    // declare char array sizes
    student.f_name = new char[128]; // note char array needs '\0' to indicate end of string
    student.l_name = new char[128];

    std::cout << "Please enter the student's first name: ";
    std::cin.getline(student.f_name, 128); // reads first 127 chars of line into a char array and ends with \0

    std::cout << "Please enter the student's last name: ";
    std::cin.getline(student.l_name, 128);

    // Send args to prompt function. With proper max and min
    student.n_assignments = promptInt("Please enter how many assignments were graded: ", 1, 134217727);
    
    // Dynamically allocate memory for array of grades
    student.grades = new double[student.n_assignments];

    std::cout << "\n"; // empty space

    for(int i = 0 ; i < student.n_assignments ; i++){
        // send over correct args to promptDouble -- store each respective result in grades array
        student.grades[i] = promptDouble("Please enter grade for assignment " + std::to_string(i) + ": ", 0.0, 1000.0);

    }

    double average; 
    Student *p = &student; //*p -> student, p = &student
    void *p_v = (void*) p;  // Makes student pointer *p typeless

    // Send address of 'student' and address of 'average' as pass-by-values
    // so 'student' and 'average' can be altered at the function.
    calculateStudentAverage(p_v, &average);

    std::cout << "\n";
    std::cout << "Student: " << student.f_name << " " << student.l_name << " [" << student.id << "]\n";
    std::cout << "  Average grade: " << std::fixed << std::setprecision(1) << average << "\n";

    //clear dynamically allocated memory
    delete[] student.f_name;
    delete[] student.l_name;
    delete[] student.grades;

    
    return 0;
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid int
   max: maximum value to accept as a valid int
*/
int promptInt(std::string message, int min, int max)
{
    // Code to prompt user for an int
    int userVal;

    while(true){
        std::cout << message; // initial prompt

        // check if type is correct 
        if(!(std::cin >> userVal)){
            std::cout << "Sorry, I cannot understand your answer" << std::endl;
            std::cin.clear(); // allow cin to read input again (fail state)
            std::cin.ignore(1000000, '\n'); //clear input buffer
            continue; // Jump back to the top of loop
        }
        char nextChar = std::cin.peek();
        // check if nextChar is a space or tab. Skip and grab the subsequent char
        while((nextChar == ' ')||(nextChar == '\t')){
            std::cin.get(); //consume the left over space/tab
            nextChar = std::cin.peek(); //store the next char and repeat if tab/space

        }
        // if user entered "123ABC\n" --> 'A' is not \n
        if(nextChar != '\n'){
            std::cout << "Sorry, I cannot understand your answer" << std::endl;
            std::cin.ignore(1000000, '\n');
            continue;
        }
        if((userVal < min) || (userVal > max)){
            std::cout << "Sorry, I cannot understand your answer" << std::endl;
            std::cin.ignore(1000000, '\n'); //clear input buffer
            continue; //jump back to top
        }

        // clear trailing \n
        std::cin.ignore(); 
        return userVal;

        


    }

    
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid double
   max: maximum value to accept as a valid double
*/
double promptDouble(std::string message, double min, double max)
{
    // Code to prompt user for a double
    double userVal;
    while(true){
        std::cout << message; // initial prompt

        // check if type is correct 
        if(!(std::cin >> userVal)){
            std::cout << "Sorry, I cannot understand your answer" << std::endl;
            std::cin.clear(); // allow cin to read input again (fail state)
            std::cin.ignore(1000000, '\n'); //clear input buffer
            continue; // Jump back to the top of loop
        }
        char nextChar = std::cin.peek();
        // check if nextChar is a space or tab. Skip and grab the subsequent char
        while((nextChar == ' ')||(nextChar == '\t')){
            std::cin.get(); //consume the left over space/tab
            nextChar = std::cin.peek(); //store the next char and repeat if tab/space

        }
        // if user entered "12.93ABC\n" --> 'A' is not \n
        if(nextChar != '\n'){
            std::cout << "Sorry, I cannot understand your answer" << std::endl;
            std::cin.ignore(1000000, '\n');
            continue;
        }
        if((userVal < min) || (userVal > max)){
            std::cout << "Sorry, I cannot understand your answer" << std::endl;
            std::cin.ignore(1000000, '\n'); //clear input buffer
            continue; //jump back to top
        }

        // clear trailing \n
        std::cin.ignore(); 
        return userVal;

        


    }


}

/*
   object: pointer to anything - your choice! (but choose something that will be helpful)
   avg: pointer to a double (can store a value here)
*/
void calculateStudentAverage(void *object, double *avg){
    // call-by-value: object = &student, avg = &average

    Student *z = (Student*) object; // *z = student, z = &student

    double sum = 0.0;
    // sum up each respective grade in array -- note the shorthand for pointer z (*z. == z->)
    for(int i = 0 ; i < z->n_assignments ; i++){
        sum += z->grades[i];
    }

    *avg = (sum)/(z->n_assignments); // calculate the average


}
    // Code to calculate and store average grade
    

