import itertools
import sys

input_stream = itertools.chain.from_iterable(line.split() for line in sys.stdin)

n = int(next(input_stream))
digits = [next(input_stream) for _ in range(n)]

best_start = 0 # Starting index of the biggets number
best_length = 1 # Length of the biggest number

start = 0
while start < n: # Find longest number starting at index start
    if digits[start] == '0': # don't process numbers starting with 0
        start += 1
        continue
    
    segment_start = start
    segment_end = start
    while segment_end < n and digits[segment_end] == digits[segment_start]:
        segment_end += 1
    needed_segment_length = segment_end - segment_start
    
    #try to append more segments to the number
    current_segment_length = needed_segment_length
    while current_segment_length == needed_segment_length:
        segment_start = segment_end
        #after the while, segment_end will point to the index AFTER the last digits of the segment
        while segment_end < n and digits[segment_end] == digits[segment_start]:
            segment_end += 1
        current_segment_length = segment_end - segment_start
    
    if current_segment_length > needed_segment_length:
        number_length = segment_start + needed_segment_length - start # we can include part of another segment
    else:
        number_length = segment_start - start #exclude the last segment

    if number_length > best_length:
        best_length = number_length
        best_start = start
    elif number_length == best_length:
        better = False
        for i in range(number_length):
            if digits[best_start + i] < digits[start + i]:
                better = True
                break
            elif digits[best_start + i] > digits[start + i]:
                break
        if better:
            best_length = number_length
            best_start = start

    if needed_segment_length == number_length and current_segment_length < needed_segment_length:
        start += needed_segment_length - current_segment_length # for single-number segments, try to use smaller part of the first
    else:
        start = segment_start
    
print(''.join(digits[best_start:best_start + best_length]))

