*This project has been created as part of the 42 curriculum by jagrund, havu.*

# push_swap

## Description

**Goal:** sort a list of unique integers into ascending order using two stacks
(`a` and `b`) and a fixed set of 11 operations, printing the shortest sequence
of operations we can find.

At start, `a` holds the input (first argument on top) and `b` is empty. At the
end, `a` must be sorted with the smallest value on top, and `b` empty.

| Op | Effect |
|----|--------|
| `sa` `sb` `ss` | swap the top two elements of a / b / both |
| `pa` `pb` | move the top of b onto a / the top of a onto b |
| `ra` `rb` `rr` | rotate up: first element becomes last |
| `rra` `rrb` `rrr` | reverse rotate: last element becomes first |

The program embeds **four strategies**, one per complexity class, plus a
disorder metric used to choose between them automatically. Complexity is
always measured in **number of push_swap operations generated**, not in the
cost of a classic array-based algorithm.

## Instructions

### Build

```sh
make        # builds ./push_swap
make clean  # removes object files
make fclean # removes objects and the binary
make re     # fclean + all
```

### Run

```sh
./push_swap [strategy] [--bench] <int> <int> ...
```

| Flag | Meaning |
|------|---------|
| `--simple` | force the O(n²) strategy |
| `--medium` | force the O(n√n) strategy |
| `--complex` | force the O(n log n) strategy |
| `--adaptive` | choose a method from the input's disorder (**default**) |
| `--bench` | print statistics to **stderr** after sorting |

Operations are written to **stdout**, one per line. Flags may appear anywhere
in the argument list.

- No arguments: prints nothing.
- Invalid input (non-integer, outside the `int` range, duplicates): prints
  `Error` on stderr and exits with status 1.

### Examples

```sh
$ ./push_swap 2 1 3 6 5 8
$ ARG="4 67 3 87 23"; ./push_swap --complex $ARG | ./checker_linux $ARG
OK
$ ARG=$(shuf -i 0-9999 -n 500 | tr '\n' ' '); ./push_swap $ARG | wc -l
$ ./push_swap --bench --adaptive $ARG 2> bench.txt >/dev/null
```

`--bench` output (stderr):

```
[bench] disorder: 49.93%
[bench] strategy: Adaptive / O(n√n)
[bench] total_ops: 7997
[bench] sa: 0  sb: 0  ss: 0  pa: 500  pb: 500
[bench] ra: 4840  rb: 1098  rr: 0  rra: 0  rrb: 1059  rrr: 0
```

### Project layout

```
includes/push_swap.h   types (t_ctx, t_node, t_op) and prototypes
src/main.c             entry point, strategy dispatch
src/parse.c            argument + flag parsing and validation
src/stack*.c           stack primitives (no printing, no counting)
src/normalize.c        replaces each value by its rank (0..n-1)
src/ops.c              do_op(): the single place that applies, counts and prints a move
src/disorder.c         disorder metric
src/bench.c            --bench output
src/strat_*.c          the four strategies
```

All algorithms call `do_op()` and never touch the stacks directly, so the
operation count and output are always consistent. There are no global
variables: state lives in a `t_ctx` passed by pointer.

## Algorithms

### Preprocessing: rank normalization

Before sorting, every value is replaced by its **rank** (its position in the
sorted input, `0..n-1`). The strategies work on ranks, so they can use bit
operations and fixed-size ranges regardless of the actual values (negatives
included).

### Disorder metric

Disorder is the fraction of pairs that are out of order:

```
disorder = inversions / (n(n-1)/2)        in [0, 1]
```

`0` means already sorted, `1` means reverse-sorted. A uniformly random
permutation sits around `0.5`. It costs O(n²) comparisons but is computed once,
before any move, and does not count as push_swap operations.

### 1. Simple: O(n²)

> TODO: confirm the variant you implemented.

Selection-style sort: repeatedly rotate the smallest remaining element to the
top of `a` (using `ra` or `rra`, whichever is shorter), push it to `b`, and
finally push everything back to `a`.

- **Time:** n elements, each needing at most ⌊n/2⌋ rotations, plus 2n pushes →
  O(n²) operations.
- **Space:** O(n) for the two stacks; O(1) additional.
- **Why:** trivial to reason about and very good when the input is already
  nearly sorted.

### 2. Medium: O(n√n)

> TODO: confirm chunk size and the pull-back rule.

Chunk-based sort. The ranks are split into about √n ranges. Chunk by chunk,
elements whose rank belongs to the current chunk are pushed to `b`, rotating
`a` as needed. Because chunks are pushed in increasing order, `b` ends up as
contiguous blocks, ordered by chunk. Then the maximum is repeatedly brought to
the top of `b` (`rb` or `rrb`, whichever is shorter) and pushed back to `a`.

- **Time:** distributing needs O(n) pushes with O(√n) rotation each (the next
  matching element is at most a chunk away on average); pulling back needs the
  maximum, which lies inside one √n-sized block, so O(√n) rotations per
  element. Total O(n√n).
- **Space:** O(n) for the stacks; O(1) additional.

### 3. Complex: O(n log n)

> TODO: confirm radix variant and any optimizations applied.

Binary LSD radix sort on ranks. For each bit from least to most significant:
for each of the n elements, `pb` if the bit is 0, otherwise `ra`; then `pa`
everything back from `b`. The number of passes is ⌈log₂ n⌉.

- **Time:** ⌈log₂ n⌉ passes × O(n) operations per pass → O(n log n).
- **Space:** O(n) for the stacks; O(1) additional.
- **Trade-off:** its cost barely depends on how sorted the input already is,
  which makes it a poor choice for low-disorder inputs.

### 4. Adaptive

The adaptive strategy measures the disorder first and picks a method whose
complexity class matches the subject's targets:

| Disorder | Method (TODO: confirm) | Target class |
|----------|------------------------|--------------|
| `< 0.2` | TODO | O(n²) |
| `0.2 ≤ d < 0.5` | TODO | O(n√n) |
| `≥ 0.5` | TODO | O(n log n) |

**Why these thresholds:** TODO. Note that a uniformly random input has
disorder close to 0.5, so random inputs land on either side of the second
threshold. Both the medium and the complex method therefore have to meet the
random-input benchmarks.

**Complexity argument:** each regime inherits the bound of the method it
dispatches to; the disorder computation itself is outside the operation model.
TODO: add the upper bound for space and any extra work in the adaptive wrapper.

## Performance

Required targets (random inputs, verified with the provided checker):

| n | pass | good | excellent |
|---|------|------|-----------|
| 100 | < 2000 | < 1500 | < 700 |
| 500 | < 12000 | < 8000 | < 5500 |

Our results, averaged over TODO random runs:

| Strategy | n = 100 | n = 500 |
|----------|---------|---------|
| `--simple` | TODO | TODO |
| `--medium` | TODO | TODO |
| `--complex` | TODO | TODO |
| `--adaptive` | TODO | TODO |

## Testing

```sh
ARG=$(shuf -i 0-9999 -n 100 | tr '\n' ' ')
./push_swap $ARG | ./checker_linux $ARG      # expect OK
./push_swap $ARG | wc -l                      # operation count
./push_swap 1 2 two                           # expect Error on stderr
./push_swap 1 2 2                             # duplicate -> Error
./push_swap 2147483648                        # overflow -> Error
```

TODO: list any test script you add, and edge cases covered (1 element,
already sorted, reverse sorted, INT_MIN / INT_MAX, 2 and 3 elements).

## Contributions

- **<login1>:** TODO
- **<login2>:** TODO

Both authors understand and can explain every part of the code.

## Resources

- Subject: *push_swap*, 42 curriculum (v1.2)
- Big-O notation and algorithmic complexity: TODO link of your choice
- Radix sort, selection sort and chunk/bucket approaches: TODO the articles you actually read

### Use of AI

- The initial project skeleton (directory layout, Makefile, header, stubbed
  source files, and the first draft of this README) was generated with an AI
  assistant (Claude) from the subject PDF.
- TODO: list every other use honestly (e.g. explanations of radix sort,
  debugging help, test ideas), saying which parts of the project each touched.
- All AI-generated content was reviewed, tested and understood by both
  authors before being kept. TODO: only keep this sentence if it is true.
