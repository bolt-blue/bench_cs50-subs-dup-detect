# Benchmarking Duplicate Detection

Given it's humble origins, this perhaps got a little out of hand.
But it has (hopefully) been good practise for me.


## Background

This started while discussing Harvard `CS50x`'s week two problem set,
`substitution`.

*If `CS50` staff for some reason think this repo should not be public, please
let me know and I'll remove or make it private.*

**WARNING**
```
The following text and this repository itself contain spoilers.
If you come across this while you are taking the `CS50` course and you have
not yet completed the second week, politely bugger off and come back later.
```

The challenge involves detecting duplicates in a 26-character long string.
This `key` is supposed to only contain letters from 'a' to 'z' with no
duplication.

It's generally agreed that the efficient solution by which to check for
duplicates is to use an array whereby we can "check off" letters as we iterate
through the `key`.

This method is (if I'm not mistaken) `O(N)` in the worst case, as at most it requires only one pass
through the entire `key` string.


## Is there a better way?

It was posited that perhaps using a single `uint32` instead of an array of
`char` could be faster.

It would certainly use less memory.

This repo contains my attempt at benchmarking these two methods:
the array vs. the bitflags.

I do not have much experience at all in benchmarking, but am aware that it is
an art that requires skill to achieve meaningful results.
Hopefully I have not made any major screw-ups.

I had a feeling that using a `bitwise` approach would possibly end up being
slower, as I could not invisage a way to do it without adding an extra step
(more instructions) to the process.

It appears that hypothesis was correct.


## Usage

```sh
make
./benchmark
```

Running `make` currently automatically runs some naive tests to first make sure
the functions being benchmarked actually do what they're supposed to.


## Improvements

Please feel free to open an issue to:

- Suggest improvement(s)
- Point out mistakes
- other?
