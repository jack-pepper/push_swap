# push_swap

## Description
`push_swap` is a project that implements an algorithm to sort a list of integers using a limited set of operations. The challenge is to sort them with the least number of operations, making the project both about algorithmic efficiency and understanding stack-based data structures. The operations allowed are stack manipulations such as pushing, rotating, reverse rotating and swapping.

To get familiar with various sorting algorithms (bubble sort, insert sort, select sort, merge sort, quick sort, heap sort...) and extend my C toolbox, I wrote the library LIBSORT during the course of this project.

## Table of Contents
- [Usage](#usage)
- [Features](#features)
- [Contributing](#contributing)
- [Acknowledgments](#acknowledgments)

## Usage

Once the project is compiled, you can use the `push_swap` executable. Here's how to run it:

```bash
./push_swap <list_of_integers>
```
where <list_of_integers> is a space-separated list of integers to be sorted (1 -3 5 4 -2).
It can be a string with space-separated integers as well ("-1 3 5 -4 2").

The program will output the sequence of operations that sorts the list.

You can also visualize these operations using a visualizer and check the efficiency of the program.

## Features

### Parsing:
I dramatically improved my first parsing solution after a colleague identified critical flaws within seconds. The arguments are now properly sanitized by removing leading "+" signs and trimming leading zeros. Each argument is then validated to ensure it can be safely converted into an integer. Invalid inputs such as non-integer or duplicate values, are handled.

### Indexing for sorting:
While converting the arguments, I assign each element the index of its position in the sorted order. This strategy significantly enhanced debugging, making the process more manageable and enjoyable by providing clear, easy-to-track indices that correspond to the final sorted order instead of more complex values.

### Sorting algorithm:
- The sorting begins with stack a.
- A pivot value is calculated as the square root of the number of elements in the stack.
- The lowest element is identified, and the range for rotation is set by defining the maximum as lowest + pivot.
- The sorting process continues as long as the stack is unsorted and contains more than 3 elements:
- For each element, the shortest distance to any number within the defined range [min, max] is calculated.
- The optimal move is determined, and the necessary rotations are applied to bring the target element to the top of stack a. If there is another element that belongs in this range, it is pushed to stack b as well.
- Once the process narrows down to 3 elements, these are sorted directly with the minimum possible moves.
- The focus shifts to stack b.
- While stack b contains more than 3 elements:
- The highest element in stack b is identified.
- The optimal rotation move is calculated to bring this element to the top of stack b. If another element is in the way, it is pushed to stack a.
- If a new element is pushed to stack a and it is smaller than the previously placed element, a swap is performed in stack a to maintain order.
- Finally, once only 3 elements remain in stack b, they are sorted directly and pushed back to stack a.

My average scores:
- 7 for a random list of 5 integers
- 684 for a random list of 100 integers
- 7871 for a random list of 500 integers

## Contributing
Contributions to push_swap are welcome! If you have improvements, optimizations, or bug fixes, feel free to fork the repository and submit a pull request.
I would be more than enthuasistic to discover a way to reduce my average number of moves even further.

### To contribute:
- Fork the repository.
- Create a new branch for your changes.
- Make your modifications.
- Commit your changes.
- Push your changes to your forked repository.
- Submit a pull request.

## Acknowledgments
Thanks to the stud who forced me to improve my parsing by rewriting a third of my code and learning a lot during the proccess.
