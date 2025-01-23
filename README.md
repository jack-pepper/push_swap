# push_swap

## Description
`push_swap` is a project that implements an algorithm to sort a list of integers using a limited set of operations. The challenge is to sort them with the least number of operations, making the project both about algorithmic efficiency and understanding stack-based data structures.

The operations allowed are stack manipulations such as pushing, rotating, reverse rotating and swapping.

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

The program will output the sequence of operations that sorts the list. You can also visualize these operations using a visualizer.

## Features
Implements an efficient algorithm to sort a list of integers with minimal operations.
Only uses stack operations (sa, sb, pa, pb, ra, rb, rra, rrb).
Optimized for performance on large datasets.

My average scores:
- 7 for a random list of 5 integers
- 688 for a random list of 100 integers
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
Thanks to my cat for warming me up when I was losing my mind on this project.
